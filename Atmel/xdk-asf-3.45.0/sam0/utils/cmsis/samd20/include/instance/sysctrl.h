/**
 * \file
 *
 * \brief Instance description for SYSCTRL
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _SAMD20_SYSCTRL_INSTANCE_
#define _SAMD20_SYSCTRL_INSTANCE_

/* ========== Register definition for SYSCTRL peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_SYSCTRL_INTENCLR       (0x40000800U) /**< \brief (SYSCTRL) Interrupt Enable Clear */
#define REG_SYSCTRL_INTENSET       (0x40000804U) /**< \brief (SYSCTRL) Interrupt Enable Set */
#define REG_SYSCTRL_INTFLAG        (0x40000808U) /**< \brief (SYSCTRL) Interrupt Flag Status and Clear */
#define REG_SYSCTRL_PCLKSR         (0x4000080CU) /**< \brief (SYSCTRL) Power and Clocks Status */
#define REG_SYSCTRL_XOSC           (0x40000810U) /**< \brief (SYSCTRL) XOSC Control */
#define REG_SYSCTRL_XOSC32K        (0x40000814U) /**< \brief (SYSCTRL) XOSC32K Control */
#define REG_SYSCTRL_OSC32K         (0x40000818U) /**< \brief (SYSCTRL) OSC32K Control */
#define REG_SYSCTRL_OSCULP32K      (0x4000081CU) /**< \brief (SYSCTRL) OSCULP32K Control */
#define REG_SYSCTRL_OSC8M          (0x40000820U) /**< \brief (SYSCTRL) OSC8M Control A */
#define REG_SYSCTRL_DFLLCTRL       (0x40000824U) /**< \brief (SYSCTRL) DFLL Config */
#define REG_SYSCTRL_DFLLVAL        (0x40000828U) /**< \brief (SYSCTRL) DFLL Calibration Value */
#define REG_SYSCTRL_DFLLMUL        (0x4000082CU) /**< \brief (SYSCTRL) DFLL Multiplier */
#define REG_SYSCTRL_DFLLSYNC       (0x40000830U) /**< \brief (SYSCTRL) DFLL Synchronization */
#define REG_SYSCTRL_BOD33          (0x40000834U) /**< \brief (SYSCTRL) 3.3V Brown-Out Detector (BOD33) Control */
#define REG_SYSCTRL_VREG           (0x4000083CU) /**< \brief (SYSCTRL) VREG Control */
#define REG_SYSCTRL_VREF           (0x40000840U) /**< \brief (SYSCTRL) VREF Control A */
#else
#define REG_SYSCTRL_INTENCLR       (*(RwReg  *)0x40000800U) /**< \brief (SYSCTRL) Interrupt Enable Clear */
#define REG_SYSCTRL_INTENSET       (*(RwReg  *)0x40000804U) /**< \brief (SYSCTRL) Interrupt Enable Set */
#define REG_SYSCTRL_INTFLAG        (*(RwReg  *)0x40000808U) /**< \brief (SYSCTRL) Interrupt Flag Status and Clear */
#define REG_SYSCTRL_PCLKSR         (*(RoReg  *)0x4000080CU) /**< \brief (SYSCTRL) Power and Clocks Status */
#define REG_SYSCTRL_XOSC           (*(RwReg16*)0x40000810U) /**< \brief (SYSCTRL) XOSC Control */
#define REG_SYSCTRL_XOSC32K        (*(RwReg16*)0x40000814U) /**< \brief (SYSCTRL) XOSC32K Control */
#define REG_SYSCTRL_OSC32K         (*(RwReg  *)0x40000818U) /**< \brief (SYSCTRL) OSC32K Control */
#define REG_SYSCTRL_OSCULP32K      (*(RwReg8 *)0x4000081CU) /**< \brief (SYSCTRL) OSCULP32K Control */
#define REG_SYSCTRL_OSC8M          (*(RwReg  *)0x40000820U) /**< \brief (SYSCTRL) OSC8M Control A */
#define REG_SYSCTRL_DFLLCTRL       (*(RwReg16*)0x40000824U) /**< \brief (SYSCTRL) DFLL Config */
#define REG_SYSCTRL_DFLLVAL        (*(RwReg  *)0x40000828U) /**< \brief (SYSCTRL) DFLL Calibration Value */
#define REG_SYSCTRL_DFLLMUL        (*(RwReg  *)0x4000082CU) /**< \brief (SYSCTRL) DFLL Multiplier */
#define REG_SYSCTRL_DFLLSYNC       (*(RwReg8 *)0x40000830U) /**< \brief (SYSCTRL) DFLL Synchronization */
#define REG_SYSCTRL_BOD33          (*(RwReg  *)0x40000834U) /**< \brief (SYSCTRL) 3.3V Brown-Out Detector (BOD33) Control */
#define REG_SYSCTRL_VREG           (*(RwReg16*)0x4000083CU) /**< \brief (SYSCTRL) VREG Control */
#define REG_SYSCTRL_VREF           (*(RwReg  *)0x40000840U) /**< \brief (SYSCTRL) VREF Control A */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for SYSCTRL peripheral ========== */
#define SYSCTRL_BGAP_CALIB_MSB      11
#define SYSCTRL_BOD33_CALIB_MSB     5
#define SYSCTRL_DFLL48M_COARSE_MSB  4
#define SYSCTRL_DFLL48M_FINE_MSB    7
#define SYSCTRL_GCLK_ID_DFLL48      0
#define SYSCTRL_OSC32K_COARSE_CALIB_MSB 6
#define SYSCTRL_POR33_ENTEST_MSB    1
#define SYSCTRL_ULPVREF_DIVLEV_MSB  3
#define SYSCTRL_ULPVREG_FORCEGAIN_MSB 1
#define SYSCTRL_ULPVREG_RAMREFSEL_MSB 2
#define SYSCTRL_VREF_CONTROL_MSB    48
#define SYSCTRL_VREF_STATUS_MSB     7
#define SYSCTRL_VREG_LEVEL_MSB      2
#define SYSCTRL_BOD12_VERSION       0x112
#define SYSCTRL_BOD33_VERSION       0x112
#define SYSCTRL_DFLL48M_VERSION     0x211   
#define SYSCTRL_GCLK_VERSION        0x210
#define SYSCTRL_OSCULP32K_VERSION   0x111
#define SYSCTRL_OSC8M_VERSION       0x120
#define SYSCTRL_OSC32K_VERSION      0x1101  
#define SYSCTRL_VREF_VERSION        0x200
#define SYSCTRL_VREG_VERSION        0x201
#define SYSCTRL_XOSC_VERSION        0x1101  
#define SYSCTRL_XOSC32K_VERSION     0x1101  

#endif /* _SAMD20_SYSCTRL_INSTANCE_ */
