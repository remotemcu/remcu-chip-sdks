/**
 * \file
 *
 * \brief Memory-to-memory transfer example for SAM.
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

/**
 * \mainpage Memory-to-Memory transfer example
 *
 * \section intro Introduction
 *
 * This example shows how to perform memory to memory transfer on MEM2MEM
 * peripheral via PDC. The transfer operation is simplified by using MEM2MEM
 * module driver (M2M).
 *
 * The example demostrates three use cases:
 * -# transfer and polling peripheral status (Transfer Wait)
 * -# transfer in background and invoke callback in ISR (Transfer Job Callback)
 * -# transfer in background and polling transfer job status (Transfer Job)
 *
 * \section Requirements
 *
 * This package can be used with STK600_SAMG51.
 *
 * \section files Main files:
 *  - mem2mem.c SAM Memory-to-memory driver implementation.
 *  - mem2mem.h SAM Memory-to-memory driver definitions.
 *  - example.c Example application.
 *
 * \section exampledescription Description of the Example
 * The example prepare source data blocks and copy them to destination buffers
 * through memory-to-memory driver, then the data copied is verified.
 *
 * The test progress and results will dump to debug serial port.
 *
 * \section Usage
 * -# Build the program and download it into the evaluation board.
 * -# On the computer, open and configure a terminal application
 *    (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# In the terminal window, the following text should appear (values depend
 *    on the board and chip used):
 *    \code
	-- MEM2MEM Example xxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 * -# the test hints should appear.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR EWARM.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/">Microchip</A>.\n
 * Support and FAQ: https://www.microchip.com/support/
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "stdio_serial.h"
#include "conf_board.h"
#include <string.h>

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

#define STRING_EOL    "\r"
#define STRING_HEADER "-- MEM2MEM Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/** Memory source buffer */
// [src_buffer]
static uint8_t src_mem[1024];
// [src_buffer]

/** Memory destination buffer */
// [dst_buffer]
static uint8_t dest_mem[1024];
// [dst_buffer]

/** Memory transfer is done */
// [transfer_done]
static volatile bool transfer_is_done = false;
// [transfer_done]

/** MEM2MEM driver (M2M) instance */
// [driver_instance]
static struct m2m_module m2m;
// [driver_instance]

/**
 *  \brief Configure the Console Uart
 */
// [_console_init]
static void _console_init(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
#ifdef CONF_UART_CHAR_LENGTH
		.charlength = CONF_UART_CHAR_LENGTH,
#endif
		.paritytype = CONF_UART_PARITY,
#ifdef CONF_UART_STOP_BITS
		.stopbits = CONF_UART_STOP_BITS,
#endif
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}
// [_console_init]

/**
 * \brief Callback when all transfer done
 */
// [_transfer_done]
static void _transfer_done(const struct m2m_module *const module)
{
	UNUSED(module);
	transfer_is_done = true;
}
// [_transfer_done]

/**
 * \brief Verify transfered data
 */
static void _verify_data(void)
{
	uint32_t err_cnt = 0;
	uint32_t i;
	/* Count the bytes mismatch */
	for (i = 0; i < sizeof(src_mem); i ++) {
		if (src_mem[i] != dest_mem[i]) {
			err_cnt ++;
		}
	}
	if (err_cnt) {
		printf("  %d bytes not match, verification fail!\r\n",
			(int)err_cnt);
	} else {
		printf("  All data verified OK\r\n");
	}
}

/**
 * \brief Application entry point for Memory-to-memory example.
 *
 * \return Unused (ANSI-C compatibility).
 */
// [main]
int main(void)
{
//! [main_values]
//! [main_config]
	struct m2m_config m2m_cfg;
//! [main_config]
	enum status_code status;
//! [main_values]
	uint32_t i;

//! [main_sys_init]
	/* Initialize the SAM system */
	sysclk_init(); /* Initialize clock */
	board_init();  /* Initialize peripheral IOs */
//! [main_sys_init]

//! [main_console_init]
	/* Initialize the console uart */
	_console_init();
//! [main_console_init]

	/* Output example information */
	puts(STRING_HEADER);

//! [main_driver_init]
//! [main_config_init]
	/* Get default configuration:
	 * - transfer byte by byte
	 * - enable interrupt for background transfer
	 */
	m2m_get_config_default(&m2m_cfg);
//! [main_config_init]
	/* Initialize M2M module */
	m2m_init(&m2m, MEM2MEM, &m2m_cfg);
//! [main_driver_init]

	/* Initialize test data */
	for (i = 0; i < sizeof(src_mem); i ++) {
		src_mem[i] = (uint8_t)((i%('z'-0x20))+0x20);
	}

	/* Perform test :
	 * transfer and polling peripheral status until transfer end */
	printf("- Transfer Wait example ...\r\n");
	memset(dest_mem, 0x00, sizeof(dest_mem));
//! [main_transfer_wait]
	status = m2m_transfer_wait(&m2m, src_mem, dest_mem, sizeof(src_mem));
//! [main_transfer_wait]
	printf("  Done %s, verify data\r\n", (STATUS_OK == status) ? "OK" : "ERR");
	_verify_data();

	/* Perform test : transfer in background and invoke callback when done */
	printf("\r\n");
	printf("- Transfer Job Callback example ...\r\n");
	memset(dest_mem, 0x00, sizeof(dest_mem));
//! [main_callback_register]
	/* Setup a callback invoked when all transfer done */
	m2m_register_callback(&m2m, _transfer_done, M2M_CALLBACK_TRANSFER_END);
	m2m_enable_callback(&m2m, M2M_CALLBACK_TRANSFER_END);
//! [main_callback_register]
//! [main_transfer_job_callback]
	transfer_is_done = false;
	/* Start transfer by issuing a job */
	m2m_transfer_job(&m2m, src_mem, dest_mem, sizeof(src_mem));
	while(!transfer_is_done);
//! [main_transfer_job_callback]
	/* Job status should be OK when finished */
	status = m2m_get_job_status(&m2m, M2M_JOB_TRANSFER);
	printf("  Done %s, verify data\r\n", (STATUS_OK == status) ? "OK" : "ERR");
	_verify_data();

	/* Perform test :
	 * transfer in background and wait until job status is done OK */
	printf("\r\n");
	printf("- Transfer Job example ...\r\n");
	memset(dest_mem, 0x00, sizeof(dest_mem));
//! [main_transfer_job]
	/* Callback will not be invoked when transfer is done */
	m2m_disable_callback(&m2m, M2M_CALLBACK_TRANSFER_END);
	/* Start transfer by issuing a job */
	m2m_transfer_job(&m2m, src_mem, dest_mem, sizeof(src_mem));
	/* Poll job status */
	while(ERR_BUSY == m2m_get_job_status(&m2m, M2M_JOB_TRANSFER));
//! [main_transfer_job]
	printf("  Done %s, verify data\r\n", (STATUS_OK == status) ? "OK" : "ERR");
	_verify_data();

	while(1) {
	}
}
// [main]

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
