/**
 * \file
 *
 * \brief mXT143E Xplained paint demo application
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
 *
 */

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is an example application for the mXT143E Xplained, designed to
 * demonstrate the use of maXTouch devices, via a simple paint application.
 *
 * \section files Main Files
 * - \ref paint_demo.c
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_ili9341.h
 * - \ref conf_mxt.h
 * - \ref conf_sysfont.h
 * - \ref conf_twim.h
 * - UC3 and SAM only: \ref conf_spi_master.h
 * - XMEGA only: \ref conf_usart_spi.h
 *
 * \section device_info Device Info
 * This example has been tested with the mXT143E Xplained on the following
 * boards:
 * - UC3-A3 Xplained
 * - UC3-L0 Xplained
 * - XMEGA-A1 Xplained
 * - XMEGA-B1 Xplained
 * - XMEGA-A3BU Xplained
 * - SAM4S Xplained
 *
 * \section exampledescription Description of the example
 * This example can track the movement and pressure of fingers on the display,
 * drawing the selected color from a pallet at the point of contact with a size
 * corresponding to the size of the touch contact. Multiple fingers can be used
 * to draw multiple lines simultaneously.
 *
 * \section dependencies Dependencies
 * Relevant module dependencies for this application are:
 * - \ref gfx_group
 * - \ref mxt_group
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for AVR. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <stdio.h>

/** Address of the mXT143E on TWI bus */
#define MAXTOUCH_TWI_ADDRESS  0x4a

/** Height of the pallet on the display */
#define PALLET_HEIGHT         22

/** Width of each color entry in the pallet on the display */
#define PALLET_COLOR_WIDTH    (gfx_get_width() / NUM_PALLET_COLORS)

/** Number of colors in the pallet (computed automatically from number of
 *  entries in the \ref pallet_colors[] array) */
#define NUM_PALLET_COLORS     (sizeof(pallet_colors) / sizeof(pallet_colors[0]))

/** Color increment/decrement amount when in multi-color mode; larger values
 *  will cause the colors to cycle faster */
#define MULTI_COLOR_INCREMENT 4

/** Color pallet for the application; add or remove colors here to update the
 *  pallet in the application */
const gfx_color_t pallet_colors[] = {
	0,           /**< First entry is for multi-color mode */
	GFX_COLOR_WHITE,
	GFX_COLOR_BLACK,
	GFX_COLOR_RED,
	GFX_COLOR_GREEN,
	GFX_COLOR_BLUE,
	GFX_COLOR_MAGENTA,
	GFX_COLOR_YELLOW,
	GFX_COLOR_CYAN,
	0,           /**< Last entry is for clear function */
};

/** Pallet index of the currently selected color by the user */
uint8_t selected_pallet_color = 0;

/**
 * \brief Set maXTouch configuration
 *
 * This function writes a set of predefined, optimal maXTouch configuration data
 * to the mXT143E Xplained.
 *
 * \param device Pointer to mxt_device struct
 */
static void mxt_init(struct mxt_device *device)
{
	enum status_code status;
	UNUSED(status);

	/* T8 configuration object data */
	uint8_t t8_object[] = {
		0x10, 0x05, 0x0a, 0x14, 0x64, 0x00, 0x05,
		0x0a, 0x00, 0x00,
	};

	/* T9 configuration object data */
	uint8_t t9_object[] = {
		0x8f, 0x00, 0x00, 0x0d, 0x0b, 0x00, 0x21,
		0x3c, 0x0f, 0x00, 0x32, 0x01, 0x01, 0x00,
		0x08, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x1c, 0x1c, 0x37, 0x37, 0x8f, 0x50,
		0xcf, 0x6e, 0x00, 0x02, 0x2f, 0x2c, 0x00
	};

	/* T48 configuration object data */
	uint8_t t48_object[] = {
		0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00
	};

	/* TWI configuration */
	twi_master_options_t twi_opt = {
		.speed = MXT_TWI_SPEED,
		.chip  = MAXTOUCH_TWI_ADDRESS,
	};

	status = twi_master_setup(TWI_INTERFACE, &twi_opt);
	Assert(status == STATUS_OK);

	/* Initialize the maXTouch device */
	status = mxt_init_device(device, TWI_INTERFACE,
			MAXTOUCH_TWI_ADDRESS, MXT143E_XPLAINED_CHG);
	Assert(status == STATUS_OK);

	/* Issue soft reset of maXTouch device by writing a non-zero value to
	 * the reset register */
	mxt_write_config_reg(device, mxt_get_object_address(device,
			MXT_GEN_COMMANDPROCESSOR_T6, 0)
			+ MXT_GEN_COMMANDPROCESSOR_RESET, 0x01);

	/* Wait for the reset of the device to complete */
	delay_ms(MXT_RESET_TIME);

	/* Write data to configuration registers in T7 configuration object */
	mxt_write_config_reg(device, mxt_get_object_address(device,
			MXT_GEN_POWERCONFIG_T7, 0) + 0, 0xff);
	mxt_write_config_reg(device, mxt_get_object_address(device,
			MXT_GEN_POWERCONFIG_T7, 0) + 1, 0xff);
	mxt_write_config_reg(device, mxt_get_object_address(device,
			MXT_GEN_POWERCONFIG_T7, 0) + 2, 0x32);

	/* Write predefined configuration data to configuration objects */
	mxt_write_config_object(device, mxt_get_object_address(device,
			MXT_GEN_ACQUISITIONCONFIG_T8, 0), &t8_object);
	mxt_write_config_object(device, mxt_get_object_address(device,
			MXT_TOUCH_MULTITOUCHSCREEN_T9, 0), &t9_object);
	mxt_write_config_object(device, mxt_get_object_address(device,
			MXT_PROCG_TOUCHSUPPRESSION_T48, 0), &t48_object);

	/* Issue recalibration command to maXTouch device by writing a non-zero
	 * value to the calibrate register */
	mxt_write_config_reg(device, mxt_get_object_address(device,
			MXT_GEN_COMMANDPROCESSOR_T6, 0)
			+ MXT_GEN_COMMANDPROCESSOR_CALIBRATE, 0x01);
}

/**
 * \brief Draws the special function pallet entry text labels
 *
 * This function draws the special function pallet entry text labels to the
 * appropriate positions on the display.
 *
 * \param clearing_display   True if the display is currently being cleared
 */
static void draw_pallet_labels(const bool clearing_display)
{
	/* Draw multi-color mode text label to the appropriate pallet entry */
	gfx_draw_string_aligned("MUL",
			PALLET_COLOR_WIDTH / 2,
			gfx_get_height() - (PALLET_HEIGHT / 2), &sysfont,
			GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE,
			TEXT_POS_CENTER, TEXT_ALIGN_LEFT);

	/* Draw display clear text label to the appropriate pallet entry */
	gfx_draw_string_aligned("CLR",
			(PALLET_COLOR_WIDTH * NUM_PALLET_COLORS) - (PALLET_COLOR_WIDTH / 2),
			gfx_get_height() - (PALLET_HEIGHT / 2), &sysfont,
			GFX_COLOR_TRANSPARENT,
			clearing_display ? GFX_COLOR_RED : GFX_COLOR_WHITE,
			TEXT_POS_CENTER, TEXT_ALIGN_LEFT);
}

/**
 * \brief Updates the color pallet to the display
 *
 * This function should be called whenever a new color is selected
 * on the pallet. It will then move the selection box to the newly
 * chosen color.
 */
static void update_pallet_selection(void)
{
	/* Keep track of the last selected color */
	static uint8_t old_selected_color = 0;

	/* Delete old selection box */
	for (uint8_t i = 0; i < 3; i++) {
		gfx_draw_rect(
				(PALLET_COLOR_WIDTH * old_selected_color) + i,
				(gfx_get_height() - PALLET_HEIGHT) + i,
				PALLET_COLOR_WIDTH - (i * 2),
				PALLET_HEIGHT - (i * 2),
				pallet_colors[old_selected_color]);
	}

	/* Draw new selection box */
	for (uint8_t i = 0; i < 3; i++) {
		gfx_draw_rect(
				(PALLET_COLOR_WIDTH * selected_pallet_color) + i,
				(gfx_get_height() - PALLET_HEIGHT) + i,
				PALLET_COLOR_WIDTH - (i * 2),
				PALLET_HEIGHT - (i * 2),
				GFX_COLOR_GRAY);
	}

	old_selected_color = selected_pallet_color;
}

/**
 * \brief Draws the color pallet to the display
 *
 * This function draws the paint pallet to the display, including the special
 * function entries (such as display clear) and the selection box.
 */
static void draw_paint_pallet(void)
{
	/* Draw each color in the pallet to the display at the correct
	 * location */
	for (uint8_t i = 0; i < NUM_PALLET_COLORS; i++) {
		gfx_draw_filled_rect(
				PALLET_COLOR_WIDTH * i,
				gfx_get_height() - PALLET_HEIGHT,
				PALLET_COLOR_WIDTH,
				PALLET_HEIGHT, pallet_colors[i]);
	}

	/* Draw a dark gray line to separate the drawing area from the pallet */
	gfx_draw_horizontal_line(0,
			(gfx_get_height() - PALLET_HEIGHT - 1),
			gfx_get_width(), GFX_COLOR_GRAY);

	/* Draw special function labels */
	draw_pallet_labels(false);

	/* Draw selection box */
	update_pallet_selection();
}

/**
 * \brief Compute the next rainbow color for multi-color drawing mode
 *
 * This function handles the color mixing algorithm needed to produce a sequence
 * of colors in the RGB spectrum. Each time it is called, the next color in the
 * sequence is returned.
 *
 * \return The next color in the rainbow sequence as a gfx_color_t.
 */
static gfx_color_t get_next_rainbow_color(void)
{
	static uint8_t multi_color_rgb[3] = {255, 0, 0};
	static uint8_t multi_color_index  = 0;
	static bool multi_color_decrement = false;

	/* Check if we are currently incrementing or decrementing the
	 * R/G/B value */
	if (multi_color_decrement) {
		/* Make sure we wrap the mixing color to the correct minimum
		 * value as we decrement it */
		if (multi_color_rgb[multi_color_index] > MULTI_COLOR_INCREMENT) {
			multi_color_rgb[multi_color_index] -= MULTI_COLOR_INCREMENT;
		}
		else {
			multi_color_rgb[multi_color_index] = 0;
		}
	}
	else {
		/* Make sure we wrap the mixing color to the correct maximum
		 * value as we increment it */
		if (multi_color_rgb[multi_color_index] <
				(255 - MULTI_COLOR_INCREMENT)) {
			multi_color_rgb[multi_color_index] += MULTI_COLOR_INCREMENT;
		}
		else {
			multi_color_rgb[multi_color_index] = 255;
		}
	}

	/* Check if we have reached the current mix color limit */
	if ((multi_color_rgb[multi_color_index] == 0) ||
			(multi_color_rgb[multi_color_index] == 255)) {
		/* Select the next R/G/B color to mix and invert the
		 * mixing direction */
		multi_color_index = (multi_color_index + 1) % 3;
		multi_color_decrement = !multi_color_decrement;
	}

	/* Create the new rainbow drawing color from the current
	 * mixed RGB values */
	return GFX_COLOR(multi_color_rgb[0], multi_color_rgb[1],
			multi_color_rgb[2]);
}

/**
 * \brief Handle maXTouch messages
 *
 * This function handles the maXTouch messages, triggering the drawing of
 * squares around new or moved touches, and removing the squares around
 * released touches.
 *
 * \param device Pointer to mxt_device struct
 */
static void mxt_handler(struct mxt_device *device)
{
	struct mxt_touch_event touch_event;
	gfx_coord_t screen_touch_x, screen_touch_y, screen_touch_size;

	do {
		/* Get the first touch event in queue */
		if (mxt_read_touch_event(device, &touch_event) != STATUS_OK) {
			continue;
		}

		/* Discard non press, movement or release events */
		if (!(touch_event.status &
				(MXT_PRESS_EVENT | MXT_MOVE_EVENT | MXT_RELEASE_EVENT))) {
			continue;
		}

		/* Rescale from 4k touch X-coordinate to the display width */
		screen_touch_x = ((uint32_t)(4096 - touch_event.x) * gfx_get_width()) / 4096;

		/* Rescale from 4k touch Y-coordinate to the display height */
		screen_touch_y = ((uint32_t)(4096 - touch_event.y) * gfx_get_height()) / 4096;

		/* Scale the touch size to a value suitable for the target display */
		screen_touch_size = touch_event.size;

		/* Check if the touch is within the drawing area */
		if (screen_touch_y < (gfx_get_height() - PALLET_HEIGHT)) {
			/* Obtain the color to draw from the pallet colors */
			gfx_color_t draw_color = pallet_colors[selected_pallet_color];

			/* Color pallet index 0 selects multi-color mode */
			if (selected_pallet_color == 0) {
				draw_color = get_next_rainbow_color();
			}

			/* Set clipping area */
			gfx_set_clipping(0, 0, gfx_get_width(),
					(gfx_get_height() - PALLET_HEIGHT - 2));

			/* Draw touch point on the screen in the selected color */
			gfx_draw_filled_circle(screen_touch_x, screen_touch_y,
					screen_touch_size, draw_color, GFX_WHOLE);

			/* Reset clipping area */
			gfx_set_clipping(0, 0, gfx_get_width(), gfx_get_height());

		} else if (touch_event.status & MXT_PRESS_EVENT) {
			/* Calculate the pressed pallet entry */
			uint8_t pallete_index = (screen_touch_x / PALLET_COLOR_WIDTH);

			/* The last entry in the pallet clears the screen */
			if (pallete_index == (NUM_PALLET_COLORS - 1)) {
				/* Indicate display is being cleared */
				draw_pallet_labels(true);

				/* Clear the display */
				gfx_draw_filled_rect(0, 0, gfx_get_width(),
						(gfx_get_height() - PALLET_HEIGHT - 1),
						GFX_COLOR_BLACK);

				/* Indicate display has been cleared */
				draw_pallet_labels(false);
			} else {
				/* Change color selection based on the color chosen */
				selected_pallet_color = pallete_index;

				/* Draw new selection box around chosen color */
				update_pallet_selection();
			}
		}

	} while (mxt_is_message_pending(device));
}

/**
 * \brief Main application loop
 *
 * This is the main application function, which runs all the initialization
 * code, clears the display and enters a loop in which it continuously polls
 * for new messages from the maXTouch device. If one or more messages are
 *  pending, the maXTouch message handler is invoked.
 */
int main(void)
{
	/* maXTouch data structure */
	static struct mxt_device device;

	/* Basic init routines */
	board_init();
	sysclk_init();
	gfx_init();
	mxt_init(&device);

	/* Draw the paint pallet to the display */
	draw_paint_pallet();

	/* Draw instructions to the display */
	gfx_draw_string_aligned(
			"Select a color from the pallet below, and\n"
			"use your finger(s) to draw onto the display.\n\n"
			"Multiple simultaneous fingers are supported,\n"
			"and the drawing size varies according to the\n"
			"pressure of the touch.\n\n"
			"Select MUL to draw using multiple colors.\n\n"
			"Select CLR to clear the display.",
			gfx_get_width() / 2,
			(gfx_get_height() - PALLET_HEIGHT) / 2,
			&sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE,
			TEXT_POS_CENTER, TEXT_ALIGN_LEFT);

	while (true) {
		/* Check for any pending messages and run message handler if any
		 * message is found in the queue */
		if (mxt_is_message_pending(&device)) {
			mxt_handler(&device);
		}
	}
}
