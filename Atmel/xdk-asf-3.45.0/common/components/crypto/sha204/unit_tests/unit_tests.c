/**
 * \file
 *
 * \brief unit tests for ATSHA204 components mounted on a Security Xplained extension board
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
#include <compiler.h>
#include <stdint.h>
#include <stdbool.h>
#include <board.h>
#include <sysclk.h>
#include <string.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <wdt.h>
#include <conf_test.h>
#include <conf_atsha204.h>
#include <sha204_comm.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the \ref sha204_communication_group
 * and \ref sha204_command_marshaling_group. It tests low level TWI communication
 * and high level API functions.
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_atsha204.h
 * - \ref conf_sleepmgr.h
 * - \ref conf_twim.h
 *
 * \section device_info Device Info
 * XMEGA-128-A1 devices on board of an Xmega-A1-Xplained board
 * with a Security Xplained extension board attached can be used.
 *
 * \section description Description of the unit tests
 * See the documentation for the individual unit test functions
 * \ref unit_tests.c "here" for detailed descriptions of the tests.
 *
 * \section dependencies Dependencies
 * This example depends directly on the following modules:
 * - \ref test_suite_group
 * - \ref sha204_communication_group
 * - \ref sha204_command_marshaling_group
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for AVR. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */

static void test_sha204_wakeup(const struct test_case *test);
static void test_all_devices(const struct test_case *test);

//! Variable to keep track of test results
static bool success = false;


/**
 * \brief This function runs a SHA204 Wakeup / Sleep test.
 *
 * This test wakes up the device, reads its Wakeup response,
 * and sends a Sleep command. It then sends a command and
 * expects a response timeout to verify that the device has
 * gone to sleep.
 *
 * \param test current test case
 */
static void test_sha204_wakeup(const struct test_case *test)
{
	uint8_t sha204_status = SHA204_SUCCESS;

	// Catch watchdog timeout in case no Security Xplained board is connected.
	if ((reset_cause_get_causes() & CHIP_RESET_CAUSE_WDT) != CHIP_RESET_CAUSE_WDT) {
		reset_cause_clear_causes(CHIP_RESET_CAUSE_POR |
				CHIP_RESET_CAUSE_EXTRST |
				CHIP_RESET_CAUSE_BOD_CPU |
				CHIP_RESET_CAUSE_OCD |
				CHIP_RESET_CAUSE_SOFT | CHIP_RESET_CAUSE_SPIKE);
	} else {
		wdt_disable();
		reset_cause_clear_causes(CHIP_RESET_CAUSE_WDT);
		test_assert_false(test, sha204_status == SHA204_SUCCESS, "No Device.");
		return;
	}

	/* Start watchdog timer. */
	wdt_set_timeout_period(WDT_TIMEOUT_PERIOD_250CLK); // 250 ms
	wdt_enable();
			
	uint8_t response[DEVREV_RSP_SIZE];
	
	success = false;
	
	sha204_status = sha204c_wakeup(response);
	// The TWI_M driver is not hanging. We can disable the watchdog now.
	wdt_disable();
	test_assert_true(test, sha204_status == SHA204_SUCCESS, "Sending Wakeup token failed.");
	
	sha204_status = sha204p_sleep();
	test_assert_true(test, sha204_status == SHA204_SUCCESS, "Sending Sleep command failed.");
	
	// Make sure the device is asleep. The code below works only for TWI, not for SWI,
	// because there is no acknowledging of a TWI address for SWI.
	uint8_t command[DEVREV_COUNT] = {DEVREV_COUNT, SHA204_DEVREV, 0, 0, 0, 0x03, 0x5d};
	sha204_status = sha204p_send_command(sizeof(command), command);
	test_assert_false(test, sha204_status == SHA204_SUCCESS, "Device is not asleep.");

	success = true;
}


/**
 * \brief This function runs a SHA204 Read test on all four devices.
 *
 * This test wakes up the devices, reads their TWI addresses from
 * their Config zone, and sends them back to sleep. The test fails if
 * there are communication failures or the TWI addresses do not match.
 *
 * \param test current test case
 */
static void test_all_devices(const struct test_case *test)
{
	test_assert_true(test, success, "Previous test failed.");
	success = false;
	
	uint8_t sha204_status;
	uint8_t i;
	uint8_t twi_address;
	uint8_t twi_address_retrieved = 0;
	uint8_t command[READ_COUNT];
	uint8_t response[READ_4_RSP_SIZE];
	
	sha204_status = sha204p_wakeup();
	test_assert_true(test, sha204_status == SHA204_SUCCESS, "Sending Wakeup token failed.");

	// Address 16 holds the TWI address.
	struct sha204_read_parameters args = 
			{.tx_buffer = command, .rx_buffer = response, .zone = SHA204_ZONE_CONFIG, .address = 16};
	
	// Read TWI address from all four devices that are mounted on the Security Xplained extension board.
	for (i = 0; i < SHA204_DEVICE_COUNT; i++) {
		twi_address = sha204_i2c_address(i);
		sha204p_set_device_id(twi_address);

		memset(response, 0, sizeof(response));
		success = false;
		sha204_status = sha204m_read(&args);
		if (sha204_status != SHA204_SUCCESS)
			break;
		twi_address_retrieved = args.rx_buffer[SHA204_BUFFER_POS_DATA] & 0xFE;
		if (twi_address_retrieved != twi_address)
			break;

		sha204_status = sha204p_sleep();
		if (sha204_status != SHA204_SUCCESS)
			break;

		success = true;
	}
	// Sleep remaining devices in case one of them failed.
	for (; i < SHA204_DEVICE_COUNT; i++) {
		twi_address = sha204_i2c_address(i);
		sha204p_set_device_id(twi_address);
		sha204p_sleep();
	}	
	test_assert_true(test, sha204_status == SHA204_SUCCESS, "Communication error.");
	test_assert_true(test, twi_address_retrieved == twi_address, "TWI address does not match.");

	success = true;
}


//! \name Unit test configuration
//@{
/**
 * \def CONF_TEST_USART
 * \brief USART to redirect STDIO to
 */
/**
 * \def CONF_TEST_BAUDRATE
 * \brief Baudrate of USART
 */
/**
 * \def CONF_TEST_CHARLENGTH
 * \brief Character length (bits) of USART
 */
/**
 * \def CONF_TEST_PARITY
 * \brief Parity mode of USART
 */
/**
 * \def CONF_TEST_STOPBITS
 * \brief Stop bit configuration of USART
 */
//@}

/**
 * \brief This function runs ATSHA204 component unit tests.
 */
int main (void)
{
	const usart_serial_options_t usart_serial_options =
	{
		.baudrate     = CONF_TEST_BAUDRATE,
		.charlength   = CONF_TEST_CHARLENGTH,
		.paritytype   = CONF_TEST_PARITY,
		.stopbits     = CONF_TEST_STOPBITS,
	};

	sysclk_init();
	board_init();
	pmic_init();
	sleepmgr_init();
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	// Enable low level interrupts
	pmic_enable_level(PMIC_LVL_LOW);

	// Enable interrupt requests
	cpu_irq_enable();

	// Define all the test cases
	DEFINE_TEST_CASE(sha204_test1, NULL, test_sha204_wakeup, NULL,
			"Testing Wakeup / Sleep");

	DEFINE_TEST_CASE(sha204_test2, NULL, test_all_devices, NULL,
			"Testing all devices");

	// Put test case addresses in an array
	DEFINE_TEST_ARRAY(sha204_tests) = {
		&sha204_test1,
		&sha204_test2
	};

	// Define the test suite
	DEFINE_TEST_SUITE(sha204_suite, sha204_tests,
			"XMEGA ATSHA204 component test suite");

	// Run all tests in the test suite
	test_suite_run(&sha204_suite);

	while (1) {
		// Loop for infinity
	}
}
