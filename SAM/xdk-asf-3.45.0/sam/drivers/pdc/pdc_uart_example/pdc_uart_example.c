/**
 * \file
 *
 * \brief SAM Peripheral DMA Controller Example.
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

#include <asf.h>
#include <stdio_serial.h>
#include <conf_board.h>
#include <conf_pdc_uart_example.h>

#define BUFFER_SIZE  5

#define STRING_EOL    "\r"
#define STRING_HEADER "-- PDC_UART Example --\r\n" \
"-- "BOARD_NAME" --\r\n" \
"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/* Pdc transfer buffer */
uint8_t g_uc_pdc_buffer[BUFFER_SIZE];
/* PDC data packet for transfer */
pdc_packet_t g_pdc_uart_packet;
/* Pointer to UART PDC register base */
Pdc *g_p_uart_pdc;

/**
 * \brief Interrupt handler for UART interrupt.
 */

//! [int_handler]
void console_uart_irq_handler(void)
{
	/* Get UART status and check if PDC receive buffer is full */
	if ((uart_get_status(CONSOLE_UART) & UART_SR_RXBUFF) == UART_SR_RXBUFF) {
		/* Configure PDC for data transfer (RX and TX) */
		pdc_rx_init(g_p_uart_pdc, &g_pdc_uart_packet, NULL);
		pdc_tx_init(g_p_uart_pdc, &g_pdc_uart_packet, NULL);
	}
}
//! [int_handler]

/**
 * \brief Configure UART console.
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
 * \brief Application entry point for pdc_uart example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Initialize the SAM system */

	//! [board_setup]
	sysclk_init();
	board_init();
	//! [board_setup]

	/* Initialize the UART console */
	configure_console();

	/* Output example information */
	puts(STRING_HEADER);

	//! [pdc_config]
	/* Get pointer to UART PDC register base */
	g_p_uart_pdc = uart_get_pdc_base(CONSOLE_UART);

	/* Initialize PDC data packet for transfer */
	g_pdc_uart_packet.ul_addr = (uint32_t) g_uc_pdc_buffer;
	g_pdc_uart_packet.ul_size = BUFFER_SIZE;

	/* Configure PDC for data receive */
	pdc_rx_init(g_p_uart_pdc, &g_pdc_uart_packet, NULL);

	/* Enable PDC transfers */
	pdc_enable_transfer(g_p_uart_pdc, PERIPH_PTCR_RXTEN | PERIPH_PTCR_TXTEN);
	//! [pdc_config]

	/* Enable UART IRQ */
	//! [uart_irq]
	uart_enable_interrupt(CONSOLE_UART, UART_IER_RXBUFF);
	//! [uart_irq]

	/* Enable UART interrupt */
	//! [uart_nvic_irq]
	NVIC_EnableIRQ(CONSOLE_UART_IRQn);
	//! [uart_nvic_irq]

	//! [busy_waiting]
	while (1) {
	}
	//! [busy_waiting]
}
