/**
 * \file
 *
 * \brief SAM Watchdog Unit test
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
 * \mainpage SAM WDT Unit Test
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This unit test carries out tests for WDT driver.
 * It consists of test cases for the following functionalities:
 *  - Test for driver initialization.
 *  - Test for early warning callbacks.
 *  - Test for system reset upon timeout.
 */

/**
 * \page appdoc_main SAM WDT Unit Test
 *
 * Overview:
 * - \ref appdoc_sam0_wdt_unit_test_intro
 * - \ref appdoc_sam0_wdt_unit_test_setup
 * - \ref appdoc_sam0_wdt_unit_test_usage
 * - \ref appdoc_sam0_wdt_unit_test_compinfo
 * - \ref appdoc_sam0_wdt_unit_test_contactinfo
 *
 * \section appdoc_sam0_wdt_unit_test_intro Introduction
 * \copydetails appdoc_preface
 *
 * The following kit is required for carrying out the test:
 *  - SAM D20 Xplained Pro board
 *  - SAM D21 Xplained Pro board
 *  - SAM R21 Xplained Pro board
 *  - SAM L21 Xplained Pro board
 *  - SAM L22 Xplained Pro board
 *  - SAM DA1 Xplained Pro board
 *  - SAM C21 Xplained Pro board
 *  - SAM R30 Xplained Pro board
 *  - SAM R34 Xplained Pro board
 *
 * \section appdoc_sam0_wdt_unit_test_setup Setup
 * The following connections has to be made using wires:
 *  - None
 *
 * To run the test:
 *  - Connect the SAM Xplained Pro board to the computer using a
 *    micro USB cable.
 *  - Open the virtual COM port in a terminal application.
 *    \note The USB composite firmware running on the Embedded Debugger (EDBG)
 *          will enumerate as debugger, virtual COM port and EDBG data
 *          gateway.
 *  - Build the project, program the target and run the application.
 *    The terminal shows the results of the unit test.
 *
 * \section appdoc_sam0_wdt_unit_test_usage Usage
 *  - The unit tests are carried out using the internal Watchdog.
 *
 * \section appdoc_sam0_wdt_unit_test_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_wdt_unit_test_contactinfo Contact Information
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

/* Flag that indicates whether Watchdog was Reset cause */
static volatile bool wdr_flag = false;

/**
 * \brief Test Early Warning of Watchdog module
 *
 * If last reset cause was not Watchdog, following the Watchdog initialization
 * and enabling in the previous test, this function will wait for
 * CONF_WDT_EARLY_WARNING_WAIT_MS and will check if early warning flag is set.
 * Consequently, clear the early warning flag.
 *
 * \param test Current test case.
 */
static void run_wdt_early_warning_test(const struct test_case *test)
{
	/* Check if last reset was by Watchdog module */
	if (wdr_flag == false) {
		/* Wait for Early Warning flag to be set */
		delay_ms(CONF_WDT_EARLY_WARNING_WAIT_MS);

		/* Check if the Early Warning flag is set */
		test_assert_true(test, wdt_is_early_warning() == true,
				"Early Warning failed \n");

		/* Clear the Early Warning flag */
		wdt_clear_early_warning();
	}
}

/**
 * \brief Wait for Watchdog module to reset
 *
 *  Wait for CONF_WDT_RESET_WAIT_MS for Watchdog to reset the device
 *
 * \param test Current test case.
 */
static void wait_for_wdt_reset(const struct test_case *test)
{
	/* Check if last reset was by Watchdog module */
	if (wdr_flag == false) {
		/* Wait for Watchdog module to reset the device */
		delay_ms(CONF_WDT_RESET_WAIT_MS);
	}
}

/**
 * \brief Test whether last reset was by Watchdog module
 *
 * This function tests whether the last reset was caused by timeout
 * of Watchdog module
 *
 * \param test Current test case.
 */
static void run_reset_cause_test(const struct test_case *test)
{
	test_assert_true(test, wdr_flag == true,
			"Watchdog reset failed: %x", wdr_flag);
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
 * \brief Run WDT unit tests
 *
 * Initializes the system and serial output, then sets up the
 * WDT unit test suite and runs it.
 */
int main(void)
{
	/* Check whether reset cause was Watchdog */
#if (SAML21) || (SAMC21) || (SAML22) || (SAMR30) || (SAMR34)
	wdr_flag = (system_get_reset_cause() & RSTC_RCAUSE_WDT);
#else
	wdr_flag = (system_get_reset_cause() & PM_RCAUSE_WDT);
#endif
	system_init();

	/* Reset the Watchdog count */
	wdt_reset_count();

	struct wdt_conf config_wdt;
	/* Get the Watchdog default configuration */
	wdt_get_config_defaults(&config_wdt);
	if(wdr_flag) {
		config_wdt.enable = false;
	}
	/* Set the desired configuration */
#if !((SAML21) || (SAMC21) || (SAML22) || (SAMR30) || (SAMR34)) 
	config_wdt.clock_source         = CONF_WDT_GCLK_GEN;
#endif
	config_wdt.timeout_period       = CONF_WDT_TIMEOUT_PERIOD;
	config_wdt.early_warning_period = CONF_WDT_EARLY_WARNING_PERIOD;
	wdt_set_config(&config_wdt);

	cdc_uart_init();

	DEFINE_TEST_CASE(wdt_early_warning_test, NULL,
			run_wdt_early_warning_test, wait_for_wdt_reset,
			"WDT Early Warning Test");

	DEFINE_TEST_CASE(reset_cause_test, NULL,
			run_reset_cause_test, NULL,
			"Confirming Watchdog Reset");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(wdt_tests) = {
			&wdt_early_warning_test,
			&reset_cause_test,
			};

	/* Define the test suite */
	DEFINE_TEST_SUITE(wdt_suite, wdt_tests,
			"SAM WDT driver test suite");

	/* Run all tests in the suite*/
	test_suite_run(&wdt_suite);

	while (1) {
		/* Intentionally left empty */
	}

}
