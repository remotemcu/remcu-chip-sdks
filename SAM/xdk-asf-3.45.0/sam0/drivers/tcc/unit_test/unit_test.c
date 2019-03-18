/**
 * \file
 *
 * \brief SAM TCC Unit test
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

/**
 * \mainpage SAM TCC Unit Test
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This unit test carries out tests for TCC driver.
 * It consists of test cases for the following functionalities:
 *  - Test for driver initialization.
 *  - Test for TCC start/stop
 *  - Test for TCC callback generation
 *  - Test for 24-bit TCC operation
 *  - Test for compare and capture TCC operation
 */

/**
 * \page appdoc_main SAM TCC Unit Test
 *
 * Overview:
 * - \ref appdoc_sam0_tcc_unit_test_intro
 * - \ref appdoc_sam0_tcc_unit_test_setup
 * - \ref appdoc_sam0_tcc_unit_test_usage
 * - \ref appdoc_sam0_tcc_unit_test_compinfo
 * - \ref appdoc_sam0_tcc_unit_test_contactinfo
 *
 * \section appdoc_sam0_tcc_unit_test_intro Introduction
 * \copydetails appdoc_preface
 *
 * The following kit is required for carrying out the test:
 *  - SAM D21/R21/L21/DA1/C21/R30/R34 Xplained Pro board
 *
 * \section appdoc_sam0_tcc_unit_test_setup Setup
 * The following connections has to be made using wires:
 * - SAM D21/DA1 Xplained Pro:
 *  - \b EXTINT 4 (PB04, EXT1 pin 9 ) <-----> TCC0 WO0 (PA08, EXT2 pin 11)
 * - SAM R21 Xplained Pro:
 *  - \b EXTINT 6 (PA06, EXT1 pin 3 ) <-----> TCC0 WO0 (PA08, EXT3 pin 10)
 * - SAM L21 Xplained Pro:
 *  - \b EXTINT 4 (PB04, EXT1 pin 9 ) <-----> TCC0 WO0 (PB30, EXT3 pin 5)
 * - SAM C21 Xplained Pro:
 *  - \b EXTINT 4 (PA20, EXT1 pin 5 ) <-----> TCC0 WO0 (PA08, EXT2 pin 3)
 * - SAM R30 Xplained Pro:
 *  - \b EXTINT 3 (PB03, EXT1 pin 15 ) <-----> TCC0 WO0 (PA08, EXT3 pin 10)
 * - SAM R30 Module Xplained Pro:
 *  - \b EXTINT 8 (PA28, EXT pin 10 ) <-----> TCC0 WO0 (PA08, EXT pin 11)
 * - SAM R34 Xplained Pro:
 *  - \b EXTINT 7 (PA28, EXT1 pin 6 ) <-----> TCC0 WO0 (PA08, EXT1 pin 5)
 *
 * To run the test:
 *  - Connect the SAM Xplained Pro board to the computer using a
 *    micro USB cable.
 *  - Open the virtual COM port in a terminal application.
 *    \note The USB composite firmware running on the Embedded Debugger (EDBG)
 *          will enumerate as debugger, virtual COM port and EDBG data
 *          gateway.
 *  - Build the project, program the target and run the application.
 *    The terminal shows the results of the unit test.
 *
 * \section appdoc_sam0_tcc_unit_test_usage Usage
 *  - The unit tests are carried out using the several TCC modules internally
 *    for internal checks.
 *  - The EXTINT module is connected to a TCC module so that it can detect the
 *    correct TCC waveform output.
 *
 * \section appdoc_sam0_tcc_unit_test_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_tcc_unit_test_contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com">http://www.microchip.com</a>.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <stdio_serial.h>
#include <string.h>
#include "conf_test.h"
#include "conf_clocks.h"

/* Structure for UART module connected to EDBG (used for unit test output) */
static struct usart_module cdc_uart_module;

/* TCC modules used in tests */
static struct tcc_module tcc_test0_module;
static struct tcc_module tcc_test1_module;

/* Config structs used in tests */
static struct tcc_config tcc_test0_config;
static struct tcc_config tcc_test1_config;

static bool tcc_init_success = 0;

static volatile uint32_t callback_function_entered = 0;
static volatile bool basic_functionality_test_passed = false;

/**
 * \internal
 * \brief Function used to test callback API
 *
 * This function indicates that the callback function has been invoked.
 */
static void tcc_callback_function(struct tcc_module *const module_inst)
{
	callback_function_entered += 1;
}

/**
 * \internal
 * \brief Test of tcc_init() and tcc_get_config_defaults()
 *
 * This test is used to initialize the tccx_module structs and associate the
 * given hw module with the struct. This test should be run at the very
 * beginning of testing as other tests depend on the result of this test.
 */
static void run_init_test(const struct test_case *test)
{
	tcc_get_config_defaults(&tcc_test0_config, CONF_TEST_TCC0);
	enum status_code test1 = tcc_init(&tcc_test0_module, CONF_TEST_TCC0,
			&tcc_test0_config);

	tcc_get_config_defaults(&tcc_test1_config, CONF_TEST_TCC1);
	enum status_code test2 = tcc_init(&tcc_test1_module, CONF_TEST_TCC1,
			&tcc_test1_config);

	if ((test1 == STATUS_OK) && (test2 == STATUS_OK)) {
		tcc_init_success = true;
	}

	test_assert_true(test,
			(test2 == STATUS_OK) && (test1 == STATUS_OK),
			"Failed to initialize modules");
}


/**
 * \internal
 * \brief Test initializing and resetting TCC and reinitialize
 *
 * This test tests the software reset of a TCC by the use of the
 * tcc_reset().
 *
 * \param test Current test case.
 */
static void run_reset_test(const struct test_case *test)
{
	test_assert_true(test,
			tcc_init_success == true,
			"TCC initialization failed, skipping test");

	/* Configure TCC module and run test*/
	tcc_reset(&tcc_test0_module);
	tcc_get_config_defaults(&tcc_test0_config, CONF_TEST_TCC0);

	tcc_init(&tcc_test0_module, CONF_TEST_TCC0, &tcc_test0_config);
	tcc_enable(&tcc_test0_module);

	while (tcc_is_syncing(&tcc_test0_module)) {
		/* Synchronize enable */
	}

	test_assert_true(test,
			tcc_test0_module.hw->CTRLA.reg & TCC_CTRLA_ENABLE,
			"Failed first enable of TCC");

	/* Reset and test if both TCC modules are disabled after reset */
	tcc_reset(&tcc_test0_module);

	while (tcc_is_syncing(&tcc_test0_module)) {
		/* Synchronize reset */
	}

	test_assert_false(test,
			tcc_test0_module.hw->CTRLA.reg & TCC_CTRLA_ENABLE,
			"Failed reset of TCC TEST");
}

/**
 * \internal
 * \brief Test basic functionality.
 *
 * This test tests the basic functionality for the TCC. It tests the following
 * functions:
 *  - tcc_get_count_value()
 *  - tcc_stop_counter()
 *  - tcc_set_count_value()
 *  - tcc_restart_counter()
 *
 * \param test Current test case.
 */
static void run_basic_functionality_test(const struct test_case *test)
{
	test_assert_true(test,
			tcc_init_success == true,
			"TCC initialization failed, skipping test");

	/* Setup TCC0 */
	tcc_reset(&tcc_test0_module);
	tcc_get_config_defaults(&tcc_test0_config, CONF_TEST_TCC0);

	tcc_init(&tcc_test0_module, CONF_TEST_TCC0, &tcc_test0_config);
	tcc_enable(&tcc_test0_module);

	/* Test tcc_get_count_value() */
	uint32_t test_val0 = tcc_get_count_value(&tcc_test0_module);

	test_assert_true(test,
			test_val0 > 0,
			"The tcc_get_count_value() returned 0 expected larger value");

	/* Test tcc_stop_counter() */
	tcc_stop_counter(&tcc_test0_module);

	uint32_t test_val1 = tcc_get_count_value(&tcc_test0_module);
	uint32_t test_val2 = tcc_get_count_value(&tcc_test0_module);

	test_assert_true(test,
			test_val1 == test_val2,
			"The counter failed to stop");

	/* Test tcc_set_count_value() */
	tcc_set_count_value(&tcc_test0_module, 0x00FF);

	test_assert_true(test,
			tcc_get_count_value(&tcc_test0_module) == 0x00FF,
			"tcc_set_count_value() have failed");

	/* Test tcc_start_counter() */
	tcc_restart_counter(&tcc_test0_module);

	test_assert_true(test,
			tcc_get_count_value(&tcc_test0_module) > 0x00FF,
			"tcc_get_count_value() have failed");

	basic_functionality_test_passed = true;
}

/**
 * \internal
 * \brief Test the callback API
 *
 * This test tests the callback API for the TCC. The TCC uses one-shot mode.
 *
 * \param test Current test case.
 */
static void run_callback_test(const struct test_case *test)
{
	test_assert_true(test,
			tcc_init_success == true,
			"TCC initialization failed, skipping test");

	test_assert_true(test,
			basic_functionality_test_passed == true,
			"Basic functionality test failed, skipping test");

	/* Setup TCC0 */
	tcc_reset(&tcc_test0_module);
	tcc_get_config_defaults(&tcc_test0_config, CONF_TEST_TCC0);

	tcc_test0_config.counter.period = 4000;
	tcc_test0_config.compare.wave_generation = TCC_WAVE_GENERATION_NORMAL_FREQ;
	tcc_test0_config.compare.match[TCC_MATCH_CAPTURE_CHANNEL_0] = 3990;

	tcc_init(&tcc_test0_module, CONF_TEST_TCC0, &tcc_test0_config);

	/* Setup callbacks */
	tcc_register_callback(&tcc_test0_module, tcc_callback_function,
			TCC_CALLBACK_CHANNEL_0);
	tcc_enable_callback(&tcc_test0_module, TCC_CALLBACK_CHANNEL_0);

	tcc_enable(&tcc_test0_module);

	while ((tcc_get_status(&tcc_test0_module) &
			TCC_STATUS_COUNT_OVERFLOW) == 0) {
		/* Wait for overflow of TCC1 */
	}

	tcc_disable(&tcc_test0_module);
	tcc_clear_status(&tcc_test0_module, TCC_STATUS_COUNT_OVERFLOW);

	test_assert_true(test,
			callback_function_entered == 1,
			"The callback has failed callback_function_entered = %d",
			(int)callback_function_entered);

	/* Test disable callback function */
	tcc_disable_callback(&tcc_test0_module, TCC_CALLBACK_CHANNEL_0);
	tcc_set_count_value(&tcc_test0_module, 0x00000000);

	tcc_enable(&tcc_test0_module);

	while (!(tcc_get_status(&tcc_test0_module) & TCC_STATUS_COUNT_OVERFLOW)) {
		/* Wait for overflow of TC1*/
	}

	/* Test tcc_disable() */
	tcc_disable(&tcc_test0_module);

	test_assert_true(test,
			callback_function_entered == 1,
			"Disabling the callback has failed");
}

/**
 * \internal
 * \brief Test capture and compare
 *
 * This test uses TCC0 as a PWM generator (compare function). TCC1 will be set
 * to capture the signal from TCC0 to test the capture functionality.
 *
 * \param test Current test case.
 */
static void run_capture_and_compare_test(const struct test_case *test)
{
	test_assert_true(test,
			tcc_init_success == true,
			"TCC initialization failed, skipping test");

	test_assert_true(test,
			callback_function_entered == 1,
			"The callback test has failed, skipping test");

	/* Configure TCC module for PWM generation */
	tcc_reset(&tcc_test0_module);
	tcc_get_config_defaults(&tcc_test0_config, CONF_TEST_TCC0);
	tcc_test0_config.counter.period = 0x03FF;
	tcc_test0_config.compare.wave_generation  =
			TCC_WAVE_GENERATION_SINGLE_SLOPE_PWM;
	tcc_test0_config.compare.match[TCC_MATCH_CAPTURE_CHANNEL_0]  = 0x01FF;

	/* Calculate the theoretical PWM frequency & duty */
	uint32_t frequency_output, duty_output;
	frequency_output = system_clock_source_get_hz(CONF_CLOCK_GCLK_0_CLOCK_SOURCE) / (0x03FF+1);

	/* This value is depend on the WaveGeneration Mode */
	duty_output = (uint32_t)(tcc_test0_config.compare.match[TCC_MATCH_CAPTURE_CHANNEL_0] * 100) /
			tcc_test0_config.counter.period;

	tcc_test0_config.pins.enable_wave_out_pin[TCC_MATCH_CAPTURE_CHANNEL_0] = true;
	tcc_test0_config.pins.wave_out_pin[TCC_MATCH_CAPTURE_CHANNEL_0]        = CONF_TEST_PIN_OUT;
	tcc_test0_config.pins.wave_out_pin_mux[TCC_MATCH_CAPTURE_CHANNEL_0]    = CONF_TEST_PIN_MUX;
	tcc_init(&tcc_test0_module, CONF_TEST_TCC0, &tcc_test0_config);

	tcc_register_callback(&tcc_test0_module, tcc_callback_function, TCC_CALLBACK_CHANNEL_0);
	tcc_enable_callback(&tcc_test0_module, TCC_CALLBACK_CHANNEL_0);

	/* Configure TCC module for capture */
	tcc_reset(&tcc_test1_module);
	tcc_get_config_defaults(&tcc_test1_config, CONF_TEST_TCC1);
	tcc_test1_config.counter.period          = 0xFFFF;
	tcc_test1_config.counter.clock_prescaler = TCC_CLOCK_PRESCALER_DIV1;
	tcc_test1_config.capture.channel_function[CONF_CAPTURE_CHAN_0] = TCC_CHANNEL_FUNCTION_CAPTURE;
	tcc_test1_config.capture.channel_function[CONF_CAPTURE_CHAN_1] = TCC_CHANNEL_FUNCTION_CAPTURE;

	tcc_init(&tcc_test1_module, CONF_TEST_TCC1, &tcc_test1_config);

	struct tcc_events tcc_events = {
		.on_input_event_perform_action[1] = true,
		.input_config[1].modify_action = true,
		.input_config[1].action = TCC_EVENT_ACTION_PERIOD_PULSE_WIDTH_CAPTURE
	};

	tcc_enable_events(&tcc_test1_module, &tcc_events);

	/* Configure external interrupt controller */
	struct extint_chan_conf extint_chan_config;
	extint_chan_config.gpio_pin            = CONF_EIC_PIN;
	extint_chan_config.gpio_pin_mux        = CONF_EIC_MUX;
	extint_chan_config.gpio_pin_pull       = EXTINT_PULL_UP;
#if (!SAML21 && !SAMC21 && !SAMR30 && !SAMR34)
	extint_chan_config.wake_if_sleeping    = false;
#endif
	extint_chan_config.filter_input_signal = false;
	extint_chan_config.detection_criteria  = EXTINT_DETECT_HIGH;
	extint_chan_set_config(CONF_EIC_CHAN, &extint_chan_config);

	/* Configure external interrupt module to be event generator */
	struct extint_events extint_event_conf;
	extint_event_conf.generate_event_on_detect[CONF_EIC_CHAN] = true;
	extint_enable_events(&extint_event_conf);

	/* Configure event system */
	struct events_resource event_res;

	/* Configure channel */
	struct events_config config;
	events_get_config_defaults(&config);
	config.generator      = CONF_EVENT_GENERATOR_ID;
	config.edge_detect    = EVENTS_EDGE_DETECT_NONE;
	config.path           = EVENTS_PATH_ASYNCHRONOUS;
	events_allocate(&event_res, &config);

	/* Configure user */
	events_attach_user(&event_res, CONF_EVENT_USED_ID);

	/* Enable TCC modules */
	tcc_enable(&tcc_test1_module);
	tcc_enable(&tcc_test0_module);

	uint16_t period_after_capture = 0;
	uint16_t pulse_width_after_capture = 0;
	uint32_t capture_frequency = 0;
	uint32_t capture_duty = 0;

	while (callback_function_entered < 4) {
		period_after_capture = tcc_get_capture_value(&tcc_test1_module,
				TCC_MATCH_CAPTURE_CHANNEL_0);
		pulse_width_after_capture = tcc_get_capture_value(&tcc_test1_module,
				TCC_MATCH_CAPTURE_CHANNEL_1);
	}

	if(period_after_capture != 0) {
		capture_frequency =
				system_clock_source_get_hz(CONF_CLOCK_GCLK_0_CLOCK_SOURCE) /
				period_after_capture;
		capture_duty = (uint32_t)(pulse_width_after_capture) * 100 /
				period_after_capture;
	}

	test_assert_true(test,
			(capture_frequency <= (frequency_output * (100 + CONF_TEST_TOLERANCE) / 100)) && \
			(capture_frequency >= (frequency_output * (100 - CONF_TEST_TOLERANCE) / 100)) && \
			(capture_duty <= (duty_output * (100 + CONF_TEST_TOLERANCE) / 100)) && \
			(capture_duty >= (duty_output * (100 - CONF_TEST_TOLERANCE) / 100)) \
			,"The result of Capture is wrong, captured frequency: %ldHz, captured duty: %ld%%",
			capture_frequency,
			capture_duty
			);
}

/**
 * \internal
 * \brief Test Recoverable Fault (FAULTn)
 *
 * This test uses TCC0 as a PWM generator (compare function).
 * EXTINT will be used to route fault input to TCC0.
 *
 * \param test Current test case.
 */
static void run_faultn_test(const struct test_case *test)
{
	test_assert_true(test,
			tcc_init_success == true,
			"TCC initialization failed, skipping test");

	/* Configure TCC module for PWM generation with fault */
	tcc_reset(&tcc_test0_module);
	tcc_get_config_defaults(&tcc_test0_config, CONF_TEST_TCC0);
	tcc_test0_config.counter.period = 0x03FF;
	tcc_test0_config.compare.wave_generation  =
			TCC_WAVE_GENERATION_SINGLE_SLOPE_PWM;
	tcc_test0_config.compare.match[TCC_MATCH_CAPTURE_CHANNEL_0]  = 0x01FF;
	tcc_test0_config.wave_ext.recoverable_fault[TCC_MATCH_CAPTURE_CHANNEL_0].source = TCC_FAULT_SOURCE_ENABLE;
	tcc_test0_config.wave_ext.recoverable_fault[TCC_MATCH_CAPTURE_CHANNEL_0].halt_action = TCC_FAULT_HALT_ACTION_SW_HALT;
	tcc_init(&tcc_test0_module, CONF_TEST_TCC0, &tcc_test0_config);
	/* Configure TCC events for recoverable fault input */
	struct tcc_events tcc_test_events;
	memset(&tcc_test_events, 0, sizeof(struct tcc_events));
	tcc_test_events.on_event_perform_channel_action[TCC_MATCH_CAPTURE_CHANNEL_0] = true;
	tcc_enable_events(&tcc_test0_module, &tcc_test_events);
	tcc_enable(&tcc_test0_module);

	/* Configure IO pin to generate fault */
	struct port_config config_pin;
	port_get_config_defaults(&config_pin);
	config_pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(CONF_TEST_PIN_OUT, &config_pin);
	port_pin_set_output_level(CONF_TEST_PIN_OUT, true);

	/* Configure EIC to capture fault input */
	struct extint_chan_conf config;
	extint_chan_get_config_defaults(&config);
	config.filter_input_signal = true;
	config.detection_criteria  = EXTINT_DETECT_BOTH;
	config.gpio_pin     = CONF_EIC_PIN;
	config.gpio_pin_mux = CONF_EIC_MUX;
	extint_chan_set_config(CONF_EIC_CHAN, &config);

	struct extint_events extint_test_events;
	memset(&extint_test_events, 0, sizeof(struct extint_events));
	extint_test_events.generate_event_on_detect[CONF_EIC_CHAN] = true;
	extint_enable_events(&extint_test_events);

	/* Configure EVENTs to route fault input */
	struct events_resource event_resource;
	struct events_config event_config;
	events_get_config_defaults(&event_config);
	event_config.generator = CONF_EVENT_GENERATOR_ID;
	event_config.path      = EVENTS_PATH_ASYNCHRONOUS;
	events_allocate(&event_resource, &event_config);
	events_attach_user(&event_resource, CONF_EVENT_USER_ID_FAULTn);

	/* Clear halt status */
	tcc_clear_status(&tcc_test0_module,
			TCC_STATUS_RECOVERABLE_FAULT_PRESENT(0) |
			TCC_STATUS_RECOVERABLE_FAULT_OCCUR(0));

	uint32_t test_val1 = tcc_get_count_value(&tcc_test0_module);
	uint32_t test_val2 = tcc_get_count_value(&tcc_test0_module);

	/* Check TCC is running */
	test_assert_true(test,
			test_val1 != test_val2,
			"The counter failed to stop on recoverable fault");

	/* Set fault */
	port_pin_set_output_level(CONF_TEST_PIN_OUT, false);

	/* Check fault state */
	test_assert_true(test,
			TCC_STATUS_RECOVERABLE_FAULT_OCCUR(0) &
					tcc_get_status(&tcc_test0_module),
			"The counter failed to detect recoverable fault");

	/* Check TCC is running */
	test_val1 = tcc_get_count_value(&tcc_test0_module);
	test_val2 = tcc_get_count_value(&tcc_test0_module);
	test_assert_true(test,
			test_val1 == test_val2,
			"The counter failed to stop on recoverable fault");
}

/**
 * \internal
 * \brief Test Non-Recoverable Fault (FAULTx)
 *
 * This test uses TCC0 as a PWM generator (compare function).
 * EXTINT will be used to route fault input to TCC0.
 *
 * \param test Current test case.
 */
static void run_faultx_test(const struct test_case *test)
{
	test_assert_true(test,
	tcc_init_success == true,
	"TCC initialization failed, skipping test");

	/* Configure TCC module for PWM generation with fault */
	tcc_reset(&tcc_test0_module);
	tcc_get_config_defaults(&tcc_test0_config, CONF_TEST_TCC0);
	tcc_test0_config.counter.period = 0x03FF;
	tcc_test0_config.compare.wave_generation  =
	TCC_WAVE_GENERATION_SINGLE_SLOPE_PWM;
	tcc_test0_config.compare.match[TCC_MATCH_CAPTURE_CHANNEL_0]  = 0x01FF;
	tcc_test0_config.wave_ext.non_recoverable_fault[TCC_WAVE_OUTPUT_0].output = TCC_FAULT_STATE_OUTPUT_1;
	tcc_init(&tcc_test0_module, CONF_TEST_TCC0, &tcc_test0_config);
	/* Configure TCC events for non-recoverable fault input */
	struct tcc_events tcc_test_events;
	memset(&tcc_test_events, 0, sizeof(struct tcc_events));
	tcc_test_events.on_input_event_perform_action[0] = true;
	tcc_test_events.input_config[0].modify_action = true;
	tcc_test_events.input_config[0].action = TCC_EVENT_ACTION_NON_RECOVERABLE_FAULT;
	tcc_enable_events(&tcc_test0_module, &tcc_test_events);
	tcc_enable(&tcc_test0_module);

	/* Configure IO pin to generate fault */
	struct port_config config_pin;
	port_get_config_defaults(&config_pin);
	config_pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(CONF_TEST_PIN_OUT, &config_pin);
	port_pin_set_output_level(CONF_TEST_PIN_OUT, true);

	/* Configure EIC to capture fault input */
	struct extint_chan_conf config;
	extint_chan_get_config_defaults(&config);
	config.filter_input_signal = true;
	config.detection_criteria  = EXTINT_DETECT_BOTH;
	config.gpio_pin     = CONF_EIC_PIN;
	config.gpio_pin_mux = CONF_EIC_MUX;
	extint_chan_set_config(CONF_EIC_CHAN, &config);

	struct extint_events extint_test_events;
	memset(&extint_test_events, 0, sizeof(struct extint_events));
	extint_test_events.generate_event_on_detect[CONF_EIC_CHAN] = true;
	extint_enable_events(&extint_test_events);

	/* Configure EVENTs to route fault input */
	struct events_resource event_resource;
	struct events_config event_config;
	events_get_config_defaults(&event_config);
	event_config.generator = CONF_EVENT_GENERATOR_ID;
	event_config.path      = EVENTS_PATH_ASYNCHRONOUS;
	events_allocate(&event_resource, &event_config);
	events_attach_user(&event_resource, CONF_EVENT_USER_ID_FAULTx);

	/* Clear halt status */
	tcc_clear_status(&tcc_test0_module,
			TCC_STATUS_NON_RECOVERABLE_FAULT_PRESENT(0) |
			TCC_STATUS_NON_RECOVERABLE_FAULT_OCCUR(0));

	uint32_t test_val1 = tcc_get_count_value(&tcc_test0_module);
	uint32_t test_val2 = tcc_get_count_value(&tcc_test0_module);

	/* Check TCC is running */
	test_assert_true(test,
			test_val1 != test_val2,
			"The counter failed to stop on non-recoverable fault");

	/* Set fault */
	port_pin_set_output_level(CONF_TEST_PIN_OUT, false);

	/* Check fault state */
	test_assert_true(test,
				TCC_STATUS_NON_RECOVERABLE_FAULT_OCCUR(0) &
						tcc_get_status(&tcc_test0_module),
				"The counter failed to detect non-recoverable fault");

	/* Check TCC is running */
	test_val1 = tcc_get_count_value(&tcc_test0_module);
	test_val2 = tcc_get_count_value(&tcc_test0_module);
	test_assert_true(test,
			test_val1 == test_val2,
			"The counter failed to stop on non-recoverable fault");
}

/**
 * \brief Initialize the USART for unit test
 *
 * Initializes the SERCOM USART used for sending the unit test status to the
 * computer via the EDBG CDC gateway.
 */
static void cdc_uart_init(void)
{
	struct usart_config usart_conf;

	/* Configure USART for unit test output */
	usart_get_config_defaults(&usart_conf);
	usart_conf.mux_setting = CONF_STDIO_MUX_SETTING;
	usart_conf.pinmux_pad0 = CONF_STDIO_PINMUX_PAD0;
	usart_conf.pinmux_pad1 = CONF_STDIO_PINMUX_PAD1;
	usart_conf.pinmux_pad2 = CONF_STDIO_PINMUX_PAD2;
	usart_conf.pinmux_pad3 = CONF_STDIO_PINMUX_PAD3;
	usart_conf.baudrate    = CONF_STDIO_BAUDRATE;

	stdio_serial_init(&cdc_uart_module, CONF_STDIO_USART, &usart_conf);
	usart_enable(&cdc_uart_module);
}

/**
 * \brief Run TCC unit tests
 *
 * Initializes the system and serial output, then sets up the TCC unit test
 * suite and runs it.
 */
int main(void)
{
	system_init();
	cdc_uart_init();

	/* Define Test Cases */
	DEFINE_TEST_CASE(init_test, NULL,
			run_init_test, NULL,
			"Initialize tcc_xmodules");

	DEFINE_TEST_CASE(basic_functionality_test, NULL,
			run_basic_functionality_test, NULL,
			"test start stop and getters and setters");

	DEFINE_TEST_CASE(callback_test, NULL,
			run_callback_test, NULL,
			"test callback API");

	DEFINE_TEST_CASE(reset_test, NULL,
			run_reset_test, NULL,
			"Setup, reset TCC module");

	DEFINE_TEST_CASE(capture_and_compare_test, NULL,
			run_capture_and_compare_test, NULL,
			"Test capture and compare");

	DEFINE_TEST_CASE(faultx_test, NULL,
			run_faultx_test, NULL,
			"Test Non-Recoverable Fault");

	DEFINE_TEST_CASE(faultn_test, NULL,
			run_faultn_test, NULL,
			"Test Recoverable Fault");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(tcc_tests) = {
		&init_test,
		&basic_functionality_test,
		&callback_test,
		&reset_test,
		&capture_and_compare_test,
		&faultx_test,
		&faultn_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(tcc_suite, tcc_tests,
			"SAM TCC driver test suite");

	/* Run all tests in the suite*/
	test_suite_run(&tcc_suite);

	tcc_reset(&tcc_test0_module);
	tcc_reset(&tcc_test1_module);

	while (true) {
		/* Intentionally left empty */
	}
}
