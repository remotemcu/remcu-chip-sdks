/**
 * \file
 *
 * \brief Unit tests for AFEC driver.
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

#include <board.h>
#include <sysclk.h>
#include <delay.h>
#include "afec.h"
#include "pmc.h"
#include "tc.h"
#include "ioport.h"
#include <string.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <conf_test.h>
#include <conf_board.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the AFEC driver.
 * It consists of test cases for the following functionality:
 * - TC trigger test
 * - Comparison window test
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_uart_serial.h
 * - \ref conf_sleepmgr.h
 *
 * \section device_info Device Info
 * The SAM4E ,SAMV71-Xplained-Ultra ,SAME70-Xplained-Pro devices can be used.
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for ARM. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */

/** Conversion data is ready flag */
volatile bool is_data_ready = false;

/** Enter comparison window flag */
volatile bool is_comp_event_flag = false;

/**
 * \brief Callback function for AFEC conversion data is ready interrupt.
 */
static void afec_set_data_ready_flag(void)
{
	is_data_ready = true;
	afec_disable_interrupt(AFEC0, AFEC_INTERRUPT_DATA_READY);
	tc_stop(TC0, 0);
}

/**
 * \brief Callback function for AFEC enter compasion window interrupt.
 */
static void afec_set_comp_flag(void)
{
	is_comp_event_flag = true;
	afec_disable_interrupt(AFEC0, AFEC_INTERRUPT_COMP_ERROR);

}

/**
 * \brief Configure to trigger AFEC by TIOA output of timer.
 */
static void configure_tc_trigger(void)
{
	uint32_t ul_div = 0;
	uint32_t ul_tc_clks = 0;
	uint32_t ul_sysclk = sysclk_get_cpu_hz();

	/* Enable peripheral clock. */
	pmc_enable_periph_clk(ID_TC0);

	/* TIOA configuration */
	ioport_set_pin_mode(PIN_TC0_TIOA0, PIN_TC0_TIOA0_FLAGS);
	ioport_disable_pin(PIN_TC0_TIOA0);

	/* Configure TC for a 10Hz frequency and trigger on RC compare. */
	tc_find_mck_divisor(10, ul_sysclk, &ul_div, &ul_tc_clks, ul_sysclk);
	tc_init(TC0, 0, ul_tc_clks | TC_CMR_CPCTRG | TC_CMR_WAVE |
			TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_SET);
	TC0->TC_CHANNEL[0].TC_RA = (ul_sysclk / ul_div) / 2;
	TC0->TC_CHANNEL[0].TC_RC = (ul_sysclk / ul_div) / 1;

	/* Start the Timer. */
	tc_start(TC0, 0);

	afec_set_trigger(AFEC0, AFEC_TRIG_TIO_CH_0);
}

/**
 * \brief Test AFEC in TC trigger mode,
 *        which also tests interrupt driven conversions.
 *
 * \param test Current test case.
 */
static void run_afec_tc_trig_test(const struct test_case *test)
{
	configure_tc_trigger();

	afec_set_callback(AFEC0, AFEC_INTERRUPT_DATA_READY,
			afec_set_data_ready_flag, 1);
	delay_ms(3000);

	test_assert_true(test, is_data_ready == true,
			"AFEC using TC trigger test failed");
}

/**
 * \brief Test AFEC in comparsion window mode.
 *
 * \param test Current test case.
 */
static void run_afec_comp_test(const struct test_case *test)
{
	afec_set_trigger(AFEC0, AFEC_TRIG_SW);
	afec_set_comparison_mode(AFEC0, AFEC_CMP_MODE_2, AFEC_CHANNEL_1, 0);
	afec_set_comparison_window(AFEC0, 0, 0xFFF);
	afec_set_callback(AFEC0, AFEC_INTERRUPT_COMP_ERROR,
			afec_set_comp_flag, 1);
	afec_start_software_conversion(AFEC0);
	delay_ms(100);

	test_assert_true(test, is_comp_event_flag == true,
			"AFEC Comparsion Window test failed");
}

/**
 * \brief Run AFEC driver unit tests.
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
		.paritytype = CONF_TEST_PARITY,
	#ifdef CONF_UART_CHAR_LENGTH
		.charlength = CONF_UART_CHAR_LENGTH,
	#endif
	#ifdef CONF_UART_STOP_BITS
		.stopbits = CONF_UART_STOP_BITS,
	#endif
	};

	/* Initialize the system clock and board */
	sysclk_init();
	board_init();

	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	afec_enable(AFEC0);

	struct afec_config afec_cfg;

	afec_get_config_defaults(&afec_cfg);
	afec_init(AFEC0, &afec_cfg);
	
  #if (SAMV71 || SAMV70 || SAME70 || SAMS70)
	/*
	 * Because the internal ADC offset is 0x200, it should cancel it and shift
	 * down to 0.
	 */
	afec_channel_set_analog_offset(AFEC0, AFEC_CHANNEL_1, 0x200);
#else
	/*
	 * Because the internal ADC offset is 0x800, it should cancel it and shift
	 * down to 0.
	 */
	afec_channel_set_analog_offset(AFEC0, AFEC_CHANNEL_1, 0x800);
#endif

	afec_channel_enable(AFEC0, AFEC_CHANNEL_1);

#if defined(__GNUC__)
	setbuf(stdout, NULL);
#endif

	/* Define all the test cases */
	DEFINE_TEST_CASE(afec_tc_trig_test, NULL, run_afec_tc_trig_test, NULL,
			"AFEC TC Trig test");
	DEFINE_TEST_CASE(afec_comp_test, NULL, run_afec_comp_test,
			NULL, "AFEC Comparison Window test");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(afec_tests) = {
		&afec_tc_trig_test,
		&afec_comp_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(afec_suite, afec_tests,
			"SAM AFEC driver test suite");

	/* Run all tests in the test suite */
	test_suite_run(&afec_suite);

	while (1) {
		/* Busy-wait forever. */
	}
}
