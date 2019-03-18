/**
 * \file
 *
 * \brief SAM RTC Calendar Unit test
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
 * \mainpage SAM0 RTC calendar Unit Test
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This unit test carries out tests for the RTC calendor driver.
 * It consists of test cases for the following functionalities:
 *      - Test for RTC calendar initialization.
 *      - Test for RTC calendar polled mode.
 *      - Test for RTC calendar callback mode.
 */

/**
 * \page appdoc_main SAM RTC Unit Test
 *
 * Overview:
 * - \ref asfdoc_sam0_rtc_unit_test_intro
 * - \ref asfdoc_sam0_rtc_unit_test_setup
 * - \ref asfdoc_sam0_rtc_unit_test_usage
 * - \ref asfdoc_sam0_rtc_unit_test_compinfo
 * - \ref asfdoc_sam0_rtc_unit_test_contactinfo
 *
 * \section asfdoc_sam0_rtc_unit_test_intro Introduction
 * \copydetails appdoc_preface
 *
 * The following kit is required for carrying out the test:
 *  - SAM D21 Xplained Pro board
 *  - SAM L21 Xplained Pro board
 *  - SAM L22 Xplained Pro board
 *  - SAM L22 Xplained Pro B board
 *  - SAM R21 Xplained Pro board
 *  - SAM DA1 Xplained Pro board
 *  - SAM C21 Xplained Pro board
 *  - SAM D20 Xplained Pro board
 *  - SAM R30 Xplained Pro board
 *  - SAM R30 Module Xplained Pro board
 *  - SAM R34 Xplained Pro board
 *
 * \section asfdoc_sam0_rtc_unit_test_setup Setup
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
 * \section asfdoc_sam0_rtc_unit_test_usage Usage
 *  - Different modes of the RTC are tested.
 *
 * \section asfdoc_sam0_rtc_unit_test_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section asfdoc_sam0_rtc_unit_test_contactinfo Contact Information
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

/* Structure for UART module connected to EDBG (used for unit test output) */
struct usart_module cdc_uart_module;
/* Structure for RTC module */
struct rtc_module rtc_inst;

/* Interrupt flag used during callback test */
volatile bool interrupt_flag = false;


static void rtc_calendar_alarm_match_callback(void)
{
	/* Do something on RTC alarm match here */
	interrupt_flag = true;
}

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
 * \internal
 * \brief Test for RTC calendar polled mode test.
 *
 * This test initializes the RTC module and checks whether the
 * initialization is successful or not.
 *
 * Then this test executes alarm match test and overflow test.
 *
 * \param test Current test case.
 */
static void run_rtc_calendar_test(const struct test_case *test)
{
	enum status_code status;
	bool result;

	/* Structure for RTC calendar configuration */
	struct rtc_calendar_config config;
	rtc_calendar_get_config_defaults(&config);

	/* Initialize the RTC */
	struct rtc_calendar_time calendar_time;
	rtc_calendar_get_time_defaults(&calendar_time);
	config.clock_24h     = true;
	rtc_calendar_init(&rtc_inst, RTC, &config);


 	struct rtc_calendar_alarm_time alarm;
	alarm.time.year = 2015;
	alarm.time.month=1;
	alarm.time.day=1;
	alarm.time.hour=0;
	alarm.time.minute=0;
	alarm.time.second=1;
	alarm.mask=RTC_CALENDAR_ALARM_MASK_YEAR;
	status = rtc_calendar_set_alarm(&rtc_inst, &alarm, 0);
	test_assert_true(test, status == STATUS_OK,
			"RTC set calendar alarm failed");
			
	/* Enable the RTC */
	rtc_calendar_enable(&rtc_inst);

	/* calendar overflow test */
	calendar_time.year   = 2063;
	calendar_time.month  = 12;
	calendar_time.day    = 31;
	calendar_time.hour   = 23;
	calendar_time.minute = 59;
	calendar_time.second = 59;
	rtc_calendar_set_time(&rtc_inst, &calendar_time);
	delay_s(2);
	result = rtc_calendar_is_overflow(&rtc_inst);
	test_assert_true(test, result == true,
		"RTC calendar overflow test failed");
	rtc_calendar_clear_overflow(&rtc_inst);

	/* calendar year mask alarm match test */
    	calendar_time.year   = 2014;
    	rtc_calendar_set_time(&rtc_inst, &calendar_time);
	delay_s(5);
        
	result = rtc_calendar_is_alarm_match(&rtc_inst,0);
	test_assert_true(test, result ==  true,
		"RTC calendar alarm match test failed");

	rtc_calendar_clear_alarm_match(&rtc_inst,0);
	rtc_calendar_disable(&rtc_inst);
}

static void run_rtc_calendar_interrupt_test(const struct test_case *test)
{
	enum status_code status;

	/* RTC calendar hour mask alarm match test*/
	status = rtc_calendar_register_callback(
			&rtc_inst, rtc_calendar_alarm_match_callback, RTC_CALENDAR_CALLBACK_ALARM_0);
	test_assert_true(test, status == STATUS_OK,
			"RTC register callback failed");
	rtc_calendar_enable_callback(&rtc_inst, RTC_CALENDAR_CALLBACK_ALARM_0);

	struct rtc_calendar_alarm_time alarm;
	alarm.time.year = 2015;
	alarm.time.month=1;
	alarm.time.day=1;
	alarm.time.hour=0;
	alarm.time.minute=0;
	alarm.time.second=1;
	alarm.mask=RTC_CALENDAR_ALARM_MASK_HOUR;
	status = rtc_calendar_set_alarm(&rtc_inst, &alarm, 0);

	struct rtc_calendar_time calendar_time;
	calendar_time.year   = 2014;
	calendar_time.month  = 12;
	calendar_time.day    = 31;
	calendar_time.hour   = 23;
	calendar_time.minute = 59;
	calendar_time.second = 59;

	rtc_calendar_set_time(&rtc_inst, &calendar_time);
	/* Enable the RTC */
	rtc_calendar_enable(&rtc_inst);


	delay_s(5);
	test_assert_true(test,interrupt_flag == true ,
			"RTC calendar interrupt test failed");

	rtc_calendar_clear_alarm_match(&rtc_inst, 0);
	rtc_calendar_disable(&rtc_inst);
	rtc_calendar_disable_callback(&rtc_inst, RTC_CALENDAR_CALLBACK_ALARM_0);
	status = rtc_calendar_unregister_callback(
			&rtc_inst, RTC_CALENDAR_CALLBACK_ALARM_0);
	test_assert_true(test, status == STATUS_OK,
			"RTC unregister callback failed");

}
/**
 * \brief Run RTC unit tests
 *
 * Initializes the system and serial output, then sets up the
 * RTC unit test suite and runs it.
 */
int main(void)
{
	system_init();
	delay_init();
	cdc_uart_init();

	/* Define Test Cases */
	DEFINE_TEST_CASE(rtc_calendar_test,
			NULL,
			run_rtc_calendar_test,
			NULL,
			"Testing RTC calendar");
	DEFINE_TEST_CASE(rtc_calendar_interrupt_test,
			NULL,
			run_rtc_calendar_interrupt_test,
			NULL,
			"Testing RTC calendar interrupt");


	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(rtc_tests) = {
		&rtc_calendar_test,
		&rtc_calendar_interrupt_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(rtc_test_suite, rtc_tests,
			"SAM0 RTC calendar driver test suite");

	/* Run all tests in the suite*/
	test_suite_run(&rtc_test_suite);

	while (true) {
		/* Intentionally left empty */
	}
}
