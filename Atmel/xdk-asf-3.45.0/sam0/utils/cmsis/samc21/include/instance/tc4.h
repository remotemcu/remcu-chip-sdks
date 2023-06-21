/**
 * \file
 *
 * \brief Instance description for TC4
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

#ifndef _SAMC21_TC4_INSTANCE_
#define _SAMC21_TC4_INSTANCE_

/* ========== Register definition for TC4 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_TC4_CTRLA              (0x42004000U) /**< \brief (TC4) Control A */
#define REG_TC4_CTRLBCLR           (0x42004004U) /**< \brief (TC4) Control B Clear */
#define REG_TC4_CTRLBSET           (0x42004005U) /**< \brief (TC4) Control B Set */
#define REG_TC4_EVCTRL             (0x42004006U) /**< \brief (TC4) Event Control */
#define REG_TC4_INTENCLR           (0x42004008U) /**< \brief (TC4) Interrupt Enable Clear */
#define REG_TC4_INTENSET           (0x42004009U) /**< \brief (TC4) Interrupt Enable Set */
#define REG_TC4_INTFLAG            (0x4200400AU) /**< \brief (TC4) Interrupt Flag Status and Clear */
#define REG_TC4_STATUS             (0x4200400BU) /**< \brief (TC4) Status */
#define REG_TC4_WAVE               (0x4200400CU) /**< \brief (TC4) Waveform Generation Control */
#define REG_TC4_DRVCTRL            (0x4200400DU) /**< \brief (TC4) Control C */
#define REG_TC4_DBGCTRL            (0x4200400FU) /**< \brief (TC4) Debug Control */
#define REG_TC4_SYNCBUSY           (0x42004010U) /**< \brief (TC4) Synchronization Status */
#define REG_TC4_COUNT16_COUNT      (0x42004014U) /**< \brief (TC4) COUNT16 Count */
#define REG_TC4_COUNT16_CC0        (0x4200401CU) /**< \brief (TC4) COUNT16 Compare and Capture 0 */
#define REG_TC4_COUNT16_CC1        (0x4200401EU) /**< \brief (TC4) COUNT16 Compare and Capture 1 */
#define REG_TC4_COUNT16_CCBUF0     (0x42004030U) /**< \brief (TC4) COUNT16 Compare and Capture Buffer 0 */
#define REG_TC4_COUNT16_CCBUF1     (0x42004032U) /**< \brief (TC4) COUNT16 Compare and Capture Buffer 1 */
#define REG_TC4_COUNT32_COUNT      (0x42004014U) /**< \brief (TC4) COUNT32 Count */
#define REG_TC4_COUNT32_CC0        (0x4200401CU) /**< \brief (TC4) COUNT32 Compare and Capture 0 */
#define REG_TC4_COUNT32_CC1        (0x42004020U) /**< \brief (TC4) COUNT32 Compare and Capture 1 */
#define REG_TC4_COUNT32_CCBUF0     (0x42004030U) /**< \brief (TC4) COUNT32 Compare and Capture Buffer 0 */
#define REG_TC4_COUNT32_CCBUF1     (0x42004034U) /**< \brief (TC4) COUNT32 Compare and Capture Buffer 1 */
#define REG_TC4_COUNT8_COUNT       (0x42004014U) /**< \brief (TC4) COUNT8 Count */
#define REG_TC4_COUNT8_PER         (0x4200401BU) /**< \brief (TC4) COUNT8 Period */
#define REG_TC4_COUNT8_CC0         (0x4200401CU) /**< \brief (TC4) COUNT8 Compare and Capture 0 */
#define REG_TC4_COUNT8_CC1         (0x4200401DU) /**< \brief (TC4) COUNT8 Compare and Capture 1 */
#define REG_TC4_COUNT8_PERBUF      (0x4200402FU) /**< \brief (TC4) COUNT8 Period Buffer */
#define REG_TC4_COUNT8_CCBUF0      (0x42004030U) /**< \brief (TC4) COUNT8 Compare and Capture Buffer 0 */
#define REG_TC4_COUNT8_CCBUF1      (0x42004031U) /**< \brief (TC4) COUNT8 Compare and Capture Buffer 1 */
#else
#define REG_TC4_CTRLA              (*(RwReg  *)0x42004000U) /**< \brief (TC4) Control A */
#define REG_TC4_CTRLBCLR           (*(RwReg8 *)0x42004004U) /**< \brief (TC4) Control B Clear */
#define REG_TC4_CTRLBSET           (*(RwReg8 *)0x42004005U) /**< \brief (TC4) Control B Set */
#define REG_TC4_EVCTRL             (*(RwReg16*)0x42004006U) /**< \brief (TC4) Event Control */
#define REG_TC4_INTENCLR           (*(RwReg8 *)0x42004008U) /**< \brief (TC4) Interrupt Enable Clear */
#define REG_TC4_INTENSET           (*(RwReg8 *)0x42004009U) /**< \brief (TC4) Interrupt Enable Set */
#define REG_TC4_INTFLAG            (*(RwReg8 *)0x4200400AU) /**< \brief (TC4) Interrupt Flag Status and Clear */
#define REG_TC4_STATUS             (*(RwReg8 *)0x4200400BU) /**< \brief (TC4) Status */
#define REG_TC4_WAVE               (*(RwReg8 *)0x4200400CU) /**< \brief (TC4) Waveform Generation Control */
#define REG_TC4_DRVCTRL            (*(RwReg8 *)0x4200400DU) /**< \brief (TC4) Control C */
#define REG_TC4_DBGCTRL            (*(RwReg8 *)0x4200400FU) /**< \brief (TC4) Debug Control */
#define REG_TC4_SYNCBUSY           (*(RoReg  *)0x42004010U) /**< \brief (TC4) Synchronization Status */
#define REG_TC4_COUNT16_COUNT      (*(RwReg16*)0x42004014U) /**< \brief (TC4) COUNT16 Count */
#define REG_TC4_COUNT16_CC0        (*(RwReg16*)0x4200401CU) /**< \brief (TC4) COUNT16 Compare and Capture 0 */
#define REG_TC4_COUNT16_CC1        (*(RwReg16*)0x4200401EU) /**< \brief (TC4) COUNT16 Compare and Capture 1 */
#define REG_TC4_COUNT16_CCBUF0     (*(RwReg16*)0x42004030U) /**< \brief (TC4) COUNT16 Compare and Capture Buffer 0 */
#define REG_TC4_COUNT16_CCBUF1     (*(RwReg16*)0x42004032U) /**< \brief (TC4) COUNT16 Compare and Capture Buffer 1 */
#define REG_TC4_COUNT32_COUNT      (*(RwReg  *)0x42004014U) /**< \brief (TC4) COUNT32 Count */
#define REG_TC4_COUNT32_CC0        (*(RwReg  *)0x4200401CU) /**< \brief (TC4) COUNT32 Compare and Capture 0 */
#define REG_TC4_COUNT32_CC1        (*(RwReg  *)0x42004020U) /**< \brief (TC4) COUNT32 Compare and Capture 1 */
#define REG_TC4_COUNT32_CCBUF0     (*(RwReg  *)0x42004030U) /**< \brief (TC4) COUNT32 Compare and Capture Buffer 0 */
#define REG_TC4_COUNT32_CCBUF1     (*(RwReg  *)0x42004034U) /**< \brief (TC4) COUNT32 Compare and Capture Buffer 1 */
#define REG_TC4_COUNT8_COUNT       (*(RwReg8 *)0x42004014U) /**< \brief (TC4) COUNT8 Count */
#define REG_TC4_COUNT8_PER         (*(RwReg8 *)0x4200401BU) /**< \brief (TC4) COUNT8 Period */
#define REG_TC4_COUNT8_CC0         (*(RwReg8 *)0x4200401CU) /**< \brief (TC4) COUNT8 Compare and Capture 0 */
#define REG_TC4_COUNT8_CC1         (*(RwReg8 *)0x4200401DU) /**< \brief (TC4) COUNT8 Compare and Capture 1 */
#define REG_TC4_COUNT8_PERBUF      (*(RwReg8 *)0x4200402FU) /**< \brief (TC4) COUNT8 Period Buffer */
#define REG_TC4_COUNT8_CCBUF0      (*(RwReg8 *)0x42004030U) /**< \brief (TC4) COUNT8 Compare and Capture Buffer 0 */
#define REG_TC4_COUNT8_CCBUF1      (*(RwReg8 *)0x42004031U) /**< \brief (TC4) COUNT8 Compare and Capture Buffer 1 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for TC4 peripheral ========== */
#define TC4_CC_NUM                  2       
#define TC4_DMAC_ID_MC_0            40
#define TC4_DMAC_ID_MC_1            41
#define TC4_DMAC_ID_MC_LSB          40
#define TC4_DMAC_ID_MC_MSB          41
#define TC4_DMAC_ID_MC_SIZE         2
#define TC4_DMAC_ID_OVF             39       // Indexes of DMA Overflow trigger
#define TC4_EXT                     0       
#define TC4_GCLK_ID                 32      
#define TC4_MASTER                  0       
#define TC4_OW_NUM                  2       

#endif /* _SAMC21_TC4_INSTANCE_ */
