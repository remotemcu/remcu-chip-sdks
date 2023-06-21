/**
 * \file
 *
 * \brief Haven Display C12832 A1Z display glue code for display controller
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef GFX_MONO_C12832_A1Z_H
#define GFX_MONO_C12832_A1Z_H
#include "compiler.h"
#include "st7565r.h"

#include "gfx_mono.h"
#include "gfx_mono_framebuffer.h"

/**
 * \ingroup gfx_mono
 * \defgroup gfx_mono_C12832_A1Z_group C12832_A1Z graphic library abstraction
 *
 * This module is an abstraction layer between the graphic library and the
 * C12832_A1Z monochrome LCD display connected to a ST7565R LCD controller.
 *
 * As the controller does not provide any hardware accelerated graphic, all the
 * graphic primitives are provided by the \ref gfx_mono_generic_group service.
 *
 * \note Do not call the gfx_mono_st7565r_ functions directly. use the gfx_mono
 * names that are defined in this header and documented in \ref gfx_mono .
 * Ie. gfx_mono_draw_pixel() should be used, not gfx_mono_st7565r_draw_pixel()
 * @{
 */

#define GFX_MONO_LCD_WIDTH              128
#define GFX_MONO_LCD_HEIGHT             32
#define GFX_MONO_LCD_PIXELS_PER_BYTE    8
#define GFX_MONO_LCD_PAGES              (GFX_MONO_LCD_HEIGHT / \
	GFX_MONO_LCD_PIXELS_PER_BYTE)
#define GFX_MONO_LCD_FRAMEBUFFER_SIZE   ((GFX_MONO_LCD_WIDTH * \
	GFX_MONO_LCD_HEIGHT) / GFX_MONO_LCD_PIXELS_PER_BYTE)

#define gfx_mono_draw_horizontal_line(x, y, length, color) \
	gfx_mono_generic_draw_horizontal_line(x, y, length, color)

#define gfx_mono_draw_vertical_line(x, y, length, color) \
	gfx_mono_generic_draw_vertical_line(x, y, length, color)

#define gfx_mono_draw_line(x1, y1, x2, y2, color) \
	gfx_mono_generic_draw_line(x1, y1, x2, y2, color)

#define gfx_mono_draw_rect(x, y, width, height, color) \
	gfx_mono_generic_draw_rect(x, y, width, height, color)

#define gfx_mono_draw_filled_rect(x, y, width, height, color) \
	gfx_mono_generic_draw_filled_rect(x, y, width, height, \
		color)

#define gfx_mono_draw_circle(x, y, radius, color, octant_mask) \
	gfx_mono_generic_draw_circle(x, y, radius, color, \
		octant_mask)

#define gfx_mono_draw_filled_circle(x, y, radius, color, quadrant_mask)	\
	gfx_mono_generic_draw_filled_circle(x, y, radius, \
		color, quadrant_mask)

#define gfx_mono_put_bitmap(bitmap, x, y) \
	gfx_mono_generic_put_bitmap(bitmap, x, y)

#define gfx_mono_draw_pixel(x, y, color) \
	gfx_mono_st7565r_draw_pixel(x, y, color)

#define gfx_mono_get_pixel(x, y) \
	gfx_mono_st7565r_get_pixel(x, y)

#define gfx_mono_init()	\
	gfx_mono_st7565r_init()

#define gfx_mono_put_page(data, page, column, width) \
	gfx_mono_st7565r_put_page(data, page, column, width)

#define gfx_mono_get_page(data, page, column, width) \
	gfx_mono_st7565r_get_page(data, page, column, width)

#define gfx_mono_put_byte(page, column, data) \
	gfx_mono_st7565r_put_byte(page, column, data)

#define gfx_mono_get_byte(page, column)	\
	gfx_mono_st7565r_get_byte(page, column)

#define gfx_mono_mask_byte(page, column, pixel_mask, color) \
	gfx_mono_st7565r_mask_byte(page, column, pixel_mask, color)

#define gfx_mono_put_framebuffer() \
	gfx_mono_st7565r_put_framebuffer()

void gfx_mono_st7565r_put_framebuffer(void);

void gfx_mono_st7565r_put_page(gfx_mono_color_t *data, gfx_coord_t page,
		gfx_coord_t page_offset, gfx_coord_t width);

void gfx_mono_st7565r_get_page(gfx_mono_color_t *data, gfx_coord_t page,
		gfx_coord_t page_offset, gfx_coord_t width);

void gfx_mono_st7565r_init(void);

void gfx_mono_st7565r_draw_pixel(gfx_coord_t x, gfx_coord_t y,
		gfx_mono_color_t color);

uint8_t gfx_mono_st7565r_get_pixel(gfx_coord_t x, gfx_coord_t y);

void gfx_mono_st7565r_put_byte(gfx_coord_t page, gfx_coord_t column,
		uint8_t data);

uint8_t gfx_mono_st7565r_get_byte(gfx_coord_t page, gfx_coord_t column);

void gfx_mono_st7565r_mask_byte(gfx_coord_t page, gfx_coord_t column,
		gfx_mono_color_t pixel_mask, gfx_mono_color_t color);

/** @} */

#endif /* GFX_MONO_C12832_A1Z_H */
