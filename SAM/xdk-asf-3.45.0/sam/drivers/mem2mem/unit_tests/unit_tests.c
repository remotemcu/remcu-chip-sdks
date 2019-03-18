/**
 * \file
 *
 * \brief Unit tests for MEM2MEM driver.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <board.h>
#include <sysclk.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <conf_test.h>
#include <conf_board.h>
#include "mem2mem.h"

/**
 * \mainpage Unit-tests for MEM2MEM driver
 *
 * \section intro Introduction
 * This is the unit test application for the MEM2MEM driver.
 * It consists of test cases for the following functionalities:
 * - Memory-to-memory transfer by low level APIs
 * - Mmeory-to-memory transfer by M2M driver APIs
 *   - Callback disabled transfer
 *   - Callback enabled transfer
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 *
 * \section device_info Device Info
 * SAM devices with MEM2MEM peripheral can be used.
 * This example has been tested with the following setup:
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
 * \def CONF_TEST_UART
 * \brief UART to redirect STDIO
 */
/**
 * \def CONF_TEST_BAUDRATE
 * \brief Baudrate of UART
 */
/**
 * \def CONF_TEST_PARITY
 * \brief Parity mode of UART
 */
//@}

/* Test memory size (two buffer) */
#define MEM_SIZE32 (512 * 2)
#define MEM_SIZE16 (MEM_SIZE32*2)
#define MEM_SIZE8  (MEM_SIZE32*4)

/* Count for buffer done callback */
static volatile uint32_t _buffer_done_cnt = 0;
/* Buffer append status */
static volatile bool _buffer_append_ok = false;
/* Flag for transfer done callback */
static volatile bool _transfer_is_done = false;

/* Source memory block */
static uint32_t  src_mem32[MEM_SIZE32];
static uint8_t  *src_mem8  = (uint8_t*)src_mem32;

/* Destination memory block */
static uint32_t  dst_mem32[MEM_SIZE32];
static uint8_t  *dst_mem8  = (uint8_t*)dst_mem32;

/* M2M driver module isntance */
static struct m2m_module _m2m;
/* M2M driver configurations */
static struct m2m_config _m2m_cfg;

/**
 * \brief Transfer done callback
 * \param m2m Pointer to M2M driver module instance
 */
static void _transfer_done(const struct m2m_module *const m2m)
{
	UNUSED(m2m);
	_transfer_is_done = true;
}

/**
 * \brief Buffer done callback
 * \param inst Pointer to M2M driver module instance
 */
static void _buffer_done(const struct m2m_module *const inst)
{
	enum status_code status;
	_buffer_done_cnt ++;
	if (1 >= _buffer_done_cnt) {
		/* Append buffer once */
		status =
		m2m_transfer_job((struct m2m_module *)inst,
				&src_mem8[MEM_SIZE8/2], &dst_mem8[MEM_SIZE8/2],
				MEM_SIZE8/2);
		_buffer_append_ok = (status == STATUS_OK);
	}
}

/**
 * \brief Verify data byte by byte
 * \return true if verify OK.
 */
static bool _verify_data(void)
{
	uint32_t i;
	for (i = 0; i < MEM_SIZE8; i ++) {
		if (src_mem8[i] != dst_mem8[i]) {
			return false;
		}
	}
	return true;
}

/**
 * \brief Memory-to-memory transfer through low level APIs
 * \param test Current test case.
 */
static void run_low_level_transfer_test(const struct test_case *test)
{
	/* Reset test buffer */
	memset(dst_mem8, 0x00, MEM_SIZE8);
	/* Low level transfer (wait) test */
	sysclk_enable_peripheral_clock(ID_MEM2MEM);
	mem2mem_set_transfer_size(MEM2MEM, MEM2MEM_TRANSFER_DWORD);
	mem2mem_transfer_set(MEM2MEM, src_mem8, dst_mem8,
			MEM_SIZE32);
	mem2mem_transfer_enable(MEM2MEM);
	/* Wait all transfer done */
	while (!(mem2mem_get_status(MEM2MEM) & MEM2MEM_ISR_RXBUFF));
	test_assert_true(test, _verify_data(), "low level transfer test fail");
}

/**
 * \brief Memory-to-memory transfer through M2M driver without callback
 * \param test Current test case.
 */
static void run_transfer_wait_test(const struct test_case *test)
{
	enum status_code status;
	/* Reset test buffer */
	memset(dst_mem8, 0x00, MEM_SIZE8);
	/* M2M driver transfer (wait) test */
	m2m_get_config_default(&_m2m_cfg);

	_m2m_cfg.transfer_size = MEM2MEM_TRANSFER_WORD;
	status = m2m_init(&_m2m, MEM2MEM, &_m2m_cfg);
	test_assert_true(test, ERR_BUSY == status,
			"M2M Initialize error fail, status %x", status);

	mem2mem_transfer_disable(MEM2MEM);
	status = m2m_init(&_m2m, MEM2MEM, &_m2m_cfg);
	test_assert_true(test, STATUS_OK == status,
			"M2M Initialize fail, status %x", status);

	status = m2m_transfer_wait(&_m2m, src_mem8, dst_mem8, MEM_SIZE16);
	test_assert_true(test, STATUS_OK == status,
			"M2M transfer wait fail, status %x", status);
	test_assert_true(test, _verify_data(), "M2M transfer wait data error");
}

/**
 * \brief Memory-to-memory transfer through M2M driver with callback
 * \param test Current test case.
 */
static void run_transfer_job_test(const struct test_case *test)
{
	enum status_code status;
	/* Reset test buffer */
	memset(dst_mem8, 0x00, MEM_SIZE8);
	/* M2M driver transfer (job) test */

	_m2m_cfg.transfer_size = MEM2MEM_TRANSFER_BYTE;
	status = m2m_set_config(&_m2m, &_m2m_cfg);
	test_assert_true(test, status == STATUS_OK,
			"M2M Configuration fail, status %x", status);

	m2m_register_callback(&_m2m, _buffer_done, M2M_CALLBACK_BUFFER_END),
	m2m_enable_callback(&_m2m, M2M_CALLBACK_BUFFER_END);
	m2m_register_callback(&_m2m, _transfer_done, M2M_CALLBACK_TRANSFER_END);
	m2m_enable_callback(&_m2m, M2M_CALLBACK_TRANSFER_END);

	_transfer_is_done = false;
	status = m2m_transfer_job(&_m2m, src_mem8, dst_mem8, MEM_SIZE8/2);
	test_assert_true(test, status == STATUS_OK,
			"M2M Job start fail, status %x", status);
	while(!_transfer_is_done);
	test_assert_true(test, _buffer_append_ok,
			"M2M Job appending fail");
	test_assert_true(test, _buffer_done_cnt == 2,
			"M2M Buffer count error, %d", (int)_buffer_done_cnt);
	test_assert_true(test, _verify_data(), "M2M transfer job data error");
}

/**
 * \brief Run MEM2MEM driver unit tests.
 */
int main(void)
{
	uint32_t i;
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_TEST_BAUDRATE,
		.paritytype = CONF_TEST_PARITY
	};

	/* Initialize the system. */
	sysclk_init();
	board_init();

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_TEST_UART, &uart_serial_options);

	/* Initialize src buffer */
	for (i = 0; i < MEM_SIZE8/2; i ++) {
		src_mem8[i] = (i % 10) + '0';
	}
	for (;i < MEM_SIZE8; i ++) {
		src_mem8[i] = (i % ('z'-'a')) + 'a';
	}

	/* Define all the test cases */
	DEFINE_TEST_CASE(low_level_test, NULL, run_low_level_transfer_test,
			NULL, "Low Level APIs data transfer test");
	DEFINE_TEST_CASE(transfer_wait_test, NULL, run_transfer_wait_test,
			NULL, "M2M APIs data transfer wait test");
	DEFINE_TEST_CASE(transfer_job_test, NULL, run_transfer_job_test,
			NULL, "M2M APIs data transfer job test");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(mem2mem_tests) = {
		&low_level_test,
		&transfer_wait_test,
		&transfer_job_test
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(mem2mem_suite, mem2mem_tests,
			"SAM MEM2MEM driver test suite");

	/* Run all tests in the test suite */
	test_suite_run(&mem2mem_suite);

	while (1) {
		/* Busy-wait forever */
	}
}
