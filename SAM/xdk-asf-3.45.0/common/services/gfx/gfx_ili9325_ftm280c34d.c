/**
 * \file
 *
 * \brief Graphic service settings for the FTM280C34D panel using the ILI9325
 * display controller
 *
 * This files includes the correct header files for the graphics service
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

/**
 * \ingroup gfx_ili9325_ftm280c34d
 * @{
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "gfx.h"
#include "gfx_ili9325_ftm280c34d.h"
#include "ili9325.h"
#include "pmc.h"
#include "smc.h"
#include "aat31xx.h"

/* Chip select number to be set */
#define ILI9325_LCD_CS      1

gfx_coord_t gfx_height, gfx_width;
gfx_coord_t gfx_min_x, gfx_min_y;
gfx_coord_t gfx_max_x, gfx_max_y;

void gfx_ili9325_set_orientation(uint8_t flags)
{
	ili9325_set_orientation(flags);

	/* Switch width and height if XY is switched. */
	if ((flags & GFX_SWITCH_XY) != 0x00) {
		gfx_width = ILI9325_SWITCH_XY_WIDTH;
		gfx_height = ILI9325_SWITCH_XY_HEIGHT;
	} else {
		gfx_width = ILI9325_LCD_WIDTH;
		gfx_height = ILI9325_LCD_HEIGHT;
	}

#ifdef CONF_GFX_USE_CLIPPING
	/* Reset clipping region. */
	gfx_set_clipping(0, 0, gfx_width, gfx_height);
#endif
}

gfx_color_t gfx_ili9325_color(uint8_t r, uint8_t g, uint8_t b)
{
	return GFX_COLOR(r, g, b);
}

gfx_color_t gfx_ili9325_get_pixel(gfx_coord_t x, gfx_coord_t y)
{
	gfx_color_t color;

#ifdef CONF_GFX_USE_CLIPPING
	if ((x < gfx_min_x) || (x > gfx_max_x) ||
			(y < gfx_min_y) || (y > gfx_max_y)) {
		return GFX_COLOR_INVALID;
	}
#endif

	/* Set up draw area and read the three bytes of pixel data. */
	gfx_set_limits(x, y, x, y);
	color = ili9325_read_gram();

	return color;
}

void gfx_ili9325_draw_pixel(gfx_coord_t x, gfx_coord_t y, gfx_color_t color)
{
#ifdef CONF_GFX_USE_CLIPPING
	if ((x < gfx_min_x) || (x > gfx_max_x) ||
			(y < gfx_min_y) || (y > gfx_max_y)) {
		return;
	}
#endif

	/* Set up draw area and write the two bytes of pixel data. */
	gfx_set_limits(x, y, x, y);
	ili9325_write_gram(color);
}

void gfx_ili9325_draw_line_pixel(gfx_coord_t x, gfx_coord_t y,
		gfx_color_t color)
{
#ifdef CONF_GFX_USE_CLIPPING
	if ((x < gfx_min_x) || (x > gfx_max_x) ||
			(y < gfx_min_y) || (y > gfx_max_y)) {
		return;
	}
#endif

	/* Set up top left corner of area and write the two bytes of */
	/* pixel data.  Bottom left corner is already set to max_x/y. */
	gfx_set_top_left_limit(x, y);
	ili9325_write_gram(color);
}

void gfx_ili9325_init(void)
{
	struct ili9325_opt_t g_ili9325_display_opt;

	/* initialize globals */
	gfx_width = ILI9325_LCD_WIDTH;
	gfx_height = ILI9325_LCD_HEIGHT;

	/* Enable peripheral clock */
	pmc_enable_periph_clk(ID_SMC);

	/* Configure SMC interface for Lcd */
	smc_set_setup_timing(SMC,ILI9325_LCD_CS,SMC_SETUP_NWE_SETUP(2)
			| SMC_SETUP_NCS_WR_SETUP(2)
			| SMC_SETUP_NRD_SETUP(2)
			| SMC_SETUP_NCS_RD_SETUP(2));
	smc_set_pulse_timing(SMC, ILI9325_LCD_CS , SMC_PULSE_NWE_PULSE(4)
			| SMC_PULSE_NCS_WR_PULSE(4)
			| SMC_PULSE_NRD_PULSE(10)
			| SMC_PULSE_NCS_RD_PULSE(10));
	smc_set_cycle_timing(SMC, ILI9325_LCD_CS, SMC_CYCLE_NWE_CYCLE(10)
			| SMC_CYCLE_NRD_CYCLE(22));
#if !defined(SAM4S)
	smc_set_mode(SMC, ILI9325_LCD_CS, SMC_MODE_READ_MODE
			| SMC_MODE_WRITE_MODE
			| SMC_MODE_DBW_8_BIT);
#else
	smc_set_mode(SMC, ILI9325_LCD_CS, SMC_MODE_READ_MODE
			| SMC_MODE_WRITE_MODE);
#endif

	/* Initialize display parameter */
	g_ili9325_display_opt.ul_width= ILI9325_LCD_WIDTH;
	g_ili9325_display_opt.ul_height = ILI9325_LCD_HEIGHT;
	g_ili9325_display_opt.foreground_color= COLOR_BLACK;
	g_ili9325_display_opt.background_color = COLOR_WHITE;

	/* Switch off backlight */
	aat31xx_disable_backlight();

	/* Initialize LCD */
	ili9325_init(&g_ili9325_display_opt);
	ili9325_display_on();
	/* Set backlight level */
	aat31xx_set_backlight(AAT31XX_AVG_BACKLIGHT_LEVEL);

	/* Set clipping area to whole screen initially */
	gfx_set_clipping(0, 0, gfx_width, gfx_height);

	gfx_draw_filled_rect(0, 0, gfx_width, gfx_height,
			GFX_COLOR(0xFF, 0xFF, 0xFF));
}

/**
 *@}
 */
