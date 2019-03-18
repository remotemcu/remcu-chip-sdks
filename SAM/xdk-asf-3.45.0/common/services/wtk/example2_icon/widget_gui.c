/**
 * \file
 *
 * \brief Display demo widget application
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
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <string.h>
#include "widget_gui.h"
#include "chip_icon1.h"
#include "chip_icon2.h"
#include "chip_icon3.h"

/**
 * \weakgroup app_widget_group
 *
 * @{
 */

/**
 * \brief Command event IDs
 *
 * \note The first entry in this enum is zero-valued, and therefore reserved for
 * widgets that should not issue command events. \sa wtk_group
 */
enum command_id {
	/** Unused command event ID. */
	DUMMY_ID,
	/** Command event ID for first icon button */
	ICON_BUTTON_1_ID,
	/** Command event ID for second icon button */
	ICON_BUTTON_2_ID,
	/** Command event ID for third icon button */
	ICON_BUTTON_3_ID,
	/** Command event ID for previous icon button */
	BUTTON_PREV_ID,
	/** Command event ID for next icon button */
	BUTTON_NEXT_ID,
	/** Command event ID for select icon button */
	BUTTON_SELECT_ID
};

#define TOTAL_NUM_ICONS    3

/** Widget application context */
struct widget_context {
	/** Pointer to frame for application */
	struct wtk_basic_frame *frame;
	/** Frame background object */
	struct gfx_bitmap frame_bg;
	/* Group of icon button widgets */
	struct wtk_icon_group *icon_group;
	/* Array if icon button widgets */
	struct wtk_icon_button *icons[TOTAL_NUM_ICONS];
	/** Label widget for user selection feedback */
	struct wtk_label *lbl_selected;
};

/** Statically allocated context pointer */
static struct widget_context *widget_ctx;

/**
 * \brief Frame handler for the application
 *
 * Handles all command events from the widgets in the application frame.
 *
 * \sa wtk_basic_frame_command_handler_t
 *
 * \param frame Pointer to the application frame
 * \param command_data Command event ID
 *
 * \return True if exiting, to destroy the window
 */
static bool widget_frame_command_handler(struct wtk_basic_frame *frame,
		win_command_t command_data)
{
	struct widget_context *widget;
	char command;

	widget = (struct widget_context *)wtk_basic_frame_get_custom_data(frame);
	command = (uintptr_t)command_data;

	struct wtk_icon_button *selected_icon;
	uint8_t selected_icon_index = 0;

	selected_icon = wtk_icon_group_get_selected(widget->icon_group);
	if (selected_icon) {
		selected_icon_index =
				(uintptr_t)wtk_icon_button_get_command(selected_icon) -
				ICON_BUTTON_1_ID;
	}

	switch (command) {
	case ICON_BUTTON_1_ID:
		wtk_label_change(widget->lbl_selected, "Icon 1 selected.");
		break;

	case ICON_BUTTON_2_ID:
		wtk_label_change(widget->lbl_selected, "Icon 2 selected.");
		break;

	case ICON_BUTTON_3_ID:
		wtk_label_change(widget->lbl_selected, "Icon 3 selected.");
		break;

	case BUTTON_PREV_ID:
		/* Cycle the selected icon to the previous icon in the array, or set it
		 * to the last icon in the array if nothing currently selected */
		if ((selected_icon == NULL) || (selected_icon_index == 0)) {
			selected_icon = widget->icons[TOTAL_NUM_ICONS - 1];
		} else {
			selected_icon = widget->icons[selected_icon_index - 1];
		}

		wtk_icon_button_select(selected_icon);

		break;

	case BUTTON_NEXT_ID:
		/* Cycle the selected icon to the next icon in the array, or set it
		 * to the first icon in the array if nothing currently selected */
		if ((selected_icon == NULL) ||
				(selected_icon_index == (TOTAL_NUM_ICONS - 1))) {
			selected_icon = widget->icons[0];
		} else {
			selected_icon = widget->icons[selected_icon_index + 1];
		}

		wtk_icon_button_select(selected_icon);

		break;

	case BUTTON_SELECT_ID:
		if (selected_icon != NULL) {
			struct win_command_event icon_command;

			/* Create a command event with the selected icon's ID */
			icon_command.sender = wtk_icon_button_as_child(selected_icon);
			icon_command.recipient = icon_command.sender;
			icon_command.data = wtk_icon_button_get_command(selected_icon);

			/* Queue up the created command event in the window manager */
			win_queue_command_event(&icon_command);
		}

		break;
	}

	return false;
}

/**
 * \brief Setup widget demo
 *
 * Allocates memory for the application context, and creates all widgets that
 * make up its interface. If memory allocation or widget creation fails, the
 * application exits immediately.
 *
 * \return Boolean true if the application was launched successfully, false if
 *         a memory allocation occurred.
 */
bool app_widget_launch(void)
{
	struct win_window *parent;
	struct win_area area;
	struct wtk_button *btn;

	char default_label_caption[] = "Please Select an Icon.";

	/* Create a new context for the GUI */
	widget_ctx = membag_alloc(sizeof(struct widget_context));
	if (!widget_ctx) {
		return false;
	}

	/* Initialize context data. */
	widget_ctx->frame_bg.type = GFX_BITMAP_SOLID;
	widget_ctx->frame_bg.data.color = GFX_COLOR_WHITE;

	/* Set the area for the GUI window */
	area = win_get_attributes(win_get_root())->area;
	win_inflate_area(&area, -20);

	/* Create and show the main GUI frame */
	widget_ctx->frame = wtk_basic_frame_create(
			win_get_root(), &area, &widget_ctx->frame_bg, NULL,
			widget_frame_command_handler, widget_ctx);
	if (!widget_ctx->frame) {
		goto error_frame;
	}

	parent = wtk_basic_frame_as_child(widget_ctx->frame);
	win_show(parent);

	/* Create a logical group for the icon buttons */
	widget_ctx->icon_group = wtk_icon_group_create();
	if (!widget_ctx->icon_group) {
		goto error_widget;
	}

	/* Update area for the first icon button widget */
	area.pos.x = 10;
	area.pos.y = 20;
	area.size.x = 0;

	/* Create the icons and display them in the GUI */
	for (uint8_t i = 0; i < TOTAL_NUM_ICONS; i++) {
		/* Temporary array of all the icon images that will be used */
		struct gfx_bitmap *icon_images[TOTAL_NUM_ICONS]
			= {&chip_icon1, &chip_icon2, &chip_icon3};

		/* Adjust the area for the next icon to create */
		area.pos.x += area.size.x + 10;
		wtk_icon_button_size_hint(&area.size, icon_images[i]);

		/* Create the next icon button inside frame */
		widget_ctx->icons[i] = wtk_icon_button_create(parent, &area,
				icon_images[i], false, widget_ctx->icon_group,
				(win_command_t)(ICON_BUTTON_1_ID + i));
		if (!widget_ctx->icons[i]) {
			goto error_widget;
		}

		win_show(wtk_icon_button_as_child(widget_ctx->icons[i]));
	}

	/* Update area for the label widget */
	area.pos.x = 20;
	area.pos.y += area.size.y + 20;
	wtk_label_size_hint(&area.size, default_label_caption);

	/* Create label inside frame */
	widget_ctx->lbl_selected = wtk_label_create(
			parent, &area, default_label_caption,
			GFX_COLOR_BLACK, NULL, false);
	if (!widget_ctx->lbl_selected) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx->lbl_selected));

	/* Update area for the button widgets */
	area.pos.y += area.size.y + 20;
	area.pos.x = 20;
	area.size.x = 60;
	area.size.y = 40;

	/* Create the buttons and display them in the GUI */
	for (uint8_t i = 0; i < 3; i++) {
		/* Temporary array of all the button captions that will be used */
		const char *nav_btn_captions[] = {"Previous", "Next", "Select"};

		/* Create the next button inside frame */
		btn = wtk_button_create(parent, &area, nav_btn_captions[i],
				(win_command_t)(BUTTON_PREV_ID + i));
		if (!btn) {
			goto error_widget;
		}

		win_show(wtk_button_as_child(btn));

		/* Adjust the area for the next button to create */
		area.pos.x += area.size.x + 20;
	}

	return true;

	/* Error handling to clean up allocations after an error */
error_widget:
	win_destroy(wtk_basic_frame_as_child(widget_ctx->frame));
error_frame:
	membag_free(widget_ctx);
	
	return false;
}

/** @} */
