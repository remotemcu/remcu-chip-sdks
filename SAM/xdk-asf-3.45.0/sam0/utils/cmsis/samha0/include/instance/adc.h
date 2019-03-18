/**
 * \file
 *
 * \brief Instance description for ADC
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
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
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
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

#ifndef _SAMHA0_ADC_INSTANCE_
#define _SAMHA0_ADC_INSTANCE_

/* ========== Register definition for ADC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_ADC_CTRLA              (0x42004000) /**< \brief (ADC) Control A */
#define REG_ADC_REFCTRL            (0x42004001) /**< \brief (ADC) Reference Control */
#define REG_ADC_AVGCTRL            (0x42004002) /**< \brief (ADC) Average Control */
#define REG_ADC_SAMPCTRL           (0x42004003) /**< \brief (ADC) Sampling Time Control */
#define REG_ADC_CTRLB              (0x42004004) /**< \brief (ADC) Control B */
#define REG_ADC_WINCTRL            (0x42004008) /**< \brief (ADC) Window Monitor Control */
#define REG_ADC_SWTRIG             (0x4200400C) /**< \brief (ADC) Software Trigger */
#define REG_ADC_INPUTCTRL          (0x42004010) /**< \brief (ADC) Input Control */
#define REG_ADC_EVCTRL             (0x42004014) /**< \brief (ADC) Event Control */
#define REG_ADC_INTENCLR           (0x42004016) /**< \brief (ADC) Interrupt Enable Clear */
#define REG_ADC_INTENSET           (0x42004017) /**< \brief (ADC) Interrupt Enable Set */
#define REG_ADC_INTFLAG            (0x42004018) /**< \brief (ADC) Interrupt Flag Status and Clear */
#define REG_ADC_STATUS             (0x42004019) /**< \brief (ADC) Status */
#define REG_ADC_RESULT             (0x4200401A) /**< \brief (ADC) Result */
#define REG_ADC_WINLT              (0x4200401C) /**< \brief (ADC) Window Monitor Lower Threshold */
#define REG_ADC_WINUT              (0x42004020) /**< \brief (ADC) Window Monitor Upper Threshold */
#define REG_ADC_GAINCORR           (0x42004024) /**< \brief (ADC) Gain Correction */
#define REG_ADC_OFFSETCORR         (0x42004026) /**< \brief (ADC) Offset Correction */
#define REG_ADC_CALIB              (0x42004028) /**< \brief (ADC) Calibration */
#define REG_ADC_DBGCTRL            (0x4200402A) /**< \brief (ADC) Debug Control */
#else
#define REG_ADC_CTRLA              (*(RwReg8 *)0x42004000UL) /**< \brief (ADC) Control A */
#define REG_ADC_REFCTRL            (*(RwReg8 *)0x42004001UL) /**< \brief (ADC) Reference Control */
#define REG_ADC_AVGCTRL            (*(RwReg8 *)0x42004002UL) /**< \brief (ADC) Average Control */
#define REG_ADC_SAMPCTRL           (*(RwReg8 *)0x42004003UL) /**< \brief (ADC) Sampling Time Control */
#define REG_ADC_CTRLB              (*(RwReg16*)0x42004004UL) /**< \brief (ADC) Control B */
#define REG_ADC_WINCTRL            (*(RwReg8 *)0x42004008UL) /**< \brief (ADC) Window Monitor Control */
#define REG_ADC_SWTRIG             (*(RwReg8 *)0x4200400CUL) /**< \brief (ADC) Software Trigger */
#define REG_ADC_INPUTCTRL          (*(RwReg  *)0x42004010UL) /**< \brief (ADC) Input Control */
#define REG_ADC_EVCTRL             (*(RwReg8 *)0x42004014UL) /**< \brief (ADC) Event Control */
#define REG_ADC_INTENCLR           (*(RwReg8 *)0x42004016UL) /**< \brief (ADC) Interrupt Enable Clear */
#define REG_ADC_INTENSET           (*(RwReg8 *)0x42004017UL) /**< \brief (ADC) Interrupt Enable Set */
#define REG_ADC_INTFLAG            (*(RwReg8 *)0x42004018UL) /**< \brief (ADC) Interrupt Flag Status and Clear */
#define REG_ADC_STATUS             (*(RoReg8 *)0x42004019UL) /**< \brief (ADC) Status */
#define REG_ADC_RESULT             (*(RoReg16*)0x4200401AUL) /**< \brief (ADC) Result */
#define REG_ADC_WINLT              (*(RwReg16*)0x4200401CUL) /**< \brief (ADC) Window Monitor Lower Threshold */
#define REG_ADC_WINUT              (*(RwReg16*)0x42004020UL) /**< \brief (ADC) Window Monitor Upper Threshold */
#define REG_ADC_GAINCORR           (*(RwReg16*)0x42004024UL) /**< \brief (ADC) Gain Correction */
#define REG_ADC_OFFSETCORR         (*(RwReg16*)0x42004026UL) /**< \brief (ADC) Offset Correction */
#define REG_ADC_CALIB              (*(RwReg16*)0x42004028UL) /**< \brief (ADC) Calibration */
#define REG_ADC_DBGCTRL            (*(RwReg8 *)0x4200402AUL) /**< \brief (ADC) Debug Control */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for ADC peripheral ========== */
#define ADC_DMAC_ID_RESRDY          39       // Index of DMA RESRDY trigger
#define ADC_EXTCHANNEL_MSB          19       // Number of external channels
#define ADC_GCLK_ID                 30       // Index of Generic Clock
#define ADC_RESULT_BITS             16       // Size of RESULT.RESULT bitfield
#define ADC_RESULT_MSB              15       // Size of Result

#endif /* _SAMHA0_ADC_INSTANCE_ */
