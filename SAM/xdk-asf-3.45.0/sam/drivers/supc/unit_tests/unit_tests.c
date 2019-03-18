/**
 * \file
 *
 * \brief Unit tests for SUPC driver.
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
#include <board.h>
#include <sysclk.h>
#include <supc.h>
#include <string.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <conf_test.h>
#include <conf_board.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the SUPC driver.
 * It consists of test cases for the following functionality:
 * - Slow clock source switching
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 *
 * \section device_info Device Info
 * All SAM devices can be used.
 * This example has been tested with the following setup:
 * - sam3n4c_sam3n_ek
 * - sam3s4c_sam3s_ek
 * - sam3sd8c_sam3s_ek2
 * - sam3u4e_sam3u_ek
 * - sam3x8h_sam3x_ek
 * - sam4s16c_sam4s_ek
 * - sam4sd32c_sam4s_ek2
 * - sam4sd32c_atpl230amb
 * - sam4n16c_sam4n_xplained_pro
 * - sam4c16c_sam4c_ek
 * - sam4cp16b_sam4cp16bmb
 * - sam4cmp16c_sam4cmp_db
 * - sam4cms16c_sam4cms_db
 * - samv71q21_samv71_xplained_ultra
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
 * \def CONF_TEST_SUPC
 * \brief Switch slow clock source to the crystal oscillator output.
 */
//@}

#define SLOW_CLK_TIMEOUT 0xFFFFFFFF

/* Systick Counter */
static volatile uint32_t gs_ul_ms_ticks = 0U;

/**
 * \brief SysTick handler.
 */
void SysTick_Handler(void)
{
	/* Increment counter necessary in delay(). */
	gs_ul_ms_ticks++;
}

/**
 * \brief Test slow clock source switching.
 *
 * This test switches the slow clock on the crystal oscillator output.
 *
 * \param test Current test case.
 */
static void run_supc_test(const struct test_case *test)
{
	uint32_t status = 0;
	uint32_t timeout = 0;

	/* Test: Switch the slow clock on the crystal oscillator output */
	supc_switch_sclk_to_32kxtal(SUPC, 0);
	do {
		status = supc_get_status(SUPC);
		if (status & SUPC_SR_OSCSEL_CRYST) break;
	} while (timeout++ < SLOW_CLK_TIMEOUT);
	test_assert_true(test, (status & SUPC_SR_OSCSEL_CRYST) == SUPC_SR_OSCSEL_CRYST, "Test: switching slow clock source failed!");
}

/**
 * \brief Run SUPC driver unit tests.
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
#ifdef CONF_TEST_CHAR_LENGTH
		.charlength = CONF_TEST_CHAR_LENGTH,
#endif
		.paritytype = CONF_TEST_PARITY,
#ifdef CONF_TEST_STOP_BITS
		.stopbits = CONF_TEST_STOP_BITS,
#endif
	};

	sysclk_init();
	board_init();

	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Set up SysTick Timer for 1 msec interrupts */
	if (SysTick_Config(sysclk_get_cpu_hz() / 1000)) {
		/* Capture error */
		while (1) {
		}
	}

	/* Define all the test cases */
	DEFINE_TEST_CASE(supc_test, NULL, run_supc_test, NULL,
		"SUPC slow clock source switching");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(supc_tests) = {
		&supc_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(supc_suite, supc_tests, "SAM SUPC driver test suite");

	/* Run all tests in the test suite */
	test_suite_run(&supc_suite);

	while (1) {
		/* Busy-wait forever */
	}
}
