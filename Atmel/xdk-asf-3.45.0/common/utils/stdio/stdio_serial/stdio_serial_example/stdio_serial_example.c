/**
 * \file
 *
 * \mainpage
 *
 * \section title Serial Standard I/O (stdio) Example
 *
 * \section file File(s)
 * - \ref stdio_serial_example.c
 *
 * Copyright (c) 2010-2018 Microchip Technology Inc. and its subsidiaries.
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
 * \defgroup group_common_utils_stdio_stdio_serial_stdio_serial_example Serial Standard I/O (stdio) Example
 *
 * \section intro Introduction
 * This example demonstrates how to use the Serial Stdio.
 *
 * \section files Main Files
 * - stdio_serial_example.c: the example application.
 * - conf_board.h: board configuration
 * - conf_clock.h: clock configuration
 * - conf_usart_serial.h: configuration of the stdio serial used by this example
 * - stdio_serial.h: Part Specific Stdio Serial Implementation
 * - read.c : System implementation function used by standard library
 * - write.c : System implementation function used by standard library
 *
 * \section stdio_serialapiinfo utils/stdio/stdio_serial API
 * The stdio_serial API can be found \ref stdio_serial.h "here".
 *
 * \section deviceinfo Device Info
 * All Atmel devices can be used. This example has been tested
 * with the following setup:
 *   - ATXMEGA128A1 XMEGA-A1 Xplained (USB connection to host virtual com port).
 *   - AT32UC3L064 UC3-L0 Xplained (USB connection to host virtual com port).
 *   - SAM4E evaluation kit.
 *
 * \section exampledescription Description of the example
 *   - Send message on serial communication port.
 *   - Performs echo of any received character
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for AVR and ARM.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com">Microchip</A>.\n
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <board.h>
#include <sysclk.h>
#include <stdio_serial.h>

#if SAM
#include <conf_uart_serial.h>
#else
#include <conf_usart_serial.h>
#endif

/*! \brief Main function.
 */
int main(void)
{
	uint32_t ch;

	const usart_serial_options_t usart_serial_options = {
		.baudrate     = USART_SERIAL_EXAMPLE_BAUDRATE,
		.charlength   = USART_SERIAL_CHAR_LENGTH,
		.paritytype   = USART_SERIAL_PARITY,
		.stopbits     = USART_SERIAL_STOP_BIT
	};

	sysclk_init();

	/* Initialize the board.  The board-specific conf_board.h file contains
	 * the configuration of the board initialization.
	 */
	board_init();

	// Initialize Serial Interface using Stdio Library
	stdio_serial_init(USART_SERIAL_EXAMPLE, &usart_serial_options);

	// Print welcome message
	printf("\n\rHello ATMEL World!\n\r");

	// Get and echo a character forever.
	while (true) {
		scanf("%c",(char*)&ch);

		if (ch) {
			printf("%c",(char)ch);
		}
	}
}

