/**
 * \file
 *
 * \brief Backlight settings widget for SAM toolkit demo application
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
 
#include "demo.h"
#include <asf.h>
#include "string.h"
#include "bitmaps.h"

/**
 * \brief Command event IDs for backlight settings widget.
 */
enum bkl_command_id {
	/** Dummy icon */
	ICON_DUMMY_ID = 0,
	/** Command event ID for baklight up icon button */
	ICON_SETTINGS_BACKLIGHT_UP_ID,
	/** Command event ID for backlight down icon button */
	ICON_SETTINGS_BACKLIGHT_DOWN_ID,
	/** Command event ID for return icon button */
	ICON_SETTINGS_BACKLIGHT_RET_ID,
	/** Max backling settings icon number */
	ICON_SETTINGS_BACKLIGHT_MAX_ID,	
};

/** Backlight settings widget context */
struct widget_context_settings_backlight {
	/** Pointer to frame for application */
	struct wtk_basic_frame *frame;
	/** Frame background object */
	struct gfx_bitmap frame_bg;
	/** Pointer to frame for the logo frame */
	struct wtk_basic_frame *logo_frame;
	/** Label widget for board name label */
	struct wtk_label *lbl_board_name;
	/** Label widget for backlight function string lable */
	struct wtk_label *lbl_func_name;
	/* Group of icon button widgets */
	struct wtk_icon_group *icon_group;
	/* Array if icon button widgets */
	struct wtk_icon_button *icons[ICON_SETTINGS_BACKLIGHT_MAX_ID];
};

/** Backlight settings function string */
static char demo_func_name[] = "Set Backlight";

/** Statically allocated context pointer */
static struct widget_context_settings_backlight *widget_ctx_settings_backlight;

/** Logo frame bitmap */
static struct gfx_bitmap win_root_logo_icon = {
	.width = 87, .height=40,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_LOGO_ATMEL
};

/** Backlight up icon bitmap */
static struct gfx_bitmap win_settings_backlight_up_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_UP
};

/** Backlight down icon bitmap */
static struct gfx_bitmap win_settings_backlight_down_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_DOWN
};


/** Function return bitmap */
static struct gfx_bitmap win_settings_backlight_ret_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_BACK
};

/**
 * \brief Frame handler for the backlight settings widget.
 *
 * Handles all command events from the widgets in the backlight frame.
 *
 * \param frame Pointer to the application frame
 * \param command_data Command event ID
 *
 * \return True if exiting, to destroy the window
 */
static bool widget_settings_backlight_setup_command_handler(struct wtk_basic_frame *frame,
		win_command_t command_data)
{
	char command;
	command = (uintptr_t)command_data;

	/* Remove warnings */
	UNUSED(frame);

	volatile uint32_t backlight_level = g_demo_parameters.backlight;

	switch (command) {
	case ICON_SETTINGS_BACKLIGHT_UP_ID:
		backlight_level ++;

		if (backlight_level >=  AAT31XX_MAX_BACKLIGHT_LEVEL)
			backlight_level = AAT31XX_MAX_BACKLIGHT_LEVEL;

		g_demo_parameters.backlight = backlight_level;
		aat31xx_set_backlight(backlight_level);

		break;

	case ICON_SETTINGS_BACKLIGHT_DOWN_ID:
		backlight_level --;

		if (backlight_level <=  AAT31XX_MIN_BACKLIGHT_LEVEL)
			backlight_level = AAT31XX_MIN_BACKLIGHT_LEVEL;

		 g_demo_parameters.backlight = backlight_level;
		aat31xx_set_backlight(backlight_level);
		break;

	case ICON_SETTINGS_BACKLIGHT_RET_ID:
		/* Update demo parameters */
		demo_parameters_commit_changes();

		/*Turn off backlight settings widget */
		app_widget_settings_backlight_on(false);

		/* Turn on settings widget */
		app_widget_settings_on(true);
		break;
	}
	return false;
}

/**
 * \brief Setup backlight settings widget.
 *
 * Allocates memory for the application context, and creates all widgets that
 * make up its interface. If memory allocation or widget creation fails, the
 * application exits immediately.
 */
static void app_widget_launch_settings_backlight(void)
{
	struct win_window *parent;
	struct win_area area;

	/* Create a new context for the GUI, clear new context state */
	widget_ctx_settings_backlight = membag_alloc(sizeof(struct widget_context_settings_backlight));

	/* Set the background information for the GUI window */
	widget_ctx_settings_backlight->frame_bg.type = GFX_BITMAP_SOLID;
	widget_ctx_settings_backlight->frame_bg.data.color = GFX_COLOR(255, 255, 255);

	/* Set the area for the GUI window */
	area = win_get_attributes(win_get_root())->area;

	/* Create and show the main GUI frame */
	widget_ctx_settings_backlight->frame = wtk_basic_frame_create(
			win_get_root(), &area, &widget_ctx_settings_backlight->frame_bg, NULL,
			widget_settings_backlight_setup_command_handler, widget_ctx_settings_backlight);
	if (!widget_ctx_settings_backlight->frame) {
		goto error_frame;
	}

	parent = wtk_basic_frame_as_child(widget_ctx_settings_backlight->frame);
	win_show(parent);

	/* Set the area for the logo frame */
	area.pos.x = 0;
	area.pos.y = 0;
	area.size.x = 87;
	area.size.y = 40;
	/* Create and show the main GUI frame */
	widget_ctx_settings_backlight->logo_frame = wtk_basic_frame_create(
			parent, &area, &win_root_logo_icon, NULL,
			NULL, NULL);
	if (!widget_ctx_settings_backlight->frame) {
		goto error_frame;
	}

	win_show(wtk_basic_frame_as_child(widget_ctx_settings_backlight->logo_frame));

	/* Update area for the board name label */
	area.pos.x = 100;
	area.pos.y = 0;
	wtk_label_size_hint(&area.size, demo_board_name);

	/* Create label inside frame */
	widget_ctx_settings_backlight->lbl_board_name = wtk_label_create(
			parent, &area, demo_board_name,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_settings_backlight->lbl_board_name) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_settings_backlight->lbl_board_name));

	/* Update area for the backlight settings label */
	area.pos.x = 100;
	area.pos.y = 20;
	wtk_label_size_hint(&area.size, demo_func_name);

	/* Create label inside frame */
	widget_ctx_settings_backlight->lbl_func_name = wtk_label_create(
			parent, &area, demo_func_name,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_settings_backlight->lbl_func_name) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_settings_backlight->lbl_func_name));

	/* Create a logical group for the icon buttons */
	widget_ctx_settings_backlight->icon_group = wtk_icon_group_create();
	if (!widget_ctx_settings_backlight->icon_group) {
		goto error_widget;
	}

	/* Update area for the backlight up icon button widget */
	area.pos.x = 98;
	area.pos.y = 80;
	area.size.x = 0;
	wtk_icon_button_size_hint(&area.size, &win_settings_backlight_up_icon);

	/* Create the icon button inside frame */
	widget_ctx_settings_backlight->icons[ICON_SETTINGS_BACKLIGHT_UP_ID] = wtk_icon_button_create(parent, &area,
			&win_settings_backlight_up_icon, false, widget_ctx_settings_backlight->icon_group,
			(win_command_t)(ICON_SETTINGS_BACKLIGHT_UP_ID));
	if (!widget_ctx_settings_backlight->icons[ICON_SETTINGS_BACKLIGHT_UP_ID]) {
		goto error_widget;
	}
	
	win_show(wtk_icon_button_as_child(widget_ctx_settings_backlight->icons[ICON_SETTINGS_BACKLIGHT_UP_ID]));


	/* Update area for the backlight down icon button widget */
	area.pos.x = 98;
	area.pos.y = 180;
	wtk_icon_button_size_hint(&area.size, &win_settings_backlight_down_icon);

	/* Create the next icon button inside frame */
	widget_ctx_settings_backlight->icons[ICON_SETTINGS_BACKLIGHT_DOWN_ID] = wtk_icon_button_create(parent, &area,
			&win_settings_backlight_down_icon, false, widget_ctx_settings_backlight->icon_group,
			(win_command_t)(ICON_SETTINGS_BACKLIGHT_DOWN_ID));
	if (!widget_ctx_settings_backlight->icons[ICON_SETTINGS_BACKLIGHT_DOWN_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_settings_backlight->icons[ICON_SETTINGS_BACKLIGHT_DOWN_ID]));


	/* Adjust the area for the return icon to create */
	area.pos.x = 12;
	area.pos.y = 220;

	wtk_icon_button_size_hint(&area.size, &win_settings_backlight_ret_icon);

	/* Create the next icon button inside frame */
	widget_ctx_settings_backlight->icons[ICON_SETTINGS_BACKLIGHT_RET_ID] = wtk_icon_button_create(parent, &area,
			&win_settings_backlight_ret_icon, false, widget_ctx_settings_backlight->icon_group,
			(win_command_t)(ICON_SETTINGS_BACKLIGHT_RET_ID));
	if (!widget_ctx_settings_backlight->icons[ICON_SETTINGS_BACKLIGHT_RET_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_settings_backlight->icons[ICON_SETTINGS_BACKLIGHT_RET_ID]));
	return;

	/* Error handling to clean up allocations after an error */
error_widget:
	win_destroy(wtk_basic_frame_as_child(widget_ctx_settings_backlight->frame));
error_frame:
	membag_free(widget_ctx_settings_backlight);
}


/**
 * \brief Enable/disable date settings widget.
 *
 * \param on Turn on/off date settings widget.
 */
void app_widget_settings_backlight_on(uint8_t on)
{
	if (on) {
		app_widget_launch_settings_backlight();
	} else {
		if (widget_ctx_settings_backlight->frame) {
			win_destroy(wtk_basic_frame_as_child(widget_ctx_settings_backlight->frame));
			}
	}

}
