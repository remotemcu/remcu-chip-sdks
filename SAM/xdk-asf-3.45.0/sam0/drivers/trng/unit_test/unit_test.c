/**
 * \file
 *
 * \brief SAM True Random Number Generator (TRNG) Unit test
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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
 * \mainpage SAM TRNG Unit Test
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This unit test carries out tests for the TRNG driver.
 * It consists of test cases for the following functionalities:
 *      - Test for TRNG polling mode read.
 *      - Test for TRNG callback mode read.
 */

/**
 * \page appdoc_main SAM TRNG Unit Test
 *
 * Overview:
 * - \ref appdoc_sam0_trng_unit_test_intro
 * - \ref appdoc_sam0_trng_unit_test_setup
 * - \ref appdoc_sam0_trng_unit_test_usage
 * - \ref appdoc_sam0_trng_unit_test_compinfo
 * - \ref appdoc_sam0_trng_unit_test_contactinfo
 *
 * \section appdoc_sam0_trng_unit_test_intro Introduction
 * \copydetails appdoc_preface
 *
 * The following kit is required for carrying out the test:
 *  - SAM L21 Xplained Pro board
 *  - SAM L22 Xplained Pro board
 *
 * \section appdoc_sam0_trng_unit_test_setup Setup
 * There is no special requirement.
 *
 * To run the test:
 *  - Connect the SAM Xplained Pro board to the computer using a
 *    micro USB cable.
 *  - Open the virtual COM port in a terminal application.
 *    \note The USB composite firmware running on the Embedded Debugger (EDBG)
 *          will enumerate as debugger, virtual COM port, and EDBG data
 *          gateway.
 *  - Build the project, program the target and run the application.
 *    The terminal shows the results of the unit test.
 *
 * \section appdoc_sam0_trng_unit_test_usage Usage
 *  - Polling mode read is tested.
 *  - Callback mode read is tested.
 *
 * \section appdoc_sam0_trng_unit_test_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_trng_unit_test_contactinfo Contact Information
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
/* Structure for TRNG module */
struct trng_module trng_instance;

/* Interrupt flag used during callback test */
volatile bool interrupt_flag = false;

/**
 * \internal
 * \brief TRNG callback function
 *
 * Called by TRNG driver on interrupt detection.
 *
 * \param module Pointer to the TRNG module (not used)
 */
static void trng_complete_callback(struct trng_module *const module_inst)
{
	UNUSED(module_inst);
	interrupt_flag = true;
}

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
 * \internal
 * \brief Test for TRNG polling mode read.
 *
 * This test reads three random data in polling mode and check the result.
 *
 * \param test Current test case
 */
static void run_trng_polling_read_test(const struct test_case *test)
{
	uint32_t i;
	uint32_t timeout;
	uint32_t random_result[3];

	/* Structure for TRNG configuration */
	struct trng_config config;

	/* Initialize and enable the TRNG */
	trng_get_config_defaults(&config);
	trng_init(&trng_instance, TRNG, &config);
	trng_enable(&trng_instance);


	/* Read random data */
	for (i = 0; i < 3; i++) {
		/* A new 32-bits random data will be generated for every
		 * 84 CLK_TRNG_APB clock cycles. */
		timeout = 84;
		if (trng_read(&trng_instance, &random_result[i]) != STATUS_OK) {
			timeout--;
			if (timeout == 0) {
				/* Skip test if fail to read random data */
				test_assert_true(test, false,
						"Fail to read random data in polling mode.");
			}
		}
	}

	/* Assume there is no probability to read same three
	 * consecutive random number */
	if ((random_result[0] == random_result[1]) &&
			(random_result[0] == random_result[2])) {
		test_assert_true(test, false,
				"Get same random data in polling mode.");
	}
}

/**
 * \internal
 * \brief TRNG callback mode test function
 *
 * This test reads three random data in callback mode and check the result.
 *
 * \param test Current test case.
 */
static void run_trng_callback_read_test(const struct test_case *test)
{
	uint32_t timeout = 84 * 3;
	uint32_t random_result[3];

	/* Register and enable TRNG read callback */
	trng_register_callback(&trng_instance, trng_complete_callback,
			TRNG_CALLBACK_READ_BUFFER);
	trng_enable_callback(&trng_instance, TRNG_CALLBACK_READ_BUFFER);

	/* Start TRNG read job */
	trng_read_buffer_job(&trng_instance, random_result, 3);
	do {
		timeout--;
		if (interrupt_flag) {
			break;
		}
	} while (timeout > 0);
	test_assert_true(test, timeout,
			"Fail to read random data in callback mode.");

	/* Assume there is no probability to read same three
	 * consecutive random number */
	if ((random_result[0] == random_result[1]) &&
			(random_result[0] == random_result[2])) {
		test_assert_true(test, false,
				"Get same random data in polling mode.");
	}

	/* Test done, disable read callback and TRNG instance */
	trng_disable_callback(&trng_instance, TRNG_CALLBACK_READ_BUFFER);
	trng_disable(&trng_instance);
}

/**
 * \brief Run TRNG unit tests
 *
 * Initializes the system and serial output, then sets up the
 * TRNG unit test suite and runs it.
 */
int main(void)
{
	system_init();
	cdc_uart_init();

	/* Define Test Cases */
	DEFINE_TEST_CASE(trng_polling_read_test,
			NULL,
			run_trng_polling_read_test,
			NULL,
			"Testing TRNG polling read");

	DEFINE_TEST_CASE(trng_callback_read_test,
			NULL,
			run_trng_callback_read_test,
			NULL,
			"Testing TRNG callback read");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(trng_tests) = {
		&trng_polling_read_test,
		&trng_callback_read_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(trng_test_suite, trng_tests,
			"SAM TRNG driver test suite");

	/* Run all tests in the suite*/
	test_suite_run(&trng_test_suite);

	while (true) {
		/* Intentionally left empty */
	}
}
