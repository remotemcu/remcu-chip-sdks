/**
 * \file
 *
 * \brief Development Board Configuration
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#ifndef _CONF_SENSOR_PLATFORM_H_
#define _CONF_SENSOR_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup atavrpb_config Sensors Platform Board Configuration
 * @brief
 * Configuration constants defined for the platform are used to enable
 * peripherals and map I/O pin interfaces between sensors and the
 * development board they are paired with.
 *
 * @sa atavrsb_config
 * @{
 */

/** \name Platform Board Interrupt Priorities */
/** @{ */
#define CONFIG_GPIO_INT_LVL         0
#define CONFIG_TWIM_INT_LVL         2
/** @} */

/** \name Platform-Specific GPIO Pin Configuration */
/** @{ */
#define CONF_BOARD_SPI              /**< Map board SPI bus I/O pins */
#define CONF_BOARD_TWI              /**< Map board TWI bus I/O pins */
#define CONF_BOARD_ENABLE_USARTC0   /**< Map XMEGA-A1 USART pins */
#define CONF_BOARD_ENABLE_USARTE0   /**< Map XMEGA-B1 USART pins */
#define CONF_BOARD_ENABLE_USARTD0   /**< Map XMEGA-A3BU USART pins */
#define CONF_BOARD_COM_PORT         /**< Map UC3-L0 / UC3-A3 USART USB Virtual Com pins */
/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif
