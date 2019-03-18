/**
 * \file
 *
 * \brief API driver for ILI9325 TFT display component.
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

/**
 * \defgroup ili9325_display_group Display - ILI9325 Controller
 *
 * Low-level driver for the ILI9325 LCD controller. This driver provides access to the main
 * features of the ILI9325 controller.
 *
 * \{
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "ili9325.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
 extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/* Pixel cache used to speed up communication */
#define LCD_DATA_CACHE_SIZE ILI9325_LCD_WIDTH
static ili9325_color_t g_ul_pixel_cache[LCD_DATA_CACHE_SIZE];

static volatile ili9325_coord_t limit_start_x, limit_start_y;
static volatile ili9325_coord_t limit_end_x, limit_end_y;

/* Global variable describing the font size used by the driver */
const struct ili9325_font gfont = {10, 14};
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

/**
 * \brief Read 16 bit data.
 */
static uint16_t ili9325_lcd_get_16(void)
{
	uint16_t us_value;

	us_value = LCD_RD();
	us_value = (us_value << 8) | LCD_RD();

	return us_value;
}

/**
 * \brief Prepare to write GRAM data.
 */
static void ili9325_write_ram_prepare(void)
{
	LCD_IR(0);
	LCD_IR(ILI9325_GRAM_DATA_REG); /* Write Data to GRAM (R22h) */
}

/**
 * \brief Write data to LCD GRAM.
 *
 * \param ul_color 24-bits RGB color.
 */
static void ili9325_write_ram(ili9325_color_t ul_color)
{
	LCD_WD((ul_color >> 16) & 0xFF);
	LCD_WD((ul_color >> 8) & 0xFF);
	LCD_WD(ul_color & 0xFF);
}

/**
 * \brief Write multiple data in buffer to LCD controller.
 *
 * \param p_ul_buf data buffer.
 * \param ul_size size in pixels.
 */
static void ili9325_write_ram_buffer(const ili9325_color_t *p_ul_buf, uint32_t ul_size)
{
	uint32_t ul_addr;

	for (ul_addr = 0; ul_addr < (ul_size - ul_size % 8); ul_addr += 8) {
		ili9325_write_ram(p_ul_buf[ul_addr]);
		ili9325_write_ram(p_ul_buf[ul_addr + 1]);
		ili9325_write_ram(p_ul_buf[ul_addr + 2]);
		ili9325_write_ram(p_ul_buf[ul_addr + 3]);
		ili9325_write_ram(p_ul_buf[ul_addr + 4]);
		ili9325_write_ram(p_ul_buf[ul_addr + 5]);
		ili9325_write_ram(p_ul_buf[ul_addr + 6]);
		ili9325_write_ram(p_ul_buf[ul_addr + 7]);
	}
	for (; ul_addr < ul_size; ul_addr++) {
		ili9325_write_ram(p_ul_buf[ul_addr]);
	}
}

/**
 * \brief Write data to LCD Register.
 *
 * \param uc_reg register address.
 * \param us_data data to be written.
 */
static void ili9325_write_register(uint8_t uc_reg, uint16_t us_data)
{
	LCD_IR(0);
	LCD_IR(uc_reg);
	LCD_WD((us_data >> 8) & 0xFF);
	LCD_WD(us_data & 0xFF);
}

/**
 * \brief Prepare to read GRAM data.
 */
static void ili9325_read_ram_prepare(void)
{
	LCD_IR(0);
	LCD_IR(ILI9325_GRAM_DATA_REG); /* Write Data to GRAM (R22h) */
}

/**
 * \brief Read data to LCD GRAM.
 *
 * \note Because pixel data LCD GRAM is 18-bits, so convertion to RGB 24-bits
 * will cause low color bit lose.
 *
 * \return color 24-bits RGB color.
 */
static uint32_t ili9325_read_ram(void)
{
	uint8_t value[2];
	uint32_t color;

	value[0] = LCD_RD();       /* dummy read */
	value[1] = LCD_RD();       /* dummy read */
	value[0] = LCD_RD();       /* data upper byte */
	value[1] = LCD_RD();       /* data lower byte */

	/* Convert RGB565 to RGB888 */
	/* For BGR format */
	color = ((value[0] & 0xF8)) |  /* R */
			((value[0] & 0x07) << 13) | ((value[1] & 0xE0) << 5) |  /* G */
			((value[1] & 0x1F) << 19);  /* B */

	return color;
}

/**
 * \brief Read data from LCD Register.
 *
 * \param uc_reg register address.
 *
 * \return register value.
 */
static uint16_t ili9325_read_register(uint8_t uc_reg)
{
	LCD_IR(0);
	LCD_IR(uc_reg);

	return ili9325_lcd_get_16();
}

/**
 * \brief Delay function.
 */
static void ili9325_delay(uint32_t ul_ms)
{
	volatile uint32_t i;

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
static void ili9325_check_box_coordinates(uint32_t *p_ul_x1, uint32_t *p_ul_y1,
		uint32_t *p_ul_x2, uint32_t *p_ul_y2)
{
	uint32_t dw;

	if (*p_ul_x1 >= ILI9325_LCD_WIDTH) {
		*p_ul_x1 = ILI9325_LCD_WIDTH - 1;
	}

	if (*p_ul_x2 >= ILI9325_LCD_WIDTH) {
		*p_ul_x2 = ILI9325_LCD_WIDTH - 1;
	}

	if (*p_ul_y1 >= ILI9325_LCD_HEIGHT) {
		*p_ul_y1 = ILI9325_LCD_HEIGHT - 1;
	}

	if (*p_ul_y2 >= ILI9325_LCD_HEIGHT) {
		*p_ul_y2 = ILI9325_LCD_HEIGHT - 1;
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
 * \brief Initialize the ILI9325 lcd driver.
 *
 * \note Make sure below works have been done before calling ili9325_init()\n
 * 1. ILI9325 related Pins have been initialized correctly. \n
 * 2. SMC has been configured correctly for access ILI9325 (8-bit system interface for now). \n
 *
 * \param p_opt pointer to ILI9325 option structure.
 *
 * \return 0 if initialization succeeds, otherwise fails.
 */
uint32_t ili9325_init(struct ili9325_opt_t *p_opt)
{
	/* Check ILI9325 chipid */
	uint16_t chipid = ili9325_read_register(ILI9325_DEVICE_CODE_REG); /* Driver Code Read (R00h) */

	if (chipid != ILI9325_DEVICE_CODE) {
		return 1;
	}

	/* Turn off LCD */
	ili9325_write_register(ILI9325_DISP_CTRL1, ILI9325_DISP_CTRL1_GON |
			ILI9325_DISP_CTRL1_DTE | ILI9325_DISP_CTRL1_D(0x03));

	/* Start initial sequence */
	/* Disable sleep and standby mode*/
	ili9325_write_register(ILI9325_POWER_CTRL1, 0x0000);
	/* Start internal OSC */
	ili9325_write_register(ILI9325_START_OSC_CTRL, ILI9325_START_OSC_CTRL_EN);
	/* Set SS bit and direction output from S720 to S1 */
	ili9325_write_register(ILI9325_DRIVER_OUTPUT_CTRL1, ILI9325_DRIVER_OUTPUT_CTRL1_SS);
	/* Set 1 line inversion */
	ili9325_write_register(ILI9325_LCD_DRIVING_CTRL, ILI9325_LCD_DRIVING_CTRL_BIT10 |
			ILI9325_LCD_DRIVING_CTRL_EOR | ILI9325_LCD_DRIVING_CTRL_BC0);
	/* Disable resizing feature */
	ili9325_write_register(ILI9325_RESIZE_CTRL, 0x0000);
	/* Set the back porch and front porch */
	ili9325_write_register(ILI9325_DISP_CTRL2, ILI9325_DISP_CTRL2_BP(0x07) |
			ILI9325_DISP_CTRL2_FP(0x02));
	/* Set non-display area refresh cycle ISC[3:0] */
	ili9325_write_register(ILI9325_DISP_CTRL3, 0x0000);
	/* Disable FMARK function */
	ili9325_write_register(ILI9325_DISP_CTRL4, 0x0000);
	/* 18-bit RGB interface and writing display data by the system interface */
	ili9325_write_register(ILI9325_RGB_DISP_INTERFACE_CTRL1, 0x0000);
	/* Set the output position of frame cycle */
	ili9325_write_register(ILI9325_FRAME_MAKER_POS, 0x0000);
	/* RGB interface polarity */
	ili9325_write_register(ILI9325_RGB_DISP_INTERFACE_CTRL2, 0x0000);

	/* Power on sequence */
	/* Disable sleep and standby mode */
	ili9325_write_register(ILI9325_POWER_CTRL1, 0x0000);
	/* Selects the operating frequency of the step-up circuit 1,2 and Sets the ratio factor of Vci */
	ili9325_write_register(ILI9325_POWER_CTRL2, 0x0000);
	/* Set VREG1OUT voltage */
	ili9325_write_register(ILI9325_POWER_CTRL3, 0x0000);
	/* Set VCOM amplitude */
	ili9325_write_register(ILI9325_POWER_CTRL4, 0x0000);
	ili9325_delay(200);

	/* Enable power supply and source driver */
	/* Adjusts the constant current and Sets the factor used in the step-up circuits.*/
	ili9325_write_register(ILI9325_POWER_CTRL1, ILI9325_POWER_CTRL1_SAP |
			ILI9325_POWER_CTRL1_BT(0x02) | ILI9325_POWER_CTRL1_APE | ILI9325_POWER_CTRL1_AP(0x01));
	/* Select the operating frequency of the step-up circuit 1,2 and Sets the ratio factor of Vci */
	ili9325_write_register(ILI9325_POWER_CTRL2, ILI9325_POWER_CTRL2_DC1(0x02) |
			ILI9325_POWER_CTRL2_DC0(0x02) | ILI9325_POWER_CTRL2_VC(0x07));
	ili9325_delay(50);
	/* Internal reference voltage= Vci */
	ili9325_write_register(ILI9325_POWER_CTRL3, ILI9325_POWER_CTRL3_PON |
			ILI9325_POWER_CTRL3_VRH(0x0B));
	ili9325_delay(50);
	/* Set VDV[4:0] for VCOM amplitude */
	ili9325_write_register(ILI9325_POWER_CTRL4, ILI9325_POWER_CTRL4_VDV(0x11));
	/* Set VCM[5:0] for VCOMH */
	ili9325_write_register(ILI9325_POWER_CTRL7, ILI9325_POWER_CTRL7_VCM(0x19));
	/* Set Frame Rate */
	ili9325_write_register(ILI9325_FRAME_RATE_AND_COLOR_CTRL,
			ILI9325_FRAME_RATE_AND_COLOR_CTRL_FRS(0x0D));
	ili9325_delay(50);

	/* Adjust the Gamma Curve */
	ili9325_write_register(ILI9325_GAMMA_CTRL1, 0x0000);
	ili9325_write_register(ILI9325_GAMMA_CTRL2, ILI9325_GAMMA_CTRL2_KP3(0x02) |
			ILI9325_GAMMA_CTRL2_KP2(0x04));
	ili9325_write_register(ILI9325_GAMMA_CTRL3, ILI9325_GAMMA_CTRL3_KP5(0x02) |
			ILI9325_GAMMA_CTRL3_KP4(0x00));
	ili9325_write_register(ILI9325_GAMMA_CTRL4, ILI9325_GAMMA_CTRL4_RP1(0x00) |
			ILI9325_GAMMA_CTRL4_RP0(0x07));
	ili9325_write_register(ILI9325_GAMMA_CTRL5, ILI9325_GAMMA_CTRL5_VRP1(0x14) |
			ILI9325_GAMMA_CTRL5_VRP0(0x04));
	ili9325_write_register(ILI9325_GAMMA_CTRL6, ILI9325_GAMMA_CTRL6_KN1(0x07) |
			ILI9325_GAMMA_CTRL6_KN0(0x05));
	ili9325_write_register(ILI9325_GAMMA_CTRL7, ILI9325_GAMMA_CTRL7_KN3(0x03) |
			ILI9325_GAMMA_CTRL7_KN2(0x05));
	ili9325_write_register(ILI9325_GAMMA_CTRL8, ILI9325_GAMMA_CTRL8_KN5(0x07) |
			ILI9325_GAMMA_CTRL8_KN4(0x07));
	ili9325_write_register(ILI9325_GAMMA_CTRL9, ILI9325_GAMMA_CTRL9_RN1(0x07) |
			ILI9325_GAMMA_CTRL9_RN0(0x01));
	ili9325_write_register(ILI9325_GAMMA_CTRL10, ILI9325_GAMMA_CTRL10_VRN1(0x00) |
			ILI9325_GAMMA_CTRL10_VRN0(0x0E));
	/* Use the high speed write mode (HWM=1) */
	/* When TRI = 1, data are transferred to the internal RAM in 8-bit x 3 transfers mode via the 8-bit interface. */
	/* DFM Set the mode of transferring data to the internal RAM when TRI = 1. */
	/* I/D[1:0] = 11 Horizontal : increment Vertical : increment, AM=0:Horizontal */
	ili9325_write_register(ILI9325_ENTRY_MODE, ILI9325_ENTRY_MODE_TRI |
			ILI9325_ENTRY_MODE_DFM | ILI9325_ENTRY_MODE_ID(0x01) |ILI9325_ENTRY_MODE_BGR);
	/* Sets the number of lines to drive the LCD at an interval of 8 lines. */
	/* The scan direction is from G320 to G1 */
	ili9325_write_register(ILI9325_DRIVER_OUTPUT_CTRL2, ILI9325_DRIVER_OUTPUT_CTRL2_GS |
			ILI9325_DRIVER_OUTPUT_CTRL2_NL(0x27));

	/* Vertical Scrolling */
	/* Disable scrolling and enable the grayscale inversion */
	ili9325_write_register(ILI9325_BASE_IMG_DISP_CTRL, ILI9325_BASE_IMG_DISP_CTRL_REV);
	ili9325_write_register(ILI9325_VERTICAL_SCROLL_CTRL, 0x0000);

	/* Disable Partial Display */
	ili9325_write_register(ILI9325_PARTIAL_IMG1_DISP_POS, 0x0000);
	ili9325_write_register(ILI9325_PARTIAL_IMG1_AREA_START_LINE, 0x0000);
	ili9325_write_register(ILI9325_PARTIAL_IMG1_AREA_END_LINE, 0x0000);
	ili9325_write_register(ILI9325_PARTIAL_IMG2_DISP_POS, 0x0000);
	ili9325_write_register(ILI9325_PARTIAL_IMG2_AREA_START_LINE, 0x0000);
	ili9325_write_register(ILI9325_PARTIAL_IMG2_AREA_END_LINE, 0x0000);

	/* Panel Control */
	ili9325_write_register(ILI9325_PANEL_INTERFACE_CTRL1,
			ILI9325_PANEL_INTERFACE_CTRL1_RTNI(0x10));
	ili9325_write_register(ILI9325_PANEL_INTERFACE_CTRL2,
			ILI9325_PANEL_INTERFACE_CTRL2_NOWI(0x06));
	ili9325_write_register(ILI9325_PANEL_INTERFACE_CTRL4,
			ILI9325_PANEL_INTERFACE_CTRL4_DIVE(0x01) |
			ILI9325_PANEL_INTERFACE_CTRL4_RTNE(0x10));

	ili9325_set_window(0, 0,p_opt->ul_width,p_opt->ul_height);
	ili9325_set_foreground_color(p_opt->foreground_color);
	ili9325_set_cursor_position(0, 0);
	return 0;
}

/**
 * \brief Turn on the LCD.
 */
void ili9325_display_on(void)
{
	ili9325_write_register(ILI9325_DISP_CTRL1,
			ILI9325_DISP_CTRL1_BASEE |
			ILI9325_DISP_CTRL1_GON |
			ILI9325_DISP_CTRL1_DTE |
			ILI9325_DISP_CTRL1_D(0x03));
}

/**
 * \brief Turn off the LCD.
 */
void ili9325_display_off(void)
{
	ili9325_write_register(ILI9325_DISP_CTRL1, 0x00);
}

/**
 * \brief Set foreground color.
 *
 * \param ul_color foreground color.
 */
void ili9325_set_foreground_color(ili9325_color_t ul_color)
{
	uint32_t i;

	/* Fill the cache with selected color */
	for (i = 0; i < LCD_DATA_CACHE_SIZE; ++i) {
		g_ul_pixel_cache[i] = ul_color;
	}
}

/**
 * \brief Fill the LCD buffer with the specified color.
 *
 * \param ul_color fill color.
 */
void ili9325_fill(ili9325_color_t ul_color)
{
	uint32_t dw;

	ili9325_set_cursor_position(0, 0);
	ili9325_write_ram_prepare();

	for (dw = ILI9325_LCD_WIDTH * ILI9325_LCD_HEIGHT; dw > 0; dw--) {
		ili9325_write_ram(ul_color);
	}
}

/**
 * \brief Set display window.
 *
 * \param ul_x Horizontal address start position
 * \param ul_y Vertical address start position
 * \param ul_width The width of the window.
 * \param ul_height The height of the window.
 */
void ili9325_set_window(uint32_t ul_x, uint32_t ul_y, uint32_t ul_width,
		uint32_t ul_height)
{
	Assert(ul_x <= 0xEF);
	Assert(ul_y <= 0x13f);
	Assert(ul_width <= (0xF0 - ul_x));
	Assert(ul_height <= (0x140 - ul_y));

	/* Set Horizontal Address Start Position */
	ili9325_write_register(ILI9325_HORIZONTAL_ADDR_START, (uint16_t)ul_x);

	/* Set Horizontal Address End Position */
	ili9325_write_register(ILI9325_HORIZONTAL_ADDR_END, (uint16_t)(ul_x + ul_width - 1));

	/* Set Vertical Address Start Position */
	ili9325_write_register(ILI9325_VERTICAL_ADDR_START, (uint16_t)ul_y);

	/* Set Vertical Address End Position */
	ili9325_write_register(ILI9325_VERTICAL_ADDR_END, (uint16_t)(ul_y + ul_height - 1));
}

/**
 * \brief Set cursor of LCD screen.
 *
 * \param us_x X coordinate of upper-left corner on LCD.
 * \param us_y Y coordinate of upper-left corner on LCD.
 */
void ili9325_set_cursor_position(uint16_t us_x, uint16_t us_y)
{
	/* GRAM Horizontal/Vertical Address Set (R20h, R21h) */
	ili9325_write_register(ILI9325_HORIZONTAL_GRAM_ADDR_SET, us_x); /* column */
	ili9325_write_register(ILI9325_VERTICAL_GRAM_ADDR_SET, us_y); /* row */
}

/**
 * \brief Scroll up/down for the number of specified lines.
 *
 * \param ul_lines number of lines to scroll.
 */
void ili9325_scroll(int32_t ul_lines)
{
	ili9325_write_register(ILI9325_VERTICAL_SCROLL_CTRL, ul_lines);
}

/**
 * \brief Enable the scrolling feature.
 */
void ili9325_enable_scroll(void)
{
	ili9325_write_register(ILI9325_BASE_IMG_DISP_CTRL,
			ILI9325_BASE_IMG_DISP_CTRL_REV |
			ILI9325_BASE_IMG_DISP_CTRL_VLE);
}

/**
 * \brief Disable the scrolling feature.
 */
void ili9325_disable_scroll(void)
{
	ili9325_write_register(ILI9325_BASE_IMG_DISP_CTRL, ILI9325_BASE_IMG_DISP_CTRL_REV);
}

/**
 * \brief Set display direction.
 *
 * \param dd 0: horizontal direction, 1: vertical direction
 * \param shd horizontal increase(1) or decrease(0)
 * \param scd vertical increase(1) or decrease(0)
 */
void ili9325_set_display_direction(enum ili9325_display_direction e_dd, enum ili9325_shift_direction e_shd,
		enum ili9325_scan_direction e_scd)
{
	if (e_dd == LANDSCAPE) {
		ili9325_write_register(ILI9325_ENTRY_MODE,
				ILI9325_ENTRY_MODE_AM | ILI9325_ENTRY_MODE_DFM |
				ILI9325_ENTRY_MODE_TRI | ILI9325_ENTRY_MODE_HWM |
				ILI9325_ENTRY_MODE_ORG);
	} else {
		ili9325_write_register(ILI9325_ENTRY_MODE,
				ILI9325_ENTRY_MODE_HWM | ILI9325_ENTRY_MODE_TRI |
				ILI9325_ENTRY_MODE_DFM | ILI9325_ENTRY_MODE_ID(0x03));
	}
	if (e_shd == H_INCREASE) {
		ili9325_write_register(ILI9325_DRIVER_OUTPUT_CTRL1, 0x0000);
	} else {
		ili9325_write_register(ILI9325_DRIVER_OUTPUT_CTRL1,
				ILI9325_DRIVER_OUTPUT_CTRL1_SS);
	}
	if (e_scd == V_INCREASE) {
		ili9325_write_register(ILI9325_DRIVER_OUTPUT_CTRL2, 0x0000);
	} else {
		ili9325_write_register(ILI9325_DRIVER_OUTPUT_CTRL2,
				ILI9325_DRIVER_OUTPUT_CTRL2_GS);
	}
}

/**
 * \brief Draw a pixel on LCD.
 *
 * \param ul_x X coordinate of pixel.
 * \param ul_y Y coordinate of pixel.
 *
 * \return 0 if succeeds, otherwise fails.
 */
uint32_t ili9325_draw_pixel(uint32_t ul_x, uint32_t ul_y)
{
	if ((ul_x >= ILI9325_LCD_WIDTH) || (ul_y >= ILI9325_LCD_HEIGHT)) {
		return 1;
	}

	/* Set cursor */
	ili9325_set_cursor_position(ul_x, ul_y);

	/* Prepare to write in GRAM */
	ili9325_write_ram_prepare();
	ili9325_write_ram(*g_ul_pixel_cache);
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
ili9325_color_t ili9325_get_pixel(uint32_t ul_x, uint32_t ul_y)
{
	Assert(ul_x <= ILI9325_LCD_WIDTH);
	Assert(ul_y <= ILI9325_LCD_HEIGHT);

	/* Set cursor */
	ili9325_set_cursor_position(ul_x, ul_y);

	/* Prepare to write in GRAM */
	ili9325_read_ram_prepare();
	return ili9325_read_ram();
}

/**
 * \brief Draw a line on LCD, which is not horizontal or vertical.
 *
 * \param ul_x1 X coordinate of line start.
 * \param ul_y1 Y coordinate of line start.
 * \param ul_x2 X coordinate of line end.
 * \param ul_y2 Y coordinate of line endl.
 */
static void ili9325_draw_line_bresenham(uint32_t ul_x1, uint32_t ul_y1,
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

	ili9325_draw_pixel(x, y);

	if (dx > dy) {
		cumul = dx >> 1;

		for (i = 1; i <= dx; i++) {
			x += xinc;
			cumul += dy;

			if (cumul >= dx) {
				cumul -= dx;
				y += yinc;
			}

			ili9325_draw_pixel(x, y);
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

			ili9325_draw_pixel(x, y);
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
void ili9325_draw_line(uint32_t ul_x1, uint32_t ul_y1,
		uint32_t ul_x2, uint32_t ul_y2)
{
	if ((ul_y1 == ul_y2) || (ul_x1 == ul_x2)) {
		ili9325_draw_filled_rectangle(ul_x1, ul_y1, ul_x2, ul_y2);
	} else {
		ili9325_draw_line_bresenham(ul_x1, ul_y1, ul_x2, ul_y2);
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
void ili9325_draw_rectangle(uint32_t ul_x1, uint32_t ul_y1,
		uint32_t ul_x2, uint32_t ul_y2)
{
	ili9325_check_box_coordinates(&ul_x1, &ul_y1, &ul_x2, &ul_y2);

	ili9325_draw_filled_rectangle(ul_x1, ul_y1, ul_x2, ul_y1);
	ili9325_draw_filled_rectangle(ul_x1, ul_y2, ul_x2, ul_y2);

	ili9325_draw_filled_rectangle(ul_x1, ul_y1, ul_x1, ul_y2);
	ili9325_draw_filled_rectangle(ul_x2, ul_y1, ul_x2, ul_y2);
}

/**
 * \brief Draw a filled rectangle on LCD.
 *
 * \param ul_x1 X coordinate of upper-left corner on LCD.
 * \param ul_y1 Y coordinate of upper-left corner on LCD.
 * \param ul_x2 X coordinate of lower-right corner on LCD.
 * \param ul_y2 Y coordinate of lower-right corner on LCD.
 */
void ili9325_draw_filled_rectangle(uint32_t ul_x1, uint32_t ul_y1,
		uint32_t ul_x2, uint32_t ul_y2)
{
	uint32_t size, blocks;

	/* Swap coordinates if necessary */
	ili9325_check_box_coordinates(&ul_x1, &ul_y1, &ul_x2, &ul_y2);

	/* Determine the refresh window area */
	ili9325_set_window(ul_x1, ul_y1, (ul_x2 - ul_x1) + 1, (ul_y2 - ul_y1) + 1);

	/* Set cursor */
	ili9325_set_cursor_position(ul_x1, ul_y1);

	/* Prepare to write in GRAM */
	ili9325_write_ram_prepare();

	size = (ul_x2 - ul_x1 + 1) * (ul_y2 - ul_y1 + 1);
	/* Send pixels blocks => one SPI IT / block */
	blocks = size / LCD_DATA_CACHE_SIZE;
	while (blocks--) {
		ili9325_write_ram_buffer(g_ul_pixel_cache, LCD_DATA_CACHE_SIZE);
	}
	/* Send remaining pixels */
	ili9325_write_ram_buffer(g_ul_pixel_cache, size % LCD_DATA_CACHE_SIZE);

	/* Reset the refresh window area */
	ili9325_set_window(0, 0, ILI9325_LCD_WIDTH, ILI9325_LCD_HEIGHT);
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
uint32_t ili9325_draw_circle(uint32_t ul_x, uint32_t ul_y, uint32_t ul_r)
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
		ili9325_draw_pixel(ul_x + curX, ul_y + curY);
		ili9325_draw_pixel(ul_x + curX, ul_y - curY);
		ili9325_draw_pixel(ul_x - curX, ul_y + curY);
		ili9325_draw_pixel(ul_x - curX, ul_y - curY);
		ili9325_draw_pixel(ul_x + curY, ul_y + curX);
		ili9325_draw_pixel(ul_x + curY, ul_y - curX);
		ili9325_draw_pixel(ul_x - curY, ul_y + curX);
		ili9325_draw_pixel(ul_x - curY, ul_y - curX);

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
uint32_t ili9325_draw_filled_circle(uint32_t ul_x, uint32_t ul_y, uint32_t ul_r)
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
		ili9325_draw_filled_rectangle(dwXmin, dwYmin, ul_x + dwCurX, dwYmin);
		ili9325_draw_filled_rectangle(dwXmin, ul_y + dwCurY, ul_x + dwCurX, ul_y + dwCurY);
		dwXmin = (dwCurY > ul_x) ? 0 : ul_x - dwCurY;
		dwYmin = (dwCurX > ul_y) ? 0 : ul_y - dwCurX;
		ili9325_draw_filled_rectangle(dwXmin, dwYmin, ul_x + dwCurY, dwYmin);
		ili9325_draw_filled_rectangle(dwXmin, ul_y + dwCurX, ul_x + dwCurY, ul_y + dwCurX);

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
void ili9325_draw_prepare(uint32_t ul_x, uint32_t ul_y, uint32_t ul_width,
		uint32_t ul_height)
{
	/* Determine the refresh window area */
	ili9325_set_window(ul_x, ul_y, ul_width, ul_height);

	/* Set cursor */
	ili9325_set_cursor_position(ul_x, ul_y);

	/* Prepare to write in GRAM */
	ili9325_write_ram_prepare();
}

/**
 * \brief Draw an ASCII character on LCD.
 *
 * \param ul_x X coordinate of character upper-left corner.
 * \param ul_y Y coordinate of character upper-left corner.
 * \param uc_c character to print.
 */
static void ili9325_draw_char(uint32_t ul_x, uint32_t ul_y, uint8_t uc_c)
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
				ili9325_draw_pixel(ul_x + col, ul_y + row);
			}
		}

		for (row = 0; row < 6; row++) {
			if ((p_uc_charset10x14[offset1] >> (7 - row)) & 0x1) {
				ili9325_draw_pixel(ul_x + col, ul_y + row + 8);
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
void ili9325_draw_string(uint32_t ul_x, uint32_t ul_y, const uint8_t *p_str)
{
	uint32_t xorg = ul_x;

	while (*p_str != 0) {
		/* If newline, jump to the next line (font height + 2) */
		if (*p_str == '\n') {
			ul_y += gfont.height + 2;
			ul_x = xorg;
		} else {
			/* Draw the character and place cursor right after (font width + 2) */
			ili9325_draw_char(ul_x, ul_y, *p_str);
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
void ili9325_draw_pixmap(uint32_t ul_x, uint32_t ul_y, uint32_t ul_width,
		uint32_t ul_height, const ili9325_color_t *p_ul_pixmap)
{
	uint32_t size;
	uint32_t dwX1, dwY1, dwX2, dwY2;
	dwX1 = ul_x;
	dwY1 = ul_y;
	dwX2 = ul_x + ul_width;
	dwY2 = ul_y + ul_height;

	/* Swap coordinates if necessary */
	ili9325_check_box_coordinates(&dwX1, &dwY1, &dwX2, &dwY2);

	/* Determine the refresh window area */
	ili9325_set_window(dwX1, dwY1, (dwX2 - dwX1 + 1), (dwY2 - dwY1 + 1));

	/* Set cursor */
	ili9325_set_cursor_position(dwX1, dwY1);

	/* Prepare to write in GRAM */
	ili9325_write_ram_prepare();

	size = (dwX2 - dwX1) * (dwY2 - dwY1);

	ili9325_write_ram_buffer(p_ul_pixmap, size);

	/* Reset the refresh window area */
	ili9325_set_window(0, 0, ILI9325_LCD_WIDTH, ILI9325_LCD_HEIGHT);
}

/**
 * \internal
 * \brief Helper function to send the drawing limits (boundaries) to the display
 *
 * This function is used to send the currently set upper-left and lower-right
 * drawing limits to the display, as set through the various limit functions.
 *
 * \param send_end_limits  True to also send the lower-right drawing limits
 */
static inline void ili9325_send_draw_limits(const bool send_end_limits)
{
	/* Set Horizontal Address Start Position */
	ili9325_write_register(ILI9325_HORIZONTAL_ADDR_START, (uint16_t)limit_start_x);

	if (send_end_limits) {
		/* Set Horizontal Address End Position */
		ili9325_write_register(ILI9325_HORIZONTAL_ADDR_END,
			(uint16_t)(limit_end_x));
	}

	/* Set Vertical Address Start Position */
	ili9325_write_register(ILI9325_VERTICAL_ADDR_START, (uint16_t)limit_start_y);
	if (send_end_limits) {
		/* Set Vertical Address End Position */
		ili9325_write_register(ILI9325_VERTICAL_ADDR_END,
			(uint16_t)(limit_end_y));
	}

	/* GRAM Horizontal/Vertical Address Set (R20h, R21h) */
	ili9325_write_register(ILI9325_HORIZONTAL_GRAM_ADDR_SET, limit_start_x); /* column */
	ili9325_write_register(ILI9325_VERTICAL_GRAM_ADDR_SET, limit_start_y); /* row */
}

/**
 * \brief Set the display top left drawing limit
 *
 * Use this function to set the top left limit of the drawing limit box.
 *
 * \param x The x coordinate of the top left corner
 * \param y The y coordinate of the top left corner
 */
void ili9325_set_top_left_limit(ili9325_coord_t x, ili9325_coord_t y)
{
	limit_start_x = x;
	limit_start_y = y;

	ili9325_send_draw_limits(false);
}

/**
 * \brief Set the display bottom right drawing limit
 *
 * Use this function to set the bottom right corner of the drawing limit box.
 *
 * \param x The x coordinate of the bottom right corner
 * \param y The y coordinate of the bottom right corner
 */
void ili9325_set_bottom_right_limit(ili9325_coord_t x, ili9325_coord_t y)
{
	limit_end_x = x;
	limit_end_y = y;

	ili9325_send_draw_limits(true);
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
void ili9325_set_limits(ili9325_coord_t start_x, ili9325_coord_t start_y,
		ili9325_coord_t end_x, ili9325_coord_t end_y)
{
	limit_start_x = start_x;
	limit_start_y = start_y;
	limit_end_x = end_x;
	limit_end_y = end_y;

	ili9325_send_draw_limits(true);
}

/**
 * \brief Read a single color from the graphical memory
 *
 * Use this function to read a color from the graphical memory of the
 * controller.
 *
 * Limits have to be set prior to calling this function, e.g.:
 * \code
	ili9325_set_top_left_limit(0, 0);
	ili9325_set_bottom_right_limit(320, 240);
	...
\endcode
 *
 * \retval ili9325_color_t The read color pixel
 */
ili9325_color_t ili9325_read_gram(void)
{
	uint8_t value[2];
	ili9325_color_t color;

	LCD_IR(0);
	LCD_IR(ILI9325_GRAM_DATA_REG); /* Write Data to GRAM (R22h) */

	value[0] = LCD_RD();       /* dummy read */
	value[1] = LCD_RD();       /* dummy read */
	value[0] = LCD_RD();       /* data upper byte */
	value[1] = LCD_RD();       /* data lower byte */

	/* Convert RGB565 to RGB888 */
	/* For BGR format */
	color = ((value[0] & 0xF8)) |  /* R */
			((value[0] & 0x07) << 13) | ((value[1] & 0xE0) << 5) |  /* G */
			((value[1] & 0x1F) << 19);  /* B */

	return color;
}

/**
 * \brief Write the graphical memory with a single color pixel
 *
 * Use this function to write a single color pixel to the controller memory.
 *
 * Limits have to be set prior to calling this function, e.g.:
 * \code
	ili9325_set_top_left_limit(0, 0);
	ili9325_set_bottom_right_limit(320, 240);
	...
\endcode
 *
 * \param color The color pixel to write to the screen
 */
void ili9325_write_gram(ili9325_color_t color)
{
	/* Only 16-bit color supported */
	Assert(sizeof(color) == 2);

	LCD_IR(0);
	LCD_IR(ILI9325_GRAM_DATA_REG); /* Write Data to GRAM (R22h) */

	LCD_WD((color >> 16) & 0xFF);
	LCD_WD((color >> 8) & 0xFF);
	LCD_WD(color & 0xFF);
}

/**
 * \brief Copy pixels from SRAM to the screen
 *
 * Used to copy a large quantitative of data to the screen in one go.
 *
 * Limits have to be set prior to calling this function, e.g.:
 * \code
	ili9325_set_top_left_limit(0, 0);
	ili9325_set_bottom_right_limit(320, 240);
	...
\endcode
 *
 * \param pixels Pointer to the pixel data
 * \param count Number of pixels to copy to the screen
 */
void ili9325_copy_pixels_to_screen(const ili9325_color_t *pixels, uint32_t count)
{
	/* Sanity check to make sure that the pixel count is not zero */
	Assert(count > 0);

	LCD_IR(0);
	LCD_IR(ILI9325_GRAM_DATA_REG); /* Write Data to GRAM (R22h) */

	while (count--) {
		LCD_WD((*pixels >> 16) & 0xFF);
		LCD_WD((*pixels >> 8) & 0xFF);
		LCD_WD(*pixels & 0xFF);

		pixels++;
	}
}

/**
 * \brief Copy pixels from SRAM to the screen
 *
 * Used to copy a large quantitative of data to the screen in one go.
 *
 * Limits have to be set prior to calling this function, e.g.:
 * \code
	ili9325_set_top_left_limit(0, 0);
	ili9325_set_bottom_right_limit(320, 240);
	...
\endcode
 *
 * \param pixels Pointer to the pixel data
 * \param count Number of pixels to copy to the screen
 */
void ili9325_copy_raw_pixel_24bits_to_screen(const uint8_t *raw_pixels, uint32_t count)
{
	ili9325_color_t pixels;

	/* Sanity check to make sure that the pixel count is not zero */
	Assert(count > 0);

	LCD_IR(0);
	LCD_IR(ILI9325_GRAM_DATA_REG); /* Write Data to GRAM (R22h) */

	while (count--) {
		pixels = (*raw_pixels)  | (*(raw_pixels+1)) << 8 | *(raw_pixels+2)<<16;
		LCD_WD((pixels >> 16) & 0xFF);
		LCD_WD((pixels >> 8) & 0xFF);
		LCD_WD(pixels & 0xFF);

		raw_pixels +=3;
	}
}


/**
 * \brief Set a given number of pixels to the same color
 *
 * Use this function to write a certain number of pixels to the same color
 * within a set limit.
 *
 * Limits have to be set prior to calling this function, e.g.:
 * \code
	ili9325_set_top_left_limit(0, 0);
	ili9325_set_bottom_right_limit(320, 240);
	...
\endcode
 *
 * \param color The color to write to the display
 * \param count The number of pixels to write with this color
 */
void ili9325_duplicate_pixel(const ili9325_color_t color, uint32_t count)
{
	/* Sanity check to make sure that the pixel count is not zero */
	Assert(count > 0);

	LCD_IR(0);
	LCD_IR(ILI9325_GRAM_DATA_REG); /* Write Data to GRAM (R22h) */

	while (count--) {
		LCD_WD((color >> 16) & 0xFF);
		LCD_WD((color >> 8) & 0xFF);
		LCD_WD(color & 0xFF);

	}
}

/**
 * \brief Copy pixels from the screen to a pixel buffer
 *
 * Use this function to copy pixels from the display to an internal SRAM buffer.
 *
 * Limits have to be set prior to calling this function, e.g.:
 * \code
	ili9325_set_top_left_limit(0, 0);
	ili9325_set_bottom_right_limit(320, 240);
	...
\endcode
 *
 * \param pixels Pointer to the pixel buffer to read to
 * \param count Number of pixels to read
 */
void ili9325_copy_pixels_from_screen(ili9325_color_t *pixels, uint32_t count)
{
	/* Remove warnings */
	UNUSED(pixels);
	UNUSED(count);
}

/**
 * \brief Sets the orientation of the display data
 *
 * Configures the display for a given orientation, including mirroring and/or
 * screen rotation.
 *
 * \param flags Orientation flags to use, see \ref ILI9325_FLIP_X, \ref ILI9325_FLIP_Y
 *        and \ref ILI9325_SWITCH_XY.
 */
void ili9325_set_orientation(uint8_t flags)
{
	uint16_t setting = 0;

	setting |= (flags & ILI9325_FLIP_X ? ILI9325_ENTRY_MODE_ID(0x01) : 0);
	setting |= (flags & ILI9325_FLIP_Y ? ILI9325_ENTRY_MODE_ID(0x10) : 0);
	setting |= (flags & ILI9325_SWITCH_XY ? ILI9325_ENTRY_MODE_AM : 0);

	ili9325_write_register(ILI9325_ENTRY_MODE, ILI9325_ENTRY_MODE_TRI |
			ILI9325_ENTRY_MODE_DFM |setting |ILI9325_ENTRY_MODE_BGR);
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
