/**
 * \file
 *
 * \brief Atmel Development Board Clock Configuration (ASF)
 *
 * Copyright (c) 2010-2018 Microchip Technology Inc. and its subsidiaries.
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

#if (UC3A3 || UC3C)
#   define CONFIG_SYSCLK_INIT_CPUMASK   (0)
#   define CONFIG_SYSCLK_INIT_PBAMASK   (0)
#   define CONFIG_SYSCLK_INIT_PBBMASK   (0)
#   define CONFIG_SYSCLK_INIT_HSBMASK   (0)
#elif UC3L
#   define CONFIG_SYSCLK_INIT_CPUMASK   (0)
#   define CONFIG_SYSCLK_INIT_PBAMASK   (0)
#   define CONFIG_SYSCLK_INIT_PBBMASK   (0)
#   define CONFIG_SYSCLK_INIT_HSBMASK   (0)
#endif

#if UC3A3
#   define CONFIG_SYSCLK_SOURCE         (SYSCLK_SRC_OSC0)
#   define CONFIG_SYSCLK_CPU_DIV        (0)
#   define CONFIG_SYSCLK_PBA_DIV        (0)
#   define CONFIG_SYSCLK_PBB_DIV        (0)
#   define CONFIG_PLL0_SOURCE           (PLL_SRC_OSC0)
#   define CONFIG_PLL0_MUL              (48000000UL / BOARD_OSC0_HZ)
#   define CONFIG_PLL0_DIV              (1)
#   define CONFIG_USBCLK_SOURCE         (USBCLK_SRC_OSC0)
#   define CONFIG_USBCLK_DIV            (1)
#   define CONFIG_PLL1_SOURCE           (PLL_SRC_OSC0)
#   define CONFIG_PLL1_DIV              (2)
#   define CONFIG_PLL1_MUL              (8)
#elif UC3L
#   define CONFIG_SYSCLK_SOURCE         (SYSCLK_SRC_DFLL)
#   define CONFIG_DFLL0_SOURCE          (GENCLK_SRC_OSC32K)
#   define CONFIG_DFLL0_MUL             (80000000UL / BOARD_OSC32_HZ)
#   define CONFIG_DFLL0_DIV             (2)
#elif UC3C
#   define CONFIG_SYSCLK_SOURCE         (SYSCLK_SRC_RC8M)
#elif XMEGA_A1 || XMEGA_A1U
#   define CONFIG_SYSCLK_SOURCE         (SYSCLK_SRC_PLL)
#   define CONFIG_SYSCLK_PSADIV         (SYSCLK_PSADIV_1)
#   define CONFIG_SYSCLK_PSBCDIV        (SYSCLK_PSBCDIV_1_2)
#   define CONFIG_PLL0_SOURCE           (PLL_SRC_RC32MHZ)
#   define CONFIG_PLL0_MUL              (8)
#   define CONFIG_PLL0_DIV              (4)
#elif XMEGA_B1
#   define CONFIG_USBCLK_SOURCE                (USBCLK_SRC_RCOSC)
#   define CONFIG_OSC_RC32_CAL                 (48000000UL)
#   define CONFIG_OSC_AUTOCAL_RC32MHZ_REF_OSC  (OSC_ID_USBSOF)
#   define CONFIG_SYSCLK_SOURCE                (SYSCLK_SRC_RC32MHZ)
#   define CONFIG_SYSCLK_PSADIV                (SYSCLK_PSADIV_2)
#   define CONFIG_SYSCLK_PSBCDIV               (SYSCLK_PSBCDIV_1_1)
#elif XMEGA_A3B || XMEGA_A3BU

/*  Configuration using On-Chip RC oscillator at 48MHz */
/*    The RC oscillator is calibrated via USB Start Of Frame */
/*    Clk USB     = 48MHz (used by USB) */
/*    Clk sys     = 48MHz */
/*    Clk cpu/per = 24MHz */
#   define CONFIG_USBCLK_SOURCE                (USBCLK_SRC_RCOSC)
#   define CONFIG_OSC_RC32_CAL                 (48000000UL)
#   define CONFIG_OSC_AUTOCAL_RC32MHZ_REF_OSC  (OSC_ID_USBSOF)
#   define CONFIG_SYSCLK_SOURCE                (SYSCLK_SRC_RC32MHZ)
#   define CONFIG_SYSCLK_PSADIV                (SYSCLK_PSADIV_2)
#   define CONFIG_SYSCLK_PSBCDIV               (SYSCLK_PSBCDIV_1_1)
#endif

#endif /* CONF_CLOCK_H_INCLUDED */
