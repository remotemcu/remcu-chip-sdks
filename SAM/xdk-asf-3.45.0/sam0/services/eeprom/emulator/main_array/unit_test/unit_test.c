/**
 * \file
 *
 * \brief SAM EEPROM Emulator Service Unit test
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

/**
 * \mainpage SAM EEPROM Emulator Unit Test
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This unit test carries out tests for the EEPROM Emulator service.
 * It consists of test cases for the following functionalities:
 *      - Test for EEPROM emulator initialization.
 *      - Test for EEPROM emulator buffer read/write functionality.
 *      - Test for EEPROM emulator page read/write functionality.
 */

/**
 * \page appdoc_main SAM EEPROM Emulator Unit Test
 *
 * Overview:
 * - \ref appdoc_sam0_eeprom_emulator_unit_test_intro
 * - \ref appdoc_sam0_eeprom_emulator_unit_test_setup
 * - \ref appdoc_sam0_eeprom_emulator_unit_test_usage
 * - \ref appdoc_sam0_eeprom_emulator_unit_test_compinfo
 * - \ref appdoc_sam0_eeprom_emulator_unit_test_contactinfo
 *
 * \section appdoc_sam0_eeprom_emulator_unit_test_intro Introduction
 * \copydetails appdoc_preface
 *
 * The following kit is required for carrying out the test:
 *      - SAM D20 Xplained Pro board
 *      - SAM D21 Xplained Pro board
 *      - SAM R21 Xplained Pro board
 *      - SAM L21 Xplained Pro board
 *      - SAM L22 Xplained Pro board
 *      - SAM C21 Xplained Pro board
 *      - SAM DA1 Xplained Pro board
 *      - SAM HA1G16A Xplained Pro board
 *      - SAM R30 Xplained Pro board
 *
 * \section appdoc_sam0_eeprom_emulator_unit_test_setup Setup
 * The following connections has to be made using wires:
 *  - \b None
 *
 * The \c NVMCTRL_FUSES_EEPROM_SIZE has to be set to 0x00 in the fuse setting
 * of the device to run this test. Atmel Studio can be used to set this fuse
 * (Tools->Device Programming).
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
 * \section appdoc_sam0_eeprom_emulator_unit_test_usage Usage
 *  - The unit test first initializes the EEPROM emulator and formats the
 *    memory if not previously done.
 *  - The test writes a buffer of data to arbitrary offset and reads back
 *    and compares
 *  - The test then writes a page of data to a page and reads back and
 *    compares
 *
 * \section appdoc_sam0_eeprom_emulator_unit_test_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_eeprom_emulator_unit_test_contactinfo Contact Information
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

#define TEST_EEPROM_PAGE    1
#define TEST_BUFFER_SIZE    19
#define TEST_BUFFER_OFFSET  123

/* Structure for UART module connected to EDBG (used for unit test output) */
struct usart_module cdc_uart_module;
/* Structure to store EEPROM emulator parameters */
struct eeprom_emulator_parameters ee_params;

/* Data buffers used in test */
uint8_t test_buffer[TEST_BUFFER_SIZE];
uint8_t verify_buffer[TEST_BUFFER_SIZE];
uint8_t test_page[EEPROM_PAGE_SIZE];
uint8_t verify_page[EEPROM_PAGE_SIZE];
uint16_t i;

/* Flag used to check successful initialization */
volatile bool init_success;

/**
 * \brief Initialize the USART for unit test
 *
 * Initializes the SERCOM USART used for sending the unit test status to the
 * computer via the EDBG CDC gateway.
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
 * \internal
 * \brief Test for EEPROM emulator initialization.
 *
 * This test initializes the EEPROM emulator. If no memory was set
 * for EEPROM in the fuses then all test will be skipped.
 * During initialization it will format the EEPROM memory if it was
 * not done previously.
 *
 * It also checks the get parameter functionality.
 *
 * \param test Current test case.
 */
static void run_eeprom_init_test(const struct test_case *test)
{
	enum status_code status;
	init_success = true;

	/* Initialize the EEPROM emulator */
	status = eeprom_emulator_init();
	if (status == STATUS_ERR_NO_MEMORY) {
		init_success = false;
	}

	test_assert_true(test, init_success,
			"No EEPROM memory section has been set in the device's fuses");

	/* Format memory if needed */
	if (status != STATUS_OK) {
		eeprom_emulator_erase_memory();
		status = eeprom_emulator_init();
		if (status != STATUS_OK) {
			init_success = false;
		}
	}

	test_assert_true(test, status == STATUS_OK,
			"EEPROM emulator initialization failed");

	/* Get parameter check */
	status = eeprom_emulator_get_parameters(&ee_params);
	if (status != STATUS_OK) {
		init_success = false;
	}

	test_assert_true(test, status == STATUS_OK,
			"EEPROM parameter retrieve failed");
	test_assert_true(test, ee_params.page_size == EEPROM_PAGE_SIZE,
			"Get parameter returned wrong page size"
			"Expected %d - Returned %d", EEPROM_PAGE_SIZE,
			ee_params.page_size);
}

/**
 * \internal
 * \brief Setup function for EEPROM emulator buffer read/write test.
 *
 * This function initializes the test buffer and verify buffer with
 * appropriate values.
 *
 * \param test Current test case.
 */
static void setup_eeprom_buffer_read_write_test(const struct test_case *test)
{
	/* Initialize buffers */
	for (i = 0; i < TEST_BUFFER_SIZE; i++) {
		test_buffer[i] = i + 1;
		verify_buffer[i] = 0;
	}
}

/**
 * \internal
 * \brief Test for EEPROM emulator buffer read/write function.
 *
 * This test writes a buffer of data of a given length to a given
 * offset. It then reads back the data from that offset and verifies.
 *
 * \param test Current test case.
 */
static void run_eeprom_buffer_read_write_test(const struct test_case *test)
{
	volatile enum status_code status;

	/* Skip test if initialization failed */
	test_assert_true(test, init_success,
			"Skipping test due to failed initialization");

	/* Write buffer test */
	status = eeprom_emulator_write_buffer(TEST_BUFFER_OFFSET,
			test_buffer, TEST_BUFFER_SIZE);
	test_assert_true(test, status == STATUS_OK,
			"EEPROM write buffer failed");

	/* Write back to physical NVM memory */
	eeprom_emulator_commit_page_buffer();

	/* Read buffer test */
	status = eeprom_emulator_read_buffer(TEST_BUFFER_OFFSET,
			verify_buffer, TEST_BUFFER_SIZE);
	test_assert_true(test, status == STATUS_OK,
			"EEPROM read buffer failed");

	/* Verify buffer test */
	for (i = 0; i < TEST_BUFFER_SIZE; i++) {
		test_assert_true(test, test_buffer[i] == verify_buffer[i],
				"Buffer data incorrect at index %d: "
				"Expected %d - Read %d", i, test_buffer[i],
				verify_buffer[i]);
	}
}

/**
 * \internal
 * \brief Setup function for EEPROM emulator page read/write test.
 *
 * This function initializes the test_page and verify_page data arrays
 * with appropriate values.
 *
 * \param test Current test case.
 */
static void setup_eeprom_page_read_write_test(const struct test_case *test)
{
	/* Initialize data arrays */
	for (i = 0; i < EEPROM_PAGE_SIZE; i++) {
		test_page[i] = i + 1;
		verify_page[i] = 0;
	}
}

/**
 * \internal
 * \brief Test for EEPROM emulator page read/write function.
 *
 * This test writes a page of data to a given page number.
 * It then reads back the page and verifies.
 *
 * \param test Current test case.
 */
static void run_eeprom_page_read_write_test(const struct test_case *test)
{
	volatile enum status_code status;

	/* Skip test if initialization failed */
	test_assert_true(test, init_success,
			"Skipping test due to failed initialization");

	/* Write page test */
	status = eeprom_emulator_write_page(TEST_EEPROM_PAGE, test_page);
	test_assert_true(test, status == STATUS_OK,
			"EEPROM write page failed");

	/* Write back to physical NVM memory */
	eeprom_emulator_commit_page_buffer();

	/* Read page test */
	status = eeprom_emulator_read_page(TEST_EEPROM_PAGE, verify_page);
	test_assert_true(test, status == STATUS_OK,
			"EEPROM read page failed");

	/* Verify page test */
	for (i = 0; i < EEPROM_PAGE_SIZE; i++) {
		test_assert_true(test, test_page[i] == verify_page[i],
				"Page data incorrect at index %d: "
				"Expected %d - Read %d", i, test_page[i],
				verify_page[i]);
	}
}

/**
 * \brief Run EEPROM emulator unit tests
 *
 * Initializes the system and serial output, then sets up the
 * EEPROM emulator unit test suite and runs it.
 */
int main(void)
{
	system_init();
	cdc_uart_init();

	/* Define Test Cases */
	DEFINE_TEST_CASE(eeprom_init_test, NULL,
			run_eeprom_init_test, NULL,
			"Testing EEPROM emulator initialization");

	DEFINE_TEST_CASE(eeprom_buffer_read_write_test,
			setup_eeprom_buffer_read_write_test,
			run_eeprom_buffer_read_write_test, NULL,
			"Testing EEPROM buffer read/write functionality");

	DEFINE_TEST_CASE(eeprom_page_read_write_test,
			setup_eeprom_page_read_write_test,
			run_eeprom_page_read_write_test, NULL,
			"Testing EEPROM page read/write functionality");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(eeprom_tests) = {
		&eeprom_init_test,
		&eeprom_buffer_read_write_test,
		&eeprom_page_read_write_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(eeprom_test_suite, eeprom_tests,
			"SAM EEPROM emulator service test suite");

	/* Run all tests in the suite*/
	test_suite_run(&eeprom_test_suite);

	while (true) {
		/* Intentionally left empty */
	}
}
