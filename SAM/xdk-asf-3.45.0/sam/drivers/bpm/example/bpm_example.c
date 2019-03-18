/**
 * \file
 *
 * \brief BPM example.
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
 * \mainpage BPM example
 * \section intro Introduction
 * This is the documentation for the data structures, functions, variables,
 * defines, enums, and typedefs for the Backup Power Manager (BPM) driver.
 * It also comes bundled with an application-example of usage.
 *
 * This example demonstrates how to use the BPM driver. It requires a
 * board monitor firmware version V1.3 or greater if it run on the SAM4L_EK.
 *
 * <b>Operating mode: </b>The user can select the low power mode and power
 * scaling from the terminal. The example uses the terminal to provide
 * infomation about the current power save mode. If it run on the SAM4L_EK,
 * the example can also uses the board monitor to provide infomation about
 * the actual power consumption.
 *
 * \section files Main Files
 * - bpm.c: BPM driver;
 * - bpm.h: BPM driver header file;
 * - bpm_example.c: BPM example application.
 *
 * \section compilinfo Compilation Information
 * This software is written for GNU GCC and IAR Embedded Workbench
 * for Atmel. Other compilers may or may not work.
 *
 * \section deviceinfo Device Information
 * All SAM devices with an BPM and a USART module can be used.
 *
 * \section configinfo Configuration Information
 * This example has been tested with the following configuration:
 * - CPU clock: 12 MHz;
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
#include <conf_board.h>

#ifdef CONF_BOARD_BM_USART
#include "board_monitor.h"
#endif

/* Flag to use board monitor */
static bool ps_status = BPM_PS_1;

#ifdef CONF_BOARD_BM_USART
/* Current sleep mode */
static uint32_t current_sleep_mode = SLEEP_MODE_NA;

/* Power scaling value -> board monitor status */
power_scaling_t ps_statuses[] = {
	POWER_SCALING_PS0, POWER_SCALING_PS1
};
#endif

/**
 * EIC interrupt handler for push button interrupt
 */
static void eic_callback(void)
{
	sysclk_enable_peripheral_clock(EIC);
	if (eic_line_interrupt_is_pending(EIC, GPIO_PUSH_BUTTON_EIC_LINE)) {
		eic_line_clear_interrupt(EIC, GPIO_PUSH_BUTTON_EIC_LINE);
		/* Stop AST and reset the counter */
		ast_stop(AST);
		ast_write_counter_value(AST, 0);
	}
	sysclk_disable_peripheral_clock(EIC);
}

/**
 * AST interrupt handler
 */
static void ast_per_callback(void)
{
	ast_stop(AST);
	ast_clear_interrupt_flag(AST, AST_INTERRUPT_PER);
}

/**
 * Initialize AST to generate 1Hz counter
 */
static void config_ast(void)
{
	struct ast_config ast_conf;

	/* Enable osc32 oscillator*/
	if (!osc_is_ready(OSC_ID_OSC32)) {
		osc_enable(OSC_ID_OSC32);
		osc_wait_ready(OSC_ID_OSC32);
	}

	/* Enable the AST. */
	ast_enable(AST);

	ast_conf.mode = AST_COUNTER_MODE;
	ast_conf.osc_type = AST_OSC_1KHZ;
	ast_conf.psel = AST_PSEL_32KHZ_1HZ;
	ast_conf.counter = 0;
	ast_set_config(AST, &ast_conf);
	ast_stop(AST);

	/* Set periodic 0 to interrupt after 8 second in counter mode. */
	ast_clear_interrupt_flag(AST, AST_INTERRUPT_PER);
	ast_write_periodic0_value(AST, AST_PSEL_32KHZ_1HZ - 2);
	/* Set callback for periodic0. */
	ast_set_callback(AST, AST_INTERRUPT_PER, ast_per_callback,
		AST_PER_IRQn, 1);
	ast_enable_wakeup(AST, AST_WAKEUP_PER);
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
	eic_line_set_callback(EIC, GPIO_PUSH_BUTTON_EIC_LINE, eic_callback,
			GPIO_PUSH_BUTTON_EIC_IRQ, 1);
	eic_line_enable(EIC, GPIO_PUSH_BUTTON_EIC_LINE);
}

/* configurations for backup mode wakeup */
static void config_backup_wakeup(void)
{
	/* Take care the table 11-5 in datasheet, not all pin can been set */
#ifdef CONF_BOARD_BM_USART
	/* EIC and AST can wakeup the device */
	bpm_enable_wakeup_source(BPM,
			(1 << BPM_BKUPWEN_EIC) | (1 << BPM_BKUPWEN_AST));

	/* EIC can wake the device from backup mode */
	bpm_enable_backup_pin(BPM, 1 << GPIO_PUSH_BUTTON_EIC_LINE);
#else
	/* Only AST can wakeup the device */
	bpm_enable_wakeup_source(BPM, (1 << BPM_BKUPWEN_AST));
#endif

	/**
	 * Retain I/O lines after wakeup from backup.
	 * Disable to undo the previous retention state then enable.
	 */
	bpm_disable_io_retention(BPM);
	bpm_enable_io_retention(BPM);
	/* Enable fast wakeup */
	bpm_enable_fast_wakeup(BPM);
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
			"  s: Switch Power scale. \r\n"
			"  0: Enter Sleep mode 0. \r\n"
			"  1: Enter Sleep mode 1. \r\n"
			"  2: Enter Sleep mode 2. \r\n"
			"  3: Enter Sleep mode 3. \r\n"
			"  4: Enter Wait mode. \r\n"
			"  5: Enter Retention mode. \r\n"
			"  6: Enter Backup mode. \r\n"
			"  h: Display menu \r\n"
			"  --AST has been used to exit low power mode.--\r\n"
#ifdef CONF_BOARD_BM_USART
			"  --Push button can also be used to exit low power mode.--\r\n"
			"\r\n"
			"-- IMPORTANT: This example requires a board "
			"monitor firmware version V1.3 or greater.\r\n\r\n");
#else
			"  --Push button can also be used to exit low power mode"
			" except the backup mode.--\r\n"
			"\r\n");
#endif
}

/**
 * \brief Application entry point for BPM example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t key;

	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	/* Initialize the console uart */
	configure_console();

#ifdef CONF_BOARD_BM_USART
	/* Initialize the board monitor  */
	bm_init();
#endif

	/* Configurate the AST to wake up */
	config_ast();

	/* Configurate the EIC */
	config_buttons();

	/* Configurate the backup wakeup source */
	config_backup_wakeup();

	/* Output example information */
	printf("\r\n");
	printf("-- BPM Example --\r\n");
	printf("-- %s\r\n", BOARD_NAME);
	printf("-- Compiled: %s %s --\r\n", __DATE__, __TIME__);

	/* Display menu */
	display_menu();

	while(1) {
		scanf("%c", (char *)&key);

		switch (key) {
		case 'h':
			display_menu();
			break;

		case 's':
			if (ps_status == BPM_PS_1) {
				printf("\r\n--Switch Power scale to 1.8V\r\n");
				ps_status = BPM_PS_0;
			} else {
				printf("\r\n--Switch Power scale to 1.2V\r\n");
				ps_status = BPM_PS_1;
			}
			/* Power scaling setup */
			bpm_configure_power_scaling(BPM, ps_status,
					BPM_PSCM_CPU_NOT_HALT);
			while((bpm_get_status(BPM) & BPM_SR_PSOK) == 0);
#ifdef CONF_BOARD_BM_USART
			bm_send_mcu_status(ps_statuses[ps_status], current_sleep_mode,
					12000000, CPU_SRC_RC4M);
#endif
			break;

		case '0':
#ifdef CONF_BOARD_BM_USART
			current_sleep_mode = SLEEP_MODE_0;
			bm_send_mcu_status(ps_statuses[ps_status], current_sleep_mode,
					12000000, CPU_SRC_RC4M);
#endif
			printf("\r\n--Enter Sleep mode 0.\r\n");
			ast_start(AST);
			/* 
			 * Wait for the printf operation to finish before setting the
			 * device in a power save mode.
			 */
			delay_ms(30);
			bpm_sleep(BPM, BPM_SM_SLEEP_0);
			printf("\r\n--Exit Sleep mode 0.\r\n");
			break;

		case '1':
#ifdef CONF_BOARD_BM_USART
			current_sleep_mode = SLEEP_MODE_1;
			bm_send_mcu_status(ps_statuses[ps_status], current_sleep_mode,
					12000000, CPU_SRC_RC4M);
#endif
			printf("\r\n--Enter Sleep mode 1.\r\n");
			ast_start(AST);
			/* 
			 * Wait for the printf operation to finish before setting the
			 * device in a power save mode.
			 */
			delay_ms(30);
			bpm_sleep(BPM, BPM_SM_SLEEP_1);
			printf("\r\n--Exit Sleep mode 1.\r\n");
			break;

		case '2':
#ifdef CONF_BOARD_BM_USART
			current_sleep_mode = SLEEP_MODE_2;
			bm_send_mcu_status(ps_statuses[ps_status], current_sleep_mode,
					12000000, CPU_SRC_RC4M);
#endif
			printf("\r\n--Enter Sleep mode 2.\r\n");
			ast_start(AST);
			/* 
			 * Wait for the printf operation to finish before setting the
			 * device in a power save mode.
			 */
			delay_ms(30);
			bpm_sleep(BPM, BPM_SM_SLEEP_2);
			printf("\r\n--Exit Sleep mode 2.\r\n");
			break;

		case '3':
#ifdef CONF_BOARD_BM_USART
			current_sleep_mode = SLEEP_MODE_3;
			bm_send_mcu_status(ps_statuses[ps_status], current_sleep_mode,
					12000000, CPU_SRC_RC4M);
#endif
			printf("\r\n--Enter Sleep mode 3.\r\n");
			ast_start(AST);
			/* 
			 * Wait for the printf operation to finish before setting the
			 * device in a power save mode.
			 */
			delay_ms(30);
			bpm_sleep(BPM, BPM_SM_SLEEP_3);
			printf("\r\n--Exit Sleep mode 3.\r\n");
			break;

		case '4':
#ifdef CONF_BOARD_BM_USART
			current_sleep_mode = SLEEP_MODE_WAIT;
			bm_send_mcu_status(ps_statuses[ps_status], current_sleep_mode,
					12000000, CPU_SRC_RC4M);
#endif
			printf("\r\n--Enter Wait mode.\r\n");
			ast_start(AST);
			/* 
			 * Wait for the printf operation to finish before setting the
			 * device in a power save mode.
			 */
			delay_ms(30);
			bpm_sleep(BPM, BPM_SM_WAIT);
			printf("\r\n--Exit Wait mode.\r\n");
			break;

		case '5':
#ifdef CONF_BOARD_BM_USART
			current_sleep_mode = SLEEP_MODE_RETENTION;
			bm_send_mcu_status(ps_statuses[ps_status], current_sleep_mode,
					12000000, CPU_SRC_RC4M);
#endif
			printf("\r\n--Enter Retention mode.\r\n");
			ast_start(AST);
			/* 
			 * Wait for the printf operation to finish before setting the
			 * device in a power save mode.
			 */
			delay_ms(30);
			bpm_sleep(BPM, BPM_SM_RET);
			printf("\r\n--Exit Retention mode.\r\n");
			break;

		case '6':
#ifdef CONF_BOARD_BM_USART
			current_sleep_mode = SLEEP_MODE_BACKUP;
			bm_send_mcu_status(ps_statuses[ps_status], current_sleep_mode,
					12000000, CPU_SRC_RC4M);
#endif
			printf("\r\n--Enter Backup mode.\r\n");
			ast_start(AST);
			/* 
			 * Wait for the printf operation to finish before setting the
			 * device in a power save mode.
			 */
			delay_ms(30);
			bpm_sleep(BPM, BPM_SM_BACKUP);
			printf("\r\n--Exit Backup mode.\r\n");
			break;

		default:
			break;
		}
	}
}
