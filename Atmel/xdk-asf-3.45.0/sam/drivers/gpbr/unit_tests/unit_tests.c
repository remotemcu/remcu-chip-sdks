/**
 * \file
 *
 * \brief Unit tests for GPBR driver.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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
#include "gpbr.h"
#include <string.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <conf_test.h>
#include <conf_board.h>
#include "rtt.h"
#include "supc.h"
#include "flash_efc.h"
/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the GPBR driver.
 * It consists of the following test steps:
 * - Write a value to the GPBR
 * - Enter the backup mode
 * - Wake up from the backup mode
 * - Read the GPBR register and compare
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 *
 * \section device_info Device Info
 * All SAM devices can be used.
 * This example has been tested with the following setup:
 * - sam3n4c_sam3n_ek
 * - sam3s4c_sam3s_ek
 * - sam3sd8c_sam3s_ek2
 * - sam3u4e_sam3u_ek
 * - sam3x8h_sam3x_ek
 * - sam4s16c_sam4s_ek
 * - sam4sd32c_sam4s_ek2
 * - sam4n16c_sam4n_xplained_pro
 * - sam4c16c_sam4c_ek
 * - sam4cp16b_sam4cp16bmb
 * - sam4cmp16c_sam4cmp_db
 * - sam4cms16c_sam4cms_db
 * - same70q21_same70_xplained_pro
 * - samv71q21_samv71_xplained_ultra
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
 * \def CONF_TEST_GPBR
 * \brief Test the functions provided by the GPBR driver.
 */
//@}

/** RTT wait time */
#define RTT_WAIT_TIME  2

/** Flash wait state number. */
#define FLASH_WAIT_STATE_NBR   6

/** Backup mode flag. */
#define BACKUP_MODE_FLAG             0xAA55AA55

/** Normal mode flag. */
#define NORMAL_MODE_FLAG             0xffffffff

/** GPBR unit test const written data */
#define GPBR_UNIT_TEST_CONST_DATA (0xdeadbeef)


/**
 * \brief Interrupt handler for the RTT.
 *
 * Get current RTT status.
 */
void RTT_Handler(void)
{
	uint32_t status;

	/* Get RTT status */
	status = rtt_get_status(RTT);

	/* Alarm */
	if ((status & RTT_SR_ALMS) == RTT_SR_ALMS) {
		/* Doing nothing here */
	}
}


/**
 * \brief RTT configuration function.
 *
 * Configures the RTT to generate a one second tick, which triggers
 * the RTT alarms interrupt.
 */
static void gpbr_test_configure_rtt(void)
{
	uint32_t ul_previous_time;

	/* Configure RTT for a 1 second tick interrupt */
	rtt_init(RTT, 32768);
	ul_previous_time = rtt_read_timer_value(RTT);
	while (ul_previous_time == rtt_read_timer_value(RTT));

	/* Enable RTT alarms interrupt to return from backup mode */
	NVIC_DisableIRQ(RTT_IRQn);
	NVIC_ClearPendingIRQ(RTT_IRQn);
	NVIC_SetPriority(RTT_IRQn, 0);
	NVIC_EnableIRQ(RTT_IRQn);
	rtt_enable_interrupt(RTT, RTT_MR_ALMIEN);
}

/**
 * \brief Test GPBR read/write interfaces.
 *
 * \param test Current test case.
 */
static void run_gpbr_test(const struct test_case *test)
{
	uint32_t ul_read_value = 0;
	uint32_t ul_test_page_addr = TEST_PAGE_ADDRESS;
	uint32_t *ul_back_mode_flag_addr = (uint32_t *) ul_test_page_addr;
	uint32_t ul_normal_mode_flag = NORMAL_MODE_FLAG;
	uint32_t ul_backup_mode_flag = BACKUP_MODE_FLAG;
	uint8_t uc_write_success_flag = 1;

	/* Initialize flash: 6 wait states for flash writing. */
	flash_init(FLASH_ACCESS_MODE_128, FLASH_WAIT_STATE_NBR);

	/* Unlock flash page. */
	flash_unlock(ul_test_page_addr,
			ul_test_page_addr + IFLASH_PAGE_SIZE - 1, NULL, NULL);

	if ((*ul_back_mode_flag_addr) == BACKUP_MODE_FLAG) {
		/* Read the data from GPBR0 */
		ul_read_value = gpbr_read(GPBR0);

#if (SAM4S || SAM4E || SAM4N || SAM4C || SAM4CP || SAM4CM || SAMV70 || SAMV71 || SAME70 || SAMS70)
		/* Erase flag page */
		flash_erase_page(ul_test_page_addr, IFLASH_ERASE_PAGES_8);

		/* Clear backup mode flag */
		if (flash_write(ul_test_page_addr, (uint8_t *)&ul_normal_mode_flag,
				sizeof(uint32_t), 0) != FLASH_RC_OK) {
			uc_write_success_flag = 0;
		}
#else
		/* Clear backup mode flag */
		if (flash_write(ul_test_page_addr, (uint8_t *)&ul_normal_mode_flag,
				sizeof(uint32_t), 1) != FLASH_RC_OK) {
			uc_write_success_flag = 0;
		}
#endif

		/* Return test result */
		test_assert_true(test, (ul_read_value == GPBR_UNIT_TEST_CONST_DATA)
				&& uc_write_success_flag, "Test GPBR: GPBR write error!");

		/* Clear GPBR 0 */
		gpbr_write(GPBR0, 0);

		return;
	}

	/* Write the data to the backup register 0 */
	gpbr_write(GPBR0, GPBR_UNIT_TEST_CONST_DATA);

	/* Enable RTT wake up */
	supc_set_wakeup_mode(SUPC, SUPC_WUMR_RTTEN);

	/* Configure RTT */
	gpbr_test_configure_rtt();

	/* Wait for RTT alarm event */
	rtt_write_alarm_time(RTT, RTT_WAIT_TIME);

#if (SAM4S || SAM4E || SAM4N || SAM4C || SAM4CP || SAM4CM || SAMV70 || SAMV71 || SAME70 || SAMS70)
	/* Erase flag page */
	if(flash_erase_page(ul_test_page_addr, IFLASH_ERASE_PAGES_8) != FLASH_RC_OK)
		printf("erase page failed!\r\n");

	/* Write backup mode flag */
	if (flash_write(ul_test_page_addr, (uint8_t *) & ul_backup_mode_flag,
					sizeof(uint32_t), 0) != FLASH_RC_OK) {
		/* Flag write failed, return error */
		test_assert_true(test, 0, "Test GPBR: GPBR write error!");
	}
#else
	/* Write backup mode flag */
	if (flash_write(ul_test_page_addr, (uint8_t *) & ul_backup_mode_flag,
					sizeof(uint32_t), 1) != FLASH_RC_OK) {
		/* Flag write failed, return error */
		test_assert_true(test, 0, "Test GPBR: GPBR write error!");
	}
#endif

	/* Enter backup mode */
	pmc_enable_backupmode();
#if (!(SAM4S) && !(SAM4E) && !(SAM4N) && !(SAM4C) && !(SAM4CP) && !(SAM4CM) && !(SAMV70) && !(SAMV71) && !(SAME70) && !(SAMS70))
	supc_enable_backup_mode(SUPC);
#endif

	/* We should never reach here */
	test_assert_true(test, 0, "Test GPBR: GPBR write error!");
}


/**
 * \brief Run GPBR driver unit tests
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate = CONF_TEST_BAUDRATE,
#ifdef CONF_TEST_CHAR_LENGTH
		.charlength = CONF_TEST_CHAR_LENGTH,
#endif
		.paritytype = CONF_TEST_PARITY,
#ifdef CONF_TEST_STOP_BITS
		.stopbits = CONF_TEST_STOP_BITS,
#endif
	};

	/* Initialize the system clock and board */
	sysclk_init();
	board_init();

	/* Enable the debug uart */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Define all the test cases */
	DEFINE_TEST_CASE(gpbr_test, NULL, run_gpbr_test, NULL,
			"GPBR read/write test");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(gpbr_tests) = {
	&gpbr_test};

	/* Define the test suite */
	DEFINE_TEST_SUITE(gpbr_suite, gpbr_tests, "SAM GPBR driver test suite");

	/* Run all tests in the test suite */
	test_suite_run(&gpbr_suite);

	while (1) {
		/* Busy-wait forever. */
	}
}
