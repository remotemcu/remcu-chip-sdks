/**
 * \file
 *
 * \brief USART IrDA example for SAM.
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
 * \mainpage USART IrDA Example
 *
 * \par Purpose
 *
 * This example demonstrates the IrDA (Infrared Data Association) on SAM.
 *
 * \par Requirements
 *
 * This example can be used on all SAM EK boards with external IrDA transceiver
 * component. Connect the board and external component with the following paired
 * pins.
 * \copydoc usart_irda_example_pin_defs
 *
 * \par Description
 *
 * The provided program uses the USART in IrDA mode for transmitting and receiving
 * several octets. This example can be used with two SAM-EK boards.
 * The program receives or transmits a series of octets according to its state of
 * either receiver or transmitter.
 *
 * \par Note
 * To receive IrDA signals, the following needs to be done:
 * <ul>
 * <li> Disable TX and Enable RX. </li>
 * <li> Configure the TXD pin as PIO and set it as an output at 0 (to avoid LED
 * emission). Disable the internal pull-up (better for power consumption).</li>
 * <li> Receive data. </li>
 * </ul>
 * \par Usage
 *
 * -# Build the program and download it into the two evaluation boards.
 * -# Connect a serial cable to the UART port for each evaluation kit.
 * -# On the computer, open and configure a terminal application (e.g.,
 *    HyperTerminal on Microsoft Windows) with these settings:
 *       - 115200 bauds
 *       - 8 data bits
 *       - No parity
 *       - 1 stop bit
 *       - No flow control
 * -# Start the application.
 * -# The following traces shall appear on the terminal:
 *    \code
	-- USART IrDA Example --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
	-I- Press t to transmit, press r to receive...
\endcode
 * -# Enable one board as transmitter and another as receiver to start the
 *    communication. If succeed, the side of receiver would output the received
 *    data.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <string.h>
#include "asf.h"
#include "stdio_serial.h"
#include "conf_board.h"
#include "conf_clock.h"
#include "conf_example.h"


/** Buffer size for PDC transfer. */
#define BUFFER_SIZE                  10

/** Communication state. */
#define STATE_TRANSMIT               0
#define STATE_RECEIVE                1
#define STATE_IDLE                   3

/** All interrupt mask. */
#define ALL_INTERRUPT_MASK           0xffffffff

#define STRING_EOL    "\r"
#define STRING_HEADER "--USART IrDA Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/** State of BOARD_USART_BASE. */
uint8_t g_uc_state = STATE_IDLE;

/** Receiving Done status. */
volatile uint32_t g_ul_recv_done = false;

/** Transmitting Done status. */
volatile uint32_t g_ul_sent_done = false;

/** Data buffer for receiving. */
uint8_t g_uc_recv_data[BUFFER_SIZE] = { 0x0 };

/** Data buffer for transmitting. */
uint8_t g_uc_send_data[BUFFER_SIZE] =
		{ 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89 };

/** Pointer to PDC register base. */
Pdc *g_p_pdc;

/** PDC data packet. */
pdc_packet_t g_st_packet;

/**
  * \brief USART IRQ Handler, handling RXBUFF and TXBUFE status.
  */
void USART_Handler(void)
{
	uint32_t ul_status;

	/* Read USART Status. */
	ul_status = usart_get_status(BOARD_USART);

	/* Receiving is done. */
	if ((ul_status & US_CSR_RXBUFF) && (g_uc_state == STATE_RECEIVE)) {
		g_ul_recv_done = true;
		usart_disable_interrupt(BOARD_USART, US_IDR_RXBUFF);
	}

	/* Transmitting is done. */
	if ((ul_status & US_CSR_TXBUFE) && (g_uc_state == STATE_TRANSMIT)) {
		g_ul_sent_done = true;
		usart_disable_interrupt(BOARD_USART, US_IDR_TXBUFE);
	}
}

/**
 * \brief Disable receiver and Enable transmitter.
 */
static void func_transmitter(void)
{
	/* Configure the TXD pin as peripheral. */
	pio_configure_pin(PIN_USART_TXD_IDX, PIN_USART_TXD_FLAGS);

	/* Disable Receiver. */
	usart_disable_rx(BOARD_USART);

	/* Enable transmitter. */
	usart_enable_tx(BOARD_USART);
}

/**
 * \brief Disable transmitter and Enable receiver.
 */
static void func_receiver(void)
{
	uint32_t ul_temp;

	/* Disable Transmitter. */
	usart_disable_tx(BOARD_USART);

	/* Configure the TXD pin as PIO. */
	pio_configure_pin(PIN_USART_TXD_IDX, PIN_USART_TXD_IO_FLAGS);
	pio_set_pin_low(PIN_USART_TXD_IDX);

	/* Enable receiver. */
	usart_enable_rx(BOARD_USART);

	/* Read dummy to make sure that there are no characters in US_THR! */
	if (usart_is_rx_ready(BOARD_USART)) {
		usart_read(BOARD_USART, &ul_temp);
		/* avoid Cppcheck Warning */
		UNUSED(ul_temp);
	}
}

/**
 * \brief Dump received buffer to uart.
 * \param p_buf   Pointer to received buffer.
 * \param uc_size The size of the buffer.
 */
static void dump_recv_buf(uint8_t *p_buf, uint8_t uc_size)
{
	uint8_t uc_i = 0;

	for (uc_i = 0; uc_i < uc_size; uc_i++) {
		printf("0x%x\t", p_buf[uc_i]);
	}
	puts("\r");
}

/**
 *  Configure board USART communication with PC or other terminal.
 */
static void configure_usart(void)
{
	const sam_usart_opt_t usart_console_settings = {
		BOARD_USART_BAUDRATE,
		US_MR_CHRL_8_BIT,
		US_MR_PAR_NO,
		US_MR_NBSTOP_1_BIT,
		US_MR_CHMODE_NORMAL,
		BOARD_USART_IRDA_FILTER
	};

	/* Enable peripheral clock. */
	sysclk_enable_peripheral_clock(BOARD_ID_USART);

	/* Configure USART in IrDA mode. */
	usart_init_irda(BOARD_USART, &usart_console_settings, sysclk_get_peripheral_hz());

	/* Disable all the interrupts. */
	usart_disable_interrupt(BOARD_USART, ALL_INTERRUPT_MASK);
	
	/* Enable TX & RX function. */
	usart_enable_tx(BOARD_USART);
	usart_enable_rx(BOARD_USART);

	/* Configure and enable interrupt of USART. */
	NVIC_EnableIRQ(USART_IRQn);
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
 * \brief Application entry point.
 *
 * Initialize the IrDA and start the main loop.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t uc_char;

	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	/* Configure UART for debug message output. */
	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);

	/* Initialize board USART. */
	configure_usart();

	/* Get board USART PDC base address and enable receiver and transmitter. */
	g_p_pdc = usart_get_pdc_base(BOARD_USART);
	pdc_enable_transfer(g_p_pdc, PERIPH_PTCR_RXTEN | PERIPH_PTCR_TXTEN);

	puts("-I- Press t to transmit, press r to receive...\r");

	/* Main loop. */
	while (1) {
		uc_char = 0;
		uart_read(CONSOLE_UART, (uint8_t *)&uc_char);

		switch (uc_char) {
		case 't':
		case 'T':
			g_uc_state = STATE_TRANSMIT;
			/* Enable transmitter. */
			func_transmitter();
			g_st_packet.ul_addr = (uint32_t)g_uc_send_data;
			g_st_packet.ul_size = BUFFER_SIZE;
			pdc_tx_init(g_p_pdc, &g_st_packet, NULL);
			usart_enable_interrupt(BOARD_USART, US_IER_TXBUFE);
			while (!g_ul_sent_done) {
			}

			puts("-I- Sent Done!\r");
			g_ul_sent_done = false;
			g_uc_state = STATE_IDLE;
			puts("-I- Press t to transmit, press r to receive...\r");
			break;

		case 'r':
		case 'R':
			g_uc_state = STATE_RECEIVE;

			/* Enable receiver. */
			puts("-I- IrDA receive mode\r");
			func_receiver();
			g_st_packet.ul_addr = (uint32_t)g_uc_recv_data;
			g_st_packet.ul_size = BUFFER_SIZE;
			pdc_rx_init(g_p_pdc, &g_st_packet, NULL);
			usart_enable_interrupt(BOARD_USART, US_IER_RXBUFF);

			while (!g_ul_recv_done) {
			}

			puts("-I- Received Done! \r");
			dump_recv_buf(g_uc_recv_data, BUFFER_SIZE);
			memset(g_uc_recv_data, 0, BUFFER_SIZE);
			g_uc_state = STATE_IDLE;
			g_ul_recv_done = false;
			puts("-I- Press t to transmit, press r to receive...\r");
			break;

		default:
			break;
		}
	}
}
