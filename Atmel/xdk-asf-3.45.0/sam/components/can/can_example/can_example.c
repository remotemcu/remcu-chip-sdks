/**
 * \file
 *
 * \brief CAN example for SAM.
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

/**
 *  \mainpage CAN example
 *
 *  \par Purpose
 *
 *  This example demonstrates the basic functions of CAN controller.
 *
 *  \par Requirements
 *
 *  This package can be used with SAM3X or SAM4E evaluation kits.
 *  CAN0 and CAN1 should be hooked-up externally before running
 *  the example.
 *
 *  \par Description
 *
 *  In this example, it sends and receives messages over CAN bus to manage
 *  the LED on the board and display CAN message on the terminal window.
 *  There are four basic tests:
 *  - test1: Test the transmission from CAN0 Mailbox 0 to CAN1 Mailbox 0.
 *  - test2: Test the transmission from CAN0 Mailboxes 1 & 2 to CAN1 Mailbox 7
 *    without overwrite.
 *  - test3: Test the transmission from CAN0 Mailboxes 1 & 2 to CAN1 Mailbox 7
 *    with overwrite.
 *  - test4: Test the communication between CAN1 Mailbox 3 and CAN0 Mailbox 3.
 *
 *  \par Usage
 *
 *  -# Build the program and download it into the evaluation board.
 *  -# On the computer, open and configure a terminal application
 *     (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *    - 115200 bauds
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# Connect CAN0 (J17 on SAM3X-EK or J13 on SAM4E-EK) and CAN1 (J20
 *     on SAM3X-EK or J14 on SAM4E-EK) in loop.
 *  -# Start the application.
 *  -# Upon startup, the application will output the following lines
 *     on the terminal window.
 *      \code
	-- CAN Example --
	-- SAMxx-EK --
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 *  -# Press a key in the terminal window to run the tests. CAN messages
 *     will be displayed on the terminal window and LED0 or LED1 will toggle
 *     according to the messages.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <stdio.h>
#include <string.h>
#include "board.h"
#include "sysclk.h"
#include "exceptions.h"
#include "uart.h"
#include "pmc.h"
#include "ioport.h"
#include "can.h"
#include "stdio_serial.h"
#include "sn65hvd234.h"
#include "conf_board.h"
#include "conf_clock.h"

#define STRING_EOL    "\r"

#define STRING_HEADER "-- CAN Example --\r\n" \
                      "-- "BOARD_NAME" --\r\n" \
                      "-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

#define CAN_MSG_TOGGLE_LED_0        0x11223344
#define CAN_MSG_TOGGLE_LED_1        0xAABBCCDD
#define CAN_MSG_DUMMY_DATA          0x55AAAA55

/** CAN frame max data length */
#define MAX_CAN_FRAME_DATA_LEN      8

/** CAN0 Transceiver */
sn65hvd234_ctrl_t can0_transceiver;

/** CAN1 Transceiver */
sn65hvd234_ctrl_t can1_transceiver;

/** CAN0 Transfer mailbox structure */
can_mb_conf_t can0_mailbox;

/** CAN1 Transfer mailbox structure */
can_mb_conf_t can1_mailbox;

/** Receive status */
volatile uint32_t g_ul_recv_status = 0;

/**
 * \brief Default interrupt handler for CAN 1.
 */
void CAN1_Handler(void)
{
	uint32_t ul_status;

	ul_status = can_get_status(CAN1);
	if (ul_status & GLOBAL_MAILBOX_MASK) {
		for (uint8_t i = 0; i < CANMB_NUMBER; i++) {
			ul_status = can_mailbox_get_status(CAN1, i);
			if ((ul_status & CAN_MSR_MRDY) == CAN_MSR_MRDY) {
				can1_mailbox.ul_mb_idx = i;
				can1_mailbox.ul_status = ul_status;
				can_mailbox_read(CAN1, &can1_mailbox);
				g_ul_recv_status = 1;
				break;
			}
		}
	}
}

/**
 * \brief Decode CAN messages.
 *
 *  \param p_mailbox Pointer to CAN Mailbox structure.
 */
static void decode_can_msg(can_mb_conf_t *p_mailbox)
{
	uint32_t ul_led_Ctrl = p_mailbox->ul_datal;

	puts("CAN message:" STRING_EOL);
	if (ul_led_Ctrl == CAN_MSG_TOGGLE_LED_0) {
		puts("  Toggle LED 0" STRING_EOL);
		ioport_toggle_pin_level(LED0_GPIO);
	} else if (ul_led_Ctrl == CAN_MSG_TOGGLE_LED_1) {
		puts("  Toggle LED 1" STRING_EOL);
		ioport_toggle_pin_level(LED1_GPIO);
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

#define TEST1_CAN_COMM_MB_IDX    0
#define TEST1_CAN_TRANSFER_ID    0x07
#define TEST1_CAN0_TX_PRIO       15
/**
 *  \brief Test the transmission from CAN0 Mailbox 0 to CAN1 Mailbox 0.
 */
static void test_1(void)
{
	can_reset_all_mailbox(CAN0);
	can_reset_all_mailbox(CAN1);

	puts("\n\rTest1: CAN0 Mailbox 0 transmitting to CAN1 Mailbox 0" STRING_EOL);

	/* Init CAN1 Mailbox 0 to Reception Mailbox. */
	reset_mailbox_conf(&can1_mailbox);
	can1_mailbox.ul_mb_idx = TEST1_CAN_COMM_MB_IDX;
	can1_mailbox.uc_obj_type = CAN_MB_RX_MODE;
	can1_mailbox.ul_id_msk = CAN_MAM_MIDvA_Msk | CAN_MAM_MIDvB_Msk;
	can1_mailbox.ul_id = CAN_MID_MIDvA(TEST1_CAN_TRANSFER_ID);
	can_mailbox_init(CAN1, &can1_mailbox);

	/* Init CAN0 Mailbox 0 to Transmit Mailbox. */
	reset_mailbox_conf(&can0_mailbox);
	can0_mailbox.ul_mb_idx = TEST1_CAN_COMM_MB_IDX;
	can0_mailbox.uc_obj_type = CAN_MB_TX_MODE;
	can0_mailbox.uc_tx_prio = TEST1_CAN0_TX_PRIO;
	can0_mailbox.uc_id_ver = 0;
	can0_mailbox.ul_id_msk = 0;
	can_mailbox_init(CAN0, &can0_mailbox);

	/* Write transmit information into mailbox. */
	can0_mailbox.ul_id = CAN_MID_MIDvA(TEST1_CAN_TRANSFER_ID);
	can0_mailbox.ul_datal = CAN_MSG_TOGGLE_LED_0;
	can0_mailbox.ul_datah = CAN_MSG_DUMMY_DATA;
	can0_mailbox.uc_length = MAX_CAN_FRAME_DATA_LEN;
	can_mailbox_write(CAN0, &can0_mailbox);

	/* Enable CAN1 mailbox 0 interrupt. */
	can_enable_interrupt(CAN1, CAN_IER_MB0);

	/* Send out the information in the mailbox. */
	can_global_send_transfer_cmd(CAN0, CAN_TCR_MB0);

	while (!g_ul_recv_status) {
	}

	if ((can1_mailbox.ul_datal == CAN_MSG_TOGGLE_LED_0) &&
		(can1_mailbox.uc_length == MAX_CAN_FRAME_DATA_LEN)) {
		puts("Test1 passed" STRING_EOL);
		decode_can_msg(&can1_mailbox);
	} else {
		puts("Test1 ERROR" STRING_EOL);
	}

	/* Disable CAN1 mailbox 0 interrupt. */
	can_disable_interrupt(CAN1, CAN_IER_MB0);
}

#define TEST2_CAN1_RX_MB_IDX     7
#define TEST2_CAN0_TX_MB1_IDX    1
#define TEST2_CAN0_TX_MB1_PRIO   15
#define TEST2_CAN0_TX_MB1_ID     0x09
#define TEST2_CAN0_TX_MB2_IDX    2
#define TEST2_CAN0_TX_MB2_PRIO   14
#define TEST2_CAN0_TX_MB2_ID     0x0A

/**
 *  \brief Test the transmission from CAN0 Mailboxes 1 & 2 to CAN1 Mailbox 7 without overwrite.
 */
static void test_2(void)
{
	can_reset_all_mailbox(CAN0);
	can_reset_all_mailbox(CAN1);

	puts("\n\rTest2: CAN0 Mailboxes 1 & 2 transmitting to ");
	puts("CAN1 Mailbox 7 without overwrite" STRING_EOL);

	/* Init CAN1 Mailbox 7 to Reception Mailbox. */
	reset_mailbox_conf(&can1_mailbox);
	can1_mailbox.ul_mb_idx = TEST2_CAN1_RX_MB_IDX;
	can1_mailbox.uc_obj_type = CAN_MB_RX_MODE;
	can1_mailbox.ul_id_msk = 0;
	can1_mailbox.ul_id = 0;
	can_mailbox_init(CAN1, &can1_mailbox);

	/* Init CAN0 Mailbox 1 to Transmit Mailbox. This message will be discarded. */
	reset_mailbox_conf(&can0_mailbox);
	can0_mailbox.ul_mb_idx = TEST2_CAN0_TX_MB1_IDX;
	can0_mailbox.uc_obj_type = CAN_MB_TX_MODE;
	can0_mailbox.uc_tx_prio = TEST2_CAN0_TX_MB1_PRIO;
	can0_mailbox.uc_id_ver = 0;
	can0_mailbox.ul_id_msk = 0;
	can_mailbox_init(CAN0, &can0_mailbox);

	/* Write transmit information into mailbox. */
	can0_mailbox.ul_id = CAN_MID_MIDvA(TEST2_CAN0_TX_MB1_ID);
	can0_mailbox.ul_datal = CAN_MSG_TOGGLE_LED_0;
	can0_mailbox.ul_datah = CAN_MSG_DUMMY_DATA;
	can0_mailbox.uc_length = MAX_CAN_FRAME_DATA_LEN;
	can_mailbox_write(CAN0, &can0_mailbox);

	/* Init CAN0 Mailbox 2 to Transmit Mailbox. This message will be received first. */
	reset_mailbox_conf(&can0_mailbox);
	can0_mailbox.ul_mb_idx = TEST2_CAN0_TX_MB2_IDX;
	can0_mailbox.uc_obj_type = CAN_MB_TX_MODE;
	can0_mailbox.uc_tx_prio = TEST2_CAN0_TX_MB2_PRIO;
	can0_mailbox.uc_id_ver = 0;
	can0_mailbox.ul_id_msk = 0;
	can_mailbox_init(CAN0, &can0_mailbox);

	/* Write transmit information into mailbox. */
	can0_mailbox.ul_id = CAN_MID_MIDvA(TEST2_CAN0_TX_MB2_ID);
	can0_mailbox.ul_datal = CAN_MSG_TOGGLE_LED_1;
	can0_mailbox.ul_datah = CAN_MSG_DUMMY_DATA;
	can0_mailbox.uc_length = MAX_CAN_FRAME_DATA_LEN;
	can_mailbox_write(CAN0, &can0_mailbox);

	/* Send out the information in mailbox 1 & 2 at the same time. */
	can_global_send_transfer_cmd(CAN0, (CAN_TCR_MB1 | CAN_TCR_MB2));

	puts("Wait for all the transmit mailboxes done." STRING_EOL);

	/* Enable CAN1 mailbox 7 interrupt. */
	can_enable_interrupt(CAN1, CAN_IER_MB7);

	while (!g_ul_recv_status) {
	}

	if ((can1_mailbox.ul_datal == CAN_MSG_TOGGLE_LED_1) &&
		(can1_mailbox.uc_length == MAX_CAN_FRAME_DATA_LEN)) {
		puts("Test2 passed" STRING_EOL);
		decode_can_msg(&can1_mailbox);
	} else {
		puts("Test2 ERROR" STRING_EOL);
	}

	/* Disable CAN1 mailbox 7 interrupt. */
	can_disable_interrupt(CAN1, CAN_IER_MB7);
}

#define TEST3_CAN1_RX_MB_IDX     7
#define TEST3_CAN0_TX_MB1_IDX    1
#define TEST3_CAN0_TX_MB1_PRIO   15
#define TEST3_CAN0_TX_MB1_ID     0x09
#define TEST3_CAN0_TX_MB2_IDX    2
#define TEST3_CAN0_TX_MB2_PRIO   14
#define TEST3_CAN0_TX_MB2_ID     0x0A
/**
 *  \brief Test the transmission from CAN0 Mailboxes 1 & 2 to CAN1 Mailbox 7 with overwrite.
 */
static void test_3(void)
{
	can_reset_all_mailbox(CAN0);
	can_reset_all_mailbox(CAN1);

	puts("\n\rTest3: CAN0 Mailboxes 1 & 2 transmitting to");
	puts("CAN1 Mailbox 7 with overwrite." STRING_EOL);

	/* Init CAN1 Mailbox 7 to Reception Mailbox with overwrite. */
	reset_mailbox_conf(&can1_mailbox);
	can1_mailbox.ul_mb_idx = TEST3_CAN1_RX_MB_IDX;
	can1_mailbox.uc_obj_type = CAN_MB_RX_OVER_WR_MODE;
	can1_mailbox.ul_id_msk = 0;
	can1_mailbox.ul_id = 0;
	can_mailbox_init(CAN1, &can1_mailbox);

	/* Init CAN0 Mailbox 1 to Transmit Mailbox. This message will be discarded. */
	reset_mailbox_conf(&can0_mailbox);
	can0_mailbox.ul_mb_idx = TEST3_CAN0_TX_MB1_IDX;
	can0_mailbox.uc_obj_type = CAN_MB_TX_MODE;
	can0_mailbox.uc_tx_prio = TEST3_CAN0_TX_MB1_PRIO;
	can0_mailbox.uc_id_ver = 0;
	can0_mailbox.ul_id_msk = 0;
	can_mailbox_init(CAN0, &can0_mailbox);

	/* Write transmit information into mailbox. */
	can0_mailbox.ul_id = CAN_MID_MIDvA(TEST3_CAN0_TX_MB1_ID);
	can0_mailbox.ul_datal = CAN_MSG_TOGGLE_LED_0;
	can0_mailbox.ul_datah = CAN_MSG_DUMMY_DATA;
	can0_mailbox.uc_length = MAX_CAN_FRAME_DATA_LEN;
	can_mailbox_write(CAN0, &can0_mailbox);

	/* Init CAN0 Mailbox 2 to Transmit Mailbox. This message will be received first. */
	reset_mailbox_conf(&can0_mailbox);
	can0_mailbox.ul_mb_idx = TEST3_CAN0_TX_MB2_IDX;
	can0_mailbox.uc_obj_type = CAN_MB_TX_MODE;
	can0_mailbox.uc_tx_prio = TEST3_CAN0_TX_MB2_PRIO;
	can0_mailbox.uc_id_ver = 0;
	can0_mailbox.ul_id_msk = 0;
	can_mailbox_init(CAN0, &can0_mailbox);

	/* Write transmit information into mailbox. */
	can0_mailbox.ul_id = CAN_MID_MIDvA(TEST3_CAN0_TX_MB2_ID);
	can0_mailbox.ul_datal = CAN_MSG_TOGGLE_LED_1;
	can0_mailbox.ul_datah = CAN_MSG_DUMMY_DATA;
	can0_mailbox.uc_length = MAX_CAN_FRAME_DATA_LEN;
	can_mailbox_write(CAN0, &can0_mailbox);

	/* Send out the information in mailbox 1 & 2 at the same time. */
	can_global_send_transfer_cmd(CAN0, (CAN_TCR_MB1 | CAN_TCR_MB2));

	puts("Wait for all the transmit mailboxes done." STRING_EOL);

	/* Enable CAN1 mailbox 7 interrupt. */
	can_enable_interrupt(CAN1, CAN_IER_MB7);

	while (!g_ul_recv_status) {
	}

	if ((can1_mailbox.ul_datal == CAN_MSG_TOGGLE_LED_0) &&
		(can1_mailbox.uc_length == MAX_CAN_FRAME_DATA_LEN)) {
		puts("Test3 passed" STRING_EOL);
		decode_can_msg(&can1_mailbox);
	} else {
		puts("Test3 ERROR" STRING_EOL);
	}

	/* Disable CAN1 mailbox 7 interrupt. */
	can_disable_interrupt(CAN1, CAN_IER_MB7);
}

#define TEST4_CAN0_MB_IDX         3
#define TEST4_CAN0_MB_ID          0x0b
#define TEST4_CAN1_TX_MB_IDX      3
#define TEST4_CAN1_TX_MB_PRIO     15
#define TEST4_CAN1_TX_MB_ID       0x0b
/**
 *  \brief Test the communication between CAN1 Mailbox 3 and CAN0 Mailbox 3.
 */
static void test_4(void)
{
	can_reset_all_mailbox(CAN0);
	can_reset_all_mailbox(CAN1);

	puts("\n\rTest4: CAN1 Mailbox 3 requesting");
	puts("CAN0 Mailbox 3 to transmit a data frame" STRING_EOL);

	/* Init CAN0 Mailbox 3 to Producer Mailbox. */
	reset_mailbox_conf(&can0_mailbox);
	can0_mailbox.ul_mb_idx = TEST4_CAN0_MB_IDX;
	can0_mailbox.uc_obj_type = CAN_MB_PRODUCER_MODE;
	can0_mailbox.ul_id_msk = 0;
	can0_mailbox.ul_id = CAN_MID_MIDvA(TEST4_CAN0_MB_ID);
	can_mailbox_init(CAN0, &can0_mailbox);

	/* Prepare the response information when it receives a remote frame. */
	can0_mailbox.ul_datal = CAN_MSG_TOGGLE_LED_0;
	can0_mailbox.ul_datah = CAN_MSG_DUMMY_DATA;
	can0_mailbox.uc_length = MAX_CAN_FRAME_DATA_LEN;
	can_mailbox_write(CAN0, &can0_mailbox);

	can_global_send_transfer_cmd(CAN0, CAN_TCR_MB3);

	/* Init CAN1 Mailbox 3 to Consumer Mailbox. It sends a remote frame and waits for an answer. */
	reset_mailbox_conf(&can1_mailbox);
	can1_mailbox.ul_mb_idx = TEST4_CAN1_TX_MB_IDX;
	can1_mailbox.uc_obj_type = CAN_MB_CONSUMER_MODE;
	can1_mailbox.uc_tx_prio = TEST4_CAN1_TX_MB_PRIO;
	can1_mailbox.ul_id_msk = CAN_MID_MIDvA_Msk | CAN_MID_MIDvB_Msk;
	can1_mailbox.ul_id = CAN_MID_MIDvA(TEST4_CAN1_TX_MB_ID);
	can_mailbox_init(CAN1, &can1_mailbox);

	/* Enable CAN1 mailbox 3 interrupt. */
	can_enable_interrupt(CAN1, CAN_IER_MB3);

	can_global_send_transfer_cmd(CAN1, CAN_TCR_MB3);
	while (!g_ul_recv_status) {
	}

	if ((can1_mailbox.ul_datal == CAN_MSG_TOGGLE_LED_0) &&
		(can1_mailbox.uc_length == MAX_CAN_FRAME_DATA_LEN)) {
		puts("Test4 passed" STRING_EOL);
		decode_can_msg(&can1_mailbox);
	} else {
		puts("Test4 ERROR" STRING_EOL);
	}

	/* Disable CAN1 mailbox 3 interrupt. */
	can_disable_interrupt(CAN1, CAN_IER_MB3);
}

/**
 *  Configure UART for debug message output.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 *  \brief can_example application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint32_t ul_sysclk;
	uint8_t uc_char;

	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	/* Configure UART for debug message output. */
	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);

	/* Initialize CAN0 Transceiver. */
	sn65hvd234_set_rs(&can0_transceiver, PIN_CAN0_TR_RS_IDX);
	sn65hvd234_set_en(&can0_transceiver, PIN_CAN0_TR_EN_IDX);
	/* Enable CAN0 Transceiver. */
	sn65hvd234_disable_low_power(&can0_transceiver);
	sn65hvd234_enable(&can0_transceiver);

	/* Initialize CAN1 Transceiver. */
	sn65hvd234_set_rs(&can1_transceiver, PIN_CAN1_TR_RS_IDX);
	sn65hvd234_set_en(&can1_transceiver, PIN_CAN1_TR_EN_IDX);
	/* Enable CAN1 Transceiver. */
	sn65hvd234_disable_low_power(&can1_transceiver);
	sn65hvd234_enable(&can1_transceiver);

	/* Enable CAN0 & CAN1 clock. */
	pmc_enable_periph_clk(ID_CAN0);
	pmc_enable_periph_clk(ID_CAN1);

	ul_sysclk = sysclk_get_cpu_hz();
	if (can_init(CAN0, ul_sysclk, CAN_BPS_1000K) &&
		can_init(CAN1, ul_sysclk, CAN_BPS_1000K)) {
		puts("CAN initialization is completed." STRING_EOL);

		/* Disable all CAN0 & CAN1 interrupts. */
		can_disable_interrupt(CAN0, CAN_DISABLE_ALL_INTERRUPT_MASK);
		can_disable_interrupt(CAN1, CAN_DISABLE_ALL_INTERRUPT_MASK);

		/* Configure and enable interrupt of CAN1, as the tests will use receiver interrupt. */
		NVIC_EnableIRQ(CAN1_IRQn);

		/* Run tests. */
		puts("Press any key to start test" STRING_EOL);
		while (uart_read(CONSOLE_UART, &uc_char)) {
		}
		test_1();
		g_ul_recv_status = 0;

		puts("Press any key to continue..." STRING_EOL);
		while (uart_read(CONSOLE_UART, &uc_char)) {
		}
		test_2();
		g_ul_recv_status = 0;

		puts("Press any key to continue..." STRING_EOL);
		while (uart_read(CONSOLE_UART, &uc_char)) {
		}
		test_3();
		g_ul_recv_status = 0;

		puts("Press any key to continue..." STRING_EOL);
		while (uart_read(CONSOLE_UART, &uc_char)) {
		}
		test_4();
		g_ul_recv_status = 0;

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

		puts("End of all tests" STRING_EOL);
	} else {
		puts("CAN initialization (sync) ERROR" STRING_EOL);
	}

	while (1) {
	}
}
