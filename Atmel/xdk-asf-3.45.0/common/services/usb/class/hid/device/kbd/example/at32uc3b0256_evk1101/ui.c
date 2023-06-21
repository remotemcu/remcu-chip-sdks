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

//! Sequence process running each \c SEQUENCE_PERIOD ms
#define SEQUENCE_PERIOD 150

static struct {
	bool b_modifier;
	bool b_down;
	uint8_t u8_value;
} ui_sequence[] = {
	// Display windows menu
	{true,true,HID_MODIFIER_LEFT_UI},
	// Launch Windows Command line
	{false,true,HID_R},
	{false,false,HID_R},
	// Clear modifier
	{true,false,HID_MODIFIER_LEFT_UI},
	// Tape sequence "notepad" + return
	{false,true,HID_N},
	{false,false,HID_N},
	{false,true,HID_O},
	{false,false,HID_O},
	{false,true,HID_T},
	{false,false,HID_T},
	{false,true,HID_E},
	{false,false,HID_E},
	{false,true,HID_P},
	{false,false,HID_P},
	{false,true,HID_A},
	{false,false,HID_A},
	{false,true,HID_D},
	{false,false,HID_D},
	{false,true,HID_ENTER},
	{false,false,HID_ENTER},
	// Delay to wait "notepad" focus
	{false,false,0}, // No key (= SEQUENCE_PERIOD delay)
	{false,false,0}, // No key (= SEQUENCE_PERIOD delay)
	{false,false,0}, // No key (= SEQUENCE_PERIOD delay)
	{false,false,0}, // No key (= SEQUENCE_PERIOD delay)
	{false,false,0}, // No key (= SEQUENCE_PERIOD delay)
	{false,false,0}, // No key (= SEQUENCE_PERIOD delay)
	{false,false,0}, // No key (= SEQUENCE_PERIOD delay)
	// Display "Atmel "
	{true,true,HID_MODIFIER_RIGHT_SHIFT}, // Enable Maj
	{false,true,HID_A},
	{false,false,HID_A},
	{true,false,HID_MODIFIER_RIGHT_SHIFT}, // Disable Maj
	{false,true,HID_T},
	{false,false,HID_T},
	{false,true,HID_M},
	{false,false,HID_M},
	{false,true,HID_E},
	{false,false,HID_E},
	{false,true,HID_L},
	{false,false,HID_L},
	{false,true,HID_SPACEBAR},
	{false,false,HID_SPACEBAR},
	// Display "AVR "
	{false,true,HID_CAPS_LOCK}, // Enable caps lock
	{false,false,HID_CAPS_LOCK},
	{false,true,HID_A},
	{false,false,HID_A},
	{false,true,HID_V},
	{false,false,HID_V},
	{false,true,HID_R},
	{false,false,HID_R},
	{false,true,HID_CAPS_LOCK}, // Disable caps lock
	{false,false,HID_CAPS_LOCK},
};

// Interrupt on "pin change" from switch to do wakeup on USB
// Note:
// This interrupt is enable when the USB host enable remotewakeup feature
// This interrupt wakeup the CPU if this one is in idle mode
ISR(ui_wakeup_isr, AVR32_GPIO_IRQ_GROUP, 0)
{
	// Clear GPIO interrupts.
	gpio_clear_pin_interrupt_flag(GPIO_PUSH_BUTTON_0);
	// Clear External Interrupt Line else Wakeup event always enabled
	eic_clear_interrupt_line(&AVR32_EIC, EXT_INT6);
	// It is a wakeup then send wakeup USB
	udc_remotewakeup();
}


void ui_init(void)
{
	/* register joystick handler on level 0 */
	irqflags_t flags = cpu_irq_save();
	irq_register_handler(ui_wakeup_isr,
			AVR32_GPIO_IRQ_0 + (GPIO_PUSH_BUTTON_0 / 8), 0);
	cpu_irq_restore(flags);

	LED_On(LED0);
	LED_Off(LED1);
	LED_Off(LED2);
	LED_Off(LED3);
}

void ui_powerdown(void)
{
	LED_Off(LED0);
	LED_Off(LED1);
	LED_Off(LED2);
	LED_Off(LED3);
}


//! Structure holding the configuration parameters of the EIC low level driver.
static eic_options_t eic_options = {
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
	/* configure buttons to produce IT on all state change */
	gpio_enable_pin_interrupt(GPIO_PUSH_BUTTON_0, GPIO_PIN_CHANGE);
	/*
	 * Configure pin change interrupt for asynchronous wake-up (required to
	 * wake up from the STATIC sleep mode).
	 *
	 * First, map the interrupt line to the GPIO pin with the right
	 * peripheral function.
	 */
	gpio_enable_module_pin(GPIO_PUSH_BUTTON_0, AVR32_EIC_EXTINT_6_FUNCTION);

	/*
	 * Enable the internal pull-up resistor on that pin (because the EIC is
	 * configured such that the interrupt will trigger on low-level, see
	 * eic_options.eic_level).
	 */
	gpio_enable_pin_pull_up(GPIO_PUSH_BUTTON_0);

	// Init the EIC controller with the set options.
	eic_options.eic_line = EXT_INT6;
	eic_init(&AVR32_EIC, &eic_options,
			sizeof(eic_options) / sizeof(eic_options_t));
	// Enable External Interrupt Controller Line
	eic_enable_line(&AVR32_EIC, EXT_INT6);
}

void ui_wakeup_disable(void)
{
	eic_disable_line(&AVR32_EIC, EXT_INT6);
	/* Disable joystick input change ITs. */
	gpio_disable_pin_interrupt(GPIO_PUSH_BUTTON_0);
}

void ui_wakeup(void)
{
	LED_On(LED0);
}

void ui_process(uint16_t framenumber)
{
	bool b_btn_state, sucess;
	static bool btn_last_state = false;
	static bool sequence_running = false;
	static uint8_t u8_sequence_pos = 0;
	uint8_t u8_value;
	static uint16_t cpt_sof = 0;

	if ((framenumber % 1000) == 0) {
		LED_On(LED1);
	}
	if ((framenumber % 1000) == 500) {
		LED_Off(LED1);
	}
	// Scan process running each 2ms
	cpt_sof++;
	if ((cpt_sof % 2) == 0) {
		return;
	}

	// Scan buttons on switch 0 to send keys sequence
	b_btn_state = (!gpio_get_pin_value(GPIO_PUSH_BUTTON_0)) ? true : false;
	if (b_btn_state != btn_last_state) {
		btn_last_state = b_btn_state;
		sequence_running = true;
	}

	// Sequence process running each period
	if (SEQUENCE_PERIOD > cpt_sof) {
		return;
	}
	cpt_sof = 0;

	if (sequence_running) {
		// Send next key
		u8_value = ui_sequence[u8_sequence_pos].u8_value;
		if (u8_value!=0) {
			if (ui_sequence[u8_sequence_pos].b_modifier) {
				if (ui_sequence[u8_sequence_pos].b_down) {
					sucess = udi_hid_kbd_modifier_down(u8_value);
				} else {
					sucess = udi_hid_kbd_modifier_up(u8_value);
				}
			} else {
				if (ui_sequence[u8_sequence_pos].b_down) {
					sucess = udi_hid_kbd_down(u8_value);
				} else {
					sucess = udi_hid_kbd_up(u8_value);
				}
			}
			if (!sucess) {
				return; // Retry it on next schedule
			}
		}
		// Valid sequence position
		u8_sequence_pos++;
		if (u8_sequence_pos >=
			sizeof(ui_sequence) / sizeof(ui_sequence[0])) {
			u8_sequence_pos = 0;
			sequence_running = false;
		}
	}
}

void ui_kbd_led(uint8_t value)
{
	if (value & HID_LED_NUM_LOCK) {
		LED_On(LED2);
	} else {
		LED_Off(LED2);
	}
	if (value & HID_LED_CAPS_LOCK) {
		LED_On(LED3);
	} else {
		LED_Off(LED3);
	}
}

/**
 * \defgroup UI User Interface
 *
 * Human interface on EVK1101 :
 * - Led 0 is on when USB line is in IDLE mode, and off in SUSPEND mode
 * - Led 1 blinks when USB host has checked and enabled HID Keyboard interface
 * - Led 2 displays numeric lock status.
 * - Led 3 displays caps lock status.
 * - The PB0 opens a notepad application on Windows O.S.
 * and sends key sequence "Atmel AVR USB Keyboard"
 * - The PB0 can be used to wakeup USB Host in remote wakeup mode.
 *
 */
