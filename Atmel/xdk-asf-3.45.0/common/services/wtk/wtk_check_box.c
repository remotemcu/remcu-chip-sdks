/**
 * \file
 *
 * \brief Check box widget implementation
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
 * \ingroup wtk_check_box_group
 * @{
 */

/** Valid states for check box, relevant to pointer and keyboard operations.
 * \internal
 */
enum wtk_check_box_state {
	/** Normal state, no highlight or press. */
	WTK_CHECKBOX_NORMAL,
	/** Widget pressed, action occurs when released. */
	WTK_CHECKBOX_PRESSED,
};

/**
 * This is the check box control struct. It contains references to the windows
 * composing the check box, as well as non-window information required.
 *
 * \note Structure fields are only internally accessible, only pointers to
 *       structure is needed externally.
 */
struct wtk_check_box {
	/** Container, ultimate widget parent. */
	struct win_window *container;
	/** Copy of caption string. */
	char *caption;
	/** True if selected. */
	bool selected;
	/** Current state. */
	enum wtk_check_box_state state;
	/** Command to send. Must be non-zero to be enabled. */
	win_command_t command;
};

/**
 * This function returns a reference to the window that should be used when
 * managing the widget, such as move, resize, destroy and reparenting.
 *
 * \param check_box Check box widget to manage.
 *
 * \return Window to be used for managing the check box.
 */
struct win_window *wtk_check_box_as_child(struct wtk_check_box *check_box)
{
	Assert(check_box);
	return check_box->container;
}

/**
 * This function returns the window command of the specified check box, as set
 * when the widget was created.
 *
 * \param check_box Check box widget to manage.
 *
 * \return Associated window command of the check box widget.
 */
win_command_t wtk_check_box_get_command(struct wtk_check_box *check_box)
{
	Assert(check_box);
	return check_box->command;
}

/**
 * This function toggles the value of a check box. If it is not selected, it
 * will be set to a selected/checked state, and vice versa. The graphics will
 * be updated if the box is visible.
 *
 * \param check_box Check box to toggle.
 */
void wtk_check_box_toggle(struct wtk_check_box *check_box)
{
	Assert(check_box);
	check_box->selected = !check_box->selected;
	win_redraw(check_box->container);
}

/**
 * This function sets the value of the check box according to the "selected"
 * parameter.
 * The graphics will be updated if the box is visible.
 *
 * \param check_box Check box to update.
 * \param selected Value to set for checkbox. True if check box is selected,
 * false otherwise
 */
void wtk_check_box_set(struct wtk_check_box *check_box, bool selected)
{
	Assert(check_box);
	check_box->selected = selected;
	win_redraw(check_box->container);
}

/**
 * This function returns true if the check box is selected.
 *
 * \return True if check box is selected.
 */
bool wtk_check_box_is_selected(struct wtk_check_box const *check_box)
{
	Assert(check_box);
	return check_box->selected;
}

/**
 * This function is the window event handler for check box widgets.
 * It handles all events sent to the windows composing the widget.
 *
 * \param win Window receiving the event.
 * \param type The event type.
 * \param data Custom data, depending on event type.
 *
 * \return True if the event was recognized and accepted.
 */
static bool wtk_check_box_handler(struct win_window *win,
		enum win_event_type type, void const *data)
{
	struct win_command_event command;

	/* Custom data for windows of a widget points back to the widget itself. */
	struct wtk_check_box *check_box
		= (struct wtk_check_box *)win_get_custom_data(win);

	switch (type) {
	case WIN_EVENT_DRAW:
	{
		/* There should not be other windows in this widget. */
		Assert(win == check_box->container);

		/* For DRAW events, the data parameter points to the
		 * clipping region.
		 */
		struct win_clip_region const *clip
			= (struct win_clip_region const *)data;

		/* Draw check box square. */
		gfx_draw_rect(clip->origin.x + WTK_CHECKBOX_BOX_X,
				clip->origin.y + WTK_CHECKBOX_BOX_Y,
				WTK_CHECKBOX_BOX_SIZE,
				WTK_CHECKBOX_BOX_SIZE,
				WTK_CHECKBOX_BOX_COLOR);

		/* Draw check box square background. */
		if (WTK_CHECKBOX_BACKGROUND_COLOR != GFX_COLOR_TRANSPARENT) {
			gfx_draw_filled_rect(clip->origin.x +
					WTK_CHECKBOX_BOX_X + 1,
					clip->origin.y +
					WTK_CHECKBOX_BOX_Y + 1,
					WTK_CHECKBOX_BOX_SIZE - 2,
					WTK_CHECKBOX_BOX_SIZE - 2,
					WTK_CHECKBOX_BACKGROUND_COLOR);
		}

		/* Draw check box select marker if selected. */
		if (check_box->selected) {
			gfx_draw_filled_rect(clip->origin.x +
					WTK_CHECKBOX_BOX_X + 2,
					clip->origin.y +
					WTK_CHECKBOX_BOX_Y + 2,
					WTK_CHECKBOX_BOX_SIZE - 4,
					WTK_CHECKBOX_BOX_SIZE - 4,
					WTK_CHECKBOX_SELECT_COLOR);
		}

		/* Draw caption. */
		gfx_draw_string(check_box->caption,
				clip->origin.x + WTK_CHECKBOX_CAPTION_X,
				clip->origin.y + WTK_CHECKBOX_CAPTION_Y,
				&sysfont,
				GFX_COLOR_TRANSPARENT,
				WTK_CHECKBOX_CAPTION_COLOR);

		/* Always accept DRAW events, as the return value is
		 * ignored anyway for that event type.
		 */
		return true;
	}

	case WIN_EVENT_POINTER:
	{
		/* There should not be other windows in this widget. */
		Assert(win == check_box->container);

		/* For POINTER events, the data parameter points to the
		 * pointer event information.
		 */
		struct win_pointer_event const *event
			= (struct win_pointer_event const *)data;

		switch (event->type) {
		case WIN_POINTER_PRESS:

			/* When check box pressed, grab pointer and
			 * wait for release inside widget borders.
			 * Other widgets won't get pointer events
			 * before it is released, and the pointer
			 * ungrabbed by us.
			 */
			if (check_box->state == WTK_CHECKBOX_NORMAL) {
				win_grab_pointer(check_box->container);
				check_box->state = WTK_CHECKBOX_PRESSED;
				win_redraw(check_box->container);
			}

			break;

		case WIN_POINTER_RELEASE:

			/* When check box released, take action only if
			 * released inside widget extents.
			 */
			if (check_box->state == WTK_CHECKBOX_PRESSED) {
				bool is_inside;

				/* Ungrab pointer. */
				win_grab_pointer(NULL);
				check_box->state = WTK_CHECKBOX_NORMAL;
				win_redraw(check_box->container);

				/* Check release position. */
				is_inside = win_is_inside_window
							(check_box->container,
							&(event->pos));

				/* Toggle check box if inside. */
				if (is_inside) {
					wtk_check_box_toggle(check_box);

					/* Send non-zero command. */
					if (check_box->command) {
						command.sender
							= check_box->container;
						command.recipient
							= check_box->container;
						command.data
							= check_box->command;
						win_queue_command_event
							(&command);
					}
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
		/* There should not be other windows in this widget. */
		Assert(win == check_box->container);

		/* Memory allocated for windows will be automatically destroyed
		 * by the window system. We must destroy other allocations.
		 */
		membag_free(check_box->caption);
		membag_free(check_box);

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
 * \brief Get minimum widget size
 *
 * This function returns the minimum size that is required for showing
 * the full widget and the caption.
 *
 * \retval size   Suggested size for the widget
 * \param caption Pointer to caption string to use for widget.
 */
void wtk_check_box_size_hint(struct win_point *size, const char *caption)
{
	Assert(size);
	Assert(caption);

	gfx_get_string_bounding_box(caption, &sysfont, &size->x, &size->y);
	size->x += WTK_CHECKBOX_CAPTION_X;
	size->y += WTK_CHECKBOX_CAPTION_Y;
	
	/* Clamp Y height to minimum check box size */
	if (size->y < WTK_CHECKBOX_BOX_SIZE) {
		size->y = WTK_CHECKBOX_BOX_SIZE;
	}
}

/**
 * This function creates a new check box widget. It allocates required memory
 * and intializes necessary windows to create the widget. If there is not enough
 * memory, the function returns NULL.
 *
 * To destroy the widget and all its contents, and free its memory, call
 * win_destroy() on the check box' child reference, given by
 * wtk_check_box_as_child(), like this:
 * "win_destroy(wtk_check_box_as_child(my_check_box_ptr));".
 * Usually it will be destroyed automatically when it's parent is destroyed.
 *
 * \param parent Parent window, possibly wtk_frame_as_parent(my_frame_ptr).
 * \param area Area of the internal contents.
 * \param caption Pointer to caption string. Will be copied into widget.
 * \param selected Initial state of check box, true if checked/selected.
 * \param command Command to send to parent window. Must be non-zero to be
 *                enabled.
 *
 * \return Pointer to check box, or NULL if failed.
 */
struct wtk_check_box *wtk_check_box_create(struct win_window *parent,
		struct win_area const *area,
		char const *caption, bool selected, win_command_t command)
{
	struct win_attributes attr;
	struct wtk_check_box *check_box;

	Assert(area);
	Assert(caption);
	Assert(parent);

	/* Allocate memory for check box control data. */
	check_box = membag_alloc(sizeof(struct wtk_check_box));
	if (!check_box) {
		goto outofmem_check_box;
	}

	check_box->state = WTK_CHECKBOX_NORMAL;
	check_box->selected = selected;
	check_box->command = command;

	/* Allocate memory for caption string, and copy text. */
	check_box->caption = membag_alloc((strlen(caption) + 1) * sizeof(char));
	if (!check_box->caption) {
		goto outofmem_caption;
	}

	wtk_copy_string(check_box->caption, caption);

	/* Handling information. */
	attr.event_handler = wtk_check_box_handler;
	attr.custom = check_box;

	/* Prepare container frame. */
	attr.area = *area;
	attr.background = NULL;
	attr.behavior = WIN_BEHAVIOR_REDRAW_PARENT;

	check_box->container = win_create(parent, &attr);
	if (!check_box->container) {
		goto outofmem_container;
	}

	return check_box;

outofmem_container:
	membag_free(check_box->caption);

outofmem_caption:
	membag_free(check_box);

outofmem_check_box:
	return NULL;
}

/** @} */
