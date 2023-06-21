/**
 * \file
 *
 * \brief SSD1306 display controller driver configuration file.
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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
#ifndef CONF_SSD1306_H_INCLUDED
#define CONF_SSD1306_H_INCLUDED

#include <board.h>

#ifdef EXT3_SPI_MODULE
/* Interface configuration for SAM Xplained Pro */
#  define SSD1306_SPI                 EXT3_SPI_MODULE
#  define CONFIG_SSD1306_FRAMEBUFFER

#  define SSD1306_DC_PIN              EXT3_PIN_5
#  define SSD1306_RES_PIN             EXT3_PIN_10
#  define SSD1306_CS_PIN              EXT3_PIN_15

#  define SSD1306_SPI_PINMUX_SETTING  EXT3_SPI_SERCOM_MUX_SETTING
#  define SSD1306_SPI_PINMUX_PAD0     EXT3_SPI_SERCOM_PINMUX_PAD0
#  define SSD1306_SPI_PINMUX_PAD1     PINMUX_UNUSED
#  define SSD1306_SPI_PINMUX_PAD2     EXT3_SPI_SERCOM_PINMUX_PAD2
#  define SSD1306_SPI_PINMUX_PAD3     EXT3_SPI_SERCOM_PINMUX_PAD3
#else
/* Dummy Interface configuration */
#  define SSD1306_SPI                 0
#  define CONFIG_SSD1306_FRAMEBUFFER

#  define SSD1306_DC_PIN              0
#  define SSD1306_RES_PIN             0
#  define SSD1306_CS_PIN              0

#  define SSD1306_SPI_PINMUX_SETTING  0
#  define SSD1306_SPI_PINMUX_PAD0     0
#  define SSD1306_SPI_PINMUX_PAD1     0
#  define SSD1306_SPI_PINMUX_PAD2     0
#  define SSD1306_SPI_PINMUX_PAD3     0
#endif

/* Minimum clock period is 50ns@3.3V -> max frequency is 20MHz */
#define SSD1306_CLOCK_SPEED           1000000UL
#define SSD1306_DISPLAY_CONTRAST_MAX  40
#define SSD1306_DISPLAY_CONTRAST_MIN  30

#endif /* CONF_SSD1306_H_INCLUDED */
