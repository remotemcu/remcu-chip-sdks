/**
 * \file
 *
 * \brief SAM NVM Unit test
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
 * \mainpage SAM NVM Unit Test
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This unit test carries out tests for NVM driver.
 * It consists of test cases for the following functionalities:
 *  - Test for driver initialization.
 *  - Test for NVM parameter retrieval.
 *  - Test for FLASH row erasure.
 *  - Test for FLASH page read and write.
 *  - Test for FLASH partial page update.
 */

/**
 * \page appdoc_main SAM NVM Unit Test
 *
 * Overview:
 * - \ref appdoc_sam0_nvm_unit_test_intro
 * - \ref appdoc_sam0_nvm_unit_test_setup
 * - \ref appdoc_sam0_nvm_unit_test_usage
 * - \ref appdoc_sam0_nvm_unit_test_compinfo
 * - \ref appdoc_sam0_nvm_unit_test_contactinfo
 *
 * \section appdoc_sam0_nvm_unit_test_intro Introduction
 * \copydetails appdoc_preface
 *
 * The following kit can be used for carrying out the test:
 *  - SAM D20 Xplained Pro board
 *  - SAM D21 Xplained Pro board
 *  - SAM R21 Xplained Pro board
 *  - SAM L21 Xplained Pro board
 *  - SAM L22 Xplained Pro board
 *  - SAM DA1 Xplained Pro board
 *  - SAM HA1G16A Xplained Pro board
 *  - SAM R30 Xplained Pro board
 *  - SAM R30 Module Xplained Pro board
 *  - SAM R34 Xplained Pro board
 *
 * \section appdoc_sam0_nvm_unit_test_setup Setup
 * The following connections has to be made using wires:
 *  - None
 *
 * To run the test:
 *  - Connect the SAM Xplained Pro board to the computer using a
 *    micro USB cable.
 *  - Open the virtual COM port in a terminal application.
 *    \note The USB composite firmware running on the Embedded Debugger (EDBG)
 *          will enumerate as debugger, virtual COM port and EDBG data
 *          gateway.
 *  - Build the project, program the target and run the application.
 *    The terminal shows the results of the unit test.
 *
 * \section appdoc_sam0_nvm_unit_test_usage Usage
 *  - The unit tests are carried out using the internal NVM controller.
 *
 * \section appdoc_sam0_nvm_unit_test_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_nvm_unit_test_contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com">http://www.microchip.com</a>.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <stdio_serial.h>
#include <string.h>
#include "conf_test.h"

/**
 * \brief Generates byte pattern 1 for a given address
 */
#define BYTE_PATTERN1(x) ((uint8_t)(((x) * 5 + 1) & 0xff))

/**
 * \brief Generates byte pattern 2 for a given address
 */
#define BYTE_PATTERN2(x) \
	((uint8_t)(((x) * 3) & 0xff))

/* Test page is set to 8th from last */
#define TEST_PAGE_ADDR     (FLASH_NB_OF_PAGES - 8) * NVMCTRL_PAGE_SIZE

/* Flag to indicate NVM initialization status */
static volatile bool nvm_init_success = false;

/* Structure for UART module connected to EDBG (used for unit test output) */
struct usart_module cdc_uart_module;

/**
 * \brief Test get flash parameter function
 *
 * This test gets the nvm parameters from the function and checks the
 * NVM page count and NVM page size
 *
 * \param test Current test case.
 */
static void run_nvm_parameter_test(const struct test_case *test)
{
	struct nvm_parameters parameters;

	/* Get the NVM parameters */
	nvm_get_parameters(&parameters);

	/* Validate the page size */
	test_assert_true(test, parameters.page_size == NVMCTRL_PAGE_SIZE,
			"Pagesize incorrect (read: 0x%02x,"
			" expected: 0x%02x)", parameters.page_size,
			NVMCTRL_PAGE_SIZE);

	/* Validate the page count */
	test_assert_true(test, parameters.nvm_number_of_pages == FLASH_NB_OF_PAGES,
			"Number of Pages incorrect (read: 0x%02x,"
			" expected: 0x%02x)", parameters.nvm_number_of_pages,
			FLASH_NB_OF_PAGES);
}

/**
 * \brief Test NVM initialization
 *
 * This function will write the default configuration to NVM
 * and returns an error in case of failure.
 *
 * \param test Current test case.
 */
static void run_nvm_init_test(const struct test_case *test)
{
	struct nvm_config config;
	enum status_code status;

	/* Get the default configuration */
	nvm_get_config_defaults(&config);

	/* Set wait state to 1 */
	config.wait_states = 1;

	/* Enable automatic page write mode */
	config.manual_page_write = false;

	/* Set the NVM configuration */
	status = nvm_set_config(&config);

	/* Validate the initialization */
	test_assert_true(test, status == STATUS_OK,
			"NVM Initialization error");

	if (status == STATUS_OK) {
		nvm_init_success = true;
	}
}

/**
 * \brief Test NVM erasing
 *
 * This test erases test row and verifies it
 *
 * \param test Current test case.
 */
static void run_nvm_erase_test(const struct test_case *test)
{
	uint16_t offset = 0;
	volatile uint32_t test_page_address;
	test_page_address = TEST_PAGE_ADDR;
	volatile uint32_t *test_address;
	test_address = (uint32_t *) test_page_address;
	enum status_code status;

	/* Skip test if NVM initialization failed */
	test_assert_true(test, nvm_init_success == true,
			"NVM initialization failed, skipping test");

	/* Erase the row at test address */
	status = nvm_erase_row(test_page_address);

	/* Validate erase operation is complete */
	test_assert_true(test, status == STATUS_OK,
			"Erase operation not completed");

	/* Validate whether the data in NVM is 0xff after erasing */
	for (offset  = 0; offset < ((NVMCTRL_ROW_PAGES * NVMCTRL_PAGE_SIZE) / 4);
			offset++) {
		test_assert_true(test, ((uint32_t)test_address[offset]) == 0xffffffff,
				"Flash erase error @ %d offset", offset);
	}
}

/**
 * \brief Test NVM writing
 *
 * This test writes erased test page with a pattern, reads it back
 * and checks the integrity
 *
 * \param test Current test case.
 */
static void run_nvm_read_and_write_test(const struct test_case *test)
{
	uint8_t buffer[NVMCTRL_PAGE_SIZE], i;
	enum status_code status;

	/* Skip test if NVM initialization failed */
	test_assert_true(test, nvm_init_success == true,
			"NVM initialization failed, skipping test");

	/* Fill the buffer with Pattern 1 */
	for (i = 0; i < NVMCTRL_PAGE_SIZE; i++) {
		buffer[i] = BYTE_PATTERN1(i);
	}

	/* Write the buffer to Test address in NVM */
	status = nvm_write_buffer(TEST_PAGE_ADDR, buffer, NVMCTRL_PAGE_SIZE);

	/* Validate whether write operation is complete */
	test_assert_true(test, status == STATUS_OK,
			"Write operation error");

	/* Flush the buffer */
	for (i = 0; i < NVMCTRL_PAGE_SIZE; i++) {
		buffer[i] = 0;
	}

	/* Read the NVM contents at test address to buffer */
	status = nvm_read_buffer(TEST_PAGE_ADDR, buffer, NVMCTRL_PAGE_SIZE);

	/* Validate whether read operation is complete */
	test_assert_true(test, status == STATUS_OK,
			"Read operation error");

	/* Check the integrity of data in NVM */
	for (i = 0; i < NVMCTRL_PAGE_SIZE; i++) {
		test_assert_true(test, buffer[i] == BYTE_PATTERN1(i),
			"Value not expected @ byte %d (read: 0x%02x,"
			" expected: 0x%02x)", i, buffer[i], BYTE_PATTERN1(i));
	}
 }

/**
 * \brief Test NVM update
 *
 * This test modifies first half of the test page with different pattern,
 * reads it back and checks whether the values are updated
 *
 * \param test Current test case.
 */
static void run_nvm_update_test(const struct test_case *test)
{
	uint8_t buffer[NVMCTRL_PAGE_SIZE], i;
	enum status_code status;

	/* Skip test if NVM initialization failed */
	test_assert_true(test, nvm_init_success == true,
			"NVM initialization failed, skipping test");

	/* Fill half of the buffer with pattern 2 */
	for (i = 0; i < (NVMCTRL_PAGE_SIZE / 2); i++) {
		buffer[i] = BYTE_PATTERN2(i);
	}

	/* Update first half of the test page with new data */
	status = nvm_update_buffer(TEST_PAGE_ADDR, buffer, 0,
		(NVMCTRL_PAGE_SIZE / 2));

	/* Validate whether the update operation is complete */
	test_assert_true(test, status == STATUS_OK,
			"Update operation error");

	/* Flush the buffer */
	for (i = 0; i < NVMCTRL_PAGE_SIZE; i++) {
		buffer[i] = 0;
	}

	/* Read the NVM contents at test address to buffer */
	status = nvm_read_buffer(TEST_PAGE_ADDR, buffer, NVMCTRL_PAGE_SIZE);

	/* Validate whether the read operation is complete */
	test_assert_true(test, status == STATUS_OK,
			"Read operation error");

	/* Check the integrity of data in NVM */
	for (i = 0; i < (NVMCTRL_PAGE_SIZE / 2); i++) {
		test_assert_true(test, buffer[i] == BYTE_PATTERN2(i),
				"Value not expected @ byte %d (read: 0x%02x,"
				" expected: 0x%02x)", i, buffer[i], BYTE_PATTERN2(i));
	}
	for (i = (NVMCTRL_PAGE_SIZE / 2); i < NVMCTRL_PAGE_SIZE; i++) {
		test_assert_true(test, buffer[i] == BYTE_PATTERN1(i),
				"Value not expected @ byte %d (read: 0x%02x,"
				" expected: 0x%02x)", i, buffer[i], BYTE_PATTERN1(i));
	}
}

/**
 * \brief Initialize USART for unit tests
 *
 * Initializes the USART used by the unit test. The USART connected to
 * embedded debugger is used for outputting the results.
 *
 */
static void cdc_uart_init(void)
{
	struct usart_config usart_conf;

	/* Configure USART for unit test output */
	usart_get_config_defaults(&usart_conf);
	usart_conf.mux_setting = CONF_STDIO_MUX_SETTING;
	usart_conf.pinmux_pad0 = CONF_STDIO_PINMUX_PAD0;
	usart_conf.pinmux_pad1 = CONF_STDIO_PINMUX_PAD1;
	usart_conf.pinmux_pad2 = CONF_STDIO_PINMUX_PAD2;
	usart_conf.pinmux_pad3 = CONF_STDIO_PINMUX_PAD3;
	usart_conf.baudrate    = CONF_STDIO_BAUDRATE;

	stdio_serial_init(&cdc_uart_module, CONF_STDIO_USART, &usart_conf);
	usart_enable(&cdc_uart_module);
}

/**
 * \brief Run NVM unit tests
 *
 * Initializes the system and serial output, then sets up the
 * NVM unit test suite and runs it.
 */
int main(void)
{
	system_init();
	cdc_uart_init();

	/* Define Test Cases */
	DEFINE_TEST_CASE(nvm_paramter_test, NULL,
			run_nvm_parameter_test, NULL,
			"NVM parameter check");

	DEFINE_TEST_CASE(nvm_init_test, NULL,
			run_nvm_init_test, NULL,
			"NVM initialization");

	DEFINE_TEST_CASE(nvm_erase_test, NULL,
			run_nvm_erase_test, NULL,
			"NVM erase row");

	DEFINE_TEST_CASE(nvm_read_and_write_test, NULL,
			run_nvm_read_and_write_test, NULL,
			"NVM page read and write");

	DEFINE_TEST_CASE(nvm_update_test, NULL,
			run_nvm_update_test, NULL,
			"NVM page update");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(nvm_tests) = {
			&nvm_paramter_test,
			&nvm_init_test,
			&nvm_erase_test,
			&nvm_read_and_write_test,
			&nvm_update_test,
			};

	/* Define the test suite */
	DEFINE_TEST_SUITE(nvm_suite, nvm_tests,
			"SAM NVM driver test suite");

	/* Run all tests in the suite*/
	test_suite_run(&nvm_suite);

	while (1) {
		/* Intentionally left empty */
	}

}
