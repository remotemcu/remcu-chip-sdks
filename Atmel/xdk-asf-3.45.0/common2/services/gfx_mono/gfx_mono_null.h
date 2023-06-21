/**
 * \file
 *
 * \brief Monochrome graphic library NULL display device with framebuffer
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

#ifndef GFX_MONO_NULL_H
#define GFX_MONO_NULL_H

#include "gfx_mono.h"
#include "gfx_mono_framebuffer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup asfdoc_common2_gfx_mono
 * \defgroup asfdoc_common2_gfx_mono_null NULL display device
 *
 * This module provides empty read/write functions to a null device
 * (framebuffer in RAM), removing the need for an actual display or
 * controller during testing, and enabling the use of most XMEGA boards.
 *
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
	gfx_mono_framebuffer_draw_pixel(x, y, color)

#define gfx_mono_get_pixel(x, y) \
	gfx_mono_framebuffer_get_pixel(x, y)

#define gfx_mono_init()	\
	gfx_mono_null_init()

#define gfx_mono_put_page(data, page, column, width) \
	gfx_mono_framebuffer_put_page(data, page, column, width)

#define gfx_mono_get_page(data, page, column, width) \
	gfx_mono_framebuffer_get_page(data, page, column, width)

#define gfx_mono_put_byte(page, column, data) \
	gfx_mono_framebuffer_put_byte(page, column, data)

#define gfx_mono_get_byte(page, column)	\
	gfx_mono_framebuffer_get_byte(page, column)

#define gfx_mono_mask_byte(page, column, pixel_mask, color) \
	gfx_mono_framebuffer_mask_byte(page, column, pixel_mask, color)

#define gfx_mono_put_framebuffer() \
	;

void gfx_mono_null_init(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* GFX_MONO_NULL_H */
