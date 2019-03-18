/**
 * \file
 *
 * \brief Frequency Meter Example for SAM4L.
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
 * \mainpage Frequency Meter Example
 *
 * \section Purpose
 *
 * The freqm_example demonstrates how to use frequency meter.
 *
 * \section Requirements
 *
 * This example can be used on SAM4L devices.
 *
 * \section Description
 *
 * The SAM4L controller select refclk and start frequency meter to measure the
 * selected clock.
 *
 * \section Usage
 *
 * - Build the program and download it to the evaluation board. Please
 *  refer to the SAM4L main page documentation
 *  http://www.microchip.com/products/microcontrollers/ARM/SAM4L.aspx
 * -# On the computer, open and configure a terminal application
 *    (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# In the terminal window, the following text should appear (values depend
 *    on the board and chip used):
 *    \code
	-- Freqm Example xxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 * -# The sent text should appear.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"

#define STRING_EOL    "\r"
#define STRING_HEADER "-- Freqm Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/** GENCLK Configuration Value */
#define GCLK_ID         0
#define GCLK_SOURCE     GENCLK_SRC_CLK_CPU
#define GCLK_DIV        1

/** FREQM instance */
struct freqm_dev_inst g_freqm_inst;

/** FREQM configuration */
struct freqm_config  g_freqm_cfg;

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
 * \brief Application entry point for freqm example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint32_t clk, result;
	struct pll_config pcfg;
	
	/* Initialize the SAM system. */
	sysclk_init();
	board_init();
	
	/* Initialize the UART console. */
	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);

	/* Measure default clock. */
	freqm_get_config_defaults(&g_freqm_cfg);
	freqm_init(&g_freqm_inst, FREQM, &g_freqm_cfg);
	freqm_enable(&g_freqm_inst);
	freqm_start_measure(&g_freqm_inst);

	if (freqm_get_result_blocking(&g_freqm_inst, &result) == STATUS_OK) {
		clk = (result / FREQM_DURATION_DEFAULT) * OSC_RC32K_NOMINAL_HZ;
		printf(" Current CPU clock mesurement result is %d Hz. \n\r",
				(int)clk);
	} else {
		printf(" Current CPU clock mesurement Failed. \n\r");
	}

	/* Measure clock from external OSC0. */
	osc_enable(OSC_ID_OSC0);
	osc_wait_ready(OSC_ID_OSC0);
	g_freqm_cfg.msr_clk = FREQM_OSC0;
	freqm_init(&g_freqm_inst, FREQM, &g_freqm_cfg);
	freqm_start_measure(&g_freqm_inst);

	if (freqm_get_result_blocking(&g_freqm_inst, &result) == STATUS_OK) {
		clk = (result / FREQM_DURATION_DEFAULT) * OSC_RC32K_NOMINAL_HZ;
		printf(" Current OSC0 output clock mesurement result is %d Hz. \n\r",
				(int)clk);
	} else {
		printf(" Current OSC0 output clock mesurement Failed. \n\r");
	}

	/* Measure clock from PLL0. */
	pll_config_init(&pcfg, PLL_SRC_OSC0, 1, 96000000 /
			BOARD_OSC0_HZ);
	pll_enable(&pcfg, 0);
	pll_wait_for_lock(0);
	g_freqm_cfg.msr_clk = FREQM_PLL0;
	freqm_init(&g_freqm_inst, FREQM, &g_freqm_cfg);
	freqm_start_measure(&g_freqm_inst);

	if (freqm_get_result_blocking(&g_freqm_inst, &result) == STATUS_OK) {
		clk = (result / FREQM_DURATION_DEFAULT) * OSC_RC32K_NOMINAL_HZ;
		printf(" Current PLL0 output clock mesurement result is %d Hz. \n\r",
				(int)clk);
	} else {
		printf(" Current PLL0 output clock mesurement Failed. \n\r");
	}

	/* Change CLK_REF source to RCSYS and Measure clock from GENCLK0. */
	osc_disable(OSC_ID_OSC0);
	osc_enable(OSC_ID_RCSYS);
	osc_wait_ready(OSC_ID_RCSYS);
	genclk_enable_config(GCLK_ID, GCLK_SOURCE, GCLK_DIV);
	g_freqm_cfg.msr_clk = FREQM_GENCLK0;
	g_freqm_cfg.ref_clk = FREQM_REF_RCOSC;
	g_freqm_cfg.duration= FREQM_DURATION_DEFAULT;
	freqm_init(&g_freqm_inst, FREQM, &g_freqm_cfg);
	freqm_start_measure(&g_freqm_inst);

	if (freqm_get_result_blocking(&g_freqm_inst, &result) == STATUS_OK) {
		clk = (result / FREQM_DURATION_DEFAULT) * OSC_RCSYS_NOMINAL_HZ;
		printf(" Current GENCLK0 output clock mesurement result is %d Hz. \n\r",
				(int)clk);
	} else {
		printf(" Current GENCLK0 output clock mesurement Failed. \n\r");
	}
	
	while (1) {
	}
}
