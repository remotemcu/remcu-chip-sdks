/**
 * \file
 *
 * \brief User interface for mXT143E Xplained trackpad demo
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
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include <conf_example.h>
#include "ui.h"
#include "conf_usb.h"

/**
 * \name Touch trace settings
 * @{
 */
/** Size (width/height) of trace-rectangle */
#define TRACE_RECT_SIZE 10
/**
 * \brief Number of rectangles in the touch trace
 *
 * \note This macro essentially sets the length of the trace.
 * */
#define NUM_TRACES      150
#if (NUM_TRACES > 255)
/* ...must be an 8-bit value */
# error "NUM_TRACES out of bounds!"
#endif
/** @} */

/** Flag that a new touch event is pending*/
bool ui_new_touch_event;
/** Struct to hold touch events to process */
struct mxt_touch_event ui_touch_event;

/** Information for one trace point */
struct trace_info {
	gfx_coord_t x; /**< Screen trace X-coordinate */
	gfx_coord_t y; /**< Screen trace Y-coordinate */
};

/** Array to hold all trace points */
static struct trace_info trace[NUM_TRACES];

/**
 * \name Display size containers
 *
 * To avoid fetching the display size multiple times from the graphics service,
 * store them in these two variables upon initialization.
 *
 * @{
 */
static uint16_t display_w; /**< Display width */
static uint16_t display_h; /**< Display height */
/** @} */

/**
 * \brief Draw a frame
 *
 * This function draws a frame with the specified thickness and color on the
 * display, at the specified start offset from the edges.
 *
 * \param start Start offset (x and y, from 0) of frame
 * \param thickness Thickness (in pixels) of frame
 * \param color Color of frame
 */
static void draw_frame(const uint8_t start, const uint8_t thickness,
		const gfx_color_t color)
{
	uint8_t c;

	/* Simply draw a rectangle THICKNESS number of times */
	for (c = 0; c < thickness; c++) {
		gfx_draw_rect(start + c, start + c,
				display_w - ((start + c) * 2),
				display_h - ((start + c) * 2), color);
	}
}

/**
 * \brief Handle finger traces on display
 *
 * This function updates the traces, drawing a new one at the specified
 * coordinates and clearing the oldest one. It must be called at regular
 * intervals to give a smooth trace animation.
 *
 * \param x X-coordinate of finger touch
 * \param y Y-coordinate of finger touch
 *
 * \note The coordinate (0,0) is used to indicate no touch, thus only causing
 * the oldest trace to be cleared.
 */
static void handle_trace(gfx_coord_t x, gfx_coord_t y)
{
	/* Keep track of trace struct position */
	static uint8_t trace_write = 0;

	/* Translate touch coordinates to display coordinates */
	x = (x * (uint32_t)display_w) / 4096L;
	y = (y * (uint32_t)display_h) / 4096L;

	if ((x > 0) && (y > 0)) {
		/* Limit coordinates to avoid drawing on any drawn touch/press frames */
		x = max(x, 4);
		x = min(x, (display_w - TRACE_RECT_SIZE - 4));
		y = max(y, 4);
		y = min(y, (display_h - TRACE_RECT_SIZE - 4));

		/* Draw the validated trace coordinates to the display */
		gfx_draw_rect(x, y, TRACE_RECT_SIZE, TRACE_RECT_SIZE,
				GFX_COLOR_WHITE);

		/* Store new trace point */
		trace[trace_write].x = x;
		trace[trace_write].y = y;
	}

	/* Increment (and wrap) our trace struct index */
	if (++trace_write >= NUM_TRACES) {
		trace_write = 0;
	}

	/* Clear the oldest trace point */
	if ((trace[trace_write].x > 0) && (trace[trace_write].y > 0)) {
		/* Valid trace. Clear it */
		gfx_draw_rect(trace[trace_write].x, trace[trace_write].y,
				TRACE_RECT_SIZE, TRACE_RECT_SIZE,
				COLOR_BACKGROUND);
		/* Invalidate trace by clearing coordinates */
		trace[trace_write].x = trace[trace_write].y = 0;
	}
}

/** Initialize the user interface */
void ui_init(void)
{
	uint8_t n;

	LED_On(LED0_GPIO);
	LED_Off(LED1_GPIO);

	ui_new_touch_event = false;

	/* Initialize trace struct to all 0 */
	for (n = 0; n < NUM_TRACES; n++) {
		trace[n].x = trace[n].y = 0;
	}

	/* Get and keep display size */
	display_w = gfx_get_width();
	display_h = gfx_get_height();
}

/** Put the user interface in power down */
void ui_powerdown(void)
{
	LED_Off(LED0_GPIO);
	LED_Off(LED1_GPIO);
}

/** Enable asynchronous interrupts of the user interface */
void ui_wakeup_enable(void)
{
	/* Intentionally left empty */
}

/** Disable asynchronous interrupts of the user interface */
void ui_wakeup_disable(void)
{
	/* Intentionally left empty */
}

/** Wake the user interface up */
void ui_wakeup(void)
{
	LED_On(LED0_GPIO);
}

/**
 * \brief Process the user interface
 *
 * This function processes user touch events and updates the display.
 *
 * The first registered touch is used to control the cursor. Its presence is
 * indicated with a red frame around the display. When the cursor touch moves,
 * its movement is visualized with a trace on the display.
 *
 * The second registered touch is used to control mouse buttons, and is
 * indicated with an inner frame of which the color depends on which side the
 * touch is for: blue for left and green for right button click. The frame is
 * shown until the touch is released.
 * To detect which side click it is, the position relative to the cursor touch
 * is used, i.e., a touch to the left of the first touch will cause a left
 * mouse click.
 *
 * \param framenumber Current USB frame number
 *
 * \note This function should be called every millisecond, e.g., for each USB
 * frame.
 */
void ui_process(uint16_t framenumber)
{
	static bool process_traces = false;
	static bool register_trace = false;
	static bool left_press = true;
	static gfx_coord_t old_x;
	static gfx_coord_t old_y;
	uint16_t blink_frame;
	uint8_t new_x_pos;
	uint8_t new_y_pos;

	/* Blink LED1 at 1 Hz (toggle every 500 frames) */
	blink_frame = framenumber % 1000;
	if (blink_frame == 0) {
		LED_On(LED1_GPIO);
	} else if (blink_frame == 500) {
		LED_Off(LED1_GPIO);
	}

	/* Interleave processing of traces and touch events so they are each
	 * handled every 2 milliseconds.
	 */
	if (process_traces) {
		process_traces = false;

		/* Is there a new trace to register? */
		if (register_trace) {
			handle_trace(old_x, old_y);
		/* No new trace, clear an old one */
		} else {
			handle_trace(0, 0);
		}

		/* Return now, don't process touches */
		return;
	}

	/* Process traces in next iteration */
	process_traces = true;
	register_trace = false;

	/* Process new touch, if it was flagged */
	if (ui_new_touch_event) {
		ui_new_touch_event = false;

		/* Is event for first finger on display? */
		if (ui_touch_event.id == 0) {
			/* Upon new press, draw red frame */
			if (ui_touch_event.status & MXT_PRESS_EVENT) {
				old_x = ui_touch_event.x;
				old_y = ui_touch_event.y;
				draw_frame(0, 2, GFX_COLOR_RED);

			/* Upon release, erase red frame */
			} else if (ui_touch_event.status & MXT_RELEASE_EVENT) {
				draw_frame(0, 2, COLOR_BACKGROUND);

			/* Upon move, update mouse position and display trace */
			} else if (ui_touch_event.status & MXT_DETECT_EVENT) {
				/* Scale the relative position down to get a
				 * sensible cursor speed.
				 */
				new_x_pos = (ui_touch_event.x - old_x) >> 2;
				new_y_pos = (ui_touch_event.y - old_y) >> 2;

				udi_hid_mouse_moveX(new_x_pos);
				udi_hid_mouse_moveY(new_y_pos);

				old_x = ui_touch_event.x;
				old_y = ui_touch_event.y;

				register_trace = true;
			}
		}

		/* Is event for second finger on display? */
		if (ui_touch_event.id == 1) {
			/* For new press, signal a left or right mouse button
			 * press depending on which side of the cursor it's on
			 */
			if (ui_touch_event.status & MXT_PRESS_EVENT) {
				/* Left click? */
				if (ui_touch_event.x <= old_x) {
					left_press = true;
					udi_hid_mouse_btnleft(HID_MOUSE_BTN_DOWN);

					/* Draw a blue inner-frame */
					draw_frame(2, 2, GFX_COLOR_BLUE);

				/* Must otherwise be a right click. */
				} else {
					left_press = false;
					udi_hid_mouse_btnright(HID_MOUSE_BTN_DOWN);

					/* Draw a green inner-frame */
					draw_frame(2, 2, GFX_COLOR_GREEN);
				}
			}

			/* For release, signal release of the mouse button */
			if (ui_touch_event.status & MXT_RELEASE_EVENT) {
				if (left_press) {
					udi_hid_mouse_btnleft(HID_MOUSE_BTN_UP);
				} else {
					udi_hid_mouse_btnright(HID_MOUSE_BTN_UP);
				}

				/* Erase blue/green inner-frame */
				draw_frame(2, 2, COLOR_BACKGROUND);
			}
		}
	}
}
