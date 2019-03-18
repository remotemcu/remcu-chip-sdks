/**
 * \file
 *
 * \brief Graphical Widget toolkit
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
#ifndef WTK_PLOT_H
#define WTK_PLOT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup wtk_group
 *
 * \defgroup wtk_plot_group Plot widget
 * @{
 */

/**
 * \defgroup wtk_plot_options Plot widget options
 * These options can be ORed together to specify the behaviour of a
 * plot widget when creating it with \ref wtk_plot_create
 * @{
 */

/**
 * \name Plot orientation configuration options.
 * For use with the option parameter of \ref wtk_plot_create
 * @{
 */

/** Plot draws values from left to right */
#define WTK_PLOT_LEFT_TO_RIGHT (0 << 0)
/** Plot draws values from right to left */
#define WTK_PLOT_RIGHT_TO_LEFT (1 << 0)

/** @} */

/**
 * \name Plot widget invert configuration options.
 * For use with the option parameter of \ref wtk_plot_create
 * @{
 */

/** Plot is inverted along y-axis. */
#define WTK_PLOT_INVERT (1 << 1)

/** @} */

/**
 * \name Redraw parent disable options.
 * For use with the option parameter of \ref wtk_plot_create
 * @{
 */
 
/** Parent is not redrawn if background is transparent. */
#define WTK_PLOT_DONT_REDRAW_PARENT (1 << 2)

/** @} */

/** @} */

/**
 * \defgroup gfx_wtk_plot_grid_options Plot widget grid options
 * These options can be ORed together to specify the behaviour of a
 * plot widget grid when adjusting it via \ref wtk_plot_set_grid.
 * @{
 */

/**
 * \name grid orientation options.
 * For use with the option parameter of \ref wtk_plot_set_grid
 * @{
 */

/** Draw horizontal grid lines along the vertical axis */
#define WTK_PLOT_GRID_VERTICAL (1 << 0)
/** Draw vertical grid lines along the horizontal axis */
#define WTK_PLOT_GRID_HORIZONTAL (1 << 1)

/** @} */

/**
 * \name axis orientation options.
 * For use with the option parameter of \ref wtk_plot_set_grid
 * @{
 */

/** Draw tick marks along the vertical axis */
#define WTK_PLOT_TICKS_VERTICAL (1 << 2)
/** Draw tick marks along the horizontal axis */
#define WTK_PLOT_TICKS_HORIZONTAL (1 << 3)

/** @} */

/**
 * \name zero line options.
 * For use with the option parameter of \ref wtk_plot_set_grid
 * @{
 */

/** Draw the zero line */
#define WTK_PLOT_ZERO (1 << 4)

/** @} */

/** @} */

struct wtk_plot;

bool wtk_plot_add_value(struct wtk_plot *plot, uint8_t value);

void wtk_plot_set_grid(struct wtk_plot *plot, uint8_t axis_option,
		uint8_t axis_spacing_x, uint8_t axis_offset_x,
		uint8_t axis_spacing_y, uint8_t axis_offset_y,
		gfx_color_t axis_color, gfx_color_t axis_zero_color);

struct wtk_plot *wtk_plot_create(struct win_window *parent,
		struct win_area const *area, uint8_t maximum,
		uint8_t datapoints,
		gfx_color_t draw_color, struct gfx_bitmap *background,
		uint8_t option);

struct win_window *wtk_plot_as_child(struct wtk_plot *plot);

void wtk_plot_set_colors(struct wtk_plot *plot,
		gfx_color_t draw_color, struct gfx_bitmap *background);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
