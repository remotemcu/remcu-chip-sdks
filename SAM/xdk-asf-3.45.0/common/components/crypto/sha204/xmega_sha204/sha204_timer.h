/*
 * \file
 *
 * \brief XMEGA-A1-XPLAINED header file for timer utility functions.
 *
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

#ifndef SHA204_TIMER_H
#   define SHA204_TIMER_H

#include <compiler.h>               //!< compiler dependent definitions

//! true if timeout timer has expired
extern volatile bool sha204_timer_expired;
/**
 * \defgroup sha204_timer_group SHA204 Service - timer functions
 *
 * code example to use the timeout timer:
   sha204_start_timeout_timer_ms(timeout);
   bool status = false;
   do {
	 status = try_your_thing();
   } while ((sha204_timer expired == false) && (status == false));
 * @{
 */
void sha204h_timer_init(void);
void sha204h_start_timer(uint16_t delay, uint8_t is_blocking);
void sha204h_delay_ms(uint16_t delay);
void sha204h_start_timeout_timer_ms(uint16_t timeout);
//! @}

#endif
