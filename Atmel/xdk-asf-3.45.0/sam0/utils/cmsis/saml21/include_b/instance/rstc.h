/**
 * \file
 *
 * \brief Instance description for RSTC
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

#ifndef _SAML21_RSTC_INSTANCE_
#define _SAML21_RSTC_INSTANCE_

/* ========== Register definition for RSTC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_RSTC_RCAUSE            (0x40000800U) /**< \brief (RSTC) Reset Cause */
#define REG_RSTC_BKUPEXIT          (0x40000802U) /**< \brief (RSTC) Backup Exit Source */
#define REG_RSTC_WKDBCONF          (0x40000804U) /**< \brief (RSTC) Wakeup Debounce Configuration */
#define REG_RSTC_WKPOL             (0x40000808U) /**< \brief (RSTC) Wakeup Polarity */
#define REG_RSTC_WKEN              (0x4000080CU) /**< \brief (RSTC) Wakeup Enable */
#define REG_RSTC_WKCAUSE           (0x40000810U) /**< \brief (RSTC) Wakeup Cause */
#else
#define REG_RSTC_RCAUSE            (*(RoReg8 *)0x40000800U) /**< \brief (RSTC) Reset Cause */
#define REG_RSTC_BKUPEXIT          (*(RoReg8 *)0x40000802U) /**< \brief (RSTC) Backup Exit Source */
#define REG_RSTC_WKDBCONF          (*(RwReg8 *)0x40000804U) /**< \brief (RSTC) Wakeup Debounce Configuration */
#define REG_RSTC_WKPOL             (*(RwReg16*)0x40000808U) /**< \brief (RSTC) Wakeup Polarity */
#define REG_RSTC_WKEN              (*(RwReg16*)0x4000080CU) /**< \brief (RSTC) Wakeup Enable */
#define REG_RSTC_WKCAUSE           (*(RwReg16*)0x40000810U) /**< \brief (RSTC) Wakeup Cause */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for RSTC peripheral ========== */
#define RSTC_NUMBER_OF_EXTWAKE      8        // number of external wakeup line

#endif /* _SAML21_RSTC_INSTANCE_ */
