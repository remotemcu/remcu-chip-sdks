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
	SLIDER_ID,
	BUTTON_ID,
};

/** Widget application context */
struct widget_context {
	/** Pointer to frame for application */
	struct wtk_basic_frame *frame;
	/** Frame background object */
	struct gfx_bitmap frame_bg;
	/** Plot background object */
	struct gfx_bitmap plot_bg;
	/** Pointer to plot for application */	
	struct wtk_plot	*plot;
	/** Pointer to slider for application */
	struct wtk_slider *slider;
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

	switch (command) {
	case BUTTON_ID:
		/* Update the plot with the new value as set by the slider */
		wtk_plot_add_value(widget->plot, wtk_slider_get_value(widget->slider));
		
		/* Redraw the plot with the new value */
		win_redraw(wtk_plot_as_child(widget->plot));
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
	struct wtk_button *button;

	/* Create a new context for the GUI */
	widget_ctx = membag_alloc(sizeof(struct widget_context));
	if (!widget_ctx) {
		return false;
	}

	/* Initialize context data. */
	widget_ctx->frame_bg.type = GFX_BITMAP_SOLID;
	widget_ctx->frame_bg.data.color = GFX_COLOR(220, 220, 220);

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

	/* Set the background information for the plot widget */
	widget_ctx->plot_bg.type = GFX_BITMAP_SOLID;
	widget_ctx->plot_bg.data.color = GFX_COLOR_WHITE;

	/* Adjust area for the plot widget */
	area.size.y -= 80;
	area.size.x -= 40;

	/* Create and show the plot widget with vertical axis marks */
	widget_ctx->plot = wtk_plot_create(parent, &area, 100, 10, GFX_COLOR_RED,
			&widget_ctx->plot_bg, WTK_PLOT_LEFT_TO_RIGHT);
	if (!widget_ctx->plot) {
		goto error_widget;
	}
	wtk_plot_set_grid(widget_ctx->plot, WTK_PLOT_TICKS_VERTICAL,
			10, 0, 10, 0, GFX_COLOR_BLUE, GFX_COLOR_GREEN);
	win_show(wtk_plot_as_child(widget_ctx->plot));
	
	/* Adjust area for the slider widget */
	area.pos.y += area.size.y + 10;
	area.size.y = 40;
	area.size.x -= 60;
	
	/* Create and show the slider widget */
	widget_ctx->slider = wtk_slider_create(parent, &area, 100, 0,
			WTK_SLIDER_HORIZONTAL, (win_command_t)SLIDER_ID);	
	if (!widget_ctx->slider) {
		goto error_widget;
	}
	win_show(wtk_slider_as_child(widget_ctx->slider));	
	
	/* Adjust area for the button widget */
	area.pos.x += area.size.x + 10;
	area.size.x = 50;
	
	/* Create and show the button widget */
	button = wtk_button_create(parent, &area, "Add", (win_command_t)BUTTON_ID);	
	if (!button) {
		goto error_widget;
	}
	win_show(wtk_button_as_child(button));

	return true;

	/* Error handling to clean up allocations after an error */
error_widget:
	win_destroy(wtk_basic_frame_as_child(widget_ctx->frame));
error_frame:
	membag_free(widget_ctx);
	
	return false;
}

/** @} */
