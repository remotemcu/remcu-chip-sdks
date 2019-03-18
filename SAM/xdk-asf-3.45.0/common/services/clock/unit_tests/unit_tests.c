/**
 * \file
 *
 * \brief Unit tests for common clock service
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
#include <string.h>

#include <compiler.h>
#include <asf.h>
#include "conf_test.h"

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the \ref sysclk.h "Common Clock service".
 * It consists of test cases for the following:
 * - Oscillator 0/1 test
 * - 32KHz Oscillator test
 * - Pll and Dfll test
 * - Synchronous clock test
 * - Generic clock test
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 *
 * \section device_info Device Info
 * All AVR and SAM4L devices can be used.
 * This example has been tested with the following setup:
 * - EVK1100
 * - EVK1101
 * - EVK1104
 * - EVK1105
 * - UC3C_EK
 * - UC3L_EK
 * - STK600+RCUC3D
 * - SAM4L-EK
 * - SAM4L Xplained Pro Board.
 * - SAM4L8 Xplained Pro Board.
 *
 * \section description Description of the unit tests
 * See the documentation for the individual unit test functions \ref unit_tests.c
 * "here" for detailed descriptions of the tests.
 *
 * \section dependencies Dependencies
 * This example depends directly on the following modules:
 * - \ref test_suite_group
 * - \ref sysclk.h "Common Clock service"
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

//! Pointer to the external low level write function.
extern int (*ptr_put)(void volatile*,char);

//! USART initialize with the CONFIG_PBA_HZ
int usart_ready = 0;

//! \name Common Clock unit test functions
//@{
/**
 * \brief Test Oscillator 0/1
 *
 * This test enables the oscillator 0 and 1 (if have), and then
 * check if they can be stable and ready for main clock after
 * startup time
 *
 * \param test Current test case.
 */
static void run_osc_test(const struct test_case *test)
{
	volatile uint32_t wait;
	bool status;
	/* avoid Cppcheck Warning */
	UNUSED(wait);
	UNUSED(status);
	
#ifdef BOARD_OSC0_HZ
	osc_enable(OSC_ID_OSC0);
	for (wait  =0; wait < OSC0_STARTUP_TIMEOUT; wait++) {
		//waiting the oscillator0 stable
		__asm__("nop");
	};
	status = osc_is_ready(OSC_ID_OSC0);
	test_assert_true(test, status, "Oscillator 0 is not stable");
#endif

#ifdef BOARD_OSC1_HZ
	osc_enable(OSC_ID_OSC1);
	for (wait = 0; wait < OSC1_STARTUP_TIMEOUT; wait++) {
		//waiting the oscillator1 stable
		__asm__("nop");
	};
	status = osc_is_ready(OSC_ID_OSC1);
	test_assert_true(test, status, "Oscillator 1 is not stable");
#endif

#ifdef BOARD_RC8M_HZ
	osc_enable(OSC_ID_RC8M);
	status = osc_is_ready(OSC_ID_RC8M);
	test_assert_true(test, status, "8M/1M RC oscillator is not stable");
#endif

#ifdef BOARD_RC120_HZ
	osc_enable(OSC_ID_RC120M);
	status = osc_is_ready(OSC_ID_RC120M);
	test_assert_true(test, status, "120M RC oscillator is not stable");
#endif

#ifdef BOARD_RC1M_HZ
	osc_enable(OSC_ID_RC1M);
	status = osc_is_ready(OSC_ID_RC1M);
	test_assert_true(test, status, "1M RC oscillator is not stable");
#endif

#ifdef BOARD_RC80M_HZ
	osc_enable(OSC_ID_RC80M);
	status = osc_is_ready(OSC_ID_RC80M);
	test_assert_true(test, status, "80M RC oscillator is not stable");
#endif

#ifdef BOARD_RCFAST_HZ
	osc_enable(OSC_ID_RCFAST);
	status = osc_is_ready(OSC_ID_RCFAST);
	test_assert_true(test, status, "RCFAST oscillator is not stable");
#endif

}

/**
 * \brief cleanup oscillator test
 *
 * \param test Current test case.
 */
static void cleanup_osc_test(const struct test_case *test)
{
#ifdef BOARD_OSC0_HZ
	osc_disable(OSC_ID_OSC0);
#endif

#ifdef BOARD_OSC1_HZ
	osc_disable(OSC_ID_OSC1);
#endif

#ifdef BOARD_RC8M_HZ
	osc_disable(OSC_ID_RC8M);
#endif

#ifdef BOARD_RC120_HZ
	osc_disable(OSC_ID_RC120M);
#endif

#ifdef BOARD_RC1M_HZ
	osc_disable(OSC_ID_RC1M);
#endif

#ifdef BOARD_RC80M_HZ
	osc_disable(OSC_ID_RC80M);
#endif

#ifdef BOARD_RCFAST_HZ
	osc_disable(OSC_ID_RCFAST);
#endif

}

/**
 * \brief Test 32KHz oscillator
 *
 * This test enables the 32KHz oscillator, and then
 * check if they can be used after startup time
 *
 * \param test Current test case.
 */
static void run_osc32_test(const struct test_case *test)
{
#ifdef BOARD_OSC32_HZ
	uint32_t osc32_startup_timeout;
	volatile uint32_t wait;
	bool status;

	osc_enable(OSC_ID_OSC32);
	osc32_startup_timeout = OSC_RCSYS_NOMINAL_HZ/4;
	// wait for 1s
	for (wait = 0; wait < osc32_startup_timeout; wait++) {
		//waiting the 32KHz oscillator ready
		__asm__("nop");
	};
	status = osc_is_ready(OSC_ID_OSC32);
	test_assert_true(test, status, "32KHz oscillator is not stable");
#endif
}

/**
 * \brief cleanup 32KHz oscillator test
 *
 * \param test Current test case.
 */
static void cleanup_osc32_test(const struct test_case *test)
{

#ifdef BOARD_OSC32_HZ
	osc_disable(OSC_ID_OSC32);
#endif

}

/**
 * \brief Test Pll and DFLL (if have)
 *
 * This test enables pll/dfll source clock, sets its mul and div
 * factor, and then enables it. Check if it's locked after max
 * startup time.
 *
 * \param test Current test case.
 */
static void run_pll_dfll_test(const struct test_case *test)
{
	uint32_t wait;
	bool status;
	/* avoid Cppcheck Warning */
	UNUSED(wait);
	UNUSED(status);

#if (defined CONFIG_PLL0_SOURCE) || (defined CONFIG_PLL1_SOURCE)
	struct pll_config pllcfg;
#endif

#ifdef CONFIG_PLL0_SOURCE
	pll_enable_source(CONFIG_PLL0_SOURCE);
	pll_config_defaults(&pllcfg, 0);
	pll_enable(&pllcfg, PLL0);
	for (wait = 0; wait < PLL_MAX_STARTUP_CYCLES; wait++) {
		//waiting PLL0 lock
		__asm__("nop");
	};
	status = pll_is_locked(PLL0);
	test_assert_true(test, status, "PLL0 can't be locked");
#endif

#ifdef CONFIG_PLL1_SOURCE
	pll_enable_source(CONFIG_PLL1_SOURCE);
	pll_config_defaults(&pllcfg, 1);
	pll_enable(&pllcfg, PLL1);
	for (wait = 0; wait < PLL_MAX_STARTUP_CYCLES; wait++) {
		//waiting PLL1 lock
		__asm__("nop");
	};
	status = pll_is_locked(PLL1);
	test_assert_true(test, status, "PLL1 can't be locked");
#endif

#ifdef CONFIG_DFLL0_SOURCE
	struct dfll_config dfllcfg;
	osc_enable(OSC_ID_RCSYS);
	osc_wait_ready(OSC_ID_RCSYS);
	dfll_config_defaults(&dfllcfg, 0);
	dfll_enable_closed_loop(&dfllcfg, 0);
	for (wait = 0; wait < DFLL_MAX_LOCK_CYCLES; wait++) {
		//waiting DFLL lock
		__asm__("nop");
	};
	status = dfll_is_fine_locked(0);
	test_assert_true(test, status, "DFLL can't be locked");
#endif

}

/**
 * \brief cleanup pll/dfll test
 *
 * \param test Current test case.
 */
static void cleanup_pll_dfll_test(const struct test_case *test)
{

#ifdef CONFIG_PLL0_SOURCE
	pll_disable(PLL0);
#endif

#ifdef CONFIG_PLL1_SOURCE
	pll_disable(PLL1);
#endif

#ifdef CONFIG_DFLL0_SOURCE
	dfll_disable_closed_loop(0);
	osc_disable(OSC_ID_RCSYS);
#endif

}

/**
 * \brief Test Synchronous clock
 *
 * This test enables source clock for main clock, sets CPU/HSB,
 * PBA,PBB,PBC(if have), PBD(if have) division factor, and then check
 * if the chip is set correctly.
 *
 * \note It's not easy to measure CPU/HSB,PBA... frequency, even through
 * some chips have freqm module. Using external module may cause some
 * reliability issue. Since synchronous clocks share the common root
 * main clock, they only need set division factor. So we just test
 * the related registers if set correctly after calling common clock
 * service.
 *
 * \param test Current test case.
 */
static void run_sync_clock_test(const struct test_case *test)
{
	bool status;
	/* avoid Cppcheck Warning */
	UNUSED(status);

	sysclk_init();
	//PBA clock set, usart can be used
	usart_ready = 1;

#ifdef CONFIG_CPU_HZ
	status = (CONFIG_CPU_HZ == sysclk_get_cpu_hz());
	test_assert_true(test, status, "CPU clock set fail");
#endif

#ifdef CONFIG_PBA_HZ
	status = (CONFIG_PBA_HZ == sysclk_get_pba_hz());
	test_assert_true(test, status, "PBA clock set fail");
#endif

#ifdef CONFIG_PBB_HZ
	status = (CONFIG_PBB_HZ == sysclk_get_pbb_hz());
	test_assert_true(test, status, "PBB clock set fail");
#endif

#ifdef CONFIG_PBC_HZ
	status = (CONFIG_PBC_HZ == sysclk_get_pbc_hz());
	test_assert_true(test, status, "PBC clock set fail");
#endif

#ifdef CONFIG_PBD_HZ
	status = (CONFIG_PBD_HZ == sysclk_get_pbd_hz());
	test_assert_true(test, status, "PBD clock set fail");
#endif
}

/**
 * \brief Test Generic clock
 *
 * This test enables the generic clock, sets its source and
 * division factor, and then check if it's set correctly.
 *
 * \param test Current test case.
 */
static void run_generic_clock_test(const struct test_case *test)
{
	struct genclk_config gencfg;
	bool status;
	genclk_config_defaults(&gencfg, CONFIG_GENERIC_ID);
	genclk_config_set_source(&gencfg, CONFIG_GENERIC_SRC);
	genclk_config_set_divider(&gencfg, CONFIG_GENERIC_DIV);
	genclk_enable(&gencfg, CONFIG_GENERIC_ID);

	status = (CONFIG_GENERIC_CLOCK == get_generic_clock());
	test_assert_true(test, status, "Generic clock set fail");
}

/**
 * \brief cleanup generic clock test
 *
 * \param test Current test case.
 */
static void cleanup_generic_clock_test(const struct test_case *test)
{
	genclk_disable(CONFIG_GENERIC_ID);
}

//@}

/**
 * \brief Run Common Clock service unit tests
 *
 * Initializes board, serial output, then sets up the
 * clock unit test suite and runs it.
 */
int main (void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits   = CONF_TEST_STOPBITS,
	};

	board_init();
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	//set the low level write function
	//usart can work only after we call sysclk_init, because the
	//PBA clock initialized with correct value which used by usart
	//So, we output the information to one buffer before usart can work.
	ptr_put = (int (*)(void volatile*,char))&usart_write_char_buf;

	// Define all the test cases.
	DEFINE_TEST_CASE(osc_test, NULL, run_osc_test, cleanup_osc_test,
			"Oscillator0/1 test");
	DEFINE_TEST_CASE(osc32_test, NULL, run_osc32_test, cleanup_osc32_test,
			"32KHz oscillator test");
	DEFINE_TEST_CASE(pll_dfll_test, NULL, run_pll_dfll_test,
			cleanup_pll_dfll_test, "Pll or Dfll test");
	DEFINE_TEST_CASE(sync_clock_test, NULL, run_sync_clock_test, NULL,
			"CPU/HSB, peripheral bridge clock test");
	DEFINE_TEST_CASE(generic_clock_test, NULL, run_generic_clock_test,
			cleanup_generic_clock_test, "Generic clock test");

	// Put test case addresses in an array.
	DEFINE_TEST_ARRAY(clock_tests) = {
		&osc_test,
		&osc32_test,
		&pll_dfll_test,
		&sync_clock_test,
		&generic_clock_test,
	};

	// Define the test suite.
	DEFINE_TEST_SUITE(clock_suite, clock_tests, "Clock service unit test suite");

	// Run all tests in the test suite.
	test_suite_run(&clock_suite);

	while (true) {
		__asm__("nop");
	};
}
