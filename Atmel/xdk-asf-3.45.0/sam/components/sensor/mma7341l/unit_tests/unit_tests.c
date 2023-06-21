/**
 * \file
 *
 * \brief Unit tests for MMA7341L driver.
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

#include <stdint.h>
#include <stdbool.h>
#include <board.h>
#include <sysclk.h>
#include <string.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <conf_clock.h>
#include <conf_board.h>
#include <conf_test.h>
#include <mma7341l.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the MMA7341L driver.
 * It consists of test cases for the following functionality:
 * - MMA7341L gravity value get
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 *
 * \section device_info Device Info
 * SAM3U devices can be used.
 * This example has been tested with the following setup:
 * - sam3u4e_sam3u_ek
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

/**
 * \brief Get the gravity value of z axis.
 *
 * This test calls the get gravity value API functions and check if the value is in correct range.
 *
 * \param test Current test case.
 */
static void run_test_get_gravity_value(const struct test_case *test)
{
	xyz_g_t xyz_g;

	/* Set MMA7341L normal mode */
	mma7341l_set_mode(MMA7341L_NORMAL_MODE);

	/* Initialize MMA7341L */
	mma7341l_init();

	/* Calibrate MMA7341L */
	mma7341l_calibration();

	xyz_g = mma7341l_get_gravity_value();

	test_assert_true(test, 0.9 < xyz_g.z_g < 1.1, "The gravity value is not in correct range");
}

/**
 * \brief Run ili9325 driver unit tests.
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits   = CONF_TEST_STOPBITS
	};

	sysclk_init();
	board_init();

	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Define all the test cases */
	DEFINE_TEST_CASE(mma7341l_test_get_gravity_value, NULL, run_test_get_gravity_value, NULL,
			"mma7341l get gravity value test");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(mma7341l_test_array) = {
		&mma7341l_test_get_gravity_value,};

	/* Define the test suite */
	DEFINE_TEST_SUITE(mma7341l_suite, mma7341l_test_array,
			"mma7341l driver test suite");

	/* Run all tests in the test suite */
	test_suite_run(&mma7341l_suite);

	while (1) {
		/* Busy-wait forever */
	}
}
