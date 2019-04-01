/***************************************************************************//**
 * @file
 * @brief Provide configuration parameters for EM4 wakeup button.
 * @version 5.1.0
 *******************************************************************************
 * @section License
 * <b>Copyright 2017 Silicon Laboratories, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef EM4CONFIG_H
#define EM4CONFIG_H

#include "bspconfig.h"

#define EM4_WU_PB           PB1
#define EM4_WU_PB_EN        (1 << 17) /* GPIO_EM4WU1 = PF7 = pushbutton 1 */
#define EM4_WU_PB_PIN       BSP_GPIO_PB1_PIN
#define EM4_WU_PB_PORT      BSP_GPIO_PB1_PORT
#define EM4_WU_PB_STR       "PB1"

#define EM4_NON_WU_PB          PB0
#define EM4_NON_WU_PB_PIN      BSP_GPIO_PB0_PIN
#define EM4_NON_WU_PB_PORT     BSP_GPIO_PB0_PORT
#define EM4_NON_WU_PB_STR      "PB0"

#endif /* EM4CONFIG_H */
