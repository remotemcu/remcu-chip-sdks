/**
 * \file
 *
 * \brief Graphical library API header file
 *
 * This files includes the correct header files for the graphics service
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef GFX_H_INCLUDED
#define GFX_H_INCLUDED

#include <assert.h>
#include <compiler.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* UC3 & ARM does not have PROGMEM, declare PROGMEM as const variables */
#ifndef PROGMEM_DECLARE
#  define PROGMEM_DECLARE(type, name) const type name
#  define PROGMEM_T const
#  define PROGMEM_PTR_T const *
#  define PROGMEM_READ_BYTE(x) *(x)
#endif

#if defined(CONF_GFX_HX8347A_ET024006DHU)
# include "gfx_hx8347a_et024006dhu.h"
# include "gfx_generic.h"
# define CONF_GFX_USE_CLIPPING
#elif defined(CONF_GFX_ILI9341_SDT028ATFT)
# include "gfx_ili9341_sdt028atft.h"
# include "gfx_generic.h"
# define CONF_GFX_USE_CLIPPING
#elif defined(CONF_GFX_HX8347A_ET024006DHU_EBI)
# include "gfx_hx8347a_et024006dhu_ebi.h"
# include "gfx_generic.h"
# define CONF_GFX_USE_CLIPPING
#elif defined(CONF_GFX_ILI9325_FTM280C34D)
# include "gfx_ili9325_ftm280c34d.h"
# include "gfx_generic.h"
#elif defined(CONF_GFX_ILI93XX)
# include "gfx_ili93xx.h"
# include "gfx_generic.h"
#elif defined(CONF_GFX_ILI9488)
# include "gfx_ili9488_90_00028_a0.h"
# include "gfx_generic.h"
#define CONF_GFX_USE_CLIPPING
#else
#  error "Configuration for display controller/panel not selected"
#endif

/**
 * \defgroup gfx_group Graphical display system
 * This service provides an interface to drawing graphics on a graphical display
 *
 * The graphics service consists of the following:
 * - Display driver interface (gfx.h)
 * - General graphics drawing primitives (gfx_generic.h)
 * - Display and controller specific implementation (ex.
 * gfx_hx8347a_et024006dhu.h)
 * - Display controller driver (ex. hx8347a.c/h)
 *
 * The display driver interface provides an general interface to be used by
 * the application or by libraries.
 *
 * The generic drawing primitives is a library  of functions for drawing
 * graphics primitives such as lines, rectangles and circles. It uses
 * other functions implemented by the display driver for drawing the
 * primitives. The implementation of these functions can optionally be
 * used by a display driver, but if the hardware of the display allows
 * faster handling of any of the primitives, the display driver can
 * implement it directly.
 *
 * The display specific drivers provides an interface to the graphical
 * display via the display controller. It implements the low level
 * communication with the display hardware, putting pixels on the display
 * and drawing primitives such as lines, circles and rectangles. Depending
 * on the display driver implementation, drawing the graphics primitives
 * might be handled by the generic graphics drawing primitives rather than the
 * display driver itself.
 *
 * @{
 */

/** \name Driver-specific Definitions */
/** @{ */

/**
 * \typedef gfx_color_t
 * \brief Data type for color values native to the display.
 */

/**
 * \typedef gfx_coord_t
 * \brief Data type representing a coordinate on the screen.
 */

/**
 * \def GFX_COLOR(r, g, b)
 * \brief Generate a display-native color value from constant RGB
 * components.
 *
 * This macro does the same job as \ref gfx_color(), except that the RGB
 * values must be constant, and that it is usable as a static
 * initializer.
 */

/**
 * \def GFX_COLOR_INVALID
 * \brief Value returned by \ref gfx_get_pixel() for pixels outside clipping
 * region.
 */

/**
 * \def GFX_COLOR_TRANSPARENT
 * \brief Value used as input to font functions to give a transparent background
 * region.
 */

/** \name Standard Color Definitions */
/** @{ */

#define GFX_COLOR_BLACK      GFX_COLOR(  0,   0,   0)
#define GFX_COLOR_WHITE      GFX_COLOR(255, 255, 255)
#define GFX_COLOR_GRAY       GFX_COLOR(128, 128, 128)
#define GFX_COLOR_RED        GFX_COLOR(255,   0,   0)
#define GFX_COLOR_DK_RED     GFX_COLOR(128,   0,   0)
#define GFX_COLOR_GREEN      GFX_COLOR(  0, 255,   0)
#define GFX_COLOR_DK_GREEN   GFX_COLOR(  0, 128,   0)
#define GFX_COLOR_BLUE       GFX_COLOR(  0,   0, 255)
#define GFX_COLOR_DK_BLUE    GFX_COLOR(  0,   0, 128)
#define GFX_COLOR_MAGENTA    GFX_COLOR(255,   0, 255)
#define GFX_COLOR_DK_MAGENTA GFX_COLOR(128,   0, 128)
#define GFX_COLOR_YELLOW     GFX_COLOR(255, 255,   0)
#define GFX_COLOR_DK_YELLOW  GFX_COLOR(128, 128,   0)
#define GFX_COLOR_CYAN       GFX_COLOR(  0, 255, 255)
#define GFX_COLOR_DK_CYAN    GFX_COLOR(  0, 128, 128)

/** @} */

/** @} */

/** \name Circle Sector Definitions */
/** @{ */

/** Bitmask for drawing circle octant 0. */
#define GFX_OCTANT0 (1 << 0)

/** Bitmask for drawing circle octant 1. */
#define GFX_OCTANT1 (1 << 1)

/** Bitmask for drawing circle octant 2. */
#define GFX_OCTANT2 (1 << 2)

/** Bitmask for drawing circle octant 3. */
#define GFX_OCTANT3 (1 << 3)

/** Bitmask for drawing circle octant 4. */
#define GFX_OCTANT4 (1 << 4)

/** Bitmask for drawing circle octant 5. */
#define GFX_OCTANT5 (1 << 5)

/** Bitmask for drawing circle octant 6. */
#define GFX_OCTANT6 (1 << 6)

/** Bitmask for drawing circle octant 7. */
#define GFX_OCTANT7 (1 << 7)

/** Bitmask for drawing circle quadrant 0. */
#define GFX_QUADRANT0 (GFX_OCTANT0 | GFX_OCTANT1)

/** Bitmask for drawing circle quadrant 1. */
#define GFX_QUADRANT1 (GFX_OCTANT2 | GFX_OCTANT3)

/** Bitmask for drawing circle quadrant 2. */
#define GFX_QUADRANT2 (GFX_OCTANT4 | GFX_OCTANT5)

/** Bitmask for drawing circle quadrant 3. */
#define GFX_QUADRANT3 (GFX_OCTANT6 | GFX_OCTANT7)

/** Bitmask for drawing left half of circle. */
#define GFX_LEFTHALF (GFX_QUADRANT3 | GFX_QUADRANT0)

/** Bitmask for drawing top half of circle. */
#define GFX_TOPHALF (GFX_QUADRANT0 | GFX_QUADRANT1)

/** Bitmask for drawing right half of circle. */
#define GFX_RIGHTHALF (GFX_QUADRANT1 | GFX_QUADRANT2)

/** Bitmask for drawing bottom half of circle. */
#define GFX_BOTTOMHALF (GFX_QUADRANT2 | GFX_QUADRANT3)

/** Bitmask for drawing whole circle. */
#define GFX_WHOLE 0xFF

/** @} */

/** \name Flags for gfx_set_orientation() */
/*@{ */
/** Bitmask for flipping X for \ref gfx_set_orientation() */
#define GFX_FLIP_X 1

/** Bitmask for flipping Y for \ref gfx_set_orientation() */
#define GFX_FLIP_Y 2

/** Bitmask for swapping X and Y for \ref gfx_set_orientation() */
#define GFX_SWITCH_XY 4

/** @} */

/**
 * \name Screen geometry and clipping variables
 * \internal
 *
 * These global variables should not be accessed directly. They cannot be
 * marked as private/static since they are shared within multiple C files
 * of the graphics drivers.
 *
 * Use \ref gfx_set_clipping() to change clipping region.
 */

/** @{ */
#if defined(CONF_GFX_USE_CLIPPING) || defined(__DOXYGEN__)
extern gfx_coord_t gfx_min_x;   /**< Minimum X of current clipping region. */
extern gfx_coord_t gfx_min_y;   /**< Maximum Y of current clipping region. */
extern gfx_coord_t gfx_max_x;   /**< Minimum X of current clipping region. */
extern gfx_coord_t gfx_max_y;   /**< Maximum Y of current clipping region. */
#endif

extern gfx_coord_t gfx_width;  /**< Current width of screen. */
extern gfx_coord_t gfx_height; /**< Current height of screen. */
/** @} */

#if defined(__DOXYGEN__)

/**
 * \name Bitmap functions and structures
 */

/** @{ */

/**
 * \brief Draw a bitmap
 *
 * Draw a bitmap to the screen on the given display coordinates
 *
 * \param bmp Pointer to bitmap \ref gfx_bitmap
 * \param x   Display X coordinate
 * \param y   Display Y coordinate
 */
void gfx_draw_bitmap(const struct gfx_bitmap *bmp, gfx_coord_t x,
		gfx_coord_t y);

/**
 * \brief Draw a bitmap to the screen tiled to cover the output area.
 *
 * The function starts at the tile origin and searches to find the coordinate
 * closest to the top left of the output area that is a multiple of the bitmap
 * width/height. It then draws the bitmap as many times as needed to cover
 * the entire output area.
 *
 * To draw a bitmap tiled on the entire screen, regardless of the bitmap
 * size, the function can be used like this:
 *
 * \code
	gfx_draw_bitmap_tiled(bmp, 0, 0, gfx_get_width(), gfx_get_height(), 0, ,0);
\endcode
 *
 * The function is used by the "window system" to redraw the
 * background of a parent window when a transparent child window needs to be
 * redrawn. In this case the full parent window does not need redrawing,
 * only the area of the parent window that is under the child window.
 * The tiles of the background image will for all windows start at the top left
 * corner of the window, so the function is used like this:
 *
 * \code
	gfx_draw_bitmap_tiled(parent_background_bmp,
	                      child_window_x1, child_window_y1,
	                      child_window_x2, child_window_y2,
	                      parent_window_origin_x, parent_window_origin_y);
\endcode
 *
 * \note If CONF_GFX_USE_CLIPPING is used, the output is clipped to the
 * output area and nothing will be drawn outside the output area.
 *
 * \param bmp           Pointer to bitmap
 * \param x1            Output area left coordinate
 * \param y1            Output area top coordinate
 * \param x2            Output area right coordinate
 * \param y2            Output area bottom coordinate
 * \param tile_origin_x Tile origin left coordinate
 * \param tile_origin_y Tile origin top coordinate
 */
void gfx_draw_bitmap_tiled(const struct gfx_bitmap *bmp, gfx_coord_t x1,
		gfx_coord_t y1, gfx_coord_t x2, gfx_coord_t y2,
		gfx_coord_t tile_origin_x, gfx_coord_t tile_origin_y);

/**
 * \brief Write a rectangular block of pixels from a bitmap to
 * the screen.
 *
 * This function draws a subset of a bitmap to the screen. The subset
 * is given by (map_x, map_y, width, height), and is outputted
 * to the screen at the screen coordinates (x, y).
 *
 * If the area to write is outside the clipping region, those pixels
 * will not be written.
 *
 * \note This function fails if the width or height is negative or the
 *       pixel rectangle is outside the pixmap buffer extents. Clipping
 *       is only performed on the screen, not inside the pixmap buffer itself.
 *
 * \note There is no checking if the pixel rectangle exceeds the bottom of
 *       the pixmap buffer.
 *
 * \param bmp       Pointer to bitmap.
 * \param map_x     X coordinate inside pixel buffer.
 * \param map_y     Y coordinate inside pixel buffer.
 * \param x         X coordinate on screen.
 * \param y         Y coordinate on screen.
 * \param width     Width of pixel rectangle to copy.
 * \param height    Height of pixel rectangle to copy.
 */
void gfx_put_bitmap(const struct gfx_bitmap *bmp, gfx_coord_t map_x,
		gfx_coord_t map_y, gfx_coord_t x, gfx_coord_t y,
		gfx_coord_t width,
		gfx_coord_t height);

/** @} */

/** \name Display driver management functions */
/** @{ */

/**
 * \brief Synchronize access to the display
 *
 * In case of a graphics driver implementation that queues graphics
 * operations, this function will make sure all pending operations are
 * completed before exiting. That way, if you want to read pixels from
 * the display, you can be sure that the display information is fresh
 * and updated. For implementations that does not queue operations,
 * this function may do nothing, but for portability it should always be
 * called before reading pixels, or performing other operations which
 * rely on all pending drawing operations having actually been
 * completed.
 */
void gfx_sync(void);

/** @} */

/** \name Display Geometry */
/** @{ */

/**
 * \brief Change display orientation
 *
 * Changes the display orientation for displays that support this.
 * Check the driver specific documentation if this is supported.
 *
 * The following masks are available and can be ORed together:
 * - #GFX_FLIP_X Flip X axis
 * - #GFX_FLIP_Y Flip Y axis
 * - #GFX_SWITCH_XY Switch X/Y
 *
 * Note that rotating the screen 90 degrees means switching X/Y _and_
 * mirroring one of the axes. It is not enough to just switch X/Y.
 *
 * \param flags A bitmask of which axes to flip and/or switch.
 */
void gfx_set_orientation(uint8_t flags);

/**
 * \brief Return the current width of the screen
 *
 * Return the current width of the screen for the current orientation. Screen
 * can be rotated runtime on supported displays with \ref gfx_set_orientation.
 *
 * \return Width of the screen in pixels.
 */
gfx_coord_t gfx_get_width(void);

/**
 * \brief Return the current height of the screen
 *
 * Return the current height of the screen for the current orientation. Screen
 * can be rotated runtime on supported displays with \ref gfx_set_orientation.
 *
 * \return Height of the screen in pixels.
 */
gfx_coord_t gfx_get_height(void);

/**
 * \name Display Clipping
 *
 * The display driver uses software and hardware clipping. In the graphics
 * drivers software clipping is referred to as clipping and hardware clipping
 * as limits.
 *
 * Software clipping is used to ensure that nothing outside the set
 * region is draw to the screen by any of the drawing functions. Eliminating
 * unwanted drawing to the display will give a higher performance on
 * displays which has a low bandwidth from the CPU.
 * Software is enabled by the CONF_GFX_USE_CLIPPING configuration symbol.
 * Clipping region is set with the \ref gfx_set_clipping() function.
 *
 * Hardware clipping is used in the supported display drivers to efficiently
 * draw primitives on a subset of the display. Example: when drawing a
 * filled rectangle the limits is set to the size of the rectangle, and the
 * driver sends the correct number of pixels to fill the entire rectangle.
 * Without hardware clipping/limits the driver will have to to move the
 * graphics ram (GRAM) position/pointer manually.
 * Hardware clipping/limits is not used like software clipping to eliminate
 * drawing outside a given region.
 * Hardware clipping is set with the \ref gfx_set_top_left_limit,
 * \ref gfx_set_bottom_right_limit and \ref gfx_set_limits functions.
 * In display drivers that do not use hardware clipping these functions
 * will not have any effect.
 */

/** @{ */

/**
 * \brief Set the clipping region
 *
 * Set the clipping region for all subsequent graphics operations.
 * Nothing will be drawn outside the clipping region. Clipping is handled
 * in software, and is enabled with CONF_GFX_USE_CLIPPING.
 *
 * \param min_x Left edge of region.
 * \param min_y Top edge of region.
 * \param max_x Right edge of region.
 * \param max_y Bottom edge of region.
 */
void gfx_set_clipping(gfx_coord_t min_x, gfx_coord_t min_y,
		gfx_coord_t max_x, gfx_coord_t max_y);

/**
 * \brief Set the top-left limit for the display.
 *
 * Set top-left clipping limit for displays that needs to set a hardware
 * clipping region.
 *
 * \param x Top left x coordinate.
 * \param y Top left y coordinate.
 */
void gfx_set_top_left_limit(gfx_coord_t x, gfx_coord_t y);

/**
 * \brief Set the bottom-right limit for the display.
 *
 * Set bottom-right clipping limit for displays that needs to set a hardware
 * clipping region.
 *
 * \param x Bottom right x coordinate.
 * \param y Bottom right y coordinate.
 */
void gfx_set_bottom_right_limit(gfx_coord_t x, gfx_coord_t y);

/**
 * \brief Set the limits for the display.
 *
 * Set clipping limit for displays that needs to set a hardware
 * clipping region.
 *
 * \param x1 Top left x coordinate.
 * \param y1 Top left y coordinate.
 * \param x2 Bottom right x coordinate.
 * \param y2 Bottom right y coordinate.
 */
void gfx_set_limits(gfx_coord_t x1, gfx_coord_t y1,
		gfx_coord_t x2, gfx_coord_t y2);

/** @} */

/** \name Low-level pixel drawing operations */
/** @{ */

/**
 * \brief Generate native color value from R/G/B values.
 *
 * Converts 8-bit R/G/B values to a color value native to the display.
 * The format of the resulting color value depends on the display.
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
gfx_color_t gfx_color(uint8_t r, uint8_t g, uint8_t b);

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
void gfx_draw_pixel(gfx_coord_t x, gfx_coord_t y, gfx_color_t color);

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
void gfx_draw_line_pixel(gfx_coord_t x, gfx_coord_t y, gfx_color_t color);

/**
 * \brief Get the color of a pixel on the display.
 *
 * \param x X coordinate of the pixel to be sampled.
 * \param y Y coordinate of the pixel to be sampled.
 *
 * \return Color value of the pixel at (x, y) in display native format,
 * or #GFX_COLOR_INVALID if outside the clipping region.
 */
gfx_color_t gfx_get_pixel(gfx_coord_t x, gfx_coord_t y);

/**
 * \brief Draw multiple pixels all having the same color.
 *
 * Draw \a count pixels using \a color within the current clipping
 * limits.
 *
 * \param color Color value in display native format.
 * \param count Number of times to write the color
 */
void gfx_duplicate_pixel(gfx_color_t color, uint32_t count);

/**
 * \brief Copy a block of pixels from data memory to screen.
 *
 * Copy pixels from RAM to the screen, given current limits.
 *
 * \param pixels An array of pixel values in display native format.
 * \param count Number of pixels to copy from the array.
 */
void gfx_copy_pixels_to_screen(const gfx_color_t *pixels, uint32_t count);

/**
 * \brief Copy a block of pixels from program memory to screen.
 *
 * Copy a block of pixels from program memory to screen, given current
 * limits.
 *
 * \param pixels An array of pixel values in display native format,
 *      stored in program (flash) memory.
 * \param count Number of pixels to copy from the array.
 */
void gfx_copy_progmem_pixels_to_screen(gfx_color_t PROGMEM_PTR_T pixels,
		uint32_t count);

/**
 * \brief Copy a block of pixels from screen to data memory.
 *
 * Copy a block of pixels from the screen into RAM, given current limits
 *
 * \param pixels Array into which the pixel values are to be stored.
 * \param count Number of pixels to copy into the array.
 */
void gfx_copy_pixels_from_screen(gfx_color_t *pixels, uint32_t count);

/**
 * \brief Set bitmap draw function with custom interface.
 *
 * Set bitmap draw function with customer interface. This allows to use the extended
 * draw functions defined by the application. For example, do the draw bitmap function
 * though a filesystem.
 *
 * \param gfx_ext_draw_handler Pointer to custom bitmap draw handler.
 */
void gfx_set_ext_handler(gfx_ext_draw_handler_t gfx_ext_draw_handler);

/** @} */

/** \name Graphics Drawing Primitives */
/** @{ */

/**
 * \def gfx_draw_horizontal_line(x, y, length, color)
 * \brief Draw a horizontal line, one pixel wide.
 *
 * \param  x          X coordinate of leftmost pixel.
 * \param  y          Y coordinate of the line.
 * \param  length     Length of the line in pixels.
 * \param  color      Color of the line, in display native format.
 */

/**
 * \def gfx_draw_vertical_line(x, y, length, color)
 * \brief Draw a vertical line, one pixel wide.
 *
 * \param  x          X coordinate of the line.
 * \param  y          Y coordinate of the topmost pixel.
 * \param  length     Length of the line in pixels.
 * \param  color      Color of the line, in display native format.
 */

/**
 * \def gfx_draw_line(x1, y1, x2, y2, color)
 * \brief Draw a line between two arbitrary points.
 *
 * \param  x1          Start X coordinate.
 * \param  y1          Start Y coordinate.
 * \param  x2          End X coordinate.
 * \param  y2          End Y coordinate.
 * \param  color       Color of the line, in display native format.
 */

/**
 * \def gfx_draw_rect(x, y, width, height, color)
 * \brief Draw an outline of a rectangle.
 *
 * \param  x           X coordinate of the left side.
 * \param  y           Y coordinate of the top side.
 * \param  width       Width of the rectangle.
 * \param  height      Height of the rectangle.
 * \param  color       Color of the rectangle, in display native format.
 */

/**
 * \def gfx_draw_filled_rect(x, y, width, height, color)
 * \brief Draw a filled rectangle.
 *
 * \param  x           X coordinate of the left side.
 * \param  y           Y coordinate of the top side.
 * \param  width       Width of the rectangle.
 * \param  height      Height of the rectangle.
 * \param  color       Color of the rectangle, in display native format.
 */

/**
 * \def gfx_draw_circle(x, y, radius, color, octant_mask)
 * \brief Draw an outline of a circle or arc.
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
 * \param  color       Circle color in display native format.
 * \param  octant_mask Bitmask indicating which octants to draw.
 */

/**
 * \def gfx_draw_filled_circle(x, y, radius, color, quadrant_mask)
 * \brief Draw a filled circle or sector.
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
 * \param  color       Circle color in display native format.
 * \param  quadrant_mask Bitmask indicating which quadrants to draw.
 */

/**
 * \def gfx_get_pixmap(pixmap, map_width, map_x,  map_y, x, y, width, height)
 * \brief Read a rectangular block of pixels from the screen into data
 * memory.
 *
 * If the area to read is outside the clipping region, those pixels will
 * not be read, and the corresponding data memory will be left
 * untouched.  Note that this function fails if width or height is
 * negative or the pixel rectangle is outside the pixmap buffer extents.
 * Clipping is only performed on the screen, not inside the pixmap
 * buffer itself.  Note that there is no checking if the pixel rectangle
 * exceeds the bottom of the pixmap buffer.
 *
 * \param  pixmap    Pointer to pixel buffer in data memory.
 * \param  map_width Width of the pixel buffer.
 * \param  map_x     X coordinate inside pixel buffer.
 * \param  map_y     Y coordinate inside pixel buffer.
 * \param  x         X coordinate on screen.
 * \param  y         Y coordinate on screen.
 * \param  width     Width of pixel rectangle to copy.
 * \param  height    Height of pixel rectangle to copy.
 */

/**
 * \def gfx_put_pixmap(pixmap, map_width, map_x, map_y, x, y, width, height);
 * \brief Write a rectangular block of pixels stored in data memory to
 * the screen.
 *
 * If the area to write is outside the clipping region, those pixels
 * will not be written.  Note that this function fails if the width or
 * height is negative or the pixel rectangle is outside the pixmap
 * buffer extents. Clipping is only performed on the screen, not inside
 * the pixmap buffer itself.  Note that there is no checking if the
 * pixel rectangle exceeds the bottom of the pixmap buffer.
 *
 * \param  pixmap    Pointer to pixel buffer in data memory.
 * \param  map_width Width of the pixel buffer.
 * \param  map_x     X coordinate inside pixel buffer.
 * \param  map_y     Y coordinate inside pixel buffer.
 * \param  x         X coordinate on screen.
 * \param  y         Y coordinate on screen.
 * \param  width     Width of pixel rectangle to copy.
 * \param  height    Height of pixel rectangle to copy.
 */

/** @} */

/** @} */

/**
 * \page gfx_quickstart Quick Start Guide for the graphics service
 *
 * This is the quick start guide for the \ref gfx_group "Graphics (GFX)
 * service", with step-by-step instructions on how to configure and use
 * it for a specific use case.
 *
 *
 * \section gfx_quickstart_basic Basic usage of the graphics service
 * This use case will demonstrate initializing the graphics service and then
 * drawing a red line on the screen from coordinate X=10, Y=10 to X=20, Y=20.
 *
 * \section gfx_basic_usage Usage steps
 * \subsection gfx_basic_usage_code Example code
 * Add to, e.g., the main function in the application C-file:
 * \code
	board_init();
	sysclk_init();
	gfx_init();
	gfx_draw_line(10, 10, 20, 20, GFX_COLOR(0xFF, 0, 0));
\endcode
 *
 * \subsection gfx_basic_usage Workflow
 * -# Initialize board IO:
 *  - \code board_init(); \endcode
 * -# Initialize clocks:
 *  - \code sysclk_init(); \endcode
 * -# Initialize graphics service
 *  - \code gfx_init(); \endcode
 *  - \note This will call the init function for the low level display
 * controller driver and initialize the screen to a white background.
 * -# Draw a red line from 10,10 to 20,20:
 * -  \code gfx_draw_line(10, 10, 20, 20, GFX_COLOR(0xFF, 0, 0)); \endcode
 * -  \attention This uses the \ref GFX_COLOR macro to convert a RGB
 *    (Red,Green,Blue)
 * value to a color value native to the display. In this case the color is
 * a constant, so we use the macro. If you need to create the color from a
 * non-constant value you must use the \ref gfx_color function to generate the
 * color.
 */

#else
	gfx_coord_t gfx_get_width(void);

	gfx_coord_t gfx_get_height(void);

	void gfx_set_clipping(gfx_coord_t min_x, gfx_coord_t min_y,
			gfx_coord_t max_x, gfx_coord_t max_y);
#endif

#ifdef __cplusplus
}
#endif

#endif /* GFX_H_INCLUDED */
