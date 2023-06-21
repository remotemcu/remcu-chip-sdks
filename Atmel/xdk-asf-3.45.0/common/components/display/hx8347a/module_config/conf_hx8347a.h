/**
 * \file
 *
 * \brief HX8347A display controller driver default config header
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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
#ifndef CONF_HX8347A_H_INCLUDED
#define CONF_HX8347A_H_INCLUDED

#include <compiler.h>

/**
 * \brief Select a SPI clock speed
 *
 * This selects the clock speed for the SPI clock used to communicate with the
 * display controller. Higher clock speeds allow for higher frame rates.
 * \note That the clock speed may be limited by the speed of the microcontroller
 * a normal limitation would be CPUclk/2. For more details please refer to the
 * device datasheet.
 */
#define CONF_HX8347A_CLOCK_SPEED   500000UL

#if XMEGA || defined(__DOXYGEN__)

/**
 * \name XMEGA typical configurations
 * @{
 */

/**
 * \brief Select the correct hardware interface
 *
 * Currently supported interfaces are the SPI interface and the USART Master SPI
 * interface.
 */
#define CONF_HX8347A_SPI           &SPIC
/* #define CONF_HX8347A_USART_SPI     &USARTD1 */

/** \brief Define what MCU pin the HX8347A chip select pin is connected to */
#define CONF_HX8347A_CS_PIN        IOPORT_CREATE_PIN(PORTD, 4)

/** \brief Define what MCU pin the HX8347A TE pin is connected to */
#define CONF_HX8347A_TE_PIN        IOPORT_CREATE_PIN(PORTD, 2)

/** \brief Define what MCU pin the HX8347A back light pin is connected to */
#define CONF_HX8347A_BACKLIGHT_PIN IOPORT_CREATE_PIN(PORTD, 0)

/** \brief Define what MCU pin the HX8347A reset is connected to */
#define CONF_HX8347A_RESET_PIN     IOPORT_CREATE_PIN(PORTD, 1)

/** @} */
#endif /* XMEGA */

#if UC3

/**
 * \name UC3 typical configurations
 * @{
 */

/**
 * \brief Select the correct hardware interface
 *
 * Currently supported interfaces are the SPI interface and the USART Master SPI
 * interface.
 */
#define CONF_HX8347A_SPI           &AVR32_SPI
/* #define CONF_HX8347A_USART_SPI     &AVR32_USART0 */

/** \brief Define what MCU pin the HX8347A chip select pin is connected to */
#define CONF_HX8347A_CS_PIN        AVR32_PIN_PA00

/** \brief Define what MCU pin the HX8347A TE pin is connected to */
#define CONF_HX8347A_TE_PIN        AVR32_PIN_PA01

/** \brief Define what MCU pin the HX8347A back light pin is connected to */
#define CONF_HX8347A_BACKLIGHT_PIN AVR32_PIN_PA02

/** \brief Define what MCU pin the HX8347A reset is connected to */
#define CONF_HX8347A_RESET_PIN     AVR32_PIN_PA03

/** @} */
#endif /* UC3 */

#endif /* CONF_HX8347A_H_INCLUDED */
