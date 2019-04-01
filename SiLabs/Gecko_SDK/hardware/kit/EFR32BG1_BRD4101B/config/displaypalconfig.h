/***************************************************************************//**
 * @file displaypalconfig.h
 * @brief Configuration file for PAL (Platform Abstraction Layer)
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

#ifndef DISPLAY_PAL_CONFIG_H
#define DISPLAY_PAL_CONFIG_H

/*
 * Select which oscillator should source the RTC clock.
 */
#undef  PAL_RTCC_CLOCK_LFXO
#define PAL_RTCC_CLOCK_LFRCO
#undef  PAL_RTCC_CLOCK_ULFRCO

/*
 * PAL SPI / USART configuration for the SLWSTK6000A.
 * Select which USART and location is connected to the device via SPI.
 */
#define PAL_SPI_USART_UNIT          (USART1)
#define PAL_SPI_USART_CLOCK         (cmuClock_USART1)
#define PAL_SPI_USART_LOCATION_TX   (0)
#define PAL_SPI_USART_LOCATION_SCLK (4)

/*
 * Specify the SPI baud rate:
 */
#define PAL_SPI_BAUDRATE       (3500000) /* Max baudrate on EFR32MG1. */

#endif /* DISPLAY_PAL_CONFIG_H */
