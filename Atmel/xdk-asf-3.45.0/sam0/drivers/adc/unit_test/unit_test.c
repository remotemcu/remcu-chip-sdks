/**
 * \file
 *
 * \brief SAM Analog to Digital Converter (ADC) Unit test
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
 * \mainpage SAM ADC Unit Test
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This unit test carries out tests for the ADC driver.
 * It consists of test cases for the following functionalities:
 *      - Test for ADC initialization.
 *      - Test for ADC polled mode conversion.
 *      - Test for ADC callback mode conversion.
 *      - Test for ADC averaging mode.
 *      - Test for ADC window mode.
 */

/**
 * \page appdoc_main SAM ADC Unit Test
 *
 * Overview:
 * - \ref asfdoc_sam0_adc_unit_test_intro
 * - \ref asfdoc_sam0_adc_unit_test_setup
 * - \ref asfdoc_sam0_adc_unit_test_usage
 * - \ref asfdoc_sam0_adc_unit_test_compinfo
 * - \ref asfdoc_sam0_adc_unit_test_contactinfo
 *
 * \section asfdoc_sam0_adc_unit_test_intro Introduction
 * \copydetails appdoc_preface
 *
 * Input to the ADC is provided with the DAC module.
 *
 * The following kit is required for carrying out the test:
 *  - SAM D20 Xplained Pro board
 *  - SAM D21 Xplained Pro board
 *  - SAM L21 Xplained Pro board
 *  - SAM DA1 Xplained Pro board
 *  - SAM C21 Xplained Pro board
 *
 * \section asfdoc_sam0_adc_unit_test_setup Setup
 * The following connections has to be made using wires:
 * - SAM D21/L21/C21/D20 Xplained Pro
 *  - \b DAC VOUT (PA02) <-----> ADC4 (PA04)
 *
 * To run the test:
 *  - Connect the supported Xplained Pro board to the computer using a
 *    micro USB cable.
 *  - Open the virtual COM port in a terminal application.
 *    \note The USB composite firmware running on the Embedded Debugger (EDBG)
 *          will enumerate as debugger, virtual COM port and EDBG data
 *          gateway.
 *  - Build the project, program the target and run the application.
 *    The terminal shows the results of the unit test.
 *
 * \section asfdoc_sam0_adc_unit_test_usage Usage
 *  - The unit test configures DAC module to provide voltage to the ADC input.
 *  - DAC output is adjusted to generate various voltages which are measured by
 *    the ADC.
 *  - Different modes of the ADC are tested.
 *
 * \section asfdoc_sam0_adc_unit_test_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section asfdoc_sam0_adc_unit_test_contactinfo Contact Information
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

/* Number of ADC samples used in the test */
#define ADC_SAMPLES 128
/* Theoretical ADC result for DAC half-swing output */
#define ADC_VAL_DAC_HALF_OUTPUT 2047
/* Theoretical ADC result for DAC full-swing output */
#define ADC_VAL_DAC_FULL_OUTPUT 4095
/* Offset due to ADC & DAC errors */
#define ADC_OFFSET              150
#if (SAML21)
#  define DAC_VAL_HALF_VOLT     2047
#  define DAC_VAL_ONE_VOLT      4095
#else
/* Theoretical DAC value for 0.5V output*/
#  define DAC_VAL_HALF_VOLT     512
/* Theoretical DAC value for 1.0V output*/
#  define DAC_VAL_ONE_VOLT      1023
#endif

/* Structure for UART module connected to EDBG (used for unit test output) */
struct usart_module cdc_uart_module;
/* Structure for ADC module */
struct adc_module adc_inst;
/* Structure for DAC module */
struct dac_module dac_inst;
/* ADC result buffer to store the sample values */
uint16_t adc_buf[ADC_SAMPLES];

/* Interrupt flag used during callback test */
volatile bool interrupt_flag = false;
/* Flag to check successful initialization */
volatile bool adc_init_success = false;

/**
 * \internal
 * \brief ADC callback function
 *
 * Called by ADC driver on interrupt detection.
 *
 * \param module Pointer to the ADC module (not used)
 */
static void adc_user_callback(struct adc_module *const module)
{
	interrupt_flag = true;
}

/**
 * \brief Initialize the USART for unit test
 *
 * Initializes the SERCOM USART (SERCOM4) used for sending the
 * unit test status to the computer via the EDBG CDC gateway.
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
 * \brief Initialize the DAC for unit test
 *
 * Initializes the DAC module used for sending the analog values
 * to the ADC during test.
 */
static void test_dac_init(void)
{
	/* Structures for DAC configuration */
	struct dac_config config;
	struct dac_chan_config chan_config;

	/* Configure the DAC module */
	dac_get_config_defaults(&config);
#if (SAML21)
	config.reference    = DAC_REFERENCE_INTREF;
#else
	config.reference    = DAC_REFERENCE_INT1V;
#endif
	config.clock_source = GCLK_GENERATOR_3;
	dac_init(&dac_inst, DAC, &config);

	/* Configure the DAC channel */
	dac_chan_get_config_defaults(&chan_config);
	dac_chan_set_config(&dac_inst, DAC_CHANNEL_0, &chan_config);
	dac_chan_enable(&dac_inst, DAC_CHANNEL_0);

	dac_enable(&dac_inst);
}

/**
 * \internal
 * \brief Test for ADC initialization.
 *
 * This test initializes the ADC module and checks whether the
 * initialization is successful or not.
 *
 * If this test fails no other tests will run.
 *
 * \param test Current test case.
 */
static void run_adc_init_test(const struct test_case *test)
{
	enum status_code status = STATUS_ERR_IO;

	/* Structure for ADC configuration */
	struct adc_config config;
	adc_get_config_defaults(&config);
	config.positive_input = CONF_ADC_POSITIVE_INPUT;
	config.negative_input = CONF_ADC_NEGATIVE_INPUT;
#if (SAML21) || (SAMC21)
	config.reference      = ADC_REFERENCE_INTREF;
#else
	config.reference      = ADC_REFERENCE_INT1V;
#endif
	config.clock_source   = GCLK_GENERATOR_3;
#if !(SAML21) && !(SAMC21)
	config.gain_factor    = ADC_GAIN_FACTOR_1X;
#endif

	/* Initialize the ADC */
#if (SAMC21)
	status = adc_init(&adc_inst, ADC0, &config);
#else
	status = adc_init(&adc_inst, ADC, &config);
#endif

	/* Check for successful initialization */
	test_assert_true(test, status == STATUS_OK,
			"ADC initialization failed");

	/* Enable the ADC */
	status = adc_enable(&adc_inst);

	/* Check for successful enable */
	test_assert_true(test, status == STATUS_OK,
			"ADC enabling failed");

	if (status == STATUS_OK) {
		adc_init_success = true;
	}
}

/**
 * \internal
 * \brief Test for ADC conversion in polled mode.
 *
 * This test checks the polled mode functionality of the ADC.
 * 0.5V and 1V inputs are applied to the ADC via DAC and the ADC
 * outputs are verified for expected results.
 *
 * \param test Current test case.
 */
static void run_adc_polled_mode_test(const struct test_case *test)
{
	uint16_t adc_result = 0;

	/* Skip test if ADC initialization failed */
	test_assert_true(test, adc_init_success,
			"Skipping test due to failed initialization");

	/* Set 0.5V on DAC output */
	dac_chan_write(&dac_inst, DAC_CHANNEL_0, DAC_VAL_HALF_VOLT);
	delay_ms(1);

	/* Start an ADC conversion */
	adc_start_conversion(&adc_inst);
	while (adc_read(&adc_inst, &adc_result) != STATUS_OK) {
	}

	/* Test result */
	test_assert_true(test,
			(adc_result > (ADC_VAL_DAC_HALF_OUTPUT - ADC_OFFSET)) &&
			(adc_result < (ADC_VAL_DAC_HALF_OUTPUT + ADC_OFFSET)),
			"Error in ADC conversion at 0.5V input (Expected: ~%d, Result: %d)", ADC_VAL_DAC_HALF_OUTPUT, adc_result);

	/* Errata 14094 for SAMC21
	   Once set, the ADC.SWTRIG.START will not be cleared until the Microcontroller is reset.
	   Border effect: FLUSH function always start a new conversion, once START = 1. */
#if !(SAMC21)
	adc_flush(&adc_inst);
#endif

	/* Set 1V on DAC output */
	dac_chan_write(&dac_inst, DAC_CHANNEL_0, DAC_VAL_ONE_VOLT);
	delay_ms(1);

	/* Start an ADC conversion */
	adc_start_conversion(&adc_inst);
	while (adc_read(&adc_inst, &adc_result) != STATUS_OK) {
	}

	/* Test result */
	test_assert_true(test,
			adc_result > (ADC_VAL_DAC_FULL_OUTPUT - ADC_OFFSET),
			"Error in ADC conversion at 1V input (Expected: ~%d, Result: %d)", ADC_VAL_DAC_FULL_OUTPUT, adc_result);

	uint16_t adc_prev_result = 0;

	/* Ensure ADC gives linearly increasing conversions for linearly increasing inputs */
	for (uint16_t i = 0; i < DAC_VAL_ONE_VOLT; i++) {
	/* Errata 14094 for SAMC21 */
#if !(SAMC21)
		adc_flush(&adc_inst);
#endif
		/* Write the next highest DAC output voltage */
		dac_chan_write(&dac_inst, DAC_CHANNEL_0, i);
		delay_ms(1);

		/* Start an ADC conversion */
		adc_start_conversion(&adc_inst);
		while (adc_read(&adc_inst, &adc_result) != STATUS_OK) {
		}

		/* Test result */
		test_assert_true(test,
				(adc_result + ADC_OFFSET) >= adc_prev_result,
				"Error in ADC conversion at a variable input (Expected: >=%d, Result: %d)", adc_prev_result, adc_result);

		adc_prev_result = adc_result;
	}
}

/**
 * \internal
 * \brief Setup Function: ADC callback mode test.
 *
 * This function initializes the ADC result buffer and
 * registers & enables callback for the ADC buffer read.
 *
 * \param test Current test case.
 */
static void setup_adc_callback_mode_test(const struct test_case *test)
{
	interrupt_flag = false;

	/* Skip test if ADC initialization failed */
	test_assert_true(test, adc_init_success,
			"Skipping test due to failed initialization");

	/* Initialize ADC buffer */
	for (uint8_t i = 0; i < ADC_SAMPLES; i++) {
		adc_buf[i] = 0;
	}

	/* Register and enable buffer read callback */
	adc_register_callback(&adc_inst, adc_user_callback,
			ADC_CALLBACK_READ_BUFFER);
	adc_enable_callback(&adc_inst, ADC_CALLBACK_READ_BUFFER);
}

/**
 * \internal
 * \brief ADC callback mode test function
 *
 * This test checks the callback functionality of the ADC driver.
 * ADC callback for buffered conversion is enabled.
 * Converted results are verified for expected results.
 *
 * \param test Current test case.
 */
static void run_adc_callback_mode_test(const struct test_case *test)
{
	uint16_t timeout_cycles = 0xFFFF;

	/* Set 0.5V DAC output */
	dac_chan_write(&dac_inst, DAC_CHANNEL_0, DAC_VAL_HALF_VOLT);
	delay_ms(1);
	/* Start ADC read */
	adc_read_buffer_job(&adc_inst, adc_buf, ADC_SAMPLES);

	do {
		timeout_cycles--;
		if (interrupt_flag) {
			break;
		}
	} while (timeout_cycles > 0);

	/* Test for timeout */
	test_assert_true(test, timeout_cycles > 0,
			"Timeout in ADC read");

	/* Test result */
	for (uint8_t i = 0; i < ADC_SAMPLES; i++) {
		test_assert_true(test,
				(adc_buf[i] > (ADC_VAL_DAC_HALF_OUTPUT - ADC_OFFSET)) &&
				(adc_buf[i] < (ADC_VAL_DAC_HALF_OUTPUT + ADC_OFFSET)),
				"Error in ADC conversion for 0.5V at index %d, Result: %d", i, adc_buf[i]);
	}
}

/**
 * \internal
 * \brief Cleanup Function: ADC callback mode test.
 *
 * This function clears the ADC result buffer and
 * unregisters & disables callback for the ADC buffer read.
 *
 * \param test Current test case.
 */
static void cleanup_adc_callback_mode_test(const struct test_case *test)
{
	/* Clear ADC buffer */
	for (uint8_t i = 0; i < ADC_SAMPLES; i++) {
		adc_buf[i] = 0;
	}

	/* Unregister & disable ADC read buffer callback */
	adc_unregister_callback(&adc_inst, ADC_CALLBACK_READ_BUFFER);
	adc_disable_callback(&adc_inst, ADC_CALLBACK_READ_BUFFER);
}

/**
 * \internal
 * \brief Setup Function: ADC average mode test.
 *
 * This function initializes the ADC in averaging mode.
 *
 * \param test Current test case.
 */
static void setup_adc_average_mode_test(const struct test_case *test)
{
	enum status_code status = STATUS_ERR_IO;

	/* Skip test if ADC initialization failed */
	test_assert_true(test, adc_init_success,
			"Skipping test due to failed initialization");

	/* Disable ADC before initialization */
	adc_disable(&adc_inst);
	struct adc_config config;
	adc_get_config_defaults(&config);
	config.positive_input     = CONF_ADC_POSITIVE_INPUT;
	config.negative_input     = CONF_ADC_NEGATIVE_INPUT;
#if (SAML21) || (SAMC21)
	config.reference          = ADC_REFERENCE_INTREF;
#else
	config.reference          = ADC_REFERENCE_INT1V;
#endif
	config.clock_source       = GCLK_GENERATOR_3;
#if !(SAML21) && !(SAMC21)
	config.gain_factor        = ADC_GAIN_FACTOR_1X;
#endif

	/* Re-initialize & enable ADC */
#if (SAMC21)
	status = adc_init(&adc_inst, ADC0, &config);
#else
	status = adc_init(&adc_inst, ADC, &config);
#endif
	test_assert_true(test, status == STATUS_OK,
			"ADC initialization failed");
	status = adc_enable(&adc_inst);
	test_assert_true(test, status == STATUS_OK,
			"ADC enabling failed");
}

/**
 * \internal
 * \brief ADC average mode test function
 *
 * This test performs the ADC averaging by starting a conversion.
 * 0.5V is applied as input from DAC.
 * Converted result is verified for expected results.
 *
 * \param test Current test case.
 */
static void run_adc_average_mode_test(const struct test_case *test)
{
	uint16_t adc_result = 0;

	/* Set 0.5V DAC output */
	dac_chan_write(&dac_inst, DAC_CHANNEL_0, DAC_VAL_HALF_VOLT);
	delay_ms(1);

	/* Start an ADC conversion */
	adc_start_conversion(&adc_inst);
	while (adc_read(&adc_inst, &adc_result) != STATUS_OK) {
	}

	/* Test result */
	test_assert_true(test,
			(adc_result > (ADC_VAL_DAC_HALF_OUTPUT - ADC_OFFSET)) &&
			(adc_result < (ADC_VAL_DAC_HALF_OUTPUT + ADC_OFFSET)),
			"Error in ADC average mode conversion at 0.5V input");
}

/**
 * \internal
 * \brief Setup Function: ADC window mode test.
 *
 * This function initializes the ADC in window mode.
 * Upper and lower threshold values are provided.
 * It also registers & enables callback for window detection.
 *
 * \param test Current test case.
 */
static void setup_adc_window_mode_test(const struct test_case *test)
{
	enum status_code status = STATUS_ERR_IO;

	interrupt_flag = false;

	/* Set 0.5V DAC output */
	dac_chan_write(&dac_inst, DAC_CHANNEL_0, DAC_VAL_HALF_VOLT);
	delay_ms(1);

	/* Skip test if ADC initialization failed */
	test_assert_true(test, adc_init_success,
			"Skipping test due to failed initialization");

	/* Disable ADC before initialization */
	adc_disable(&adc_inst);
	struct adc_config config;
	adc_get_config_defaults(&config);
	config.positive_input = CONF_ADC_POSITIVE_INPUT;
	config.negative_input = CONF_ADC_NEGATIVE_INPUT;
#if (SAML21) || (SAMC21)
	config.reference      = ADC_REFERENCE_INTREF;
	config.clock_prescaler = ADC_CLOCK_PRESCALER_DIV16;
#else
	config.reference      = ADC_REFERENCE_INT1V;
#endif
	config.clock_source   = GCLK_GENERATOR_3;
#if !(SAML21) && !(SAMC21)
	config.gain_factor    = ADC_GAIN_FACTOR_1X;
#endif
	config.resolution     = ADC_RESOLUTION_12BIT;
	config.freerunning    = true;
	config.window.window_mode = ADC_WINDOW_MODE_BETWEEN_INVERTED;
	config.window.window_lower_value = (ADC_VAL_DAC_HALF_OUTPUT - ADC_OFFSET);
	config.window.window_upper_value = (ADC_VAL_DAC_HALF_OUTPUT + ADC_OFFSET);

	/* Re-initialize & enable ADC */
#if (SAMC21)
	status = adc_init(&adc_inst, ADC0, &config);
#else
	status = adc_init(&adc_inst, ADC, &config);
#endif
	test_assert_true(test, status == STATUS_OK,
			"ADC initialization failed");
	status = adc_enable(&adc_inst);
	test_assert_true(test, status == STATUS_OK,
			"ADC enabling failed");

	/* Register and enable window mode callback */
	adc_register_callback(&adc_inst, adc_user_callback,
			ADC_CALLBACK_WINDOW);
	adc_enable_callback(&adc_inst, ADC_CALLBACK_WINDOW);

	/* Start ADC conversion */
	adc_start_conversion(&adc_inst);
}

/**
 * \internal
 * \brief ADC window mode test function
 *
 * This test gives an input voltage outside the window and checks
 * whether the callback is triggered or not.
 *
 * \param test Current test case.
 */
static void run_adc_window_mode_test(const struct test_case *test)
{
	uint16_t timeout_cycles = 0xFFFF;

	/* Set 1V DAC output */
	dac_chan_write(&dac_inst, DAC_CHANNEL_0, DAC_VAL_ONE_VOLT);
	delay_ms(1);

	do {
		timeout_cycles--;
		if (interrupt_flag) {
			break;
		}
	} while (timeout_cycles > 0);
	test_assert_true(test, timeout_cycles > 0,
			"Timeout in window detection");
}

/**
 * \internal
 * \brief Cleanup Function: ADC window mode test.
 *
 * This function unregisters & disables callback for window detection.
 *
 * \param test Current test case.
 */
static void cleanup_adc_window_mode_test(const struct test_case *test)
{
	/* Unregister and disable window mode callback */
	adc_disable_callback(&adc_inst, ADC_CALLBACK_WINDOW);
	adc_unregister_callback(&adc_inst, ADC_CALLBACK_WINDOW);
}

/**
 * \brief Run ADC unit tests
 *
 * Initializes the system and serial output, then sets up the
 * ADC unit test suite and runs it.
 */
int main(void)
{
	system_init();
	delay_init();
	cdc_uart_init();
	test_dac_init();

	/* Define Test Cases */
	DEFINE_TEST_CASE(adc_init_test,
			NULL,
			run_adc_init_test,
			NULL,
			"Testing ADC Initialization");

	DEFINE_TEST_CASE(adc_polled_mode_test,
			NULL,
			run_adc_polled_mode_test,
			NULL,
			"Testing ADC single ended mode by polling");

	DEFINE_TEST_CASE(adc_callback_mode_test,
			setup_adc_callback_mode_test,
			run_adc_callback_mode_test,
			cleanup_adc_callback_mode_test,
			"Testing ADC single ended mode by interrupt");

	DEFINE_TEST_CASE(adc_average_mode_test,
			setup_adc_average_mode_test,
			run_adc_average_mode_test,
			NULL,
			"Testing ADC average mode");

	DEFINE_TEST_CASE(adc_window_mode_test,
			setup_adc_window_mode_test,
			run_adc_window_mode_test,
			cleanup_adc_window_mode_test,
			"Testing ADC window mode");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(adc_tests) = {
		&adc_init_test,
		&adc_polled_mode_test,
		&adc_callback_mode_test,
		&adc_average_mode_test,
		&adc_window_mode_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(adc_test_suite, adc_tests,
			"SAM ADC driver test suite");

	/* Run all tests in the suite*/
	test_suite_run(&adc_test_suite);

	while (true) {
		/* Intentionally left empty */
	}
}
