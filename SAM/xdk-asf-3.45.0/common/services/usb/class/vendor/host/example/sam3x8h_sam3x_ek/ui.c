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

/**
 * \name Main user interface functions
 * @{
 */
void ui_init(void)
{
	/* Initialize LEDs */
	LED_Off(LED0_GPIO);
	LED_Off(LED1_GPIO);
	LED_Off(LED2_GPIO);
	LED_Off(LED3_GPIO);
}

void ui_usb_mode_change(bool b_host_mode)
{
	(void)b_host_mode;
	ui_init();
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
/*! Status of the Vendor test */
static bool ui_test_done;
/*! Result of the Vendor test */
static bool ui_test_result;

void ui_usb_vbus_change(bool b_vbus_present)
{
	if (b_vbus_present) {
		LED_On(LED3_GPIO);
	} else {
		LED_Off(LED3_GPIO);
	}
}

void ui_usb_vbus_error(void)
{
}

void ui_usb_connection_event(uhc_device_t *dev, bool b_present)
{
	(void)dev;
	if (b_present) {
		LED_On(LED1_GPIO);
	} else {
		LED_Off(LED0_GPIO);
		LED_Off(LED1_GPIO);
		ui_enum_status = UHC_ENUM_DISCONNECT;
	}
}

void ui_usb_enum_event(uhc_device_t *dev, uhc_enum_status_t status)
{
	UNUSED(dev);
	ui_enum_status = status;
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
	ui_test_done = false;
}


void ui_usb_sof_event(void)
{
	static uint16_t counter_sof = 0;

	if (ui_enum_status == UHC_ENUM_SUCCESS) {
		/* Display device enumerated and in active mode */
		if (++counter_sof > ui_device_speed_blink) {
			counter_sof = 0;
			LED_Toggle(LED1_GPIO);
			if (ui_test_done && !ui_test_result) {
				/* Test fail then blink led */
				LED_Toggle(LED0_GPIO);
			}
		}
	}
}

void ui_test_finish(bool b_success)
{
	ui_test_done = true;
	ui_test_result = b_success;
	if (b_success) {
		LED_On(LED0_GPIO);
	}
}

/*! @} */


/**
 * \defgroup UI User Interface
 *
 * Human interface on SAM3X-EK :
 * - Led 3 (D5, red) is on when Vbus is generated
 * - Led 1 (D4, green) is continuously on when a device is connected
 * - Led 1 blinks when the device is enumerated and USB in idle mode
 *   - The blink is slow (1s) with low speed device
 *   - The blink is normal (0.5s) with full speed device
 *   - The blink is fast (0.25s) with high speed device
 * - Led 0 (D2, blue) is on when all vendor tests are success
 * - Led 0 blinks when a vendor test is unsuccess
 */
