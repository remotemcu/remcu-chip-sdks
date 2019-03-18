/**
 * \file
 *
 * \brief Graphic service settings for the LCD panel using the ILI93XX
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef GFX_ILI93XX_H_INCLUDED
#define GFX_ILI93XX_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "ili93xx.h"

/**
 * \ingroup gfx_group
 * \defgroup gfx_ili93xx display using ILI93XX display controller
 *
 * This is hardware specific configuration that configures the graphical
 * service for use with the ILI93XX display controller display.
 * All the drawing functionality in this configuration is provided
 * by the \ref gfx_generic driver. This configuration includes information
 * about the panel size, data type used for coordinates and color and
 * functionality to convert RGB color to the color format native to the display.
 *
 * @{
 */

/* This macro generates a 16-bit native color for the display from a
 * 24-bit RGB value
 */
#define GFX_COLOR(r, g, b)      ILI93XX_COLOR(r, g, b)

/**
 * It is not possible to define a color that is outside the color spectrum for
 * the ILI93XX driver, hence use a dark color as invalid color.
 */
#define GFX_COLOR_INVALID       GFX_COLOR(1, 2, 3)

#define GFX_COLOR_TRANSPARENT   GFX_COLOR(254, 0, 0)

/**
 * \brief Initialize the ili93xx display controller
 *
 * This function will be called when calling \ref gfx_init.
 * It will draw a black background to the display and enable the
 * display backlight if available.
 */
void gfx_ili93xx_init(void);

/**
 * \brief Generate native color value from R/G/B values.
 *
 * Converts 8-bit R/G/B values to a color value native to the display.
 *
 * The macro \ref GFX_COLOR does the same, only allows the preprocessor to
 * handle the calculations.
 *
 * \param r 8-bit red value.
 * \param g 8-bit green value.
 * \param b 8-bit blue value.
 *
 * \return Color value in display native format.
 */
gfx_color_t gfx_ili93xx_color(uint8_t r, uint8_t g, uint8_t b);

/**
 * \brief Get the color of a pixel on the display.
 *
 * \param x X coordinate of the pixel to be sampled.
 * \param y Y coordinate of the pixel to be sampled.
 *
 * \return Color value of the pixel at (x, y) in display native format,
 * or #GFX_COLOR_INVALID if outside the clipping region.
 */
gfx_color_t gfx_ili93xx_get_pixel(gfx_coord_t x, gfx_coord_t y);

/**
 * \brief Draw a single pixel on the screen
 *
 * Draw a single pixel on screen setting top and bottom limits.
 * If outside the clipping region, nothing is drawn.
 *
 * \param x X coordinate of the pixel to be drawn.
 * \param y Y coordinate of the pixel to be drawn.
 * \param color Color value of the pixel in display native format.
 */
void gfx_ili93xx_draw_pixel(gfx_coord_t x, gfx_coord_t y, gfx_color_t color);

/**
 * \brief Draw a single pixel on the screen
 *
 * This function draws a single pixel on screen only setting top limit
 * which makes it more suitable for line drawing.
 * If outside the clipping region, nothing is drawn.
 *
 * \param x X coordinate of the pixel to be drawn.
 * \param y Y coordinate of the pixel to be drawn.
 * \param color Color value of the pixel in display native format.
 */
void gfx_ili93xx_draw_line_pixel(gfx_coord_t x, gfx_coord_t y,
		gfx_color_t color);

/**
 * \brief Set display orientation
 *
 * Set the display orientation
 *
 * \param flags
 */
void gfx_ili93xx_set_orientation(uint8_t flags);

/**
 * ILI93XX display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_draw_horizontal_line
 */
#define gfx_draw_horizontal_line(x, y, length, color)\
	gfx_generic_draw_horizontal_line(x, y, length, color)

/**
 * ILI93XX display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_draw_vertical_line
 */
#define gfx_draw_vertical_line(x, y, length, color)\
	gfx_generic_draw_vertical_line(x, y, length, color)

/**
 * ILI93XX display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_draw_line
 */
#define gfx_draw_line(x1, y1, x2, y2, color)\
	gfx_generic_draw_line(x1, y1, x2, y2, color)

/**
 * ILI93XX display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_draw_rect
 */
#define gfx_draw_rect(x, y, width, height, color)\
	gfx_generic_draw_rect(x, y, width, height, color)

/**
 * ILI93XX display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_draw_filled_rect
 */
#define gfx_draw_filled_rect(x, y, width, height, color)\
	gfx_generic_draw_filled_rect(x, y, width, height, color)

/**
 * ILI93XX display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_draw_circle
 */
#define gfx_draw_circle(x, y, radius, color, octant_mask)\
	gfx_generic_draw_circle(x, y, radius, color, octant_mask)

/**
 * ILI93XX display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_draw_filled_circle
 */
#define gfx_draw_filled_circle(x, y, radius, color, quadrant_mask)\
	gfx_generic_draw_filled_circle(x, y, radius, color,\
		quadrant_mask)

/**
 * ILI93XX display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_get_pixmap
 */
#define gfx_get_pixmap(pixmap, map_width, map_x, map_y, x, y, width, height)\
	gfx_generic_get_pixmap(pixmap, map_width, map_x, map_y, x, y,\
		width, height)

/**
 * ILI93XX display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_put_pixmap
 */
#define gfx_put_pixmap(pixmap, map_width, map_x, map_y, x, y, width, height)\
	gfx_generic_put_pixmap(pixmap, map_width, map_x, map_y, x, y,\
		width, height)

/**
 * ILI93XX display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_put_bitmap
 */
#define gfx_put_bitmap(bmp, map_x, map_y, x, y, width, height)\
	gfx_generic_put_bitmap(bmp, map_x, map_y, x, y, width, height)

/**
 * ILI93XX display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_draw_bitmap_tiled
 */
#define gfx_draw_bitmap_tiled(bmp, x1, y1, x2, y2, tile_origin_x,\
			tile_origin_y)\
	gfx_generic_draw_bitmap_tiled(bmp, x1, y1, x2, y2,\
		tile_origin_x, tile_origin_y)

/**
 * ILI93XX display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_draw_bitmap
 */
#define gfx_draw_bitmap(bmp, x, y) gfx_generic_draw_bitmap(bmp, x, y)

/**
 * ILI93XX display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_set_ext_handler
 */
#define gfx_set_ext_handler(ext_draw_handler)\
	gfx_generic_set_ext_handler(ext_draw_handler)

/**
 * ILI93XX display driver specific function, see
 * \ref ili93xx_duplicate_pixel
 */
#define gfx_duplicate_pixel(color, count) ili93xx_duplicate_pixel(color, count)

/**
 * ILI93XX display driver specific function, see
 * \ref gfx_ili93xx_get_pixel
 */
#define gfx_get_pixel(x, y) gfx_ili93xx_get_pixel(x, y)

/**
 * ILI93XX display driver specific function, see
 * \ref gfx_ili93xx_draw_pixel
 */
#define gfx_draw_pixel(x, y, color) gfx_ili93xx_draw_pixel(x, y, color)

/**
 * ILI93XX display driver specific function, see
 * \ref gfx_ili93xx_draw_line_pixel
 */
#define gfx_draw_line_pixel(x, y, color) gfx_ili93xx_draw_line_pixel(x, y,\
		color)

/**
 * ILI93XX display driver specific function, see
 * \ref ili93xx_set_top_left_limit
 */
#define gfx_set_top_left_limit(x, y) ili93xx_set_top_left_limit(x, y)

/**
 * ILI93XX display driver specific function, see
 * \ref ili93xx_set_bottom_right_limit
 */
#define gfx_set_bottom_right_limit(x, y) ili93xx_set_bottom_right_limit(x, y)

/**
 * ILI93XX display driver specific function, see
 * \ref ili93xx_set_limits
 */
#define gfx_set_limits(x1, y1, x2, y2) ili93xx_set_limits(x1, y1, x2, y2)

/**
 * ILI93XX display driver specific function, see
 * \ref ili93xx_copy_pixels_to_screen
 */
#define gfx_copy_pixels_to_screen(pixels, count)\
	ili93xx_copy_pixels_to_screen(pixels, count)

/**
 * ILI93XX display driver specific function, see
 * \ref ili93xx_copy_pixels_from_screen
 */
#define gfx_copy_pixels_from_screen(pixels, count)\
	ili93xx_copy_pixels_from_screen(pixels, count)

/**
 * ILI93XX display driver specific function available for ATmega and ATXmega
 * devices, see \ref ili93xx_copy_progmem_pixels_to_screen
 */
#define gfx_copy_progmem_pixels_to_screen(pixels, count)\
	ili93xx_copy_raw_pixel_24bits_to_screen(pixels, count)

/**
 * ILI93XX display driver specific function, see
 * \ref gfx_ili93xx_color
 */
#define gfx_color(r, g, b) gfx_ili93xx_color(r, g, b)

/**
 * ILI93XX display driver specific function, see
 * \ref gfx_ili93xx_set_orientation
 */
 #define gfx_set_orientation(flags) gfx_ili93xx_set_orientation(flags)

/**
 * ILI93XX display driver specific function, see
 * \ref gfx_ili93xx_init
 */
#define gfx_init() gfx_ili93xx_init()

/**
 * ILI93XX display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_sync
 */
#define gfx_sync() gfx_generic_sync()

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* GFX_ILI93XX_H_INCLUDED */
