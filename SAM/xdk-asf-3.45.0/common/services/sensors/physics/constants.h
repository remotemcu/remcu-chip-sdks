/**
 * \file
 *
 * \brief ASF Sensor API Physics Constants
 *
 * This module defines commonly used physical constants and conversions in
 * standard units.
 *
 * \todo
 *
 * Investigate replacing numerical library, including constants in this
 * header, with the GNU Scientific Library (GSL) and select pieces of the
 * Boost C++ math and numerics libraries for feature rich application layer
 * code.
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

#ifndef _SENSOR_CONSTANTS_H_
#define _SENSOR_CONSTANTS_H_

#ifdef __cplusplus
extern "C" {
#endif

/** \name Physical Constants */
/** @{ */

/** \brief molar mass of dry air \f$\frac{kg}{mol}\f$ */
#define CONST_AIR_MOLAR_MASS    (0.0289644)

/** \brief Boltzmann constant \f$\frac{m^{2} kg}{s^{2} K}\f$ */
#define CONST_BOLTZMANN         (1.2806503e-23)

/** \brief standard atmospheric pressure \f$\frac{N}{m^{2}}\f$ */
#define CONST_STANDARD_ATM      (1.01325e5)

/** \brief dry atmospheric air gas constant \f$\frac{m^{2}}{s^{2} K}\f$ */
#define CONST_REAL_GAS          (287.04)

/** \brief standard gravity \f$\frac{m}{s^{2}}\f$ */
#define CONST_STANDARD_GRAVITY  (9.80665)

/** \brief ideal gas constant \f$\frac{J}{K mol}\f$ */
#define CONST_UNIVERSAL_GAS     (8.31447215)

/** \brief universal gravitational constant \f$\frac{m^{3}}{s^{2} kg}\f$ */
#define CONST_UNIVERSAL_GRAVITY (6.673e-11)

/** @} */

/** \name General Purpose Conversion Constants */
/** @{ */

#ifndef M_PI
#   define M_PI                     (3.14159265358979323846264338327)
#endif

#define RAD_TO_DEG                  (180 / M_PI) /**< radians to degrees */
#define DEG_TO_RAD                  (M_PI / 180) /**< degrees to radians */

#define GAUSS_TO_MICRO_TESLA        (100)        /**< \f$1 Gauss = 100 \mu T\f$ */

#define KELVIN_TO_CELSIUS(K)        ((K)-273.15)
#define CELSIUS_TO_KELVIN(C)        ((C)+273.15)

#define FAHRENHEIT_TO_CELSIUS(F)    (((5 * ((F)-32)) / 9) + 0.5)
#define CELSIUS_TO_FAHRENHEIT(C)    ((((9 * (C)) / 5) + 32) + 0.5)

/** @} */

#ifdef __cplusplus
}
#endif

#endif
