/**
 * \file
 *
 * \brief Low power mode widget for SAM toolkit demo application.
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
 * \brief Command event IDs for low power mode widget.
 */
enum command_id {
	/** Dummy icon */
	ICON_DUMMY_ID = 0,
	/** Command event ID for wait mode icon button */
	ICON_LPM_WAIT_ID,
	/** Command event ID for sleep mode icon button */
	ICON_LPM_SLEEP_ID,
	/** Command event ID for backup mode icon button */
	ICON_LPM_BACKUP_ID,
	/** Command event ID for second icon button */
	ICON_LPM_RET_ID,
	/** Max information icon number */
	ICON_LPM_MAX,
};


/** Widget application context */
struct widget_context_lpm {
	/** Pointer to frame for application */
	struct wtk_basic_frame *frame;
	/** Frame background object */
	struct gfx_bitmap frame_bg;
	/** Pointer to frame for logo */
	struct wtk_basic_frame *logo_frame;
	/** Label widget for board name */
	struct wtk_label *lbl_board_name;
	/** Label widget for function name */
	struct wtk_label *lbl_func_name;
	/* Group of icon button widgets */
	struct wtk_icon_group *icon_group;
	/* Array if icon button widgets */
	struct wtk_icon_button *icons[ICON_LPM_MAX];
	/** Label widget for indications */
	struct wtk_label *lbl_indication[4];
};

/** Statically allocated context pointer */
static struct widget_context_lpm *widget_ctx_lpm;

/** Low power mode function name string */
static char demo_func_name[] = "Low Power Mode";

/** Wait mode string */
static char lpm_wait[] = "Wait";

/** Backup mode string */
static char lpm_backup[] = "Backup";

/** Sleep mode string */
static char lpm_sleep[] = "Sleep";

/** Logo bitmap */
static struct gfx_bitmap win_root_logo_icon = {
	.width = 87, .height = 40,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_LOGO_ATMEL
};

/** Wait mode bitmap */
static struct gfx_bitmap win_lpm_wait_icon = {
	.width = 64, .height = 64,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_WAIT_MODE
};

/** Sleep mode bitmap */
static struct gfx_bitmap win_lpm_sleep_icon = {
	.width = 64, .height = 64,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_SLEEP_MODE
};

/** Backup mode bitmap */
static struct gfx_bitmap win_lpm_backup_icon = {
	.width = 64, .height = 64,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BACKUP_MODE
};

/** Return bitmap */
static struct gfx_bitmap win_lpm_ret_icon = {
	.width = 48, .height = 48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_BACK
};

/**
 * \brief Frame handler for the low power mode widget.
 *
 * Handles all command events from the widgets in the application frame.
 *
 * \param frame Pointer to the application frame
 * \param command_data Command event ID
 *
 * \return True if exiting, to destroy the window
 */
static bool widget_lpm_command_handler(struct wtk_basic_frame *frame,
		win_command_t command_data)
{
	char command;
	command = (uintptr_t)command_data;

	/* Remove warnings */
	UNUSED(frame);

	switch (command) {
	case ICON_LPM_WAIT_ID:
		/* Hide low power mode window and start to launch wait mode widget */
		app_widget_lpm_on(false);
		app_widget_lpm_wait_on(true);
		break;

	case ICON_LPM_SLEEP_ID:
		/* Hide low power mode window and start to launch sleep mode widget */
		app_widget_lpm_on(false);
		app_widget_lpm_sleep_on(true);
		break;

	case ICON_LPM_BACKUP_ID:
		/* Hide low power mode window and start to launch backup mode widget */
		app_widget_lpm_on(false);
		app_widget_lpm_backup_on(true);
		break;

	case ICON_LPM_RET_ID:
		/* Turn off low power mode and return to main widget */
		app_widget_lpm_on(false);
		app_widget_main_on(true);
		break;
	}

	return false;
}

/**
 * \brief Setup low power mode widget.
 *
 * Allocates memory for the application context, and creates all widgets that
 * make up its interface. If memory allocation or widget creation fails, the
 * application exits immediately.
 */
static void app_widget_launch_lpm(void)
{
	struct win_window *parent;
	struct win_area area;

	/* Create a new context for the GUI, clear new context state */
	widget_ctx_lpm = membag_alloc(sizeof(struct widget_context_lpm));

	/* Set the background information for the GUI window */
	widget_ctx_lpm->frame_bg.type = GFX_BITMAP_SOLID;
	widget_ctx_lpm->frame_bg.data.color = GFX_COLOR(255, 255, 255);

	/* Set the area for the GUI window */
	area = win_get_attributes(win_get_root())->area;

	/* Create and show the main GUI frame */
	widget_ctx_lpm->frame = wtk_basic_frame_create(
			win_get_root(), &area, &widget_ctx_lpm->frame_bg, NULL,
			widget_lpm_command_handler, widget_ctx_lpm);
	if (!widget_ctx_lpm->frame) {
		goto error_frame;
	}

	parent = wtk_basic_frame_as_child(widget_ctx_lpm->frame);
	win_show(parent);

	/* Set area for logo */
	area.pos.x = 0;
	area.pos.y = 0;
	area.size.x = 87;
	area.size.y = 40;
	/* Create and show the main GUI frame */
	widget_ctx_lpm->logo_frame = wtk_basic_frame_create(
			parent, &area, &win_root_logo_icon, NULL,
			NULL, NULL);
	if (!widget_ctx_lpm->frame) {
		goto error_frame;
	}

	win_show(wtk_basic_frame_as_child(widget_ctx_lpm->logo_frame));

	/* Set area for board name string */
	area.pos.x = 100;
	area.pos.y = 0;
	wtk_label_size_hint(&area.size, demo_board_name);

	/* Create label inside frame */
	widget_ctx_lpm->lbl_board_name = wtk_label_create(
			parent, &area, demo_board_name,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_lpm->lbl_board_name) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_lpm->lbl_board_name));

	/* Set area for function name string */
	area.pos.x = 100;
	area.pos.y = 20;
	wtk_label_size_hint(&area.size, demo_func_name);

	/* Create label inside frame */
	widget_ctx_lpm->lbl_func_name = wtk_label_create(
			parent, &area, demo_func_name,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_lpm->lbl_func_name) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_lpm->lbl_func_name));

	/* Create a logical group for the icon buttons */
	widget_ctx_lpm->icon_group = wtk_icon_group_create();
	if (!widget_ctx_lpm->icon_group) {
		goto error_widget;
	}

	/* Set area for the wait mode icon button widget */
	area.pos.x = 88;
	area.pos.y = 78;
	area.size.x = 0;
	wtk_icon_button_size_hint(&area.size, &win_lpm_wait_icon);

	/* Create the wait mode icon button inside frame */
	widget_ctx_lpm->icons[ICON_LPM_WAIT_ID] = wtk_icon_button_create(parent, &area,
			&win_lpm_wait_icon, false, widget_ctx_lpm->icon_group,
			(win_command_t)(ICON_LPM_WAIT_ID));
	if (!widget_ctx_lpm->icons[ICON_LPM_WAIT_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_lpm->icons[ICON_LPM_WAIT_ID]));

	/* Set area for the wait mode label widget */
	area.pos.x = 166;
	area.pos.y = 80;
	wtk_label_size_hint(&area.size, lpm_wait);

	/* Create label inside frame */
	widget_ctx_lpm->lbl_indication[ICON_LPM_WAIT_ID] = wtk_label_create(
			parent, &area, lpm_wait,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_lpm->lbl_indication[ICON_LPM_WAIT_ID]) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_lpm->lbl_indication[ICON_LPM_WAIT_ID]));

	/* Set area for the sleep mode label widget */
	area.pos.x = 88;
	area.pos.y = 157;
	wtk_icon_button_size_hint(&area.size, &win_lpm_sleep_icon);

	/* Create the sleep mode icon button inside frame */
	widget_ctx_lpm->icons[ICON_LPM_SLEEP_ID] = wtk_icon_button_create(parent, &area,
			&win_lpm_sleep_icon, false, widget_ctx_lpm->icon_group,
			(win_command_t)(ICON_LPM_SLEEP_ID));
	if (!widget_ctx_lpm->icons[ICON_LPM_SLEEP_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_lpm->icons[ICON_LPM_SLEEP_ID]));

	/* Set area for the sleep mode label widget */
	area.pos.x = 166;
	area.pos.y = 160;
	wtk_label_size_hint(&area.size, lpm_sleep);

	/* Create label inside frame */
	widget_ctx_lpm->lbl_indication[ICON_LPM_SLEEP_ID] = wtk_label_create(
			parent, &area, lpm_sleep,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_lpm->lbl_indication[ICON_LPM_SLEEP_ID]) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_lpm->lbl_indication[ICON_LPM_SLEEP_ID]));

	/* Set area for the backup mode icon widget */
	area.pos.x = 88;
	area.pos.y = 238;
	wtk_icon_button_size_hint(&area.size, &win_lpm_backup_icon);

	/* Create the backup icon button inside frame */
	widget_ctx_lpm->icons[ICON_LPM_BACKUP_ID] = wtk_icon_button_create(parent, &area,
			&win_lpm_backup_icon, false, widget_ctx_lpm->icon_group,
			(win_command_t)(ICON_LPM_BACKUP_ID));
	if (!widget_ctx_lpm->icons[ICON_LPM_BACKUP_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_lpm->icons[ICON_LPM_BACKUP_ID]));

	/* Set area for the backup mode label widget */
	area.pos.x = 166;
	area.pos.y = 240;
	wtk_label_size_hint(&area.size, lpm_backup);

	/* Create label inside frame */
	widget_ctx_lpm->lbl_indication[ICON_LPM_BACKUP_ID] = wtk_label_create(
			parent, &area, lpm_backup,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_lpm->lbl_indication[ICON_LPM_BACKUP_ID]) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_lpm->lbl_indication[ICON_LPM_BACKUP_ID]));

	/* Set area for the return icon widget */
	area.pos.x = 12;
	area.pos.y = 232;
	wtk_icon_button_size_hint(&area.size, &win_lpm_ret_icon);

	/* Create the return icon button inside frame */
	widget_ctx_lpm->icons[ICON_LPM_RET_ID] = wtk_icon_button_create(parent, &area,
			&win_lpm_ret_icon, false, widget_ctx_lpm->icon_group,
			(win_command_t)(ICON_LPM_RET_ID));
	if (!widget_ctx_lpm->icons[ICON_LPM_RET_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_lpm->icons[ICON_LPM_RET_ID]));
	return;

	/* Error handling to clean up allocations after an error */
error_widget:
	win_destroy(wtk_basic_frame_as_child(widget_ctx_lpm->frame));
error_frame:
	membag_free(widget_ctx_lpm);
}

/**
 * \brief Enable/disable low power mode widget.
 *
 * \param on Turn on/off low power mode widget.
 */
void app_widget_lpm_on(uint8_t on)
{
	if (on) {
		app_widget_launch_lpm();
	} else {
		if (widget_ctx_lpm->frame) {
			win_destroy(wtk_basic_frame_as_child(widget_ctx_lpm->frame));
		}
	}
}
