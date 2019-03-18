/**
 * \file
 *
 * \brief ILI9341 display controller component driver default config header
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
#ifndef CONF_ILI9341_H_INCLUDED
#define CONF_ILI9341_H_INCLUDED

#include <compiler.h>

/**
 * \brief Select a SPI clock speed
 *
 * This selects the clock speed for the SPI clock used to communicate with the
 * display controller. Higher clock speeds allow for higher frame rates.
 * \note That the clock speed may be limited by the speed of the
 * microcontroller a normal limitation would be CPUclk/2. For more details
 * please refer to the device datasheet.
 */
#define CONF_ILI9341_CLOCK_SPEED   8000000UL

/**
 * \name SAM typical configurations
 * @{
 */

/**
 * \brief Select the correct hardware interface
 *
 * Currently supported interfaces are the SPI interface and the USART Master SPI
 * interface.
 */
#if defined(SPI0)
#  define CONF_ILI9341_SPI         SPI0
#else
#  define CONF_ILI9341_SPI         SPI
#endif
/* #define CONF_ILI9341_USART_SPI    UART0 */

/** \brief Define what MCU pin the ILI9341 chip select pin is connected to */
#define CONF_ILI9341_CS_PIN        PIO_PA11_IDX

/** \brief Define what MCU pin the ILI9341 DC pin is connected to */
#define CONF_ILI9341_DC_PIN        PIO_PB3_IDX

/** \brief Define what MCU pin the ILI9341 back light pin is connected to */
#define CONF_ILI9341_BACKLIGHT_PIN PIO_PA17_IDX

/** \brief Define what MCU pin the ILI9341 reset is connected to */
#define CONF_ILI9341_RESET_PIN     PIO_PC13_IDX

/** @} */

#endif /* CONF_ILI9341_H_INCLUDED */
