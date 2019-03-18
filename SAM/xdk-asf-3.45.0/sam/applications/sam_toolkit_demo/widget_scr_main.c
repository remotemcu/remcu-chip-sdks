/**
 * \file
 *
 * \brief Main widget for SAM toolkit demo application.
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
#include "demo.h"
#include "bitmaps.h"

/**
 * \brief Command event IDs for main widget.
 *
 */
enum main_command_id {
	/** Dummy ICON */
	ICON_DUMMY_ID = 0,
	/** Command event ID for audio icon button */
	ICON_MAIN_AUDIO_ID,
	/** Command event ID for video icon button */
	ICON_MAIN_VIDEO_ID,
	/** Command event ID for ppt icon button */
	ICON_MAIN_PPT_ID,
	/** Command event ID for settings icon button */
	ICON_MAIN_SETTINGS_ID,
	/** Command event ID for qtouch icon button */
	ICON_MAIN_QTOUCH_ID,
	/** Command event ID for low power mode icon button */
	ICON_MAIN_LPM_ID,
	/** Command event ID for information icon button */
	ICON_MAIN_INFO_ID,	
	/** Max icon number for main widget */
	ICON_MAIN_MAX_NUM,
};

/** Widget application context */
struct widget_context {
	/** Pointer to frame for application */
	struct wtk_basic_frame *frame;
	/** Frame background object */
	struct gfx_bitmap frame_bg;
	/** Pointer to frame for logo */
	struct wtk_basic_frame *logo_frame;
	/* Group of icon button widgets */
	struct wtk_icon_group *icon_group;
	/* Array if icon button widgets */
	struct wtk_icon_button *icons[ICON_MAIN_MAX_NUM];
	/** Label widget for board name */
	struct wtk_label *lbl_board_name;
	/** Label widget for function name */
	struct wtk_label *lbl_func_name;
};

/** Statically allocated context pointer */
static struct widget_context *widget_ctx_main;

static char demo_func_name[] = "Demo";

/** Logo bitmap */
static struct gfx_bitmap win_main_logo_icon = {
	.width = 87, .height=40,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_LOGO_ATMEL
};

/** Audio bitmap */
static struct gfx_bitmap win_main_audio_icon = {
	.width = 64, .height=64,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_AUDIO
};


/** Video bitmap */
static struct gfx_bitmap win_main_video_icon = {
	.width = 64, .height=64,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_GFX_DEMO
};

/** Slider show bitmap */
static struct gfx_bitmap win_main_slidershow_icon = {
	.width = 64, .height=64,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_SLIDESHOW
};

/** Settings bitmap */
static struct gfx_bitmap win_main_settings_icon = {
	.width = 64, .height=64,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_SETTINGS
};

/** QTouch bitmap */
static struct gfx_bitmap win_main_qtouch_icon = {
	.width = 64, .height=64,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_QTOUCH
};

/** Low power mode bitmap */
static struct gfx_bitmap win_main_lpm_icon = {
	.width = 64, .height=64,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_LOW_POWER_MODES
};

/** Information bitmap */
static struct gfx_bitmap win_main_info_icon = {
	.width = 64, .height=64,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_INFOS
};

char demo_board_name[] = DEMO_BOARD_NAME;

/**
 * \brief Frame handler for the main widget.
 *
 * Handles all command events from the widgets in the main widget.
 *
 * \param frame Pointer to the application frame.
 * \param command_data Command event ID.
 *
 * \return True if exiting, to destroy the window.
 */
static bool widget_frame_command_handler(struct wtk_basic_frame *frame,
		void* command_data)
{
	char command;
	command = (uintptr_t)command_data;

	/* Remove warnings */
	UNUSED(frame);

	switch (command) {
	case ICON_MAIN_AUDIO_ID:
		/* Launch audio widget */
		app_widget_main_on(false);
		app_widget_audio_on(true);

		/* Clear main window special handler */
		 demo_set_special_mode_status(DEMO_MAIN_MODE, 0);
		break;

	case ICON_MAIN_VIDEO_ID:
		/* Set FFT window special handler */
		 demo_set_special_mode_status(DEMO_FFT_MODE, 1);
		app_widget_main_on(false);
		app_widget_fft_on();

		/* Clear FFT window special handler */
		app_widget_main_on(true);
		break;

	case ICON_MAIN_PPT_ID:
		/* Launch ppt mode */
		demo_set_special_mode_status(DEMO_PPT_MODE, 1);
		app_widget_main_on(false);

		/* Clear main window special handler */
		demo_set_special_mode_status(DEMO_MAIN_MODE, 0);
		break;

	case ICON_MAIN_SETTINGS_ID:
		/* Launch settings widget */
		app_widget_main_on(false);
		app_widget_settings_on(true);
		 demo_set_special_mode_status(DEMO_MAIN_MODE, 0);
		break;

	case ICON_MAIN_QTOUCH_ID:
		/* Launch qtouch widget */
		app_widget_main_on(false);
		app_widget_qtouch_on(true);

		/* Clear main window special handler */
		 demo_set_special_mode_status(DEMO_MAIN_MODE, 0);
		break;

	case ICON_MAIN_LPM_ID:
		/* Launch low power mode widget */
		app_widget_main_on(false);
		app_widget_lpm_on(true);

		/* Clear main window special handler */
		 demo_set_special_mode_status(DEMO_MAIN_MODE, 0);
		break;

	case ICON_MAIN_INFO_ID:
		/* Launch information widget */
		app_widget_main_on(false);
		app_widget_info_on(true);

		/* Clear main window special handler */
		 demo_set_special_mode_status(DEMO_MAIN_MODE, 0);
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
 */
static void app_widget_launch_main(void)
{
	struct win_window *parent;
	struct win_area area;

	/* Create a new context for the GUI, clear new context state */
	widget_ctx_main = membag_alloc(sizeof(struct widget_context));

	/* Set the background information for the GUI window */
	widget_ctx_main->frame_bg.type = GFX_BITMAP_SOLID;
	widget_ctx_main->frame_bg.data.color = GFX_COLOR(255, 255, 255);

	/* Set the area for the GUI window */
	area = win_get_attributes(win_get_root())->area;

	/* Create and show the main GUI frame */
	widget_ctx_main->frame = wtk_basic_frame_create(
			win_get_root(), &area, &widget_ctx_main->frame_bg, NULL,
			widget_frame_command_handler, widget_ctx_main);
	if (!widget_ctx_main->frame) {
		goto error_frame;
	}

	parent = wtk_basic_frame_as_child(widget_ctx_main->frame);
	win_show(parent);

	/* Set area for logo */
	area.pos.x = 0;
	area.pos.y = 0;
	area.size.x = 87;
	area.size.y = 40;
	/* Create and show the main GUI frame */
	widget_ctx_main->logo_frame = wtk_basic_frame_create(
			parent, &area, &win_main_logo_icon, NULL,
			NULL, NULL);
	if (!widget_ctx_main->frame) {
		goto error_frame;
	}

	win_show(wtk_basic_frame_as_child(widget_ctx_main->logo_frame));

	/* Set area for board name */
	area.pos.x = 100;
	area.pos.y = 0;
	wtk_label_size_hint(&area.size, demo_board_name);

	/* Create label inside frame */
	widget_ctx_main->lbl_board_name = wtk_label_create(
			parent, &area, demo_board_name,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_main->lbl_board_name) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_main->lbl_board_name));

	/* Set area for function name */
	area.pos.x = 100;
	area.pos.y = 20;
	wtk_label_size_hint(&area.size, demo_func_name);

	/* Create label inside frame */
	widget_ctx_main->lbl_func_name = wtk_label_create(
			parent, &area, demo_func_name,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_main->lbl_func_name) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_main->lbl_func_name));

	/* Create a logical group for the icon buttons */
	widget_ctx_main->icon_group = wtk_icon_group_create();
	if (!widget_ctx_main->icon_group) {
		goto error_widget;
	}

	/* Set area for the audio icon button widget */
	area.pos.x = 14;
	area.pos.y = 62;
	area.size.x = 0;
	wtk_icon_button_size_hint(&area.size, &win_main_audio_icon);

	/* Create the next icon button inside frame */
	widget_ctx_main->icons[ICON_MAIN_AUDIO_ID] = wtk_icon_button_create(parent, &area,
			&win_main_audio_icon, false, widget_ctx_main->icon_group,
			(win_command_t)(ICON_MAIN_AUDIO_ID));
	if (!widget_ctx_main->icons[ICON_MAIN_AUDIO_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_main->icons[ICON_MAIN_AUDIO_ID]));

	/* Adjust the area for the video icon */
	area.pos.x += 76;
	wtk_icon_button_size_hint(&area.size, &win_main_video_icon);

	/* Create the video icon button inside frame */
	widget_ctx_main->icons[ICON_MAIN_VIDEO_ID] = wtk_icon_button_create(parent, &area,
			&win_main_video_icon, false, widget_ctx_main->icon_group,
			(win_command_t)(ICON_MAIN_VIDEO_ID));
	if (!widget_ctx_main->icons[ICON_MAIN_VIDEO_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_main->icons[ICON_MAIN_VIDEO_ID]));

	/* Adjust the area for the slider show icon */
	area.pos.x += 76;
	wtk_icon_button_size_hint(&area.size, &win_main_slidershow_icon);

	/* Create the icon button inside frame */
	widget_ctx_main->icons[ICON_MAIN_PPT_ID] = wtk_icon_button_create(parent, &area,
			&win_main_slidershow_icon, false, widget_ctx_main->icon_group,
			(win_command_t)(ICON_MAIN_PPT_ID));
	if (!widget_ctx_main->icons[ICON_MAIN_PPT_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_main->icons[ICON_MAIN_PPT_ID]));

	/* Adjust the area for the settings icon */
	area.pos.x = 14;
	area.pos.y += 76;
	wtk_icon_button_size_hint(&area.size, &win_main_settings_icon);

	/* Create the icon button inside frame */
	widget_ctx_main->icons[ICON_MAIN_SETTINGS_ID] = wtk_icon_button_create(parent, &area,
			&win_main_settings_icon, false, widget_ctx_main->icon_group,
			(win_command_t)(ICON_MAIN_SETTINGS_ID));
	if (!widget_ctx_main->icons[ICON_MAIN_SETTINGS_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_main->icons[ICON_MAIN_SETTINGS_ID]));

	/* Adjust the area for the QTouch icon */
	area.pos.x += 76;	
	wtk_icon_button_size_hint(&area.size, &win_main_qtouch_icon);

	/* Create the icon button inside frame */
	widget_ctx_main->icons[ICON_MAIN_QTOUCH_ID] = wtk_icon_button_create(parent, &area,
			&win_main_qtouch_icon, false, widget_ctx_main->icon_group,
			(win_command_t)(ICON_MAIN_QTOUCH_ID));
	if (!widget_ctx_main->icons[ICON_MAIN_QTOUCH_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_main->icons[ICON_MAIN_QTOUCH_ID]));

	/* Adjust the area for the low power mode icon */
	area.pos.x += 76;	
	wtk_icon_button_size_hint(&area.size, &win_main_lpm_icon);

	/* Create the next icon button inside frame */
	widget_ctx_main->icons[ICON_MAIN_LPM_ID] = wtk_icon_button_create(parent, &area,
			&win_main_lpm_icon, false, widget_ctx_main->icon_group,
			(win_command_t)(ICON_MAIN_LPM_ID));
	if (!widget_ctx_main->icons[ICON_MAIN_LPM_ID]) {
		goto error_widget;
	}
	
	win_show(wtk_icon_button_as_child(widget_ctx_main->icons[ICON_MAIN_LPM_ID]));

	/* Adjust the area for the information icon */
	area.pos.x = 90;
	area.pos.y += 76;
	wtk_icon_button_size_hint(&area.size, &win_main_info_icon);

	/* Create the next icon button inside frame */
	widget_ctx_main->icons[ICON_MAIN_INFO_ID] = wtk_icon_button_create(parent, &area,
			&win_main_info_icon, false, widget_ctx_main->icon_group,
			(win_command_t)(ICON_MAIN_INFO_ID));
	if (!widget_ctx_main->icons[ICON_MAIN_INFO_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_main->icons[ICON_MAIN_INFO_ID]));

	/* Enable the special main mode */
	 demo_set_special_mode_status(DEMO_MAIN_MODE, 1);

	return;

	/* Error handling to clean up allocations after an error */
error_widget:
	win_destroy(wtk_basic_frame_as_child(widget_ctx_main->frame));
error_frame:
	membag_free(widget_ctx_main);
}

/**
 * \brief Enable/disable mainmode widget.
 *
 * \param on Turn on/off main mode widget.
 */
void app_widget_main_on(uint8_t on)
{
	if (on) {
		/* Launch the main widget */
		app_widget_launch_main();

		/* Set the main sepcial mode */
		demo_set_special_mode_status(DEMO_MAIN_MODE, 1);
	} else {
		/* Clear main speical mode */
		demo_set_special_mode_status(DEMO_MAIN_MODE, 0);

		/* Destroy main window */
		if (widget_ctx_main->frame) {
			win_destroy(wtk_basic_frame_as_child(
					widget_ctx_main->frame));
		}
	}
}
