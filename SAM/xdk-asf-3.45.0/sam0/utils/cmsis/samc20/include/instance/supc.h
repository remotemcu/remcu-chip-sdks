/**
 * \file
 *
 * \brief Instance description for SUPC
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

#ifndef _SAMC20_SUPC_INSTANCE_
#define _SAMC20_SUPC_INSTANCE_

/* ========== Register definition for SUPC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_SUPC_INTENCLR          (0x40001800U) /**< \brief (SUPC) Interrupt Enable Clear */
#define REG_SUPC_INTENSET          (0x40001804U) /**< \brief (SUPC) Interrupt Enable Set */
#define REG_SUPC_INTFLAG           (0x40001808U) /**< \brief (SUPC) Interrupt Flag Status and Clear */
#define REG_SUPC_STATUS            (0x4000180CU) /**< \brief (SUPC) Power and Clocks Status */
#define REG_SUPC_BODVDD            (0x40001810U) /**< \brief (SUPC) BODVDD Control */
#define REG_SUPC_BODCORE           (0x40001814U) /**< \brief (SUPC) BODCORE Control */
#define REG_SUPC_VREG              (0x40001818U) /**< \brief (SUPC) VREG Control */
#define REG_SUPC_VREF              (0x4000181CU) /**< \brief (SUPC) VREF Control */
#else
#define REG_SUPC_INTENCLR          (*(RwReg  *)0x40001800U) /**< \brief (SUPC) Interrupt Enable Clear */
#define REG_SUPC_INTENSET          (*(RwReg  *)0x40001804U) /**< \brief (SUPC) Interrupt Enable Set */
#define REG_SUPC_INTFLAG           (*(RwReg  *)0x40001808U) /**< \brief (SUPC) Interrupt Flag Status and Clear */
#define REG_SUPC_STATUS            (*(RoReg  *)0x4000180CU) /**< \brief (SUPC) Power and Clocks Status */
#define REG_SUPC_BODVDD            (*(RwReg  *)0x40001810U) /**< \brief (SUPC) BODVDD Control */
#define REG_SUPC_BODCORE           (*(RwReg  *)0x40001814U) /**< \brief (SUPC) BODCORE Control */
#define REG_SUPC_VREG              (*(RwReg  *)0x40001818U) /**< \brief (SUPC) VREG Control */
#define REG_SUPC_VREF              (*(RwReg  *)0x4000181CU) /**< \brief (SUPC) VREF Control */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for SUPC peripheral ========== */
#define SUPC_BODCORE_CALIB_MSB      5       
#define SUPC_BODVDD_CALIB_MSB       5       
#define SUPC_SUPC_OUT_NUM_MSB       1        // MSB of backup output pad Number

#endif /* _SAMC20_SUPC_INSTANCE_ */
