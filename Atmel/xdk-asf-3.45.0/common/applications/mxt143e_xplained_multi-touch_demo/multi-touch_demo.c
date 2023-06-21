/**
 * \file
 *
 * \brief mXT143E Xplained multi-touch demo application
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
 * demonstrate multi-touch sensing with maXTouch devices.
 *
 * \section files Main Files
 * - \ref multi-touch_demo.c
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
 * This example can track up to 8 touches and will visualize the tracking for
 * the user by drawing a uniquely colored square around each finger.
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
#define MAXTOUCH_TWI_ADDRESS 0x4a
/** Background color of display */
#define DISPLAY_COLOR        GFX_COLOR_BLACK
/** Minimum size of touch squares to draw */
#define MIN_SQUARE_SIZE      70
/** Maximum number of touches to track */
#define MAX_TOUCHES          8
/** Define to enable resizing of the touch square based on the touch size */
#define ENABLE_TOUCH_SIZE_DISPLAY
/** Define to enable display of touch coordinates with each square */
#define ENABLE_COORDINATE_DISPLAY

/** Struct for touch visualization data */
struct finger {
	bool enable;   /**< Enable drawing */
	gfx_coord_t x; /**< X-coordinate on display */
	gfx_coord_t y; /**< Y-coordinate on display */
	uint8_t size;  /**< Size of the detected touch */
};

/**
 * \brief Draw square around a finger
 *
 * This function draws an unfilled square around the specified finger.
 *
 * \param draw_finger Pointer to finger struct
 * \param color Color to draw with
 */
static void draw_finger_square(const struct finger *draw_finger,
		const gfx_color_t color)
{
	gfx_coord_t upper_x, upper_y;
	uint8_t square_size = MIN_SQUARE_SIZE;

#ifdef ENABLE_TOUCH_SIZE_DISPLAY
	/* Increase the size of the touch square based on the touch size */
	square_size += draw_finger->size;
#endif

	/* Calculate upper-left X/Y coordinates for the touch bounding box */
	upper_x = draw_finger->x - (square_size / 2);
	upper_y = draw_finger->y - (square_size / 2);

#ifdef ENABLE_COORDINATE_DISPLAY
	char str_buffer[10];
	gfx_coord_t str_width, str_height;

	/* Print the formatted touch coordinates into the temporary buffer */
	sprintf(str_buffer, "%03d, %03d", draw_finger->x, draw_finger->y);

	/* Calculate the bounding box of the coordinate text on the display */
	gfx_get_string_bounding_box(str_buffer, &sysfont, &str_width, &str_height);

	/* Write touch coordinates to the display above the finger touch box */
	gfx_draw_string(str_buffer, upper_x + ((square_size - str_width) / 2),
			upper_y - (str_height + 1),
			&sysfont, GFX_COLOR_TRANSPARENT, color);
#endif

	/* Draw a box around the touch point */
	gfx_generic_draw_rect(upper_x, upper_y,
			square_size, square_size, color);
}

/**
 * \brief Compute display coordinates for touch
 *
 * This function computes the display coordinates for a given touch event,
 * and stores it in the specified X- and Y-coordinate containers.
 *
 * \param touch_event Pointer to touch event
 * \param finger_data Pointer to finger struct
 */
static void get_finger_display_coordinates(const struct mxt_touch_event *touch_event,
		struct finger *finger_data)
{
	/* Display X-coordinate: rescale from 4k touch Y-coordinate to the
	 * display's width
	 */
	finger_data->x = ((uint32_t)(4096 - touch_event->x) * gfx_get_width()) / 4096;

	/* Display Y-coordinate: rescale from 4k touch X-coordinate to the
	 * display's height, and flip to get the right direction
	 */
	finger_data->y = ((uint32_t)(4096 - touch_event->y) * gfx_get_height()) / 4096;

	/* Save the scaled size of the touch */
	finger_data->size = (touch_event->size * 4);
}

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
	static struct finger fingers[MAX_TOUCHES];
	static const gfx_color_t finger_colors[MAX_TOUCHES] = {
		GFX_COLOR_RED,
		GFX_COLOR_GREEN,
		GFX_COLOR_BLUE,
		GFX_COLOR_CYAN,
		GFX_COLOR_YELLOW,
		GFX_COLOR_MAGENTA,
		GFX_COLOR_WHITE,
		GFX_COLOR_GRAY,
	};
	struct mxt_touch_event touch_event;
	struct finger *curr_finger;
	uint8_t finger_index;

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

		/* Use the touch ID as finger index */
		finger_index = touch_event.id;

		/* Skip if touch ID is out of bounds */
		if (!(finger_index < MAX_TOUCHES)) {
			continue;
		}

		/* Get address of current finger info struct */
		curr_finger = &fingers[finger_index];

		/* If finger already registered (and thus drawn), clear it on the display */
		if (curr_finger->enable) {
			draw_finger_square(curr_finger, DISPLAY_COLOR);
		}

		/* Update finger info - finger is enabled unless it was released */
		curr_finger->enable = !(touch_event.status & MXT_RELEASE_EVENT);

		/* If the finger is now enabled, we need to update its position and redraw */
		if (curr_finger->enable) {
			/* Compute new display coordinates from touch coordinates */
			get_finger_display_coordinates(&touch_event, curr_finger);

			/* Draw updated representation on the display */
			draw_finger_square(curr_finger,
					finger_colors[finger_index]);
		}
	} while (mxt_is_message_pending(device));
}

/**
 * \brief Main application loop
 *
 * This is the main application function, which runs all the initialization
 * code, clears the display and enters a loop in which it continuously polls for
 * new messages from the maXTouch device. If one or more messages are pending,
 * the maXTouch message handler is invoked.
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

	/* Clear the display */
	gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(),
			DISPLAY_COLOR);

	while (true) {
		/* Check for any pending messages and run message handler if any
		 * message is found in the queue */
		if (mxt_is_message_pending(&device)) {
			mxt_handler(&device);
		}
	}
}
