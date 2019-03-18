/**
 * \file
 *
 * \brief Instance description for TSENS
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

#ifndef _SAMC21_TSENS_INSTANCE_
#define _SAMC21_TSENS_INSTANCE_

/* ========== Register definition for TSENS peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_TSENS_CTRLA            (0x40003000U) /**< \brief (TSENS) Control A Register */
#define REG_TSENS_CTRLB            (0x40003001U) /**< \brief (TSENS) Control B Register */
#define REG_TSENS_CTRLC            (0x40003002U) /**< \brief (TSENS) Control C Register */
#define REG_TSENS_EVCTRL           (0x40003003U) /**< \brief (TSENS) Event Control Register */
#define REG_TSENS_INTENCLR         (0x40003004U) /**< \brief (TSENS) Interrupt Enable Clear Register */
#define REG_TSENS_INTENSET         (0x40003005U) /**< \brief (TSENS) Interrupt Enable Set Register */
#define REG_TSENS_INTFLAG          (0x40003006U) /**< \brief (TSENS) Interrupt Flag Status and Clear Register */
#define REG_TSENS_STATUS           (0x40003007U) /**< \brief (TSENS) Status Register */
#define REG_TSENS_SYNCBUSY         (0x40003008U) /**< \brief (TSENS) Synchronization Busy Register */
#define REG_TSENS_VALUE            (0x4000300CU) /**< \brief (TSENS) Value Register */
#define REG_TSENS_WINLT            (0x40003010U) /**< \brief (TSENS) Window Monitor Lower Threshold Register */
#define REG_TSENS_WINUT            (0x40003014U) /**< \brief (TSENS) Window Monitor Upper Threshold Register */
#define REG_TSENS_GAIN             (0x40003018U) /**< \brief (TSENS) Gain Register */
#define REG_TSENS_OFFSET           (0x4000301CU) /**< \brief (TSENS) Offset Register */
#define REG_TSENS_CAL              (0x40003020U) /**< \brief (TSENS) Calibration Register */
#define REG_TSENS_DBGCTRL          (0x40003024U) /**< \brief (TSENS) Debug Control Register */
#else
#define REG_TSENS_CTRLA            (*(RwReg8 *)0x40003000U) /**< \brief (TSENS) Control A Register */
#define REG_TSENS_CTRLB            (*(WoReg8 *)0x40003001U) /**< \brief (TSENS) Control B Register */
#define REG_TSENS_CTRLC            (*(RwReg8 *)0x40003002U) /**< \brief (TSENS) Control C Register */
#define REG_TSENS_EVCTRL           (*(RwReg8 *)0x40003003U) /**< \brief (TSENS) Event Control Register */
#define REG_TSENS_INTENCLR         (*(RwReg8 *)0x40003004U) /**< \brief (TSENS) Interrupt Enable Clear Register */
#define REG_TSENS_INTENSET         (*(RwReg8 *)0x40003005U) /**< \brief (TSENS) Interrupt Enable Set Register */
#define REG_TSENS_INTFLAG          (*(RwReg8 *)0x40003006U) /**< \brief (TSENS) Interrupt Flag Status and Clear Register */
#define REG_TSENS_STATUS           (*(RoReg8 *)0x40003007U) /**< \brief (TSENS) Status Register */
#define REG_TSENS_SYNCBUSY         (*(RoReg  *)0x40003008U) /**< \brief (TSENS) Synchronization Busy Register */
#define REG_TSENS_VALUE            (*(RoReg  *)0x4000300CU) /**< \brief (TSENS) Value Register */
#define REG_TSENS_WINLT            (*(RwReg  *)0x40003010U) /**< \brief (TSENS) Window Monitor Lower Threshold Register */
#define REG_TSENS_WINUT            (*(RwReg  *)0x40003014U) /**< \brief (TSENS) Window Monitor Upper Threshold Register */
#define REG_TSENS_GAIN             (*(RwReg  *)0x40003018U) /**< \brief (TSENS) Gain Register */
#define REG_TSENS_OFFSET           (*(RwReg  *)0x4000301CU) /**< \brief (TSENS) Offset Register */
#define REG_TSENS_CAL              (*(RwReg  *)0x40003020U) /**< \brief (TSENS) Calibration Register */
#define REG_TSENS_DBGCTRL          (*(RwReg8 *)0x40003024U) /**< \brief (TSENS) Debug Control Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for TSENS peripheral ========== */
#define TSENS_DMAC_ID_RESRDY        1        // Index of DMA RESRDY trigger
#define TSENS_GCLK_ID               5        // Index of Generic Clock

#endif /* _SAMC21_TSENS_INSTANCE_ */
