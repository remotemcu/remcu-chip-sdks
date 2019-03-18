/**
 * \file
 *
 * \brief Unit tests for MegaRF IOPORT service
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <conf_test.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test for the IOPORT service. The IO Pin is
 * tested by setting high and low and read back using another
 * IO Pin by shorting the pins.
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 *
 * \section device_info Device Info
 * This example has been tested with the following setup(s):
 * - atmega128rfa1_stk600 and atmega256rfr2_xplained_pro
 *
 * \section description Description of the unit tests
 * See the documentation for the individual unit test functions
 * \ref unit_tests.c "here" for detailed descriptions of the tests.
 *
 * \section dependencies Dependencies
 * This example depends directly on the following modules:
 * - \ref test_suite_group
 * - \ref megarf_usart_group
 * - \ref megarf_ioport_group
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for AVR. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 */

/**
 * \brief Test IOPORT pin level is getting changed.
 *
 * This function set the direction of CONF_OUT_PIN to output mode with pull-up
 * enabled and read the status of pin using CONF_IN_PIN which is configured in
 * input mode.
 *
 * The pin CONF_OUT_PIN and CONF_IN_PIN are shorted using a jumper.
 *
 * \param test Current test case.
 */
static void run_ioport_pin_test(const struct test_case *test)
{
	static volatile pin_mask_t pin_val;

	/* Set output direction on the given IO Pin */
	ioport_set_pin_dir(CONF_OUT_PIN, IOPORT_DIR_OUTPUT);

	/* Set direction and pull-up on the given IO Pin */
	ioport_set_pin_dir(CONF_IN_PIN, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(CONF_IN_PIN, IOPORT_MODE_PULLUP);

	/* Set IO pin as high */
	ioport_set_pin_level(CONF_OUT_PIN, IOPORT_PIN_LEVEL_HIGH);
	delay_ms(10);
	pin_val = ioport_get_pin_level(CONF_IN_PIN);
	test_assert_true(test, pin_val == 1,
			"IOPORT Set pin level high test failed");

	/* Set IO pin as low */
	ioport_set_pin_level(CONF_OUT_PIN, IOPORT_PIN_LEVEL_LOW);
	delay_ms(10);
	pin_val = ioport_get_pin_level(CONF_IN_PIN);
	test_assert_true(test, pin_val == 0,
			"IOPORT Set pin level low test failed");

	/* Toggle IO pin */
	ioport_toggle_pin_level(CONF_OUT_PIN);
	delay_ms(10);
	pin_val = ioport_get_pin_level(CONF_IN_PIN);
	test_assert_true(test, pin_val == 1,
			"IOPORT Set pin level toggle test failed");
}

/**
 * \brief Test IOPORT port level is getting changed.
 *
 * This function set the direction of CONF_PORT_OUT_PIN_MASK to output mode with
 * pull-up enabled and read the status of pin using CONF_PORT_IN_PIN_MASK which
 * is configured in input mode.
 * The pin CONF_PORT_OUT_PIN_MASK and CONF_PORT_IN_PIN_MASK are shorted using a
 * jumper.
 *
 * \param test Current test case.
 */
static void run_ioport_port_test(const struct test_case *test)
{
	static volatile pin_mask_t port_val;

	/* Set direction and pull-up on the given IOPORT */
	ioport_set_port_dir(CONF_PORT, CONF_PORT_IN_PIN_MASK, IOPORT_DIR_INPUT);
	ioport_set_port_mode(CONF_PORT, CONF_PORT_IN_PIN_MASK,
			IOPORT_MODE_PULLUP);

	/* Set output direction on the given IOPORT */
	ioport_set_port_dir(CONF_PORT, CONF_PORT_OUT_PIN_MASK,
			IOPORT_DIR_OUTPUT);

	/* Set  IOPORT as high */
	ioport_set_port_level(CONF_PORT, CONF_PORT_OUT_PIN_MASK,
			IOPORT_PIN_LEVEL_HIGH);
	delay_ms(10);
	port_val = ioport_get_port_level(CONF_PORT, CONF_PORT_IN_PIN_MASK);
	test_assert_true(test, port_val == CONF_PORT_IN_PIN_MASK,
			"IOPORT Set port level high test failed.");

	/* Set  IOPORT as low */
	ioport_set_port_level(CONF_PORT, CONF_PORT_OUT_PIN_MASK,
			IOPORT_PIN_LEVEL_LOW);
	delay_ms(10);
	port_val = ioport_get_port_level(CONF_PORT, CONF_PORT_IN_PIN_MASK);
	test_assert_true(test, port_val == 0,
			"IOPORT Set port level low test failed.");

	/* Toggle  IOPORT */
	ioport_toggle_port_level(CONF_PORT, CONF_PORT_OUT_PIN_MASK);
	delay_ms(10);
	port_val = ioport_get_port_level(CONF_PORT, CONF_PORT_IN_PIN_MASK);
	test_assert_true(test, port_val == CONF_PORT_IN_PIN_MASK,
			"IOPORT Set port level toggle test failed.");
}

/**
 * \brief Run IOPORT unit tests
 *
 * Initializes the clock system, board and serial output, then sets up the
 * IOPORT Service unit test suite and runs it.
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits   = CONF_TEST_STOPBITS,
	};

	board_init();
	sysclk_init();
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	DEFINE_TEST_CASE(ioport_port_test, NULL, run_ioport_port_test, NULL,
			"Test setting of various IOPORT functions");
	DEFINE_TEST_CASE(ioport_pin_test, NULL, run_ioport_pin_test, NULL,
			"Test IOPORT pin level is getting changed");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(ioport_test) = {
		&ioport_port_test,
		&ioport_pin_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(ioport_suite, ioport_test,
			"MEGARF IOPORT test suite");

	/* Run all tests in the suite */
	test_suite_run(&ioport_suite);

	while (1) {
		/* Intentionally left empty. */
	}
}
