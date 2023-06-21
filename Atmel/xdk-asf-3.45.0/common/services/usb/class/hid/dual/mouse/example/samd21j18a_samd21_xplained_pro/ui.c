/**
 * \file
 *
 * \brief User Interface
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
#include "ui.h"

#define  MOUSE_MOVE_RANGE  3
#define  MOUSE_MOVE_COUNT  50

#define  MOVE_UP     0
#define  MOVE_RIGHT  1
#define  MOVE_DOWN   2
#define  MOVE_LEFT   3

#define LED_On(LED_0_PIN)      port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE)
#define LED_Off(LED_0_PIN)     port_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE)
#define LED_Toggle(LED_0_PIN)  port_pin_toggle_output_level(LED_0_PIN)

/* Current USB mode */
static bool ui_b_host_mode = false;

/**
 * \name Internal routines to manage asynchronous interrupt pin change
 * This interrupt is connected to a switch and allows to wakeup CPU in low sleep
 * mode.
 * In USB device mode, this wakeup the USB host via a upstream resume.
 * In USB host mode, this wakeup the USB devices connected via a downstream
 * resume.
 * @{
 */
static void ui_enable_asynchronous_interrupt(void);
static void ui_disable_asynchronous_interrupt(void);

/**
 * \brief Interrupt handler for interrupt pin change
 */
static void UI_WAKEUP_HANDLER(void)
{
	if (ui_b_host_mode) {
		if (uhc_is_suspend()) {
			ui_disable_asynchronous_interrupt();

			/* Wakeup the devices connected */
			uhc_resume();
		}
	} else {
		/* In device mode, wakeup the USB host. */
		udc_remotewakeup();
	}
}

/**
 * \brief Initializes and enables interrupt pin change
 */
static void ui_enable_asynchronous_interrupt(void)
{
	/* Initialize EIC for button wakeup */
	struct extint_chan_conf eint_chan_conf;
	extint_chan_get_config_defaults(&eint_chan_conf);

	eint_chan_conf.gpio_pin            = BUTTON_0_EIC_PIN;
	eint_chan_conf.gpio_pin_mux        = BUTTON_0_EIC_MUX;
	eint_chan_conf.detection_criteria  = EXTINT_DETECT_FALLING;
	eint_chan_conf.filter_input_signal = true;
	extint_chan_set_config(BUTTON_0_EIC_LINE, &eint_chan_conf);
	extint_register_callback(UI_WAKEUP_HANDLER,
			BUTTON_0_EIC_LINE,
			EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_clear_detected(BUTTON_0_EIC_LINE);
	extint_chan_enable_callback(BUTTON_0_EIC_LINE,
			EXTINT_CALLBACK_TYPE_DETECT);
}

/**
 * \brief Disables interrupt pin change
 */
static void ui_disable_asynchronous_interrupt(void)
{
	extint_chan_disable_callback(BUTTON_0_EIC_LINE,
			EXTINT_CALLBACK_TYPE_DETECT);
}

/*! @} */

/**
 * \name Main user interface functions
 * @{
 */
void ui_init(void)
{
	/* Initialize LEDs */
	LED_Off(LED_0_PIN);
}

void ui_usb_mode_change(bool b_host_mode)
{
	ui_b_host_mode = b_host_mode;
	if (b_host_mode) {
		LED_On(LED_0_PIN);
	} else {
		LED_Off(LED_0_PIN);
	}
}

/*! @} */

/**
 * \name Host mode user interface functions
 * @{
 */

/*! Status of device enumeration */
static uhc_enum_status_t ui_enum_status = UHC_ENUM_DISCONNECT;
/*! Blink frequency depending on device speed */
static uint16_t ui_device_speed_blink;
/*! Manages device mouse button down */
static uint8_t ui_nb_down = 0;
/*! Manages device mouse move */
static bool ui_move = false;

void ui_host_vbus_change(bool b_vbus_present)
{
	UNUSED(b_vbus_present);
}

void ui_host_vbus_error(void)
{
	/* Not used for SAMD21 */
}

void ui_host_connection_event(uhc_device_t *dev, bool b_present)
{
	UNUSED(dev);
	if (!b_present) {
		LED_On(LED_0_PIN);
		ui_enum_status = UHC_ENUM_DISCONNECT;
	}
}

void ui_host_enum_event(uhc_device_t *dev, uhc_enum_status_t status)
{
	ui_enum_status = status;
	if (ui_enum_status == UHC_ENUM_SUCCESS) {
		switch (dev->speed) {
		case UHD_SPEED_HIGH:
			ui_device_speed_blink = 250;
			break;

		case UHD_SPEED_FULL:
			ui_device_speed_blink = 500;
			break;

		case UHD_SPEED_LOW:
		default:
			ui_device_speed_blink = 1000;
			break;
		}
	}
}

void ui_host_wakeup_event(void)
{
	ui_disable_asynchronous_interrupt();
}

void ui_host_sof_event(void)
{
	bool b_btn_state;
	static bool btn_suspend_and_remotewakeup = false;
	static uint16_t counter_sof = 0;

	if (ui_enum_status == UHC_ENUM_SUCCESS) {
		/* Display device enumerated and in active mode */
		if (++counter_sof > ui_device_speed_blink) {
			counter_sof = 0;
			LED_Toggle(LED_0_PIN);
		}

		/* Scan button to enter in suspend mode and remote wakeup */
		b_btn_state = !port_pin_get_input_level(BUTTON_0_PIN);
		if (b_btn_state != btn_suspend_and_remotewakeup) {
			/* Button have changed */
			btn_suspend_and_remotewakeup = b_btn_state;
			if (b_btn_state) {
				/* Button has been pressed */
				ui_enable_asynchronous_interrupt();
				LED_Off(LED_0_PIN);
				uhc_suspend(true);
				return;
			}
		}

		/* Power on a LED when the mouse button down */
		if (ui_nb_down) {
			LED_On(LED_0_PIN);
		}
		/* Power on a LED when the mouse moves */
		if (ui_move) {
			ui_move = false;
			LED_On(LED_0_PIN);
		}
	}
}

static void ui_host_hid_mouse_btn(bool b_state)
{
	if (b_state) {
		ui_nb_down++;
	} else {
		ui_nb_down--;
	}
}

void ui_host_hid_mouse_btn_left(bool b_state)
{
	ui_host_hid_mouse_btn(b_state);
}

void ui_host_hid_mouse_btn_right(bool b_state)
{
	ui_host_hid_mouse_btn(b_state);
}

void ui_host_hid_mouse_btn_middle(bool b_state)
{
	ui_host_hid_mouse_btn(b_state);
}

void ui_host_hid_mouse_move(int8_t x, int8_t y, int8_t scroll)
{
	UNUSED(x);
	UNUSED(y);
	UNUSED(scroll);
	ui_move = true;
}

/*! @} */

/**
 * \name Device mode user interface functions
 * @{
 */
#define  MOUSE_MOVE_RANGE  3
static bool ui_device_b_mouse_enable = false;

void ui_device_suspend_action(void)
{
	ui_init();
}

void ui_device_resume_action(void)
{
}

void ui_device_remotewakeup_enable(void)
{
	ui_enable_asynchronous_interrupt();
}

void ui_device_remotewakeup_disable(void)
{
	ui_disable_asynchronous_interrupt();
}

bool ui_device_mouse_enable(void)
{
	ui_device_b_mouse_enable = true;
	return true;
}

void ui_device_mouse_disable(void)
{
	ui_device_b_mouse_enable = false;
}

void ui_device_sof_action(void)
{
	uint16_t framenumber;
	static uint8_t cpt_sof = 0;
	static int32_t move_count = MOUSE_MOVE_COUNT;
	static uint8_t move_dir = MOVE_UP;

	if (!ui_device_b_mouse_enable) {
		return;
	}

	framenumber = udd_get_frame_number();
	if ((framenumber % 1000) == 0) {
		LED_On(LED_0_PIN);
	}

	if ((framenumber % 1000) == 500) {
		LED_Off(LED_0_PIN);
	}

	/* Scan process running each 2ms */
	cpt_sof++;
	if (2 > cpt_sof) {
		return;
	}

	cpt_sof = 0;

	/* Uses buttons to move mouse */
	if (!port_pin_get_input_level(BUTTON_0_PIN)) {
		move_count--;
		switch (move_dir) {
		case MOVE_UP:
			udi_hid_mouse_moveY(-MOUSE_MOVE_RANGE);
			if (move_count < 0) {
				move_dir = MOVE_RIGHT;
				move_count = MOUSE_MOVE_COUNT;
			}

			break;

		case MOVE_RIGHT:
			udi_hid_mouse_moveX(+MOUSE_MOVE_RANGE);
			if (move_count < 0) {
				move_dir = MOVE_DOWN;
				move_count = MOUSE_MOVE_COUNT;
			}

			break;

		case MOVE_DOWN:
			udi_hid_mouse_moveY(+MOUSE_MOVE_RANGE);
			if (move_count < 0) {
				move_dir = MOVE_LEFT;
				move_count = MOUSE_MOVE_COUNT;
			}

			break;

		case MOVE_LEFT:
			udi_hid_mouse_moveX(-MOUSE_MOVE_RANGE);
			if (move_count < 0) {
				move_dir = MOVE_UP;
				move_count = MOUSE_MOVE_COUNT;
			}

			break;
		}
	}
}

/*! @} */

/**
 * \defgroup UI User Interface
 *
 * Human interface on SAM D21 Xplained Pro:
 * - host mode:
 *   - Led 0 is on when it's host and there is no device connected
 *   - Led 0 blinks when a HID mouse is enumerated and USB in idle mode
 *     - The blink is slow (1s) with low speed device
 *     - The blink is normal (0.5s) with full speed device
 *     - The blink is fast (0.25s) with high speed device
 *   - Led 0 is on when a HID mouse button is pressed
 *   - Button SW0 allows to enter the device in suspend mode with remote wakeup
 *     feature authorized
 *   - Only SW0 button can be used to wakeup USB device in suspend mode
 * - device mode:
 *   - Led 0 blinks when the device is enumerated and USB in idle mode
 *   - SW0 is used to move mouse around
 *   - Only a low level on SW0 will generate a wakeup to USB Host in remote
 *     wakeup mode.
 */
