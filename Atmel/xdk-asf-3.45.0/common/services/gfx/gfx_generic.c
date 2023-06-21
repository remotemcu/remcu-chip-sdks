/**
 * \file
 *
 * \brief Generic graphic primitive routines
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include "gfx.h"
#include "compiler.h"

/** External bitmap draw interface handler */
static gfx_ext_draw_handler_t gfx_ext_draw_func;

/* This function is documented in gfx.h */
void gfx_set_clipping(gfx_coord_t min_x, gfx_coord_t min_y,
		gfx_coord_t max_x, gfx_coord_t max_y)
{
#ifdef CONF_GFX_USE_CLIPPING
	/* Limit clipping region to within display panel boundaries. */
	if (min_x < 0) {
		min_x = 0;
	}

	if (min_y < 0) {
		min_y = 0;
	}

	if (max_x >= gfx_width) {
		max_x = gfx_width - 1;
	}

	if (max_y >= gfx_height) {
		max_y = gfx_height - 1;
	}

	gfx_min_x = min_x;
	gfx_min_y = min_y;
	gfx_max_x = max_x;
	gfx_max_y = max_y;
#endif
}

gfx_coord_t gfx_get_width(void)
{
	return gfx_width;
}

gfx_coord_t gfx_get_height(void)
{
	return gfx_height;
}

/* This function is documented in gfx.h */
void gfx_generic_draw_filled_rect(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t width, gfx_coord_t height,
		gfx_color_t color)
{
	gfx_coord_t x2;
	gfx_coord_t y2;

	if ((width == 0) || (height == 0)) {
		return;
	}

	/* Invert if width or height is negative. */
	if (width < 0) {
		width = -width;
		x -= width - 1;
	}

	if (height < 0) {
		height = -height;
		y -= height - 1;
	}

#ifdef CONF_GFX_USE_CLIPPING
	/* Nothing to do if entire rectangle is outside clipping region. */
	if ((x > gfx_max_x) || (y > gfx_max_y) ||
			((x + width) <= gfx_min_x) ||
			((y + height) <= gfx_min_y)) {
		return;
	}

	/* Clip if outside left X limit. */
	if (x < gfx_min_x) {
		width -= gfx_min_x - x;
		x = gfx_min_x;
	}

	/* Clip if outside top Y limit. */
	if (y < gfx_min_y) {
		height -= gfx_min_y - y;
		y = gfx_min_y;
	}
#endif

	/*  Compute bottom right point. */
	x2 = x + width - 1;
	y2 = y + height - 1;

#ifdef CONF_GFX_USE_CLIPPING
	/* Clip if outside right X limit. */
	if (x2 > gfx_max_x) {
		x2 = gfx_max_x;
		width = x2 - x + 1;
	}

	/* Clip if outside bottom Y limit. */
	if (y2 > gfx_max_y) {
		y2 = gfx_max_y;
		height = y2 - y + 1;
	}
#endif

	/* Set up draw area and duplicate pixel color until area is full. */
	gfx_set_limits(x, y, x2, y2);
	gfx_duplicate_pixel(color, (uint32_t)width * height);
}

void gfx_generic_draw_line(gfx_coord_t x1, gfx_coord_t y1,
		gfx_coord_t x2, gfx_coord_t y2, gfx_color_t color)
{
	gfx_coord_t x;
	gfx_coord_t y;
	int16_t xinc;
	int16_t yinc;
	int16_t dx;
	int16_t dy;

	/* Compute deltas, ie. "width" and "height" of line, then
	 * compute x and y direction, and make deltas positive for later use.
	 * Start off assuming direction is positive, ie. right and down.
	 */
	xinc = 1;
	dx = x2 - x1;
	if (dx < 0) {
		xinc = -1;
		dx = -dx;
	}

	yinc = 1;
	dy = y2 - y1;
	if (dy < 0) {
		yinc = -1;
		dy = -dy;
	}

	/* Set up current point and prepare bottom right corner of draw area.*/
	x = x1;
	y = y1;
	gfx_set_bottom_right_limit(gfx_width - 1, gfx_height - 1);

	/*
	 * A "flat" line (dx>dy) is handled differently from a "steep"
	 * line (dx<dy).
	 */
	if (dx > dy) {
		gfx_coord_t i;
		int16_t e = dx >> 1;

		/* Walk along X, draw pixel, and step Y when required. */
		for (i = 0; i <= dx; ++i) {
			gfx_draw_line_pixel(x, y, color);

			/* Update fractional part ("error"),
			 * and step Y when it crosses 0.
			 */
			e -= dy;
			if (e < 0) {
				e += dx;
				y += yinc;
			}

			/* Walk one step along X.*/
			x += xinc;
		}
	} else {
		gfx_coord_t i;
		int16_t e = dy >> 1;

		/* Walk along Y, draw pixel, and step X when required. */
		for (i = 0; i <= dy; ++i) {
			gfx_draw_line_pixel(x, y, color);

			/* Update fractional part ("error"),
			 * and step X when it crosses 0.
			 */
			e -= dx;
			if (e < 0) {
				e += dy;
				x += xinc;
			}

			/* Walk one step along Y. */
			y += yinc;
		}
	}
}

void gfx_generic_draw_circle(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t radius, gfx_color_t color, uint8_t octant_mask)
{
	gfx_coord_t offset_x;
	gfx_coord_t offset_y;
	int16_t error;

	/* Draw only a pixel if radius is zero. */
	if (radius == 0) {
		gfx_draw_pixel(x, y, color);
		return;
	}

	/* Set up start iterators. */
	offset_x = 0;
	offset_y = radius;
	error = 3 - 2 * radius;

	/* Iterate offsetX from 0 to radius. */
	while (offset_x <= offset_y) {
		/* Draw one pixel for each octant enabled in octant_mask. */
		if (octant_mask & GFX_OCTANT0) {
			gfx_draw_pixel(x + offset_y, y - offset_x, color);
		}

		if (octant_mask & GFX_OCTANT1) {
			gfx_draw_pixel(x + offset_x, y - offset_y, color);
		}

		if (octant_mask & GFX_OCTANT2) {
			gfx_draw_pixel(x - offset_x, y - offset_y, color);
		}

		if (octant_mask & GFX_OCTANT3) {
			gfx_draw_pixel(x - offset_y, y - offset_x, color);
		}

		if (octant_mask & GFX_OCTANT4) {
			gfx_draw_pixel(x - offset_y, y + offset_x, color);
		}

		if (octant_mask & GFX_OCTANT5) {
			gfx_draw_pixel(x - offset_x, y + offset_y, color);
		}

		if (octant_mask & GFX_OCTANT6) {
			gfx_draw_pixel(x + offset_x, y + offset_y, color);
		}

		if (octant_mask & GFX_OCTANT7) {
			gfx_draw_pixel(x + offset_y, y + offset_x, color);
		}

		/* Update error value and step offset_y when required. */
		if (error < 0) {
			error += ((offset_x << 2) + 6);
		} else {
			error += (((offset_x - offset_y) << 2) + 10);
			--offset_y;
		}

		/* Next X. */
		++offset_x;
	}
}

void gfx_generic_draw_filled_circle(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t radius, gfx_color_t color, uint8_t quadrant_mask)
{
	gfx_coord_t offset_x;
	gfx_coord_t offset_y;
	int16_t error;

	/* Draw only a pixel if radius is zero. */
	if (radius == 0) {
		gfx_draw_pixel(x, y, color);
		return;
	}

	/* Set up start iterators. */
	offset_x = 0;
	offset_y = radius;
	error = 3 - 2 * radius;

	/* Iterate offset_x from 0 to radius. */
	while (offset_x <= offset_y) {
		/* Draw vertical lines tracking each quadrant. */
		if (quadrant_mask & GFX_QUADRANT0) {
			gfx_draw_vertical_line(x + offset_y,
					y - offset_x, offset_x + 1, color);
			gfx_draw_vertical_line(x + offset_x,
					y - offset_y, offset_y + 1, color);
		}

		if (quadrant_mask & GFX_QUADRANT1) {
			gfx_draw_vertical_line(x - offset_y,
					y - offset_x, offset_x + 1, color);
			gfx_draw_vertical_line(x - offset_x,
					y - offset_y, offset_y + 1, color);
		}

		if (quadrant_mask & GFX_QUADRANT2) {
			gfx_draw_vertical_line(x - offset_y,
					y, offset_x + 1, color);
			gfx_draw_vertical_line(x - offset_x,
					y, offset_y + 1, color);
		}

		if (quadrant_mask & GFX_QUADRANT3) {
			gfx_draw_vertical_line(x + offset_y,
					y, offset_x + 1, color);
			gfx_draw_vertical_line(x + offset_x,
					y, offset_y + 1, color);
		}

		/* Update error value and step offset_y when required. */
		if (error < 0) {
			error += ((offset_x << 2) + 6);
		} else {
			error += (((offset_x - offset_y) << 2) + 10);
			--offset_y;
		}

		/* Next X. */
		++offset_x;
	}
}

void gfx_generic_get_pixmap(gfx_color_t *pixmap, gfx_coord_t map_width,
		gfx_coord_t map_x, gfx_coord_t map_y,
		gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t width, gfx_coord_t height)
{
	gfx_coord_t x2;
	gfx_coord_t y2;

	/* Nothing to do if width or height is zero. */
	if ((width == 0) || (height == 0)) {
		return;
	}

	/* Sanity check on parameters. */
	Assert(pixmap != 0);
	Assert((map_x + width) <= map_width);
	Assert(map_x >= 0);
	Assert(map_y >= 0);
	Assert(width > 0);
	Assert(height > 0);

#ifdef CONF_GFX_USE_CLIPPING
	/* Nothing to do if entire rectangle is outside clipping region. */
	if ((x > gfx_max_x) || (y > gfx_max_y) ||
			((x + width) <= gfx_min_x) ||
			((y + height) <= gfx_min_y)) {
		return;
	}

	/* Clip if outside left X limit. */
	if (x < gfx_min_x) {
		width -= gfx_min_x - x;
		map_x += gfx_min_x - x;
		x = gfx_min_x;
	}

	/* Clip if outside top Y limit. */
	if (y < gfx_min_y) {
		height -= gfx_min_y - y;
		map_y += gfx_min_y - y;
		y = gfx_min_y;
	}
#endif

	/* Compute bottom right point. */
	x2 = x + width - 1;
	y2 = y + height - 1;

#ifdef CONF_GFX_USE_CLIPPING
	/* Clip if outside right X limit. */
	if (x2 > gfx_max_x) {
		x2 = gfx_max_x;
		width = x2 - x + 1;
	}

	/* Clip if outside bottom Y limit. */
	if (y2 > gfx_max_y) {
		y2 = gfx_max_y;
		height = y2 - y + 1;
	}
#endif

	/* Offset into pixmap. */
	pixmap += map_x;
	if (map_y > 0) {
		pixmap += (uint32_t)map_y * map_width;
	}

	/* Set up read area. */
	gfx_set_bottom_right_limit(x2, y2);

	/* In case of no horizontal pixmap clipping, easier handling is
	 * possible.
	 */
	if ((map_width == width) && (map_x == 0)) {
		gfx_set_top_left_limit(x, y);
		gfx_copy_pixels_from_screen(pixmap, (uint32_t)width * height);
	} else {
		/* Copy line by line from screen. */
		gfx_coord_t lines_left = height;

		while (lines_left > 0) {
			/* Set up read area. */
			gfx_set_top_left_limit(x, y);
			++y;

			/* Get the pixels. */
			gfx_copy_pixels_from_screen(pixmap, width);
			pixmap += map_width;
			--lines_left;
		}
	}
}

void gfx_generic_put_pixmap(const gfx_color_t *pixmap, gfx_coord_t map_width,
		gfx_coord_t map_x, gfx_coord_t map_y,
		gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t width, gfx_coord_t height)
{
	gfx_coord_t x2;
	gfx_coord_t y2;

	/* Nothing to do if width or height is zero. */
	if ((width == 0) || (height == 0)) {
		return;
	}

	/* Sanity check on parameters. */
	Assert(pixmap != 0);
	Assert((map_x + width) <= map_width);
	Assert(map_x >= 0);
	Assert(map_y >= 0);
	Assert(width > 0);
	Assert(height > 0);

#ifdef CONF_GFX_USE_CLIPPING
	/* Nothing to do if entire rectangle is outside clipping region. */
	if ((x > gfx_max_x) || (y > gfx_max_y) ||
			((x + width) <= gfx_min_x) ||
			((y + height) <= gfx_min_y)) {
		return;
	}

	/* Clip if outside left X limit. */
	if (x < gfx_min_x) {
		width -= gfx_min_x - x;
		map_x += gfx_min_x - x;
		x = gfx_min_x;
	}

	/* Clip if outside top Y limit. */
	if (y < gfx_min_y) {
		height -= gfx_min_y - y;
		map_y += gfx_min_y - y;
		y = gfx_min_y;
	}
#endif

	/* Compute bottom right point. */
	x2 = x + width - 1;
	y2 = y + height - 1;

#ifdef CONF_GFX_USE_CLIPPING
	/* Clip if outside right X limit. */
	if (x2 > gfx_max_x) {
		x2 = gfx_max_x;
		width = x2 - x + 1;
	}

	/* Clip if outside bottom Y limit. */
	if (y2 > gfx_max_y) {
		y2 = gfx_max_y;
		height = y2 - y + 1;
	}
#endif

	/* Offset into pixmap. */
	pixmap += map_x;
	if (map_y > 0) {
		pixmap += (uint32_t)map_y * map_width;
	}

	/* Set up draw area. */
	gfx_set_bottom_right_limit(x2, y2);

	/* In case of no horizontal pixmap clipping, easier handling is
	 * possible.
	 */
	if ((map_width == width) && (map_x == 0)) {
		gfx_set_top_left_limit(x, y);
		gfx_copy_pixels_to_screen(pixmap, (uint32_t)width * height);
	} else {
		gfx_coord_t lines_left = height;

		/* Copy line by line to screen. */
		while (lines_left > 0) {
			/* Set up draw area. */
			gfx_set_top_left_limit(x, y);
			++y;

			/* Do the pixel copying. */
			gfx_copy_pixels_to_screen(pixmap, width);
			pixmap += map_width;
			--lines_left;
		}
	}
}

void gfx_generic_draw_bitmap_tiled(const struct gfx_bitmap *bmp, gfx_coord_t x1,
		gfx_coord_t y1, gfx_coord_t x2, gfx_coord_t y2,
		gfx_coord_t tile_origin_x, gfx_coord_t tile_origin_y)
{
	gfx_coord_t map_width;
	gfx_coord_t map_height;
	gfx_coord_t start_x;
	gfx_coord_t start_y;
	gfx_coord_t index_x;
	gfx_coord_t index_y;

	/* Sanity check on parameters. */
	Assert(bmp);
	Assert(x1 >= 0);
	Assert(y1 >= 0);
	Assert(x2 > x1);
	Assert(y2 > y1);
	Assert(tile_origin_x <= x1);
	Assert(tile_origin_y <= y1);

	/* Faster handling for solid color bitmaps */
	if (bmp->type == GFX_BITMAP_SOLID) {
		gfx_draw_filled_rect(x1, y1, x2 - x1 + 1, y2 - y1 + 1,
				bmp->data.color);
		return;
	}

	/* Find starting position */
	map_width = bmp->width;
	map_height = bmp->height;
	start_x = tile_origin_x;
	start_y = tile_origin_y;

	while (start_x <= (x1 - map_width)) {
		start_x += map_width;
	}
	while (start_y <= (y1 - map_height)) {
		start_y += map_height;
	}

	/* Draw tiles to cover the output area */
	for (index_y = start_y; index_y <= y2; index_y += map_height) {
		for (index_x = start_x; index_x <= x2; index_x += map_width) {
			gfx_put_bitmap(bmp, 0, 0, index_x, index_y, map_width,
					map_height);
		}
	}
}

void gfx_generic_put_bitmap(const struct gfx_bitmap *bmp,
		gfx_coord_t map_x, gfx_coord_t map_y,
		gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t width, gfx_coord_t height)
{
	gfx_coord_t x2;
	gfx_coord_t y2;
	gfx_coord_t map_width = bmp->width;
	gfx_color_t *pixmap;
#if XMEGA
	gfx_color_t PROGMEM_PTR_T progmem_pixmap;
#endif

	/* Nothing to do if width or height is zero. */
	if ((width == 0) || (height == 0)) {
		return;
	}

	/* Sanity check on parameters. */
	Assert(bmp);
	Assert((map_x + width) <= map_width);
	Assert(map_x >= 0);
	Assert(map_y >= 0);
	Assert(width > 0);
	Assert(height > 0);

#ifdef CONF_GFX_USE_CLIPPING
	/* Nothing to do if entire rectangle is outside clipping region. */
	if ((x > gfx_max_x) || (y > gfx_max_y) ||
			((x + width) <= gfx_min_x) ||
			((y + height) <= gfx_min_y)) {
		return;
	}

	/* Clip if outside left X limit. */
	if (x < gfx_min_x) {
		width -= gfx_min_x - x;
		map_x += gfx_min_x - x;
		x = gfx_min_x;
	}

	/* Clip if outside top Y limit. */
	if (y < gfx_min_y) {
		height -= gfx_min_y - y;
		map_y += gfx_min_y - y;
		y = gfx_min_y;
	}

#endif

	/* Compute bottom right point. */
	x2 = x + width - 1;
	y2 = y + height - 1;

#ifdef CONF_GFX_USE_CLIPPING
	/* Clip if outside right X limit. */
	if (x2 > gfx_max_x) {
		x2 = gfx_max_x;
		width = x2 - x + 1;
	}

	/* Clip if outside bottom Y limit. */
	if (y2 > gfx_max_y) {
		y2 = gfx_max_y;
		height = y2 - y + 1;
	}
#endif

	switch (bmp->type) {
	case GFX_BITMAP_SOLID:
		gfx_draw_filled_rect(x, y, x2 - x, y2 - y, bmp->data.color);
		break;

	case GFX_BITMAP_EXT:
		/* Draw bitmap through external interface */
		if (gfx_ext_draw_func != NULL) {
			gfx_ext_draw_func(bmp, x, y, x2 - x, y2 - y);
		}
		break;

	case GFX_BITMAP_RAM:
#if !XMEGA
	case GFX_BITMAP_PROGMEM:
#endif
		pixmap = bmp->data.pixmap;

		/* Offset into pixmap. */
		pixmap += map_x;

		if (map_y > 0) {
			pixmap += (uint32_t)map_y * map_width;
		}

		/* Set up draw area. */
		gfx_set_bottom_right_limit(x2, y2);

		/* In case of no horizontal pixmap clipping, easier handling is
		 * possible. */
		if ((map_width == width) && (map_x == 0)) {
			gfx_set_top_left_limit(x, y);
			gfx_copy_pixels_to_screen(pixmap,
					(uint32_t)width * height);
		} else {
			gfx_coord_t lines_left = height;

			/* Copy line by line to screen. */
			while (lines_left > 0) {
				/* Set up draw area. */
				gfx_set_top_left_limit(x, y);
				++y;

				/* Do the pixel copying. */
				gfx_copy_pixels_to_screen(pixmap, width);
				pixmap += map_width;
				--lines_left;
			}
		}

		break;

#if XMEGA
	case GFX_BITMAP_PROGMEM:
		progmem_pixmap = bmp->data.progmem;

		/* Offset into pixmap. */
		progmem_pixmap += map_x;

		if (map_y > 0) {
			progmem_pixmap += (uint32_t)map_y * map_width;
		}

		/* Set up draw area. */
		gfx_set_bottom_right_limit(x2, y2);

		/* In case of no horizontal pixmap clipping, easier handling is
		 * possible.
		 */
		if ((map_width == width) && (map_x == 0)) {
			gfx_set_top_left_limit(x, y);
			gfx_copy_progmem_pixels_to_screen(progmem_pixmap,
					(uint32_t)width * height);
		} else {
			gfx_coord_t lines_left = height;

			/* Copy line by line to screen. */
			while (lines_left > 0) {
				/* Set up draw area. */
				gfx_set_top_left_limit(x, y);
				++y;

				/* Do the pixel copying. */
				gfx_copy_progmem_pixels_to_screen(
						progmem_pixmap, width);
				progmem_pixmap += map_width;
				--lines_left;
			}
		}

		break;
#endif
	}
}

void gfx_generic_set_ext_handler(gfx_ext_draw_handler_t gfx_ext_draw)
{
	gfx_ext_draw_func = gfx_ext_draw;
}
