/**
 * \file
 *
 * \brief Unit tests for First In First Out buffer service
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
#include <string.h>

#include <compiler.h>
#include <conf_test.h>
#include <asf.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the \ref fifo.h "FIFO service".
 * It consists of test cases for the following:
 * - size reporting on flushed/empty and used FIFO
 * - under- and overflow on pull/push
 * - data integrity for push/pull
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 *
 * \section device_info Device Info
 * All Atmel devices can be used.
 *
 * \section description Description of the unit tests
 * See the documentation for the individual unit test functions \ref unit_tests.c
 * "here" for detailed descriptions of the tests.
 *
 * \section dependencies Dependencies
 * This example depends directly on the following modules:
 * - \ref test_suite_group
 * - \ref fifo.h "FIFO service"
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for AVR or ARM. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
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

//! Size of buffer, as number of \ref buffer_element
#define TEST_FIFO_BUFFER_LENGTH  4

//! Common value to use when pushing the different datatypes
#define TEST_VALUE               0x12345678

/**
 * \brief Datatype for the FIFO buffer
 *
 * This is a union of all the datatypes which the FIFO service supports. The
 * purpose of this type is to allow for the buffer \e length (in elements) to be
 * specified instead of the \e size (in bytes), making it easier to ensure that
 * the buffer is large enough to contain the specified number of all datatypes.
 */
union buffer_element {
	uint8_t  byte;
	uint16_t halfword;
	uint32_t word;
};

/**
 * \brief Buffer to associate with FIFO
 *
 * This buffer consists of \ref TEST_FIFO_BUFFER_LENGTH elements capable of
 * holding a byte, halfword or word.
 */
union buffer_element test_fifo_buffer[TEST_FIFO_BUFFER_LENGTH];

/**
 * \brief FIFO buffer descriptor to use
 *
 * This descriptor contains information about the location of the FIFO buffer,
 * its size and where to read from or write to upon the next buffer pull or
 * push. This is required to access the FIFO buffer via the FIFO service.
 *
 * \pre The descriptor must be initialized with \ref fifo_init() before the FIFO
 * buffer can be used.
 *
 * \note The FIFO buffer should be used with only one of its supported datatypes
 * at a time, or the buffered values will be corrupted unless special conditions
 * are met.
 */
fifo_desc_t test_fifo_desc;

//! \name FIFO unit test functions
//@{
/**
 * \brief Test size-checking functions on non-empty buffer
 *
 * This test flushes the buffer, then pushes one element to it before checking
 * that the functions for checking size return the expected values.
 *
 * \param test Current test case.
 */
static void run_fifo_size_test(const struct test_case *test)
{
	uint16_t size;
	bool     status;

	// Push an element to a flushed FIFO.
	fifo_flush(&test_fifo_desc);
	fifo_push_uint8(&test_fifo_desc, TEST_VALUE & 0xff);

	// Check that the various size-related functions report correctly.
	status = fifo_is_empty(&test_fifo_desc);
	test_assert_false(test, status,
			"Buffer unexpectedly reported as empty");

	size = fifo_get_used_size(&test_fifo_desc);
	test_assert_true(test, size == 1, "Used size %u, expected 1", size);

	size = fifo_get_free_size(&test_fifo_desc);
	test_assert_true(test, size == (TEST_FIFO_BUFFER_LENGTH - 1),
			"Free size %u, expected %u", size,
			TEST_FIFO_BUFFER_LENGTH - 1);
}

/**
 * \brief Test size-checking function on flushed buffer
 *
 * This test pushes one element to the buffer, then flushes it before checking
 * that the functions for checking size return the expected values.
 *
 * \param test Current test case.
 */
static void run_fifo_flush_test(const struct test_case *test)
{
	uint16_t size;
	bool     status;

	// Push an element to FIFO, then flush it
	fifo_push_uint8(&test_fifo_desc, TEST_VALUE);
	fifo_flush(&test_fifo_desc);

	// Check that the various size-related functions report correctly
	status = fifo_is_empty(&test_fifo_desc);
	test_assert_true(test, status,
			"Buffer unexpectedly reported as not empty");

	size = fifo_get_used_size(&test_fifo_desc);
	test_assert_true(test, size == 0, "Used size %u, expected 0", size);

	size = fifo_get_free_size(&test_fifo_desc);
	test_assert_true(test, size == TEST_FIFO_BUFFER_LENGTH,
			"Free size %u, expected %u", size,
			TEST_FIFO_BUFFER_LENGTH);
}

/**
 * \brief Test that underflow is reported
 *
 * This test flushes the buffer and attempts to pull an element of every
 * supported datatype, checking that a buffer underflow is reported for
 * all of them.
 *
 * \param test Current test case.
 */
static void run_fifo_underflow_test(const struct test_case *test)
{
	union buffer_element item;
	uint_fast8_t         status;

	fifo_flush(&test_fifo_desc);

	/*
	 * Try pulling each datatype from flushed, i.e., empty FIFO, and
	 * verify that underflow is reported.
	 */
	status = fifo_pull_uint8(&test_fifo_desc, &item.byte);
	test_assert_true(test, status == FIFO_ERROR_UNDERFLOW,
			"No underflow for byte pull");

	status = fifo_pull_uint16(&test_fifo_desc, &item.halfword);
	test_assert_true(test, status == FIFO_ERROR_UNDERFLOW,
			"No underflow for halfword pull");

	status = fifo_pull_uint32(&test_fifo_desc, &item.word);
	test_assert_true(test, status == FIFO_ERROR_UNDERFLOW,
			"No underflow for word pull");
}

/**
 * \brief Test that overflow is reported
 *
 * This test flushes the buffer and fills it with at least one element of every
 * supported datatype, before attempting to push one more element of each type,
 * checking that a buffer overflow is reported for all of them.
 *
 * \param test Current test case.
 */
static void run_fifo_overflow_test(const struct test_case *test)
{
	uint_fast8_t status;
	uint_fast8_t i;

	fifo_flush(&test_fifo_desc);

	// Fill FIFO, using at least one element of each datatype.
	for (i = 0; i < TEST_FIFO_BUFFER_LENGTH; i++) {
		switch (i) {
		case 0:
			status = fifo_push_uint8(&test_fifo_desc,
					TEST_VALUE & 0xff);
			break;

		case 1:
			status = fifo_push_uint16(&test_fifo_desc,
					TEST_VALUE & 0xffff);
			break;

		default:
			status = fifo_push_uint32(&test_fifo_desc, TEST_VALUE);
		}

		test_assert_true(test, status == FIFO_OK,
				"Unexpected push failure after %u successes",
				i);
	}

	// Try pushing to a full buffer, verify that overflow is reported.
	status = fifo_push_uint8(&test_fifo_desc, 0);
	test_assert_true(test, status == FIFO_ERROR_OVERFLOW,
			"No overflow for byte push");

	status = fifo_push_uint16(&test_fifo_desc, 0);
	test_assert_true(test, status == FIFO_ERROR_OVERFLOW,
			"No overflow for halfword push");

	status = fifo_push_uint32(&test_fifo_desc, 0);
	test_assert_true(test, status == FIFO_ERROR_OVERFLOW,
			"No overflow for word push");
}

/**
 * \brief Test push and pull
 *
 * This test pushes an element of every supported datatype, with increasing
 * size, to the buffer. The elements are then pulled in the same order and
 * their values verified.
 *
 * \note The elements are pushed with increasing datatype size to prevent
 * corruption of the buffer contents. This is due to the FIFO indexes its
 * buffer based on the datatype that is being pulled or pushed.
 *
 * \param test Current test case.
 */
static void run_fifo_push_pull_test(const struct test_case *test)
{
	union buffer_element item;
	uint_fast8_t         status;

	fifo_flush(&test_fifo_desc);

	/* Push three elements into the FIFO, with increasing datatype size.
	 * Check that the pushes succeed.
	 */
	status = fifo_push_uint8(&test_fifo_desc, TEST_VALUE);
	test_assert_true(test, status == FIFO_OK, "Error during byte push");

	status = fifo_push_uint16(&test_fifo_desc, TEST_VALUE);
	test_assert_true(test, status == FIFO_OK, "Error during halfword push");

	status = fifo_push_uint32(&test_fifo_desc, TEST_VALUE);
	test_assert_true(test, status == FIFO_OK, "Error during word push");

	/* Pull the elements back out, in the same order, and verify them.
	 * Check that the pulls succeed.
	 */
	status = fifo_pull_uint8(&test_fifo_desc, &item.byte);
	test_assert_true(test, status == FIFO_OK, "Error during byte pull");
	test_assert_true(test, item.byte == (TEST_VALUE & 0xff),
			"Pulled byte 0x%02x, expected 0x%02x", item.byte,
			TEST_VALUE & 0xff);

	status = fifo_pull_uint16(&test_fifo_desc, &item.halfword);
	test_assert_true(test, status == FIFO_OK, "Error during halfword pull");
	test_assert_true(test, item.halfword == (TEST_VALUE & 0xffff),
			"Pulled halfword 0x%04x, expected 0x%04x", item.halfword,
			TEST_VALUE & 0xffff);

	status = fifo_pull_uint32(&test_fifo_desc, &item.word);
	test_assert_true(test, status == FIFO_OK, "Error during word pull");
	test_assert_true(test, item.word == TEST_VALUE,
			"Pulled word 0x%08lx, expected 0x%08lx", item.word,
			TEST_VALUE);
}
//@}

/**
 * \brief Run FIFO service unit tests
 *
 * Initializes the clock system, board, serial output and FIFO, then sets up the
 * FIFO unit test suite and runs it.
 */
int main (void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits   = CONF_TEST_STOPBITS,
	};

	sysclk_init();
	board_init();
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	fifo_init(&test_fifo_desc, test_fifo_buffer, TEST_FIFO_BUFFER_LENGTH);

	// Define all the test cases.
	DEFINE_TEST_CASE(fifo_size_test, NULL, run_fifo_size_test, NULL,
			"Size with push");
	DEFINE_TEST_CASE(fifo_flush_test, NULL, run_fifo_flush_test, NULL,
			"Size with flush");
	DEFINE_TEST_CASE(fifo_underflow_test, NULL, run_fifo_underflow_test,
			NULL, "Underflow on pull");
	DEFINE_TEST_CASE(fifo_overflow_test, NULL, run_fifo_overflow_test, NULL,
			"Overflow on push");
	DEFINE_TEST_CASE(fifo_push_pull_test, NULL, run_fifo_push_pull_test,
			NULL, "Push and pull");

	// Put test case addresses in an array.
	DEFINE_TEST_ARRAY(fifo_tests) = {
		&fifo_size_test,
		&fifo_flush_test,
		&fifo_underflow_test,
		&fifo_overflow_test,
		&fifo_push_pull_test,
	};

	// Define the test suite.
	DEFINE_TEST_SUITE(fifo_suite, fifo_tests, "FIFO service unit test suite");

	// Run all tests in the test suite.
	test_suite_run(&fifo_suite);

	while (1) {
		// Intentionally left empty.
	};
}
