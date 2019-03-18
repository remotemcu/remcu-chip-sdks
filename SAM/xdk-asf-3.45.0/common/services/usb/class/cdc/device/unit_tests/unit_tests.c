/**
 * \file
 *
 * \brief Main functions for CDC unit test
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <stdio.h>
#include <asf.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <conf_test.h>

/**
 * \mainpage ASF USB Device CDC
 *
 * \section intro Introduction
 * This example implements a USB Device CDC enumeration
 * but the CDC events to move and click are not linked.
 * It is to validated the CDC enumeration
 * and USB core callback (VBus presence, resume, suspend and SOF).
 * This example uses the CDC driver for these operating systems.
 *
 */

//! \name Unit test configuration
//@{
/**
 * \def CONF_TEST_USART
 * \brief USART to redirect STDIO to
 */
/**
 * \def CONF_TEST_BAUDRATE
 * \brief Baudrate of USART
 */
/**
 * \def CONF_TEST_CHARLENGTH
 * \brief Character length (bits) of USART
 */
/**
 * \def CONF_TEST_PARITY
 * \brief Parity mode of USART
 */
/**
 * \def CONF_TEST_STOPBITS
 * \brief Stopbit configuration of USART
 */
//@}

static bool main_b_vbus_event = false;
static bool main_b_resume_event = false;
static bool main_b_suspend_event = false;
static bool main_b_sof_event = false;
static bool main_b_cdc_configurated = false;
static bool main_b_cdc_enumerated = false;
#if SAM0
/* Structure for UART module connected to EDBG (used for unit test output) */
static struct usart_module cdc_uart_module;
#endif

static void run_usb_cdc_test(const struct test_case *test)
{
	UNUSED(test);
	// Start USB stack to authorize VBus monitoring
	udc_start();

	if (!udc_include_vbus_monitoring()) {
		// VBUS monitoring is not available on this product
		// thereby VBUS has to be considered as present
		main_vbus_action(true);
	}

	// The main loop manages only the power mode
	// because the USB management is done by interrupt
	while (!main_b_cdc_configurated) {
		sleepmgr_enter_sleep();
		// No test_assert_true() call
		// because it must be a timeout from server
	}
	while (!main_b_cdc_enumerated);

	udc_stop();
}

static void run_usb_cdc_config_test(const struct test_case *test)
{
	test_assert_true(test, main_b_cdc_configurated, "CDC configuration not received");
}

static void run_usb_vbus_test(const struct test_case *test)
{
	test_assert_true(test, main_b_vbus_event, "Event vbus not received");
}

static void run_usb_resume_test(const struct test_case *test)
{
	test_assert_true(test, main_b_resume_event, "Event resume not received");
}

static void run_usb_suspend_test(const struct test_case *test)
{
	test_assert_true(test, main_b_suspend_event, "Event suspend not received");
}

static void run_usb_sof_test(const struct test_case *test)
{
	test_assert_true(test, main_b_sof_event, "Event sof not received");
}

/**
 * \brief Run usb device cdc unit tests
 *
 * Initializes the clock system, board and serial output, then sets up the
 * usb unit test suite and runs it.
 */
int main(void)
{
#if !SAM0
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits   = CONF_TEST_STOPBITS,
	};
#else
	struct usart_config usart_conf;
#endif

	irq_initialize_vectors();
	cpu_irq_enable();

#if !SAM0
	sysclk_init();
	board_init();
#else
	system_init();
#endif
	// Initialize the sleep manager
	sleepmgr_init();

#if !SAM0
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);
#else
	/* Configure USART for unit test output */
	usart_get_config_defaults(&usart_conf);
	usart_conf.mux_setting = CONF_STDIO_MUX_SETTING;
	usart_conf.pinmux_pad0 = CONF_STDIO_PINMUX_PAD0;
	usart_conf.pinmux_pad1 = CONF_STDIO_PINMUX_PAD1;
	usart_conf.pinmux_pad2 = CONF_STDIO_PINMUX_PAD2;
	usart_conf.pinmux_pad3 = CONF_STDIO_PINMUX_PAD3;
	usart_conf.baudrate    = CONF_STDIO_BAUDRATE;
	usart_conf.generator_source = GCLK_GENERATOR_3;

	stdio_serial_init(&cdc_uart_module, CONF_STDIO_USART, &usart_conf);
	usart_enable(&cdc_uart_module);
#endif

	// Define all the timestamp to date test cases
	DEFINE_TEST_CASE(usb_cdc_test, NULL,
			run_usb_cdc_test, NULL,
			"USB Device cdc enumeration test");
	DEFINE_TEST_CASE(usb_cdc_config_test, NULL,
			run_usb_cdc_config_test, NULL,
			"USB CDC configuration test");
	DEFINE_TEST_CASE(usb_vbus_test, NULL,
			run_usb_vbus_test, NULL,
			"USB vbus event test");
	DEFINE_TEST_CASE(usb_resume_test, NULL,
			run_usb_resume_test, NULL,
			"USB resume event test");
	DEFINE_TEST_CASE(usb_suspend_test, NULL,
			run_usb_suspend_test, NULL,
			"USB suspend event test");
	DEFINE_TEST_CASE(usb_sof_test, NULL,
			run_usb_sof_test, NULL,
			"USB sof event test");

	// Put test case addresses in an array
	DEFINE_TEST_ARRAY(usb_cdc_tests) = {
		&usb_cdc_test,
		&usb_cdc_config_test,
		&usb_vbus_test,
		&usb_resume_test,
		&usb_suspend_test,
		&usb_sof_test,
	};

	// Define the test suite
	DEFINE_TEST_SUITE(usb_cdc_suite, usb_cdc_tests,
			"Common usb CDC service with test suite");

	// The unit test prints message via UART which does not support deep sleep mode.
#if SAM
	sleepmgr_lock_mode(SLEEPMGR_ACTIVE);
#else
	sleepmgr_lock_mode(SLEEPMGR_IDLE);
#endif

	// Run all tests in the suite
	test_suite_run(&usb_cdc_suite);

	while (1) {
		// Intentionally left empty.
	}
}

void main_vbus_action(bool b_high)
{
	if (b_high) {
		main_b_vbus_event = true;
	}
}

void main_suspend_action(void)
{
	main_b_resume_event = true;
}

void main_resume_action(void)
{
	main_b_suspend_event = true;
}

void main_sof_action(void)
{
	main_b_sof_event = true;
}

void main_remotewakeup_enable(void)
{
}

void main_remotewakeup_disable(void)
{
}

bool main_cdc_enable(void)
{
	main_b_cdc_enumerated = true;
	return true;
}

void main_cdc_disable(void)
{
	main_b_cdc_enumerated = false;
}

void main_cdc_config(void)
{
	main_b_cdc_configurated = true;
}


