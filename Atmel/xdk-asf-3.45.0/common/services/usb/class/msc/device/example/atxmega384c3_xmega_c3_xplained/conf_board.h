/**
 * \file
 *
 * \brief Board configuration
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
#ifndef CONF_BOARD_H_INCLUDED
#define CONF_BOARD_H_INCLUDED

// Initialize SPI and control pins for UG_2832HSWEG04 OLED controller
//#define CONF_BOARD_OLED_UG_2832HSWEG04

// Initialize SPI pins and presence pin for MicroSD card slot
#define CONF_BOARD_SD_MMC_SPI

// Initialize Analog Comparator pin for light sensor
//#define CONF_BOARD_LIGHT_SENSOR

// Initialize Analog Comparator pin for NTC sensor
//#define CONF_BOARD_TEMPERATURE_SENSOR

// Initialize Analog Comparator pin and input signal pin
// for Analog Filter (lowpass RC @ 159 Hz)
//#define CONF_BOARD_ANALOG_FILTER

// Initialize IO pins for use with USART 0 on port C
//#define CONF_BOARD_ENABLE_USARTC0

// Initialize IO pins for use with USART 0 on port D
//#define CONF_BOARD_ENABLE_USARTD0

// Initialize IO pins for use with USART 0 on port E
//#define CONF_BOARD_ENABLE_USARTE0

#endif /* CONF_BOARD_H_INCLUDED */
