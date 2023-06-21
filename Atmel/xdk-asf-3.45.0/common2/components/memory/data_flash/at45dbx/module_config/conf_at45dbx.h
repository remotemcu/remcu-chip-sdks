/**
 * \file
 *
 * \brief AT45DBX configuration file.
 *
 * This file contains the possible external configuration of the AT45DBX.
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


#ifndef _CONF_AT45DBX_H_
#define _CONF_AT45DBX_H_

#include "at45dbx.h"
#include <board.h>

#warning "Using a default at45dbx configuration: edit and modify the file conf_at45dbx.h depending on the application."

//! Size of AT45DBX data flash memories to manage.
#define AT45DBX_MEM_SIZE            AT45DBX_8MB

//! Number of AT45DBX components to manage.
#define AT45DBX_MEM_CNT             1

//! SPI master speed in Hz.
#define AT45DBX_CLOCK_SPEED         9600

#ifdef EXT2_SPI_MODULE
//! Select the SPI module AT45DBX is connected to
#  define AT45DBX_SPI                 EXT2_SPI_MODULE
#  define AT45DBX_SPI_PINMUX_SETTING  EXT2_SPI_SERCOM_MUX_SETTING
#  define AT45DBX_SPI_PINMUX_PAD0     EXT2_SPI_SERCOM_PINMUX_PAD0
#  define AT45DBX_SPI_PINMUX_PAD1     EXT2_SPI_SERCOM_PINMUX_PAD1
#  define AT45DBX_SPI_PINMUX_PAD2     EXT2_SPI_SERCOM_PINMUX_PAD2
#  define AT45DBX_SPI_PINMUX_PAD3     EXT2_SPI_SERCOM_PINMUX_PAD3
#  define AT45DBX_CS                  EXT2_PIN_15
#else
#  define AT45DBX_SPI                 0
#  define AT45DBX_SPI_PINMUX_SETTING  0
#  define AT45DBX_SPI_PINMUX_PAD0     0
#  define AT45DBX_SPI_PINMUX_PAD1     0
#  define AT45DBX_SPI_PINMUX_PAD2     0
#  define AT45DBX_SPI_PINMUX_PAD3     0
#  define AT45DBX_CS                  0
#endif
/*
 * For ATSAMR21G18-MR210UA, AT45DB041E is connected to ATSAMR21G18A on board.
 * pins connections as below:
 * #define AT45DBX_SPI                 SERCOM5
 * #define AT45DBX_SPI_PINMUX_SETTING  SPI_SIGNAL_MUX_SETTING_K
 * #define AT45DBX_SPI_PINMUX_PAD0     PINMUX_UNUSED
 * #define AT45DBX_SPI_PINMUX_PAD1     PINMUX_PB03D_SERCOM5_PAD1
 * #define AT45DBX_SPI_PINMUX_PAD2     PINMUX_PB22D_SERCOM5_PAD2
 * #define AT45DBX_SPI_PINMUX_PAD3     PINMUX_PB23D_SERCOM5_PAD3
 * #define AT45DBX_CS                  PIN_PB02
 */

#endif  // _CONF_AT45DBX_H_
