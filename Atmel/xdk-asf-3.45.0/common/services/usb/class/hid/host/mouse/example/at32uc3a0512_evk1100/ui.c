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

/**
 * \name Internal routines to manage asynchronous interrupt pin change
 * This interrupt is connected to a switch and allows to wakeup CPU in low sleep mode.
 * This wakeup the USB devices connected via a downstream resume.
 * @{
 */
static void ui_enable_asynchronous_interrupt(void);
static void ui_disable_asynchronous_interrupt(void);

/**
 * \brief Interrupt handler for interrupt pin change
 */
ISR(ui_wakeup_isr, AVR32_GPIO_IRQ_GROUP, 0)
{
	// Clear GPIO interrupt.
	gpio_clear_pin_interrupt_flag(GPIO_JOYSTICK_PUSH);

	// Clear External Interrupt Line else Wakeup event always enabled
	eic_clear_interrupt_line(&AVR32_EIC, EXT_NMI);

	if (uhc_is_suspend()) {
		ui_disable_asynchronous_interrupt();

		// Wakeup host and device
		uhc_resume();
	}
}

/**
 * \brief Initializes and enables interrupt pin change
 */
static void ui_enable_asynchronous_interrupt(void)
{
	//! Structure holding the configuration parameters of the EIC low level driver.
	eic_options_t eic_options = {
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
			.eic_async = EIC_ASYNCH_MODE};

	/* register joystick handler on level 0 */
	irqflags_t flags = cpu_irq_save();
	irq_register_handler(ui_wakeup_isr,
			AVR32_GPIO_IRQ_0 + (GPIO_JOYSTICK_PUSH / 8), 0);
	cpu_irq_restore(flags);

	/* configure joystick to produce IT on all state change */
	gpio_enable_pin_interrupt(GPIO_JOYSTICK_PUSH, GPIO_PIN_CHANGE);

	/*
	 * Configure pin change interrupt for asynchronous wake-up (required to
	 * wake up from the STATIC sleep mode).
	 *
	 * First, map the interrupt line to the GPIO pin with the right
	 * peripheral function.
	 */
	gpio_enable_module_pin(GPIO_JOYSTICK_PUSH, AVR32_EIC_EXTINT_8_FUNCTION);

	/*
	 * Enable the internal pull-up resistor on that pin (because the EIC is
	 * configured such that the interrupt will trigger on low-level, see
	 * eic_options.eic_level).
	 */
	gpio_enable_pin_pull_up(GPIO_JOYSTICK_PUSH);

	// Init the EIC controller with the set options.
	eic_init(&AVR32_EIC, &eic_options, sizeof(eic_options) /
			sizeof(eic_options_t));

	// Enable External Interrupt Controller Line
	eic_enable_line(&AVR32_EIC, EXT_NMI);
}

/**
 * \brief Disables interrupt pin change
 */
static void ui_disable_asynchronous_interrupt(void)
{
	eic_disable_line(&AVR32_EIC, EXT_NMI);

	/* Disable joystick input change ITs. */
	gpio_disable_pin_interrupt(GPIO_JOYSTICK_PUSH);
}
//! @}

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
	LED_Off(LED4);
	LED_Off(LED5);
	LED_Off(LED6);
	LED_Off(LED7);
}

void ui_usb_mode_change(bool b_host_mode)
{
	ui_init();
	if (b_host_mode) {
		LED_On(LED0);
	}
}
//! @}

/**
 * \name Host mode user interface functions
 * @{
 */

//! Status of device enumeration
static uhc_enum_status_t ui_enum_status=UHC_ENUM_DISCONNECT;
//! Manages device mouse moving
static int8_t ui_x, ui_y, ui_scroll;

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
	LED_On(LED7);
}

void ui_usb_connection_event(uhc_device_t *dev, bool b_present)
{
	LED_Off(LED3);
	LED_Off(LED4);
	LED_Off(LED5);
	LED_Off(LED6);
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
	if (ui_enum_status == UHC_ENUM_SUCCESS) {
		ui_x = 0, ui_y = 0, ui_scroll = 0;
	}
}

void ui_usb_wakeup_event(void)
{
	ui_disable_asynchronous_interrupt();
}

void ui_usb_sof_event(void)
{
	bool b_btn_state;
	static bool btn_suspend = false;
	static bool btn_suspend_and_remotewakeup = false;
	static uint16_t counter_sof = 0;

	if (ui_enum_status == UHC_ENUM_SUCCESS) {

		// Display device enumerated and in active mode
		if (++counter_sof == 500) {
			counter_sof = 0;
			LED_Toggle(LED3);
		}

		// Scan button to enter in suspend mode
		b_btn_state = !gpio_get_pin_value(GPIO_PUSH_BUTTON_0);
		if (b_btn_state != btn_suspend) {
			// Button have changed
			btn_suspend = b_btn_state;
			if (b_btn_state) {
				// Button has been pressed
				LED_Off(LED3);
				LED_Off(LED4);
				LED_Off(LED5);
				LED_Off(LED6);
				ui_enable_asynchronous_interrupt();
				uhc_suspend(false);
				return;
			}
		}

		// Scan button to enter in suspend mode and remote wakeup
		b_btn_state = !gpio_get_pin_value(GPIO_PUSH_BUTTON_1);
		if (b_btn_state != btn_suspend_and_remotewakeup) {
			// Button have changed
			btn_suspend_and_remotewakeup = b_btn_state;
			if (b_btn_state) {
				// Button has been pressed
				LED_Off(LED3);
				LED_Off(LED4);
				LED_Off(LED5);
				LED_Off(LED6);
				ui_enable_asynchronous_interrupt();
				uhc_suspend(true);
				return;
			}
		}

		// Power on a LED when the mouse move
		if (!ui_x && !ui_y && !ui_scroll) {
			LED_Off(LED6);
		}else{
			ui_x = ui_y = ui_scroll = 0;
			LED_On(LED6);
		}
	}
}

void ui_uhi_hid_mouse_btn_left(bool b_state)
{
	if (b_state) {
		LED_On(LED4);
	} else {
		LED_Off(LED4);
	}
}

void ui_uhi_hid_mouse_btn_right(bool b_state)
{
	if (b_state) {
		LED_On(LED5);
	} else {
		LED_Off(LED5);
	}
}

void ui_uhi_hid_mouse_btn_middle(bool b_state)
{
}

void ui_uhi_hid_mouse_move(int8_t x,int8_t y,int8_t scroll)
{
	ui_x = x;
	ui_y = y;
	ui_scroll = scroll;
}
//! @}

/**
 * \defgroup UI User Interface
 *
 * Human interface on EVK1100 :
 * - PWR led is on when power present
 * - Led 0 is on when USB OTG cable is plugged
 * - Led 1 is on when Vbus is present
 * - Led 2 is on when a device is connected
 * - Led 3 blinks when the device is enumerated and USB in idle mode
 * - Led 4 is on when the mouse left button is down
 * - Led 5 is on when the mouse right button is down
 * - Led 6 is on when the mouse move
 * - Led 7 is on when a bad Vbus level has been detected
 * - Switch PB0 allows to enter the device in suspend mode
 * - Switch PB1 allows to enter the device in suspend mode with remote wakeup feature authorized
 * - Only Push joystick button can be used to wakeup USB device in suspend mode
 *
 * Note: On board the LED labels are incremented of one.
 * E.g. Led0 in software corresponding at Led1 label on board.
 */
