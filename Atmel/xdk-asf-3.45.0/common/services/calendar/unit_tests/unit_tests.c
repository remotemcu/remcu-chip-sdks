/**
 * \file
 *
 * \brief Unit tests for calendar service
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
#include <asf.h>
#include <string.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <conf_test.h>
#include <calendar.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the \ref calendar_group
 * "Calendar service".
 * It consists of test cases for the following:
 * - convert timestamp to date
 * - convert date to timestamp
 * - compute time between two dates
 * - increment date with one second
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
 * - UC3-L0 Xplained
 * - STK600 with RCUC3D extension board
 *
 * \section description Description of the unit tests
 * See the documentation for the individual unit test functions
 * \ref unit_tests.c "here" for detailed descriptions of the tests.
 *
 * \section dependencies Dependencies
 * This example depends directly on the following modules:
 * - \ref test_suite_group
 * - \ref calendar_group "Calendar service"
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for AVR. Other compilers
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

//! \name Calendar unit test functions
//@{

/**
 * \internal
 * \brief Test conversion of normal timestamp to date
 *
 * This test checks that conversion of a normal timestamp results in the
 * expected date.
 *
 * \param test Current test case.
 */
static void run_timestamp_to_normal_date_test(const struct test_case *test)
{
	struct calendar_date expected;
	struct calendar_date actual;

	expected.second = 56;
	expected.minute = 24;
	expected.hour = 11;
	expected.date = 21;
	expected.month = 5;
	expected.year = 2011;

	calendar_timestamp_to_date(1308741896, &actual);

	test_assert_true(test, actual.second == expected.second,
			"Second mismatch %d != %d", actual.second, expected.second);
	test_assert_true(test, actual.minute == expected.minute,
			"Minute mismatch %d != %d", actual.minute, expected.minute);
	test_assert_true(test, actual.hour == expected.hour,
			"Hour mismatch %d != %d", actual.hour, expected.hour);
	test_assert_true(test, actual.date == expected.date,
			"Date mismatch %d != %d", actual.date, expected.date);
	test_assert_true(test, actual.month == expected.month,
			"Month mismatch %d != %d", actual.month, expected.month);
	test_assert_true(test, actual.year == expected.year,
			"Year mismatch %d != %d", actual.year, expected.year);
}

/**
 * \internal
 * \brief Test conversion of timestamp 0 to date
 *
 * This test checks that conversion of timestamp 0 results in January 1st 1970
 * 00:00:00.
 *
 * \param test Current test case.
 */
static void run_timestamp_0_to_date_test(const struct test_case *test)
{
	struct calendar_date expected;
	struct calendar_date actual;

	expected.second = 0;
	expected.minute = 0;
	expected.hour = 0;
	expected.date = 0;
	expected.month = 0;
	expected.year = 1970;

	calendar_timestamp_to_date(0, &actual);
	test_assert_true(test, actual.second == expected.second,
			"Second mismatch %d != %d", actual.second, expected.second);
	test_assert_true(test, actual.minute == expected.minute,
			"Minute mismatch %d != %d", actual.minute, expected.minute);
	test_assert_true(test, actual.hour == expected.hour,
			"Hour mismatch %d != %d", actual.hour, expected.hour);
	test_assert_true(test, actual.date == expected.date,
			"Date mismatch %d != %d", actual.date, expected.date);
	test_assert_true(test, actual.month == expected.month,
			"Month mismatch %d != %d", actual.month, expected.month);
	test_assert_true(test, actual.year == expected.year,
			"Year mismatch %d != %d", actual.year, expected.year);
}

/**
 * \internal
 * \brief Test conversion of timestamp to end of February in leap year date
 *
 * This test checks that conversion of a timestamp results in February 29th 2008
 * 06:05:50.
 *
 * \param test Current test case.
 */
static void run_timestamp_to_leap_year_date_test(const struct test_case *test)
{
	struct calendar_date expected;
	struct calendar_date actual;

	expected.second = 50;
	expected.minute = 5;
	expected.hour = 6;
	expected.date = 28;
	expected.month = 1;
	expected.year = 2008;

	calendar_timestamp_to_date(1204265150, &actual);
	test_assert_true(test, actual.second == expected.second,
			"Second mismatch %d != %d", actual.second, expected.second);
	test_assert_true(test, actual.minute == expected.minute,
			"Minute mismatch %d != %d", actual.minute, expected.minute);
	test_assert_true(test, actual.hour == expected.hour,
			"Hour mismatch %d != %d", actual.hour, expected.hour);
	test_assert_true(test, actual.date == expected.date,
			"Date mismatch %d != %d", actual.date, expected.date);
	test_assert_true(test, actual.month == expected.month,
			"Month mismatch %d != %d", actual.month, expected.month);
	test_assert_true(test, actual.year == expected.year,
			"Year mismatch %d != %d", actual.year, expected.year);
}

/**
 * \internal
 * \brief Test conversion of timestamp to March in leap year date
 *
 * This test checks that conversion of a timestamp results in March 3rd 1992
 * 15:30:11.
 *
 * \param test Current test case.
 */
static void run_timestamp_to_leap_year_date2_test(const struct test_case *test)
{
	struct calendar_date expected;
	struct calendar_date actual;

	// Convert  leap year timestamp to date
	expected.second = 11;
	expected.minute = 30;
	expected.hour = 15;
	expected.date = 2;
	expected.month = 2;
	expected.year = 1992;

	calendar_timestamp_to_date(699636611, &actual);
	test_assert_true(test, actual.second == expected.second,
			"Second mismatch %d != %d", actual.second, expected.second);
	test_assert_true(test, actual.minute == expected.minute,
			"Minute mismatch %d != %d", actual.minute, expected.minute);
	test_assert_true(test, actual.hour == expected.hour,
			"Hour mismatch %d != %d", actual.hour, expected.hour);
	test_assert_true(test, actual.date == expected.date,
			"Date mismatch %d != %d", actual.date, expected.date);
	test_assert_true(test, actual.month == expected.month,
			"Month mismatch %d != %d", actual.month, expected.month);
	test_assert_true(test, actual.year == expected.year,
			"Year mismatch %d != %d", actual.year, expected.year);
}

/**
 * \internal
 * \brief Test conversion of first date to timestamp
 *
 * This test checks that conversion of the first date in UNIX time date results
 * in timestamp 0.
 *
 * \param test Current test case.
 */
static void run_date_to_timestamp_0_test(const struct test_case *test)
{
	uint32_t expected = 0;
	uint32_t actual;

	struct calendar_date testvar = {
		.second = 0,
		.minute = 0,
		.hour = 0,
		.date = 0,
		.month = 0,
		.year = 1970
		};
	actual = calendar_date_to_timestamp(&testvar);
	test_assert_true(test, actual == expected,
			"Date January 1st 1970, 00:00:00, %d != %d",
			actual, expected);
}

/**
 * \internal
 * \brief Test conversion of a date with invalid time to timestamp
 *
 * This test checks that conversion of a date with 83 seconds results in
 * timestamp 0.
 *
 * \param test Current test case.
 */
static void run_erronous_time_to_timestamp_test(const struct test_case *test)
{
	uint32_t expected = 0;
	uint32_t actual;

	struct calendar_date testvar = {
		.second = 83,
		.minute = 12,
		.hour = 11,
		.date = 21,
		.month = 4,
		.year = 1983
		};

	actual = calendar_date_to_timestamp(&testvar);
	test_assert_true(test, actual == expected,
			"Wrong date May 12th 1983, 11:12:83, %d != %d",
			actual, expected);
}

/**
 * \internal
 * \brief Test conversion of a date with invalid day to timestamp
 *
 * This test checks that conversion of February 29th in a year that is not
 * a leap year results in timestamp 0.
 *
 * \param test Current test case.
 */
static void run_erronous_date_to_timestamp_test(const struct test_case *test)
{
	uint32_t expected = 0;
	uint32_t actual;

	struct calendar_date testvar = {
		.second = 53,
		.minute = 1,
		.hour = 15,
		.date = 28,
		.month = 1,
		.year = 1983
		};

	actual = calendar_date_to_timestamp(&testvar);
	test_assert_true(test, actual == expected,
			"Wrong date February 29th 1983, 15:01:53, %d != %d",
			actual, expected);
}

/**
 * \internal
 * \brief Test conversion of a date in a leap year to timestamp
 *
 * This test checks that conversion of February 29th in a year that is a leap
 * year results in the correct timestamp.
 *
 * \param test Current test case.
 */
static void run_leap_year_date_to_timestamp_test(const struct test_case *test)
{
	uint32_t expected = 1204245932;
	uint32_t actual;

	struct calendar_date testvar = {
		.second = 32,
		.minute = 45,
		.hour = 0,
		.date = 28,
		.month = 1,
		.year = 2008
		};

	actual = calendar_date_to_timestamp(&testvar);
	test_assert_true(test, actual == expected,
			"Date February 29th 2008, 00:45:32, %d != %d",
			actual, expected);
}

/**
 * \internal
 * \brief Test conversion of a normal date to timestamp
 *
 * This test checks that conversion of a normal date results in the correct
 * timestamp.
 *
 * \param test Current test case.
 */
static void run_date_to_timestamp_test(const struct test_case *test)
{
	uint32_t expected = 479258400;
	uint32_t actual;

	struct calendar_date testvar = {
		.second = 0,
		.minute = 20,
		.hour = 23,
		.date = 8,
		.month = 2,
		.year = 1985
		};

	actual = calendar_date_to_timestamp(&testvar);
	test_assert_true(test, actual == expected,
			"Date March 9th 1985, 23:20:00, %d != %d",
			actual, expected);
}

/**
 * \internal
 * \brief Test conversion of a date before 1970 to timestamp 0
 *
 * This test checks that conversion of a date before epoch year 1970 results in
 * timestamp 0.
 *
 * \param test Current test case.
 */
static void run_date_1855_to_timestamp_test(const struct test_case *test)
{
	uint32_t expected = 0;
	uint32_t actual;

	struct calendar_date testvar = {
		.second = 7,
		.minute = 14,
		.hour = 3,
		.date = 18,
		.month = 0,
		.year = 1855
		};

	actual = calendar_date_to_timestamp(&testvar);
	test_assert_true(test, actual == expected,
			"Date January 19th 1855, 03:14:07, %d != %d",
			actual, expected);
}

/**
 * \internal
 * \brief Test conversion of a date after 2106 to timestamp 0
 *
 * This test checks that conversion of a date after overflow year 2106 results
 * in timestamp 0.
 *
 * \param test Current test case.
 */
static void run_date_2107_to_timestamp_test(const struct test_case *test)
{
	uint32_t expected = 0;
	uint32_t actual;

	struct calendar_date testvar = {
		.second = 7,
		.minute = 14,
		.hour = 3,
		.date = 18,
		.month = 0,
		.year = 2107
		};

	actual = calendar_date_to_timestamp(&testvar);
	test_assert_true(test, actual == expected,
			"Date January 19th 2107, 03:14:07, %d != %d",
			actual, expected);
}

/**
* \internal
 * \brief Test computation of time between dates in the same year
 *
 * This test checks that computing time between dates in the same year returns
 * the expected duration.
 *
 * \param test Current test case.
 */
static void run_time_between_dates_same_year_test(const struct test_case *test)
{
	struct calendar_date expected;
	struct calendar_date actual;
	uint32_t testvar_start;
	uint32_t testvar_end;

	struct calendar_date testcal_end;
	struct calendar_date testcal_start;

	expected.second = 8;
	expected.minute = 10;
	expected.hour = 22;
	expected.date = 15;
	expected.month = 1;
	expected.year = 0;

	testvar_start = 1306329300;
	testvar_end = 1310383508;
	calendar_timestamp_to_date(testvar_start, &testcal_start);
	calendar_timestamp_to_date(testvar_end, &testcal_end);

	calendar_time_between_dates(&testcal_end, &testcal_start, &actual);

	test_assert_true(test, actual.second == expected.second,
			"Second mismatch %d != %d", actual.second, expected.second);
	test_assert_true(test, actual.minute == expected.minute,
			"Minute mismatch %d != %d", actual.minute, expected.minute);
	test_assert_true(test, actual.hour == expected.hour,
			"Hour mismatch %d != %d", actual.hour, expected.hour);
	test_assert_true(test, actual.date == expected.date,
			"Date mismatch %d != %d", actual.date, expected.date);
	test_assert_true(test, actual.month == expected.month,
			"Month mismatch %d != %d", actual.month, expected.month);
	test_assert_true(test, actual.year == expected.year,
			"Year mismatch %d != %d", actual.year, expected.year);
}

/**
* \internal
 * \brief Test computation of time between dates in the different years
 *
 * This test checks that computing time between dates in the different years,
 * but less than one year apart results in the expected duration.
 *
 * \param test Current test case.
 */
static void run_time_between_dates_diff_year_test(const struct test_case *test)
{
	struct calendar_date expected;
	struct calendar_date actual;
	uint32_t testvar_start;
	uint32_t testvar_end;

	struct calendar_date testcal_end;
	struct calendar_date testcal_start;

	expected.second = 8;
	expected.minute = 10;
	expected.hour = 22;
	expected.date = 16;
	expected.month = 10;
	expected.year = 0;

	testvar_start = 1274793300;
	testvar_end = 1302521108;

	calendar_timestamp_to_date(testvar_start, &testcal_start);
	calendar_timestamp_to_date(testvar_end, &testcal_end);

	calendar_time_between_dates(&testcal_end, &testcal_start, &actual);

	test_assert_true(test, actual.second == expected.second,
			"Second mismatch %d != %d", actual.second, expected.second);
	test_assert_true(test, actual.minute == expected.minute,
			"Minute mismatch %d != %d", actual.minute, expected.minute);
	test_assert_true(test, actual.hour == expected.hour,
			"Hour mismatch %d != %d", actual.hour, expected.hour);
	test_assert_true(test, actual.date == expected.date,
			"Date mismatch %d != %d", actual.date, expected.date);
	test_assert_true(test, actual.month == expected.month,
			"Month mismatch %d != %d", actual.month, expected.month);
	test_assert_true(test, actual.year == expected.year,
			"Year mismatch %d != %d", actual.year, expected.year);
}

/**
* \internal
 * \brief Test computation of time between dates in the same leap year
 *
 * This test checks that computing time between dates in the same leap year
 * results the expected duration.
 *
 * \param test Current test case.
 */
static void run_time_between_dates_leap_year_test(const struct test_case *test)
{
	struct calendar_date expected;
	struct calendar_date actual;
	uint32_t testvar_start;
	uint32_t testvar_end;

	struct calendar_date testcal_end;
	struct calendar_date testcal_start;

	expected.second = 8;
	expected.minute = 3;
	expected.hour = 19;
	expected.date = 16;
	expected.month = 1;
	expected.year = 0;

	testvar_start = 1203956520;
	testvar_end = 1207913108;
	calendar_timestamp_to_date(testvar_start, &testcal_start);
	calendar_timestamp_to_date(testvar_end, &testcal_end);

	calendar_time_between_dates(&testcal_end, &testcal_start, &actual);

	test_assert_true(test, actual.second == expected.second,
			"Second mismatch %d != %d", actual.second, expected.second);
	test_assert_true(test, actual.minute == expected.minute,
			"Minute mismatch %d != %d", actual.minute, expected.minute);
	test_assert_true(test, actual.hour == expected.hour,
			"Hour mismatch %d != %d", actual.hour, expected.hour);
	test_assert_true(test, actual.date == expected.date,
			"Date mismatch %d != %d", actual.date, expected.date);
	test_assert_true(test, actual.month == expected.month,
			"Month mismatch %d != %d", actual.month, expected.month);
	test_assert_true(test, actual.year == expected.year,
			"Year mismatch %d != %d", actual.year, expected.year);
}

/**
* \internal
 * \brief Test computation of time between dates several years apart
 *
 * This test checks that computing time between dates several years apart
 * results in the expected duration.
 *
 * \param test Current test case.
 */
static void run_time_between_dates_years_test(const struct test_case *test)
{
	struct calendar_date expected;
	struct calendar_date actual;
	uint32_t testvar_start;
	uint32_t testvar_end;

	struct calendar_date testcal_end;
	struct calendar_date testcal_start;

	expected.second = 8;
	expected.minute = 5;
	expected.hour = 12;
	expected.date = 12;
	expected.month = 3;
	expected.year = 26;

	testvar_start = 479258400;
	testvar_end = 1308741908;
	calendar_timestamp_to_date(testvar_start, &testcal_start);
	calendar_timestamp_to_date(testvar_end, &testcal_end);

	calendar_time_between_dates(&testcal_end, &testcal_start, &actual);

	test_assert_true(test, actual.second == expected.second,
			"Second mismatch %d != %d", actual.second, expected.second);
	test_assert_true(test, actual.minute == expected.minute,
			"Minute mismatch %d != %d", actual.minute, expected.minute);
	test_assert_true(test, actual.hour == expected.hour,
			"Hour mismatch %d != %d", actual.hour, expected.hour);
	test_assert_true(test, actual.date == expected.date,
			"Date mismatch %d != %d", actual.date, expected.date);
	test_assert_true(test, actual.month == expected.month,
			"Month mismatch %d != %d", actual.month, expected.month);
	test_assert_true(test, actual.year == expected.year,
			"Year mismatch %d != %d", actual.year, expected.year);
}

/**
* \internal
 * \brief Test computation of time between dates several years apart
 *
 * This test checks that computing time between dates several years apart
 * results in the expected duration.
 *
 * \param test Current test case.
 */
static void run_time_between_dates_years2_test(const struct test_case *test)
{
	struct calendar_date expected;
	struct calendar_date actual;
	uint32_t testvar_start;
	uint32_t testvar_end;

	struct calendar_date testcal_end;
	struct calendar_date testcal_start;

	expected.second = 16;
	expected.minute = 11;
	expected.hour = 8;
	expected.date = 11;
	expected.month = 6;
	expected.year = 20;

	testvar_start = 288109292;
	testvar_end = 935879568;
	calendar_timestamp_to_date(testvar_start, &testcal_start);
	calendar_timestamp_to_date(testvar_end, &testcal_end);

	calendar_time_between_dates(&testcal_end, &testcal_start, &actual);

	test_assert_true(test, actual.second == expected.second,
			"Second mismatch %d != %d", actual.second, expected.second);
	test_assert_true(test, actual.minute == expected.minute,
			"Minute mismatch %d != %d", actual.minute, expected.minute);
	test_assert_true(test, actual.hour == expected.hour,
			"Hour mismatch %d != %d", actual.hour, expected.hour);
	test_assert_true(test, actual.date == expected.date,
			"Date mismatch %d != %d", actual.date, expected.date);
	test_assert_true(test, actual.month == expected.month,
			"Month mismatch %d != %d", actual.month, expected.month);
	test_assert_true(test, actual.year == expected.year,
			"Year mismatch %d != %d", actual.year, expected.year);
}

/**
* \internal
 * \brief Test computation of time between dates with end before start
 *
 * This test checks that computing time between dates several years apart
 * where end date is earlier than start date results in the expected duration.
 *
 * \param test Current test case.
 */
static void run_time_between_dates_exchanged_test(const struct test_case *test)
{
	struct calendar_date expected;
	struct calendar_date actual;
	uint32_t testvar_start;
	uint32_t testvar_end;

	struct calendar_date testcal_end;
	struct calendar_date testcal_start;

	expected.second = 16;
	expected.minute = 11;
	expected.hour = 8;
	expected.date = 11;
	expected.month = 6;
	expected.year = 20;

	testvar_start = 935879568;
	testvar_end = 288109292;

	calendar_timestamp_to_date(testvar_start, &testcal_start);
	calendar_timestamp_to_date(testvar_end, &testcal_end);

	calendar_time_between_dates(&testcal_end, &testcal_start, &actual);

	test_assert_true(test, actual.second == expected.second,
			"Second mismatch %d != %d", actual.second, expected.second);
	test_assert_true(test, actual.minute == expected.minute,
			"Minute mismatch %d != %d", actual.minute, expected.minute);
	test_assert_true(test, actual.hour == expected.hour,
			"Hour mismatch %d != %d", actual.hour, expected.hour);
	test_assert_true(test, actual.date == expected.date,
			"Date mismatch %d != %d", actual.date, expected.date);
	test_assert_true(test, actual.month == expected.month,
			"Month mismatch %d != %d", actual.month, expected.month);
	test_assert_true(test, actual.year == expected.year,
			"Year mismatch %d != %d", actual.year, expected.year);
}

/**
 * \internal
 * \brief Test adding one second to a normal date
 *
 * This test checks that incrementing a normal date with one second gives
 * the correct result.
 *
 * \param test Current test case.
 */
static void run_add_second_to_normal_date_test(const struct test_case *test)
{
	struct calendar_date actual;
	struct calendar_date expected;

	// Add one second to a normal date
	actual.second = 45;
	actual.minute = 19;
	actual.hour = 22;
	actual.date = 12;
	actual.month = 2;
	actual.year = 2001;

	expected.second = 46;
	expected.minute = 19;
	expected.hour = 22;
	expected.date = 12;
	expected.month = 2;
	expected.year = 2001;

	calendar_add_second_to_date(&actual);
	test_assert_true(test, actual.second == expected.second,
			"Second mismatch %d != %d", actual.second, expected.second);
	test_assert_true(test, actual.minute == expected.minute,
			"Minute mismatch %d != %d", actual.minute, expected.minute);
	test_assert_true(test, actual.hour == expected.hour,
			"Hour mismatch %d != %d", actual.hour, expected.hour);
	test_assert_true(test, actual.date == expected.date,
			"Date mismatch %d != %d", actual.date, expected.date);
	test_assert_true(test, actual.month == expected.month,
			"Month mismatch %d != %d", actual.month, expected.month);
	test_assert_true(test, actual.year == expected.year,
			"Year mismatch %d != %d", actual.year, expected.year);
}

/**
 * \internal
 * \brief Test adding one second to the end of a day
 *
 * This test checks that incrementing the end of a day with one second gives
 * the correct result.
 *
 * \param test Current test case.
 */
static void run_add_second_to_end_of_day_test(const struct test_case *test)
{
	struct calendar_date actual;
	struct calendar_date expected;

	actual.second = 59;
	actual.minute = 59;
	actual.hour = 23;
	actual.date = 11;
	actual.month = 8;
	actual.year = 2005;

	expected.second = 0;
	expected.minute = 0;
	expected.hour = 0;
	expected.date = 12;
	expected.month = 8;
	expected.year = 2005;

	calendar_add_second_to_date(&actual);
	test_assert_true(test, actual.second == expected.second,
			"Second mismatch %d != %d", actual.second, expected.second);
	test_assert_true(test, actual.minute == expected.minute,
			"Minute mismatch %d != %d", actual.minute, expected.minute);
	test_assert_true(test, actual.hour == expected.hour,
			"Hour mismatch %d != %d", actual.hour, expected.hour);
	test_assert_true(test, actual.date == expected.date,
			"Date mismatch %d != %d", actual.date, expected.date);
	test_assert_true(test, actual.month == expected.month,
			"Month mismatch %d != %d", actual.month, expected.month);
	test_assert_true(test, actual.year == expected.year,
			"Year mismatch %d != %d", actual.year, expected.year);
}

/**
 * \internal
 * \brief Test adding one second to the 28th of February, normal year
 *
 * This test checks that incrementing the end of February 28th in a year
 * that is not a leap year with one second results in March 1st.
 *
 * \param test Current test case.
 */
static void run_add_second_to_end_feb_test(const struct test_case *test)
{
	struct calendar_date actual;
	struct calendar_date expected;

	actual.second = 59;
	actual.minute = 59;
	actual.hour = 23;
	actual.date = 27;
	actual.month = 1;
	actual.year = 2011;

	expected.second = 0;
	expected.minute = 0;
	expected.hour = 0;
	expected.date = 0;
	expected.month = 2;
	expected.year = 2011;

	calendar_add_second_to_date(&actual);
	test_assert_true(test, actual.second == expected.second,
			"Second mismatch %d != %d", actual.second, expected.second);
	test_assert_true(test, actual.minute == expected.minute,
			"Minute mismatch %d != %d", actual.minute, expected.minute);
	test_assert_true(test, actual.hour == expected.hour,
			"Hour mismatch %d != %d", actual.hour, expected.hour);
	test_assert_true(test, actual.date == expected.date,
			"Date mismatch %d != %d", actual.date, expected.date);
	test_assert_true(test, actual.month == expected.month,
			"Month mismatch %d != %d", actual.month, expected.month);
	test_assert_true(test, actual.year == expected.year,
			"Year mismatch %d != %d", actual.year, expected.year);
}

/**
 * \internal
 * \brief Test adding one second to the 28th of February, leap year
 *
 * This test checks that incrementing the end of February 28th in a year
 * that is not a leap year with one second results in February 29th.
 *
 * \param test Current test case.
 */
static void run_add_second_to_leap_year_feb_test(const struct test_case *test)
{
	struct calendar_date actual;
	struct calendar_date expected;

	actual.second = 59;
	actual.minute = 59;
	actual.hour = 23;
	actual.date = 27;
	actual.month = 1;
	actual.year = 2008;

	expected.second = 0;
	expected.minute = 0;
	expected.hour = 0;
	expected.date = 28;
	expected.month = 1;
	expected.year = 2008;

	calendar_add_second_to_date(&actual);
	test_assert_true(test, actual.second == expected.second,
			"Second mismatch %d != %d", actual.second, expected.second);
	test_assert_true(test, actual.minute == expected.minute,
			"Minute mismatch %d != %d", actual.minute, expected.minute);
	test_assert_true(test, actual.hour == expected.hour,
			"Hour mismatch %d != %d", actual.hour, expected.hour);
	test_assert_true(test, actual.date == expected.date,
			"Date mismatch %d != %d", actual.date, expected.date);
	test_assert_true(test, actual.month == expected.month,
			"Month mismatch %d != %d", actual.month, expected.month);
	test_assert_true(test, actual.year == expected.year,
			"Year mismatch %d != %d", actual.year, expected.year);
}

/**
 * \internal
 * \brief Test adding one second to the end of February, leap year
 *
 * This test checks that incrementing the end of February 29th in a year
 * that is a leap year with one second results in March 1st.
 *
 * \param test Current test case.
 */
static void run_add_second_to_leap_year_feb2_test(const struct test_case *test)
{
	struct calendar_date actual;
	struct calendar_date expected;

	actual.second = 59;
	actual.minute = 59;
	actual.hour = 23;
	actual.date = 28;
	actual.month = 1;
	actual.year = 2008;

	expected.second = 0;
	expected.minute = 0;
	expected.hour = 0;
	expected.date = 0;
	expected.month = 2;
	expected.year = 2008;

	calendar_add_second_to_date(&actual);
	test_assert_true(test, actual.second == expected.second,
			"Second mismatch %d != %d", actual.second, expected.second);
	test_assert_true(test, actual.minute == expected.minute,
			"Minute mismatch %d != %d", actual.minute, expected.minute);
	test_assert_true(test, actual.hour == expected.hour,
			"Hour mismatch %d != %d", actual.hour, expected.hour);
	test_assert_true(test, actual.date == expected.date,
			"Date mismatch %d != %d", actual.date, expected.date);
	test_assert_true(test, actual.month == expected.month,
			"Month mismatch %d != %d", actual.month, expected.month);
	test_assert_true(test, actual.year == expected.year,
			"Year mismatch %d != %d", actual.year, expected.year);
}

/**
 * \internal
 * \brief Test adding one second to the end of a year
 *
 * This test checks that incrementing the end of a day year results in
 * start of a new year.
 *
 * \param test Current test case.
 */
static void run_add_second_to_end_of_year_test(const struct test_case *test)
{
	struct calendar_date actual;
	struct calendar_date expected;

	actual.second = 59;
	actual.minute = 59;
	actual.hour = 23;
	actual.date = 30;
	actual.month = 11;
	actual.year = 1993;

	expected.second = 0;
	expected.minute = 0;
	expected.hour = 0;
	expected.date = 0;
	expected.month = 0;
	expected.year = 1994;

	calendar_add_second_to_date(&actual);
	test_assert_true(test, actual.second == expected.second,
			"Second mismatch %d != %d", actual.second, expected.second);
	test_assert_true(test, actual.minute == expected.minute,
			"Minute mismatch %d != %d", actual.minute, expected.minute);
	test_assert_true(test, actual.hour == expected.hour,
			"Hour mismatch %d != %d", actual.hour, expected.hour);
	test_assert_true(test, actual.date == expected.date,
			"Date mismatch %d != %d", actual.date, expected.date);
	test_assert_true(test, actual.month == expected.month,
			"Month mismatch %d != %d", actual.month, expected.month);
	test_assert_true(test, actual.year == expected.year,
			"Year mismatch %d != %d", actual.year, expected.year);
}
//@}

/**
 * \brief Run calendar service unit tests
 *
 * Initializes the clock system, board and serial output, then sets up the
 * calendar unit test suite and runs it.
 */
int main(void)
{

	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits   = CONF_TEST_STOPBITS,
	};
	sysclk_init();
	board_init();
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	// Define all the timestamp to date test cases
	DEFINE_TEST_CASE(timestamp_to_normal_date_test, NULL,
			run_timestamp_to_normal_date_test, NULL,
			"Stamp to normal date test");
	DEFINE_TEST_CASE(timestamp_0_to_date_test, NULL,
			run_timestamp_0_to_date_test, NULL, "Stamp 0 to date test");
	DEFINE_TEST_CASE(timestamp_to_leap_year_date_test, NULL,
			run_timestamp_to_leap_year_date_test, NULL,
			"Stamp to leap year date test");
	DEFINE_TEST_CASE(timestamp_to_leap_year_date2_test, NULL,
			run_timestamp_to_leap_year_date2_test, NULL,
			"Stamp to leap year date2 test");

	// Define all the date to timestamp test cases
	DEFINE_TEST_CASE(date_to_timestamp_0_test, NULL,
			run_date_to_timestamp_0_test, NULL, "Date to stamp 0 test");
	DEFINE_TEST_CASE(erronous_time_to_timestamp_test, NULL,
			run_erronous_time_to_timestamp_test, NULL,
			"Erronous time to stamp test");
	DEFINE_TEST_CASE(erronous_date_to_timestamp_test, NULL,
			run_erronous_date_to_timestamp_test, NULL,
			"Erronous date to stamp test");
	DEFINE_TEST_CASE(leap_year_date_to_timestamp_test, NULL,
			run_leap_year_date_to_timestamp_test, NULL,
			"Leap year date to stamp test");
	DEFINE_TEST_CASE(date_to_timestamp_test, NULL,
			run_date_to_timestamp_test, NULL, "Date to stamp test");
	DEFINE_TEST_CASE(date_1855_to_timestamp_test, NULL,
			run_date_1855_to_timestamp_test, NULL, "1855 date to stamp test");
	DEFINE_TEST_CASE(date_2107_to_timestamp_test, NULL,
			run_date_2107_to_timestamp_test, NULL, "2107 date to stamp test");

	// Define all the time between dates test cases
	DEFINE_TEST_CASE(time_between_dates_same_year_test, NULL,
			run_time_between_dates_same_year_test, NULL,
			"Time between dates in same year test");
	DEFINE_TEST_CASE(time_between_dates_diff_year_test, NULL,
			run_time_between_dates_diff_year_test, NULL,
			"Time between dates in different years test");
	DEFINE_TEST_CASE(time_between_dates_leap_year_test, NULL,
			run_time_between_dates_leap_year_test, NULL,
			"Time between dates in leap year test");
	DEFINE_TEST_CASE(time_between_dates_years_test, NULL,
			run_time_between_dates_years_test, NULL,
			"Time between dates several years apart test");
	DEFINE_TEST_CASE(time_between_dates_years2_test, NULL,
			run_time_between_dates_years2_test, NULL,
			"Time between dates several years apart test2");
	DEFINE_TEST_CASE(time_between_dates_exchanged_test, NULL,
			run_time_between_dates_exchanged_test, NULL,
			"Time between dates with end before start test");

			// Define all the add second to date test cases
	DEFINE_TEST_CASE(add_second_to_normal_date_test, NULL,
			run_add_second_to_normal_date_test, NULL,
			"Add second to normal date test");
	DEFINE_TEST_CASE(add_second_to_end_of_day_test, NULL,
			run_add_second_to_end_of_day_test, NULL,
			"Add second to end of day test");
	DEFINE_TEST_CASE(add_second_to_end_feb_test, NULL,
			run_add_second_to_end_feb_test, NULL,
			"Add second to 28th of February, normal year test");
	DEFINE_TEST_CASE(add_second_to_leap_year_feb_test, NULL,
			run_add_second_to_leap_year_feb_test, NULL,
			"Add second to 28th of February, leap year test");
	DEFINE_TEST_CASE(add_second_to_leap_year_feb2_test, NULL,
			run_add_second_to_leap_year_feb2_test, NULL,
			"Add second to 29th of February, leap year test");
	DEFINE_TEST_CASE(add_second_to_end_of_year_test, NULL,
			run_add_second_to_end_of_year_test, NULL,
			"Add second to end of year test");

	// Put test case addresses in an array
	DEFINE_TEST_ARRAY(calendar_tests) = {
		&timestamp_to_normal_date_test,
		&timestamp_0_to_date_test,
		&timestamp_to_leap_year_date_test,
		&timestamp_to_leap_year_date2_test,
		&date_to_timestamp_0_test,
		&erronous_time_to_timestamp_test,
		&erronous_date_to_timestamp_test,
		&leap_year_date_to_timestamp_test,
		&date_to_timestamp_test,
		&date_1855_to_timestamp_test,
		&date_2107_to_timestamp_test,
		&time_between_dates_same_year_test,
		&time_between_dates_diff_year_test,
		&time_between_dates_leap_year_test,
		&time_between_dates_years_test,
		&time_between_dates_years2_test,
		&time_between_dates_exchanged_test,
		&add_second_to_normal_date_test,
		&add_second_to_end_of_day_test,
		&add_second_to_end_feb_test,
		&add_second_to_leap_year_feb_test,
		&add_second_to_leap_year_feb2_test,
		&add_second_to_end_of_year_test,
	};

	// Define the test suite
	DEFINE_TEST_SUITE(calendar_suite, calendar_tests,
			"Common calendar service with test suite");

	// Run all tests in the suite
	test_suite_run(&calendar_suite);

	while (1) {
		// Intentionally left empty.
	}
}
