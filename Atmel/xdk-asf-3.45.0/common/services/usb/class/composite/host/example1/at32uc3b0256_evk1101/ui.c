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
	// Clear GPIO interrupts.
	gpio_clear_pin_interrupt_flag(GPIO_PUSH_BUTTON_0);
	gpio_clear_pin_interrupt_flag(GPIO_PUSH_BUTTON_1);

	// Clear External Interrupt Line else Wakeup event always enabled
	eic_clear_interrupt_line(&AVR32_EIC, EXT_INT6);
	eic_clear_interrupt_line(&AVR32_EIC, EXT_INT7);

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

	/* register joystick handler on level 0 */
	irqflags_t flags = cpu_irq_save();
	irq_register_handler(ui_wakeup_isr,
			AVR32_GPIO_IRQ_0 + (GPIO_PUSH_BUTTON_0 / 8), 0);
	cpu_irq_restore(flags);

	/* configure buttons to produce IT on all state change */
	gpio_enable_pin_interrupt(GPIO_PUSH_BUTTON_0, GPIO_PIN_CHANGE);
	gpio_enable_pin_interrupt(GPIO_PUSH_BUTTON_1, GPIO_PIN_CHANGE);

	/*
	 * Configure pin change interrupt for asynchronous wake-up (required to
	 * wake up from the STATIC sleep mode).
	 *
	 * First, map the interrupt line to the GPIO pin with the right
	 * peripheral function.
	 */
	gpio_enable_module_pin(GPIO_PUSH_BUTTON_0, AVR32_EIC_EXTINT_6_FUNCTION);
	gpio_enable_module_pin(GPIO_PUSH_BUTTON_1, AVR32_EIC_EXTINT_7_FUNCTION);

	/*
	 * Enable the internal pull-up resistor on that pin (because the EIC is
	 * configured such that the interrupt will trigger on low-level, see
	 * eic_options.eic_level).
	 */
	gpio_enable_pin_pull_up(GPIO_PUSH_BUTTON_0);
	gpio_enable_pin_pull_up(GPIO_PUSH_BUTTON_1);

	// Init the EIC controller with the set options.
	eic_options.eic_line = EXT_INT6;
	eic_init(&AVR32_EIC, &eic_options,
			sizeof(eic_options) / sizeof(eic_options_t));
	eic_options.eic_line = EXT_INT7;
	eic_init(&AVR32_EIC, &eic_options,
			sizeof(eic_options) / sizeof(eic_options_t));

	// Enable External Interrupt Controller Line
	eic_enable_line(&AVR32_EIC, EXT_INT6);
	eic_enable_line(&AVR32_EIC, EXT_INT7);
}

/**
 * \brief Disables interrupt pin change
 */
static void ui_disable_asynchronous_interrupt(void)
{
	eic_disable_line(&AVR32_EIC, EXT_INT6);
	eic_disable_line(&AVR32_EIC, EXT_INT7);
	/* Disable joystick input change ITs. */
	gpio_disable_pin_interrupt(GPIO_PUSH_BUTTON_0);
	gpio_disable_pin_interrupt(GPIO_PUSH_BUTTON_1);
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
}
//! @}

/**
 * \name Host mode user interface functions
 * @{
 */

//! Status of device enumeration
static uhc_enum_status_t ui_enum_status=UHC_ENUM_DISCONNECT;
//! Blink frequency depending on device speed
static uint16_t ui_device_speed_blink;
//! Notify the presence of a USB device mouse
static bool ui_hid_mouse_plug = false;
//! Notify the presence of a USB device MSC
static bool ui_msc_plug = false;
//! Status of the MSC test
static bool ui_test_done;
//! Result of the MSC test
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
	if (b_present) {
		LED_On(LED0);
	} else {
		ui_enum_status = UHC_ENUM_DISCONNECT;
		LED_Off(LED0);
	}
	LED_Off(LED1);
	LED_Off(LED2);
	LED_Off(LED3);
}

void ui_usb_enum_event(uhc_device_t *dev, uhc_enum_status_t status)
{
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
		ui_test_done = false;
	}
}

void ui_uhi_hid_mouse_change(uhc_device_t * dev, bool b_plug)
{
	ui_hid_mouse_plug = b_plug;
}

void ui_uhi_msc_change(uhc_device_t * dev, bool b_plug)
{
	ui_msc_plug = b_plug;
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

		// Display device enumerated and in active mode
		if (++counter_sof > ui_device_speed_blink) {
			counter_sof = 0;
			if (ui_hid_mouse_plug) {
				LED_Toggle(LED0);
			}else{
				LED_Off(LED0);
			}
			if (ui_msc_plug) {
				LED_Toggle(LED1);
			}
			if (ui_test_done && !ui_test_result) {
				// Test fail then blink led
				LED_Toggle(LED3);
			}
		}
		
		// Scan button to enter in suspend mode and remote wakeup
		b_btn_state = is_joystick_pressed();
		if (b_btn_state != btn_suspend) {
			// Button have changed
			btn_suspend = b_btn_state;
			if (b_btn_state) {
				// Button has been pressed
				LED_Off(LED0);
				LED_Off(LED1);
				LED_Off(LED2);
				ui_enable_asynchronous_interrupt();
				uhc_suspend(true);
				return;
			}
		}
	}
}

static void ui_uhi_hid_mouse_btn(bool b_state)
{
	static uint8_t nb_down = 0;
	if (b_state) {
		nb_down++;
	} else {
		nb_down--;
	}
	if (nb_down) {
		LED_On(LED2);
	} else {
		LED_Off(LED2);
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
	if (b_success) {
		LED_On(LED3);
	}
}
//! @}

//! \name Callback to mange the HID mouse events
//! @{
void ui_uhi_hid_mouse_btn_left(bool b_state)
{
	ui_uhi_hid_mouse_btn(b_state);
}

void ui_uhi_hid_mouse_btn_right(bool b_state)
{
	ui_uhi_hid_mouse_btn(b_state);
}

void ui_uhi_hid_mouse_btn_middle(bool b_state)
{
	ui_uhi_hid_mouse_btn(b_state);
}

void ui_uhi_hid_mouse_move(int8_t x, int8_t y, int8_t scroll)
{
}
//! @}

//! \name Callback to show the MSC read and write access
//! @{
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
//! @}

/**
 * \defgroup UI User Interface
 *
 * Human interface on EVK1101 :
 * - PWR led is on when power present
 * - Led 0 is continuously on when a device is connected
 * - Led 0 blinks when a HID mouse is enumerated and USB in idle mode
 *   - The blink is slow (1s) with low speed device
 *   - The blink is normal (0.5s) with full speed device
 *   - The blink is fast (0.25s) with high speed device
 * - Led 1 blinks when a MSC is enumerated and USB in idle mode
 *   - The blink is slow (1s) with low speed device
 *   - The blink is normal (0.5s) with full speed device
 *   - The blink is fast (0.25s) with high speed device
 * - Led 2 is on when a HID mouse button is pressed
 * - Led 3 is on when a LUN test is success
 * - Led 3 blinks when a LUN test is unsuccessful
 * - Joystick press allows to enter the device in suspend mode with remote wakeup feature authorized
 * - The PB0 and PB1 button can be used to wakeup the USB devices in suspend mode
 */
