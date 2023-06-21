/**
 * \file
 *
 * \brief Resistive touch service settings for the ADS7843 controller.
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

#ifndef RTOUCH_ADS7843_H_INCLUDED
#define RTOUCH_ADS7843_H_INCLUDED

#include "ads7843.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \ingroup sam_services_rtouch_group
 * \defgroup sam_services_rtouch_ads7843_group ADS7843 Touch Controller
 *
 * This is hardware specific configuration that configures the resistive touch 
 * service for use with the ADS7843 touch controller. All the functionalities 
 * in this configuration are provided by the \ref sam_component_ads7843_group 
 * driver.
 *
 * @{
 */

/**
 * ADS7843 touch driver specific function, see
 * \ref ads7843_is_pressed
 */
#define rtouch_is_pressed()                    ads7843_is_pressed()

/**
 * ADS7843 touch driver specific function, see
 * \ref ads7843_set_handler
 */
#define rtouch_set_handler(p_handler)          ads7843_set_handler(p_handler)

/**
 * ADS7843 touch driver specific function, see
 * \ref ads7843_enable_interrupt
 */
#define rtouch_enable_interrupt()              ads7843_enable_interrupt()

/**
 * ADS7843 touch driver specific function, see
 * \ref ads7843_disable_interrupt
 */
#define rtouch_disable_interrupt()             ads7843_disable_interrupt()

/**
 * ADS7843 touch driver specific function, see
 * \ref ads7843_get_raw_point
 */
#define rtouch_get_raw_point(p_x, p_y)         ads7843_get_raw_point(p_x, p_y)

/**
 * ADS7843 touch driver specific function, see
 * \ref ads7843_init
 */
#define rtouch_init_device()                   ads7843_init()

//@}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

#endif /* RTOUCH_ADS7843_H_INCLUDED */
