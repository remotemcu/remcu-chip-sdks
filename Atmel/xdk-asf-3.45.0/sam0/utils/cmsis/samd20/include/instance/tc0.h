/**
 * \file
 *
 * \brief Instance description for TC0
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

#ifndef _SAMD20_TC0_INSTANCE_
#define _SAMD20_TC0_INSTANCE_

/* ========== Register definition for TC0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_TC0_CTRLA              (0x42002000U) /**< \brief (TC0) Control A */
#define REG_TC0_READREQ            (0x42002002U) /**< \brief (TC0) Read Request */
#define REG_TC0_CTRLBCLR           (0x42002004U) /**< \brief (TC0) Control B Clear */
#define REG_TC0_CTRLBSET           (0x42002005U) /**< \brief (TC0) Control B Set */
#define REG_TC0_CTRLC              (0x42002006U) /**< \brief (TC0) Control C */
#define REG_TC0_DBGCTRL            (0x42002008U) /**< \brief (TC0) Debug Control */
#define REG_TC0_EVCTRL             (0x4200200AU) /**< \brief (TC0) Event Control */
#define REG_TC0_INTENCLR           (0x4200200CU) /**< \brief (TC0) Interrupt Enable Clear */
#define REG_TC0_INTENSET           (0x4200200DU) /**< \brief (TC0) Interrupt Enable Set */
#define REG_TC0_INTFLAG            (0x4200200EU) /**< \brief (TC0) Interrupt Flag Status and Clear */
#define REG_TC0_STATUS             (0x4200200FU) /**< \brief (TC0) Status */
#define REG_TC0_COUNT16_COUNT      (0x42002010U) /**< \brief (TC0) COUNT16 Counter Value */
#define REG_TC0_COUNT16_CC0        (0x42002018U) /**< \brief (TC0) COUNT16 Compare/Capture 0 */
#define REG_TC0_COUNT16_CC1        (0x4200201AU) /**< \brief (TC0) COUNT16 Compare/Capture 1 */
#define REG_TC0_COUNT32_COUNT      (0x42002010U) /**< \brief (TC0) COUNT32 Counter Value */
#define REG_TC0_COUNT32_CC0        (0x42002018U) /**< \brief (TC0) COUNT32 Compare/Capture 0 */
#define REG_TC0_COUNT32_CC1        (0x4200201CU) /**< \brief (TC0) COUNT32 Compare/Capture 1 */
#define REG_TC0_COUNT8_COUNT       (0x42002010U) /**< \brief (TC0) COUNT8 Counter Value */
#define REG_TC0_COUNT8_PER         (0x42002014U) /**< \brief (TC0) COUNT8 Period Value */
#define REG_TC0_COUNT8_CC0         (0x42002018U) /**< \brief (TC0) COUNT8 Compare/Capture 0 */
#define REG_TC0_COUNT8_CC1         (0x42002019U) /**< \brief (TC0) COUNT8 Compare/Capture 1 */
#else
#define REG_TC0_CTRLA              (*(RwReg16*)0x42002000U) /**< \brief (TC0) Control A */
#define REG_TC0_READREQ            (*(RwReg16*)0x42002002U) /**< \brief (TC0) Read Request */
#define REG_TC0_CTRLBCLR           (*(RwReg8 *)0x42002004U) /**< \brief (TC0) Control B Clear */
#define REG_TC0_CTRLBSET           (*(RwReg8 *)0x42002005U) /**< \brief (TC0) Control B Set */
#define REG_TC0_CTRLC              (*(RwReg8 *)0x42002006U) /**< \brief (TC0) Control C */
#define REG_TC0_DBGCTRL            (*(RwReg8 *)0x42002008U) /**< \brief (TC0) Debug Control */
#define REG_TC0_EVCTRL             (*(RwReg16*)0x4200200AU) /**< \brief (TC0) Event Control */
#define REG_TC0_INTENCLR           (*(RwReg8 *)0x4200200CU) /**< \brief (TC0) Interrupt Enable Clear */
#define REG_TC0_INTENSET           (*(RwReg8 *)0x4200200DU) /**< \brief (TC0) Interrupt Enable Set */
#define REG_TC0_INTFLAG            (*(RwReg8 *)0x4200200EU) /**< \brief (TC0) Interrupt Flag Status and Clear */
#define REG_TC0_STATUS             (*(RoReg8 *)0x4200200FU) /**< \brief (TC0) Status */
#define REG_TC0_COUNT16_COUNT      (*(RwReg16*)0x42002010U) /**< \brief (TC0) COUNT16 Counter Value */
#define REG_TC0_COUNT16_CC0        (*(RwReg16*)0x42002018U) /**< \brief (TC0) COUNT16 Compare/Capture 0 */
#define REG_TC0_COUNT16_CC1        (*(RwReg16*)0x4200201AU) /**< \brief (TC0) COUNT16 Compare/Capture 1 */
#define REG_TC0_COUNT32_COUNT      (*(RwReg  *)0x42002010U) /**< \brief (TC0) COUNT32 Counter Value */
#define REG_TC0_COUNT32_CC0        (*(RwReg  *)0x42002018U) /**< \brief (TC0) COUNT32 Compare/Capture 0 */
#define REG_TC0_COUNT32_CC1        (*(RwReg  *)0x4200201CU) /**< \brief (TC0) COUNT32 Compare/Capture 1 */
#define REG_TC0_COUNT8_COUNT       (*(RwReg8 *)0x42002010U) /**< \brief (TC0) COUNT8 Counter Value */
#define REG_TC0_COUNT8_PER         (*(RwReg8 *)0x42002014U) /**< \brief (TC0) COUNT8 Period Value */
#define REG_TC0_COUNT8_CC0         (*(RwReg8 *)0x42002018U) /**< \brief (TC0) COUNT8 Compare/Capture 0 */
#define REG_TC0_COUNT8_CC1         (*(RwReg8 *)0x42002019U) /**< \brief (TC0) COUNT8 Compare/Capture 1 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for TC0 peripheral ========== */
#define TC0_CC8_NUM                 2
#define TC0_CC16_NUM                2
#define TC0_CC32_NUM                2
#define TC0_DITHERING_EXT           0
#define TC0_GCLK_ID                 19
#define TC0_MASTER                  1
#define TC0_OW_NUM                  2
#define TC0_PERIOD_EXT              0
#define TC0_SHADOW_EXT              0

#endif /* _SAMD20_TC0_INSTANCE_ */
