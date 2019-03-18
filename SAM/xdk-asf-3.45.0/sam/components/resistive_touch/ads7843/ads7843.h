/**
 * \file
 *
 * \brief API driver for component ADS7843.
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

#ifndef ADS7843_H_INCLUDED
#define ADS7843_H_INCLUDED

#include "compiler.h"

/** @cond 0*/
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/** @endcond*/

/**
 * \defgroup sam_component_ads7843_group Resistive Touch - ADS7843 Controller
 *
 * Low-level driver for the ADS7843 touch controller. This driver provides
 * access to the main features of the ADS7843 controller.
 *
 * \{
 */

/**
 * \brief Return the touch screen status, pressed or not.
 *
 * \return 1 if the touchscreen is pressed, 0 otherwise.
 */
uint32_t ads7843_is_pressed(void);

/**
 * \brief Set the touch interrupt handler.
 *
 * \note This handler will be called whenever a touch event is detected by the
 * ADS7843 controller.
 *
 * \param p_handler Interrupt handler function pointer.
 */
void ads7843_set_handler(void (*p_handler) (uint32_t, uint32_t));

/**
 * \brief Enable interrupts on touch event.
 */
void ads7843_enable_interrupt(void);

/**
 * \brief Disable interrupts on touch event.
 */
void ads7843_disable_interrupt(void);

/**
 * \brief Get the touch raw coordinates.
 *
 * \param p_x Pointer to an integer representing the X value.
 * \param p_y Pointer to an integer representing the Y value.
 */
void ads7843_get_raw_point(uint32_t *p_x, uint32_t *p_y);

/**
 * \brief Initialize the SPI communication with the ADS7843 controller.
 */
uint32_t ads7843_init(void);

/**@}*/

/** @cond 0*/
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/** @endcond*/

#endif /* ADS7843_H_INCLUDED */
