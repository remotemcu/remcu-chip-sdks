/**
 * \file
 *
 * \brief Instance description for TC7
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

#ifndef _SAMD20_TC7_INSTANCE_
#define _SAMD20_TC7_INSTANCE_

/* ========== Register definition for TC7 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_TC7_CTRLA              (0x42003C00U) /**< \brief (TC7) Control A */
#define REG_TC7_READREQ            (0x42003C02U) /**< \brief (TC7) Read Request */
#define REG_TC7_CTRLBCLR           (0x42003C04U) /**< \brief (TC7) Control B Clear */
#define REG_TC7_CTRLBSET           (0x42003C05U) /**< \brief (TC7) Control B Set */
#define REG_TC7_CTRLC              (0x42003C06U) /**< \brief (TC7) Control C */
#define REG_TC7_DBGCTRL            (0x42003C08U) /**< \brief (TC7) Debug Control */
#define REG_TC7_EVCTRL             (0x42003C0AU) /**< \brief (TC7) Event Control */
#define REG_TC7_INTENCLR           (0x42003C0CU) /**< \brief (TC7) Interrupt Enable Clear */
#define REG_TC7_INTENSET           (0x42003C0DU) /**< \brief (TC7) Interrupt Enable Set */
#define REG_TC7_INTFLAG            (0x42003C0EU) /**< \brief (TC7) Interrupt Flag Status and Clear */
#define REG_TC7_STATUS             (0x42003C0FU) /**< \brief (TC7) Status */
#define REG_TC7_COUNT16_COUNT      (0x42003C10U) /**< \brief (TC7) COUNT16 Counter Value */
#define REG_TC7_COUNT16_CC0        (0x42003C18U) /**< \brief (TC7) COUNT16 Compare/Capture 0 */
#define REG_TC7_COUNT16_CC1        (0x42003C1AU) /**< \brief (TC7) COUNT16 Compare/Capture 1 */
#define REG_TC7_COUNT32_COUNT      (0x42003C10U) /**< \brief (TC7) COUNT32 Counter Value */
#define REG_TC7_COUNT32_CC0        (0x42003C18U) /**< \brief (TC7) COUNT32 Compare/Capture 0 */
#define REG_TC7_COUNT32_CC1        (0x42003C1CU) /**< \brief (TC7) COUNT32 Compare/Capture 1 */
#define REG_TC7_COUNT8_COUNT       (0x42003C10U) /**< \brief (TC7) COUNT8 Counter Value */
#define REG_TC7_COUNT8_PER         (0x42003C14U) /**< \brief (TC7) COUNT8 Period Value */
#define REG_TC7_COUNT8_CC0         (0x42003C18U) /**< \brief (TC7) COUNT8 Compare/Capture 0 */
#define REG_TC7_COUNT8_CC1         (0x42003C19U) /**< \brief (TC7) COUNT8 Compare/Capture 1 */
#else
#define REG_TC7_CTRLA              (*(RwReg16*)0x42003C00U) /**< \brief (TC7) Control A */
#define REG_TC7_READREQ            (*(RwReg16*)0x42003C02U) /**< \brief (TC7) Read Request */
#define REG_TC7_CTRLBCLR           (*(RwReg8 *)0x42003C04U) /**< \brief (TC7) Control B Clear */
#define REG_TC7_CTRLBSET           (*(RwReg8 *)0x42003C05U) /**< \brief (TC7) Control B Set */
#define REG_TC7_CTRLC              (*(RwReg8 *)0x42003C06U) /**< \brief (TC7) Control C */
#define REG_TC7_DBGCTRL            (*(RwReg8 *)0x42003C08U) /**< \brief (TC7) Debug Control */
#define REG_TC7_EVCTRL             (*(RwReg16*)0x42003C0AU) /**< \brief (TC7) Event Control */
#define REG_TC7_INTENCLR           (*(RwReg8 *)0x42003C0CU) /**< \brief (TC7) Interrupt Enable Clear */
#define REG_TC7_INTENSET           (*(RwReg8 *)0x42003C0DU) /**< \brief (TC7) Interrupt Enable Set */
#define REG_TC7_INTFLAG            (*(RwReg8 *)0x42003C0EU) /**< \brief (TC7) Interrupt Flag Status and Clear */
#define REG_TC7_STATUS             (*(RoReg8 *)0x42003C0FU) /**< \brief (TC7) Status */
#define REG_TC7_COUNT16_COUNT      (*(RwReg16*)0x42003C10U) /**< \brief (TC7) COUNT16 Counter Value */
#define REG_TC7_COUNT16_CC0        (*(RwReg16*)0x42003C18U) /**< \brief (TC7) COUNT16 Compare/Capture 0 */
#define REG_TC7_COUNT16_CC1        (*(RwReg16*)0x42003C1AU) /**< \brief (TC7) COUNT16 Compare/Capture 1 */
#define REG_TC7_COUNT32_COUNT      (*(RwReg  *)0x42003C10U) /**< \brief (TC7) COUNT32 Counter Value */
#define REG_TC7_COUNT32_CC0        (*(RwReg  *)0x42003C18U) /**< \brief (TC7) COUNT32 Compare/Capture 0 */
#define REG_TC7_COUNT32_CC1        (*(RwReg  *)0x42003C1CU) /**< \brief (TC7) COUNT32 Compare/Capture 1 */
#define REG_TC7_COUNT8_COUNT       (*(RwReg8 *)0x42003C10U) /**< \brief (TC7) COUNT8 Counter Value */
#define REG_TC7_COUNT8_PER         (*(RwReg8 *)0x42003C14U) /**< \brief (TC7) COUNT8 Period Value */
#define REG_TC7_COUNT8_CC0         (*(RwReg8 *)0x42003C18U) /**< \brief (TC7) COUNT8 Compare/Capture 0 */
#define REG_TC7_COUNT8_CC1         (*(RwReg8 *)0x42003C19U) /**< \brief (TC7) COUNT8 Compare/Capture 1 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for TC7 peripheral ========== */
#define TC7_CC8_NUM                 2
#define TC7_CC16_NUM                2
#define TC7_CC32_NUM                2
#define TC7_DITHERING_EXT           0
#define TC7_GCLK_ID                 22
#define TC7_MASTER                  0
#define TC7_OW_NUM                  2
#define TC7_PERIOD_EXT              0
#define TC7_SHADOW_EXT              0

#endif /* _SAMD20_TC7_INSTANCE_ */
