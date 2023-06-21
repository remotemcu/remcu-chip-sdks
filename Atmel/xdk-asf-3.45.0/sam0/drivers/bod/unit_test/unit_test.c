/**
 * \file
 *
 * \brief SAM BOD Callback Quick Start
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
 * \mainpage SAM0 BOD Unit Test
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This unit test carries out tests for the BOD driver.
 * It consists of test cases for the following functionalities:
 *      - Test for BOD initialization.
 *      - Test for BOD detected.
 */

/**
 * \page appdoc_main SAM0 BOD Unit Test
 *
 * Overview:
 * - \ref asfdoc_sam0_bod_unit_test_intro
 * - \ref asfdoc_sam0_bod_unit_test_setup
 * - \ref asfdoc_sam0_bod_unit_test_usage
 * - \ref asfdoc_sam0_bod_unit_test_compinfo
 * - \ref asfdoc_sam0_bod_unit_test_contactinfo
 *
 * \section asfdoc_sam0_bod_unit_test_intro Introduction
 * \copydetails appdoc_preface
 *
 * The following kit is required for carrying out the test:
 *  - SAM D21 Xplained Pro board
 *
 * \section asfdoc_sam0_bod_unit_test_setup Setup
 * The following operation has to be made:
 *  - \b adjust the power supply to lower than 3v.
 *
 * To run the test:
 *  - Connect the supported Xplained Pro board to the computer using a
 *    micro USB cable.
 *  - Open the virtual COM port in a terminal application.
 *    \note The USB composite firmware running on the Embedded Debugger (EDBG)
 *          will enumerate as debugger, virtual COM port and EDBG data
 *          gateway.
 *  - Build the project, program the target and run the application.
 *  - Conect board to external power supply though "PWR 5.0 IN and GND",
 *    this power have higher priority than usb power supply,
 *    you can check the cpu voltage from VCC.
 *
 *    The terminal shows the results of the unit test.
 *
 * \section asfdoc_sam0_bod_unit_test_usage Usage
 *  - Init bod and then test bod detected.
 *
 * \section asfdoc_sam0_bod_unit_test_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section asfdoc_sam0_bod_unit_test_contactinfo Contact Information
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
 * \brief Initialize the bod for unit test
 *
 * Initializes the BOD module used for detected test.
 */
static void run_bod_init_test(const struct test_case *test)
{
	enum status_code status;
	/* Structures for BOD configuration */
	struct bod_config config_bod;

	bod_get_config_defaults(&config_bod);
	/* if action set to  BOD_ACTION_NONE, STATUS register won't be set */
	config_bod.action = BOD_ACTION_INTERRUPT;
	/* level is 48, bod will detected when cpu voltage is lower than 3v */
	config_bod.level = 48;
	status = bod_set_config(BOD_BOD33, &config_bod);
	test_assert_true(test, status == STATUS_OK,
			"BOD init failed");
	status = bod_enable(BOD_BOD33);
	test_assert_true(test, status == STATUS_OK,
			"BOD enable failed");
			
}

/**
 * \internal
 * \brief Test for bod detected in polled mode.
 *
 * adjust the cpu power supply to lower than 3v, 
 * bod should be detected.
 *
 * \param test Current test case.
 */
static void run_bod_test(const struct test_case *test)
{
	bool bod_status;
	enum status_code status;

	/* adjust the cpu voltage to lower than 3V*/
	bod_status = bod_is_detected(BOD_BOD33);
	/* level is 48, bod detected should happen*/
	test_assert_true(test, bod_status == true,
			"bod detect failed");

	bod_clear_detected(BOD_BOD33);
	status = bod_disable(BOD_BOD33);
	test_assert_true(test, status == STATUS_OK,
			"BOD disable failed");
}

/**
 * \brief Run BOD unit tests
 *
 * Initializes the system and serial output, then sets up the
 * BOD unit test suite and runs it.
 */
int main(void)
{

	system_init();
	cdc_uart_init();

	DEFINE_TEST_CASE(bod_init_test,NULL,
			run_bod_init_test,NULL,
			"bod init test");
	DEFINE_TEST_CASE(bod_test,NULL,
			run_bod_test,NULL,
			"bod detect test");


	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(bod_tests) = {
		&bod_init_test,
		&bod_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(bod_test_suite, bod_tests,
			"SAM0 BOD driver test suite");

	/* Run all tests in the suite*/
	test_suite_run(&bod_test_suite);

	while (true) {
		/* Intentionally left empty */
	}
}

