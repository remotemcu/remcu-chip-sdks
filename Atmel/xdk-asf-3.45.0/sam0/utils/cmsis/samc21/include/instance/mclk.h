/**
 * \file
 *
 * \brief Instance description for MCLK
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

#ifndef _SAMC21_MCLK_INSTANCE_
#define _SAMC21_MCLK_INSTANCE_

/* ========== Register definition for MCLK peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_MCLK_INTENCLR          (0x40000801U) /**< \brief (MCLK) Interrupt Enable Clear */
#define REG_MCLK_INTENSET          (0x40000802U) /**< \brief (MCLK) Interrupt Enable Set */
#define REG_MCLK_INTFLAG           (0x40000803U) /**< \brief (MCLK) Interrupt Flag Status and Clear */
#define REG_MCLK_CPUDIV            (0x40000804U) /**< \brief (MCLK) CPU Clock Division */
#define REG_MCLK_AHBMASK           (0x40000810U) /**< \brief (MCLK) AHB Mask */
#define REG_MCLK_APBAMASK          (0x40000814U) /**< \brief (MCLK) APBA Mask */
#define REG_MCLK_APBBMASK          (0x40000818U) /**< \brief (MCLK) APBB Mask */
#define REG_MCLK_APBCMASK          (0x4000081CU) /**< \brief (MCLK) APBC Mask */
#else
#define REG_MCLK_INTENCLR          (*(RwReg8 *)0x40000801U) /**< \brief (MCLK) Interrupt Enable Clear */
#define REG_MCLK_INTENSET          (*(RwReg8 *)0x40000802U) /**< \brief (MCLK) Interrupt Enable Set */
#define REG_MCLK_INTFLAG           (*(RwReg8 *)0x40000803U) /**< \brief (MCLK) Interrupt Flag Status and Clear */
#define REG_MCLK_CPUDIV            (*(RwReg8 *)0x40000804U) /**< \brief (MCLK) CPU Clock Division */
#define REG_MCLK_AHBMASK           (*(RwReg  *)0x40000810U) /**< \brief (MCLK) AHB Mask */
#define REG_MCLK_APBAMASK          (*(RwReg  *)0x40000814U) /**< \brief (MCLK) APBA Mask */
#define REG_MCLK_APBBMASK          (*(RwReg  *)0x40000818U) /**< \brief (MCLK) APBB Mask */
#define REG_MCLK_APBCMASK          (*(RwReg  *)0x4000081CU) /**< \brief (MCLK) APBC Mask */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for MCLK peripheral ========== */
#define MCLK_CTRLA_MCSEL_GCLK       1       
#define MCLK_CTRLA_MCSEL_OSC8M      0       
#define MCLK_MCLK_CLK_APB_NUM       3       
#define MCLK_SYSTEM_CLOCK           4000000  // System Clock Frequency at Reset

#endif /* _SAMC21_MCLK_INSTANCE_ */
