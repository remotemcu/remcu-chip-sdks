/**
 * \file
 *
 * \brief Graphic service settings for the ET024006DHU panel using the HX8347A display controller over EBI
 *
 * This files includes the correct header files for the grapics service
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
 * \ingroup gfx_hx8347a_et024006dhu_ebi
 * @{
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "gfx.h"
#include "gfx_hx8347a_et024006dhu_ebi.h"
#include "et024006dhu.h"
#include "sysclk.h"
#include "ioport.h"

gfx_coord_t gfx_height, gfx_width;
gfx_coord_t gfx_min_x, gfx_min_y;
gfx_coord_t gfx_max_x, gfx_max_y;

void gfx_et024006dhu_set_orientation(uint8_t flags)
{
	/* Not implemented for this controller */
}

gfx_color_t gfx_et024006dhu_color(uint8_t r, uint8_t g, uint8_t b)
{
	return GFX_COLOR(r, g, b);
}

gfx_color_t gfx_et024006dhu_get_pixel(gfx_coord_t x, gfx_coord_t y)
{
#ifdef CONF_GFX_USE_CLIPPING
	if ((x < gfx_min_x) || (x > gfx_max_x) ||
			(y < gfx_min_y) || (y > gfx_max_y)) {
		return GFX_COLOR_INVALID;
	}
#endif

	return et024006_GetPixel(x, y);
}

void gfx_et024006dhu_draw_pixel(gfx_coord_t x, gfx_coord_t y, gfx_color_t color)
{
#ifdef CONF_GFX_USE_CLIPPING
	if ((x < gfx_min_x) || (x > gfx_max_x) ||
			(y < gfx_min_y) || (y > gfx_max_y)) {
		return;
	}
#endif

	et024006_DrawPixel(x, y, color);
}

void gfx_et024006dhu_draw_line_pixel(gfx_coord_t x, gfx_coord_t y,
		gfx_color_t color)
{
#ifdef CONF_GFX_USE_CLIPPING
	if ((x < gfx_min_x) || (x > gfx_max_x) ||
			(y < gfx_min_y) || (y > gfx_max_y)) {
		return;
	}
#endif

	et024006_DrawQuickPixel(x, y, color);
}

void gfx_et024006dhu_init(void)
{
	/* Initialize globals */
	gfx_width  = GFX_PANELWIDTH;
	gfx_height = GFX_PANELHEIGHT;

	et024006_Init(sysclk_get_cpu_hz(), sysclk_get_pbb_hz());
	
#if defined(ET024006DHU_BL_PIN)
	/* Turn on backlight if one has been configured */
	ioport_enable_pin(ET024006DHU_BL_PIN);
	ioport_set_pin_dir(ET024006DHU_BL_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(ET024006DHU_BL_PIN, true);
#endif

	/* Set clipping area to whole screen initially */
	gfx_set_clipping(0, 0, GFX_PANELWIDTH, GFX_PANELHEIGHT);

	gfx_draw_filled_rect(0, 0, GFX_PANELWIDTH, GFX_PANELHEIGHT,
			GFX_COLOR(0xFF, 0xFF, 0xFF));
}

/**
 *@}
 */
