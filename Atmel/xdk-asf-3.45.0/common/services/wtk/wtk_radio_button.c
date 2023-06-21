/**
 * \file
 *
 * \brief Radio button widget implementation
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
 * \ingroup wtk_radio_button_group
 * @{
 */

/** Valid states for radio button, relevant to pointer and keyboard operations.
 * \internal
 */
enum wtk_radio_button_state {
	/** Normal state, no highlight or press. */
	WTK_RADIOBUTTON_NORMAL,
	/** Widget pressed, action occurs when released. */
	WTK_RADIOBUTTON_PRESSED,
};

/**
 * This is the radio button group control struct. It contains the necessary
 * information about a radio button group, i.e. number of members in the group
 * and the current selected one.
 *
 * \note Structure fields are only internally accessible, only pointers to
 *       structure is needed externally.
 */
struct wtk_radio_group {
	/** Number of members in this group. */
	wtk_radio_group_size_t num_references;
	/** Currently selected member. */
	struct wtk_radio_button *selected;
};

/**
 * This is the radio button control struct. It contains references to the
 * windows composing the radio button, as well as non-window information
 * required.
 *
 * \note Structure fields are only internally accessible, only pointers to
 *       structure is needed externally.
 */
struct wtk_radio_button {
	/** Container, ultimate widget parent. */
	struct win_window *container;
	/** Copy of caption string. */
	char *caption;
	/** Reference to the group we are member of. */
	struct wtk_radio_group *group;
	/** Current state. */
	enum wtk_radio_button_state state;
	/** Command to send. Must be non-zero to be enabled. */
	win_command_t command;
};

/**
 * This function returns a reference to the window that should be used when
 * managing the widget, such as move, resize, destroy and reparenting.
 *
 * \param radio_button Radio button widget to manage.
 *
 * \return Window to be used for managing the radio button.
 */
struct win_window *wtk_radio_button_as_child(struct wtk_radio_button
		*radio_button)
{
	Assert(radio_button);
	return radio_button->container;
}

/**
 * This function returns the window command of the specified radio button, as set
 * when the widget was created.
 *
 * \param radio_button Radio button widget to manage.
 *
 * \return Associated window command of the radio button widget.
 */
win_command_t wtk_radio_button_get_command(struct wtk_radio_button *radio_button)
{
	Assert(radio_button);
	return radio_button->command;
}

/**
 * This function sets this radio button to be the single radio button
 * selected within its group. If another radio button was selected, it
 * will be deselected. Both widgets will be redrawn if visible.
 *
 * \param radio_button Radio button widget to select.
 */
void wtk_radio_button_select(struct wtk_radio_button *radio_button)
{
	struct wtk_radio_button *old_selected;

	Assert(radio_button);

	/* Nothing to do if already selected. */
	if (radio_button->group->selected == radio_button) {
		return;
	}

	/* Change selection and redraw both. */
	old_selected = radio_button->group->selected;
	radio_button->group->selected = radio_button;
	if (old_selected) {
		win_redraw(old_selected->container);
	}

	win_redraw(radio_button->container);
}

/**
 * This function returns true if the radio button is the one currently
 * selected within its radio button group.
 *
 * \param radio_button Radio button widget to check.
 *
 * \return True if radio button selected.
 */
bool wtk_radio_button_is_selected(struct wtk_radio_button const *radio_button)
{
	Assert(radio_button);
	return (radio_button->group->selected == radio_button);
}

/**
 * This function is the window event handler for radio button widgets.
 * It handles all events sent to the windows composing the widget.
 *
 * \param win Window receiving the event.
 * \param type The event type.
 * \param data Custom data, depending on event type.
 *
 * \return True if the event was recognized and accepted.
 */
static bool wtk_radio_button_handler(struct win_window *win,
		enum win_event_type type, void const *data)
{
	struct win_command_event command;

	/* Custom data for windows of a widget points back to the widget itself. */
	struct wtk_radio_button *radio_button
		= (struct wtk_radio_button *)win_get_custom_data(win);

	switch (type) {
	case WIN_EVENT_DRAW:
	{
		/* For DRAW events, the data parameter points to the
		 * clipping region.
		 */
		struct win_clip_region const *clip
			= (struct win_clip_region const *)data;

		/* There should not be other windows in this widget. */
		Assert(win == radio_button->container);

		/* Draw radio button circle. */
		gfx_draw_circle(clip->origin.x +
				WTK_RADIOBUTTON_BUTTON_X,
				clip->origin.y +
				WTK_RADIOBUTTON_BUTTON_Y,
				WTK_RADIOBUTTON_RADIUS,
				WTK_RADIOBUTTON_BUTTON_COLOR,
				GFX_WHOLE);

		/* Draw radio button filled circle background. */
		if (WTK_RADIOBUTTON_BACKGROUND_COLOR != GFX_COLOR_TRANSPARENT) {
			gfx_draw_filled_circle(clip->origin.x +
				WTK_RADIOBUTTON_BUTTON_X,
				clip->origin.y +
				WTK_RADIOBUTTON_BUTTON_Y,
				WTK_RADIOBUTTON_RADIUS - 1,
				WTK_RADIOBUTTON_BACKGROUND_COLOR,
				GFX_WHOLE);
		}	

		/* Draw radio button select marker if selected. */
		if (radio_button->group->selected == radio_button) {
			gfx_draw_filled_circle(clip->origin.x +
					WTK_RADIOBUTTON_BUTTON_X,
					clip->origin.y +
					WTK_RADIOBUTTON_BUTTON_Y,
					WTK_RADIOBUTTON_RADIUS - 2,
					WTK_RADIOBUTTON_SELECT_COLOR,
					GFX_WHOLE);
		}

		/* Draw caption. */
		gfx_draw_string(radio_button->caption,
				clip->origin.x +
				WTK_RADIOBUTTON_CAPTION_X,
				clip->origin.y +
				WTK_RADIOBUTTON_CAPTION_Y, &sysfont,
				GFX_COLOR_TRANSPARENT,
				WTK_RADIOBUTTON_CAPTION_COLOR);

		/* Always accept DRAW events, as the return value is
		 * ignored anyway for that event type.
		 */
		return true;
	}

	case WIN_EVENT_POINTER:
	{
		/* There should not be other windows in this widget. */
		Assert(win == radio_button->container);

		/* For POINTER events, the data parameter points to the
		 * pointer event information.
		 */
		struct win_pointer_event const *event
			= (struct win_pointer_event const *)data;

		switch (event->type) {
		case WIN_POINTER_PRESS:

			/* When radio button pressed, grab pointer and
			 * wait for release inside widget borders.
			 * Other widgets won't get pointer events
			 * before it is released, and the pointer
			 * ungrabbed by us.
			 */
			if (radio_button->state ==
					WTK_RADIOBUTTON_NORMAL) {
				win_grab_pointer(radio_button->
						container);
				radio_button->state
					= WTK_RADIOBUTTON_PRESSED;
				win_redraw(radio_button->container);
			}

			break;

		case WIN_POINTER_RELEASE:

			/* When button released, take action only if
			 * released inside widget extents.
			 */
			if (radio_button->state ==
					WTK_RADIOBUTTON_PRESSED) {
				bool is_inside;

				/* Ungrab pointer. */
				win_grab_pointer(NULL);
				radio_button->state
					= WTK_RADIOBUTTON_NORMAL;
				win_redraw(radio_button->container);

				/* Check release position. */
				is_inside = win_is_inside_window
							(radio_button->
							container,
							&(event->pos));

				/* Select this radio button if inside. */
				if (is_inside) {
					wtk_radio_button_select
						(radio_button);

					/* Send non-zero command. */
					if (radio_button->command) {
						command.sender
							= radio_button->
								container;
						command.recipient
							= radio_button->
								container;
						command.data
							= radio_button->command;
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
		Assert(win == radio_button->container);

		/* Memory allocated for windows will be automatically destroyed
		 * by the window system. We must destroy other allocations.
		 */
		membag_free(radio_button->caption);

		/* Destroy radio group as well if we are the last one in the
		 * group. If not, remove ourselves from the group.
		 */
		--(radio_button->group->num_references);
		if (!radio_button->group->num_references) {
			membag_free(radio_button->group);
		} else {
			if (radio_button->group->selected == radio_button) {
				radio_button->group->selected = NULL;
			}
		}

		membag_free(radio_button);

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
void wtk_radio_button_size_hint(struct win_point *size, const char *caption)
{
	Assert(size);
	Assert(caption);

	gfx_get_string_bounding_box(caption, &sysfont, &size->x, &size->y);

	/* Add two pixel padding to ensure the outer radio button circle is not
	 * overlapped when multiple widgets are placed underneath each other */
	size->x += WTK_RADIOBUTTON_CAPTION_X + 2;
	size->y += WTK_RADIOBUTTON_CAPTION_Y + 2;

	/* Clamp Y height to minimum radio button size */
	if (size->y < (WTK_RADIOBUTTON_BUTTON_Y + WTK_RADIOBUTTON_RADIUS + 2)) {
		size->y = WTK_RADIOBUTTON_BUTTON_Y + WTK_RADIOBUTTON_RADIUS + 2;
	}
}

/**
 * This function creates a new radio button widget. It allocates required memory
 * and intializes necessary windows to create the widget. If there is not enough
 * memory, the function returns NULL.
 * To destroy the widget and all its contents, and free its memory, call
 * win_destroy() on the radio button's child reference, given by
 * wtk_radio_button_as_child(), like this:
 * "win_destroy(wtk_radio_button_as_child(myButtonPtr));".
 * Usually it will be destroyed automatically when it's parent is destroyed.
 *
 * \param parent Parent window, possibly wtk_frame_as_parent(myFramePtr).
 * \param area Area of the internal contents.
 * \param caption Pointer to caption string. Will be copied into widget.
 * \param selected Initial state of radio button, true if checked/selected.
 * \param group Radio button group to be a member of.
 * \param command Command to send to parent window. Must be non-zero to be
 *                enabled.
 *
 * \return Pointer to radio button, or NULL if failed.
 */
struct wtk_radio_button *wtk_radio_button_create(struct win_window *parent,
		struct win_area const *area,
		char const *caption,
		bool selected,
		struct wtk_radio_group *group, win_command_t command)
{
	struct wtk_radio_button *radio_button;
	struct win_attributes attr;

	Assert(group);
	Assert(area);
	Assert(caption);
	Assert(parent);

	/* Allocate memory for check box control data. */
	radio_button = membag_alloc(sizeof(struct wtk_radio_button));
	if (!radio_button) {
		goto outofmem_radio_button;
	}

	radio_button->state = WTK_RADIOBUTTON_NORMAL;
	radio_button->group = group;
	radio_button->command = command;

	/* Allocate memory for caption string, and copy text. */
	radio_button->caption = membag_alloc(
			(strlen(caption) + 1) * sizeof(char));
	if (!radio_button->caption) {
		goto outofmem_caption;
	}

	wtk_copy_string(radio_button->caption, caption);

	/* Handling information. */
	attr.event_handler = wtk_radio_button_handler;
	attr.custom = radio_button;

	/* Prepare container frame. */
	attr.area = *area;
	attr.background = NULL;
	attr.behavior = WIN_BEHAVIOR_REDRAW_PARENT;

	radio_button->container = win_create(parent, &attr);
	if (!radio_button->container) {
		goto outofmem_container;
	}

	/* Select the radio button in the group if either no radio button is
	 * currently selected (empty group), or the user has requested it takes
	 * over the selection */
	if (selected || (group->selected == NULL)) {
		wtk_radio_button_select(radio_button);
	}

	/* Make sure we haven't filled up the group reference count, and
	 * increment. */
	Assert(group->num_references < (wtk_radio_group_size_t)-1L);
	++(group->num_references);

	return radio_button;

outofmem_container:
	membag_free(radio_button->caption);

outofmem_caption:
	membag_free(radio_button);

outofmem_radio_button:
	return NULL;
}

/**
 * This function retrieves a pointer to the currently selected radio button
 * in a radio group.
 *
 * \return Pointer to the selected radio button in a radio button group,
 *         or NULL if no item is selected.
 */
struct wtk_radio_button *wtk_radio_group_get_selected(struct wtk_radio_group *group)
{
	Assert(group);

	return group->selected;
}

/**
 * This function creates a new radio button group, allocating required memory
 * and properly initializing the object. If there is not enough memory, the
 * function returns NULL.
 * The radio button group will keep a reference count for its members, and
 * will be automatically destroyed when the last member is destroyed.
 *
 * \return Pointer to radio button group, or NULL if failed.
 */
struct wtk_radio_group *wtk_radio_group_create(void)
{
	/* Allocate memory for radio group data. */
	struct wtk_radio_group *radio_group
		= membag_alloc(sizeof(struct wtk_radio_group));
	if (!radio_group) {
		goto outofmem_radio_group;
	}

	/* Initialize. */
	radio_group->num_references = 0;
	radio_group->selected = NULL;

	return radio_group;

outofmem_radio_group:
	return NULL;
}

/** @} */
