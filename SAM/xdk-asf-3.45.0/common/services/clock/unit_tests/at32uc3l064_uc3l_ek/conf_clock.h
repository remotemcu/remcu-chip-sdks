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

// ===== System Clock Source Options
#define CONFIG_SYSCLK_SOURCE          SYSCLK_SRC_DFLL

// ===== DFLL Options
#define CONFIG_DFLL0_SOURCE            GENCLK_SRC_RCSYS
#define CONFIG_DFLL0_MUL               835 /* Fdfll = (Fclk * mul) / div */
#define CONFIG_DFLL0_DIV               1 /* Fdfll = (Fclk * mul) / div */

#define PLL0                          0
#define PLL1                          1

// ===== System Clock Bus Division Options
#define CONFIG_SYSCLK_CPU_DIV         1 /* Fcpu = Fsys/(2 ^ CPU_div) */
#define CONFIG_SYSCLK_PBA_DIV         2 /* Fpba = Fsys/(2 ^ PBA_div) */
#define CONFIG_SYSCLK_PBB_DIV         2 /* Fpbb = Fsys/(2 ^ PBB_div) */

#define CONFIG_CPU_HZ                 48012500
#define CONFIG_PBA_HZ                 24006250
#define CONFIG_PBB_HZ                 24006250

// ===== Generic clock
#define CONFIG_GENERIC_SRC            GENCLK_SRC_RCSYS
#define CONFIG_GENERIC_DIV            1
#define CONFIG_GENERIC_ID             2
#define CONFIG_GENERIC_CLOCK          28750

#define get_generic_clock()           \
	(CONFIG_GENERIC_DIV == 0 ? osc_get_rate(OSC_ID_RCSYS) \
	: osc_get_rate(OSC_ID_RCSYS) / (2*(CONFIG_GENERIC_DIV + 1)))

// ===== Nominal frequency of RCSYS in Hz
#define OSC_RCSYS_NOMINAL_HZ          115000

#endif /* CONF_CLOCK_H_INCLUDED */
