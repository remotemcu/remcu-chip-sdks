/**
 * \file
 *
 * \brief Unit tests for PMC driver.
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
#include <pmc.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <conf_test.h>
#include <conf_board.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the PMC driver.
 * It consists of test cases for the following functionalities:
 * - Enable and disable peripheral clocks
 * - Switch slow clock as MCK and enable PCK output
 * - Switch main clock as MCK and enable PCK output
 * - Switch PLLA clock as MCK and enable PCK output
 * - Switch PLLB clock as MCK and enable PCK output (for SAM3S, SAM4S, SAM4C/SAM4CM and SAM4CP)
 * - Switch UPLL clock as MCK and enable PCK output (for SAM3XA, SAM3U and SAMV71)
 * - Test entering and exiting of sleep mode
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
 * - sam4e16e_sam4e_ek
 * - sam4n16c_sam4n_xplained_pro
 * - sam4c16c_sam4c_ek
 * - sam4cp16b_sam4cp16bmb
 * - sam4cmp16c_sam4cmp_db
 * - sam4cms16c_sam4cms_db
 * - samv71q21_samv71_xplained_ultra
 * - same70q21_same70_xplained_pro
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
 * \def CONF_TEST_UART
 * \brief UART to redirect STDIO
 */
/**
 * \def CONF_TEST_BAUDRATE
 * \brief Baudrate of UART
 */
/**
 * \def CONF_TEST_PARITY
 * \brief Parity mode of UART
 */
//@}

#if !defined(PMC_PCK_PRES_CLK_1)
#define PMC_PCK_PRES_CLK_1   PMC_PCK_PRES(0)
#endif

/* Flag for wake-up from sleep mode */
volatile uint32_t g_ul_sleep_wake_up = 0;

/**
 * \brief Enable and disable peripheral clock test.
 * Enable peripheral clocks, and then check if the clocks are enabled.
 * Disable peripheral clocks, and then check if the clocks are disabled.
 *
 * \param test Current test case.
 */
static void run_periph_clk_cfg_test(const struct test_case *test)
{
/* Define start and end peripheral ID for test  */
#if (SAM3N || SAM4N)
#  define PERIPH_ID_START     ID_UART0
#  define PERIPH_ID_END       ID_PWM
#elif (SAM3XA)
#  define PERIPH_ID_START     ID_PIOA
#  define PERIPH_ID_END       ID_CAN1
#elif (SAM3U)
#  define PERIPH_ID_START     ID_UART
#  define PERIPH_ID_END       ID_UDPHS
#elif (SAM3S || SAM4S)
#  define PERIPH_ID_START     ID_UART0
#  define PERIPH_ID_END       ID_UDP
#elif (SAM4E)
#  define PERIPH_ID_START     ID_UART0
#  define PERIPH_ID_END       ID_UART1
#elif (SAM4C || SAM4CM || SAM4CP)
#  define PERIPH_ID_START     ID_UART0
#  define PERIPH_ID_END       ID_SMC1
#elif (SAMV71 || SAMV70 || SAME70 || SAMS70)
#  define PERIPH_ID_START     ID_UART0
#  define PERIPH_ID_END       ID_PWM1
#else
#  error No peripheral defined for test.
#endif

	uint32_t i;
	uint32_t rc;

	/* Enable all peripheral clocks */
	for (i = PERIPH_ID_START; i <= PERIPH_ID_END; i++) {
		rc = pmc_enable_periph_clk(i);
		test_assert_true(test, rc == 0,
				"pmc_enable_periph_clk() failed: %d", (int)i);
	}

	/* Disable all peripheral clocks */
	for (i = PERIPH_ID_START; i <= PERIPH_ID_END; i++) {
		rc = pmc_disable_periph_clk(i);
		/* Re-enable UART clock for console */
		pmc_enable_periph_clk(CONSOLE_UART_ID);
		test_assert_true(test, rc == 0,
				"pmc_disable_periph_clk() failed: %d!", (int)i);
	}
}

/**
 * \brief Switch MCK to default as startup.
 *
 * \note MCK should be switched to default after clock switching test,
 * so that we can use stdio console again.
 */
static void switch_mck_to_default(void)
{
	pmc_switch_mck_to_mainck(PMC_MCKR_PRES_CLK_1);
	sysclk_init();
}

/**
 * \brief Check if serial output is done.
 *
 * \retval 0 - Not done.
 * \retval 1 - Done.
 */
static uint32_t is_serial_output_done(void)
{
#if (SAMV71 || SAMV70 || SAME70 || SAMS70)
	if (usart_is_tx_empty(CONF_TEST_UART)) {
#else
	if (uart_is_tx_empty(CONF_TEST_UART)) {
#endif
		return 1;
	} else {
		return 0;
	}
}

/**
 * \brief Switch slow clock as MCK and enable PCK output,
 * and check if it can be used.
 *
 *
 * \param test Current test case.
 */
static void run_switch_slck_as_mck_test(const struct test_case *test)
{
	uint32_t rc0, rc1;

	/* Wait for console output to be done before changing MCK */
	while (!is_serial_output_done());

	/* Switch slow clock as MCK */
	rc0 = pmc_switch_mck_to_sclk(PMC_MCKR_PRES_CLK_1);

	/* Enable PCK output */
	pmc_disable_pck(PMC_PCK_0);
	rc1 = pmc_switch_pck_to_sclk(PMC_PCK_0, PMC_PCK_PRES_CLK_1);
	pmc_enable_pck(PMC_PCK_0);

	/* Check status */
	switch_mck_to_default();
	test_assert_true(test, rc0 == 0, "Failed to switch MCK to Slow Clock");
	test_assert_true(test, rc1 == 0, "Failed to switch PCK to Slow Clock");
}

/**
 * \brief Switch main clock as MCK and enable PCK output,
 * and check if it can be used.
 *
 * \param test Current test case.
 */
static void run_switch_mainck_as_mck_test(const struct test_case *test)
{
	uint32_t rc0, rc1, rc2, rc3;

	/* Wait for console output to be done before changing MCK */
	while (!is_serial_output_done());

	/*
	 * Switch main clock as MCK and use 12M fast RC as clock input
	 */
	/* Switch slow clock as MCK */
	pmc_switch_mck_to_sclk(PMC_MCKR_PRES_CLK_1);

	/* Switch the mainck clock to the Fast RC */
	pmc_switch_mainck_to_fastrc(CKGR_MOR_MOSCRCF_12_MHz);

	/* Switch main clock as MCK */
	rc0 = pmc_switch_mck_to_mainck(PMC_MCKR_PRES_CLK_1);

	/* Enable PCK output */
	pmc_disable_pck(PMC_PCK_0);
	rc1 = pmc_switch_pck_to_mainck(PMC_PCK_0, PMC_PCK_PRES_CLK_1);
	pmc_enable_pck(PMC_PCK_0);

	/*
	 * Switch main clock as MCK and use 12M, 8M(In SAM4C/SAM4CM) or 10M(In SAM4CP)
	 * XTAL as clock input (BYPASS as clock input in SAM4CP)
	 */

#if SAM4CP
	/* Switch mainck to bypass mode */
	pmc_switch_mainck_to_xtal(1, pmc_us_to_moscxtst(BOARD_OSC_STARTUP_US,
			OSC_SLCK_32K_RC_HZ));
#else
	/* Switch mainck to external xtal */
	pmc_switch_mainck_to_xtal(0, pmc_us_to_moscxtst(BOARD_OSC_STARTUP_US,
			OSC_SLCK_32K_RC_HZ));
#endif

	/* Switch main clock as MCK */
	rc2 = pmc_switch_mck_to_mainck(PMC_MCKR_PRES_CLK_1);

	/* Enable PCK output */
	pmc_disable_pck(PMC_PCK_0);
	rc3 = pmc_switch_pck_to_mainck(PMC_PCK_0, PMC_PCK_PRES_CLK_1);
	pmc_enable_pck(PMC_PCK_0);

	/* Check status */
	switch_mck_to_default();
	test_assert_true(test, rc0 == 0,
			"Failed to switch MCK to Main Clock with fast RC");
	test_assert_true(test, rc1 == 0,
			"Failed to switch PCK to Main Clock with fast RC");
#if SAM4CP
	test_assert_true(test, rc2 == 0,
			"Failed to switch PCK to Main Clock with BYPASS");
	test_assert_true(test, rc3 == 0,
			"Failed to switch PCK to Main Clock with BYPASS");
#else
	test_assert_true(test, rc2 == 0,
			"Failed to switch PCK to Main Clock with XTAL");
	test_assert_true(test, rc3 == 0,
			"Failed to switch PCK to Main Clock with XTAL");
#endif
}

/**
 * \brief Switch PLLA clock as MCK and enable PCK output,
 * and check if it can be used.
 *
 * \param test Current test case.
 */
static void run_switch_pllack_as_mck_test(const struct test_case *test)
{
	uint32_t rc0, rc1;

	/* Wait for console output to be done before changing MCK */
	while (!is_serial_output_done());

	/* First, switch main clock as MCK */
	rc0 = pmc_switch_mck_to_mainck(PMC_MCKR_PRES_CLK_1);

#if (SAM4C || SAM4CM || SAM4CP)
	/* Enable the PLLA clock, the mainck equals 32.768K * 250 = 8.192Mhz */
	pmc_enable_pllack((250 - 1), 0x3f, 1);
#else
	/* Enable the PLLA clock, the mainck equals 12Mhz * (32-1+1) / 3 = 128Mhz */
	pmc_enable_pllack((32 - 1), 0x3f, 3);
#endif

	/* Then, switch PLLA clock as MCK */
	rc0 |= pmc_switch_mck_to_pllack(PMC_MCKR_PRES_CLK_4);

	/* Enable PCK output */
	pmc_disable_pck(PMC_PCK_0);
	rc1 = pmc_switch_pck_to_pllack(PMC_PCK_0, PMC_PCK_PRES_CLK_1);
	pmc_enable_pck(PMC_PCK_0);

	/* Check status */
	switch_mck_to_default();
	test_assert_true(test, rc0 == 0, "Failed to switch MCK to PLLA clock");
	test_assert_true(test, rc1 == 0, "Failed to switch PCK to PLLA clock");
}

#if (SAM3S || SAM4S || SAM4C || SAM4CM || SAM4CP)
/**
 * \brief Switch PLLB clock as MCK and enable PCK output,
 * and check if it can be used.
 *
 * \param test Current test case.
 */
static void run_switch_pllbck_as_mck_test(const struct test_case *test)
{
	uint32_t rc0, rc1;

	/* Wait for console output to be done before changing MCK */
	while (!is_serial_output_done());

	/* First, switch main clock as MCK */
	rc0 = pmc_switch_mck_to_mainck(PMC_MCKR_PRES_CLK_1);

#if (SAM4C || SAM4CM)
	/* Enable the PLLB clock, the mainck equals (8Mhz * (11+1) / 1) = 96Mhz
	 * with the initialize counter be 0x3f
	 */
	 pmc_enable_pllbck(11, 0x3f, 1);
#elif SAM4CP
	/* Enable the PLLB clock, the mainck equals (10Mhz * (9+1) / 1) = 100Mhz
	 * with the initialize counter be 0x3f
	 */
	 pmc_enable_pllbck(9, 0x3f, 1);
#else
	/* Enable the PLLB clock, the mainck equals (12Mhz * (7+1) / 1) = 96Mhz
	 * with the initialize counter be 0x3f
	 */
	pmc_enable_pllbck(7, 0x3f, 1);
#endif

	/* Then, switch PLLB clock as MCK */
	rc0 |= pmc_switch_mck_to_mainck(PMC_MCKR_PRES_CLK_2);

	/* Enable PCK output */
	pmc_disable_pck(PMC_PCK_0);
	rc1 = pmc_switch_pck_to_pllbck(PMC_PCK_0, PMC_PCK_PRES_CLK_1);
	pmc_enable_pck(PMC_PCK_0);

	/* Check status */
	switch_mck_to_default();
	test_assert_true(test, rc0 == 0, "Failed to switch MCK to PLLB clock");
	test_assert_true(test, rc1 == 0, "Failed to switch PCK to PLLB clock");
}
#endif

#if (SAM3XA || SAM3U || SAMV71 || SAMV70 || SAME70 || SAMS70)
/**
 * \brief Switch UPLL clock as MCK and enable PCK output,
 * and check if it can be used.
 *
 * \param test Current test case.
 */
static void run_switch_upllck_as_mck_test(const struct test_case *test)
{
	uint32_t rc0, rc1;

	/* Wait for console output to be done before changing MCK */
	while (!is_serial_output_done());

	/* First, switch main clock as MCK */
	rc0 = pmc_switch_mck_to_mainck(PMC_MCKR_PRES_CLK_1);

	/* Enable the UPLLB clock */
	pmc_enable_upll_clock();

	/* Then, switch UPLL clock as MCK */
	rc0 |= pmc_switch_mck_to_upllck(PMC_MCKR_PRES_CLK_8);

	/* Enable PCK output */
	pmc_disable_pck(PMC_PCK_0);
	rc1 = pmc_switch_pck_to_upllck(PMC_PCK_0, PMC_PCK_PRES_CLK_1);
	pmc_enable_pck(PMC_PCK_0);

	/* Check status */
	switch_mck_to_default();
	test_assert_true(test, rc0 == 0, "Failed to switch MCK to UPLL clock");
	test_assert_true(test, rc1 == 0, "Failed to switch PCK to UPLL clock");
}
#endif

/**
 * \brief Test entering and exiting sleep mode.
 *
 * \param test Current test case.
 */
static void run_sleep_mode_test(const struct test_case *test)
{
	/* Set up SysTick Timer for 1 msec interrupts. */
	if (SysTick_Config(sysclk_get_cpu_hz() / 1000)) {
		/* Capture error. */
		while (1) {
		}
	}

	g_ul_sleep_wake_up = 0;
	/* Enter sleep mode and wait for interrupt of systick to wake up */
	pmc_enable_sleepmode(0);
	test_assert_true(test, g_ul_sleep_wake_up == 1,
			"Failed to wake up from sleep mode");

}

/**
 * \brief SysTick handler.
 */
void SysTick_Handler(void)
{
	g_ul_sleep_wake_up = 1;
}


/**
 * \brief Run PMC driver unit tests.
 */
int main(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_TEST_BAUDRATE,
#ifdef CONF_UART_CHAR_LENGTH
		.charlength = CONF_UART_CHAR_LENGTH,
#endif
		.paritytype = CONF_TEST_PARITY,
#ifdef CONF_UART_STOP_BITS
		.stopbits = CONF_UART_STOP_BITS,
#endif
	};

	/* Initialize the system. */
	sysclk_init();
	board_init();

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_TEST_UART, &uart_serial_options);

	/* Configure PCK0 */
#ifdef CONF_TEST_PCK_OUTPUT_ENABLE
	ioport_set_pin_mode(PIN_PCK0, PIN_PCK0_MUX);
	ioport_disable_pin(PIN_PCK0);
#endif
	pmc_disable_pck(PMC_PCK_0);
	pmc_switch_pck_to_mainck(PMC_PCK_0, PMC_PCK_PRES_CLK_1);
	pmc_enable_pck(PMC_PCK_0);

	/* Define all the test cases */
	DEFINE_TEST_CASE(periph_clk_cfg_test, NULL, run_periph_clk_cfg_test,
			NULL, "Enable and disable peripheral clock");


	DEFINE_TEST_CASE(switch_slck_as_mck, NULL, run_switch_slck_as_mck_test,
			NULL, "Switch to Slow Clock");

	DEFINE_TEST_CASE(switch_mainck_as_mck, NULL,
			run_switch_mainck_as_mck_test, NULL,
			"Switch to Main Clock");


	DEFINE_TEST_CASE(switch_pllack_as_mck, NULL,
			run_switch_pllack_as_mck_test, NULL,
			"Switch to PLLA Clock");


#if (SAM3S || SAM4S || SAM4C || SAM4CM || SAM4CP)
	DEFINE_TEST_CASE(switch_pllbck_as_mck, NULL,
			run_switch_pllbck_as_mck_test, NULL,
			"Switch to PLLB Clock");
#endif

#if (SAM3XA || SAM3U || SAMV71 || SAMV70 || SAME70 || SAMS70)
	DEFINE_TEST_CASE(switch_upllck_as_mck, NULL,
			run_switch_upllck_as_mck_test, NULL,
			"Switch to UPLL Clock");
#endif

	DEFINE_TEST_CASE(test_sleep_mode, NULL, run_sleep_mode_test, NULL,
			"Test sleep mode");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(pmc_tests) = {
		&periph_clk_cfg_test,
		&switch_slck_as_mck,
		&switch_mainck_as_mck,
		&switch_pllack_as_mck,
#if (SAM3S || SAM4S || SAM4C || SAM4CM || SAM4CP)
		&switch_pllbck_as_mck,
#endif
#if (SAM3XA || SAM3U || SAMV71 || SAMV70 || SAME70 || SAMS70)
		&switch_upllck_as_mck,
#endif
		&test_sleep_mode,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(pmc_suite, pmc_tests, "SAM PMC driver test suite");

	/* Run all tests in the test suite */
	test_suite_run(&pmc_suite);

	while (1) {
		/* Busy-wait forever */
	}
}
