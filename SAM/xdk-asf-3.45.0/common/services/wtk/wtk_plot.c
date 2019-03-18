/**
 * \file
 *
 * \brief Plot widget implementation
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
#include <stdint.h>
#include <stdlib.h>
#include <membag.h>
#include <string.h>
#include <wtk.h>

/**
 * \ingroup gfx_wtk_plot
 * @{
 */

/**
 * \brief Plot control struct.
 * \internal
 *
 * Contains a pointer to the plot's containing window, and non-window
 * information necessary for its operation. Structs of this type are created
 * with \ref wtk_plot_create().
 *
 * \note Structure fields are only internally accessible. Only pointers to
 * these structures are needed externally.
 */
struct wtk_plot {
	/** Container window of plot. */
	struct win_window *container;
	/** Maximum value of plot. */
	uint8_t maximum;
	/** Number of datapoints in plot. */
	uint8_t num_datapoints;
	/** Space between datapoints. */
	uint8_t spacing;
	/** Error in spacing between datapoints. */
	uint8_t spacing_error;
	/** Pointer to ring buffer containing values to plot. */
	uint8_t *plot_buffer;
	/** Ring buffer start-point displacement */
	uint8_t buffer_start;
	/** Configuration of orientation and behavior. */
	uint8_t option;
	/** Color for plot. */
	gfx_color_t draw_color;
	/** Pointer to plot background bitmap. */
	struct gfx_bitmap *background;
	/** Configuration of axis, grid and zero-line behaviour. */
	uint8_t axis_option;
	/** Space between x-axis grid lines/tick marks. */
	uint8_t axis_spacing_x;
	/** Grid/axis offset along the x-axis. */
	uint8_t axis_offset_x;
	/** Space between y-axis grid lines/tick marks. */
	uint8_t axis_spacing_y;
	/** Grid/axis offset along the y-axis. */
	uint8_t axis_offset_y;
	/** Color for the tick marks and grid lines. */
	gfx_color_t axis_color;
	/** Color for the zero line. */
	gfx_color_t axis_zero_color;
};

/**
 * \brief Get pointer to plot window.
 *
 * Returns a reference to the window that should be used when managing the
 * widget, such as destroying, moving or reparenting it.
 *
 * \param plot Pointer to wtk_plot struct to manage.
 *
 * \return Pointer to window to be used for managing the plot.
 */
struct win_window *wtk_plot_as_child(struct wtk_plot *plot)
{
	Assert(plot);
	return plot->container;
}

/**
 * \brief Add a value to the end of the plot.
 *
 * Scales the input value to fit the plot dimensions and adds it to the end of
 * the ring buffer.
 *
 * \param plot Pointer to wtk_plot struct to set new value for.
 * \param value New value for the plot.
 *
 * \return True.
 */
bool wtk_plot_add_value(struct wtk_plot *plot, uint8_t value)
{
	uint8_t height;
	uint8_t maximum;
	struct win_area const *area;

	Assert(plot);
	Assert(value <= plot->maximum);
	Assert(plot->buffer_start < plot->num_datapoints);

	maximum = plot->maximum;

	area = win_get_area(plot->container);

	/* Makes the plot fit inside the window border. */
	height = area->size.y - 2;

	/* Rescales the added value to fit inside the plot */
	/* and stores it in the ring buffer. */
	*(plot->plot_buffer + plot->buffer_start)
		= height - wtk_rescale_value((value), maximum, height - 1);

	/* Increments ring buffer pointer and resets at end */
	plot->buffer_start++;
	if (plot->buffer_start >= plot->num_datapoints) {
		plot->buffer_start = 0;
	}

	return true;
}

/**
 * \brief Set grid/axis parameters.
 *
 * This function sets the grid and axis options, colors for the plot.
 * The axis_spacing_y and axis_offset_y parameter is rescaled to fit the plot.
 * Both grid and axis can not be used on the same plot.
 *
 * Refer to <gfx/wtk.h> for available configuration options.
 *
 * \param plot Pointer to wtk_plot struct to set colors for.
 * \param axis_option Configuration of axis, grid and zero-line behaviour.
 * \param axis_spacing_x Space between x-axis grid lines/tick marks.
 * \param axis_offset_x Grid/axis offset along the x-axis.
 * \param axis_spacing_y Space between y-axis grid lines/tick marks.
 * \param axis_offset_y Grid/axis offset along the y-axis.
 * \param axis_color Color for the tick marks and grid lines.
 * \param axis_zero_color Color for the zero line.
 */

void wtk_plot_set_grid(struct wtk_plot *plot,
		uint8_t axis_option,
		uint8_t axis_spacing_x, uint8_t axis_offset_x,
		uint8_t axis_spacing_y, uint8_t axis_offset_y,
		gfx_color_t axis_color,
		gfx_color_t axis_zero_color)
{
	Assert(plot);

	uint8_t height;
	struct win_area const *area;

	area = win_get_area(plot->container);
	/* Makes grid/axis fit inside the window border */
	height = area->size.y - 2;

	plot->axis_option = axis_option;
	plot->axis_spacing_x = axis_spacing_x;
	plot->axis_offset_x = axis_offset_x;
	plot->axis_spacing_y = wtk_rescale_value(axis_spacing_y,
			plot->maximum, height);

	plot->axis_offset_y = height - wtk_rescale_value(axis_offset_y,
			plot->maximum, height);

	plot->axis_color = axis_color;
	plot->axis_zero_color = axis_zero_color;
}

/**
 * \brief Set new plot colors.
 *
 * This sets new draw and background colors for the plot.
 *
 * \param plot Pointer to wtk_plot struct to set colors for.
 * \param draw_color Draw color to set for plot.
 * \param background Background color to set for plot.
 */

void wtk_plot_set_colors(struct wtk_plot *plot,
		gfx_color_t draw_color, struct gfx_bitmap *background)
{
	Assert(plot);

	plot->draw_color = draw_color;
	plot->background = background;
}

/**
 * \brief Grid draw function.
 * \internal
 *
 * Draws the grid or axis, and zero line based on options.
 *
 * \param plot Pointer to wtk_plot struct to draw.
 * \param area Pointer to win_area struct with position and size of the plot.
 * \param clip Pointer to win_clip_region.
 *
 * Called by the event handler to draw the grid.
 */
static void wtk_plot_grid_draw(struct wtk_plot *plot,
		struct win_area const *area,
		struct win_clip_region const *clip)
{
	uint8_t axis_option = plot->axis_option;
	uint8_t axis_spacing_x = plot->axis_spacing_x;
	uint8_t axis_offset_x = plot->axis_offset_x;
	uint8_t axis_spacing_y = plot->axis_spacing_y;
	uint8_t axis_offset_y = plot->axis_offset_y;
	uint8_t axis_color = plot->axis_color;

	gfx_coord_t plot_height = area->size.y - 2;
	gfx_coord_t plot_width = area->size.x - 2;
	gfx_coord_t plot_top = clip->origin.y + 1;
	gfx_coord_t plot_right = clip->origin.x + 1;

	/* draw lines/ticks along the vertical axis: */
	if (axis_spacing_y > 0) {
		gfx_coord_t offset = axis_offset_y;

		/* Roll offset back to top line */
		while (offset > axis_spacing_y) {
			offset -= axis_spacing_y;
		}

		if (axis_option & WTK_PLOT_GRID_VERTICAL) {
			while (offset < plot_height) {
				gfx_draw_line(plot_right,
						plot_top + offset,
						plot_right + plot_width,
						plot_top + offset,
						axis_color);

				offset += axis_spacing_y;
			}
		} else if (axis_option & WTK_PLOT_TICKS_VERTICAL) {
			while (offset < plot_height) {
				gfx_draw_line(plot_right,
						plot_top + offset,
						plot_right
						+ WTK_PLOT_TICK_MARKER_LENGTH,
						plot_top + offset,
						axis_color);

				gfx_draw_line(plot_right + plot_width
						- WTK_PLOT_TICK_MARKER_LENGTH,
						plot_top + offset,
						plot_right + plot_width,
						plot_top + offset,
						axis_color);

				offset += axis_spacing_y;
			}
		}
	}

	/* draw lines/ticks along the horizontal axis */
	if (axis_spacing_x > 0) {
		gfx_coord_t offset = axis_offset_x;

		/* Roll offset back to top line */
		while (offset > axis_spacing_x) {
			offset -= axis_spacing_x;
		}

		if (axis_option & WTK_PLOT_GRID_HORIZONTAL) {
			while (offset < plot_width) {
				gfx_draw_line(plot_right + offset,
						plot_top,
						plot_right + offset,
						plot_top + plot_height,
						axis_color);

				offset += axis_spacing_x;
			}
		} else if (axis_option & WTK_PLOT_TICKS_HORIZONTAL) {
			while (offset < plot_width) {
				gfx_draw_line(plot_right + offset,
						plot_top,
						plot_right + offset,
						plot_top
						+ WTK_PLOT_TICK_MARKER_LENGTH,
						axis_color);

				gfx_draw_line(plot_right + offset,
						plot_top + plot_height
						- WTK_PLOT_TICK_MARKER_LENGTH,
						plot_right + offset,
						plot_top + plot_height,
						axis_color);

				offset += axis_spacing_x;
			}
		}
	}

	if (axis_option & WTK_PLOT_ZERO) {
		gfx_draw_line(plot_right,
				plot_top + plot->axis_offset_y,
				plot_right + plot_width,
				plot_top + plot->axis_offset_y,
				plot->axis_zero_color);
	}
}

/**
 * \brief Plot draw function.
 * \internal
 *
 * Draws the plot itself.
 *
 * \param plot Pointer to wtk_plot struct to draw.
 * \param area Pointer to win_area struct with position and size of the plot.
 * \param clip Pointer to win_clip_region.
 *
 * Called by the event handler to draw the plot.
 */
static void wtk_plot_draw(struct wtk_plot *plot, struct win_area const *area,
		struct win_clip_region const *clip)
{
	uint8_t option = plot->option;
	uint8_t ring_buffer_offset = plot->buffer_start;
	if (option & WTK_PLOT_RIGHT_TO_LEFT) {
		if (ring_buffer_offset == 0) {
			ring_buffer_offset = plot->num_datapoints - 1;
		} else {
			ring_buffer_offset--;
		}
	}

	/* the distance from clip to the bottom of the plot area */
	gfx_coord_t plot_bottom = area->size.y - 1;
	gfx_coord_t x_error = plot->spacing_error;
	gfx_coord_t x_current = 1 + plot->spacing;
	gfx_coord_t x_previous = 1;
	gfx_coord_t y_current;
	gfx_coord_t y_previous;

	if (option & WTK_PLOT_INVERT) {
		y_previous = plot_bottom -
				*(plot->plot_buffer + ring_buffer_offset);
	} else {
		y_previous = *(plot->plot_buffer + ring_buffer_offset);
	}

	/* the for loop's variable datapoint's initial value is 1 because we
	 * use previous posistion to draw the line.
	 */
	for (uint8_t datapoint = 1;
			datapoint < (plot->num_datapoints); datapoint++) {
		/* increment the datapointer around the ring buffer */
		if (option & WTK_PLOT_RIGHT_TO_LEFT) {
			if (ring_buffer_offset == 0) {
				ring_buffer_offset = plot->num_datapoints - 1;
			} else {ring_buffer_offset--; }
		} else {
			ring_buffer_offset++;
			if (ring_buffer_offset >= plot->num_datapoints) {
				ring_buffer_offset = 0;
			}
		}

		if (option & WTK_PLOT_INVERT) {
			y_current = plot_bottom - *(plot->plot_buffer +
					ring_buffer_offset);
		} else {
			y_current = *(plot->plot_buffer + ring_buffer_offset);
		}

		gfx_draw_line(clip->origin.x + x_previous,
				clip->origin.y + y_previous,
				clip->origin.x + x_current,
				clip->origin.y + y_current,
				plot->draw_color);

		y_previous = y_current;
		x_previous = x_current;
		x_current += plot->spacing;
		x_error += plot->spacing_error;

		/* Add together the fixed-point remainder from plot->spacing and
		 * add one to the spacing between two datapoints when it
		 * exceeds a full pixel.
		 */
		if (x_error >= WTK_PLOT_SCALE_FACTOR) {
			x_current++;
			x_error -= WTK_PLOT_SCALE_FACTOR;
		}
	}
}

/**
 * \brief plot event handler.
 *
 * This is the window event handler for plot widgets. It handles the two
 * relevant event types sent to a plot's container window, i.e., drawing,
 * and destroy events.
 *
 * \param win Window receiving the event.
 * \param type The event type.
 * \param data Custom data, depending on event type.
 *
 * \return True if the event was recognized and accepted.
 */
static bool wtk_plot_handler(struct win_window *win,
		enum win_event_type type, void const *data)
{
	struct win_clip_region const *clip;
	struct win_area const *area;
	struct wtk_plot *plot;
	struct gfx_bitmap *background;

	plot = (struct wtk_plot *)win_get_custom_data(win);

	/* Window receiving the event should be the widget's containing window. */
	Assert(win == plot->container);

	switch (type) {
	case WIN_EVENT_DRAW:

		/* For DRAW events, the data parameter points to the clipping
		 * region. The window area parameter is needed because it
		 * contains the size of the widget.
		 */
		clip = (struct win_clip_region const *)data;
		area = win_get_area(win);
		background = plot->background;

		if (background != NULL) {
			/* Draw a window border. */
			gfx_draw_rect(clip->origin.x, clip->origin.y,
					area->size.x, area->size.y,
					WTK_PLOT_BORDER_COLOR);
		}

		wtk_plot_grid_draw(plot, area, clip);

		wtk_plot_draw(plot, area, clip);

		/* Always accept DRAW events, as the return value is ignored
		 * anyway for that event type.
		 */
		return true;

	case WIN_EVENT_DESTROY:

		/* Free up all memory allocated by widget.
		 * The window is freed by the window system
		 */
		membag_free(plot->plot_buffer);
		membag_free(plot);

		return true;

	default:
		return false;
	}
}

/**
 * \brief Create a new plot widget.
 *
 * Allocates the necessary memory and intializes the window and data for
 * plot widgets. If there is not enough memory, the function returns
 * NULL.\n To destroy a plot widget and all its contents, and free its
 * memory, call \ref win_destroy() on the plot's child reference, given
 * by \ref wtk_plot_as_child(), similar to:
 * \code
	win_destroy(wtk_plot_as_child(my_plot_ptr));
\endcode
 *
 * The plotted graph will shift from right to left as new data values are added.
 * Data values will be overwritten in the ring buffer as they shift out of
 * the plot window.
 * The maximum parameter scales the input value to fit the plot dimensions.
 *
 * The num_datapoints parameter must not exceed the maximum membag size,
 * and never over 255.
 *
 *
 * Refer to <gfx/wtk.h> for available configuration options.
 *
 * \param parent Pointer to parent win_window struct.
 * \param area Pointer to win_area struct with position and size of the
 *        plot. Minimum size in both x and y direction is 4 pixels.
 * \param maximum Maximum value of the plot.
 * \param num_datapoints Number of datapoints of the plot.
 * \param draw_color Plot drawing color.
 * \param background Pointer to background bitmap for frame. NULL for
 *        transparent background. When background is transparent
 *        the parent window will automatically be redrawn
 *        when the basic frame is drawn.
 * \param option Configuration options for plot.
 *
 * \return Pointer to new plot, if memory allocation was successful.
 */
struct wtk_plot *wtk_plot_create(struct win_window *parent,
		struct win_area const *area, uint8_t maximum,
		uint8_t num_datapoints, gfx_color_t draw_color,
		struct gfx_bitmap *background, uint8_t option)
{
	uint16_t length;

	/* Do sanity check on parameters. */
	Assert(maximum > 0);
	Assert(area);
	Assert(parent);
	Assert(num_datapoints > 1);

	/* Attributes scratchpad. */
	struct win_attributes attr;

	/* Allocate memory for the control data. */
	struct wtk_plot *plot = membag_alloc(sizeof(struct wtk_plot));
	if (!plot) {
		goto outofmem_plot;
	}

	/* Allocate memory for the control data. */
	plot->plot_buffer = membag_alloc(num_datapoints);
	if (!plot->plot_buffer) {
		goto outofmem_plot_buffer;
	}

	/* Initialize the plot data. */
	plot->maximum = maximum;
	plot->num_datapoints = num_datapoints;
	plot->buffer_start = 0;
	plot->option = option;
	plot->draw_color = draw_color;
	plot->background = background;

	plot->axis_option = 0;
	plot->axis_spacing_x = 0;
	plot->axis_offset_x = 0;
	plot->axis_spacing_y = 0;
	plot->axis_offset_y = 0;
	plot->axis_color = 0;
	plot->axis_zero_color = 0;

	/* Do sanity check of specified window area parameters
	 * according to the orientation of the plot.
	 */
	attr.area = *area;
	Assert(attr.area.size.x > 3);
	Assert(attr.area.size.y > 3);

	/* Makes the plot fit inside the window border. */
	length = attr.area.size.x;
	length -= 2;

	/* Calculate the spacing between datapoints. */
	plot->spacing = length / (num_datapoints - 1);

	/* Calculate the fixed-point remainder of the above operation. */
	plot->spacing_error = (uint8_t)(
		(((uint16_t)(length - plot->spacing * (num_datapoints - 1)))
		* WTK_PLOT_SCALE_FACTOR) / ((uint16_t)(num_datapoints - 1)));

	/* Set up handling information. */
	attr.event_handler = wtk_plot_handler;
	attr.custom = plot;

	/* Set background for window */
	if (background) {
		attr.background = background;
		attr.behavior = 0;
	} else {
		attr.background = NULL;
		if (option & WTK_PLOT_DONT_REDRAW_PARENT) {
			attr.behavior = 0;
		} else {
			attr.behavior = WIN_BEHAVIOR_REDRAW_PARENT;
		}
	}

	/* Create a new window for the plot. */
	plot->container = win_create(parent, &attr);
	if (!plot->container) {
		goto outofmem_container;
	}

	return plot;

outofmem_container:
	membag_free(plot->plot_buffer);

outofmem_plot_buffer:
	membag_free(plot);

outofmem_plot:
	return NULL;
}

/** @} */
