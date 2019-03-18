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


/* Structure for USART module connected to EDBG */
struct usart_module usart_module_edbg;

/* Structure for USART parameter configuration */
struct usart_config usart_conf;

/* Data for EDBG communication */
static uint8_t tx_data;
static uint8_t rx_data;

/* USART TX callback flag */
static volatile uint8_t tx_callback_flag = 0;

/**
 * \internal
 * \brief USART interrupt callback function
 *
 * Called by USART driver when transmit is complete.
 *
 * * \param module USART module causing the interrupt (not used)
 */
static void usart_tx_callback(struct usart_module *const module)
{
	tx_callback_flag = 1;
	/* Data ready to be sent */
	if (udi_cdc_is_rx_ready()) {
		/* Transmit next data */
		ui_com_rx_start();
		tx_data = udi_cdc_getc();
		usart_write_buffer_job(&usart_module_edbg, &tx_data, 1);
	} else {
		/* Fifo empty then Stop UART transmission */
		usart_disable_callback(&usart_module_edbg, USART_CALLBACK_BUFFER_TRANSMITTED);
		ui_com_rx_stop();
	}
	tx_callback_flag = 0;
}

/**
 * \internal
 * \brief USART interrupt callback function
 *
 * Called by USART driver when receiving is complete.
 *
 * * \param module USART module causing the interrupt (not used)
 */
static void usart_rx_callback(struct usart_module *const module)
{
	/* Data received */
	ui_com_tx_start();

	/* Transfer UART RX fifo to CDC TX */
	if (!udi_cdc_is_tx_ready()) {
		/* Fifo full */
		udi_cdc_signal_overrun();
		ui_com_overflow();
	} else {
		udi_cdc_putc(rx_data);
	}

	ui_com_tx_stop();

	usart_read_buffer_job(&usart_module_edbg, &rx_data, 1);

	return;
}

void uart_rx_notify(uint8_t port)
{
	UNUSED(port);
	if (!tx_callback_flag) {
		/* Transmit first data */
		ui_com_rx_start();
		usart_enable_callback(&usart_module_edbg, USART_CALLBACK_BUFFER_TRANSMITTED);
		tx_data = udi_cdc_getc();
		usart_write_buffer_job(&usart_module_edbg, &tx_data, 1);
	}
}

void uart_config(uint8_t port,usb_cdc_line_coding_t *cfg)
{
	UNUSED(port);
	/* Configure USART for unit test output */
	usart_get_config_defaults(&usart_conf);
	usart_conf.generator_source = GCLK_GENERATOR_3;

	switch (cfg->bCharFormat) {
	case CDC_STOP_BITS_2:
		usart_conf.stopbits = USART_STOPBITS_2;
		break;

	case CDC_STOP_BITS_1_5:
		usart_conf.stopbits = USART_STOPBITS_1;
		break;

	case CDC_STOP_BITS_1:
	default:
		/* Default stop bit = 1 stop bit */
		usart_conf.stopbits = USART_STOPBITS_1;
		break;
	}

	switch (cfg->bParityType) {
	case CDC_PAR_EVEN:
		usart_conf.parity = USART_PARITY_EVEN;
		break;

	case CDC_PAR_ODD:
		usart_conf.parity = USART_PARITY_ODD;
		break;

	case CDC_PAR_MARK:
		usart_conf.parity = USART_PARITY_NONE;
		break;

	case CDC_PAR_SPACE:
		usart_conf.parity = USART_PARITY_NONE;
		break;

	case CDC_PAR_NONE:
	default:
		usart_conf.parity = USART_PARITY_NONE;
		break;
	}

	switch(cfg->bDataBits) {
	case 5:
		usart_conf.character_size = USART_CHARACTER_SIZE_5BIT;
		break;
	case 6:
		usart_conf.character_size = USART_CHARACTER_SIZE_6BIT;
		break;
	case 7:
		usart_conf.character_size = USART_CHARACTER_SIZE_7BIT;
		break;
	case 8:
	default:
		usart_conf.character_size = USART_CHARACTER_SIZE_8BIT;
		break;
	}

	/* Options for USART. */
	usart_conf.baudrate = LE32_TO_CPU(cfg->dwDTERate);
	usart_conf.mux_setting = CONF_USART_MUX_SETTING;
	usart_conf.pinmux_pad0 = CONF_USART_PINMUX_PAD0;
	usart_conf.pinmux_pad1 = CONF_USART_PINMUX_PAD1;
	usart_conf.pinmux_pad2 = CONF_USART_PINMUX_PAD2;
	usart_conf.pinmux_pad3 = CONF_USART_PINMUX_PAD3;
	usart_disable(&usart_module_edbg);
	usart_init(&usart_module_edbg, CONF_USART_BASE, &usart_conf);
	usart_enable(&usart_module_edbg);

	/* Enable interrupts */
	usart_register_callback(&usart_module_edbg, usart_tx_callback,
			USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_enable_callback(&usart_module_edbg, USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_register_callback(&usart_module_edbg, usart_rx_callback,
			USART_CALLBACK_BUFFER_RECEIVED);
	usart_enable_callback(&usart_module_edbg, USART_CALLBACK_BUFFER_RECEIVED);
	usart_read_buffer_job(&usart_module_edbg, &rx_data, 1);
}

void uart_open(uint8_t port)
{
	UNUSED(port);

	usart_enable(&usart_module_edbg);
}

void uart_close(uint8_t port)
{
	UNUSED(port);
	/* Close RS232 communication */
	usart_disable(&usart_module_edbg);
}
