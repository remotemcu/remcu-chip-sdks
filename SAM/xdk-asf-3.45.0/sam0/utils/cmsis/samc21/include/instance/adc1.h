/**
 * \file
 *
 * \brief Instance description for ADC1
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

#ifndef _SAMC21_ADC1_INSTANCE_
#define _SAMC21_ADC1_INSTANCE_

/* ========== Register definition for ADC1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_ADC1_CTRLA             (0x42004800U) /**< \brief (ADC1) Control A */
#define REG_ADC1_CTRLB             (0x42004801U) /**< \brief (ADC1) Control B */
#define REG_ADC1_REFCTRL           (0x42004802U) /**< \brief (ADC1) Reference Control */
#define REG_ADC1_EVCTRL            (0x42004803U) /**< \brief (ADC1) Event Control */
#define REG_ADC1_INTENCLR          (0x42004804U) /**< \brief (ADC1) Interrupt Enable Clear */
#define REG_ADC1_INTENSET          (0x42004805U) /**< \brief (ADC1) Interrupt Enable Set */
#define REG_ADC1_INTFLAG           (0x42004806U) /**< \brief (ADC1) Interrupt Flag Status and Clear */
#define REG_ADC1_SEQSTATUS         (0x42004807U) /**< \brief (ADC1) Sequence Status */
#define REG_ADC1_INPUTCTRL         (0x42004808U) /**< \brief (ADC1) Input Control */
#define REG_ADC1_CTRLC             (0x4200480AU) /**< \brief (ADC1) Control C */
#define REG_ADC1_AVGCTRL           (0x4200480CU) /**< \brief (ADC1) Average Control */
#define REG_ADC1_SAMPCTRL          (0x4200480DU) /**< \brief (ADC1) Sample Time Control */
#define REG_ADC1_WINLT             (0x4200480EU) /**< \brief (ADC1) Window Monitor Lower Threshold */
#define REG_ADC1_WINUT             (0x42004810U) /**< \brief (ADC1) Window Monitor Upper Threshold */
#define REG_ADC1_GAINCORR          (0x42004812U) /**< \brief (ADC1) Gain Correction */
#define REG_ADC1_OFFSETCORR        (0x42004814U) /**< \brief (ADC1) Offset Correction */
#define REG_ADC1_SWTRIG            (0x42004818U) /**< \brief (ADC1) Software Trigger */
#define REG_ADC1_DBGCTRL           (0x4200481CU) /**< \brief (ADC1) Debug Control */
#define REG_ADC1_SYNCBUSY          (0x42004820U) /**< \brief (ADC1) Synchronization Busy */
#define REG_ADC1_RESULT            (0x42004824U) /**< \brief (ADC1) Result */
#define REG_ADC1_SEQCTRL           (0x42004828U) /**< \brief (ADC1) Sequence Control */
#define REG_ADC1_CALIB             (0x4200482CU) /**< \brief (ADC1) Calibration */
#else
#define REG_ADC1_CTRLA             (*(RwReg8 *)0x42004800U) /**< \brief (ADC1) Control A */
#define REG_ADC1_CTRLB             (*(RwReg8 *)0x42004801U) /**< \brief (ADC1) Control B */
#define REG_ADC1_REFCTRL           (*(RwReg8 *)0x42004802U) /**< \brief (ADC1) Reference Control */
#define REG_ADC1_EVCTRL            (*(RwReg8 *)0x42004803U) /**< \brief (ADC1) Event Control */
#define REG_ADC1_INTENCLR          (*(RwReg8 *)0x42004804U) /**< \brief (ADC1) Interrupt Enable Clear */
#define REG_ADC1_INTENSET          (*(RwReg8 *)0x42004805U) /**< \brief (ADC1) Interrupt Enable Set */
#define REG_ADC1_INTFLAG           (*(RwReg8 *)0x42004806U) /**< \brief (ADC1) Interrupt Flag Status and Clear */
#define REG_ADC1_SEQSTATUS         (*(RoReg8 *)0x42004807U) /**< \brief (ADC1) Sequence Status */
#define REG_ADC1_INPUTCTRL         (*(RwReg16*)0x42004808U) /**< \brief (ADC1) Input Control */
#define REG_ADC1_CTRLC             (*(RwReg16*)0x4200480AU) /**< \brief (ADC1) Control C */
#define REG_ADC1_AVGCTRL           (*(RwReg8 *)0x4200480CU) /**< \brief (ADC1) Average Control */
#define REG_ADC1_SAMPCTRL          (*(RwReg8 *)0x4200480DU) /**< \brief (ADC1) Sample Time Control */
#define REG_ADC1_WINLT             (*(RwReg16*)0x4200480EU) /**< \brief (ADC1) Window Monitor Lower Threshold */
#define REG_ADC1_WINUT             (*(RwReg16*)0x42004810U) /**< \brief (ADC1) Window Monitor Upper Threshold */
#define REG_ADC1_GAINCORR          (*(RwReg16*)0x42004812U) /**< \brief (ADC1) Gain Correction */
#define REG_ADC1_OFFSETCORR        (*(RwReg16*)0x42004814U) /**< \brief (ADC1) Offset Correction */
#define REG_ADC1_SWTRIG            (*(RwReg8 *)0x42004818U) /**< \brief (ADC1) Software Trigger */
#define REG_ADC1_DBGCTRL           (*(RwReg8 *)0x4200481CU) /**< \brief (ADC1) Debug Control */
#define REG_ADC1_SYNCBUSY          (*(RoReg16*)0x42004820U) /**< \brief (ADC1) Synchronization Busy */
#define REG_ADC1_RESULT            (*(RoReg16*)0x42004824U) /**< \brief (ADC1) Result */
#define REG_ADC1_SEQCTRL           (*(RwReg  *)0x42004828U) /**< \brief (ADC1) Sequence Control */
#define REG_ADC1_CALIB             (*(RwReg16*)0x4200482CU) /**< \brief (ADC1) Calibration */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for ADC1 peripheral ========== */
#define ADC1_DMAC_ID_RESRDY         43       // index of DMA RESRDY trigger
#define ADC1_EXTCHANNEL_MSB         11       // Number of external channels
#define ADC1_GCLK_ID                34       // index of Generic Clock
#define ADC1_INT_CH30               0        // Select OPAMP or CTAT on Channel 30
#define ADC1_MASTER_SLAVE_MODE      2        // ADC Master/Slave Mode

#endif /* _SAMC21_ADC1_INSTANCE_ */
