/**
 * \file
 *
 * \brief Unit tests for gfx_mono menu system
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <board.h>
#include <compiler.h>
#include <gfx_mono.h>
#include <gfx_mono_menu.h>

#include <sysclk.h>
#include <sysfont.h>
#include <stdio_serial.h>
#include <unit_test/suite.h>
#include <conf_test.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is a unit test application for the gfx_mono menu system.
 * It consists of test cases for the following functionality:
 * - Initializing the menu system
 * - Navigation using simulated key presses
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_menu.h
 * - \ref conf_sysfont.h
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 *
 * \section device_info Device Info
 * All AVR XMEGA devices can be used.
 * This example has been tested with the following setup:
 * - XMEGA A1 Xplain
 *
 * \section description Description of the unit tests
 * See the documentation for the individual unit test
 * functions \ref unit_tests.c
 * "here" for detailed descriptions of the tests.
 *
 * \section dependencies Dependencies
 * This example depends directly on the following modules:
 * - \ref test_suite_group
 * - \ref gfx_mono_menu
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for AVR. Other compilers
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
 * \brief Stop bit configuration of USART
 */
//@}

//! \name Indicator icon definitions
//@{
/**
 * \def GFX_MONO_MENU_INDICATOR_BITMAP
 * \brief Bitmap data, row by row, MSB is leftmost pixel, one byte per row.
 */
/**
 * \def GFX_MONO_MENU_INDICATOR_HEIGHT
 * \brief Height in pixels of indicator icon.
 */
/**
 * \def GFX_MONO_MENU_INDICATOR_WIDTH
 * \brief Width in pixels of indicator icon.
 */
//@}

//! \name Keyboard codes
//@{
/**
 * \def GFX_MONO_MENU_KEYCODE_DOWN
 * \brief Down
 */
/**
 * \def GFX_MONO_MENU_KEYCODE_UP
 * \brief Up
 */
/**
 * \def GFX_MONO_MENU_KEYCODE_BACK
 * \brief Back/exit
 */
/**
 * \def GFX_MONO_MENU_KEYCODE_ENTER
 * \brief Enter/select
 */
//@}

//! \name Menu elements
//@{
/**
 * \def NUM_OF_ELEMENTS
 * \brief Number of elements in menu
 */
/**
 * \def FIRST_ELEMENT
 * \brief First element in menu
 */
/**
 * \def LAST_ELEMENT
 * \brief Last element in menu
 */
/**
 * \def FIRST_PAGE
 * First page of menu
 */
/**
 * \def LAST_PAGE
 * Last page of menu
 */
//@}

//! \name Menu string declarations
//@{
PROGMEM_DECLARE(char const, main_menu_title[]) = "Menu Title";
PROGMEM_DECLARE(char const, main_menu_1[]) = "Selection 1";
PROGMEM_DECLARE(char const, main_menu_2[]) = "Selection 2";
PROGMEM_DECLARE(char const, main_menu_3[]) = "Selection 3";
PROGMEM_DECLARE(char const, main_menu_4[]) = "Selection 4";
PROGMEM_DECLARE(char const, main_menu_5[]) = "Selection 5";
PROGMEM_DECLARE(char const, main_menu_6[]) = "Selection 6";
//@}

PROGMEM_STRING_T main_menu_strings[] = {
	main_menu_1,
	main_menu_2,
	main_menu_3,
	main_menu_4,
	main_menu_5,
	main_menu_6,
};

/**
 * \brief Test menu initialization
 *
 * This function runs the menu initialization, and check to see
 * that is has been set up correctly. Test assumes that there are
 * more menu items than can fit on one page.
 *
 * \param test Current test case
 */
static void run_menu_init_test(const struct test_case *test)
{
	// Set menu options
	struct gfx_mono_menu menu_options = {
		.title             = main_menu_title,
		.strings           = main_menu_strings,
		.num_elements      = NUM_OF_ELEMENTS,
		.current_selection = LAST_ELEMENT
	};

	// Initialize the menu system with these settings
	gfx_mono_menu_init(&menu_options);

	// Only do this test if there actually are several pages
	if (menu_options.current_selection > GFX_MONO_MENU_ELEMENTS_PER_SCREEN) {
		// Check that current page is not first
		test_assert_true(test, menu_options.current_page > FIRST_PAGE,
				"Menu has not been initialized properly");
	}
}

/**
 * \brief Test menu navigation interface using fake keyboard input
 *
 * This test runs the menu system, goes to a menu item, selects it,
 * and verifies that it has been selected. The test assumes that at
 * least three menu items are available on each page.
 *
 * \param test Current test case
 */
static void run_menu_navigation_test(const struct test_case *test)
{
	uint8_t menu_status;
	struct gfx_mono_menu menu_options = {
		.title             = main_menu_title,
		.strings           = main_menu_strings,
		.num_elements      = NUM_OF_ELEMENTS,
		.current_selection = FIRST_ELEMENT
	};

	// Initialize menu system
	gfx_mono_menu_init(&menu_options);

	// Check that current page is first and that current selection is the first
	test_assert_true(test, menu_options.current_page == FIRST_PAGE,
			"Menu system is not on correct page (First)");
	test_assert_true(test, menu_options.current_selection == FIRST_ELEMENT,
			"Menu system is not on correct selection (First)");

	// Go down to selection 2
	menu_status = gfx_mono_menu_process_key(&menu_options,
			GFX_MONO_MENU_KEYCODE_DOWN);
	menu_status = gfx_mono_menu_process_key(&menu_options,
			GFX_MONO_MENU_KEYCODE_DOWN);

	// Verify that menu system is IDLE and waiting
	test_assert_true(test, menu_status == GFX_MONO_MENU_EVENT_IDLE,
			"Menu is not in IDLE mode");

	// Press enter on the selection
	menu_status = gfx_mono_menu_process_key(&menu_options,
			GFX_MONO_MENU_KEYCODE_ENTER);

	// Check that the menu item has been pressed
	test_assert_true(test, menu_status == 2,
			"Menu system has not selected correct menu item");

	// Exit the current selection
	menu_status = gfx_mono_menu_process_key(&menu_options,
			GFX_MONO_MENU_KEYCODE_BACK);

	// Check that the menu has returned EXIT status
	test_assert_true(test, menu_status == GFX_MONO_MENU_EVENT_EXIT,
			"Menu system has not returned exit status after return");

	// Go up a selection, and verify that it is selection 1
	menu_status = gfx_mono_menu_process_key(&menu_options,
			GFX_MONO_MENU_KEYCODE_UP);
	menu_status = gfx_mono_menu_process_key(&menu_options,
			GFX_MONO_MENU_KEYCODE_ENTER);

	// Check that the correct selection has been made
	test_assert_true(test, menu_status == 1,
			"Menu system has not navigated to correct item");
}

/**
 * \brief Test menu page changing
 *
 * This test scrolls down in a menu, until it reaches the next page.
 * This test relies on there being more elements than can fit in a page.
 *
 * \param test Current test case
 */
static void run_menu_page_change_test(const struct test_case *test)
{
	struct gfx_mono_menu menu_options = {
		.title             = main_menu_title,
		.strings           = main_menu_strings,
		.num_elements      = NUM_OF_ELEMENTS,
		.current_selection = FIRST_ELEMENT
	};

	// Initialize menu system
	gfx_mono_menu_init(&menu_options);

	/*
	 * We're on selection 0, we need to scroll
	 * GFX_MONO_MENU_ELEMENTS_PER_SCREEN elements down to
	 * go to the next page of menu items
	 */
	for (uint8_t i = 0; i < GFX_MONO_MENU_ELEMENTS_PER_SCREEN; i++) {
		gfx_mono_menu_process_key(&menu_options,
				GFX_MONO_MENU_KEYCODE_DOWN);
	}

	// Verify that it is the next page
	test_assert_true(test, menu_options.current_page > FIRST_PAGE,
			"Menu system is not on page 1");

	// Verify that we are on the first selection of the next page
	test_assert_true(test,
			menu_options.current_selection ==
					GFX_MONO_MENU_ELEMENTS_PER_SCREEN,
			"Menu system is not on first selection in page");

}

/**
 * \brief Test menu edge wrapping upward from first element
 *
 * This test navigates upward from the first element, expecting
 * to come to the last element in the last page on such an event.
 *
 * \param test Current test case
 */
static void run_menu_wrap_first_test(const struct test_case *test)
{
	struct gfx_mono_menu menu_options = {
		.title             = main_menu_title,
		.strings           = main_menu_strings,
		.num_elements      = NUM_OF_ELEMENTS,
		.current_selection = FIRST_ELEMENT
	};

	// Initialize menu system
	gfx_mono_menu_init(&menu_options);

	/*
	 * Scroll up, and verify that we end up on the last selection,
	 * and the last page.
	 */
	gfx_mono_menu_process_key(&menu_options,
			GFX_MONO_MENU_KEYCODE_UP);

	// Verify that we are on the last selection
	test_assert_true(test, menu_options.current_selection == LAST_ELEMENT,
			"Menu system is not on the last element");
	test_assert_true(test, menu_options.current_page == LAST_PAGE,
			"Menu system is not on the last page");
}

/**
 * \brief Test menu edge wrapping downward from last element
 *
 * This test starts from the last element, and navigates downward,
 * expecting to come to the first element in the first page on such
 * and event.
 *
 * \param test Current test case
 */
static void run_menu_wrap_last_test(const struct test_case *test)
{
	struct gfx_mono_menu menu_options = {
		.title             = main_menu_title,
		.strings           = main_menu_strings,
		.num_elements      = NUM_OF_ELEMENTS,
		.current_selection = LAST_ELEMENT
	};

	// Initialize menu system
	gfx_mono_menu_init(&menu_options);

	// Verify that we are on the last selection
	test_assert_true(test,
			menu_options.current_selection == LAST_ELEMENT,
			"Current selection is not the last as expected");

	// Go down once, to return to top of menu
	gfx_mono_menu_process_key(&menu_options,
			GFX_MONO_MENU_KEYCODE_DOWN);

	// Check that page and selection are at the top
	test_assert_true(test,
			menu_options.current_selection == FIRST_ELEMENT &&
			menu_options.current_page == FIRST_PAGE,
			"Current selection and page are not at beginning");

}

/**
 * \brief Run test suite
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate     = CONF_TEST_BAUDRATE,
		.charlength   = CONF_TEST_CHARLENGTH,
		.paritytype   = CONF_TEST_PARITY,
		.stopbits     = CONF_TEST_STOPBITS,
	};

	sysclk_init();
	board_init();

	// Initialize the Monochrome Graphics library
	gfx_mono_init();

	// Initialize serial communication
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	DEFINE_TEST_CASE(menu_init_test, NULL, run_menu_init_test,
			NULL, "Initialization test");
	DEFINE_TEST_CASE(menu_navigation_test, NULL, run_menu_navigation_test,
			NULL, "Navigation test");
	DEFINE_TEST_CASE(menu_page_change_test, NULL, run_menu_page_change_test,
			NULL, "Change page test");
	DEFINE_TEST_CASE(menu_wrap_first_test, NULL, run_menu_wrap_first_test,
			NULL, "Wrap to last from first test");
	DEFINE_TEST_CASE(menu_wrap_last_test, NULL, run_menu_wrap_last_test,
			NULL, "Wrap from last to first test");

	// Put test case addresses in an array
	DEFINE_TEST_ARRAY(gfx_mono_menu_tests) = {
		&menu_init_test,
		&menu_navigation_test,
		&menu_page_change_test,
		&menu_wrap_first_test,
		&menu_wrap_last_test
	};

	// Define the test suite
	DEFINE_TEST_SUITE(gfx_mono_menu_suite, gfx_mono_menu_tests,
			"gfx_mono menu system test suite");

	// Run all tests in the test suite
	test_suite_run(&gfx_mono_menu_suite);

	while (1) {
		// Intentionally left empty
	}
}
