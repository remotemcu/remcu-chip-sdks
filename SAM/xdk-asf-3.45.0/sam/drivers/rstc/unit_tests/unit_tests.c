/**
 * \file
 *
 * \brief Unit tests for RSTC driver.
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
#include <wdt.h>
#include <gpbr.h>
#include <rstc.h>
#include <string.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <conf_test.h>
#include <conf_board.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the RSTC driver.
 * It consists of test cases for the following functionality:
 * - Watchdog Reset
 * - Software Reset
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_uart_serial.h
 *
 * \section device_info Device Info
 * All SAM devices can be used.
 * This example has been tested with the following setup:
 * - sam3n4c_sam3n_ek
 * - sam3s4c_sam3s_ek
 * - sam3sd8c_sam3s_ek2
 * - sam3u4e_sam3u_ek
 * - sam3x8h_sam3x_ek
 * - sam4e16e_sam4e_ek
 * - sam4s16c_sam4s_ek
 * - sam4sd32c_sam4s_ek2
 * - sam4sd32c_atpl230amb
 * - sam4n16c_sam4n_xplained_pro
 * - sam4c16c_sam4c_ek
 * - sam4cp16b_sam4cp16bmb
 * - sam4cmp16c_sam4cmp_db
 * - sam4cms16c_sam4cms_db
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
 * \def CONF_TEST_RSTC
 * \brief Check the reset type of different reasons.
 */
//@}

/** Reset type of chip. */
#define GENERAL_RESET          (0x00 << RSTC_SR_RSTTYP_Pos)
#define BACKUP_RESET           (0x01 << RSTC_SR_RSTTYP_Pos)
#define WDT_RESET              (0x02 << RSTC_SR_RSTTYP_Pos)
#define SOFTWARE_RESET         (0x03 << RSTC_SR_RSTTYP_Pos)
#define USER_RESET             (0x04 << RSTC_SR_RSTTYP_Pos)

/** GPBR registers used for saving test state. */
#define RSTC_GPBR_FLAG         GPBR0
#define RSTC_GPBR_STEP         GPBR1
#define RSTC_GPBR_RES1         GPBR2
#define RSTC_GPBR_RES2         GPBR3

/** RSTC start flag value. */
#define RSTC_UT_START_FLAG     0x1337BEEF

/** Test step of chip reset. */
#define RSTC_UT_STEP1          1
#define RSTC_UT_STEP2          2
#define RSTC_UT_STEP3          3

/**
 * \brief Test Reset Controller.
 *
 * This test check the reset type of RSTC when the chip resets for different reasons.
 */
static void run_rstc_test(const struct test_case *test)
{
	uint32_t dw_reset_type;

	if (gpbr_read(RSTC_GPBR_FLAG) != RSTC_UT_START_FLAG) {
		gpbr_write(RSTC_GPBR_FLAG, RSTC_UT_START_FLAG);
		gpbr_write(RSTC_GPBR_STEP, RSTC_UT_STEP1);
	}

	/* Get the reset type of this time. */
	dw_reset_type = rstc_get_reset_cause(RSTC);

	/* Read current step. */
	switch (gpbr_read(RSTC_GPBR_STEP)) {
	case RSTC_UT_STEP1:
		/* Step 1: Software reset test. */
		wdt_disable(WDT);
		gpbr_write(RSTC_GPBR_STEP, RSTC_UT_STEP2);
		rstc_start_software_reset(RSTC);
		while (1) {
		}

	case RSTC_UT_STEP2:
		/* Save reset type in RES1 */
		gpbr_write(RSTC_GPBR_RES1, dw_reset_type);
		test_assert_true(test, gpbr_read(RSTC_GPBR_RES1) == SOFTWARE_RESET,
			"Test: unexpected reset type, expected SOFTWARE_RESET!");
		/* Step 2: Watchdog reset test. */
		gpbr_write(RSTC_GPBR_STEP, RSTC_UT_STEP3);
		wdt_init(WDT, WDT_MR_WDRSTEN | WDT_MR_WDRPROC, 0, 0);
		while (1) {
		}

	case RSTC_UT_STEP3:
		/* Save reset type in RES2 */
		gpbr_write(RSTC_GPBR_RES2, dw_reset_type);
		test_assert_true(test, gpbr_read(RSTC_GPBR_RES2) == WDT_RESET,
			"Test: unexpected reset type, expected WDT_RESET!");
		wdt_disable(WDT);
		break;

	default:
		wdt_disable(WDT);
		puts("\r\nrun_rstc_test: corrupted data, unknown step!\r\n");
		while (1) {
		}
	}

}

/**
 * \brief Run RSTC driver unit tests.
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate = CONF_TEST_BAUDRATE,
#ifdef CONF_TEST_CHAR_LENGTH
		.charlength = CONF_TEST_CHAR_LENGTH,
#endif
		.paritytype = CONF_TEST_PARITY,
#ifdef CONF_TEST_STOP_BITS
		.stopbits = CONF_TEST_STOP_BITS,
#endif
	};
	/* Clear DEMCR.VC_CORERESET bit in case of external tool set it.
	   When RSTC unit test performs reset in the code with VC_CORERESET bit set,
	   the program will halt at Reset_Handler() after reset. */
	CoreDebug->DEMCR &= (~CoreDebug_DEMCR_VC_CORERESET_Msk);

	sysclk_init();
	board_init();

	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Define all the test cases. */
	DEFINE_TEST_CASE(rstc_test, NULL, run_rstc_test, NULL,
			"Reset Controller, check reset type");

	/* Put test case addresses in an array. */
	DEFINE_TEST_ARRAY(rstc_tests) = {
	&rstc_test,};

	/* Define the test suite */
	DEFINE_TEST_SUITE(rstc_suite, rstc_tests, "SAM RSTC driver test suite");

	/* Run all tests in the test suite. */
	test_suite_run(&rstc_suite);

	/* Clear test flag. */
	gpbr_write(RSTC_GPBR_FLAG, 0);

	/* Disable watchdog */
	wdt_disable(WDT);

	while (1) {
		/* Busy-wait forever. */
	}
}
