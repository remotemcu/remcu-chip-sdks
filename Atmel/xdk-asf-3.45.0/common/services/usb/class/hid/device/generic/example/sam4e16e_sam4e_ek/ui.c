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

/** HID report buffer */
static uint8_t ui_hid_report[UDI_HID_REPORT_OUT_SIZE];

void ui_init(void)
{
	/* Initialize LEDs */
	LED_Off(LED0);
	LED_Off(LED1);
}

void ui_powerdown(void)
{
	LED_Off(LED0);
	LED_Off(LED1);
}


void ui_wakeup_enable(void)
{
}

void ui_wakeup_disable(void)
{
}

void ui_wakeup(void)
{
	LED_On(LED0);
}

void ui_process(uint16_t framenumber)
{
	bool b_btn_state;
	static bool btn0_last_state = false;
	static bool btn1_last_state = false;
	static uint8_t cpt_sof = 0;

	if ((framenumber % 1000) == 0) {
		LED_On(LED1);
	}
	if ((framenumber % 1000) == 500) {
		LED_Off(LED1);
	}
	/* Scan process running each 40ms */
	cpt_sof++;
	if (cpt_sof < 40) {
		return;
	}
	cpt_sof = 0;

	/* Scan push buttons 1 and 2 */
	b_btn_state = !ioport_get_pin_level(GPIO_PUSH_BUTTON_1);
	if (b_btn_state != btn0_last_state) {
		ui_hid_report[0]=b_btn_state;
		udi_hid_generic_send_report_in(ui_hid_report);
		btn0_last_state = b_btn_state;
	}
	b_btn_state = !ioport_get_pin_level(GPIO_PUSH_BUTTON_2);
	if (b_btn_state != btn1_last_state) {
		ui_hid_report[0]=b_btn_state;
		udi_hid_generic_send_report_in(ui_hid_report);
		btn1_last_state = b_btn_state;
	}
}

void ui_led_change(uint8_t *report)
{
	if (report[0]=='1') {
		/* A led must be on */
		switch(report[1]) {
			case '1':
			LED_On(LED2);
			break;
		}
	} else {
		/* A led must be off */
		switch(report[1]) {
			case '1':
			LED_Off(LED2);
			break;
		}
	}
}

/**
 * \defgroup UI User Interface
 *
 * Human interface on SAM4E-EK:
 * - Led 0 (D2) is on when USB is wakeup
 * - Led 1 (D3) blinks when USB host has checked and enabled HID generic interface
 * - Led 2 (D4) is linked on HID events LED1
 * - Event buttons are linked to push button 1 (BP2) and push button 2 (BP3)
 *
 */
