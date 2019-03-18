/**
 * \file
 *
 * \brief USART DMAC Example for SAM.
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
 * \mainpage USART DMAC Example
 *
 * \par Purpose
 * This example demonstrates how to use DMAC to implement USART
 * peripherals function in serial mode.
 *
 * \par Requirements
 *  This package can be used with all SAM-EK with UART/USART and DMAC.
 *
 * \par Description
 *
 * On start up, the debug information is dumped to on-board UART port.
 * A terminal application, such as HyperTerminal, is used to monitor these
 * debug information. Open another HyperTerminal to connect with
 * on-board USART port. Then the program works in ECHO mode, so USART will
 * send back anything it receives from the HyperTerminal. You can send a text
 * file from the HyperTerminal connected with USART port to the device (without
 * any protocol such as X-modem).
 *
 * \note The text file size must be equal to BUFFER_SIZE(32 bytes in this example).
 *
 * \par Usage
 *
 * -# Build the program and download it into the evaluation boards.
 * -# Connect a serial cable to the UART port for the evaluation kit.
 * -# On the computer, open and configure a terminal application
 *    (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# In the terminal window, the following text should appear:
 *    \code
	-- USART DMAC Example --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
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

#include "asf.h"
#include "conf_example.h"

/** Size of the receive buffer used by the DMAC, in bytes. */
#define BUFFER_SIZE               32

/** DMAC receive channel of master. */
#define BOARD_USART_DMAC_RX_CH    0
/** DMAC transmit channel of master. */
#define BOARD_USART_DMAC_TX_CH    1

/** DMAC Channel HW Interface Number for USART. */
#define USART_TX_IDX              11
#define USART_RX_IDX              12

#define STRING_EOL    "\r"
#define STRING_HEADER "-- USART DMAC Serial Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/** Receive buffer. */
static uint8_t gs_puc_buffer[BUFFER_SIZE];

/**
 * \brief DMAC rx channel configuration.
 */
static void configure_dmac_rx(void)
{
	uint32_t ul_cfg;
	dma_transfer_descriptor_t dmac_trans;

	ul_cfg = 0;
	ul_cfg |= DMAC_CFG_SRC_PER(USART_RX_IDX) |
			DMAC_CFG_SRC_H2SEL |
			DMAC_CFG_SOD_ENABLE | DMAC_CFG_FIFOCFG_ALAP_CFG;
	dmac_channel_set_configuration(DMAC, BOARD_USART_DMAC_RX_CH, ul_cfg);

	dmac_channel_disable(DMAC, BOARD_USART_DMAC_RX_CH);
	dmac_trans.ul_source_addr = (uint32_t) & BOARD_USART->US_RHR;
	dmac_trans.ul_destination_addr = (uint32_t) gs_puc_buffer;
	dmac_trans.ul_ctrlA =
			DMAC_CTRLA_BTSIZE(BUFFER_SIZE) |
			DMAC_CTRLA_SRC_WIDTH_BYTE | DMAC_CTRLA_DST_WIDTH_BYTE;
	dmac_trans.ul_ctrlB =
			DMAC_CTRLB_SRC_DSCR | DMAC_CTRLB_DST_DSCR |
			DMAC_CTRLB_FC_PER2MEM_DMA_FC | DMAC_CTRLB_SRC_INCR_FIXED
			| DMAC_CTRLB_DST_INCR_INCREMENTING;
	dmac_trans.ul_descriptor_addr = 0;
	dmac_channel_single_buf_transfer_init(DMAC, BOARD_USART_DMAC_RX_CH,
			&dmac_trans);
	dmac_channel_enable(DMAC, BOARD_USART_DMAC_RX_CH);
}

/**
 * \brief DMAC tx channel configuration.
 */
static void configure_dmac_tx(void)
{
	uint32_t ul_cfg;
	dma_transfer_descriptor_t dmac_trans;

	ul_cfg = 0;
	ul_cfg |= DMAC_CFG_DST_PER(USART_TX_IDX) |
			DMAC_CFG_DST_H2SEL |
			DMAC_CFG_SOD_ENABLE | DMAC_CFG_FIFOCFG_ALAP_CFG;
	dmac_channel_set_configuration(DMAC, BOARD_USART_DMAC_TX_CH, ul_cfg);

	dmac_channel_disable(DMAC, BOARD_USART_DMAC_TX_CH);
	dmac_trans.ul_source_addr = (uint32_t) gs_puc_buffer;
	dmac_trans.ul_destination_addr = (uint32_t) & BOARD_USART->US_THR;
	dmac_trans.ul_ctrlA =
			DMAC_CTRLA_BTSIZE(BUFFER_SIZE) |
			DMAC_CTRLA_SRC_WIDTH_BYTE | DMAC_CTRLA_DST_WIDTH_BYTE;
	dmac_trans.ul_ctrlB =
			DMAC_CTRLB_SRC_DSCR | DMAC_CTRLB_DST_DSCR |
			DMAC_CTRLB_FC_MEM2PER_DMA_FC |
			DMAC_CTRLB_SRC_INCR_INCREMENTING |
			DMAC_CTRLB_DST_INCR_FIXED;
	dmac_trans.ul_descriptor_addr = 0;
	dmac_channel_single_buf_transfer_init(DMAC, BOARD_USART_DMAC_TX_CH,
			&dmac_trans);
	dmac_channel_enable(DMAC, BOARD_USART_DMAC_TX_CH);
}

/**
 * \brief DMAC interrupt handler.
 */
void DMAC_Handler(void)
{
	uint32_t dma_status;

	dma_status = dmac_get_status(DMAC);

	if (dma_status & (1 << BOARD_USART_DMAC_RX_CH)) {
		configure_dmac_tx();
		configure_dmac_rx();
	}
}

/**
 * \brief Configure USART in normal (serial rs232) mode, asynchronous,
 * 8 bits, 1 stop bit, no parity, 115200 bauds and enable its transmitter
 * and receiver.
 */
static void configure_usart(void)
{
	const sam_usart_opt_t usart_console_settings = {
		BOARD_USART_BAUDRATE,
		US_MR_CHRL_8_BIT,
		US_MR_PAR_NO,
		US_MR_NBSTOP_1_BIT,
		US_MR_CHMODE_NORMAL,
		/* This field is only used in IrDA mode. */
		0
	};

	/* Enable the peripheral clock in the PMC. */
	sysclk_enable_peripheral_clock(BOARD_ID_USART);

	/* Configure USART in serial mode. */
	usart_init_rs232(BOARD_USART, &usart_console_settings,
			sysclk_get_peripheral_hz());

	/* Enable the receiver and transmitter. */
	usart_enable_tx(BOARD_USART);
	usart_enable_rx(BOARD_USART);
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
 * \brief DMAC driver configuration.
 */
static void configure_dmac(void)
{
	/* Initialize and enable DMA controller. */
	pmc_enable_periph_clk(ID_DMAC);
	dmac_init(DMAC);
	dmac_set_priority_mode(DMAC, DMAC_PRIORITY_ROUND_ROBIN);
	dmac_enable(DMAC);

	/* Enable receive channel interrupt for DMAC. */
	NVIC_EnableIRQ(DMAC_IRQn);
	dmac_enable_interrupt(DMAC, (1 << BOARD_USART_DMAC_RX_CH));
}

/**
 * \brief Application entry point for usart_dmac_serial example.
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

	/* Configure USART. */
	configure_usart();

	/* Configure DMAC. */
	configure_dmac();

	/* Configure DMAC RX channel. */
	configure_dmac_rx();

	while (1) {
	}
}
