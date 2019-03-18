/**
 * \file
 *
 * \brief Unit tests for flashcalw driver.
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
#include "conf_test.h"

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the flashcalw driver.
 * It consists of test cases for the following functionalities:
 * - Get properties
 * - Control test
 * - Protection test
 * - Page access and command contro test
 * - General purpose fuses test
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_uart_serial.h
 *
 * \section device_info Device Info
 * All SAM devices with FLASHCALW controller can be used.
 * This example has been tested with the following setup:
 * - sam4l4c_sam4l_ek
 * - sam4l4c_sam4l_xplained_pro
 * - sam4l8c_sam4l8_xplained_pro
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
 * \brief Test the functions provided by the flashcalw driver.
 */
//@}

#define FLASHCALW_TEST_PAGE_NUM    (FLASH_SIZE / FLASH_PAGE_SIZE - 16)
#define FLASHCALW_ALL_REGION_LOCK   (0xffff)
#define GP_FUSE_BIT_POS    (20)
#define GP_FUSE_BITFIELD_POS    (28)
#define GP_FUSE_BITFIELD_WIDTH    (16)
#define GP_FUSE_BITFIELD_DATA    (0x1234)
#define GP_FUSE_BYTE_NUM    (5)
#define GP_FUSE_BYTE_DATA   (0x5a)
#define GP_FUSE_ALL_DATA   (0xFFFF12345678FFFFULL)

/**
 *  Configure serial console.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
#ifdef CONF_UART_CHAR_LENGTH
		.charlength = CONF_UART_CHAR_LENGTH,
#endif
		.paritytype = CONF_UART_PARITY,
#ifdef CONF_UART_STOP_BITS
		.stopbits = CONF_UART_STOP_BITS,
#endif
	};

	/* Configure console UART. */
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief Test flashcalw preperties interfaces.
 *
 * This test gets the flashcalw size of the flashcalw. Other properties
 * interfaces are based this function.
 *
 * \param test Current test case.
 */
static void run_flashcalw_properties_test(const struct test_case *test)
{
	uint32_t rc;

	/* Read flashcalw size */
	rc = flashcalw_get_flash_size();

	/* Validate the get flashcalw size function */
	test_assert_true(test, rc == FLASH_SIZE,
		"Test get flashcalw properties: flashcalw read size error!");
}

/**
 * \brief Test flashcalw configure functions.
 *
 * This test gets the default wait state first, then it will reset the wait
 * state and validate the result.
 *
 * \param test Current test case.
 */
static void run_flashcalw_control_test(const struct test_case *test)
{
	uint32_t default_ws;
	uint32_t tmp_ws;

	/* Backup default wait state */
	default_ws = flashcalw_get_wait_state();

	/* Set the reversed wait state */
	flashcalw_set_wait_state(default_ws ? 0 : 1);

	/* Get the wait state set */
	tmp_ws = flashcalw_get_wait_state();

	/* Validate the flashcalw set wait state function */
	test_assert_true(test, tmp_ws == (default_ws ? 0 : 1),
		"Test flashcalw control: flashcalw set wait state error!");

	/*Restore default wait state */
	flashcalw_set_wait_state(default_ws);
}

/**
 * \brief Test flashcalw protection.
 *
 * This test backups the region protection status, then validates the 3 types of
 * region protection interface and restores the default protection status.
 *
 * \param test Current test case.
 */
static void run_flashcalw_protection_test(const struct test_case *test)
{
	uint32_t region_num;
	uint32_t region_lock_status = 0;
	uint32_t default_region_lock_status = 0;
	uint32_t i;

	/* Backup the flashcalw protection status */
	for (i = 0; i < FLASH_NB_OF_REGIONS; i++) {
		if (flashcalw_is_region_locked(i)) {
			default_region_lock_status |= 1 << i;
		}
	}

	/* Lock all regions */
	flashcalw_lock_all_regions(true);

	/* Get all region protection status */
	for (i = 0; i < FLASH_NB_OF_REGIONS; i++) {
		if (flashcalw_is_region_locked(i)) {
			region_lock_status |= 1 << i;
		}
	}

	/* Validate the protect all regions function */
	test_assert_true(test, ((region_lock_status & FLASHCALW_ALL_REGION_LOCK)
		== FLASHCALW_ALL_REGION_LOCK),
		"Test flashcalw protection: lock all regions error!");

	/* Unlock all regions */
	flashcalw_lock_all_regions(false);

	/* Get all region protection status */
	region_lock_status = 0;
	for (i = 0; i < FLASH_NB_OF_REGIONS; i++) {
		if (flashcalw_is_region_locked(i)) {
			region_lock_status |= 1 << i;
		}
	}

	/* Validate the unlock all regions function */
	test_assert_true(test, (region_lock_status == 0),
		"Test flashcalw protection: unlock all regions error!");

	/* Lock region through page number */
	flashcalw_lock_page_region(FLASHCALW_TEST_PAGE_NUM, true);

	/* Get page lock status */
	region_lock_status =
		flashcalw_is_page_region_locked
		(FLASHCALW_TEST_PAGE_NUM);

	/* Validate the get region count function */
	test_assert_true(test, region_lock_status,
		"Test flashcalw protection: page region lock operation error!");

	/* Unlock region through page number */
	flashcalw_lock_page_region(FLASHCALW_TEST_PAGE_NUM, false);

	/* Get region number through page number */
	region_num = flashcalw_get_page_region(FLASHCALW_TEST_PAGE_NUM);

	/* Lock region through region number */
	flashcalw_lock_region(region_num, true);

	/* Get region lock status */
	region_lock_status = flashcalw_is_region_locked(region_num);

	/* Validate the lock region through region number function */
	test_assert_true(test, region_lock_status,
		"Test flashcalw protection: region lock operation error!");

	/* Restore default region protection status */
	for (i = 0; i < FLASH_NB_OF_REGIONS; i++) {
		if (default_region_lock_status & 0x1) {
			flashcalw_lock_page_region(i, true);
			default_region_lock_status >>= 1;
		}
	}
}

/**
 * \brief Test flashcalw page access and get flashcalw command interfaces.
 *
 * This test tests the flashcalw memset and memcpy function in the specific page
 * of the flash. The flashcalw command control interfaces will be also
 * validated.
 *
 * \param test Current test case.
 */
static void run_flashcalw_page_access_test(const struct test_case *test)
{
	uint32_t page_buffer[FLASH_PAGE_SIZE / sizeof(uint32_t)];
	volatile uint32_t page_addr = FLASH_ADDR +
		FLASH_PAGE_SIZE * FLASHCALW_TEST_PAGE_NUM;
	volatile uint32_t *last_page = (volatile uint32_t *)page_addr;
	uint32_t command;
	uint32_t rc = 0;
	uint32_t idx;

	/* Unlock the test page */
	flashcalw_lock_page_region(FLASHCALW_TEST_PAGE_NUM, false);

	/* Memset the test page */
	flashcalw_memset((void *)page_addr, 0x0, 8, FLASH_PAGE_SIZE, true);

	/* Get the last command issued in the flashcalw */
	command = flashcalw_get_command();

	/* The last issued command should be write page as it's setting the page
	 * to 0x0 */
	test_assert_true(test, command == FLASHCALW_FCMD_CMD_WP,
			"Test flashcalw page access: flashcalw get command error!");

	/* Validate page contents */
	for (idx = 0; idx < (FLASH_PAGE_SIZE / 4); idx++) {
		if (last_page[idx] != 0) {
		rc = 1;
		}
	}

	/* Validate the flashcalw memset function */
	test_assert_true(test, rc == 0,
		"Test flashcalw page access: flashcalw page memset error!");

	/* Write the test page with walking bit pattern */
	for (idx = 0; idx < (FLASH_PAGE_SIZE / 4); idx++) {
		page_buffer[idx] = 1 << (idx % 32);
	}

	flashcalw_memcpy((void volatile *)page_addr, page_buffer,
		FLASH_PAGE_SIZE, true);

	/* Validate page contents */
	for (idx = 0; idx < (FLASH_PAGE_SIZE / 4); idx++) {
		if (last_page[idx] != page_buffer[idx]) {
			rc = 1;
		}
	}

	/* Validate the flashcalw write function */
	test_assert_true(test, rc == 0,
		"Test flashcalw page access: flashcalw page write error!");
}

/**
 * \brief Test flashcalw general purpose fuse interface group.
 *
 * This test tests the gp fuse read, write and erase functions,
 * including bit, bitfield, byte and all fuses groups.
 *
 * \param test Current test case.
 */
static void run_flashcalw_gp_fuse_test(const struct test_case *test)
{
	/* Test and validate erase all gp fuse function */
	test_assert_true(test, flashcalw_erase_all_gp_fuses(true),
		"Test flashcalw gp_fuse: gp_fuse erase all error!");

	/* Test the gp fuse bit write operations */
	flashcalw_write_gp_fuse_bit(GP_FUSE_BIT_POS, true);

	/* Validate the gp fuse bit write operation */
	test_assert_true(test, flashcalw_read_gp_fuse_bit(GP_FUSE_BIT_POS),
		"Test flashcalw gp_fuse: gp_fuse bit read/write error!");

	/* Test and validate the gp fuse erase function */
	test_assert_true(test, flashcalw_erase_gp_fuse_bit(GP_FUSE_BIT_POS,
		true), "Test flashcalw gp_fuse: gp_fuse bit erase operation error!");

	/* Test the gp fuse bitfield write operation */
	flashcalw_write_gp_fuse_bitfield(GP_FUSE_BITFIELD_POS,
		GP_FUSE_BITFIELD_WIDTH, GP_FUSE_BITFIELD_DATA);

	/* Read and validate the test bitfield */
	test_assert_true(test,
		flashcalw_read_gp_fuse_bitfield(GP_FUSE_BITFIELD_POS,
		GP_FUSE_BITFIELD_WIDTH) == GP_FUSE_BITFIELD_DATA,
		"Test flashcalw gp_fuse: gp_fuse bitfield read/write error!");

	/* Validate the bitfield erase function */
	test_assert_true(test,
		flashcalw_erase_gp_fuse_bitfield(GP_FUSE_BITFIELD_POS,
		GP_FUSE_BITFIELD_WIDTH, true),
		"Test flashcalw gp_fuse: gp_fuse erase bitfield operation error!");

	/* Test the gp fuse byte write operation */
	flashcalw_write_gp_fuse_byte(GP_FUSE_BYTE_NUM, GP_FUSE_BYTE_DATA);

	/* Read and validate the test byte */
	test_assert_true(test,
		flashcalw_read_gp_fuse_byte(GP_FUSE_BYTE_NUM) ==
		GP_FUSE_BYTE_DATA,
		"Test flashcalw gp_fuse: gp_fuse byte read/write error!");

	/* Validate the byte erase function */
	test_assert_true(test,
		flashcalw_erase_gp_fuse_byte(GP_FUSE_BYTE_NUM, true),
		"Test flashcalw gp_fuse: gp_fuse erase byte operation error!");

	/* Test the gp fuse write all operation */
	flashcalw_write_all_gp_fuses(GP_FUSE_ALL_DATA);

	/* Read and validate the test all interface */
	test_assert_true(test,
		flashcalw_read_all_gp_fuses() == GP_FUSE_ALL_DATA,
		"Test flashcalw gp_fuse: gp_fuse read/write all error!");

	/* Clear all fuses */
    flashcalw_erase_all_gp_fuses(true);
}

/** Counts for 1ms time ticks. */
volatile uint32_t g_ms_ticks = 0;

/** Fibonacci number */
#define FIBONACCI_NUM    20
#define TICK_US 1000

/**
 *  \brief Recursively calculate the nth Fibonacci number.
 *
 * \param n Indicates which (positive) Fibonacci number to compute.
 *
 * \return The nth Fibonacci number.
 */
static uint32_t recfibo(uint32_t n)
{
	if (n == 0 || n == 1) {
		return n;
	}

	return recfibo(n - 2) + recfibo(n - 1);
}

/**
 * \brief Handler for Sytem Tick interrupt.
 *
 * Process System Tick Event
 * Increments the g_ms_ticks counter.
 */
void SysTick_Handler(void)
{
	g_ms_ticks++;
}

static uint32_t time_tick_get(void)
{
	return g_ms_ticks;
}

static uint32_t time_tick_calc_delay(uint32_t tick_start, uint32_t tick_end)
{
	if (tick_end >= tick_start) {
		return (tick_end - tick_start) * (1000 / TICK_US);
	} else {
		/* In the case of 32-bit couter number overflow */
		return (tick_end +
			(0xFFFFFFFF - tick_start)) * (1000 / TICK_US);
	}
}

/**
 * \brief Test flashcalw PicoCache feature.
 *
 * PicoCache test shows how much the PicoCache feature can improve the
 * execution speed.
 *
 * \param test Current test case.
 */
static void run_flashcalw_picocache_test(const struct test_case *test)
{
	uint32_t tick_start, time_ms_nocache, time_ms_cache;

	flashcalw_set_wait_state(1);
	/* Disable PicoCache */
	flashcalw_picocache_disable();
	flashcalw_picocache_disable_monitor();

	/* Get current time tick */
	tick_start = time_tick_get();

	/* Do the Fibonacci calculation. */
	recfibo(FIBONACCI_NUM);

	/* Calculate the Fibonacci spent time */
	time_ms_nocache = time_tick_calc_delay(tick_start, time_tick_get());

	/* Enable PicoCache */
	flashcalw_picocache_enable();

	/* Get current time tick */
	tick_start = time_tick_get();

	/* Do the Fibonacci calculation. */
	recfibo(FIBONACCI_NUM);

	/* Calculate the Fibonacci spent time */
	time_ms_cache = time_tick_calc_delay(tick_start, time_tick_get());

	test_assert_true(test,
		time_ms_nocache > time_ms_cache,
		"Test flashcalw PicoCache: PicoCache feature does not work!");
}

/**
 * \brief main function : do init and loop (poll if configured so).
 */
int main(void)
{
	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	g_ms_ticks = 0;

	/* Configure systick */
	if (SysTick_Config(sysclk_get_cpu_hz() / TICK_US)) {
		Assert(false);
	}

	/* Initialize the console uart */
	configure_console();

	/* Define all the test cases */
	DEFINE_TEST_CASE(flashcalw_properties_test, NULL,
		run_flashcalw_properties_test, NULL,
		"flashcalw get properties test");

	DEFINE_TEST_CASE(flashcalw_control_test, NULL,
		run_flashcalw_control_test, NULL,
		"flashcalw control test");

	DEFINE_TEST_CASE(flashcalw_protection_test, NULL,
		run_flashcalw_protection_test, NULL,
		"flashcalw protection test");

	DEFINE_TEST_CASE(flashcalw_gp_fuse_test, NULL,
		run_flashcalw_gp_fuse_test, NULL,
		"flashcalw general purpose fuses test");

	DEFINE_TEST_CASE(flashcalw_page_access_test, NULL,
		run_flashcalw_page_access_test, NULL,
		"flashcalw page access test");

	DEFINE_TEST_CASE(flashcalw_picocache_test, NULL,
		run_flashcalw_picocache_test, NULL,
		"flashcalw picocache test");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(flashcalw_suite_array) = {
		&flashcalw_page_access_test,
		&flashcalw_properties_test,
		&flashcalw_control_test,
		&flashcalw_protection_test,
		&flashcalw_gp_fuse_test,
		&flashcalw_picocache_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(flashcalw_suite, flashcalw_suite_array,
		"flashcalw driver test suite");

	/* Run all tests in the test suite */
	test_suite_run(&flashcalw_suite);

	while (1) {
		/* Busy-wait forever */
	}
}
