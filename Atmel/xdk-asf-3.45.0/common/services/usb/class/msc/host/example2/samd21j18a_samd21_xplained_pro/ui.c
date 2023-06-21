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

#include "conf_usb_host.h"
#include <asf.h>

/**
 * \name Internal routines to manage asynchronous interrupt pin change
 * This interrupt is connected to a switch and allows to wakeup CPU in low sleep
 * mode.
 * This wakeup the USB devices connected via a downstream resume.
 * @{
 */
static void ui_enable_asynchronous_interrupt(void);
static void ui_disable_asynchronous_interrupt(void);

/**
 * \brief Interrupt handler for interrupt pin change
 */
static void UI_WAKEUP_HANDLER(void)
{
	if (uhc_is_suspend()) {
		ui_disable_asynchronous_interrupt();

		/* Wakeup host and device */
		uhc_resume();
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
/*! Status of the MSC test */
static bool ui_test_done;
/*! Result of the MSC test */
static bool ui_test_result;

void ui_usb_vbus_change(bool b_vbus_present)
{
	UNUSED(b_vbus_present);
}

void ui_usb_vbus_error(void)
{
}

void ui_usb_connection_event(uhc_device_t *dev, bool b_present)
{
	UNUSED(dev);
	if (!b_present) {
		LED_On(LED_0_PIN);
		ui_enum_status = UHC_ENUM_DISCONNECT;
	}
}

void ui_usb_enum_event(uhc_device_t *dev, uhc_enum_status_t status)
{
	UNUSED(dev);
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
	ui_test_done = false;
}

void ui_usb_wakeup_event(void)
{
	ui_disable_asynchronous_interrupt();
}

void ui_usb_sof_event(void)
{
	bool b_btn_state;
	static bool btn_suspend = false;
	static uint16_t counter_sof = 0;

	if (ui_enum_status == UHC_ENUM_SUCCESS) {
		/* Display device enumerated and in active mode */
		if (++counter_sof > ui_device_speed_blink) {
			counter_sof = 0;
			LED_Toggle(LED_0_PIN);
			if (ui_test_done) {
				if (ui_test_result) {
					/* Test successful */
					LED_On(LED_0_PIN);
				} else {
					/* Test fail */
					LED_Off(LED_0_PIN);
				}
			}
		}
		/* Scan button to enter in suspend mode and remote wakeup */
		b_btn_state = !port_pin_get_input_level(BUTTON_0_PIN);
		if (b_btn_state != btn_suspend) {
			/* Button have changed */
			btn_suspend = b_btn_state;
			if (b_btn_state) {
				/* Button has been pressed */
				LED_Off(LED_0_PIN);
				ui_enable_asynchronous_interrupt();
				uhc_suspend(true);
				return;
			}
		}
	}
}

void ui_test_flag_reset(void)
{
	ui_test_done = false;
}

void ui_test_finish(bool b_success)
{
	ui_test_done = true;
	ui_test_result = b_success;
}

/*! @} */

/*! \name Callback to show the MSC read and write access
 *  @{ */
void ui_start_read(void)
{
	LED_On(LED_0_PIN);
}

void ui_stop_read(void)
{
	LED_Off(LED_0_PIN);
}

void ui_start_write(void)
{
	LED_On(LED_0_PIN);
}

void ui_stop_write(void)
{
	LED_Off(LED_0_PIN);
}

/*! @} */

/**
 * \defgroup UI User Interface
 *
 * Human interface on SAM D21 Xplained Pro:
 * - Led 0 is on when it's host and there is no device connected
 * - Led 0 blinks when a device is enumerated and USB in idle mode
 *   - The blink is slow (1s) with low speed device
 *   - The blink is normal (0.5s) with full speed device
 *   - The blink is fast (0.25s) with high speed device
 * - Led 0 is on when a read or write access is on going, and keep on if a LUN test is successful
 * - Led 0 is off when a LUN test is unsuccessful
 * - Button SW0 allows to enter the device in suspend mode with remote wakeup
 *   feature authorized
 * - Only SW0 button can be used to wakeup USB device in suspend mode
 */
