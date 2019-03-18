/**
 * \file
 *
 * \brief Instance description for ADC0
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

#ifndef _SAMC21_ADC0_INSTANCE_
#define _SAMC21_ADC0_INSTANCE_

/* ========== Register definition for ADC0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_ADC0_CTRLA             (0x42004400U) /**< \brief (ADC0) Control A */
#define REG_ADC0_CTRLB             (0x42004401U) /**< \brief (ADC0) Control B */
#define REG_ADC0_REFCTRL           (0x42004402U) /**< \brief (ADC0) Reference Control */
#define REG_ADC0_EVCTRL            (0x42004403U) /**< \brief (ADC0) Event Control */
#define REG_ADC0_INTENCLR          (0x42004404U) /**< \brief (ADC0) Interrupt Enable Clear */
#define REG_ADC0_INTENSET          (0x42004405U) /**< \brief (ADC0) Interrupt Enable Set */
#define REG_ADC0_INTFLAG           (0x42004406U) /**< \brief (ADC0) Interrupt Flag Status and Clear */
#define REG_ADC0_SEQSTATUS         (0x42004407U) /**< \brief (ADC0) Sequence Status */
#define REG_ADC0_INPUTCTRL         (0x42004408U) /**< \brief (ADC0) Input Control */
#define REG_ADC0_CTRLC             (0x4200440AU) /**< \brief (ADC0) Control C */
#define REG_ADC0_AVGCTRL           (0x4200440CU) /**< \brief (ADC0) Average Control */
#define REG_ADC0_SAMPCTRL          (0x4200440DU) /**< \brief (ADC0) Sample Time Control */
#define REG_ADC0_WINLT             (0x4200440EU) /**< \brief (ADC0) Window Monitor Lower Threshold */
#define REG_ADC0_WINUT             (0x42004410U) /**< \brief (ADC0) Window Monitor Upper Threshold */
#define REG_ADC0_GAINCORR          (0x42004412U) /**< \brief (ADC0) Gain Correction */
#define REG_ADC0_OFFSETCORR        (0x42004414U) /**< \brief (ADC0) Offset Correction */
#define REG_ADC0_SWTRIG            (0x42004418U) /**< \brief (ADC0) Software Trigger */
#define REG_ADC0_DBGCTRL           (0x4200441CU) /**< \brief (ADC0) Debug Control */
#define REG_ADC0_SYNCBUSY          (0x42004420U) /**< \brief (ADC0) Synchronization Busy */
#define REG_ADC0_RESULT            (0x42004424U) /**< \brief (ADC0) Result */
#define REG_ADC0_SEQCTRL           (0x42004428U) /**< \brief (ADC0) Sequence Control */
#define REG_ADC0_CALIB             (0x4200442CU) /**< \brief (ADC0) Calibration */
#else
#define REG_ADC0_CTRLA             (*(RwReg8 *)0x42004400U) /**< \brief (ADC0) Control A */
#define REG_ADC0_CTRLB             (*(RwReg8 *)0x42004401U) /**< \brief (ADC0) Control B */
#define REG_ADC0_REFCTRL           (*(RwReg8 *)0x42004402U) /**< \brief (ADC0) Reference Control */
#define REG_ADC0_EVCTRL            (*(RwReg8 *)0x42004403U) /**< \brief (ADC0) Event Control */
#define REG_ADC0_INTENCLR          (*(RwReg8 *)0x42004404U) /**< \brief (ADC0) Interrupt Enable Clear */
#define REG_ADC0_INTENSET          (*(RwReg8 *)0x42004405U) /**< \brief (ADC0) Interrupt Enable Set */
#define REG_ADC0_INTFLAG           (*(RwReg8 *)0x42004406U) /**< \brief (ADC0) Interrupt Flag Status and Clear */
#define REG_ADC0_SEQSTATUS         (*(RoReg8 *)0x42004407U) /**< \brief (ADC0) Sequence Status */
#define REG_ADC0_INPUTCTRL         (*(RwReg16*)0x42004408U) /**< \brief (ADC0) Input Control */
#define REG_ADC0_CTRLC             (*(RwReg16*)0x4200440AU) /**< \brief (ADC0) Control C */
#define REG_ADC0_AVGCTRL           (*(RwReg8 *)0x4200440CU) /**< \brief (ADC0) Average Control */
#define REG_ADC0_SAMPCTRL          (*(RwReg8 *)0x4200440DU) /**< \brief (ADC0) Sample Time Control */
#define REG_ADC0_WINLT             (*(RwReg16*)0x4200440EU) /**< \brief (ADC0) Window Monitor Lower Threshold */
#define REG_ADC0_WINUT             (*(RwReg16*)0x42004410U) /**< \brief (ADC0) Window Monitor Upper Threshold */
#define REG_ADC0_GAINCORR          (*(RwReg16*)0x42004412U) /**< \brief (ADC0) Gain Correction */
#define REG_ADC0_OFFSETCORR        (*(RwReg16*)0x42004414U) /**< \brief (ADC0) Offset Correction */
#define REG_ADC0_SWTRIG            (*(RwReg8 *)0x42004418U) /**< \brief (ADC0) Software Trigger */
#define REG_ADC0_DBGCTRL           (*(RwReg8 *)0x4200441CU) /**< \brief (ADC0) Debug Control */
#define REG_ADC0_SYNCBUSY          (*(RoReg16*)0x42004420U) /**< \brief (ADC0) Synchronization Busy */
#define REG_ADC0_RESULT            (*(RoReg16*)0x42004424U) /**< \brief (ADC0) Result */
#define REG_ADC0_SEQCTRL           (*(RwReg  *)0x42004428U) /**< \brief (ADC0) Sequence Control */
#define REG_ADC0_CALIB             (*(RwReg16*)0x4200442CU) /**< \brief (ADC0) Calibration */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for ADC0 peripheral ========== */
#define ADC0_DMAC_ID_RESRDY         42       // index of DMA RESRDY trigger
#define ADC0_EXTCHANNEL_MSB         11       // Number of external channels
#define ADC0_GCLK_ID                33       // index of Generic Clock
#define ADC0_INT_CH30               0        // Select OPAMP or CTAT on Channel 30
#define ADC0_MASTER_SLAVE_MODE      1        // ADC Master/Slave Mode

#endif /* _SAMC21_ADC0_INSTANCE_ */
