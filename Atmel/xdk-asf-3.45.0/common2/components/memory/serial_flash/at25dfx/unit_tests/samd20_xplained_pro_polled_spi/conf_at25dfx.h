/**
 * \file
 *
 * \brief AT25DFx configuration.
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

#ifndef CONF_AT25DFX_H_INCLUDED
#define CONF_AT25DFX_H_INCLUDED

#include <board.h>
#include "at25dfx.h"

//! Select the SPI module AT25DFx is connected to
#define AT25DFX_SPI                 EXT1_SPI_MODULE

/** AT25DFx device type */
#define AT25DFX_MEM_TYPE            AT25DFX_081A

#define AT25DFX_SPI_PINMUX_SETTING  EXT1_SPI_SERCOM_MUX_SETTING
#define AT25DFX_SPI_PINMUX_PAD0     EXT1_SPI_SERCOM_PINMUX_PAD0
#define AT25DFX_SPI_PINMUX_PAD1     PINMUX_UNUSED
#define AT25DFX_SPI_PINMUX_PAD2     EXT1_SPI_SERCOM_PINMUX_PAD2
#define AT25DFX_SPI_PINMUX_PAD3     EXT1_SPI_SERCOM_PINMUX_PAD3

#define AT25DFX_CS                  EXT1_PIN_SPI_SS_0 

//! SPI master speed in Hz.
#define AT25DFX_CLOCK_SPEED         1000000

#endif  /* CONF_AT25DFX_H_INCLUDED */
