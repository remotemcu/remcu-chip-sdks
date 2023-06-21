/**
 * \file
 *
 * \brief SAM Asynchronous Timer (AST) example 1.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include "ast_example1.h"

/**
 *  \brief Configure serial console.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
#ifdef CONF_UART_CHAR_LENGTH
		.charlength = CONF_UART_CHAR_LENGTH,
#endif /* CONF_UART_CHAR_LENGTH */
		.paritytype = CONF_UART_PARITY,
#ifdef CONF_UART_STOP_BITS
		.stopbits = CONF_UART_STOP_BITS,
#endif /* CONF_UART_STOP_BITS */
	};

	// Configure console.
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief main function : do init and loop
 */
int main(void)
{

	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	/* Initialize the console uart */
	configure_console();

	/* Output example information */
	printf("-- AST Example 1 in Calendar Mode --\r\n");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	printf("Config AST with 32 KHz oscillator.\r\n");

	/* Enable osc32 oscillator*/
	if (!osc_is_ready(OSC_ID_OSC32)) {
		osc_enable(OSC_ID_OSC32);
		osc_wait_ready(OSC_ID_OSC32);
	}

	struct ast_calendar calendar;
	calendar.FIELD.sec = 0;
	calendar.FIELD.min = 15;
	calendar.FIELD.hour = 12;
	calendar.FIELD.day = 20;
	calendar.FIELD.month = 9;
	calendar.FIELD.year = 14;

	/* Enable the AST */
	ast_enable(AST);

	struct ast_config ast_conf;
	ast_conf.mode = AST_CALENDAR_MODE;
	ast_conf.osc_type = AST_OSC_32KHZ;
	ast_conf.psel = AST_PSEL_32KHZ_1HZ;
	ast_conf.calendar = calendar;

	/* Initialize the AST */
	if (!ast_set_config(AST, &ast_conf)) {
		printf("Error initializing the AST\r\n");
		while (1) {
		}
	}

	while (1) {
		/* slow down operations */
		delay_s(1);

		ioport_toggle_pin_level(LED0_GPIO);

		/* Output the calendar */
		calendar = ast_read_calendar_value(AST);
		printf("\r");
		printf("Calendar: Year:%02u Month:%02u Day:%02u, %02uh%02um%02us ",
				(unsigned int)calendar.FIELD.year,
				(unsigned int)calendar.FIELD.month,
				(unsigned int)calendar.FIELD.day,
				(unsigned int)calendar.FIELD.hour,
				(unsigned int)calendar.FIELD.min,
				(unsigned int)calendar.FIELD.sec);
	}
}
