/**
 * \file
 *
 * \brief Progress bar widget implementation
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
#include <stdint.h>
#include <stdlib.h>
#include <membag.h>
#include <string.h>
#include <wtk.h>

/**
 * \ingroup wtk_progress_bar_group
 * @{
 */

/**
 * \brief Progress bar control struct.
 * \internal
 *
 * Contains a pointer to the progress bar's containing window, and non-window
 * information necessary for its operation. Structs of this type are created
 * with \ref wtk_progress_bar_create().
 *
 * \note Structure fields are only internally accessible. Only pointers to
 * these structures are needed externally.
 */
struct wtk_progress_bar {
	/** Container window of progress bar. */
	struct win_window *container;
	/** Maximum value of progress bar. */
	uint8_t maximum;
	/** Value of progress bar. */
	uint8_t value;
	/** End position of progress bar. */
	uint8_t position;
	/** Configuration of orientation and behavior. */
	uint8_t option;
	/** Color for progress bar fill. */
	gfx_color_t fill_color;
	/** Color for progress bar background. */
	gfx_color_t background_color;
};

/**
 * \brief Get pointer to progress bar window.
 *
 * Returns a reference to the window that should be used when managing the
 * widget, such as destroying, moving or reparenting it.
 *
 * \param bar Pointer to wtk_progress_bar struct to manage.
 *
 * \return Pointer to window to be used for managing the progress bar.
 */
struct win_window *wtk_progress_bar_as_child(struct wtk_progress_bar *bar)
{
	Assert(bar);
	return bar->container;
}

/**
 * \brief Set new progress bar value.
 *
 * Updates the current value and issues a redrawing of the progress bar if its
 * value was indeed changed. In this case, a new end position for the progress
 * bar's fill area is also computed.
 *
 * \param bar Pointer to wtk_progress_bar struct to set new value for.
 * \param value New value for the progress bar.
 *
 * \return True if progress bar's value was changed.
 */
bool wtk_progress_bar_set_value(struct wtk_progress_bar *bar, uint8_t value)
{
	uint8_t length;
	uint8_t option;
	uint8_t maximum;
	struct win_area const *area;

	Assert(bar);
	Assert(value <= bar->maximum);

	if (value != bar->value) {
		bar->value = value;
		option = bar->option;
		maximum = bar->maximum;
		area = win_get_area(bar->container);

		/* Get length of progress bar from window. */
		if (option & WTK_PROGRESS_BAR_VERTICAL) {
			length = area->size.y;
		} else {
			length = area->size.x;
		}

		length -= 2;

		if (option & WTK_PROGRESS_BAR_INVERT) {
			value = maximum - value;
		}

		bar->position = wtk_rescale_value(value, maximum, length);
		win_redraw(bar->container);

		return true;
	} else {
		return false;
	}
}

/**
 * \brief Get progress bar value.
 *
 * \param bar Pointer to wtk_progress_bar struct to get value from.
 *
 * \return Value of progress bar.
 */
uint8_t wtk_progress_bar_get_value(struct wtk_progress_bar *bar)
{
	Assert(bar);
	return bar->value;
}

/**
 * \brief Set new progress bar colors.
 *
 * This sets new fill and background colors for the progress bar. If the bar is
 * inverted, the two colors are switched.
 *
 * \param bar Pointer to wtk_progress_bar struct to set colors for.
 * \param fill_color Fill color to set for progress bar.
 * \param background_color Background color to set for progress bar.
 */
void wtk_progress_bar_set_colors(struct wtk_progress_bar *bar,
		gfx_color_t fill_color, gfx_color_t background_color)
{
	Assert(bar);

	if (bar->option & WTK_PROGRESS_BAR_INVERT) {
		bar->fill_color = background_color;
		bar->background_color = fill_color;
	} else {
		bar->fill_color = fill_color;
		bar->background_color = background_color;
	}
}

/**
 * \brief Progress bar event handler.
 *
 * This is the window event handler for progress bar widgets. It handles the two
 * relevant event types sent to a progress bar's container window, i.e.,
 * drawing, and destroy events.
 *
 * \param win Window receiving the event.
 * \param type The event type.
 * \param data Custom data, depending on event type.
 *
 * \return True if the event was recognized and accepted.
 */
static bool wtk_progress_bar_handler(struct win_window *win,
		enum win_event_type type, void const *data)
{
	struct win_clip_region const *clip;
	struct win_area const *area;
	struct wtk_progress_bar *bar;
	uint8_t position;
	uint8_t option;

	bar = (struct wtk_progress_bar *)win_get_custom_data(win);

	/* Window receiving the event should be the widget's containing window. */
	Assert(win == bar->container);

	switch (type) {
	case WIN_EVENT_DRAW:

		/* For DRAW events, the data parameter points to the clipping
		 * region. The window area parameter is needed because it
		 * contains the size of the widget.
		 */
		clip = (struct win_clip_region const *)data;
		area = win_get_area(win);

		position = bar->position;
		option = bar->option;

		/* Draw a window border. */
		gfx_draw_rect(clip->origin.x, clip->origin.y, area->size.x,
				area->size.y, WTK_PROGRESS_BAR_BORDER_COLOR);

		/* Draw progress bar interior according to orientation.
		 * An inverted progress bar is drawn in the same way as a
		 * non-inverted, as this option is handled in the functions
		 * for setting the bar's colors and value.
		 */
		if (option & WTK_PROGRESS_BAR_VERTICAL) {
			/* Draw the top section of the bar. */
			gfx_draw_filled_rect(clip->origin.x + 1,
					clip->origin.y + 1,
					area->size.x - 2,
					position, bar->fill_color);
			/* Draw the bottom section of the bar. */
			gfx_draw_filled_rect(clip->origin.x + 1,
					clip->origin.y + 1 + position,
					area->size.x - 2,
					area->size.y - 2 - position,
					bar->background_color);
		} else {
			/* Draw the left section of the bar. */
			gfx_draw_filled_rect(clip->origin.x + 1,
					clip->origin.y + 1,
					bar->position,
					area->size.y - 2, bar->fill_color);
			/* Draw the right section of the bar. */
			gfx_draw_filled_rect(clip->origin.x + 1 + position,
					clip->origin.y + 1,
					area->size.x - 2 - position,
					area->size.y - 2,
					bar->background_color);
		}

		/* Always accept DRAW events, as the return value is ignored
		 * anyway for that event type.
		 */
		return true;

	case WIN_EVENT_DESTROY:

		/* Free up all memory allocated by widget.
		 * The window is freed by the window system
		 */
		membag_free(bar);
		return true;

	default:
		return false;
	}
}

/**
 * \brief Create a new progress bar widget.
 *
 * Allocates the necessary memory and intializes the window and data for
 * progress bar widgets. If there is not enough memory, the function returns
 * NULL.\n To destroy a progress bar widget and all its contents, and free its
 * memory, call \ref win_destroy() on the progress bar's child reference, given
 * by \ref wtk_progress_bar_as_child(), like this:
 * "win_destroy(wtk_progress_bar_as_child(my_progress_bar_ptr));".\par
 *
 * Progress bar widgets divide their window area in two non-overlapping
 * rectangles: one with a fill color, and one with a background color.
 * The ratio between the two rectangles' sizes is given by the progress bar's
 * value relative to its maximum: a higher value gives a larger fill.\par
 *
 * By default, a vertically oriented progress bar fills from the top, while a
 * horizontal one fills from the left. The progress bar's orientation and fill
 * direction can both be configured at the time of creation. The fill and
 * background colors can be changed at runtime.\par
 *
 * Refer to <gfx/wtk.h> for available configuration options.
 *
 * \param parent Pointer to parent win_window struct.
 * \param area Pointer to win_area struct with position and size of the
 *             progress bar. Minimum size in both x and y direction is 3 pixels.
 * \param maximum Maximum value of the progress bar.
 * \param value Initial value of the progress bar.
 * \param fill_color Color for filled area.
 * \param background_color Color for background area.
 * \param option Configuration options for progress bar.
 *
 * \return Pointer to new progress bar, if memory allocation was successful.
 */
struct wtk_progress_bar *wtk_progress_bar_create(struct win_window *parent,
		struct win_area const *area, uint8_t maximum, uint8_t value,
		gfx_color_t fill_color, gfx_color_t background_color,
		uint8_t option)
{
	uint8_t length;

	/* Do sanity check on parameters. */
	Assert(maximum > 0);
	Assert(value <= maximum);
	Assert(area);
	Assert(parent);

	/* Attributes scratchpad. */
	struct win_attributes attr;

	/* Allocate memory for the control data. */
	struct wtk_progress_bar *bar
		= membag_alloc(sizeof(struct wtk_progress_bar));
	if (!bar) {
		goto outofmem_bar;
	}

	/* Initialize the progress bar data. */
	bar->maximum = maximum;
	bar->value = value;
	bar->option = option;

	/* Set the progress bar's colors and prepare the value for computation
	 * of the bar's end position according to the invert option.
	 */
	if (option & WTK_PROGRESS_BAR_INVERT) {
		bar->fill_color = background_color;
		bar->background_color = fill_color;
		value = maximum - value;
	} else {
		bar->fill_color = fill_color;
		bar->background_color = background_color;
	}

	/* Set up handling information. */
	attr.event_handler = wtk_progress_bar_handler;
	attr.custom = bar;

	/* Do sanity check of specified window area parameters
	 * according to the orientation of the progress bar.
	 */
	attr.area = *area;
	Assert(attr.area.size.x > 3);
	Assert(attr.area.size.y > 3);

	if (option & WTK_PROGRESS_BAR_VERTICAL) {
		Assert(attr.area.size.y < (uint8_t) ~0);
		length = attr.area.size.y;
	} else {
		Assert(attr.area.size.x < (uint8_t) ~0);
		length = attr.area.size.x;
	}

	length -= 2;

	/* Set the progress bar's end position. */
	bar->position = wtk_rescale_value(value, maximum, length);

	/* All drawing is done in wtk_progress_bar_handler() so no background is
	 * needed.
	 */
	attr.background = NULL;

	/* Since the widget has no transparent areas, the parent does not need
	 * to be redrawn.
	 */
	attr.behavior = 0;

	/* Create a new window for the progress bar. */
	bar->container = win_create(parent, &attr);
	if (!bar->container) {
		goto outofmem_container;
	}

	return bar;

outofmem_container:
	membag_free(bar);

outofmem_bar:
	return NULL;
}

/** @} */
