/**
 * \file
 *
 * \brief Generic monochrome LCD graphic primitives
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
#ifndef GFX_MONO_GENERIC
#define GFX_MONO_GENERIC
#include "gfx_mono.h"

/**
 * \ingroup gfx_mono
 * \defgroup gfx_mono_generic_group Generic monochrome graphic primitives
 *
 * This is a service providing generic implementations of graphic primitives
 * - Horizontal line
 * - Vertical line
 * - Line
 * - Circle (filled/not filled)
 * - Rectangle (filled/not filled)
 *
 * it also provides functionality to draw a bitmap to the graphic memory.
 *
 * These functions are made available if the graphic hardware being used do
 * not implement the functionality in hardware. This is true in most cases.
 *
 * This service is included as a requirement for a
 * hardware specific component that uses these functions, and provides a
 * gfx_draw_pixel function.
 *
 * @{
 */

/**
 * \brief Storage structure for bitmap pixel data and metadata
 */
struct gfx_mono_bitmap {
	/** Width of bitmap */
	gfx_coord_t width;
	/** Height of bitmap */
	gfx_coord_t height;
	/** Bitmap type */
	enum gfx_mono_bitmap_type type;
	union {
		/** Pointer to pixels for bitmap stored in RAM */
		gfx_mono_color_t *pixmap;
		/** Pointer to pixels for bitmap stored in progmem */
		gfx_mono_color_t PROGMEM_T *progmem;
	}
	data;
};

void gfx_mono_generic_draw_horizontal_line(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t length, enum gfx_mono_color color);

void gfx_mono_generic_draw_vertical_line(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t length, enum gfx_mono_color color);

void gfx_mono_generic_draw_line(gfx_coord_t x1, gfx_coord_t y1,
		gfx_coord_t x2, gfx_coord_t y2,
		enum gfx_mono_color color);

void gfx_mono_generic_draw_rect(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t width, gfx_coord_t height,
		enum gfx_mono_color color);

void gfx_mono_generic_draw_filled_rect(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t width, gfx_coord_t height,
		enum gfx_mono_color color);

void gfx_mono_generic_draw_circle(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t radius, enum gfx_mono_color color,
		uint8_t octant_mask);

void gfx_mono_generic_draw_filled_circle(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t radius, enum gfx_mono_color color,
		uint8_t quadrant_mask);

void gfx_mono_generic_put_bitmap(struct gfx_mono_bitmap *bitmap, gfx_coord_t x,
		gfx_coord_t y);

/** @} */

#endif /* GFX_MONO_GENERIC */
