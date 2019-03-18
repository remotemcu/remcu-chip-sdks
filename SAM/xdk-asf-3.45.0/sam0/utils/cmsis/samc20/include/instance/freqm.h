/**
 * \file
 *
 * \brief Instance description for FREQM
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _SAMC20_FREQM_INSTANCE_
#define _SAMC20_FREQM_INSTANCE_

/* ========== Register definition for FREQM peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_FREQM_CTRLA            (0x40002C00U) /**< \brief (FREQM) Control A Register */
#define REG_FREQM_CTRLB            (0x40002C01U) /**< \brief (FREQM) Control B Register */
#define REG_FREQM_CFGA             (0x40002C02U) /**< \brief (FREQM) Config A register */
#define REG_FREQM_INTENCLR         (0x40002C08U) /**< \brief (FREQM) Interrupt Enable Clear Register */
#define REG_FREQM_INTENSET         (0x40002C09U) /**< \brief (FREQM) Interrupt Enable Set Register */
#define REG_FREQM_INTFLAG          (0x40002C0AU) /**< \brief (FREQM) Interrupt Flag Register */
#define REG_FREQM_STATUS           (0x40002C0BU) /**< \brief (FREQM) Status Register */
#define REG_FREQM_SYNCBUSY         (0x40002C0CU) /**< \brief (FREQM) Synchronization Busy Register */
#define REG_FREQM_VALUE            (0x40002C10U) /**< \brief (FREQM) Count Value Register */
#else
#define REG_FREQM_CTRLA            (*(RwReg8 *)0x40002C00U) /**< \brief (FREQM) Control A Register */
#define REG_FREQM_CTRLB            (*(WoReg8 *)0x40002C01U) /**< \brief (FREQM) Control B Register */
#define REG_FREQM_CFGA             (*(RwReg16*)0x40002C02U) /**< \brief (FREQM) Config A register */
#define REG_FREQM_INTENCLR         (*(RwReg8 *)0x40002C08U) /**< \brief (FREQM) Interrupt Enable Clear Register */
#define REG_FREQM_INTENSET         (*(RwReg8 *)0x40002C09U) /**< \brief (FREQM) Interrupt Enable Set Register */
#define REG_FREQM_INTFLAG          (*(RwReg8 *)0x40002C0AU) /**< \brief (FREQM) Interrupt Flag Register */
#define REG_FREQM_STATUS           (*(RwReg8 *)0x40002C0BU) /**< \brief (FREQM) Status Register */
#define REG_FREQM_SYNCBUSY         (*(RoReg  *)0x40002C0CU) /**< \brief (FREQM) Synchronization Busy Register */
#define REG_FREQM_VALUE            (*(RoReg  *)0x40002C10U) /**< \brief (FREQM) Count Value Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for FREQM peripheral ========== */
#define FREQM_GCLK_ID_MSR           3        // Index of measure generic clock
#define FREQM_GCLK_ID_REF           4        // Index of reference generic clock

#endif /* _SAMC20_FREQM_INSTANCE_ */
