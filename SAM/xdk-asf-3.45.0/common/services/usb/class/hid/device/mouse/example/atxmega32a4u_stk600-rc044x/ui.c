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

void ui_init(void)
{
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
	PORT_t *port;
	// Configure pin change interrupt for asynch. wake-up on button pin.
	ioport_configure_pin(GPIO_PUSH_BUTTON_0,
			IOPORT_DIR_INPUT | IOPORT_PULL_UP);
	ioport_configure_pin(GPIO_PUSH_BUTTON_1,
			IOPORT_DIR_INPUT | IOPORT_PULL_UP);
	ioport_configure_pin(GPIO_PUSH_BUTTON_2,
			IOPORT_DIR_INPUT | IOPORT_PULL_UP);
	ioport_configure_pin(GPIO_PUSH_BUTTON_3,
			IOPORT_DIR_INPUT | IOPORT_PULL_UP);
	port = ioport_pin_to_port(GPIO_PUSH_BUTTON_0);
	port->INT0MASK = 0x0F;
	port->INTCTRL = PORT_INT0LVL_LO_gc;
}

void ui_wakeup_disable(void)
{
	PORT_t *port;
	port = ioport_pin_to_port(GPIO_PUSH_BUTTON_0);
	port->INT0MASK = 0x00;
}


/*! \brief Interrupt on "pin change" from switch to do wakeup on USB
 * Callback running when USB Host enable mouse interface
 *
 * Note:
 * This interrupt is enable when the USB host enable remotewakeup feature
 * This interrupt wakeup the CPU if this one is in idle mode
 */
ISR(PORTB_INT0_vect)
{
	PORT_t *port;
	port = ioport_pin_to_port(GPIO_PUSH_BUTTON_0);
	port->INTFLAGS = 0x01; // Ack interrupt
	// It is a wakeup then send wakeup USB
	udc_remotewakeup();
}

void ui_wakeup(void)
{
	LED_On(LED0_GPIO);
}

void ui_process(uint16_t framenumber)
{
	static uint8_t cpt_sof = 0;

	if ((framenumber % 1000) == 0) {
		LED_On(LED1_GPIO);
	}
	if ((framenumber % 1000) == 500) {
		LED_Off(LED1_GPIO);
	}
	// Scan process running each 2ms
	cpt_sof++;
	if (2 > cpt_sof)
		return;
	cpt_sof = 0;
	// Scan move on switch 4 (right), 5 (left), 6 (down), 7 (up)
	if (gpio_pin_is_low(GPIO_PUSH_BUTTON_0))
		udi_hid_mouse_moveX(MOUSE_MOVE_RANGE);
	if (gpio_pin_is_low(GPIO_PUSH_BUTTON_1))
		udi_hid_mouse_moveX(-MOUSE_MOVE_RANGE);
	if (gpio_pin_is_low(GPIO_PUSH_BUTTON_2))
		udi_hid_mouse_moveY(MOUSE_MOVE_RANGE);
	if (gpio_pin_is_low(GPIO_PUSH_BUTTON_3))
		udi_hid_mouse_moveY(-MOUSE_MOVE_RANGE);
}

/**
 * \defgroup UI User Interface
 *
 * Human interface on STK600:
 * - Led 0 is on when USB line is in IDLE mode, and off in SUSPEND mode
 * - Led 1 blinks when USB host has checked and enabled HID mouse interface
 * - Mouse move are linked at switches 0 (right), 1 (left), 2 (down), 3 (up)
 * - Mouse buttons are not handle in this user interface example.
 * - The switches 0 to 3 can be used to wakeup USB Host in remote wakeup mode.
 *
 * Setup for STK600:
 * - LEDS connector is connected to PORTA
 * - SWITCHES are connected to PORTB
 * - Warning! The AREF0 jumper must be removed
 * because AREF0 connected on PORTA0 overrides led 0.
 * - Warning! The AREF1 jumper must be removed
 * because AREF1 connected on PORTB0 overrides switch 0.
 */
