/**
 * \file
 *
 * \brief Unit tests for PICOUART driver.
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
#include "board_monitor.h"

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the PICOUART driver. It requires
 * a board monitor firmware version V1.3 or greater.
 * It contains one test case for the PICOUART module:
 * - Test wakeup functions.
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_uart_serial.h
 *
 * \section device_info Device Info
 * SAM4L devices can be used.
 * This example has been tested with the following setup:
 * - sam4lc4c_sam4l_ek
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for ARM. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */

void PM_Handler(void)
{
	Pm *p_pm = PM;
	p_pm->PM_ICR = PM_ICR_WAKE;
}

/**
 * \brief Test board monitor functions.
 *
 * \param test Current test case.
 */
static void run_getversion_test(const struct test_case *test)
{
	uint8_t fw_minor_version, fw_major_version;

	/* For test */
	bm_get_firmware_version(&fw_minor_version, &fw_major_version);
	test_assert_true(test, fw_minor_version == '3', "FW minor version error!");
	test_assert_true(test, fw_major_version == '1', "FW major version error!");
}

/**
 * \brief Test wakeup functions.
 *
 * \param test Current test case.
 */
static void run_picouart_test(const struct test_case *test)
{
	uint8_t value;
	Pm *p_pm = PM;
	struct picouart_dev_inst dev_inst;
	struct picouart_config config;

	/* Init the PICOUART */
	picouart_get_config_defaults(&config);
	picouart_init(&dev_inst, PICOUART, &config);

	/* Enable the PICOUART */
	picouart_enable(&dev_inst);
	delay_ms(30);

	/* PICOUART can wakeup the device. */
	bpm_enable_wakeup_source(BPM, (1 << BPM_BKUPWEN_PICOUART));
	p_pm->PM_AWEN = 1 << PM_AWEN_PICOUART;
	p_pm->PM_IER = PM_IER_WAKE;
	NVIC_SetPriority(PM_IRQn,1);
	NVIC_EnableIRQ(PM_IRQn);

	config.action = PICOUART_ACTION_WAKEUP_ON_STARTBIT;
	picouart_set_config(&dev_inst, &config);
	bm_send_picouart_frame('A', 1);
	bpm_sleep(BPM, BPM_SM_SLEEP_1);

	config.action = PICOUART_ACTION_WAKEUP_ON_FULLFRAME;
	picouart_set_config(&dev_inst, &config);
	bm_send_picouart_frame('T', 5);
	bpm_sleep(BPM, BPM_SM_SLEEP_3);

	config.action = PICOUART_ACTION_WAKEUP_ON_FULLFRAME;
	picouart_set_config(&dev_inst, &config);
	bm_send_picouart_frame('M', 5);
	bpm_sleep(BPM, BPM_SM_WAIT);

	config.action = PICOUART_ACTION_WAKEUP_ON_MATCH;
	config.match = 'L';
	picouart_set_config(&dev_inst, &config);
	bm_send_picouart_frame('L', 10);
	bpm_sleep(BPM, BPM_SM_RET);
	while(!picouart_is_data_ready(&dev_inst)) {
	}
	picouart_read(&dev_inst, &value);
	test_assert_true(test, value == 'L', "Picouart wakeup not work!");

}

/**
 * \brief Run PICOUART driver unit tests.
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

	/* Enable osc32 oscillator*/
	if (!osc_is_ready(OSC_ID_OSC32)) {
		osc_enable(OSC_ID_OSC32);
		osc_wait_ready(OSC_ID_OSC32);
	}

	/* Disable all AST wake enable bits for safety since the AST is reset
	only by a POR. */
	ast_enable(AST);
	ast_conf.mode = AST_COUNTER_MODE;
	ast_conf.osc_type = AST_OSC_32KHZ;
	ast_conf.psel = AST_PSEL_32KHZ_1HZ;
	ast_conf.counter = 0;
	ast_set_config(AST, &ast_conf);
	ast_disable_wakeup(AST, AST_WAKEUP_ALARM);
	ast_disable_wakeup(AST, AST_WAKEUP_PER);
	ast_disable_wakeup(AST, AST_WAKEUP_OVF);
	ast_disable(AST);

	/* Configurate the USART to board monitor */
	bm_init();

	/* Define all the test cases. */
	DEFINE_TEST_CASE(picouart_test, NULL, run_picouart_test, NULL,
			"SAM PICOUART wakeup test.");
	DEFINE_TEST_CASE(getversion_test, NULL, run_getversion_test, NULL,
				"SAM get version test.");

	/* Put test case addresses in an array. */
	DEFINE_TEST_ARRAY(picouart_tests) = {
		&getversion_test,
		&picouart_test,
	};

	/* Define the test suite. */
	DEFINE_TEST_SUITE(picouart_suite, picouart_tests,
			"SAM PICOUART driver test suite");

	/* Run all tests in the test suite. */
	test_suite_run(&picouart_suite);

	while (1) {
		/* Busy-wait forever. */
	}
}
