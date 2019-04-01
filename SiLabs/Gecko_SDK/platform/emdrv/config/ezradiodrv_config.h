/***************************************************************************//**
 * @file ezradiodrv_config.h
 * @brief EZRADIODRV configuration file.
 * @version 5.1.2
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2015 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Silicon Labs has no
 * obligation to support this Software. Silicon Labs is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Silicon Labs will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/
#ifndef __SILICON_LABS_EZRADIODRV_CONFIG_H__
#define __SILICON_LABS_EZRADIODRV_CONFIG_H__

/***************************************************************************//**
 * @addtogroup emdrv
 * @{
 ******************************************************************************/

 /***************************************************************************//**
 * @addtogroup EZRADIODRV
 * @{
 ******************************************************************************/

#warning "This configuration file is deprecated and marked for removal in a later release. Please use the new configuration template file in emdrv\ezradiodrv\config instead."

/// @brief Number of wait-for-CTS retries.
#define EZRADIODRV_COMM_CTS_RETRY 10000

/// @brief Enable poll GPIO1 for CTS.
//#define EZRADIODRV_COMM_USE_GPIO1_FOR_CTS

/// @brief Define to disable packet trace interface.
//#define EZRADIODRV_DISABLE_PTI

/// @brief Define to enable 4-wire SPI communication with the radio.
///        Note: 4-wire mode cannot be used in EZR32 devices.
//#define EZRADIODRV_SPI_4WIRE_MODE

// ONly EZR32 devices support these macros by default, we need to add these for other
// devices. Uncomment & define all the following RF_* macros to support the EzRadio 
// device on other EFM32 micros.

//#define RF_USARTRF_LOCATION     1     /**< RF SPI-port (USART) location number. */
//#define RF_USARTRF_CS_PORT      3     /**< Bit banged RF SPI CS GPIO port no.   */
//#define RF_USARTRF_CS_PIN       3     /**< Bit banged RF SPI CS GPIO pin number.*/
//#define RF_USARTRF_CLK_PORT     3     /**< RF SPI CLK GPIO port number.      */
//#define RF_USARTRF_CLK_PIN      2     /**< RF SPI CLK GPIO pin number.       */
//#define RF_USARTRF_MISO_PORT    3     /**< RF SPI MISO GPIO port number.     */
//#define RF_USARTRF_MISO_PIN     1     /**< RF SPI MISO GPIO pin number.      */
//#define RF_USARTRF_MOSI_PORT    3     /**< RF SPI MOSI GPIO port number.     */
//#define RF_USARTRF_MOSI_PIN     0     /**< RF SPI MOSI GPIO pin number.      */
//#define RF_INT_PORT             2     /**< RF interrupt GPIO port number.    */
//#define RF_INT_PIN              0     /**< RF interrupt GPIO pin number.     */
//#define RF_SDN_PORT             2     /**< RF SDN GPIO port number.          */
//#define RF_SDN_PIN              3     /**< RF SDN GPIO pin number.           */

#if !(defined EZRADIODRV_DISABLE_PTI)
//#define RF_GPIO0_PORT           0     /**< RF GPIO0 GPIO port number.        */
//#define RF_GPIO0_PIN            15    /**< RF GPIO0 GPIO pin number.         */
//#define RF_GPIO1_PORT           4     /**< RF GPIO1 GPIO port number.        */
//#define RF_GPIO1_PIN            14    /**< RF GPIO1 GPIO pin number.         */
#endif

/** @} (end addtogroup EZRADIODRV) */
/** @} (end addtogroup emdrv) */

#endif /* __SILICON_LABS_EZRADIODRV_CONFIG_H__ */
