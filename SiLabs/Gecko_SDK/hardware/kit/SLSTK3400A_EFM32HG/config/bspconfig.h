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

#ifndef __SILICON_LABS_BSPCONFIG_H
#define __SILICON_LABS_BSPCONFIG_H

#define BSP_STK
#define BSP_STK_BRD2012

#define BSP_BCC_USART         USART1
#define BSP_BCC_CLK           cmuClock_USART1
#define BSP_BCC_LOCATION      USART_ROUTE_LOCATION_LOC4
#define BSP_BCC_TXPORT        gpioPortF
#define BSP_BCC_TXPIN         2
#define BSP_BCC_RXPORT        gpioPortA
#define BSP_BCC_RXPIN         0
#define BSP_BCC_ENABLE_PORT   gpioPortA
#define BSP_BCC_ENABLE_PIN    9

#define BSP_GPIO_LEDS
#define BSP_NO_OF_LEDS  2
#define BSP_GPIO_LEDARRAY_INIT {{gpioPortF,4},{gpioPortF,5}}

#define BSP_GPIO_BUTTONS
#define BSP_NO_OF_BUTTONS       2
#define BSP_GPIO_PB0_PORT       gpioPortC
#define BSP_GPIO_PB0_PIN        9
#define BSP_GPIO_PB1_PORT       gpioPortC
#define BSP_GPIO_PB1_PIN        10

#define BSP_GPIO_BUTTONARRAY_INIT {{BSP_GPIO_PB0_PORT, BSP_GPIO_PB0_PIN}, {BSP_GPIO_PB1_PORT, BSP_GPIO_PB1_PIN}}

#define BSP_INIT_DEFAULT  0

#define BSP_BCP_VERSION 2
#include "bsp_bcp.h"

#endif /* __SILICON_LABS_BSPCONFIG_H */
