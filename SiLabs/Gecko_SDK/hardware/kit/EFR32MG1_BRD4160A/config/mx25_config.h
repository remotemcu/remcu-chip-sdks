/***************************************************************************//**
 * @file mx25_config.h
 * @brief MX25R8035F NOR flash configuration file
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

#ifndef __MX25_CONFIG_H
#define __MX25_CONFIG_H

#include "em_device.h"
#include "em_gpio.h"

#define MX25_PORT_MOSI         gpioPortC
#define MX25_PIN_MOSI          6
#define MX25_PORT_MISO         gpioPortC
#define MX25_PIN_MISO          7
#define MX25_PORT_SCLK         gpioPortC
#define MX25_PIN_SCLK          8
#define MX25_PORT_CS           gpioPortA
#define MX25_PIN_CS            4

#define MX25_USART             USART1
#define MX25_USART_CLK         cmuClock_USART1

#define MX25_USART_LOC_MOSI    USART_ROUTELOC0_TXLOC_LOC11
#define MX25_USART_LOC_MISO    USART_ROUTELOC0_RXLOC_LOC11
#define MX25_USART_LOC_SCLK    USART_ROUTELOC0_CLKLOC_LOC11

#endif /* __MX25_CONFIG_H */
