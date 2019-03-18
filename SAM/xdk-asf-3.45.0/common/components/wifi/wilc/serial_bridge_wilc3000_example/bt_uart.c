/**
 * \file
 *
 * \brief Configurations for the WILC3000 Serial Bridge Application
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
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


#include "bt_uart.h"
#include "uart_stream.h"
#include <string.h>

static uint8_t bt_usart_buffer[USART_BUFFER_MAX];
static uint32_t usart_recv_size = 0;

/** All interrupt mask. */
#define ALL_INTERRUPT_MASK  0xffffffff
/** USART is reading. */
#define STATE_READ          0
/** USART is writing. */
#define STATE_WRITE         1

/** Buffer for receiving. */
int8_t g_c_recv_buff[USART_BUFFER_MAX] = { 0 };

/** Reception is done. */
/** Sending is done. */
volatile uint32_t g_ul_sent_done = false;

/** State of reading or writing. */
uint8_t g_uc_state = STATE_WRITE;

/** PDC data packet. */
pdc_packet_t g_st_packet;

/** Pointer to PDC register base. */
Pdc *g_p_pdc;

uint8_t read_buffer[12];

uint8_t *tx_buffer = NULL;
uint32_t tx_size = 0;
extern uint8_t hci_recv_buffer[13];
/**
 * \brief USART IRQ handler.
 *
 * Interrupt handler for USART. After reception is done, set g_ul_recv_done to true,
 * and if transmission is done, set g_ul_sent_done to true.
 *
 */
void USART1_Handler(void)
{
	uint32_t ul_status;

	/* Read USART Status. */
	ul_status = usart_get_status(BT_CONF_UART);

	/* Receive buffer is full. */
	if ((ul_status & US_CSR_RXBUFF) && (g_uc_state == STATE_READ)) {
		usart_disable_interrupt(BT_CONF_UART, US_IDR_RXBUFF);
		usart_stream_write_buffer(hci_recv_buffer,g_st_packet.ul_size);
	}
	if ((ul_status & US_CSR_TXBUFE) && (g_uc_state == STATE_WRITE)) {
		g_ul_sent_done = true;
		usart_disable_interrupt(BT_CONF_UART, US_IDR_TXBUFE);
	}
}

void bt_usart_stream_write_buffer(uint8_t *data, uint32_t size)
{
	for (uint32_t i = 0; i < size; i++) {
		usart_serial_putchar((usart_if)BT_CONF_UART, data[i]);
#ifdef SAMG55
	while (!usart_is_tx_empty((Usart *)BT_CONF_UART)) {}
#else
	while (!uart_is_tx_buf_empty((Uart *)BT_CONF_UART)) {}
#endif
	}
}

static void usart_clear(void)
{
	/* Reset and disable receiver & transmitter. */
	usart_reset_rx(BT_CONF_UART);
	usart_reset_tx(BT_CONF_UART);

	/* Clear PDC counter. */
	g_st_packet.ul_addr = 0;
	g_st_packet.ul_size = 0;
	pdc_rx_init(g_p_pdc, &g_st_packet, NULL);
	pdc_tx_init(g_p_pdc, &g_st_packet, NULL);

	/* Enable receiver & transmitter. */
	usart_enable_tx(BT_CONF_UART);
	usart_enable_rx(BT_CONF_UART);
}

void bt_usart_receive(uint8_t *buffer,uint32_t size)
{
	g_uc_state = STATE_READ;
	usart_clear();
	g_st_packet.ul_addr = (uint32_t)buffer;
	g_st_packet.ul_size = size;
	pdc_rx_init(g_p_pdc, &g_st_packet, NULL);
	usart_enable_interrupt(BT_CONF_UART, US_IER_RXBUFF);
}

void bt_usart_transfer(uint8_t *buffer,uint32_t size)
{
	g_uc_state = STATE_WRITE;
 	usart_clear();
	g_ul_sent_done = false;
	g_st_packet.ul_addr = (uint32_t)buffer;
	g_st_packet.ul_size = size;
	pdc_tx_init(g_p_pdc, &g_st_packet, NULL);
	usart_enable_interrupt(BT_CONF_UART, US_IER_TXBUFE);
	while (!g_ul_sent_done) {}

}

/**
 * \brief Configure USART in normal (serial rs232) mode, asynchronous,
 * 8 bits, 1 stop bit, no parity, 115200 bauds and enable its transmitter
 * and receiver.
 */
 void bt_configure_usart(uint32_t baudrate)
 {
	usart_serial_options_t uart_serial_options = {
		.baudrate = baudrate,
		.paritytype = CONF_STDIO_PARITY,
		.charlength = US_MR_CHRL_8_BIT,
		.stopbits = 0,
	};

	/* Enable the peripheral clock in the PMC. */
	sysclk_enable_peripheral_clock(ID_USART1);

	gpio_configure_group(PIOA, (PIO_PA21A_RXD1|PIO_PA22A_TXD1), PINS_UART1_FLAGS);
	
	/* Configure the UART console. */
	usart_serial_init((usart_if)BT_CONF_UART, &uart_serial_options);

	/* Disable all the interrupts. */
	usart_disable_interrupt(BT_CONF_UART, ALL_INTERRUPT_MASK);

	/* Enable the receiver and transmitter. */
	usart_enable_tx(BT_CONF_UART);
	usart_enable_rx(BT_CONF_UART);

	/* Configure and enable interrupt of USART. */
	NVIC_EnableIRQ(USART1_IRQn);

	/* Get board USART PDC base address and enable receiver and transmitter. */
	g_p_pdc = usart_get_pdc_base(BT_CONF_UART);
	pdc_enable_transfer(g_p_pdc, PERIPH_PTCR_RXTEN | PERIPH_PTCR_TXTEN);	
}

