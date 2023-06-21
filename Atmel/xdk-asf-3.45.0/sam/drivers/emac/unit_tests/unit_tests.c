/**
 * \file
 *
 * \brief Unit tests for EMAC driver.
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

#include "board.h"
#include <sysclk.h>
#include "emac.h"
#include <string.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include "conf_test.h"
#include "conf_board.h"
#include "mini_ip.h"
#include "rstc.h"
#include "ethernet_phy.h"

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the EMAC driver.
 * It consists of test cases for the following functionalities:
 * - Write an arp frame through the EMAC
 * - Read the EMAC buffer and check if the frame sent is received
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
 * \def CONF_TEST_EMAC
 * \brief Test the functions provided by the EMAC driver.
 */
//@}

/** The EMAC driver instance */
static emac_device_t gs_emac_dev;

/** Buffer for ethernet packets */
static uint8_t gs_uc_eth_buffer[EMAC_FRAME_LENTGH_MAX];

static uint8_t gs_arp_frame[] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	ETHERNET_CONF_ETHADDR0, ETHERNET_CONF_ETHADDR1, ETHERNET_CONF_ETHADDR2,
	ETHERNET_CONF_ETHADDR3, ETHERNET_CONF_ETHADDR4,
	ETHERNET_CONF_ETHADDR5, 0x08, 0x06, 0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00, 0x01,
	ETHERNET_CONF_ETHADDR0, ETHERNET_CONF_ETHADDR1, ETHERNET_CONF_ETHADDR2,
	ETHERNET_CONF_ETHADDR3, ETHERNET_CONF_ETHADDR4,
	ETHERNET_CONF_ETHADDR5,
	ETHERNET_CONF_IPADDR0, ETHERNET_CONF_IPADDR1, ETHERNET_CONF_IPADDR2,
	ETHERNET_CONF_IPADDR3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	ETHERNET_CONF_GATEWAY_ADDR0, ETHERNET_CONF_GATEWAY_ADDR1,
	ETHERNET_CONF_GATEWAY_ADDR2, ETHERNET_CONF_GATEWAY_ADDR3
};

/** The MAC address used for the test */
static uint8_t gs_uc_mac_address[] =
		{ ETHERNET_CONF_ETHADDR0, ETHERNET_CONF_ETHADDR1, ETHERNET_CONF_ETHADDR2,
			ETHERNET_CONF_ETHADDR3, ETHERNET_CONF_ETHADDR4, ETHERNET_CONF_ETHADDR5
};

#define EMAC_UINT_TEST_MAX_RETRY_TIME    50

/**
 * \brief EMAC interrupt handler.
 */
void EMAC_Handler(void)
{
	emac_handler(&gs_emac_dev);
}

/**
 * \brief EMAC link test function.
 *
 * \param test Current test case.
 */
static void run_emac_link_test(const struct test_case *test)
{
	volatile uint32_t ul_delay;
	emac_options_t emac_option;
	uint8_t uc_rc = 1;

	/* Reset PHY */
	rstc_set_external_reset(RSTC, 13);	/* (2^(13+1))/32768 */
	rstc_reset_extern(RSTC);
	while (rstc_get_status(RSTC) & RSTC_SR_NRSTL) {
	};
	rstc_set_external_reset(RSTC, 0);       /* restore default */

	/* Wait for PHY to be ready (CAT811: Max400ms) */
	ul_delay = sysclk_get_cpu_hz() / 1000 / 3 * 400;
	while (ul_delay--);

	/* Enable EMAC clock */
	pmc_enable_periph_clk(ID_EMAC);

	/* Fill in EMAC options */
	emac_option.uc_copy_all_frame = 1;
	emac_option.uc_no_boardcast = 1;

	memcpy(emac_option.uc_mac_addr, gs_uc_mac_address, sizeof(gs_uc_mac_address));

	gs_emac_dev.p_hw = EMAC;

	/* Init EMAC driver structure */
	emac_dev_init(EMAC, &gs_emac_dev, &emac_option);

	/* Enable Interrupt */
	NVIC_EnableIRQ(EMAC_IRQn);

	/* Init MAC PHY driver */
	if (ethernet_phy_init(EMAC, BOARD_EMAC_PHY_ADDR, sysclk_get_cpu_hz())
			!= EMAC_OK) {
		uc_rc = 0;
	}

	/* Auto Negotiate, work in RMII mode */
	if (ethernet_phy_auto_negotiate(EMAC, BOARD_EMAC_PHY_ADDR) != EMAC_OK) {
		uc_rc = 0;

	}

	/* Establish ethernet link */
	while (ethernet_phy_set_link(EMAC, BOARD_EMAC_PHY_ADDR, 1) != EMAC_OK) {
		uc_rc = 0;
	}

	test_assert_true(test, uc_rc == 1, "Test EMAC: EMAC link test error!");
}

/**
 * \brief Test EMAC read/write interfaces.
 *
 * \param test Current test case.
 */
static void run_emac_read_write_test(const struct test_case *test)
{
	uint32_t ul_frm_size;
	uint8_t uc_rc = 0;
	uint32_t ul_retry_time = 0;

	/* Write the arp frame first */
	emac_dev_write(&gs_emac_dev, gs_arp_frame, sizeof(gs_arp_frame), NULL);

	while ( ul_retry_time < EMAC_UINT_TEST_MAX_RETRY_TIME ) {
		/* Read the frame in the emac buffer */
		if (EMAC_OK != emac_dev_read(&gs_emac_dev, (uint8_t *) gs_uc_eth_buffer,
						sizeof(gs_uc_eth_buffer), &ul_frm_size)) {
			continue;
		}	

		/* Is arp frame sent? */
		if (strncmp((const char *)gs_uc_eth_buffer, (const char *)gs_uc_mac_address, sizeof(gs_uc_mac_address))) {
			uc_rc = 1;
			break;
		}

		ul_retry_time++;
	}

	test_assert_true(test, uc_rc == 1, "Test EMAC: emac write error!");
}

/**
 * \brief Run EMAC driver unit tests.
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
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Define all the test cases */
	DEFINE_TEST_CASE(emac_link_test, NULL, run_emac_link_test, NULL,
			"EMAC link test");

	/* Define all the test cases */
	DEFINE_TEST_CASE(emac_rw_test, NULL, run_emac_read_write_test, NULL,
			"EMAC read/write test");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(emac_tests) = {
	&emac_link_test,
	&emac_rw_test};

	/* Define the test suite */
	DEFINE_TEST_SUITE(emac_suite, emac_tests, "SAM EMAC driver test suite");

	/* Run all tests in the test suite */
	test_suite_run(&emac_suite);

	while (1) {
		/* Busy-wait forever */
	}
}
