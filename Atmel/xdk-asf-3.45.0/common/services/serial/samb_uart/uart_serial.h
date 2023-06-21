/**
 * \file
 *
 * \brief UART Serial wrapper service for the SAM B11 devices.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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
#ifndef _UART_SERIAL_H_
#define _UART_SERIAL_H_

#include "compiler.h"
#include "status_codes.h"
#include "uart.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \name Serial Management Configuration */

/*! \brief Initializes the Uart in serial mode.
 *
 * \param[in,out] module  Software instance of the UART to initialize.
 * \param[in]     hw      Base address of the hardware UART.
 * \param[in]     config  Configuration settings for the UART.
 *
 * \retval true if the initialization was successful
 * \retval false if initialization failed (error in baud rate calculation)
 */
static inline bool usart_serial_init(
		struct uart_module *const module,
		Uart * const hw,
		const struct uart_config *const config)
{
	if (uart_init(module, hw, config) == STATUS_OK) {
		return true;
	}
	else {
		return false;
	}
}

/** \brief Sends a character with the UART.
 *
 * \param[in,out] module  Software instance of the UART.
 * \param[in]     c       Character to write.
 *
 * \return Status code
 */
static inline enum status_code usart_serial_putchar(
		struct uart_module *const module,
		uint8_t c)
{
	while(STATUS_OK !=uart_write_wait(module, c));

	return STATUS_OK;
}

/** \brief Waits until a character is received, and returns it.
 *
 * \param[in,out] module  Software instance of the UART.
 * \param[out]    c       Destination for the read character.
 */
static inline void usart_serial_getchar(
		struct uart_module *const module,
		uint8_t *c)
{
	while(STATUS_OK != uart_read_wait(module, c));
}

/**
 * \brief Send a sequence of bytes to UART device
 *
 * \param[in,out] module   Software instance of the UART.
 * \param[in]     tx_data  Data buffer to read the data to write from.
 * \param[in]     length   Length of data to write.
 */
static inline enum status_code usart_serial_write_packet(
		struct uart_module *const module,
		const uint8_t *tx_data,
		uint16_t length)
{
	return uart_write_buffer_wait(module, tx_data, length);
}

/**
 * \brief Receive a sequence of bytes from UART device
 *
 * \param[in,out] module   Software instance of the UART.
 * \param[out]    rx_data  Data buffer to store the read data into.
 * \param[in]     length   Length of data to read.
 */
static inline enum status_code usart_serial_read_packet(
		struct uart_module *const module,
		uint8_t *rx_data,
		uint16_t length)
{
	return uart_read_buffer_wait(module, rx_data, length);
}

#ifdef __cplusplus
}
#endif

#endif  // _UART_SERIAL_H_
