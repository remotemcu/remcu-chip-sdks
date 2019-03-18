/**
 * \file
 *
 * \brief Time settings widget for SAM toolkit demo application.
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
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
 
#include "demo.h"
#include <asf.h>
#include "string.h"
#include "bitmaps.h"

/** Total number of time settings widget labels */
#define TOTAL_NUM_TIME_LABEL    6

/**
 * \brief Command event IDs for time settings widget.
 */
enum time_command_id {
	/** Dummy icon */
	ICON_DUMMY_ID = 0,
	/** Command event ID for hour up icon button */
	ICON_SETTINGS_TIME_HOUR_UP_ID,
	/** Command event ID for minutes up icon button */
	ICON_SETTINGS_TIME_MIN_UP_ID,
	/** Command event ID for second up icon button */
	ICON_SETTINGS_TIME_SEC_UP_ID,
	/** Command event ID for hour down icon button */
	ICON_SETTINGS_TIME_HOUR_DOWN_ID,
	/** Command event ID for minutes down icon button */
	ICON_SETTINGS_TIME_MIN_DOWN_ID,
	/** Command event ID for second down icon button */
	ICON_SETTINGS_TIME_SEC_DOWN_ID,	
	/** Command event ID for second icon button */
	ICON_SETTINGS_TIME_RET_ID,
	/** Max time settings icon number */
	ICON_SETTINGS_TIME_MAX_ID,
};

/**
 * \brief Label widget IDs.
 */
enum time_settings_label_type {
	/** Hour label ID */
	LABEL_HOUR_ID = 0,
	/** Minute label ID */
	LABEL_MIN_ID,
	/** Second label ID */
	LABEL_SEC_ID,
};

/** Time settings widget context */
struct widget_context_settings_time {
	/** Pointer to frame for application */
	struct wtk_basic_frame *frame;
	/** Frame background object */
	struct gfx_bitmap frame_bg;
	/** Pointer to logo frame */
	struct wtk_basic_frame *logo_frame;
	/** Label widget for board name */
	struct wtk_label *lbl_board_name;
	/** Label widget for time settings function string */
	struct wtk_label *lbl_func_name;
	/* Group of icon button widgets */
	struct wtk_icon_group *icon_group;
	/* Array if icon button widgets */
	struct wtk_icon_button *icons[ICON_SETTINGS_TIME_MAX_ID];
	/** Label widget for indications */
	struct wtk_label *lbl_indication[TOTAL_NUM_TIME_LABEL];
};

/** Statically allocated context pointer */
static struct widget_context_settings_time *widget_ctx_settings_time;

/** Function name string */
static char demo_func_name[] = "Set Time";

/** String array for hour */
static char str_hour[3];

/** String array for minutes */
static char str_min[3];

/** String array for second */
static char str_sec[3];

/** Root logo bitmap */
static struct gfx_bitmap win_root_logo_icon = {
	.width = 87, .height=40,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_LOGO_ATMEL
};

/** Hour up icon bitmap */
static struct gfx_bitmap win_settings_time_hour_up_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_UP
};

/** Minutes up icon bitmap */
static struct gfx_bitmap win_settings_time_min_up_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_UP
};

/** Second up icon bitmap */
static struct gfx_bitmap win_settings_time_sec_up_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_UP
};

/** Hour down icon bitmap */
static struct gfx_bitmap win_settings_time_hour_down_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_DOWN
};


/** Mintues down icon bitmap */
static struct gfx_bitmap win_settings_time_min_down_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_DOWN
};

/** Second down icon bitmap */
static struct gfx_bitmap win_settings_time_sec_down_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_DOWN
};

/** Return to up layer screen icon bitmap */
static struct gfx_bitmap win_settings_time_ret_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_BACK
};

/**
 * \brief Frame handler for the application.
 *
 * Handles all command events from the widgets in the application frame.
 *
 * \param frame Pointer to the application frame
 * \param command_data Command event ID
 *
 * \return True if exiting, to destroy the window
 */
static bool widget_settings_time_setup_command_handler(struct wtk_basic_frame *frame,
		win_command_t command_data)
{
	struct widget_context_settings_time *widget;
	char command;
	widget = (struct widget_context_settings_time *)wtk_basic_frame_get_custom_data(frame);
	command = (uintptr_t)command_data;

	switch (command) {
	case ICON_SETTINGS_TIME_HOUR_UP_ID:
		g_demo_parameters.hour++;
		if (g_demo_parameters.hour == 24) {
			g_demo_parameters.hour = 0;
		}
		snprintf( str_hour, sizeof( str_hour ), "%02u",g_demo_parameters.hour);
		wtk_label_change(widget->lbl_indication[0], str_hour);
		break;

	case ICON_SETTINGS_TIME_MIN_UP_ID:
		g_demo_parameters.minute++;
		if (g_demo_parameters.minute == 60) {
			g_demo_parameters.minute = 0;
		}
		snprintf( str_min, sizeof( str_min ), "%02u",g_demo_parameters.minute);
		wtk_label_change(widget->lbl_indication[1], str_min);
		break;

	case ICON_SETTINGS_TIME_SEC_UP_ID:
		g_demo_parameters.second++;
		if (g_demo_parameters.second == 60) {
			g_demo_parameters.second = 0;
		}
		snprintf( str_sec, sizeof( str_sec ), "%02u",g_demo_parameters.second);
		wtk_label_change(widget->lbl_indication[2], str_sec);
		break;

	case ICON_SETTINGS_TIME_HOUR_DOWN_ID:
		if (g_demo_parameters.hour == 0) {
			g_demo_parameters.hour = 23;
		} else {
			g_demo_parameters.hour--;
		}
		snprintf( str_hour, sizeof( str_hour ), "%02u",g_demo_parameters.hour);
		wtk_label_change(widget->lbl_indication[0], str_hour);
		break;

	case ICON_SETTINGS_TIME_MIN_DOWN_ID:
		if (g_demo_parameters.minute == 0) {
			g_demo_parameters.minute = 60;
		}

		g_demo_parameters.minute--;

		snprintf( str_min, sizeof( str_min ), "%02u",g_demo_parameters.minute);
		wtk_label_change(widget->lbl_indication[1], str_min);
		break;

	case ICON_SETTINGS_TIME_SEC_DOWN_ID:
		if (g_demo_parameters.second== 0) {
			g_demo_parameters.second = 60;
		}

		g_demo_parameters.second--;

		snprintf( str_sec, sizeof( str_sec ), "%02u",g_demo_parameters.second);
		wtk_label_change(widget->lbl_indication[2], str_sec);
		break;

	case ICON_SETTINGS_TIME_RET_ID:
		/* Update RTC time */
		rtc_set_time(RTC,  g_demo_parameters.hour, g_demo_parameters.minute, g_demo_parameters.second );

		/* Commit update demo parameters */
		demo_parameters_commit_changes();

		/* Turn off time settings widget */
		app_widget_settings_time_on(false);

		/* Turn on settings widget */
		app_widget_settings_on(true);
		break;
	}
	return false;
}

/**
 * \brief Setup time settings widget.
 *
 * Allocates memory for the application context, and creates all widgets that
 * make up its interface. If memory allocation or widget creation fails, the
 * application exits immediately.
 */
static void app_widget_launch_settings_time(void)
{
	struct win_window *parent;
	struct win_area area;
	uint32_t hour, minute, second;

	/* Setup RTC time */
	rtc_get_time( RTC, &hour, &minute, &second );
	snprintf( str_hour, sizeof( str_hour ), "%02u",hour);
	snprintf( str_min, sizeof( str_min ), "%02u",minute);
	snprintf( str_sec, sizeof( str_sec ), "%02u",second);

	/* Create a new context for the GUI, clear new context state */
	widget_ctx_settings_time = membag_alloc(sizeof(struct widget_context_settings_time));

	/* Set the background information for the GUI window */
	widget_ctx_settings_time->frame_bg.type = GFX_BITMAP_SOLID;
	widget_ctx_settings_time->frame_bg.data.color = GFX_COLOR(255, 255, 255);

	/* Set the area for the GUI window */
	area = win_get_attributes(win_get_root())->area;

	/* Create and show the main GUI frame */
	widget_ctx_settings_time->frame = wtk_basic_frame_create(
			win_get_root(), &area, &widget_ctx_settings_time->frame_bg, NULL,
			widget_settings_time_setup_command_handler, widget_ctx_settings_time);
	if (!widget_ctx_settings_time->frame) {
		goto error_frame;
	}

	parent = wtk_basic_frame_as_child(widget_ctx_settings_time->frame);
	win_show(parent);

	/* Update area for the logo frame */
	area.pos.x = 0;
	area.pos.y = 0;
	area.size.x = 87;
	area.size.y = 40;
	widget_ctx_settings_time->logo_frame = wtk_basic_frame_create(
			parent, &area, &win_root_logo_icon, NULL,
			NULL, NULL);
	if (!widget_ctx_settings_time->frame) {
		goto error_frame;
	}

	win_show(wtk_basic_frame_as_child(widget_ctx_settings_time->logo_frame));

	/* Update area for the board name label widget */
	area.pos.x = 100;
	area.pos.y = 0;
	wtk_label_size_hint(&area.size, demo_board_name);

	/* Create label inside frame */
	widget_ctx_settings_time->lbl_board_name = wtk_label_create(
			parent, &area, demo_board_name,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_settings_time->lbl_board_name) {
		goto error_widget;
	}
	
	win_show(wtk_label_as_child(widget_ctx_settings_time->lbl_board_name));

	/* Update area for the label of function name */
	area.pos.x = 100;
	area.pos.y = 20;
	wtk_label_size_hint(&area.size, demo_func_name);

	/* Create label inside frame */
	widget_ctx_settings_time->lbl_func_name = wtk_label_create(
			parent, &area, demo_func_name,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_settings_time->lbl_func_name) {
		goto error_widget;
	}
	
	win_show(wtk_label_as_child(widget_ctx_settings_time->lbl_func_name));

	/* Create a logical group for the icon buttons */
	widget_ctx_settings_time->icon_group = wtk_icon_group_create();
	if (!widget_ctx_settings_time->icon_group) {
		goto error_widget;
	}

	/* Update area for the hour up icon button widget */
	area.pos.x = 43;
	area.pos.y = 60;
	area.size.x = 0;
	wtk_icon_button_size_hint(&area.size, &win_settings_time_hour_up_icon);

	/* Create the icon button inside frame */
	widget_ctx_settings_time->icons[ICON_SETTINGS_TIME_HOUR_UP_ID] = wtk_icon_button_create(parent, &area,
			&win_settings_time_hour_up_icon, false, widget_ctx_settings_time->icon_group,
			(win_command_t)(ICON_SETTINGS_TIME_HOUR_UP_ID));
	if (!widget_ctx_settings_time->icons[ICON_SETTINGS_TIME_HOUR_UP_ID]) {
		goto error_widget;
	}
	
	win_show(wtk_icon_button_as_child(widget_ctx_settings_time->icons[ICON_SETTINGS_TIME_HOUR_UP_ID]));

	/* Update area for the minutes up icon button widget */
	area.pos.x = 104;
	area.pos.y = 60;
	wtk_icon_button_size_hint(&area.size, &win_settings_time_min_up_icon);

	/* Create the icon button inside frame */
	widget_ctx_settings_time->icons[ICON_SETTINGS_TIME_MIN_UP_ID] = wtk_icon_button_create(parent, &area,
			&win_settings_time_min_up_icon, false, widget_ctx_settings_time->icon_group,
			(win_command_t)(ICON_SETTINGS_TIME_MIN_UP_ID));
	if (!widget_ctx_settings_time->icons[ICON_SETTINGS_TIME_MIN_UP_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_settings_time->icons[ICON_SETTINGS_TIME_MIN_UP_ID]));

	/* Update area for the second up icon button widget */
	area.pos.x = 162;
	area.pos.y = 60;
	wtk_icon_button_size_hint(&area.size, &win_settings_time_sec_up_icon);

	/* Create the icon button inside frame */
	widget_ctx_settings_time->icons[ICON_SETTINGS_TIME_SEC_UP_ID] = wtk_icon_button_create(parent, &area,
			&win_settings_time_sec_up_icon, false, widget_ctx_settings_time->icon_group,
			(win_command_t)(ICON_SETTINGS_TIME_SEC_UP_ID));
	if (!widget_ctx_settings_time->icons[ICON_SETTINGS_TIME_SEC_UP_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_settings_time->icons[ICON_SETTINGS_TIME_SEC_UP_ID]));

	/* Update area for the hour indicator label */
	area.pos.x = 55;
	area.pos.y = 135;
	wtk_label_size_hint(&area.size, str_hour);

	/* Create label inside frame */
	widget_ctx_settings_time->lbl_indication[LABEL_HOUR_ID] = wtk_label_create(
			parent, &area, str_hour,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_settings_time->lbl_indication[LABEL_HOUR_ID]) {
		goto error_widget;
	}
	win_show(wtk_label_as_child(widget_ctx_settings_time->lbl_indication[LABEL_HOUR_ID]));

	/* Update area for the minute indicator label */
	area.pos.x = 116;
	area.pos.y = 135;
	wtk_label_size_hint(&area.size, str_min);

	/* Create label inside frame */
	widget_ctx_settings_time->lbl_indication[LABEL_MIN_ID] = wtk_label_create(
			parent, &area, str_min,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_settings_time->lbl_indication[LABEL_MIN_ID]) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_settings_time->lbl_indication[LABEL_MIN_ID]));

	/* Update area for the second indicator label */
	area.pos.x = 174;
	area.pos.y = 135;
	wtk_label_size_hint(&area.size, str_sec);

	/* Create label inside frame */
	widget_ctx_settings_time->lbl_indication[LABEL_SEC_ID] = wtk_label_create(
			parent, &area, str_sec,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_settings_time->lbl_indication[LABEL_SEC_ID]) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_settings_time->lbl_indication[LABEL_SEC_ID]));	


	/* Adjust the area for the hour down icon to create */
	area.pos.x = 43;
	area.pos.y = 164;
	wtk_icon_button_size_hint(&area.size, &win_settings_time_hour_down_icon);

	/* Create the icon button inside frame */
	widget_ctx_settings_time->icons[ICON_SETTINGS_TIME_HOUR_DOWN_ID] = wtk_icon_button_create(parent, &area,
			&win_settings_time_hour_down_icon, false, widget_ctx_settings_time->icon_group,
			(win_command_t)(ICON_SETTINGS_TIME_HOUR_DOWN_ID));
	if (!widget_ctx_settings_time->icons[ICON_SETTINGS_TIME_HOUR_DOWN_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_settings_time->icons[ICON_SETTINGS_TIME_HOUR_DOWN_ID]));


	/* Adjust the area for the minutes down icon to create */
	area.pos.x = 104;
	area.pos.y = 164;
	wtk_icon_button_size_hint(&area.size, &win_settings_time_min_down_icon);

	/* Create the icon button inside frame */
	widget_ctx_settings_time->icons[ICON_SETTINGS_TIME_MIN_DOWN_ID] = wtk_icon_button_create(parent, &area,
			&win_settings_time_min_down_icon, false, widget_ctx_settings_time->icon_group,
			(win_command_t)(ICON_SETTINGS_TIME_MIN_DOWN_ID));
	if (!widget_ctx_settings_time->icons[ICON_SETTINGS_TIME_MIN_DOWN_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_settings_time->icons[ICON_SETTINGS_TIME_MIN_DOWN_ID]));

	/* Adjust the area for the second down icon to create */
	area.pos.x = 162;
	area.pos.y = 164;
	wtk_icon_button_size_hint(&area.size, &win_settings_time_sec_down_icon);

	/* Create the icon button inside frame */
	widget_ctx_settings_time->icons[ICON_SETTINGS_TIME_SEC_DOWN_ID] = wtk_icon_button_create(parent, &area,
			&win_settings_time_sec_down_icon, false, widget_ctx_settings_time->icon_group,
			(win_command_t)(ICON_SETTINGS_TIME_SEC_DOWN_ID));
	if (!widget_ctx_settings_time->icons[ICON_SETTINGS_TIME_SEC_DOWN_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_settings_time->icons[ICON_SETTINGS_TIME_SEC_DOWN_ID]));

	
	/* Adjust the area for the return icon to create */
	area.pos.x = 12;
	area.pos.y = 220;
	wtk_icon_button_size_hint(&area.size, &win_settings_time_ret_icon);

	/* Create the icon button inside frame */
	widget_ctx_settings_time->icons[ICON_SETTINGS_TIME_RET_ID] = wtk_icon_button_create(parent, &area,
			&win_settings_time_ret_icon, false, widget_ctx_settings_time->icon_group,
			(win_command_t)(ICON_SETTINGS_TIME_RET_ID));
	if (!widget_ctx_settings_time->icons[ICON_SETTINGS_TIME_RET_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_settings_time->icons[ICON_SETTINGS_TIME_RET_ID]));
	return;

	/* Error handling to clean up allocations after an error */
error_widget:
	win_destroy(wtk_basic_frame_as_child(widget_ctx_settings_time->frame));
error_frame:
	membag_free(widget_ctx_settings_time);
}

/**
 * \brief Enable/disable time settings widget.
 *
 * \param on Turn on/off time settings widget.
 */
void app_widget_settings_time_on(uint8_t on)
{
	if (on) {
		app_widget_launch_settings_time();
	} else {
		if (widget_ctx_settings_time->frame) {
			win_destroy(wtk_basic_frame_as_child(widget_ctx_settings_time->frame));
		}
	}

}
