/**
 * \file
 *
 * \brief Peripheral DMA Controller Example for SAM.
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
 * \mainpage Peripheral DMA Controller Example
 *
 * \section Purpose
 *
 * The pdc_usart example demonstrates how to use PDC driver to receive/send 
 * data from/to the USART.
 *
 * \section Requirements
 *
 * This example can be used on samg55j19_samg_xplained_pro.
 *
 * \section Description
 *
 * The SAM controller waits for BUFFER_SIZE data to receive from the USART.
 * As soon as the expected amount of data is received, the whole buffer is 
 * sent back to the terminal.
 *
 * \section Usage
 *
 * -# Build the program and download it into the evaluation board.
 * -# On the computer, open and configure a terminal application
 *    (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# In the terminal window, the following text should appear (values depend
 *    on the board and chip used):
 *    \code
	-- PDC Usart Example xxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 * -# the sent text should appear.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "stdio_serial.h"
#include "conf_board.h"
#include "conf_pdc_usart_example.h"

#define BUFFER_SIZE  5

#define STRING_EOL    "\r"
#define STRING_HEADER "-- PDC_USART Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/* Pdc transfer buffer */
uint8_t g_uc_pdc_buffer[BUFFER_SIZE];
/* PDC data packet for transfer */
pdc_packet_t g_pdc_usart_packet;
/* Pointer to USART PDC register base */
Pdc *g_p_usart_pdc;

/**
 * \brief Interrupt handler for USART interrupt.
 */
void console_usart_irq_handler(void)
{
	/* Get USART status and check if PDC receive buffer is full */
	if ((usart_get_status(CONSOLE_UART) & US_CSR_RXBUFF) == US_CSR_RXBUFF) {
		/* Configure PDC for data transfer (RX and TX) */
		pdc_rx_init(g_p_usart_pdc, &g_pdc_usart_packet, NULL);
		pdc_tx_init(g_p_usart_pdc, &g_pdc_usart_packet, NULL);
	}
}

/**
 * \brief Configure UART console.
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
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief Application entry point for pdc_usart example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Initialize the SAM system */
	sysclk_init();
	board_init();    

	/* Initialize the UART console */
	configure_console();

	/* Output example information */
	puts(STRING_HEADER);

	/* Get pointer to USART PDC register base */
	g_p_usart_pdc = usart_get_pdc_base(CONSOLE_UART);

	/* Initialize PDC data packet for transfer */
	g_pdc_usart_packet.ul_addr = (uint32_t) g_uc_pdc_buffer;
	g_pdc_usart_packet.ul_size = BUFFER_SIZE;

	/* Configure PDC for data receive */
	pdc_rx_init(g_p_usart_pdc, &g_pdc_usart_packet, NULL);

	/* Enable PDC transfers */
	pdc_enable_transfer(g_p_usart_pdc, PERIPH_PTCR_RXTEN | PERIPH_PTCR_TXTEN);

	/* Enable USART IRQ */
	usart_enable_interrupt(CONSOLE_UART, US_IER_RXBUFF);

	/* Enable USART interrupt */
	NVIC_EnableIRQ(CONSOLE_USART_IRQn);

	while (1) {
	}
}
