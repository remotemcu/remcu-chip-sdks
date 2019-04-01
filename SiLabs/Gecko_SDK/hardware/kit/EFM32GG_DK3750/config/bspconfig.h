/***************************************************************************//**
 * @file
 * @brief Provide BSP (board support package) configuration parameters.
 * @version 5.1.1
 *******************************************************************************
 * @section License
 * <b>Copyright 2015 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef __BSPCONFIG_H
#define __BSPCONFIG_H

#define BSP_DK
#define BSP_DK_BRD3201
#define BSP_MCUBOARD_USB
#define BSP_MCUBOARD_BRD3600

#define BSP_GPIO_INT_PORT       gpioPortE
#define BSP_GPIO_INT_PIN        0
#define BSP_USB_STATUSLED_PORT  gpioPortE
#define BSP_USB_STATUSLED_PIN   1
#define BSP_USB_OCFLAG_PORT     gpioPortE
#define BSP_USB_OCFLAG_PIN      2
#define BSP_USB_VBUSEN_PORT     gpioPortF
#define BSP_USB_VBUSEN_PIN      5

#include "bsp_dk_bcreg_3201.h"

#define BSP_DK_LEDS
#define BSP_NO_OF_LEDS  16
#define BSP_LED_MASK    0xFFFF
#define BSP_LED_PORT    (&BC_REGISTER->UIF_LEDS)

#define BSP_INIT_DEFAULT  BSP_INIT_DK_EBI

#endif
