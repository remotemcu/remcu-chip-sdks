/**
 * \file
 *
 * \brief Chip-specific system clock manager configuration
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
#ifndef CONF_CLOCK_H_INCLUDED
#define CONF_CLOCK_H_INCLUDED

//! Configuration using On-Chip RC oscillator at 48MHz
//! The RC oscillator is calibrated via USB Start Of Frame
//! Clk USB     = 48MHz (used by USB)
//! Clk sys     = 48MHz
//! Clk cpu/per = 24MHz
#define CONFIG_USBCLK_SOURCE     USBCLK_SRC_RCOSC
#define CONFIG_OSC_RC32_CAL      48000000UL

#define CONFIG_OSC_AUTOCAL_RC32MHZ_REF_OSC  OSC_ID_USBSOF

#define CONFIG_SYSCLK_SOURCE     SYSCLK_SRC_RC32MHZ
#define CONFIG_SYSCLK_PSADIV     SYSCLK_PSADIV_2
#define CONFIG_SYSCLK_PSBCDIV    SYSCLK_PSBCDIV_1_1

/*
//! Use external board OSC (8MHz)
//! Clk pll     = 48MHz (used by USB)
//! Clk sys     = 48MHz
//! Clk cpu/per = 12MHz

#define CONFIG_PLL0_SOURCE       PLL_SRC_XOSC
#define CONFIG_PLL0_MUL          6
#define CONFIG_PLL0_DIV          1

#define CONFIG_USBCLK_SOURCE     USBCLK_SRC_PLL

#define CONFIG_SYSCLK_SOURCE     SYSCLK_SRC_PLL
#define CONFIG_SYSCLK_PSADIV     SYSCLK_PSADIV_2
#define CONFIG_SYSCLK_PSBCDIV    SYSCLK_PSBCDIV_1_2
*/


#endif /* CONF_CLOCK_H_INCLUDED */
