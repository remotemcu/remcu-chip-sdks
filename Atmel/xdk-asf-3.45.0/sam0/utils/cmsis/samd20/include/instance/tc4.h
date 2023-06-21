/**
 * \file
 *
 * \brief Instance description for TC4
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

#ifndef _SAMD20_TC4_INSTANCE_
#define _SAMD20_TC4_INSTANCE_

/* ========== Register definition for TC4 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_TC4_CTRLA              (0x42003000U) /**< \brief (TC4) Control A */
#define REG_TC4_READREQ            (0x42003002U) /**< \brief (TC4) Read Request */
#define REG_TC4_CTRLBCLR           (0x42003004U) /**< \brief (TC4) Control B Clear */
#define REG_TC4_CTRLBSET           (0x42003005U) /**< \brief (TC4) Control B Set */
#define REG_TC4_CTRLC              (0x42003006U) /**< \brief (TC4) Control C */
#define REG_TC4_DBGCTRL            (0x42003008U) /**< \brief (TC4) Debug Control */
#define REG_TC4_EVCTRL             (0x4200300AU) /**< \brief (TC4) Event Control */
#define REG_TC4_INTENCLR           (0x4200300CU) /**< \brief (TC4) Interrupt Enable Clear */
#define REG_TC4_INTENSET           (0x4200300DU) /**< \brief (TC4) Interrupt Enable Set */
#define REG_TC4_INTFLAG            (0x4200300EU) /**< \brief (TC4) Interrupt Flag Status and Clear */
#define REG_TC4_STATUS             (0x4200300FU) /**< \brief (TC4) Status */
#define REG_TC4_COUNT16_COUNT      (0x42003010U) /**< \brief (TC4) COUNT16 Counter Value */
#define REG_TC4_COUNT16_CC0        (0x42003018U) /**< \brief (TC4) COUNT16 Compare/Capture 0 */
#define REG_TC4_COUNT16_CC1        (0x4200301AU) /**< \brief (TC4) COUNT16 Compare/Capture 1 */
#define REG_TC4_COUNT32_COUNT      (0x42003010U) /**< \brief (TC4) COUNT32 Counter Value */
#define REG_TC4_COUNT32_CC0        (0x42003018U) /**< \brief (TC4) COUNT32 Compare/Capture 0 */
#define REG_TC4_COUNT32_CC1        (0x4200301CU) /**< \brief (TC4) COUNT32 Compare/Capture 1 */
#define REG_TC4_COUNT8_COUNT       (0x42003010U) /**< \brief (TC4) COUNT8 Counter Value */
#define REG_TC4_COUNT8_PER         (0x42003014U) /**< \brief (TC4) COUNT8 Period Value */
#define REG_TC4_COUNT8_CC0         (0x42003018U) /**< \brief (TC4) COUNT8 Compare/Capture 0 */
#define REG_TC4_COUNT8_CC1         (0x42003019U) /**< \brief (TC4) COUNT8 Compare/Capture 1 */
#else
#define REG_TC4_CTRLA              (*(RwReg16*)0x42003000U) /**< \brief (TC4) Control A */
#define REG_TC4_READREQ            (*(RwReg16*)0x42003002U) /**< \brief (TC4) Read Request */
#define REG_TC4_CTRLBCLR           (*(RwReg8 *)0x42003004U) /**< \brief (TC4) Control B Clear */
#define REG_TC4_CTRLBSET           (*(RwReg8 *)0x42003005U) /**< \brief (TC4) Control B Set */
#define REG_TC4_CTRLC              (*(RwReg8 *)0x42003006U) /**< \brief (TC4) Control C */
#define REG_TC4_DBGCTRL            (*(RwReg8 *)0x42003008U) /**< \brief (TC4) Debug Control */
#define REG_TC4_EVCTRL             (*(RwReg16*)0x4200300AU) /**< \brief (TC4) Event Control */
#define REG_TC4_INTENCLR           (*(RwReg8 *)0x4200300CU) /**< \brief (TC4) Interrupt Enable Clear */
#define REG_TC4_INTENSET           (*(RwReg8 *)0x4200300DU) /**< \brief (TC4) Interrupt Enable Set */
#define REG_TC4_INTFLAG            (*(RwReg8 *)0x4200300EU) /**< \brief (TC4) Interrupt Flag Status and Clear */
#define REG_TC4_STATUS             (*(RoReg8 *)0x4200300FU) /**< \brief (TC4) Status */
#define REG_TC4_COUNT16_COUNT      (*(RwReg16*)0x42003010U) /**< \brief (TC4) COUNT16 Counter Value */
#define REG_TC4_COUNT16_CC0        (*(RwReg16*)0x42003018U) /**< \brief (TC4) COUNT16 Compare/Capture 0 */
#define REG_TC4_COUNT16_CC1        (*(RwReg16*)0x4200301AU) /**< \brief (TC4) COUNT16 Compare/Capture 1 */
#define REG_TC4_COUNT32_COUNT      (*(RwReg  *)0x42003010U) /**< \brief (TC4) COUNT32 Counter Value */
#define REG_TC4_COUNT32_CC0        (*(RwReg  *)0x42003018U) /**< \brief (TC4) COUNT32 Compare/Capture 0 */
#define REG_TC4_COUNT32_CC1        (*(RwReg  *)0x4200301CU) /**< \brief (TC4) COUNT32 Compare/Capture 1 */
#define REG_TC4_COUNT8_COUNT       (*(RwReg8 *)0x42003010U) /**< \brief (TC4) COUNT8 Counter Value */
#define REG_TC4_COUNT8_PER         (*(RwReg8 *)0x42003014U) /**< \brief (TC4) COUNT8 Period Value */
#define REG_TC4_COUNT8_CC0         (*(RwReg8 *)0x42003018U) /**< \brief (TC4) COUNT8 Compare/Capture 0 */
#define REG_TC4_COUNT8_CC1         (*(RwReg8 *)0x42003019U) /**< \brief (TC4) COUNT8 Compare/Capture 1 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for TC4 peripheral ========== */
#define TC4_CC8_NUM                 2
#define TC4_CC16_NUM                2
#define TC4_CC32_NUM                2
#define TC4_DITHERING_EXT           0
#define TC4_GCLK_ID                 21
#define TC4_MASTER                  1
#define TC4_OW_NUM                  2
#define TC4_PERIOD_EXT              0
#define TC4_SHADOW_EXT              0

#endif /* _SAMD20_TC4_INSTANCE_ */
