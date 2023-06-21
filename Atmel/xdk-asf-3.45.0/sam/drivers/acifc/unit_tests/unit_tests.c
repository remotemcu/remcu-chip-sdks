/**
 * \file
 *
 * \brief Unit tests for ACIFC driver.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <board.h>
#include <sysclk.h>
#include "acifc.h"
#include "delay.h"
#include <string.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <conf_test.h>
#include <conf_board.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the ACIFC driver.
 * It consists of test cases for the following functionality:
 * - Configure ACIFC channel to generate interrupt
 *
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 *
 * \section device_info Device Info
 * The SAM4L devices can be used.
 * This example has been tested with the following setup:
 * - sam4lc4c_sam4l_ek
 * - sam4lc4c_sam4l_xplained_pro
 * - sam4lc8c_sam4l8_xplained_pro
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for ARM. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */

//! \name Unit test configuration
//@{
/**
 * \def CONF_TEST_ACIFC
 * \brief Test the functions provided by the ACIFC driver.
 */
//@}

/** Analog comparator channel number */
#define EXAMPLE_AC_CHANNEL         0

volatile bool intflag = false;

struct ac_dev_inst ac_device;

/**
 * \brief Callback for AC interrupt.
 */
static void set_int_flag(void)
{
	ac_clear_interrupt_status(&ac_device, ACIFC_ICR_ACINT0);
	intflag = true;
}

/**
 * \brief Test AC
 *
 * \param test Current test case.
 */
static void run_ac_test(const struct test_case *test)
{
	/* AC instance configuration */
	struct ac_config module_cfg;
	ac_get_config_defaults(&module_cfg);
	module_cfg.event_trigger = true;
	ac_init(&ac_device, ACIFC, &module_cfg);

	ac_enable(&ac_device);

	/* AC channel configuration */
	struct ac_ch_config ch_cfg;
	ac_ch_get_config_defaults(&ch_cfg);
	ch_cfg.always_on = true;
	ch_cfg.fast_mode = true;
	ac_ch_set_config(&ac_device, EXAMPLE_AC_CHANNEL, &ch_cfg);
	ac_set_callback(&ac_device, AC_INTERRUPT_CONVERSION_COMPLETED_0,
			set_int_flag, 1);

	/* Start the comparison */
	ac_user_trigger_single_comparison(&ac_device);

	delay_ms(100);

	test_assert_true(test, intflag == true, "AC test failed");
}

/**
 * \brief Run AC driver unit tests.
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits   = CONF_TEST_STOPBITS
	};

	/* Initialize the system clock and board */
	sysclk_init();
	board_init();

	/* Enable the debug uart */
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

#if defined(__GNUC__)
	setbuf(stdout, NULL);
#endif

	/* Define all the test cases */
	DEFINE_TEST_CASE(ac_test, NULL, run_ac_test, NULL,
			"AC test");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(ac_tests) = {
		&ac_test
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(ac_suite, ac_tests,
			"SAM AC driver test suite");

	/* Run all tests in the test suite */
	test_suite_run(&ac_suite);

	while (1) {
		/* Busy-wait forever. */
	}
}
