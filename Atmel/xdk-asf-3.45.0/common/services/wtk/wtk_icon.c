/**
 * \file
 *
 * \brief Icon button widget implementation
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
 * \ingroup wtk_icon_button_group
 * @{
 */

/** Valid states for icon button, relevant to pointer and keyboard operations.
 * \internal
 */
enum wtk_icon_button_state {
	/** Normal state, no highlight or press. */
	WTK_ICONBUTTON_NORMAL,
	/** Widget pressed, action occurs when released. */
	WTK_ICONBUTTON_PRESSED,
};

/**
 * This is the icon button group control struct. It contains the necessary
 * information about a icon button group, i.e. number of members in the group
 * and the current selected one.
 *
 * \note Structure fields are only internally accessible, only pointers to
 *       structure is needed externally.
 */
struct wtk_icon_group {
	/** Number of members in this group. */
	wtk_icon_group_size_t num_references;
	/** Currently selected member. */
	struct wtk_icon_button *selected;
};

/**
 * This is the icon button control struct. It contains references to the
 * windows composing the icon button, as well as non-window information
 * required.
 *
 * \note Structure fields are only internally accessible, only pointers to
 *       structure is needed externally.
 */
struct wtk_icon_button {
	/** Container, ultimate widget parent. */
	struct win_window *container;
	/** Reference to the group we are member of. */
	struct wtk_icon_group *group;
	/** Current state. */
	enum wtk_icon_button_state state;
	/** Command to send. Must be non-zero to be enabled. */
	win_command_t command;
};

/**
 * This function returns a reference to the window that should be used when
 * managing the widget, such as move, resize, destroy and reparenting.
 *
 * \param icon_button Icon button widget to manage.
 *
 * \return Window to be used for managing the icon button.
 */
struct win_window *wtk_icon_button_as_child(struct wtk_icon_button
		*icon_button)
{
	Assert(icon_button);
	return icon_button->container;
}

/**
 * This function returns the window command of the specified icon button, as set
 * when the widget was created.
 *
 * \param icon_button Icon button widget to manage.
 *
 * \return Associated window command of the icon button widget.
 */
win_command_t wtk_icon_button_get_command(struct wtk_icon_button *icon_button)
{
	Assert(icon_button);
	return icon_button->command;
}

/**
 * This function sets this icon button to be the single icon button
 * selected within its group. If another icon button was selected, it
 * will be deselected. Both widgets will be redrawn if visible.
 *
 * \param icon_button Icon button widget to select.
 */
void wtk_icon_button_select(struct wtk_icon_button *icon_button)
{
	struct wtk_icon_button *old_selected;

	Assert(icon_button);

	/* Nothing to do if already selected. */
	if (icon_button->group->selected == icon_button) {
		return;
	}

	/* Change selection and redraw both. */
	old_selected = icon_button->group->selected;
	icon_button->group->selected = icon_button;
	if (old_selected) {
		win_redraw(old_selected->container);
	}

	win_redraw(icon_button->container);
}

/**
 * This function returns true if the icon button is the one currently
 * selected within its icon button group.
 *
 * \return True if icon button selected.
 */
bool wtk_icon_button_is_selected(struct wtk_icon_button const *icon_button)
{
	Assert(icon_button);
	return (icon_button->group->selected == icon_button);
}

/**
 * This function is the window event handler for icon button widgets.
 * It handles all events sent to the windows composing the widget.
 *
 * \param win Window receiving the event.
 * \param type The event type.
 * \param data Custom data, depending on event type.
 *
 * \return True if the event was recognized and accepted.
 */
static bool wtk_icon_button_handler(struct win_window *win,
		enum win_event_type type, void const *data)
{
	struct win_command_event command;

	/* Custom data for windows of a widget points back to the widget itself. */
	struct wtk_icon_button *icon_button
		= (struct wtk_icon_button *)win_get_custom_data(win);

	switch (type) {
	case WIN_EVENT_DRAW:
	{
		/* For DRAW events, the data parameter points to the
		 * clipping region.
		 */
		struct win_clip_region const *clip
			= (struct win_clip_region const *)data;
		struct win_area const *area = win_get_area(win);

		/* There should not be other windows in this widget. */
		Assert(win == icon_button->container);

		/* Draw icon button select marker if selected. */
		if (icon_button->group->selected == icon_button) {
			gfx_draw_rect(clip->origin.x, clip->origin.y,
					area->size.x, area->size.y,
					WTK_ICONBUTTON_SELECT_COLOR);
		}

		/* Always accept DRAW events, as the return value is
		 * ignored anyway for that event type.
		 */
		return true;
	}

	case WIN_EVENT_POINTER:
	{
		/* There should not be other windows in this widget. */
		Assert(win == icon_button->container);

		/* For POINTER events, the data parameter points to the
		 * pointer event information.
		 */
		struct win_pointer_event const *event
			= (struct win_pointer_event const *)data;

		switch (event->type) {
		case WIN_POINTER_PRESS:

			/* When icon button pressed, grab pointer and
			 * wait for release inside widget borders.
			 * Other widgets won't get pointer events
			 * before it is released, and the pointer
			 * ungrabbed by us.
			 */
			if (icon_button->state ==
					WTK_ICONBUTTON_NORMAL) {
				win_grab_pointer(icon_button->container);
				icon_button->state
					= WTK_ICONBUTTON_PRESSED;
				win_redraw(icon_button->container);
			}

			break;

		case WIN_POINTER_RELEASE:

			/* When button released, take action only if
			 * released inside widget extents.
			 */
			if (icon_button->state ==
					WTK_ICONBUTTON_PRESSED) {
				bool is_inside;

				/* Ungrab pointer. */
				win_grab_pointer(NULL);
				icon_button->state
					= WTK_ICONBUTTON_NORMAL;
				win_redraw(icon_button->container);

				/* Check release position. */
				is_inside = win_is_inside_window
							(icon_button->
							container,
							&(event->pos));

				/* Select this icon button if inside. */
				if (is_inside) {
					wtk_icon_button_select
						(icon_button);

					/* Send non-zero command. */
					if (icon_button->command) {
						command.sender
							= icon_button->
								container;
						command.recipient
							= icon_button->
								container;
						command.data
							= icon_button->command;
						win_queue_command_event
							(&command);
					}
				}
			}

			break;

		default:
			break;
		}

		/* Accept all POINTER events since all activity inside
		 * the widget extents is relevant to us.
		 */
		return true;
	}

	case WIN_EVENT_DESTROY:
		/* There should not be other windows in this widget. */
		Assert(win == icon_button->container);

		/* Destroy icon group as well if we are the last one in the
		 * group. If not, remove ourselves from the group.
		 */
		--(icon_button->group->num_references);
		if (!icon_button->group->num_references) {
			membag_free(icon_button->group);
		} else {
			if (icon_button->group->selected == icon_button) {
				icon_button->group->selected = NULL;
			}
		}

		membag_free(icon_button);

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
 * the full widget icon image.
 *
 * \retval size   Suggested size for the widget
 * \param icon_image Pointer to icon image to use for widget.
 */
void wtk_icon_button_size_hint(struct win_point *size, const struct gfx_bitmap *icon_image)
{
	Assert(size);
	Assert(icon_image);

	size->x = icon_image->width;
	size->y = icon_image->height;
}

/**
 * This function creates a new icon button widget. It allocates required memory
 * and initializes necessary windows to create the widget. If there is not enough
 * memory, the function returns NULL.
 * To destroy the widget and all its contents, and free its memory, call
 * win_destroy() on the icon button's child reference, given by
 * wtk_icon_button_as_child(), like this:
 * "win_destroy(wtk_icon_button_as_child(myButtonPtr));".
 * Usually it will be destroyed automatically when it's parent is destroyed.
 *
 * \param parent Parent window, possibly wtk_frame_as_parent(myFramePtr).
 * \param area Area of the internal contents.
 * \param icon Bitmap to draw as the icon.
 * \param selected Initial state of icon button, true if checked/selected.
 * \param group Icon button group to be a member of.
 * \param command Command to send to parent window. Must be non-zero to be
 *                enabled.
 *
 * \return Pointer to icon button, or NULL if failed.
 */
struct wtk_icon_button *wtk_icon_button_create(struct win_window *parent,
		struct win_area const *area, struct gfx_bitmap *icon,
		bool selected, struct wtk_icon_group *group, win_command_t command)
{
	struct wtk_icon_button *icon_button;
	struct win_attributes attr;

	Assert(group);
	Assert(area);
	Assert(icon);
	Assert(parent);

	/* Allocate memory for check box control data. */
	icon_button = membag_alloc(sizeof(struct wtk_icon_button));
	if (!icon_button) {
		goto outofmem_icon_button;
	}

	icon_button->state = WTK_ICONBUTTON_NORMAL;
	icon_button->group = group;
	icon_button->command = command;

	/* Handling information. */
	attr.event_handler = wtk_icon_button_handler;
	attr.custom = icon_button;

	/* Prepare container frame. */
	attr.area = *area;
	attr.background = icon;
	attr.behavior = 0;

	icon_button->container = win_create(parent, &attr);
	if (!icon_button->container) {
		goto outofmem_container;
	}

	/* Select the icon button in the group if either no icon button is
	 * currently selected (empty group), or the user has requested it takes
	 * over the selection */
	if (selected || (group->selected == NULL)) {
		/* Add ourselves to the icon group, take over selection if required. */
		wtk_icon_button_select(icon_button);
	}

	/* Make sure we haven't filled up the group reference count, and
	 * increment. */
	Assert(group->num_references < (wtk_icon_group_size_t)-1L);
	++(group->num_references);

	return icon_button;

outofmem_container:
	membag_free(icon_button);

outofmem_icon_button:
	return NULL;
}

/**
 * This function retrieves a pointer to the currently selected icon in an
 * icon group.
 *
 * \return Pointer to the selected icon button in an icon button group,
 *         or NULL if no item is selected.
 */
struct wtk_icon_button *wtk_icon_group_get_selected(struct wtk_icon_group *group)
{
	Assert(group);

	return group->selected;
}

/**
 * This function creates a new icon button group, allocating required memory
 * and properly initializing the object. If there is not enough memory, the
 * function returns NULL.
 * The icon button group will keep a reference count for its members, and
 * will be automatically destroyed when the last member is destroyed.
 *
 * \return Pointer to icon button group, or NULL if failed.
 */
struct wtk_icon_group *wtk_icon_group_create(void)
{
	/* Allocate memory for icon group data. */
	struct wtk_icon_group *icon_group
		= membag_alloc(sizeof(struct wtk_icon_group));
	if (!icon_group) {
		goto outofmem_icon_group;
	}

	/* Initialize. */
	icon_group->num_references = 0;
	icon_group->selected = NULL;

	return icon_group;

outofmem_icon_group:
	return NULL;
}

/** @} */
