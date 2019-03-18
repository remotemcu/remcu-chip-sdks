/**
 * \file
 *
 * \brief User Interface
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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

// Interrupt on "pin change" from switch to do wakeup on USB
// Note:
// This interrupt is enable when the USB host enable remotewakeup feature
// This interrupt wakeup the CPU if this one is in idle mode
ISR(ui_wakeup_isr, AVR32_GPIO_IRQ_GROUP, 0)
{
	// Clear GPIO interrupt.
	gpio_clear_pin_interrupt_flag(GPIO_PUSH_BUTTON_0);
	// Clear External Interrupt Line else Wakeup event always enabled
	eic_clear_interrupt_line(&AVR32_EIC, EXT_NMI);
	// It is a wakeup then send wakeup USB
	udc_remotewakeup();
}


void ui_init(void)
{
	/* register joystick handler on level 0 */
	irqflags_t flags = cpu_irq_save();
	irq_register_handler(ui_wakeup_isr,
			AVR32_GPIO_IRQ_0 + (GPIO_PUSH_BUTTON_2 / 8), 0);
	cpu_irq_restore(flags);

	LED_On(LED0);
	LED_Off(LED1);
}

void ui_powerdown(void)
{
	LED_Off(LED0);
	LED_Off(LED1);
}


//! Structure holding the configuration parameters of the EIC low level driver.
static const eic_options_t eic_options = {
	// Choose External Interrupt Controller Line
	.eic_line = EXT_NMI,
	// Enable level-triggered interrupt.
	.eic_mode = EIC_MODE_LEVEL_TRIGGERED,
	// Don't care value because the chosen eic mode is level-triggered.
	.eic_edge = 0,
	// Interrupt will trigger on low-level.
	.eic_level = EIC_LEVEL_LOW_LEVEL,
	// Enable filter.
	.eic_filter = EIC_FILTER_ENABLED,
	// For Wake Up mode, initialize in asynchronous mode
	.eic_async = EIC_ASYNCH_MODE
};


void ui_wakeup_enable(void)
{
	/* configure joystick to produce IT on all state change */
	gpio_enable_pin_interrupt(GPIO_PUSH_BUTTON_0, GPIO_PIN_CHANGE);
	/*
	 * Configure pin change interrupt for asynchronous wake-up (required to
	 * wake up from the STATIC sleep mode).
	 *
	 * First, map the interrupt line to the GPIO pin with the right
	 * peripheral function.
	 */
	gpio_enable_module_pin(GPIO_PUSH_BUTTON_0, 6);

	/*
	 * Enable the internal pull-up resistor on that pin (because the EIC is
	 * configured such that the interrupt will trigger on low-level, see
	 * eic_options.eic_level).
	 */
	gpio_enable_pin_pull_up(GPIO_PUSH_BUTTON_0);

	// Init the EIC controller with the set options.
	eic_init(&AVR32_EIC, &eic_options, sizeof(eic_options) /
			sizeof(eic_options_t));

	// Enable External Interrupt Controller Line
	eic_enable_line(&AVR32_EIC, EXT_NMI);
}

void ui_wakeup_disable(void)
{
	eic_disable_line(&AVR32_EIC, EXT_NMI);
	/* Disable joystick input change ITs. */
	gpio_disable_pin_interrupt(GPIO_PUSH_BUTTON_0);
}

void ui_wakeup(void)
{
	LED_On(LED0);
}

void ui_process(uint16_t framenumber)
{
	static uint8_t cpt_sof = 0;

	if ((framenumber % 1000) == 0) {
		LED_On(LED1);
	}
	if ((framenumber % 1000) == 500) {
		LED_Off(LED1);
	}
	// Scan process running each 2ms
	cpt_sof++;
	if (2 > cpt_sof)
		return;
	cpt_sof = 0;

	// No Scan buttons
	// Look touch sensor activity for the X and Y events
	if (!gpio_get_pin_value(GPIO_PUSH_BUTTON_0)) {
		udi_hid_mouse_moveX(-MOUSE_MOVE_RANGE);
	}
	if (!gpio_get_pin_value(GPIO_PUSH_BUTTON_1)) {
		udi_hid_mouse_moveX(MOUSE_MOVE_RANGE);
	}
}

/**
 * \defgroup UI User Interface
 *
 * Human interface on STK600 :
 * - PWR led is on when power present
 * - Led 0 is on when USB line is in IDLE mode, and off in SUSPEND mode
 * - Led 1 blinks when USB host has checked and enabled HID mouse interface
 * - Mouse move are linked at switches 0 (left), 1 (right)
 * - Switch 0 is linked to wakeup USB Host in remote wakeup mode
 */
