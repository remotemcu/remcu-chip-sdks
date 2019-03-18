/**
 * \file
 *
 * \brief Instance description for AON_GP_REGS0
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

#ifndef _SAMB11_AON_GP_REGS0_INSTANCE_
#define _SAMB11_AON_GP_REGS0_INSTANCE_

/* ========== Register definition for AON_GP_REGS0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_AON_GP_REGS0_AON_PINMUX_SEL (0x4000F000U) /**< (AON_GP_REGS0) Controls the pinmux selection for the AO GPIOs */
#define REG_AON_GP_REGS0_AON_PMU_CTRL (0x4000F004U) /**< (AON_GP_REGS0) Always On Misc Control */
#define REG_AON_GP_REGS0_AON_BLE_LP_CTRL (0x4000F008U) /**< (AON_GP_REGS0) Always On BLE LP Control */
#define REG_AON_GP_REGS0_AON_MISC_CTRL (0x4000F00CU) /**< (AON_GP_REGS0) Always On Misc Control */
#define REG_AON_GP_REGS0_AON_GLOBAL_RESET (0x4000F010U) /**< (AON_GP_REGS0) Active Low Always On Reset Control */
#define REG_AON_GP_REGS0_AON_PULL_ENABLE (0x4000F014U) /**< (AON_GP_REGS0) Active Low Always On Pull Enable Control */
#define REG_AON_GP_REGS0_AON_RESET_CTRL (0x4000F01CU) /**< (AON_GP_REGS0) Reset Count Control for PD1, PD4, PD6 and PD7 */
#define REG_AON_GP_REGS0_AON_BTRIM_ACTIVE (0x4000F020U) /**< (AON_GP_REGS0) BTRIM settings for active mode (i.e. not in retention) */
#define REG_AON_GP_REGS0_AON_BTRIM_RETENTION (0x4000F024U) /**< (AON_GP_REGS0) BTRIM settings for retention mode */
#define REG_AON_GP_REGS0_AON_LPMCU_SCRATCH_PAD (0x4000F040U) /**< (AON_GP_REGS0) Usage for the LPMCU for any sort of status it needs to store for itself before it goes to sleep */
#define REG_AON_GP_REGS0_AON_LPMCU_COLD_BOOT (0x4000F044U) /**< (AON_GP_REGS0) To be used by ARM to determine if it is a cold boot or not */
#define REG_AON_GP_REGS0_AON_BO_OUT_STATUS (0x4000F080U) /**< (AON_GP_REGS0) Brown Out Detected (must be cleared manually) */
#define REG_AON_GP_REGS0_CLEAR_BROWN_OUT_REG (0x4000F084U) /**< (AON_GP_REGS0) Set to 1 to clear (hold until 0 read at aon_bo_out_status and then this must be cleared to detect another brown out condition) */
#define REG_AON_GP_REGS0_RF_PMU_REGS_0 (0x4000F400U) /**< (AON_GP_REGS0) RF PMU Registers */
#define REG_AON_GP_REGS0_RF_PMU_REGS_1 (0x4000F404U) /**< (AON_GP_REGS0) RF PMU Registers */
#define REG_AON_GP_REGS0_RF_PMU_REGS_2 (0x4000F408U) /**< (AON_GP_REGS0) RF PMU Registers */
#define REG_AON_GP_REGS0_MS_GPIO_MODE (0x4000F410U) /**< (AON_GP_REGS0) Analog Mode Select of Mixed Signal GPIOs */
#define REG_AON_GP_REGS0_IO_PADS_CONTROL (0x4000F414U) /**< (AON_GP_REGS0) Controls behaviour of IO Pads in Sleep Mode */

#else

#define REG_AON_GP_REGS0_AON_PINMUX_SEL (*(__IO uint16_t*)0x4000F000U) /**< (AON_GP_REGS0) Controls the pinmux selection for the AO GPIOs */
#define REG_AON_GP_REGS0_AON_PMU_CTRL (*(__IO uint32_t*)0x4000F004U) /**< (AON_GP_REGS0) Always On Misc Control */
#define REG_AON_GP_REGS0_AON_BLE_LP_CTRL (*(__IO uint8_t*)0x4000F008U) /**< (AON_GP_REGS0) Always On BLE LP Control */
#define REG_AON_GP_REGS0_AON_MISC_CTRL (*(__IO uint32_t*)0x4000F00CU) /**< (AON_GP_REGS0) Always On Misc Control */
#define REG_AON_GP_REGS0_AON_GLOBAL_RESET (*(__IO uint8_t*)0x4000F010U) /**< (AON_GP_REGS0) Active Low Always On Reset Control */
#define REG_AON_GP_REGS0_AON_PULL_ENABLE (*(__IO uint8_t*)0x4000F014U) /**< (AON_GP_REGS0) Active Low Always On Pull Enable Control */
#define REG_AON_GP_REGS0_AON_RESET_CTRL (*(__IO uint32_t*)0x4000F01CU) /**< (AON_GP_REGS0) Reset Count Control for PD1, PD4, PD6 and PD7 */
#define REG_AON_GP_REGS0_AON_BTRIM_ACTIVE (*(__IO uint8_t*)0x4000F020U) /**< (AON_GP_REGS0) BTRIM settings for active mode (i.e. not in retention) */
#define REG_AON_GP_REGS0_AON_BTRIM_RETENTION (*(__IO uint8_t*)0x4000F024U) /**< (AON_GP_REGS0) BTRIM settings for retention mode */
#define REG_AON_GP_REGS0_AON_LPMCU_SCRATCH_PAD (*(__IO uint8_t*)0x4000F040U) /**< (AON_GP_REGS0) Usage for the LPMCU for any sort of status it needs to store for itself before it goes to sleep */
#define REG_AON_GP_REGS0_AON_LPMCU_COLD_BOOT (*(__IO uint8_t*)0x4000F044U) /**< (AON_GP_REGS0) To be used by ARM to determine if it is a cold boot or not */
#define REG_AON_GP_REGS0_AON_BO_OUT_STATUS (*(__I  uint8_t*)0x4000F080U) /**< (AON_GP_REGS0) Brown Out Detected (must be cleared manually) */
#define REG_AON_GP_REGS0_CLEAR_BROWN_OUT_REG (*(__IO uint8_t*)0x4000F084U) /**< (AON_GP_REGS0) Set to 1 to clear (hold until 0 read at aon_bo_out_status and then this must be cleared to detect another brown out condition) */
#define REG_AON_GP_REGS0_RF_PMU_REGS_0 (*(__IO uint32_t*)0x4000F400U) /**< (AON_GP_REGS0) RF PMU Registers */
#define REG_AON_GP_REGS0_RF_PMU_REGS_1 (*(__IO uint32_t*)0x4000F404U) /**< (AON_GP_REGS0) RF PMU Registers */
#define REG_AON_GP_REGS0_RF_PMU_REGS_2 (*(__IO uint16_t*)0x4000F408U) /**< (AON_GP_REGS0) RF PMU Registers */
#define REG_AON_GP_REGS0_MS_GPIO_MODE (*(__IO uint8_t*)0x4000F410U) /**< (AON_GP_REGS0) Analog Mode Select of Mixed Signal GPIOs */
#define REG_AON_GP_REGS0_IO_PADS_CONTROL (*(__IO uint8_t*)0x4000F414U) /**< (AON_GP_REGS0) Controls behaviour of IO Pads in Sleep Mode */

#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMB11_AON_GP_REGS0_INSTANCE_ */
