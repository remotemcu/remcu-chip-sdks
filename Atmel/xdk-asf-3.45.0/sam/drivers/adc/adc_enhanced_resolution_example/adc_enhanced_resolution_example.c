/**
 * \file
 *
 * \brief ADC Enhanced Resolution example.
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
 * \mainpage ADC Enhanced Resolution Example
 *
 * \section Purpose
 *
 * This example demonstrates how to use the enhanced resolution feature.
 *
 * \section Requirements
 *
 * This example can be used on boards:
 * - sam4n16c_sam4n_xplained_pro
 * - samg53n19_samg_xplained_pro
 * - samg55j19_samg_xplained_pro
 *
 * \section Description
 *
 * The ADC on normally operates in 8-bit, 10-bit or 12-bit resolution mode.
 * But obtained by interpolating multiple samples, the hegher resolution
 * mode can be achieved, which is so called enhanced resolution mode.
 * For basic resolution plus one bit mode, 4 samples are used, which gives an
 * effective sample rate of 1/4 of the actual sample frequency.
 * For basic resolution plus two bit mode, 16 samples are used, giving an
 * effective sample rate of 1/16 of the actual sample frequency. This
 * arrangement allows conversion speed to be traded for better accuracy.
 *
 * \section Usage
 *
 * -# Build the program and download it into the evaluation board.
 * -# On the computer, open and configure a terminal application
 *    (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# In the terminal window, the
 *    following text should appear (values depend on the board and the chip
 *used):
 *    \code
	-- ADC Enhanced Resolution Example xxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "asf.h"

/** Reference voltage for ADC,in mv. */
#define VOLT_REF        (3300)

/** The maximal digital value */
#define MAX_DIGITAL_8_BIT  (255UL)
#define MAX_DIGITAL_10_BIT (1023UL)
#define MAX_DIGITAL_11_BIT (2046UL)
#define MAX_DIGITAL_12_BIT (4092UL)
#if SAMG55
#define MAX_DIGITAL_13_BIT (8190UL)
#define MAX_DIGITAL_14_BIT (16382UL)
#define MAX_DIGITAL_15_BIT (32766UL)
#define MAX_DIGITAL_16_BIT (65534UL)
#endif

#define STRING_EOL    "\r"

#define STRING_HEADER "\n-- ADC Enhanced Resolution Example --\r\n" \
	"-- "BOARD_NAME " --\r\n" \
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

/** The conversion data is done flag */
volatile bool is_conversion_done = false;

/** The conversion data value */
volatile uint32_t g_ul_value = 0;

/** The maximal digital value */
static uint32_t g_max_digital;

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
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief Configure to trigger ADC by TIOA output of timer.
 */
static void configure_tc_trigger(void)
{
	uint32_t ul_div = 0;
	uint32_t ul_tc_clks = 0;
	uint32_t ul_sysclk = sysclk_get_cpu_hz();

	/* Enable peripheral clock. */
	pmc_enable_periph_clk(ID_TC0);
#if SAMG55
	/* Enable PCK output */
	pmc_disable_pck(PMC_PCK_3);
	pmc_switch_pck_to_sclk(PMC_PCK_3, PMC_PCK_PRES(0));
	pmc_enable_pck(PMC_PCK_3);
#endif

	/* TIOA configuration */
	ioport_set_pin_mode(PIN_TC0_TIOA0, PIN_TC0_TIOA0_MUX);
	ioport_disable_pin(PIN_TC0_TIOA0);

	/* Configure TC for a 1Hz frequency and trigger on RC compare. */
	tc_find_mck_divisor(1, ul_sysclk, &ul_div, &ul_tc_clks, ul_sysclk);
	tc_init(TC0, 0, ul_tc_clks | TC_CMR_CPCTRG | TC_CMR_WAVE |
			TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_SET);
	TC0->TC_CHANNEL[0].TC_RA = (ul_sysclk / ul_div) / 2;
	TC0->TC_CHANNEL[0].TC_RC = (ul_sysclk / ul_div) / 1;

	/* Start the Timer. */
	tc_start(TC0, 0);
}

/**
 * \brief Display main menu.
 */
static void display_menu(void)
{
	printf("\n\r-- press a key to select the resolution mode--\n\r"
#if SAMG55
	"-- a: Normal Resolution Mode, 12-bit --\n\r"
	"-- b: Enhanced Resolution Mode, 13-bit --\n\r"
	"-- c: Enhanced Resolution Mode, 14-bit --\n\r"
	"-- d: Enhanced Resolution Mode, 15-bit --\n\r"
	"-- e: Enhanced Resolution Mode, 16-bit --\n\r");
#else
	"-- a: Normal Resolution Mode, 8-bit --\n\r"
	"-- b: Normal Resolution Mode, 10-bit --\n\r"
	"-- c: Enhanced Resolution Mode, 11-bit --\n\r"
	"-- d: Enhanced Resolution Mode, 12-bit --\n\r");
#endif
}

/**
 * \brief Set ADC resolution mode.
 */
static void set_adc_resolution(void)
{
	uint8_t uc_key;
	uint8_t uc_done = 0;

	display_menu();

	while (!uc_done) {
		scanf("%c", (char *)&uc_key);

		switch (uc_key) {
#if SAMG55
		case 'a':
			g_max_digital = MAX_DIGITAL_12_BIT;
			adc_set_resolution(ADC, ADC_12_BITS);
			puts(" Set Resolution to Normal 12-bit \n\r");
			uc_done = 1;
			puts(" Quit Configuration \n\r");
			break;
		case 'b':
			g_max_digital = MAX_DIGITAL_13_BIT;
			adc_set_resolution(ADC, ADC_13_BITS);
			adc_average_on_single_trigger(ADC);
			puts(" Set Resolution to Enhanced 13-bit \n\r");
			uc_done = 1;
			puts(" Quit Configuration \n\r");
			break;

		case 'c':
			g_max_digital = MAX_DIGITAL_14_BIT;
			adc_set_resolution(ADC, ADC_14_BITS);
			adc_average_on_single_trigger(ADC);
			puts(" Set Resolution to Enhanced 14-bit \n\r");
			uc_done = 1;
			puts(" Quit Configuration \n\r");
			break;

		case 'd':
			g_max_digital = MAX_DIGITAL_15_BIT;
			adc_set_resolution(ADC, ADC_15_BITS);
			adc_average_on_single_trigger(ADC);
			puts(" Set Resolution to Enhanced 15-bit \n\r");
			uc_done = 1;
			puts(" Quit Configuration \n\r");
			break;

		case 'e':
			g_max_digital = MAX_DIGITAL_16_BIT;
			adc_set_resolution(ADC, ADC_16_BITS);
			adc_average_on_single_trigger(ADC);
			puts(" Set Resolution to Enhanced 16-bit \n\r");
			uc_done = 1;
			puts(" Quit Configuration \n\r");
			break;

#else
		case 'a':
			g_max_digital = MAX_DIGITAL_8_BIT;
			adc_set_resolution(ADC, ADC_8_BITS);
			puts(" Set Resolution to Normal 8-bit \n\r");
			uc_done = 1;
			puts(" Quit Configuration \n\r");
			break;
		case 'b':
			g_max_digital = MAX_DIGITAL_10_BIT;
			adc_set_resolution(ADC, ADC_10_BITS);
			puts(" Set Resolution to Normal 10-bit \n\r");
			uc_done = 1;
			puts(" Quit Configuration \n\r");
			break;

		case 'c':
			g_max_digital = MAX_DIGITAL_11_BIT;
			adc_set_resolution(ADC, ADC_11_BITS);
			adc_average_on_single_trigger(ADC);
			puts(" Set Resolution to Enhanced 11-bit \n\r");
			uc_done = 1;
			puts(" Quit Configuration \n\r");
			break;

		case 'd':
			g_max_digital = MAX_DIGITAL_12_BIT;
			adc_set_resolution(ADC, ADC_12_BITS);
			adc_average_on_single_trigger(ADC);
			puts(" Set Resolution to Enhanced 12-bit \n\r");
			uc_done = 1;
			puts(" Quit Configuration \n\r");
			break;
#endif
		default:
			break;
		}
	}
}

/**
 * \brief ADC interrupt callback function.
 */
static void adc_end_conversion(void)
{
	g_ul_value = adc_channel_get_value(ADC, ADC_CHANNEL_1);
	is_conversion_done = true;
}

/**
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	int32_t ul_vol;

	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);

	adc_enable();
#if SAMG55
	adc_select_clock_source_mck(ADC);
#endif

	struct adc_config adc_cfg;

	adc_get_config_defaults(&adc_cfg);

	adc_init(ADC, &adc_cfg);
	adc_channel_enable(ADC, ADC_CHANNEL_1);

	adc_set_trigger(ADC, ADC_TRIG_TIO_CH_0);

	adc_set_callback(ADC, ADC_INTERRUPT_EOC_1,
			adc_end_conversion, 1);

	set_adc_resolution();
	adc_start_calibration(ADC);

	/* Configure TC */
	configure_tc_trigger();

	while (1) {
		/* Check if ADC sample is done. */
		if (is_conversion_done == true) {
			ul_vol = g_ul_value * VOLT_REF / g_max_digital;
			printf("-- Voltage is: %4dmv\r\n", (int)ul_vol);
			is_conversion_done = false;
		}
	}
}
