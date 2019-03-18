/**
 * \file
 *
 * \brief AT45dbx DataFlash Component Unit Test.
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

/*! \mainpage
 * \section intro Introduction
 * This is the unit test application for the \ref at45dbx.h "AT45dbx component".
 * It consists of test cases for the following:
 * - Memory check
 * - Read/write byte access and data integrity
 * - Read/write sector access and data integrity
 * - Read/write multiple sector access and data integrity
 *
 * \section files Main Files
 * - \ref unit_tests.c: AT45DBx memory unit tests application.
 * - \ref at45dbx.c: The DataFlash driver
 * - \ref at45dbx.h: The DataFlash driver header
 * - \ref conf_test.h: test configuration file
 * - \ref conf_board.h: board initialization process configuration
 * - \ref conf_clock.h: clock specific initialization
 * - \ref conf_at45dbx.h: DataFlash driver configuration (including SPI service
 * selection)
 * - \ref conf_usart_serial.h: Serial port configuration (\see conf_test.h)
 *
 * \section deviceinfo Device Info
 * All AVR devices can be used. This application has been tested
 * with the following setup:
 *   - Evaluation kits with a DataFlash connected to an SPI interface.
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
#include "at45dbx.h"
#include "conf_test.h"

//! \name Debug output configuration
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

//! \name Byte pattern generator
//@{
/**
 * \brief Generates byte pattern 1 for a given address
 */
#define BYTE_PATTERN1(x)                                                       \
	((uint8_t) (((x) * 5 + 1) & 0xff))
/**
 * \brief Generates byte pattern 2 for a given address
 */
#define BYTE_PATTERN2(x)                                                       \
	((uint8_t) (((x) * 3) & 0xff))
/**
 * \brief Generates byte pattern 3 for a given address
 */
#define BYTE_PATTERN3(x)                                                       \
	((uint8_t) (((x) * 7 + 3) & 0xff))
//@}

/**
 * \brief A DataFlash sector-sized buffer for processing data in ram memory
 */
static uint8_t sector_buf[AT45DBX_SECTOR_SIZE];

/**
 * \brief Performs a memory check on all DataFlash memories
 *
 * This function will simply test the output of the function
 * \ref at45dbx_mem_check and returns an error in case of failure.
 *
 * \param test Current test case.
 */
static void run_memory_check_test(const struct test_case *test)
{
	bool status;

	status = at45dbx_mem_check();
	test_assert_true(test, status == true, "Error memory check failed");
}

/**
 * \brief Performs out of range memory test on DataFlash memory
 *
 * This function will simply test the output of the function
 * \ref at45dbx_mem_check and returns an error in case of failure.
 *
 * \param test Current test case.
 */
static void run_memory_range_check_test(const struct test_case *test)
{
	bool status;

	status = at45dbx_read_byte_open(
			(((uint32_t)1<<AT45DBX_MEM_SIZE)*AT45DBX_MEM_CNT));
	test_assert_true(test, status == true, "Error memory range check failed");
	status = at45dbx_read_byte_open(
			(((uint32_t)1<<AT45DBX_MEM_SIZE)*AT45DBX_MEM_CNT)+1);
	test_assert_true(test, status == false, "Error memory range check failed");

	}

/**
 * \brief Test the read and write byte operations on the DataFlash
 *
 * This function will test the read and write functionalities of the DataFlash
 * using byte access. It will first write a known pattern on the 2 first
 * consecutive sectors and read it back by testing each value read.\n
 * In addition to test the data integrity and the byte read / write
 * functions, this will also test the continuity of the sectors as well as the
 * auto-incrementation of the DataFlash address.
 *
 * \param test Current test case.
 */
static void run_byte_access_test(const struct test_case *test)
{
	uint32_t i;
	bool status;
	uint8_t byte;

	/* Write bytes one by one to the 2 first continuous sectors
	 */
	status = at45dbx_write_byte_open(0);
	test_assert_true(test, status == true,
			"Cannot open the DataFlash memory for write access");
	for (i=0; i<AT45DBX_SECTOR_SIZE * 2; i++) {
		status = at45dbx_write_byte(BYTE_PATTERN1(i));
		test_assert_true(test, status == true,
				"Write byte operation error @ 0x%08x", i);
	}
	at45dbx_write_close();

	/* Read back the 2 first sectors of the DataFlash and check the values
	 */
	status = at45dbx_read_byte_open(0);
	test_assert_true(test, status == true,
			"Cannot open the DataFlash memory for read access");
	for (i=0; i<AT45DBX_SECTOR_SIZE * 2; i++) {
		byte = at45dbx_read_byte();
		test_assert_true(test, byte == BYTE_PATTERN1(i),
				"Read byte operation error @ 0x%08x"
				" (read: 0x%02x, expected: 0x%02x)", i,
				byte, BYTE_PATTERN1(i));
	}
	at45dbx_read_close();
}

/**
 * \brief Test the read and write sector operations on the DataFlash
 *
 * This function will test the read and write functionalities of the DataFlash
 * using sector access. It will first fill a sector with a known pattern and
 * read it back by testing each value read.\n
 *
 * \param test Current test case.
 */
static void run_sector_access_test(const struct test_case *test)
{
	uint32_t i;
	bool status;

	/* Fills a ram sector with a known pattern
	 */
	for (i=0; i<AT45DBX_SECTOR_SIZE; i++) {
		sector_buf[i] = BYTE_PATTERN2(i);
	}

	/* Write the ram sector to the DataFlash
	 */
	status = at45dbx_write_sector_open(0);
	test_assert_true(test, status == true,
			"Cannot open the DataFlash memory for write access");
	status = at45dbx_write_sector_from_ram(sector_buf);
	test_assert_true(test, status == true,
			"Write sector operation error");
	at45dbx_write_close();

	/* Clear the ram sector buffer
	 */
	for (i=0; i<AT45DBX_SECTOR_SIZE; i++) {
		sector_buf[i] = 0;
	}

	/* Read back the sector of the DataFlash
	 */
	status = at45dbx_read_sector_open(0);
	test_assert_true(test, status == true,
			"Cannot open the DataFlash memory for read access");
	status = at45dbx_read_sector_to_ram(sector_buf);
	test_assert_true(test, status == true,
			"Read sector operation error");
	at45dbx_read_close();

	/* Compare the values read from the DataFlash with the expected values
	 */
	for (i=0; i<AT45DBX_SECTOR_SIZE; i++) {
		test_assert_true(test, sector_buf[i] == BYTE_PATTERN2(i),
				"Value not expected @ 0x%08x (read: 0x%02x,"
				" expected: 0x%02x)", i, sector_buf[i],
				BYTE_PATTERN2(i));
	}
}

/**
 * \brief Test the read and write multiple sector operations on the DataFlash
 *
 * This function will test the read and write functionalities of the DataFlash
 * using multiple sector access. It will first fill the 10 first DataFlash
 * sectors with a known pattern and read it back to test each value.\n
 *
 * \param test Current test case.
 */
static void run_multiple_sector_access_test(const struct test_case *test)
{
	bool status;
	uint32_t i;
	uint8_t value, cur_sector;
	uint8_t expected;

	/* Write the ram sector to the DataFlash
	 */
	status = at45dbx_write_sector_open(0);
	test_assert_true(test, status == true,
			"Cannot open the DataFlash memory for write access");
	cur_sector = 0;
	while (cur_sector++ < 10) {
		/* Fills a ram sector with a known pattern
		 */
		for (i=0; i<AT45DBX_SECTOR_SIZE; i++) {
			value = BYTE_PATTERN3(cur_sector * AT45DBX_SECTOR_SIZE + i);
			((uint8_t *) sector_buf)[i] = value;
		}
		/* Write sector on DataFlash */
		status = at45dbx_write_sector_from_ram(sector_buf);
		test_assert_true(test, status == true,
				"Error while writing sector # %i", cur_sector);
	}
	at45dbx_write_close();

	/* Read back the sector of the DataFlash
	 */
	status = at45dbx_read_sector_open(0);
	test_assert_true(test, status == true,
			"Cannot open the DataFlash memory for read access");
	cur_sector = 0;
	while (cur_sector++ < 10) {
		// Read the next sector.
		status = at45dbx_read_sector_to_ram(sector_buf);
		test_assert_true(test, status == true,
				"Error while reading sector # %i", cur_sector);

		/* Test each values of the current sector
		 */
		for (i=0; i<AT45DBX_SECTOR_SIZE; i++) {
			expected = BYTE_PATTERN3(cur_sector * AT45DBX_SECTOR_SIZE + i);
			test_assert_true(test, ((uint8_t *) sector_buf)[i] == expected,
					"Value not expected @ 0x%08x in sector # %i"
					" (read: 0x%02x, expected: 0x%02x)", i,
					cur_sector, ((uint8_t *) sector_buf)[i],
					expected);
		}
	}
	at45dbx_read_close();
}

/**
 * \brief Run DataFlash component unit tests
 *
 * Initializes the clock system, board, serial output and DataFlash, then sets
 * up the DataFlash unit test suite and runs it.
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits   = CONF_TEST_STOPBITS,
	};

	// Initialize the board and all the peripheral required
	sysclk_init();
	board_init();
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);
	at45dbx_init();

	// Define all the test cases
	DEFINE_TEST_CASE(memory_check_test, NULL, run_memory_check_test, NULL,
			"Memory check");
	DEFINE_TEST_CASE(byte_access_test, NULL, run_byte_access_test, NULL,
			"Read/write byte access");
	DEFINE_TEST_CASE(sector_access_test, NULL, run_sector_access_test, NULL,
			"Read/write sector access");
	DEFINE_TEST_CASE(multiple_sector_access_test, NULL,
			run_multiple_sector_access_test, NULL,
			"Read/write multiple sector access");
	DEFINE_TEST_CASE(memory_range_check_test, NULL,
			run_memory_range_check_test, NULL,
			"Memory range address check");

	// Put test case addresses in an array.
	DEFINE_TEST_ARRAY(memory_tests) = {
		&memory_check_test,
		&byte_access_test,
		&sector_access_test,
		&multiple_sector_access_test,
		&memory_range_check_test
	};

	// Define the test suite.
	DEFINE_TEST_SUITE(memory_suite, memory_tests,
			"AT45dbx component unit test suite");

	// Run all tests in the test suite.
	test_suite_run(&memory_suite);

	while (1) {
		// Intentionally left empty.
	};
}
