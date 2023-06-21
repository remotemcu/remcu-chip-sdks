/**
 * \file
 *
 * \brief Unit tests for NAND Flash component.
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
#include <asf.h>
#include <board.h>
#include <sysclk.h>
#include "nand_flash_raw.h"
#include "nand_flash_ecc.h"
#include <string.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <conf_test.h>
#include <conf_board.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the NAND Flash component.
 * It consists of test cases for the following functionality:
 * - read flash ID
 * - raw data read/write
 * - data read/write with software ecc
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 *
 * \section device_info Device Info
 * SAM3S,U,X devices can be used.
 * This example has been tested with the following setup:
 * - sam3s4c_sam3s_ek
 * - sam3sd8c_sam3s_ek2
 * - sam3u4e_sam3u_ek
 * - sam3x8h_sam3x_ek
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

/* Number of blocks in NAND Flash. */
static uint32_t num_block;
/* Size of one page in the NAND Flash, in bytes. */
static uint32_t page_size;

/* NAND Flash raw structure. */
static struct nand_flash_raw nf_raw;
/* Address for transferring command to the NAND Flash. */
static uint32_t cmd_address = BOARD_NF_COMMAND_ADDR;
/* Address for transferring address to the NAND Flash. */
static uint32_t addr_address = BOARD_NF_ADDRESS_ADDR;
/* Address for transferring data to the NAND Flash. */
static uint32_t data_address = BOARD_NF_DATA_ADDR;

/* NAND Flash ecc structure. */
static struct nand_flash_ecc nf_ecc;

/* Temporary buffer */
static uint8_t write_buffer[2048];
static uint8_t read_buffer[2048];
static uint8_t spare_buffer[NAND_COMMON_MAX_PAGE_SPARE_SIZE];

volatile uint32_t error_code;
volatile uint32_t flash_id;
volatile uint32_t block;

/**
 * \brief Test NAND Flash initialization
 *
 * This test call the initialization function and check the flash id.
 *
 * \param test Current test case.
 */
static void run_test_initialization(const struct test_case *test)
{
	/* Test1: Check the initialize function */
	error_code = nand_flash_raw_initialize(&nf_raw, 0, cmd_address,
			addr_address, data_address);
	test_assert_true(test, error_code == 0,
			"NAND Flash initialization failed!");

	/* Get device parameters */
	num_block = nand_flash_model_get_device_size_in_blocks(&nf_raw.model);
	page_size = nand_flash_model_get_page_data_size(&nf_raw.model);

	nf_ecc.raw = nf_raw;

	/* Check the flash ID */
	flash_id = nand_flash_raw_read_id(&nf_raw);
#if (SAM3XA || SAM3S)
	test_assert_true(test, flash_id == 0x9580DA2C,
		"NAND Flash ID error!");
#endif
#if SAM3U
	test_assert_true(test, flash_id == 0xD580CA2C,
		"NAND Flash ID error!");
#endif
#if UC3A3
	test_assert_true(test, flash_id == 0x1580DA2C,
		"NAND Flash ID error!");
#endif

}

/**
 * \brief Test raw read/write functions
 *
 * This test call the raw read/write functions and check the data value.
 *
 * \param test Current test case.
 */
static void run_test_raw_read_write(const struct test_case *test)
{
	uint32_t i;

	/* Erase block and use the first good block for read/write test */
	for (block = (num_block / 2); block > 0; block--) {
		error_code = nand_flash_raw_erase_block(&nf_raw, block);
		if (!error_code) {
			break;
		}
	}
	/* Check the erase result */
	test_assert_true(test, block != 0,
			"All block erase failed!");

	/* Reset read buffer. */
	memset(read_buffer, 0, sizeof(read_buffer));

	/* Read the first page from the erased block of NAND Flash. */
	nand_flash_raw_read_page(&nf_raw, block, 0, read_buffer, 0);
	/* Check data content of the erase result. */
	for (i = 0; i < page_size; i++) {
		if (read_buffer[i] != 0xFF) {
			error_code = 1;
			break;
		}
	}
	test_assert_true(test, error_code == 0,
			"The content of the block erase result error!");

	/* Prepare a page size buffer in SRAM. */
	for (i = 0; i < page_size; i++) {
		write_buffer[i] = i & 0xFF;
	}

	/* Reset read buffer. */
	memset(read_buffer, 0, sizeof(read_buffer));

	/* Write a page to the NAND Flash. */
	error_code = nand_flash_raw_write_page(&nf_raw, block, 0, write_buffer,
			0);
	/* Read the page from the NAND Flash. */
	nand_flash_raw_read_page(&nf_raw, block, 0, read_buffer, 0);

	/* Test if the read buffer is the same as SRAM buffer */
	error_code = memcmp(read_buffer, write_buffer, sizeof(write_buffer));

	/* Check the erase result */
	test_assert_true(test, error_code == 0,
			"The raw read/write functions test failed!");

}

/**
 * \brief Test software ECC read/write functions
 *
 * This test call the software ECC read/write functions and check the data value.
 *
 * \param test Current test case.
 */
static void run_test_software_ecc(const struct test_case *test)
{
	uint32_t i;

	/* Erase block and use the first good block for read/write test */
	for (block = (num_block / 2); block > 0; block--) {
		error_code = nand_flash_raw_erase_block(&nf_raw, block);
		if (!error_code) {
			break;
		}
	}
	/* Check the erase result */
	test_assert_true(test, block != 0,
			"All block erase failed!");

	/* Reset read buffer. */
	memset(read_buffer, 0, sizeof(read_buffer));

	/* Read the first page from the erased block of NAND Flash. */
	nand_flash_raw_read_page(&nf_raw, block, 0, read_buffer, 0);
	/* Check data content of the erase result. */
	for (i = 0; i < page_size; i++) {
		if (read_buffer[i] != 0xFF) {
			error_code = 1;
			break;
		}
	}
	test_assert_true(test, error_code == 0,
			"The content of the block erase result error!");

	/* Prepare a page size buffer in SRAM. */
	for (i = 0; i < page_size; i++) {
		write_buffer[i] = i & 0xFF;
	}

	/* Reset read buffer. */
	memset(read_buffer, 0, sizeof(read_buffer));

	/* Write a page to the NAND Flash. */
	error_code = nand_flash_ecc_write_page(&nf_ecc, block, 0, write_buffer,
				spare_buffer);
	/* Read the page from the NAND Flash. */
	nand_flash_ecc_read_page(&nf_ecc, block, 0, read_buffer, spare_buffer);

	/* Test if the read buffer is the same as SRAM buffer */
	error_code = memcmp(read_buffer, write_buffer, sizeof(write_buffer));

	/* Check the erase result */
	test_assert_true(test, error_code == 0,
			"The software ECC read/write functions test failed!");

	/* Erase all blocks to clean the NAND Flash. */
	for (i = 0; i < num_block; i++) {
		nand_flash_raw_erase_block(&nf_raw, i);
	}
}


/**
 * \brief Run NAND Flash component unit tests
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

#if SAM
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
#else
	sysclk_enable_hsb_module(SYSCLK_EBI);
	sysclk_enable_pbb_module(SYSCLK_SMC_REGS);
	sysclk_enable_pbb_module(SYSCLK_HMATRIX);
#endif

	board_init();

	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Define all the test cases */
	DEFINE_TEST_CASE(nand_flash_test_read_id, NULL, run_test_initialization, NULL,
			"NAND Flash initialization and id test");
	DEFINE_TEST_CASE(nand_flash_test_raw_read_write, NULL,
			run_test_raw_read_write, NULL,
			"NAND Flash raw data read/write test");
	DEFINE_TEST_CASE(nand_flash_test_software_ecc, NULL,
			run_test_software_ecc, NULL,
			"NAND Flash data read/write with software ECC test");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(nand_flash_test_array) = {
		&nand_flash_test_read_id,
		&nand_flash_test_raw_read_write,
		&nand_flash_test_software_ecc,};

	/* Define the test suite */
	DEFINE_TEST_SUITE(nand_flash_suite, nand_flash_test_array,
			"NAND Flash component test suite");

	/* Run all tests in the test suite */
	test_suite_run(&nand_flash_suite);

	while (1) {
		/* Busy-wait forever. */
	}
}
