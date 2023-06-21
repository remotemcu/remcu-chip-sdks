/**
 * \file
 *
 * \brief TWIHS Slave driver for SAM.
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef TWIHS_SLAVE_H_INCLUDED
#define TWIHS_SLAVE_H_INCLUDED

#include "twihs.h"
#include "sysclk.h"

typedef Twihs *twihs_slave_t;

static inline void twihs_slave_setup(twihs_slave_t p_twihs, uint32_t dw_device_addr)
{
#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
	if (p_twihs == TWIHS0) {
		sysclk_enable_peripheral_clock(ID_TWIHS0);
	} else if (p_twihs == TWIHS1) {
		sysclk_enable_peripheral_clock(ID_TWIHS1);
	} else if (p_twihs == TWIHS2) {
		sysclk_enable_peripheral_clock(ID_TWIHS2);
	} else {
		// Do Nothing
	}
#else
	if (p_twihs == TWI0) {
		sysclk_enable_peripheral_clock(ID_TWI0);
#if SAMG55		
	} else if (p_twihs == TWI1) {
		sysclk_enable_peripheral_clock(ID_TWI1);
	} else if (p_twihs == TWI2) {
		sysclk_enable_peripheral_clock(ID_TWI2);
	} else if (p_twihs == TWI3) {
		sysclk_enable_peripheral_clock(ID_TWI3);
	} else if (p_twihs == TWI4) {
		sysclk_enable_peripheral_clock(ID_TWI4);
	} else if (p_twihs == TWI5) {
		sysclk_enable_peripheral_clock(ID_TWI5);
	} else if (p_twihs == TWI6) {
		sysclk_enable_peripheral_clock(ID_TWI6);
	} else if (p_twihs == TWI7) {
		sysclk_enable_peripheral_clock(ID_TWI7);
#endif		
	} else {
		// Do Nothing
	}
#endif
	twihs_slave_init(p_twihs, dw_device_addr);
}

#define twihs_slave_enable(p_twihs)  twihs_enable_slave_mode(p_twihs)

#define twihs_slave_disable(p_twihs)  twihs_disable_slave_mode(p_twihs)

#endif /* TWIHS_SLAVE_H_INCLUDED */
