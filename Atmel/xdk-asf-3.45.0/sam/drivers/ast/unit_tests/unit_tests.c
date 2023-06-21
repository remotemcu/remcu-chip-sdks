/**
 * \file
 *
 * \brief Unit tests for AST driver.
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

#include <asf.h>
#include <conf_test.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the AST driver.
 * It contains two test case for the AST module:
 * - Test alarm interrupt and wakeup functions in calendar/counter mode.
 * - Test periodic interrupt and wakeup functions in counter mode.
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_uart_serial.h
 *
 * \section device_info Device Info
 * Only SAM4L devices can be used.
 * This example has been tested with the following setup:
 * - sam4lc4c_sam4l_ek
 * - sam4lc4c_sam4l_xplained_pro
 * - sam4lc8c_sam4l8_xplained_pro
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for ARM. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */

volatile uint8_t flag = 0;

/**
 * \brief Callback handler for AST periodic interrupt.
 */
static void ast_per_callback(void)
{
	ast_disable_interrupt(AST, AST_INTERRUPT_PER);
	ast_clear_interrupt_flag(AST, AST_INTERRUPT_PER);
	flag = 1;
}

/**
 * \brief Callback handler for AST alarm interrupt.
 */
static void ast_alarm_callback(void)
{
	ast_disable_interrupt(AST, AST_INTERRUPT_ALARM);
	ast_clear_interrupt_flag(AST, AST_INTERRUPT_ALARM);
	flag = 2;
}

/**
 * \brief Test alarm interrupt and wakeup functions in calendar/counter mode.
 *
 * \param test Current test case.
 */
static void run_alarm_test(const struct test_case *test)
{
	uint32_t ast_alarm, ast_counter;
	struct ast_calendar calendar;
	struct ast_config ast_conf;

	/* Enable the AST. */
	ast_enable(AST);

	/* Set alarm 0 to interrupt after 1 second in calendar mode. */
	calendar.FIELD.sec = 0;
	calendar.FIELD.min = 15;
	calendar.FIELD.hour = 12;
	calendar.FIELD.day = 20;
	calendar.FIELD.month = 9;
	calendar.FIELD.year = 12;
	ast_conf.mode = AST_CALENDAR_MODE;
	ast_conf.osc_type = AST_OSC_32KHZ;
	ast_conf.psel = AST_PSEL_32KHZ_1HZ;
	ast_conf.calendar = calendar;
	ast_set_config(AST, &ast_conf);

	/* Set callback for alarm0. */
	ast_clear_interrupt_flag(AST, AST_INTERRUPT_ALARM);
	ast_write_alarm0_value(AST, calendar.field + 1);
	ast_set_callback(AST, AST_INTERRUPT_ALARM, ast_alarm_callback,
		AST_ALARM_IRQn, 1);

	flag = 0;
	delay_ms(1500);
	test_assert_true(test, flag == 2, "Alarm interrupt not work!");

	/* Set alarm 0 to wakeup after 1 second in counter mode. */
	ast_conf.mode = AST_COUNTER_MODE;
	ast_conf.osc_type = AST_OSC_32KHZ;
	ast_conf.psel = AST_PSEL_32KHZ_1HZ - 2;
	ast_conf.counter = 0;
	ast_set_config(AST, &ast_conf);

	/* ast_init_counter Set Alarm to current time+4 quarter second. */
	ast_counter = ast_read_counter_value(AST);
	ast_alarm = ast_counter + 4;
	ast_write_alarm0_value(AST, ast_alarm);
	ast_enable_interrupt(AST, AST_INTERRUPT_ALARM);
	ast_enable_wakeup(AST, AST_WAKEUP_ALARM);

	/* AST can wakeup the device. */
	bpm_enable_wakeup_source(BPM, (1 << BPM_BKUPWEN_AST));

	flag = 0;
	/* Go into WAIT mode. */
	bpm_sleep(BPM, BPM_SM_WAIT);
	delay_ms(1000);
	test_assert_true(test, flag == 2, "Alarm wakeup not work!");

	/* Disable the AST. */
	ast_disable(AST);
}

/**
 * \brief Test periodic interrupt and wakeup functions in counter mode.
 *
 * \param test Current test case.
 */
static void run_periodic_test(const struct test_case *test)
{
	struct ast_config ast_conf;

	/* Enable the AST. */
	ast_enable(AST);

	ast_conf.mode = AST_COUNTER_MODE;
	ast_conf.osc_type = AST_OSC_32KHZ;
	ast_conf.psel = AST_PSEL_32KHZ_1HZ;
	ast_conf.counter = 0;
	ast_set_config(AST, &ast_conf);

	/* Set periodic 0 to interrupt after 1/16 second in counter mode. */
	ast_clear_interrupt_flag(AST, AST_INTERRUPT_PER);
	ast_write_periodic0_value(AST, AST_PSEL_32KHZ_1HZ - 4);
	/* Set callback for periodic0. */
	flag = 0;
	ast_set_callback(AST, AST_INTERRUPT_PER, ast_per_callback,
		AST_PER_IRQn, 1);
	delay_ms(200);
	test_assert_true(test, flag == 1, "Periodic interrupt not work!");

	/* Set periodic 0 to wakeup after 1/16 second in counter mode. */
	while (!(ast_read_interrupt_mask(AST) & AST_IMR_PER0_1)) {
		ast_enable_interrupt(AST, AST_INTERRUPT_PER);
	}
	ast_enable_wakeup(AST, AST_WAKEUP_PER);

	/* AST can wakeup the device. */
	bpm_enable_wakeup_source(BPM, (1 << BPM_BKUPWEN_AST));

	flag = 0;
	/* Go into WAIT mode. */
	bpm_sleep(BPM, BPM_SM_WAIT);
	delay_ms(200);
	test_assert_true(test, flag == 1, "Periodic wakeup not work!");
	ast_disable_interrupt(AST, AST_INTERRUPT_PER);

	/* Disable the AST. */
	ast_disable(AST);
}

/**
 * \brief Run AST driver unit tests.
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits = CONF_TEST_STOPBITS
	};

	sysclk_init();
	board_init();
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Enable osc32 oscillator*/
	if (!osc_is_ready(OSC_ID_OSC32)) {
		osc_enable(OSC_ID_OSC32);
		osc_wait_ready(OSC_ID_OSC32);
	}

	/* Define all the test cases. */
	DEFINE_TEST_CASE(alarm_test, NULL, run_alarm_test, NULL,
			"SAM AST alarm interrupt and wakeup test.");
	DEFINE_TEST_CASE(periodic_test, NULL, run_periodic_test, NULL,
			"SAM AST periodic interrupt and wakeup test.");

	/* Put test case addresses in an array. */
	DEFINE_TEST_ARRAY(ast_tests) = {
		&alarm_test,
		&periodic_test,
	};

	/* Define the test suite. */
	DEFINE_TEST_SUITE(ast_suite, ast_tests, "SAM AST driver test suite");

	/* Run all tests in the test suite. */
	test_suite_run(&ast_suite);

	while (1) {
		/* Busy-wait forever. */
	}
}
