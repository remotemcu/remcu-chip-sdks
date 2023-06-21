/**
 * \file
 *
 * \brief Monochrome graphic library API header file
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
#ifndef GFX_MONO_H
#define GFX_MONO_H

#include <stdint.h>

#include "compiler.h"
#include "progmem.h"
#ifdef CONFIG_HAVE_HUGEMEM
# include "hugemem.h"
#endif

/**
 * \defgroup gfx_mono Monochrome graphical display system
 *
 * See \ref gfx_mono_quickstart.
 *
 * This library provides an interface to drawing graphics on monochrome
 * graphical displays
 *
 * The graphics drivers consists of the following:
 * - Display driver interface (gfx_mono.h)
 * - General graphics drawing primitives (gfx_mono_generic.h)
 * - Display specific implementation (ex. gfx_mono_c12832_a1z.h)
 *
 * The generic drawing primitives is a library of functions for drawing
 * graphics primitives such as lines, rectangles and circles. It uses other
 * functions implemented by the display driver for drawing the primitives. The
 * implementation of these functions can optionally be used by a display
 * driver, but if the hardware of the display allows faster handling of any of
 * the primitives, the display driver can implement it directly.
 *
 * The display specific drivers provides an interface to the graphical display.
 * It implements the low level communication with the display hardware, putting
 * pixels on the display and drawing primitives such as lines, circles and
 * rectangles. Depending on the display driver implementation, drawing the
 * graphics primitives might be handled by the generic graphics drawing
 * primitives rather than the display driver itself.
 *
 * \note The functions in the library are not interrupt safe.
 * @{
 */

typedef uint8_t gfx_mono_color_t;
typedef uint8_t gfx_coord_t;

/** Pixel operations */
enum gfx_mono_color {
	/** Pixel is cleared */
	GFX_PIXEL_CLR = 0,
	/** Pixel is set on screen (OR) */
	GFX_PIXEL_SET = 1,
	/** Pixel is XORed */
	GFX_PIXEL_XOR = 2,
};

/** Bitmap types */
enum gfx_mono_bitmap_type {
	/** Bitmap stored in SRAM */
	GFX_MONO_BITMAP_RAM,
	/** Bitmap stored in progmem */
	GFX_MONO_BITMAP_PROGMEM
};

/* Cannot be moved to top, as they use the bitmap and color enums. */
#ifdef USE_SDL
# include "gfx_mono_sdl.h"
#elif defined(GFX_MONO_C12832_A1Z)
# include "gfx_mono_c12832_a1z.h"
#elif defined(GFX_MONO_UG_2832HSWEG04)
# include "gfx_mono_ug_2832hsweg04.h"
#else
/* NULL driver by default */
# include "gfx_mono_null.h"
#endif
#include "gfx_mono_generic.h"

/** \name Circle Sector Definitions */
/** @{ */

/** Bitmask for drawing circle octant 0. */
#define GFX_OCTANT0     (1 << 0)
/** Bitmask for drawing circle octant 1. */
#define GFX_OCTANT1     (1 << 1)
/** Bitmask for drawing circle octant 2. */
#define GFX_OCTANT2     (1 << 2)
/** Bitmask for drawing circle octant 3. */
#define GFX_OCTANT3     (1 << 3)
/** Bitmask for drawing circle octant 4. */
#define GFX_OCTANT4     (1 << 4)
/** Bitmask for drawing circle octant 5. */
#define GFX_OCTANT5     (1 << 5)
/** Bitmask for drawing circle octant 6. */
#define GFX_OCTANT6     (1 << 6)
/** Bitmask for drawing circle octant 7. */
#define GFX_OCTANT7     (1 << 7)

/** Bitmask for drawing circle quadrant 0. */
#define GFX_QUADRANT0   (GFX_OCTANT0 | GFX_OCTANT1)
/** Bitmask for drawing circle quadrant 1. */
#define GFX_QUADRANT1   (GFX_OCTANT2 | GFX_OCTANT3)
/** Bitmask for drawing circle quadrant 2. */
#define GFX_QUADRANT2   (GFX_OCTANT4 | GFX_OCTANT5)
/** Bitmask for drawing circle quadrant 3. */
#define GFX_QUADRANT3   (GFX_OCTANT6 | GFX_OCTANT7)

/** Bitmask for drawing left half of circle. */
#define GFX_LEFTHALF    (GFX_QUADRANT3 | GFX_QUADRANT0)
/** Bitmask for drawing top half of circle. */
#define GFX_TOPHALF     (GFX_QUADRANT0 | GFX_QUADRANT1)
/** Bitmask for drawing right half of circle. */
#define GFX_RIGHTHALF   (GFX_QUADRANT1 | GFX_QUADRANT2)
/** Bitmask for drawing bottom half of circle. */
#define GFX_BOTTOMHALF  (GFX_QUADRANT2 | GFX_QUADRANT3)

/** Bitmask for drawing whole circle. */
#define GFX_WHOLE       0xFF

/** @} */

/** \name Graphic Drawing Primitives */
/** @{ */

/**
 * \def gfx_mono_draw_horizontal_line(x, y, length, color)
 * \brief Draw a horizontal line, one pixel wide.
 *
 * \param  x          X coordinate of leftmost pixel.
 * \param  y          Y coordinate of the line.
 * \param  length     Length of the line in pixels.
 * \param  color      Pixel operation of the line.
 */

/**
 * \def gfx_mono_draw_vertical_line(x, y, length, color)
 * \brief Draw a vertical line, one pixel wide.
 *
 * \param  x          X coordinate of the line.
 * \param  y          Y coordinate of the topmost pixel.
 * \param  length     Length of the line in pixels.
 * \param  color      Pixel operation of the line.
 */

/**
 * \def gfx_mono_draw_line(x1, y1, x2, y2, color)
 * \brief Draw a line between two arbitrary points.
 *
 * \param  x1          Start X coordinate.
 * \param  y1          Start Y coordinate.
 * \param  x2          End X coordinate.
 * \param  y2          End Y coordinate.
 * \param  color       Pixel operation of the line.
 */

/**
 * \def gfx_mono_draw_rect(x, y, width, height, color)
 * \brief Draw an outline of a rectangle.
 *
 * \param  x           X coordinate of the left side.
 * \param  y           Y coordinate of the top side.
 * \param  width       Width of the rectangle.
 * \param  height      Height of the rectangle.
 * \param  color       Pixel operation of the line.
 */

/**
 * \def gfx_mono_draw_filled_rect(x, y, width, height, color)
 * \brief Draw a filled rectangle.
 *
 * \param  x           X coordinate of the left side.
 * \param  y           Y coordinate of the top side.
 * \param  width       Width of the rectangle.
 * \param  height      Height of the rectangle.
 * \param  color       Pixel operation of the line
 */

/**
 * \def gfx_mono_draw_circle(x, y, radius, color, octant_mask)
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
 * \param  color       Pixel operation.
 * \param  octant_mask Bitmask indicating which octants to draw.
 */

/**
 * \def gfx_mono_draw_filled_circle(x, y, radius, color, quadrant_mask)
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
 * \param  color       Pixel operation.
 * \param  quadrant_mask Bitmask indicating which quadrants to draw.
 */

/** @} */

/** @} */

/**
 * \page gfx_mono_quickstart Quick Start Guide for the mono graphics service
 *
 * This is the quick start guide for the \ref gfx_mono "Monochrome Graphics service",
 * with step-by-step instructions on how to configure and use it for a specific
 * use case.
 *
 * \section gfx_mono_quickstart_basic Basic usage of the graphics service
 * This use case will demonstrate initializing the mono graphics service and
 * then draw a black line on the screen from coordinates X=10, Y=10 to X=20,
 * Y=20.
 *
 * \section gfx_mono_basic_usage Usage steps
 * \subsection gfx_mono_basic_usage_code Example code
 * Add to, e.g., the main function in the application C-file:
 * \code
	board_init();
	sysclk_init();
	gfx_mono_init();
	gfx_mono_draw_line(10, 10, 20, 20, GFX_PIXEL_SET);
\endcode
 *
 * \subsection gfx_mono_basic_usage Workflow
 * -# Initialize board IO:
 *  - \code board_init(); \endcode
 * -# Initialize clocks:
 *  - \code sysclk_init(); \endcode
 * -# Initialize monochrome graphics service
 *  - \code gfx_mono_init(); \endcode
 *  - \note This will call the init function for the low level display
 *          controller driver and intialize the screen to a cleared background.
 * -# Draw a line from 10,10 to 20,20:
 * -  \code gfx_mono_draw_line(10, 10, 20, 20, GFX_PIXEL_SET); \endcode
 * -  \note This uses GFX_PIXEL_SET to set the display pixels on the line;
 *          other options can be found in \ref gfx_mono_color.
 */

#endif /* GFX_MONO_H */
