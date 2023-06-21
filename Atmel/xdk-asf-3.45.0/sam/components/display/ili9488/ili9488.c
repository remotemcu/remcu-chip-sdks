/**
 * \file
 *
 * \brief API driver for ILI9488 TFT display component.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

/**
 * \defgroup ili9488_display_group Display - ILI9488 Controller
 *
 * Low-level driver for the ILI9488 LCD controller. This driver provides access to the main
 * features of the ILI9488 controller.
 *
 * \{
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "ili9488.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "pio.h"
#ifdef ILI9488_EBIMODE
#  include "smc.h"
#  include "pmc.h"
#endif
#ifdef ILI9488_SPIMODE
#  include "spi_master.h"
#endif

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
 extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/* Pixel cache used to speed up communication */
#define LCD_DATA_CACHE_SIZE ILI9488_LCD_WIDTH
static ili9488_color_t g_ul_pixel_cache[LCD_DATA_CACHE_SIZE*LCD_DATA_COLOR_UNIT];

/* Global variable describing the font size used by the driver */
const struct ili9488_font gfont = {10, 14};
/**
 * Character set table for font 10x14
 * Coding format:
 * Char height is 14 bits, which is coded using 2 bytes per column (2 unused bits).
 * Char width is 10 bits.
 */
const uint8_t p_uc_charset10x14[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xCC,
	0xFF, 0xCC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xF0, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x0C, 0xC0, 0x0C, 0xC0, 0xFF, 0xFC, 0xFF, 0xFC, 0x0C, 0xC0,
	0x0C, 0xC0, 0xFF, 0xFC, 0xFF, 0xFC, 0x0C, 0xC0, 0x0C, 0xC0,
	0x0C, 0x60, 0x1E, 0x70, 0x3F, 0x30, 0x33, 0x30, 0xFF, 0xFC,
	0xFF, 0xFC, 0x33, 0x30, 0x33, 0xF0, 0x39, 0xE0, 0x18, 0xC0,
	0x60, 0x00, 0xF0, 0x0C, 0xF0, 0x3C, 0x60, 0xF0, 0x03, 0xC0,
	0x0F, 0x00, 0x3C, 0x18, 0xF0, 0x3C, 0xC0, 0x3C, 0x00, 0x18,
	0x3C, 0xF0, 0x7F, 0xF8, 0xC3, 0x1C, 0xC7, 0x8C, 0xCF, 0xCC,
	0xDC, 0xEC, 0x78, 0x78, 0x30, 0x30, 0x00, 0xFC, 0x00, 0xCC,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x00, 0xEC, 0x00,
	0xF8, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0F, 0xC0, 0x3F, 0xF0, 0x78, 0x78,
	0x60, 0x18, 0xC0, 0x0C, 0xC0, 0x0C, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xC0, 0x0C, 0xC0, 0x0C, 0x60, 0x18,
	0x78, 0x78, 0x3F, 0xF0, 0x0F, 0xC0, 0x00, 0x00, 0x00, 0x00,
	0x0C, 0x60, 0x0E, 0xE0, 0x07, 0xC0, 0x03, 0x80, 0x3F, 0xF8,
	0x3F, 0xF8, 0x03, 0x80, 0x07, 0xC0, 0x0E, 0xE0, 0x0C, 0x60,
	0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x3F, 0xF0,
	0x3F, 0xF0, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00,
	0x00, 0x44, 0x00, 0xEC, 0x00, 0xF8, 0x00, 0x70, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00,
	0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00,
	0x00, 0x18, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x18, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x0C, 0x00, 0x3C, 0x00, 0xF0, 0x03, 0xC0,
	0x0F, 0x00, 0x3C, 0x00, 0xF0, 0x00, 0xC0, 0x00, 0x00, 0x00,
	0x3F, 0xF0, 0x7F, 0xF8, 0xE0, 0xFC, 0xC1, 0xCC, 0xC3, 0x8C,
	0xC7, 0x0C, 0xCE, 0x0C, 0xFC, 0x1C, 0x7F, 0xF8, 0x3F, 0xF0,
	0x00, 0x00, 0x00, 0x00, 0x30, 0x0C, 0x70, 0x0C, 0xFF, 0xFC,
	0xFF, 0xFC, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00,
	0x30, 0x0C, 0x70, 0x1C, 0xE0, 0x3C, 0xC0, 0x7C, 0xC0, 0xEC,
	0xC1, 0xCC, 0xC3, 0x8C, 0xE7, 0x0C, 0x7E, 0x0C, 0x3C, 0x0C,
	0x30, 0x30, 0x70, 0x38, 0xE0, 0x1C, 0xC0, 0x0C, 0xC0, 0x0C,
	0xC3, 0x0C, 0xC3, 0x0C, 0xE3, 0x1C, 0x7F, 0xF8, 0x3C, 0xF0,
	0x03, 0xC0, 0x07, 0xC0, 0x0E, 0xC0, 0x1C, 0xC0, 0x38, 0xC0,
	0x70, 0xC0, 0xFF, 0xFC, 0xFF, 0xFC, 0x00, 0xC0, 0x00, 0xC0,
	0xFC, 0x30, 0xFC, 0x38, 0xCC, 0x1C, 0xCC, 0x0C, 0xCC, 0x0C,
	0xCC, 0x0C, 0xCC, 0x0C, 0xCE, 0x1C, 0xC7, 0xF8, 0xC3, 0xF0,
	0x3F, 0xF0, 0x7F, 0xF8, 0xE3, 0x1C, 0xC3, 0x0C, 0xC3, 0x0C,
	0xC3, 0x0C, 0xC3, 0x0C, 0xE3, 0x9C, 0x71, 0xF8, 0x30, 0xF0,
	0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC3, 0xFC,
	0xC7, 0xFC, 0xCE, 0x00, 0xDC, 0x00, 0xF8, 0x00, 0xF0, 0x00,
	0x3C, 0xF0, 0x7F, 0xF8, 0xE7, 0x9C, 0xC3, 0x0C, 0xC3, 0x0C,
	0xC3, 0x0C, 0xC3, 0x0C, 0xE7, 0x9C, 0x7F, 0xF8, 0x3C, 0xF0,
	0x3C, 0x00, 0x7E, 0x00, 0xE7, 0x0C, 0xC3, 0x0C, 0xC3, 0x1C,
	0xC3, 0x38, 0xC3, 0x70, 0xE7, 0xE0, 0x7F, 0xC0, 0x3F, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x60, 0x3C, 0xF0,
	0x3C, 0xF0, 0x18, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x44, 0x3C, 0xEC,
	0x3C, 0xF8, 0x18, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x03, 0x00, 0x07, 0x80, 0x0F, 0xC0, 0x1C, 0xE0,
	0x38, 0x70, 0x70, 0x38, 0xE0, 0x1C, 0xC0, 0x0C, 0x00, 0x00,
	0x0C, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0,
	0x0C, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0,
	0x00, 0x00, 0xC0, 0x0C, 0xE0, 0x1C, 0x70, 0x38, 0x38, 0x70,
	0x1C, 0xE0, 0x0F, 0xC0, 0x07, 0x80, 0x03, 0x00, 0x00, 0x00,
	0x30, 0x00, 0x70, 0x00, 0xE0, 0x00, 0xC0, 0x00, 0xC1, 0xEC,
	0xC3, 0xEC, 0xC3, 0x00, 0xE6, 0x00, 0x7E, 0x00, 0x3C, 0x00,
	0x30, 0xF0, 0x71, 0xF8, 0xE3, 0x9C, 0xC3, 0x0C, 0xC3, 0xFC,
	0xC3, 0xFC, 0xC0, 0x0C, 0xE0, 0x1C, 0x7F, 0xF8, 0x3F, 0xF0,
	0x3F, 0xFC, 0x7F, 0xFC, 0xE0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
	0xC0, 0xC0, 0xC0, 0xC0, 0xE0, 0xC0, 0x7F, 0xFC, 0x3F, 0xFC,
	0xFF, 0xFC, 0xFF, 0xFC, 0xC3, 0x0C, 0xC3, 0x0C, 0xC3, 0x0C,
	0xC3, 0x0C, 0xC3, 0x0C, 0xE7, 0x9C, 0x7F, 0xF8, 0x3C, 0xF0,
	0x3F, 0xF0, 0x7F, 0xF8, 0xE0, 0x1C, 0xC0, 0x0C, 0xC0, 0x0C,
	0xC0, 0x0C, 0xC0, 0x0C, 0xE0, 0x1C, 0x70, 0x38, 0x30, 0x30,
	0xFF, 0xFC, 0xFF, 0xFC, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0, 0x0C,
	0xC0, 0x0C, 0xC0, 0x0C, 0xE0, 0x1C, 0x7F, 0xF8, 0x3F, 0xF0,
	0xFF, 0xFC, 0xFF, 0xFC, 0xC3, 0x0C, 0xC3, 0x0C, 0xC3, 0x0C,
	0xC3, 0x0C, 0xC3, 0x0C, 0xC3, 0x0C, 0xC0, 0x0C, 0xC0, 0x0C,
	0xFF, 0xFC, 0xFF, 0xFC, 0xC3, 0x00, 0xC3, 0x00, 0xC3, 0x00,
	0xC3, 0x00, 0xC3, 0x00, 0xC3, 0x00, 0xC0, 0x00, 0xC0, 0x00,
	0x3F, 0xF0, 0x7F, 0xF8, 0xE0, 0x1C, 0xC0, 0x0C, 0xC0, 0x0C,
	0xC3, 0x0C, 0xC3, 0x0C, 0xE3, 0x1C, 0x73, 0xF8, 0x33, 0xF0,
	0xFF, 0xFC, 0xFF, 0xFC, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00,
	0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0xFF, 0xFC, 0xFF, 0xFC,
	0x00, 0x00, 0x00, 0x00, 0xC0, 0x0C, 0xC0, 0x0C, 0xFF, 0xFC,
	0xFF, 0xFC, 0xC0, 0x0C, 0xC0, 0x0C, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x30, 0x00, 0x38, 0xC0, 0x1C, 0xC0, 0x0C, 0xC0, 0x0C,
	0xC0, 0x1C, 0xFF, 0xF8, 0xFF, 0xF0, 0xC0, 0x00, 0xC0, 0x00,
	0xFF, 0xFC, 0xFF, 0xFC, 0x07, 0x80, 0x07, 0x80, 0x0F, 0xC0,
	0x1C, 0xE0, 0x38, 0x70, 0x70, 0x38, 0xE0, 0x1C, 0xC0, 0x0C,
	0xFF, 0xFC, 0xFF, 0xFC, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C,
	0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C,
	0xFF, 0xFC, 0xFF, 0xFC, 0x70, 0x00, 0x38, 0x00, 0x1F, 0x00,
	0x1F, 0x00, 0x38, 0x00, 0x70, 0x00, 0xFF, 0xFC, 0xFF, 0xFC,
	0xFF, 0xFC, 0xFF, 0xFC, 0x1C, 0x00, 0x0E, 0x00, 0x07, 0x00,
	0x03, 0x80, 0x01, 0xC0, 0x00, 0xE0, 0xFF, 0xFC, 0xFF, 0xFC,
	0x3F, 0xF0, 0x7F, 0xF8, 0xE0, 0x1C, 0xC0, 0x0C, 0xC0, 0x0C,
	0xC0, 0x0C, 0xC0, 0x0C, 0xE0, 0x1C, 0x7F, 0xF8, 0x3F, 0xF0,
	0xFF, 0xFC, 0xFF, 0xFC, 0xC3, 0x00, 0xC3, 0x00, 0xC3, 0x00,
	0xC3, 0x00, 0xC3, 0x00, 0xE7, 0x00, 0x7E, 0x00, 0x3C, 0x00,
	0x3F, 0xF0, 0x7F, 0xF8, 0xE0, 0x1C, 0xC0, 0x0C, 0xC0, 0xCC,
	0xC0, 0xEC, 0xC0, 0x7C, 0xE0, 0x38, 0x7F, 0xFC, 0x3F, 0xEC,
	0xFF, 0xFC, 0xFF, 0xFC, 0xC3, 0x00, 0xC3, 0x80, 0xC3, 0x80,
	0xC3, 0xC0, 0xC3, 0xC0, 0xE7, 0x70, 0x7E, 0x3C, 0x3C, 0x1C,
	0x3C, 0x18, 0x7E, 0x1C, 0xE7, 0x0C, 0xC3, 0x0C, 0xC3, 0x0C,
	0xC3, 0x0C, 0xC3, 0x0C, 0xC3, 0x9C, 0xE1, 0xF8, 0x60, 0xF0,
	0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xFF, 0xFC,
	0xFF, 0xFC, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00,
	0xFF, 0xF0, 0xFF, 0xF8, 0x00, 0x1C, 0x00, 0x0C, 0x00, 0x0C,
	0x00, 0x0C, 0x00, 0x0C, 0x00, 0x1C, 0xFF, 0xF8, 0xFF, 0xF0,
	0xFF, 0xC0, 0xFF, 0xE0, 0x00, 0x70, 0x00, 0x38, 0x00, 0x1C,
	0x00, 0x1C, 0x00, 0x38, 0x00, 0x70, 0xFF, 0xE0, 0xFF, 0xC0,
	0xFF, 0xF0, 0xFF, 0xF8, 0x00, 0x1C, 0x00, 0x3C, 0x00, 0xF8,
	0x00, 0xF8, 0x00, 0x3C, 0x00, 0x1C, 0xFF, 0xF8, 0xFF, 0xF0,
	0xF0, 0x3C, 0xF8, 0x7C, 0x1C, 0xE0, 0x0F, 0xC0, 0x07, 0x80,
	0x07, 0x80, 0x0F, 0xC0, 0x1C, 0xE0, 0xF8, 0x7C, 0xF0, 0x3C,
	0xFC, 0x00, 0xFE, 0x00, 0x07, 0x00, 0x03, 0x80, 0x01, 0xFC,
	0x01, 0xFC, 0x03, 0x80, 0x07, 0x00, 0xFE, 0x00, 0xFC, 0x00,
	0xC0, 0x3C, 0xC0, 0x7C, 0xC0, 0xEC, 0xC1, 0xCC, 0xC3, 0x8C,
	0xC7, 0x0C, 0xCE, 0x0C, 0xDC, 0x0C, 0xF8, 0x0C, 0xF0, 0x0C,
	0x00, 0x00, 0x00, 0x00, 0xFF, 0xFC, 0xFF, 0xFC, 0xC0, 0x0C,
	0xC0, 0x0C, 0xC0, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x30, 0x00, 0x30, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x03, 0x00,
	0x03, 0x00, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0x30, 0x00, 0x30,
	0x00, 0x00, 0x00, 0x00, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0, 0x0C,
	0xFF, 0xFC, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x0C, 0x00, 0x1C, 0x00, 0x38, 0x00, 0x70, 0x00, 0xE0, 0x00,
	0xE0, 0x00, 0x70, 0x00, 0x38, 0x00, 0x1C, 0x00, 0x0C, 0x00,
	0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C,
	0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C,
	0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0xE0, 0x00, 0x70, 0x00,
	0x38, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x30, 0x06, 0x78, 0x0E, 0xFC, 0x0C, 0xCC, 0x0C, 0xCC,
	0x0C, 0xCC, 0x0C, 0xCC, 0x0E, 0xCC, 0x07, 0xFC, 0x03, 0xF8,
	0xFF, 0xFC, 0xFF, 0xFC, 0x03, 0x0C, 0x03, 0x0C, 0x03, 0x0C,
	0x03, 0x0C, 0x03, 0x0C, 0x03, 0x9C, 0x01, 0xF8, 0x00, 0xF0,
	0x03, 0xF0, 0x07, 0xF8, 0x0E, 0x1C, 0x0C, 0x0C, 0x0C, 0x0C,
	0x0C, 0x0C, 0x0C, 0x0C, 0x0E, 0x1C, 0x07, 0x38, 0x03, 0x30,
	0x00, 0xF0, 0x01, 0xF8, 0x03, 0x9C, 0x03, 0x0C, 0x03, 0x0C,
	0x03, 0x0C, 0x03, 0x0C, 0x03, 0x0C, 0xFF, 0xFC, 0xFF, 0xFC,
	0x03, 0xF0, 0x07, 0xF8, 0x0E, 0xDC, 0x0C, 0xCC, 0x0C, 0xCC,
	0x0C, 0xCC, 0x0C, 0xCC, 0x0E, 0xDC, 0x07, 0xD8, 0x03, 0x90,
	0x00, 0x00, 0x03, 0x00, 0x3F, 0xFC, 0x7F, 0xFC, 0xE3, 0x00,
	0xE3, 0x00, 0x70, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x03, 0x18, 0x07, 0x9C, 0x0F, 0xCC, 0x0C, 0xCC, 0x0C, 0xCC,
	0x0C, 0xCC, 0x0C, 0xCC, 0x0C, 0xDC, 0x0F, 0xF8, 0x07, 0xF0,
	0xFF, 0xFC, 0xFF, 0xFC, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00,
	0x03, 0x00, 0x03, 0x80, 0x01, 0xFC, 0x00, 0xFC, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0xFC,
	0x1B, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x30, 0x00, 0x38, 0x00, 0x1C, 0x00, 0x0C,
	0x00, 0x0C, 0x00, 0x1C, 0xCF, 0xF8, 0xCF, 0xF0, 0x00, 0x00,
	0x00, 0x00, 0xFF, 0xFC, 0xFF, 0xFC, 0x00, 0xE0, 0x01, 0xE0,
	0x03, 0xF0, 0x07, 0x38, 0x0E, 0x1C, 0x0C, 0x0C, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xC0, 0x0C, 0xC0, 0x0C, 0xFF, 0xFC,
	0xFF, 0xFC, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00,
	0x0F, 0xFC, 0x0F, 0xFC, 0x0E, 0x00, 0x07, 0x00, 0x03, 0xC0,
	0x03, 0xC0, 0x07, 0x00, 0x0E, 0x00, 0x0F, 0xFC, 0x0F, 0xFC,
	0x0F, 0xFC, 0x0F, 0xFC, 0x03, 0x00, 0x07, 0x00, 0x0E, 0x00,
	0x0C, 0x00, 0x0C, 0x00, 0x0E, 0x00, 0x07, 0xFC, 0x03, 0xFC,
	0x03, 0xF0, 0x07, 0xF8, 0x0E, 0x1C, 0x0C, 0x0C, 0x0C, 0x0C,
	0x0C, 0x0C, 0x0C, 0x0C, 0x0E, 0x1C, 0x07, 0xF8, 0x03, 0xF0,
	0x0F, 0xFC, 0x0F, 0xFC, 0x0C, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0,
	0x0C, 0xC0, 0x0C, 0xC0, 0x0F, 0xC0, 0x07, 0x80, 0x03, 0x00,
	0x03, 0x00, 0x07, 0x80, 0x0F, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0,
	0x0C, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0, 0x0F, 0xFC, 0x0F, 0xFC,
	0x0F, 0xFC, 0x0F, 0xFC, 0x03, 0x80, 0x07, 0x00, 0x0E, 0x00,
	0x0C, 0x00, 0x0C, 0x00, 0x0E, 0x00, 0x07, 0x00, 0x03, 0x00,
	0x03, 0x18, 0x07, 0x9C, 0x0F, 0xCC, 0x0C, 0xCC, 0x0C, 0xCC,
	0x0C, 0xCC, 0x0C, 0xCC, 0x0C, 0xFC, 0x0E, 0x78, 0x06, 0x30,
	0x00, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0xFF, 0xF0, 0xFF, 0xF8,
	0x0C, 0x1C, 0x0C, 0x1C, 0x0C, 0x38, 0x0C, 0x30, 0x00, 0x00,
	0x0F, 0xF0, 0x0F, 0xF8, 0x00, 0x1C, 0x00, 0x0C, 0x00, 0x0C,
	0x00, 0x0C, 0x00, 0x0C, 0x00, 0x1C, 0x0F, 0xF8, 0x0F, 0xF0,
	0x0F, 0xC0, 0x0F, 0xE0, 0x00, 0x70, 0x00, 0x38, 0x00, 0x1C,
	0x00, 0x1C, 0x00, 0x38, 0x00, 0x70, 0x0F, 0xE0, 0x0F, 0xC0,
	0x0F, 0xF0, 0x0F, 0xF8, 0x00, 0x1C, 0x00, 0x1C, 0x00, 0xF8,
	0x00, 0xF8, 0x00, 0x1C, 0x00, 0x1C, 0x0F, 0xF8, 0x0F, 0xF0,
	0x0C, 0x0C, 0x0E, 0x1C, 0x07, 0x38, 0x03, 0xF0, 0x01, 0xE0,
	0x01, 0xE0, 0x03, 0xF0, 0x07, 0x38, 0x0E, 0x1C, 0x0C, 0x0C,
	0x0C, 0x00, 0x0E, 0x00, 0x07, 0x0C, 0x03, 0x9C, 0x01, 0xF8,
	0x01, 0xF0, 0x03, 0x80, 0x07, 0x00, 0x0E, 0x00, 0x0C, 0x00,
	0x0C, 0x0C, 0x0C, 0x1C, 0x0C, 0x3C, 0x0C, 0x7C, 0x0C, 0xEC,
	0x0D, 0xCC, 0x0F, 0x8C, 0x0F, 0x0C, 0x0E, 0x0C, 0x0C, 0x0C,
	0x00, 0x00, 0x03, 0x00, 0x07, 0x80, 0x3F, 0xF0, 0x7C, 0xF8,
	0xE0, 0x1C, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0, 0x0C, 0x00, 0x00,
	0x03, 0x0C, 0x03, 0x0C, 0x3F, 0xFC, 0x7F, 0xFC, 0xE3, 0x0C,
	0xC3, 0x0C, 0xC0, 0x0C, 0xE0, 0x0C, 0x70, 0x0C, 0x30, 0x0C,
	0x00, 0x00, 0xC0, 0x0C, 0xC0, 0x0C, 0xC0, 0x0C, 0xE0, 0x1C,
	0x7C, 0xF8, 0x3F, 0xF0, 0x07, 0x80, 0x03, 0x00, 0x00, 0x00,
	0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00,
	0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00,
	0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC,
	0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC, 0xFF, 0xFC
};

#ifdef ILI9488_EBIMODE
/**
 * \brief Read 32 bit data.
 */
static uint32_t ili9488_lcd_get_16(void)
{
	uint16_t readbuf[5];
	uint16_t *ptr, i;
	uint32_t shift_cnt = 2;
	uint32_t chipid = 0;
	uint32_t retval = 0;

	pio_set(PIN_EBI_CDS_PIO, PIN_EBI_CDS_MASK);
	LCD_MULTI_RD(readbuf, 5);
	ptr = &readbuf[1];
	for(i = 1; i < 4; i++) {
		chipid |= (*ptr &0xFF)<< (shift_cnt << 3);
		ptr++;
		shift_cnt--;
	}
	retval = chipid;
	return retval;
}

/**
 * \brief Prepare to write GRAM data.
 */
static void ili9488_write_ram_prepare(void)
{
	pio_clear(PIN_EBI_CDS_PIO, PIN_EBI_CDS_MASK);
	LCD_IR(ILI9488_CMD_MEMORY_WRITE); /* Write Data to GRAM (R2Ch) */
}

/**
 * \brief Write data to LCD GRAM.
 *
 * \param ul_color 16-bits RGB color.
 */
static void ili9488_write_ram(ili9488_color_t ul_color)
{
	pio_set(PIN_EBI_CDS_PIO, PIN_EBI_CDS_MASK);
	LCD_WD(ul_color);
}

/**
 * \brief Write multiple data in buffer to LCD controller.
 *
 * \param p_ul_buf data buffer.
 * \param ul_size size in pixels.
 */
static void ili9488_write_ram_buffer(const ili9488_color_t *p_ul_buf, uint32_t ul_size)
{
	pio_set(PIN_EBI_CDS_PIO, PIN_EBI_CDS_MASK);
	LCD_MULTI_WD(p_ul_buf, ul_size);
}

/**
 * \brief Write data to LCD Register.
 *
 * \param uc_reg register address.
 * \param us_data data to be written.
 * \param size the number of parameters.
 */
static void ili9488_write_register(uint8_t uc_reg, const ili9488_color_t *us_data, uint32_t size)
{
	/* CDS pin is set low level when writing command*/
	pio_clear(PIN_EBI_CDS_PIO, PIN_EBI_CDS_MASK);
	LCD_IR(uc_reg);

	if(size == 0) {
		return;
	}

	/* CDS pin is set high level when writing parameters or image data*/
	pio_set(PIN_EBI_CDS_PIO, PIN_EBI_CDS_MASK);
	LCD_MULTI_WD(us_data, size);
}

/**
 * \brief Read data to LCD GRAM.
 *
 * \note Because pixel data LCD GRAM is 18-bits, so convertion to RGB565 16-bits
 * will cause low color bit lose.
 *
 * \return color 16-bits RGB color.
 */
static uint32_t ili9488_read_ram(void)
{
	uint16_t value[3] = {0};
	uint32_t color = 0;

	pio_clear(PIN_EBI_CDS_PIO, PIN_EBI_CDS_MASK);
	LCD_IR(ILI9488_CMD_MEMORY_READ);/* Write Data to GRAM (R2Eh) */

	pio_set(PIN_EBI_CDS_PIO, PIN_EBI_CDS_MASK);
	LCD_MULTI_RD(value, 3);

	/* The first data is dummy*/
	color = ILI9488_COLOR(value[1] >> 8, value[1] & 0xFF, value[2] >> 8);
	return color;
}

/**
 * \brief Read chipid.
 *
 * \return chipid value.
 */
static uint32_t ili9488_read_chipid(void)
{
	pio_clear(PIN_EBI_CDS_PIO, PIN_EBI_CDS_MASK);
	LCD_IR(ILI9488_CMD_READ_ID4);

	return ili9488_lcd_get_16();
}
#endif
#ifdef ILI9488_SPIMODE
/**
 * \brief Prepare to write GRAM data.
 */
static void ili9488_write_ram_prepare(void)
{
	volatile uint32_t i;
	pio_set_pin_low(LCD_SPI_CDS_PIO);
	spi_write(BOARD_ILI9488_SPI, ILI9488_CMD_MEMORY_WRITE, BOARD_ILI9488_SPI_NPCS, 0);
	for(i = 0; i < 0xFF; i++);
}

/**
 * \brief Write data to LCD GRAM.
 *
 * \param ul_color 16-bits RGB color.
 */
static void ili9488_write_ram(ili9488_color_t ul_color)
{
	pio_set_pin_high(LCD_SPI_CDS_PIO);
	spi_write(BOARD_ILI9488_SPI, ul_color, BOARD_ILI9488_SPI_NPCS, 0);
}

/**
 * \brief Write multiple data in buffer to LCD controller.
 *
 * \param p_ul_buf data buffer.
 * \param ul_size size in pixels.
 */
static void ili9488_write_ram_buffer(const ili9488_color_t *p_ul_buf, uint32_t ul_size)
{
	volatile uint32_t i;
	pio_set_pin_high(LCD_SPI_CDS_PIO);
	spi_write_packet(BOARD_ILI9488_SPI, p_ul_buf, ul_size);
	for(i = 0; i < 0xFF; i++);
}

/**
 * \brief Write data to LCD Register.
 *
 * \param uc_reg register address.
 * \param us_data data to be written.
 * \param size the number of parameters.
 */
static void ili9488_write_register(uint8_t uc_reg, const ili9488_color_t *us_data, uint32_t size)
{
	volatile uint32_t i;

	/* Transfer cmd */
	pio_set_pin_low(LCD_SPI_CDS_PIO);
	spi_write(BOARD_ILI9488_SPI, uc_reg, BOARD_ILI9488_SPI_NPCS, 0);
	for(i = 0; i < 0xFF; i++);

	if(size > 0) {
		/* Transfer data */
		pio_set_pin_high(LCD_SPI_CDS_PIO);
		spi_write_packet(BOARD_ILI9488_SPI, us_data, size);
		for(i = 0; i < 0x5F; i++);
	}
}

/**
 * \brief Read data to LCD GRAM.
 *
 * \note Because pixel data LCD GRAM is 18-bits, so convertion to RGB565 16-bits
 * will cause low color bit lose.
 *
 * \return color 16-bits RGB color.
 */
static uint32_t ili9488_read_ram(void)
{
	uint8_t grambuf[4];
	ili9488_write_register(ILI9488_CMD_MEMORY_READ, 0x0000, 0);

	pio_set_pin_high(LCD_SPI_CDS_PIO);
	spi_read_packet(BOARD_ILI9488_SPI, grambuf, 4);
	/* The first data is dummy*/
	return ILI9488_COLOR(grambuf[1], grambuf[2], grambuf[3]);
}

/**
 * \brief Read chipid.
 *
 * \return chipid value.
 */
static uint32_t ili9488_read_chipid(void)
{
	uint32_t i, chipid = 0;
	volatile uint32_t j;
	ili9488_color_t chipidBuf, reg, param;

	reg = 0x81;
	param = 0x0;
	for (i = 3; i > 0; i--) {
		ili9488_write_register(ILI9488_CMD_SPI_READ_SETTINGS, &reg, 1);
		reg++;
		for(j = 0; j < 0xFF; j++);
		ili9488_write_register(ILI9488_CMD_READ_ID4, 0, 0);
		{
			pio_set_pin_high(LCD_SPI_CDS_PIO);
			spi_read_packet(BOARD_ILI9488_SPI, &chipidBuf, 1);
			for(j = 0; j < 0xFF; j++);
		}
		chipid |= (chipidBuf & 0xFF) << ((i - 1) << 3);
		ili9488_write_register(ILI9488_CMD_SPI_READ_SETTINGS, &param, 1);
		for(j = 0; j < 0xFFF; j++);
	}
	return chipid;
}
#endif

/**
 * \brief Delay function.
 */
void ili9488_delay(uint32_t ul_ms)
{
	uint32_t i;

	for(i = 0; i < ul_ms; i++) {
		for(i = 0; i < 100000; i++) {
		}
	}
}

/**
 * \brief Check box coordinates.
 *
 * \param p_ul_x1 X coordinate of upper-left corner on LCD.
 * \param p_ul_y1 Y coordinate of upper-left corner on LCD.
 * \param p_ul_x2 X coordinate of lower-right corner on LCD.
 * \param p_ul_y2 Y coordinate of lower-right corner on LCD.
 */
static void ili9488_check_box_coordinates(uint32_t *p_ul_x1, uint32_t *p_ul_y1,
		uint32_t *p_ul_x2, uint32_t *p_ul_y2)
{
	uint32_t dw;

	if (*p_ul_x1 >= ILI9488_LCD_WIDTH) {
		*p_ul_x1 = ILI9488_LCD_WIDTH - 1;
	}

	if (*p_ul_x2 >= ILI9488_LCD_WIDTH) {
		*p_ul_x2 = ILI9488_LCD_WIDTH - 1;
	}

	if (*p_ul_y1 >= ILI9488_LCD_HEIGHT) {
		*p_ul_y1 = ILI9488_LCD_HEIGHT - 1;
	}

	if (*p_ul_y2 >= ILI9488_LCD_HEIGHT) {
		*p_ul_y2 = ILI9488_LCD_HEIGHT - 1;
	}

	if (*p_ul_x1 > *p_ul_x2) {
		dw = *p_ul_x1;
		*p_ul_x1 = *p_ul_x2;
		*p_ul_x2 = dw;
	}

	if (*p_ul_y1 > *p_ul_y2) {
		dw = *p_ul_y1;
		*p_ul_y1 = *p_ul_y2;
		*p_ul_y2 = dw;
	}
}
/**
 * \brief ILI9488 configure landscape.
 *
 * \Param LandscaprMode Landscape Mode.
 */
void ili9488_set_display_direction(enum ili9488_display_direction direction )
{
	ili9488_color_t value;
	if(direction) {
		value = 0xE8;
	} else {
		value = 0x48;
	}
	ili9488_write_register(ILI9488_CMD_MEMORY_ACCESS_CONTROL, &value, 1);
}

/**
 * \brief ILI9488 configure window.

 * \Param x start position.
 * \Param y start position.
 * \Param width  Width of window.
 * \Param height Height of window.
 */
void ili9488_set_window(uint16_t x, uint16_t y, uint16_t width, uint16_t height )
{
	uint16_t col_start, col_end, row_start, row_end;
	uint32_t cnt = 0;
	ili9488_color_t buf[4];

	cnt = sizeof(buf)/sizeof(ili9488_color_t);

	col_start  =  x ;
	col_end    =  width + x - 1;

	row_start = y ;
	row_end   = height + y - 1;

	buf[0] = get_8b_to_16b(col_start);
	buf[1] = get_0b_to_8b(col_start);
	buf[2] = get_8b_to_16b(col_end);
	buf[3] = get_0b_to_8b(col_end);
	ili9488_write_register(ILI9488_CMD_COLUMN_ADDRESS_SET, buf, cnt);
	ili9488_write_register(ILI9488_CMD_NOP, 0, 0);

	/* Set Horizontal Address End Position */
	buf[0] = get_8b_to_16b(row_start);
	buf[1] = get_0b_to_8b(row_start);
	buf[2] = get_8b_to_16b(row_end);
	buf[3] = get_0b_to_8b(row_end);
	ili9488_write_register(ILI9488_CMD_PAGE_ADDRESS_SET, buf, cnt);
	ili9488_write_register(ILI9488_CMD_NOP, 0, 0);
}

/**
 * \brief Initialize the ILI9488 lcd driver.
 *
 * \note Make sure below works have been done before calling ili9488_init()\n
 * 1. ILI9488 related Pins have been initialized correctly. \n
 * 2. SMC has been configured correctly for access ILI9488 (16-bit system interface for now). \n
 *
 * \param p_opt pointer to ILI9488 option structure.
 *
 * \return 0 if initialization succeeds, otherwise fails.
 */
uint32_t ili9488_init(struct ili9488_opt_t *p_opt)
{
	ili9488_color_t param;
	uint32_t chipid;
#ifdef ILI9488_EBIMODE
	/* Enable peripheral clock */
	pmc_enable_periph_clk(ID_SMC);

	/* Configure SMC, NCS3 is assigned to LCD */
	smc_set_setup_timing(SMC, BOARD_ILI9488_EBI_NPCS, SMC_SETUP_NWE_SETUP(0)
			| SMC_SETUP_NCS_WR_SETUP(0)
			| SMC_SETUP_NRD_SETUP(0)
			| SMC_SETUP_NCS_RD_SETUP(0));
	smc_set_pulse_timing(SMC, BOARD_ILI9488_EBI_NPCS , SMC_PULSE_NWE_PULSE(3)
			| SMC_PULSE_NCS_WR_PULSE(0x4)
			| SMC_PULSE_NRD_PULSE(0xA)
			| SMC_PULSE_NCS_RD_PULSE(0xA));
	smc_set_cycle_timing(SMC, BOARD_ILI9488_EBI_NPCS, SMC_CYCLE_NWE_CYCLE(0x4)
			| SMC_CYCLE_NRD_CYCLE(0xA));


	smc_set_mode(SMC, BOARD_ILI9488_EBI_NPCS, SMC_MODE_READ_MODE
			| SMC_MODE_WRITE_MODE
			| SMC_MODE_DBW_16_BIT
			| SMC_MODE_EXNW_MODE_DISABLED
			| SMC_MODE_TDF_CYCLES(0xF));
#endif
#ifdef ILI9488_SPIMODE
	struct spi_device ILI9488_SPI_DEVICE = {
		// Board specific chip select configuration
		.id = BOARD_ILI9488_SPI_NPCS
	};

	/* Init, select and configure the chip */
	spi_master_init(BOARD_ILI9488_SPI);
	spi_master_setup_device(BOARD_ILI9488_SPI, &ILI9488_SPI_DEVICE, SPI_MODE_3, ILI9488_SPI_BAUDRATE, 0);
	spi_configure_cs_behavior(BOARD_ILI9488_SPI, BOARD_ILI9488_SPI_NPCS, SPI_CS_RISE_NO_TX);
	spi_select_device(BOARD_ILI9488_SPI, &ILI9488_SPI_DEVICE);

	/* Enable the SPI peripheral */
	spi_enable(BOARD_ILI9488_SPI);
	spi_enable_interrupt(BOARD_ILI9488_SPI, SPI_IER_RDRF);
#endif

	ili9488_write_register(ILI9488_CMD_SOFTWARE_RESET, 0x0000, 0);
	ili9488_delay(200);

	ili9488_write_register(ILI9488_CMD_SLEEP_OUT, 0x0000, 0);
	ili9488_delay(200);

	/** read chipid */
	chipid = ili9488_read_chipid();
	if (chipid != ILI9488_DEVICE_CODE) {
		return 1;
	}

	/** make it tRGB and reverse the column order */
	param = 0x48;
	ili9488_write_register(ILI9488_CMD_MEMORY_ACCESS_CONTROL, &param, 1);
	ili9488_delay(100);

	param = 0x04;
	ili9488_write_register(ILI9488_CMD_CABC_CONTROL_9, &param, 1);
	ili9488_delay(100);
#ifdef ILI9488_EBIMODE
	/** Set ILI9488 Pixel Format in SMC mode.*/
	param = 0x05;
	ili9488_write_register(ILI9488_CMD_COLMOD_PIXEL_FORMAT_SET, &param, 1);
	ili9488_delay(100);
	ili9488_write_register(ILI9488_CMD_PARTIAL_MODE_ON, 0, 0);
	ili9488_delay(100);
#endif
#ifdef ILI9488_SPIMODE
	param = 0x06;
	ili9488_write_register(ILI9488_CMD_COLMOD_PIXEL_FORMAT_SET, &param, 1);
	ili9488_delay(100);
	ili9488_write_register(ILI9488_CMD_NORMAL_DISP_MODE_ON, 0, 0);
	ili9488_delay(100);
#endif

	ili9488_display_on();
	ili9488_delay(100);

	ili9488_set_display_direction(LANDSCAPE);
	ili9488_delay(100);

	ili9488_set_window(0, 0,p_opt->ul_width,p_opt->ul_height);
	ili9488_set_foreground_color(p_opt->foreground_color);
	ili9488_set_cursor_position(0, 0);

	return 0;
}

/**
 * \brief Turn on the LCD.
 */
void ili9488_display_on(void)
{
	ili9488_write_register(ILI9488_CMD_DISPLAY_ON, 0, 0);
}

/**
 * \brief Turn off the LCD.
 */
void ili9488_display_off(void)
{
	ili9488_write_register(ILI9488_CMD_DISPLAY_OFF, 0x00, 0);
}

/**
 * \brief Set foreground color.
 *
 * \param ul_color foreground color.
 */
void ili9488_set_foreground_color(uint32_t ul_color)
{
	uint32_t i;
#ifdef ILI9488_EBIMODE
	/* Fill the cache with selected color */
	for (i = 0; i < LCD_DATA_CACHE_SIZE; ++i) {
		g_ul_pixel_cache[i] = ul_color;
	}
#endif
#ifdef ILI9488_SPIMODE
	for (i = 0; i < LCD_DATA_CACHE_SIZE * LCD_DATA_COLOR_UNIT; ) {
		g_ul_pixel_cache[i++] = ul_color>>16;
		g_ul_pixel_cache[i++] = ul_color>>8;
		g_ul_pixel_cache[i++] = ul_color&0xFF;
	}
#endif
}

/**
 * \brief Fill the LCD buffer with the specified color.
 *
 * \param ul_color fill color.
 */
void ili9488_fill(ili9488_color_t ul_color)
{
	uint32_t dw;

	ili9488_set_cursor_position(0, 0);
	ili9488_write_ram_prepare();

	for (dw = ILI9488_LCD_WIDTH * ILI9488_LCD_HEIGHT; dw > 0; dw--) {
		ili9488_write_ram(ul_color);
	}
}

/**
 * \brief Set cursor of LCD screen.
 *
 * \param x X coordinate of upper-left corner on LCD.
 * \param y Y coordinate of upper-left corner on LCD.
 */
void ili9488_set_cursor_position(uint16_t x, uint16_t y)
{
	/* Set Horizontal Address Start Position */
	uint32_t cnt = 0;

	ili9488_color_t buf[4];
	cnt = sizeof(buf)/sizeof(ili9488_color_t);

	buf[0] = get_8b_to_16b(x);
	buf[1] = get_0b_to_8b(x);
	buf[2] = get_8b_to_16b(x);
	buf[3] = get_0b_to_8b(x);
	ili9488_write_register(ILI9488_CMD_COLUMN_ADDRESS_SET, buf, cnt);
	ili9488_write_register(ILI9488_CMD_NOP, 0, 0);


	/* Set Horizontal Address End Position */
	buf[0] = get_8b_to_16b(y);
	buf[1] = get_0b_to_8b(y);
	buf[2] = get_8b_to_16b(y);
	buf[3] = get_0b_to_8b(y);
	ili9488_write_register(ILI9488_CMD_PAGE_ADDRESS_SET, buf, cnt);
	ili9488_write_register(ILI9488_CMD_NOP, 0, 0);
}

/**
 * \brief Scroll up/down for the number of specified lines.
 *
 * \param ul_tfa  Top Fixed Area in number of lines from the top of the frame memory.
 * \param ul_lines number of lines to scroll.
 * \param ul_bfa  bottom Fixed Area in number of lines from the bottom of the frame memory.
 */
void ili9488_scroll(uint16_t ul_tfa, uint16_t ul_vsa, uint16_t ul_bfa)
{
	uint32_t cnt = 0;
	ili9488_color_t buf[6];

	cnt = sizeof(buf)/sizeof(ili9488_color_t);

	buf[0] = get_8b_to_16b(ul_tfa);
	buf[1] = get_0b_to_8b(ul_tfa);

	buf[2] = get_8b_to_16b(ul_vsa);
	buf[3] = get_0b_to_8b(ul_vsa);

	buf[4] = get_8b_to_16b(ul_bfa);
	buf[5] = get_0b_to_8b(ul_bfa);

	ili9488_write_register(ILI9488_CMD_VERT_SCROLL_DEFINITION, buf, cnt);
}

/**
 * \brief Enable the scrolling feature.
 *
 * \param ul_vsp Vertical Scrolling Start Address
 */
void ili9488_set_scroll_address(uint16_t ul_vsp)
{
	uint32_t cnt = 0;

	ili9488_color_t buf[2];
	cnt = sizeof(buf)/sizeof(ili9488_color_t);

	buf[0] = get_8b_to_16b(ul_vsp);
	buf[1] = get_0b_to_8b(ul_vsp);
	ili9488_write_register(ILI9488_CMD_VERT_SCROLL_START_ADDRESS, buf, cnt);
}

/**
 * \brief Draw a pixel on LCD.
 *
 * \param ul_x X coordinate of pixel.
 * \param ul_y Y coordinate of pixel.
 *
 * \return 0 if succeeds, otherwise fails.
 */
uint32_t ili9488_draw_pixel(uint32_t ul_x, uint32_t ul_y)
{
	if ((ul_x >= ILI9488_LCD_WIDTH) || (ul_y >= ILI9488_LCD_HEIGHT)) {
		return 1;
	}

	/* Set cursor */
	ili9488_set_cursor_position(ul_x, ul_y);

	/* Prepare to write in GRAM */
	ili9488_write_ram_prepare();
	ili9488_write_ram_buffer(g_ul_pixel_cache, LCD_DATA_COLOR_UNIT);
	return 0;
}

/**
 * \brief Get a pixel from LCD.
 *
 * \param ul_x X coordinate of pixel.
 * \param ul_y Y coordinate of pixel.
 *
 * \return the pixel color.
 */
ili9488_color_t ili9488_get_pixel(uint32_t ul_x, uint32_t ul_y)
{
#ifdef ILI9488_EBIMODE
	Assert(ul_x <= ILI9488_LCD_WIDTH);
	Assert(ul_y <= ILI9488_LCD_HEIGHT);

	/* Set cursor */
	ili9488_set_cursor_position(ul_x, ul_y);

	/* Prepare to write in GRAM */
	return ili9488_read_ram();
#endif
#ifdef ILI9488_SPIMODE
	Assert(0);
	return 0;
#endif
}

/**
 * \brief Draw a line on LCD, which is not horizontal or vertical.
 *
 * \param ul_x1 X coordinate of line start.
 * \param ul_y1 Y coordinate of line start.
 * \param ul_x2 X coordinate of line end.
 * \param ul_y2 Y coordinate of line endl.
 */
static void ili9488_draw_line_bresenham(uint32_t ul_x1, uint32_t ul_y1,
		uint32_t ul_x2, uint32_t ul_y2)
{
	int dx, dy;
	int i;
	int xinc, yinc, cumul;
	int x, y;

	x = ul_x1;
	y = ul_y1;
	dx = ul_x2 - ul_x1;
	dy = ul_y2 - ul_y1;
	xinc = (dx > 0) ? 1 : -1;
	yinc = (dy > 0) ? 1 : -1;
	dx = abs(ul_x2 - ul_x1);
	dy = abs(ul_y2 - ul_y1);

	ili9488_draw_pixel(x, y);

	if (dx > dy) {
		cumul = dx >> 1;

		for (i = 1; i <= dx; i++) {
			x += xinc;
			cumul += dy;

			if (cumul >= dx) {
				cumul -= dx;
				y += yinc;
			}

			ili9488_draw_pixel(x, y);
		}
	} else {
		cumul = dy >> 1;

		for (i = 1; i <= dy; i++) {
			y += yinc;
			cumul += dx;

			if (cumul >= dy) {
				cumul -= dy;
				x += xinc;
			}

			ili9488_draw_pixel(x, y);
		}
	}
}

/**
 * \brief Draw a line on LCD.
 *
 * \param ul_x1 X coordinate of line start.
 * \param ul_y1 Y coordinate of line start.
 * \param ul_x2 X coordinate of line end.
 * \param ul_y2 Y coordinate of line end.
 */
void ili9488_draw_line(uint32_t ul_x1, uint32_t ul_y1,
		uint32_t ul_x2, uint32_t ul_y2)
{
	if ((ul_y1 == ul_y2) || (ul_x1 == ul_x2)) {
		ili9488_draw_filled_rectangle(ul_x1, ul_y1, ul_x2, ul_y2);
	} else {
		ili9488_draw_line_bresenham(ul_x1, ul_y1, ul_x2, ul_y2);
	}
}

/**
 * \brief Draw a rectangle on LCD.
 *
 * \param ul_x1 X coordinate of upper-left corner on LCD.
 * \param ul_y1 Y coordinate of upper-left corner on LCD.
 * \param ul_x2 X coordinate of lower-right corner on LCD.
 * \param ul_y2 Y coordinate of lower-right corner on LCD.
 */
void ili9488_draw_rectangle(uint32_t ul_x1, uint32_t ul_y1,
		uint32_t ul_x2, uint32_t ul_y2)
{
	ili9488_check_box_coordinates(&ul_x1, &ul_y1, &ul_x2, &ul_y2);

	ili9488_draw_filled_rectangle(ul_x1, ul_y1, ul_x2, ul_y1);
	ili9488_draw_filled_rectangle(ul_x1, ul_y2, ul_x2, ul_y2);

	ili9488_draw_filled_rectangle(ul_x1, ul_y1, ul_x1, ul_y2);
	ili9488_draw_filled_rectangle(ul_x2, ul_y1, ul_x2, ul_y2);
}

/**
 * \brief Draw a filled rectangle on LCD.
 *
 * \param ul_x1 X coordinate of upper-left corner on LCD.
 * \param ul_y1 Y coordinate of upper-left corner on LCD.
 * \param ul_x2 X coordinate of lower-right corner on LCD.
 * \param ul_y2 Y coordinate of lower-right corner on LCD.
 */
void ili9488_draw_filled_rectangle(uint32_t ul_x1, uint32_t ul_y1,
		uint32_t ul_x2, uint32_t ul_y2)
{
	uint32_t size, blocks;

	/* Swap coordinates if necessary */
	ili9488_check_box_coordinates(&ul_x1, &ul_y1, &ul_x2, &ul_y2);

	/* Determine the refresh window area */
	ili9488_set_window(ul_x1, ul_y1, (ul_x2 - ul_x1) + 1, (ul_y2 - ul_y1) + 1);

	/* Prepare to write in GRAM */
	ili9488_write_ram_prepare();

	size = (ul_x2 - ul_x1 + 1) * (ul_y2 - ul_y1 + 1);
	/* Send pixels blocks => one SPI IT / block */
	blocks = size / LCD_DATA_CACHE_SIZE;
	while (blocks--) {
		ili9488_write_ram_buffer(g_ul_pixel_cache, LCD_DATA_CACHE_SIZE * LCD_DATA_COLOR_UNIT);
	}

	/* Send remaining pixels */
	ili9488_write_ram_buffer(g_ul_pixel_cache, (size % LCD_DATA_CACHE_SIZE) * LCD_DATA_COLOR_UNIT);

	/* Reset the refresh window area */
	ili9488_set_window(0, 0, ILI9488_LCD_WIDTH, ILI9488_LCD_HEIGHT);

}

/**
 * \brief Draw a circle on LCD.
 *
 * \param ul_x X coordinate of circle center.
 * \param ul_y Y coordinate of circle center.
 * \param ul_r circle radius.
 *
 * \return 0 if succeeds, otherwise fails.
 */
uint32_t ili9488_draw_circle(uint32_t ul_x, uint32_t ul_y, uint32_t ul_r)
{
	int32_t   d;    /* Decision Variable */
	uint32_t  curX; /* Current X Value */
	uint32_t  curY; /* Current Y Value */

	if (ul_r == 0) {
		return 1;
	}

	d = 3 - (ul_r << 1);
	curX = 0;
	curY = ul_r;

	while (curX <= curY) {
		ili9488_draw_pixel(ul_x + curX, ul_y + curY);
		ili9488_draw_pixel(ul_x + curX, ul_y - curY);
		ili9488_draw_pixel(ul_x - curX, ul_y + curY);
		ili9488_draw_pixel(ul_x - curX, ul_y - curY);
		ili9488_draw_pixel(ul_x + curY, ul_y + curX);
		ili9488_draw_pixel(ul_x + curY, ul_y - curX);
		ili9488_draw_pixel(ul_x - curY, ul_y + curX);
		ili9488_draw_pixel(ul_x - curY, ul_y - curX);

		if (d < 0) {
			d += (curX << 2) + 6;
		} else {
			d += ((curX - curY) << 2) + 10;
			curY--;
		}
		curX++;
	}

	return 0;
}

/**
 * \brief Draw a filled circle on LCD.
 *
 * \param ul_x X coordinate of circle center.
 * \param ul_y Y coordinate of circle center.
 * \param ul_r circle radius.
 *
 * \return 0 if succeeds, otherwise fails.
 */
uint32_t ili9488_draw_filled_circle(uint32_t ul_x, uint32_t ul_y, uint32_t ul_r)
{
	signed int d;       /* Decision Variable */
	uint32_t dwCurX;    /* Current X Value */
	uint32_t dwCurY;    /* Current Y Value */
	uint32_t dwXmin, dwYmin;

	if (ul_r == 0) {
		return 1;
	}

	d = 3 - (ul_r << 1);
	dwCurX = 0;
	dwCurY = ul_r;

	while (dwCurX <= dwCurY) {
		dwXmin = (dwCurX > ul_x) ? 0 : ul_x - dwCurX;
		dwYmin = (dwCurY > ul_y) ? 0 : ul_y - dwCurY;
		ili9488_draw_filled_rectangle(dwXmin, dwYmin, ul_x + dwCurX, dwYmin);
		ili9488_draw_filled_rectangle(dwXmin, ul_y + dwCurY, ul_x + dwCurX, ul_y + dwCurY);
		dwXmin = (dwCurY > ul_x) ? 0 : ul_x - dwCurY;
		dwYmin = (dwCurX > ul_y) ? 0 : ul_y - dwCurX;
		ili9488_draw_filled_rectangle(dwXmin, dwYmin, ul_x + dwCurY, dwYmin);
		ili9488_draw_filled_rectangle(dwXmin, ul_y + dwCurX, ul_x + dwCurY, ul_y + dwCurX);

		if (d < 0) {
			d += (dwCurX << 2) + 6;
		} else {
			d += ((dwCurX - dwCurY) << 2) + 10;
			dwCurY--;
		}

		dwCurX++;
	}

	return 0;
}

/**
 * \brief Prepare LCD to draw.
 *
 * \param ul_x Horizontal address start position
 * \param ul_y Vertical address start position
 * \param ul_width The width of the window.
 * \param ul_height The height of the window.
 */
void ili9488_draw_prepare(uint32_t ul_x, uint32_t ul_y, uint32_t ul_width,
		uint32_t ul_height)
{
	/* Determine the refresh window area */
	ili9488_set_window(ul_x, ul_y, ul_width, ul_height);

	/* Set cursor */
	ili9488_set_cursor_position(ul_x, ul_y);

	/* Prepare to write in GRAM */
	ili9488_write_ram_prepare();
}

/**
 * \brief Draw an ASCII character on LCD.
 *
 * \param ul_x X coordinate of character upper-left corner.
 * \param ul_y Y coordinate of character upper-left corner.
 * \param uc_c character to print.
 */
static void ili9488_draw_char(uint32_t ul_x, uint32_t ul_y, uint8_t uc_c)
{
	uint32_t row, col;
	uint32_t offset, offset0, offset1;

	/* Compute offset according of the specified ASCII character */
	/* Note: the first 32 characters of the ASCII table are not handled */
	offset = ((uint32_t)uc_c - 0x20) * 20;

	for (col = 0; col < 10; col++) {
		/* Compute the first and second byte offset of a column */
		offset0 = offset + col * 2;
		offset1 = offset0 + 1;

		/* Draw pixel on screen depending on the corresponding bit value from the charset */
		for (row = 0; row < 8; row++) {
			if ((p_uc_charset10x14[offset0] >> (7 - row)) & 0x1) {
				ili9488_draw_pixel(ul_x + col, ul_y + row);
			}
		}

		for (row = 0; row < 6; row++) {
			if ((p_uc_charset10x14[offset1] >> (7 - row)) & 0x1) {
				ili9488_draw_pixel(ul_x + col, ul_y + row + 8);
			}
		}
	}
}

/**
 * \brief Draw a string on LCD.
 *
 * \param ul_x X coordinate of string top-left corner.
 * \param ul_y Y coordinate of string top-left corner.
 * \param p_str String to display.
 */
void ili9488_draw_string(uint32_t ul_x, uint32_t ul_y, const uint8_t *p_str)
{
	uint32_t xorg = ul_x;

	while (*p_str != 0) {
		/* If newline, jump to the next line (font height + 2) */
		if (*p_str == '\n') {
			ul_y += gfont.height + 2;
			ul_x = xorg;
		} else {
			/* Draw the character and place cursor right after (font width + 2) */
			ili9488_draw_char(ul_x, ul_y, *p_str);
			ul_x += gfont.width + 2;
		}
		p_str++;
	}
}

/**
 * \brief Draw a pixmap on LCD.
 *
 * \param ul_x X coordinate of upper-left corner on LCD.
 * \param ul_y Y coordinate of upper-left corner on LCD.
 * \param ul_width width of the picture.
 * \param ul_height height of the picture.
 * \param p_ul_pixmap pixmap of the image.
 */
void ili9488_draw_pixmap(uint32_t ul_x, uint32_t ul_y, uint32_t ul_width,
		uint32_t ul_height, const ili9488_color_t *p_ul_pixmap)
{
	uint32_t size;
	uint32_t dwX1, dwY1, dwX2, dwY2;
	dwX1 = ul_x;
	dwY1 = ul_y;
	dwX2 = ul_x + ul_width - 1;
	dwY2 = ul_y + ul_height - 1;

	/* Swap coordinates if necessary */
	ili9488_check_box_coordinates(&dwX1, &dwY1, &dwX2, &dwY2);

	/* Determine the refresh window area */
	ili9488_set_window(dwX1, dwY1, (dwX2 - dwX1 + 1), (dwY2 - dwY1 + 1));

	size = (dwX2 - dwX1) * (dwY2 - dwY1);

	ili9488_write_register(ILI9488_CMD_MEMORY_WRITE, p_ul_pixmap, size * LCD_DATA_COLOR_UNIT);

	/* Reset the refresh window area */
	ili9488_set_window(0, 0, ILI9488_LCD_WIDTH, ILI9488_LCD_HEIGHT);
}

/**
 * \brief Set display brightness
 *
 * Configures the display for a given brightness value
 *
 * \param us_value brightness value need to written.
 */
void ili9488_write_brightness(uint16_t us_value)
{
	ili9488_write_register(ILI9488_CMD_WRITE_DISPLAY_BRIGHTNESS, (ili9488_color_t *)&us_value, 1);
}


static ili9488_coord_t limit_start_x, limit_start_y;
static ili9488_coord_t limit_end_x, limit_end_y;

/**
 * \brief Set the display top left drawing limit
 *
 * Use this function to set the top left limit of the drawing limit box.
 *
 * \param x The x coordinate of the top left corner
 * \param y The y coordinate of the top left corner
 */
void ili9488_set_top_left_limit(ili9488_coord_t x, ili9488_coord_t y)
{
	limit_start_x = x;
	limit_start_y = y;
}

/**
 * \brief Set the display bottom right drawing limit
 *
 * Use this function to set the bottom right corner of the drawing limit box.
 *
 * \param x The x coordinate of the bottom right corner
 * \param y The y coordinate of the bottom right corner
 */
void ili9488_set_bottom_right_limit(ili9488_coord_t x, ili9488_coord_t y)
{
	limit_end_x = x;
	limit_end_y = y;
}

/**
 * \brief Set the full display drawing limits
 *
 * Use this function to set the full drawing limit box.
 *
 * \param start_x The x coordinate of the top left corner
 * \param start_y The y coordinate of the top left corner
 * \param end_x The x coordinate of the bottom right corner
 * \param end_y The y coordinate of the bottom right corner
 */
void ili9488_set_limits(ili9488_coord_t start_x, ili9488_coord_t start_y,
		ili9488_coord_t end_x, ili9488_coord_t end_y)
{
	limit_start_x = start_x;
	limit_start_y = start_y;
	limit_end_x = end_x;
	limit_end_y = end_y;
}

/**
 * \brief Sets the orientation of the display data
 *
 * Configures the display for a given orientation, including mirroring and/or
 * screen rotation.
 *
 * \param flags Orientation flags to use, see \ref ILI9488_FLIP_X, \ref ILI9488_FLIP_Y
 *        and \ref ILI9488_SWITCH_XY.
 */
void ili9488_set_orientation(uint8_t flags)
{
	/* Flip X/Y and reverse X orientation and set BGR mode*/
	ili9488_color_t madctl = 0x68;

	if (flags & ILI9488_FLIP_X) {
		madctl &= ~(1 << 6);
	}

	if (flags & ILI9488_FLIP_Y) {
		madctl |= 1 << 7;
	}

	if (flags & ILI9488_SWITCH_XY) {
		madctl &= ~(1 << 5);
	}

	ili9488_write_register(ILI9488_CMD_MEMORY_ACCESS_CONTROL, &madctl, 1);
}

/**
 * \brief Read a single color from the graphical memory
 *
 * Use this function to read a color from the graphical memory of the
 * controller.
 *
 * Limits have to be set prior to calling this function, e.g.:
 * \code
 * ili9488_set_top_left_limit(0, 0);
 * ili9488_set_bottom_right_limit(320, 240);
 * ...
 * \endcode
 *
 * \retval ili9488_color_t The read color pixel
 */
uint16_t ili9488_read_gram(void)
{
	ili9488_set_cursor_position(limit_start_x, limit_start_y);
	return ili9488_read_ram();
}

/**
 * \brief Write the graphical memory with a single color pixel
 *
 * Use this function to write a single color pixel to the controller memory.
 *
 * Limits have to be set prior to calling this function, e.g.:
 * \code
 * ili9488_set_top_left_limit(0, 0);
 * ili9488_set_bottom_right_limit(320, 240);
 * ...
 * \endcode
 *
 * \param color The color pixel to write to the screen
 */
void ili9488_write_gram(uint16_t color)
{
	ili9488_set_cursor_position(limit_start_x, limit_start_y);
	ili9488_write_ram_prepare();
#ifdef ILI9488_EBIMODE
	ili9488_write_ram(color);
#endif
#ifdef ILI9488_SPIMODE
	uint32_t color_666 = RGB_16_TO_18BIT(color);
	ili9488_write_ram(color_666 >> 16);
	ili9488_write_ram(color_666 >> 8);
	ili9488_write_ram(color_666 & 0xFF);
#endif
}

/**
 * \brief Copy pixels from SRAM to the screen
 *
 * Used to copy a large quantitative of data to the screen in one go.
 *
 * Limits have to be set prior to calling this function, e.g.:
 * \code
 * ili9488_set_top_left_limit(0, 0);
 * ili9488_set_bottom_right_limit(320, 240);
 * ...
 * \endcode
 *
 * \param pixels Pointer to the pixel data
 * \param count Number of pixels to copy to the screen
 */
void ili9488_copy_pixels_to_screen(const uint16_t *pixels, uint32_t count)
{
	ili9488_set_window(limit_start_x, limit_start_y, (limit_end_x - limit_start_x) + 1, (limit_end_y - limit_start_y) + 1);

#ifdef ILI9488_EBIMODE
	ili9488_write_register(ILI9488_CMD_MEMORY_WRITE, pixels, count * LCD_DATA_COLOR_UNIT);
#endif
#ifdef ILI9488_SPIMODE
	uint32_t color_666;
	ili9488_write_ram_prepare();
	while (count--) {
		color_666 = RGB_16_TO_18BIT(*pixels);
		ili9488_write_ram(color_666 >> 16);
		ili9488_write_ram(color_666 >> 8);
		ili9488_write_ram(color_666 & 0xFF);
		pixels++;
	}
#endif
}

/**
 * \brief Set a given number of pixels to the same color
 *
 * Use this function to write a certain number of pixels to the same color
 * within a set limit.
 *
 * Limits have to be set prior to calling this function, e.g.:
 * \code
 * ili9488_set_top_left_limit(0, 0);
 * ili9488_set_bottom_right_limit(320, 240);
 * ...
 * \endcode
 *
 * \param color The color to write to the display
 * \param count The number of pixels to write with this color
 */
void ili9488_duplicate_pixel(const uint16_t color, uint32_t count)
{
	ili9488_set_window(limit_start_x, limit_start_y, (limit_end_x - limit_start_x) + 1, (limit_end_y - limit_start_y) + 1);
	ili9488_write_ram_prepare();

#ifdef ILI9488_EBIMODE
	while (count--) {
		ili9488_write_ram(color);
	}
#endif
#ifdef ILI9488_SPIMODE
	uint32_t color_666 = RGB_16_TO_18BIT(color);
	while (count--) {
		ili9488_write_ram(color_666 >> 16);
		ili9488_write_ram(color_666 >> 8);
		ili9488_write_ram(color_666 & 0xFF);
	}
#endif
}

/**
 * \brief Copy pixels from the screen to a pixel buffer
 *
 * Use this function to copy pixels from the display to an internal SRAM buffer.
 *
 * Limits have to be set prior to calling this function, e.g.:
 * \code
 * ili9488_set_top_left_limit(0, 0);
 * ili9488_set_bottom_right_limit(320, 240);
 * ...
 * \endcode
 *
 * \param pixels Pointer to the pixel buffer to read to
 * \param count Number of pixels to read
 */
void ili9488_copy_pixels_from_screen(uint16_t *pixels, uint32_t count)
{
	ili9488_set_window(limit_start_x, limit_start_y, (limit_end_x - limit_start_x) + 1, (limit_end_y - limit_start_y) + 1);
	ili9488_write_register(ILI9488_CMD_MEMORY_READ, 0x0000, 0);
#ifdef ILI9488_EBIMODE
	pio_set(PIN_EBI_CDS_PIO, PIN_EBI_CDS_MASK);
	LCD_MULTI_RD(pixels, count);
#endif
#ifdef ILI9488_SPIMODE
	ili9488_color_t grambuf[3];
	pio_set_pin_high(LCD_SPI_CDS_PIO);
	spi_read_packet(BOARD_ILI9488_SPI, grambuf, 1);
	while (count--) {
		spi_read_packet(BOARD_ILI9488_SPI, grambuf, 3);

		*pixels = ILI9488_COLOR(grambuf[0], grambuf[1], grambuf[2]);
		pixels++;
	}
#endif
}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \}
 */
