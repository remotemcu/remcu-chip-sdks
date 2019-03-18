/**
 * \file
 *
 * \brief SAM SERCOM I2C Unit test
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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
 * \mainpage SAM I2C Unit Test
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This unit test carries out tests for the I2C driver.
 * It consists of test cases for the following functionalities:
 *      - Test for I2C initialization.
 *      - Test for I2C master transfer.
 *      - Test for I2C master full speed transfer.
 */

/**
 * \page appdoc_main SAM0 I2C Unit Test
 *
 * Overview:
 * - \ref asfdoc_sam0_i2c_unit_test_intro
 * - \ref asfdoc_sam0_i2c_unit_test_setup
 * - \ref asfdoc_sam0_i2c_unit_test_usage
 * - \ref asfdoc_sam0_i2c_unit_test_compinfo
 * - \ref asfdoc_sam0_i2c_unit_test_contactinfo
 *
 * \section asfdoc_sam0_i2c_unit_test_intro Introduction
 * \copydetails appdoc_preface
 *
 * The following kit is required for carrying out the test:
 *  - SAM D21 Xplained Pro board
 *  - SAM L21 Xplained Pro board
 *  - SAM L22 Xplained Pro board
 *  - SAM R21 Xplained Pro board
 *  - SAM DA1 Xplained Pro board
 *  - SAM C21 Xplained Pro board
 *  - SAM D20 Xplained Pro board
 *  - SAM R30 Xplained Pro board
 *  - SAM R34 Xplained Pro board
 *
 * \section asfdoc_sam0_i2c_unit_test_setup Setup
 * The following connections has to be made using wires:
 * - SAM D21/DA1/D20 Xplained Pro board
 *  - \b PB02 (EXT1 PIN7) <-----> PA08 (EXT2 PIN11) 
 *  - \b PB03 (EXT1 PIN8) <-----> PA09 (EXT2 PIN12)
 * - SAM L21 Xplained Pro board
 *  - \b PA12 (EXT1 PIN7) <-----> PA08 (EXT2 PIN11) 
 *  - \b PA13 (EXT1 PIN8) <-----> PA09 (EXT2 PIN12)
 * - SAM L22 Xplained Pro board
 *  - \b PB30 (EXT1 PIN11) <-----> PA12 (EXT2 PIN14) 
 *  - \b PB31 (EXT1 PIN12) <-----> PA13 (EXT2 PIN13)
 * - SAM R21 Xplained Pro board
 *  - \b PA16 (EXT1 PIN11) <-----> PB02 (EXT1 PIN17) 
 *  - \b PA17 (EXT1 PIN12) <-----> PB03 (EXT1 PIN15)
 * - SAM C21 Xplained Pro board
 *  - \b PA12 (EXT2 PIN11) <-----> PB30 (EXT2 PIN7) 
 *  - \b PA13 (EXT2 PIN12) <-----> PB31 (EXT2 PIN8)
 * - SAM R30 Xplained Pro board
 *  - \b PA22 (EXT1 PIN9) <-----> PA16 (EXT1 PIN11)
 *  - \b PA23 (EXT1 PIN10) <-----> PA17 (EXT1 PIN12)
 * - SAM R34 Xplained Pro board
 *  - \b PB02 (EXT1 PIN17) <-----> PA16 (EXT1 PIN11)
 *  - \b PA23 (EXT1 PIN15) <-----> PA17 (EXT1 PIN12)
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
 * \section asfdoc_sam0_i2c_unit_test_usage Usage
 *  - The unit test configures a I2C master and a I2C slave, 
 *  - master write to slave and then read from slave,
 *  - compare the write and read results
 *
 * \section asfdoc_sam0_i2c_unit_test_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section asfdoc_sam0_i2c_unit_test_contactinfo Contact Information
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

void i2c_slave_read_request_callback(
		struct i2c_slave_module *const module);
void i2c_slave_write_request_callback(
		struct i2c_slave_module *const module);
void configure_i2c_slave_callbacks(void);

/* Structure for UART module connected to EDBG (used for unit test output) */
struct usart_module cdc_uart_module;

/* master packet_data */
#define DATA_LENGTH 10
#define SLAVE_ADDRESS 0x12
static uint8_t master_write_buffer[DATA_LENGTH] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
};
static uint8_t master_read_buffer[DATA_LENGTH] = {0};

/* slave packet_data */
static struct i2c_slave_packet slave_packet;
static uint8_t slave_buffer[DATA_LENGTH] = {0};;

/* Stucture for i2c master module and slave module */
static struct i2c_master_module i2c_master_instance;
static struct i2c_slave_module i2c_slave_instance;

/* slave read quest */
void i2c_slave_read_request_callback(
		struct i2c_slave_module *const module)
{
	/* Init i2c packet. */
	slave_packet.data_length = DATA_LENGTH;
	slave_packet.data        = slave_buffer;
	
	/* Write buffer to master */
	i2c_slave_write_packet_job(module, &slave_packet);
}

/* slave write quest */
void i2c_slave_write_request_callback(
		struct i2c_slave_module *const module)
{
	/* Init i2c packet. */
	slave_packet.data_length = DATA_LENGTH;
	slave_packet.data        = slave_buffer;

	/* Read buffer from master */
	i2c_slave_read_packet_job(module, &slave_packet);
}

/* setup i2c callback */
void configure_i2c_slave_callbacks(void)
{
	/* Register and enable callback functions */
	i2c_slave_register_callback(&i2c_slave_instance, i2c_slave_read_request_callback,
			I2C_SLAVE_CALLBACK_READ_REQUEST);
	i2c_slave_enable_callback(&i2c_slave_instance,
			I2C_SLAVE_CALLBACK_READ_REQUEST);

	i2c_slave_register_callback(&i2c_slave_instance, i2c_slave_write_request_callback,
			I2C_SLAVE_CALLBACK_WRITE_REQUEST);
	i2c_slave_enable_callback(&i2c_slave_instance,
			I2C_SLAVE_CALLBACK_WRITE_REQUEST);
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
 * \internal
 * \brief Test for I2C master and slave initialization.
 *
 * This test initializes the i2c master and slave and checks whether the
 * initialization is successful or not.
 *
 * \param test Current test case.
 */
static void run_i2c_init_test(const struct test_case *test)
{
	enum status_code status;
	struct i2c_master_config config_i2c_master;
	struct i2c_slave_config config_i2c_slave;

	/* master init testing */
	i2c_master_get_config_defaults(&config_i2c_master);
	config_i2c_master.buffer_timeout = 10000;
	config_i2c_master.pinmux_pad0    = CONF_MASTER_SDA_PINMUX;
	config_i2c_master.pinmux_pad1    = CONF_MASTER_SCK_PINMUX;
	status = i2c_master_init(&i2c_master_instance, CONF_I2C_MASTER_MODULE, &config_i2c_master);
	/* Check for successful initialization */
	test_assert_true(test, status == STATUS_OK,
			"I2C master initialization failed");
	i2c_master_enable(&i2c_master_instance);

	/* slave init testing */
	i2c_slave_get_config_defaults(&config_i2c_slave);
	config_i2c_slave.address        = SLAVE_ADDRESS;
	config_i2c_slave.address_mode   = I2C_SLAVE_ADDRESS_MODE_MASK;
	config_i2c_slave.buffer_timeout = 10000;
#if SAMR30 || SAMR34 || SAMR35
	config_i2c_slave.pinmux_pad0    = CONF_SLAVE_SDA_PINMUX;
	config_i2c_slave.pinmux_pad1    = CONF_SLAVE_SCK_PINMUX;
#endif	
	status = i2c_slave_init(&i2c_slave_instance, CONF_I2C_SLAVE_MODULE, &config_i2c_slave);
	/* Check for successful initialization */
	test_assert_true(test, status == STATUS_OK,
			"I2C slave initialization failed");
	i2c_slave_enable(&i2c_slave_instance);
	/* setup i2c slave in callback mode for write and read request */
	configure_i2c_slave_callbacks();
}

/**
 * \internal
 * \brief Test for I2C master transfer.
 *
 * First test transfer function with stop.
 * write to slave, read from slave and then compare the data.
 * the slave send out the data it received,
 * so master write and read data should be the same.
 *
 * Then test transfer function without stop.
 * write to slave, then use i2c_master_send_stop to complete writing,
 * read from slave, compare the data.
 * finally, use function with stop to complete the transfer.
 *
 * \param test Current test case.
 */
static void run_i2c_master_transfer_test(const struct test_case *test)
{
	uint32_t timeout_cycles = 1000;
	uint32_t i;
	bool status = true;
	struct i2c_master_packet master_packet = {
		.address     = SLAVE_ADDRESS,
		.data_length = DATA_LENGTH,
		.data        = master_write_buffer,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	/* with stop function: master transfer test */
	/* wait the master write to complete */
	do {
		timeout_cycles--;
		if (i2c_master_write_packet_wait(&i2c_master_instance, &master_packet) ==
			STATUS_OK) {
			break;
		}
	} while (timeout_cycles > 0);
	test_assert_true(test, timeout_cycles > 0,
			"i2c master write failed");
	
	/* wait the master read to complete */
	master_packet.data = master_read_buffer;
	timeout_cycles = 1000;
	do {
		timeout_cycles--;
		if (i2c_master_read_packet_wait(&i2c_master_instance, &master_packet) ==
			STATUS_OK) {
			break;
		}
	} while (timeout_cycles > 0);
	test_assert_true(test, timeout_cycles > 0,
			"i2c master read failed");
	
	/* Compare the sent and the received */
	for (i = 0; i < DATA_LENGTH; i++) {
		if (master_read_buffer[i] != master_write_buffer[i]) {
			status = false;
			break;
		}
	}
	test_assert_true(test, status == true,
			"i2c master transfer comparsion failed");
	/* with stop function master transfer test end */
	
	/* without stop function: master transfer test*/
	/* wait the master write to finish */
	master_packet.data = master_write_buffer;
	timeout_cycles = 1000;
	do {

		timeout_cycles--;
		if (i2c_master_write_packet_wait_no_stop(&i2c_master_instance, &master_packet) ==
		STATUS_OK) {
			break;
		}
	} while (timeout_cycles > 0);
	test_assert_true(test, timeout_cycles > 0,
                         "i2c master write without stop failed");
	
	/* wait the master read to finish */
	master_packet.data = master_read_buffer;
	timeout_cycles = 1000;
	do {
		timeout_cycles--;
		if (i2c_master_read_packet_wait_no_stop(&i2c_master_instance, &master_packet) ==
		STATUS_OK) {
			break;
		}
	} while (timeout_cycles > 0);
	test_assert_true(test, timeout_cycles > 0,
                         "i2c master read without stop failed");
	
	/* Compare the sent and the received */
	for (i = 0; i < DATA_LENGTH; i++) {
		if (master_read_buffer[i] != master_write_buffer[i]) {
			status = false;
			break;
		}
	}
	test_assert_true(test, status == true,
                         "i2c master transfer without stop comparsion failed");
	
	/* use i2c_master_write_packet_wait to complete the transfer */
	master_packet.data = master_write_buffer;
	do {
		timeout_cycles--;
		if (i2c_master_write_packet_wait(&i2c_master_instance, &master_packet) ==
		STATUS_OK) {
			break;
		}
	} while (timeout_cycles > 0);
	test_assert_true(test, timeout_cycles > 0,
	"i2c master write with repeated start failed");
	
	/* without stop function: master transfer test end*/
}

/**
 * \internal
 * \brief Test full speed mode master transfer.
 *
 * test function with stop in full speed mode.
 * \param test Current test case.
 */
static void run_i2c_full_speed_test(const struct test_case *test)
{
	enum status_code status;
	struct i2c_master_config config_i2c_master;
	
	/* init i2c master in full speed mode*/
	i2c_master_get_config_defaults(&config_i2c_master);
	config_i2c_master.buffer_timeout = 10000;
	config_i2c_master.baud_rate      = I2C_MASTER_BAUD_RATE_400KHZ;
	config_i2c_master.pinmux_pad0    = CONF_MASTER_SDA_PINMUX;
	config_i2c_master.pinmux_pad1    = CONF_MASTER_SCK_PINMUX;
	i2c_master_disable(&i2c_master_instance);
	status = i2c_master_init(&i2c_master_instance, CONF_I2C_MASTER_MODULE, &config_i2c_master);
	/* Check for successful initialization */
	test_assert_true(test, status == STATUS_OK,
			"I2C master fast-mode initialization failed");
	i2c_master_enable(&i2c_master_instance);

	uint32_t timeout_cycles = 1000;
	uint32_t i;
	bool status1 = true;
	struct i2c_master_packet master_packet = {
		.address     = SLAVE_ADDRESS,
		.data_length = DATA_LENGTH,
		.data        = master_write_buffer,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	
	/* wait master write complete */	 
	do {
		timeout_cycles--;
		if (i2c_master_write_packet_wait(&i2c_master_instance, &master_packet) ==
			STATUS_OK) {
			break;
		}
	} while (timeout_cycles > 0);
	test_assert_true(test, timeout_cycles > 0,
			"i2c master write failed");
	
	/* wait master read complete */
	master_packet.data = master_read_buffer;
	timeout_cycles = 1000;
	do {
		timeout_cycles--;
		if (i2c_master_read_packet_wait(&i2c_master_instance, &master_packet) ==
			STATUS_OK) {
			break;
		}
	} while (timeout_cycles > 0);
	test_assert_true(test, timeout_cycles > 0,
			"i2c master read failed");
	
	/* Compare the sent and the received */
	for (i = 0; i < DATA_LENGTH; i++) {
		if (master_read_buffer[i] != master_write_buffer[i]) {
			status1 = false;
			break;
		}
	}
	test_assert_true(test, status1 == true,
			"i2c master transfer comparsion failed");
}

	
/**
 * \brief Run I2C master unit tests
 *
 * Initializes the system and serial output, then sets up the
 * I2C master unit test suite and runs it.
 */
int main(void)
{
	system_init();
	cdc_uart_init();

	/* Define Test Cases */
	DEFINE_TEST_CASE(i2c_init_test,
			NULL,
			run_i2c_init_test,
			NULL,
			"Testing I2C Initialization");

	DEFINE_TEST_CASE(i2c_master_transfer_test,
			NULL,
			run_i2c_master_transfer_test,
			NULL,
			"Testing I2C master data transfer");

	DEFINE_TEST_CASE(i2c_full_speed_test,
			NULL,
			run_i2c_full_speed_test,
			NULL,
			"Testing I2C change speed transfer");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(i2c_tests) = {
		&i2c_init_test,
		&i2c_master_transfer_test,
		&i2c_full_speed_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(i2c_test_suite, i2c_tests,
			"SAM I2C driver test suite");

	/* Run all tests in the suite*/
	test_suite_run(&i2c_test_suite);

	while (true) {
		/* Intentionally left empty */
	}
}
