/**
 * \file
 *
 * \brief Debug print configuration
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

#ifndef CONF_DBG_PRINT_H
#define CONF_DBG_PRINT_H

#include <board.h>

#define CONF_DBG_PRINT_SERCOM        EDBG_CDC_MODULE
#define CONF_DBG_PRINT_BUFFER_SIZE   128
#define CONF_DBG_PRINT_GCLK_SOURCE   GCLK_GENERATOR_0
// #define CONF_DBG_PRINT_BAUD_RATE     9600
// This BAUD value gives 9600 baud with 48 MHz GCLK
#define CONF_DBG_PRINT_BAUD_VALUE    65326

#define CONF_DBG_PRINT_SERCOM_MUX    EDBG_CDC_SERCOM_MUX_SETTING
#define CONF_DBG_PRINT_PINMUX_PAD0   EDBG_CDC_SERCOM_PINMUX_PAD0
#define CONF_DBG_PRINT_PINMUX_PAD1   EDBG_CDC_SERCOM_PINMUX_PAD1
#define CONF_DBG_PRINT_PINMUX_PAD2   EDBG_CDC_SERCOM_PINMUX_PAD2
#define CONF_DBG_PRINT_PINMUX_PAD3   EDBG_CDC_SERCOM_PINMUX_PAD3

#endif // CONF_DBG_PRINT_H
