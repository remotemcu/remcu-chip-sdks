/**
 * \file
 *
 * \brief Instance description for TC5
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

#ifndef _SAMD20_TC5_INSTANCE_
#define _SAMD20_TC5_INSTANCE_

/* ========== Register definition for TC5 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_TC5_CTRLA              (0x42003400U) /**< \brief (TC5) Control A */
#define REG_TC5_READREQ            (0x42003402U) /**< \brief (TC5) Read Request */
#define REG_TC5_CTRLBCLR           (0x42003404U) /**< \brief (TC5) Control B Clear */
#define REG_TC5_CTRLBSET           (0x42003405U) /**< \brief (TC5) Control B Set */
#define REG_TC5_CTRLC              (0x42003406U) /**< \brief (TC5) Control C */
#define REG_TC5_DBGCTRL            (0x42003408U) /**< \brief (TC5) Debug Control */
#define REG_TC5_EVCTRL             (0x4200340AU) /**< \brief (TC5) Event Control */
#define REG_TC5_INTENCLR           (0x4200340CU) /**< \brief (TC5) Interrupt Enable Clear */
#define REG_TC5_INTENSET           (0x4200340DU) /**< \brief (TC5) Interrupt Enable Set */
#define REG_TC5_INTFLAG            (0x4200340EU) /**< \brief (TC5) Interrupt Flag Status and Clear */
#define REG_TC5_STATUS             (0x4200340FU) /**< \brief (TC5) Status */
#define REG_TC5_COUNT16_COUNT      (0x42003410U) /**< \brief (TC5) COUNT16 Counter Value */
#define REG_TC5_COUNT16_CC0        (0x42003418U) /**< \brief (TC5) COUNT16 Compare/Capture 0 */
#define REG_TC5_COUNT16_CC1        (0x4200341AU) /**< \brief (TC5) COUNT16 Compare/Capture 1 */
#define REG_TC5_COUNT32_COUNT      (0x42003410U) /**< \brief (TC5) COUNT32 Counter Value */
#define REG_TC5_COUNT32_CC0        (0x42003418U) /**< \brief (TC5) COUNT32 Compare/Capture 0 */
#define REG_TC5_COUNT32_CC1        (0x4200341CU) /**< \brief (TC5) COUNT32 Compare/Capture 1 */
#define REG_TC5_COUNT8_COUNT       (0x42003410U) /**< \brief (TC5) COUNT8 Counter Value */
#define REG_TC5_COUNT8_PER         (0x42003414U) /**< \brief (TC5) COUNT8 Period Value */
#define REG_TC5_COUNT8_CC0         (0x42003418U) /**< \brief (TC5) COUNT8 Compare/Capture 0 */
#define REG_TC5_COUNT8_CC1         (0x42003419U) /**< \brief (TC5) COUNT8 Compare/Capture 1 */
#else
#define REG_TC5_CTRLA              (*(RwReg16*)0x42003400U) /**< \brief (TC5) Control A */
#define REG_TC5_READREQ            (*(RwReg16*)0x42003402U) /**< \brief (TC5) Read Request */
#define REG_TC5_CTRLBCLR           (*(RwReg8 *)0x42003404U) /**< \brief (TC5) Control B Clear */
#define REG_TC5_CTRLBSET           (*(RwReg8 *)0x42003405U) /**< \brief (TC5) Control B Set */
#define REG_TC5_CTRLC              (*(RwReg8 *)0x42003406U) /**< \brief (TC5) Control C */
#define REG_TC5_DBGCTRL            (*(RwReg8 *)0x42003408U) /**< \brief (TC5) Debug Control */
#define REG_TC5_EVCTRL             (*(RwReg16*)0x4200340AU) /**< \brief (TC5) Event Control */
#define REG_TC5_INTENCLR           (*(RwReg8 *)0x4200340CU) /**< \brief (TC5) Interrupt Enable Clear */
#define REG_TC5_INTENSET           (*(RwReg8 *)0x4200340DU) /**< \brief (TC5) Interrupt Enable Set */
#define REG_TC5_INTFLAG            (*(RwReg8 *)0x4200340EU) /**< \brief (TC5) Interrupt Flag Status and Clear */
#define REG_TC5_STATUS             (*(RoReg8 *)0x4200340FU) /**< \brief (TC5) Status */
#define REG_TC5_COUNT16_COUNT      (*(RwReg16*)0x42003410U) /**< \brief (TC5) COUNT16 Counter Value */
#define REG_TC5_COUNT16_CC0        (*(RwReg16*)0x42003418U) /**< \brief (TC5) COUNT16 Compare/Capture 0 */
#define REG_TC5_COUNT16_CC1        (*(RwReg16*)0x4200341AU) /**< \brief (TC5) COUNT16 Compare/Capture 1 */
#define REG_TC5_COUNT32_COUNT      (*(RwReg  *)0x42003410U) /**< \brief (TC5) COUNT32 Counter Value */
#define REG_TC5_COUNT32_CC0        (*(RwReg  *)0x42003418U) /**< \brief (TC5) COUNT32 Compare/Capture 0 */
#define REG_TC5_COUNT32_CC1        (*(RwReg  *)0x4200341CU) /**< \brief (TC5) COUNT32 Compare/Capture 1 */
#define REG_TC5_COUNT8_COUNT       (*(RwReg8 *)0x42003410U) /**< \brief (TC5) COUNT8 Counter Value */
#define REG_TC5_COUNT8_PER         (*(RwReg8 *)0x42003414U) /**< \brief (TC5) COUNT8 Period Value */
#define REG_TC5_COUNT8_CC0         (*(RwReg8 *)0x42003418U) /**< \brief (TC5) COUNT8 Compare/Capture 0 */
#define REG_TC5_COUNT8_CC1         (*(RwReg8 *)0x42003419U) /**< \brief (TC5) COUNT8 Compare/Capture 1 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for TC5 peripheral ========== */
#define TC5_CC8_NUM                 2
#define TC5_CC16_NUM                2
#define TC5_CC32_NUM                2
#define TC5_DITHERING_EXT           0
#define TC5_GCLK_ID                 21
#define TC5_MASTER                  0
#define TC5_OW_NUM                  2
#define TC5_PERIOD_EXT              0
#define TC5_SHADOW_EXT              0

#endif /* _SAMD20_TC5_INSTANCE_ */
