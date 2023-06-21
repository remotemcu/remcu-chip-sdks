/**
 * \file
 *
 * \brief Board specific definition for resistive touch example.
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

#ifndef RESISTIVE_TOUCH_BOARD_H_INCLUDED
#define RESISTIVE_TOUCH_BOARD_H_INCLUDED

#include "hx8347a.h"

#define lcd_set_foreground_color  hx8347a_set_foreground_color
#define lcd_draw_filled_rectangle hx8347a_draw_filled_rectangle
#define lcd_display_on hx8347a_display_on
#define lcd_fill  hx8347a_fill
#define lcd_draw_string hx8347a_draw_string

#define LCD_WIDTH HX8347A_LCD_WIDTH
#define LCD_HEIGHT HX8347A_LCD_HEIGHT

#define UNI_COLOR_BLACK  rgb24_to_rgb16(COLOR_BLACK)
#define UNI_COLOR_WHITE  rgb24_to_rgb16(COLOR_WHITE)
#define UNI_COLOR_RED  rgb24_to_rgb16(COLOR_RED)

/* Convert 24-bits color to 16-bits color */
static hx8347a_color_t rgb24_to_rgb16(uint32_t ul_color)
{
	hx8347a_color_t result_color;
	result_color = (((ul_color >> 8) & 0xF800) |
			((ul_color >> 5) & 0x7E0) | ((ul_color >> 3) & 0x1F));
	return result_color;
}

static void lcd_init(void)
{
	struct hx8347a_opt_t g_display_opt;
	
	/* Enable SMC clock */
	pmc_enable_periph_clk(ID_SMC);

	/* Configure SMC interface for Lcd */
	smc_set_setup_timing(SMC, CONF_BOARD_HX8347A_LCD_CS, SMC_SETUP_NWE_SETUP(1)
			| SMC_SETUP_NCS_WR_SETUP(1)
			| SMC_SETUP_NRD_SETUP(9)
			| SMC_SETUP_NCS_RD_SETUP(9));
	smc_set_pulse_timing(SMC, CONF_BOARD_HX8347A_LCD_CS, SMC_PULSE_NWE_PULSE(4)
			| SMC_PULSE_NCS_WR_PULSE(4)
			| SMC_PULSE_NRD_PULSE(36)
			| SMC_PULSE_NCS_RD_PULSE(36));
	smc_set_cycle_timing(SMC, CONF_BOARD_HX8347A_LCD_CS, SMC_CYCLE_NWE_CYCLE(10)
			| SMC_CYCLE_NRD_CYCLE(45));
	smc_set_mode(SMC, CONF_BOARD_HX8347A_LCD_CS, SMC_MODE_READ_MODE
			| SMC_MODE_WRITE_MODE | SMC_MODE_DBW_BIT_16);

	/* Initialize display parameter */
	g_display_opt.ul_width = HX8347A_LCD_WIDTH;
	g_display_opt.ul_height = HX8347A_LCD_HEIGHT;
	g_display_opt.foreground_color = rgb24_to_rgb16(COLOR_BLACK);
	g_display_opt.background_color = rgb24_to_rgb16(COLOR_WHITE);

	/* Initialize hx8347a */
	hx8347a_init(&g_display_opt);
}

#endif /* RESISTIVE_TOUCH_BOARD_H_INCLUDED */
