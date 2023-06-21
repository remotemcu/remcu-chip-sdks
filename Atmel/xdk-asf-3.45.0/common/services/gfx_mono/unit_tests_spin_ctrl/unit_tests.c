/**
 * \file
 *
 * \brief Unit tests for spinner widget
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
#include <progmem.h>
#include <asf.h>
#include <conf_test.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the \ref gfx_mono_spinctrl.
 * It tests that the a set of keycodes processed by a spincollection
 * results in expected spinner choices.
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 * - \ref conf_spinctrl.h
 * - \ref conf_sysfont.h
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
 * - \ref gfx_mono
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for AVR. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
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

PROGMEM_DECLARE(char const, spinnertitle[]) = "Strings:";
PROGMEM_DECLARE(char const, spinnertitle2[]) = "Numbers:";
PROGMEM_DECLARE(char const, spinnertitle3[]) = "Numbers2:";
PROGMEM_DECLARE(char const, spinner_choice1[]) = "String 1";
PROGMEM_DECLARE(char const, spinner_choice2[]) = "String 2";
PROGMEM_DECLARE(char const, spinner_choice3[]) = "String 3";
PROGMEM_DECLARE(char const, spinner_choice4[]) = "String 4";

PROGMEM_STRING_T spinner_choicestrings[] = {
	spinner_choice1,
	spinner_choice2,
	spinner_choice3,
	spinner_choice4,
};

//! \name Spinctrl unit test functions
//@{

/**
 * \internal
 * \brief Test spinning through a spincollection with only one spinner
 *
 * This test checks that spinning in a spincollection with only one integer
 * spinner gives the correct result.
 *
 * \param test Current test case.
 */
static void run_single_spinner_spincollection_test(const struct test_case
		*test)
{
	int16_t actual[1];
	int16_t expected[1];
	uint8_t actual_status_code;
	uint8_t expected_status_code;
	struct gfx_mono_spinctrl spinner;
	struct gfx_mono_spinctrl_spincollection spincollection;

	expected[0] = 46;
	expected_status_code = GFX_MONO_SPINCTRL_EVENT_FINISH;

	// Initialize spinner and spincollection and add spinner to collection
	gfx_mono_spinctrl_init(&spinner, SPINTYPE_INTEGER, spinnertitle2, NULL,
			40, 48, 0);
	gfx_mono_spinctrl_spincollection_init(&spincollection);
	gfx_mono_spinctrl_spincollection_add_spinner(&spinner, &spincollection);

	// Choose spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_ENTER, actual);
	// Step up spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_UP, actual);
	// Step up spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_UP, actual);
	// Step up spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_UP, actual);
	// Step up spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_UP, actual);
	// Step up spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_UP, actual);
	// Step up spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_UP, actual);
	// Select current spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_ENTER, actual);
	// Go down to OK button
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Select OK button
	actual_status_code = gfx_mono_spinctrl_spincollection_process_key(
			&spincollection, GFX_MONO_SPINCTRL_KEYCODE_ENTER, actual);

	test_assert_true(test, actual_status_code == expected_status_code,
			"Status code mismatch: %d != %d", actual_status_code,
			expected_status_code);
	test_assert_true(test, actual[0] == expected[0],
			"Result mismatch: %d != %d", actual[0],
			expected[0]);
}

/**
 * \internal
 * \brief Test spinning through a spincollection with two spinners
 *
 * This test checks that spinning in a spincollection with one integer
 * spinner and one string spinner gives the correct result.
 *
 * \param test Current test case.
 */
static void run_two_spinners_spincollection_test(const struct test_case *test)
{
	int16_t actual[2];
	int16_t expected[2];
	uint8_t actual_status_code;
	uint8_t expected_status_code;
	struct gfx_mono_spinctrl spinner1;
	struct gfx_mono_spinctrl spinner2;
	struct gfx_mono_spinctrl_spincollection spincollection;

	expected[0] = 3;
	expected[1] = 2;
	expected_status_code = GFX_MONO_SPINCTRL_EVENT_FINISH;

	// Initialize spinners and spincollection and add spinners to collection
	gfx_mono_spinctrl_init(&spinner1, SPINTYPE_INTEGER, spinnertitle2, NULL,
			-1, 3, 0);
	gfx_mono_spinctrl_init(&spinner2, SPINTYPE_STRING, spinnertitle,
		spinner_choicestrings, 0, 3, 0);
	gfx_mono_spinctrl_spincollection_init(&spincollection);
	gfx_mono_spinctrl_spincollection_add_spinner(&spinner1, &spincollection);
	gfx_mono_spinctrl_spincollection_add_spinner(&spinner2, &spincollection);

	// Go down to next spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Select spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_ENTER, actual);
	// Step up spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_UP, actual);
	// Step up spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_UP, actual);
	// Select spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_ENTER, actual);
	// Go down to OK button
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Go down (wrap around) to first spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Select current spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_ENTER, actual);
	// Step down spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Select spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_ENTER, actual);
	// Go down to next spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Go down to OK button
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Select OK button
	actual_status_code = gfx_mono_spinctrl_spincollection_process_key(
			&spincollection, GFX_MONO_SPINCTRL_KEYCODE_ENTER, actual);

	test_assert_true(test, actual_status_code == expected_status_code,
			"Status code mismatch: %d != %d", actual_status_code,
			expected_status_code);
	test_assert_true(test, actual[0] == expected[0],
			"Result mismatch from spinner 1: %d != %d", actual[0],
			expected[0]);
	test_assert_true(test, actual[1] == expected[1],
			"Result mismatch from spinner 2: %d != %d", actual[1],
			expected[1]);
}

/**
 * \internal
 * \brief Test spinning through a spincollection with three spinners
 *
 * This test checks that spinning in a spincollection with two integer
 * spinners and one string spinner gives the correct result.
 *
 * \param test Current test case.
 */
static void run_three_spinners_spincollection_test(const struct test_case
		*test)
{
	int16_t actual[3];
	int16_t expected[3];
	uint8_t actual_status_code;
	uint8_t expected_status_code;
	struct gfx_mono_spinctrl spinner1;
	struct gfx_mono_spinctrl spinner2;
	struct gfx_mono_spinctrl spinner3;
	struct gfx_mono_spinctrl_spincollection spincollection;

	expected[0] = -1;
	expected[1] = 1;
	expected[2] = 2008;
	expected_status_code = GFX_MONO_SPINCTRL_EVENT_FINISH;

	// Initialize spinners and spincollection and add spinners to collection
	gfx_mono_spinctrl_init(&spinner1, SPINTYPE_INTEGER, spinnertitle2, NULL,
			-1, 3, 0);
	gfx_mono_spinctrl_init(&spinner2, SPINTYPE_STRING, spinnertitle,
		spinner_choicestrings, 0, 3, 0);
	gfx_mono_spinctrl_init(&spinner3, SPINTYPE_INTEGER, spinnertitle3, NULL,
			2006, 2999, 0);
	gfx_mono_spinctrl_spincollection_init(&spincollection);
	gfx_mono_spinctrl_spincollection_add_spinner(&spinner1, &spincollection);
	gfx_mono_spinctrl_spincollection_add_spinner(&spinner2, &spincollection);
	gfx_mono_spinctrl_spincollection_add_spinner(&spinner3, &spincollection);

	// Go down to next spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Go down to last spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Select spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_ENTER, actual);
	// Step up spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_UP, actual);
	// Step up spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_UP, actual);
	// Select spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_ENTER, actual);
	// Go up to previous spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_UP, actual);
	// Select current spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_ENTER, actual);
	// Step down spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Step down spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Step down spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Select spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_ENTER, actual);
	// Go up to first spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_UP, actual);
	// Select current spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_ENTER, actual);
	// Step down spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Step up spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_UP, actual);
	// Select spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_ENTER, actual);
	// Go up to OK button
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_UP, actual);
	// Select OK button
	actual_status_code = gfx_mono_spinctrl_spincollection_process_key(
			&spincollection, GFX_MONO_SPINCTRL_KEYCODE_ENTER, actual);

	test_assert_true(test, actual_status_code == expected_status_code,
			"Status code mismatch: %d != %d", actual_status_code,
			expected_status_code);
	test_assert_true(test, actual[0] == expected[0],
			"Result mismatch from spinner 1: %d != %d", actual[0],
			expected[0]);
	test_assert_true(test, actual[1] == expected[1],
			"Result mismatch from spinner 2: %d != %d", actual[1],
			expected[1]);
	test_assert_true(test, actual[2] == expected[2],
			"Result mismatch from spinner 3: %d != %d", actual[2],
			expected[2]);
}

/**
 * \internal
 * \brief Test spinning through a spincollection and cancelling
 *
 * This test checks that spinning in a spincollection with two spinners
 * and pressing the back button results in the correct event.
 *
 * \param test Current test case.
 */
static void run_event_back_spincollection_test(const struct test_case *test)
{
	int16_t actual[2];
	uint8_t actual_status_code;
	uint8_t expected_status_code;
	struct gfx_mono_spinctrl spinner;
	struct gfx_mono_spinctrl spinner2;
	struct gfx_mono_spinctrl_spincollection spincollection;

	expected_status_code = GFX_MONO_SPINCTRL_EVENT_BACK;

	// Initialize spinners and spincollection and add spinners to collection
	gfx_mono_spinctrl_init(&spinner, SPINTYPE_INTEGER, spinnertitle2, NULL,
			40, 48, 0);
	gfx_mono_spinctrl_init(&spinner2, SPINTYPE_INTEGER, spinnertitle3, NULL,
			55, 110, 0);
	gfx_mono_spinctrl_spincollection_init(&spincollection);
	gfx_mono_spinctrl_spincollection_add_spinner(&spinner, &spincollection);
	gfx_mono_spinctrl_spincollection_add_spinner(&spinner2, &spincollection);

	// Go down to next spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Select current spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_ENTER, actual);
	// Spin spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Spin spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Spin spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Deselect spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_BACK, actual);
	// Cancel spincollection
	actual_status_code = gfx_mono_spinctrl_spincollection_process_key(
			&spincollection, GFX_MONO_SPINCTRL_KEYCODE_BACK, actual);

	test_assert_true(test, actual_status_code == expected_status_code,
			"Status code mismatch: %d != %d", actual_status_code,
			expected_status_code);
}

/**
 * \internal
 * \brief Test selecting a spinner in a spincollection, changing and saving its
 * value, then selecting the spinner again, but this time not saving the result.
 *
 * This test checks that spinning in a spincollection with three spinners,
 * selecting a spinner, changing and saving its value and then select and
 * change its value again, but this time not saving, will result in the saved
 * result being stored in the results array.
 *
 * \param test Current test case.
 */
static void run_cancel_spinner_spincollection_test(const struct test_case *test)
{
	int16_t actual[3];
	int16_t expected[3];
	uint8_t actual_status_code;
	uint8_t expected_status_code;
	struct gfx_mono_spinctrl spinner;
	struct gfx_mono_spinctrl spinner2;
	struct gfx_mono_spinctrl spinner3;
	struct gfx_mono_spinctrl_spincollection spincollection;

	expected[0] = 40;
	expected[1] = 108;
	expected[2] = 1;
	expected_status_code = GFX_MONO_SPINCTRL_EVENT_FINISH;

	// Initialize spinners and spincollection and add spinners to collection
	gfx_mono_spinctrl_init(&spinner, SPINTYPE_INTEGER, spinnertitle2, NULL,
			40, 48, 0);
	gfx_mono_spinctrl_init(&spinner2, SPINTYPE_INTEGER, spinnertitle3, NULL,
			55, 110, 0);
	gfx_mono_spinctrl_init(&spinner3, SPINTYPE_STRING, spinnertitle,
		spinner_choicestrings, 0, 3, 0);
	gfx_mono_spinctrl_spincollection_init(&spincollection);
	gfx_mono_spinctrl_spincollection_add_spinner(&spinner, &spincollection);
	gfx_mono_spinctrl_spincollection_add_spinner(&spinner2, &spincollection);
	gfx_mono_spinctrl_spincollection_add_spinner(&spinner3, &spincollection);

	// Go down to next spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Select current spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_ENTER, actual);
	// Spin spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Spin spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Spin spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Select spinner value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_ENTER, actual);
	// Go down to next spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	//Select current spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_ENTER, actual);
	// Spin spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_UP, actual);
	// Select current value
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_ENTER, actual);
	// Go up to previous spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_UP, actual);
	// Select current spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_ENTER, actual);
	// Spin spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_UP, actual);
	// Spin spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_UP, actual);
	// Deselect spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_BACK, actual);
	// Go down to next spinner
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Go down to OK button
	gfx_mono_spinctrl_spincollection_process_key(&spincollection,
			GFX_MONO_SPINCTRL_KEYCODE_DOWN, actual);
	// Select OK button
	actual_status_code = gfx_mono_spinctrl_spincollection_process_key(
			&spincollection, GFX_MONO_SPINCTRL_KEYCODE_ENTER,
			actual);

	test_assert_true(test, actual_status_code == expected_status_code,
			"Status code mismatch: %d != %d", actual_status_code,
			expected_status_code);
	test_assert_true(test, actual[0] == expected[0],
			"Result mismatch from spinner: 1 %d != %d", actual[0],
			expected[0]);
	test_assert_true(test, actual[1] == expected[1],
			"Result mismatch from spinner 2: %d != %d", actual[1],
			expected[1]);
	test_assert_true(test, actual[2] == expected[2],
			"Result mismatch from spinner 3: %d != %d", actual[2],
			expected[2]);
}
//@}

/**
 * \brief Run spinner widget unit tests
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
	DEFINE_TEST_CASE(single_spinner_spincollection_test, NULL,
			run_single_spinner_spincollection_test, NULL,
			"Single spinners in spincollection test");
	DEFINE_TEST_CASE(two_spinners_spincollection_test, NULL,
			run_two_spinners_spincollection_test, NULL,
			"Two spinners in spincollection test");
	DEFINE_TEST_CASE(three_spinners_spincollection_test, NULL,
			run_three_spinners_spincollection_test, NULL,
			"Three spinners in spincollection test");
	DEFINE_TEST_CASE(cancel_spinner_spincollection_test, NULL,
			run_cancel_spinner_spincollection_test, NULL,
			"Cancel spinner choice test");
	DEFINE_TEST_CASE(event_back_spincollection_test, NULL,
			run_event_back_spincollection_test, NULL,
			"Event back spincollection test");

	// Put test case addresses in an array
	DEFINE_TEST_ARRAY(spinctrl_tests) = {
		&single_spinner_spincollection_test,
		&two_spinners_spincollection_test,
		&three_spinners_spincollection_test,
		&event_back_spincollection_test,
		&cancel_spinner_spincollection_test,
	};

	// Define the test suite
	DEFINE_TEST_SUITE(spinctrl_suite, spinctrl_tests,
			"Spinner widget with test suite");

	// Set up the test data pointer and run all tests in the suite
	test_suite_run(&spinctrl_suite);

	while (1) {
		/* Intentionally left empty. */
	}
}
