/**
 * \file
 *
 * \brief Unit tests for USART driver.
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
#include <string.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <conf_test.h>
#include "asf.h"

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the USART driver.
 * It consists of test cases for the following functionalities:
 * - USART async mode test
 * - USART sync mode test
 * - USART Write Protection
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 *
 * \section device_info Device Info
 * All SAM devices can be used.
 * This example has been tested with the following setup:
 * - samg55_xplained_pro
 *
 * To run the test:
 *  - Connect the supported Xplained Pro board to the computer using a
 *    micro USB cable.
 *  - Open the virtual COM port in a terminal application.
 *    \note The USB composite firmware running on the Embedded Debugger (EDBG)
 *          will enumerate as debugger, virtual COM port and EDBG data
 *          gateway.
 *  - Build the project, program the target and run the application.
 *  - Connect usarts as follows on SAMG55_Xplained_pro:
 *  EXT1_PIN14(PA10)(TXD0) -- EXT4_PIN12(PB11)(RXD6)
 *  EXT3_PIN14(PB00)(SCK0) -- EXT3_PIN08(PB13)(SCK6)
 *  EXT1_PIN06(PA25)(CTS0) -- EXT3_PIN06(PB15)(RTS6)
 *
 *    The terminal shows the results of the unit test.
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for ARM. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com">http://www.microchip.com</a>.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

/* variables for transmit and receive */
static uint32_t tx_data, rx_data;
/* variable for cpu frequency */
static uint32_t cpu_hz;

/**
 *  \brief transfer data between 2 usarts.
 */
static void data_transfer(void)
{
	uint32_t timeout_cycles = cpu_hz/2;

	/* Enable transmit */
	usart_enable_tx(BOARD_USART_PAIR_1);
	/* Enable receive */
	usart_enable_rx(BOARD_USART_PAIR_2);
	/* Reset rx_data */
	rx_data = 0;

	/* Send out data */
	do {
		timeout_cycles--;
		if (usart_is_tx_ready(BOARD_USART_PAIR_1)) {
			usart_write(BOARD_USART_PAIR_1, tx_data);
			break;
		}
	} while (timeout_cycles > 0);

	/* Receive data */
	timeout_cycles = cpu_hz/2;
	do {
		timeout_cycles--;
		if (usart_is_rx_ready(BOARD_USART_PAIR_2)) {
			usart_read(BOARD_USART_PAIR_2, &rx_data);
			break;
		}
	} while (timeout_cycles > 0); 
}

/**
 * \brief This test tests USART async mode test .
 *
 * include 8 bits transfer test, 9 bits transfer test,
 * parity error detect and hardware handshaking test.
 *
 * \param test Current test case
 */
static void run_usart_async_test(const struct test_case *test)
{
	uint32_t status;
	/* Sanity check argument. */
	Assert(test);

#if (SAMG55)
	/* Enable the peripheral and set USART mode. */
	flexcom_enable(BOARD_FLEXCOM_PAIR_1);
	flexcom_set_opmode(BOARD_FLEXCOM_PAIR_1, FLEXCOM_USART);
	flexcom_enable(BOARD_FLEXCOM_PAIR_2);
	flexcom_set_opmode(BOARD_FLEXCOM_PAIR_2, FLEXCOM_USART);
#else
	/* Enable the peripheral clock in the PMC. */
	sysclk_enable_peripheral_clock(BOARD_USART_PAIR_1);
	sysclk_enable_peripheral_clock(BOARD_USART_PAIR_2);
#endif

	/* Usart async mode 8 bits transfer test */
	sam_usart_opt_t usart_asynchronous_settings = {
		.baudrate     = BOARD_USART_BAUDRATE,
		.char_length  = US_MR_CHRL_8_BIT,
		.parity_type  = US_MR_PAR_NO,
		.stop_bits    = US_MR_NBSTOP_1_BIT,
		.channel_mode = US_MR_CHMODE_NORMAL,
		/* This field is only used in IrDA mode. */
		.irda_filter  = 0
	};

	/* Configure USART in async mode, 8 bits data, no parity, 1 stop bit */
	usart_init_rs232(BOARD_USART_PAIR_1, &usart_asynchronous_settings, cpu_hz);
	usart_init_rs232(BOARD_USART_PAIR_2, &usart_asynchronous_settings, cpu_hz);
	tx_data = 0x3A;
	/* Transfer data between 2 usarts */
	data_transfer();
	test_assert_true(test, tx_data == rx_data,
		"usart async 8 bits transfer test failed");

	/* Usart async mode 9 bits transfer test */
	/* Configure USART in async mode, 9 bits data, no parity, 1 stop bit */
	usart_asynchronous_settings.char_length = US_MR_MODE9;
	usart_init_rs232(BOARD_USART_PAIR_1, &usart_asynchronous_settings, cpu_hz);
	usart_init_rs232(BOARD_USART_PAIR_2, &usart_asynchronous_settings, cpu_hz);
	tx_data = 0x1A3;
	/* Transfer data between 2 usarts */
	data_transfer();
	test_assert_true(test, tx_data == rx_data,
		"usart async 9 bits transfer test failed");

	/* Async mode parity error dected test */
	/* Configure transmiter parity bit as 0 but receiver parity bit as 1 */
	usart_asynchronous_settings.parity_type = US_MR_PAR_SPACE;
	usart_init_rs232(BOARD_USART_PAIR_1, &usart_asynchronous_settings, cpu_hz);
	usart_asynchronous_settings.parity_type = US_MR_PAR_MARK;
	usart_init_rs232(BOARD_USART_PAIR_2, &usart_asynchronous_settings, cpu_hz);
	/* Transfer data between 2 usarts */
	data_transfer();
	status = usart_get_status(BOARD_USART_PAIR_2);
	test_assert_true(test, (status & US_CSR_PARE) ,
		"usart async parity error detected test failed");

	/* Hardware handshaking test */
	/* Enable transmiter and receiver hardware handshaking feature */
	usart_init_hw_handshaking(BOARD_USART_PAIR_1, &usart_asynchronous_settings, cpu_hz);
	usart_init_hw_handshaking(BOARD_USART_PAIR_2, &usart_asynchronous_settings, cpu_hz);
	/* Enable USART1 transmit, USART2 receive doesn't enable, so USART2 will produce high RTS signal */
	usart_enable_tx(BOARD_USART_PAIR_1);
	/* USART1 should get high CTS siganl */
	status = usart_get_status(BOARD_USART_PAIR_1);
	test_assert_true(test, status & US_CSR_CTS,
		"usart async handshaking test failed");
}

/**
 * \brief This test tests USART sync mode test .
 *
 * include 8 bits transfer test, 9 bits transfer test and
 * parity error detect test.
 * 
 * \param test Current test case
 */
static void run_usart_sync_test(const struct test_case *test)
{
	uint32_t status;
	/* Sanity check argument. */
	Assert(test);

	/* Usart sync mode 8 bits transfer test */
	sam_usart_opt_t usart_synchronous_settings = {
		.baudrate     = BOARD_USART_BAUDRATE,
		.char_length  = US_MR_CHRL_8_BIT,
		.parity_type  = US_MR_PAR_NO,
		.stop_bits    = US_MR_NBSTOP_1_BIT,
		.channel_mode = US_MR_CHMODE_NORMAL,
		/* This field is only used in IrDA mode. */
		.irda_filter  = 0
	};
	/* Configure USART in sync mode, 8 bits data, no parity, 1 stop bit */
	usart_init_sync_master(BOARD_USART_PAIR_1, &usart_synchronous_settings, cpu_hz);
	usart_init_sync_slave(BOARD_USART_PAIR_2, &usart_synchronous_settings);
	tx_data = 0x0A3;
	/* Transfer data between 2 usarts */
	data_transfer();
	test_assert_true(test, tx_data == rx_data,
		"usart sync 8 bits transfer test failed");

	/* Usart async mode 9 bits transfer test */
	/* Configure USART in sync mode, 9 bits data, no parity, 1 stop bit */
	usart_synchronous_settings.char_length = US_MR_MODE9;
	usart_init_sync_master(BOARD_USART_PAIR_1, &usart_synchronous_settings, cpu_hz);
	usart_init_sync_slave(BOARD_USART_PAIR_2, &usart_synchronous_settings);
	tx_data = 0x13A;
	/* Transfer data between 2 usarts */
	data_transfer();
	test_assert_true(test, tx_data == rx_data,
		"usart sync 9 bits transfer test failed");

	/* Parity error dected test */
	/* Configure transmiter parity bit as 0 but receiver parity bit as 1 */
	usart_synchronous_settings.parity_type = US_MR_PAR_SPACE;
	usart_init_sync_master(BOARD_USART_PAIR_1, &usart_synchronous_settings, cpu_hz);
	usart_synchronous_settings.parity_type = US_MR_PAR_MARK;
	usart_init_sync_slave(BOARD_USART_PAIR_2, &usart_synchronous_settings);
	/* Transfer data between 2 usarts */
	data_transfer();
	status = usart_get_status(BOARD_USART_PAIR_2);
	test_assert_true(test, (status & US_CSR_PARE),
		"usart sync parity error detected test failed");
}

/**
 * \brief Test USART write protection.
 * \param test Current test case
 */
static void run_usart_writeprotect_test(const struct test_case *test)
{
	uint32_t wp_status;
	uint32_t reg_backup;
	/* Sanity check argument. */
	Assert(test);

	/* Enable write protect */
	usart_enable_writeprotect(BOARD_USART_PAIR_1);

	/* Access US_MR to generate violation */
	reg_backup = BOARD_USART_PAIR_1->US_MR;
	BOARD_USART_PAIR_1->US_MR = 0xFF;
	
	wp_status = usart_get_writeprotect_status(BOARD_USART_PAIR_1);

	/* If status is 0, no write violation detected */
	test_assert_true(test, wp_status != 0,
		"WriteProtection on US_MR not detected");

	/* Write violation source should be US_MR */
	test_assert_true(test, wp_status == 0x4,
		"WriteProtection on US_MR src error");

	/* Write violation should be blocked */
	test_assert_true(test, reg_backup == BOARD_USART_PAIR_1->US_MR,
		"US_MR write not blocked");

	/* Disable write protect */
	usart_disable_writeprotect(BOARD_USART_PAIR_1);
}

/**
 * \brief Run USART driver unit test.
 */
int main(void)
{
	
	/* Configure UART for debug message output. */
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits   = CONF_TEST_STOPBITS
	};

	sysclk_init();
	board_init();

	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);
	cpu_hz = sysclk_get_peripheral_hz();

	/* Define all the test cases */
	DEFINE_TEST_CASE(usart_async_test, NULL, run_usart_async_test, NULL,
		"USART async mode transfer test");
	DEFINE_TEST_CASE(usart_sync_test, NULL, run_usart_sync_test, NULL,
		"USART sync mode transfer test");
	DEFINE_TEST_CASE(usart_writeprotect_test, NULL, run_usart_writeprotect_test, NULL,
		"USART write protection test");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(usart_tests) = {
		&usart_async_test,
		&usart_sync_test,
		&usart_writeprotect_test
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(usart_suite, usart_tests, "SAM USART driver test suite");

	/* Run all tests in the test suite */
	test_suite_run(&usart_suite);

	while (1) {
		/* Busy-wait forever */
	}
}
