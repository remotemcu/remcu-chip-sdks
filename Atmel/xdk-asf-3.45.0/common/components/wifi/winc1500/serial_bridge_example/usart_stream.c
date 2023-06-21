/**
 *
 * \file
 *
 * \brief Serial Bridge.
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

#include "usart_stream.h"
#include <string.h>

static uint8_t usart_buffer[USART_BUFFER_MAX];
static uint32_t usart_recv_size = 0;

void configure_usart(uint32_t baudrate)
{
	usart_serial_options_t uart_serial_options = {
		.baudrate = baudrate,
		.paritytype = CONF_UART_PARITY,
		.charlength = US_MR_CHRL_8_BIT,
		.stopbits = 0,
	};

	/* Configure the UART console. */
	usart_serial_init((usart_if)CONF_UART, &uart_serial_options);

	usart_stream_reset();
}

void usart_stream_reset(void)
{
#ifdef SAMG55
	usart_reset_rx((Usart *)CONF_UART);
	usart_enable_rx((Usart *)CONF_UART);
#else
	uart_reset((Uart *)CONF_UART);
	uart_enable((Uart *)CONF_UART);
#endif
	usart_recv_size = 0;
}

void usart_stream_write(uint8_t data)
{
	usart_serial_putchar((usart_if)CONF_UART, data);
#ifdef SAMG55
	while (!usart_is_tx_empty((Usart *)CONF_UART)) {
#else
	while (!uart_is_tx_buf_empty((Uart *)CONF_UART)) {
#endif
	}
}

void usart_stream_write_buffer(uint8_t *data, uint32_t size)
{
	for (uint32_t i = 0; i < size; i++) {
		usart_serial_putchar((usart_if)CONF_UART, data[i]);
	}
}

int usart_stream_read(uint8_t **data, uint32_t *size)
{
#ifdef SAMG55
	uint32_t val;
	
	while (usart_recv_size < sizeof(usart_buffer) && usart_read((Usart *)CONF_UART, &val) == 0) {
#else
	uint8_t val;

	while (usart_recv_size < sizeof(usart_buffer) && uart_read((Uart *)CONF_UART, &val) == 0) {
#endif
		usart_buffer[usart_recv_size++] = val;
	}

	*data = usart_buffer;
	*size = usart_recv_size;

	return 0;
}

void usart_stream_move(uint32_t offset)
{
	usart_recv_size -= offset;
	if (usart_recv_size > 0) {
		memmove(usart_buffer, usart_buffer + offset, usart_recv_size);
	} else {
		usart_recv_size = 0;
	}
}
