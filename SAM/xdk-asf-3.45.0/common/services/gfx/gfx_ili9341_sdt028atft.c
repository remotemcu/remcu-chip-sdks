/**
 * \file
 *
 * \brief Graphic service settings for the SDT028ATFT panel using the ILI9341
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
 * \ingroup gfx_ili9341_sdt028atft
 * @{
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "gfx.h"
#include "gfx_ili9341_sdt028atft.h"
#include "ili9341.h"
#include "ili9341_regs.h"

gfx_coord_t gfx_height, gfx_width;
gfx_coord_t gfx_min_x, gfx_min_y;
gfx_coord_t gfx_max_x, gfx_max_y;

void gfx_ili9341_set_orientation(uint8_t flags)
{
	ili9341_set_orientation(flags);

	/* Switch width and height if XY is switched. */
	if ((flags & GFX_SWITCH_XY) != 0x00) {
		gfx_width = ILI9341_SWITCH_XY_WIDTH;
		gfx_height = ILI9341_SWITCH_XY_HEIGHT;
	} else {
		gfx_width = ILI9341_DEFAULT_WIDTH;
		gfx_height = ILI9341_DEFAULT_HEIGHT;
	}

#ifdef CONF_GFX_USE_CLIPPING
	/* Reset clipping region. */
	gfx_set_clipping(0, 0, gfx_width - 1, gfx_height - 1);
#endif
}

gfx_color_t gfx_ili9341_color(uint8_t r, uint8_t g, uint8_t b)
{
	return GFX_COLOR(r, g, b);
}

gfx_color_t gfx_ili9341_get_pixel(gfx_coord_t x, gfx_coord_t y)
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
	color = ili9341_read_gram();

	return color;
}

void gfx_ili9341_draw_pixel(gfx_coord_t x, gfx_coord_t y, gfx_color_t color)
{
#ifdef CONF_GFX_USE_CLIPPING
	if ((x < gfx_min_x) || (x > gfx_max_x) ||
			(y < gfx_min_y) || (y > gfx_max_y)) {
		return;
	}
#endif

	/* Set up draw area and write the two bytes of pixel data. */
	gfx_set_limits(x, y, x, y);
	ili9341_write_gram(color);
}

void gfx_ili9341_draw_line_pixel(gfx_coord_t x, gfx_coord_t y,
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
	ili9341_write_gram(color);
}

void gfx_ili9341_init(void)
{
	/* initialize globals */
	gfx_width = ILI9341_DEFAULT_WIDTH;
	gfx_height = ILI9341_DEFAULT_HEIGHT;

	ili9341_init();
	ili9341_backlight_on();

	/* Set clipping area to whole screen initially */
	gfx_set_clipping(0, 0, gfx_width, gfx_height);

	gfx_draw_filled_rect(0, 0, gfx_width, gfx_height,
			GFX_COLOR_BLACK);
}

/**
 *@}
 */
