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

#define  MOUSE_MOVE_RANGE 5


/* Interrupt on "pin change" from push button to do wakeup on USB
 * Note:
 * This interrupt is enable when the USB host enable remote wakeup feature
 * This interrupt wakeup the CPU if this one is in idle mode
 */
static void ui_wakeup_handler(void)
{
	/* It is a wakeup then send wakeup USB */
	udc_remotewakeup();
	LED_On(LED_0_PIN);
}


void ui_init(void)
{
	struct extint_chan_conf config_extint_chan;

	extint_chan_get_config_defaults(&config_extint_chan);

	config_extint_chan.gpio_pin            = BUTTON_0_EIC_PIN;
	config_extint_chan.gpio_pin_mux        = BUTTON_0_EIC_MUX;
	config_extint_chan.gpio_pin_pull       = EXTINT_PULL_UP;
	config_extint_chan.filter_input_signal = true;
	config_extint_chan.detection_criteria  = EXTINT_DETECT_FALLING;
	extint_chan_set_config(BUTTON_0_EIC_LINE, &config_extint_chan);
	extint_register_callback(ui_wakeup_handler, BUTTON_0_EIC_LINE,
			EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_enable_callback(BUTTON_0_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);

	/* Initialize LEDs */
	LED_Off(LED_0_PIN);
}

void ui_powerdown(void)
{
	LED_Off(LED_0_PIN);
}


void ui_wakeup_enable(void)
{
	extint_chan_enable_callback(BUTTON_0_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);
}

void ui_wakeup_disable(void)
{
	extint_chan_disable_callback(BUTTON_0_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);
}

void ui_wakeup(void)
{
	LED_On(LED_0_PIN);
}

void ui_start_read(void)
{
}

void ui_stop_read(void)
{
}

void ui_start_write(void)
{
}

void ui_stop_write(void)
{
}

void ui_process(uint16_t framenumber)
{
	static uint8_t cpt_sof = 0;

	if ((framenumber % 1000) == 0) {
		LED_On(LED_0_PIN);
	}
	if ((framenumber % 1000) == 500) {
		LED_Off(LED_0_PIN);
	}
	/* Scan process running each 5ms */
	cpt_sof++;
	if (cpt_sof < 5) {
		return;
	}
	cpt_sof = 0;

	/* Uses buttons to move mouse */
	if (!port_pin_get_input_level(BUTTON_0_PIN)) {
		udi_hid_mouse_moveY(-MOUSE_MOVE_RANGE);
	}
}

/**
 * \defgroup UI User Interface
 *
 * Human interface on SAMD21-XPlain:
 * - Led 0 blinks when USB is connected and enabled Mouse and MSC interface
 * - Push button 0 (SW0) are used to move mouse up
 * - Only a low level on push button 0 will generate a wakeup to USB Host in remote wakeup mode.
 *
 */
