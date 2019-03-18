/**
 * \file
 *
 * \brief Memory bag allocator
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
 * \mainpage Memory Bag allocator unit test
 *
 * \par Purpose
 *
 * A set of unit tests to check each feature of the membag module
 *
 * \par Behavior: executing each unit test in turn
 *
 * -# Check that the Membag is initialized and re-initialized correctly.
 * -# Check that the Membag allocates small and large chunks of memory
 *  correctly, and fails when a chunk that is too large is requested.
 * -# Check that the Membag frees previously allocated memory correctly
 * -# Check that the Membag functions to determine memory status work correctly.
 * -# Check that the Membag allocations fail once all suitable bags are already
 *  allocated.
 * -# Check that the Membag re-allocates previously allocated and subsequently
 *  freed blocks of memory correctly.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include "conf_test.h"

/** Unit test to check that the Membag is initialized and re-initialized
 *  correctly.
 *
 *  \param test  Pointer to the unit test case instance
 */
static void run_membag_init_test(const struct test_case *test)
{
	/* Initialize membag system. */
	membag_init();

	/* Check that no memory is currently allocated */
	test_assert_true(test, membag_get_total() == membag_get_total_free(),
			"Initialized membag should contain no allocated memory!");

	/* Allocate a small chunk of memory */
	membag_alloc(CONF_TEST_ALLOC_SIZE_SMALL);

	/* Check that sufficient memory was allocated */
	test_assert_false(test,
			(membag_get_total() - membag_get_total_free()) < CONF_TEST_ALLOC_SIZE_SMALL,
			"Not enough memory was allocated!");

	/* Re-Initialize membag system. */
	membag_init();

	/* Check that no memory is now allocated */
	test_assert_true(test,
			membag_get_total() == membag_get_total_free(),
			"Re-Initialized membag should contain no allocated memory!");
}

/** Unit test to check that the Membag allocates small and large chunks of
 *  memory correctly, and fails when a chunk that is too large is requested.
 *
 *  \param test  Pointer to the unit test case instance
 */
static void run_membag_alloc_test(const struct test_case *test)
{
	void *data;

	/* Initialize membag system. */
	membag_init();

	/* Try to allocate a small chunk, should succeed. */
	data = membag_alloc(CONF_TEST_ALLOC_SIZE_SMALL);

	test_assert_false(test, data == NULL,
			"Unable to allocate a small chunk!");

	/* Re-initialize the membag system. */
	membag_init();

	/* Try to allocate a large chunk, should succeed. */
	data = membag_alloc(CONF_TEST_ALLOC_SIZE_LARGE);

	test_assert_false(test, data == NULL,
			"Unable to allocate a large chunk!");

	/* Try to allocate a massive (too large) chunk, should fail. */
	data = membag_alloc(CONF_TEST_ALLOC_SIZE_TOO_LARGE);

	test_assert_true(test, data == NULL,
			"Should not be able to allocate a too-large chunk!");
}

/** Unit test to check that the Membag frees previously allocated memory
 *  correctly.
 *
 *  \param test  Pointer to the unit test case instance
 */
static void run_membag_free_test(const struct test_case *test)
{
	void *data1, *data2, *data3;

	/* Initialize membag system. */
	membag_init();

	/* Allocate three small chunks of data. */
	data1 = membag_alloc(CONF_TEST_ALLOC_SIZE_SMALL);
	data2 = membag_alloc(CONF_TEST_ALLOC_SIZE_SMALL);
	data3 = membag_alloc(CONF_TEST_ALLOC_SIZE_SMALL);

	/* Check that all three membag allocations completed successfully. */
	test_assert_false(test, (data1 == NULL) || (data2 == NULL) ||
			(data3 == NULL),
			"Less than three small chunks were allocated!");

	/* Check that all three membag allocations actually reserved sufficient
	 *memory. */
	test_assert_false(test,
			(membag_get_total() - membag_get_total_free()) <
			(CONF_TEST_ALLOC_SIZE_SMALL * 3),
			"Not enough memory was allocated!");

	membag_free(data1);
	membag_free(data2);
	membag_free(data3);

	/* Check that all memory has been returned to the membag. */
	test_assert_true(test, membag_get_total() == membag_get_total_free(),
			"Not all memory is free!");
}

/** Unit test to check that the Membag functions to determine memory status work
 *  correctly.
 *
 *  \param test  Pointer to the unit test case instance
 */
static void run_membag_get_test(const struct test_case *test)
{
	void *data;
	size_t prev_total_free, chunk_size;

	/* Initialize membag system. */
	membag_init();

	prev_total_free = membag_get_total_free();

	/* Keep allocating chunks until all memory allocated */
	while (membag_get_total_free() > 0) {
		/* Keep track of how much memory we have left and the largest
		 * block size */
		prev_total_free = membag_get_total_free();
		chunk_size = membag_get_largest_free_block_size();

		/* Allocate the next largest block sized chunk of memory */
		data = membag_alloc(chunk_size);
		test_assert_false(test, data == NULL,
				"Unable to allocate a block sized chunk!");

		/* Check that the new memory usage was calculated correctly */
		test_assert_true(test, membag_get_total_free() ==
				(prev_total_free - chunk_size),
				"Failed to calculate correct memory usage!");
	}
}

/** Unit test to check that the Membag allocations fail once all suitable bags
 * are already
 *  allocated.
 *
 *  \param test  Pointer to the unit test case instance
 */
static void run_membag_alloc_when_full_test(const struct test_case *test)
{
	void *data;

	/* Initialize membag system. */
	membag_init();

	/* Allocate as many small chunks as there are sufficiently sized blocks. */
	while (membag_get_largest_free_block_size() >=
			CONF_TEST_ALLOC_SIZE_SMALL) {
		data = membag_alloc(CONF_TEST_ALLOC_SIZE_SMALL);

		test_assert_false(test, data == NULL,
				"Unable to allocate a small chunk!");
	}

	/* Try to allocate one more small chunk, should fail */
	data = membag_alloc(CONF_TEST_ALLOC_SIZE_SMALL);

	test_assert_true(test, data == NULL,
			"Should not be able to allocate small chunk while full!");

	/* Re-initialize the membag system. */
	membag_init();

	/* Allocate as many large chunks as there are sufficiently sized blocks. */
	while (membag_get_largest_free_block_size() >=
			CONF_TEST_ALLOC_SIZE_LARGE) {
		data = membag_alloc(CONF_TEST_ALLOC_SIZE_LARGE);

		test_assert_false(test, data == NULL,
				"Unable to allocate a large chunk!");
	}

	/* Try to allocate one more large chunk, should fail */
	data = membag_alloc(CONF_TEST_ALLOC_SIZE_LARGE);

	test_assert_true(test, data == NULL,
			"Should not be able to allocate large chunk while full!");
}

/** Unit test to check that the Membag re-allocates previously allocated and
 *  subsequently freed blocks of memory correctly.
 *
 *  \param test  Pointer to the unit test case instance
 */
static void run_membag_realloc_test(const struct test_case *test)
{
	void *data;

	/* Initialize membag system. */
	membag_init();

	/* Allocate as many small chunks as there are sufficiently sized blocks. */
	while (membag_get_largest_free_block_size() >=
			CONF_TEST_ALLOC_SIZE_SMALL) {
		data = membag_alloc(CONF_TEST_ALLOC_SIZE_SMALL);

		test_assert_false(test, data == NULL,
				"Unable to allocate a small chunk!");
	}

	/* Free last allocated chunk of memory */
	membag_free(data);

	/* Re-allocate a small chunk, should succeed by re-using the last freed
	 * block of memory. */
	data = membag_alloc(CONF_TEST_ALLOC_SIZE_SMALL);

	test_assert_false(test, data == NULL,
			"Unable to re-allocate a small chunk!");
}

int main()
{
	/* USART init values */
	const usart_serial_options_t usart_serial_options = {
		.baudrate     = CONF_TEST_BAUDRATE,
		.charlength   = CONF_TEST_CHARLENGTH,
		.paritytype   = CONF_TEST_PARITY,
		.stopbits     = CONF_TEST_STOPBITS,
	};

	// Initialize the board and all the peripheral required
	sysclk_init();
	board_init();
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

#if XMEGA
	pmic_init();
	sleepmgr_init();
#endif

	DEFINE_TEST_CASE(membag_init_test, NULL, run_membag_init_test,
			NULL, "Test membag initialization");
	DEFINE_TEST_CASE(membag_alloc_test, NULL, run_membag_alloc_test,
			NULL, "Test membag memory allocation");
	DEFINE_TEST_CASE(membag_free_test, NULL, run_membag_free_test,
			NULL, "Test membag memory freeing");
	DEFINE_TEST_CASE(membag_get_test, NULL, run_membag_get_test,
			NULL, "Test membag get functions");
	DEFINE_TEST_CASE(membag_alloc_when_full_test, NULL,
			run_membag_alloc_when_full_test, NULL,
			"Test membag allocation when all membags are full");
	DEFINE_TEST_CASE(membag_realloc_test, NULL, run_membag_realloc_test,
			NULL, "Test membag allocation and reallocation");

	DEFINE_TEST_ARRAY(membag_tests) = {
		&membag_init_test,
		&membag_alloc_test,
		&membag_free_test,
		&membag_get_test,
		&membag_alloc_when_full_test,
		&membag_realloc_test
	};

	DEFINE_TEST_SUITE(membag_suite,
			membag_tests, "Common util membag test suite");

	test_suite_run(&membag_suite);

	while (1) {
		/* Intentionally left blank */
	}
}
