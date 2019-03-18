/**
 * \file
 *
 * \brief Atmel Common Sensor Service configuration parameters.
 *
 * This file defines tunable configuration constants for user selected API
 * features and functions.
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

#ifndef _CONF_SENSORS_H_
#define _CONF_SENSORS_H_

/* Sensor Platform Board Configuration
 *
 * The Sensor API hardware abstraction layer is conditionally compiled
 * for a particular platform and target MCU based upon application and
 * toolchain constants exposed through the common board.h file.
 */
#include    <board.h>

/* Atmel Software Framework (ASF) Interfaces */
#include    <sysclk.h>

#if UC3
#   include <cycle_counter.h>
#endif

/** \name Redirect C Standard I/O (USB or USART) */
/** @{ */
#if defined(CONF_STDIO_REDIRECT)
#if (UC3A || UC3B || UC3C || XMEGA_AU || XMEGA_B)
#   include <stdio/stdio_usb/stdio_usb.h>
#   define CONF_STDIO_USB           /* !< Configure C Standard I/O over USB/CDC */
#elif (UC3L || XMEGA_A1)
#   include <stdio/stdio_serial/stdio_serial.h>
#   define CONF_STDIO_SERIAL        /* !< Configure C Standard I/O over USART */
#endif
#endif
/** @} */

/** \name Xplained Platform USART Configuration */
/** @{ */
#if (BOARD == XMEGA_A1_XPLAINED)
#   define CONFIG_USART_IF          (USARTC0)
#elif (BOARD == XMEGA_B1_XPLAINED)
#   define CONFIG_USART_IF          (USARTE0)
#elif (BOARD == XMEGA_A3BU_XPLAINED)
#   define CONFIG_USART_IF          (USARTD0)
#elif (BOARD == UC3_L0_XPLAINED)
#   define CONFIG_USART_IF          (AVR32_USART2)
#elif (BOARD == UC3_A3_XPLAINED)
#   define CONFIG_USART_IF          (AVR32_USART2)
#else
#   define CONFIG_USART_IF          (NULL)
#endif

#if XMEGA
#   define CONFIG_USART_BAUDRATE    (115200)
#   define CONFIG_USART_CHAR_LENGTH (USART_CHSIZE_8BIT_gc)
#   define CONFIG_USART_PARITY      (USART_PMODE_DISABLED_gc)
#   define CONFIG_USART_STOP_BIT    (false)
#else
#   define CONFIG_USART_BAUDRATE    (115200)
#   define CONFIG_USART_CHAR_LENGTH (8)
#   define CONFIG_USART_PARITY      (USART_NO_PARITY)
#   define CONFIG_USART_STOP_BIT    (USART_1_STOPBIT)
#endif
/** @} */

/** \name Platform TWI and SPI Bus Configuration */
/** @{ */
#if (BOARD == XMEGA_A1_XPLAINED)
#   define CONFIG_TWI_MASTER_IF     (TWIF)
#   define CONFIG_SPI_MASTER_IF     (SPIF)
#elif (BOARD == XMEGA_B1_XPLAINED)
#   define CONFIG_TWI_MASTER_IF     (TWIC)
#   define CONFIG_SPI_MASTER_IF     (SPIC)
#elif (BOARD == XMEGA_A3BU_XPLAINED)
#   define CONFIG_TWI_MASTER_IF     (TWIC)
#   define CONFIG_SPI_MASTER_IF     (SPIC)
#elif (BOARD == UC3_L0_XPLAINED)
#   define CONFIG_TWI_MASTER_IF     (AVR32_TWIM0)
#   define CONFIG_SPI_MASTER_IF     (AVR32_SPI)
#elif (BOARD == UC3_A3_XPLAINED)
#   define CONFIG_TWI_MASTER_IF     (AVR32_TWIM0)
#   define CONFIG_SPI_MASTER_IF     (AVR32_SPI0)
#else
#   define CONFIG_TWI_MASTER_IF     (NULL)
#   define CONFIG_SPI_MASTER_IF     (NULL)
#endif

#define CONFIG_TWI_BAUDRATE         (400000)
#define CONFIG_TWI_OFFSET           (0)

#define CONFIG_SPI_BAUDRATE         (12000000)
#define CONFIG_SPI_OFFSET           (0)

#undef CONF_EVENT_COUNTERS          /**< Development and Debugging Facilities */
/** @} */

#endif
