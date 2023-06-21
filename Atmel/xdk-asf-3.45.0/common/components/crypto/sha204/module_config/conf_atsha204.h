/**
 * \file
 *
 * \brief ATSHA204 CryptoAuth driver configuration file
 *
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
#ifndef CONF_ATSHA204_H_INCLUDED
#define CONF_ATSHA204_H_INCLUDED

#include <board.h>

#if BOARD == XMEGA_A1_XPLAINED
// Interface configuration for XMEGA-A1 Xplained
#  define ATSHA204_TWI_PORT         (&TWIC)

#else
// Interface configuration for other boards
#  warning ATSHA204 TWI port is not set for your board. Please see conf_atsha204.h.
#  define ATSHA204_TWI_PORT         (&TWIC)
#endif // BOARD

// Xplain board independent configuration
#define ATSHA204_TWI_SPEED      	(400000)

//! TWI address used at SHA204 library startup
#define SHA204_I2C_DEFAULT_ADDRESS  (0xCA)

#endif /* CONF_ATSHA204_H_INCLUDED */
