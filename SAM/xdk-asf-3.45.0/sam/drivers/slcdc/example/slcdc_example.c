/**
 * \file
 *
 * \brief SLCDC example for SAM.
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
 * \mainpage
 * \section intro Introduction
 * This example demonstrates how to use SLCDC driver to address an external
 * LCD segment. The LCD still display in steady state after core
 * entering backup mode.
 *
 * \section files Main Files
 *  - slcdc.c SLCDC driver implementation
 *  - slcdc.h SLCDC driver definitions
 *  - slcdc_example.c example application
 *
 * \section compilinfo Compilation Information
 * This software is written for GNU GCC and IAR Embedded Workbench
 * for Atmel. Other compilers may or may not work.
 *
 * \section deviceinfo Device Information
 * All SAM devices with a SLCDC can be used.
 *
 * \section exampledescription Description of the example
 * After an initialization phase, the display memory in SLCDC will be set.
 * Then the core will enter backup mode and LCD still display in steady sate mode.
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

/** LCD buffer on-time */
#define LCD_BUF_TIME         SLCDC_BUFTIME_X64_SCLK

/** LCD frame rate value */
#define LCD_FRAME_RATE     64

/** LCD display mode */
#define LCD_DISP_MODE         SLCDC_DISPMODE_NORMAL

/** LCD power mode */
#define LCD_POWER_MODE         SLCDC_POWER_MODE_LCDON_INVR

#if SAM4C
/* The LCD segment map number */
#define LCD_SEGMAP_NUM_0     0xff720000
#define LCD_SEGMAP_NUM_1     0x3ffff
#elif SAM4CP
/* The LCD segment map number */
#define LCD_SEGMAP_NUM_0     0x9F73FFF8
#define LCD_SEGMAP_NUM_1     0x0FDFC
#elif SAM4CM
/* The LCD segment map number */
#define LCD_SEGMAP_NUM_0     0x7F0056F8
#define LCD_SEGMAP_NUM_1     0x00001
#endif
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
 * \brief Application entry point for SLCDC example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* SLCDC configuration */
	struct slcdc_config slcdc_cfg;
	status_code_t status;

	/* Initialize the SAM system */
	sysclk_init();
	board_init();
	sleepmgr_init();

	/* Initialize the console uart */
	configure_console();

	/* Output example information */
	printf("-- SLCDC Example --\r\n");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

#if SAM4C
	/* Turn on the backlight. */
	ioport_set_pin_level(LCD_BL_GPIO, LCD_BL_ACTIVE_LEVEL);
#endif
	/* Set LCD power mode: Internal supply */
	supc_set_slcd_power_mode(SUPC, LCD_POWER_MODE);
	
	/* SLCDC Reset */
	slcdc_reset(SLCDC);
	/*
	 * SLCDC initialization
	 * - Clock,
	 * - Display mode: Normal
	 * - Frame Rate:  64Hz
	 */
	slcdc_cfg.buf_time = LCD_BUF_TIME;
	slcdc_cfg.frame_rate= LCD_FRAME_RATE;
	slcdc_cfg.disp_mode = LCD_DISP_MODE;

	status = slcdc_init(SLCDC, &slcdc_cfg);
	if (status != STATUS_OK) {
		printf("-- Initialization fails! --\r\n");
		while (1) {
		}
	}
	/*LCD seg mapped on SEGx I/O pin */
	slcdc_set_segmap0(SLCDC, LCD_SEGMAP_NUM_0);
	slcdc_set_segmap1(SLCDC, LCD_SEGMAP_NUM_1);

	/* Enable SLCDC */
	slcdc_enable(SLCDC);
	while(!slcdc_get_status(SLCDC));
	
	/* Display all SLCDC memory*/
	slcdc_set_display_memory(SLCDC);

	printf("-- Enter Backup Mode! --\r\n");
	
	/* Enter in sleep mode */
	sleepmgr_enter_sleep();

	while (1) {
	}
}
