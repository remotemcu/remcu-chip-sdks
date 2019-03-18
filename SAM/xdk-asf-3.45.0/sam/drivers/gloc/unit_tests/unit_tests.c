/**
 * \file
 *
 * \brief Unit tests for GLOC driver.
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

#include <asf.h>
#include <conf_test.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the GLOC driver.
 * It contains one test case for the GLOC module:
 * - Test 4 inputs XOR.
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_uart_serial.h
 * - \ref conf_gloc.h
 *
 * \section device_info Device Info
 * This example has been tested on a sam4lc4c_sam4l_user_board with the 
 * following setup:
 * - A 12MHz oscillator on OSC0,
 * - A USART connected on PIN_PC11 (RxD) and PIN_PC12 (TxD) pins,
 * - The selected GLOC input/output pins are PIN_PA20 (GLOC_IN0), PIN_PA21 
 *   (GLOC_IN1), PIN_PA22 (GLOC_IN2), PIN_PA07 (GLOC_IN3) and PIN_PA24 
 *   (GLOC_OUT0).
 * - GPIO pins used to set/clear GLOC input pins are PIN_PC01 (connected to 
 *   GLOC_IN0), PIN_PC07 (connected to GLOC_IN1), PIN_PC08 (connected to 
 *   GLOC_IN2) and PIN_PC13 (connected to GLOC_IN3).
 * - GPIO pin used to read GLOC output pin is PA24 (connected to GLOC_OUT0).
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for ARM. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */

/** GLOC instance */
struct gloc_dev_inst   dev_inst;
/** GLOC LUT configuration */
struct gloc_lut_config lut_config;

/** XOR truth table for four input */
#define XOR_TRUTH_TABLE_FOUR_INPUT     0x6996u

/**
 * \brief Test GLOC Logic module with 4 Inputs XOR.
 *
 * This tests check the capabilty of the Glue Logic driver to handle 4
 * inputs XOR operation.
 *
 * \param test Current test case.
 */
static void run_gloc_4inputs_xor_test(const struct test_case *test)
{
	bool out;

	/* Configure pins for changing GLOC input */
	ioport_set_pin_dir(CONF_TEST_GLOC_IN0, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(CONF_TEST_GLOC_IN1, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(CONF_TEST_GLOC_IN2, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(CONF_TEST_GLOC_IN3, IOPORT_DIR_OUTPUT);

	/* Set the 4 inputs XOR truth table value in LUT0. */
	gloc_lut_get_config_defaults(&lut_config);
	lut_config.truth_table_value = XOR_TRUTH_TABLE_FOUR_INPUT;
	gloc_lut_set_config(&dev_inst, 0, &lut_config);

	/* Test GLOC with different input */
	ioport_set_pin_level(CONF_TEST_GLOC_IN0, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN1, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN2, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN3, LOW);
	/** Ensure a minimum propagation delay to read the port pin. */
	delay_us(50);
	out = ioport_get_pin_level(CONF_TEST_GLOC_OUT0);
	test_assert_true(test, out == false, "4 inputs XOR failed at 1");

	ioport_set_pin_level(CONF_TEST_GLOC_IN0, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN1, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN2, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN3, LOW);
	/* Ensure a minimum propagation delay to read the port pin. */
	delay_us(50);
	out = ioport_get_pin_level(CONF_TEST_GLOC_OUT0);
	test_assert_true(test, out == true, "4 inputs XOR failed at 2");

	ioport_set_pin_level(CONF_TEST_GLOC_IN0, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN1, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN2, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN3, LOW);
	/* Ensure a minimum propagation delay to read the port pin. */
	delay_us(50);
	out = ioport_get_pin_level(CONF_TEST_GLOC_OUT0);
	test_assert_true(test, out == true, "4 inputs XOR failed at 3");

	ioport_set_pin_level(CONF_TEST_GLOC_IN0, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN1, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN2, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN3, LOW);
	/* Ensure a minimum propagation delay to read the port pin. */
	delay_us(50);
	out = ioport_get_pin_level(CONF_TEST_GLOC_OUT0);
	test_assert_true(test, out == false, "4 inputs XOR failed at 4");

	ioport_set_pin_level(CONF_TEST_GLOC_IN0, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN1, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN2, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN3, LOW);
	/* Ensure a minimum propagation delay to read the port pin. */
	delay_us(50);
	out = ioport_get_pin_level(CONF_TEST_GLOC_OUT0);
	test_assert_true(test, out == true, "4 inputs XOR failed at 5");

	ioport_set_pin_level(CONF_TEST_GLOC_IN0, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN1, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN2, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN3, LOW);
	/* Ensure a minimum propagation delay to read the port pin. */
	delay_us(50);
	out = ioport_get_pin_level(CONF_TEST_GLOC_OUT0);
	test_assert_true(test, out == false, "4 inputs XOR failed at 6");

	ioport_set_pin_level(CONF_TEST_GLOC_IN0, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN1, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN2, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN3, LOW);
	/* Ensure a minimum propagation delay to read the port pin. */
	delay_us(50);
	out = ioport_get_pin_level(CONF_TEST_GLOC_OUT0);
	test_assert_true(test, out == false, "4 inputs XOR failed at 7");

	ioport_set_pin_level(CONF_TEST_GLOC_IN0, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN1, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN2, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN3, LOW);
	/* Ensure a minimum propagation delay to read the port pin. */
	delay_us(50);
	out = ioport_get_pin_level(CONF_TEST_GLOC_OUT0);
	test_assert_true(test, out == true, "4 inputs XOR failed at 8");

	ioport_set_pin_level(CONF_TEST_GLOC_IN0, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN1, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN2, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN3, HIGH);
	/* Ensure a minimum propagation delay to read the port pin. */
	delay_us(50);
	out = ioport_get_pin_level(CONF_TEST_GLOC_OUT0);
	test_assert_true(test, out == true, "4 inputs XOR failed at 9");

	ioport_set_pin_level(CONF_TEST_GLOC_IN0, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN1, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN2, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN3, HIGH);
	/* Ensure a minimum propagation delay to read the port pin. */
	delay_us(50);
	out = ioport_get_pin_level(CONF_TEST_GLOC_OUT0);
	test_assert_true(test, out == false, "4 inputs XOR failed at 10");

	ioport_set_pin_level(CONF_TEST_GLOC_IN0, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN1, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN2, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN3, HIGH);
	/* Ensure a minimum propagation delay to read the port pin. */
	delay_us(50);
	out = ioport_get_pin_level(CONF_TEST_GLOC_OUT0);
	test_assert_true(test, out == false, "4 inputs XOR failed at 11");

	ioport_set_pin_level(CONF_TEST_GLOC_IN0, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN1, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN2, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN3, HIGH);
	/* Ensure a minimum propagation delay to read the port pin. */
	delay_us(50);
	out = ioport_get_pin_level(CONF_TEST_GLOC_OUT0);
	test_assert_true(test, out == true, "4 inputs XOR failed at 12");

	ioport_set_pin_level(CONF_TEST_GLOC_IN0, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN1, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN2, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN3, HIGH);
	/* Ensure a minimum propagation delay to read the port pin. */
	delay_us(50);
	out = ioport_get_pin_level(CONF_TEST_GLOC_OUT0);
	test_assert_true(test, out == false, "4 inputs XOR failed at 13");

	ioport_set_pin_level(CONF_TEST_GLOC_IN0, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN1, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN2, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN3, HIGH);
	/* Ensure a minimum propagation delay to read the port pin. */
	delay_us(50);
	out = ioport_get_pin_level(CONF_TEST_GLOC_OUT0);
	test_assert_true(test, out == true, "4 inputs XOR failed at 14");

	ioport_set_pin_level(CONF_TEST_GLOC_IN0, LOW);
	ioport_set_pin_level(CONF_TEST_GLOC_IN1, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN2, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN3, HIGH);
	/* Ensure a minimum propagation delay to read the port pin. */
	delay_us(50);
	out = ioport_get_pin_level(CONF_TEST_GLOC_OUT0);
	test_assert_true(test, out == true, "4 inputs XOR failed at 15");

	ioport_set_pin_level(CONF_TEST_GLOC_IN0, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN1, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN2, HIGH);
	ioport_set_pin_level(CONF_TEST_GLOC_IN3, HIGH);
	/* Ensure a minimum propagation delay to read the port pin. */
	delay_us(50);
	out = ioport_get_pin_level(CONF_TEST_GLOC_OUT0);
	test_assert_true(test, out == false, "4 inputs XOR failed at 16");
}

/**
 * \brief Run GLOC driver unit tests.
 */
int main(void)
{
	sysclk_init();
	board_init();

	const usart_serial_options_t usart_serial_options = {
		.baudrate = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits = CONF_TEST_STOPBITS
	};

	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Initialize the GLOC module */
	gloc_init(&dev_inst, GLOC);
	/* Enable the GLOC module. */
	gloc_enable(&dev_inst);

	/* Define all the test cases. */
	DEFINE_TEST_CASE(gloc_4inputs_xor_test, NULL, run_gloc_4inputs_xor_test,
			NULL, "SAM GLOC LUT 4 Inputs XOR Test");

	/* Put test case addresses in an array. */
	DEFINE_TEST_ARRAY(gloc_tests) = {
		&gloc_4inputs_xor_test,
	};

	/* Define the test suite. */
	DEFINE_TEST_SUITE(gloc_suite, gloc_tests, "SAM GLOC driver test suite");

	/* Run all tests in the test suite. */
	test_suite_run(&gloc_suite);

	while (1) {
		/* Busy-wait forever. */
	}
}
