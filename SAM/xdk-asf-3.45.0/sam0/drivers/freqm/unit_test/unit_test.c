/**
 * \file
 *
 * \brief SAM Frequency Meter (FREQM) Unit test
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */


/**
 * \mainpage SAM FREQM Unit Test
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This unit test carries out tests for the FREQM driver.
 * It consists of test cases for the following functionalities:
 *      - Test for FREQM polling mode read.
 *      - Test for FREQM callback mode read.
 */

/**
 * \page appdoc_main SAM FREQM Unit Test
 *
 * Overview:
 * - \ref appdoc_sam0_freqm_unit_test_intro
 * - \ref appdoc_sam0_freqm_unit_test_setup
 * - \ref appdoc_sam0_freqm_unit_test_usage
 * - \ref appdoc_sam0_freqm_unit_test_compinfo
 * - \ref appdoc_sam0_freqm_unit_test_contactinfo
 *
 * \section appdoc_sam0_freqm_unit_test_intro Introduction
 * \copydetails appdoc_preface
 *
 * The following kit is required for carrying out the test:
 *  - SAM L22 Xplained Pro board
 *
 * \section appdoc_sam0_freqm_unit_test_setup Setup
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
 * \section appdoc_sam0_freqm_unit_test_usage Usage
 *  - Polling mode read is tested.
 *  - Callback mode read is tested.
 *
 * \section appdoc_sam0_freqm_unit_test_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_freqm_unit_test_contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com">http://www.microchip.com</a>.
 */

#include <asf.h>
#include <stdio_serial.h>
#include <string.h>
#include "conf_test.h"

/* Theoretical frequency value of clock source */
#define FREQM_CLK_FREQ_VAL     4000000
/* Offset due to FREQM errors */
#define FREQM_OFFSET           200000

/* Structure for UART module connected to EDBG (used for unit test output) */
struct usart_module cdc_uart_module;
/* Structure for FREQM module */
struct freqm_module freqm_instance;

/* Interrupt flag used during callback test */
volatile bool interrupt_flag = false;

/**
 * \internal
 * \brief FREQM callback function
 *
 * Called by FREQM driver on interrupt detection.
 *
 * \param module Pointer to the FREQM module (not used)
 */
static void freqm_complete_callback(void)
{
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
 * \brief Test for FREQM polling mode read.
 *
 * This test reads three measure data in polling mode and check the result.
 *
 * \param test Current test case
 */
static void run_freqm_polling_read_test(const struct test_case *test)
{
	uint32_t measure_result;
	enum freqm_status measure_status;

	/* Structure for FREQM configuration */
	struct freqm_config config;

	/* Initialize and enable the FREQM */
	freqm_get_config_defaults(&config);
	freqm_init(&freqm_instance, FREQM, &config);
	freqm_enable(&freqm_instance);

	/* Read measure data */
	freqm_start_measure(&freqm_instance);
	while ((measure_status = freqm_get_result_value(&freqm_instance, &measure_result))
			== FREQM_STATUS_MEASURE_BUSY) {
	}
	/* Test result */
	test_assert_true(test, measure_status != FREQM_STATUS_CNT_OVERFLOW, 
			"Overflow condition occus in polling mode!");

	test_assert_true(test,
			(measure_result > (FREQM_CLK_FREQ_VAL - FREQM_OFFSET)) &&
			(measure_result < (FREQM_CLK_FREQ_VAL + FREQM_OFFSET)),
			"Error measure data in polling mode. ");

}

/**
 * \internal
 * \brief FREQM callback mode test function
 *
 * This test reads three measure data in callback mode and check the result.
 *
 * \param test Current test case.
 */
static void run_freqm_callback_read_test(const struct test_case *test)
{
	uint32_t measure_result;
	enum freqm_status measure_status;

	/* Register and enable FREQM read callback */
	freqm_register_callback(&freqm_instance, freqm_complete_callback,
			FREQM_CALLBACK_MEASURE_DONE);
	freqm_enable_callback(&freqm_instance, FREQM_CALLBACK_MEASURE_DONE);

	/* Start FREQM read job */
	freqm_start_measure(&freqm_instance);
	while(!interrupt_flag) {
	}
	measure_status = freqm_get_result_value(&freqm_instance, &measure_result);

	/* Test result */
	test_assert_true(test, measure_status != FREQM_STATUS_CNT_OVERFLOW, 
			"Overflow condition occus in callback mode!");

	test_assert_true(test,
			(measure_result > (FREQM_CLK_FREQ_VAL - FREQM_OFFSET)) &&
			(measure_result < (FREQM_CLK_FREQ_VAL + FREQM_OFFSET)),
			"Error measure data in callback mode. ");

	/* Test done, disable read callback and FREQM instance */
	freqm_disable_callback(&freqm_instance, FREQM_CALLBACK_MEASURE_DONE);
	freqm_disable(&freqm_instance);
}

/**
 * \brief Run FREQM unit tests
 *
 * Initializes the system and serial output, then sets up the
 * FREQM unit test suite and runs it.
 */
int main(void)
{
	system_init();
	cdc_uart_init();

	/* Define Test Cases */
	DEFINE_TEST_CASE(freqm_polling_read_test,
			NULL,
			run_freqm_polling_read_test,
			NULL,
			"Testing FREQM polling read");

	DEFINE_TEST_CASE(freqm_callback_read_test,
			NULL,
			run_freqm_callback_read_test,
			NULL,
			"Testing FREQM callback read");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(freqm_tests) = {
		&freqm_polling_read_test,
		&freqm_callback_read_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(freqm_test_suite, freqm_tests,
			"SAM FREQM driver test suite");

	/* Run all tests in the suite*/
	test_suite_run(&freqm_test_suite);

	while (true) {
		/* Intentionally left empty */
	}
}
