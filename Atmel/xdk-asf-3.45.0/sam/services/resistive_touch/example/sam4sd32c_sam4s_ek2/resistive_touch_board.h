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

#include "ili9325.h"

#define lcd_set_foreground_color  ili9325_set_foreground_color
#define lcd_draw_filled_rectangle ili9325_draw_filled_rectangle
#define lcd_display_on ili9325_display_on
#define lcd_fill  ili9325_fill
#define lcd_draw_string ili9325_draw_string

#define LCD_WIDTH ILI9325_LCD_WIDTH
#define LCD_HEIGHT ILI9325_LCD_WIDTH

#define UNI_COLOR_BLACK  COLOR_BLACK
#define UNI_COLOR_WHITE  COLOR_WHITE
#define UNI_COLOR_RED  COLOR_RED

static inline void lcd_init(void)
{
	struct ili9325_opt_t g_display_opt;

	/* Enable SMC clock */
	pmc_enable_periph_clk(ID_SMC);

	smc_set_setup_timing(SMC, 1, SMC_SETUP_NWE_SETUP(2)
			| SMC_SETUP_NCS_WR_SETUP(2)
			| SMC_SETUP_NRD_SETUP(2)
			| SMC_SETUP_NCS_RD_SETUP(2));
	smc_set_pulse_timing(SMC, 1, SMC_PULSE_NWE_PULSE(4)
			| SMC_PULSE_NCS_WR_PULSE(4)
			| SMC_PULSE_NRD_PULSE(10)
			| SMC_PULSE_NCS_RD_PULSE(10));
	smc_set_cycle_timing(SMC, 1, SMC_CYCLE_NWE_CYCLE(10)
			| SMC_CYCLE_NRD_CYCLE(22));
	smc_set_mode(SMC, 1, SMC_MODE_READ_MODE | SMC_MODE_WRITE_MODE);

	g_display_opt.ul_width = LCD_WIDTH;
	g_display_opt.ul_height = LCD_HEIGHT;
	g_display_opt.foreground_color = COLOR_BLACK;
	g_display_opt.background_color = COLOR_WHITE;

	/* Initialize ili9325 */
	ili9325_init(&g_display_opt);
}

#endif /* RESISTIVE_TOUCH_BOARD_H_INCLUDED */
