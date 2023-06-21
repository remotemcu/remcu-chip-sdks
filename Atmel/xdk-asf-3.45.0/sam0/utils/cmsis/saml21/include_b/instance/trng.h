/**
 * \file
 *
 * \brief Instance description for TRNG
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

#ifndef _SAML21_TRNG_INSTANCE_
#define _SAML21_TRNG_INSTANCE_

/* ========== Register definition for TRNG peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_TRNG_CTRLA             (0x42003800U) /**< \brief (TRNG) Control A */
#define REG_TRNG_EVCTRL            (0x42003804U) /**< \brief (TRNG) Event Control */
#define REG_TRNG_INTENCLR          (0x42003808U) /**< \brief (TRNG) Interrupt Enable Clear */
#define REG_TRNG_INTENSET          (0x42003809U) /**< \brief (TRNG) Interrupt Enable Set */
#define REG_TRNG_INTFLAG           (0x4200380AU) /**< \brief (TRNG) Interrupt Flag Status and Clear */
#define REG_TRNG_DATA              (0x42003820U) /**< \brief (TRNG) Output Data */
#else
#define REG_TRNG_CTRLA             (*(RwReg8 *)0x42003800U) /**< \brief (TRNG) Control A */
#define REG_TRNG_EVCTRL            (*(RwReg8 *)0x42003804U) /**< \brief (TRNG) Event Control */
#define REG_TRNG_INTENCLR          (*(RwReg8 *)0x42003808U) /**< \brief (TRNG) Interrupt Enable Clear */
#define REG_TRNG_INTENSET          (*(RwReg8 *)0x42003809U) /**< \brief (TRNG) Interrupt Enable Set */
#define REG_TRNG_INTFLAG           (*(RwReg8 *)0x4200380AU) /**< \brief (TRNG) Interrupt Flag Status and Clear */
#define REG_TRNG_DATA              (*(RoReg  *)0x42003820U) /**< \brief (TRNG) Output Data */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */


#endif /* _SAML21_TRNG_INSTANCE_ */
