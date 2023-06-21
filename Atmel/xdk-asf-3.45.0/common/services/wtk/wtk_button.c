/**
 * \file
 *
 * \brief Button widget implementation
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
 * \ingroup wtk_button_group
 * @{
 */

/** Valid states for button, relevant to pointer and keyboard operations.
 * \internal
 */
enum wtk_button_state {
	/** Normal state, no highlight or press. */
	WTK_BUTTON_NORMAL,
	/** Widget pressed, action occurs when released. */
	WTK_BUTTON_PRESSED,
};

/**
 * This is the button control struct. It contains references to the windows
 * composing the button, as well as non-window information required.
 *
 * \internal
 * \note Structure fields are only internally accessible, only pointers to
 *       structure is needed externally.
 */
struct wtk_button {
	/** Container, ultimate widget parent. */
	struct win_window *container;
	/** Copy of caption string. */
	char *caption;
	/** Custom command data, used when "clicked". */
	win_command_t command;
	/** Current state. */
	enum wtk_button_state state;
};

/**
 * This function returns a reference to the window that should be used when
 * managing the widget, such as move, resize, destroy and reparenting.
 *
 * \param button Button widget to manage.
 *
 * \return Window to be used for managing the button.
 */
struct win_window *wtk_button_as_child(struct wtk_button *button)
{
	Assert(button);
	return button->container;
}

/**
 * This function returns the window command of the specified button, as set
 * when the widget was created.
 *
 * \param button Button widget to manage.
 *
 * \return Associated window command of the button widget.
 */
win_command_t wtk_button_get_command(struct wtk_button *button)
{
	Assert(button);
	return button->command;
}

/**
 * This function is the window event handler for button widgets.
 * It handles all events sent to the windows composing the widget.
 *
 * \param win Window receiving the event.
 * \param type The event type.
 * \param data Custom data, depending on event type.
 *
 * \return True if the event was recognized and accepted.
 */
static bool wtk_button_handler(struct win_window *win,
		enum win_event_type type, void const *data)
{
	/* Custom data for windows of a widget points back to the widget itself. */
	struct wtk_button *button
		= (struct wtk_button *)win_get_custom_data(win);

	switch (type) {
	case WIN_EVENT_DRAW:
	{
		/* For DRAW events, the data parameter points to the
		 * clipping region. */
		struct win_clip_region const *clip
			= (struct win_clip_region const *)data;
		struct win_area const *area = win_get_area(win);

		/* Preare background and caption colors depending on state of
		 * button. If pressed/highlighted, the colors are inverted. */
		gfx_color_t background_color;
		gfx_color_t caption_color;

		/* There should not be other windows in this widget. */
		Assert(win == button->container);

		switch (button->state) {
		case WTK_BUTTON_NORMAL:
			background_color = WTK_BUTTON_BACKGROUND_COLOR;
			caption_color = WTK_BUTTON_CAPTION_COLOR;
			break;

		case WTK_BUTTON_PRESSED:
			background_color = WTK_BUTTON_CAPTION_COLOR;
			caption_color = WTK_BUTTON_BACKGROUND_COLOR;
			break;

		default:
			Assert(false);
			background_color = WTK_BUTTON_BACKGROUND_COLOR;
			caption_color = WTK_BUTTON_CAPTION_COLOR;
		}

		/* Draw background. */
		gfx_draw_filled_rect(clip->origin.x, clip->origin.y,
				area->size.x, area->size.y,
				background_color);

		/* Draw border. */
		gfx_draw_rect(clip->origin.x, clip->origin.y,
				area->size.x, area->size.y,
				WTK_BUTTON_BORDER_COLOR);

		/* Draw caption. */
		gfx_draw_string_aligned(button->caption,
				clip->origin.x + (area->size.x / 2),
				clip->origin.y + (area->size.y / 2),
				&sysfont, GFX_COLOR_TRANSPARENT, caption_color,
				TEXT_POS_CENTER, TEXT_ALIGN_CENTER);

		/* Always accept DRAW events, as the return value is
		 * ignored anyway for that event type.
		 */
		return true;
	}

	case WIN_EVENT_POINTER:
	{
		/* There should not be other windows in this widget. */
		Assert(win == button->container);

		/* For POINTER events, the data parameter points to the
		 * pointer event information.
		 */
		struct win_pointer_event const *event
			= (struct win_pointer_event const *)data;

		switch (event->type) {
		case WIN_POINTER_PRESS:

			/* When button pressed, grab pointer and wait
			 * for release inside button borders. Other
			 * widgets won't get pointer events before it
			 * is released, and the pointer ungrabbed by
			 * us.
			 */
			if (button->state == WTK_BUTTON_NORMAL) {
				win_grab_pointer(button->container);
				button->state = WTK_BUTTON_PRESSED;
				win_redraw(button->container);
			}

			break;

		case WIN_POINTER_RELEASE:

			/* When button released, take action only if
			 * released inside widget extents.
			 */
			if (button->state == WTK_BUTTON_PRESSED) {
				/* Ungrab pointer. */
				win_grab_pointer(NULL);
				button->state = WTK_BUTTON_NORMAL;
				win_redraw(button->container);

				/* Check release position. */
				bool isInside = win_is_inside_window
							(button->container,
							&(event->pos));

				/* Send command event if inside. */
				if (isInside) {
					struct win_command_event
							command;
					command.sender = button->
							container;
					command.recipient
						= button->
							container;
					command.data = button->
							command;
					win_queue_command_event
						(&command);
				}
			}

			break;

		default:
			break;
		}

		/* Accept all POINTER events since all acitivity inside
		 * the widget extents is relevant to us.
		 */
		return true;
	}

	case WIN_EVENT_DESTROY:
	{
		/* There should not be other windows in this widget. */
		Assert(win == button->container);

		/* Memory allocated for windows will be automatically
		 * destroyed by the window system. We must destroy
		 * other allocations.
		 */
		membag_free(button->caption);
		membag_free(button);

		/* Always accept DESTROY events, as the return value is
		 * ignored anyway for that event type.
		 */
		return true;
	}

	default:
		/* Reject unknown event types. */
		return false;
	}
}

/**
 * \brief Get minimum widget size
 *
 * This function returns the minimum size that is required for showing
 * the full widget and the caption.
 *
 * \retval size   Suggested size for the widget
 * \param caption Pointer to caption string to use for widget.
 */
void wtk_button_size_hint(struct win_point *size, const char *caption)
{
	Assert(size);
	Assert(caption);

	gfx_get_string_bounding_box(caption, &sysfont, &size->x, &size->y);
	/* Add 2 pixels for the button border */
	size->x += 2;
	size->y += 2;
}

/**
 * This function creates a new button widget. It allocates required memory and
 * intializes necessary windows to create the widget. If there is not enough
 * memory, the function returns NULL.
 *
 * To destroy the widget and all its contents, and free its memory, call
 * win_destroy() on the button's child reference, given by
 * wtk_button_as_child(), like this:
 *   "win_destroy(wtk_button_as_child(myButtonPtr));".
 * Usually it will be destroyed automatically when it's parent is destroyed.
 *
 * \param parent Parent window, possibly wtk_frame_as_parent(myFramePtr).
 * \param area Area of the internal contents.
 * \param caption Pointer to caption string. Will be copied into widget.
 * \param command_data Custom data to put into a command event when "clicked".
 *
 * \return Pointer to button, or NULL if failed.
 */
struct wtk_button *wtk_button_create(struct win_window *parent,
		struct win_area const *area,
		char const *caption, win_command_t command_data)
{
	struct win_attributes attr;
	struct wtk_button *button;

	Assert(area);
	Assert(caption);
	Assert(parent);

	/* Allocate memory for button control data. */
	button = membag_alloc(sizeof(struct wtk_button));
	if (!button) {
		goto outofmem_button;
	}

	button->state = WTK_BUTTON_NORMAL;
	button->command = command_data;

	/* Allocate memory for caption string, and copy text. */
	button->caption = membag_alloc((strlen(caption) + 1) * sizeof(char));
	if (!button->caption) {
		goto outofmem_caption;
	}

	wtk_copy_string(button->caption, caption);

	/* Handling information. */
	attr.event_handler = wtk_button_handler;
	attr.custom = button;

	/* Prepare container frame. */
	attr.area = *area;
	attr.background = NULL;
	attr.behavior = 0x00;

	button->container = win_create(parent, &attr);
	if (!button->container) {
		goto outofmem_container;
	}

	return button;

outofmem_container:
	membag_free(button->caption);

outofmem_caption:
	membag_free(button);

outofmem_button:
	return NULL;
}

/** @} */
