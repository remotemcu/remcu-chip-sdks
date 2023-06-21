/**
 *
 * \file
 *
 * \brief CMCC example for SAM.
 *
 * This file defines a useful set of functions for the CMCC on SAM devices.
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

/** \mainpage
 * \section intro Introduction
 * This is the documentation for the data structures, functions, variables,
 * defines, enums, and typedefs for the CMCC driver. <BR>It also gives several
 * examples of usage of the CMCC module: <BR>
 *
 * \section files Main Files
 * - cmcc.c : CMCC driver
 * - cmcc.h : CMCC header file
 * - cmcc_example.c : CMCC code example
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR Systems compiler.
 * Other compilers may or may not work.
 *
 * \section deviceinfo Device Info
 * All SAM devices with an CMCC module can be used. This example has been
 * tested with the following setup:<BR>
 * - SAM4E evaluation kit.
 * - SAM4C evaluation kit.
 * - SAM4CMP and SAM4CMS demo board
 * - SAMG55 Xplained Pro board
 *
 * \section setupinfo Setup Information
 * - Please connect the DBGU port com to a PC
 * - PC terminal settings:
 *     - 115200 bps,
 *     - 8 data bits,
 *     - no parity bit,
 *     - 1 stop bit,
 *     - no flow control.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com">Microchip</A>.\n
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>

/** Define CMCC Base */
#if SAM4C || SAM4CM
#define CMCC_BASE    CMCC0
#else
#define CMCC_BASE    CMCC
#endif

/** Fibonacci number */
#define FIBONACCI_NUM    30

/** CMCC configuration */
struct cmcc_config g_cmcc_cfg;

/**
 *  \brief Recursively calculate the nth Fibonacci number.
 *
 * \param n Indicates which (positive) Fibonacci number to compute.
 *
 * \return The nth Fibonacci number.
 */
static uint32_t recfibo(uint32_t n)
{
	if (n == 0 || n == 1) {
		return n;
	}

	return recfibo(n - 2) + recfibo(n - 1);
}

/**
 *  Configure serial console.
 */
static void configure_console(void)
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

	/* Configure console. */
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief The main function.
 */
int main(void)
{
	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	/* Initialize the console  */
	configure_console();

	/* Output example information */
	printf("-- CMCC Example --\r\n");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	/* Enable the CMCC module. */
	cmcc_get_config_defaults(&g_cmcc_cfg);
	cmcc_init(CMCC_BASE, &g_cmcc_cfg);
	cmcc_enable(CMCC_BASE);

	/* Do the Fibonacci calculation. */
	recfibo(FIBONACCI_NUM);
	printf("Fibonacci calculation completed \r\n");
	printf("Cache Data hit: %ld \r\n", cmcc_get_monitor_cnt(CMCC_BASE));

	while (true) {
	}
}
