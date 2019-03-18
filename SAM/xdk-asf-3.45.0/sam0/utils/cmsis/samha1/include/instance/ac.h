/**
 * \file
 *
 * \brief Instance description for AC
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

#ifndef _SAMHA1_AC_INSTANCE_
#define _SAMHA1_AC_INSTANCE_

/* ========== Register definition for AC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_AC_CTRLA               (0x42004400) /**< \brief (AC) Control A */
#define REG_AC_CTRLB               (0x42004401) /**< \brief (AC) Control B */
#define REG_AC_EVCTRL              (0x42004402) /**< \brief (AC) Event Control */
#define REG_AC_INTENCLR            (0x42004404) /**< \brief (AC) Interrupt Enable Clear */
#define REG_AC_INTENSET            (0x42004405) /**< \brief (AC) Interrupt Enable Set */
#define REG_AC_INTFLAG             (0x42004406) /**< \brief (AC) Interrupt Flag Status and Clear */
#define REG_AC_STATUSA             (0x42004408) /**< \brief (AC) Status A */
#define REG_AC_STATUSB             (0x42004409) /**< \brief (AC) Status B */
#define REG_AC_STATUSC             (0x4200440A) /**< \brief (AC) Status C */
#define REG_AC_WINCTRL             (0x4200440C) /**< \brief (AC) Window Control */
#define REG_AC_COMPCTRL0           (0x42004410) /**< \brief (AC) Comparator Control 0 */
#define REG_AC_COMPCTRL1           (0x42004414) /**< \brief (AC) Comparator Control 1 */
#define REG_AC_SCALER0             (0x42004420) /**< \brief (AC) Scaler 0 */
#define REG_AC_SCALER1             (0x42004421) /**< \brief (AC) Scaler 1 */
#else
#define REG_AC_CTRLA               (*(RwReg8 *)0x42004400UL) /**< \brief (AC) Control A */
#define REG_AC_CTRLB               (*(WoReg8 *)0x42004401UL) /**< \brief (AC) Control B */
#define REG_AC_EVCTRL              (*(RwReg16*)0x42004402UL) /**< \brief (AC) Event Control */
#define REG_AC_INTENCLR            (*(RwReg8 *)0x42004404UL) /**< \brief (AC) Interrupt Enable Clear */
#define REG_AC_INTENSET            (*(RwReg8 *)0x42004405UL) /**< \brief (AC) Interrupt Enable Set */
#define REG_AC_INTFLAG             (*(RwReg8 *)0x42004406UL) /**< \brief (AC) Interrupt Flag Status and Clear */
#define REG_AC_STATUSA             (*(RoReg8 *)0x42004408UL) /**< \brief (AC) Status A */
#define REG_AC_STATUSB             (*(RoReg8 *)0x42004409UL) /**< \brief (AC) Status B */
#define REG_AC_STATUSC             (*(RoReg8 *)0x4200440AUL) /**< \brief (AC) Status C */
#define REG_AC_WINCTRL             (*(RwReg8 *)0x4200440CUL) /**< \brief (AC) Window Control */
#define REG_AC_COMPCTRL0           (*(RwReg  *)0x42004410UL) /**< \brief (AC) Comparator Control 0 */
#define REG_AC_COMPCTRL1           (*(RwReg  *)0x42004414UL) /**< \brief (AC) Comparator Control 1 */
#define REG_AC_SCALER0             (*(RwReg8 *)0x42004420UL) /**< \brief (AC) Scaler 0 */
#define REG_AC_SCALER1             (*(RwReg8 *)0x42004421UL) /**< \brief (AC) Scaler 1 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for AC peripheral ========== */
#define AC_CMP_NUM                  2        // Number of comparators
#define AC_GCLK_ID_ANA              32       // Index of Generic Clock for analog
#define AC_GCLK_ID_DIG              31       // Index of Generic Clock for digital
#define AC_NUM_CMP                  2       
#define AC_PAIRS                    1        // Number of pairs of comparators

#endif /* _SAMHA1_AC_INSTANCE_ */
