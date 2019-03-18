/**
 * \file
 *
 * \brief SAM SPI Unit test
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
 * \mainpage SAM SPI Unit Test
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This unit test carries out tests for SERCOM SPI driver.
 * It consists of test cases for the following functionalities:
 *  - Test for driver initialization.
 *  - Test for single byte write and read by polling.
 *  - Test for buffer write by polling and read with interrupt.
 *  - Test for buffer read & write using transceive function.
 *  - Test for 9-bit data transfer.
 *  - Test for baudrate.
 */

/**
 * \page appdoc_main SAM SPI Unit Test
 *
 * Overview:
 * - \ref appdoc_sam0_spi_unit_test_intro
 * - \ref appdoc_sam0_spi_unit_test_setup
 * - \ref appdoc_sam0_spi_unit_test_usage
 * - \ref appdoc_sam0_spi_unit_test_compinfo
 * - \ref appdoc_sam0_spi_unit_test_contactinfo
 *
 * \section appdoc_sam0_spi_unit_test_intro Introduction
 * \copydetails appdoc_preface
 *
 * The following kit is required for carrying out the test:
 *  - SAM D20 Xplained Pro board
 *  - SAM D21 Xplained Pro board
 *  - SAM R21 Xplained Pro board
 *  - SAM L21 Xplained Pro board
 *  - SAM L22 Xplained Pro board
 *  - SAM DA1 Xplained Pro board
 *  - SAM HA1G16A Xplained Pro board
 *  - SAM C21 Xplained Pro board
 *  - SAM R30 Xplained Pro board
 *  - SAM R34 Xplained Pro board 
 *
 * \section appdoc_sam0_spi_unit_test_setup Setup
 * The following connections has to be made using wires:
 * -SAM D20 Xplained Pro
 *  - \b SCK:   EXT3 PIN18 (PB23) <--> EXT2 PIN15 (PA17)
 *  - \b SS_0:  EXT3 PIN15 (PB17) <--> EXT2 PIN16 (PA18)
 *  - \b DI/DO: EXT3 PIN17 (PB16) <--> EXT2 PIN17 (PA16)
 *  - \b DO/DI: EXT3 PIN16 (PB22) <--> EXT2 PIN18 (PA19)
 * -SAM D21/DA1 Xplained Pro
 *  - \b SCK:   EXT3 PIN15 (PB17) <--> EXT2 PIN15 (PA17)
 *  - \b SS_0:  EXT3 PIN16 (PB22) <--> EXT2 PIN16 (PA18)
 *  - \b DI/DO: EXT3 PIN17 (PB16) <--> EXT2 PIN17 (PA16)
 *  - \b DO/DI: EXT3 PIN18 (PB23) <--> EXT2 PIN18 (PA19)
 * -SAM HA1G16A Xplained Pro
 *  - \b SCK:   EXT3 PIN17 (PA16) <--> EXT1 PIN16 (PA04)
 *  - \b SS_0:  EXT3 PIN18 (PA17) <--> EXT1 PIN18 (PA05)
 *  - \b DI/DO: EXT3 PIN15 (PA20) <--> EXT1 PIN15 (PA10)
 *  - \b DO/DI: EXT3 PIN16 (PA21) <--> EXT1 PIN17 (PA11)
 * - SAM R21 Xplained Pro
 *  - \b SS_0:  EXT1 PIN15 (PB03) <--> EXT1 PIN12 (PA17)
 *  - \b DI/D0: EXT1 PIN16 (PB22) <--> EXT1 PIN7  (PA18)
 *  - \b DO/DI: EXT1 PIN17 (PB02) <--> EXT1 PIN11  (PA16)
 *  - \b SCK:   EXT1 PIN18 (PB23) <--> EXT1 PIN8  (PA19)
 * - SAM L21 Xplained Pro
 *  - \b DO/DI: EXT3 PIN9  (PA16) <--> EXT3 PIN17 (PB16)
 *  - \b SS_0:  EXT2 PIN15 (PA17) <--> EXT3 PIN15 (PB17)
 *  - \b DI/DO: EXT2 PIN14 (PA18) <--> EXT3 PIN16 (PB22)
 *  - \b SCK:   EXT2 PIN13 (PA19) <--> EXT3 PIN18 (PB23)
 * - SAM L22 Xplained Pro.
 *  - \b SS_0:  EXT1 PIN15 (PB21) <--> EXT2 PIN15 (PA17)
 *  - \b DO/DI: EXT1 PIN16 (PB00) <--> EXT2 PIN17 (PA16)
 *  - \b DI/DO: EXT1 PIN17 (PB02) <--> EXT2 PIN16 (PA18)
 *  - \b SCK:   EXT1 PIN18 (PB01) <--> EXT2 PIN18 (PA19)
 * - SAM C21 Xplained Pro.
 *  - \b SS_0:  EXT1 PIN15 (PA17) <--> EXT2 PIN15 (PB03)
 *  - \b DO/DI: EXT1 PIN16 (PA18) <--> EXT2 PIN17 (PB02)
 *  - \b DI/DO: EXT1 PIN17 (PA16) <--> EXT2 PIN16 (PB00)
 *  - \b SCK:   EXT1 PIN18 (PA19) <--> EXT2 PIN18 (PB01)
 * - SAM R30 Xplained Pro
 *  - \b DO/DI: EXT1 PIN11 (PA16) <--> EXT3 PIN17 (PB02)
 *  - \b SS_0:  EXT1 PIN12 (PA17) <--> EXT3 PIN15 (PA14)
 *  - \b DI/DO: EXT1 PIN7  (PA18) <--> EXT3 PIN16 (PB22)
 *  - \b SCK:   EXT1 PIN8  (PA19) <--> EXT3 PIN18 (PB23)
 * - SAM R34 Xplained Pro
 *  - \b DO/DI: EXT1 PIN11 (PA16) <--> EXT1 PIN17 (PB02)
 *  - \b SS_0:  EXT1 PIN12 (PA17) <--> EXT1 PIN15 (PA23)
 *  - \b DI/DO: EXT1 PIN7  (PA18) <--> EXT1 PIN16 (PB22)
 *  - \b SCK:   EXT1 PIN8  (PA19) <--> EXT1 PIN18 (PB23)
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
 * \section appdoc_sam0_spi_unit_test_usage Usage
 *  - The unit tests are carried out with SERCOM1 on EXT2 as SPI master and
 *    SERCOM0 on EXT1 as SPI slave.
 *  - Data is transmitted from master to slave in lengths of a single byte
 *    as well as multiple bytes.
 *
 * \section appdoc_sam0_spi_unit_test_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_spi_unit_test_contactinfo Contact Information
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

/* Test Baud rate */
#define TEST_SPI_BAUDRATE             1000000UL

/* Buffer size used during test */
#define BUFFER_LENGTH                 256

/* Structures for SPI master, slave configuration & slave instance selection */
struct spi_module master;
struct spi_module slave;
struct spi_slave_inst slave_inst;

/* Structure for UART module connected to EDBG (used for unit test output) */
struct usart_module cdc_uart_module;

/* Transmit and receive buffers used by master during test */
uint8_t tx_buf[BUFFER_LENGTH];
uint8_t rx_buf[BUFFER_LENGTH];
/* Transmit and receive buffers used by slave during test */
uint8_t slave_tx_buf[BUFFER_LENGTH];
uint8_t slave_rx_buf[BUFFER_LENGTH];

/* Flag to indicate whether buffer transmission is complete or not */
volatile bool transfer_complete = false;
/* Flag to check whether initialization passed */
volatile bool spi_init_success = false;

/**
 * \internal
 * \brief SPI interrupt callback function
 *
 * Called by SPI driver when transmission/reception is complete.
 *
 * \param module SPI module causing the interrupt (not used)
 */
static void user_spi_callback(struct spi_module *const module)
{
	transfer_complete = true;
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
 * \internal
 * \brief Test initializing SPI master & slave.
 *
 * This initializes the SPI master & slave.
 *
 * Test passes if initialization succeeds fails otherwise.
 *
 * \param test Current test case.
 */
static void run_spi_init_test(const struct test_case *test)
{
	enum status_code status = STATUS_ERR_IO;

	/* Structure for SPI configuration */
	struct spi_config config;
	struct spi_slave_inst_config slave_config;

	/* Select SPI slave SS pin */
	spi_slave_inst_get_config_defaults(&slave_config);
	slave_config.ss_pin = CONF_SPI_SLAVE_SS_PIN;
	spi_attach_slave(&slave_inst, &slave_config);

	/* Configure the SPI master */
	spi_get_config_defaults(&config);

	config.mux_setting     = CONF_SPI_MASTER_SPI_MUX;
	config.pinmux_pad0     = CONF_SPI_MASTER_DATA_IN_PIN_MUX;
	config.pinmux_pad1     = PINMUX_UNUSED;
	config.pinmux_pad2     = CONF_SPI_MASTER_DATA_OUT_PIN_MUX;
	config.pinmux_pad3     = CONF_SPI_MASTER_SCK_PIN_MUX;

	config.mode_specific.master.baudrate = TEST_SPI_BAUDRATE;
	status = spi_init(&master, CONF_SPI_MASTER_MODULE, &config);
	test_assert_true(test, status == STATUS_OK,
			"SPI master initialization failed");

	/* Enable the SPI master */
	spi_enable(&master);

	status = STATUS_ERR_IO;
	/* Configure the SPI slave */
	spi_get_config_defaults(&config);
	config.mode                 = SPI_MODE_SLAVE;
	config.mux_setting          = CONF_SPI_SLAVE_SPI_MUX;
	config.pinmux_pad0          = CONF_SPI_SLAVE_DATA_IN_PIN_MUX;
	config.pinmux_pad1          = CONF_SPI_SLAVE_SS_PIN_MUX;
	config.pinmux_pad2          = CONF_SPI_SLAVE_DATA_OUT_PIN_MUX;
	config.pinmux_pad3          = CONF_SPI_SLAVE_SCK_PIN_MUX;

	config.mode_specific.slave.frame_format   = SPI_FRAME_FORMAT_SPI_FRAME;
	config.mode_specific.slave.preload_enable = true;
	status = spi_init(&slave, CONF_SPI_SLAVE_MODULE, &config);
	test_assert_true(test, status == STATUS_OK,
			"SPI slave initialization failed");

	/* Enable the SPI slave */
	spi_enable(&slave);
	if (status == STATUS_OK) {
		spi_init_success = true;
	}
}

/**
 * \internal
 * \brief Test sending and receiving a byte by polling.
 *
 * This test sends (writes) one byte of data to the slave and
 * receives (reads) the data back and compares.
 *
 * Writing and reading are carried out by polling.
 *
 * \param test Current test case.
 */
static void run_single_byte_polled_test(const struct test_case *test)
{
	uint16_t txd_data = 0x55;
	uint16_t rxd_data = 0;

	/* Skip test if initialization failed */
	test_assert_true(test, spi_init_success,
			"Skipping test due to failed initialization");

	/* Send data to slave */
	spi_select_slave(&master, &slave_inst, true);
	while (!spi_is_ready_to_write(&master)) {
	}
	spi_write(&master, txd_data);
	while (!spi_is_write_complete(&master)) {
	}

	/* Dummy read SPI master data register */
	while (!spi_is_ready_to_read(&master)) {
	}
	spi_read(&master, &rxd_data);

	/* Read SPI slave data register */
	while (!spi_is_ready_to_read(&slave)) {
	}
	spi_read(&slave, &rxd_data);
	spi_select_slave(&master, &slave_inst, false);

	/* Output test result */
	test_assert_true(test, rxd_data == txd_data,
			"Failed transmitting/receiving byte. TX='%d', RX='%d'",
			txd_data, rxd_data);
}

/**
 * \internal
 * \brief Setup function: Send data by polling & receive with interrupt.
 *
 * This function registers and enables callback for buffer receive
 * completed operation.
 *
 * \param test Current test case.
 */
static void setup_buffer_polled_write_interrupt_read_test
	(const struct test_case *test)
{
	/* Register & enable callback for buffer reception */
	spi_register_callback(&slave, user_spi_callback,
			SPI_CALLBACK_BUFFER_RECEIVED);
	spi_enable_callback(&slave, SPI_CALLBACK_BUFFER_RECEIVED);
}

/**
 * \internal
 * \brief Cleanup function: Send data by polling & receive with interrupt.
 *
 * This function unregisters and disables callback for buffer receive
 * completed operation. It also clears the receive buffer rx_buf.
 *
 * \param test Current test case.
 */
static void cleanup_buffer_polled_write_interrupt_read_test
	(const struct test_case *test)
{
	/* Unregister & disable callback */
	spi_unregister_callback(&slave, SPI_CALLBACK_BUFFER_RECEIVED);
	spi_disable_callback(&slave, SPI_CALLBACK_BUFFER_RECEIVED);

	/* Clear receive buffer for next test */
	for (uint16_t i = 0; i < BUFFER_LENGTH; i++) {
		rx_buf[i] = 0;
	}
}

/**
 * \internal
 * \brief Test: Send data by polling & receive with interrupt.
 *
 * This test sends (writes) an array of data to the slave by polling and
 * receives (reads) the buffer back with interrupt and compares.
 *
 * \param test Current test case.
 */
static void run_buffer_polled_write_interrupt_read_test
	(const struct test_case *test)
{
	uint16_t i;
	uint16_t timeout_cycles;

	/* Skip test if initialization failed */
	test_assert_true(test, spi_init_success,
			"Skipping test due to failed initialization");

	/* Start the test */
	transfer_complete = false;
	timeout_cycles = 1000;
	spi_select_slave(&master, &slave_inst, true);
	spi_read_buffer_job(&slave, rx_buf, BUFFER_LENGTH, 0);
	spi_write_buffer_wait(&master, tx_buf, BUFFER_LENGTH);

	/* Wait until reception completes */
	do {
		timeout_cycles--;
		if (transfer_complete) {
			break;
		}
	} while (timeout_cycles != 0);
	spi_select_slave(&master, &slave_inst, false);

	test_assert_true(test, timeout_cycles > 0,
			"Timeout in reception");

	/* Compare received data with transmitted data */
	if (transfer_complete) {
		for (i = 0; i < BUFFER_LENGTH; i++) {
			test_assert_true(test, tx_buf[i] == rx_buf[i],
					"Bytes differ at buffer index %d : %d != %d",
					i, tx_buf[i], rx_buf[i]);
		}
	}
}

/**
 * \internal
 * \brief Test: Send & receive data using transceive functions.
 *
 * This test sends (writes) an array of data to the slave and
 * receives (reads) the buffer back using transceive functions
 * and compares.
 *
 * \param test Current test case.
 */
static void run_transceive_buffer_test(const struct test_case *test)
{
	enum status_code status = STATUS_ERR_IO;

	/* Skip test if initialization failed */
	test_assert_true(test, spi_init_success,
			"Skipping test due to failed initialization");

	/* Start the test */
	spi_transceive_buffer_job(&slave, slave_tx_buf, slave_rx_buf,
			BUFFER_LENGTH);
	spi_select_slave(&master, &slave_inst, true);
	status = spi_transceive_buffer_wait(&master, tx_buf, rx_buf,
			BUFFER_LENGTH);
	spi_select_slave(&master, &slave_inst, false);

	test_assert_true(test, status == STATUS_OK,
			"Transceive buffer failed");

	/* Compare received data with transmitted data */
	if (status == STATUS_OK) {
		for (uint16_t i = 0; i < BUFFER_LENGTH; i++) {
			test_assert_true(test, tx_buf[i] == slave_rx_buf[i],
					"During TX: Bytes differ at buffer index %d : %d != %d",
					i, tx_buf[i], slave_rx_buf[i]);
			test_assert_true(test, slave_tx_buf[i] == rx_buf[i],
					"During RX: Bytes differ at buffer index %d : %d != %d",
					i, slave_tx_buf[i], rx_buf[i]);
		}
	}
}

/**
 * \internal
 * \brief Test: Sends data at different baud rates.
 *
 * This test sends (writes) a byte to the slave and receives the data
 * at different baudrate testing up to the maximum allowed level.
 *
 * Transmission and reception are carried out by polling.
 *
 * \param test Current test case.
 */
static void run_baud_test(const struct test_case *test)
{
	uint32_t test_baud = 1000000;
	uint8_t txd_data   = 0x55;
	uint8_t rxd_data   = 0;
	bool max_baud      = true;

	/* Skip test if initialization failed */
	test_assert_true(test, spi_init_success,
			"Skipping test due to failed initialization");

	/* Structure for SPI configuration */
	struct spi_config config;

	/* Configure the SPI master */
	spi_get_config_defaults(&config);

	config.mux_setting     = CONF_SPI_MASTER_SPI_MUX;
	config.pinmux_pad0     = CONF_SPI_MASTER_DATA_IN_PIN_MUX;
	config.pinmux_pad1     = PINMUX_UNUSED;
	config.pinmux_pad2     = CONF_SPI_MASTER_DATA_OUT_PIN_MUX;
	config.pinmux_pad3     = CONF_SPI_MASTER_SCK_PIN_MUX;

	do {
		spi_disable(&master);
		config.mode_specific.master.baudrate = test_baud;
		spi_init(&master, CONF_SPI_MASTER_MODULE, &config);
		spi_enable(&master);

		/* Send data to slave */
		spi_select_slave(&master, &slave_inst, true);
		spi_write_buffer_wait(&master, &txd_data, 1);
		spi_read_buffer_wait(&slave, &rxd_data, 1, 0);
		spi_select_slave(&master, &slave_inst, false);

		if (txd_data != rxd_data) {
			max_baud = false;
			break;
		}

		test_baud += 1000000;
	} while (test_baud <= 24000000);

	/* Output the result */
	test_assert_true(test, max_baud,
			"Test failed at baudrate: %lu", test_baud);
}

/**
 * \internal
 * \brief Setup function: Send & receive 9-bit data by polling.
 *
 * This function configures the SPI master & slave in 9-bit mode.
 *
 * \param test Current test case.
 */
static void setup_transfer_9bit_test(const struct test_case *test)
{
	enum status_code status = STATUS_ERR_IO;
	spi_init_success = false;

	/* Structure for SPI configuration */
	struct spi_config config;

	spi_disable(&master);
	spi_disable(&slave);

	/* Configure the SPI master */
	spi_get_config_defaults(&config);

	config.mux_setting     = CONF_SPI_MASTER_SPI_MUX;
	config.pinmux_pad0     = CONF_SPI_MASTER_DATA_IN_PIN_MUX;
	config.pinmux_pad1     = PINMUX_UNUSED;
	config.pinmux_pad2     = CONF_SPI_MASTER_DATA_OUT_PIN_MUX;
	config.pinmux_pad3     = CONF_SPI_MASTER_SCK_PIN_MUX;

	config.mode_specific.master.baudrate = TEST_SPI_BAUDRATE;
	config.character_size  = SPI_CHARACTER_SIZE_9BIT;
	status = spi_init(&master, CONF_SPI_MASTER_MODULE, &config);
	test_assert_true(test, status == STATUS_OK,
			"SPI master initialization failed for 9-bit configuration");
	/* Enable the SPI master */
	spi_enable(&master);

	status = STATUS_ERR_IO;

	/* Configure the SPI slave */
	spi_get_config_defaults(&config);
	config.mode                 = SPI_MODE_SLAVE;

	config.mux_setting          = CONF_SPI_SLAVE_SPI_MUX;
	config.pinmux_pad0          = CONF_SPI_SLAVE_DATA_IN_PIN_MUX;
	config.pinmux_pad1          = CONF_SPI_SLAVE_SS_PIN_MUX;
	config.pinmux_pad2          = CONF_SPI_SLAVE_DATA_OUT_PIN_MUX;
	config.pinmux_pad3          = CONF_SPI_SLAVE_SCK_PIN_MUX;

	config.mode_specific.slave.frame_format   = SPI_FRAME_FORMAT_SPI_FRAME;
	config.mode_specific.slave.preload_enable = true;
	config.character_size       = SPI_CHARACTER_SIZE_9BIT;
	status = spi_init(&slave, CONF_SPI_SLAVE_MODULE, &config);
	test_assert_true(test, status == STATUS_OK,
			"SPI slave initialization failed for 9-bit configuration");

	/* Enable the SPI slave */
	spi_enable(&slave);
	if (status == STATUS_OK) {
		spi_init_success = true;
	}
}

/**
 * \internal
 * \brief Test sending and receiving 9-bit data by polling.
 *
 * This test sends (writes) one 9-bit data to the slave and
 * receives (reads) the data back and compares.
 *
 * Writing and reading are carried out by polling.
 *
 * \param test Current test case.
 */
static void run_transfer_9bit_test(const struct test_case *test)
{
	uint16_t txd_data = 0x155;
	uint16_t rxd_data = 0;

	/* Skip test if initialization failed */
	test_assert_true(test, spi_init_success,
			"Skipping test due to failed initialization");

	/* Send data to slave */
	spi_select_slave(&master, &slave_inst, true);
	while (!spi_is_ready_to_write(&master)) {
	}
	spi_write(&master, txd_data);
	while (!spi_is_write_complete(&master)) {
	}

	/* Dummy read SPI master data register */
	while (!spi_is_ready_to_read(&master)) {
	}
	spi_read(&master, &rxd_data);

	/* Read SPI slave data register */
	while (!spi_is_ready_to_read(&slave)) {
	}
	spi_read(&slave, &rxd_data);
	spi_select_slave(&master, &slave_inst, false);

	/* Output test result */
	test_assert_true(test, rxd_data == txd_data,
			"Failed transmitting/receiving byte. TX='%d', RX='%d'",
			txd_data, rxd_data);
}

/**
 * \brief Run SPI unit tests
 *
 * Initializes the system and serial output, then sets up the
 * SPI unit test suite and runs it.
 */
int main(void)
{
	system_init();
	cdc_uart_init();
	cpu_irq_enable();

	/* Fill the transmit buffers with some data */
	for (uint16_t i = 0; i < BUFFER_LENGTH; i++) {
		tx_buf[i] = i + 1;
		slave_tx_buf[i] = i + 1;
	}

	/* Define Test Cases */
	DEFINE_TEST_CASE(spi_init_test, NULL,
			run_spi_init_test, NULL,
			"Initialization test for SPI master & slave");

	DEFINE_TEST_CASE(single_byte_polled_test, NULL,
			run_single_byte_polled_test, NULL,
			"Transfer single byte and readback by polling");

	DEFINE_TEST_CASE(buffer_polled_write_interrupt_read_test,
			setup_buffer_polled_write_interrupt_read_test,
			run_buffer_polled_write_interrupt_read_test,
			cleanup_buffer_polled_write_interrupt_read_test,
			"Transfer bytes by polling and read back with interrupt");

	DEFINE_TEST_CASE(transceive_buffer_test, NULL,
			run_transceive_buffer_test, NULL,
			"Transmit & receive bytes using transceive functions");

	DEFINE_TEST_CASE(baud_test, NULL, run_baud_test, NULL,
			"Transfer byte at different baud rates");

	DEFINE_TEST_CASE(transfer_9bit_test, setup_transfer_9bit_test,
			run_transfer_9bit_test, NULL,
			"Transfer 9-bit character and readback by polling");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(spi_tests) = {
		&spi_init_test,
		&single_byte_polled_test,
		&buffer_polled_write_interrupt_read_test,
		&transceive_buffer_test,
		&baud_test,
		&transfer_9bit_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(spi_test_suite, spi_tests,
			"SAM SPI driver test suite");

	/* Run all tests in the suite*/
	test_suite_run(&spi_test_suite);

	while (true) {
		/* Intentionally left empty */
	}
}
