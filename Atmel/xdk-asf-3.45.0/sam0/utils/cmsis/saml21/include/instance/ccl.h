/**
 * \file
 *
 * \brief Instance description for CCL
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

#ifndef _SAML21_CCL_INSTANCE_
#define _SAML21_CCL_INSTANCE_

/* ========== Register definition for CCL peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_CCL_CTRL               (0x43001C00U) /**< \brief (CCL) Control */
#define REG_CCL_SEQCTRL0           (0x43001C04U) /**< \brief (CCL) SEQ Control x 0 */
#define REG_CCL_SEQCTRL1           (0x43001C05U) /**< \brief (CCL) SEQ Control x 1 */
#define REG_CCL_LUTCTRL0           (0x43001C08U) /**< \brief (CCL) LUT Control x 0 */
#define REG_CCL_LUTCTRL1           (0x43001C0CU) /**< \brief (CCL) LUT Control x 1 */
#define REG_CCL_LUTCTRL2           (0x43001C10U) /**< \brief (CCL) LUT Control x 2 */
#define REG_CCL_LUTCTRL3           (0x43001C14U) /**< \brief (CCL) LUT Control x 3 */
#else
#define REG_CCL_CTRL               (*(RwReg8 *)0x43001C00U) /**< \brief (CCL) Control */
#define REG_CCL_SEQCTRL0           (*(RwReg8 *)0x43001C04U) /**< \brief (CCL) SEQ Control x 0 */
#define REG_CCL_SEQCTRL1           (*(RwReg8 *)0x43001C05U) /**< \brief (CCL) SEQ Control x 1 */
#define REG_CCL_LUTCTRL0           (*(RwReg  *)0x43001C08U) /**< \brief (CCL) LUT Control x 0 */
#define REG_CCL_LUTCTRL1           (*(RwReg  *)0x43001C0CU) /**< \brief (CCL) LUT Control x 1 */
#define REG_CCL_LUTCTRL2           (*(RwReg  *)0x43001C10U) /**< \brief (CCL) LUT Control x 2 */
#define REG_CCL_LUTCTRL3           (*(RwReg  *)0x43001C14U) /**< \brief (CCL) LUT Control x 3 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for CCL peripheral ========== */
#define CCL_GCLK_ID                 34       // GCLK index for CCL
#define CCL_IO_NUM                  12       // Numer of input pins
#define CCL_LUT_NUM                 4        // Number of LUT in a CCL
#define CCL_SEQ_NUM                 2        // Number of SEQ in a CCL

#endif /* _SAML21_CCL_INSTANCE_ */
