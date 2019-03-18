/**
 * \file
 *
 * \brief USART Serial example for SAM.
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
 * \mainpage USART Serial Example
 *
 * \par Purpose
 * This example demonstrates the normal (serial) mode provided by the USART
 * peripherals.
 *
 * \par Requirements
 *  This package can be used with all SAM-EK with UART/USART and PDC.
 *
 * \par Description
 *
 * On start up, the debug information is dumped to on-board USART port.
 * A terminal application, such as HyperTerminal, is used to monitor these
 * debug information. Open another HyperTerminal to connect with
 * on-board USART port. Then the program works in ECHO mode, so USART will
 * send back anything it receives from the HyperTerminal.  You can send a text
 * file from the HyperTerminal connected with USART port to the device (without
 * any protocol such as X-modem).
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
	-- USART Serial Example --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
	-- Start to echo serial inputs --
	-- -I- Default Transfer with PDC --
	-- -I- Press 's' to switch transfer mode
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
#include "asf.h"
#include "stdio_serial.h"
#include "conf_board.h"
#include "conf_clock.h"
#include "conf_example.h"

/** Size of the receive buffer used by the PDC, in bytes. */
#define BUFFER_SIZE         100

/** USART PDC transfer type definition. */
#define PDC_TRANSFER        1

/** USART FIFO transfer type definition. */
#define BYTE_TRANSFER       0

/** Max buffer number. */
#define MAX_BUF_NUM         1

/** All interrupt mask. */
#define ALL_INTERRUPT_MASK  0xffffffff

/** Timer counter frequency in Hz. */
#define TC_FREQ             1

#define STRING_EOL    "\r"
#define STRING_HEADER "-- USART Serial Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/** Receive buffer. */
static uint8_t gs_puc_buffer[2][BUFFER_SIZE];

/** Next Receive buffer. */
static uint8_t gs_puc_nextbuffer[2][BUFFER_SIZE];

/** Current bytes in buffer. */
static uint32_t gs_ul_size_buffer = BUFFER_SIZE;

/** Current bytes in next buffer. */
static uint32_t gs_ul_size_nextbuffer = BUFFER_SIZE;

/** Byte mode read buffer. */
static uint32_t gs_ul_read_buffer = 0;

/** Current transfer mode. */
static uint8_t gs_uc_trans_mode = PDC_TRANSFER;

/** Buffer number in use. */
static uint8_t gs_uc_buf_num = 0;

/** PDC data packet. */
pdc_packet_t g_st_packet, g_st_nextpacket;

/** Pointer to PDC register base. */
Pdc *g_p_pdc;

/** Flag of one transfer end. */
static uint8_t g_uc_transend_flag = 0;

/**
 * \brief Interrupt handler for USART. Echo the bytes received and start the
 * next receive.
 */
void USART_Handler(void)
{
	uint32_t ul_status;

	/* Read USART Status. */
	ul_status = usart_get_status(BOARD_USART);

	if (gs_uc_trans_mode == PDC_TRANSFER) {
		/* Receive buffer is full. */
		if (ul_status & US_CSR_RXBUFF) {
			/* Disable timer. */
			tc_stop(TC0, 0);

			/* Echo back buffer. */
			g_st_packet.ul_addr =
					(uint32_t)gs_puc_buffer[gs_uc_buf_num];
			g_st_packet.ul_size = gs_ul_size_buffer;
			g_st_nextpacket.ul_addr =
					(uint32_t)gs_puc_nextbuffer[gs_uc_buf_num];
			g_st_nextpacket.ul_size = gs_ul_size_nextbuffer;
			pdc_tx_init(g_p_pdc, &g_st_packet, &g_st_nextpacket);

			if (g_uc_transend_flag) {
				gs_ul_size_buffer = BUFFER_SIZE;
				gs_ul_size_nextbuffer = BUFFER_SIZE;
				g_uc_transend_flag = 0;
			}

			gs_uc_buf_num = MAX_BUF_NUM - gs_uc_buf_num;

			/* Restart read on buffer. */
			g_st_packet.ul_addr =
					(uint32_t)gs_puc_buffer[gs_uc_buf_num];
			g_st_packet.ul_size = BUFFER_SIZE;
			g_st_nextpacket.ul_addr =
					(uint32_t)gs_puc_nextbuffer[ gs_uc_buf_num];
			g_st_nextpacket.ul_size = BUFFER_SIZE;
			pdc_rx_init(g_p_pdc, &g_st_packet, &g_st_nextpacket);

			/* Restart timer. */
			tc_start(TC0, 0);
		}
	} else {
		/* Transfer without PDC. */
		if (ul_status & US_CSR_RXRDY) {
			usart_getchar(BOARD_USART, (uint32_t *)&gs_ul_read_buffer);
			usart_write(BOARD_USART, gs_ul_read_buffer);
		}
	}
}

/**
 * \brief Interrupt handler for TC0. Record the number of bytes received,
 * and then restart a read transfer on the USART if the transfer was stopped.
 */
void TC0_Handler(void)
{
	uint32_t ul_status;
	uint32_t ul_byte_total = 0;

	/* Read TC0 Status. */
	ul_status = tc_get_status(TC0, 0);

	/* RC compare. */
	if (((ul_status & TC_SR_CPCS) == TC_SR_CPCS) &&
			(gs_uc_trans_mode == PDC_TRANSFER)) {
		/* Flush PDC buffer. */
		ul_byte_total = BUFFER_SIZE - pdc_read_rx_counter(g_p_pdc);
		if ((ul_byte_total != 0) && (ul_byte_total != BUFFER_SIZE)) {
			/* Log current size. */
			g_uc_transend_flag = 1;
			if (pdc_read_rx_next_counter(g_p_pdc) == 0) {
				gs_ul_size_buffer = BUFFER_SIZE;
				gs_ul_size_nextbuffer = ul_byte_total;
			} else {
				gs_ul_size_buffer = ul_byte_total;
				gs_ul_size_nextbuffer = 0;
			}

			/* Trigger USART Receive Buffer Full Interrupt. */
			pdc_rx_clear_cnt(g_p_pdc);
		}
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
#if (SAM4L)
			sysclk_get_pba_hz());
#else
			sysclk_get_peripheral_hz());
#endif

	/* Disable all the interrupts. */
	usart_disable_interrupt(BOARD_USART, ALL_INTERRUPT_MASK);

	/* Enable the receiver and transmitter. */
	usart_enable_tx(BOARD_USART);
	usart_enable_rx(BOARD_USART);

	/* Configure and enable interrupt of USART. */
	NVIC_EnableIRQ(USART_IRQn);
}

/**
 * \brief Configure Timer Counter 0 (TC0) to generate an interrupt every 200ms.
 * This interrupt will be used to flush USART input and echo back.
 */
static void configure_tc(void)
{
	uint32_t ul_div;
	uint32_t ul_tcclks;
	static uint32_t ul_sysclk;

	/* Get system clock. */
	ul_sysclk = sysclk_get_cpu_hz();

	/* Configure PMC. */
	pmc_enable_periph_clk(ID_TC0);

	/* Configure TC for a 50Hz frequency and trigger on RC compare. */
	tc_find_mck_divisor(TC_FREQ, ul_sysclk, &ul_div, &ul_tcclks, ul_sysclk);
	tc_init(TC0, 0, ul_tcclks | TC_CMR_CPCTRG);
	tc_write_rc(TC0, 0, (ul_sysclk / ul_div) / TC_FREQ);

	/* Configure and enable interrupt on RC compare. */
	NVIC_EnableIRQ((IRQn_Type)ID_TC0);
	tc_enable_interrupt(TC0, 0, TC_IER_CPCS);
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
 * \brief Reset the TX & RX, and clear the PDC counter.
 */
static void usart_clear(void)
{
	/* Reset and disable receiver & transmitter. */
	usart_reset_rx(BOARD_USART);
	usart_reset_tx(BOARD_USART);

	/* Clear PDC counter. */
	g_st_packet.ul_addr = 0;
	g_st_packet.ul_size = 0;
	g_st_nextpacket.ul_addr = 0;
	g_st_nextpacket.ul_size = 0;
	pdc_rx_init(g_p_pdc, &g_st_packet, &g_st_nextpacket);

	/* Enable receiver & transmitter. */
	usart_enable_tx(BOARD_USART);
	usart_enable_rx(BOARD_USART);
}

/**
 * \brief Display main menu.
 */
static void display_main_menu(void)
{
	puts("-- Menu Choices for this example --\r\n"
			"-- s: Switch mode for USART between PDC and without PDC.--\r\n"
			"-- m: Display this menu again.--\r");
}

/**
 * \brief Application entry point for usart_serial example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t uc_char;
	uint8_t uc_flag;

	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	/* Configure UART for debug message output. */
	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);

	/* Configure USART. */
	configure_usart();

	/* Get board USART PDC base address. */
	g_p_pdc = usart_get_pdc_base(BOARD_USART);
	/* Enable receiver and transmitter. */
	pdc_enable_transfer(g_p_pdc, PERIPH_PTCR_RXTEN | PERIPH_PTCR_TXTEN);

	/* Configure TC. */
	configure_tc();

	/* Start receiving data and start timer. */
	g_st_packet.ul_addr = (uint32_t)gs_puc_buffer[gs_uc_buf_num];
	g_st_packet.ul_size = BUFFER_SIZE;
	g_st_nextpacket.ul_addr = (uint32_t)gs_puc_nextbuffer[gs_uc_buf_num];
	g_st_nextpacket.ul_size = BUFFER_SIZE;
	pdc_rx_init(g_p_pdc, &g_st_packet, &g_st_nextpacket);

	puts("-- Start to echo serial inputs -- \r\n"
			"-I- Default Transfer with PDC \r\n"
			"-I- Press 's' to switch transfer mode \r");
	gs_uc_trans_mode = PDC_TRANSFER;

	usart_disable_interrupt(BOARD_USART, US_IDR_RXRDY);
	usart_enable_interrupt(BOARD_USART, US_IER_RXBUFF);

	tc_start(TC0, 0);

	while (1) {
		uc_char = 0;
		uc_flag = uart_read(CONSOLE_UART, &uc_char);
		if (!uc_flag) {
			switch (uc_char) {
			case 's':
			case 'S':
				if (gs_uc_trans_mode == PDC_TRANSFER) {
					/* Transfer to no PDC communication mode. */
					/* Disable PDC controller. */
					pdc_disable_transfer(g_p_pdc,
							PERIPH_PTCR_RXTDIS | PERIPH_PTCR_TXTDIS);
					/* Disable the RXBUFF interrupt. */
					usart_disable_interrupt(BOARD_USART, US_IDR_RXBUFF);

					/* Clear USART controller. */
					usart_clear();

					/* Enable the RXRDY interrupt. */
					usart_enable_interrupt(BOARD_USART, US_IER_RXRDY);
					gs_uc_trans_mode = BYTE_TRANSFER;

					puts("-I- Transfer without PDC \r");
				} else if (gs_uc_trans_mode == BYTE_TRANSFER) {
					pdc_enable_transfer(g_p_pdc,
							PERIPH_PTCR_RXTEN | PERIPH_PTCR_TXTEN);
					/* Clear USART controller. */
					usart_clear();

					/* Reset pdc current buffer size. */
					gs_ul_size_buffer = BUFFER_SIZE;
					gs_ul_size_nextbuffer = BUFFER_SIZE;
					gs_uc_buf_num = 0;

					/* Start receiving data. */
					g_st_packet.ul_addr =
							(uint32_t)gs_puc_buffer[gs_uc_buf_num];
					g_st_packet.ul_size = BUFFER_SIZE;
					g_st_nextpacket.ul_addr =
							(uint32_t)gs_puc_nextbuffer[gs_uc_buf_num];
					g_st_nextpacket.ul_size = BUFFER_SIZE;
					pdc_rx_init(g_p_pdc, &g_st_packet, &g_st_nextpacket);
					
					/* Transfer to PDC communication mode, disable RXRDY interrupt and enable RXBUFF interrupt. */
					usart_disable_interrupt(BOARD_USART, US_IER_RXRDY);
					usart_enable_interrupt(BOARD_USART, US_IER_RXBUFF);

					gs_uc_trans_mode = PDC_TRANSFER;
					puts("-I- Transfer with PDC \r");
				}

				break;

			case 'm':
			case 'M':
				display_main_menu();
				break;

			default:
				break;
			}
		}
	}
}
