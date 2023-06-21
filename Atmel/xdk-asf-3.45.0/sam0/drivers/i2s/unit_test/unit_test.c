/**
 * \file
 *
 * \brief SAM I2S Unit test
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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
 * \mainpage SAM I2S Unit Test
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This unit test carries out tests for the I<SUP>2</SUP>S driver.
 * It consists of test cases for the following functionalities:
 *  - Test for polled mode transmit/receive of I<SUP>2</SUP>S.
 *  - Test for callback mode transmit/receive of I<SUP>2</SUP>S.
 */

/**
 * \page appdoc_main SAM I2S Unit Test
 *
 * Overview:
 * - \ref appdoc_sam0_i2s_unit_test_intro
 * - \ref appdoc_sam0_i2s_unit_test_setup
 * - \ref appdoc_sam0_i2s_unit_test_usage
 * - \ref appdoc_sam0_i2s_unit_test_compinfo
 * - \ref appdoc_sam0_i2s_unit_test_contactinfo
 *
 * \section appdoc_sam0_i2s_unit_test_intro Introduction
 * \copydetails appdoc_preface
 *
 * Tests will be performed for data transmitting and receiving of I<SUP>2</SUP>S.
 *
 * The following kit is required for carrying out the test:
 *  - SAM D21 Xplained Pro board
 *  - SAM DA1 Xplained Pro board
 *
 * \section appdoc_sam0_i2s_unit_test_setup Setup
 * The following connections has to be made using wires:
 *  - SAM D21/DA1 Xplained Pro
 *    - EXT2 \b Pin 3 (PA10, SCK0) <-----> EXT3 \b Pin 13 (PB11, SCK1)
 *    - EXT2 \b Pin 4 (PA11, FS0)  <-----> \b Pin 7 (PB12, FS1)
 *
 * To run the test:
 *  - Connect the board to the computer using a micro USB cable.
 *  - Open the virtual COM port in a terminal application.
 *    \note The USB composite firmware running on the Embedded Debugger (EDBG)
 *          will enumerate as debugger, virtual COM port and EDBG data
 *          gateway.
 *  - Build the project, program the target and run the application.
 *    The terminal shows the results of the unit test.
 *
 * \section appdoc_sam0_i2s_unit_test_usage Usage
 *  - The unit test configures Clock Unit 0 to generate SCK and FS and
 *    Clock Unit 1 to use the signals.
 *  - The unit test configures Serializer 0 to transmit data and Serializer 1
 *    to receive data, over control signals received by Clock Unit 1.
 *  - The test is again and with callback disabled.
 *
 * \section appdoc_sam0_i2s_unit_test_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_i2s_unit_test_contactinfo Contact Information
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

/* Test buffer size (number of samples) */
#define TEST_SIZE      4

/* Test TX data */
uint16_t test_tx_data[TEST_SIZE] = {11, 60, 0xF860, 0x9001};

/* Test RX buffer */
uint16_t test_rx_data[TEST_SIZE] = {0, 0, 0, 0};

/* Structure for UART module connected to EDBG (used for unit test output) */
struct usart_module cdc_uart_module;

/* Structure instance for I<SUP>2</SUP>S module */
struct i2s_module i2s_instance;

/* Flags for TX/RX */
volatile uint32_t test_tx_done = false, test_rx_done = false;

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
 * \internal
 * \brief I<SUP>2</SUP>S data TX callback
 */
static void i2s_callback_tx(struct i2s_module *const module_inst)
{
	test_tx_done = true;
}

/**
 * \internal
 * \brief I<SUP>2</SUP>S data RX callback
 */
static void i2s_callback_rx(struct i2s_module *const module_inst)
{
	test_rx_done = true;
}

/**
 * \brief Initialize the I<SUP>2</SUP>S module Clock Unit and Serializer
 *
 * Reset I<SUP>2</SUP>S module.
 * Initialize Clock Unit 0 and Serializer 0 for TX.
 * Initialize Serializer 1 for RX.
 * Data format is I<SUP>2</SUP>S compatible 16 bit stream.
 */
static void setup_i2s(void)
{
	i2s_reset(&i2s_instance);

	struct i2s_clock_unit_config config_clock_unit;
	struct i2s_serializer_config config_serializer;

	// Clock Unit 0 is controller to generate FS and SCK
	// Configure SCK and FS generation
	i2s_clock_unit_get_config_defaults(&config_clock_unit);
	config_clock_unit.clock.gclk_src = GCLK_GENERATOR_1;
	config_clock_unit.clock.sck_src = I2S_SERIAL_CLOCK_SOURCE_MCKDIV;
	config_clock_unit.clock.sck_div = 32;
	config_clock_unit.frame.number_slots = 2;
	config_clock_unit.frame.slot_size = I2S_SLOT_SIZE_32_BIT;
	config_clock_unit.frame.data_delay = I2S_DATA_DELAY_I2S;
	config_clock_unit.frame.frame_sync.source = I2S_FRAME_SYNC_SOURCE_SCKDIV;
	config_clock_unit.frame.frame_sync.width = I2S_FRAME_SYNC_WIDTH_HALF_FRAME;
#if CONF_TEST_CTRL_RX
	config_clock_unit.sck_pin.enable = true;
	config_clock_unit.sck_pin.gpio = CONF_TEST_SCK_TX_PIN;
	config_clock_unit.sck_pin.mux = CONF_TEST_SCK_TX_MUX;
	config_clock_unit.fs_pin.enable = true;
	config_clock_unit.fs_pin.gpio = CONF_TEST_FS_TX_PIN;
	config_clock_unit.fs_pin.mux = CONF_TEST_FS_TX_MUX;
#endif
	i2s_clock_unit_set_config(&i2s_instance, I2S_CLOCK_UNIT_0,
			&config_clock_unit);

#if CONF_TEST_CTRL_RX
	// Clock Unit 1 uses the generated FS and SCK
	// Configure SCK and FS Receive
	i2s_clock_unit_get_config_defaults(&config_clock_unit);
	config_clock_unit.clock.sck_src = I2S_SERIAL_CLOCK_SOURCE_SCKPIN;
	config_clock_unit.frame.number_slots = 2;
	config_clock_unit.frame.slot_size = I2S_SLOT_SIZE_32_BIT;
	config_clock_unit.frame.data_delay = I2S_DATA_DELAY_I2S;
	config_clock_unit.frame.frame_sync.source = I2S_FRAME_SYNC_SOURCE_FSPIN;
	config_clock_unit.sck_pin.enable = true;
	config_clock_unit.sck_pin.gpio = CONF_TEST_SCK_RX_PIN;
	config_clock_unit.sck_pin.mux = CONF_TEST_SCK_RX_MUX;
	config_clock_unit.fs_pin.enable = true;
	config_clock_unit.fs_pin.gpio = CONF_TEST_FS_RX_PIN;
	config_clock_unit.fs_pin.mux = CONF_TEST_FS_RX_MUX;
	i2s_clock_unit_set_config(&i2s_instance, I2S_CLOCK_UNIT_1,
			&config_clock_unit);
#else
	// Both Serializers will uses Clock Unit 0
#endif

	// Configure data TX
	i2s_serializer_get_config_defaults(&config_serializer);
#if !CONF_TEST_CTRL_RX
	// TX/RX using clock unit 0
	config_serializer.clock_unit = I2S_CLOCK_UNIT_0;
#else
	// TX/RX using clock unit 1
	config_serializer.clock_unit = I2S_CLOCK_UNIT_1;
#endif
	config_serializer.mode = I2S_SERIALIZER_TRANSMIT;
	config_serializer.data_size = I2S_DATA_SIZE_16BIT;
	// Data pin loops back internally
	i2s_serializer_set_config(&i2s_instance, I2S_SERIALIZER_0,
			&config_serializer);

	// Configure data RX
	config_serializer.loop_back = true;
	config_serializer.mode = I2S_SERIALIZER_RECEIVE;
	i2s_serializer_set_config(&i2s_instance, I2S_SERIALIZER_1,
			&config_serializer);

	// Enable
	i2s_enable(&i2s_instance);

	i2s_clock_unit_enable(&i2s_instance, I2S_CLOCK_UNIT_0);
#if CONF_TEST_CTRL_RX
	i2s_clock_unit_enable(&i2s_instance, I2S_CLOCK_UNIT_1);
#endif

	i2s_serializer_enable(&i2s_instance, I2S_SERIALIZER_0);
	i2s_serializer_enable(&i2s_instance, I2S_SERIALIZER_1);
}

/**
 * \internal
 * \brief Setup function for polled mode test.
 *
 * This function sets up the I<SUP>2</SUP>S module.
 *
 * \param test Current test case.
 */
static void setup_i2s_polled_mode_test(const struct test_case *test)
{
	setup_i2s();
}

/**
 * \internal
 * \brief Cleanup function for polled mode test.
 *
 * This function disables the I<SUP>2</SUP>S module.
 *
 * \param test Current test case.
 */
static void cleanup_i2s_polled_mode_test(const struct test_case *test)
{
	i2s_disable(&i2s_instance);
}

/**
 * \internal
 * \brief Test for I<SUP>2</SUP>S TX/RX by polling.
 *
 * Send several words by polling and receive them.
 * \note In polling mode, the first received word may not be the first one sent
 *       due to timing delay, so test words list are sent twice, to confirm that
 *       all words are received.
 *
 * \param test Current test case.
 */
static void run_i2s_polled_mode_test(const struct test_case *test)
{
	uint32_t i, j;

	memset(test_rx_data, 0, sizeof(test_rx_data));
	for (i = 0; i < TEST_SIZE * 2; i ++) {
		i2s_serializer_write_wait(&i2s_instance, I2S_SERIALIZER_0,
				test_tx_data[i % TEST_SIZE]);
		test_rx_data[i % TEST_SIZE] =
				i2s_serializer_read_wait(&i2s_instance, I2S_SERIALIZER_1);
	}

	/* Find actual capture start */
	for (i = 0; i < TEST_SIZE; i ++) {
		if (test_tx_data[0] == test_rx_data[i]) {
			break;
		}
	}
	test_assert_true(test, i < TEST_SIZE,
			"RX fail, data stream not found");
	for (j = 0; j < TEST_SIZE; j ++, i = (i + 1) % TEST_SIZE) {
		test_assert_true(test, test_rx_data[i] == test_tx_data[j],
				"TX/RX data mismatch %d <> %d",
				test_tx_data[j], test_rx_data[i]);
	}
}

/**
 * \internal
 * \brief Setup function for callback mode test.
 *
 * This function sets up the I<SUP>2</SUP>S & the callback function.
 *
 * \param test Current test case.
 */
static void setup_i2s_callback_mode_test(const struct test_case *test)
{
	setup_i2s();

	i2s_serializer_register_callback(&i2s_instance, I2S_SERIALIZER_0,
			i2s_callback_tx, I2S_SERIALIZER_CALLBACK_BUFFER_DONE);
	i2s_serializer_enable_callback(&i2s_instance, I2S_SERIALIZER_0,
			I2S_SERIALIZER_CALLBACK_BUFFER_DONE);
	i2s_serializer_register_callback(&i2s_instance, I2S_SERIALIZER_1,
			i2s_callback_rx, I2S_SERIALIZER_CALLBACK_BUFFER_DONE);
	i2s_serializer_enable_callback(&i2s_instance, I2S_SERIALIZER_1,
			I2S_SERIALIZER_CALLBACK_BUFFER_DONE);
}

/**
 * \internal
 * \brief Cleanup function for callback mode test.
 *
 * This function disables the callback & I<SUP>2</SUP>S module.
 *
 * \param test Current test case.
 */
static void cleanup_i2s_callback_mode_test(const struct test_case *test)
{
	i2s_serializer_disable_callback(&i2s_instance, I2S_SERIALIZER_0,
			I2S_SERIALIZER_CALLBACK_BUFFER_DONE);
	i2s_serializer_unregister_callback(&i2s_instance, I2S_SERIALIZER_0,
			I2S_SERIALIZER_CALLBACK_BUFFER_DONE);
	i2s_serializer_disable_callback(&i2s_instance, I2S_SERIALIZER_1,
			I2S_SERIALIZER_CALLBACK_BUFFER_DONE);
	i2s_serializer_unregister_callback(&i2s_instance, I2S_SERIALIZER_1,
			I2S_SERIALIZER_CALLBACK_BUFFER_DONE);
	i2s_disable(&i2s_instance);
}

/**
 * \internal
 * \brief Test for I<SUP>2</SUP>S TX/RX using callback.
 *
 * \param test Current test case.
 */
static void run_i2s_callback_mode_test(const struct test_case *test)
{
	uint32_t i;

	memset(test_rx_data, 0, sizeof(test_rx_data));
	test_rx_done = false;
	i2s_serializer_read_buffer_job(&i2s_instance, I2S_SERIALIZER_1,
			test_rx_data, TEST_SIZE);
	i2s_serializer_write_buffer_job(&i2s_instance, I2S_SERIALIZER_0,
			test_tx_data, TEST_SIZE);

	while(!test_rx_done) {
		/* Wait transfer done */
	}

	test_assert_true(test, test_tx_done, "TX done callback does not occur");

	for (i = 0; i < TEST_SIZE; i ++) {
		test_assert_true(test, test_rx_data[i] == test_tx_data[i],
		"TX/RX data mismatch %d <> %d",
		test_tx_data[i], test_rx_data[i]);
	}
}

/**
 * \brief Run I<SUP>2</SUP>S unit tests
 *
 * Initializes the system and serial output, then sets up the
 * I<SUP>2</SUP>S unit test suite and runs it.
 */
int main(void)
{
	system_init();
	cdc_uart_init();

	/* Initialize module instance */
	i2s_init(&i2s_instance, CONF_TEST_I2S);

	/* Define Test Cases */
	DEFINE_TEST_CASE(i2s_polled_mode_test,
			setup_i2s_polled_mode_test,
			run_i2s_polled_mode_test,
			cleanup_i2s_polled_mode_test,
			"Testing I2S TX/RX by polling");

	DEFINE_TEST_CASE(i2s_callback_mode_test,
			setup_i2s_callback_mode_test,
			run_i2s_callback_mode_test,
			cleanup_i2s_callback_mode_test,
			"Testing I2S TX/RX using callback");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(i2s_tests) = {
		&i2s_callback_mode_test,
		&i2s_polled_mode_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(i2s_test_suite, i2s_tests,
			"SAM I2S driver test suite");

	/* Run all tests in the suite*/
	test_suite_run(&i2s_test_suite);

	while (true) {
		/* Intentionally left empty */
	}
}
