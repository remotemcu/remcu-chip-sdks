/**
 * \file
 *
 * \brief PARC unit test configuration.
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

#ifndef CONF_TEST_H_INCLUDED
#define CONF_TEST_H_INCLUDED

#include "conf_board.h"
#include "conf_clock.h"

#define PIN_PCCK                   PIN_PA06
#define DATA_MASK                  0xDF

static inline void parc_port_source_simulation_config(void)
{
	ioport_set_pin_dir(PIN_PA06, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIN_PA06, IOPORT_PIN_LEVEL_HIGH);
	ioport_set_pin_dir(PIN_PC00, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIN_PC00, IOPORT_PIN_LEVEL_HIGH);
	ioport_set_pin_dir(PIN_PC01, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIN_PC01, IOPORT_PIN_LEVEL_HIGH);
	ioport_set_pin_dir(PIN_PC02, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIN_PC02, IOPORT_PIN_LEVEL_HIGH);
	ioport_set_pin_dir(PIN_PC03, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIN_PC03, IOPORT_PIN_LEVEL_HIGH);
	ioport_set_pin_dir(PIN_PC04, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIN_PC04, IOPORT_PIN_LEVEL_HIGH);
	ioport_set_pin_dir(PIN_PC05, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIN_PC05, IOPORT_PIN_LEVEL_HIGH);
	ioport_set_pin_dir(PIN_PC06, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIN_PC06, IOPORT_PIN_LEVEL_HIGH);
	ioport_set_pin_dir(PIN_PC17, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIN_PC17, IOPORT_PIN_LEVEL_HIGH);
	ioport_set_pin_dir(PIN_PC18, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIN_PC18, IOPORT_PIN_LEVEL_HIGH);
}

/**
 * \brief Place data (a byte) on GPIO port.
 *
 * * \param data   GPIO output simulation data for PARC capture.
 */
static inline void place_data_to_port(uint32_t data)
{
	ioport_pin_t pin;

	for (int32_t i = 0;i < 8; i++) {
		pin = PIN_PC00 + i;
		if (pin == PIN_PC05) {
			data = data >> 1;
		}
		if (data & 0x01) {
			ioport_set_pin_level(pin,IOPORT_PIN_LEVEL_HIGH);
		} else {
			ioport_set_pin_level(pin,IOPORT_PIN_LEVEL_LOW);
		}
		data = data >> 1;
	}
}
#endif /* CONF_TEST_H_INCLUDED */

