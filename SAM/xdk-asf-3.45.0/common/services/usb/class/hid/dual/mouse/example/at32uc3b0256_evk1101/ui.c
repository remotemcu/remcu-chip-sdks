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
	// Clear GPIO interrupts.
	gpio_clear_pin_interrupt_flag(GPIO_PUSH_BUTTON_0);
	gpio_clear_pin_interrupt_flag(GPIO_PUSH_BUTTON_1);

	// Clear External Interrupt Line else Wakeup event always enabled
	eic_clear_interrupt_line(&AVR32_EIC, EXT_INT6);
	eic_clear_interrupt_line(&AVR32_EIC, EXT_INT7);

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
			.eic_async = EIC_ASYNCH_MODE};

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
	// Initialize accelerometer driver
	sysclk_enable_pba_module(SYSCLK_ADC);
	acc_init();

	LED_Off(LED0);
	LED_Off(LED1);
	LED_Off(LED2);
	LED_Off(LED3);
}

void ui_usb_mode_change(bool b_host_mode)
{
	LED_Off(LED0);
	LED_Off(LED1);
	LED_Off(LED2);
	LED_Off(LED3);
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
	if (b_vbus_present) {
		LED_On(LED0);
	} else {
		LED_Off(LED0);
	}
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
		b_btn_state = is_joystick_pressed();
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
	LED_On(LED1);
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
	bool b_btn_state;
	static bool btn_left_last_state = HID_MOUSE_BTN_UP;
	static bool btn_right_last_state = HID_MOUSE_BTN_UP;
	static bool btn_middle_last_state = HID_MOUSE_BTN_UP;
	uint8_t i;
	signed int val;
	struct cal_t {
		uint8_t angle;
		int8_t move;
	} calibration_acc[5] = {
		{40, 10 * MOUSE_MOVE_RANGE},
		{30, 6 * MOUSE_MOVE_RANGE},
		{20, 4 * MOUSE_MOVE_RANGE},
		{15, 2 * MOUSE_MOVE_RANGE},
		{10, 1 * MOUSE_MOVE_RANGE}};
	static uint8_t cpt_sof = 0;

	if (!ui_device_b_mouse_enable) {
		return;
	}

	framenumber = udd_get_frame_number();

	if ((framenumber % 1000) == 0) {
		LED_On(LED2);
	}
	if ((framenumber % 1000) == 500) {
		LED_Off(LED2);
	}
	// Scan process running each 40ms
	cpt_sof++;
	if (40 > cpt_sof) {
		return;
	}
	cpt_sof = 0;

	// Scan buttons on switch 0 (left), 1 (right), joystick_press (middle),
	b_btn_state = (!gpio_get_pin_value(GPIO_PUSH_BUTTON_0)) ?
			HID_MOUSE_BTN_DOWN : HID_MOUSE_BTN_UP;
	if (b_btn_state != btn_left_last_state) {
		udi_hid_mouse_btnleft(b_btn_state);
		btn_left_last_state = b_btn_state;
	}
	b_btn_state = (is_joystick_pressed())? HID_MOUSE_BTN_DOWN :
			HID_MOUSE_BTN_UP;
	if (b_btn_state != btn_middle_last_state) {
		udi_hid_mouse_btnmiddle(b_btn_state);
		btn_middle_last_state = b_btn_state;
	}
	b_btn_state = (!gpio_get_pin_value(GPIO_PUSH_BUTTON_1)) ?
			HID_MOUSE_BTN_DOWN : HID_MOUSE_BTN_UP;
	if (b_btn_state != btn_right_last_state) {
		udi_hid_mouse_btnright(b_btn_state);
		btn_right_last_state = b_btn_state;
	}
	// Look joystick activity for the Wheel events
	if (is_joystick_up()) {
		udi_hid_mouse_moveScroll(MOUSE_MOVE_RANGE);
	}
	if (is_joystick_down()) {
		udi_hid_mouse_moveScroll(-MOUSE_MOVE_RANGE);
	}

	// Look accelerometer activity for the X and Y events
	acc_update();	// Get accelerometer acquisition and process data
	for (i = 0; i < (sizeof(calibration_acc) / sizeof(struct cal_t)); i++) {
		val = is_acc_abs_angle_x(calibration_acc[i].angle);
		if (0 == val) {
			continue;
		}
		if (0 < val) {
			udi_hid_mouse_moveX(0 - calibration_acc[i].move);
		} else {
			udi_hid_mouse_moveX(calibration_acc[i].move);
		}
		break;
	}
	for (i = 0; i < (sizeof(calibration_acc) / sizeof(struct cal_t)); i++) {
		val = is_acc_abs_angle_y(calibration_acc[i].angle);
		if (0 == val) {
			continue;
		}
		if (0 < val) {
			udi_hid_mouse_moveY(0 - calibration_acc[i].move);
		} else {
			udi_hid_mouse_moveY(calibration_acc[i].move);
		}
		break;
	}
}
//! @}

/**
 * \defgroup UI User Interface
 *
 * Human interface on EVK1101 :
 * - PWR led is on when power present
 * - Led 0 is on in host mode (when USB OTG cable is pluged)
 * - device mode:
 *   - Led 1 is on when USB line is in IDLE mode, and off in SUSPEND mode
 *   - Led 2 blinks when USB host has checked and enabled HID mouse interface
 *   - Mouse buttons are linked to switch PB0 (left), PB1 (right), joystick press (middle)
 *   - Look accelerometer activity for the X and Y mouse events
 *   - Look joystick activity for the Wheel events
 *   - The PB0 and PB1 can be used to wakeup USB Host in remote wakeup mode
 * - host mode:
 *   - Led  is on when Vbus is present
 *   - Led 1 is continuously on when a device is connected
 *   - Led 1 blinks when the device is enumerated and USB in idle mode
 *   - Led 2 is on when a HID mouse button is pressed
 *   - Led 3 is on when the mouse move
 *   - Joystick press allows to enter the device in suspend mode with remote wakeup feature authorized
 *   - The PB0 and PB1 button can be used to wakeup the USB devices in suspend mode
 */
