/**
 * \file
 *
 * \brief SAML21 USART configuration.
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

#ifndef CONF_TEST_H
#define CONF_TEST_H

#include <board.h>
//! [conf_uart_serial_settings]
#define CONF_STDIO_USART_MODULE  EDBG_CDC_MODULE
#define CONF_STDIO_MUX_SETTING   EDBG_CDC_SERCOM_MUX_SETTING
#define CONF_STDIO_PINMUX_PAD0   EDBG_CDC_SERCOM_PINMUX_PAD0
#define CONF_STDIO_PINMUX_PAD1   EDBG_CDC_SERCOM_PINMUX_PAD1
#define CONF_STDIO_PINMUX_PAD2   EDBG_CDC_SERCOM_PINMUX_PAD2
#define CONF_STDIO_PINMUX_PAD3   EDBG_CDC_SERCOM_PINMUX_PAD3
#define CONF_STDIO_BAUDRATE      38400
//! [conf_uart_serial_settings]
#endif // CONF_TEST_H