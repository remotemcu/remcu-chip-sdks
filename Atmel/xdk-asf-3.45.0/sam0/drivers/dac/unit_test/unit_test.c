/**
 * \file
 *
 * \brief SAM DAC Unit Test
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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
 * \mainpage SAM0 DAC Unit Test
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This unit test carries out tests for the DAC driver.
 * DAC conversion has already been tested by quick_start.
 * This test cases consists of the following functionalities:
 *      - Test for DAC initialization.
 *      - Test for DAC buffer empty
 */

/**
 * \page appdoc_main SAM0 DAC Unit Test
 *
 * Overview:
 * - \ref asfdoc_sam0_dac_unit_test_intro
 * - \ref asfdoc_sam0_dac_unit_test_setup
 * - \ref asfdoc_sam0_dac_unit_test_usage
 * - \ref asfdoc_sam0_dac_unit_test_compinfo
 * - \ref asfdoc_sam0_dac_unit_test_contactinfo
 *
 * \section asfdoc_sam0_dac_unit_test_intro Introduction
 * \copydetails appdoc_preface
 *
 * The following kit is required for carrying out the test:
 *  - SAM D21 Xplained Pro board
 *  - SAM L21 Xplained Pro board
 *  - SAM DA1 Xplained Pro board
 *  - SAM HA1G16A Xplained Pro board
 *  - SAM C21 Xplained Pro board
 *  - SAM D20 Xplained Pro board
 *
 * \section asfdoc_sam0_dac_unit_test_setup Setup
 *
 * To run the test:
 *  - Connect the supported Xplained Pro board to the computer using a
 *    micro USB cable.
 *  - Open the virtual COM port in a terminal application.
 *    \note The USB composite firmware running on the Embedded Debugger (EDBG)
 *          will enumerate as debugger, virtual COM port and EDBG data
 *          gateway.
 *  - Build the project, program the target and run the application.
 *    The terminal shows the results of the unit test.
 *
 * \section asfdoc_sam0_dac_unit_test_usage Usage
 *  - Different operations of the dac are tested.
 *
 * \section asfdoc_sam0_dac_unit_test_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section asfdoc_sam0_dac_unit_test_contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com">http://www.microchip.com</a>.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include <stdio_serial.h>
#include <string.h>
#include "conf_test.h"

void configure_rtc_count(void);
void configure_event_resource(void);
/* Structure for UART module connected to EDBG (used for unit test output) */
struct usart_module cdc_uart_module;
/* Structure for DAC module */
struct dac_module dac_instance;
/* Structure for RTC module */
struct rtc_module rtc_instance;
/* Structure for event source */
struct events_resource event_dac;

/**
 * \brief Initialize the USART for unit test
 *
 * Initializes the SERCOM USART (SERCOM4) used for sending the
 * unit test status to the computer via the EDBG CDC gateway.
 */
static void cdc_uart_init(void)
{
	struct usart_config usart_conf;

	/* Configure USART for unit test output */
	usart_get_config_defaults(&usart_conf);
	usart_conf.mux_setting = CONF_STDIO_MUX_SETTING;
	usart_conf.pinmux_pad0 = CONF_STDIO_PINMUX_PAD0;
	usart_conf.pinmux_pad1 = CONF_STDIO_PINMUX_PAD1;
	usart_conf.pinmux_pad2 = CONF_STDIO_PINMUX_PAD2;
	usart_conf.pinmux_pad3 = CONF_STDIO_PINMUX_PAD3;
	usart_conf.baudrate    = CONF_STDIO_BAUDRATE;

	stdio_serial_init(&cdc_uart_module, CONF_STDIO_USART, &usart_conf);
	usart_enable(&cdc_uart_module);
}

/**
 * \configure event source for DAC conversion
 *
 *   set rtc overflow as the event generator for DAC conversion
 */
void configure_event_resource(void)
{
	struct events_config event_config;
	events_get_config_defaults(&event_config);

	event_config.generator      = EVSYS_ID_GEN_RTC_OVF;
	event_config.edge_detect    = EVENTS_EDGE_DETECT_NONE;
	event_config.path           = EVENTS_PATH_ASYNCHRONOUS;
	event_config.clock_source   = GCLK_GENERATOR_0;

	events_allocate(&event_dac, &event_config);
#if (SAML21)
	events_attach_user(&event_dac, EVSYS_ID_USER_DAC_START_0);
#else
	events_attach_user(&event_dac, EVSYS_ID_USER_DAC_START);
#endif
}

/**
 * \init rtc for event generator
 *
 *  set rtc clock prescaler and mode to generate overflow events
 */
void configure_rtc_count(void)
{
	struct rtc_count_events rtc_event;
	struct rtc_count_config config_rtc_count;
	rtc_count_get_config_defaults(&config_rtc_count);
	config_rtc_count.prescaler           = RTC_COUNT_PRESCALER_DIV_1;
	config_rtc_count.mode                = RTC_COUNT_MODE_16BIT;
#ifdef FEATURE_RTC_CONTINUOUSLY_UPDATED
	config_rtc_count.continuously_update = true;
#endif
	rtc_count_init(&rtc_instance, RTC, &config_rtc_count);
	rtc_event.generate_event_on_overflow = true;
	rtc_count_enable_events(&rtc_instance, &rtc_event);
	rtc_count_enable(&rtc_instance);
}

/**
 * \brief Initialize the DAC for unit test
 *
 * Initializes the DAC module to accept events to start conversion
 */
static void run_dac_init_test(const struct test_case *test)
{
	enum status_code status = STATUS_ERR_IO;
	struct dac_config config_dac;

	dac_get_config_defaults(&config_dac);
#if (SAML21)
    dac_instance.start_on_event[0] = true;
#else
	dac_instance.start_on_event = true;
#endif
	status = dac_init(&dac_instance, DAC, &config_dac);
		/* Check for successful initialization */
	test_assert_true(test, status == STATUS_OK,
			"DAC initialization failed");

	/* set dac start conversion on events*/
#if  (SAML21)
	struct dac_events events =
		{ .on_event_chan0_start_conversion = true };
#else
	struct dac_events events =
		{ .on_event_start_conversion = true };
#endif
	dac_enable_events(&dac_instance, &events);

	struct dac_chan_config config_dac_chan;
	dac_chan_get_config_defaults(&config_dac_chan);
	dac_chan_set_config(&dac_instance, DAC_CHANNEL_0,
			&config_dac_chan);
	dac_chan_enable(&dac_instance, DAC_CHANNEL_0);
	dac_enable(&dac_instance);
}

/**
 * \internal
 * \brief Test for DAC conversion driven by events in polled mode.
 *
 * after the first event, dac should enter channel buffer empty status.
 * after the second event, dac should enter channel buffer underrun status.
 */
static void run_dac_event_control_test(const struct test_case *test)
{
	enum status_code status;
	uint32_t dac_status;

	status = dac_chan_write(&dac_instance, DAC_CHANNEL_0, 100);
	test_assert_true(test, status == STATUS_OK,
			"DAC chan write failed");

	configure_rtc_count();
	rtc_count_set_period(&rtc_instance, 1);
	configure_event_resource();

	/* DAC buffer empty test*/
	delay_ms(3);
	dac_status = dac_get_status(&dac_instance);
	test_assert_true(test, (dac_status & DAC_STATUS_CHANNEL_0_EMPTY)
			== DAC_STATUS_CHANNEL_0_EMPTY,
			"dac channel buffer empty didn't happen");

	/* DAC buffer underrun test*/
	delay_ms(3);
	dac_status = dac_get_status(&dac_instance);
	test_assert_true(test, (dac_status & DAC_STATUS_CHANNEL_0_UNDERRUN)
			== DAC_STATUS_CHANNEL_0_UNDERRUN,
			"dac channel buffer underrun didn't happen");
}

/**
 * \brief Run DAC unit tests
 *
 * Initializes the system and serial output, then sets up the
 * DAC unit test suite and runs it.
 */
int main(void)
{

	system_init();
	cdc_uart_init();
	delay_init();

	DEFINE_TEST_CASE(dac_init_test, NULL,
			run_dac_init_test, NULL,
			"dac buffer init test");
	DEFINE_TEST_CASE(dac_event_control_test, NULL,
			run_dac_event_control_test, NULL,
			"dac event control conversion test");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(dac_tests) = {
		&dac_init_test,
		&dac_event_control_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(dac_test_suite, dac_tests,
			"SAM DAC driver test suite");

	/* Run all tests in the suite*/
	test_suite_run(&dac_test_suite);

	while (true) {
		/* Intentionally left empty */
	}
}

