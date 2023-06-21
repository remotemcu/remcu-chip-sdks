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
#define  MOUSE_MOVE_COUNT  50

#define  MOVE_UP     0
#define  MOVE_RIGHT  1
#define  MOVE_DOWN   2
#define  MOVE_LEFT   3

// Wakeup pin is PA15 (fast wakeup 14)
#define  WAKEUP_PMC_FSTT (PMC_FSMR_FSTT14)
#define  WAKEUP_PIN      (PIO_PA15_IDX)
#define  WAKEUP_PIO      (PIOA)
#define  WAKEUP_PIO_ID   (ID_PIOA)
#define  WAKEUP_PIO_MASK (PIO_PA15)
#define  WAKEUP_PIO_ATTR (PIO_INPUT | PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_LOW_LEVEL)

static uint8_t move_dir = MOVE_UP;
static int32_t move_count = MOUSE_MOVE_COUNT;

// Interrupt on "pin change" from PA15 to do wakeup on USB
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
	pmc_enable_periph_clk(ID_PIOA);
	pmc_enable_periph_clk(ID_PIOB);
	pmc_enable_periph_clk(ID_PIOC);
	// Set handler for PA15
	pio_handler_set(WAKEUP_PIO, WAKEUP_PIO_ID, WAKEUP_PIO_MASK, WAKEUP_PIO_ATTR, ui_wakeup_handler);
	// Enable IRQ for button (PIOA)
	NVIC_EnableIRQ((IRQn_Type) WAKEUP_PIO_ID);
	// Initialize LEDs
	LED_On(LED0_GPIO);
	LED_Off(LED1_GPIO);
}

void ui_powerdown(void)
{
	LED_Off(LED0_GPIO);
	LED_Off(LED1_GPIO);
}


void ui_wakeup_enable(void)
{
	// Configure PA15 as PIO input
	pio_configure_pin(WAKEUP_PIN, WAKEUP_PIO_ATTR);
	// Enable interrupt for PA15
	pio_enable_pin_interrupt(WAKEUP_PIN);
	// Enable fast wakeup for button pin (WKUP14 for PA15)
	pmc_set_fast_startup_input(WAKEUP_PMC_FSTT);
}

void ui_wakeup_disable(void)
{
	// Disable interrupt for button pin
	pio_disable_pin_interrupt(WAKEUP_PIN);
	// Disable fast wakeup for button pin (WKUP14 for PA15)
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
		move_count --;
		switch(move_dir) {
		case MOVE_UP:
			udi_hid_mouse_moveY(-MOUSE_MOVE_RANGE);
			if (move_count < 0) {
				move_dir = MOVE_RIGHT;
				move_count = MOUSE_MOVE_COUNT;
			}
			break;
		case MOVE_RIGHT:
			udi_hid_mouse_moveX(+MOUSE_MOVE_RANGE);
			if (move_count < 0) {
				move_dir = MOVE_DOWN;
				move_count = MOUSE_MOVE_COUNT;
			}
			break;
		case MOVE_DOWN:
			udi_hid_mouse_moveY(+MOUSE_MOVE_RANGE);
			if (move_count < 0) {
				move_dir = MOVE_LEFT;
				move_count = MOUSE_MOVE_COUNT;
			}
			break;
		case MOVE_LEFT:
			udi_hid_mouse_moveX(-MOUSE_MOVE_RANGE);
			if (move_count < 0) {
				move_dir = MOVE_UP;
				move_count = MOUSE_MOVE_COUNT;
			}
			break;
		}
	}
}

/**
 * \defgroup UI User Interface
 *
 * Human interface on SAM4S-Xplained:
 * - LED D9 blinks when USB host has checked and enabled HID Mouse interface
 * - No mouse buttons are linked
 * - SW1(BOARD REV A) or BP2(BOARD REV B) is used to move mouse around
 * - Only a low level on J13.PA15 will generate a wakeup to USB Host in remote wakeup mode.
 *
 */
