/**
 * \file
 *
 * \brief SAM4S Xplained Pro LEDs support package.
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

#ifndef _LED_H_
#define _LED_H_

#include "gpio.h"

/**
 * \brief Turns off the specified LEDs.
 *
 * \param led LED to turn off (LEDx).
 *
 * \note The pins of the specified LEDs are set to GPIO output mode.
 */
#define LED_Off(led)     ioport_set_pin_level(led, IOPORT_PIN_LEVEL_HIGH)

/**
 * \brief Turns on the specified LEDs.
 *
 * \param led LED to turn on (LEDx).
 *
 * \note The pins of the specified LEDs are set to GPIO output mode.
 */
#define LED_On(led)      ioport_set_pin_level(led, IOPORT_PIN_LEVEL_LOW)

/**
 * \brief Toggles the specified LEDs.
 *
 * \param led LED to toggle (LEDx).
 *
 * \note The pins of the specified LEDs are set to GPIO output mode.
 */
#define LED_Toggle(led)  ioport_toggle_pin_level(led)

#endif  // _LED_H_
