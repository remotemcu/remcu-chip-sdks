/**
 * \file
 *
 * \brief Audio widget for SAM toolkit demo application.
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
 * \brief Command event IDs for audio widget.
 */
enum command_id {
	/** Dummy icon */
	ICON_DUMMY_ID = 0,
	/** Command event ID for audio record icon button */
	ICON_AUDIO_RECORD_ID,
	/** Command event ID for microphone icon button */
	ICON_AUDIO_MIC_ID,
	/** Command event ID for pause icon button */
	ICON_AUDIO_PLAY_PAUSE_ID,
	/** Command event ID for stop icon button */
	ICON_AUDIO_STOP_ID,
	/** Command event ID for volume icon button */
	ICON_AUDIO_VOLUME_ID,
	/** Command event ID for return icon button */
	ICON_AUDIO_RET_ID,
	/* Audio icon max */
	ICON_AUDIO_MAX_ID,
};

/** Widget application context */
struct widget_context_audio {
	/** Pointer to frame for application */
	struct wtk_basic_frame *frame;
	/** Pointer to frame for logo frame */
	struct wtk_basic_frame *logo_frame;
	/** Frame background object */
	struct gfx_bitmap frame_bg;
	/* Group of icon button widgets */
	struct wtk_icon_group *icon_group;
	/* Array if icon button widgets */
	struct wtk_icon_button *icons[ICON_AUDIO_MAX_ID];
	/** Label widget for board name label */
	struct wtk_label *lbl_board_name;
	/** Label widget for function name label */
	struct wtk_label *lbl_func_name;
};

/** Statically allocated context pointer */
static struct widget_context_audio *widget_ctx_audio;

/** String for function name */
static char demo_func_name[] = "Audio";

/** Indication string */
static char demo_idc[] = "  This module is\nunder construction\n Press any icon\n   to return!";

/** Logo bitmap */
static struct gfx_bitmap win_root_logo_icon = {
	.width = 87, .height=40,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_LOGO_ATMEL
};

/** Audio record bitmap */
static struct gfx_bitmap win_audio_record_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_RECORD
};


/** Microphone bitmap */
static struct gfx_bitmap win_audio_mic_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_MICROPHONE_DISABLED
};

/** Play pause bitmap */
static struct gfx_bitmap win_audio_play_pause_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_PLAY_PAUSE_DISABLED
};

/** Audio stop bitmap */
static struct gfx_bitmap win_audio_stop_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_STOP_DISABLED
};

/** Volume disable bitmap */
static struct gfx_bitmap win_audio_vol_disable_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_VOLUME_DISABLED
};

/** Audio return bitmap */
static struct gfx_bitmap win_audio_ret_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_BACK
};

/**
 * \brief Frame handler for the application
 *
 * Handles all command events from the widgets in the application frame.
 *
 * \param frame Pointer to the application frame
 * \param command_data Command event ID
 *
 * \return True if exiting, to destroy the window
 */
static bool widget_audio_command_handler(struct wtk_basic_frame *frame,
		win_command_t command_data)
{
	char command;
	command = (uintptr_t)command_data;

	/* Remove warnings */
	UNUSED(frame);

	switch (command) {
	/* Simply return right now */
	case ICON_AUDIO_RECORD_ID:
	case ICON_AUDIO_MIC_ID:
	case ICON_AUDIO_PLAY_PAUSE_ID:
	case ICON_AUDIO_STOP_ID:
	case ICON_AUDIO_VOLUME_ID:
	case ICON_AUDIO_RET_ID:
		app_widget_audio_on(false);
		app_widget_main_on(true);
		break;
	}
	return false;
}


/**
 * \brief Setup audio widget.
 *
 * Allocates memory for the application context, and creates all widgets that
 * make up its interface. If memory allocation or widget creation fails, the
 * application exits immediately.
 */
static void app_widget_launch_audio(void)
{
	struct win_window *parent;
	struct win_area area;

	/* Create a new context for the GUI, clear new context state */
	widget_ctx_audio = membag_alloc(sizeof(struct widget_context_audio));

	/* Set the background information for the GUI window */
	widget_ctx_audio->frame_bg.type = GFX_BITMAP_SOLID;
	widget_ctx_audio->frame_bg.data.color = GFX_COLOR(255, 255, 255);

	/* Set the area for the GUI window */
	area = win_get_attributes(win_get_root())->area;

	/* Create and show the main GUI frame */
	widget_ctx_audio->frame = wtk_basic_frame_create(
			win_get_root(), &area, &widget_ctx_audio->frame_bg, NULL,
			widget_audio_command_handler, widget_ctx_audio);
	if (!widget_ctx_audio->frame) {
		goto error_frame;
	}

	parent = wtk_basic_frame_as_child(widget_ctx_audio->frame);
	win_show(parent);

	/* Set area for the logo widget */
	area.pos.x = 0;
	area.pos.y = 0;
	area.size.x = 87;
	area.size.y = 40;
	/* Create and show the main GUI frame */
	widget_ctx_audio->logo_frame = wtk_basic_frame_create(
			parent, &area, &win_root_logo_icon, NULL,
			NULL, NULL);
	if (!widget_ctx_audio->frame) {
		goto error_frame;
	}

	win_show(wtk_basic_frame_as_child(widget_ctx_audio->logo_frame));

	/* Set area for board name label */
	area.pos.x = 100;
	area.pos.y = 0;
	wtk_label_size_hint(&area.size, demo_board_name);

	/* Create label inside frame */
	widget_ctx_audio->lbl_board_name = wtk_label_create(
			parent, &area, demo_board_name,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_audio->lbl_board_name) {
		goto error_widget;
	}
	
	win_show(wtk_label_as_child(widget_ctx_audio->lbl_board_name));

	/* Set area for function name label */
	area.pos.x = 100;
	area.pos.y = 20;
	wtk_label_size_hint(&area.size, demo_func_name);

	/* Create label inside frame */
	widget_ctx_audio->lbl_func_name = wtk_label_create(
			parent, &area, demo_func_name,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_audio->lbl_func_name) {
		goto error_widget;
	}
	
	win_show(wtk_label_as_child(widget_ctx_audio->lbl_func_name));

	/* Create a logical group for the icon buttons */
	widget_ctx_audio->icon_group = wtk_icon_group_create();
	if (!widget_ctx_audio->icon_group) {
		goto error_widget;
	}

	/* Set area for the audio record icon */
	area.pos.x = 14;
	area.pos.y = 62;
	area.size.x = 0;
	wtk_icon_button_size_hint(&area.size, &win_audio_record_icon);

	/* Create the icon button inside frame */
	widget_ctx_audio->icons[ICON_AUDIO_RECORD_ID] = wtk_icon_button_create(parent, &area,
			&win_audio_record_icon, false, widget_ctx_audio->icon_group,
			(win_command_t)(ICON_AUDIO_RECORD_ID));
	if (!widget_ctx_audio->icons[ICON_AUDIO_RECORD_ID]) {
		goto error_widget;
	}
	
	win_show(wtk_icon_button_as_child(widget_ctx_audio->icons[ICON_AUDIO_RECORD_ID]));

	/* Set area for the microphone icon */
	area.pos.x = 174;
	area.pos.y = 62;
	wtk_icon_button_size_hint(&area.size, &win_audio_mic_icon);

	/* Create the icon button inside frame */
	widget_ctx_audio->icons[ICON_AUDIO_MIC_ID] = wtk_icon_button_create(parent, &area,
			&win_audio_mic_icon, false, widget_ctx_audio->icon_group,
			(win_command_t)(ICON_AUDIO_MIC_ID));
	if (!widget_ctx_audio->icons[ICON_AUDIO_MIC_ID]) {
		goto error_widget;
	}
	
	win_show(wtk_icon_button_as_child(widget_ctx_audio->icons[ICON_AUDIO_MIC_ID]));

	/* Set area for the play pause icon */
	area.pos.x = 14;
	area.pos.y = 140;
	wtk_icon_button_size_hint(&area.size, &win_audio_play_pause_icon);

	/* Create the icon button inside frame */
	widget_ctx_audio->icons[ICON_AUDIO_PLAY_PAUSE_ID] = wtk_icon_button_create(parent, &area,
			&win_audio_play_pause_icon, false, widget_ctx_audio->icon_group,
			(win_command_t)(ICON_AUDIO_PLAY_PAUSE_ID));
	if (!widget_ctx_audio->icons[ICON_AUDIO_PLAY_PAUSE_ID]) {
		goto error_widget;
	}
	
	win_show(wtk_icon_button_as_child(widget_ctx_audio->icons[ICON_AUDIO_PLAY_PAUSE_ID]));

	/* Set area for the play stop icon */
	area.pos.x = 94;
	area.pos.y = 140;
	wtk_icon_button_size_hint(&area.size, &win_audio_stop_icon);

	/* Create the icon button inside frame */
	widget_ctx_audio->icons[ICON_AUDIO_STOP_ID] = wtk_icon_button_create(parent, &area,
			&win_audio_stop_icon, false, widget_ctx_audio->icon_group,
			(win_command_t)(ICON_AUDIO_STOP_ID));
	if (!widget_ctx_audio->icons[ICON_AUDIO_STOP_ID]) {
		goto error_widget;
	}
	
	win_show(wtk_icon_button_as_child(widget_ctx_audio->icons[ICON_AUDIO_STOP_ID]));

	/* Set area for the volume disable icon */
	area.pos.x = 174;
	area.pos.y = 140;
	wtk_icon_button_size_hint(&area.size, &win_audio_vol_disable_icon);

	/* Create the icon button inside frame */
	widget_ctx_audio->icons[ICON_AUDIO_VOLUME_ID] = wtk_icon_button_create(parent, &area,
			&win_audio_vol_disable_icon, false, widget_ctx_audio->icon_group,
			(win_command_t)(ICON_AUDIO_VOLUME_ID));
	if (!widget_ctx_audio->icons[ICON_AUDIO_VOLUME_ID]) {
		goto error_widget;
	}
	
	win_show(wtk_icon_button_as_child(widget_ctx_audio->icons[ICON_AUDIO_VOLUME_ID]));

	/* Set area for the audio return icon */
	area.pos.x = 12;
	area.pos.y = 232;
	wtk_icon_button_size_hint(&area.size, &win_audio_ret_icon);

	/* Create the icon button inside frame */
	widget_ctx_audio->icons[ICON_AUDIO_RET_ID] = wtk_icon_button_create(parent, &area,
			&win_audio_ret_icon, false, widget_ctx_audio->icon_group,
			(win_command_t)(ICON_AUDIO_RET_ID));
	if (!widget_ctx_audio->icons[ICON_AUDIO_RET_ID]) {
		goto error_widget;
	}
	
	win_show(wtk_icon_button_as_child(widget_ctx_audio->icons[ICON_AUDIO_RET_ID]));

	gfx_draw_string(demo_idc, 55, 200,
		&sysfont, GFX_COLOR_TRANSPARENT, COLOR_BLUE);
	return;

	/* Error handling to clean up allocations after an error */
error_widget:
	win_destroy(wtk_basic_frame_as_child(widget_ctx_audio->frame));
error_frame:
	membag_free(widget_ctx_audio);
}

/**
 * \brief Enable/disable audio widget.
 *
 * \param on Turn on/off audio widget.
 */
void app_widget_audio_on(uint8_t on)
{
	if (on) {
		app_widget_launch_audio();
	} else {
		if (widget_ctx_audio->frame) {
			win_destroy(wtk_basic_frame_as_child(widget_ctx_audio->frame));
		}
	}

}
