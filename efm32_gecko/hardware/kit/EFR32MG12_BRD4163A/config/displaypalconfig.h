/***************************************************************************//**
 * @file displaypalconfig.h
 * @brief Configuration file for PAL (Platform Abstraction Layer)
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

#ifndef DISPLAYPALCONFIG_H
#define DISPLAYPALCONFIG_H

/*
 * Select which oscillator should source the RTC clock.
 */
#undef  PAL_RTCC_CLOCK_LFXO
#define PAL_RTCC_CLOCK_LFRCO
#undef  PAL_RTCC_CLOCK_ULFRCO

/*
 * PAL SPI / USART configuration.
 * Select which USART and location is connected to the device via SPI.
 */
#define PAL_SPI_USART_UNIT          (USART1)
#define PAL_SPI_USART_CLOCK         (cmuClock_USART1)
#define PAL_SPI_USART_LOCATION_TX   (11)
#define PAL_SPI_USART_LOCATION_SCLK (11)

/*
 * Specify the SPI baud rate:
 */
#define PAL_SPI_BAUDRATE       (3500000) /* Max baudrate on EFR32xG12. */

#endif /* DISPLAYPALCONFIG_H */
