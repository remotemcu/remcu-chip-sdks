/**
 * \file
 *
 * \brief SAM TC Unit test
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
 * \mainpage SAM TC Unit Test
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This unit test carries out tests for TC driver.
 * It consists of test cases for the following functionalities:
 *  - Test for driver initialization.
 *  - Test for TC start/stop
 *  - Test for TC callback generation
 *  - Test for 32-bit (chained) TC operation
 *  - Test for compare and capture TC operation
 */

/**
 * \page appdoc_main SAM TC Unit Test
 *
 * Overview:
 * - \ref appdoc_sam0_tc_unit_test_intro
 * - \ref appdoc_sam0_tc_unit_test_setup
 * - \ref appdoc_sam0_tc_unit_test_usage
 * - \ref appdoc_sam0_tc_unit_test_compinfo
 * - \ref appdoc_sam0_tc_unit_test_contactinfo
 *
 * \section appdoc_sam0_tc_unit_test_intro Introduction
 * \copydetails appdoc_preface
 *
 * The following kit is required for carrying out the test:
 *  - SAM D20/D21/R21/L21/L22/DA1/C21/R30/HA1G16A Xplained Pro board
 *
 * \section appdoc_sam0_tc_unit_test_setup Setup
 * The following connections has to be made using wires:
 *  - \b SAM D21/D20 Xplained Pro:EXTINT 0 (PB00, EXT1 pin 3) <-----> TC4 WO1 (PB09, EXT1 pin 13)
 *  - \b SAM R21 Xplained Pro:EXTINT 0 (PA16, EXT2 pin 11) <-----> TC4 WO1 (PA23, EXT1 pin 10)
 *  - \b SAM L21 Xplained Pro:EXTINT 0 (PB00, EXT3 pin 3)  <-----> TC0 WO1 (PB09, EXT1 pin 13)
 *  - \b SAM L22 Xplained Pro:EXTINT 2 (PB16, EXT3 pin 7)  <-----> TC0 WO1 (PB09, EXT1 pin 8)
 *  - \b SAM DA1 Xplained Pro:EXTINT 0 (PA16, EXT2 pin 17) <-----> TC4 WO1 (PB09, EXT1 pin 13)
 *  - \b SAM HA1G16A Xplained Pro:EXTINT 0 (PA16, EXT1 pin 10) <-----> TC3 WO1 (PA19, EXT1 pin 8)
 *  - \b SAM C21 Xplained Pro:EXTINT 0 (PB16, EXT2 pin 9)  <-----> TC0 WO1 (PB09, EXT1 pin 3)
 *  - \b SAM R30 Xplained Pro:EXTINT 0 (PA16, EXT1 pin 11)  <-----> TC0 WO1 (PA23, EXT1 pin 10)
 *  - \b SAM R30 Module Xplained Pro:EXTINT 0 (PA16, EXT1 pin 11)  <-----> TC4 WO1 (PA19, EXT pin 17)
 *  - \b SAM R34 Xplained Pro:EXTINT 1 (PA17, EXT1 pin 12)  <-----> TC0 WO1 (PA23, EXT1 pin 15)
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
 * \section appdoc_sam0_tc_unit_test_usage Usage
 *  - The unit tests are carried out using the several TC modules internally
 *    for internal checks.
 *  - The EXTINT module is connected to a TC module so that it can detect the
 *    correct TC waveform output.
 *
 * \section appdoc_sam0_tc_unit_test_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_tc_unit_test_contactinfo Contact Information
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

/* Structure for UART module connected to EDBG (used for unit test output) */
struct usart_module cdc_uart_module;

/* TC modules used in tests */
struct tc_module tc_test0_module;
struct tc_module tc_test1_module;


/* Config structs used in tests */
struct tc_config tc_test0_config;
struct tc_config tc_test1_config;

bool tc_init_success = 0;

volatile uint32_t callback_function_entered = 0;
bool basic_functionality_test_passed = false;

/**
 * \internal
 * \brief Function used to test callback API
 *
 * This function indicates that the callback function has been invoked.
 */
static void tc_callback_function(struct tc_module *const module_inst)
{
	callback_function_entered += 1;
}

/**
 * \internal
 * \brief Test of tc_init() and tc_get_config_defaults()
 *
 * This test is used to initialize the tcx_module structs and associate the given
 * hw module with the struct. This test should be run at the very beginning of
 * testing as other tests depend on the result of this test.
 */
static void run_init_test(const struct test_case *test)
{
	tc_get_config_defaults(&tc_test0_config);
	enum status_code test1 = tc_init(&tc_test0_module, CONF_TEST_TC0, &tc_test0_config);

	tc_get_config_defaults(&tc_test1_config);
	enum status_code test2 = tc_init(&tc_test1_module, CONF_TEST_TC1, &tc_test1_config);

	if ((test1 == STATUS_OK) && (test2 == STATUS_OK)) {
		tc_init_success = true;
	}

	test_assert_true(test,
			(test2 == STATUS_OK) && (test1 == STATUS_OK),
			"Failed to initialize modules");
}

/**
 * \internal
 * \brief Test initializing and resetting 32-bit TC and reinitialize
 *
 * This test tests the software reset of a 32-bit TC by the use of the
 * tc_reset(). It also test re-enabling the two TC modules used in the 32-bit
 * TC into two separate 16-bit TC's.
 *
 * \param test Current test case.
 */
static void run_reset_32bit_master_test(const struct test_case *test)
{
	test_assert_true(test,
			tc_init_success == true,
			"TC initialization failed, skipping test");

	/* Configure 32-bit TC module and run test*/
	tc_reset(&tc_test0_module);
	tc_get_config_defaults(&tc_test0_config);
	tc_test0_config.counter_size = TC_COUNTER_SIZE_32BIT;

	tc_init(&tc_test0_module, CONF_TEST_TC0, &tc_test0_config);
	tc_enable(&tc_test0_module);

	while (tc_is_syncing(&tc_test0_module)) {
		/* Synchronize enable */
	}

	test_assert_true(test,
			tc_test0_module.hw->COUNT32.CTRLA.reg & TC_CTRLA_ENABLE,
			"Failed first enable of 32-bit TC");

	/* Reset and test if both TC modules are disabled after reset */
	tc_reset(&tc_test0_module);

	while (tc_is_syncing(&tc_test0_module)) {
		/* Synchronize reset */
	}

	test_assert_false(test,
			tc_test0_module.hw->COUNT32.CTRLA.reg & TC_CTRLA_ENABLE,
			"Failed reset of 32-bit master TC TEST0");
	test_assert_false(test,
			tc_test1_module.hw->COUNT32.CTRLA.reg & TC_CTRLA_ENABLE,
			"Failed reset of 32-bit slave TC TEST1");

	/* Change to 16-bit counter on TC0  */
	tc_test0_config.counter_size = TC_COUNTER_SIZE_16BIT;

	tc_init(&tc_test0_module, CONF_TEST_TC0, &tc_test0_config);
	tc_enable(&tc_test0_module);

	while (tc_is_syncing(&tc_test0_module)) {
		/* Synchronize enable */
	}


	tc_init(&tc_test1_module, CONF_TEST_TC1, &tc_test1_config);
	tc_enable(&tc_test1_module);

	while (tc_is_syncing(&tc_test1_module)) {
		/* Synchronize enable */
	}

	test_assert_true(test,
			tc_test0_module.hw->COUNT16.CTRLA.reg & TC_CTRLA_ENABLE,
			"Failed re-enable of TC TEST0");
	test_assert_true(test,
			tc_test1_module.hw->COUNT16.CTRLA.reg & TC_CTRLA_ENABLE,
			"Failed re-enable of TC TEST1");
}

/**
 * \internal
 * \brief Test basic functionality.
 *
 * This test tests the basic functionality for the TC. It tests the following functions:
 *  - tc_get_count_value()
 *  - tc_stop_counter()
 *  - tc_set_count_value()
 *  - tc_start_counter()
 *
 * \param test Current test case.
 */
static void run_basic_functionality_test(const struct test_case *test)
{
	test_assert_true(test,
			tc_init_success == true,
			"TC initialization failed, skipping test");

	/* Setup TC0 */
	tc_reset(&tc_test0_module);
	tc_get_config_defaults(&tc_test0_config);

	tc_init(&tc_test0_module, CONF_TEST_TC0, &tc_test0_config);
	tc_enable(&tc_test0_module);

	/* Test tc_get_count_value() */
	uint32_t test_val0 = tc_get_count_value(&tc_test0_module);

	test_assert_true(test,
			test_val0 > 0,
			"The tc_get_count_value() returned 0 expected larger value");

	/* Test tc_stop_counter() */
	tc_stop_counter(&tc_test0_module);

	uint32_t test_val1 = tc_get_count_value(&tc_test0_module);
	uint32_t test_val2 = tc_get_count_value(&tc_test0_module);

	test_assert_true(test,
			test_val1 == test_val2,
			"The counter failed to stop");

	/* Test tc_set_count_value() */
	tc_set_count_value(&tc_test0_module, 0x00FF);

	test_assert_true(test,
			tc_get_count_value(&tc_test0_module) == 0x00FF,
			"tc_set_count_value() have failed");

	/* Test tc_start_counter() */
	tc_start_counter(&tc_test0_module);

	test_assert_true(test,
			tc_get_count_value(&tc_test0_module) > 0x00FF,
			"tc_get_count_value() have failed");

	basic_functionality_test_passed = true;
}

/**
 * \internal
 * \brief Test the callback API
 *
 * This test tests the callback API for the TC. The TC uses one-shot mode.
 *
 * \param test Current test case.
 */
static void run_callback_test(const struct test_case *test)
{
	test_assert_true(test,
			tc_init_success == true,
			"TC initialization failed, skipping test");

	test_assert_true(test,
			basic_functionality_test_passed == true,
			"Basic functionality test failed, skipping test");

	/* Setup TC0 */
	tc_reset(&tc_test0_module);
	tc_get_config_defaults(&tc_test0_config);
	tc_test0_config.wave_generation                       = TC_WAVE_GENERATION_MATCH_PWM;
	tc_test0_config.counter_16_bit.compare_capture_channel\
		[TC_COMPARE_CAPTURE_CHANNEL_0]                    = 0x03FF;
	tc_test0_config.counter_16_bit.compare_capture_channel\
		[TC_COMPARE_CAPTURE_CHANNEL_1]                    = 0x03FA;


	tc_init(&tc_test0_module, CONF_TEST_TC0, &tc_test0_config);

	/* Setup callbacks */
	tc_register_callback(&tc_test0_module, tc_callback_function, TC_CALLBACK_CC_CHANNEL1);
	tc_enable_callback(&tc_test0_module, TC_CALLBACK_CC_CHANNEL1);

	tc_enable(&tc_test0_module);

	while ((tc_get_status(&tc_test0_module) & TC_STATUS_COUNT_OVERFLOW) == 0) {
		/* Wait for overflow of TC1*/
	}

	tc_disable(&tc_test0_module);
	tc_clear_status(&tc_test0_module, TC_STATUS_COUNT_OVERFLOW);

	test_assert_true(test,
			callback_function_entered == 1,
			"The callback has failed callback_function_entered = %d",
			(int)callback_function_entered);

	/* Test disable callback function */
	tc_disable_callback(&tc_test0_module, TC_CALLBACK_CC_CHANNEL1);
	tc_set_count_value(&tc_test0_module, 0x00000000);

	tc_enable(&tc_test0_module);

	while ((tc_get_status(&tc_test0_module) & TC_STATUS_COUNT_OVERFLOW) == 0) {
		/* Wait for overflow of TC1*/
	}

	/* Test tc_disable() */
	tc_disable(&tc_test0_module);

	test_assert_true(test,
			callback_function_entered == 1,
			"Disabling the callback has failed");
}

/**
 * \internal
 * \brief Test capture and compare
 *
 * This test uses TC module 0 as a PWM generator (compare function).
 * TC module 1 will be set to capture the signal from TC module 0 to test the capture
 * functionality.
 *
 * \param test Current test case.
 */
static void run_16bit_capture_and_compare_test(const struct test_case *test)
{
	test_assert_true(test,
			tc_init_success == true,
			"TC initialization failed, skipping test");

	test_assert_true(test,
			callback_function_entered == 1,
			"The callback test has failed, skipping test");

	/* Configure 16-bit TC module for PWM generation */
	tc_reset(&tc_test0_module);
	tc_get_config_defaults(&tc_test0_config);
	tc_test0_config.wave_generation  = TC_WAVE_GENERATION_MATCH_PWM;
	tc_test0_config.counter_16_bit.compare_capture_channel[TC_COMPARE_CAPTURE_CHANNEL_0]  = 0x03FF;
	tc_test0_config.counter_16_bit.compare_capture_channel[TC_COMPARE_CAPTURE_CHANNEL_1]  = 0x01FF;

	/* Calculate the theoretical PWM frequency & duty */
	uint32_t frequency_output, duty_output;
#if (SAML21) || (SAML22) || (SAMR30) || (SAMR34)
	frequency_output = system_clock_source_get_hz(SYSTEM_CLOCK_SOURCE_OSC16M)/ (0x03FF+1);
	/* This value is depend on the WaveGeneration Mode */
	duty_output = (uint32_t)(tc_test0_config.counter_16_bit.compare_capture_channel[TC_COMPARE_CAPTURE_CHANNEL_1]) * 100 \
					/ tc_test0_config.counter_16_bit.compare_capture_channel[TC_COMPARE_CAPTURE_CHANNEL_0];
#elif SAMC21
	frequency_output = system_clock_source_get_hz(SYSTEM_CLOCK_SOURCE_OSC48M)/ (0x03FF+1);
	/* This value is depend on the WaveGeneration Mode */
	duty_output = (uint32_t)(tc_test0_config.counter_16_bit.compare_capture_channel[TC_COMPARE_CAPTURE_CHANNEL_1]) * 100 \
					/ tc_test0_config.counter_16_bit.compare_capture_channel[TC_COMPARE_CAPTURE_CHANNEL_0];
#else
	frequency_output = system_clock_source_get_hz(SYSTEM_CLOCK_SOURCE_OSC8M)/ (0x03FF+1);
	/* This value is depend on the WaveGeneration Mode */
	duty_output = (uint32_t)(tc_test0_config.counter_16_bit.compare_capture_channel[TC_COMPARE_CAPTURE_CHANNEL_1]) * 100 \
					/ tc_test0_config.counter_16_bit.compare_capture_channel[TC_COMPARE_CAPTURE_CHANNEL_0];
#endif

	tc_test0_config.pwm_channel[TC_COMPARE_CAPTURE_CHANNEL_1].enabled = true;
	tc_test0_config.pwm_channel[TC_COMPARE_CAPTURE_CHANNEL_1].pin_out = CONF_TEST_PIN_OUT;
	tc_test0_config.pwm_channel[TC_COMPARE_CAPTURE_CHANNEL_1].pin_mux = CONF_TEST_PIN_MUX;
	tc_init(&tc_test0_module, CONF_TEST_TC0, &tc_test0_config);

	tc_register_callback(&tc_test0_module, tc_callback_function, TC_CALLBACK_CC_CHANNEL0);
	tc_enable_callback(&tc_test0_module, TC_CALLBACK_CC_CHANNEL0);

	/* Configure 16-bit TC module for capture */
	tc_reset(&tc_test1_module);
	tc_get_config_defaults(&tc_test1_config);
	tc_test1_config.clock_prescaler              = TC_CLOCK_PRESCALER_DIV1;
	tc_test1_config.enable_capture_on_channel[CONF_CAPTURE_CHAN_0] = true;
	tc_test1_config.enable_capture_on_channel[CONF_CAPTURE_CHAN_1] = true;

	tc_init(&tc_test1_module, CONF_TEST_TC1, &tc_test1_config);

	struct tc_events tc_events = { .on_event_perform_action = true,
								.event_action = TC_EVENT_ACTION_PPW,};

	tc_enable_events(&tc_test1_module, &tc_events);

	/* Configure external interrupt controller */
	struct extint_chan_conf extint_chan_config;
	extint_chan_config.gpio_pin            = CONF_EIC_PIN;
	extint_chan_config.gpio_pin_mux        = CONF_EIC_MUX;
	extint_chan_config.gpio_pin_pull       = EXTINT_PULL_UP;
#if (!SAML21) && (!SAML22) && (!SAMC21) && (!SAMR30) && (!SAMR34)
	extint_chan_config.wake_if_sleeping    = false;
#endif
	extint_chan_config.filter_input_signal = false;
	extint_chan_config.detection_criteria  = EXTINT_DETECT_HIGH;
#if (SAMR34)
	extint_chan_set_config(CONF_EIC_CHANNEL, &extint_chan_config);
#else
	extint_chan_set_config(0, &extint_chan_config);
#endif

	/* Configure external interrupt module to be event generator */
	struct extint_events extint_event_conf;
#if (SAMR34)
	extint_event_conf.generate_event_on_detect[CONF_EIC_CHANNEL] = true;
#else
	extint_event_conf.generate_event_on_detect[0] = true;
#endif
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

	/* Enable TC modules */
	tc_enable(&tc_test1_module);
	tc_enable(&tc_test0_module);

	uint16_t period_after_capture = 0;
	uint16_t pulse_width_after_capture = 0;
	uint32_t capture_frequency = 0;
	uint32_t capture_duty = 0;


	while (callback_function_entered < 4) {
		period_after_capture = tc_get_capture_value(&tc_test1_module,
				TC_COMPARE_CAPTURE_CHANNEL_0);
		pulse_width_after_capture = tc_get_capture_value(&tc_test1_module,
				TC_COMPARE_CAPTURE_CHANNEL_1);
	}

	if(period_after_capture != 0) {
#if (SAML21) || (SAML22) || (SAMR30) || (SAMR34)
		capture_frequency = system_clock_source_get_hz(SYSTEM_CLOCK_SOURCE_OSC16M)/ period_after_capture;
#elif SAMC21
		capture_frequency = system_clock_source_get_hz(SYSTEM_CLOCK_SOURCE_OSC48M)/ period_after_capture;
#else
		capture_frequency = system_clock_source_get_hz(SYSTEM_CLOCK_SOURCE_OSC8M)/ period_after_capture;
#endif
		capture_duty = (uint32_t)(pulse_width_after_capture) * 100 / period_after_capture;
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
 * \brief Run TC unit tests
 *
 * Initializes the system and serial output, then sets up the TC unit test
 * suite and runs it.
 */
int main(void)
{
	system_init();
	cdc_uart_init();

	/* Define Test Cases */
	DEFINE_TEST_CASE(init_test, NULL,
			run_init_test, NULL,
			"Initialize tc_xmodules");

	DEFINE_TEST_CASE(basic_functionality_test, NULL,
			run_basic_functionality_test, NULL,
			"test start stop and getters and setters");

	DEFINE_TEST_CASE(callback_test, NULL,
			run_callback_test, NULL,
			"test callback API");

	DEFINE_TEST_CASE(reset_32bit_master_test, NULL,
			run_reset_32bit_master_test, NULL,
			"Setup, reset and reinitialize TC modules of a 32-bit TC");


	DEFINE_TEST_CASE(capture_and_compare_test, NULL,
			run_16bit_capture_and_compare_test, NULL,
			"Test capture and compare");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(tc_tests) = {
		&init_test,
		&basic_functionality_test,
		&callback_test,
		&reset_32bit_master_test,
		&capture_and_compare_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(tc_suite, tc_tests,
			"SAM TC driver test suite");

	/* Run all tests in the suite*/
	test_suite_run(&tc_suite);

	tc_reset(&tc_test0_module);
	tc_reset(&tc_test1_module);

	while (true) {
		/* Intentionally left empty */
	}
}

