/**
 * \file
 *
 * \brief Touch screen interface functions for the mxt143e Xplained module
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include "touch_interface.h"

/** Address of the mXT143E on TWI bus */
#define MAXTOUCH_TWI_ADDRESS  0x4a

/** Software maXTouch device instance */
static struct mxt_device mxt_dev_inst;

/**
 * \brief Convert touch events from the touchscreen into window pointer events
 *
 * Reads touch events in from the touchscreen and converts them into a
 * Window Manager pointer event, for enqueuing into the window event queue.
 *
 * \return Boolean \c true if a touch event was read, false if no touch event
 *         or a corrupt touch event was received
 */
bool touch_interface_read(struct win_pointer_event *win_touch_event)
{
	struct mxt_touch_event touch_event;

	/* Abort if no touch event is pending */
	if (!(mxt_is_message_pending(&mxt_dev_inst))) {
		return false;
	}

	/* Get the first touch event in queue */
	if (mxt_read_touch_event(&mxt_dev_inst, &touch_event) != STATUS_OK) {
		return false;
	}

	/* Translate touch event type into a WTK event type */
	if (touch_event.status & MXT_PRESS_EVENT) {
		win_touch_event->type = WIN_POINTER_PRESS;
	} else if (touch_event.status & MXT_MOVE_EVENT) {
		win_touch_event->type = WIN_POINTER_MOVE;
	} else if (touch_event.status & MXT_RELEASE_EVENT) {
		win_touch_event->type = WIN_POINTER_RELEASE;
	} else {
		return false;
	}

	/* Indicate the touch event is a non-relative movement with the virtual
	 * touch button pressed
	 */
	win_touch_event->is_relative = false;
	win_touch_event->buttons = WIN_TOUCH_BUTTON;

	/* Translate the touch X and Y position into a screen coordinate */
	win_touch_event->pos.x =
			((uint32_t)(4096 - touch_event.x) * gfx_get_width()) / 4096;
	win_touch_event->pos.y =
			((uint32_t)(4096 - touch_event.y) * gfx_get_height()) / 4096;

	return true;
}

/**
 * \brief Initializes the touchscreen, ready to detect user input
 *
 * Performs and initialization and calibration of the touchscreen, so that it
 * is ready for use.
 */
void touch_interface_init(void)
{
	enum status_code status;

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
	status = mxt_init_device(&mxt_dev_inst, TWI_INTERFACE,
			MAXTOUCH_TWI_ADDRESS, MXT143E_XPLAINED_CHG);
	Assert(status == STATUS_OK);

	/* Issue soft reset of maXTouch device by writing a non-zero value to
	 * the reset register */
	mxt_write_config_reg(&mxt_dev_inst, mxt_get_object_address(&mxt_dev_inst,
			MXT_GEN_COMMANDPROCESSOR_T6, 0)
			+ MXT_GEN_COMMANDPROCESSOR_RESET, 0x01);

	/* Wait for the reset of the device to complete */
	delay_ms(MXT_RESET_TIME);

	/* Write data to configuration registers in T7 configuration object */
	mxt_write_config_reg(&mxt_dev_inst, mxt_get_object_address(&mxt_dev_inst,
			MXT_GEN_POWERCONFIG_T7, 0) + 0, 0xff);
	mxt_write_config_reg(&mxt_dev_inst, mxt_get_object_address(&mxt_dev_inst,
			MXT_GEN_POWERCONFIG_T7, 0) + 1, 0xff);
	mxt_write_config_reg(&mxt_dev_inst, mxt_get_object_address(&mxt_dev_inst,
			MXT_GEN_POWERCONFIG_T7, 0) + 2, 0x32);

	/* Write predefined configuration data to configuration objects */
	mxt_write_config_object(&mxt_dev_inst, mxt_get_object_address(&mxt_dev_inst,
			MXT_GEN_ACQUISITIONCONFIG_T8, 0), &t8_object);
	mxt_write_config_object(&mxt_dev_inst, mxt_get_object_address(&mxt_dev_inst,
			MXT_TOUCH_MULTITOUCHSCREEN_T9, 0), &t9_object);
	mxt_write_config_object(&mxt_dev_inst, mxt_get_object_address(&mxt_dev_inst,
			MXT_PROCG_TOUCHSUPPRESSION_T48, 0), &t48_object);

	/* Issue recalibration command to maXTouch device by writing a non-zero
	 * value to the calibrate register */
	mxt_write_config_reg(&mxt_dev_inst, mxt_get_object_address(&mxt_dev_inst,
			MXT_GEN_COMMANDPROCESSOR_T6, 0)
			+ MXT_GEN_COMMANDPROCESSOR_CALIBRATE, 0x01);
}

