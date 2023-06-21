/**
 * \file
 *
 * \brief Instance description for PAC
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

#ifndef _SAMC20_PAC_INSTANCE_
#define _SAMC20_PAC_INSTANCE_

/* ========== Register definition for PAC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_PAC_WRCTRL             (0x40000000U) /**< \brief (PAC) Write control */
#define REG_PAC_EVCTRL             (0x40000004U) /**< \brief (PAC) Event control */
#define REG_PAC_INTENCLR           (0x40000008U) /**< \brief (PAC) Interrupt enable clear */
#define REG_PAC_INTENSET           (0x40000009U) /**< \brief (PAC) Interrupt enable set */
#define REG_PAC_INTFLAGAHB         (0x40000010U) /**< \brief (PAC) Bridge interrupt flag status */
#define REG_PAC_INTFLAGA           (0x40000014U) /**< \brief (PAC) Peripheral interrupt flag status - Bridge A */
#define REG_PAC_INTFLAGB           (0x40000018U) /**< \brief (PAC) Peripheral interrupt flag status - Bridge B */
#define REG_PAC_INTFLAGC           (0x4000001CU) /**< \brief (PAC) Peripheral interrupt flag status - Bridge C */
#define REG_PAC_STATUSA            (0x40000034U) /**< \brief (PAC) Peripheral write protection status - Bridge A */
#define REG_PAC_STATUSB            (0x40000038U) /**< \brief (PAC) Peripheral write protection status - Bridge B */
#define REG_PAC_STATUSC            (0x4000003CU) /**< \brief (PAC) Peripheral write protection status - Bridge C */
#else
#define REG_PAC_WRCTRL             (*(RwReg  *)0x40000000U) /**< \brief (PAC) Write control */
#define REG_PAC_EVCTRL             (*(RwReg8 *)0x40000004U) /**< \brief (PAC) Event control */
#define REG_PAC_INTENCLR           (*(RwReg8 *)0x40000008U) /**< \brief (PAC) Interrupt enable clear */
#define REG_PAC_INTENSET           (*(RwReg8 *)0x40000009U) /**< \brief (PAC) Interrupt enable set */
#define REG_PAC_INTFLAGAHB         (*(RwReg  *)0x40000010U) /**< \brief (PAC) Bridge interrupt flag status */
#define REG_PAC_INTFLAGA           (*(RwReg  *)0x40000014U) /**< \brief (PAC) Peripheral interrupt flag status - Bridge A */
#define REG_PAC_INTFLAGB           (*(RwReg  *)0x40000018U) /**< \brief (PAC) Peripheral interrupt flag status - Bridge B */
#define REG_PAC_INTFLAGC           (*(RwReg  *)0x4000001CU) /**< \brief (PAC) Peripheral interrupt flag status - Bridge C */
#define REG_PAC_STATUSA            (*(RoReg  *)0x40000034U) /**< \brief (PAC) Peripheral write protection status - Bridge A */
#define REG_PAC_STATUSB            (*(RoReg  *)0x40000038U) /**< \brief (PAC) Peripheral write protection status - Bridge B */
#define REG_PAC_STATUSC            (*(RoReg  *)0x4000003CU) /**< \brief (PAC) Peripheral write protection status - Bridge C */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for PAC peripheral ========== */
#define PAC_CLK_AHB_DOMAIN                   // Clock domain of AHB clock
#define PAC_CLK_AHB_ID              10       // AHB clock index
#define PAC_HPB_NUM                 3        // Number of bridges AHB/APB
#define PAC_INTFLAG_NUM             4        // Number of intflag registers

#endif /* _SAMC20_PAC_INSTANCE_ */
