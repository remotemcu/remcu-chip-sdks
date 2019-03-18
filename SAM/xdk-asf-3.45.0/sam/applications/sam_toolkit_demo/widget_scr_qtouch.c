/**
 * \file
 *
 * \brief QTouch widget for SAM toolkit demo application
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
 * \brief Command event IDs for QTouch widget.
 */
enum qtouch_command_id {
	/** Dummy icon */
	ICON_DUMMY_ID = 0,
	/** Command event ID for QTouch up icon button */
	ICON_QTOUCH_BTN_UP_ID,
	/** Command event ID for QTouch down icon button */
	ICON_QTOUCH_BTN_DOWN_ID,
	/** Command event ID for QTouch previous icon button */
	ICON_QTOUCH_BTN_PREV_ID,
	/** Command event ID for QTouch next icon button */
	ICON_QTOUCH_BTN_NEXT_ID,
	/** Command event ID for QTouch enter icon button */
	ICON_QTOUCH_BTN_ENTER_ID,
	/** Command event ID for QTouch up icon button pressed */
	ICON_QTOUCH_BTN_UP_PRESS_ID,
	/** Command event ID for QTouch down icon button pressed*/
	ICON_QTOUCH_BTN_DOWN_PRESS_ID,
	/** Command event ID for QTouch previous icon button pressed*/
	ICON_QTOUCH_BTN_PREV_PRESS_ID,
	/** Command event ID for QTouch next icon button pressed*/
	ICON_QTOUCH_BTN_NEXT_PRESS_ID,
	/** Command event ID for QTouch enter icon button pressed*/
	ICON_QTOUCH_BTN_ENTER_PRESS_ID,
	/** Command event ID for QTouch widget return icon button */
	ICON_QTOUCH_RET_ID,
	/** QTouch max icon number*/
	ICON_QTOUCH_MAX_ID,	
};

/** QTouch widget context */
struct widget_context_qtouch {
	/** Pointer to frame for application */
	struct wtk_basic_frame *frame;
	/** Frame background object */
	struct gfx_bitmap frame_bg;
	/** Pointer to slider */
	struct wtk_slider *slider;
	/** Pointer to progress bar */
	struct wtk_progress_bar *pb;
	/* Group of icon button widgets */
	struct wtk_icon_group *icon_group;
	/* Array if icon button widgets */
	struct wtk_icon_button *icons[ICON_QTOUCH_MAX_ID];
};

/** Statically allocated context pointer */
static struct widget_context_qtouch *widget_ctx_qtouch;

/** QTouch up button bitmap */
static struct gfx_bitmap win_qtouch_btn_up_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_QT_UP
};

/** QTouch down button bitmap */
static struct gfx_bitmap win_qtouch_btn_down_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_QT_DOWN
};

/** QTouch previous button bitmap */
static struct gfx_bitmap win_qtouch_btn_prev_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_QT_PREV
};

/** QTouch next button bitmap */
static struct gfx_bitmap win_qtouch_btn_next_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_QT_NEXT
};

/** QTouch enter button bitmap */
static struct gfx_bitmap win_qtouch_btn_enter_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_QT_ENTER
};

/** QTouch up button pressed bitmap */
static struct gfx_bitmap win_qtouch_btn_up_press_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_QT_UP_PRESSED
};

/** QTouch down button pressed bitmap */
static struct gfx_bitmap win_qtouch_btn_down_press_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_QT_DOWN_PRESSED
};

/** QTouc previous button pressed bitmap */
static struct gfx_bitmap win_qtouch_btn_prev_press_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_QT_PREV_PRESSED
};

/** QTouch next button pressed bitmap */
static struct gfx_bitmap win_qtouch_btn_next_press_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_QT_NEXT_PRESSED
};

/** QTouch enter button pressed bitmap */
static struct gfx_bitmap win_qtouch_btn_enter_press_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_QT_ENTER_PRESSED
};

/** QTouch return icon bitmap */
static struct gfx_bitmap win_settings_ret_icon = {
	.width = 48, .height=48,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BTN_BACK
};

/**
 * \brief Frame handler for the QTouch widget.
 *
 * Handles all command events from the widgets in the QTouch frame.
 *
 * \param frame Pointer to the application frame
 * \param command_data Command event ID
 *
 * \return True if exiting, to destroy the window
 */
static bool widget_qtouch_command_handler(struct wtk_basic_frame *frame,
		win_command_t command_data)
{
	char command;
	command = (uintptr_t)command_data;

	/* Remove warnings */
	UNUSED(frame);

	switch (command) {
	case ICON_QTOUCH_BTN_UP_ID:
		/* Display the QTouch up pressed bitmap */
		win_hide(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_UP_ID]));
		win_show(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_UP_PRESS_ID]));
		break;

	case ICON_QTOUCH_BTN_DOWN_ID:
		/* Display the QTouch down pressed bitmap */
		win_hide(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_DOWN_ID]));
		win_show(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_DOWN_PRESS_ID]));
		break;

	case ICON_QTOUCH_BTN_PREV_ID:
		/* Display the QTouch previous pressed bitmap */
		win_hide(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_PREV_ID]));
		win_show(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_PREV_PRESS_ID]));
		break;

	case ICON_QTOUCH_BTN_NEXT_ID:
		/* Display the QTouch next pressed bitmap */
		win_hide(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_NEXT_ID]));
		win_show(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_NEXT_PRESS_ID]));
		break;

	case ICON_QTOUCH_BTN_ENTER_ID:
		/* Display the QTouch enter pressed bitmap */
		win_hide(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_ENTER_ID]));
		win_show(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_ENTER_PRESS_ID]));
		break;

	case ICON_QTOUCH_BTN_UP_PRESS_ID:
		/* Display the QTouch up bitmap */
		win_hide(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_UP_PRESS_ID]));
		win_show(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_UP_ID]));
		break;

	case ICON_QTOUCH_BTN_DOWN_PRESS_ID:
		/* Display the QTouch down bitmap */
		win_hide(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_DOWN_PRESS_ID]));
		win_show(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_DOWN_ID]));
		break;

	case ICON_QTOUCH_BTN_PREV_PRESS_ID:
		/* Display the QTouch previous bitmap */
		win_hide(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_PREV_PRESS_ID]));
		win_show(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_PREV_ID]));
		break;

	case ICON_QTOUCH_BTN_NEXT_PRESS_ID:
		/* Display the QTouch next bitmap */
		win_hide(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_NEXT_PRESS_ID]));
		win_show(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_NEXT_ID]));
		break;

	case ICON_QTOUCH_BTN_ENTER_PRESS_ID:
		/* Display the QTouch enter bitmap */
		win_hide(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_ENTER_PRESS_ID]));
		win_show(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_ENTER_ID]));
		break;

	case ICON_QTOUCH_RET_ID:
		/* Turn off QTouch widget */
		app_widget_qtouch_on(false);

		/* Turn on main widget */
		app_widget_main_on(true);

		/* Reset the QTouch mode */
		demo_set_special_mode_status(DEMO_QTOUCH_MODE, 0);
		break;
	}
	return false;
}


/**
 * \brief Setup QTouch widget.
 *
 * Allocates memory for the application context, and creates all widgets that
 * make up its interface. If memory allocation or widget creation fails, the
 * application exits immediately.
 */
static void app_widget_launch_qtouch(void)
{
	struct win_window *parent;
	struct win_area area;

	/* Create a new context for the GUI, clear new context state */
	widget_ctx_qtouch = membag_alloc(sizeof(struct widget_context_qtouch));

	/* Set the background information for the GUI window */
	widget_ctx_qtouch->frame_bg.type = GFX_BITMAP_SOLID;
	widget_ctx_qtouch->frame_bg.data.color = GFX_COLOR(255, 255, 255);

	/* Set the area for the GUI window */
	area = win_get_attributes(win_get_root())->area;

	/* Create and show the main GUI frame */
	widget_ctx_qtouch->frame = wtk_basic_frame_create(
			win_get_root(), &area, &widget_ctx_qtouch->frame_bg, NULL,
			widget_qtouch_command_handler, widget_ctx_qtouch);
	if (!widget_ctx_qtouch->frame) {
		goto error_frame;
	}

	parent = wtk_basic_frame_as_child(widget_ctx_qtouch->frame);
	win_show(parent);

	/* Create a logical group for the icon buttons */
	widget_ctx_qtouch->icon_group = wtk_icon_group_create();
	if (!widget_ctx_qtouch->icon_group) {
		goto error_widget;
	}

	/* Set area for the QTouch up icon button widget */
	area.pos.x = 96;
	area.pos.y = 70;
	wtk_icon_button_size_hint(&area.size, &win_qtouch_btn_up_press_icon);

	/* Create the QTouch up pressed icon button inside frame */
	widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_UP_PRESS_ID] = wtk_icon_button_create(parent, &area,
			&win_qtouch_btn_up_press_icon, false, widget_ctx_qtouch->icon_group,
			(win_command_t)(ICON_QTOUCH_BTN_UP_PRESS_ID));
	if (!widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_UP_PRESS_ID]) {
		goto error_widget;
	}

	/* Hide the pressed bitmap by default */
	win_hide(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_UP_PRESS_ID]));

	wtk_icon_button_size_hint(&area.size, &win_qtouch_btn_up_icon);

	/* Create the QTouch up icon button inside frame */
	widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_UP_ID] = wtk_icon_button_create(parent, &area,
			&win_qtouch_btn_up_icon, false, widget_ctx_qtouch->icon_group,
			(win_command_t)(ICON_QTOUCH_BTN_UP_ID));
	if (!widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_UP_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_UP_ID]));

	/* Set area for the QTouch down icon button widget */
	area.pos.x = 96;
	area.pos.y = 200;
	wtk_icon_button_size_hint(&area.size, &win_qtouch_btn_down_press_icon);

	/* Create the QTouch down pressed icon button inside frame */
	widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_DOWN_PRESS_ID] = wtk_icon_button_create(parent, &area,
			&win_qtouch_btn_down_press_icon, false, widget_ctx_qtouch->icon_group,
			(win_command_t)(ICON_QTOUCH_BTN_DOWN_PRESS_ID));
	if (!widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_DOWN_PRESS_ID]) {
		goto error_widget;
	}
	win_hide(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_DOWN_PRESS_ID]));

	/* Hide the pressed bitmap by default */
	wtk_icon_button_size_hint(&area.size, &win_qtouch_btn_down_icon);

	/* Create the QTouch down icon button inside frame */
	widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_DOWN_ID] = wtk_icon_button_create(parent, &area,
			&win_qtouch_btn_down_icon, false, widget_ctx_qtouch->icon_group,
			(win_command_t)(ICON_QTOUCH_BTN_DOWN_ID));
	if (!widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_DOWN_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_DOWN_ID]));

	/* Set area for the QTouch previous icon button widget */
	area.pos.x = 30;
	area.pos.y = 136;
	wtk_icon_button_size_hint(&area.size, &win_qtouch_btn_prev_press_icon);

	/* Create the QTouch previous pressed icon button inside frame */
	widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_PREV_PRESS_ID] = wtk_icon_button_create(parent, &area,
			&win_qtouch_btn_prev_press_icon, false, widget_ctx_qtouch->icon_group,
			(win_command_t)(ICON_QTOUCH_BTN_PREV_PRESS_ID));
	if (!widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_PREV_PRESS_ID]) {
		goto error_widget;
	}
	/* Hide the pressed bitmap by default */
	win_hide(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_PREV_PRESS_ID]));

	wtk_icon_button_size_hint(&area.size, &win_qtouch_btn_prev_icon);

	/* Create the next icon button inside frame */
	widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_PREV_ID] = wtk_icon_button_create(parent, &area,
			&win_qtouch_btn_prev_icon, false, widget_ctx_qtouch->icon_group,
			(win_command_t)(ICON_QTOUCH_BTN_PREV_ID));
	if (!widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_PREV_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_PREV_ID]));

	/* Set area for the QTouch next icon button widget */
	area.pos.x = 170;
	area.pos.y = 136;
	wtk_icon_button_size_hint(&area.size, &win_qtouch_btn_next_press_icon);

	/* Create the QTouch next pressed icon button inside frame */
	widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_NEXT_PRESS_ID] = wtk_icon_button_create(parent, &area,
			&win_qtouch_btn_next_press_icon, false, widget_ctx_qtouch->icon_group,
			(win_command_t)(ICON_QTOUCH_BTN_NEXT_PRESS_ID));
	if (!widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_NEXT_PRESS_ID]) {
		goto error_widget;
	}
	/* Hide the pressed bitmap by default */
	win_hide(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_NEXT_PRESS_ID]));

	wtk_icon_button_size_hint(&area.size, &win_qtouch_btn_next_icon);

	/* Create the QTouch next icon button inside frame */
	widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_NEXT_ID] = wtk_icon_button_create(parent, &area,
			&win_qtouch_btn_next_icon, false, widget_ctx_qtouch->icon_group,
			(win_command_t)(ICON_QTOUCH_BTN_NEXT_ID));
	if (!widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_NEXT_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_NEXT_ID]));

	/* Set area for the QTouch enter icon button widget */
	area.pos.x = 96;
	area.pos.y = 136;
	wtk_icon_button_size_hint(&area.size, &win_qtouch_btn_enter_press_icon);

	/* Create the QTouch enter pressed icon button inside frame */
	widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_ENTER_PRESS_ID] = wtk_icon_button_create(parent, &area,
			&win_qtouch_btn_enter_press_icon, false, widget_ctx_qtouch->icon_group,
			(win_command_t)(ICON_QTOUCH_BTN_ENTER_PRESS_ID));
	if (!widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_ENTER_PRESS_ID]) {
		goto error_widget;
	}
	/* Hide the pressed bitmap by default */
	win_hide(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_ENTER_PRESS_ID]));

	wtk_icon_button_size_hint(&area.size, &win_qtouch_btn_enter_icon);

	/* Create the QTouch enter icon button inside frame */
	widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_ENTER_ID] = wtk_icon_button_create(parent, &area,
			&win_qtouch_btn_enter_icon, false, widget_ctx_qtouch->icon_group,
			(win_command_t)(ICON_QTOUCH_BTN_ENTER_ID));
	if (!widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_ENTER_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_BTN_ENTER_ID]));

	/* Update area for the return icon button widget */
	area.pos.x = 12;
	area.pos.y = 232;

	/* Create the return icon button inside frame */
	widget_ctx_qtouch->icons[ICON_QTOUCH_RET_ID] = wtk_icon_button_create(parent, &area,
			&win_settings_ret_icon, false, widget_ctx_qtouch->icon_group,
			(win_command_t)(ICON_QTOUCH_RET_ID));
	if (!widget_ctx_qtouch->icons[ICON_QTOUCH_RET_ID]) {
		goto error_widget;
	}

	win_show(wtk_icon_button_as_child(widget_ctx_qtouch->icons[ICON_QTOUCH_RET_ID]));

	gfx_draw_rect(19, 19, 202, 42, GFX_COLOR(0, 0, 0));

	demo_set_special_mode_status(DEMO_QTOUCH_MODE, 1);
	return;

	/* Error handling to clean up allocations after an error */
error_widget:
	win_destroy(wtk_basic_frame_as_child(widget_ctx_qtouch->frame));
error_frame:
	membag_free(widget_ctx_qtouch);
}

/**
 * \brief Enable/disable QTouch widget.
 *
 * \param on Turn on/off QTouch widget.
 */
void app_widget_qtouch_on(uint8_t on)
{
	if (on) {
		app_widget_launch_qtouch();
	} else {
		if (widget_ctx_qtouch->frame) {
			win_destroy(wtk_basic_frame_as_child(widget_ctx_qtouch->frame));
		}
	}

}
