/**
 * \file
 *
 * \brief AVR XMEGA USART in SPI mode driver functions.
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
#include "usart_spi.h"
#include "sysclk.h"

void usart_spi_init(USART_t *usart)
{
#ifdef USARTC0
	if((uint16_t)usart == (uint16_t)&USARTC0) {
		sysclk_enable_module(SYSCLK_PORT_C,PR_USART0_bm);
	}
#endif
#ifdef USARTC1
	else
	if((uint16_t)usart == (uint16_t)&USARTC1) {
		sysclk_enable_module(SYSCLK_PORT_C,PR_USART1_bm);
	}
#endif
#ifdef USARTD0
	else
	if((uint16_t)usart == (uint16_t)&USARTD0) {
		sysclk_enable_module(SYSCLK_PORT_D,PR_USART0_bm);
	}
#endif
#ifdef USARTD1
	else
	if((uint16_t)usart == (uint16_t)&USARTD1) {
		sysclk_enable_module(SYSCLK_PORT_D,PR_USART1_bm);
	}
#endif
#ifdef USARTE0
	else
	if((uint16_t)usart == (uint16_t)&USARTE0) {
		sysclk_enable_module(SYSCLK_PORT_E,PR_USART0_bm);
	}
#endif
#ifdef USARTE1
	else
	if((uint16_t)usart == (uint16_t)&USARTE1) {
		sysclk_enable_module(SYSCLK_PORT_E,PR_USART1_bm);
	}
#endif
#ifdef USARTF0
	else
	if((uint16_t)usart == (uint16_t)&USARTF0) {
		sysclk_enable_module(SYSCLK_PORT_F,PR_USART0_bm);
	}
#endif
#ifdef USARTF1
	else
	if((uint16_t)usart == (uint16_t)&USARTF1) {
		sysclk_enable_module(SYSCLK_PORT_F,PR_USART1_bm);
	}
#endif
}

void usart_spi_setup_device(USART_t *usart, struct usart_spi_device *device,
     spi_flags_t flags, unsigned long baud_rate,
     board_spi_select_id_t sel_id)
{
	usart_spi_options_t opt;
	opt.baudrate=baud_rate;
	opt.spimode=flags;
	opt.data_order=false;
	usart_init_spi(usart, &opt);
}

status_code_t usart_spi_write_packet(USART_t *usart,const uint8_t *data, size_t len)
{
	size_t i=0;
	while(len) {
		usart_spi_transmit(usart,*(data+i));
		len--;
		i++;
	}
	return STATUS_OK;
}

status_code_t usart_spi_read_packet(USART_t *usart, uint8_t *data, size_t len)
{
	while(len) {
		*data = usart_spi_transmit(usart, CONFIG_USART_SPI_DUMMY);
		len--;
		data++;
 	}
	return STATUS_OK;
}

void usart_spi_select_device(USART_t *usart, struct usart_spi_device *device)
{
	ioport_set_pin_low(device->id);
}

void usart_spi_deselect_device(USART_t *usart, struct usart_spi_device *device)
{
	ioport_set_pin_high(device->id);
}
