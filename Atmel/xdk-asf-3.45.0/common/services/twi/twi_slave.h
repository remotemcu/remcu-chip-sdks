/**
 * \file
 *
 * \brief TWI Slave Mode management
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
#ifndef TWI_SLAVE_H_INCLUDED
#define TWI_SLAVE_H_INCLUDED

#include <parts.h>
#include <compiler.h>

#if (SAM3S || SAM3U || SAM3N || SAM3XA || SAM4S || SAM4E || SAM4N || SAM4C || SAM4CM || SAMG || SAM4CP)
# include "sam_twi/twi_slave.h"
#elif XMEGA
# include "xmega_twi/twi_slave.h"
#elif MEGA_RF
# include "megarf_twi/twi_slave.h"
#elif (defined(__GNUC__) && defined(__AVR32__)) || (defined(__ICCAVR32__) || defined(__AAVR32__))
#if (defined AVR32_TWI)
#error Not supported.
#endif
#else
# error Unsupported chip type
#endif

/**
 *
 * \defgroup twi_group Two Wire-interface(TWI)
 *
 * This is the common API for TWIs. Additional features are available
 * in the documentation of the specific modules.
 *
 * \section twi_group_platform Platform Dependencies
 *
 * The twi API is partially chip- or platform-specific. While all
 * platforms provide mostly the same functionality, there are some
 * variations around how different bus types and clock tree structures
 * are handled.
 *
 * The following functions are available on all platforms, but there may
 * be variations in the function signature (i.e. parameters) and
 * behaviour. These functions are typically called by platform-specific
 * parts of drivers, and applications that aren't intended to be
 * portable:
 *   - twi_slave_setup()
 *   - twi_slave_enable()
 *   - twi_slave_disable()
 *   - twi_slave_read()
 *   - twi_slave_write()
 *
 * @{
 */

/**
 * \typedef twi_slave_t
 * This type can be used independently to refer to TWI slave module for the
 * architecture used. It refers to the correct type definition for the
 * architecture, ie. TWI_t* for XMEGA or avr32_twi_t* for UC3
 */

//! @}

#endif /* TWI_SLAVE_H_INCLUDED */
