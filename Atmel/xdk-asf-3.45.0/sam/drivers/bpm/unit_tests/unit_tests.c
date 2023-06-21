/**
 * \file
 *
 * \brief Unit tests for BPM driver.
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
 * This is the unit test application for the BPM driver.
 * It contains below test cases for the BPM module:
 * - Enter backup mode & wakeup.
 * - Power Scaling mode switch
 * - Enter retention mode & wakeup.
 * - Enter wait mode & wakeup.
 * - Enter sleep mode 3 & wakeup.
 * - Enter sleep mode 2 & wakeup.
 * - Enter sleep mode 1 & wakeup.
 * - Enter sleep mode 0 & wakeup.
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_uart_serial.h
 * - \ref conf_sleepmgr.h
 * - \ref conf_ast.h
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

/** \name Unit test configuration */

/** Wakeup event, logged in ISR that wakes up the device */
#define EVENT_WAKEUP 1
/** Run event, logged in main loop after wakeup */
#define EVENT_RUN    2

/** Logs for events detected */
static uint8_t log_events[2];
/** Current log index */
static volatile uint8_t log_index = 0;

/** 1ms Time Tick */
static volatile uint32_t tick_1ms = 0;

/**
 * Reset event log list
 */
static inline void reset_log(void)
{
	log_index = 0;
	log_events[0] = log_events[1] = 0;
}

/**
 * Log a event
 */
static inline void log_event(uint8_t event)
{
	if (log_index < 2) {
		log_events[log_index] = event;
	}
	log_index ++;
}
/** Is OK if 2 events detected */
#define IS_NB_EVENTS_OK() \
	(2 == log_index)
/** Is OK if first event is wakeup and second one is run */
#define IS_EVENTS_OK() \
	((log_events[0]==EVENT_WAKEUP) && (log_events[1]==EVENT_RUN))

/**
 * \brief Wait until test assert is done (no wave on assert port)
 */
static inline void wait_test_assert_idle(void)
{
	while(!usart_is_tx_empty(CONF_TEST_USART));
}

/**
 * \brief AST interrupt handler
 */
static void ast_per_callback(void)
{
	log_event(EVENT_WAKEUP);
	ast_clear_interrupt_flag(AST, AST_INTERRUPT_PER);
}

/**
 * \brief BPM interrupt handler
 */
void BPM_Handler(void)
{
	if (bpm_get_interrupt_status(BPM) == BPM_ISR_PSOK) {
		bpm_clear_interrupt(BPM, BPM_ICR_PSOK);
		bpm_disable_interrupt(BPM, BPM_IDR_PSOK);
		log_event(EVENT_WAKEUP);
	}
}

/**
 * \brief Test entering and exiting backup mode.
 *
 * \param test Current test case.
 */
static void run_backup_test(const struct test_case *test)
{
	volatile uint32_t wakeup_cause = bpm_get_backup_wakeup_cause(BPM);
	/* Wakeup from backup mode */
	if (wakeup_cause) {
		test_assert_true(test, wakeup_cause & (1 << BPM_BKUPWEN_AST),
			"Unexpected backup wakeup cause, should be AST!");
		return;
	}

	/* Wait for the printf operation to finish before
	setting the device in a power save mode. */
	delay_ms(30);

	/* Enter backup mode */
	bpm_sleep(BPM, BPM_SM_BACKUP);
}

/**
 * \brief Test power scaling switch.
 *
 * \param test Current test case.
 */
static void run_ps_test(const struct test_case *test)
{
	uint32_t timeout = sysclk_get_cpu_hz() / 1000 * 10; /* Wait 10ms */
	bool b_psok;

	b_psok = bpm_power_scaling_cpu_failsafe(BPM, BPM_PMCON_PS(BPM_PS_1),
			timeout);
	test_assert_true(test, b_psok, "Switch to PS1: PSOK not ready");
	wait_test_assert_idle();

	b_psok = bpm_power_scaling_cpu_failsafe(BPM, BPM_PMCON_PS(BPM_PS_0),
			timeout);
	test_assert_true(test, b_psok, "Switch to PS0: PSOK not ready");
	wait_test_assert_idle();
}

/**
 * \brief Test entering and exiting retention mode.
 *
 * \param test Current test case.
 */
static void run_ret_test(const struct test_case *test)
{
	/* Wait for the printf operation to finish before
	setting the device in a power save mode. */
	delay_ms(30);

	reset_log();
	bpm_sleep(BPM, BPM_SM_RET);
	log_event(EVENT_RUN);

	test_assert_true(test, IS_NB_EVENTS_OK(),
		"Unexpected number of events, should be 2");
	test_assert_true(test, IS_EVENTS_OK(),
		"Unexpected events sequence");
	wait_test_assert_idle();
}

/**
 * \brief Test entering and exiting wait mode.
 *
 * \param test Current test case.
 */
static void run_wait_test(const struct test_case *test)
{
	/* Wait for the printf operation to finish before
	setting the device in a power save mode. */
	delay_ms(30);

	reset_log();
	bpm_sleep(BPM, BPM_SM_WAIT);
	log_event(EVENT_RUN);

	test_assert_true(test, IS_NB_EVENTS_OK(),
		"Unexpected number of events, should be 2");
	test_assert_true(test, IS_EVENTS_OK(),
		"Unexpected events sequence");
	wait_test_assert_idle();
}

/**
 * \brief Test entering and exiting sleep 3 mode.
 *
 * \param test Current test case.
 */
static void run_sleep_3_test(const struct test_case *test)
{
	/* Wait for the printf operation to finish before
	setting the device in a power save mode. */
	delay_ms(30);

	reset_log();
	bpm_sleep(BPM, BPM_SM_SLEEP_3);
	log_event(EVENT_RUN);

	test_assert_true(test, IS_NB_EVENTS_OK(),
		"Unexpected number of events, should be 2");
	test_assert_true(test, IS_EVENTS_OK(),
		"Unexpected events sequence");
	wait_test_assert_idle();
}

/**
 * \brief Test entering and exiting sleep 2 mode.
 *
 * \param test Current test case.
 */
static void run_sleep_2_test(const struct test_case *test)
{
	/* Wait for the printf operation to finish before
	setting the device in a power save mode. */
	delay_ms(30);

	reset_log();
	bpm_sleep(BPM, BPM_SM_SLEEP_2);
	log_event(EVENT_RUN);

	test_assert_true(test, IS_NB_EVENTS_OK(),
		"Unexpected number of events, should be 2");
	test_assert_true(test, IS_EVENTS_OK(),
		"Unexpected events sequence");
	wait_test_assert_idle();
}

/**
 * \brief Test entering and exiting sleep 1 mode.
 *
 * \param test Current test case.
 */
static void run_sleep_1_test(const struct test_case *test)
{
	/* Wait for the printf operation to finish before
	setting the device in a power save mode. */
	delay_ms(30);

	reset_log();
	bpm_sleep(BPM, BPM_SM_SLEEP_1);
	log_event(EVENT_RUN);

	test_assert_true(test, IS_NB_EVENTS_OK(),
		"Unexpected number of events, should be 2");
	test_assert_true(test, IS_EVENTS_OK(),
		"Unexpected events sequence");
	wait_test_assert_idle();
}

/**
 * \brief Test entering and exiting sleep 0 mode.
 *
 * \param test Current test case.
 */
static void run_sleep_0_test(const struct test_case *test)
{
	/* Wait for the printf operation to finish before
	setting the device in a power save mode. */
	delay_ms(30);

	reset_log();
	bpm_sleep(BPM, BPM_SM_SLEEP_0);
	log_event(EVENT_RUN);

	test_assert_true(test, IS_NB_EVENTS_OK(),
		"Unexpected number of events, should be 2");
	test_assert_true(test, IS_EVENTS_OK(),
		"Unexpected events sequence");
	wait_test_assert_idle();
}

/**
 * \brief Run BPM driver unit tests.
 */
int main(void)
{
	struct ast_config ast_conf;

	const usart_serial_options_t usart_serial_options = {
		.baudrate = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits = CONF_TEST_STOPBITS
	};

	sysclk_init();
	board_init();
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Initialize AST for all tests */
	/* Enable osc32 oscillator*/
	if (!osc_is_ready(OSC_ID_OSC32)) {
		osc_enable(OSC_ID_OSC32);
		osc_wait_ready(OSC_ID_OSC32);
	}

	/* Enable the AST. */
	ast_enable(AST);

	ast_conf.mode = AST_COUNTER_MODE;
	ast_conf.osc_type = AST_OSC_32KHZ;
	ast_conf.psel = AST_PSEL_32KHZ_1HZ;
	ast_conf.counter = 0;
	ast_set_config(AST, &ast_conf);

	/* Set periodic 0 to interrupt after 1/16 second in counter mode. */
	ast_clear_interrupt_flag(AST, AST_INTERRUPT_PER);
	ast_write_periodic0_value(AST, AST_PSEL_32KHZ_1HZ - 2);

	ast_set_callback(AST, AST_INTERRUPT_PER, ast_per_callback,
		AST_PER_IRQn, 1);

	ast_enable_wakeup(AST, AST_WAKEUP_PER);

	/* AST can wakeup the device */
	bpm_enable_wakeup_source(BPM, (1 << BPM_BKUPWEN_AST));
	/**
	 * Retain I/O lines after wakeup from backup.
	 * Disable to undo the previous retention state then enable.
	 */
	bpm_disable_io_retention(BPM);
	bpm_enable_io_retention(BPM);
	/* Enable fast wakeup */
	bpm_enable_fast_wakeup(BPM);

	/* Define all the test cases. */
	DEFINE_TEST_CASE(backup_test, NULL, run_backup_test, NULL,
			"Backup Power Manager, Backup mode & wakeup.");
	DEFINE_TEST_CASE(ps_test, NULL, run_ps_test, NULL,
			"Backup Power Manager, Power Scaling.");
	DEFINE_TEST_CASE(ret_test, NULL, run_ret_test, NULL,
			"Backup Power Manager, Retention mode & wakeup.");
	DEFINE_TEST_CASE(wait_test, NULL, run_wait_test, NULL,
			"Backup Power Manager, Wait mode & wakeup.");
	DEFINE_TEST_CASE(sleep_3_test, NULL, run_sleep_3_test, NULL,
			"Backup Power Manager, Sleep mode 3 & wakeup.");
	DEFINE_TEST_CASE(sleep_2_test, NULL, run_sleep_2_test, NULL,
			"Backup Power Manager, Sleep mode 2 & wakeup.");
	DEFINE_TEST_CASE(sleep_1_test, NULL, run_sleep_1_test, NULL,
			"Backup Power Manager, Sleep mode 1 & wakeup.");
	DEFINE_TEST_CASE(sleep_0_test, NULL, run_sleep_0_test, NULL,
			"Backup Power Manager, Sleep mode 0 & wakeup.");

	/* Put test case addresses in an array. */
	DEFINE_TEST_ARRAY(bpm_tests) = {
			&backup_test,
			&ps_test,
			&ret_test,
			&wait_test,
			&sleep_3_test,
			&sleep_2_test,
			&sleep_1_test,
			&sleep_0_test,
			};

	/* Define the test suite. */
	DEFINE_TEST_SUITE(bpm_suite, bpm_tests, "SAM BPM driver test suite");

	/* Run all tests in the test suite. */
	test_suite_run(&bpm_suite);

	/* Disable the AST */
	ast_disable(AST);

	while (1) {
		/* Busy-wait forever. */
	}
}
