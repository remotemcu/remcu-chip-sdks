/**
 * \file
 *
 * \brief HX8347A display controller configuration for the HX8347A example 2
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
#include <board.h>

#ifndef CONF_HX8347A_H_INCLUDED
#define CONF_HX8347A_H_INCLUDED

/**
 * \brief Select the correct hardware interface
 *
 * Currently supported interfaces are the SPI interface and the USART Master SPI
 * interface.
 */
/* #define CONF_HX8347A_SPI           &SPID */
#define CONF_HX8347A_USART_SPI     DISPLAY_XPLAINED_USART_SPI

/**
 * \brief Select a SPI clock speed
 *
 * This selects the clock speed for the SPI clock used to communicate with the
 * display controller. Higher clock speeds allow for higher frame rates.
 * \note That the clock speed may be limited by the speed of the microcontroller
 * a normal limitation would be CPUclk/2. For more details please refer to the
 * device datasheet.
 */
#define CONF_HX8347A_CLOCK_SPEED   8000000UL

/** \brief Define what MCU pin the HX8347A chip select pin is connected to */
#define CONF_HX8347A_CS_PIN        DISPLAY_XPLAINED_CS

/** \brief Define what MCU pin the HX8347A TE pin is connected to */
#define CONF_HX8347A_TE_PIN        DISPLAY_XPLAINED_TE

/** \brief Define what MCU pin the HX8347A back light pin is connected to */
#define CONF_HX8347A_BACKLIGHT_PIN DISPLAY_XPLAINED_BACKLIGHT

/** \brief Define what MCU pin the HX8347A reset is connected to */
#define CONF_HX8347A_RESET_PIN     DISPLAY_XPLAINED_RESET

#endif /* CONF_HX8347A_H_INCLUDED */
