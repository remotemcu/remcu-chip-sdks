/**
 * \file
 *
 * \brief Instance description for WDT
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

#ifndef _SAMC20_WDT_INSTANCE_
#define _SAMC20_WDT_INSTANCE_

/* ========== Register definition for WDT peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_WDT_CTRLA              (0x40002000U) /**< \brief (WDT) Control */
#define REG_WDT_CONFIG             (0x40002001U) /**< \brief (WDT) Configuration */
#define REG_WDT_EWCTRL             (0x40002002U) /**< \brief (WDT) Early Warning Interrupt Control */
#define REG_WDT_INTENCLR           (0x40002004U) /**< \brief (WDT) Interrupt Enable Clear */
#define REG_WDT_INTENSET           (0x40002005U) /**< \brief (WDT) Interrupt Enable Set */
#define REG_WDT_INTFLAG            (0x40002006U) /**< \brief (WDT) Interrupt Flag Status and Clear */
#define REG_WDT_SYNCBUSY           (0x40002008U) /**< \brief (WDT) Synchronization Busy */
#define REG_WDT_CLEAR              (0x4000200CU) /**< \brief (WDT) Clear */
#else
#define REG_WDT_CTRLA              (*(RwReg8 *)0x40002000U) /**< \brief (WDT) Control */
#define REG_WDT_CONFIG             (*(RwReg8 *)0x40002001U) /**< \brief (WDT) Configuration */
#define REG_WDT_EWCTRL             (*(RwReg8 *)0x40002002U) /**< \brief (WDT) Early Warning Interrupt Control */
#define REG_WDT_INTENCLR           (*(RwReg8 *)0x40002004U) /**< \brief (WDT) Interrupt Enable Clear */
#define REG_WDT_INTENSET           (*(RwReg8 *)0x40002005U) /**< \brief (WDT) Interrupt Enable Set */
#define REG_WDT_INTFLAG            (*(RwReg8 *)0x40002006U) /**< \brief (WDT) Interrupt Flag Status and Clear */
#define REG_WDT_SYNCBUSY           (*(RoReg  *)0x40002008U) /**< \brief (WDT) Synchronization Busy */
#define REG_WDT_CLEAR              (*(WoReg8 *)0x4000200CU) /**< \brief (WDT) Clear */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */


#endif /* _SAMC20_WDT_INSTANCE_ */
