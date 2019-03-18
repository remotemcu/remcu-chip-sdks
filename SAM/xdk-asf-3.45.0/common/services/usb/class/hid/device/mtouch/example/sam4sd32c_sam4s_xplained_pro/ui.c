/**
 * \file
 *
 * \brief User Interface
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

static uint8_t ui_hid_report[UDI_HID_REPORT_IN_SIZE] = {0};

static uint8_t ui_step = 0;

void ui_multitouch_down(void);

void ui_init(void)
{
	// Enable PIO clock for button inputs
	pmc_enable_periph_clk(ID_PIOA);
	pmc_enable_periph_clk(ID_PIOB);
	pmc_enable_periph_clk(ID_PIOC);
	// Initialize LEDs
	LED_On(LED0_GPIO);
}

void ui_powerdown(void)
{
	LED_Off(LED0_GPIO);
}


void ui_wakeup_enable(void)
{

}

void ui_wakeup_disable(void)
{

}

void ui_wakeup(void)
{
	LED_On(LED0_GPIO);
}

void ui_process(uint16_t framenumber)
{
	bool b_btn_state;
	static bool btn0_last_state = false;
	static uint8_t cpt_sof = 0;

	// Blink LED
	if ((framenumber % 1000) == 0) {
		LED_On(LED0_GPIO);
	}
	if ((framenumber % 1000) == 500) {
		LED_Off(LED0_GPIO);
	}
	// Scan process running each 40ms
	cpt_sof++;
	if (cpt_sof < 40) {
		return;
	}
	cpt_sof = 0;

	// Scan buttons on switch 0 and 1
	b_btn_state = (!gpio_pin_is_high(GPIO_PUSH_BUTTON_0)) ? true : false;
	if (b_btn_state != btn0_last_state) {
		ui_multitouch_down();
		ui_step++;
		btn0_last_state = b_btn_state;
	}
}

void ui_multitouch_down()
{
	// Report ID
	ui_hid_report[0] = UDI_HID_REPORT_ID_MTOUCH;
 
	// 1st touch
	ui_hid_report[1] = 3;
	ui_hid_report[2] = 1;
	ui_hid_report[3] = (uint8_t)((1365 + 10 * ui_step) & 0x00FF);
	ui_hid_report[4] = (uint8_t)(((1365 + 10 * ui_step) & 0xFF00) >> 8);
	ui_hid_report[5] = (uint8_t)(1365 & 0x00FF);
	ui_hid_report[6] = (uint8_t)((1365 & 0xFF00) >> 8);
 
	// 2nd touch
	ui_hid_report[7] = 3;
	ui_hid_report[8] = 2;
	ui_hid_report[9] = (uint8_t)(1365 & 0x00FF);
	ui_hid_report[10] = (uint8_t)((1365 & 0xFF00) >> 8);
	ui_hid_report[11] = (uint8_t)((1365 + 10 * ui_step) & 0x00FF);
	ui_hid_report[12] = (uint8_t)(((1365 + 10 * ui_step) & 0xFF00) >> 8);
 
	// Number of touches   
	ui_hid_report[13] = 2;

	udi_hid_multi_touch_send_report_in(ui_hid_report);
}

/**
 * \defgroup UI User Interface
 *
 * Human interface on SAM4S-EK:
 * - Led 0 (D2) blinks when USB host has checked and enabled HID generic interface
 * - Push button 0 (SW0) is used to draw line in paint application on Windows O.S
 *  - Run the application and connect usb to he PC first.
 *  - Open paint and push button 0 continuously, then two lines painted.
 *
 */
