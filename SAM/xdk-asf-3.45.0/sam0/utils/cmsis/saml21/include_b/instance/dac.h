/**
 * \file
 *
 * \brief Instance description for DAC
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

#ifndef _SAML21_DAC_INSTANCE_
#define _SAML21_DAC_INSTANCE_

/* ========== Register definition for DAC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_DAC_CTRLA              (0x42003000U) /**< \brief (DAC) Control A */
#define REG_DAC_CTRLB              (0x42003001U) /**< \brief (DAC) Control B */
#define REG_DAC_EVCTRL             (0x42003002U) /**< \brief (DAC) Event Control */
#define REG_DAC_INTENCLR           (0x42003004U) /**< \brief (DAC) Interrupt Enable Clear */
#define REG_DAC_INTENSET           (0x42003005U) /**< \brief (DAC) Interrupt Enable Set */
#define REG_DAC_INTFLAG            (0x42003006U) /**< \brief (DAC) Interrupt Flag Status and Clear */
#define REG_DAC_STATUS             (0x42003007U) /**< \brief (DAC) Status */
#define REG_DAC_SYNCBUSY           (0x42003008U) /**< \brief (DAC) Synchronization Busy */
#define REG_DAC_DACCTRL0           (0x4200300CU) /**< \brief (DAC) DAC 0 Control */
#define REG_DAC_DACCTRL1           (0x4200300EU) /**< \brief (DAC) DAC 1 Control */
#define REG_DAC_DATA0              (0x42003010U) /**< \brief (DAC) DAC 0 Data */
#define REG_DAC_DATA1              (0x42003012U) /**< \brief (DAC) DAC 1 Data */
#define REG_DAC_DATABUF0           (0x42003014U) /**< \brief (DAC) DAC 0 Data Buffer */
#define REG_DAC_DATABUF1           (0x42003016U) /**< \brief (DAC) DAC 1 Data Buffer */
#define REG_DAC_DBGCTRL            (0x42003018U) /**< \brief (DAC) Debug Control */
#else
#define REG_DAC_CTRLA              (*(RwReg8 *)0x42003000U) /**< \brief (DAC) Control A */
#define REG_DAC_CTRLB              (*(RwReg8 *)0x42003001U) /**< \brief (DAC) Control B */
#define REG_DAC_EVCTRL             (*(RwReg8 *)0x42003002U) /**< \brief (DAC) Event Control */
#define REG_DAC_INTENCLR           (*(RwReg8 *)0x42003004U) /**< \brief (DAC) Interrupt Enable Clear */
#define REG_DAC_INTENSET           (*(RwReg8 *)0x42003005U) /**< \brief (DAC) Interrupt Enable Set */
#define REG_DAC_INTFLAG            (*(RwReg8 *)0x42003006U) /**< \brief (DAC) Interrupt Flag Status and Clear */
#define REG_DAC_STATUS             (*(RoReg8 *)0x42003007U) /**< \brief (DAC) Status */
#define REG_DAC_SYNCBUSY           (*(RoReg  *)0x42003008U) /**< \brief (DAC) Synchronization Busy */
#define REG_DAC_DACCTRL0           (*(RwReg16*)0x4200300CU) /**< \brief (DAC) DAC 0 Control */
#define REG_DAC_DACCTRL1           (*(RwReg16*)0x4200300EU) /**< \brief (DAC) DAC 1 Control */
#define REG_DAC_DATA0              (*(WoReg16*)0x42003010U) /**< \brief (DAC) DAC 0 Data */
#define REG_DAC_DATA1              (*(WoReg16*)0x42003012U) /**< \brief (DAC) DAC 1 Data */
#define REG_DAC_DATABUF0           (*(WoReg16*)0x42003014U) /**< \brief (DAC) DAC 0 Data Buffer */
#define REG_DAC_DATABUF1           (*(WoReg16*)0x42003016U) /**< \brief (DAC) DAC 1 Data Buffer */
#define REG_DAC_DBGCTRL            (*(RwReg8 *)0x42003018U) /**< \brief (DAC) Debug Control */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for DAC peripheral ========== */
#define DAC_DAC_NUM                 2        // Number of DACs
#define DAC_DATA_SIZE               12       // Number of bits in data
#define DAC_DMAC_ID_EMPTY_0         38
#define DAC_DMAC_ID_EMPTY_1         39
#define DAC_DMAC_ID_EMPTY_LSB       38
#define DAC_DMAC_ID_EMPTY_MSB       39
#define DAC_DMAC_ID_EMPTY_SIZE      2
#define DAC_GCLK_ID                 32       // Index of Generic Clock

#endif /* _SAML21_DAC_INSTANCE_ */
