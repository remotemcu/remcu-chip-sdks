/**
 * \file
 *
 * \brief Date settings widget for SAM toolkit demo application
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

/** Total number of date settings widget labels */
#define TOTAL_NUM_DATE_LABLE    6

/**
 * \brief Command event IDs for date settings widget.
 */
enum date_command_id {
	/** Dummy icon */
	ICON_DUMMY_ID = 0,
	/** Command event ID for year up icon */
	ICON_SETTINGS_DATE_YEAR_UP_ID,
	/** Command event ID for month up icon */
	ICON_SETTINGS_DATE_MONTH_UP_ID,
	/** Command event ID for date up icon */
	ICON_SETTINGS_DATE_DAY_UP_ID,
	/** Command event ID for year down icon */
	ICON_SETTINGS_DATE_YEAR_DOWN_ID,
	/** Command event ID for month down icon */
	ICON_SETTINGS_DATE_MONTH_DOWN_ID,
	/** Command event ID for date down icon */
	ICON_SETTINGS_DATE_DAY_DOWN_ID,
	/** Command event ID for screen return icon */
	ICON_SETTINGS_DATE_RET_ID,
	/** Max date settings icon number */
	ICON_SETTINGS_DATE_MAX_ID,	
};

/**
 * \brief Label widget IDs.
 */
enum time_command_id {
	/** Year label ID */
	LABEL_YEAR_ID = 0,
	/** Month label ID */
	LABEL_MONTH_ID,
	/** Date label ID */
	LABEL_DATE_ID,
};

/** Widget application context for date settings */
struct widget_context_settings_date {
	/** Pointer to frame for application */
	struct wtk_basic_frame *frame;
	/** Frame background object */
	struct gfx_bitmap frame_bg;
	/** Pointer to logo frame */
	struct wtk_basic_frame *logo_frame;
	/** Label widget for board name */
	struct wtk_label *lbl_board_name;
	/** Label widget for function name */
	struct wtk_label *lbl_func_name;
	/* Group of icon button widgets */
	struct wtk_icon_group *icon_group;
	/* Array if icon button widgets */
	struct wtk_icon_button *icons[ICON_SETTINGS_DATE_MAX_ID];
	/** Label widget for indication label */
	struct wtk_label *lbl_indication[TOTAL_NUM_DATE_LABLE];
};

/** Statically allocated context pointer */
static struct widget_context_settings_date *widget_ctx_settings_date;

/** Function name */
static char demo_func_date_name[] = "Set Date";

/** String array for day */
static char str_day[3];

/** String array for month */
static char str_month[3];

/** String array for year */
static char str_year[5];

/** Root logo bitmap */
static struct gfx_bitmap win_root_logo_icon = {
	.width = 87, .height = 40,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_LOGO_ATMEL
};

/** Year up icon bitmap */
static struct gfx_bitmap win_settings_date_year_up_icon = {
	.width = 48, .height = 48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_UP
};

/**  Month up icon bitmap */
static struct gfx_bitmap win_settings_date_month_up_icon = {
	.width = 48, .height = 48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_UP
};

/** Date up icon bitmap */
static struct gfx_bitmap win_settings_date_date_up_icon = {
	.width = 48, .height = 48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_UP
};

/** Year down icon bitmap */
static struct gfx_bitmap win_settings_date_year_down_icon = {
	.width = 48, .height = 48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_DOWN
};

/** Month down icon bitmap */
static struct gfx_bitmap win_settings_date_month_down_icon = {
	.width = 48, .height = 48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_DOWN
};

/** Date down icon bitmap */
static struct gfx_bitmap win_settings_date_date_down_icon = {
	.width = 48, .height = 48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_DOWN
};

/** Return icon bitmap */
static struct gfx_bitmap win_settings_date_ret_icon = {
	.width = 48, .height = 48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_BACK
};

/**
 * \brief Frame handler for the date settings widget.
 *
 * Handles all command events from the date settings widget.
 *
 * \param frame Pointer to the application frame
 * \param command_data Command event ID
 *
 * \return True if exiting, to destroy the window
 */
static bool widget_settings_date_setup_command_handler(
		struct wtk_basic_frame *frame,
		win_command_t command_data)
{
	struct widget_context_settings_date *widget;
	char command;

	widget = (struct widget_context_settings_date *)
			wtk_basic_frame_get_custom_data(
			frame);
	command = (uintptr_t)command_data;

	switch (command) {
	case ICON_SETTINGS_DATE_DAY_UP_ID:
		g_demo_parameters.day++;
		if (g_demo_parameters.day == 32) {
			g_demo_parameters.day = 1;
		}

		snprintf( str_day, sizeof(str_day), "%02u",
				g_demo_parameters.day);
		wtk_label_change(widget->lbl_indication[LABEL_DATE_ID], str_day);
		break;

	case ICON_SETTINGS_DATE_MONTH_UP_ID:
		g_demo_parameters.month++;
		if (g_demo_parameters.month == 13) {
			g_demo_parameters.month = 1;
		}

		snprintf( str_month, sizeof(str_month), "%02u",
				g_demo_parameters.month);
		wtk_label_change(widget->lbl_indication[LABEL_MONTH_ID], str_month);
		break;

	case ICON_SETTINGS_DATE_YEAR_UP_ID:
		g_demo_parameters.year++;
		if (g_demo_parameters.year == 2080) {
			g_demo_parameters.year = 1980;
		}

		snprintf( str_year, sizeof(str_year), "%04u",
				g_demo_parameters.year);
		wtk_label_change(widget->lbl_indication[LABEL_YEAR_ID], str_year);
		break;

	case ICON_SETTINGS_DATE_DAY_DOWN_ID:
		if (g_demo_parameters.day == 1) {
			g_demo_parameters.day = 31;
		} else {
			g_demo_parameters.day--;
		}

		snprintf( str_day, sizeof(str_day), "%02u",
				g_demo_parameters.day);
		wtk_label_change(widget->lbl_indication[LABEL_DATE_ID], str_day);
		break;

	case ICON_SETTINGS_DATE_MONTH_DOWN_ID:
		if (g_demo_parameters.month == 1) {
			g_demo_parameters.month = 12;
		} else {
			g_demo_parameters.month--;
		}

		snprintf( str_month, sizeof(str_month), "%02u",
				g_demo_parameters.month);
		wtk_label_change(widget->lbl_indication[LABEL_MONTH_ID], str_month);
		break;

	case ICON_SETTINGS_DATE_YEAR_DOWN_ID:
		if (g_demo_parameters.year == 1980) {
			g_demo_parameters.year = 2080;
		} else {
			g_demo_parameters.year--;
		}

		snprintf( str_year, sizeof(str_year), "%04u",
				g_demo_parameters.year);
		wtk_label_change(widget->lbl_indication[LABEL_YEAR_ID], str_year);
		break;

	case ICON_SETTINGS_DATE_RET_ID:
		rtc_set_date( RTC, g_demo_parameters.year,
				g_demo_parameters.month,
				g_demo_parameters.day, 1 );
		demo_parameters_commit_changes();
		app_widget_settings_date_on(false);
		app_widget_settings_on(true);
		break;
	}
	return false;
}

/**
 * \brief Launch date settings widget.
 *
 * Allocates memory for the widget context, and creates all widgets that
 * make up its interface. If memory allocation or widget creation fails, the
 * application exits immediately.
 */
static void app_widget_launch_settings_date(void)
{
	struct win_window *parent;
	struct win_area area;

	/* Initialize date strings */
	snprintf( str_day, sizeof(str_day), "%02u", g_demo_parameters.day);
	snprintf( str_month, sizeof(str_month), "%02u",
			g_demo_parameters.month);
	snprintf( str_year, sizeof(str_year), "%04u", g_demo_parameters.year);

	/* Create a new context for the GUI, clear new context state */
	widget_ctx_settings_date
		= membag_alloc(
			sizeof(struct widget_context_settings_date));

	/* Set widget background */
	widget_ctx_settings_date->frame_bg.type = GFX_BITMAP_SOLID;
	widget_ctx_settings_date->frame_bg.data.color
		= GFX_COLOR(255, 255, 255);

	/* Set window area */
	area = win_get_attributes(win_get_root())->area;

	/* Create and show the date settings widget */
	widget_ctx_settings_date->frame = wtk_basic_frame_create(
			win_get_root(), &area, &widget_ctx_settings_date->frame_bg, NULL,
			widget_settings_date_setup_command_handler,
			widget_ctx_settings_date);
	if (!widget_ctx_settings_date->frame) {
		goto error_frame;
	}

	parent = wtk_basic_frame_as_child(widget_ctx_settings_date->frame);
	win_show(parent);

	/* Set positions for logo frame */
	area.pos.x = 0;
	area.pos.y = 0;
	area.size.x = 87;
	area.size.y = 40;

	/* Create logo frame */
	widget_ctx_settings_date->logo_frame = wtk_basic_frame_create(
			parent, &area, &win_root_logo_icon, NULL,
			NULL, NULL);
	if (!widget_ctx_settings_date->frame) {
		goto error_frame;
	}

	win_show(wtk_basic_frame_as_child(widget_ctx_settings_date->logo_frame));

	/* Update area for the label widget of board name */
	area.pos.x = 100;
	area.pos.y = 0;
	wtk_label_size_hint(&area.size, demo_board_name);

	/* Create label inside frame */
	widget_ctx_settings_date->lbl_board_name = wtk_label_create(
			parent, &area, demo_board_name,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_settings_date->lbl_board_name) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_settings_date->lbl_board_name));

	/* Update area for the label widget of function name */
	area.pos.x = 100;
	area.pos.y = 20;
	wtk_label_size_hint(&area.size, demo_func_date_name);

	/* Create label inside frame */
	widget_ctx_settings_date->lbl_func_name = wtk_label_create(
			parent, &area, demo_func_date_name,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_settings_date->lbl_func_name) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_settings_date->lbl_func_name));

	/* Create a logical group for the icon buttons */
	widget_ctx_settings_date->icon_group = wtk_icon_group_create();
	if (!widget_ctx_settings_date->icon_group) {
		goto error_widget;
	}

	/* Update area for the year up icon button widget */
	area.pos.x = 43;
	area.pos.y = 60;
	area.size.x = 0;
	wtk_icon_button_size_hint(&area.size, &win_settings_date_year_up_icon);

	/* Create the year up icon button inside frame */
	widget_ctx_settings_date->icons[ICON_SETTINGS_DATE_YEAR_UP_ID] = wtk_icon_button_create(parent,
			&area,
			&win_settings_date_year_up_icon, false,
			widget_ctx_settings_date->icon_group,
			(win_command_t)(ICON_SETTINGS_DATE_YEAR_UP_ID));
	if (!widget_ctx_settings_date->icons[ICON_SETTINGS_DATE_YEAR_UP_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_settings_date->icons[ICON_SETTINGS_DATE_YEAR_UP_ID]));

	/* Adjust the area for the next icon to create */
	area.pos.x = 104;
	area.pos.y = 60;
	wtk_icon_button_size_hint(&area.size, &win_settings_date_month_up_icon);

	/* Create the icon button inside frame */
	widget_ctx_settings_date->icons[ICON_SETTINGS_DATE_MONTH_UP_ID] = wtk_icon_button_create(parent,
			&area,
			&win_settings_date_month_up_icon, false,
			widget_ctx_settings_date->icon_group,
			(win_command_t)(ICON_SETTINGS_DATE_MONTH_UP_ID));
	if (!widget_ctx_settings_date->icons[ICON_SETTINGS_DATE_MONTH_UP_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_settings_date->icons[ICON_SETTINGS_DATE_MONTH_UP_ID]));

	/* Adjust the area for the next icon to create */
	area.pos.x = 162;
	area.pos.y = 60;
	wtk_icon_button_size_hint(&area.size, &win_settings_date_date_up_icon);

	/* Create the icon button inside frame */
	widget_ctx_settings_date->icons[ICON_SETTINGS_DATE_DAY_UP_ID] = wtk_icon_button_create(parent,
			&area,
			&win_settings_date_date_up_icon, false,
			widget_ctx_settings_date->icon_group,
			(win_command_t)(ICON_SETTINGS_DATE_DAY_UP_ID));
	if (!widget_ctx_settings_date->icons[ICON_SETTINGS_DATE_DAY_UP_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_settings_date->icons[ICON_SETTINGS_DATE_DAY_UP_ID]));

	area.pos.x = 55;
	area.pos.y = 135;
	wtk_label_size_hint(&area.size, str_year);

	/* Create label inside frame */
	widget_ctx_settings_date->lbl_indication[LABEL_YEAR_ID] = wtk_label_create(
			parent, &area, (char const *)str_year,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_settings_date->lbl_indication[LABEL_YEAR_ID]) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_settings_date->lbl_indication[LABEL_YEAR_ID]));

	area.pos.x = 116;
	area.pos.y = 135;
	wtk_label_size_hint(&area.size, str_month);

	/* Create label inside frame */
	widget_ctx_settings_date->lbl_indication[LABEL_MONTH_ID] = wtk_label_create(
			parent, &area, str_month,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_settings_date->lbl_indication[LABEL_MONTH_ID]) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_settings_date->lbl_indication[LABEL_MONTH_ID]));

	area.pos.x = 174;
	area.pos.y = 135;
	wtk_label_size_hint(&area.size, str_day);

	/* Create label inside frame */
	widget_ctx_settings_date->lbl_indication[LABEL_DATE_ID] = wtk_label_create(
			parent, &area, str_day,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_settings_date->lbl_indication[LABEL_DATE_ID]) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_settings_date->lbl_indication[LABEL_DATE_ID]));

	area.pos.x = 43;
	area.pos.y = 164;

	/* Adjust the area for the next icon to create */
	wtk_icon_button_size_hint(&area.size,
			&win_settings_date_year_down_icon);

	/* Create the icon button inside frame */
	widget_ctx_settings_date->icons[ICON_SETTINGS_DATE_YEAR_DOWN_ID] = wtk_icon_button_create(parent,
			&area,
			&win_settings_date_year_down_icon, false,
			widget_ctx_settings_date->icon_group,
			(win_command_t)(ICON_SETTINGS_DATE_YEAR_DOWN_ID));
	if (!widget_ctx_settings_date->icons[ICON_SETTINGS_DATE_YEAR_DOWN_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_settings_date->icons[ICON_SETTINGS_DATE_YEAR_DOWN_ID]));

	/* Adjust the area for the month down icon to create */
	area.pos.x = 104;
	area.pos.y = 164;
	wtk_icon_button_size_hint(&area.size, &win_settings_date_month_down_icon);

	/* Create the icon button inside frame */
	widget_ctx_settings_date->icons[ICON_SETTINGS_DATE_MONTH_DOWN_ID] = wtk_icon_button_create(parent,
			&area,
			&win_settings_date_month_down_icon, false,
			widget_ctx_settings_date->icon_group,
			(win_command_t)(ICON_SETTINGS_DATE_MONTH_DOWN_ID));
	if (!widget_ctx_settings_date->icons[ICON_SETTINGS_DATE_MONTH_DOWN_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_settings_date->icons[ICON_SETTINGS_DATE_MONTH_DOWN_ID]));

	/* Adjust the area for the date down icon to create */
	area.pos.x = 162;
	area.pos.y = 164;
	wtk_icon_button_size_hint(&area.size, &win_settings_date_date_down_icon);

	/* Create the icon button inside frame */
	widget_ctx_settings_date->icons[ICON_SETTINGS_DATE_DAY_DOWN_ID] = wtk_icon_button_create(parent,
			&area,
			&win_settings_date_date_down_icon, false,
			widget_ctx_settings_date->icon_group,
			(win_command_t)(ICON_SETTINGS_DATE_DAY_DOWN_ID));
	if (!widget_ctx_settings_date->icons[ICON_SETTINGS_DATE_DAY_DOWN_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_settings_date->icons[ICON_SETTINGS_DATE_DAY_DOWN_ID]));

	/* Adjust the area for the date return icon to create */
	area.pos.x = 12;
	area.pos.y = 220;
	wtk_icon_button_size_hint(&area.size, &win_settings_date_ret_icon);

	/* Create the icon button inside frame */
	widget_ctx_settings_date->icons[ICON_SETTINGS_DATE_RET_ID] = wtk_icon_button_create(parent,
			&area,
			&win_settings_date_ret_icon, false,
			widget_ctx_settings_date->icon_group,
			(win_command_t)(ICON_SETTINGS_DATE_RET_ID));
	if (!widget_ctx_settings_date->icons[ICON_SETTINGS_DATE_RET_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_settings_date->icons[ICON_SETTINGS_DATE_RET_ID]));
	return;

	/* Error handling to clean up allocations after an error */
error_widget:
	win_destroy(wtk_basic_frame_as_child(widget_ctx_settings_date->frame));
error_frame:
	membag_free(widget_ctx_settings_date);
}

/**
 * \brief Enable/disable date settings widget.
 *
 * \param on Turn on/off date settings widget.
 */
void app_widget_settings_date_on(uint8_t on)
{
	if (on) {
		app_widget_launch_settings_date();
	} else {
		if (widget_ctx_settings_date->frame) {
			win_destroy(wtk_basic_frame_as_child(
					widget_ctx_settings_date->frame));
		}
	}
}
