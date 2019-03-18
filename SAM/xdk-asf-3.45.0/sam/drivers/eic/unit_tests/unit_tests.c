/**
 * \file
 *
 * \brief Unit tests for EIC driver.
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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
#include "eic.h"
#include "ioport.h"
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
 * This is the unit test application for the EIC driver.
 * It consists of test cases for the following functionality:
 * - Using GPIO as EIC pin to generate interrupt
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
 * - Connect Pin PA06 and PB05
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
 * \def CONF_TEST_EIC
 * \brief Test the functions provided by the EIC driver.
 */
//@}

volatile uint8_t intflag = 0;

/**
 * \brief Interrupt handler for EIC interrupt.
 */
static void set_int_flag(void)
{
	/* Check if EIC test line interrupt line is pending */
	if (eic_line_interrupt_is_pending(EIC, GPIO_UNIT_TEST_EIC_LINE)) {
		eic_line_disable_interrupt(EIC, GPIO_UNIT_TEST_EIC_LINE);
		intflag = 1;
	}
}

/**
 * \brief Test EIC
 *
 * \param test Current test case.
 */
static void run_eic_test(const struct test_case *test)
{
	struct eic_line_config eic_line_conf;

	ioport_set_pin_mode(GPIO_UNIT_TEST_EIC_PIN,
				GPIO_UNIT_TEST_EIC_PIN_MUX);
	ioport_disable_pin(GPIO_UNIT_TEST_EIC_PIN);

	eic_line_conf.eic_mode = EIC_MODE_EDGE_TRIGGERED;
	eic_line_conf.eic_edge = EIC_EDGE_FALLING_EDGE;
	eic_line_conf.eic_level = EIC_LEVEL_LOW_LEVEL;
	eic_line_conf.eic_filter = EIC_FILTER_DISABLED;
	eic_line_conf.eic_async = EIC_ASYNCH_MODE;

	eic_enable(EIC);
	eic_line_set_config(EIC, GPIO_UNIT_TEST_EIC_LINE, 
		&eic_line_conf);
	eic_line_set_callback(EIC, GPIO_UNIT_TEST_EIC_LINE, set_int_flag, 
		EIC_1_IRQn, 1);
	eic_line_enable(EIC, GPIO_UNIT_TEST_EIC_LINE);

	ioport_set_pin_dir(GPIO_EIC_TRIG_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(GPIO_EIC_TRIG_PIN, IOPORT_PIN_LEVEL_HIGH);
	delay_ms(100);
	ioport_set_pin_level(GPIO_EIC_TRIG_PIN, IOPORT_PIN_LEVEL_LOW);

	delay_ms(100);

	test_assert_true(test, intflag == 1, "EIC test failed");


}

/**
 * \brief Run EIC driver unit tests.
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
	DEFINE_TEST_CASE(eic_test, NULL, run_eic_test, NULL,
			"EIC test");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(eic_tests) = {
		&eic_test
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(eic_suite, eic_tests,
			"SAM EIC driver test suite");

	/* Run all tests in the test suite */
	test_suite_run(&eic_suite);

	while (1) {
		/* Busy-wait forever. */
	}
}
