/**
 * \file
 *
 * \brief CAN example for SAM.
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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
 *  This package can be used with two SAM4E-XPRO boards.
 *  The CAN1 in two board should be connected externally before running
 *  the example.
 *
 *  \par Description
 *
 *  In this example, one board sends messages over CAN bus to another board.
 *  The CAN message will display on the terminal window.
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
 *  -# Connect CAN1 in two boards.
 *  -# Start the application.
 *  -# Upon startup, the application will output the following lines
 *     on the terminal window.
 *      \code
	-- CAN Example --
	-- SAM4E -XPRO --
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 *  -# Press 'r' key in the terminal window to configure one board to
 *     receive CAN message.
 *  -# Press 't' key in the terminal window to confgure another board to
 *     send CAN message. The message will be displayed on the terminal window.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"

#define STRING_EOL    "\r"
#define STRING_HEADER "-- CAN Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

#define CAN_COMM_RXMB_ID    0
#define CAN_COMM_TXMB_ID    1
#define CAN_TRANSFER_ID     7
#define CAN_TX_PRIO         15
#define CAN_MSG_DUMMY_DATA  0x55AAAA55u

/** CAN frame max data length */
#define MAX_CAN_FRAME_DATA_LEN      8

/** Transfer mailbox structure */
can_mb_conf_t tx_mailbox, rx_mailbox;

/** Receive status */
volatile uint32_t g_ul_recv_status = 0;

/**
 * \brief Default interrupt handler for CAN 1.
 */
void CAN1_Handler(void)
{
	uint32_t ul_status;

	ul_status = can_mailbox_get_status(CAN1, 0);
	if (ul_status & CAN_MSR_MRDY) {
		rx_mailbox.ul_status = ul_status;
		can_mailbox_read(CAN1, &rx_mailbox);
		puts("Got CAN message, press 'r' to display\r");
		g_ul_recv_status = 1;
	}
}

/**
 * \brief Decode CAN messages.
 *
 *  \param p_mailbox Pointer to CAN Mailbox structure.
 */
static void decode_can_msg(can_mb_conf_t *p_mailbox)
{
	if (p_mailbox->ul_datal != CAN_MSG_DUMMY_DATA) {
		puts("Wrong message header\r");
	} else {
		printf("%d\r\n", (int)p_mailbox->ul_datah);
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
	uint32_t ul_sysclk, cnt = 0;
	uint8_t uc_key;

	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	/* Configure UART for debug message output. */
	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);

	/* Enable CAN1 clock. */
	pmc_enable_periph_clk(ID_CAN1);

	ul_sysclk = sysclk_get_cpu_hz();
	if (can_init(CAN1, ul_sysclk, CAN_BPS_1000K)) {
		puts("CAN initialization is completed." STRING_EOL);

		/* Disable all CAN1 interrupts. */
		can_disable_interrupt(CAN1, CAN_DISABLE_ALL_INTERRUPT_MASK);
		can_reset_all_mailbox(CAN1);

		/* Init CAN1 Mailbox 0 to Reception Mailbox. */
		reset_mailbox_conf(&rx_mailbox);
		rx_mailbox.ul_mb_idx = CAN_COMM_RXMB_ID;
		rx_mailbox.uc_obj_type = CAN_MB_RX_MODE;
		rx_mailbox.ul_id_msk = CAN_MAM_MIDvA_Msk | CAN_MAM_MIDvB_Msk;
		rx_mailbox.ul_id = CAN_MID_MIDvA(CAN_TRANSFER_ID);
		can_mailbox_init(CAN1, &rx_mailbox);

		/* Init CAN1 Mailbox 1 to Transmit Mailbox. */
		reset_mailbox_conf(&tx_mailbox);
		tx_mailbox.ul_mb_idx = CAN_COMM_TXMB_ID;
		tx_mailbox.uc_obj_type = CAN_MB_TX_MODE;
		tx_mailbox.uc_tx_prio = CAN_TX_PRIO;
		tx_mailbox.uc_id_ver = 0;
		tx_mailbox.ul_id_msk = 0;
		can_mailbox_init(CAN1, &tx_mailbox);

		/* Write transmit information into mailbox. */
		tx_mailbox.ul_id = CAN_MID_MIDvA(CAN_TRANSFER_ID);
		tx_mailbox.ul_datal = CAN_MSG_DUMMY_DATA;
		tx_mailbox.uc_length = MAX_CAN_FRAME_DATA_LEN;

		/* Enable CAN1 mailbox interrupt. */
		can_enable_interrupt(CAN1, 1 << CAN_COMM_RXMB_ID);
		/* Configure and enable interrupt of CAN1. */
		NVIC_EnableIRQ(CAN1_IRQn);

		puts("\tt: Perform CAN Transmisson \r");

		while (1) {
			scanf("%c", (char *)&uc_key);

			switch (uc_key) {
			case 'R':
			case 'r':
				if (!g_ul_recv_status) {
					puts("No CAN message\r");
				} else {
					g_ul_recv_status = 0;
					decode_can_msg(&rx_mailbox);
				}
				break;

			case 'T':
			case 't':
				if (can_get_status(CAN1) & CAN_SR_TBSY) {
					puts("Transmission is busy\r");
				} else {
					tx_mailbox.ul_datah = cnt++;
					can_mailbox_write(CAN1, &tx_mailbox);
					/* Send out the information in the mailbox. */
					can_global_send_transfer_cmd(CAN1, CAN_TCR_MB1);
				}
				break;

			default:
				puts("Unknown input\r");
				break;
			}
		}
	} else {
		puts("CAN initialization (sync) ERROR" STRING_EOL);
	}

	while (1) {
	}
}
