/**
 * \file
 *
 * \brief AT30TS(E)75x Unit Tests.
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
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the AT30TS(E)75x driver.
 * It consists of test cases for the following functionality:
 * - AT30TS(E)75x data write (if has EEPROM)
 * - AT30TS(E)75x data read (if has EEPROM)
 * - AT30TS(E)75x temperature read
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 *
 * \section device_info Device Info
 * This example has been tested with the following setup:
 * - sam4n16c_sam4n_xplained_pro with I/O1 XPRO board connected to EXT1
 * - sam4c16c_sam4c_ek
 * - sam4cmp_db
 * - sam4cms_db
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
//@}

#include "asf.h"
#include <stdio.h>
#include <string.h>
#include "conf_test.h"

#define NB_PAGE 16
#define NB_BYTE 16

double temp;
uint8_t rx[NB_BYTE], tx[NB_BYTE];

#if BOARD_USING_AT30TSE != AT30TS75
/**
 * \brief AT30TS(E)75x write EEPROM test.
 *
 * \param test Current test case.
 */
static void run_test_write_data(const struct test_case *test)
{
	memset(tx, 0xFF, NB_BYTE);
	test_assert_true(test,
			at30tse_eeprom_write(tx, NB_BYTE, 0,
			(int)temp % NB_PAGE) == TWI_SUCCESS,
			"Error: AT30TS(E)75x write failed\n\r");
	delay_ms(5);
}

/**
 * \brief AT30TS(E)75x read and comparison EEPROM test.
 *
 * \param test Current test case.
 */
static void run_test_read_compare_data(const struct test_case *test)
{
	memset(rx, 0, NB_BYTE);
	test_assert_true(test,
			at30tse_eeprom_read(rx, NB_BYTE, 0,
			(int)temp % NB_PAGE) == TWI_SUCCESS,
			"Error: AT30TS(E)75x read failed\n\r");
	test_assert_true(test,
			!memcmp(tx, rx, NB_BYTE),
			"Error: AT30TS(E)75x comparison failed\n\r");
}
#endif

/**
 * \brief AT30TS(E)75x read temperature test.
 *
 * \param test Current test case.
 */
static void run_test_read_temperature(const struct test_case *test)
{
	test_assert_true(test,
			(at30tse_read_temperature(&temp) == TWI_SUCCESS),
			"Error: AT30TS(E)75x read temperature failed\n\r");
}

/**
 * \brief Application entry point for AT30TS(E)75x unit tests.
 *
 * \return Unused (ANSI-C compatibility).
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
	/* Initialize AT30TS(E)75x */
	at30tse_init();

	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Define all the test cases */
	DEFINE_TEST_CASE(at30tse_test_read_temperature,
			NULL, run_test_read_temperature, NULL,
			"at30tse read temperature test");
#if BOARD_USING_AT30TSE != AT30TS75
	DEFINE_TEST_CASE(at30tse_test_write_data,
			NULL, run_test_write_data, NULL,
			"at30tse write data test");
	DEFINE_TEST_CASE(at30tse_test_read_data,
			NULL, run_test_read_compare_data, NULL,
			"at30tse read and compare data test");
#endif
	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(at30tse_test_array) = {
			&at30tse_test_read_temperature,
#if BOARD_USING_AT30TSE != AT30TS75
			&at30tse_test_write_data,
			&at30tse_test_read_data,
#endif
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(at30tse_suite, at30tse_test_array,
			"at30tse driver test suite");

	/* Run all tests in the test suite */
	test_suite_run(&at30tse_suite);

	while (1) {
		/* Busy-wait forever */
	}
}
