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
#define PAL_SPI_USART_UNIT        (USART0)
#define PAL_SPI_USART_CLOCK       (cmuClock_USART0)
#define PAL_SPI_USART_LOCATION    (USART_ROUTE_LOCATION_LOC0)
#define PAL_SPI_USART_DMAREQ_TXBL (DMAREQ_USART0_TXBL)

/*
 * Specify the SPI baud rate:
 */
#define PAL_SPI_BAUDRATE       (3500000) /* Max baudrate ????. */

/*
 * On the SLSTK3400A_EFM32HG, we can toggle some GPIO pins with hw only,
 * especially the GPIO port E pin 10 signal which is connected to the
 * polarity inversion (EXTCOMIN) pin on the Sharp Memory LCD. By defining
 * INCLUDE_PAL_GPIO_PIN_AUTO_TOGGLE_HW_ONLY the toggling of EXTCOMIN will
 * be handled by hardware, without software intervention, which saves power.
 */
#define INCLUDE_PAL_GPIO_PIN_AUTO_TOGGLE_HW_ONLY

#endif /* __SILICON_LABS_DISPLAY_PAL_CONFIG_H_ */
