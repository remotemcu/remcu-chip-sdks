/**
 * \file
 *
 * \brief SAM D21 Console configuration
 *
 * Copyright (c) 2017-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef CONF_CONSOLE_H_
#define CONF_CONSOLE_H_

#include <asf.h>
#include "stdio_serial.h"

/** UART module for debug. */
static struct usart_module cdc_uart_module;
#define CONF_STDIO_USART_MODULE  EDBG_CDC_MODULE
#define CONF_STDIO_MUX_SETTING   EDBG_CDC_SERCOM_MUX_SETTING
#define CONF_STDIO_PINMUX_PAD0   EDBG_CDC_SERCOM_PINMUX_PAD0
#define CONF_STDIO_PINMUX_PAD1   EDBG_CDC_SERCOM_PINMUX_PAD1
#define CONF_STDIO_PINMUX_PAD2   EDBG_CDC_SERCOM_PINMUX_PAD2
#define CONF_STDIO_PINMUX_PAD3   EDBG_CDC_SERCOM_PINMUX_PAD3
#define CONF_STDIO_BAUDRATE      115200
/**
 *  Configure UART console.
 */
static inline void configure_console(void)
{
	struct usart_config usart_conf;
	usart_get_config_defaults(&usart_conf);
	usart_conf.mux_setting = CONF_STDIO_MUX_SETTING;
	usart_conf.pinmux_pad0 = CONF_STDIO_PINMUX_PAD0;
	usart_conf.pinmux_pad1 = CONF_STDIO_PINMUX_PAD1;
	usart_conf.pinmux_pad2 = CONF_STDIO_PINMUX_PAD2;
	usart_conf.pinmux_pad3 = CONF_STDIO_PINMUX_PAD3;
	usart_conf.baudrate    = CONF_STDIO_BAUDRATE;
	stdio_serial_init(&cdc_uart_module, CONF_STDIO_USART_MODULE, &usart_conf);
	usart_enable(&cdc_uart_module);
}

#endif /* CONF_CONSOLE_H_ */