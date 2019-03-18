/**
 * \file
 *
 * \brief PICOUART example 1 for SAM.
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
 * defines, enums, and typedefs for the PICOUART driver. It also comes
 * bundled with an application-example of usage.
 *
 * This example demonstrates how to use the PICOUART driver with the 32 KHz
 * oscillator crystal. And it requires a board monitor firmware version V1.3
 * or greater.
 *
 * <b>Operating mode: </b>It uses the USART driver to display menu. And let
 * the user select the wake up mode. Then make the system to lower power mode
 * and wait for the wakeup signal. You can use the board monitor or use
 * another device to send the character to the PICOUART RXD pin to wakeup
 * the system. You also can just use the push button to wakeup the system.
 *
 * \section files Main Files
 * - picouart.c: Picopower UART driver;
 * - picouart.h: Picopower UART driver header file;
 * - picouart_example1.c: Picopower UART example application.
 *
 * \section compilinfo Compilation Information
 * This software is written for GNU GCC and IAR Embedded Workbench
 * for Atmel. Other compilers may or may not work.
 *
 * \section deviceinfo Device Information
 * All SAM devices with a PICOUART and a USART module can be used.
 *
 * \section configinfo Configuration Information
 * This example has been tested with the following configuration:
 * - SAM4L_EK evaluation kit;
 * - CPU clock: 12 MHz;
 * - USART2 (on SAM4L_EK) abstracted with a USB CDC connection to a PC;
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
#include "board_monitor.h"

/* Flag to use board monitor */
static volatile bool bm_flag = true;

void PM_Handler(void)
{
	Pm *p_pm = PM;
	p_pm->PM_ICR = PM_ICR_WAKE;
}

/**
 * \brief EIC interrupt handler for push button interrupt
 */
static void eic_5_callback(void)
{
	if (eic_line_interrupt_is_pending(EIC, GPIO_PUSH_BUTTON_EIC_LINE)) {
		eic_line_clear_interrupt(EIC, GPIO_PUSH_BUTTON_EIC_LINE);
	}
}

static void config_buttons(void)
{
	/* Initialize EIC for button wakeup. */
	struct eic_line_config eic_line_conf = {
		EIC_MODE_EDGE_TRIGGERED,
		EIC_EDGE_FALLING_EDGE,
		EIC_LEVEL_LOW_LEVEL,
		EIC_FILTER_DISABLED,
		EIC_ASYNCH_MODE
	};
	eic_enable(EIC);
	eic_line_set_config(EIC, GPIO_PUSH_BUTTON_EIC_LINE, 
		&eic_line_conf);
	eic_line_set_callback(EIC, GPIO_PUSH_BUTTON_EIC_LINE, eic_5_callback,
		EIC_5_IRQn, 1);
	eic_line_enable(EIC, GPIO_PUSH_BUTTON_EIC_LINE);
}

static void config_wakeup(void)
{
	Pm *p_pm = PM;

	/* EIC and PICOUART can wakeup the device. */
	bpm_enable_wakeup_source(BPM,
			(1 << BPM_BKUPWEN_EIC) | (1 << BPM_BKUPWEN_PICOUART));
	p_pm->PM_AWEN = 1 << PM_AWEN_PICOUART;
	p_pm->PM_IER = PM_IER_WAKE;
	NVIC_SetPriority(PM_IRQn,1);
	NVIC_EnableIRQ(PM_IRQn);

	/* EIC can wake the device from backup mode. */
	bpm_enable_backup_pin(BPM, 1 << GPIO_PUSH_BUTTON_EIC_LINE);
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
 * \brief Display the user menu on the terminal.
 */
static void display_menu(void)
{
	printf("Menu :\r\n"
			"  -- Select the action:\r\n"
			"  s: Switch on/off the board monitor to wake up. \r\n"
			"  0: Enter Sleep mode with start bit wakeup. \r\n"
			"  1: Enter Retention mode with full frame wakeup. \r\n"
			"  2: Enter backup mode with character match wakeup. \r\n"
			"  h: Display menu \r\n"
			"  --Push button can also be used to exit low power mode--\r\n"
			"\r\n\r\n");
}

/*!
 * \brief main function : do init and loop (poll if configured so)
 */
int main(void)
{
	uint8_t key;
	struct picouart_dev_inst dev_inst;
	struct picouart_config config;
	struct ast_config ast_conf;

	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	/* Initialize the console uart */
	configure_console();

	/* Output example information */
	printf("\r\n");
	printf("-- PICOUART Example 1 --\r\n");
	printf("-- %s\r\n", BOARD_NAME);
	printf("-- Compiled: %s %s --\r\n", __DATE__, __TIME__);
	printf("-- IMPORTANT: This example requires a board "
			"monitor firmware version V1.3 or greater.\r\n");

	/* Enable osc32 oscillator*/
	if (!osc_is_ready(OSC_ID_OSC32)) {
		osc_enable(OSC_ID_OSC32);
		osc_wait_ready(OSC_ID_OSC32);
	}

	/* Disable all AST wake enable bits for safety since the AST is reset
		only by a POR. */
	ast_enable(AST);
	ast_conf.mode = AST_COUNTER_MODE;
	ast_conf.osc_type = AST_OSC_32KHZ;
	ast_conf.psel = AST_PSEL_32KHZ_1HZ;
	ast_conf.counter = 0;
	ast_set_config(AST, &ast_conf);
	ast_disable_wakeup(AST, AST_WAKEUP_ALARM);
	ast_disable_wakeup(AST, AST_WAKEUP_PER);
	ast_disable_wakeup(AST, AST_WAKEUP_OVF);
	ast_disable(AST);

	/* Config the push button */
	config_buttons();

	/* Configurate the USART to board monitor */
	bm_init();
	sysclk_enable_hsb_module(SYSCLK_PBA_BRIDGE);
	sysclk_enable_peripheral_clock(BM_USART_USART);

	/* Init the PICOUART */
	picouart_get_config_defaults(&config);
	picouart_init(&dev_inst, PICOUART, &config);

	/* Enable the PICOUART */
	picouart_enable(&dev_inst);

	/* PICOUART and EIC can wakeup the device */
	config_wakeup();

	/* Display menu */
	display_menu();

	while (1) {
		scanf("%c", (char *)&key);

		switch (key) {
		case 'h':
			display_menu();
			break;

		case 's':
			if (bm_flag) {
				printf("Switch off the board monitor to wake up..\r\n");
				bm_flag = false;
			} else {
				printf("Switch on the board monitor to wake up..\r\n");
				bm_flag = true;
			}
			break;

		case '0':
			printf("Enter Sleep mode with start bit wakeup.\r\n");
			config.action = PICOUART_ACTION_WAKEUP_ON_STARTBIT;
			picouart_set_config(&dev_inst, &config);
			if (bm_flag) {
				printf("Board monitor will send frame after 3 seconds.\r\n");
				bm_send_picouart_frame('A', 3000);
			}
			/* Wait for the printf operation to finish before
			setting the device in a power save mode. */
			delay_ms(30);
			bpm_sleep(BPM, BPM_SM_SLEEP_2);
			printf("--Exit Sleep mode.\r\n\r\n");
			break;

		case '1':
			printf("Enter Retention mode with full frame wakeup.\r\n");
			config.action = PICOUART_ACTION_WAKEUP_ON_FULLFRAME;
			picouart_set_config(&dev_inst, &config);
			if (bm_flag) {
				printf("Board monitor will send frame after 3 seconds.\r\n");
				bm_send_picouart_frame('T', 3000);
			}
			/* Wait for the printf operation to finish before
			setting the device in a power save mode. */
			delay_ms(30);
			bpm_sleep(BPM, BPM_SM_RET);
			printf("--Exit Retention mode.\r\n\r\n");
			break;

		case '2':
			printf("Enter backup mode with character match wakeup.\r\n");
			config.action = PICOUART_ACTION_WAKEUP_ON_MATCH;
			config.match = 'L';
			picouart_set_config(&dev_inst, &config);
			if (bm_flag) {
				printf("Board monitor will send frame after 3 seconds.\r\n");
				bm_send_picouart_frame('L', 3000);
			}
			/* Wait for the printf operation to finish before
			setting the device in a power save mode. */
			delay_ms(30);
			bpm_sleep(BPM, BPM_SM_BACKUP);
			break;

		default:
			break;
		}
	}
}
