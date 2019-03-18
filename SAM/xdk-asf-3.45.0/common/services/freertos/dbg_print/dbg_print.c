/**
 * \file
 *
 * \brief Debug print implementation
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "dbg_print.h"
#include <gclk.h>
#include <sercom.h>
#include <status_codes.h>
#include <string.h>
#include <system.h>
#include <usart.h>

#if defined(__FREERTOS__) || defined(__DOXYGEN__)
# include <FreeRTOS.h>
# include <semphr.h>
# include <task.h>
#endif


//! \name Convenience macros
//@{

//! Size of print buffer (must be power of 2)
#define DBG_BUFFER_SIZE   (CONF_DBG_PRINT_BUFFER_SIZE)
#if DBG_BUFFER_SIZE & (DBG_BUFFER_SIZE - 1)
#  error Size of debug UART buffer must be a power of 2!
#endif
/**
 * \brief Maximum number of simultaneously queued bytes in print buffer
 *
 * \note This number is one less than the size of the buffer due to its circular
 * nature. Otherwise, it would be impossible to tell whether the buffer is full
 * or empty as computed in \ref _dbg_get_free_buffer_space().
 */
#define DBG_BUFFER_SPACE  (DBG_BUFFER_SIZE - 1)
//! Bitmask for print buffer head and tail
#define DBG_BUFFER_MASK   (DBG_BUFFER_SIZE - 1)
/**
 * \brief Type for buffer space and indexes
 *
 * \note This type must have at least as many bits as \ref DBG_BUFFER_SPACE.
 */
#if (DBG_BUFFER_SIZE <= 256)
	typedef uint8_t dbg_buffer_space_t;
#elif (DBG_BUFFER_SIZE <= 65536)
	typedef uint16_t dbg_buffer_space_t;
#else
	typedef uint32_t dbg_buffer_space_t;
#endif
//! Translate nibble (4-bit) value to ASCII symbol
#define TRANSLATE_NIBBLE_TO_ASCII(nibble_var) \
		(nibble_var) += ((nibble_var) < 0x0a) ? '0' : ('A' - 0x0a)

//@}

//! \name Internal data
//@{

//! Pointer to SERCOM USART instance to use
static SercomUsart *const sercom_uart = &(CONF_DBG_PRINT_SERCOM->USART);
//! Circular print buffer
static uint8_t dbg_buffer[DBG_BUFFER_SIZE];
//! Print buffer head (write index)
static dbg_buffer_space_t buffer_head;
//! Print buffer tail (read index)
static dbg_buffer_space_t buffer_tail;
//! Variable for buffer space requests
static dbg_buffer_space_t requested_space;

#if defined(__FREERTOS__) || defined(__DOXYGEN__)
//! Mutex to prevent concurrent writes to print buffer
static xSemaphoreHandle dbg_is_free;
//! Semaphore to signal buffer has requested space
static xSemaphoreHandle requested_space_is_free;
#else
static volatile bool requested_space_is_free;
#endif

//@}

//! \name Access lock/unlock
//@{

/**
 * \brief Wait indefinitely to lock access
 *
 * This function will try to take the \ref dbg_is_free mutex, and will wait an
 * indefinite amount of time for it.
 */
static inline void _dbg_wait_for_lock(void)
{
#if defined(__FREERTOS__) || defined(__DOXYGEN__)
	xSemaphoreTake(dbg_is_free, portMAX_DELAY);
#endif
}

//! Unlock access
static inline void _dbg_unlock(void)
{
#if defined(__FREERTOS__) || defined(__DOXYGEN__)
	xSemaphoreGive(dbg_is_free);
#endif
}

//@}

//! \name UART start/stop
//@{

//! Start UART by enabling DRE interrupt
static inline void _dbg_start_uart(void)
{
	sercom_uart->INTENSET.reg = SERCOM_USART_INTFLAG_DRE;
}

//! Stop UART by disabling DRE interrupt
static inline void _dbg_stop_uart(void)
{
	sercom_uart->INTENCLR.reg = SERCOM_USART_INTFLAG_DRE;
}

//@}

//! \name Internal buffer helpers
//@{

/**
 * \brief Get current space in print buffer
 *
 * \return Number of free bytes in buffer.
 */
static inline dbg_buffer_space_t _dbg_get_free_buffer_space(void)
{
	dbg_buffer_space_t temp;

	temp = buffer_head - buffer_tail;
	temp &= (DBG_BUFFER_MASK);

	return DBG_BUFFER_SPACE - temp;
}

/**
 * \brief Write string to the print buffer
 *
 * This is a helper function for copying a string into the print buffer, using
 * circular buffer indexing.
 *
 * \param[in] str Pointer to string to write into buffer.
 * \paran[in] length Number of string bytes to write.
 *
 * \note This function does not check if the specified length is larger than the
 * free space in the print buffer. That must be checked by the calling code.
 */
static inline void _dbg_write_str_to_buffer(const char *str,
		dbg_buffer_space_t length)
{
	Assert(str);

	while (length--) {
			dbg_buffer[buffer_head++] = (uint8_t)*(str++);
			buffer_head &= DBG_BUFFER_MASK;
	}
}

/**
 * \brief Issue request for free buffer space
 *
 * This function will issue a request for \ref _dbg_interrupt_handler() to
 * notify when either the specified number or all (\ref DBG_BUFFER_SPACE) bytes
 * have been freed in a full buffer, depending on which is smaller. The number
 * of bytes that were actually requested is returned by this function.
 *
 * \param[in] length Desired number of bytes to free up.
 *
 * \return The number of bytes which were requested
 * \retval DBG_BUFFER_SPACE if length was greater than what buffer can contain.
 * \retval length if desired length is less than DBG_BUFFER_SPACE.
 *
 * \attention The print buffer should be full when this function is called
 *    because requesting more buffer space than is currently used in will cause
 *    \ref _dbg_wait_for_requested_space() to never return.
 *
 * \pre \ref _dbg_stop_uart() must be called before this function.
 * \post \ref _dbg_wait_for_requested_space() must be used to detect when the
 *    space has been freed.
 */
static inline dbg_buffer_space_t _dbg_request_free_space(
		dbg_buffer_space_t length)
{
	length = min(DBG_BUFFER_SPACE, length);

	requested_space = length;

	return length;
}

/**
 * \brief Wait for requested space to free up
 *
 * This function will wait indefinitely for \ref _dbg_interrupt_handler() to
 * free up the number of bytes requested earlier using
 * \ref _dbg_request_free_space() in the print buffer.
 *
 * \attention If the previous call to \ref _dbg_request_free_space() returned 0,
 *    this function must not be called, because it will never return.
 *
 * \pre \ref _dbg_request_free_space() must be called before this function.
 * \pre \ref _dbg_start_uart() must be called before this function, for the
 *    buffer to be processed and space freed up.
 */
static inline void _dbg_wait_for_requested_space(void)
{
#if defined(__FREERTOS__) || defined(__DOXYGEN__)
	xSemaphoreTake(requested_space_is_free, portMAX_DELAY);
#else
	do {
	} while (!requested_space_is_free);
	requested_space_is_free = false;
#endif
}

/**
 * \brief Put a string into the print buffer
 *
 * This function puts a string into the print buffer, taking care to not exceed
 * the buffer's free space. If the buffer becomes full, this function will start
 * the UART and wait for enough space to free up until the entire string has
 * been put into buffer.
 *
 * \param[in] str Pointer to string to put into the print buffer.
 * \param[out] length Length of the string to put into the print buffer.
 */
static inline void _dbg_putstr(const char *str, size_t length)
{
	dbg_buffer_space_t write_length;

	_dbg_stop_uart();

	// Write entire string, or as much as will fit into buffer
	write_length = _dbg_get_free_buffer_space();
	if (write_length) {
		write_length = min(write_length, length);

		_dbg_write_str_to_buffer(str, write_length);
		length -= write_length;
		str += write_length;
	}

	// If we need to request more buffer space, set it up before starting UART.
	write_length = _dbg_request_free_space(length);

	_dbg_start_uart();

	while (length) {
		_dbg_wait_for_requested_space();

		_dbg_stop_uart();

		_dbg_write_str_to_buffer(str, write_length);
		length -= write_length;
		str += write_length;

		// Do another space request
		write_length = _dbg_request_free_space(length);

		_dbg_start_uart();
	}
}

//@}

/**
 * \brief SERCOM UART interrupt handler
 *
 * This interrupt handler will transmit bytes from the internal print buffer
 * until the tail (read-index) catches up with the head (write-index), at
 * which point it will disable itself since the entire buffer will have been
 * transmitted.
 *
 * If a print function has requested more space in the buffer, this interrupt
 * handler will also track the number of bytes that have been transmitted and
 * give the mutex when the request has been fulfilled.
 *
 * \param dummy Not used. (SERCOM number passed from master interrupt handler.)
 */
static void _dbg_interrupt_handler(uint8_t dummy)
{
	uint8_t data;

	// First, read out next byte to send
	data = dbg_buffer[buffer_tail++];
	buffer_tail &= DBG_BUFFER_MASK;

	// Disable DRE if it was the last byte to send
	if (buffer_tail == buffer_head) {
		sercom_uart->INTENCLR.reg = SERCOM_USART_INTFLAG_DRE;
	}

	// Must send _after_ disabling DRE, or we risk
	// instantly getting another interrupt.
	sercom_uart->DATA.reg = data;

	if (requested_space) {
		if (--requested_space == 0) {
#if defined(__FREERTOS__) || defined(__DOXYGEN__)
			xSemaphoreGiveFromISR(requested_space_is_free, NULL);
#else
			requested_space_is_free = true;
#endif
		}
	}
}

/**
 * \brief Write an integer as hex digits (ASCII) into string
 *
 * This function will convert a 32-bit integer into a string of hexadecimal
 * digits (0-9, A-F) and store them to the specified location, most significant
 * digit first.
 *
 * Note that this function does not add the '0x'-prefix, which.
 *
 * \param[in] out_str Pointer to where digits shall be written.
 * \param[in] out_int The integer to write.
 */
void dbg_sprint_hexint(char *out_str, uint32_t out_int)
{
	uint8_t bytes_left = sizeof(out_int);

	do {
		char hi_nibble, lo_nibble;

		lo_nibble = out_int >> 24;
		hi_nibble = lo_nibble >> 4;
		lo_nibble &= 0x0f;

		TRANSLATE_NIBBLE_TO_ASCII(hi_nibble);
		TRANSLATE_NIBBLE_TO_ASCII(lo_nibble);

		*(out_str++) = hi_nibble;
		*(out_str++) = lo_nibble;

		out_int <<= 8;
	} while (--bytes_left);
}

/**
 * \brief Print an integer as hex digits
 *
 * This function will put the hex digits of a 32-bit integer into the print
 * buffer. It does not add the '0x'-prefix.
 *
 * \param[in] out_int The integer to print.
 */
void dbg_print_hexint(uint32_t out_int)
{
	char out_str[2 * sizeof(out_int)];

	dbg_sprint_hexint(out_str, out_int);

	_dbg_wait_for_lock();
	_dbg_putstr(out_str, sizeof(out_str));
	_dbg_unlock();
}

/**
 * \brief Print a zero-terminated string
 *
 * \param[in] out_str The string to print.
 */
void dbg_print_str(const char *out_str)
{
	size_t length = strlen(out_str);

	_dbg_wait_for_lock();
	_dbg_putstr(out_str, length);
	_dbg_unlock();
}

/**
 * \brief Print a single character
 *
 * \param[in] out_char The character to print.
 */
void dbg_print_char(const char out_char)
{
	_dbg_wait_for_lock();
	_dbg_putstr(&out_char, 1);
	_dbg_unlock();
}

/**
 * \brief Initialize and enable debug UART
 *
 * This function sets up the configured SERCOM with the following static
 * features:
 * - asynchronous, internally clocked (UART)
 * - TX only
 * - 1 stop bit
 * - 8-bit data
 * - LSB first
 * - no parity bit
 *
 * The baud rate, SERCOM signal MUX and pin MUX are set up as configured in
 * \ref conf_debug_print.h, which also contains the configuration of which
 * SERCOM to use.
 *
 * The SERCOM UART is left enabled after this function call.
 *
 * \return Indication whether or not initialization succeeded.
 * \retval STATUS_OK if initialization was successful.
 * \retval STATUS_ERR_BAUDRATE_UNAVAILABLE if configured baud rate is too high.
 *
 * \note This function is based on \ref usart_init() from ASF, but is modified
 * to use a single instance in order to reduce code size.
 */
enum status_code dbg_init(void)
{
	enum status_code status = STATUS_OK;
	Sercom *const sercom = CONF_DBG_PRINT_SERCOM;
	struct system_gclk_chan_config gclk_chan_conf;
	struct system_pinmux_config pin_conf;
	uint16_t baud;
	uint32_t sercom_index, pm_index, gclk_index;

#if defined(__FREERTOS__) || defined(__DOXYGEN__)
	dbg_is_free = xSemaphoreCreateMutex();
	vSemaphoreCreateBinary(requested_space_is_free);
	xSemaphoreTake(requested_space_is_free, 0);
#else
	requested_space_is_free = false;
#endif

	// Get required indexes
	sercom_index = _sercom_get_sercom_inst_index(sercom);
	pm_index = sercom_index + PM_APBCMASK_SERCOM0_Pos;
	gclk_index = sercom_index + SERCOM0_GCLK_ID_CORE;

	// Turn on module in PM
	system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBC, 1 << pm_index);

	// Set up the GCLK for the module
	system_gclk_chan_get_config_defaults(&gclk_chan_conf);
	gclk_chan_conf.source_generator = CONF_DBG_PRINT_GCLK_SOURCE;
	system_gclk_chan_set_config(gclk_index, &gclk_chan_conf);
	system_gclk_chan_enable(gclk_index);
	sercom_set_gclk_generator(CONF_DBG_PRINT_GCLK_SOURCE, false);

#if defined(CONF_DBG_PRINT_BAUD_VALUE)
	baud = CONF_DBG_PRINT_BAUD_VALUE;
#else
	// Compute baud rate, if it is achievable
	status = _sercom_get_async_baud_val(CONF_DBG_PRINT_BAUD_RATE,
			system_gclk_chan_get_hz(gclk_index), &baud,
			SERCOM_ASYNC_OPERATION_MODE_ARITHMETIC,
			SERCOM_ASYNC_SAMPLE_NUM_16);
	if (status != STATUS_OK) {
		return status;
	}
#endif

	sercom_uart->BAUD.reg = baud;
	sercom_uart->CTRLB.reg = SERCOM_USART_CTRLB_TXEN;
	sercom_uart->CTRLA.reg = SERCOM_USART_CTRLA_MODE_USART_INT_CLK
			| SERCOM_USART_CTRLA_DORD | SERCOM_USART_CTRLA_ENABLE
			| CONF_DBG_PRINT_SERCOM_MUX | (system_is_debugger_present() ?
					SERCOM_USART_CTRLA_RUNSTDBY : 0);

	// Set up the pin MUXes
	system_pinmux_get_config_defaults(&pin_conf);
	pin_conf.direction = SYSTEM_PINMUX_PIN_DIR_INPUT;
	uint32_t pad_pinmuxes[] = {
			CONF_DBG_PRINT_PINMUX_PAD0,
			CONF_DBG_PRINT_PINMUX_PAD1,
			CONF_DBG_PRINT_PINMUX_PAD2,
			CONF_DBG_PRINT_PINMUX_PAD3,
		};

	for (uint8_t pad = 0; pad < 4; pad++) {
		uint32_t current_pinmux = pad_pinmuxes[pad];

		if (current_pinmux == PINMUX_DEFAULT) {
			current_pinmux = _sercom_get_default_pad(sercom, pad);
		}

		if (current_pinmux != PINMUX_UNUSED) {
			pin_conf.mux_position = current_pinmux & 0xFFFF;
			system_pinmux_pin_set_config(current_pinmux >> 16, &pin_conf);
		}
	}

	// Set up and enable interrupts
	_sercom_set_handler(sercom_index, _dbg_interrupt_handler);
	system_interrupt_enable(_sercom_get_interrupt_vector(sercom));

	// Wait for sync before returning
#if defined(FEATURE_SERCOM_SYNCBUSY_SCHEME_VERSION_1)
	while (sercom_uart->STATUS.reg & SERCOM_USART_STATUS_SYNCBUSY) {
		/* Intentionally left empty */
	}
#elif defined(FEATURE_SERCOM_SYNCBUSY_SCHEME_VERSION_2)
	while (sercom_uart->SYNCBUSY.reg) {
		/* Intentionally left empty */
	}
#else
#  error Unknown SERCOM SYNCBUSY scheme!
#endif

	return status;
}
