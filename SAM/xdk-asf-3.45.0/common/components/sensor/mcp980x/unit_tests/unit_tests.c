/**
 * \file
 *
 * \brief Unit tests for MCP980X driver.
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
#include <mcp980x.h>
#include <string.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <conf_test.h>
#include <conf_board.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the MCP980X driver.
 * It consists of test cases for the following functionality:
 * - Temperature range (from 0 to 35)
 * - Temperature change (the delta is supposed to be lower than 5)
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 *
 * \section device_info Device Info
 * Only SAM3U can be used since MCP9800 is available only on SAM3U-EK.

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
 * \def CONF_TEST_MCP980X
 * \brief Init TWI, read temperature values returned by MCP980X and check them.
 */
//@}

#define MCP980X_MAX_SAMPLES   5
#define MCP980X_LOWEST_TEMP  10
#define MCP980X_HIGHEST_TEMP 40
#define MCP980X_TEMP_DELTA    5

/* A counter for temperature samples */
static volatile uint32_t temp_counter = 0U;

/* A buffer to store temperature values */
static int8_t temp_buf[MCP980X_MAX_SAMPLES] = { 0U };

/* A flag to indicate if the test case is successful */
static volatile uint8_t mcp980x_test_flag = 0U;

/* Systick Counter */
static volatile uint32_t dw_ms_ticks = 0U;


/**
 * \brief SysTick handler.
 */
void SysTick_Handler(void)
{
	/* Increment counter necessary in delay(). */
	dw_ms_ticks++;
}

/**
 * \brief Delay number of tick Systicks (happens every 1 ms).
 */
static void mdelay(uint32_t dw_dly_ticks)
{
	uint32_t dw_cur_ticks;

	dw_cur_ticks = dw_ms_ticks;
	while ((dw_ms_ticks - dw_cur_ticks) < dw_dly_ticks) {
	}
}

/**
 * \brief Test MCP980X
 *
 * This test reads temperature values returned by MCP980X every 100ms and check if the temperature is delightful.
 *
 * \param test Current test case.
 */
static void run_mcp980x_test(const struct test_case *test)
{
	/* Initialize MCP980X driver. */
	mcp980x_init();

	/* Set MCP980X configuration.
	 * Disable ONE-SHOT mode;
	 * 12-bit ADC resolution;
	 * 2 fault queue cycles;
	 * Active-high alert polarity;
	 * Alert output in interrupt mode;
	 * Disable shutdown mode.
	 */
	mcp980x_set_configuration(
			MCP980X_CONFIG_RESOLUTION_12_BIT          |
			MCP980X_CONFIG_FAULT_QUEUE_2              |
			MCP980X_CONFIG_ALERT_POLARITY_ACTIVE_HIGH |
			MCP980X_CONFIG_INTERRUPT_MODE);

	uint32_t i = 0;
	uint32_t ul_unused = 0;
	for (; i < MCP980X_MAX_SAMPLES; i++) {
		/* Enable One-Shot mode to perform a single temperature measurement. */
		if (TWI_SUCCESS != mcp980x_one_shot_mode()) {
			mcp980x_test_flag = 1;
			break;
		}

		/* Retrieve ambient temperature every 100ms. */
		mdelay(100);
		if (TWI_SUCCESS != mcp980x_get_temperature(&temp_buf[i], &ul_unused)) {
			mcp980x_test_flag = 1;
			break;
		}
	}

	/* Test1: if TWI bus operation is successful */
	test_assert_true(test, mcp980x_test_flag == 0, "Test1: TWI bus operation is aborted!");

	/* Test2: if the temperature values returned are correct */
	for (i = 0; i < MCP980X_MAX_SAMPLES; i++) {
		if ((temp_buf[i] > MCP980X_HIGHEST_TEMP) || (temp_buf[i] < MCP980X_LOWEST_TEMP)) {
			mcp980x_test_flag = 1;
			break;
		}
	}
	test_assert_true(test, mcp980x_test_flag == 0, "Test2: The temperature is undelightful!");

	/* Test3: if the temperature change is reasonable */
	volatile int8_t temp_delta = 0;
	for (i = 0; i < (MCP980X_MAX_SAMPLES - 1); i++) {
		temp_delta = (temp_buf[i] > temp_buf[i + 1]) ?
				(temp_buf[i] - temp_buf[i + 1]) : (temp_buf[i + 1] - temp_buf[i]);
		if (temp_delta > MCP980X_TEMP_DELTA) {
			mcp980x_test_flag = 1;
			break;
		}
	}
	test_assert_true(test, mcp980x_test_flag == 0, "Test3: The temperature change is unreasonable!");
}

/**
 * \brief Run MCP980X driver unit tests
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
		.paritytype = CONF_TEST_PARITY
	};

	sysclk_init();
	board_init();

	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Set up SysTick Timer for 1 msec interrupts. */
	if (SysTick_Config(sysclk_get_cpu_hz() / 1000)) {
		/* Capture error. */
		while (1) {
		}
	}

	/* Define all the test cases */
	DEFINE_TEST_CASE(mcp980x_test, NULL, run_mcp980x_test, NULL,
		"Init TWI, read temperature values returned by MCP980X and check them.");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(mcp980x_tests) = {
		&mcp980x_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(mcp980x_suite, mcp980x_tests, "SAM MCP980X test suite");

	/* Run all tests in the test suite */
	test_suite_run(&mcp980x_suite);

	while (1) {
		/* Busy-wait forever. */
	}
}
