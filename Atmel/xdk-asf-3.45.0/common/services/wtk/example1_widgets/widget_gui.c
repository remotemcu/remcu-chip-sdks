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
	/** Command event ID for slider */
	SLIDER_ID,
	/** Command event ID for check box */
	CHECK_BOX_ID,
	/** Command event ID for radio button 1 */
	RADIO_BUTTON_1_ID,
	/** Command event ID for radio button 2 */
	RADIO_BUTTON_2_ID,
	/** Command event ID for button */
	BUTTON_ID,
};

/**
 * \name Color scheme
 *
 * @{
 */

/** Color scheme 0 foreground color */
#define COLOR_SCHEME_0_FG           GFX_COLOR(30, 30, 200)
/** Color scheme 0 background color */
#define COLOR_SCHEME_0_BG           GFX_COLOR(255, 255, 255)
/** Color scheme 1 foreground color */
#define COLOR_SCHEME_1_FG           GFX_COLOR(0, 255, 0)
/** Color scheme 1 background color */
#define COLOR_SCHEME_1_BG           GFX_COLOR(0, 100, 100)

/** Background color of the application frame */
#define APP_BACKGROUND_COLOR        GFX_COLOR(220, 220, 220)

/** @} */

/**
 * \name Widget positions and sizes
 *
 * @{
 */

/** Leftmost X coordinate in frame for the widgets */
#define WIDGET_POS_X                14
/** Topmost Y coordinate in frame for the widgets */
#define WIDGET_POS_Y                5

/** Slider X coordinate, inside frame */
#define SLIDER_POS_Y                10
/** Width of slider */
#define SLIDER_SIZE_X               120
/** Height of slider */
#define SLIDER_SIZE_Y               40

/** Spacing between the slider and progress bars */
#define SLIDER_PB_SPACING_X         10
/** Width of progress bar */
#define PB_SIZE_X                   SLIDER_SIZE_X
/** Height of progress bar */
#define PB_SIZE_Y                   SLIDER_SIZE_Y

/** Spacing above check box to slider and progress bars */
#define CHECK_BOX_SPACING_Y         20

/** Spacing above each radio button */
#define RADIO_BUTTON_SPACING_Y      10

/** Spacing above the button */
#define BUTTON_SPACING_Y            20
/** Height of the button */
#define BUTTON_SIZE_Y               30

/** @} */

/** Description for the check box */
const static char checkbox_string[] = "Invert colors";
/** Description for the first radio button */
const static char rb1_string[]      = "Color scheme 1";
/** Description for the second radio button */
const static char rb2_string[]      = "Color scheme 2";
/** Description for the button */
const static char btn_string[]      = "Reset Slider";

/** Widget application context */
struct widget_context {
	/** Pointer to frame for application */
	struct wtk_basic_frame *frame;
	/** Frame background object */
	struct gfx_bitmap frame_bg;
	/** Pointer to slider */
	struct wtk_slider *slider;
	/** Pointer to progress bar */
	struct wtk_progress_bar *pb;
	/** Current color scheme in use */
	uint8_t color_scheme;
	/** Current color scheme has inverted colors */
	bool color_invert;
};

/** Statically allocated context pointer */
static struct widget_context *widget_ctx;

/**
 * \brief Update colors
 *
 * Updates the colors for the progress bar and issues redrawing of the widgets.
 *
 * \param widget Context for widget application
 */
static void app_widget_update_colors(struct widget_context *widget)
{
	gfx_color_t temp;
	gfx_color_t fg;
	gfx_color_t bg;

	switch (widget->color_scheme) {
	case 1:
		/* Set colors for color scheme 1 */
		fg = COLOR_SCHEME_1_FG;
		bg = COLOR_SCHEME_1_BG;
		break;

	default:
		/* Set default color scheme */
		fg = COLOR_SCHEME_0_FG;
		bg = COLOR_SCHEME_0_BG;
		break;
	}

	if (widget->color_invert) {
		temp = bg;
		bg = fg;
		fg = temp;
	}

	wtk_progress_bar_set_colors(widget->pb, fg, bg);
	win_redraw(wtk_progress_bar_as_child(widget->pb));
}

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

	switch (command) {
	case SLIDER_ID:
		/* Update the progress bar when slider value changes. */
		wtk_progress_bar_set_value(widget->pb,
				wtk_slider_get_value(widget->slider));
		break;

	case CHECK_BOX_ID:
		/* Invert the colors for the progress bar. */
		widget->color_invert = !widget->color_invert;
		app_widget_update_colors(widget);
		break;

	case RADIO_BUTTON_1_ID:
		/* Set first color scheme for the progress bar. */
		widget->color_scheme = 0;
		app_widget_update_colors(widget);
		break;

	case RADIO_BUTTON_2_ID:
		/* Set second color scheme for the progress bar. */
		widget->color_scheme = 1;
		app_widget_update_colors(widget);
		break;

	case BUTTON_ID:
		/* Reset the slider and progress bar values and update */
		wtk_slider_set_value(widget->slider, 0);
		wtk_progress_bar_set_value(widget->pb, 0);
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
	struct wtk_check_box *cb;
	struct wtk_radio_group *rg;
	struct wtk_radio_button *rb;
	struct wtk_button *btn;

	/* Create a new context for the GUI */
	widget_ctx = membag_alloc(sizeof(struct widget_context));
	if (!widget_ctx) {
		return false;
	}

	/* Initialize context data. */
	widget_ctx->color_scheme = 0;
	widget_ctx->color_invert = 0;

	/* Set the background information for the GUI window */
	widget_ctx->frame_bg.type = GFX_BITMAP_SOLID;
	widget_ctx->frame_bg.data.color = APP_BACKGROUND_COLOR;

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

	/* Update area for the slider widget */
	area.pos.x = WIDGET_POS_X;
	area.pos.y = WIDGET_POS_Y + SLIDER_POS_Y;
	area.size.x = SLIDER_SIZE_X;
	area.size.y = SLIDER_SIZE_Y;

	/* Create slider inside frame */
	widget_ctx->slider = wtk_slider_create(parent, &area, 100, 50,
			WTK_SLIDER_HORIZONTAL | WTK_SLIDER_CMD_MOVE | WTK_SLIDER_CMD_RELEASE,
			(win_command_t)SLIDER_ID);

	if (!widget_ctx->slider) {
		goto error_widget;
	}
	win_show(wtk_slider_as_child(widget_ctx->slider));

	/* Update area for the progress bar widget */
	area.pos.x += area.size.x + SLIDER_PB_SPACING_X;
	area.size.x = PB_SIZE_X;
	area.size.y = PB_SIZE_Y;

	/* Create progress bar to the right of the slider */
	widget_ctx->pb = wtk_progress_bar_create(parent, &area, 100,
			50, GFX_COLOR_BLACK, GFX_COLOR_BLACK, WTK_PROGRESS_BAR_HORIZONTAL);

	if (!widget_ctx->pb) {
		goto error_widget;
	}
	win_show(wtk_progress_bar_as_child(widget_ctx->pb));
	app_widget_update_colors(widget_ctx);

	/* Update area for the checkbox widget */
	area.pos.x = WIDGET_POS_X;
	area.pos.y += area.size.y + CHECK_BOX_SPACING_Y;
	wtk_check_box_size_hint(&area.size, checkbox_string);

	/* Create check box below slider and progress bar */
	cb = wtk_check_box_create(parent, &area, checkbox_string,
			false, (win_command_t)CHECK_BOX_ID);

	if (!cb) {
		goto error_widget;
	}
	win_show(wtk_check_box_as_child(cb));

	/* Create a logical group for the radio buttons */
	rg = wtk_radio_group_create();
	if (!rg) {
		goto error_widget;
	}

	/* Update area for the first radio button widget */
	area.pos.y += area.size.y + RADIO_BUTTON_SPACING_Y;
	wtk_radio_button_size_hint(&area.size, rb1_string);

	/* Create first radio button widget */
	rb = wtk_radio_button_create(parent, &area, rb1_string,
			true, rg, (win_command_t)RADIO_BUTTON_1_ID);

	if (!rb) {
		goto error_widget;
	}
	win_show(wtk_radio_button_as_child(rb));

	/* Update area for the second radio button widget */
	area.pos.y += area.size.y + RADIO_BUTTON_SPACING_Y;
	wtk_radio_button_size_hint(&area.size, rb2_string);

	/* Create second radio button widget */
	rb = wtk_radio_button_create(parent, &area, rb2_string,
			false, rg, (win_command_t)RADIO_BUTTON_2_ID);

	if (!rb) {
		goto error_widget;
	}
	win_show(wtk_radio_button_as_child(rb));

	/* Update area for the button widget */
	area.pos.y += area.size.y + BUTTON_SPACING_Y;
	area.size.x = SLIDER_SIZE_X + SLIDER_PB_SPACING_X + PB_SIZE_X;
	area.size.y = BUTTON_SIZE_Y;

	/* Create button widget */
	btn = wtk_button_create(parent, &area, btn_string, (win_command_t)BUTTON_ID);
	wtk_button_size_hint(&area.size, btn_string);

	if (!btn) {
		goto error_widget;
	}
	win_show(wtk_button_as_child(btn));

	return true;

	/* Error handling to clean up allocations after an error */
error_widget:
	win_destroy(wtk_basic_frame_as_child(widget_ctx->frame));
error_frame:
	membag_free(widget_ctx);
	
	return false;
}

/** @} */
