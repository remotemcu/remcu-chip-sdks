/**
 * \file
 *
 * \brief Instance description for DIVAS
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

#ifndef _SAMC21_DIVAS_INSTANCE_
#define _SAMC21_DIVAS_INSTANCE_

/* ========== Register definition for DIVAS peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_DIVAS_CTRLA            (0x48000000U) /**< \brief (DIVAS) Control */
#define REG_DIVAS_STATUS           (0x48000004U) /**< \brief (DIVAS) Status */
#define REG_DIVAS_DIVIDEND         (0x48000008U) /**< \brief (DIVAS) Dividend */
#define REG_DIVAS_DIVISOR          (0x4800000CU) /**< \brief (DIVAS) Divisor */
#define REG_DIVAS_RESULT           (0x48000010U) /**< \brief (DIVAS) Result */
#define REG_DIVAS_REM              (0x48000014U) /**< \brief (DIVAS) Remainder */
#define REG_DIVAS_SQRNUM           (0x48000018U) /**< \brief (DIVAS) Square Root Input */
#else
#define REG_DIVAS_CTRLA            (*(RwReg8 *)0x48000000U) /**< \brief (DIVAS) Control */
#define REG_DIVAS_STATUS           (*(RwReg8 *)0x48000004U) /**< \brief (DIVAS) Status */
#define REG_DIVAS_DIVIDEND         (*(RwReg  *)0x48000008U) /**< \brief (DIVAS) Dividend */
#define REG_DIVAS_DIVISOR          (*(RwReg  *)0x4800000CU) /**< \brief (DIVAS) Divisor */
#define REG_DIVAS_RESULT           (*(RoReg  *)0x48000010U) /**< \brief (DIVAS) Result */
#define REG_DIVAS_REM              (*(RoReg  *)0x48000014U) /**< \brief (DIVAS) Remainder */
#define REG_DIVAS_SQRNUM           (*(RwReg  *)0x48000018U) /**< \brief (DIVAS) Square Root Input */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for DIVAS peripheral ========== */
#define DIVAS_CLK_AHB_ID            12       // AHB clock index

#endif /* _SAMC21_DIVAS_INSTANCE_ */
