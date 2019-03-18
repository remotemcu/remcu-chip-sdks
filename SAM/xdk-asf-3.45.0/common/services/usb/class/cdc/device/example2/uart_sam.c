/**
 * \file
 *
 * \brief UART functions
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include "conf_example.h"
#include "uart.h"
#include "main.h"
#include "ui.h"

static sam_usart_opt_t usart_options;

static Usart* get_usart(uint8_t port)
{
	Usart* usart;
	if (0 == port) {
		usart = USART_BASE_0;
	} else if (1 == port) {
		usart = USART_BASE_1;
	} else {
		return NULL;
	}
	return usart;
}

static void usart_handler(uint8_t port)
{
	Usart* usart = get_usart(port);
	uint32_t sr = usart_get_status(usart);
	if (sr & US_CSR_RXRDY) {
		// Data received
		ui_com_tx_start();
		uint32_t value;
		bool b_error = usart_read(usart, &value) ||
			(sr & (US_CSR_FRAME | US_CSR_TIMEOUT | US_CSR_PARE));
		if (b_error) {
			usart_reset_rx(usart);
			usart_enable_rx(usart);
			udi_cdc_multi_signal_framing_error(port);
			ui_com_error();
		}
		// Transfer UART RX fifo to CDC TX
		if (!udi_cdc_multi_is_tx_ready(port)) {
			// Fifo full
			udi_cdc_multi_signal_overrun(port);
			ui_com_overflow();
		} else {
			udi_cdc_multi_putc(port, value);
		}
		ui_com_tx_stop();
		return;
	}

	if (sr & US_CSR_TXRDY) {
		// Data send
		if (udi_cdc_multi_is_rx_ready(port)) {
			// Transmit next data
			ui_com_rx_start();
			int c = udi_cdc_multi_getc(port);
			usart_write(usart, c);
			
		} else {
			// Fifo empty then Stop UART transmission
			usart_disable_tx(usart);
			usart_disable_interrupt(usart, US_IDR_TXRDY);
			ui_com_rx_stop();
		}
	}
}

ISR(USART_HANDLER_0)
{
	usart_handler(0);
}

ISR(USART_HANDLER_1)
{
	usart_handler(1);
}

void uart_rx_notify(uint8_t port)
{
	Usart* usart = get_usart(port);
	// If UART is open
	if (usart_get_interrupt_mask(usart)
		& US_IMR_RXRDY) {
		// Enable UART TX interrupt to send a new value
		usart_enable_tx(usart);
		usart_enable_interrupt(usart, US_IER_TXRDY);
	}
}


void uart_config(uint8_t port, usb_cdc_line_coding_t * cfg)
{
	Usart* usart = get_usart(port);
	uint32_t stopbits, parity, databits;
	uint32_t imr;

	switch (cfg->bCharFormat) {
	case CDC_STOP_BITS_2:
		stopbits = US_MR_NBSTOP_2_BIT;
		break;
	case CDC_STOP_BITS_1_5:
		stopbits = US_MR_NBSTOP_1_5_BIT;
		break;
	case CDC_STOP_BITS_1:
	default:
		// Default stop bit = 1 stop bit
		stopbits = US_MR_NBSTOP_1_BIT;
		break;
	}

	switch (cfg->bParityType) {
	case CDC_PAR_EVEN:
		parity = US_MR_PAR_EVEN;
		break;
	case CDC_PAR_ODD:
		parity = US_MR_PAR_ODD;
		break;
	case CDC_PAR_MARK:
		parity = US_MR_PAR_MARK;
		break;
	case CDC_PAR_SPACE:
		parity = US_MR_PAR_SPACE;
		break;
	default:
	case CDC_PAR_NONE:
		parity = US_MR_PAR_NO;
		break;
	}
	
	switch(cfg->bDataBits) {
	case 5: case 6: case 7:
		databits = cfg->bDataBits - 5;
		break;
	default:
	case 8:
		databits = US_MR_CHRL_8_BIT;
		break;
	}

	// Options for USART.
	usart_options.baudrate = LE32_TO_CPU(cfg->dwDTERate);
	usart_options.char_length = databits;
	usart_options.parity_type = parity;
	usart_options.stop_bits = stopbits;
	usart_options.channel_mode = US_MR_CHMODE_NORMAL;
	imr = usart_get_interrupt_mask(usart);
	usart_disable_interrupt(usart, 0xFFFFFFFF);
	usart_init_rs232(usart, &usart_options,
			sysclk_get_peripheral_hz());
	// Restore both RX and TX
	usart_enable_tx(usart);
	usart_enable_rx(usart);
	usart_enable_interrupt(usart, imr);
}

void uart_open(uint8_t port)
{
	Usart* usart = get_usart(port);

	if (0 == port) {
		// IO is initialized in board init
		// Enable interrupt with priority higher than USB
		NVIC_SetPriority((IRQn_Type) USART_ID_0, USART_INT_LEVEL_0);
		NVIC_EnableIRQ((IRQn_Type) USART_ID_0);
		NVIC_SetPriority((IRQn_Type) USART_ID_1, USART_INT_LEVEL_1);
		NVIC_EnableIRQ((IRQn_Type) USART_ID_1);
		// Initialize it in RS232 mode.
		pmc_enable_periph_clk(USART_ID_0);
		USART_ENABLE_0();
	} else if (1 == port) {
		// IO is initialized in board init
		// Enable interrupt with priority higher than USB
		NVIC_SetPriority((IRQn_Type) USART_ID_1, USART_INT_LEVEL_1);
		NVIC_EnableIRQ((IRQn_Type) USART_ID_1);
		// Initialize it in RS232 mode.
		pmc_enable_periph_clk(USART_ID_1);
		USART_ENABLE_1();
	} else {
		return;
	}
	if (usart_init_rs232(usart, &usart_options,
				sysclk_get_peripheral_hz())) {
		return;
	}
	// Enable both RX and TX
	usart_enable_tx(usart);
	usart_enable_rx(usart);
	// Enable interrupts
	usart_enable_interrupt(usart, US_IER_RXRDY | US_IER_TXRDY);
}

void uart_close(uint8_t port)
{
	if (0 == port) {
		// Disable interrupts
		usart_disable_interrupt(USART_BASE_0, 0xFFFFFFFF);
		// Close RS232 communication
		USART_DISABLE_0();
	}
	else if (1 == port) {
		// Disable interrupts
		usart_disable_interrupt(USART_BASE_1, 0xFFFFFFFF);
		// Close RS232 communication
		USART_DISABLE_1();
	}
}
