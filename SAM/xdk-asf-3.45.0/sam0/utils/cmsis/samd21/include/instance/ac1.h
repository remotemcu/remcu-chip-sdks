/**
 * \file
 *
 * \brief Instance description for AC1
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

#ifndef _SAMD21_AC1_INSTANCE_
#define _SAMD21_AC1_INSTANCE_

/* ========== Register definition for AC1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_AC1_CTRLA              (0x42005400U) /**< \brief (AC1) Control A */
#define REG_AC1_CTRLB              (0x42005401U) /**< \brief (AC1) Control B */
#define REG_AC1_EVCTRL             (0x42005402U) /**< \brief (AC1) Event Control */
#define REG_AC1_INTENCLR           (0x42005404U) /**< \brief (AC1) Interrupt Enable Clear */
#define REG_AC1_INTENSET           (0x42005405U) /**< \brief (AC1) Interrupt Enable Set */
#define REG_AC1_INTFLAG            (0x42005406U) /**< \brief (AC1) Interrupt Flag Status and Clear */
#define REG_AC1_STATUSA            (0x42005408U) /**< \brief (AC1) Status A */
#define REG_AC1_STATUSB            (0x42005409U) /**< \brief (AC1) Status B */
#define REG_AC1_STATUSC            (0x4200540AU) /**< \brief (AC1) Status C */
#define REG_AC1_WINCTRL            (0x4200540CU) /**< \brief (AC1) Window Control */
#define REG_AC1_COMPCTRL0          (0x42005410U) /**< \brief (AC1) Comparator Control 0 */
#define REG_AC1_COMPCTRL1          (0x42005414U) /**< \brief (AC1) Comparator Control 1 */
#define REG_AC1_SCALER0            (0x42005420U) /**< \brief (AC1) Scaler 0 */
#define REG_AC1_SCALER1            (0x42005421U) /**< \brief (AC1) Scaler 1 */
#else
#define REG_AC1_CTRLA              (*(RwReg8 *)0x42005400U) /**< \brief (AC1) Control A */
#define REG_AC1_CTRLB              (*(WoReg8 *)0x42005401U) /**< \brief (AC1) Control B */
#define REG_AC1_EVCTRL             (*(RwReg16*)0x42005402U) /**< \brief (AC1) Event Control */
#define REG_AC1_INTENCLR           (*(RwReg8 *)0x42005404U) /**< \brief (AC1) Interrupt Enable Clear */
#define REG_AC1_INTENSET           (*(RwReg8 *)0x42005405U) /**< \brief (AC1) Interrupt Enable Set */
#define REG_AC1_INTFLAG            (*(RwReg8 *)0x42005406U) /**< \brief (AC1) Interrupt Flag Status and Clear */
#define REG_AC1_STATUSA            (*(RoReg8 *)0x42005408U) /**< \brief (AC1) Status A */
#define REG_AC1_STATUSB            (*(RoReg8 *)0x42005409U) /**< \brief (AC1) Status B */
#define REG_AC1_STATUSC            (*(RoReg8 *)0x4200540AU) /**< \brief (AC1) Status C */
#define REG_AC1_WINCTRL            (*(RwReg8 *)0x4200540CU) /**< \brief (AC1) Window Control */
#define REG_AC1_COMPCTRL0          (*(RwReg  *)0x42005410U) /**< \brief (AC1) Comparator Control 0 */
#define REG_AC1_COMPCTRL1          (*(RwReg  *)0x42005414U) /**< \brief (AC1) Comparator Control 1 */
#define REG_AC1_SCALER0            (*(RwReg8 *)0x42005420U) /**< \brief (AC1) Scaler 0 */
#define REG_AC1_SCALER1            (*(RwReg8 *)0x42005421U) /**< \brief (AC1) Scaler 1 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for AC1 peripheral ========== */
#define AC1_CMP_NUM                 2        // Number of comparators
#define AC1_GCLK_ID_ANA             32       // Index of Generic Clock for analog
#define AC1_GCLK_ID_DIG             31       // Index of Generic Clock for digital
#define AC1_NUM_CMP                 2       
#define AC1_PAIRS                   1        // Number of pairs of comparators

#endif /* _SAMD21_AC1_INSTANCE_ */
