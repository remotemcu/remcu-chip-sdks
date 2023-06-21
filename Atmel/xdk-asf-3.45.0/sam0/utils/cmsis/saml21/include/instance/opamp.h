/**
 * \file
 *
 * \brief Instance description for OPAMP
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

#ifndef _SAML21_OPAMP_INSTANCE_
#define _SAML21_OPAMP_INSTANCE_

/* ========== Register definition for OPAMP peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_OPAMP_CTRLA            (0x43001800U) /**< \brief (OPAMP) Control A */
#define REG_OPAMP_STATUS           (0x43001802U) /**< \brief (OPAMP) Status */
#define REG_OPAMP_OPAMPCTRL0       (0x43001804U) /**< \brief (OPAMP) OPAMP Control 0 */
#define REG_OPAMP_OPAMPCTRL1       (0x43001808U) /**< \brief (OPAMP) OPAMP Control 1 */
#define REG_OPAMP_OPAMPCTRL2       (0x4300180CU) /**< \brief (OPAMP) OPAMP Control 2 */
#else
#define REG_OPAMP_CTRLA            (*(RwReg8 *)0x43001800U) /**< \brief (OPAMP) Control A */
#define REG_OPAMP_STATUS           (*(RoReg8 *)0x43001802U) /**< \brief (OPAMP) Status */
#define REG_OPAMP_OPAMPCTRL0       (*(RwReg  *)0x43001804U) /**< \brief (OPAMP) OPAMP Control 0 */
#define REG_OPAMP_OPAMPCTRL1       (*(RwReg  *)0x43001808U) /**< \brief (OPAMP) OPAMP Control 1 */
#define REG_OPAMP_OPAMPCTRL2       (*(RwReg  *)0x4300180CU) /**< \brief (OPAMP) OPAMP Control 2 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */


#endif /* _SAML21_OPAMP_INSTANCE_ */
