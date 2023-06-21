/**
 * \file
 *
 * \brief Unit tests for GPIO driver.
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

#include <asf.h>
#include <conf_test.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for GPIO driver.
 * It consists of test cases for the following functionality:
 * - GPIO interupt support
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_uart_serial.h
 *
 * \section device_info Device Info
 * SAM4L devices can be used.
 * This example has been tested with the following setup:
 * - sam4l4c_sam4l_ek (Need to connect PA06 and PB05 on the board)
 * - sam4l4c_sam4l_xplained_pro (Need to connect EXT3/PIN9 and EXT4/PIN3 on the board)
 * - sam4l4c_sam4l8_xplained_pro (Need to connect EXT3/PIN9 and EXT4/PIN3 on the board)
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for ARM. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */

/** \name Unit test configuration */
/* @{ */
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
/* @} */

volatile bool gpio_int_happened = false;

/**
 * GPIO pin interrupt callback.
 */
static void gpio_pin_callback(void)
{
	gpio_int_happened = true;
}

/**
 * \brief Test GPIO interrupt.
 *
 * \param test Current test case.
 */
static void run_gpio_int_test(const struct test_case *test)
{
	/* Configure an input pin to trigger an interrupt on falling edge */
	ioport_set_pin_dir(CONF_TEST_GPIO_IN, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(CONF_TEST_GPIO_IN, IOPORT_MODE_PULLUP |
			IOPORT_MODE_GLITCH_FILTER);
	ioport_set_pin_sense_mode(CONF_TEST_GPIO_IN, IOPORT_SENSE_FALLING);
	gpio_set_pin_callback(CONF_TEST_GPIO_IN, gpio_pin_callback, 1);
	gpio_enable_pin_interrupt(CONF_TEST_GPIO_IN);

	/* Configure an output pin */
	ioport_set_pin_dir(CONF_TEST_GPIO_OUT, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(CONF_TEST_GPIO_OUT, IOPORT_PIN_LEVEL_HIGH);

	/* Trigger an interrupt */
	gpio_int_happened = false;
	ioport_set_pin_level(CONF_TEST_GPIO_OUT, IOPORT_PIN_LEVEL_LOW);
	delay_ms(5);
	test_assert_true(test, gpio_int_happened,
			"No interrupt has been triggered!");
}

/**
 * \brief Run GPIO driver unit tests.
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits = CONF_TEST_STOPBITS
	};

	sysclk_init();
	board_init();
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Define all the test cases */
	DEFINE_TEST_CASE(gpio_int_test, NULL, run_gpio_int_test, NULL,
			"Test GPIO driver with interrupt support.");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(gpio_tests) = {
		&gpio_int_test
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(gpio_suite, gpio_tests, "GPIO driver test suite");

	/* Run all tests in the test suite */
	test_suite_run(&gpio_suite);

	while (1) {
		/* Busy-wait forever. */
	}
}
