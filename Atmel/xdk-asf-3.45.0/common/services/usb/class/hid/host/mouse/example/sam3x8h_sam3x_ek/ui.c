/**
 * \file
 *
 * \brief User Interface
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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

/* Wakeup pin is RIGHT CLICK (fast wakeup 14) */
#define  RESUME_PMC_FSTT (PMC_FSMR_FSTT14)
#define  RESUME_PIN      (GPIO_PUSH_BUTTON_2)
#define  RESUME_PIO      (PIN_PUSHBUTTON_2_PIO)
#define  RESUME_PIO_ID   (PIN_PUSHBUTTON_2_ID)
#define  RESUME_PIO_MASK (PIN_PUSHBUTTON_2_MASK)
#define  RESUME_PIO_ATTR (PIN_PUSHBUTTON_2_ATTR)

/**
 * \name Internal routines to manage asynchronous interrupt pin change
 * This interrupt is connected to a switch and allows to wakeup CPU in low sleep
 * mode.
 * This wakeup the USB devices connected via a downstream resume.
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
		if (uhc_is_suspend()) {
			ui_disable_asynchronous_interrupt();

			/* Wakeup host and device */
			pmc_wait_wakeup_clocks_restore(uhc_resume);
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
	LED_Off(LED0_GPIO);
	LED_Off(LED1_GPIO);
	LED_Off(LED2_GPIO);
	LED_Off(LED3_GPIO);
}

void ui_usb_mode_change(bool b_host_mode)
{
	(void)b_host_mode;
	ui_init();
}

/*! @} */

/**
 * \name Host mode user interface functions
 * @{
 */

/*! Status of device enumeration */
static uhc_enum_status_t ui_enum_status = UHC_ENUM_DISCONNECT;
/*! Blink frequency depending on device speed */
static uint16_t ui_device_speed_blink;
/*! Manages device mouse moving */
static int8_t ui_x, ui_y, ui_scroll;

void ui_usb_vbus_change(bool b_vbus_present)
{
	if (b_vbus_present) {
		LED_On(LED3_GPIO);
	} else {
		LED_Off(LED3_GPIO);
	}
}

void ui_usb_vbus_error(void)
{
}

void ui_usb_connection_event(uhc_device_t *dev, bool b_present)
{
	(void)dev;
	if (b_present) {
		LED_On(LED1_GPIO);
	} else {
		LED_Off(LED1_GPIO);
		ui_enum_status = UHC_ENUM_DISCONNECT;
	}
}

void ui_usb_enum_event(uhc_device_t *dev, uhc_enum_status_t status)
{
	(void)dev;
	ui_enum_status = status;
	if (ui_enum_status == UHC_ENUM_SUCCESS) {
		ui_x = 0, ui_y = 0, ui_scroll = 0;
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
	}
}

void ui_usb_wakeup_event(void)
{
	ui_disable_asynchronous_interrupt();
}

void ui_usb_sof_event(void)
{
	bool b_btn_state;
	static bool btn_suspend_and_remotewakeup = false;
	static uint16_t counter_sof = 0;

	if (ui_enum_status == UHC_ENUM_SUCCESS) {
		/* Display device enumerated and in active mode */
		if (++counter_sof > ui_device_speed_blink) {
			counter_sof = 0;
			LED_Toggle(LED1_GPIO);
		}

		/* Scan button to enter in suspend mode and remote wakeup */
		b_btn_state = (!gpio_pin_is_high(GPIO_PUSH_BUTTON_1)) ?
				true : false;
		if (b_btn_state != btn_suspend_and_remotewakeup) {
			/* Button have changed */
			btn_suspend_and_remotewakeup = b_btn_state;
			if (b_btn_state) {
				/* Button has been pressed */
				LED_Off(LED1_GPIO);
				LED_Off(LED2_GPIO);
				ui_enable_asynchronous_interrupt();
				uhc_suspend(true);
				return;
			}
		}

		/* Power on a LED when the mouse move */
		if (!ui_x && !ui_y && !ui_scroll) {
			LED_Off(LED0_GPIO);
		} else {
			ui_x = ui_y = ui_scroll = 0;
			LED_On(LED0_GPIO);
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
		LED_On(LED2_GPIO);
	} else {
		LED_Off(LED2_GPIO);
	}
}

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
	ui_x = x;
	ui_y = y;
	ui_scroll = scroll;
}

/*! @} */

/**
 * \defgroup UI User Interface
 *
 * Human interface on SAM3X-EK :
 * - Led 3 (D5, red) is on when Vbus is generated
 * - Led 1 (D4, green) is continuously on when a device is connected
 * - Led 1 blinks when a HID mouse is enumerated and USB in idle mode
 *   - The blink is slow (1s) with low speed device
 *   - The blink is normal (0.5s) with full speed device
 *   - The blink is fast (0.25s) with high speed device
 * - Led 2 (D3, amber) is on when a HID mouse button is pressed
 * - Led 0 (D2, blue) is on when the mouse move
 * - LEFT CLICK (BP5) allows to enter the device in suspend mode with remote
 *   wakeup feature authorized
 * - Only RIGHT CLICK (BP4) can be used to wakeup USB device in suspend mode
 */
