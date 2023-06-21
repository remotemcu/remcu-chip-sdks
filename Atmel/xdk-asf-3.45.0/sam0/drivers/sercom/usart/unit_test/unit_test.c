/**
 * \file
 *
 * \brief SAM USART Unit test
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
 * \mainpage SAM USART Unit Test
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This unit test carries out tests for SERCOM USART driver.
 * It consists of test cases for the following functionalities:
 *  - Test for driver initialization.
 *  - Test for single 8-bit write and read by polling.
 *  - Test for single 9-bit write and read by polling.
 *  - Test for multiple 8-bit write by polling and read by interrupts.
 *  - Test for multiple 8-bit write and read by interrupts.
 */

/**
 * \page appdoc_main SAM USART Unit Test
 *
 * Overview:
 * - \ref appdoc_sam0_usart_unit_test_intro
 * - \ref appdoc_sam0_usart_unit_test_setup
 * - \ref appdoc_sam0_usart_unit_test_usage
 * - \ref appdoc_sam0_usart_unit_test_compinfo
 * - \ref appdoc_sam0_usart_unit_test_contactinfo
 *
 * \section appdoc_sam0_usart_unit_test_intro Introduction
 * \copydetails appdoc_preface
 *
 * The following kit is required for carrying out the test:
 *  - SAM D20 Xplained Pro board
 *  - SAM D21 Xplained Pro board
 *  - SAM R21 Xplained Pro board
 *  - SAM L21 Xplained Pro board
 *  - SAM L22 Xplained Pro board
 *  - SAM DA1 Xplained Pro board
 *  - SAM HA1G16A  Xplained Pro board
 *  - SAM C21 Xplained Pro board
 *  - SAM R30 Xplained Pro board
 *  - SAM R30 Module Xplained Pro board
 *  - SAM R34 Xplained Pro board
 *
 * \section appdoc_sam0_usart_unit_test_setup Setup
 * The following connections has to be made using wires:
 * - SAM D21/DA1/D20 Xplained Pro board
 *  - \b TX/RX: EXT2 PIN17 (PA16) <--> EXT3 PIN17 (PB16)
 * - SAM HA1G16A  Xplained Pro board
 *  - \b TX/RX: EXT1 PIN14 (PB10) <--> EXT1 PIN12 (PA09)
 * - SAM R21 Xplained Pro board
 *  - \b TX/RX: EXT1 PIN11 (PA16) <--> EXT1 PIN17 (PB02)
 * - SAM L21 Xplained Pro board
 *  - \b TX/RX: EXT2 PIN3  (PA10) <--> EXT2 PIN8  (PB13)
 * - SAM L22 Xplained Pro board
 *  - \b TX/RX: EXT1 PIN13  (PA23) <--> EXT3 PIN3  (PA06)
 * - SAM C21 Xplained Pro board
 *  - \b TX/RX: EXT1 PIN11 (PA12) <--> EXT2 PIN4  (PA09)
 * - SAM R30 Xplained Pro board
 *  - \b TX/RX: EXT1 PIN7 (PA18) <--> EXT1 PIN12  (PA17)
<<<<<<< HEAD
 * - SAM R30 Module Xplained Pro board
 *  - \b TX/RX: EXT PIN13 (PA14) <--> EXT PIN15  (PA17)
=======
 * - SAM R34 Xplained Pro board
 *  - \b TX/RX: EXT1 PIN11 (PA16) <--> EXT1 PIN17  (PB02)
>>>>>>> 3518a2958ff4695a84f9222901de2da524b4520d
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
 * \section appdoc_sam0_usart_unit_test_usage Usage
 *  - The unit tests are carried out with one SERCOM on EXT1 as the USART
 *    transmitter and another SERCOM on EXT1 as the SERCOM USART receiver.
 *  - Data is transmitted from transmitter to receiver in lengths of a single
 *    byte as well as multiple bytes.
 *
 * \section appdoc_sam0_usart_unit_test_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_usart_unit_test_contactinfo Contact Information
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

/* Test string to send */
#define TEST_STRING        "Hello world!"
/* Length of test string */
#define TEST_STRING_LEN    13

/* Speed to test USART at */
#define TEST_USART_SPEED   115200

/* Structure for UART module connected to EDBG (used for unit test output) */
struct usart_module cdc_uart_module;

struct usart_module usart_rx_module;
struct usart_config usart_rx_config;
struct usart_module usart_tx_module;
struct usart_config usart_tx_config;

volatile bool transfer_complete;


/**
 * \internal
 * \brief USART interrupt callback function
 *
 * Called by USART driver when receiving is complete.
 *
 * * \param module USART module causing the interrupt (not used)
 */
static void usart_callback(struct usart_module *const module)
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
 * \brief Test single 8-bit character send and receive.
 *
 * This test sends on 9-bit character and checks it's received properly
 * on the other end.
 *
 * \param test Current test case.
 */
static void run_transfer_single_8bit_char_test(const struct test_case *test)
{
	uint16_t tx_char = 0x53;
	volatile uint16_t rx_char = 0;

	/* Write and read the data */
	usart_write_wait(&usart_tx_module, tx_char);
	usart_read_wait(&usart_rx_module, (uint16_t*)&rx_char);

	/* Make sure we received what we sent */
	test_assert_true(test, tx_char==rx_char,
			"Failed receiving sent byte. TX=%d, RX=%d", tx_char, rx_char);

}

/**
 * \internal
 * \brief Test single 9-bit character send and receive.
 *
 * This test sends one 9-bit character and checks it's received properly
 * on the other end.
 *
 * \param test Current test case.
 */
static void run_transfer_single_9bit_char_test(const struct test_case *test)
{
	uint16_t tx_char = 0x166;
	uint16_t rx_char;

	/* Re-configure RX USART to operate with 9 bit character size */
	usart_disable(&usart_rx_module);
	usart_rx_config.character_size = USART_CHARACTER_SIZE_9BIT;
	usart_init(&usart_rx_module, CONF_RX_USART,	&usart_rx_config);

	/* Re-configure TX USART to operate with 9 bit character size */
	usart_disable(&usart_tx_module);
	usart_tx_config.character_size = USART_CHARACTER_SIZE_9BIT;
	usart_init(&usart_tx_module, CONF_TX_USART,	&usart_tx_config);

	/* Enable USART */
	usart_enable(&usart_rx_module);
	usart_enable(&usart_tx_module);

	/* Write and read the data */
	usart_write_wait(&usart_tx_module, tx_char);
	usart_read_wait(&usart_rx_module, &rx_char);

	/* Make sure we received what we sent */
	test_assert_true(test, tx_char==rx_char,
			"Failed receiving sent byte. TX=%d, RX=%d", tx_char, rx_char);

	/* Put RX USART back in 8 bit mode */
	usart_disable(&usart_rx_module);
	usart_rx_config.character_size = USART_CHARACTER_SIZE_8BIT;
	usart_init(&usart_rx_module, CONF_RX_USART,	&usart_rx_config);

	/* Put TX USART back in 8 bit mode */
	usart_disable(&usart_tx_module);
	usart_tx_config.character_size = USART_CHARACTER_SIZE_8BIT;
	usart_init(&usart_tx_module, CONF_TX_USART,	&usart_tx_config);

	/* Enable USART */
	usart_enable(&usart_rx_module);
	usart_enable(&usart_tx_module);
}


/**
 * \internal
 * \brief Test sending (blocking) and receiving (interrupt) a string.
 *
 * This test sends one string from one USART to another.
 * It's sent using a blocking write, while it's received using interrupts.
 *
 * \param test Current test case.
 */
static void run_buffer_write_blocking_read_interrupt_test(const struct test_case *test)
{
	uint8_t tx_string[TEST_STRING_LEN] = TEST_STRING;
	volatile uint8_t rx_string[TEST_STRING_LEN] = "";
	int16_t result;

	/* We will read back the buffer using interrupt */
	usart_register_callback(&usart_rx_module, usart_callback,
			USART_CALLBACK_BUFFER_RECEIVED);
	usart_enable_callback(&usart_rx_module, USART_CALLBACK_BUFFER_RECEIVED);

	/* Start receiving */
	transfer_complete = false;
	usart_read_buffer_job(&usart_rx_module, (uint8_t*)rx_string,
			TEST_STRING_LEN);

	/* Send the string */
	usart_write_buffer_wait(&usart_tx_module, tx_string,
			TEST_STRING_LEN );

	uint16_t timeout_cycles = 0xFFFF;

	/* Wait until reception completes */
	do {
		timeout_cycles--;
		if (transfer_complete) {
			break;
		}
	} while (timeout_cycles != 0);

	test_assert_true(test, timeout_cycles > 0,
			"Timeout in reception");

	usart_disable_callback(&usart_rx_module, USART_CALLBACK_BUFFER_RECEIVED);
	usart_unregister_callback(&usart_rx_module, USART_CALLBACK_BUFFER_RECEIVED);

	/* Compare strings */
	result = strcmp((char*)tx_string, (char*)rx_string);

	/* Make sure we 0-terminate the received string in case it's
		gibberish and we have to print it */
	rx_string[TEST_STRING_LEN-1] = 0;

	test_assert_false(test, result,
			"Failed receiving string. TX='%s', RX='%s'", tx_string, rx_string);
}

/**
 * \internal
 * \brief Test sending and receiving a string using interrupts.
 *
 * This test sends one string from one USART to another.
 * Both the send and receive is done using interrupts.
 *
 * \param test Current test case.
 */
static void run_buffer_read_write_interrupt_test(const struct test_case *test)
{
	volatile uint8_t tx_string[TEST_STRING_LEN] = TEST_STRING;
	volatile uint8_t rx_string[TEST_STRING_LEN] = "";
	int16_t result;

	usart_register_callback(&usart_rx_module, usart_callback,
			USART_CALLBACK_BUFFER_RECEIVED);
	usart_enable_callback(&usart_rx_module, USART_CALLBACK_BUFFER_RECEIVED);

	/* start send */
	transfer_complete = false;

	usart_write_buffer_job(&usart_tx_module, (uint8_t*)tx_string,
			TEST_STRING_LEN);
	usart_read_buffer_job(&usart_rx_module, (uint8_t*)rx_string,
			TEST_STRING_LEN);

	uint16_t timeout_cycles = 0xFFFF;

	/* Wait until reception completes */
	do {
		timeout_cycles--;
		if (transfer_complete) {
			break;
		}
	} while (timeout_cycles != 0);

	test_assert_true(test, timeout_cycles > 0,
			"Timeout in send/receive");

	/* Compare strings */
	result = strcmp((char*)tx_string, (char*)rx_string);

	/* Make sure we 0-terminate the received string in case it's
		gibberish and we have to print it */
	rx_string[TEST_STRING_LEN-1] = 0;

	test_assert_false(test, result,
			"Failed receiving string. TX='%s', RX='%s'", tx_string, rx_string);
}

/**
 * \brief Initialize USARTs for unit tests
 *
 * Initializes the two USARTs used by the unit test (one for RX and one for TX).
 *
 */
static void test_system_init(void)
{
	/* Configure RX USART */
	usart_get_config_defaults(&usart_rx_config);
	usart_rx_config.mux_setting = CONF_RX_USART_SERCOM_MUX;
	usart_rx_config.pinmux_pad0 = CONF_RX_USART_PINMUX_PAD0;
	usart_rx_config.pinmux_pad1 = CONF_RX_USART_PINMUX_PAD1;
	usart_rx_config.pinmux_pad2 = CONF_RX_USART_PINMUX_PAD2;
	usart_rx_config.pinmux_pad3 = CONF_RX_USART_PINMUX_PAD3;
	usart_rx_config.baudrate    = TEST_USART_SPEED;
	/* Apply configuration */
	usart_init(&usart_rx_module, CONF_RX_USART, &usart_rx_config);

	/* Configure TX USART */
	usart_get_config_defaults(&usart_tx_config);
	usart_tx_config.mux_setting = CONF_TX_USART_SERCOM_MUX;
	usart_tx_config.pinmux_pad0 = CONF_TX_USART_PINMUX_PAD0;
	usart_tx_config.pinmux_pad1 = CONF_TX_USART_PINMUX_PAD1;
	usart_tx_config.pinmux_pad2 = CONF_TX_USART_PINMUX_PAD2;
	usart_tx_config.pinmux_pad3 = CONF_TX_USART_PINMUX_PAD3;
	usart_tx_config.baudrate    = TEST_USART_SPEED;
	/* Apply configuration */
	usart_init(&usart_tx_module, CONF_TX_USART, &usart_tx_config);
	/* Enable USART */
	usart_enable(&usart_rx_module);
	usart_enable(&usart_tx_module);
}


/**
 * \brief Run USART unit tests
 *
 * Initializes the system and serial output, then sets up the
 * USART unit test suite and runs it.
 */
int main(void)
{
	system_init();
	cdc_uart_init();
	test_system_init();

	/* Define Test Cases */
	DEFINE_TEST_CASE(transfer_single_8bit_char_test, NULL,
			run_transfer_single_8bit_char_test, NULL,
			"Transfer single 8-bit character");

	DEFINE_TEST_CASE(transfer_single_9bit_char_test, NULL,
			run_transfer_single_9bit_char_test, NULL,
			"Transfer single 9-bit character");

	DEFINE_TEST_CASE(transfer_buffer_test, NULL,
			run_buffer_write_blocking_read_interrupt_test, NULL,
			"Buffer write blocking/read interrupt");

	DEFINE_TEST_CASE(receive_buffer_test, NULL,
			run_buffer_read_write_interrupt_test, NULL,
			"Buffer interrupt read and write");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(usart_tests) = {
			&transfer_single_8bit_char_test,
			&transfer_single_9bit_char_test,
			&transfer_buffer_test,
			&receive_buffer_test,
			};

	/* Define the test suite */
	DEFINE_TEST_SUITE(usart_suite, usart_tests,
			"SAM USART driver test suite");

	/* Run all tests in the suite*/
	test_suite_run(&usart_suite);

	while (true) {
		/* Intentionally left empty */
	}

}
