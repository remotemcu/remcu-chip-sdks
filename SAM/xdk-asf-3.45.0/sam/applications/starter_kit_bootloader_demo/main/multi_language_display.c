/**
 * \file
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

#include "conf_example.h"
#include "multi_language_display.h"
#include "unicode_font_table.h"
#include "unicode_string.h"
#include "ssd1306.h"
#include "font.h"
#include "delay.h"

#ifndef CONF_ENGLISH_LANGUAGE
/* Font bitmap buffer. */
uint8_t font_bitmap_origin[32];
uint8_t font_bitmap_show[32];
uint8_t font_bitmap_width;

/**
 * \brief Transfer the font bitmap data to fit the display.
 */
static void font_bitmap_transfer(void)
{
	if (font_bitmap_width == 2) {
		font_bitmap_show[0] = ((font_bitmap_origin[0] & 0x80) >> 7) |
				((font_bitmap_origin[2] & 0x80) >> 6) |
				((font_bitmap_origin[4] & 0x80) >> 5) |
				((font_bitmap_origin[6] & 0x80) >> 4) |
				((font_bitmap_origin[8] & 0x80) >> 3) |
				((font_bitmap_origin[10] & 0x80) >> 2) |
				((font_bitmap_origin[12] & 0x80) >> 1) |
				((font_bitmap_origin[14] & 0x80) >> 0);
		font_bitmap_show[1] = ((font_bitmap_origin[0] & 0x40) >> 6) |
				((font_bitmap_origin[2] & 0x40) >> 5) |
				((font_bitmap_origin[4] & 0x40) >> 4) |
				((font_bitmap_origin[6] & 0x40) >> 3) |
				((font_bitmap_origin[8] & 0x40) >> 2) |
				((font_bitmap_origin[10] & 0x40) >> 1) |
				((font_bitmap_origin[12] & 0x40) >> 0) |
				((font_bitmap_origin[14] & 0x40) << 1);
		font_bitmap_show[2] = ((font_bitmap_origin[0] & 0x20) >> 5) |
				((font_bitmap_origin[2] & 0x20) >> 4) |
				((font_bitmap_origin[4] & 0x20) >> 3) |
				((font_bitmap_origin[6] & 0x20) >> 2) |
				((font_bitmap_origin[8] & 0x20) >> 1) |
				((font_bitmap_origin[10] & 0x20) >> 0) |
				((font_bitmap_origin[12] & 0x20) << 1) |
				((font_bitmap_origin[14] & 0x20) << 2);
		font_bitmap_show[3] = ((font_bitmap_origin[0] & 0x10) >> 4) |
				((font_bitmap_origin[2] & 0x10) >> 3) |
				((font_bitmap_origin[4] & 0x10) >> 2) |
				((font_bitmap_origin[6] & 0x10) >> 1) |
				((font_bitmap_origin[8] & 0x10) >> 0) |
				((font_bitmap_origin[10] & 0x10) << 1) |
				((font_bitmap_origin[12] & 0x10) << 2) |
				((font_bitmap_origin[14] & 0x10) << 3);
		font_bitmap_show[4] = ((font_bitmap_origin[0] & 0x08) >> 3) |
				((font_bitmap_origin[2] & 0x08) >> 2) |
				((font_bitmap_origin[4] & 0x08) >> 1) |
				((font_bitmap_origin[6] & 0x08) >> 0) |
				((font_bitmap_origin[8] & 0x08) << 1) |
				((font_bitmap_origin[10] & 0x08) << 2) |
				((font_bitmap_origin[12] & 0x08) << 3) |
				((font_bitmap_origin[14] & 0x08) << 4);
		font_bitmap_show[5] = ((font_bitmap_origin[0] & 0x04) >> 2) |
				((font_bitmap_origin[2] & 0x04) >> 1) |
				((font_bitmap_origin[4] & 0x04) >> 0) |
				((font_bitmap_origin[6] & 0x04) << 1) |
				((font_bitmap_origin[8] & 0x04) << 2) |
				((font_bitmap_origin[10] & 0x04) << 3) |
				((font_bitmap_origin[12] & 0x04) << 4) |
				((font_bitmap_origin[14] & 0x04) << 5);
		font_bitmap_show[6] = ((font_bitmap_origin[0] & 0x02) >> 1) |
				((font_bitmap_origin[2] & 0x02) >> 0) |
				((font_bitmap_origin[4] & 0x02) << 1) |
				((font_bitmap_origin[6] & 0x02) << 2) |
				((font_bitmap_origin[8] & 0x02) << 3) |
				((font_bitmap_origin[10] & 0x02) << 4) |
				((font_bitmap_origin[12] & 0x02) << 5) |
				((font_bitmap_origin[14] & 0x02) << 6);
		font_bitmap_show[7] = ((font_bitmap_origin[0] & 0x01) >> 0) |
				((font_bitmap_origin[2] & 0x01) << 1) |
				((font_bitmap_origin[4] & 0x01) << 2) |
				((font_bitmap_origin[6] & 0x01) << 3) |
				((font_bitmap_origin[8] & 0x01) << 4) |
				((font_bitmap_origin[10] & 0x01) << 5) |
				((font_bitmap_origin[12] & 0x01) << 6) |
				((font_bitmap_origin[14] & 0x01) << 7);
		font_bitmap_show[8] = ((font_bitmap_origin[1] & 0x80) >> 7) |
				((font_bitmap_origin[3] & 0x80) >> 6) |
				((font_bitmap_origin[5] & 0x80) >> 5) |
				((font_bitmap_origin[7] & 0x80) >> 4) |
				((font_bitmap_origin[9] & 0x80) >> 3) |
				((font_bitmap_origin[11] & 0x80) >> 2) |
				((font_bitmap_origin[13] & 0x80) >> 1) |
				((font_bitmap_origin[15] & 0x80) >> 0);
		font_bitmap_show[9] = ((font_bitmap_origin[1] & 0x40) >> 6) |
				((font_bitmap_origin[3] & 0x40) >> 5) |
				((font_bitmap_origin[5] & 0x40) >> 4) |
				((font_bitmap_origin[7] & 0x40) >> 3) |
				((font_bitmap_origin[9] & 0x40) >> 2) |
				((font_bitmap_origin[11] & 0x40) >> 1) |
				((font_bitmap_origin[13] & 0x40) >> 1) |
				((font_bitmap_origin[15] & 0x40) << 1);
		font_bitmap_show[10] = ((font_bitmap_origin[1] & 0x20) >> 5) |
				((font_bitmap_origin[3] & 0x20) >> 4) |
				((font_bitmap_origin[5] & 0x20) >> 3) |
				((font_bitmap_origin[7] & 0x20) >> 2) |
				((font_bitmap_origin[9] & 0x20) >> 1) |
				((font_bitmap_origin[11] & 0x20) >> 0) |
				((font_bitmap_origin[13] & 0x20) << 1) |
				((font_bitmap_origin[15] & 0x20) << 2);
		font_bitmap_show[11] = ((font_bitmap_origin[1] & 0x10) >> 4) |
				((font_bitmap_origin[3] & 0x10) >> 3) |
				((font_bitmap_origin[5] & 0x10) >> 2) |
				((font_bitmap_origin[7] & 0x10) >> 1) |
				((font_bitmap_origin[9] & 0x10) >> 0) |
				((font_bitmap_origin[11] & 0x10) << 1) |
				((font_bitmap_origin[13] & 0x10) << 2) |
				((font_bitmap_origin[15] & 0x10) << 3);
		font_bitmap_show[12] = ((font_bitmap_origin[1] & 0x08) >> 3) |
				((font_bitmap_origin[3] & 0x08) >> 2) |
				((font_bitmap_origin[5] & 0x08) >> 1) |
				((font_bitmap_origin[7] & 0x08) >> 0) |
				((font_bitmap_origin[9] & 0x08) << 1) |
				((font_bitmap_origin[11] & 0x08) << 2) |
				((font_bitmap_origin[13] & 0x08) << 3) |
				((font_bitmap_origin[15] & 0x08) << 4);
		font_bitmap_show[13] = ((font_bitmap_origin[1] & 0x04) >> 2) |
				((font_bitmap_origin[3] & 0x04) >> 1) |
				((font_bitmap_origin[5] & 0x04) >> 0) |
				((font_bitmap_origin[7] & 0x04) << 1) |
				((font_bitmap_origin[9] & 0x04) << 2) |
				((font_bitmap_origin[11] & 0x04) << 3) |
				((font_bitmap_origin[13] & 0x04) << 4) |
				((font_bitmap_origin[15] & 0x04) << 5);
		font_bitmap_show[14] = ((font_bitmap_origin[1] & 0x02) >> 1) |
				((font_bitmap_origin[3] & 0x02) >> 0) |
				((font_bitmap_origin[5] & 0x02) << 1) |
				((font_bitmap_origin[7] & 0x02) << 2) |
				((font_bitmap_origin[9] & 0x02) << 3) |
				((font_bitmap_origin[11] & 0x02) << 4) |
				((font_bitmap_origin[13] & 0x02) << 5) |
				((font_bitmap_origin[15] & 0x02) << 6);
		font_bitmap_show[15] = ((font_bitmap_origin[1] & 0x01) >> 0) |
				((font_bitmap_origin[3] & 0x01) << 1) |
				((font_bitmap_origin[5] & 0x01) << 2) |
				((font_bitmap_origin[7] & 0x01) << 3) |
				((font_bitmap_origin[9] & 0x01) << 4) |
				((font_bitmap_origin[11] & 0x01) << 5) |
				((font_bitmap_origin[13] & 0x01) << 6) |
				((font_bitmap_origin[15] & 0x01) << 7);
		font_bitmap_show[16] = ((font_bitmap_origin[16] & 0x80) >> 7) |
				((font_bitmap_origin[18] & 0x80) >> 6) |
				((font_bitmap_origin[20] & 0x80) >> 5) |
				((font_bitmap_origin[22] & 0x80) >> 4) |
				((font_bitmap_origin[24] & 0x80) >> 3) |
				((font_bitmap_origin[26] & 0x80) >> 2) |
				((font_bitmap_origin[28] & 0x80) >> 1) |
				((font_bitmap_origin[30] & 0x80) >> 0);
		font_bitmap_show[17] = ((font_bitmap_origin[16] & 0x40) >> 6) |
				((font_bitmap_origin[18] & 0x40) >> 5) |
				((font_bitmap_origin[20] & 0x40) >> 4) |
				((font_bitmap_origin[22] & 0x40) >> 3) |
				((font_bitmap_origin[24] & 0x40) >> 2) |
				((font_bitmap_origin[26] & 0x40) >> 1) |
				((font_bitmap_origin[28] & 0x40) >> 0) |
				((font_bitmap_origin[30] & 0x40) << 1);
		font_bitmap_show[18] = ((font_bitmap_origin[16] & 0x20) >> 5) |
				((font_bitmap_origin[18] & 0x20) >> 4) |
				((font_bitmap_origin[20] & 0x20) >> 3) |
				((font_bitmap_origin[22] & 0x20) >> 2) |
				((font_bitmap_origin[24] & 0x20) >> 1) |
				((font_bitmap_origin[26] & 0x20) >> 0) |
				((font_bitmap_origin[28] & 0x20) << 1) |
				((font_bitmap_origin[30] & 0x20) << 2);
		font_bitmap_show[19] = ((font_bitmap_origin[16] & 0x10) >> 4) |
				((font_bitmap_origin[18] & 0x10) >> 3) |
				((font_bitmap_origin[20] & 0x10) >> 2) |
				((font_bitmap_origin[22] & 0x10) >> 1) |
				((font_bitmap_origin[24] & 0x10) >> 0) |
				((font_bitmap_origin[26] & 0x10) << 1) |
				((font_bitmap_origin[28] & 0x10) << 2) |
				((font_bitmap_origin[30] & 0x10) << 3);
		font_bitmap_show[20] = ((font_bitmap_origin[16] & 0x08) >> 3) |
				((font_bitmap_origin[18] & 0x08) >> 2) |
				((font_bitmap_origin[20] & 0x08) >> 1) |
				((font_bitmap_origin[22] & 0x08) >> 0) |
				((font_bitmap_origin[24] & 0x08) << 1) |
				((font_bitmap_origin[26] & 0x08) << 2) |
				((font_bitmap_origin[28] & 0x08) << 3) |
				((font_bitmap_origin[30] & 0x08) << 4);
		font_bitmap_show[21] = ((font_bitmap_origin[16] & 0x04) >> 2) |
				((font_bitmap_origin[18] & 0x04) >> 1) |
				((font_bitmap_origin[20] & 0x04) >> 0) |
				((font_bitmap_origin[22] & 0x04) << 1) |
				((font_bitmap_origin[24] & 0x04) << 2) |
				((font_bitmap_origin[26] & 0x04) << 3) |
				((font_bitmap_origin[28] & 0x04) << 4) |
				((font_bitmap_origin[30] & 0x04) << 5);
		font_bitmap_show[22] = ((font_bitmap_origin[16] & 0x02) >> 1) |
				((font_bitmap_origin[18] & 0x02) >> 0) |
				((font_bitmap_origin[20] & 0x02) << 1) |
				((font_bitmap_origin[22] & 0x02) << 2) |
				((font_bitmap_origin[24] & 0x02) << 3) |
				((font_bitmap_origin[26] & 0x02) << 4) |
				((font_bitmap_origin[28] & 0x02) << 5) |
				((font_bitmap_origin[30] & 0x02) << 6);
		font_bitmap_show[23] = ((font_bitmap_origin[16] & 0x01) >> 0) |
				((font_bitmap_origin[18] & 0x01) << 1) |
				((font_bitmap_origin[20] & 0x01) << 2) |
				((font_bitmap_origin[22] & 0x01) << 3) |
				((font_bitmap_origin[24] & 0x01) << 4) |
				((font_bitmap_origin[26] & 0x01) << 5) |
				((font_bitmap_origin[28] & 0x01) << 6) |
				((font_bitmap_origin[30] & 0x01) << 7);
		font_bitmap_show[24] = ((font_bitmap_origin[17] & 0x80) >> 7) |
				((font_bitmap_origin[19] & 0x80) >> 6) |
				((font_bitmap_origin[21] & 0x80) >> 5) |
				((font_bitmap_origin[23] & 0x80) >> 4) |
				((font_bitmap_origin[25] & 0x80) >> 3) |
				((font_bitmap_origin[27] & 0x80) >> 2) |
				((font_bitmap_origin[29] & 0x80) >> 1) |
				((font_bitmap_origin[31] & 0x80) >> 0);
		font_bitmap_show[25] = ((font_bitmap_origin[17] & 0x40) >> 6) |
				((font_bitmap_origin[19] & 0x40) >> 5) |
				((font_bitmap_origin[21] & 0x40) >> 4) |
				((font_bitmap_origin[23] & 0x40) >> 3) |
				((font_bitmap_origin[25] & 0x40) >> 2) |
				((font_bitmap_origin[27] & 0x40) >> 1) |
				((font_bitmap_origin[29] & 0x40) >> 0) |
				((font_bitmap_origin[31] & 0x40) << 1);
		font_bitmap_show[26] = ((font_bitmap_origin[17] & 0x20) >> 5) |
				((font_bitmap_origin[19] & 0x20) >> 4) |
				((font_bitmap_origin[21] & 0x20) >> 3) |
				((font_bitmap_origin[23] & 0x20) >> 2) |
				((font_bitmap_origin[25] & 0x20) >> 1) |
				((font_bitmap_origin[27] & 0x20) >> 0) |
				((font_bitmap_origin[29] & 0x20) << 1) |
				((font_bitmap_origin[31] & 0x20) << 2);
		font_bitmap_show[27] = ((font_bitmap_origin[17] & 0x10) >> 4) |
				((font_bitmap_origin[19] & 0x10) >> 3) |
				((font_bitmap_origin[21] & 0x10) >> 2) |
				((font_bitmap_origin[23] & 0x10) >> 1) |
				((font_bitmap_origin[25] & 0x10) >> 0) |
				((font_bitmap_origin[27] & 0x10) << 1) |
				((font_bitmap_origin[29] & 0x10) << 2) |
				((font_bitmap_origin[31] & 0x10) << 3);
		font_bitmap_show[28] = ((font_bitmap_origin[17] & 0x08) >> 3) |
				((font_bitmap_origin[19] & 0x08) >> 2) |
				((font_bitmap_origin[21] & 0x08) >> 1) |
				((font_bitmap_origin[23] & 0x08) >> 0) |
				((font_bitmap_origin[25] & 0x08) << 1) |
				((font_bitmap_origin[27] & 0x08) << 2) |
				((font_bitmap_origin[29] & 0x08) << 3) |
				((font_bitmap_origin[31] & 0x08) << 4);
		font_bitmap_show[29] = ((font_bitmap_origin[17] & 0x04) >> 2) |
				((font_bitmap_origin[19] & 0x04) >> 1) |
				((font_bitmap_origin[21] & 0x04) >> 0) |
				((font_bitmap_origin[23] & 0x04) << 1) |
				((font_bitmap_origin[25] & 0x04) << 2) |
				((font_bitmap_origin[27] & 0x04) << 3) |
				((font_bitmap_origin[29] & 0x04) << 4) |
				((font_bitmap_origin[31] & 0x04) << 5);
		font_bitmap_show[30] = ((font_bitmap_origin[17] & 0x02) >> 1) |
				((font_bitmap_origin[19] & 0x02) >> 0) |
				((font_bitmap_origin[21] & 0x02) << 1) |
				((font_bitmap_origin[23] & 0x02) << 2) |
				((font_bitmap_origin[25] & 0x02) << 3) |
				((font_bitmap_origin[27] & 0x02) << 4) |
				((font_bitmap_origin[29] & 0x02) << 5) |
				((font_bitmap_origin[31] & 0x02) << 6);
		font_bitmap_show[31] = ((font_bitmap_origin[17] & 0x01) >> 0) |
				((font_bitmap_origin[19] & 0x01) << 1) |
				((font_bitmap_origin[21] & 0x01) << 2) |
				((font_bitmap_origin[23] & 0x01) << 3) |
				((font_bitmap_origin[25] & 0x01) << 4) |
				((font_bitmap_origin[27] & 0x01) << 5) |
				((font_bitmap_origin[29] & 0x01) << 6) |
				((font_bitmap_origin[31] & 0x01) << 7);
	} else {
		font_bitmap_show[0] = ((font_bitmap_origin[0] & 0x80) >> 7) |
				((font_bitmap_origin[1] & 0x80) >> 6) |
				((font_bitmap_origin[2] & 0x80) >> 5) |
				((font_bitmap_origin[3] & 0x80) >> 4) |
				((font_bitmap_origin[4] & 0x80) >> 3) |
				((font_bitmap_origin[5] & 0x80) >> 2) |
				((font_bitmap_origin[6] & 0x80) >> 1) |
				((font_bitmap_origin[7] & 0x80) >> 0);
		font_bitmap_show[1] = ((font_bitmap_origin[0] & 0x40) >> 6) |
				((font_bitmap_origin[1] & 0x40) >> 5) |
				((font_bitmap_origin[2] & 0x40) >> 4) |
				((font_bitmap_origin[3] & 0x40) >> 3) |
				((font_bitmap_origin[4] & 0x40) >> 2) |
				((font_bitmap_origin[5] & 0x40) >> 1) |
				((font_bitmap_origin[6] & 0x40) >> 0) |
				((font_bitmap_origin[7] & 0x40) << 1);
		font_bitmap_show[2] = ((font_bitmap_origin[0] & 0x20) >> 5) |
				((font_bitmap_origin[1] & 0x20) >> 4) |
				((font_bitmap_origin[2] & 0x20) >> 3) |
				((font_bitmap_origin[3] & 0x20) >> 2) |
				((font_bitmap_origin[4] & 0x20) >> 1) |
				((font_bitmap_origin[5] & 0x20) >> 0) |
				((font_bitmap_origin[6] & 0x20) << 1) |
				((font_bitmap_origin[7] & 0x20) << 2);
		font_bitmap_show[3] = ((font_bitmap_origin[0] & 0x10) >> 4) |
				((font_bitmap_origin[1] & 0x10) >> 3) |
				((font_bitmap_origin[2] & 0x10) >> 2) |
				((font_bitmap_origin[3] & 0x10) >> 1) |
				((font_bitmap_origin[4] & 0x10) >> 0) |
				((font_bitmap_origin[5] & 0x10) << 1) |
				((font_bitmap_origin[6] & 0x10) << 2) |
				((font_bitmap_origin[7] & 0x10) << 3);
		font_bitmap_show[4] = ((font_bitmap_origin[0] & 0x08) >> 3) |
				((font_bitmap_origin[1] & 0x08) >> 2) |
				((font_bitmap_origin[2] & 0x08) >> 1) |
				((font_bitmap_origin[3] & 0x08) >> 0) |
				((font_bitmap_origin[4] & 0x08) << 1) |
				((font_bitmap_origin[5] & 0x08) << 2) |
				((font_bitmap_origin[6] & 0x08) << 3) |
				((font_bitmap_origin[7] & 0x08) << 4);
		font_bitmap_show[5] = ((font_bitmap_origin[0] & 0x04) >> 2) |
				((font_bitmap_origin[1] & 0x04) >> 1) |
				((font_bitmap_origin[2] & 0x04) >> 0) |
				((font_bitmap_origin[3] & 0x04) << 1) |
				((font_bitmap_origin[4] & 0x04) << 2) |
				((font_bitmap_origin[5] & 0x04) << 3) |
				((font_bitmap_origin[6] & 0x04) << 4) |
				((font_bitmap_origin[7] & 0x04) << 5);
		font_bitmap_show[6] = ((font_bitmap_origin[0] & 0x02) >> 1) |
				((font_bitmap_origin[1] & 0x02) >> 0) |
				((font_bitmap_origin[2] & 0x02) << 1) |
				((font_bitmap_origin[3] & 0x02) << 2) |
				((font_bitmap_origin[4] & 0x02) << 3) |
				((font_bitmap_origin[5] & 0x02) << 4) |
				((font_bitmap_origin[6] & 0x02) << 5) |
				((font_bitmap_origin[7] & 0x02) << 6);
		font_bitmap_show[7] = ((font_bitmap_origin[0] & 0x01) >> 0) |
				((font_bitmap_origin[1] & 0x01) << 1) |
				((font_bitmap_origin[2] & 0x01) << 2) |
				((font_bitmap_origin[3] & 0x01) << 3) |
				((font_bitmap_origin[4] & 0x01) << 4) |
				((font_bitmap_origin[5] & 0x01) << 5) |
				((font_bitmap_origin[6] & 0x01) << 6) |
				((font_bitmap_origin[7] & 0x01) << 7);

		font_bitmap_show[16] = ((font_bitmap_origin[8] & 0x80) >> 7) |
				((font_bitmap_origin[9] & 0x80) >> 6) |
				((font_bitmap_origin[10] & 0x80) >> 5) |
				((font_bitmap_origin[11] & 0x80) >> 4) |
				((font_bitmap_origin[12] & 0x80) >> 3) |
				((font_bitmap_origin[13] & 0x80) >> 2) |
				((font_bitmap_origin[14] & 0x80) >> 1) |
				((font_bitmap_origin[15] & 0x80) >> 0);
		font_bitmap_show[17] = ((font_bitmap_origin[8] & 0x40) >> 6) |
				((font_bitmap_origin[9] & 0x40) >> 5) |
				((font_bitmap_origin[10] & 0x40) >> 4) |
				((font_bitmap_origin[11] & 0x40) >> 3) |
				((font_bitmap_origin[12] & 0x40) >> 2) |
				((font_bitmap_origin[13] & 0x40) >> 1) |
				((font_bitmap_origin[14] & 0x40) >> 0) |
				((font_bitmap_origin[15] & 0x40) << 1);
		font_bitmap_show[18] = ((font_bitmap_origin[8] & 0x20) >> 5) |
				((font_bitmap_origin[9] & 0x20) >> 4) |
				((font_bitmap_origin[10] & 0x20) >> 3) |
				((font_bitmap_origin[11] & 0x20) >> 2) |
				((font_bitmap_origin[12] & 0x20) >> 1) |
				((font_bitmap_origin[13] & 0x20) >> 0) |
				((font_bitmap_origin[14] & 0x20) << 1) |
				((font_bitmap_origin[15] & 0x20) << 2);
		font_bitmap_show[19] = ((font_bitmap_origin[8] & 0x10) >> 4) |
				((font_bitmap_origin[9] & 0x10) >> 3) |
				((font_bitmap_origin[10] & 0x10) >> 2) |
				((font_bitmap_origin[11] & 0x10) >> 1) |
				((font_bitmap_origin[12] & 0x10) >> 0) |
				((font_bitmap_origin[13] & 0x10) << 1) |
				((font_bitmap_origin[14] & 0x10) << 2) |
				((font_bitmap_origin[15] & 0x10) << 3);
		font_bitmap_show[20] = ((font_bitmap_origin[8] & 0x08) >> 3) |
				((font_bitmap_origin[9] & 0x08) >> 2) |
				((font_bitmap_origin[10] & 0x08) >> 1) |
				((font_bitmap_origin[11] & 0x08) >> 0) |
				((font_bitmap_origin[12] & 0x08) << 1) |
				((font_bitmap_origin[13] & 0x08) << 2) |
				((font_bitmap_origin[14] & 0x08) << 3) |
				((font_bitmap_origin[15] & 0x08) << 4);
		font_bitmap_show[21] = ((font_bitmap_origin[8] & 0x04) >> 2) |
				((font_bitmap_origin[9] & 0x04) >> 1) |
				((font_bitmap_origin[10] & 0x04) >> 0) |
				((font_bitmap_origin[11] & 0x04) << 1) |
				((font_bitmap_origin[12] & 0x04) << 2) |
				((font_bitmap_origin[13] & 0x04) << 3) |
				((font_bitmap_origin[14] & 0x04) << 4) |
				((font_bitmap_origin[15] & 0x04) << 5);
		font_bitmap_show[22] = ((font_bitmap_origin[8] & 0x02) >> 1) |
				((font_bitmap_origin[9] & 0x02) >> 0) |
				((font_bitmap_origin[10] & 0x02) << 1) |
				((font_bitmap_origin[11] & 0x02) << 2) |
				((font_bitmap_origin[12] & 0x02) << 3) |
				((font_bitmap_origin[13] & 0x02) << 4) |
				((font_bitmap_origin[14] & 0x02) << 5) |
				((font_bitmap_origin[15] & 0x02) << 6);
		font_bitmap_show[23] = ((font_bitmap_origin[8] & 0x01) >> 0) |
				((font_bitmap_origin[9] & 0x01) << 1) |
				((font_bitmap_origin[10] & 0x01) << 2) |
				((font_bitmap_origin[11] & 0x01) << 3) |
				((font_bitmap_origin[12] & 0x01) << 4) |
				((font_bitmap_origin[13] & 0x01) << 5) |
				((font_bitmap_origin[14] & 0x01) << 6) |
				((font_bitmap_origin[15] & 0x01) << 7);
	}
}

/**
 * \brief Find the font bitmap data by given the unicode.
 */
static void font_bitmap_find(uint16_t unicode)
{
	uint32_t i;

	volatile uint32_t first_char_info_offset;
	volatile uint32_t unicode_char_info_offset;
	volatile uint32_t unicode_char_info;
	volatile uint32_t font_bitmap_offset;

	first_char_info_offset = unicode_font_table[0x14] |
			(unicode_font_table[0x15] << 8) |
			(unicode_font_table[0x16] << 16) |
			(unicode_font_table[0x17] << 24);

	unicode_char_info_offset = first_char_info_offset +
			(unicode - unicode_font_table[0x10]) * 4;
	unicode_char_info = unicode_font_table[unicode_char_info_offset] |
			(unicode_font_table[unicode_char_info_offset + 1] << 8) |
			(unicode_font_table[unicode_char_info_offset + 2] << 16) |
			(unicode_font_table[unicode_char_info_offset + 3] << 24);
	font_bitmap_offset = unicode_char_info & 0xffffff;
	font_bitmap_width = unicode_font_table[unicode_char_info_offset + 3];
	if (font_bitmap_width > 0x20) {
		font_bitmap_width = 2;
	} else {
		font_bitmap_width = 1;
	}

	for (i = 0; i < 32; i++) {
		font_bitmap_origin[i] = unicode_font_table[font_bitmap_offset];
		font_bitmap_offset++;
	}
}

/**
 * \brief Display the font bitmap data in the given position.
 *
 * \param page page address of the OLED.
 * \param column column address of the OLED.
 */
static void font_bitmap_display(uint8_t page, uint8_t column)
{
	uint32_t i;

	ssd1306_set_page_address(page);
	ssd1306_set_column_address(column);
	for (i = 0; i < (8 * font_bitmap_width); i++) {
		ssd1306_write_data(font_bitmap_show[i]);
	}
	ssd1306_set_page_address(page + 1);
	ssd1306_set_column_address(column);
	for (i = 0; i < (8 * font_bitmap_width); i++) {
		ssd1306_write_data(font_bitmap_show[i + 16]);
	}
}

/**
 * \brief Display SD card file name on OLED screen.
 *
 * \param page page address of the OLED, 0 or 2 for 16*16 font unicode.
 * \param column column address of the OLED.
 * \param string String to display(unicode format).
 *
 * \return column address reached
 */
static uint8_t unicode_show_one_line(uint8_t page, uint8_t column,
		const uint16_t *p_unicode_string)
{
	uint16_t unicode_16;
	uint8_t column_address;

	column_address = column;

	unicode_16 = *p_unicode_string;
	p_unicode_string++;
	while ((unicode_16 != 0) && (column_address < 128)) {
		if (unicode_16 == 0xFFFF) {
			/* unicode 0xFFFF redefined as a space. */
			column_address += 4;
		} else {
			font_bitmap_find(unicode_16);
			font_bitmap_transfer();
			if ((column_address + 8 * font_bitmap_width) <= 128) {
				font_bitmap_display(page, column_address);
			}
			column_address += (8 * font_bitmap_width);
			/* For better display, some 16*16 font only */
			if ((unicode_16 == 0x0050) || (unicode_16 == 0x0061) ||
					(unicode_16 == 0x0062) || (unicode_16 == 0x0064) ||
					(unicode_16 == 0x0065) || (unicode_16 == 0x0067) ||
					(unicode_16 == 0x006E) || (unicode_16 == 0x006F) ||
					(unicode_16 == 0x0070) || (unicode_16 == 0x0075)) {
				column_address -= 4;
			}
		}
		unicode_16 = *p_unicode_string;
		p_unicode_string++;
	}

	return column_address;
}
#endif

/**
 * \brief Show the switch info on the OLED screen.
 */
void multi_language_show_switch_info(void)
{
	/* Clear screen. */
	ssd1306_clear();

	/* Start message on the screen. */
#ifdef CONF_ENGLISH_LANGUAGE
	ssd1306_set_page_address(0);
	ssd1306_set_column_address(0);
	ssd1306_write_text("Other language demo is");
	ssd1306_set_page_address(1);
	ssd1306_set_column_address(0);
	ssd1306_write_text("found on SD card.");
	ssd1306_set_page_address(2);
	ssd1306_set_column_address(0);
	ssd1306_write_text("Push SW0 to switch.");
#endif
#ifdef CONF_CHINESE_LANGUAGE
	unicode_show_one_line(0, 0, switch_info_1_cn);
	unicode_show_one_line(2, 0, switch_info_2_cn);
	ssd1306_set_page_address(3);
	ssd1306_set_column_address(17);
	ssd1306_write_text("SW0");
	unicode_show_one_line(2, 34, switch_info_3_cn);
#endif
#ifdef CONF_JAPANESE_LANGUAGE
	unicode_show_one_line(0, 0, switch_info_1_jp);
	ssd1306_set_page_address(1);
	ssd1306_set_column_address(33);
	ssd1306_write_text("SW0");
	unicode_show_one_line(0, 50, switch_info_2_jp);
#endif
#ifdef CONF_FRENCH_LANGUAGE
	uint8_t colume_index;
	unicode_show_one_line(0, 0, switch_info_1_fr);
	colume_index = unicode_show_one_line(2, 0, switch_info_2_fr);

	ssd1306_set_page_address(3);
	ssd1306_set_column_address(colume_index);
	ssd1306_write_text("SW0");
#endif
#ifdef CONF_SPANISH_LANGUAGE
	uint8_t colume_index;
	colume_index = unicode_show_one_line(0, 0, switch_info_1_sp);
	colume_index += 1;
	ssd1306_set_page_address(1);
	ssd1306_set_column_address(colume_index);
	ssd1306_write_text("SW0");

	unicode_show_one_line(2, 0, switch_info_2_sp);
#endif
}

/**
 * \brief Show the start info on the OLED screen.
 */
void multi_language_show_start_info(void)
{
	/* Clear screen. */
	ssd1306_clear();

	/* Start message on the screen. */
#ifdef CONF_ENGLISH_LANGUAGE
	ssd1306_set_page_address(1);
	ssd1306_set_column_address(0);
	ssd1306_write_text("Starter Kit Bootloader Demo");
#endif
#ifdef CONF_CHINESE_LANGUAGE
	unicode_show_one_line(0, 0, start_info_1_cn);
#endif
#ifdef CONF_JAPANESE_LANGUAGE
	unicode_show_one_line(0, 0, start_info_1_jp);
#endif
#ifdef CONF_FRENCH_LANGUAGE
	unicode_show_one_line(0, 0, start_info_1_fr);
	unicode_show_one_line(2, 0, start_info_2_fr);
#endif
#ifdef CONF_SPANISH_LANGUAGE
	unicode_show_one_line(0, 0, start_info_1_sp);
	unicode_show_one_line(2, 0, start_info_2_sp);
#endif
}

/**
 * \brief Show the temperature info on the OLED screen.
 */
void multi_language_show_temperature_info(void)
{
#ifdef CONF_ENGLISH_LANGUAGE
	ssd1306_write_text("Temperature sensor:");
#endif
#ifdef CONF_CHINESE_LANGUAGE
	unicode_show_one_line(0, 0, temperature_info_1_cn);
#endif
#ifdef CONF_JAPANESE_LANGUAGE
	unicode_show_one_line(0, 0, temperature_info_1_jp);
#endif
#ifdef CONF_FRENCH_LANGUAGE
	unicode_show_one_line(0, 0, temperature_info_1_fr);
#endif
#ifdef CONF_SPANISH_LANGUAGE
	unicode_show_one_line(0, 0, temperature_info_1_sp);
#endif
}

/**
 * \brief Show the light info on the OLED screen.
 */
void multi_language_show_light_info(void)
{
#ifdef CONF_ENGLISH_LANGUAGE
	ssd1306_write_text("Light sensor:");
#endif
#ifdef CONF_CHINESE_LANGUAGE
	unicode_show_one_line(0, 0, light_info_1_cn);
#endif
#ifdef CONF_JAPANESE_LANGUAGE
	unicode_show_one_line(0, 0, light_info_1_jp);
#endif
#ifdef CONF_FRENCH_LANGUAGE
	unicode_show_one_line(0, 0, light_info_1_fr);
#endif
#ifdef CONF_SPANISH_LANGUAGE
	unicode_show_one_line(0, 0, light_info_1_sp);
#endif
}

/**
 * \brief Show the end info on the OLED screen.
 */
void multi_language_show_end_info(void)
{
	/* Clear screen. */
	ssd1306_clear();

	/* End message on the screen. */
#ifdef CONF_ENGLISH_LANGUAGE
	ssd1306_set_page_address(1);
	ssd1306_set_column_address(0);
	ssd1306_write_text("Wait bootloader complete...");
#endif
#ifdef CONF_CHINESE_LANGUAGE
	unicode_show_one_line(0, 0, end_info_1_cn);
#endif
#ifdef CONF_JAPANESE_LANGUAGE
	unicode_show_one_line(0, 0, end_info_1_jp);
	unicode_show_one_line(2, 0, end_info_2_jp);
#endif
#ifdef CONF_FRENCH_LANGUAGE
	unicode_show_one_line(0, 0, end_info_1_fr);
	unicode_show_one_line(2, 0, end_info_2_fr);
#endif
#ifdef CONF_SPANISH_LANGUAGE
	unicode_show_one_line(0, 0, end_info_1_sp);
	unicode_show_one_line(2, 0, end_info_2_sp);
#endif
}

/**
 * \brief Show the no SD card info on the OLED screen.
 */
void multi_language_show_no_sd_info(void)
{
#ifdef CONF_ENGLISH_LANGUAGE
	ssd1306_write_text("Please insert SD card...");
#endif
#ifdef CONF_CHINESE_LANGUAGE
	unicode_show_one_line(0, 0, no_sd_info_1_cn);
#endif
#ifdef CONF_JAPANESE_LANGUAGE
	unicode_show_one_line(0, 0, no_sd_info_1_jp);
#endif
#ifdef CONF_FRENCH_LANGUAGE
	unicode_show_one_line(0, 0, no_sd_info_1_fr);
	unicode_show_one_line(2, 0, no_sd_info_2_fr);
#endif
#ifdef CONF_SPANISH_LANGUAGE
	unicode_show_one_line(0, 0, no_sd_info_1_sp);
	unicode_show_one_line(2, 0, no_sd_info_2_sp);
#endif
}

/**
 * \brief Show the SD card info on the OLED screen.
 */
void multi_language_show_sd_info(void)
{
#ifdef CONF_ENGLISH_LANGUAGE
	ssd1306_write_text("SD card information:");
	ssd1306_set_page_address(1);
	ssd1306_set_column_address(0);
#endif
#ifdef CONF_CHINESE_LANGUAGE
	unicode_show_one_line(0, 0, sd_info_1_cn);
	ssd1306_set_page_address(1);
	ssd1306_set_column_address(48);
	ssd1306_write_text(":");
#endif
#ifdef CONF_JAPANESE_LANGUAGE
	unicode_show_one_line(0, 0, sd_info_1_jp);
	ssd1306_set_page_address(1);
	ssd1306_set_column_address(80);
	ssd1306_write_text(":");
#endif
#ifdef CONF_FRENCH_LANGUAGE
	uint8_t colume_index;
	colume_index = unicode_show_one_line(0, 0, sd_info_1_fr);
	ssd1306_set_page_address(1);
	ssd1306_set_column_address(colume_index);
	ssd1306_write_text(":");
#endif
#ifdef CONF_SPANISH_LANGUAGE
	uint8_t colume_index;
	colume_index = unicode_show_one_line(0, 0, sd_info_1_sp);
	ssd1306_set_page_address(1);
	ssd1306_set_column_address(colume_index);
	ssd1306_write_text(":");
#endif
}

/**
 * \brief Show normal SD card info on the OLED screen.
 */
void multi_language_show_normal_card_info(void)
{
#ifdef CONF_ENGLISH_LANGUAGE
	ssd1306_write_text("- Type: Normal SD card");
#endif
#ifdef CONF_CHINESE_LANGUAGE
	unicode_show_one_line(0, 56, normal_card_info_1_cn);
#endif
#ifdef CONF_JAPANESE_LANGUAGE
	unicode_show_one_line(0, 88, normal_card_info_1_jp);
#endif
#ifdef CONF_FRENCH_LANGUAGE
	unicode_show_one_line(2, 0, normal_card_info_1_fr);
#endif
#ifdef CONF_SPANISH_LANGUAGE
	unicode_show_one_line(2, 0, normal_card_info_1_sp);
#endif
}

/**
 * \brief Show high capacity SD card info on the OLED screen.
 */
void multi_language_show_high_capacity_card_info(void)
{
#ifdef CONF_ENGLISH_LANGUAGE
	ssd1306_write_text("- Type: High Capacity card");
#endif
#ifdef CONF_CHINESE_LANGUAGE
	unicode_show_one_line(0, 56, high_capacity_card_info_1_cn);
#endif
#ifdef CONF_JAPANESE_LANGUAGE
	unicode_show_one_line(0, 88, high_capacity_card_info_1_jp);
#endif
#ifdef CONF_FRENCH_LANGUAGE
	unicode_show_one_line(2, 0, high_capacity_card_info_1_fr);
#endif
#ifdef CONF_SPANISH_LANGUAGE
	unicode_show_one_line(2, 0, high_capacity_card_info_1_sp);
#endif
}

/**
 * \brief Show unknow card info on the OLED screen.
 */
void multi_language_show_unknow_card_info(void)
{
#ifdef CONF_ENGLISH_LANGUAGE
	ssd1306_write_text("- Type: unknown");
#endif
#ifdef CONF_CHINESE_LANGUAGE
	unicode_show_one_line(0, 56, unknow_card_info_1_cn);
#endif
#ifdef CONF_JAPANESE_LANGUAGE
	unicode_show_one_line(0, 88, unknow_card_info_1_jp);
#endif
#ifdef CONF_FRENCH_LANGUAGE
	unicode_show_one_line(2, 0, unknow_card_info_1_fr);
#endif
#ifdef CONF_SPANISH_LANGUAGE
	unicode_show_one_line(2, 0, unknow_card_info_1_sp);
#endif
}

/**
 * \brief Show the SD card size info on the OLED screen.
 */
void multi_language_show_card_size_info(char *p_string,
		uint32_t sd_card_size)
{
#ifdef CONF_ENGLISH_LANGUAGE
	ssd1306_set_page_address(2);
	ssd1306_set_column_address(0);

	sprintf(p_string, "- Total size: %lu KB", sd_card_size);
	ssd1306_write_text(p_string);

	ssd1306_set_page_address(3);
	ssd1306_set_column_address(0);
#endif
#ifdef CONF_CHINESE_LANGUAGE
	unicode_show_one_line(2, 0, card_size_info_1_cn);

	ssd1306_set_page_address(3);
	ssd1306_set_column_address(48);
	sprintf(p_string, ": %lu KB", sd_card_size);
	ssd1306_write_text(p_string);

	/* Wait 3 seconds to show the above message. */
	delay_s(3);

	/* Clear screen. */
	ssd1306_clear();

	/* scroll one line to show file info */
	unicode_show_one_line(0, 0, card_size_info_1_cn);

	ssd1306_set_page_address(1);
	ssd1306_set_column_address(48);
	sprintf(p_string, ": %lu KB", sd_card_size);
	ssd1306_write_text(p_string);
#endif
#ifdef CONF_JAPANESE_LANGUAGE
	unicode_show_one_line(2, 0, card_size_info_1_jp);

	ssd1306_set_page_address(3);
	ssd1306_set_column_address(32);
	sprintf(p_string, ": %lu KB", sd_card_size);
	ssd1306_write_text(p_string);

	/* Wait 3 seconds to show the above message. */
	delay_s(3);

	/* Clear screen. */
	ssd1306_clear();

	/* scroll one line to show file info */
	unicode_show_one_line(0, 0, card_size_info_1_jp);

	ssd1306_set_page_address(1);
	ssd1306_set_column_address(32);
	sprintf(p_string, ": %lu KB", sd_card_size);
	ssd1306_write_text(p_string);
#endif
#ifdef CONF_FRENCH_LANGUAGE
	/* Wait 1.5 seconds to show the above message. */
	delay_ms(1500);

	/* Clear screen. */
	ssd1306_clear();

	unicode_show_one_line(0, 0, card_size_info_1_fr);

	ssd1306_set_page_address(2);
	ssd1306_set_column_address(0);
	sprintf(p_string, ": %lu KB", sd_card_size);
	ssd1306_write_text(p_string);

	/* Wait 1.5 seconds to show the above message. */
	delay_ms(1500);

	/* Clear screen. */
	ssd1306_clear();
#endif
#ifdef CONF_SPANISH_LANGUAGE
	/* Wait 1.5 seconds to show the above message. */
	delay_ms(1500);

	/* Clear screen. */
	ssd1306_clear();

	unicode_show_one_line(0, 0, card_size_info_1_sp);

	ssd1306_set_page_address(2);
	ssd1306_set_column_address(0);
	sprintf(p_string, ": %lu KB", sd_card_size);
	ssd1306_write_text(p_string);

	/* Wait 1.5 seconds to show the above message. */
	delay_ms(1500);

	/* Clear screen. */
	ssd1306_clear();
#endif
}

/**
 * \brief Show no fatfs found info on the OLED screen.
 */
void multi_language_show_no_fatfs_info(void)
{
#ifdef CONF_ENGLISH_LANGUAGE
	ssd1306_write_text("   <No FAT FS found on SD>");
#endif
#ifdef CONF_CHINESE_LANGUAGE
	unicode_show_one_line(2, 0, no_fatfs_info_1_cn);
#endif
#ifdef CONF_JAPANESE_LANGUAGE
	unicode_show_one_line(2, 0, no_fatfs_info_1_jp);
#endif
#ifdef CONF_FRENCH_LANGUAGE
	unicode_show_one_line(0, 0, no_fatfs_info_1_fr);
#endif
#ifdef CONF_SPANISH_LANGUAGE
	unicode_show_one_line(0, 0, no_fatfs_info_1_sp);
#endif
}

/**
 * \brief Show no file found info on the OLED screen.
 */
void multi_language_show_no_files_info(void)
{
#ifdef CONF_ENGLISH_LANGUAGE
	ssd1306_write_text("         <no content>");
#endif
#ifdef CONF_CHINESE_LANGUAGE
	unicode_show_one_line(2, 0, no_files_info_1_cn);
#endif
#ifdef CONF_JAPANESE_LANGUAGE
	unicode_show_one_line(2, 0, no_files_info_1_jp);
#endif
#ifdef CONF_FRENCH_LANGUAGE
	unicode_show_one_line(0, 0, no_files_info_1_fr);
#endif
#ifdef CONF_SPANISH_LANGUAGE
	unicode_show_one_line(0, 0, no_files_info_1_sp);
#endif
}

/**
 * \brief Show how to browse the SD card info on the OLED screen.
 */
void multi_language_show_browse_info(void)
{
#ifdef CONF_ENGLISH_LANGUAGE
	ssd1306_write_text("  <Press B2-3 to browse SD>");
#endif
#ifdef CONF_CHINESE_LANGUAGE
	unicode_show_one_line(2, 0, browse_info_1_cn);
#endif
#ifdef CONF_JAPANESE_LANGUAGE
	unicode_show_one_line(2, 0, browse_info_1_jp);
#endif
#ifdef CONF_FRENCH_LANGUAGE
	unicode_show_one_line(0, 0, browse_info_1_fr);
	unicode_show_one_line(2, 0, browse_info_2_fr);
#endif
#ifdef CONF_SPANISH_LANGUAGE
	unicode_show_one_line(0, 0, browse_info_1_sp);
	unicode_show_one_line(2, 0, browse_info_2_sp);
#endif
}

/**
 * \brief Display SD card file name on OLED screen.
 *
 * \param page page address of the OLED.
 * \param string String to display(unicode format).
 */
void multi_language_show_file_name(uint8_t page,
		const char *string)
{
#ifdef CONF_ENGLISH_LANGUAGE
	uint8_t *char_ptr;
	uint32_t i;
#endif
#ifndef CONF_ENGLISH_LANGUAGE
	uint16_t unicode_16;
#endif
	uint8_t unicode_8[2];
	uint8_t column;

	ssd1306_set_page_address(page);
	ssd1306_set_column_address(0);
	ssd1306_write_text("/");

	column = 3;

	unicode_8[0] = *string;
	string++;
	unicode_8[1] = *string;
	string++;

	while (((unicode_8[0] != 0) || (unicode_8[1] != 0)) && (column < 128)) {
#ifdef CONF_ENGLISH_LANGUAGE
		if ((unicode_8[0] < 0x7F) && (unicode_8[1] == 0)) {
			char_ptr = font_table[unicode_8[0] - 32];
			if ((column + char_ptr[0]) < 128) {
				for (i = 1; i <= char_ptr[0]; i++) {
					ssd1306_write_data(char_ptr[i]);
				}
				ssd1306_write_data(0x00);
			}
			column += char_ptr[0];
			column++;
		}
#else
		unicode_16 = unicode_8[0] | (unicode_8[1] << 8);
		font_bitmap_find(unicode_16);
		font_bitmap_transfer();
		if ((column + 8 * font_bitmap_width) < 128) {
			font_bitmap_display(page - 1, column);
		}
		column += (8 * font_bitmap_width);
#endif
		unicode_8[0] = *string;
		string++;
		unicode_8[1] = *string;
		string++;
	}
}

