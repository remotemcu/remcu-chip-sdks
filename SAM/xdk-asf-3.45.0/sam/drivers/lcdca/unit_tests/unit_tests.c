/**
 * \file
 *
 * \brief Unit tests for lcdca driver.
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
#include <string.h>

#include <asf.h>
#include "conf_test.h"

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for LCDCA driver.
 * It consists of test cases for the following:
 * - LCDCA initialization test
 * - LCDCA blink feature test
 * - LCDCA automated feature test (sequential and scrolling)
 * - LCDCA autonomous segment feature test
 *   LCDCA contrast change test
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_sleepmgr.h
 * - \ref conf_uart_serial.h
 *
 * \section device_info Device Info
 * All SAM devices with a LCDCA and a USART module can be used.
 *
 * \section description Description of the unit tests
 * See the documentation for the individual unit test functions \ref
 * unit_tests.c "here" for detailed descriptions of the tests.
 *
 *
 * \section dependencies Dependencies
 * This example depends directly on the following modules:
 * - \ref test_suite_group
 * - \ref sysclk.h "Common Clock service"
 *
 * \section compinfo Compilation info
 * This software is written for GNU GCC and IAR Embedded Workbench
 * for Atmel. Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */

/** \name Unit test configuration */
/* @{ */

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
/* @} */

/**
 * \brief Test LCDCA initialization.
 *
 * \param test Current test case.
 */
static void run_lcdca_init_test(const struct test_case *test)
{
#define LCDCA_INIT_CHECK_MASK \
	(LCDCA_SR_EN | LCDCA_SR_FC0S | LCDCA_SR_FC1S | LCDCA_SR_FC2S)
	struct lcdca_config lcdca_cfg;
	uint32_t status;

	/*
	 * LCDCA Controller initialization
	 * - Clock,
	 * - Connect to C42364A glass LCD component,
	 * - Timing:  64 Hz frame rate & low power waveform, FC0, FC1, FC2
	 * - Interrupt: off
	 */
	lcdca_clk_init();
	lcdca_cfg.port_mask = PORT_MASK;
	lcdca_cfg.x_bias = false;
	lcdca_cfg.lp_wave = true;
	lcdca_cfg.duty_type = LCD_DUTY;
	lcdca_cfg.lcd_pres = false;
	lcdca_cfg.lcd_clkdiv = 3;
	lcdca_cfg.fc0 = 2;
	lcdca_cfg.fc1 = 1;
	lcdca_cfg.fc2 = 0;
	lcdca_cfg.contrast = LCD_CONTRAST_LEVEL;
	lcdca_set_config(&lcdca_cfg);
	lcdca_enable();
	lcdca_enable_timer(LCDCA_TIMER_FC0);
	lcdca_enable_timer(LCDCA_TIMER_FC1);
	lcdca_enable_timer(LCDCA_TIMER_FC2);

	/* Check status */
	status = lcdca_get_status();
	test_assert_true(test,
			(status & LCDCA_INIT_CHECK_MASK) == LCDCA_INIT_CHECK_MASK,
			"LCDCA initialization failed.");

	/* Turn on LCD back light */
	ioport_set_pin_level(LCD_BL_GPIO, IOPORT_PIN_LEVEL_HIGH);
}

/**
 * \brief Test LCDCA blink feature.
 *
 * \param test Current test case.
 */
static void run_lcdca_blink_test(const struct test_case *test)
{
#define LCDCA_BLINK_CHECK_MASK (LCDCA_SR_BLKS)
	uint32_t status;
	struct lcdca_blink_config blink_cfg;

	/* Blink "error" icon */
	blink_cfg.lcd_blink_timer = LCDCA_TIMER_FC2;
	blink_cfg.lcd_blink_mode = LCDCA_BLINK_SELECTED;
	lcdca_blink_set_config(&blink_cfg);
	lcdca_set_pixel(ICON_ERROR);
	lcdca_set_blink_pixel(ICON_ERROR);
	lcdca_blink_enable();
	delay_ms(500);

	/* Check status */
	status = lcdca_get_status();
	test_assert_true(test,
			(status & LCDCA_BLINK_CHECK_MASK) == LCDCA_BLINK_CHECK_MASK,
			"LCDCA blink test failed.");

	lcdca_blink_disable();
	lcdca_clear_pixel(ICON_ERROR);
}

/**
 * \brief Test LCDCA automated sequential feature.
 *
 * \param test Current test case.
 */
static void run_lcdca_automated_sequential_test(const struct test_case *test)
{
	uint32_t status;
	/* Automated display configuration */
	struct lcdca_automated_char_config automated_char_cfg;
	/* String for sequential display */
	uint8_t const sequential_str[] = "Sequen tial   ";

	/* Automated sequential character string display */
	automated_char_cfg.automated_mode = LCDCA_AUTOMATED_MODE_SEQUENTIAL;
	automated_char_cfg.automated_timer = LCDCA_TIMER_FC1;
	automated_char_cfg.lcd_tdg = LCDCA_TDG_14SEG4COM;
	automated_char_cfg.stseg = FIRST_14SEG_4C;
	automated_char_cfg.dign = WIDTH_14SEG_4C;
	automated_char_cfg.steps = 0;
	automated_char_cfg.dir_reverse = LCDCA_AUTOMATED_DIR_REVERSE;
	lcdca_automated_char_set_config(&automated_char_cfg);
	lcdca_automated_char_start(sequential_str, strlen((char const *)sequential_str));
	delay_ms(1000);

	/* Check status */
	status = LCDCA->LCDCA_ACMCFG & LCDCA_ACMCFG_EN;
	test_assert_true(test,
			status,
			"LCDCA automated sequential test failed.");

	lcdca_automated_char_stop();
}

/**
 * \brief Test LCDCA automated scrolling feature.
 *
 * \param test Current test case.
 */
static void run_lcdca_automated_scrolling_test(const struct test_case *test)
{
	uint32_t status;
	/* Automated display configuration */
	struct lcdca_automated_char_config automated_char_cfg;
	/* String for scrolling display */
	uint8_t const scrolling_str[] = "Scrolling  ";

	/* Automated scrolling of character string display */
	automated_char_cfg.automated_mode = LCDCA_AUTOMATED_MODE_SCROLLING;
	automated_char_cfg.automated_timer = LCDCA_TIMER_FC1;
	automated_char_cfg.lcd_tdg = LCDCA_TDG_14SEG4COM;
	automated_char_cfg.stseg = FIRST_14SEG_4C;
	automated_char_cfg.dign = WIDTH_14SEG_4C;
	/* STEPS = string length - DIGN + 1 */
	automated_char_cfg.steps = sizeof(scrolling_str) - WIDTH_14SEG_4C + 1;
	automated_char_cfg.dir_reverse = LCDCA_AUTOMATED_DIR_REVERSE;
	lcdca_automated_char_set_config(&automated_char_cfg);
	lcdca_automated_char_start(scrolling_str, strlen((char const *)scrolling_str));
	delay_ms(1000);

	/* Check status */
	status = LCDCA->LCDCA_ACMCFG & LCDCA_ACMCFG_EN;
	test_assert_true(test,
			status,
			"LCDCA automated scrolling test failed.");

	lcdca_automated_char_stop();
}

/**
 * \brief Test LCDCA autonomous feature.
 *
 * \param test Current test case.
 */
static void run_lcdca_autonomous_test(const struct test_case *test)
{
#define LCDCA_AUTONOMOUS_CHECK_MASK (LCDCA_SR_CSRS)
	uint32_t status;
	struct lcdca_circular_shift_config cs_cfg;

	/* Autonomous segment animation of 7-pixels area of the LCD */
	cs_cfg.lcd_csr_timer = LCDCA_TIMER_FC2;
	cs_cfg.lcd_csr_dir = LCDCA_CSR_RIGHT;
	cs_cfg.size = 7;    /* Total 7-pixels */
	cs_cfg.data = 0x03; /* Display 2 pixel at one time */
	lcdca_circular_shift_set_config(&cs_cfg);
	lcdca_circular_shift_enable();
	delay_ms(500);

	/* Check status */
	status = lcdca_get_status();
	test_assert_true(test,
			(status & LCDCA_AUTONOMOUS_CHECK_MASK) == LCDCA_AUTONOMOUS_CHECK_MASK,
			"LCDCA autonomous test failed.");

	lcdca_circular_shift_disable();
}

/**
 * \brief Test LCDCA contrast change.
 *
 * \param test Current test case.
 */
static void run_lcdca_contrast_change_test(const struct test_case *test)
{
	uint32_t fcst;

	/* Set LCD contrast and check */
	lcdca_set_contrast(-32);
	fcst = LCDCA->LCDCA_CFG & LCDCA_CFG_FCST_Msk;
	test_assert_true(test,
			(fcst == (0x20 << LCDCA_CFG_FCST_Pos)),
			"LCDCA contrast change (-32) test failed.");

	lcdca_set_contrast(0);
	fcst = LCDCA->LCDCA_CFG & LCDCA_CFG_FCST_Msk;
	test_assert_true(test,
			(fcst == (0 << LCDCA_CFG_FCST_Pos)),
			"LCDCA contrast change (0) test failed.");

	lcdca_set_contrast(31);
	fcst = LCDCA->LCDCA_CFG & LCDCA_CFG_FCST_Msk;
	test_assert_true(test,
			(fcst == (31 << LCDCA_CFG_FCST_Pos)),
			"LCDCA contrast change (31) test failed.");
}


/**
 * \brief Clean up LCDCA test.
 *
 * \param test Current test case.
 */
static void run_lcdca_end_test(const struct test_case *test)
{
	UNUSED(test);

	/* Turn off LCD back light */
	ioport_set_pin_level(LCD_BL_GPIO, IOPORT_PIN_LEVEL_LOW);

	/* Disable LCDCA */
	lcdca_disable();
}

/**
 * \brief Run LCDCA unit tests
 *
 * Initializes board, serial output, then sets up the
 * LCDCA unit test suite and runs it.
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
	sleepmgr_init();

	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Define all the test cases. */
	DEFINE_TEST_CASE(lcdca_init_test, NULL, run_lcdca_init_test, NULL,
			"LCDCA initialization test");

	DEFINE_TEST_CASE(lcdca_blink_test, NULL, run_lcdca_blink_test, NULL,
			"LCDCA blink test");

	DEFINE_TEST_CASE(lcdca_automated_sequential_test, NULL,
			run_lcdca_automated_sequential_test, NULL,
			"LCDCA automated sequential test");

	DEFINE_TEST_CASE(lcdca_automated_scrolling_test, NULL,
			run_lcdca_automated_scrolling_test, NULL,
			"LCDCA automated scrolling test");

	DEFINE_TEST_CASE(lcdca_autonomous_test, NULL,
			run_lcdca_autonomous_test, NULL,
			"LCDCA autonomous segment test");

	DEFINE_TEST_CASE(lcdca_contrast_change_test, NULL,
			run_lcdca_contrast_change_test, run_lcdca_end_test,
			"LCDCA contrast change test");

	/* Put test case addresses in an array. */
	DEFINE_TEST_ARRAY(lcdca_tests) = {
		&lcdca_init_test,
		&lcdca_blink_test,
		&lcdca_automated_sequential_test,
		&lcdca_automated_scrolling_test,
		&lcdca_autonomous_test,
		&lcdca_contrast_change_test,
	};

	/* Define the test suite. */
	DEFINE_TEST_SUITE(lcdca_suite, lcdca_tests,
			"LCDCA driver unit test suite");

	/* Run all tests in the test suite. */
	test_suite_run(&lcdca_suite);

	while (true) {
		__asm__("nop");
	}
}
