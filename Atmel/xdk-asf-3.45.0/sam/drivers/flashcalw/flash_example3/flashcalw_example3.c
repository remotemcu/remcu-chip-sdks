/**
 * \file
 *
 * \brief FLASHCALW example3 for SAM.
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
 * defines, enums, and typedefs for the FLASHCALW software driver.
 *
 * It also comes bundled with several examples. Using a Fibonacci calculation,
 * this example demonstrates how much the PicoCache feature can improve the
 * execution speed.
 *
 * \note The PicoCache always has a positive impact in terms of power
 * consumption (Explanation: since the PicoCache features allows to do less
 * access to the Flash, the power consumption is therefore reduced). Note
 * however that the PicoCache feature may have a negligible negative impact on
 * the execution speed when there are no wait states on the Flash (which may be
 * the case when the CPU runs at 12MHz in some cases). See also the Flash
 * Characteristics in the electrical characteristics section of the datasheet
 * for more information.
 *
 * Operating mode of the example:
 *   -# After reset, the example will run without PicoCache at 48MHz with 1 wait
 * state.
 *   -# A Fibonacci calculation will be done.
 *   -# The power consumption of the calculation without PicoCache will be
 * displayed on the board monitor.
 *   -# The time spent on the Fibonacci will be displayed on the debug monitor.
 *   -# PicoCache will be enabled.
 *   -# The Fibonacci calculation will be done again.
 *   -# The power consumption of the calculation with PicoCache will be
 * displayed on the board monitor.
 *   -# The time spent on the Fibonacci will be displayed on the debug monitor.
 *   -# The cache hit number will be displayed on the debug monitor, which is
 * the cause of the performance improvement and power consumption decrease.
 *   -# Then the example will run without PicoCache at 12MHz with 0 wait state.
 *   -# A Fibonacci calculation will be done.
 *   -# The power consumption of the calculation without PicoCache will be
 * displayed on the board monitor.
 *   -# The time spent on the Fibonacci will be displayed on the debug monitor.
 *   -# PicoCache will be enabled.
 *   -# The Fibonacci calculation will be done again.
 *   -# The power consumption of the calculation with PicoCache will be
 * displayed on the board monitor. The power consumption will be lower.
 *   -# The time spent on the Fibonacci will be displayed on the debug monitor.
 *   -# The cache hit number will be displayed on the debug monitor, which is
 * the cause of the performance improvement and power consumption decrease.
 *
 * \section files Main Files
 *   - flashcalw.c: FLASHCALW driver;
 *   - flashcalw.h: FLASHCALW driver header file;
 *   - time_tick_sam.c: Time tick utilities for getting the time spent on the
 *   calculation;
 *   - time_tick.h: Time tick utilities header file;
 *   - flashcalw_example3.c: PicoCache access example application.
 *
 * \section compilinfo Compilation Information
 * This software is written for GNU GCC and IAR Embedded Workbench
 * for Atmel. Other compilers may or may not work.
 *
 * \section deviceinfo Device Information
 * SAM4L devices with a FLASHCALW module can be used.
 *
 * \section configinfo Configuration Information
 * This example has been tested with the following kits:
 * - SAM4L-EK evaluation kit;
 * - SAM4L Xplained Pro
 * - SAM4L8 Xplained Pro
 * This example has been tested with the following configuration:
 * - CPU clock: 48 MHz;
 * - USARTx abstracted with a USB CDC connection to a PC;
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
#include "time_tick.h"

/** Fibonacci number */
#define FIBONACCI_NUM    32

#define LOWER_SYS_CLK 12000000

/**
 *  \brief Configure serial console.
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
 *  \brief Reconfigure serial console.
 */
static void reconfigure_com_port(void)
{
	const sam_usart_opt_t opt = {
		.baudrate = CONF_UART_BAUDRATE,
		.char_length = CONF_UART_CHAR_LENGTH,
		.parity_type = CONF_UART_PARITY,
		.stop_bits = CONF_UART_STOP_BITS,
		.channel_mode = US_MR_CHMODE_NORMAL,
		.irda_filter = 0,
	};
	usart_init_rs232(CONF_UART, &opt, LOWER_SYS_CLK);
	usart_enable_tx(CONF_UART);
}

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
 * \brief This is an example demonstrating Fibonacci calculation
 *         with and without PicoCache.
 *
 * \param caption     Caption to print before running the example.
 * \param pico_enable Enable PicoCache or not.
 */
static void flash_picocache_example(const char *caption, bool pico_enable)
{
	uint32_t tick_start, time_ms;

	printf("\n\r--------------\n\r%s\n\r", caption);

	/* Enable PicoCache if required */
	if (pico_enable) {
		flashcalw_picocache_enable();

		flashcalw_picocache_set_monitor_mode(HCACHE_MCFG_MODE_IHIT);
		flashcalw_picocache_enable_monitor();
		flashcalw_picocache_reset_monitor();
	} else {
		flashcalw_picocache_disable();
		flashcalw_picocache_disable_monitor();
	}

	/* Get current time tick */
	tick_start = time_tick_get();

	/* Do the Fibonacci calculation. */
	recfibo(FIBONACCI_NUM);

	/* Calculate the Fibonacci spent time */
	time_ms = time_tick_calc_delay(tick_start, time_tick_get());
	if (time_ms) {
		printf("Time spent: %u ms\r\n", (unsigned int)time_ms);
	}

	/* Display cache hit counter */
	if (pico_enable) {
		printf("Pico cache instruction hit: %u \r\n",
			(unsigned int)flashcalw_picocache_get_monitor_cnt());
	}
}

static void wait_for_pushbutton(void)
{
	while (ioport_get_pin_level(GPIO_PUSH_BUTTON_0));
	delay_ms(1);
	while (!ioport_get_pin_level(GPIO_PUSH_BUTTON_0));
	delay_ms(1);
}

/**
 * \brief main function. Do the Fibonacci calculation with and without
 * PicoCache and print the calculation time to the UART console.
 */
int main(void)
{
	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	/* Initialize the console uart */
	configure_console();

	/* Output example information */
	printf("-- FLASHCALW Example3 --\r\n");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	/* Intialize time tick utilities */
	time_tick_init(sysclk_get_cpu_hz());

	/* Calculate the Fibonacci without PicoCache */
	flash_picocache_example(
		"Fibonacci calculation without PicoCache at 48MHz",
		false);

	/* Calculate the Fibonacci with PicoCache */
	flash_picocache_example(
		"Fibonacci calculation with PicoCache at 48MHz",
		true);

	puts("From now on, System is running at 12MHz\r");
	puts("Please check the power consumption\r");
	printf("Push %s to continue\r\n", BUTTON_0_NAME);
	wait_for_pushbutton();
	sysclk_set_prescalers(2, 0, 0, 0, 0);
	reconfigure_com_port();

	flashcalw_set_wait_state(0);
	/* Calculate the Fibonacci without PicoCache */
	flash_picocache_example(
		"Fibonacci calculation without PicoCache at 12MHz",
		false);

	puts("Please check the power consumption\r");
	printf("Push %s to continue\r\n", BUTTON_0_NAME);
	wait_for_pushbutton();

	/* Calculate the Fibonacci with PicoCache */
	flash_picocache_example(
		"Fibonacci calculation with PicoCache at 12MHz",
		true);

	puts("End");

	while (true) {
	}
}
