/**
 * \file
 *
 * \brief Widget ToolKit training application
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
 */

/**
 * \mainpage Widget ToolKit training
 *
 * \section introduction Introduction
 * This is the skeleton application to be used with the application note
 * <a href="http://www.microchip.com//wwwAppNotes/AppNotes.aspx?appnote=en591589">AVR1614: Widget Toolkit -
 * Getting Started</a>.
 *
 * \section files Main Files
 * The main files of interest to the user are:
 * - \ref main.c
 * - \ref app_widget.c
 * - \ref app_widget.h
 *
 * \section device_info Device Info
 * This training has been tested with the mXT143E Xplained on the following
 * boards:
 * - UC3-A3 Xplained
 * - UC3-L0 Xplained
 * - XMEGA-A1 Xplained
 * - XMEGA-B1 Xplained
 * - XMEGA-A3BU Xplained
 * - SAM4S Xplained
 *
 * Please ensure that the SPI mode switch on the mXT143E Xplained is in the
 * correct position for your evaluation board:
 * - "XMEGA USART in SPI mode" for XMEGA
 * - "Native SPI" for others
 *
 * \section description Training description
 * This application is made as a training to introduce users to some of the
 * available widgets in the \ref gfx_wtk "Widget toolkit".
 *
 * Initially this application will draw a \ref gfx_wtk_basic_frame "basic frame"
 * filling the entire screen and add a \ref gfx_wtk_slider "slider" and a
 * \ref gfx_wtk_progress_bar "progress bar" on the upper half of the screen.
 *
 * The user's task is then to add a \ref gfx_wtk_basic_frame "sub-frame" and a
 * \ref gfx_wtk_button "button". The button should increment a counter presented
 * in the sub-frame each time the button is pressed.
 *
 * \section dependencies Dependencies
 * The most relevant module dependencies for this training are:
 * - \ref gfx_group
 * - \ref win_group
 * - \ref wtk_group
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

#include "app_widget.h"

/** Address of the mXT143E on TWI bus */
#define MAXTOUCH_TWI_ADDRESS  0x4a

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
 * \brief Set up and show the root window
 */
static void setup_root_window(void)
{
	struct win_window *win_root;
	struct win_attributes attr;

	win_root = win_get_root();
	attr = *win_get_attributes(win_root);
	attr.background = NULL;

	win_set_attributes(win_root, &attr, WIN_ATTR_BACKGROUND);
	win_show(win_root);
}

/**
 * \brief Main application function
 *
 * This function executes the necessary initialization calls and displays the
 * demo widgets before entering the main work loop of the application.
 *
 * The main work loop reads out the touch events from the mXT143E Xplained and
 * enqueues the corresponding touch events in the window system, before
 * processing the window system's event queue.
 */
int main(void)
{
	static struct mxt_device device;

	board_init();
	sysclk_init();
	membag_init();
	gfx_init();
	mxt_init(&device);
	win_init();

	setup_root_window();
	app_widget_launch();

	while (true) {
		/* Process received messages from the maXTouch device */
		while (mxt_is_message_pending(&device)) {
			struct mxt_touch_event touch_event;
			struct win_pointer_event win_touch_event;

			/* Get the first touch event in queue */
			if (mxt_read_touch_event(&device,
					&touch_event) != STATUS_OK) {
				continue;
			}

			/* Translate touch event type into a WTK event type */
			if (touch_event.status & MXT_PRESS_EVENT) {
				win_touch_event.type = WIN_POINTER_PRESS;
			} else if (touch_event.status & MXT_MOVE_EVENT) {
				win_touch_event.type = WIN_POINTER_MOVE;
			} else if (touch_event.status & MXT_RELEASE_EVENT) {
				win_touch_event.type = WIN_POINTER_RELEASE;
			} else {
				continue;
			}

			/* Indicate the touch event is a non-relative movement
			 * with the virtual touch button pressed
			 */
			win_touch_event.is_relative = false;
			win_touch_event.buttons = WIN_TOUCH_BUTTON;

			/* Translate the touch X and Y position into a screen
			 * coordinate
			 */
			win_touch_event.pos.x =
					((uint32_t)(4096 - touch_event.x) * gfx_get_width()) / 4096;
			win_touch_event.pos.y =
					((uint32_t)(4096 - touch_event.y) * gfx_get_height()) / 4096;
			win_queue_pointer_event(&win_touch_event);
		}

		/* Process queued events in the windowing system */
		win_process_events();
	}
}
