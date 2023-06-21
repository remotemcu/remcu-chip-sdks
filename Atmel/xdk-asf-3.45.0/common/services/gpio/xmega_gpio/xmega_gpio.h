/**
 * \file
 *
 * \brief Common gpio data/structure for all AVR XMEGA implementations.
 *
 * Copyright (c) 2010-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _XMEGA_GPIO_H_
#define _XMEGA_GPIO_H_

#include "compiler.h"
#include "ioport.h"

#define gpio_pin_is_low(io_id) \
	ioport_pin_is_low(io_id)

#define gpio_pin_is_high(io_id) \
	ioport_pin_is_high(io_id)

#define gpio_set_pin_high(io_id) \
	ioport_set_value(io_id,1)

#define gpio_set_pin_low(io_id) \
	ioport_set_value(io_id,0)

#define gpio_toggle_pin(io_id) \
	ioport_toggle_pin(io_id)

#define gpio_configure_pin(io_id,io_flags) \
	ioport_configure_pin(io_id,io_flags)

#define gpio_configure_group(port_id,port_mask,io_flags) \
	ioport_configure_group(port_id,port_mask,io_flags)

#define gpio_set_pin_group_high(port_id,mask) \
	ioport_set_group_high(port_id,mask)

#define gpio_set_pin_group_low(port_id,mask) \
	ioport_set_group_low(port_id,mask)

#define gpio_toggle_pin_group(port_id,mask) \
	ioport_tgl_group(port_id,mask)

#endif  // _XMEGA_GPIO_H_
