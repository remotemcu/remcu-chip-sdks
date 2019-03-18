/**
 * \file
 *
 * \brief TWIHS Slave Mode management
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

#include <parts.h>
#include <compiler.h>

#if (SAMG || SAMV70 || SAMV71 || SAME70 || SAMS70)
# include "sam_twihs/twihs_slave.h"
#else
# error Unsupported chip type
#endif

/**
 *
 * \defgroup twihs_group Two Wire-interface High Speed(TWIHS)
 *
 * This is the common API for TWIHS. Additional features are available
 * in the documentation of the specific modules.
 *
 * \section twihs_group_platform Platform Dependencies
 *
 * The twihs API is partially chip- or platform-specific. While all
 * platforms provide mostly the same functionality, there are some
 * variations around how different bus types and clock tree structures
 * are handled.
 *
 * The following functions are available on all platforms, but there may
 * be variations in the function signature (i.e. parameters) and
 * behaviour. These functions are typically called by platform-specific
 * parts of drivers, and applications that aren't intended to be
 * portable:
 *   - twihs_slave_setup()
 *   - twihs_slave_enable()
 *   - twihs_slave_disable()
 *   - twihs_slave_read()
 *   - twihs_slave_write()
 *
 * @{
 */

/**
 * \typedef twihs_slave_t
 * This type can be used independently to refer to TWIHS slave module for the
 * architecture used.
 */

//! @}

#endif /* TWIHS_SLAVE_H_INCLUDED */
