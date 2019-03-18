/**
 * \file
 *
 * \brief Unit tests for graphical drawing primitives
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
#include <stdio.h>
#include <string.h>
#include <asf.h>
#include <conf_test.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for \ref gfx_mono.
 * It tests that drawing different primitives will result in the correct output
 * to a display using a framebuffer in RAM.
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 *
 * \section device_info Device Info
 * All AVR devices can be used.
 * This example has been tested with the following setup:
 * - Xplain
 *
 * \section description Description of the unit tests
 * See the documentation for the individual test functions
 * \ref unit_tests.c "here" for detailed descriptions of the
 * tests.
 *
 * \section dependencies Dependencies
 * Relevant module dependencies for this application are:
 * - \ref test_suite_group
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for AVR. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */

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

//! \name Helper functions, macros and bitmaps
//@{
//! Bitmap of two 8x8 pixel smileyfaces on top of each other stored in RAM
uint8_t smiley_data[16] = {
	0x3C, 0x42, 0x95, 0xA1, 0xA1, 0x95, 0x42, 0x3C,
	0x3C, 0x42, 0x95, 0xA1, 0xA1, 0x95, 0x42, 0x3C
};

//! Bitmap of two 8x8 pixel smileyfaces on top of each other stored in FLASH
PROGMEM_DECLARE(gfx_mono_color_t, flash_bitmap[16]) = {
	0x3C, 0x42, 0x95, 0xA1, 0xA1, 0x95, 0x42, 0x3C,
	0x3C, 0x42, 0x95, 0xA1, 0xA1, 0x95, 0x42, 0x3C
};

//! \brief Set all bytes in \a buffer to \a value.
#define set_buffer(buffer, value) memset(buffer, value, sizeof(buffer))
//! \brief The height of one lcd page
#define LCD_PAGE_HEIGHT 8

/**
 * \internal
 * \brief Check if a page buffer is equal to another
 *
 * \param test Current test case.
 *
 * \retval true  If the page buffers are the same
 * \retval false If the page buffers are not the same
 */
static bool is_page_correct(uint8_t *test_page, uint8_t *correct_page)
{
	uint16_t column;

	for (column = 0; column < GFX_MONO_LCD_WIDTH; column++) {
		if (test_page[column] != correct_page[column]) {
			return false;
		}
	}

	return true;
}
// @}

/**
 * \internal
 * \brief Test clearing the display
 *
 * This test clears the display, and then checks that each page is empty.
 *
 * \param test Current test case.
 */
static void run_clear_display_test(const struct test_case *test)
{
	uint8_t actual[GFX_MONO_LCD_WIDTH];
	uint8_t expected_empty[GFX_MONO_LCD_WIDTH];
	uint8_t page;

	set_buffer(expected_empty, 0x00);

	// Clear entire display
	gfx_mono_draw_filled_rect(0, 0, GFX_MONO_LCD_WIDTH, GFX_MONO_LCD_HEIGHT,
			GFX_PIXEL_CLR);

	// Get all pages from display and check that each matches the empty page
	for (page = 0; page < GFX_MONO_LCD_PAGES; page++) {
		gfx_mono_get_page(actual, page, 0, GFX_MONO_LCD_WIDTH);
		test_assert_true(test, is_page_correct(actual, expected_empty),
			"Page %d not matching expected page", page);
	}
}

/**
 * \internal
 * \brief Test filling the display
 *
 * This test fills the entire display and checks that this is done.
 *
 * \param test Current test case.
 */
static void run_set_display_test(const struct test_case *test)
{
	uint8_t actual[GFX_MONO_LCD_WIDTH];
	uint8_t expected_set[GFX_MONO_LCD_WIDTH];
	uint8_t page;

	// Clear entire display
	gfx_mono_draw_filled_rect(0, 0, GFX_MONO_LCD_WIDTH, GFX_MONO_LCD_HEIGHT,
			GFX_PIXEL_CLR);

	// Filled expected page buffer
	set_buffer(expected_set, 0xFF);

	// Fill entire display
	gfx_mono_draw_filled_rect(0, 0, GFX_MONO_LCD_WIDTH, GFX_MONO_LCD_HEIGHT,
			GFX_PIXEL_SET);

	// Get all pages from display and check that each matches the empty page
	for (page = 0; page < GFX_MONO_LCD_PAGES; page++) {
		gfx_mono_get_page(actual, page, 0, GFX_MONO_LCD_WIDTH);
		test_assert_true(test, is_page_correct(actual, expected_set),
				"Page %d not matching expected page", page);
	}
}

/**
 * \internal
 * \brief Test drawing a filled rectangle to the every other page of the
 * display
 *
 * This test draws a filled rectangle to every other page of a display and
 * checks that every other page is filled and the rest are empty.
 *
 * \param test Current test case.
 */
static void run_draw_rectangles_test(const struct test_case *test)
{
	uint8_t actual[GFX_MONO_LCD_WIDTH];
	uint8_t expected_set[GFX_MONO_LCD_WIDTH];
	uint8_t expected_empty[GFX_MONO_LCD_WIDTH];
	uint8_t page;

	// Clear entire display
	gfx_mono_draw_filled_rect(0, 0, GFX_MONO_LCD_WIDTH, GFX_MONO_LCD_HEIGHT,
			GFX_PIXEL_CLR);

	// Fill expected page buffers
	set_buffer(expected_set, 0xFF);
	set_buffer(expected_empty, 0x00);

	// Fill every other page
	for (page = 0; page < GFX_MONO_LCD_PAGES; page++) {
		if (page % 2 == 0) {
			gfx_mono_draw_filled_rect(0, LCD_PAGE_HEIGHT * page,
					GFX_MONO_LCD_WIDTH, LCD_PAGE_HEIGHT, GFX_PIXEL_SET);
		}
	}

	// Get all pages from display and check that every other is filled
	for (page = 0; page < GFX_MONO_LCD_PAGES; page++) {
		gfx_mono_get_page(actual, page, 0, GFX_MONO_LCD_WIDTH);
		if (page % 2 == 0) {
			test_assert_true(test, is_page_correct(actual, expected_set),
					"Set page %d not matching expected page", page);
		} else {
			test_assert_true(test, is_page_correct(actual, expected_empty),
					"Empty page %d not matching expected page", page);
		}
	}
}

/**
 * \internal
 * \brief Test drawing a filled rectangle inside a page
 *
 * This test draws a filled rectangle inside a page and checks that this
 * is done.
 *
 * \param test Current test case.
 */
static void run_draw_filled_rectangle_test(const struct test_case *test)
{
	uint8_t actual[GFX_MONO_LCD_WIDTH];
	uint8_t expected_page[GFX_MONO_LCD_WIDTH];
	uint8_t expected_empty[GFX_MONO_LCD_WIDTH];
	uint8_t page;
	uint8_t i;

	// Clear entire display
	gfx_mono_draw_filled_rect(0, 0, GFX_MONO_LCD_WIDTH, GFX_MONO_LCD_HEIGHT,
			GFX_PIXEL_CLR);

	// Fill page buffer holding rectangle
	set_buffer(expected_page, 0x00);
	for (i = 0; i < 10; i++) {
		expected_page[i + 50] = 0x7C;
	}
	
	// Fill empty page buffer
	set_buffer(expected_empty, 0x00);

	// Draw a 10x5 filled rectangle at position 50, 10
	gfx_mono_draw_filled_rect(50, 10, 10, 5, GFX_PIXEL_SET);

	// Get all pages from display and check that the rectangle is drawn
	for (page = 0; page < GFX_MONO_LCD_PAGES; page++) {
		gfx_mono_get_page(actual, page, 0, GFX_MONO_LCD_WIDTH);
		if (page == 1) {
			test_assert_true(test, is_page_correct(actual, expected_page),
					"Page with rectangle %d not matching expected page",
					page);
		} else {
			test_assert_true(test, is_page_correct(actual, expected_empty),
					"Empty page %d not matching expected page", page);
		}
	}
}

/**
 * \internal
 * \brief Test drawing a filled rectangle spanning two pages
 *
 * This test draws a filled rectangle spanning two pages and checks that this
 * is done.
 *
 * \param test Current test case.
 */
static void run_draw_rectangle_two_pages_test(const struct test_case *test)
{
	uint8_t actual[GFX_MONO_LCD_WIDTH];
	uint8_t expected_page1[GFX_MONO_LCD_WIDTH];
	uint8_t expected_page2[GFX_MONO_LCD_WIDTH];
	uint8_t expected_empty[GFX_MONO_LCD_WIDTH];
	uint8_t page;
	uint8_t i;

	// Clear entire display
	gfx_mono_draw_filled_rect(0, 0, GFX_MONO_LCD_WIDTH, GFX_MONO_LCD_HEIGHT,
			GFX_PIXEL_CLR);

	// Fill page buffer holding first part of rectangle
	set_buffer(expected_page1, 0x00);
	for (i = 0; i < 10; i++) {
		expected_page1[i + 48] = 0x80;
	}

	// Fill page buffer holding second part of rectangle
	set_buffer(expected_page2, 0x00);
	for (i = 0; i < 10; i++) {
		expected_page2[i + 48] = 0x7F;
	}

	// Fill empty page buffer
	set_buffer(expected_empty, 0x00);

	// Draw a 10x8 filled rectangle at position 48, 15
	gfx_mono_draw_filled_rect(48, 15, 10, 8, GFX_PIXEL_SET);

	// Get all pages from display and check that the rectangle is drawn
	for (page = 0; page < GFX_MONO_LCD_PAGES; page++) {
		gfx_mono_get_page(actual, page, 0, GFX_MONO_LCD_WIDTH);
		if (page == 1) {
			test_assert_true(test, is_page_correct(actual, expected_page1),
					"First page %d with rectangle not matching expected page",
					page);
		} else if (page == 2) {
			test_assert_true(test, is_page_correct(actual, expected_page2),
					"Second page %d with rectangle not matching expected page",
					page);
		} else {
			test_assert_true(test, is_page_correct(actual, expected_empty),
					"Empty page %d not matching expected page", page);
		}
	}
}

/**
 * \internal
 * \brief Test drawing the outline of a rectangle spanning two pages
 *
 * This test draws the outline of a rectangle spanning two pages and checks
 * that this is done.
 *
 * \param test Current test case.
 */
static void run_draw_rectangle_outline_test(const struct test_case *test)
{
	uint8_t actual[GFX_MONO_LCD_WIDTH];
	uint8_t expected_page1[GFX_MONO_LCD_WIDTH];
	uint8_t expected_page2[GFX_MONO_LCD_WIDTH];
	uint8_t expected_empty[GFX_MONO_LCD_WIDTH];
	uint8_t page;
	uint8_t i;

	// Clear entire display
	gfx_mono_draw_filled_rect(0, 0, GFX_MONO_LCD_WIDTH, GFX_MONO_LCD_HEIGHT,
			GFX_PIXEL_CLR);

	// Fill page buffer holding first part of rectangle
	set_buffer(expected_page1, 0x00);
	expected_page1[5] = 0xE0;
	for (i = 1; i < 99; i++) {
		expected_page1[i + 5] = 0x20;
	}
	expected_page1[99 + 5] = 0xE0;

	// Fill page buffer holding second part of rectangle
	set_buffer(expected_page2, 0x00);
	expected_page2[5] = 0x7F;
	for (i = 1; i < 99; i++) {
		expected_page2[i + 5] = 0x40;
	}
	expected_page2[99 + 5] = 0x7F;

	// Fill empty page buffer
	set_buffer(expected_empty, 0x00);

	// Draw the outline of a 100x10 rectangle at position 5, 5
	gfx_mono_draw_rect(5, 5, 100, 10, GFX_PIXEL_SET);

	// Get all pages from display and check that the rectangle is drawn
	for (page = 0; page < GFX_MONO_LCD_PAGES; page++) {
		gfx_mono_get_page(actual, page, 0, GFX_MONO_LCD_WIDTH);
		if (page == 0) {
			test_assert_true(test, is_page_correct(actual, expected_page1),
					"Page %d with rectangle not matching expected page",
					page);
		} else if (page == 1) {
			test_assert_true(test, is_page_correct(actual, expected_page2),
					"Page %d with rectangle not matching expected page",
					page);
		} else {
			test_assert_true(test, is_page_correct(actual, expected_empty),
					"Empty page %d not matching expected page", page);
		}
	}
}

/**
 * \internal
 * \brief Test drawing the outline of a circle on a page
 *
 * This test draws the outline of a circle and checks that this is done.
 *
 * \param test Current test case.
 */
static void run_draw_circle_outline_test(const struct test_case *test)
{
	uint8_t actual[GFX_MONO_LCD_WIDTH];
	uint8_t expected_page[GFX_MONO_LCD_WIDTH];
	uint8_t expected_empty[GFX_MONO_LCD_WIDTH];
	uint8_t page;

	// Clear entire display
	gfx_mono_draw_filled_rect(0, 0, GFX_MONO_LCD_WIDTH, GFX_MONO_LCD_HEIGHT,
			GFX_PIXEL_CLR);

	// Fill page buffer holding the outlined circle
	set_buffer(expected_page, 0x00);
	expected_page[47] = 0x1C;
	expected_page[48] = 0x22;
	expected_page[49] = 0x41;
	expected_page[50] = 0x41;
	expected_page[51] = 0x41;
	expected_page[52] = 0x22;
	expected_page[53] = 0x1C;

	// Fill empty page buffer
	set_buffer(expected_empty, 0x00);

	// Draw the outline of a circle with radius 3 and centre at position 50, 11
	gfx_mono_draw_circle(50, 11, 3, GFX_PIXEL_SET, GFX_WHOLE);

	// Get all pages from display and check that the circle is drawn
	for (page = 0; page < GFX_MONO_LCD_PAGES; page++) {
		gfx_mono_get_page(actual, page, 0, GFX_MONO_LCD_WIDTH);
		if (page == 1) {
			test_assert_true(test, is_page_correct(actual, expected_page),
					"Page %d with outlined circle not matching expected page",
					page);
		} else {
			test_assert_true(test, is_page_correct(actual, expected_empty),
					"Empty page %d not matching expected page", page);
		}
	}
}

/**
 * \internal
 * \brief Test drawing a filled circle spanning two pages
 *
 * This test draws a filled circle spanning two pages and checks that this is
 * done.
 *
 * \param test Current test case.
 */
static void run_draw_filled_circle_test(const struct test_case *test)
{
	uint8_t actual[GFX_MONO_LCD_WIDTH];
	uint8_t expected_page1[GFX_MONO_LCD_WIDTH];
	uint8_t expected_page2[GFX_MONO_LCD_WIDTH];
	uint8_t expected_empty[GFX_MONO_LCD_WIDTH];
	uint8_t page;

	// Clear entire display
	gfx_mono_draw_filled_rect(0, 0, GFX_MONO_LCD_WIDTH, GFX_MONO_LCD_HEIGHT,
			GFX_PIXEL_CLR);

	// Fill first page buffer holding the top part of the circle
	set_buffer(expected_page1, 0x00);
	expected_page1[36] = 0x80;
	expected_page1[37] = 0xC0;
	expected_page1[38] = 0xE0;
	expected_page1[39] = 0xE0;
	expected_page1[40] = 0xE0;
	expected_page1[41] = 0xE0;
	expected_page1[42] = 0xE0;
	expected_page1[43] = 0xC0;
	expected_page1[44] = 0x80;

	// Fill second page buffer holding the lower part of the circle
	set_buffer(expected_page2, 0x00);
	expected_page2[35] = 0x1F;
	expected_page2[36] = 0x3F;
	expected_page2[37] = 0x7F;
	expected_page2[38] = 0xFF;
	expected_page2[39] = 0xFF;
	expected_page2[40] = 0xFF;
	expected_page2[41] = 0xFF;
	expected_page2[42] = 0xFF;
	expected_page2[43] = 0x7F;
	expected_page2[44] = 0x3F;
	expected_page2[45] = 0x1F;

	// Fill empty page buffer
	set_buffer(expected_empty, 0x00);

	// Draw a filled circle with radius 5 and centre at position 40, 18
	gfx_mono_draw_filled_circle(40, 18, 5, GFX_PIXEL_SET, GFX_WHOLE);

	// Get all pages from display and check that the circle is drawn
	for (page = 0; page < GFX_MONO_LCD_PAGES; page++) {
		gfx_mono_get_page(actual, page, 0, GFX_MONO_LCD_WIDTH);
		if (page == 1) {
			test_assert_true(test, is_page_correct(actual, expected_page1),
					"Page %d with filled circle not matching expected page",
					page);
		} else if (page == 2) {
			test_assert_true(test, is_page_correct(actual, expected_page2),
					"Page %d with filled circle not matching expected page",
					page); 
		} else {
			test_assert_true(test, is_page_correct(actual, expected_empty),
					"Empty page %d not matching expected page", page);
		}
	}
}

/**
 * \internal
 * \brief Test drawing a vertical line
 *
 * This test draws a vertical line and checks that this is done.
 *
 * \param test Current test case.
 */
static void run_draw_vertical_line_test(const struct test_case *test)
{
	uint8_t actual[GFX_MONO_LCD_WIDTH];
	uint8_t expected_page1[GFX_MONO_LCD_WIDTH];
	uint8_t expected_page2[GFX_MONO_LCD_WIDTH];
	uint8_t expected_empty[GFX_MONO_LCD_WIDTH];
	uint8_t page;

	// Clear entire display
	gfx_mono_draw_filled_rect(0, 0, GFX_MONO_LCD_WIDTH, GFX_MONO_LCD_HEIGHT,
			GFX_PIXEL_CLR);

	// Fill page buffer holding the top of the line
	set_buffer(expected_page1, 0x00);
	expected_page1[4] = 0xFC;

	// Fill page buffer holding the bottom of the line
	set_buffer(expected_page2, 0x00);
	expected_page2[4] = 0x1F;

	// Fill empty page buffer
	set_buffer(expected_empty, 0x00);

	// Draw a vertical line at position 4, 2 with length 11
	gfx_mono_draw_vertical_line(4, 2, 11, GFX_PIXEL_SET);

	// Get all pages from display and check that the line is drawn
	for (page = 0; page < GFX_MONO_LCD_PAGES; page++) {
		gfx_mono_get_page(actual, page, 0, GFX_MONO_LCD_WIDTH);
		if (page == 0) {
			test_assert_true(test, is_page_correct(actual, expected_page1),
					"Page %d with line not matching expected page",
					page);
		} else if (page == 1) {
			test_assert_true(test, is_page_correct(actual, expected_page2),
					"Page %d with line not matching expected page",
					page);
		} else {
			test_assert_true(test, is_page_correct(actual, expected_empty),
					"Empty page %d not matching expected page", page);
		}
	}
}

/**
 * \internal
 * \brief Test drawing a horizontal line
 *
 * This test draws a horizontal line and checks that this is done.
 *
 * \param test Current test case.
 */
static void run_draw_horizontal_line_test(const struct test_case *test)
{
	uint8_t actual[GFX_MONO_LCD_WIDTH];
	uint8_t expected_page[GFX_MONO_LCD_WIDTH];
	uint8_t expected_empty[GFX_MONO_LCD_WIDTH];
	uint8_t page;
	uint8_t i;

	// Clear entire display
	gfx_mono_draw_filled_rect(0, 0, GFX_MONO_LCD_WIDTH, GFX_MONO_LCD_HEIGHT,
			GFX_PIXEL_CLR);

	// Fill page buffer holding the line
	set_buffer(expected_page, 0x00);
	for (i = 0; i < 50; i++) {
		expected_page[i + 10] = 0x10;
	}

	// Fill empty page buffer
	set_buffer(expected_empty, 0x00);

	// Draw a horizontal line at postition 10, 20 with length 50
	gfx_mono_draw_horizontal_line(10, 20, 50, GFX_PIXEL_SET);

	// Get all pages from display and check that the line is drawn
	for (page = 0; page < GFX_MONO_LCD_PAGES; page++) {
		gfx_mono_get_page(actual, page, 0, GFX_MONO_LCD_WIDTH);
		if (page == 2) {
			test_assert_true(test, is_page_correct(actual, expected_page),
					"Page %d with line not matching expected page",
					page);
		} else {
			test_assert_true(test, is_page_correct(actual, expected_empty),
					"Empty page %d not matching expected page", page);
		}
	}
}

/**
 * \internal
 * \brief Test drawing a line between to points
 *
 * This test draws a line between two points and checks that this is done.
 *
 * \param test Current test case.
 */
static void run_draw_diagonal_line_test(const struct test_case *test)
{
	uint8_t actual[GFX_MONO_LCD_WIDTH];
	uint8_t expected_page1[GFX_MONO_LCD_WIDTH];
	uint8_t expected_page2[GFX_MONO_LCD_WIDTH];
	uint8_t expected_empty[GFX_MONO_LCD_WIDTH];
	uint8_t page;

	// Clear entire display
	gfx_mono_draw_filled_rect(0, 0, GFX_MONO_LCD_WIDTH, GFX_MONO_LCD_HEIGHT,
			GFX_PIXEL_CLR);

	// Fill first page buffer holding the line
	set_buffer(expected_page1, 0x00);
	expected_page1[0] = 0x03;
	expected_page1[1] = 0x0C;
	expected_page1[2] = 0x30;
	expected_page1[3] = 0xC0;

	// Fill second page buffer holding the line
	set_buffer(expected_page2, 0x00);
	expected_page2[4] = 0x01;
	
	// Fill empty page buffer
	set_buffer(expected_empty, 0x00);

	// Draw a line between 0,0 and 4, 8
	gfx_mono_draw_line(0, 0, 4, 8, GFX_PIXEL_SET);

	// Get all pages from display and check that the line is drawn
	for (page = 0; page < GFX_MONO_LCD_PAGES; page++) {
		gfx_mono_get_page(actual, page, 0, GFX_MONO_LCD_WIDTH);
		if (page == 0) {
			test_assert_true(test, is_page_correct(actual, expected_page1),
					"Page %d with line not matching expected page",
					page);
		} else if (page == 1) {
			test_assert_true(test, is_page_correct(actual, expected_page2),
					"Page %d with line not matching expected page",
					page);
		} else {
			test_assert_true(test, is_page_correct(actual, expected_empty),
					"Empty page %d not matching expected page", page);
		}
	}
}

/**
 * \internal
 * \brief Test drawing a bitmap stored in FLASH
 *
 * This test draws a bitmap to position x = 60, y = 9 and checks that
 * it is aligned with display pages and that it is drawn correctly.
 *
 * \param test Current test case.
 */
static void run_draw_flash_bitmap_test(const struct test_case *test)
{
	uint8_t actual[GFX_MONO_LCD_WIDTH];
	uint8_t expected_page1[GFX_MONO_LCD_WIDTH];
	uint8_t expected_page2[GFX_MONO_LCD_WIDTH];
	uint8_t expected_empty[GFX_MONO_LCD_WIDTH];
	uint8_t page;
	struct gfx_mono_bitmap smiley_flash;

	// Setup bitmap for bitmap stored in FLASH
	smiley_flash.type = GFX_MONO_BITMAP_PROGMEM;
	smiley_flash.width = 8;
	smiley_flash.height = 16;
	smiley_flash.data.progmem = flash_bitmap;

	// Clear entire display
	gfx_mono_draw_filled_rect(0, 0, GFX_MONO_LCD_WIDTH, GFX_MONO_LCD_HEIGHT,
			GFX_PIXEL_CLR);

	// Fill first page buffer holding smileys
	set_buffer(expected_page1, 0x00);
	expected_page1[60] = 0x3C;
	expected_page1[61] = 0x42;
	expected_page1[62] = 0x95;
	expected_page1[63] = 0xA1;
	expected_page1[64] = 0xA1;
	expected_page1[65] = 0x95;
	expected_page1[66] = 0x42;
	expected_page1[67] = 0x3C;

	// Fill second page buffer holding smileys
	set_buffer(expected_page2, 0x00);
	expected_page2[60] = 0x3C;
	expected_page2[61] = 0x42;
	expected_page2[62] = 0x95;
	expected_page2[63] = 0xA1;
	expected_page2[64] = 0xA1;
	expected_page2[65] = 0x95;
	expected_page2[66] = 0x42;
	expected_page2[67] = 0x3C;


	// Fill empty page buffer
	set_buffer(expected_empty, 0x00);

	// Output bitmap
	gfx_mono_put_bitmap(&smiley_flash, 60, 9);

	// Get all pages from display and check that the bitmap is drawn
	for (page = 0; page < GFX_MONO_LCD_PAGES; page++) {
		gfx_mono_get_page(actual, page, 0, GFX_MONO_LCD_WIDTH);
		if (page == 1) {
			test_assert_true(test, is_page_correct(actual, expected_page1),
					"Page %d with smileys not matching expected page",
					page);
		} else if (page == 2) {
			test_assert_true(test, is_page_correct(actual, expected_page2),
					"Page %d with smileys not matching expected page",
					page);
		} else {
			test_assert_true(test, is_page_correct(actual, expected_empty),
					"Empty page %d not matching expected page", page);
		}
	}
}

/**
 * \internal
 * \brief Test drawing a bitmap stored in RAM
 *
 * This test draws a bitmap to position x = 50, y = 5 and checks that
 * it is aligned with display pages and that it is drawn correctly.
 *
 * \param test Current test case.
 */
static void run_draw_ram_bitmap_test(const struct test_case *test)
{
	uint8_t actual[GFX_MONO_LCD_WIDTH];
	uint8_t expected_page1[GFX_MONO_LCD_WIDTH];
	uint8_t expected_page2[GFX_MONO_LCD_WIDTH];
	uint8_t expected_empty[GFX_MONO_LCD_WIDTH];
	uint8_t page;
	struct gfx_mono_bitmap smiley;

	// Setup bitmap struct for bitmap stored in RAM
	smiley.type = GFX_MONO_BITMAP_RAM;
	smiley.width = 8;
	smiley.height = 16;
	smiley.data.pixmap = smiley_data;

	// Clear entire display
	gfx_mono_draw_filled_rect(0, 0, GFX_MONO_LCD_WIDTH, GFX_MONO_LCD_HEIGHT,
			GFX_PIXEL_CLR);

	// Fill first page buffer holding smileys
	set_buffer(expected_page1, 0x00);
	expected_page1[50] = 0x3C;
	expected_page1[51] = 0x42;
	expected_page1[52] = 0x95;
	expected_page1[53] = 0xA1;
	expected_page1[54] = 0xA1;
	expected_page1[55] = 0x95;
	expected_page1[56] = 0x42;
	expected_page1[57] = 0x3C;

	// Fill second page buffer holding smileys
	set_buffer(expected_page2, 0x00);
	expected_page2[50] = 0x3C;
	expected_page2[51] = 0x42;
	expected_page2[52] = 0x95;
	expected_page2[53] = 0xA1;
	expected_page2[54] = 0xA1;
	expected_page2[55] = 0x95;
	expected_page2[56] = 0x42;
	expected_page2[57] = 0x3C;

	// Fill empty page buffer
	set_buffer(expected_empty, 0x00);

	// Output bitmap
	gfx_mono_put_bitmap(&smiley, 50, 5);

	// Get all pages from display and check that the bitmap is drawn
	for (page = 0; page < GFX_MONO_LCD_PAGES; page++) {
		gfx_mono_get_page(actual, page, 0, GFX_MONO_LCD_WIDTH);
		if (page == 0) {
			test_assert_true(test, is_page_correct(actual, expected_page1),
					"Page %d with smileys not matching expected page", page);
		} else if (page == 1) {
			test_assert_true(test, is_page_correct(actual, expected_page2),
					"Page %d with smileys not matching expected page", page);
		} else {
			test_assert_true(test, is_page_correct(actual, expected_empty),
					"Empty page %d not matching expected page", page);
		}
	}
}
//@}

/**
 * \brief Run gfx_mono unit tests
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
	gfx_mono_init();

	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);


	// Define all the test cases
	DEFINE_TEST_CASE(clear_display_test, NULL, run_clear_display_test, NULL,
			"Clear display test");
	DEFINE_TEST_CASE(set_display_test, NULL, run_set_display_test, NULL,
			"Set display test");
	DEFINE_TEST_CASE(draw_rectangles_test, NULL, run_draw_rectangles_test,
			NULL, "Draw filled rectangles test");
	DEFINE_TEST_CASE(draw_filled_rectangle_test, NULL,
			run_draw_filled_rectangle_test, NULL,
			"Draw filled rectangle in one page test");
	DEFINE_TEST_CASE(draw_rectangle_two_pages_test, NULL,
			run_draw_rectangle_two_pages_test, NULL,
			"Draw filled rectangle in two pages test");
	DEFINE_TEST_CASE(draw_rectangle_outline_test, NULL,
			run_draw_rectangle_outline_test, NULL, 
			"Draw rectangle outline test");
	DEFINE_TEST_CASE(draw_filled_circle_test, NULL,
			run_draw_filled_circle_test, NULL, "Draw filled circle test");
	DEFINE_TEST_CASE(draw_circle_outline_test, NULL,
			run_draw_circle_outline_test, NULL, "Draw circle outline test");
	DEFINE_TEST_CASE(draw_vertical_line_test, NULL, 
			run_draw_vertical_line_test, NULL, "Draw vertical line test");
	DEFINE_TEST_CASE(draw_horizontal_line_test, NULL,
			run_draw_horizontal_line_test, NULL, "Draw horizontal line test");
	DEFINE_TEST_CASE(draw_diagonal_line_test, NULL,
			run_draw_diagonal_line_test, NULL,
			"Draw a line between two points test");
	DEFINE_TEST_CASE(draw_flash_bitmap_test, NULL, run_draw_flash_bitmap_test,
			NULL, "Draw bitmap stored in FLASH test");
	DEFINE_TEST_CASE(draw_ram_bitmap_test, NULL, run_draw_ram_bitmap_test,
			NULL, "Draw bitmap stored in RAM test");

	// Put test case addresses in an array
	DEFINE_TEST_ARRAY(gfx_mono_tests) = {
			&clear_display_test,
			&set_display_test,
			&draw_rectangles_test,
			&draw_filled_rectangle_test,
			&draw_rectangle_two_pages_test,
			&draw_rectangle_outline_test,
			&draw_filled_circle_test,
			&draw_circle_outline_test,
			&draw_horizontal_line_test,
			&draw_vertical_line_test,
			&draw_diagonal_line_test,
			&draw_flash_bitmap_test,
			&draw_ram_bitmap_test,
	};

	// Define the test suite
	DEFINE_TEST_SUITE(gfx_mono_suite, gfx_mono_tests, "gfx_mono test suite");

	// Set up the test data pointer and run all tests in the suite
	test_suite_run(&gfx_mono_suite);

	while (1) {
		/* Intentionally left empty. */
	}
}
