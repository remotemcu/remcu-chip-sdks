/**************************************************************************//**
 * @file
 * @brief Kit specific board defines for BRD8001A sensor expansion board.
 * @version 5.1.1
 ******************************************************************************
 * @section License
 * <b>Copyright 2016 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef BRD8001A_CONFIG_H
#define BRD8001A_CONFIG_H

#include "em_device.h"
#include "em_gpio.h"

// Definition for the proximity detector part of SI1147
#define BRD8001A_INT_INPUT_PORT   gpioPortA
#define BRD8001A_INT_INPUT_PIN    1

// Definition for powering up sensor board STK
#define BRD8001A_POWER_PORT       gpioPortA
#define BRD8001A_POWER_PIN        0

#endif /* BRD8001A_CONFIG_H */
