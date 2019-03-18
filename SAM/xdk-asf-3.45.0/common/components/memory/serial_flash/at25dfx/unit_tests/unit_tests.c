/**
 * \file
 *
 * \brief Unit tests for AT25DFx driver.
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
#include <at25dfx.h>
#include <conf_at25dfx.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the AT25DFx driver.
 * It consists of test cases for the following functionalities:
 * - AT25DFx initialization
 * - AT25DFx protect functions
 * - AT25DFx data access functions
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_at25dfx.h
 *
 * \section device_info Device Info
 * This example has been tested with the following setup:
 * - sam3n4c_sam3n_ek
 * - sam4lc4c_sam4l_ek
 * - sam4e16e_sam4e_ek
 * - sam4c16c_sam4c_ek
 * - sam4cmp16c_sam4cmp_db
 * - sam4cms16c_sam4cms_db
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
 * \def CONF_TEST_AT25DFX
 * \brief AT25DFx SerialFlash configurations.
 */
//@}

#define TEST_PROTECT_ADDRESS   0x200

/* Data buffer for the unit test */
static uint8_t data_buff[AT25DFX_UNIT_TEST_PAGE_SIZE];

/**
 * \brief Test AT25DFx initialization procedure.
 *
 * This test calls the initialization function and checks the SerialFlash.
 *
 * \param test Current test case.
 */
static void run_test_at25dfx_init(const struct test_case *test)
{
	at25_status_t status;

	/* Initialize the SerialFlash */
	at25dfx_initialize();

	/* Set the SerialFlash active */
	at25dfx_set_mem_active(AT25DFX_MEM_ID);

	/* Check if the SerialFlash is valid */
	status = at25dfx_mem_check();

	/* Validate the SerialFlash init and check function */
	test_assert_true(test, status == AT25_SUCCESS, 
			"Specific SerialFlash not found!");
}

/**
 * \brief Test AT25DFx protect functions.
 *
 * This test calls the SerialFlash protect functions.
 *
 * \param test Current test case.
 */
static void run_test_at25dfx_protect(const struct test_case *test)
{
	at25_status_t status;
	uint8_t dev_status;

	at25dfx_protect_chip(AT25_TYPE_UNPROTECT);

	/* Get chip protection status through the status register */
	status = at25dfx_read_status(&dev_status);

	/* Validate the chip unprotect command */
	if ((dev_status & AT25_STATUS_SWP) != AT25_STATUS_SWP_PROTNONE) {
		test_assert_true(test, 0, "Unprotect chip cmd error!");
	}

	at25dfx_protect_sector(TEST_PROTECT_ADDRESS, AT25_TYPE_PROTECT);

	status = at25dfx_read_sector_protect_status(TEST_PROTECT_ADDRESS);

	test_assert_true(test, status == AT25_SECTOR_PROTECTED, 
			"Protect sector cmd error!");

	at25dfx_protect_sector(TEST_PROTECT_ADDRESS, AT25_TYPE_UNPROTECT);

	status = at25dfx_read_sector_protect_status(TEST_PROTECT_ADDRESS);

	test_assert_true(test, status == AT25_SECTOR_UNPROTECTED, 
			"Unrotect sector cmd error!");

	at25dfx_protect_chip(AT25_TYPE_PROTECT);

	/* Get chip protection status through the status register */
	status = at25dfx_read_status(&dev_status);

	/* Validate the chip protect command */
	if ((dev_status & AT25_STATUS_SWP) != AT25_STATUS_SWP) {
		test_assert_true(test, 0, "Protect chip cmd error!");
	}
}

/**
 * \brief Test data read, write and erase API functions.
 *
 * This test calls the data chip erase, read, write and block erase API 
 * functions.
 *
 * \param test Current test case.
 */
static void run_test_at25dfx_data_access(const struct test_case *test)
{
	at25_status_t status;
	uint32_t i;
	uint32_t page_num = 0;

	/* Unprotect the SerialFlash first */
	at25dfx_protect_chip(AT25_TYPE_UNPROTECT);

	/* Test block erase */
	i = 0;
	page_num = 0;

	status = at25dfx_erase_block(AT25DFX_UNIT_TEST_BLOCK_ADDR);

	while (page_num < 
			AT25DFX_UNIT_TEST_BLOCK_SIZE / AT25DFX_UNIT_TEST_PAGE_SIZE) {
		memset(data_buff, 0x0, sizeof(data_buff));

		at25dfx_read(data_buff, AT25DFX_UNIT_TEST_PAGE_SIZE, 
				page_num * AT25DFX_UNIT_TEST_PAGE_SIZE);

		for (i = 0; i < AT25DFX_UNIT_TEST_PAGE_SIZE; i++) {
			if (data_buff[i] != 0xff) {
				status = AT25_ERROR;
			}
		}

		page_num++;
	}

	/* Validate the SerialFlash block erase function */
	test_assert_true(test, status == AT25_SUCCESS, "Block erase failed!");

	/* Test read/write function */
	i = 0;
	page_num = 0;

	while (page_num <
			AT25DFX_UNIT_TEST_BLOCK_SIZE / AT25DFX_UNIT_TEST_PAGE_SIZE) {
		for (i = 0; i < AT25DFX_UNIT_TEST_PAGE_SIZE; i++) {
			data_buff[i] = i & 0xff;
		}

		at25dfx_write(data_buff, AT25DFX_UNIT_TEST_PAGE_SIZE,
				page_num * AT25DFX_UNIT_TEST_PAGE_SIZE);

		/* Reset the data buffer */
		memset(data_buff, 0x0, sizeof(data_buff));

		status = at25dfx_read(data_buff, AT25DFX_UNIT_TEST_PAGE_SIZE, 
				page_num * AT25DFX_UNIT_TEST_PAGE_SIZE);

		for (i = 0; i < AT25DFX_UNIT_TEST_PAGE_SIZE; i++) {
			if (data_buff[i] != (i & 0xff)) {
				status = AT25_ERROR;
				break;
			}
		}

		page_num++;
	}

	/* Validate the SerialFlash write function */
	test_assert_true(test, status == AT25_SUCCESS, "Write operation failed!");
}

/**
 * \brief Run AT25DFx driver unit tests.
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits   = CONF_TEST_STOPBITS
	};

	/* Initialize the system clock and board */
	sysclk_init();
	board_init();

	/* Enable the debug uart */
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Define all the test cases */
	DEFINE_TEST_CASE(at25dfx_init_test, NULL, run_test_at25dfx_init, NULL,
			"SerialFlash initialize functions");

	DEFINE_TEST_CASE(at25dfx_protect_test, NULL, run_test_at25dfx_protect, NULL,
			"SerialFlash sector protect/unprotect, chip protect/unprotect functions");

	DEFINE_TEST_CASE(at25dfx_data_access_test, NULL, 
			run_test_at25dfx_data_access, NULL,
			"SerialFlash read, write, and block erase functions");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(at25dfx_tests) = {
		&at25dfx_init_test,
		&at25dfx_protect_test,
		&at25dfx_data_access_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(at25dfx_suite, at25dfx_tests, 
			"SAM AT25DFx driver test suite");

	/* Run all tests in the test suite */
	test_suite_run(&at25dfx_suite);

	while (1) {
		/* Busy-wait forever */
	}
}

