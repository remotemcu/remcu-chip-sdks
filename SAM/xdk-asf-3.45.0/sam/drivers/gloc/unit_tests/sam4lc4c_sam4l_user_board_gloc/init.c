/**
 * \file
 *
 * \brief SAM4L User Board init.
 *
 * This file contains board initialization function.
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
#include "compiler.h"
#include "conf_board.h"
#include "ioport.h"
#include "board.h"

/**
 * \brief Set peripheral mode for one single IOPORT pin.
 * It will configure port mode and disable pin mode (but enable peripheral).
 * \param pin IOPORT pin to configure
 * \param mode Mode masks to configure for the specified pin (\ref ioport_modes)
 */
#define ioport_set_pin_peripheral_mode(pin, mode) \
	do {\
		ioport_set_pin_mode(pin, mode);\
		ioport_disable_pin(pin);\
	} while (0)

void board_init(void)
{
	// Initialize IOPORTs
	ioport_init();

	// Put all pins to default state (input & pull-up)
	uint32_t pin;

	for (pin = PIN_PA00; pin <= PIN_PC31; pin ++) {
		ioport_set_pin_dir(pin, IOPORT_DIR_INPUT);
		ioport_set_pin_mode(pin, IOPORT_MODE_PULLUP);
	}

#if defined (CONF_BOARD_COM_PORT)
	ioport_set_pin_peripheral_mode(COM_PORT_RX_PIN, COM_PORT_RX_MUX);
	ioport_set_pin_peripheral_mode(COM_PORT_TX_PIN, COM_PORT_TX_MUX);
#endif

#ifdef CONF_BOARD_GLOC_LUT0_PORT
	ioport_set_pin_peripheral_mode(PIN_PA20D_GLOC_IN0, MUX_PA20D_GLOC_IN0);
	ioport_set_pin_peripheral_mode(PIN_PA21D_GLOC_IN1, MUX_PA21D_GLOC_IN1);
	ioport_set_pin_peripheral_mode(PIN_PA22D_GLOC_IN2, MUX_PA22D_GLOC_IN2);
	ioport_set_pin_peripheral_mode(PIN_PA07D_GLOC_IN3, MUX_PA07D_GLOC_IN3);
	ioport_set_pin_peripheral_mode(PIN_PA24D_GLOC_OUT0, MUX_PA24D_GLOC_OUT0);
#endif
}