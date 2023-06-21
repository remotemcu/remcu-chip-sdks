/**
 * \file
 *
 * \brief CPU reset cause example for SAM4L
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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
 * \mainpage CPU reset cause example
 *
 * \section Purpose
 *
 * This example demonstrates how to use the reset cause interface.
 *
 * \section Requirements
 *
 *  This example can be used with SAM4L boards.
 *
 * \section Description
 *
 * The program turns LED0 on when the power-on reset happens and outputs
 * different informaiton on the terminal, depending on the reset cause.
 *
 * Type different commands to generate different reset. To generate Core BOD 
 * reset or I/O BOD reset, press reset button after typing 'c' or 'i'.
 *
 * \section Usage
 *
 * - Build the program and download it to the board.
 * -# On the computer, open and configure a terminal application
 *    (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *    \code
	-- Reset_Cause Example xxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 * -# Choose the item in the following menu to test.
 *    \code
	Menu :
	------Please select reset cause way--------
	  c: Generate core BOD reset
	  i: Generate I/O BOD reset
	  w: Generate watchdog reset
	  s: Generate system reset
\endcode
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"

#define STRING_EOL    "\r"
#define STRING_HEADER "-- Reset_Cause Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/**
 * \brief Configure UART console.
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

	/* Configure console UART. */
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief Main function.
 */
int main(void)
{
	uint8_t key;

	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	/* Initialize the UART console. */
	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);
	puts("------ Please select which reset is to be generated ----------\r\n"
			"  c:  Generate core BOD reset\r\n"
			"  i:  Generate I/O BOD reset\r\n"
			"  w:  Generate watchdog reset\r\n"
			"  s:  Generate system reset \r");

	if (reset_cause_is_power_on_reset()) {
		LED_On(LED0);
	}
	if (reset_cause_is_cpu_brown_out_detected()) {
		puts("-- Reset Cause is Core browm out reset --\r");
	}
	if (reset_cause_is_io_brown_out_detected()) {
		puts("-- Reset Cause is I/O brown out reset --\r");
	}
	if (reset_cause_is_ocd()) {
		puts("-- Reset Cause is system reset request --\r");
	}
	if (reset_cause_is_external_reset()) {
		puts("-- Reset Cause is external reset --\r");
	}
	if (reset_cause_is_watchdog()) {
		puts("-- Reset Cause is watchdog reset --\r");
	}

	while(1) {
		scanf("%c", (char *)&key);
		switch (key) {
		case 'c':
			puts("-- Please press reset button --\r");
			BSCIF->BSCIF_BOD18CTRL = BSCIF_BOD18CTRL_EN | BSCIF_BOD18CTRL_ACTION(1) |
					BSCIF_BOD18CTRL_HYST | BSCIF_BOD18CTRL_FCD;
			BSCIF->BSCIF_BOD18LEVEL |= BSCIF_BOD18LEVEL_VAL(0x3F);
			break;
		case 'i':
			puts("-- Please press reset button --\r");
			BSCIF->BSCIF_BOD33CTRL = BSCIF_BOD33CTRL_EN | BSCIF_BOD33CTRL_ACTION(1) |
					BSCIF_BOD33CTRL_HYST | BSCIF_BOD33CTRL_FCD;
			BSCIF->BSCIF_BOD33LEVEL = BSCIF_BOD33LEVEL_VAL(0x3F);
			break;
		case 'w':
			wdt_reset_mcu();
			break;
		case 's':
			reset_do_soft_reset();
			break;
		}
	}
}
