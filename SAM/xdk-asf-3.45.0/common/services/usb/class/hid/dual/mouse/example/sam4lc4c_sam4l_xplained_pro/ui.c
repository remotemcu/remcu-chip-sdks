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

/* Wakeup pin is SW0 (PC24, EIC1) */
#define UI_WAKEUP_IRQN         EIC_1_IRQn
#define UI_WAKEUP_IRQ_LEVEL    5
#define UI_WAKEUP_EIC_LINE     SW0_EIC_LINE
#define UI_WAKEUP_HANDLER      button_handler
#define UI_WAKEUP_BPM_SRC      BPM_BKUPWEN_EIC

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
	sysclk_enable_peripheral_clock(EIC);
	if (eic_line_interrupt_is_pending(EIC, UI_WAKEUP_EIC_LINE)) {
		eic_line_clear_interrupt(EIC, UI_WAKEUP_EIC_LINE);
		if (ui_b_host_mode) {
			if (!uhc_is_suspend()) {
				/* USB is not in suspend mode
				 *  Let's interrupt enable. */
				return;
			}

			ui_disable_asynchronous_interrupt();

			/* Wakeup the devices connected */
			uhc_resume();
		} else {
			/* In device mode, wakeup the USB host. */
			udc_remotewakeup();
		}
	}

	sysclk_disable_peripheral_clock(EIC);
}

/**
 * \brief Initializes and enables interrupt pin change
 */
static void ui_enable_asynchronous_interrupt(void)
{
	/* Initialize EIC for button wakeup */
	sysclk_enable_peripheral_clock(EIC);
	struct eic_line_config eic_opt = {
		.eic_mode = EIC_MODE_EDGE_TRIGGERED,
		.eic_edge = EIC_EDGE_FALLING_EDGE,
		.eic_level = EIC_LEVEL_LOW_LEVEL,
		.eic_filter = EIC_FILTER_DISABLED,
		.eic_async = EIC_ASYNCH_MODE
	};
	eic_enable(EIC);
	eic_line_set_config(EIC, UI_WAKEUP_EIC_LINE, &eic_opt);
	eic_line_set_callback(EIC, UI_WAKEUP_EIC_LINE, UI_WAKEUP_HANDLER,
			UI_WAKEUP_IRQN, UI_WAKEUP_IRQ_LEVEL);
	eic_line_enable(EIC, UI_WAKEUP_EIC_LINE);
	eic_line_enable_interrupt(EIC, UI_WAKEUP_EIC_LINE);
}

/**
 * \brief Disables interrupt pin change
 */
static void ui_disable_asynchronous_interrupt(void)
{
	eic_line_disable_interrupt(EIC, UI_WAKEUP_EIC_LINE);
	sysclk_disable_peripheral_clock(EIC);
}

/*! @} */

/**
 * \name Main user interface functions
 * @{
 */
void ui_init(void)
{
	/* Initialize LEDs */
	LED_Off(LED0);
}

void ui_usb_mode_change(bool b_host_mode)
{
	ui_b_host_mode = b_host_mode;
	if (b_host_mode) {
		LED_On(LED0);
	} else {
		LED_Off(LED0);
	}
}

/*! @} */

/**
 * \name Host mode user interface functions
 * @{
 */

/* ! Status of device enumeration */
static uhc_enum_status_t ui_enum_status = UHC_ENUM_DISCONNECT;
/* ! Blink frequency depending on device speed */
static uint16_t ui_device_speed_blink;
/* ! Manages device mouse button down */
static uint8_t ui_nb_down = 0;

void ui_host_vbus_change(bool b_vbus_present)
{
	UNUSED(b_vbus_present);
}

void ui_host_vbus_error(void)
{
	/* Not used for 4L */
}

void ui_host_connection_event(uhc_device_t *dev, bool b_present)
{
	UNUSED(dev);
	if (!b_present) {
		LED_On(LED0);
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
			LED_Toggle(LED0);
		}

		/* Scan button to enter in suspend mode and remote wakeup */
		b_btn_state = !ioport_get_pin_level(GPIO_PUSH_BUTTON_0);
		if (b_btn_state != btn_suspend_and_remotewakeup) {
			/* Button have changed */
			btn_suspend_and_remotewakeup = b_btn_state;
			if (b_btn_state) {
				/* Button has been pressed */
				ui_enable_asynchronous_interrupt();
				LED_Off(LED0);
				uhc_suspend(true);
				return;
			}
		}

		/* Power on a LED when the mouse button down */
		if (ui_nb_down) {
			LED_On(LED0);
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
		LED_On(LED0);
	}

	if ((framenumber % 1000) == 500) {
		LED_Off(LED0);
	}

	/* Scan process running each 2ms */
	cpt_sof++;
	if (2 > cpt_sof) {
		return;
	}

	cpt_sof = 0;

	/* Uses buttons to move mouse */
	if (!ioport_get_pin_level(GPIO_PUSH_BUTTON_0)) {
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
 * Human interface on SAM4L Xplained Pro:
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
