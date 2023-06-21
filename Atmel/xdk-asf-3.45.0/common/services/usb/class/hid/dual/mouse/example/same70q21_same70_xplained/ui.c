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
#include "conf_board.h"
#include "conf_usb_host.h"
#include "conf_usb.h"

/* Wakeup pin is SW0 (fast wakeup 14) */
#define  RESUME_PMC_FSTT (PMC_FSMR_FSTT14)
#define  RESUME_PIN      (GPIO_PUSH_BUTTON_1)
#define  RESUME_PIO      (PIN_PUSHBUTTON_1_PIO)
#define  RESUME_PIO_ID   (PIN_PUSHBUTTON_1_ID)
#define  RESUME_PIO_MASK (PIN_PUSHBUTTON_1_MASK)
#define  RESUME_PIO_ATTR (PIN_PUSHBUTTON_1_ATTR)

/*! Current USB mode */
static bool ui_b_host_mode = false;

/**
 * \name Internal routines to manage asynchronous interrupt pin change
 * This interrupt is connected to a switch and allows to wakeup CPU in low sleep
 * mode.
 * In USB device mode, this wakeup the USB host via a upstream resume.
 * In USB host mode, this wakeup the USB devices connected via a downstream
 * resume.
 * @{
 */
static void ui_enable_asynchronous_interrupt(void);
static void ui_disable_asynchronous_interrupt(void);

/* Interrupt on "pin change" from RIGHT CLICK to do wakeup on USB
 *  Note:
 *  This interrupt is enable when the USB host enable remotewakeup feature
 *  This interrupt wakeup the CPU if this one is in idle mode */
static void ui_wakeup_handler(uint32_t id, uint32_t mask)
{
	if (RESUME_PIO_ID == id && RESUME_PIO_MASK == mask) {
		if (ui_b_host_mode) {
			if (!uhc_is_suspend()) {
				/* USB is not in suspend mode
				 *  Let's interrupt enable. */
				return;
			}

			ui_disable_asynchronous_interrupt();

			/* Wakeup the devices connected */
			pmc_wait_wakeup_clocks_restore(uhc_resume);
		} else {
			/* In device mode, wakeup the USB host. */
			pmc_wait_wakeup_clocks_restore(udc_remotewakeup);
		}
	}
}

/**
 * \brief Initializes and enables interrupt pin change
 */
static void ui_enable_asynchronous_interrupt(void)
{
	/* Enable interrupt for button pin */
	pio_get_interrupt_status(RESUME_PIO);
	pio_enable_pin_interrupt(RESUME_PIN);
	/* Enable fast wakeup for button pin */
	pmc_set_fast_startup_input(RESUME_PMC_FSTT);
}

/**
 * \brief Disables interrupt pin change
 */
static void ui_disable_asynchronous_interrupt(void)
{
	/* Disable interrupt for button pin */
	pio_disable_pin_interrupt(RESUME_PIN);
	pio_get_interrupt_status(RESUME_PIO);
	/* Enable fast wakeup for button pin */
	pmc_clr_fast_startup_input(RESUME_PMC_FSTT);
}

/*! @} */

/**
 * \name Main user interface functions
 * @{
 */
void ui_init(void)
{
	/* Enable PIO clock for button inputs */
	pmc_enable_periph_clk(RESUME_PIO_ID);
	pmc_enable_periph_clk(ID_PIOE);
	/* Set handler for wakeup */
	pio_handler_set(RESUME_PIO, RESUME_PIO_ID, RESUME_PIO_MASK,
			RESUME_PIO_ATTR, ui_wakeup_handler);
	/* Enable IRQ for button (PIOB) */
	NVIC_EnableIRQ((IRQn_Type)RESUME_PIO_ID);
	pio_configure_pin(RESUME_PIN, RESUME_PIO_ATTR);

	/* Initialize LEDs */
	LED_Off(LED0);
}

void ui_usb_mode_change(bool b_host_mode)
{
	ui_init();
	ui_b_host_mode = b_host_mode;
}

/*! @} */

/**
 * \name Host mode user interface functions
 * @{
 */

/*! Status of device enumeration */
static uhc_enum_status_t ui_host_enum_status = UHC_ENUM_DISCONNECT;
/*! Manages device mouse moving */
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
	(void)dev;
	if (b_present) {
		
	} else {
		ui_host_enum_status = UHC_ENUM_DISCONNECT;
	}
}

void ui_host_enum_event(uhc_device_t *dev, uhc_enum_status_t status)
{
	(void)dev;
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
	static uint16_t counter_sof = 0;

	if (ui_host_enum_status == UHC_ENUM_SUCCESS) {
		/* Display device enumerated and in active mode */
		if (++counter_sof == 500) {
			counter_sof = 0;
			LED_Toggle(LED0);
		}

		/* Scan button to enter in suspend mode and remote wakeup */
		b_btn_state = (!gpio_pin_is_high(GPIO_PUSH_BUTTON_1)) ?
				true : false;
		if (b_btn_state != btn_suspend_and_remotewakeup) {
			/* Button have changed */
			btn_suspend_and_remotewakeup = b_btn_state;
			if (b_btn_state) {
				/* Button has been pressed */
				LED_Off(LED0);
				ui_enable_asynchronous_interrupt();
				uhc_suspend(true);
				return;
			}
		}

		/* Power on a LED when the mouse move */
		if (!ui_host_x && !ui_host_y && !ui_host_scroll) {
			
		} else {
			ui_host_x = ui_host_y = ui_host_scroll = 0;
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
		
	} else {
		
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

void ui_host_hid_mouse_move(int8_t x, int8_t y, int8_t scroll)
{
	ui_host_x = x;
	ui_host_y = y;
	ui_host_scroll = scroll;
}

/*! @} */

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

	if (!ui_device_b_mouse_enable) {
		return;
	}

	framenumber = udd_get_frame_number();
	if ((framenumber % 1000) == 0) {
		LED_On(LED0);
	}

	if ((framenumber % 1000) == 500) {
		LED_Off(LED0);
	}

	/* Scan process running each 2ms */
	cpt_sof++;
	if (2 > cpt_sof) {
		return;
	}

	cpt_sof = 0;

	/* Look touch sensor activity for the X and Y events */
	if (!gpio_pin_is_high(GPIO_PUSH_BUTTON_1)) {
		udi_hid_mouse_moveX(-MOUSE_MOVE_RANGE);
	}
}

/*! @} */

/**
 * \defgroup UI User Interface
 *
 * Human interface on SAME70-Xplained:
 * - device mode:
 *   - Led 0 blinks when USB Host have checked and enabled HID mouse
 *     interface
 *   - Mouse buttons are not linked.
 *   - The SW0 are used to move mouse on the axis X.
 * - host mode:
 *   - Led 0 blinks when the device is enumerated and USB in idle mode
 * - SW0 allows to enter the device in suspend mode with remote
 *   wakeup feature authorized
 * - Only SW0 can be used to wakeup USB device in suspend mode
 */
