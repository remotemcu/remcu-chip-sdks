/**
 * \file
 *
 * \brief Slider widget implementation
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
 * \ingroup wtk_slider_group
 * @{
 */

/**
 * \brief Valid states for slider, relevant to pointer operations.
 * \internal
 */
enum wtk_slider_state {
	/** Normal state, no highlight or movement. */
	WTK_SLIDER_NORMAL,
	/** Slider is pressed, highlighted and moving. */
	WTK_SLIDER_MOVING,
};

/**
 * \brief Slider control struct.
 * \internal
 *
 * Contains a pointer to the slider's containing window, and non-window
 * information necessary for its operation. Structs of this type are created
 * with \ref wtk_slider_create().
 *
 * \note Structure fields are only internally accessible. Only pointers to
 * these structures are needed externally.
 */
struct wtk_slider {
	/** Container window of slider. */
	struct win_window *container;
	/** Slider position in relation to root window */
	struct win_point root_pos;
	/** State of slider. */
	enum wtk_slider_state state;
	/** Maximum value of slider. */
	uint8_t maximum;
	/** Value of slider. */
	uint8_t value;
	/** Position of slider knob. */
	uint8_t position;
	/** Configuration of orientation and behavior. */
	uint8_t option;
	/** Command to send. Must be non-zero if used. */
	win_command_t command;
};

/**
 * \brief Get pointer to slider window.
 *
 * Returns a reference to the window that should be used when managing the
 * widget, such as destroying, moving or reparenting it.
 *
 * \param slider Pointer to wtk_slider struct to manage.
 *
 * \return Pointer to window to be used for managing the slider.
 */
struct win_window *wtk_slider_as_child(struct wtk_slider *slider)
{
	Assert(slider);
	return slider->container;
}

/**
 * This function returns the window command of the specified slider, as set
 * when the widget was created.
 *
 * \param slider Slider widget to manage.
 *
 * \return Associated window command of the slider widget.
 */
win_command_t wtk_slider_get_command(struct wtk_slider *slider)
{
	Assert(slider);
	return slider->command;
}

/**
 * \brief Get slider status.
 *
 * Returns whether or not the slider is currently being manipulated by pointer
 * events, i.e., it is moving.
 *
 * \param slider Pointer to wtk_slider struct to get status of.
 *
 * \return True if slider is currently moving.
 */
bool wtk_slider_is_moving(struct wtk_slider const *slider)
{
	Assert(slider);
	return slider->state == WTK_SLIDER_MOVING;
}

/**
 * \brief Get slider value.
 *
 * Returns the slider value, inverted if such behavior is configured.
 *
 * \param slider Pointer to wtk_slider struct to get value from.
 *
 * \return Value of slider.
 */
uint8_t wtk_slider_get_value(struct wtk_slider const *slider)
{
	Assert(slider);

	if (slider->option & WTK_SLIDER_INVERT) {
		return slider->maximum - slider->value;
	} else {
		return slider->value;
	}
}

/**
 * \brief Set new slider value.
 *
 * Updates the current value and issues a redrawing of the slider if its value
 * was indeed changed. In this case, the new position of the slider knob is
 * also computed.
 *
 * \param slider Pointer to wtk_slider struct to set new value for.
 * \param value New value for the slider.
 *
 * \return True if slider value was changed.
 */
bool wtk_slider_set_value(struct wtk_slider *slider, uint8_t value)
{
	struct win_area const *area;
	uint8_t length;
	uint8_t option;

	Assert(slider);
	Assert(value <= slider->maximum);

	option = slider->option;

	if (option & WTK_SLIDER_INVERT) {
		value = slider->maximum - value;
	}

	if (slider->value != value) {
		slider->value = value;
		area = win_get_area(slider->container);

		/* Get length of slider from window.
		 * wtk_slider_create() asserts that this is an 8-bit value.
		 */
		if (option & WTK_SLIDER_VERTICAL) {
			length = area->size.y;
		} else {
			length = area->size.x;
		}

		length -= WTK_SLIDER_KNOB_WIDTH;
		slider->position = wtk_rescale_value(value, slider->maximum,
				length);

		win_redraw(slider->container);

		return true;
	} else {
		return false;
	}
}

/**
 * \brief Slider event handler.
 *
 * This is the window event handler for slider widgets. It handles the three
 * relevant event types sent to a slider's container window, i.e., drawing,
 * pointer and destroy events.\par
 *
 * For POINTER events, the slider value is only updated when the pointer moves,
 * and not upon press or release events. The handler will grab the pointer and
 * allow for it to move outside the actual widget window and still control the
 * slider knob.
 *
 * \param win Window receiving the event.
 * \param type The event type.
 * \param data Custom data, depending on event type.
 *
 * \return True if the event was recognized and accepted.
 */
static bool wtk_slider_handler(struct win_window *win, enum win_event_type type,
		void const *data)
{
	struct win_pointer_event const *event;
	struct win_clip_region const *clip;
	struct win_command_event command;
	struct win_area const *area;
	struct wtk_slider *slider;
	struct win_point origin;
	gfx_color_t knob_color;
	gfx_coord_t position;
	gfx_coord_t length;
	uint8_t option;
	uint8_t value;
	bool send_command;
	uint8_t new_position;
	struct win_area bg1_draw_area;
	struct win_area bg2_draw_area;
	struct win_area knob_draw_area;

	slider = (struct wtk_slider *)win_get_custom_data(win);

	/* There should not be other windows in this widget. */
	Assert(win == slider->container);

	switch (type) {
	case WIN_EVENT_DRAW:

		/* For DRAW events, the data parameter points to the
		 * clipping region.
		 */
		clip = (struct win_clip_region const *)data;
		area = win_get_area(win);
		option = slider->option;

		if (slider->state == WTK_SLIDER_NORMAL) {
			knob_color = WTK_SLIDER_KNOB_COLOR_NORMAL;
		} else {
			knob_color = WTK_SLIDER_KNOB_COLOR_MOVING;
		}

		/* Set up the drawing areas */
		knob_draw_area.pos = clip->origin;
		knob_draw_area.size = area->size;
		bg1_draw_area = knob_draw_area;
		win_inflate_area(&bg1_draw_area, -1);
		bg2_draw_area = bg1_draw_area;

		/* Draw the slider knob according to configured orientation. */
		if (option & WTK_SLIDER_VERTICAL) {
			knob_draw_area.pos.y += slider->position + 1;
			knob_draw_area.size.y = WTK_SLIDER_KNOB_WIDTH;
			bg1_draw_area.size.y = slider->position;
			bg2_draw_area.pos.y += slider->position +
					WTK_SLIDER_KNOB_WIDTH;
			bg2_draw_area.size.y -= slider->position +
					WTK_SLIDER_KNOB_WIDTH;
		} else {
			knob_draw_area.pos.x += slider->position + 1;
			knob_draw_area.size.x = WTK_SLIDER_KNOB_WIDTH;
			bg1_draw_area.size.x = slider->position;
			bg2_draw_area.pos.x += slider->position +
					WTK_SLIDER_KNOB_WIDTH;
			bg2_draw_area.size.x -= slider->position +
					WTK_SLIDER_KNOB_WIDTH;
		}

		/* Draw slider knob border. */
		gfx_draw_rect(knob_draw_area.pos.x, knob_draw_area.pos.y,
				knob_draw_area.size.x, knob_draw_area.size.y,
				WTK_SLIDER_BORDER_COLOR);

		/* Shrink knob area for the graphical fill */
		win_inflate_area(&knob_draw_area, -1);

		/* Draw slider knob. */
		gfx_draw_filled_rect(knob_draw_area.pos.x, knob_draw_area.pos.y,
				knob_draw_area.size.x, knob_draw_area.size.y,
				knob_color);

		/* Draw left/top section of background around the slider */
		gfx_draw_filled_rect(bg1_draw_area.pos.x, bg1_draw_area.pos.y,
				bg1_draw_area.size.x, bg1_draw_area.size.y,
				WTK_SLIDER_BACKGROUND_COLOR);

		/* Draw right/bottom section of background around the slider */
		gfx_draw_filled_rect(bg2_draw_area.pos.x, bg2_draw_area.pos.y,
				bg2_draw_area.size.x, bg2_draw_area.size.y,
				WTK_SLIDER_BACKGROUND_COLOR);

		/* Draw slider frame border. */
		gfx_draw_rect(clip->origin.x,
				clip->origin.y,
				area->size.x,
				area->size.y, WTK_SLIDER_BORDER_COLOR);

		/* Always accept DRAW events, as the return value is ignored
		 * anyway for that event type.
		 */
		return true;

	case WIN_EVENT_POINTER:

		/* For POINTER events, the data parameter points to the pointer
		 * event information.
		 */
		event = (struct win_pointer_event const *)data;
		area = win_get_area(win);
		option = slider->option;
		send_command = false;
		origin = slider->root_pos;

		switch (event->type) {
		case WIN_POINTER_PRESS:

			/* Grab the pointer and redraw a highlighted slider.
			 * Slider value is not updated yet.
			 */
			if (slider->state == WTK_SLIDER_NORMAL) {
				slider->state = WTK_SLIDER_MOVING;
				win_grab_pointer(win);
				win_redraw(win);
			}

#if WTK_SLIDER_PARENT_MOVE_SUPPORT
			/* Update root position. */
			win_translate_win_to_root(win, &slider->root_pos);
#endif
			break;

		case WIN_POINTER_MOVE:

			/* The slider is only updated when the pointer moves
			 * and the window was previously pressed. The pointer
			 * does not need to remain within the window to control
			 * the knob as only the position along the slider's
			 * direction of orientation is used.
			 */
			if (slider->state == WTK_SLIDER_MOVING) {
				/* Get the position of the pointer relative to
				 * slider knob's origin, and the length of the
				 * slider itself.
				 */
				if (option & WTK_SLIDER_VERTICAL) {
					position = event->pos.y - origin.y;
					length = area->size.y;
				} else {
					position = event->pos.x - origin.x;
					length = area->size.x;
				}

				/* Subtract offsets due to slider knob size. */
				position -= WTK_SLIDER_KNOB_WIDTH / 2;
				length -= WTK_SLIDER_KNOB_WIDTH;

				/* Bound the value if pointer is outside window.
				 * Otherwise, compute the slider value from the
				 * knob position.
				 */
				if (position < 0) {
					value = 0;
				} else if (position > length) {
					value = slider->maximum;
				} else {
					value = wtk_rescale_value(position,
							length,
							slider->maximum);
				}

				/* Update slider only if this is a new value. */
				if (slider->value != value) {
					slider->value = value;

					/* Compute knob position from value to
					 * get correct positioning.
					 */
					new_position = wtk_rescale_value(
							value, slider->maximum,
							length);

					if (option & WTK_SLIDER_CMD_MOVE) {
						send_command = true;
					}

					if (new_position != slider->position) {
						slider->position = new_position;
						win_redraw(win);
					}
				}
			}

			break;

		case WIN_POINTER_RELEASE:

			/* Release the pointer and redraw a normal slider.
			 * The slider's value is not updated. Hence, a pointer
			 * press directly followed by a release will leave the
			 * slider value unchanged.
			 */
			if (slider->state == WTK_SLIDER_MOVING) {
				slider->state = WTK_SLIDER_NORMAL;
				win_grab_pointer(NULL);
				win_redraw(win);

				if (option & WTK_SLIDER_CMD_RELEASE) {
					send_command = true;
				}
			}

			break;

		default:
			break;
		}

		/* Prepare and send command, if it was flagged. */
		if (send_command) {
			command.sender = slider->container;
			command.recipient = slider->container;
			command.data = slider->command;
			win_queue_command_event(&command);
		}

		/* Accept all POINTER events since all activity inside the
		 * widget window is relevant.
		 */
		return true;

	case WIN_EVENT_DESTROY:

		/* Memory allocated for windows will be automatically destroyed
		 * by the window system. We must destroy other allocations.
		 */
		membag_free(slider);

		/* Always accept DESTROY events, as the return value is ignored
		 * anyway for that event type.
		 */
		return true;

	default:
		/* Reject unknown event types. */
		return false;
	}
}

/**
 * \brief Create a new slider widget.
 *
 * Allocates the necessary memory and intializes the window and data for slider
 * widgets. If there is not enough memory, the function returns NULL.\n
 * To destroy a slider widget and all its contents, and free its memory, call
 * \ref win_destroy() on the slider's child reference, given by
 * \ref wtk_slider_as_child(), like this:
 * "win_destroy(wtk_slider_as_child(my_slider_ptr));".\par
 *
 * Slider widgets fill the specified area and perform a mapping of the slider
 * knob's position to a value between 0 and maximum. The length of the slider
 * cannot exceed 255 pixels.\par
 *
 * By default, the value 0 corresponds to the top-most position for a vertical
 * slider, and the left-most position for a horizontal one. The slider's
 * orientation and inversion of the value can be configured.\par
 *
 * A slider can be configured to issue command events whenever its value is
 * changed by a pointer and/or when a pointer releases it.\par
 *
 * Refer to <gfx/wtk.h> for available configuration options.
 *
 * \param parent Pointer to parent win_window struct.
 * \param area Pointer to win_area struct with position and size of the slider.
 * \param maximum Maximum value of the slider.
 * \param value Initial value of the slider.
 * \param option Configuration options for slider.
 *               See \ref wtk_slider_options_group
 * \param command Command to send to parent window. Must be non-zero if used.
 *
 * \return Pointer to new slider, if memory allocation was successful.
 */
struct wtk_slider *wtk_slider_create(struct win_window *parent,
		struct win_area const *area, uint8_t maximum, uint8_t value,
		uint8_t option, win_command_t command)
{
	struct win_attributes attr;
	struct wtk_slider *slider;
	uint8_t length;

	/* Do sanity check on parameters. */
	Assert(maximum > 0);
	Assert(area);
	Assert(parent);

	/* Allocate memory for the control data. */
	slider = membag_alloc(sizeof(struct wtk_slider));
	if (!slider) {
		goto outofmem_slider;
	}

	/* Initialize the slider data. */
	slider->state = WTK_SLIDER_NORMAL;
	slider->maximum = maximum;
	slider->value = value;
	slider->option = option;

	/* Invert the initial value if slider is inverted. */
	if (option & WTK_SLIDER_INVERT) {
		value = maximum - value;
	}

	slider->value = value;

	/* Enforce a non-zero command value, if these are enabled. */
	if (option & (WTK_SLIDER_CMD_MOVE | WTK_SLIDER_CMD_RELEASE)) {
		Assert(command > 0);
		slider->command = command;
	}

	/* Set up event handling for the widget window. */
	attr.event_handler = wtk_slider_handler;
	attr.custom = slider;

	/* Do a sanity check of the specified window area parameters. */
	attr.area = *area;
	Assert(attr.area.size.x > 0);
	Assert(attr.area.size.y > 0);

	if (option & WTK_SLIDER_VERTICAL) {
		Assert(attr.area.size.x > 3);
		Assert(attr.area.size.x <= (uint8_t) ~0);
		Assert(attr.area.size.y > WTK_SLIDER_KNOB_WIDTH);
		length = attr.area.size.y;
	} else {
		Assert(attr.area.size.x > WTK_SLIDER_KNOB_WIDTH);
		Assert(attr.area.size.y <= (uint8_t) ~0);
		Assert(attr.area.size.y > 3);
		length = attr.area.size.x;
	}

	/* Set slider knob position according to initial value. */
	length -= WTK_SLIDER_KNOB_WIDTH;
	slider->position = wtk_rescale_value(value, maximum, length);

	/* All drawing is done in wtk_slider_handler() to reduce overhead.
	 * Slider has no transparent areas, so parent does not need redrawing.
	 */
	attr.background = NULL;
	attr.behavior = 0;

	/* Create the widget window. */
	slider->container = win_create(parent, &attr);
	if (!slider->container) {
		goto outofmem_container;
	}

	/* Store absolute position */
	win_translate_win_to_root(slider->container, &slider->root_pos);
	return slider;

outofmem_container:
	membag_free(slider);

outofmem_slider:
	return NULL;
}

/** @} */
