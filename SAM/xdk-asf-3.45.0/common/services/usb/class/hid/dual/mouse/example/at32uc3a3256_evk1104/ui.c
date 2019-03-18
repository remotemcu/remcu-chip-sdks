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

//! Current USB mode
static bool ui_b_host_mode = false;

/**
 * \name Internal routines to manage asynchronous interrupt pin change
 * This interrupt is connected to a switch and allows to wakeup CPU in low sleep mode.
 * In USB device mode, this wakeup the USB host via a upstream resume.
 * In USB host mode, this wakeup the USB devices connected via a downstream resume.
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
	gpio_clear_pin_interrupt_flag(AVR32_PIN_PA20);

	// Clear External Interrupt Line else Wakeup event always enabled
	eic_clear_interrupt_line(&AVR32_EIC, EXT_NMI);

	if (ui_b_host_mode) {
		if (!uhc_is_suspend()) {
			// USB is not in suspend mode
			// Let's interrupt enable.
			return;
		}
		ui_disable_asynchronous_interrupt();

		// Wakeup the devices connected
		uhc_resume();
	} else {
		// In device mode, wakeup the USB host.
		udc_remotewakeup();
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
			AVR32_GPIO_IRQ_0 + (AVR32_PIN_PA20 / 8), 0);
	cpu_irq_restore(flags);

	// With the UC3A3 datasheet, in section "Peripheral Multiplexing on I/O lines"
	// in the table "GPIO Controller Function Multiplexing", we see that the NMI is
	// mapped on GPIO 20 (i.e. PA20). Using the EVK1104 schematics, we see that the
	// J17.7 pin is connected to PA20. Thus, a low level on J17.7 will generate an
	// NMI. The External Interrupt number 8 is the NMI.

	/* configure joystick to produce IT on all state change */
	gpio_enable_pin_interrupt(AVR32_PIN_PA20, GPIO_PIN_CHANGE);

	/*
	 * Configure pin change interrupt for asynchronous wake-up (required to
	 * wake up from the STATIC sleep mode).
	 *
	 * First, map the interrupt line to the GPIO pin with the right
	 * peripheral function.
	 */
	gpio_enable_module_pin(AVR32_PIN_PA20, AVR32_EIC_EXTINT_8_FUNCTION);

	/*
	 * Enable the internal pull-up resistor on that pin (because the EIC is
	 * configured such that the interrupt will trigger on low-level, see
	 * eic_options.eic_level).
	 */
	gpio_enable_pin_pull_up(AVR32_PIN_PA20);

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
	gpio_disable_pin_interrupt(AVR32_PIN_PA20);
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
}

void ui_usb_mode_change(bool b_host_mode)
{
	ui_init();
	ui_b_host_mode = b_host_mode;
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
static uhc_enum_status_t ui_host_enum_status=UHC_ENUM_DISCONNECT;
//! Manages device mouse moving
static int8_t ui_host_x, ui_host_y, ui_host_scroll;

void ui_host_vbus_change(bool b_vbus_present)
{
	UNUSED(b_vbus_present);
}

void ui_host_vbus_error(void)
{
}

void ui_host_connection_event(uhc_device_t *dev, bool b_present)
{
	LED_Off(LED2);
	LED_Off(LED3);
	if (b_present) {
		LED_On(LED1);
	} else {
		LED_Off(LED1);
		ui_host_enum_status = UHC_ENUM_DISCONNECT;
	}
}

void ui_host_enum_event(uhc_device_t *dev, uhc_enum_status_t status)
{
	ui_host_enum_status = status;
	if (ui_host_enum_status == UHC_ENUM_SUCCESS) {
		ui_host_x = 0, ui_host_y = 0, ui_host_scroll = 0;
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
	static uint16_t counter_sof=0;

	if (ui_host_enum_status == UHC_ENUM_SUCCESS) {

		// Display device enumerated and in active mode
		if (++counter_sof == 500) {
			counter_sof = 0;
			LED_Toggle(LED1);
		}

		// Scan button to enter in suspend mode and remote wakeup
		b_btn_state = !gpio_get_pin_value(GPIO_PUSH_BUTTON_SW2);
		if (b_btn_state != btn_suspend_and_remotewakeup) {
			// Button have changed
			btn_suspend_and_remotewakeup = b_btn_state;
			if (b_btn_state) {
				// Button has been pressed
				LED_Off(LED1);
				LED_Off(LED2);
				LED_Off(LED3);
				ui_enable_asynchronous_interrupt();
				uhc_suspend(true);
				return;
			}
		}

		// Power on a LED when the mouse move
		if (!ui_host_x && !ui_host_y && !ui_host_scroll) {
			LED_Off(LED2);
		}else{
			ui_host_x = ui_host_y = ui_host_scroll = 0;
			LED_On(LED2);
		}
	}
}

static void ui_host_hid_mouse_btn(bool b_state)
{
	static uint8_t nb_down = 0;
	if (b_state) {
		nb_down++;
	} else {
		nb_down--;
	}
	if (nb_down) {
		LED_On(LED3);
	} else {
		LED_Off(LED3);
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

void ui_host_hid_mouse_move(int8_t x,int8_t y,int8_t scroll)
{
	ui_host_x = x;
	ui_host_y = y;
	ui_host_scroll = scroll;
}
//! @}

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

	if (!ui_device_b_mouse_enable)
		return;

	framenumber = udd_get_frame_number();
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

	// Scan move on SW2 (right)
	if (gpio_get_pin_value(GPIO_PUSH_BUTTON_SW2) ==
			GPIO_PUSH_BUTTON_SW2_PRESSED) {
		udi_hid_mouse_moveX(MOUSE_MOVE_RANGE);
	}
}
//! @}

/**
 * \defgroup UI User Interface
 *
 * Human interface on EVK1104 :
 * - PWR led is on when power present
 * - Led 0 is on in host mode (when USB OTG cable is pluged)
 * - device mode:
 *   - Led 1 is on when USB line is in IDLE mode, and off in SUSPEND mode
 *   - Led 2 blinks when USB host has checked and enabled HID mouse interface
 *   - Mouse buttons are not linked.
 *   - Only SW2 allows to move mouse on X axe.
 * - host mode:
 *   - Led  is on when Vbus is present
 *   - Led 1 is continuously on when a device is connected
 *   - Led 1 blinks when the device is enumerated and USB in idle mode
 *   - Led 2 is on when a HID mouse button is pressed
 *   - Led 3 is on when the mouse move
 *   - Switch SW2 allows to enter the device in suspend mode with remote wakeup feature authorized
 *   - Only a low level on J17.7 will generate a wakeup USB device in suspend mode.
 */
