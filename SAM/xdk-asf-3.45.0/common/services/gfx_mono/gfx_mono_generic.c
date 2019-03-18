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

/**
 * \ingroup gfx_mono_generic_group
 * @{
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include "gfx_mono_generic.h"

/**
 * \brief Draw a horizontal line, one pixel wide (generic implementation)
 *
 * \note This function does a very simple bounds checking that does not
 * check if the line is placed outside the screen. If you supply an
 * x- or y-coordinate outside the display the behaviour is undefined,
 * and you risk overwriting portions of internal SRAM.
 *
 * \param  x          X coordinate of leftmost pixel.
 * \param  y          Y coordinate of the line.
 * \param  length     Length of the line in pixels.
 * \param  color      Pixel operation of the line.
 */
void gfx_mono_generic_draw_horizontal_line(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t length, enum gfx_mono_color color)
{
	uint8_t page;
	uint8_t pixelmask;
	uint8_t temp;

	/* Clip line length if too long */
	if (x + length > GFX_MONO_LCD_WIDTH) {
		length = GFX_MONO_LCD_WIDTH - x;
	}

	page = y / 8;
	pixelmask = (1 << (y - (page * 8)));

	if (length == 0) {
		/* Nothing to do. Move along. */
		return;
	}

	switch (color) {
	case GFX_PIXEL_SET:
		while (length-- > 0) {
			temp = gfx_mono_get_byte(page, x + length);
			temp |= pixelmask;
			gfx_mono_put_byte(page, x + length, temp);
		}
		break;

	case GFX_PIXEL_CLR:
		while (length-- > 0) {
			temp = gfx_mono_get_byte(page, x + length);
			temp &= ~pixelmask;
			gfx_mono_put_byte(page, x + length, temp);
		}
		break;

	case GFX_PIXEL_XOR:
		while (length-- > 0) {
			temp = gfx_mono_get_byte(page, x + length);
			temp ^= pixelmask;
			gfx_mono_put_byte(page, x + length, temp);
		}
		break;

	default:
		break;
	}
}

/**
 * \brief Draw a vertical line, one pixel wide (generic implementation)
 *
 * \note This function does a very simple bounds checking that does not
 * check if the line is placed outside the screen. If you supply an
 * x- or y-coordinate outside the display the behaviour is undefined,
 * and you risk overwriting portions of internal SRAM.
 *
 * \param  x          X coordinate of the line.
 * \param  y          Y coordinate of the topmost pixel.
 * \param  length     Length of the line in pixels.
 * \param  color      Pixel operation of the line.
 */
void gfx_mono_generic_draw_vertical_line(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t length, enum gfx_mono_color color)
{
	if (length == 0) {
		return;
	}

	gfx_coord_t y2 = y + length - 1;

	if (y == y2) {
		gfx_mono_draw_pixel(x, y, color);
		return;
	}

	if (y2 >= GFX_MONO_LCD_HEIGHT - 1) {
		y2 = GFX_MONO_LCD_HEIGHT - 1;
	}

	gfx_coord_t y1page = y / 8;
	gfx_coord_t y2page = y2 / 8;

	uint8_t y1bitpos = y & 0x07;
	uint8_t y2bitpos = y2 & 0x07;

	uint8_t y1pixelmask = 0xFF << y1bitpos;
	uint8_t y2pixelmask = 0xFF >> (7 - y2bitpos);

	/* The pixels are on the same page; combine masks */
	if (y1page == y2page) {
		uint8_t pixelmask = y1pixelmask & y2pixelmask;
		gfx_mono_mask_byte(y1page, x, pixelmask, color);
	} else {
		gfx_mono_mask_byte(y1page, x, y1pixelmask, color);

		while (++y1page < y2page) {
			gfx_mono_mask_byte(y1page, x, 0xFF, color);
		}

		gfx_mono_mask_byte(y2page, x, y2pixelmask, color);
	}
}

/**
 * \brief Draw a line between two arbitrary points (generic implementation).
 *
 * \param  x1          Start X coordinate.
 * \param  y1          Start Y coordinate.
 * \param  x2          End X coordinate.
 * \param  y2          End Y coordinate.
 * \param  color       Pixel operation of the line.
 */
void gfx_mono_generic_draw_line(gfx_coord_t x1, gfx_coord_t y1,
		gfx_coord_t x2, gfx_coord_t y2,
		enum gfx_mono_color color)
{
	uint8_t i;
	uint8_t x;
	uint8_t y;
	int8_t xinc;
	int8_t yinc;
	int8_t dx;
	int8_t dy;
	int8_t e;

	/* swap x1,y1  with x2,y2 */
	if (x1 > x2) {
		dx = x1;
		x1 = x2;
		x2 = dx;
		dy = y1;
		y1 = y2;
		y2 = dy;
	}

	dx = x2 - x1;
	dy = y2 - y1;

	x = x1;
	y = y1;

	if (dx < 0) {
		xinc = -1;
		dx = -dx;
	} else {
		xinc = 1;
	}

	if (dy < 0) {
		yinc = -1;
		dy = -dy;
	} else {
		yinc = 1;
	}

	if (dx > dy) {
		e = dy - dx;
		for (i = 0; i <= dx; i++) {
			gfx_mono_draw_pixel(x, y, color);
			if (e >= 0) {
				e -= dx;
				y += yinc;
			}

			e += dy;
			x += xinc;
		}
	} else {
		e = dx - dy;
		for (i = 0; i <= dy; i++) {
			gfx_mono_draw_pixel(x, y, color);
			if (e >= 0) {
				e -= dy;
				x += xinc;
			}

			e += dx;
			y += yinc;
		}
	}
}

/**
 * \brief Draw an outline of a rectangle (generic implementation).
 *
 * \param  x           X coordinate of the left side.
 * \param  y           Y coordinate of the top side.
 * \param  width       Width of the rectangle.
 * \param  height      Height of the rectangle.
 * \param  color       Pixel operation of the line.
 */
void gfx_mono_generic_draw_rect(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t width, gfx_coord_t height,
		enum gfx_mono_color color)
{
	gfx_mono_draw_horizontal_line(x, y, width, color);
	gfx_mono_draw_horizontal_line(x, y + height - 1, width, color);

	gfx_mono_draw_vertical_line(x, y, height, color);
	gfx_mono_draw_vertical_line(x + width - 1, y, height, color);
}

/**
 * \brief Draw a filled rectangle (generic implementation).
 *
 * \param  x           X coordinate of the left side.
 * \param  y           Y coordinate of the top side.
 * \param  width       Width of the rectangle.
 * \param  height      Height of the rectangle.
 * \param  color       Pixel operation of the line
 */
void gfx_mono_generic_draw_filled_rect(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t width, gfx_coord_t height,
		enum gfx_mono_color color)
{
	if (height == 0) {
		/* Nothing to do. Move along. */
		return;
	}

	while (height-- > 0) {
		gfx_mono_draw_horizontal_line(x, y + height, width, color);
	}
}

/**
 * \brief Draw an outline of a circle or arc (generic implementation).
 *
 * The radius is the distance from the center to the circumference,
 * which means that the total width or height of a circle will be
 * (radius*2+1).
 *
 * The octant_mask parameter is a bitmask that decides which octants of
 * the circle to draw. Use the GFX_OCTANTn, GFX_QUADRANTn, GFX_xHALF and
 * GFX_WHOLE constants and OR them together if required. Radius equal to
 * zero gives a single pixel.
 *
 * \param  x           X coordinate of center.
 * \param  y           Y coordinate of center.
 * \param  radius      Circle radius in pixels.
 * \param  color       Pixel operation.
 * \param  octant_mask Bitmask indicating which octants to draw.
 */
void gfx_mono_generic_draw_circle(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t radius, enum gfx_mono_color color,
		uint8_t octant_mask)
{
	gfx_coord_t offset_x;
	gfx_coord_t offset_y;
	int16_t error;

	/* Draw only a pixel if radius is zero. */
	if (radius == 0) {
		gfx_mono_draw_pixel(x, y, color);
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
			gfx_mono_draw_pixel(x + offset_y, y - offset_x, color);
		}

		if (octant_mask & GFX_OCTANT1) {
			gfx_mono_draw_pixel(x + offset_x, y - offset_y, color);
		}

		if (octant_mask & GFX_OCTANT2) {
			gfx_mono_draw_pixel(x - offset_x, y - offset_y, color);
		}

		if (octant_mask & GFX_OCTANT3) {
			gfx_mono_draw_pixel(x - offset_y, y - offset_x, color);
		}

		if (octant_mask & GFX_OCTANT4) {
			gfx_mono_draw_pixel(x - offset_y, y + offset_x, color);
		}

		if (octant_mask & GFX_OCTANT5) {
			gfx_mono_draw_pixel(x - offset_x, y + offset_y, color);
		}

		if (octant_mask & GFX_OCTANT6) {
			gfx_mono_draw_pixel(x + offset_x, y + offset_y, color);
		}

		if (octant_mask & GFX_OCTANT7) {
			gfx_mono_draw_pixel(x + offset_y, y + offset_x, color);
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

/**
 * \brief Draw a filled circle or sector (generic implementation).
 *
 * The radius is the distance from the center to the circumference,
 * which means that the total width or height of a circle will be
 * (radius*2+1).
 *
 * The quadrant_mask parameter is a bitmask that decides which quadrants
 * of the circle to draw. Use the GFX_QUADRANTn, GFX_xHALF and
 * GFX_WHOLE constants and OR them together if required. Radius equal to
 * zero gives a single pixel.
 *
 * \note This function only supports quadrants while gfx_draw_circle()
 *       supports octants. This is to improve performance on drawing
 *       filled circles.
 *
 * \param  x           X coordinate of center.
 * \param  y           Y coordinate of center.
 * \param  radius      Circle radius in pixels.
 * \param  color       Pixel operation.
 * \param  quadrant_mask Bitmask indicating which quadrants to draw.
 */
void gfx_mono_generic_draw_filled_circle(gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t radius, enum gfx_mono_color color,
		uint8_t quadrant_mask)
{
	gfx_coord_t offset_x;
	gfx_coord_t offset_y;
	int16_t error;

	/* Draw only a pixel if radius is zero. */
	if (radius == 0) {
		gfx_mono_draw_pixel(x, y, color);
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
			gfx_mono_draw_vertical_line(x + offset_y,
					y - offset_x, offset_x + 1, color);
			gfx_mono_draw_vertical_line(x + offset_x,
					y - offset_y, offset_y + 1, color);
		}

		if (quadrant_mask & GFX_QUADRANT1) {
			gfx_mono_draw_vertical_line(x - offset_y,
					y - offset_x, offset_x + 1, color);
			gfx_mono_draw_vertical_line(x - offset_x,
					y - offset_y, offset_y + 1, color);
		}

		if (quadrant_mask & GFX_QUADRANT2) {
			gfx_mono_draw_vertical_line(x - offset_y,
					y, offset_x + 1, color);
			gfx_mono_draw_vertical_line(x - offset_x,
					y, offset_y + 1, color);
		}

		if (quadrant_mask & GFX_QUADRANT3) {
			gfx_mono_draw_vertical_line(x + offset_y,
					y, offset_x + 1, color);
			gfx_mono_draw_vertical_line(x + offset_x,
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

/**
 * \brief Put bitmap from FLASH or RAM to display
 *
 * This function will output bitmap data from FLASH or RAM.
 * The bitmap y-coordinate will be aligned with display pages, rounded down.
 * Ie: placing a bitmap at x=10, y=5 will put the bitmap at x = 10,y = 0 and
 * placing a bitmap at x = 10, y = 10 will put the bitmap at x = 10, y = 8
 *
 */
void gfx_mono_generic_put_bitmap(struct gfx_mono_bitmap *bitmap, gfx_coord_t x,
		gfx_coord_t y)
{
	gfx_coord_t num_pages = bitmap->height / 8;
	gfx_coord_t page = y / 8;
	gfx_coord_t column;
	gfx_coord_t i;
	gfx_mono_color_t temp;

	switch (bitmap->type) {
	case GFX_MONO_BITMAP_PROGMEM:
		for (i = 0; i < num_pages; i++) {
			for (column = 0; column < bitmap->width; column++) {
				temp = PROGMEM_READ_BYTE(bitmap->data.progmem
						+ (i * bitmap->width)
						+ column);
				gfx_mono_put_byte(i + page, column + x, temp);
			}
		}
		break;

	case GFX_MONO_BITMAP_RAM:
		for (i = 0; i < num_pages; i++) {
			gfx_mono_put_page(bitmap->data.pixmap
					+ (i * bitmap->width), page + i, x,
					bitmap->width);
		}
		break;

	default:
		break;
	}
}

/** @} */
