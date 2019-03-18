/**
 * \file
 *
 * \brief Calculator demo widget application
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
#include "widget_gui.h"

/**
 * \weakgroup app_widget_group
 *
 * @{
 */

/** Width (in pixels) of a normal sized button */
#define BT_W  40
/** Height (in pixels) of a normal sized button */
#define BT_H  40
/** Number of buttons in one column */
#define BT_X  4
/** Number of buttons in one row */
#define BT_Y  5
/** Spacing between widget frame and components*/
#define W_SP  16
/** Width of the static text field */
#define T_W   (BT_W * BT_X)
/** Height of the static text field */
#define T_H   16
/** Spacing between static text and button pad */
#define T_SP  16

/** Calculate button X coordinate */
#define BT_POS_X(col) (W_SP + (BT_W * (col)))
/** Calculate button Y coordinate */
#define BT_POS_Y(row) (W_SP + T_H + T_SP + (BT_H * (row)))

/** Maximum number of digits on display */
#define MAX_DIGITS 9
/** Maximum value we can show on display */
#define MAX_VALUE  999999999L
/** Minimum value we can show on display */
#define MIN_VALUE -999999999L

/** Calculator context */
struct app_calculator_t {
	/** Pointer to frame for application */
	struct wtk_basic_frame * frame;
	/** Pointer to display label */
	struct wtk_label * text;
	/** Frame background object */
	struct gfx_bitmap frame_bg;
	/** Pointer to Value text frame background */
	struct wtk_basic_frame * text_frame;
	/** Value Frame background object */
	struct gfx_bitmap text_frame_bg;

	/** Calculator internal state registers */
	struct {
		/** Current calculator state */
		enum {
			/** Waiting for first value */
			CALC_STATE_WAIT_VAL1,
			/** Waiting for operator */
			CALC_STATE_WAIT_OP,
			/** Waiting for second value */
			CALC_STATE_WAIT_VAL2,
			/**< Ready to calculate */
			CALC_STATE_READY,
			/** Error occurred (oveflow/division by zero) */
			CALC_STATE_ERROR,
		} state;

		/** Current calculator result */
		int32_t result;
		/** Current calculator operand */
		int32_t operand;
		/** Current calculator operator */
		char operation;
		/** Current calculator display value */
		int32_t display;
	} calc_regs;
};

/**
 * \brief Update calculator display with new value
 *
 * \param calc Pointer to calculator struct
 */
static void app_calc_update_disp(struct app_calculator_t *calc)
{
	int32_t display_value = calc->calc_regs.display;

	/* Prepare string scratchpad: sign + digits + 0. */
	char caption[1 + MAX_DIGITS + 1] = "ERROR";

	/* Index within the caption buffer where the display text starts */
	uint8_t caption_start = 0;

	/* Check for overflow */
	if ((display_value > MAX_VALUE) || (display_value < MIN_VALUE)) {
		calc->calc_regs.state = CALC_STATE_ERROR;
	}

	/* Only perform ASCII conversion if not currently in an error state */
	if (calc->calc_regs.state != CALC_STATE_ERROR) {
		/* Temporary variable to indicate sign of the display value */
		bool negative = false;

		/* Move the start of the caption to the end of the buffer and
		 * NUL terminate it
		 */
		caption_start = sizeof(caption);
		caption[--caption_start] = 0;

		/* If the value is negative, remember that in a temporary
		 * variable and make it positive for the conversion
		 */
		if (display_value < 0) {
			negative = true;
			display_value = -display_value;
		}

		/* Convert each integer power of 10 to corresponding ASCII */
		do {
			caption[--caption_start] = '0' + (display_value % 10);
			display_value /= 10;
		} while (display_value);

		/* If the value was originally negative, add the sign to the
		 * front of the buffer
		 */
		if (negative) {
			caption[--caption_start] = '-';
		}
	}

	/* Update display, ignore the return value */
	wtk_label_change(calc->text, &caption[caption_start]);
}

/**
 * \brief Perform calculation
 *
 * \param calc Pointer to calculator struct
 */
static void calc_perform_operation(struct app_calculator_t *calc)
{
	int32_t res = calc->calc_regs.result;

	switch (calc->calc_regs.operation) {

	/* Perform requested calculation */
	case '+':
		res += calc->calc_regs.operand;
		break;

	case '-':
		res -= calc->calc_regs.operand;
		break;

	case '*':
		res *= calc->calc_regs.operand;
		break;

	case '/':
		if (calc->calc_regs.operand == 0) {
			/* Division by zero, enter error state */
			calc->calc_regs.state = CALC_STATE_ERROR;
		} else {
			res /= calc->calc_regs.operand;
		}
		break;

	default:
		/* User pressed equals, copy operand to result */
		res = calc->calc_regs.operand;
		break;
	}

	/* Check for overflow */
	if ((res > MAX_VALUE) || (res < MIN_VALUE)) {
		calc->calc_regs.state = CALC_STATE_ERROR;
	}

	calc->calc_regs.result = res;
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
static bool app_calc_handler(struct wtk_basic_frame *frame,
		win_command_t command_data)
{
	/* Get calculator context from frame. */
	struct app_calculator_t *calc = (struct app_calculator_t *)
			wtk_basic_frame_get_custom_data(frame);

	/* Get button ID from the widget command data */
	char button_char = (uintptr_t)command_data;

	/* Handle button based on its value. */
	switch (button_char) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		switch (calc->calc_regs.state) {
			/* Waiting for first value, clear display and indicate
			 * we have at least one digit entered as the first value
			 */
			case CALC_STATE_WAIT_VAL1:
				calc->calc_regs.display = 0;
				calc->calc_regs.state = CALC_STATE_WAIT_OP;
				break;

			/* Waiting for second value, clear display and indicate
			 * we have at least one digit entered as the second
			 * value
			 */
			case CALC_STATE_WAIT_VAL2:
				calc->calc_regs.display = 0;
				calc->calc_regs.state = CALC_STATE_READY;
				break;

			default:
				break;
		}

		/* If not in error state, append the entered digit to the input
		 * value
		 */
		if (calc->calc_regs.state != CALC_STATE_ERROR) {
			calc->calc_regs.display *= 10;
			calc->calc_regs.display += (uint8_t)(button_char - '0');
			app_calc_update_disp(calc);
		}

		return false;

	case '/':
	case '*':
	case '-':
	case '+':
	case '=':
		switch (calc->calc_regs.state) {
			/* Waiting for an operator, first value becomes the
			 * result and we wait for the next value to be entered
			 */
			case CALC_STATE_WAIT_OP:
				calc->calc_regs.result =
						calc->calc_regs.display;
				calc->calc_regs.state = CALC_STATE_WAIT_VAL2;
				break;

			/* Two digits already entered, calculate using the
			 * current operator and loop back waiting for a new
			 * second value
			 */
			case CALC_STATE_READY:
				calc->calc_regs.operand =
						calc->calc_regs.display;
				calc_perform_operation(calc);

				if (calc->calc_regs.state != CALC_STATE_ERROR) {
					calc->calc_regs.state =
							CALC_STATE_WAIT_VAL2;
				}
				break;

			default:
				break;
		}

		/* Store the new operator and move the calc result to the
		 * display
		 */
		calc->calc_regs.operation = button_char;
		calc->calc_regs.display = calc->calc_regs.result;
		app_calc_update_disp(calc);

		return false;

	case 'C':
		/* See if we are clearing the current entered value, or the full
		 * calculator state
		 */
		if ((calc->calc_regs.display == 0) ||
			(calc->calc_regs.state == CALC_STATE_ERROR)) {
			/* Clear full calculator state */
			calc->calc_regs.operand = 0;
			calc->calc_regs.result = 0;
			calc->calc_regs.operation = 0;
			calc->calc_regs.display = 0;
			calc->calc_regs.state = CALC_STATE_WAIT_VAL1;
		} else {
			/* Clear current display only */
			calc->calc_regs.display = 0;
		}

		app_calc_update_disp(calc);
		return false;

	default:
		return false;
	}
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
	/* Layout of control widgets:
	 *
	 * ##################
	 * # ############## #
	 * # # 0000000000 # #
	 * # ############## #
	 * #                #
	 * #  C   /   *   - #
	 * #              - #
	 * #  7   8   9   - #
	 * #                #
	 * #  4   5   6   + #
	 * #              + #
	 * #  1   2   3   + #
	 * #                #
	 * #  00000   ===== #
	 * #                #
	 * ##################
	 */

	/* Variables used throughout function. */
	struct win_area area;
	char caption[2] = "0";
	struct wtk_button *button;

	/* Allocate memory for calculator application context data. */
	struct app_calculator_t *calc;
	calc = membag_alloc(sizeof(struct app_calculator_t));
	if (!calc) {
		return false;
	}

	/* Initialize context data. */
	calc->calc_regs.display = 0;
	calc->calc_regs.operand = 0;
	calc->calc_regs.result = 0;
	calc->calc_regs.operation = 0;
	calc->calc_regs.state = CALC_STATE_WAIT_VAL1;

	/* Set the background information for the GUI window */
	calc->frame_bg.type = GFX_BITMAP_SOLID;
	calc->frame_bg.data.color = GFX_COLOR(220, 220, 220);

	/* Prepare area for calculator application frame. */
	area.size.x = (W_SP * 2) + (BT_W * BT_X);
	area.size.y = (W_SP * 2) + T_SP + T_H + (BT_H * BT_Y);

	/* Center application frame on display */
	area.pos.x = (gfx_get_width() / 2) - (area.size.x / 2);
	area.pos.y = (gfx_get_height() / 2) - (area.size.y / 2);

	/* Create the frame. */
	calc->frame = wtk_basic_frame_create(
			win_get_root(),
			&area,
			&calc->frame_bg,
			NULL,
			app_calc_handler,
			calc);

	if (!calc->frame) {
		goto error_frame;
	}
	
	/* Create digit buttons 1-9. */
	area.size.x = BT_W;
	area.size.y = BT_H;

	for (uint8_t row = 0; row < 3; ++row) {
		/* Prepare Y coord for buttons. */
		area.pos.y = BT_POS_Y(row + 1);

		for (uint8_t col = 0; col < 3; ++col) {
			/* Prepare X coord for button. */
			area.pos.x = BT_POS_X(col);

			/* Prepare digit caption. */
			caption[0] = '1' + col + ((2 - row) * 3);

			/* Create button, using digit as command data. */
			button = wtk_button_create(
					wtk_basic_frame_as_child(calc->frame),
					&area,
					caption,
					(win_command_t)caption[0]);

			if (!button) {
				goto error_widget;
			}
			win_show(wtk_button_as_child(button));
		}
	}

	/* Create the other normal sized buttons, 'C', '/' and '*' */
	area.pos.y = BT_POS_Y(0); /* All except on same row. */

	caption[0] = 'C';
	area.pos.x = BT_POS_X(0);
	button = wtk_button_create(
			wtk_basic_frame_as_child(calc->frame),
			&area,
			caption,
			(win_command_t)caption[0]);

	if (!button) {
		goto error_widget;
	}
	win_show(wtk_button_as_child(button));

	caption[0] = '/';
	area.pos.x = BT_POS_X(1);
	button = wtk_button_create(
			wtk_basic_frame_as_child(calc->frame),
			&area,
			caption,
			(win_command_t)caption[0]);

	if (!button) {
		goto error_widget;
	}
	win_show(wtk_button_as_child(button));

	caption[0] = '*';
	area.pos.x = BT_POS_X(2);
	button = wtk_button_create(
			wtk_basic_frame_as_child(calc->frame),
			&area,
			caption,
			(win_command_t)caption[0]);

	if (!button) {
		goto error_widget;
	}
	win_show(wtk_button_as_child(button));

	/* Create the '-' and '+' buttons, double height. */
	area.pos.x = BT_POS_X(3);
	area.size.x = BT_W;
	area.size.y = BT_H * 2;

	caption[0] = '-';
	area.pos.y = BT_POS_Y(0);
	button = wtk_button_create(
			wtk_basic_frame_as_child(calc->frame),
			&area,
			caption,
			(win_command_t)caption[0]);

	if (!button) {
		goto error_widget;
	}
	win_show(wtk_button_as_child(button));

	caption[0] = '+';
	area.pos.y = BT_POS_Y(2);
	button = wtk_button_create(
			wtk_basic_frame_as_child(calc->frame),
			&area,
			caption,
			(win_command_t)caption[0]);

	if (!button) {
		goto error_widget;
	}
	win_show(wtk_button_as_child(button));

	/* Create the '0' and '=' buttons, double width. */
	area.pos.y = BT_POS_Y(4);
	area.size.x = BT_W * 2;
	area.size.y = BT_H;

	area.pos.x = BT_POS_X(0);
	caption[0] = '0';
	button = wtk_button_create(
			wtk_basic_frame_as_child(calc->frame),
			&area,
			caption,
			(win_command_t)caption[0]);

	if (!button) {
		goto error_widget;
	}
	win_show(wtk_button_as_child(button));

	area.pos.x = BT_POS_X(2);
	caption[0] = '=';
	button = wtk_button_create(
			wtk_basic_frame_as_child(calc->frame),
			&area,
			caption,
			(win_command_t)caption[0]);

	if (!button) {
		goto error_widget;
	}
	win_show(wtk_button_as_child(button));

	/* Set the background information for the GUI window */
	calc->text_frame_bg.type = GFX_BITMAP_SOLID;
	calc->text_frame_bg.data.color = GFX_COLOR(100, 100, 100);

	/* Create the value text background frame. */
	area.pos.x = BT_POS_X(0);
	area.pos.y = W_SP;
	area.size.x = T_W;
	area.size.y = T_H;
	calc->text_frame = wtk_basic_frame_create(
			wtk_basic_frame_as_child(calc->frame),
			&area,
			&calc->text_frame_bg,
			NULL,
			NULL,
			0);

	if (!calc->text_frame) {
		goto error_widget;
	}
	win_show(wtk_basic_frame_as_child(calc->text_frame));

	/* Create static text for values. */
	area.pos.x = 0;
	area.pos.y = (T_H - sysfont.height) / 2;
	calc->text = wtk_label_create(
		wtk_basic_frame_as_child(calc->text_frame),
		&area, "0", GFX_COLOR_WHITE, NULL,
		true);

	if (!calc->text) {
		goto error_widget;
	}
	win_show(wtk_label_as_child(calc->text));

	/* Show entire calculator frame as well. */
	win_show(wtk_basic_frame_as_child(calc->frame));

	return true;

	/* Error handling to clean up allocations after an error */
error_widget:
	win_destroy(wtk_basic_frame_as_child(calc->frame));
error_frame:
	membag_free(calc);
	
	return false;
}

/** @} */
