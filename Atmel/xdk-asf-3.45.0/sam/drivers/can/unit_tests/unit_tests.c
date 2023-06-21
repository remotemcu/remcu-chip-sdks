/**
 * \file
 *
 * \brief Unit tests for CAN driver.
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

#include <stdint.h>
#include <stdbool.h>
#include <board.h>
#include <sysclk.h>
#include <can.h>
#include <sn65hvd234.h>
#include <string.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <conf_test.h>
#include <conf_board.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the CAN driver.
 * It contains only one test case for the CAN module:
 * - CAN0 mailbox 0 & 1 communicate with CAN1 mailbox 0
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_uart_serial.h
 *
 * \section device_info Device Info
 * SAM3X or SAM4E devices can be used.
 * This example has been tested with the following setup:
 * - sam3x8h_sam3x_ek
 * - sam4e16e_sam4e_ek
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
 * \def CONF_TEST_CAN
 * \brief Use mailbox of CAN0 and CAN1 to communicate with each other.
 */
//@}

/** The data transfer between the CAN0 and CAN1 */
#define TRANSFER_DATA_LOW             0x12345678
#define TRANSFER_DATA_HIGH            0x87654321

/** The CAN1 communication mailbox ID */
#define CAN1_PRO_MB_IDX               0

/** The CAN0 communication mailbox ID */
#define CAN0_TX_MB_IDX                0
#define CAN0_RX_MB_IDX                1

/** The transfer identifier */
#define CAN_TRANSFER_ID               0x0a

/** The transfer data length */
#define CAN_TRANSFER_DATA_LEN         8

/** CAN0 Transceiver */
sn65hvd234_ctrl_t can0_transceiver;

/** CAN1 Transceiver */
sn65hvd234_ctrl_t can1_transceiver;

/** CAN0 Transfer */
can_mb_conf_t can0_mailbox;

/** CAN1 Transfer */
can_mb_conf_t can1_mailbox;

/** Receive status */
volatile uint32_t g_ul_recv_status = 0;

/**
 * \brief Default interrupt handler for CAN0.
 */
void CAN0_Handler(void)
{
	uint32_t ul_status;

	ul_status = can_get_status(CAN0);
	if (ul_status & GLOBAL_MAILBOX_MASK) {
		ul_status = can_mailbox_get_status(CAN0, CAN0_RX_MB_IDX);
		if ((ul_status & CAN_MSR_MRDY) == CAN_MSR_MRDY) {
			can0_mailbox.ul_mb_idx = CAN0_RX_MB_IDX;
			can0_mailbox.ul_status = ul_status;
			can_mailbox_read(CAN0, &can0_mailbox);
			g_ul_recv_status = 1;
		}
	}
}

/**
 * \brief Reset mailbox configure structure.
 *
 *  \param p_mailbox Pointer to mailbox configure structure.
 */
static void reset_mailbox_conf(can_mb_conf_t *p_mailbox)
{
	p_mailbox->ul_mb_idx = 0;
	p_mailbox->uc_obj_type = 0;
	p_mailbox->uc_id_ver = 0;
	p_mailbox->uc_length = 0;
	p_mailbox->uc_tx_prio = 0;
	p_mailbox->ul_status = 0;
	p_mailbox->ul_id_msk = 0;
	p_mailbox->ul_id = 0;
	p_mailbox->ul_fid = 0;
	p_mailbox->ul_datal = 0;
	p_mailbox->ul_datah = 0;
}

/**
 * \brief Test Controller Area Network (CAN) Controller.
 *
 * This test checks whether the transmitted and received data are consistent.
 *
 * \param test Current test case.
 */
static void run_can_test(const struct test_case *test)
{
	uint32_t ul_sysclk;
	
	/* Initialize CAN0 Transceiver */
	sn65hvd234_set_rs(&can0_transceiver, PIN_CAN0_TR_RS_IDX);
	sn65hvd234_set_en(&can0_transceiver, PIN_CAN0_TR_EN_IDX);
	/* Enable CAN0 Transceiver */
	sn65hvd234_disable_low_power(&can0_transceiver);
	sn65hvd234_enable(&can0_transceiver);

	/* Initialize CAN1 Transceiver */
	sn65hvd234_set_rs(&can1_transceiver, PIN_CAN1_TR_RS_IDX);
	sn65hvd234_set_en(&can1_transceiver, PIN_CAN1_TR_EN_IDX);
	/* Enable CAN1 Transceiver */
	sn65hvd234_disable_low_power(&can1_transceiver);
	sn65hvd234_enable(&can1_transceiver);

	/* Enable CAN0 & CAN1 clock */
	pmc_enable_periph_clk(ID_CAN0);
	pmc_enable_periph_clk(ID_CAN1);

	ul_sysclk = sysclk_get_cpu_hz();
	if (can_init(CAN0, ul_sysclk, CAN_BPS_1000K) &&
		can_init(CAN1, ul_sysclk, CAN_BPS_1000K)) {
		
		/* Disable all CAN0 & CAN1 interrupts */
		can_disable_interrupt(CAN0, CAN_DISABLE_ALL_INTERRUPT_MASK);
		can_disable_interrupt(CAN1, CAN_DISABLE_ALL_INTERRUPT_MASK);

		/* Configure and enable interrupt of CAN1, as the tests will use receiver interrupt. */
		NVIC_EnableIRQ(CAN0_IRQn);

		/* Reset all the mailboxes of CAN0 and CAN1 for the following communication. */
		can_reset_all_mailbox(CAN0);
		can_reset_all_mailbox(CAN1);
		
		/* Init CAN1 Mailbox 0 to Producer Mailbox. */
		reset_mailbox_conf(&can1_mailbox);
		can1_mailbox.ul_mb_idx = CAN1_PRO_MB_IDX;
		can1_mailbox.uc_obj_type = CAN_MB_PRODUCER_MODE;
		can1_mailbox.ul_id_msk = 0;
		can1_mailbox.ul_id = CAN_MID_MIDvA(CAN_TRANSFER_ID);
		can_mailbox_init(CAN1, &can1_mailbox);
	
		/* Prepare the response information when it receives a remote frame. */
		can1_mailbox.ul_datal = TRANSFER_DATA_LOW;
		can1_mailbox.ul_datah = TRANSFER_DATA_HIGH;
		can1_mailbox.uc_length = CAN_TRANSFER_DATA_LEN;
		can_mailbox_write(CAN1, &can1_mailbox);
	
		can_global_send_transfer_cmd(CAN1, CAN_TCR_MB0);

		/* Init CAN0 Mailbox 1 to Receive Mailbox. */
		reset_mailbox_conf(&can0_mailbox);
		can0_mailbox.ul_mb_idx = CAN0_RX_MB_IDX;
		can0_mailbox.uc_obj_type = CAN_MB_RX_MODE;
		can0_mailbox.ul_id_msk = CAN_MID_MIDvA_Msk | CAN_MID_MIDvB_Msk;
		can0_mailbox.ul_id = CAN_MID_MIDvA(CAN_TRANSFER_ID);
		can_mailbox_init(CAN0, &can0_mailbox);

		/* Init CAN0 Mailbox 0 to Transmit Mailbox, and send out a remote frame. */
		reset_mailbox_conf(&can0_mailbox);
		can0_mailbox.ul_mb_idx = CAN0_TX_MB_IDX;
		can0_mailbox.uc_obj_type = CAN_MB_TX_MODE;
		can0_mailbox.uc_tx_prio = 0;
		can0_mailbox.uc_id_ver = 0;
		can0_mailbox.ul_id_msk = 0;
		can0_mailbox.ul_id = CAN_MID_MIDvA(CAN_TRANSFER_ID);
		can_mailbox_init(CAN0, &can0_mailbox);
		
		/* Enable CAN0 mailbox 1 interrupt. */
		can_enable_interrupt(CAN0, CAN_IER_MB1);

		/* Use CAN0 mailbox 0 to send out a remote frame to CAN1 mailbox 0. 
		 * CAN1 mailbox 0 in Producer mode will respond the remote frame, and 
		 * send out one data frame. CAN0 mailbox 1 will receive the message. 
		*/
		can_mailbox_tx_remote_frame(CAN0, &can0_mailbox);
		
		while (!g_ul_recv_status) {
		}
		
		/* Disable CAN0 Controller */
		can_disable(CAN0);
		/* Disable CAN0 Transceiver */
		sn65hvd234_enable_low_power(&can0_transceiver);
		sn65hvd234_disable(&can0_transceiver);

		/* Disable CAN1 Controller */
		can_disable(CAN1);
		/* Disable CAN1 Transceiver */
		sn65hvd234_enable_low_power(&can1_transceiver);
		sn65hvd234_disable(&can1_transceiver);
		
		/* Check the data received by the CAN0 mailbox 1. */
		test_assert_true(test, ((can0_mailbox.ul_datal == TRANSFER_DATA_LOW) &&
			(can0_mailbox.ul_datah == TRANSFER_DATA_HIGH)),
			"Test: CAN communication failed!");
	}
}

/**
 * \brief Run RSTC driver unit tests.
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate = CONF_TEST_BAUDRATE,
		.paritytype = CONF_TEST_PARITY
	};

	sysclk_init();
	board_init();

	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Define all the test cases. */
	DEFINE_TEST_CASE(can_test, NULL, run_can_test, NULL,
			"Controller Area Network, check the transmit and receive data.");

	/* Put test case addresses in an array. */
	DEFINE_TEST_ARRAY(can_tests) = {
	&can_test,};

	/* Define the test suite. */
	DEFINE_TEST_SUITE(can_suite, can_tests, "SAM CAN driver test suite");

	/* Run all tests in the test suite. */
	test_suite_run(&can_suite);

	while (1) {
		/* Busy-wait forever. */
	}
}
