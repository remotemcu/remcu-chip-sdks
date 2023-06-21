/**
 * \file
 *
 * \brief Unit tests for FREQM driver.
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

#include <asf.h>
#include <conf_test.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the FREQM driver.
 * It consists of test cases for the following functionality:
 * - Enable FREQM and start measurement, when measurement done will generate interrupt
 *
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 * - \ref conf_sleepmgr.h
 *
 * \section device_info Device Info
 * The SAM4L devices can be used.
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
 * \def CONF_TEST_FREQM
 * \brief Test the functions provided by the FREQM driver.
 */
//@}

volatile uint8_t intflag = 0;

/** FREQM instance */
struct freqm_dev_inst g_freqm_inst;

/** FREQM configuration */
struct freqm_config  g_freqm_cfg;

/**
 * \brief Interrupt handler for FREQM interrupt.
 */
static void set_int_flag(void)
{
	if (freqm_get_interrupt_status(&g_freqm_inst) & FREQM_ISR_DONE) {
		freqm_disable_interrupt(&g_freqm_inst,
				FREQM_INTERRUPT_MEASURMENT_READY);
		intflag = 1;
	}
}

/**
 * \brief Test FREQM measurement done.
 *
 * \param test Current test case.
 */
static void run_freqm_test(const struct test_case *test)
{
	/* Measure default clock. */
	freqm_get_config_defaults(&g_freqm_cfg);
	freqm_init(&g_freqm_inst, FREQM, &g_freqm_cfg);
	freqm_set_callback(&g_freqm_inst, FREQM_INTERRUPT_MEASURMENT_READY,
			set_int_flag, 1);
	freqm_start_measure(&g_freqm_inst);

	/* Delay more than the measurement time to wait for interrupt. */
	delay_ms(20);

	test_assert_true(test, intflag == 1, "FREQM test failed");
}

/**
 * \brief Run FREQM driver unit tests.
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits   = CONF_TEST_STOPBITS
	};

	/* Initialize the system clock and board */
	sysclk_init();
	board_init();

	/* Enable the debug uart */
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

#if defined(__GNUC__)
	setbuf(stdout, NULL);
#endif

	/* Define all the test cases */
	DEFINE_TEST_CASE(freqm_test, NULL, run_freqm_test, NULL,
			"FREQM test");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(freqm_tests) = {
		&freqm_test
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(freqm_suite, freqm_tests,
			"SAM FREQM driver test suite");

	/* Run all tests in the test suite */
	test_suite_run(&freqm_suite);

	while (1) {
		/* Busy-wait forever. */
	}
}
