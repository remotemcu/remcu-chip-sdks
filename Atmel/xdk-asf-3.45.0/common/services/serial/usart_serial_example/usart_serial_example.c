/**
 *
 * \file
 *
 * \brief Example of usage of the USART Serial.
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
/*! \mainpage
 * \section intro Introduction
 * This example demonstrates how to use the USART Serial.
 *
 * \section files Main Files
 * - usart_serial_example.c: the example application.
 * - conf_board.h: board configuration
 * - conf_stdio_serial.h: configuration of the usart_serial used by this example
 * - usart_serial.h: Part Specific USART Serial Implementation
 * - usart_serial.c : System implementation functions
 *
 * \section usart_serialapiinfo basic/serial/usart_serial API
 * The usart_serial API can be found \ref usart_serial.h "here".
 *
 * \section deviceinfo Device Info
 * All devices can be used. This example has been tested
 * with the following setup:
 *   - Evaluation kits with a serial interface (RS232 connection).
 *
 * \section exampledescription Description of the example
 *   - Send message on RS232 Com Port.
 *   - Performs echo of any received character
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com">Microchip</A>.\n
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>

/*! \brief Main function.
 */
int main(void)
{
	uint8_t tx_len = 24;
	uint8_t tx_buf[] = "\n\rHello Atmel world ! : ";
	uint8_t rx_buf[] = "0";

	// USART options.
	static usart_serial_options_t USART_SERIAL_OPTIONS =
	{
		.baudrate   = USART_SERIAL_EXAMPLE_BAUDRATE,
		.charlength = USART_SERIAL_CHAR_LENGTH,
		.paritytype = USART_SERIAL_PARITY,
		.stopbits   = USART_SERIAL_STOP_BIT
	};

	sysclk_init();

	// Initialize the board.
	// The board-specific conf_board.h file contains the
	// configuration of the board initialization.
	board_init();

	// Initialize Serial Interface using Stdio Library
	usart_serial_init(USART_SERIAL_EXAMPLE,&USART_SERIAL_OPTIONS);

	// Print welcome message
	usart_serial_write_packet(USART_SERIAL_EXAMPLE, tx_buf, tx_len);

	// Get and echo a character forever, specific '\r' processing.
	while (true) {
		usart_serial_read_packet(USART_SERIAL_EXAMPLE, rx_buf, 1);
		if (rx_buf[0] == '\r') {
			usart_serial_write_packet(USART_SERIAL_EXAMPLE,
					tx_buf, tx_len);
		} else {
			usart_serial_write_packet(USART_SERIAL_EXAMPLE,
					rx_buf, 1);
		}
	}
}

