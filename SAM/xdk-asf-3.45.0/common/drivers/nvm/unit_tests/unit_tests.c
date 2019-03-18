/**
 * \file
 *
 * \brief Common NVM driver Unit Test.
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

/*! \mainpage
 * \section intro Introduction
 * This is the unit test application for the \ref common_nvm.h "Common NVM
 *driver".
 * It consists of test cases for the following:
 * - Memory check
 * - Read/write byte access and data integrity
 * - Read/write buffer access and data integrity
 *
 * \section files Main Files
 * - \ref unit_tests.c: Non volatile memory unit tests application.
 * - \ref common_nvm.h: The NVM driver header
 * - \ref conf_test.h: test configuration file
 * - \ref conf_board.h: board initialization process configuration
 * - \ref conf_clock.h: clock specific initialization
 * - \ref conf_nvm.h: NVM driver configuration
 * - \ref conf_usart_serial.h: Serial port configuration (\see conf_test.h)
 *
 * \section deviceinfo Device Info
 * All AVR devices can be used. This application has been tested
 * with the following setup:
 *   - Evaluation kits with xxxxxxxxxxxxx
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for AVR.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/">Microchip</A>.\n
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <stdint.h>
#include <stdbool.h>
#include <asf.h>
#include <string.h>
#include "common_nvm.h"
#include "conf_test.h"
#if UC3
#include "uc3/flash_api.h"
#endif

/* ! \name Debug output configuration */
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

/* ! \name Byte pattern generator */
/* @{ */

/**
 * \brief Generates byte pattern 1 for a given address
 */
#define BYTE_PATTERN1(x) \
	((uint8_t)(((x) * 5 + 1) & 0xff))

/**
 * \brief Generates byte pattern 2 for a given address
 */
#define BYTE_PATTERN2(x) \
	((uint8_t)(((x) * 3) & 0xff))
/* @} */

#if XMEGA
#define TEST_ADDRESS             (PROGMEM_START + FLASH_SIZE - FLASH_PAGE_SIZE)
#elif UC3
#define TEST_ADDRESS             (FLASH_API_BASE_ADDRESS + FLASH_API_SIZE - \
	FLASH_API_PAGE_SIZE)
#elif SAM
#define TEST_ADDRESS             (IFLASH_ADDR + IFLASH_SIZE - IFLASH_PAGE_SIZE)
#endif

/**
 * \brief Performs a memory check on the non volatile memory
 *
 * This function will simply test the output of the function
 * \ref nvm_init and returns an error in case of failure.
 *
 * \param test Current test case.
 */
static void run_memory_check_test(const struct test_case *test)
{
	status_code_t status;

	status = nvm_init(INT_FLASH);
	test_assert_true(test, status == STATUS_OK,
			"Error memory check failed");
}

/**
 * \brief Test the read and write byte operations on the NVM
 *
 * This function will test the read and write functionalities of the NVM
 * using byte access. It will first write a known pattern on the 2
 * consecutive addresses and read it back by testing each value read.\n
 *
 * \param test Current test case.
 */
static void run_byte_access_test(const struct test_case *test)
{
	status_code_t status;
	uint8_t read_data[4], i;
#if SAM4S
	nvm_page_erase(INT_FLASH, TEST_ADDRESS / IFLASH_PAGE_SIZE);
#endif
	/* Write four bytes one by one from the given address */
	for (i = 0; i < 4; i++) {
		status = nvm_write_char(INT_FLASH, (uint32_t)TEST_ADDRESS + i, BYTE_PATTERN1(
				i));
		test_assert_true(test, status == STATUS_OK,
				"Write byte operation error @ byte %d", i);
	}

	/* Read back the four bytes one by one */
	for (i = 0; i < 4; i++) {
		nvm_read_char(INT_FLASH, (uint32_t)TEST_ADDRESS + i,
				&read_data[i]);
		test_assert_true(test, read_data[i] == BYTE_PATTERN1(i),
				"Read byte operation error @ byte %d"
				" (read: 0x%02x, expected: 0x%02x)", i,
				read_data[i], BYTE_PATTERN1(i));
	}
}

/**
 * \brief Test the read and write buffer operations on the NVM
 *
 * This function will test the read and write functionalities of the NVM
 * using buffer access. It will first fill a buffer with a known pattern and
 * read it back by testing each value read.\n
 *
 * \param test Current test case.
 */
static void run_buffer_access_test(const struct test_case *test)
{
	status_code_t status;
	uint8_t i, test_buf[20];

	/* Fills a test buffer with a known pattern
	 */
	for (i = 0; i < 20; i++) {
		test_buf[i] = BYTE_PATTERN2(i);
	}
#if SAM4S
	nvm_page_erase(INT_FLASH, TEST_ADDRESS / IFLASH_PAGE_SIZE);
#endif

	/* Write the buffer to the non volatile memory */
	status = nvm_write(INT_FLASH, (uint32_t)TEST_ADDRESS, (void *)test_buf,
			sizeof(test_buf));
	test_assert_true(test, status == STATUS_OK,
			"Write buffer operation error");

	/* Clear the test buffer */
	for (i = 0; i < 20; i++) {
		test_buf[i] = 0;
	}

	/* Read back the non volatile memory */
	status = nvm_read(INT_FLASH, (uint32_t)TEST_ADDRESS, (void *)test_buf,
			sizeof(test_buf));
	test_assert_true(test, status == STATUS_OK,
			"Read buffer operation error");

	/* Compare the values read from the NVM with the expected values
	 */
	for (i = 0; i < 20; i++) {
		test_assert_true(test, test_buf[i] == BYTE_PATTERN2(i),
				"Value not expected @ byte %d (read: 0x%02x,"
				" expected: 0x%02x)", i, test_buf[i],
				BYTE_PATTERN2(i));
	}
}

/**
 * \brief Run common NVM driver unit tests
 *
 * Initializes the clock system, board, serial output and NVM, then sets
 * up the NVM unit test suite and runs it.
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
#if XMEGA || UC3
		.charlength = CONF_TEST_CHARLENGTH,
#endif
		.paritytype = CONF_TEST_PARITY,
#if XMEGA || UC3
		.stopbits   = CONF_TEST_STOPBITS,
#endif
	};

	/* Initialize the board and all the peripheral required */
	sysclk_init();
	board_init();
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Define all the test cases */
	DEFINE_TEST_CASE(memory_check_test, NULL, run_memory_check_test, NULL,
			"Memory check");
	DEFINE_TEST_CASE(byte_access_test, NULL, run_byte_access_test, NULL,
			"Read/write byte access");
	DEFINE_TEST_CASE(buffer_access_test, NULL, run_buffer_access_test, NULL,
			"Read/write buffer access");

	/* Put test case addresses in an array. */
	DEFINE_TEST_ARRAY(memory_tests) = {
		&memory_check_test,
		&byte_access_test,
		&buffer_access_test
	};

	/* Define the test suite. */
	DEFINE_TEST_SUITE(memory_suite, memory_tests,
			"Common NVM driver unit test suite");

	/* Run all tests in the test suite. */
	test_suite_run(&memory_suite);

	while (1) {
		/* Intentionally left empty. */
	}
}
