/**
 * \file
 *
 * \brief SAM Event System Unit test
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
 * \mainpage SAM EVENTS Unit Test
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This unit test carries out tests for the EVENTS driver.
 * It consists of test cases for the following functionalities:
 *      - Test for synchronous event propagation.
 *      - Test for resynchronized event propagation.
 *      - Test for asynchronous event propagation.
 */

/**
 * \page appdoc_main SAM EVENTS Unit Test
 *
 * Overview:
 * - \ref appdoc_sam0_events_unit_test_intro
 * - \ref appdoc_sam0_events_unit_test_setup
 * - \ref appdoc_sam0_events_unit_test_usage
 * - \ref appdoc_sam0_events_unit_test_compinfo
 * - \ref appdoc_sam0_events_unit_test_contactinfo
 *
 * \section appdoc_sam0_events_unit_test_intro Introduction
 * \copydetails appdoc_preface
 *
 * This unit test carries out test for three modes of event propagation:
 * Synchronous, Resynchronized & Asynchronous.
 *  - A RTC module with internal 32kHz RC oscillator is configured as
 *    an event generator and a Timer Counter (TC3) module is configured as event
 *    user.
 *  - RTC overflow signal is sent as an event to the timer. The timer will
 *    start counting on receiving this event.
 *  - The timer's count register is read to detect successful event action.
 *
 * The following kits are supported for carrying out the test:
 *      - SAM D20 Xplained Pro board
 *      - SAM D21 Xplained Pro board
 *      - SAM R21 Xplained Pro board
 *      - SAM L21 Xplained Pro board
 *      - SAM L22 Xplained Pro board
 *      - SAM DA1 Xplained Pro board
 *      - SAM C21 Xplained Pro board
 *      - SAM HA1G16A Xplained Pro board
 *      - SAM R30 Xplained Pro board
 *      - SAM R30 Module Xplained Pro board
 *      - SAM R34 Xplained Pro board
 *
 * \section appdoc_sam0_events_unit_test_setup Setup
 * The following connections has to be made using wires:
 *  - \b None
 *
 * To run the test:
 *  - Connect the Xplained Pro board to the computer using a
 *    micro USB cable.
 *  - Open the virtual COM port in a terminal application.
 *    \note The USB composite firmware running on the Embedded Debugger (EDBG)
 *          will enumerate as debugger, virtual COM port and EDBG data
 *          gateway.
 *  - Build the project, program the target and run the application.
 *    The terminal shows the results of the unit test.
 *
 * \section appdoc_sam0_events_unit_test_usage Usage
 *  - The unit test carries out test for three modes of event propagation:
 *    Synchronous, Resynchronized & Asynchronous.
 *  - RTC module with internal 32kHz RC oscillator is configured as
 *    event generator and Timer (TC3) module is configured as event user.
 *  - RTC overflow signal is sent as an event to the timer. The timer will
 *    start counting on receiving this event.
 *  - Timer's count register is read to detect successful event action.
 *
 * \section appdoc_sam0_events_unit_test_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_events_unit_test_contactinfo Contact Information
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

/* Event user being TC3 or TC1 */
#if SAMR30 || SAMR34 || SAMR35 
#define TEST_EVENT_USER   EVSYS_ID_USER_TC1_EVU
#else
#define TEST_EVENT_USER   EVSYS_ID_USER_TC3_EVU
#endif
/* Event generator being RTC overflow */
#define TEST_EVENT_GEN    EVSYS_ID_GEN_RTC_OVF

/* Structure for UART module connected to EDBG (used for unit test output) */
struct usart_module cdc_uart_module;

/* Structure for TC module */
struct tc_module  tc_inst;

/* Structure for RTC module */
struct rtc_module rtc_inst;

/* Flag to check successful initialization */
volatile bool init_success;

/* The event channel handle */
struct events_resource events;

/**
 * \brief Initialize the USART for unit test
 *
 * Initializes the SERCOM USART used for sending the unit test status to the
 * computer via the EDBG CDC gateway.
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
 * \brief Initialize the (TC3 | TC1) & RTC for unit test
 *
 * Initializes the RTC module and (TC3 | TC1) module which are used as
 * event generator and event user respectively.
 */
static void test_event_gen_user_init(void)
{
	enum status_code status;
	init_success = true;

	/* Timer configuration (Event User) */
	struct tc_config config_tc;

	tc_get_config_defaults(&config_tc);
	config_tc.counter_16_bit.compare_capture_channel[0]
		= (0xFFFF / 4);

	/* Initialize the TC3 or TC1 */
#if SAMR30 || SAMR34 || SAMR35
	status = tc_init(&tc_inst, TC1, &config_tc);
#else
	status = tc_init(&tc_inst, TC3, &config_tc);
#endif
	if (status != STATUS_OK) {
		init_success = false;
	}

	struct tc_events events_tc;

	events_tc.on_event_perform_action = true;
	events_tc.event_action = TC_EVENT_ACTION_START;

	tc_enable_events(&tc_inst, &events_tc);

	/* Enable the TC3 or TC1 */
	tc_enable(&tc_inst);

	/* RTC configuration (Event Generator) */
	struct rtc_count_config config_rtc_count;
	struct rtc_count_events config_rtc_event
		= { .generate_event_on_overflow = true };

	/* Initialize the RTC module */
	rtc_count_get_config_defaults(&config_rtc_count);
	config_rtc_count.prescaler           = RTC_COUNT_PRESCALER_DIV_1;
	config_rtc_count.mode                = RTC_COUNT_MODE_16BIT;
#ifdef FEATURE_RTC_CONTINUOUSLY_UPDATED
	config_rtc_count.continuously_update = true;
#endif
	config_rtc_count.compare_values[0]   = 50;
	status = rtc_count_init(&rtc_inst, RTC, &config_rtc_count);

	if (status != STATUS_OK) {
		init_success = false;
	}

	/* Enable RTC events */
	config_rtc_event.generate_event_on_overflow = true;
	rtc_count_enable_events(&rtc_inst, &config_rtc_event);
}

/**
 * \internal
 * \brief Setup Function: Synchronous event propagation.
 *
 * This function initializes the event system channel 0 and the RTC
 * module (event generator) to be in the same clock domain for
 * synchronous event propagation.
 *
 * \param test Current test case.
 */
static void setup_synchronous_event_test(const struct test_case *test)
{
	struct events_config   events_conf;

	/* Get default event channel configuration */
	events_get_config_defaults(&events_conf);

	events_conf.clock_source   = GCLK_GENERATOR_2;
	events_conf.edge_detect    = EVENTS_EDGE_DETECT_RISING;
	events_conf.path           = EVENTS_PATH_SYNCHRONOUS;
	events_conf.generator      = TEST_EVENT_GEN;

	events_allocate(&events, &events_conf);
	events_attach_user(&events, TEST_EVENT_USER);
}

/**
 * \internal
 * \brief Test for event system in synchronous mode.
 *
 * This test waits for event channel and user to be ready and then
 * starts the RTC to generate overflow event. It waits until the timer
 * is started. If the timer starts running then it can be assumed that
 * the event has been propagated properly.
 *
 * \param test Current test case.
 */
static void run_synchronous_event_test(const struct test_case *test)
{
	uint32_t timeout_cycles = 1000;

	/* Skip test if initialization failed */
	test_assert_true(test, init_success,
			"Skipping test due to failed initialization");

	/* Check whether event user is ready */
	do {

		timeout_cycles--;
		if (events_is_users_ready(&events)) {
			break;
		}

	} while (timeout_cycles > 0);

	test_assert_true(test, timeout_cycles > 0,
			"Timeout error: Event user not ready");

	/* Check whether event channel is ready */
	timeout_cycles = 1000;
	do {

		timeout_cycles--;
		if (!events_is_busy(&events)) {
			break;
		}

	} while (timeout_cycles > 0);

	test_assert_true(test, timeout_cycles > 0,
			"Timeout error: Event channel not ready");

	/* Event action test */
	rtc_count_enable(&rtc_inst);
	rtc_count_set_period(&rtc_inst, 100);
	timeout_cycles = 10000;

	do {

		timeout_cycles--;
		if (tc_get_count_value(&tc_inst)) {
			break;
		}

	} while (timeout_cycles > 0);

	test_assert_true(test, timeout_cycles > 0,
			"Error: Timeout in event reception/action");
}

/**
 * \internal
 * \brief Cleanup Function: Synchronous event propagation.
 *
 * This function disables the RTC, clears the RTC COUNT register and
 * stops the timer (TC3 | TC1).
 *
 * \param test Current test case.
 */
static void cleanup_synchronous_event_test(const struct test_case *test)
{
	rtc_count_disable(&rtc_inst);
	rtc_count_set_count(&rtc_inst, 0);
	tc_stop_counter(&tc_inst);
	events_release(&events);
}

/**
 * \internal
 * \brief Setup Function: Resynchronized event propagation.
 *
 * This function initializes the event system channel 0 and the RTC
 * module (event generator) to be in the different clock domain for
 * resynchronized event propagation.
 *
 * \param test Current test case.
 */
static void setup_resynchronous_event_test(const struct test_case *test)
{

	struct events_config   events_conf;

	/* Get default event channel configuration */
	events_get_config_defaults(&events_conf);

	events_conf.clock_source   = GCLK_GENERATOR_0;
	events_conf.edge_detect    = EVENTS_EDGE_DETECT_RISING;
	events_conf.path           = EVENTS_PATH_RESYNCHRONIZED;
	events_conf.generator      = TEST_EVENT_GEN;

	events_allocate(&events, &events_conf);
	events_attach_user(&events, TEST_EVENT_USER);

}

/**
 * \internal
 * \brief Test for event system in resynchronous mode.
 *
 * This test waits for event channel and user to be ready and then
 * starts the RTC to generate overflow event. It waits until the timer
 * is started. If the timer starts running then it can be assumed that
 * the event has been propagated properly.
 *
 * \param test Current test case.
 */
static void run_resynchronous_event_test(const struct test_case *test)
{
	uint32_t timeout_cycles = 1000;

	/* Skip test if initialization failed */
	test_assert_true(test, init_success,
			"Skipping test due to failed initialization");

	/* Check whether event user is ready */
	do {
		timeout_cycles--;
		if (events_is_users_ready(&events)) {
			break;
		}
	} while (timeout_cycles > 0);

	test_assert_true(test, timeout_cycles > 0,
			"Timeout error: Event user not ready");

	/* Check whether event channel is ready */
	timeout_cycles = 1000;
	do {
		timeout_cycles--;
		if (!events_is_busy(&events)) {
			break;
		}
	} while (timeout_cycles > 0);

	test_assert_true(test, timeout_cycles > 0,
			"Timeout error: Event channel not ready");

	/* Event action test */
	rtc_count_enable(&rtc_inst);
	rtc_count_set_period(&rtc_inst, 100);
	timeout_cycles = 10000;

	do {
		timeout_cycles--;
		if (tc_get_count_value(&tc_inst)) {
			break;
		}
	} while (timeout_cycles > 0);

	test_assert_true(test, timeout_cycles > 0,
			"Error: Timeout in event reception/action");
}

/**
 * \internal
 * \brief Cleanup Function: Resynchronized event propagation.
 *
 * This function disables the RTC, clears the RTC COUNT register and
 * stops the timer (TC3 | TC1).
 *
 * \param test Current test case.
 */
static void cleanup_resynchronous_event_test(const struct test_case *test)
{
	rtc_count_disable(&rtc_inst);
	rtc_count_set_count(&rtc_inst, 0);
	tc_stop_counter(&tc_inst);
	events_release(&events);
}

/**
 * \internal
 * \brief Setup Function: Asynchronous event propagation.
 *
 * This function initializes the event system channel 0 and the RTC
 * module (event generator). The event channel clock will not be
 * enabled for asynchronous event propagation.
 *
 * \param test Current test case.
 */
static void setup_asynchronous_event_test(const struct test_case *test)
{

	struct events_config   events_conf;

	/* Get default event channel configuration */
	events_get_config_defaults(&events_conf);

	events_conf.path           = EVENTS_PATH_ASYNCHRONOUS;
	events_conf.generator      = TEST_EVENT_GEN;

	events_allocate(&events, &events_conf);
	events_attach_user(&events, TEST_EVENT_USER);

}

/**
 * \internal
 * \brief Test for event system in asynchronous mode.
 *
 * This test waits for event channel and user to be ready and then
 * starts the RTC to generate overflow event. It waits until the timer
 * is started. If the timer starts running then it can be assumed that
 * the event has been propagated properly.
 *
 * \param test Current test case.
 */
static void run_asynchronous_event_test(const struct test_case *test)
{
	uint32_t timeout_cycles;

	/* Skip test if initialization failed */
	test_assert_true(test, init_success,
			"Skipping test due to failed initialization");

	/* Event action test */
	rtc_count_enable(&rtc_inst);
	rtc_count_set_period(&rtc_inst, 100);
	timeout_cycles = 10000;

	do {

		timeout_cycles--;
		if (tc_get_count_value(&tc_inst)) {
			break;
		}

	} while (timeout_cycles > 0);

	test_assert_true(test, timeout_cycles > 0,
			"Error: Timeout in event reception/action");
}

/**
 * \internal
 * \brief Cleanup Function: Asynchronous event propagation.
 *
 * This function disables the RTC, clears the RTC COUNT register and
 * stops the timer (TC3 | TC1).
 *
 * \param test Current test case.
 */
static void cleanup_asynchronous_event_test(const struct test_case *test)
{
	rtc_count_disable(&rtc_inst);
	rtc_count_set_count(&rtc_inst, 0);
	tc_stop_counter(&tc_inst);
	events_release(&events);
}

/**
 * \brief Run Event System unit tests
 *
 * Initializes the system and serial output, then sets up the
 * Event system unit test suite and runs it.
 */
int main(void)
{
	system_init();
	cdc_uart_init();
	test_event_gen_user_init();

	/* Define Test Cases */
	DEFINE_TEST_CASE(synchronous_event_test,
			setup_synchronous_event_test,
			run_synchronous_event_test,
			cleanup_synchronous_event_test,
			"Testing Synchronous Event Propagation");

	DEFINE_TEST_CASE(resynchronous_event_test,
			setup_resynchronous_event_test,
			run_resynchronous_event_test,
			cleanup_resynchronous_event_test,
			"Testing Resynchronized Event Propagation");

	DEFINE_TEST_CASE(asynchronous_event_test,
			setup_asynchronous_event_test,
			run_asynchronous_event_test,
			cleanup_asynchronous_event_test,
			"Testing Asynchronous Event Propagation");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(events_tests) = {
		&synchronous_event_test,
		&resynchronous_event_test,
		&asynchronous_event_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(events_test_suite, events_tests,
			"SAM Event System driver test suite");

	/* Run all tests in the suite*/
	test_suite_run(&events_test_suite);

	while (true) {
		/* Intentionally left empty */
	}
}
