/***************************************************************************//**
 * @file util.h
 * @brief Utility Functions for the Thunderboard Sense
 * @version 5.1.1
 *******************************************************************************
 * @section License
 * <b>Copyright 2016 Silicon Laboratories, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef __UTIL_H_
#define __UTIL_H_

#include <stdint.h>
#include <stdbool.h>

/***************************************************************************//**
 * @addtogroup Util
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @defgroup Util_Defs Utility Definitions
 * @{
 * @brief Definitions used in the utility functions
 ******************************************************************************/

#define UTIL_SUPPLY_TYPE_UNKNOWN    0	/**< Unknown power supply type                */
#define UTIL_SUPPLY_TYPE_USB        1	/**< The board powered from the USB connector */
#define UTIL_SUPPLY_TYPE_AA         2	/**< The board powered from AA batteries      */
#define UTIL_SUPPLY_TYPE_AAA        3	/**< The board powered from AAA batteries     */
#define UTIL_SUPPLY_TYPE_CR2032     4	/**< The board powered from a CR2032 battery  */

/** @} {end defgroup Util_Defs} */

/***************************************************************************//**
 * @addtogroup Util_Functions
 * @{
 ******************************************************************************/

uint32_t UTIL_init        ( void );
void     UTIL_delay       ( uint32_t ms );
void     UTIL_shutdown    ( void );

uint32_t UTIL_sleepInit   ( void );
void     UTIL_sleep       ( uint32_t ms );
uint32_t UTIL_waitForEvent( uint32_t timeout );

void     UTIL_supplyProbe                ( void );
void     UTIL_supplyGetCharacteristics   ( uint8_t *type, float *voltage, float *ir );
uint8_t  UTIL_supplyGetType              ( void );
bool     UTIL_isLowPower                 ( void );

/** @} {end addtogroup Util_Functions} */

/** @} {end addtogroup Util} */

#endif /* __UTIL_H_ */
