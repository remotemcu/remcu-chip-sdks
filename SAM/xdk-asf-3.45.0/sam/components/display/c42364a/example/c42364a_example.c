/**
 * \file
 *
 * \brief C42364A LCD Glass component example for SAM.
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
 * \mainpage
 * \section intro Introduction
 * This is the documentation for the data structures, functions, variables,
 * defines, enums, and typedefs for the C42364A LCD Glass component example.
 * It also comes bundled with an application-example of usage.
 *
 * This example demonstrates how to use the C42364A LCD Glass driver with the
 * 32 KHz oscillator crystal.
 *
 * \section files Main Files
 * - c42364a_lcdca.c: C42364A LCD Glass component driver using LCDCA;
 * - c42364a_slcdc.c: C42364A LCD Glass component driver using SLCDC;
 * - c42364a.h: C42364A LCD Glass component driver header file;
 * - c42364a_example.c: C42364A LCD Glass component example application.
 *
 * \section compilinfo Compilation Information
 * This software is written for GNU GCC and IAR Embedded Workbench
 * for Atmel. Other compilers may or may not work.
 *
 * \section deviceinfo Device Information
 * All SAM devices with an LCDCA or SLCDC connected to C42364A LCD Glass
 * component and a USART module can be used.
 *
 * \section configinfo Configuration Information
 * - PC terminal settings:
 *   - 115200 bps,
 *   - 8 data bits,
 *   - no parity bit,
 *   - 1 stop bit,
 *   - no flow control.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com">Microchip</A>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <string.h>

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
 * \brief Display the user menu on the terminal.
 */
static void display_menu(void)
{
	printf("Menu :\n\r"
			"  -- Select operation:\n\r"
			"  c: Clear the screen \n\r"
			"  h: Display menu \n\r"
		#if ( SAM4C || SAM4CP )
			"  1: Basic show feature \n\r"
		#else
			"  1: Basic show feature(need 'c' first if '4' selected) \n\r"
		#endif
			"  2: Blink feature \n\r"
		#if !( SAM4C || SAM4CP )
			"  3: Circular animation feature \n\r"
			"  4: Text scrolling feature \n\r"
		#endif
			"\n\r\n\r");
}

/**
 * \brief main function : do init and loop
 */
int main(void)
{
	uint8_t key;
#if !( SAM4C || SAM4CP )
	uint8_t const scrolling_str[] = "C42364A Example  ";
#endif
#if ( SAM4C || SAM4CP )
	int32_t value = 1234;
#else
	int32_t value = -12345;
#endif
	status_code_t status;

	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	/* Initialize the console uart */
	configure_console();

	/* Output example information */
	printf("-- C42364A Example --\r\n");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

#if !SAM4CP
	/* Turn on the backlight. */
	ioport_set_pin_level(LCD_BL_GPIO, LCD_BL_ACTIVE_LEVEL);
#endif

	/* Initialize the C42364A LCD glass component. */
	status = c42364a_init();
	if (status != STATUS_OK) {
		printf("-- LCD Initialization fails! --\r\n");
		while (1) {
		}
	}

	printf("Show all the components on the glass.\r\n");
	c42364a_show_all();

	printf("Press any key to continue.\r\n");
	scanf("%c", (char *)&key);

	c42364a_clear_all();

	/* Display menu */
	display_menu();

	while (1) {
		scanf("%c", (char *)&key);

		switch (key) {
		case 'h':
			display_menu();
			break;

		case 'c':
			printf("Clear all the screen.\r\n");
			c42364a_clear_all();
			break;

		case '1':
			printf("Show icons, number and string.\r\n");
		#if ( SAM4C || SAM4CP )
			c42364a_clear_all();
			c42364a_blink_disable();
		#endif
			c42364a_show_icon(C42364A_ICON_ARM);
			c42364a_show_numeric_dec(value);
		#if ( SAM4C || SAM4CP )
			c42364a_show_text((const uint8_t *)"SAM4C");
		#else
			c42364a_show_text((const uint8_t *)"Welcome");
		#endif
			c42364a_show_battery(C42364A_BATTERY_TWO);
			break;

		case '2':
		#if ( SAM4C || SAM4CP )
			printf("Blink Full Screen.\r\n");
			c42364a_clear_all();
			c42364a_write_num_packet((const uint8_t *)"1023");
			c42364a_show_icon(C42364A_ICON_AM);
			c42364a_show_icon(C42364A_ICON_COLON);
			c42364a_blink_screen();
		#else
			printf("Blink colon icon, show a time.\r\n");
			c42364a_clear_icon(C42364A_ICON_MINUS);
			c42364a_clear_icon(C42364A_ICON_MINUS_SEG1);
			c42364a_clear_icon(C42364A_ICON_MINUS_SEG2);
			c42364a_write_num_packet((const uint8_t *)"1023");
			c42364a_show_icon(C42364A_ICON_AM);
			c42364a_blink_icon_start(C42364A_ICON_COLON);
		#endif
			break;
	#if !( SAM4C || SAM4CP )
		case '3':
			printf("Show the two dots circular animation.\r\n");
			c42364a_circular_animation_start(C42364A_CSR_RIGHT, 7, 0x03);
			break;

		case '4':
			printf("Text scrolling.\r\n");
			c42364a_text_scrolling_start(scrolling_str,
					strlen((char const *)scrolling_str));
			break;
	#endif
		default:
			break;
		}
	}

}
