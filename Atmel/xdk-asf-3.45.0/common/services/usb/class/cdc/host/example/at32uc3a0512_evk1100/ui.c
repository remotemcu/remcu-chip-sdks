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
#include "conf_usb_host.h"
#include "ui.h"

/**
 * \name Main user interface functions
 * @{
 */
void ui_init(void)
{
	LED_Off(LED0);
	LED_Off(LED1);
	LED_Off(LED2);
	LED_Off(LED3);
	LED_Off(LED_BI0_GREEN);
	LED_Off(LED_BI0_RED);
	LED_Off(LED_BI1_GREEN);
	LED_Off(LED_BI1_RED);
}

void ui_usb_mode_change(bool b_host_mode)
{
	ui_init();
	if (b_host_mode) {
		LED_On(LED0);
	}
}
/*! @} */

/**
 * \name Host mode user interface functions
 * @{
 */

/*! Status of device enumeration */
static uhc_enum_status_t ui_enum_status=UHC_ENUM_DISCONNECT;
/*! Blink frequency depending on device speed */
static uint16_t ui_device_speed_blink;

void ui_usb_vbus_change(bool b_vbus_present)
{
	if (b_vbus_present) {
		LED_On(LED1);
	} else {
		LED_Off(LED1);
	}
}

void ui_usb_vbus_error(void)
{
}

void ui_usb_connection_event(uhc_device_t *dev, bool b_present)
{
	LED_Off(LED3);
	LED_Off(LED_BI0_GREEN);
	LED_Off(LED_BI0_RED);
	LED_Off(LED_BI1_GREEN);
	LED_Off(LED_BI1_RED);
	if (b_present) {
		LED_On(LED2);
	} else {
		LED_Off(LED2);
		ui_enum_status = UHC_ENUM_DISCONNECT;
	}
}

void ui_usb_enum_event(uhc_device_t *dev, uhc_enum_status_t status)
{
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
	if (ui_enum_status == UHC_ENUM_SUCCESS) {
		/* USB Device CDC connected
		   Open and configure UART and USB CDC ports */
		usb_cdc_line_coding_t cfg = {
			.dwDTERate   = CPU_TO_LE32(115200),
			.bCharFormat = CDC_STOP_BITS_1,
			.bParityType = CDC_PAR_NONE,
			.bDataBits   = 8,
		};
		uart_open();
		uart_config(&cfg);
		uhi_cdc_open(0, &cfg);
	}
}

void ui_usb_wakeup_event(void)
{
}

void ui_usb_sof_event(void)
{
	static uint16_t counter_sof = 0;

	if (ui_enum_status == UHC_ENUM_SUCCESS) {

		/*Display device enumerated and in active mode */
		if (++counter_sof > ui_device_speed_blink) {
			counter_sof = 0;
			LED_Toggle(LED3);
		}
	}
}

void ui_com_rx_start(void)
{
	LED_On(LED_BI0_GREEN);
}

void ui_com_rx_stop(void)
{
	LED_Off(LED_BI0_GREEN);
}

void ui_com_tx_start(void)
{
	LED_On(LED_BI1_GREEN);
}

void ui_com_tx_stop(void)
{
	LED_Off(LED_BI1_GREEN);
}

void ui_com_error(void)
{
	LED_On(LED_BI0_RED);
}

void ui_com_overflow(void)
{
	LED_On(LED_BI1_RED);
}

/*! @} */

/**
 * \defgroup UI User Interface
 *
 * Human interface on EVK1100 :
 * - PWR led is on when power present
 * - Led 0 is on when USB OTG cable is plugged in
 * - Led 1 is on when Vbus is present
 * - Led 2 is on when a device is connected
 * - Led 3 blinks when the CDC device is enumerated and USB in idle mode
 *   - The blink is slow (1s) with low speed device
 *   - The blink is normal (0.5s) with full speed device
 *   - The blink is fast (0.25s) with high speed device
 * - Led 4 green is on during data transfer from CDC to UART
 * - Led 5 green is on during data transfer from UART to CDC
 *
 * Note: On board the LED labels are incremented of one.
 * E.g. Led0 in software corresponding at Led1 label on board.
 */
