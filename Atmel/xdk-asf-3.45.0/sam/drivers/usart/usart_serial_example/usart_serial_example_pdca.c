/**
 * \file
 *
 * \brief USART Serial example for SAM.
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

/**
 * \mainpage USART Serial Example
 *
 * \par Purpose
 * This example demonstrates the normal (serial) mode provided by the USART
 * peripherals.
 *
 * \par Requirements
 * This package can be used with SAM4L with USART and PDCA.
 * - SAM4L-EK
 * - SAM4L Xplained Pro
 * - SAM4L8 Xplained Pro
 *
 * \par Description
 *
 * On start up, the debug information is dumped to on-board USART port.
 * A terminal application, such as HyperTerminal, is used to monitor these
 * debug information. Then the program works in ECHO mode, so USART will
 * send back anything it receives from the HyperTerminal.  You can send a text
 * file from the HyperTerminal connected with USART port to the device (without
 * any protocol such as X-modem).
 *
 * \par Usage
 *
 * -# Build the program and download it into the evaluation boards.
 * -# Connect a serial cable to the USART port for the evaluation kit.
 * -# On the computer, open and configure a terminal application
 *    (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# In the terminal window, the following text should appear:
 *    \code
	-- USART Serial Example --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
	-- Start to echo serial inputs with PDCA --
\endcode
 * -# Send a file in text format from the HyperTerminal connected with USART
 *    port to the device. On HyperTerminal, this is done by selecting
 *    "Transfer -> Send Text File"(this does not prevent you from sending
 *    binary files). The transfer will start and then you could read the file
 *    in the HyperTerminal.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <string.h>
#include <asf.h>
#include "conf_board.h"
#include "conf_clock.h"
#include "conf_example.h"

/** Size of the receive buffer used by the PDCA, in bytes. */
#define BUFFER_SIZE         100

/** Max buffer number. */
#define MAX_BUF_NUM         1

/** All interrupt mask. */
#define ALL_INTERRUPT_MASK  0xffffffff

/** Timer counter frequency in Hz. */
#define TC_FREQ             10

#define STRING_EOL    "\r"
#define STRING_HEADER "-- USART Serial Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

#define PDCA_RX_CHANNEL  0
#define PDCA_TX_CHANNEL  1

/** Receive buffer. */
static uint8_t gs_puc_buffer[2][BUFFER_SIZE];

/** Next Receive buffer. */
static uint8_t gs_puc_nextbuffer[2][BUFFER_SIZE];

/** Current bytes in buffer. */
static uint32_t gs_ul_size_buffer = BUFFER_SIZE;

/** Current bytes in next buffer. */
static uint32_t gs_ul_size_nextbuffer = BUFFER_SIZE;

/** Buffer number in use. */
static uint8_t gs_uc_buf_num = 0;

/** Flag of one transfer end. */
static uint8_t g_uc_transend_flag = 0;

/** PDCA channel options. */
pdca_channel_config_t pdca_rx_options = {
	.addr = (void *)gs_puc_buffer, /* memory address */
	.pid = PDCA_PID_USART_RX, /* select peripheral - USART0 RX line.*/
	.size = BUFFER_SIZE, /* transfer counter */
	.r_addr = (void *)gs_puc_nextbuffer, /* next memory address */
	.r_size = BUFFER_SIZE, /* next transfer counter */
	.transfer_size = PDCA_MR_SIZE_BYTE, /* select size of the transfer */
	.etrig = false, /* disable event trigger*/
	.ring = false /* not use ring buffer*/
};
pdca_channel_config_t pdca_tx_options = {
	.addr = (void *)gs_puc_buffer, /* memory address */
	.pid = PDCA_PID_USART_TX, /* select peripheral - USART0 TX line.*/
	.size = 0, /* transfer counter */
	.r_addr = (void *)gs_puc_nextbuffer, /* next memory address */
	.r_size = 0, /* next transfer counter */
	.transfer_size = PDCA_MR_SIZE_BYTE, /* select size of the transfer */
	.etrig = false, /* disable event trigger*/
	.ring = false /* not use ring buffer*/
};

/**
 * \brief Interrupt handler for USART. Echo the bytes received and start the
 * next receive.
 */
void USART_Handler(void)
{
	uint32_t ul_status;

	/* Read USART Status. */
	ul_status = usart_get_status(BOARD_USART);

	/* Receive buffer is full. */
	if (ul_status & US_CSR_RXBUFF) {
		/* Disable timer. */
		tc_stop(TC0, 0);

		/* Echo back buffer. */
		pdca_channel_write_load(PDCA_TX_CHANNEL,
				(void *)gs_puc_buffer[gs_uc_buf_num],
				gs_ul_size_buffer);
		pdca_channel_write_reload(PDCA_TX_CHANNEL,
				(void *)gs_puc_nextbuffer[gs_uc_buf_num],
				gs_ul_size_nextbuffer);

		if (g_uc_transend_flag) {
			gs_ul_size_buffer = BUFFER_SIZE;
			gs_ul_size_nextbuffer = BUFFER_SIZE;
			g_uc_transend_flag = 0;
		}

		gs_uc_buf_num = MAX_BUF_NUM - gs_uc_buf_num;

		/* Restart read on buffer. */
		pdca_channel_write_load(PDCA_RX_CHANNEL,
				(void *)gs_puc_buffer[gs_uc_buf_num], BUFFER_SIZE);
		pdca_channel_write_reload(PDCA_RX_CHANNEL,
				(void *)gs_puc_nextbuffer[gs_uc_buf_num], BUFFER_SIZE);

		/* Restart timer. */
		tc_start(TC0, 0);
	}
}

/**
 * \brief Interrupt handler for TC00. Record the number of bytes received,
 * and then restart a read transfer on the USART if the transfer was stopped.
 */
void TC00_Handler(void)
{
	uint32_t ul_status;
	uint32_t ul_byte_total = 0;

	/* Read TC0 Status. */
	ul_status = tc_get_status(TC0, 0);

	/* RC compare. */
	if ((ul_status & TC_SR_CPCS) == TC_SR_CPCS) {
		/* Flush PDC buffer. */
		ul_byte_total = BUFFER_SIZE -
				pdca_channel_read_load_size(PDCA_RX_CHANNEL);
		if ((ul_byte_total != 0) && (ul_byte_total != BUFFER_SIZE)) {
			/* Log current size. */
			g_uc_transend_flag = 1;
			if (pdca_channel_read_reload_size(PDCA_RX_CHANNEL) == 0) {
				gs_ul_size_buffer = BUFFER_SIZE;
				gs_ul_size_nextbuffer = ul_byte_total;
			} else {
				gs_ul_size_buffer = ul_byte_total;
				gs_ul_size_nextbuffer = 0;
			}

			/* Trigger USART Receive Buffer Full Interrupt. */
			/* Restart read on buffer. */
			pdca_channel_write_reload(PDCA_RX_CHANNEL,
					(void *)gs_puc_nextbuffer[gs_uc_buf_num], 0);
			pdca_channel_write_load(PDCA_RX_CHANNEL,
					(void *)gs_puc_buffer[gs_uc_buf_num], 0);
		}
	}
}

/**
 * \brief Configure Timer Counter 0 (TC0) to generate an interrupt every 200ms.
 * This interrupt will be used to flush USART input and echo back.
 */
static void configure_tc(void)
{
	uint32_t ul_div;
	uint32_t ul_tcclks;
	static uint32_t ul_pbaclk;

	/* Configure clock service. */
	sysclk_enable_peripheral_clock(TC0);

	/* Get system clock. */
	ul_pbaclk = sysclk_get_peripheral_bus_hz(TC0);

	/* Configure TC for a 1Hz frequency and trigger on RC compare. */
	tc_find_mck_divisor(TC_FREQ, ul_pbaclk, &ul_div, &ul_tcclks, ul_pbaclk);
	tc_init(TC0, 0, ul_tcclks | TC_CMR_CPCTRG);
	tc_write_rc(TC0, 0, (ul_pbaclk / ul_div) / TC_FREQ);

	/* Configure and enable interrupt on RC compare. */
	NVIC_EnableIRQ(TC00_IRQn);
	tc_enable_interrupt(TC0, 0, TC_IER_CPCS);
}

/**
 *  Configure UART for debug message output.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
#ifdef CONF_UART_CHAR_LENGTH
		.charlength = CONF_UART_CHAR_LENGTH,
#endif
		.paritytype = CONF_UART_PARITY,
#ifdef CONF_UART_STOP_BITS
		.stopbits = CONF_UART_STOP_BITS,
#endif
	};

	/* Configure console UART. */
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief Application entry point for usart_serial example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	/* Configure UART for debug message output. */
	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);
	puts("-- Start to echo serial inputs with PDCA -- \r\n\r");

	/* Configure TC. */
	configure_tc();

	/* Enable PDCA module clock */
	pdca_enable(PDCA);
	/* Init PDCA channel with the pdca_options.*/
	pdca_channel_set_config(PDCA_RX_CHANNEL, &pdca_rx_options);
	pdca_channel_set_config(PDCA_TX_CHANNEL, &pdca_tx_options);
	/* Enable PDCA channel, start receiving data. */
	pdca_channel_enable(PDCA_RX_CHANNEL);
	pdca_channel_enable(PDCA_TX_CHANNEL);

	/* Enable USART RXBUFF interrupt */
	usart_enable_interrupt(BOARD_USART, US_IER_RXBUFF);
	/* Configure and enable interrupt of USART. */
	NVIC_EnableIRQ(USART_IRQn);

	/* Start timer. */
	tc_start(TC0, 0);

	while (1) {
	}
}
