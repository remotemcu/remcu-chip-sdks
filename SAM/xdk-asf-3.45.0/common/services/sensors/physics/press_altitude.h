/**
 * \file
 *
 * \brief Utilities that convert pressure to altitude
 *
 * This is a collection of high-level utility functions that will convert a
 * given pressure to an altitude within the Earth's atmosphere using the
 * International Standard Atmosphere (ISA) model.  The ISA is an ideal model
 * of how pressure, temperature, density, and viscosity of the atmosphere
 * change with altitude.  The basic pressure_altitude_xxx() routines implement
 * ISA equations in a fairly straightforward fashion without additional
 * constraints.  For example, the temperature decrease with altitude (lapse
 * rate) is approximately -6.5 degrees Celsius per 1000 meters for standard
 * atmosphere, but the actual rate varies from day to day and throughout the
 * day.
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

#ifndef _SENSOR_PRESSURE_ALTITUDE_H_
#define _SENSOR_PRESSURE_ALTITUDE_H_

#include "physics.h"

/*! \brief Specify the (corrected) pressure-altitude sea level pressure.
 *
 * This routine will calculate a bias to correct the ISA standard pressure
 * at sea level (1 atm. = 101 325 Pa) for local variations in barometric
 * pressure at mean sea level (MSL).
 *
 * \param   P           The current local pressure (pascals) at sea level.
 * \return  Nothing.
 */
extern void   pressure_sea_level(scalar P = CONST_STANDARD_ATM);

/*! \brief Specify a pressure-altitude layer
 *
 * The routine sets the pressure_altitude() function to use a specified
 * "layer" in domain [0, 6].  By default layer 0 is assumed.  Calling
 * this routine without arguments will set the pressure_altitude() to
 * calculate barometric altitude assuming a pressure domain within ISA
 * layer zero (P < 22 632 pascals).
 *
 * \param   index   The atmospheric layer index, zero by default.
 *
 * \return  bool    True if a valid layer index is specified.
 */
extern bool   pressure_isa_layer(int index = 0);

/*! \brief Get an ISA pressure altitude
 *
 * Given atmospheric pressure "P" in pascals, this routine returns the
 * associated barometric altitude ("pressure altitude") using
 * International Standard Atmosphere (ISA) pressure model coefficients
 * and equations.
 *
 * \param   P       The current atmospheric pressure in pascals.
 *
 * \return  scalar  The altitude in meters.
 */
extern scalar pressure_altitude(scalar P);

#endif
