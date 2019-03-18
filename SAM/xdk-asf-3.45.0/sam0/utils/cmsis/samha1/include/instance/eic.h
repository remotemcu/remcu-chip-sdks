/**
 * \file
 *
 * \brief Instance description for EIC
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _SAMHA1_EIC_INSTANCE_
#define _SAMHA1_EIC_INSTANCE_

/* ========== Register definition for EIC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_EIC_CTRL               (0x40001800) /**< \brief (EIC) Control */
#define REG_EIC_STATUS             (0x40001801) /**< \brief (EIC) Status */
#define REG_EIC_NMICTRL            (0x40001802) /**< \brief (EIC) Non-Maskable Interrupt Control */
#define REG_EIC_NMIFLAG            (0x40001803) /**< \brief (EIC) Non-Maskable Interrupt Flag Status and Clear */
#define REG_EIC_EVCTRL             (0x40001804) /**< \brief (EIC) Event Control */
#define REG_EIC_INTENCLR           (0x40001808) /**< \brief (EIC) Interrupt Enable Clear */
#define REG_EIC_INTENSET           (0x4000180C) /**< \brief (EIC) Interrupt Enable Set */
#define REG_EIC_INTFLAG            (0x40001810) /**< \brief (EIC) Interrupt Flag Status and Clear */
#define REG_EIC_WAKEUP             (0x40001814) /**< \brief (EIC) Wake-Up Enable */
#define REG_EIC_CONFIG0            (0x40001818) /**< \brief (EIC) Configuration 0 */
#define REG_EIC_CONFIG1            (0x4000181C) /**< \brief (EIC) Configuration 1 */
#else
#define REG_EIC_CTRL               (*(RwReg8 *)0x40001800UL) /**< \brief (EIC) Control */
#define REG_EIC_STATUS             (*(RoReg8 *)0x40001801UL) /**< \brief (EIC) Status */
#define REG_EIC_NMICTRL            (*(RwReg8 *)0x40001802UL) /**< \brief (EIC) Non-Maskable Interrupt Control */
#define REG_EIC_NMIFLAG            (*(RwReg8 *)0x40001803UL) /**< \brief (EIC) Non-Maskable Interrupt Flag Status and Clear */
#define REG_EIC_EVCTRL             (*(RwReg  *)0x40001804UL) /**< \brief (EIC) Event Control */
#define REG_EIC_INTENCLR           (*(RwReg  *)0x40001808UL) /**< \brief (EIC) Interrupt Enable Clear */
#define REG_EIC_INTENSET           (*(RwReg  *)0x4000180CUL) /**< \brief (EIC) Interrupt Enable Set */
#define REG_EIC_INTFLAG            (*(RwReg  *)0x40001810UL) /**< \brief (EIC) Interrupt Flag Status and Clear */
#define REG_EIC_WAKEUP             (*(RwReg  *)0x40001814UL) /**< \brief (EIC) Wake-Up Enable */
#define REG_EIC_CONFIG0            (*(RwReg  *)0x40001818UL) /**< \brief (EIC) Configuration 0 */
#define REG_EIC_CONFIG1            (*(RwReg  *)0x4000181CUL) /**< \brief (EIC) Configuration 1 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for EIC peripheral ========== */
#define EIC_CONFIG_NUM              2        // Number of CONFIG registers
#define EIC_GCLK_ID                 5        // Index of Generic Clock

#endif /* _SAMHA1_EIC_INSTANCE_ */
