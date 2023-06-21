/**
 * \file
 *
 * \brief Instance description for PM
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

#ifndef _SAML21_PM_INSTANCE_
#define _SAML21_PM_INSTANCE_

/* ========== Register definition for PM peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_PM_CTRLA               (0x40000000U) /**< \brief (PM) Control A */
#define REG_PM_SLEEPCFG            (0x40000001U) /**< \brief (PM) Sleep Configuration */
#define REG_PM_PLCFG               (0x40000002U) /**< \brief (PM) Performance Level Configuration */
#define REG_PM_INTENCLR            (0x40000004U) /**< \brief (PM) Interrupt Enable Clear */
#define REG_PM_INTENSET            (0x40000005U) /**< \brief (PM) Interrupt Enable Set */
#define REG_PM_INTFLAG             (0x40000006U) /**< \brief (PM) Interrupt Flag Status and Clear */
#define REG_PM_STDBYCFG            (0x40000008U) /**< \brief (PM) Standby Configuration */
#define REG_PM_PWSAKDLY            (0x4000000CU) /**< \brief (PM) Power Switch Acknowledge Delay */
#else
#define REG_PM_CTRLA               (*(RwReg8 *)0x40000000U) /**< \brief (PM) Control A */
#define REG_PM_SLEEPCFG            (*(RwReg8 *)0x40000001U) /**< \brief (PM) Sleep Configuration */
#define REG_PM_PLCFG               (*(RwReg8 *)0x40000002U) /**< \brief (PM) Performance Level Configuration */
#define REG_PM_INTENCLR            (*(RwReg8 *)0x40000004U) /**< \brief (PM) Interrupt Enable Clear */
#define REG_PM_INTENSET            (*(RwReg8 *)0x40000005U) /**< \brief (PM) Interrupt Enable Set */
#define REG_PM_INTFLAG             (*(RwReg8 *)0x40000006U) /**< \brief (PM) Interrupt Flag Status and Clear */
#define REG_PM_STDBYCFG            (*(RwReg16*)0x40000008U) /**< \brief (PM) Standby Configuration */
#define REG_PM_PWSAKDLY            (*(RwReg8 *)0x4000000CU) /**< \brief (PM) Power Switch Acknowledge Delay */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for PM peripheral ========== */
#define PM_PD_NUM                   3        // Number of switchable Power Domain

#endif /* _SAML21_PM_INSTANCE_ */
