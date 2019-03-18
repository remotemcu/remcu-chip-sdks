/**
 * \file
 *
 * \brief Unit tests for ICM driver.
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

#include <asf.h>
#include <conf_test.h>
#include <string.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the ICM driver.
 * It consists of test cases for the following functionality:
 * - ICM region SHA1 hash
 * - ICM region SHA224 hash
 * - ICM region SHA256 hash
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 * - \ref conf_sleepmgr.h
 *
 * \section device_info Device Info
 * SAM4C devices can be used.
 * This unit test has been tested with the following setup:
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

/* Is set to 1 when a ICM interrupt happens */
static volatile uint32_t gs_icm_triggered1 = 0U;
static volatile uint32_t gs_icm_triggered2 = 0U;
static volatile uint32_t gs_icm_triggered3 = 0U;

/* Hash area */
COMPILER_ALIGNED(128)
uint32_t output_sha[0x20];

/* Region descriptor */
COMPILER_ALIGNED(64)
struct icm_region_descriptor_main_list reg_descriptor;

/* Memory region area */
uint32_t message_sha[16] = {
	0x80636261,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x18000000
};

static void reg_hash_complete_handler(uint8_t reg_num)
{
	UNUSED(reg_num);
	if((output_sha[0] == 0x363E99A9) &&
			(output_sha[1] == 0x6A810647) &&
			(output_sha[2] == 0x71253EBA) &&
			(output_sha[3] == 0x6CC25078) &&
			(output_sha[4] == 0x9DD8D09C)) {
		gs_icm_triggered1 = 1;
	}
	if((output_sha[0] == 0x227D0923) &&
			(output_sha[1] == 0x22D80534) &&
			(output_sha[2] == 0x77A44286) &&
			(output_sha[3] == 0xB355A2BD) &&
			(output_sha[4] == 0xE4BCAD2A) &&
			(output_sha[5] == 0xF7B3A0BD) &&
			(output_sha[6] == 0xA79D6CE3)) {
		gs_icm_triggered2 = 1;
	}
	if((output_sha[0] == 0xBF1678BA) &&
			(output_sha[1] == 0xEACF018F) &&
			(output_sha[2] == 0xDE404141) &&
			(output_sha[3] == 0x2322AE5D) &&
			(output_sha[4] == 0xA36103B0) &&
			(output_sha[5] == 0x9C7A1796) &&
			(output_sha[6] == 0x61FF10B4) &&
			(output_sha[7] == 0xAD1500F2)) {
		gs_icm_triggered3 = 1;
	}
}

/**
 * \brief Test ICM
 *
 * This test sets the ICM to trigger an region hash complete interrupt.
 *
 * \param test Current test case.
 */
static void run_icm_test(const struct test_case *test)
{
	/* ICM configuration */
	struct icm_config icm_cfg;

	/* ICM initialization */
	icm_cfg.is_write_back= false;
	icm_cfg.is_dis_end_mon = false;
	icm_cfg.is_sec_list_branch = true;
	icm_cfg.bbc = 0;
	icm_cfg.is_auto_mode = false;
	icm_cfg.is_dual_buf = false;
	icm_cfg.is_user_hash = false;
	icm_cfg.ualgo = ICM_SHA_1;
	icm_cfg.hash_area_val = 0;
	icm_cfg.des_area_val = 0;
	icm_init(ICM, &icm_cfg);

	/* Set region descriptor */
	reg_descriptor.start_addr = (uint32_t)message_sha;
	reg_descriptor.cfg.is_compare_mode = false;
	reg_descriptor.cfg.is_wrap = false;
	reg_descriptor.cfg.is_end_mon = true;
	reg_descriptor.cfg.reg_hash_int_en = false;
	reg_descriptor.cfg.dig_mis_int_en = false;
	reg_descriptor.cfg.bus_err_int_en = false;
	reg_descriptor.cfg.wrap_con_int_en = false;
	reg_descriptor.cfg.ebit_con_int_en = false;
	reg_descriptor.cfg.status_upt_con_int_en = false;
	reg_descriptor.cfg.is_pro_dly = false;
	reg_descriptor.cfg.mem_reg_val = 0;
	reg_descriptor.cfg.algo = ICM_SHA_1;
	reg_descriptor.tran_size = 0;
	reg_descriptor.next_addr = 0;

	/* Set region descriptor start addres */
	icm_set_reg_des_addr(ICM, (uint32_t)&reg_descriptor);

	/* Set hash area start addres */
	icm_set_hash_area_addr(ICM, (uint32_t)output_sha);

	/* Set callback function for region hash complete interrupt handler */
	icm_set_callback(ICM, reg_hash_complete_handler,
			ICM_REGION_NUM_0, ICM_INTERRUPT_RHC, 1);

	/* Enable ICM */
	icm_enable(ICM);

	delay_ms(50);
	test_assert_true(test, gs_icm_triggered1 == 1, "Test1: SHA1 hash not complete!");

	reg_descriptor.cfg.algo = ICM_SHA_224;
	/* Enable ICM */
	icm_enable(ICM);

	delay_ms(50);
	test_assert_true(test, gs_icm_triggered2 == 1, "Test2: SHA224 hash not complete!");

	reg_descriptor.cfg.algo = ICM_SHA_256;
	/* Enable ICM */
	icm_enable(ICM);

	delay_ms(50);
	test_assert_true(test, gs_icm_triggered3 == 1, "Test3: SHA256 hash not complete!");
}

/**
 * \brief Run ICM driver unit tests
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
#ifdef CONF_UART_CHAR_LENGTH
		.charlength = CONF_UART_CHAR_LENGTH,
#endif
		.paritytype = CONF_TEST_PARITY,
#ifdef CONF_UART_STOP_BITS
		.stopbits = CONF_UART_STOP_BITS,
#endif
	};

	sysclk_init();
	board_init();

	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Define all the test cases */
	DEFINE_TEST_CASE(icm_test, NULL, run_icm_test, NULL,
		"ICM init, region hash");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(icm_tests) = {
		&icm_test,
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(icm_suite, icm_tests, "SAM ICM driver test suite");

	/* Run all tests in the test suite */
	test_suite_run(&icm_suite);

	while (1) {
		/* Busy-wait forever. */
	}
}
