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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef GFX_HX8347A_ET024006DH_EBI_H_INCLUDED
#define GFX_HX8347A_ET024006DH_EBI_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "et024006dhu.h"

/**
 * \ingroup gfx_group
 * \defgroup gfx_hx8347a_et024006dhu_ebi ET024006DHU display using HX8347A display controller over EBI
 *
 * This is hardware specific configuration that configures the graphical
 * service for use with the ET024006DHU TFT display. All the drawing
 * functionality in this configuration is provided by the \ref gfx_generic
 * driver. This configuration includes information about the panel size, data
 * type used for coordinates and color and functionality to convert RGB color
 * to the color format native to the display.
 *
 * @{
 */

/* Panel information */
#define GFX_PANELWIDTH   ET024006_WIDTH
#define GFX_PANELHEIGHT  ET024006_HEIGHT

typedef et024006_color_t gfx_color_t;
typedef uint16_t         gfx_coord_t;

/* This macro generates a 16-bit native color for the display from a
 * 24-bit RGB value
 */
#define GFX_COLOR(r, g, b) \
	((((uint16_t)b) >> 3) |\
	((((uint16_t)g) << 3) & 0x07E0) |\
	((((uint16_t)r) << 8) & 0xf800))

#define GFX_COLOR_INVALID       GFX_COLOR(0, 0, 0)
#define GFX_COLOR_TRANSPARENT   GFX_COLOR(254, 0, 0)

/**
 * \brief Initialize the et024006dhu display controller
 *
 * This function will be called when calling \ref gfx_init.
 * It will draw a black bacground to the display and enable the
 * display backlight if available.
 */
void gfx_et024006dhu_init(void);

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
gfx_color_t gfx_et024006dhu_color(uint8_t r, uint8_t g, uint8_t b);

/**
 * \brief Get the color of a pixel on the display.
 *
 * \param x X coordinate of the pixel to be sampled.
 * \param y Y coordinate of the pixel to be sampled.
 *
 * \return Color value of the pixel at (x, y) in display native format,
 * or #GFX_COLOR_INVALID if outside the clipping region.
 */
gfx_color_t gfx_et024006dhu_get_pixel(gfx_coord_t x, gfx_coord_t y);

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
void gfx_et024006dhu_draw_pixel(gfx_coord_t x, gfx_coord_t y, gfx_color_t color);

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
void gfx_et024006dhu_draw_line_pixel(gfx_coord_t x, gfx_coord_t y,
		gfx_color_t color);

/**
 * \brief Set display orientation
 *
 * Set the display orientation
 *
 * \param flags
 */
void gfx_et024006dhu_set_orientation(uint8_t flags);

/**
 * ET024006DHU display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_draw_horizontal_line
 */
#define gfx_draw_horizontal_line(x, y, length, color)\
	gfx_generic_draw_horizontal_line(x, y, length, color)

/**
 * ET024006DHU display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_draw_vertical_line
 */
#define gfx_draw_vertical_line(x, y, length, color)\
	gfx_generic_draw_vertical_line(x, y, length, color)

/**
 * ET024006DHU display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_draw_line
 */
#define gfx_draw_line(x1, y1, x2, y2, color)\
	gfx_generic_draw_line(x1, y1, x2, y2, color)

/**
 * ET024006DHU display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_draw_rect
 */
#define gfx_draw_rect(x, y, width, height, color)\
	gfx_generic_draw_rect(x, y, width, height, color)

/**
 * ET024006DHU display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_draw_filled_rect
 */
#define gfx_draw_filled_rect(x, y, width, height, color)\
	gfx_generic_draw_filled_rect(x, y, width, height, color)

/**
 * ET024006DHU display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_draw_circle
 */
#define gfx_draw_circle(x, y, radius, color, octant_mask)\
	gfx_generic_draw_circle(x, y, radius, color, octant_mask)

/**
 * ET024006DHU display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_draw_filled_circle
 */
#define gfx_draw_filled_circle(x, y, radius, color, quadrant_mask)\
	gfx_generic_draw_filled_circle(x, y, radius, color,\
		quadrant_mask)

/**
 * ET024006DHU display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_get_pixmap
 */
#define gfx_get_pixmap(pixmap, map_width, map_x, map_y, x, y, width, height)\
	gfx_generic_get_pixmap(pixmap, map_width, map_x, map_y, x, y,\
		width, height)

/**
 * ET024006DHU display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_put_pixmap
 */
#define gfx_put_pixmap(pixmap, map_width, map_x, map_y, x, y, width, height)\
	gfx_generic_put_pixmap(pixmap, map_width, map_x, map_y, x, y,\
		width, height)

/**
 * ET024006DHU display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_put_bitmap
 */
#define gfx_put_bitmap(bmp, map_x, map_y, x, y, width, height)\
	gfx_generic_put_bitmap(bmp, map_x, map_y, x, y, width, height)

/**
 * ET024006DHU display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_draw_bitmap_tiled
 */
#define gfx_draw_bitmap_tiled(bmp, x1, y1, x2, y2, tile_origin_x,\
			tile_origin_y)\
	gfx_generic_draw_bitmap_tiled(bmp, x1, y1, x2, y2,\
		tile_origin_x, tile_origin_y)

/**
 * ET024006DHU display driver uses generic gfx implementation for this function. See
 * \ref gfx_generic_draw_bitmap
 */
#define gfx_draw_bitmap(bmp, x, y)\
		gfx_generic_draw_bitmap(bmp, x, y)

/**
 * ET024006DHU display driver specific function, see
 * \ref et024006_DuplicatePixel
 */
#define gfx_duplicate_pixel(color, count)\
		et024006_DuplicatePixel(color, count)

/**
 * ET024006DHU display driver specific function, see
 * \ref gfx_et024006dhu_get_pixel
 */
#define gfx_get_pixel(x, y)\
		gfx_et024006dhu_get_pixel(x, y)

/**
 * ET024006DHU display driver specific function, see
 * \ref gfx_et024006dhu_draw_pixel
 */
#define gfx_draw_pixel(x, y, color)\
		gfx_et024006dhu_draw_pixel(x, y, color)

/**
 * ET024006DHU display driver specific function, see
 * \ref gfx_et024006dhu_draw_line_pixel
 */
#define gfx_draw_line_pixel(x, y, color)\
		gfx_et024006dhu_draw_line_pixel(x, y, color)

/**
 * ET024006DHU display driver specific function, see
 * \ref et024006_SetQuickLimits
 */
#define gfx_set_top_left_limit(x, y)\
		et024006_SetQuickLimits(x, y)

/**
 * ET024006DHU display driver specific function, see
 * \ref et024006_SetQuickLimits2
 */
#define gfx_set_bottom_right_limit(x, y)\
		et024006_SetQuickLimits2(x, y)

/**
 * ET024006DHU display driver specific function, see
 * \ref et024006_SetLimits
 */
#define gfx_set_limits(x1, y1, x2, y2)\
		et024006_SetLimits(x1, y1, x2, y2)

/**
 * ET024006DHU display driver specific function, see
 * \ref et024006_CopyPixelsToScreen
 */
#define gfx_copy_pixels_to_screen(pixels, count)\
		et024006_CopyPixelsToScreen(pixels, count)

/**
 * ET024006DHU display driver specific function, see
 * \ref et024006_CopyPixelsFromScreen
 */
#define gfx_copy_pixels_from_screen(pixels, count)\
		et024006_CopyPixelsFromScreen(pixels, count)

/**
 * ET024006DHU display driver specific function available for ATmega and ATXmega
 * devices, see \ref et024006_CopyPixelsToScreen
 */
#define gfx_copy_progmem_pixels_to_screen(pixels, count)\
		et024006_CopyPixelsToScreen(pixels, count)

/**
 * ET024006DHU display driver specific function, see
 * \ref gfx_et024006dhu_color
 */
#define gfx_color(r, g, b)\
		gfx_et024006dhu_color(r, g, b)

/**
 * ET024006DHU display driver specific function, see
 * \ref gfx_et024006dhu_set_orientation
 */
 #define gfx_set_orientation(flags)\
		gfx_et024006dhu_set_orientation(flags)

/**
 * ET024006DHU display driver specific function, see
 * \ref gfx_et024006dhu_init()
 */
#define gfx_init() gfx_et024006dhu_init()

/*! @} */

#ifdef __cplusplus
}
#endif

#endif /* GFX_HX8347A_ET024006DH_EBI_H_INCLUDED */
