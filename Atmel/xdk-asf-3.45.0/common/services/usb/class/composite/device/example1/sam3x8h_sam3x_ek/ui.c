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

#define  MOUSE_MOVE_RANGE  3

// Wakeup pin is RIGHT CLICK (fast wakeup 14)
#define  WAKEUP_PMC_FSTT (PMC_FSMR_FSTT14)
#define  WAKEUP_PIN      (GPIO_PUSH_BUTTON_2)
#define  WAKEUP_PIO      (PIN_PUSHBUTTON_2_PIO)
#define  WAKEUP_PIO_ID   (PIN_PUSHBUTTON_2_ID)
#define  WAKEUP_PIO_MASK (PIN_PUSHBUTTON_2_MASK)
#define  WAKEUP_PIO_ATTR (PIN_PUSHBUTTON_2_ATTR)

// Interrupt on "pin change" from RIGHT CLICK to do wakeup on USB
// Note:
// This interrupt is enable when the USB host enable remotewakeup feature
// This interrupt wakeup the CPU if this one is in idle mode
static void ui_wakeup_handler(uint32_t id, uint32_t mask)
{
	if (WAKEUP_PIO_ID == id && WAKEUP_PIO_MASK == mask) {
		// It is a wakeup then send wakeup USB
		udc_remotewakeup();
	}
}

void ui_init(void)
{
	// Enable PIO clock for button inputs
	pmc_enable_periph_clk(ID_PIOB);
	pmc_enable_periph_clk(ID_PIOE);
	// Set handler for wakeup
	pio_handler_set(WAKEUP_PIO, WAKEUP_PIO_ID, WAKEUP_PIO_MASK, WAKEUP_PIO_ATTR, ui_wakeup_handler);
	// Enable IRQ for button (PIOB)
	NVIC_EnableIRQ((IRQn_Type) WAKEUP_PIO_ID);
	// Initialize LEDs
	LED_On(LED0_GPIO);
	LED_Off(LED1_GPIO);
	LED_Off(LED2_GPIO);
}

void ui_powerdown(void)
{
	LED_Off(LED0_GPIO);
	LED_Off(LED1_GPIO);
	LED_Off(LED2_GPIO);
}


void ui_wakeup_enable(void)
{
	// Enable interrupt for button pin
	pio_configure_pin(WAKEUP_PIN, WAKEUP_PIO_ATTR);
	pio_enable_pin_interrupt(WAKEUP_PIN);
	// Enable fast wakeup for button pin
	pmc_set_fast_startup_input(WAKEUP_PMC_FSTT);
}

void ui_wakeup_disable(void)
{
	// Disable interrupt for button pin
	pio_disable_pin_interrupt(WAKEUP_PIN);
	// Disable fast wakeup for button pin
	pmc_clr_fast_startup_input(WAKEUP_PMC_FSTT);
}

void ui_wakeup(void)
{
	LED_On(LED0_GPIO);
}

void ui_process(uint16_t framenumber)
{
	static uint8_t cpt_sof = 0;

	if ((framenumber % 1000) == 0) {
		LED_On(LED0_GPIO);
	}
	if ((framenumber % 1000) == 500) {
		LED_Off(LED0_GPIO);
	}
	// Scan process running each 2ms
	cpt_sof++;
	if (cpt_sof < 2) {
		return;
	}
	cpt_sof = 0;

	// Uses buttons to move mouse
	if (!gpio_pin_is_high(GPIO_PUSH_BUTTON_1)) {
		udi_hid_mouse_moveX(-MOUSE_MOVE_RANGE);
	}
	if (!gpio_pin_is_high(GPIO_PUSH_BUTTON_2)) {
		udi_hid_mouse_moveX( MOUSE_MOVE_RANGE);
	}
}

void ui_start_read(void)
{
	LED_On(LED1_GPIO);
}

void ui_stop_read(void)
{
	LED_Off(LED1_GPIO);
}

void ui_start_write(void)
{
	LED_On(LED2_GPIO);
}

void ui_stop_write(void)
{
	LED_Off(LED2_GPIO);
}


/**
 * \defgroup UI User Interface
 *
 * Human interface on SAM3X-EK:
 * - Led 0 (D2, blue) blinks when USB host has checked and enabled HID and MSC interface
 * - Led 1 (D3, green) is on during read operation
 * - Led 2 (D4, amber) is on during write operation
 * - LEFT CLICK (BP5) and RIGHT CLICK (BP4) are used to move mouse left and right
 * - RIGHT CLICK (BP4) can be used to wakeup USB Host in remote wakeup mode.
 *
 */
