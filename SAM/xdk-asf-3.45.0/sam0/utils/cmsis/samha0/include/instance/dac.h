/**
 * \file
 *
 * \brief Instance description for DAC
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

#ifndef _SAMHA0_DAC_INSTANCE_
#define _SAMHA0_DAC_INSTANCE_

/* ========== Register definition for DAC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_DAC_CTRLA              (0x42004800) /**< \brief (DAC) Control A */
#define REG_DAC_CTRLB              (0x42004801) /**< \brief (DAC) Control B */
#define REG_DAC_EVCTRL             (0x42004802) /**< \brief (DAC) Event Control */
#define REG_DAC_INTENCLR           (0x42004804) /**< \brief (DAC) Interrupt Enable Clear */
#define REG_DAC_INTENSET           (0x42004805) /**< \brief (DAC) Interrupt Enable Set */
#define REG_DAC_INTFLAG            (0x42004806) /**< \brief (DAC) Interrupt Flag Status and Clear */
#define REG_DAC_STATUS             (0x42004807) /**< \brief (DAC) Status */
#define REG_DAC_DATA               (0x42004808) /**< \brief (DAC) Data */
#define REG_DAC_DATABUF            (0x4200480C) /**< \brief (DAC) Data Buffer */
#else
#define REG_DAC_CTRLA              (*(RwReg8 *)0x42004800UL) /**< \brief (DAC) Control A */
#define REG_DAC_CTRLB              (*(RwReg8 *)0x42004801UL) /**< \brief (DAC) Control B */
#define REG_DAC_EVCTRL             (*(RwReg8 *)0x42004802UL) /**< \brief (DAC) Event Control */
#define REG_DAC_INTENCLR           (*(RwReg8 *)0x42004804UL) /**< \brief (DAC) Interrupt Enable Clear */
#define REG_DAC_INTENSET           (*(RwReg8 *)0x42004805UL) /**< \brief (DAC) Interrupt Enable Set */
#define REG_DAC_INTFLAG            (*(RwReg8 *)0x42004806UL) /**< \brief (DAC) Interrupt Flag Status and Clear */
#define REG_DAC_STATUS             (*(RoReg8 *)0x42004807UL) /**< \brief (DAC) Status */
#define REG_DAC_DATA               (*(RwReg16*)0x42004808UL) /**< \brief (DAC) Data */
#define REG_DAC_DATABUF            (*(RwReg16*)0x4200480CUL) /**< \brief (DAC) Data Buffer */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for DAC peripheral ========== */
#define DAC_DMAC_ID_EMPTY           40       // Index of DMAC EMPTY trigger
#define DAC_GCLK_ID                 33       // Index of Generic Clock

#endif /* _SAMHA0_DAC_INSTANCE_ */
