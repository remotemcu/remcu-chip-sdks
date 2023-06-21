/**
 * \file
 *
 * \brief Unit tests for SDRAMC driver.
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

#include <board.h>
#include <sysclk.h>
#include "sdramc.h"
#include <string.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <conf_test.h>
#include <conf_board.h>
#include "mt48lc16m16a2.h"

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the SDRAMC driver.
 * It consists of test cases for the following functionality:
 * - Write a value to the SDRAMC
 * - Read the written data and compare
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 *
 * \section device_info Device Info
 * The SAM3X devices can be used.
 * This example has been tested with the following setup:
 * - sam3x8h_sam3x_ek
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for ARM. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */

//! \name Unit test configuration
//@{
/**
 * \def CONF_TEST_SDRAMC
 * \brief Test the functions provided by the SDRAMC driver.
 */
//@}

/** SDRAMC uint test const written data */
#define SDRAMC_UNIT_TEST_CONST_WRITE_DATA (0xA55A5AA5)

/** SDRAMC uint test const read data */
#define SDRAMC_UNIT_TEST_CONST_READ_DATA (0x5AA5A55A)

/* SDRAMC address line length */
#define SDRAMC_ADDR_LINE_LENGTH        16

/**
 * \brief Test SDRAMC initialize interface, through SDRAMC read/write access.
 *
 * \param test Current test case.
 */
static void run_sdramc_test(const struct test_case *test)
{
	uint32_t ul;
	uint32_t *pul = (uint32_t *)BOARD_SDRAM_ADDR;

	/* Enable SMC peripheral clock */
	pmc_enable_periph_clk(ID_SMC);

	/* Complete SDRAM configuration */
	sdramc_init((sdramc_memory_dev_t *)&SDRAM_MICRON_MT48LC16M16A2,
			sysclk_get_cpu_hz());

	for (ul = 0; ul < SDRAMC_ADDR_LINE_LENGTH; ++ul) {
		pul[1 << ul] = SDRAMC_UNIT_TEST_CONST_WRITE_DATA;
	}

	for (ul = 0; ul < SDRAMC_ADDR_LINE_LENGTH; ++ul) {
		test_assert_true(test,
				pul[1 << ul] == SDRAMC_UNIT_TEST_CONST_WRITE_DATA,
				"SDRAMC write test failed");
	}

	for (ul = 0; ul < SDRAMC_ADDR_LINE_LENGTH; ++ul) {
		pul[1 << ul] = SDRAMC_UNIT_TEST_CONST_READ_DATA;
	}

	for (ul = 0; ul < SDRAMC_ADDR_LINE_LENGTH; ++ul) {
		test_assert_true(test,
				pul[1 << ul] == SDRAMC_UNIT_TEST_CONST_READ_DATA,
				"SDRAMC read test failed");
	}
}

/**
 * \brief Run SDRAMC driver unit tests.
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate = CONF_TEST_BAUDRATE,
		.paritytype = CONF_TEST_PARITY
	};

	/* Initialize the system clock and board */
	sysclk_init();
	board_init();

	/* Enable the debug uart */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_TEST_UART, &usart_serial_options);

#if defined(__GNUC__)
	setbuf(stdout, NULL);
#endif

	/* Define all the test cases */
	DEFINE_TEST_CASE(sdramc_test, NULL, run_sdramc_test, NULL,
			"SDRAMC read/write test");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(sdramc_tests) = {
		&sdramc_test
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(sdramc_suite, sdramc_tests,
			"SAM SDRAMC driver test suite");

	/* Run all tests in the test suite */
	test_suite_run(&sdramc_suite);

	while (1) {
		/* Busy-wait forever. */
	}
}
