/***************************************************************************//**
 * @file displaypalconfig.h
 * @brief Configuration file for PAL (Platform Abstraction Layer)
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

#ifndef __SILICON_LABS_DISPLAY_PAL_CONFIG_H_
#define __SILICON_LABS_DISPLAY_PAL_CONFIG_H_

/*
 * Select which oscillator should source the RTC clock.
 */
#undef  PAL_RTC_CLOCK_LFXO
#undef  PAL_RTC_CLOCK_LFRCO
#define PAL_RTC_CLOCK_ULFRCO

/*
 * PAL SPI / USART configuration for the EFM32ZG_STK3200.
 * Select which USART and location is connected to the device via SPI.
 */
#define PAL_SPI_USART_UNIT     (USART1)
#define PAL_SPI_USART_CLOCK    (cmuClock_USART1)
#define PAL_SPI_USART_LOCATION (USART_ROUTE_LOCATION_LOC1)

/*
 * Specify the SPI baud rate:
 */
#define PAL_SPI_BAUDRATE       (3500000) /* Max baudrate on Zero Gecko. */

#endif /* __SILICON_LABS_DISPLAY_PAL_CONFIG_H_ */
