/**
 * \file
 *
 * \brief Instance description for AON_PWR_SEQ0
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

#ifndef _SAMB11_AON_PWR_SEQ0_INSTANCE_
#define _SAMB11_AON_PWR_SEQ0_INSTANCE_

/* ========== Register definition for AON_PWR_SEQ0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_AON_PWR_SEQ0_GPIO_WAKEUP_CTRL (0x4000E000U) /**< (AON_PWR_SEQ0) Controls the wakeup enable for GPIO_0, GPIO_1 and GPIO_2 (Pinmux will control the ARM wakeup) */
#define REG_AON_PWR_SEQ0_AON_ST_WAKEUP_CTRL (0x4000E00CU) /**< (AON_PWR_SEQ0) Controls the wakeup enable for the Always On Sleep Timer (AON_ST) */
#define REG_AON_PWR_SEQ0_LPMCU_WAKEUP_CTRL (0x4000E010U) /**< (AON_PWR_SEQ0) Controls the wakeup enable for the Low Power Micro Controller Unit (LPMCU) */
#define REG_AON_PWR_SEQ0_BLE_ST_WAKEUP_CTRL (0x4000E014U) /**< (AON_PWR_SEQ0) Controls the wakeup enable for the BLE Sleep Timer (BLE_ST) */
#define REG_AON_PWR_SEQ0_LPMCU_SLEEP_1_CTRL (0x4000E020U) /**< (AON_PWR_SEQ0) Controls the sleep and retention options for SLEEP request 1 from the ARM */
#define REG_AON_PWR_SEQ0_OFF_DELAY_0_CTRL (0x4000E040U) /**< (AON_PWR_SEQ0) Power OFF Delays */
#define REG_AON_PWR_SEQ0_OFF_DELAY_1_CTRL (0x4000E044U) /**< (AON_PWR_SEQ0) Power OFF Delays */
#define REG_AON_PWR_SEQ0_ON_DELAY_0_CTRL (0x4000E048U) /**< (AON_PWR_SEQ0) Power ON Delays */
#define REG_AON_PWR_SEQ0_ON_DELAY_1_CTRL (0x4000E04CU) /**< (AON_PWR_SEQ0) Power ON Delays */
#define REG_AON_PWR_SEQ0_VDD_DCDC_EN_DELAY_CTRL (0x4000E050U) /**< (AON_PWR_SEQ0) VDD_DCDC_EN Delay Control */
#define REG_AON_PWR_SEQ0_MISC_BYPASS_0_CTRL (0x4000E218U) /**< (AON_PWR_SEQ0) Bypass control for misc signals */
#define REG_AON_PWR_SEQ0_RAW_WAKEUP_BITS (0x4000E300U) /**< (AON_PWR_SEQ0) Raw Wakeup Bits */
#define REG_AON_PWR_SEQ0_PD_WAKEUP_BITS (0x4000E304U) /**< (AON_PWR_SEQ0) Individual Power Domain Wakeup Bits */
#define REG_AON_PWR_SEQ0_SERVICED_REQUEST (0x4000E308U) /**< (AON_PWR_SEQ0) Serviced Request Status Bits */
#define REG_AON_PWR_SEQ0_ACTIVE_REQUEST (0x4000E30CU) /**< (AON_PWR_SEQ0) Active Request Status Bits */
#define REG_AON_PWR_SEQ0_LOGIC_FSM_STATES (0x4000E3F0U) /**< (AON_PWR_SEQ0) Current Logic FSM States */

#else

#define REG_AON_PWR_SEQ0_GPIO_WAKEUP_CTRL (*(__IO uint8_t*)0x4000E000U) /**< (AON_PWR_SEQ0) Controls the wakeup enable for GPIO_0, GPIO_1 and GPIO_2 (Pinmux will control the ARM wakeup) */
#define REG_AON_PWR_SEQ0_AON_ST_WAKEUP_CTRL (*(__IO uint8_t*)0x4000E00CU) /**< (AON_PWR_SEQ0) Controls the wakeup enable for the Always On Sleep Timer (AON_ST) */
#define REG_AON_PWR_SEQ0_LPMCU_WAKEUP_CTRL (*(__IO uint16_t*)0x4000E010U) /**< (AON_PWR_SEQ0) Controls the wakeup enable for the Low Power Micro Controller Unit (LPMCU) */
#define REG_AON_PWR_SEQ0_BLE_ST_WAKEUP_CTRL (*(__IO uint8_t*)0x4000E014U) /**< (AON_PWR_SEQ0) Controls the wakeup enable for the BLE Sleep Timer (BLE_ST) */
#define REG_AON_PWR_SEQ0_LPMCU_SLEEP_1_CTRL (*(__IO uint32_t*)0x4000E020U) /**< (AON_PWR_SEQ0) Controls the sleep and retention options for SLEEP request 1 from the ARM */
#define REG_AON_PWR_SEQ0_OFF_DELAY_0_CTRL (*(__IO uint32_t*)0x4000E040U) /**< (AON_PWR_SEQ0) Power OFF Delays */
#define REG_AON_PWR_SEQ0_OFF_DELAY_1_CTRL (*(__IO uint32_t*)0x4000E044U) /**< (AON_PWR_SEQ0) Power OFF Delays */
#define REG_AON_PWR_SEQ0_ON_DELAY_0_CTRL (*(__IO uint16_t*)0x4000E048U) /**< (AON_PWR_SEQ0) Power ON Delays */
#define REG_AON_PWR_SEQ0_ON_DELAY_1_CTRL (*(__IO uint32_t*)0x4000E04CU) /**< (AON_PWR_SEQ0) Power ON Delays */
#define REG_AON_PWR_SEQ0_VDD_DCDC_EN_DELAY_CTRL (*(__IO uint16_t*)0x4000E050U) /**< (AON_PWR_SEQ0) VDD_DCDC_EN Delay Control */
#define REG_AON_PWR_SEQ0_MISC_BYPASS_0_CTRL (*(__IO uint16_t*)0x4000E218U) /**< (AON_PWR_SEQ0) Bypass control for misc signals */
#define REG_AON_PWR_SEQ0_RAW_WAKEUP_BITS (*(__I  uint8_t*)0x4000E300U) /**< (AON_PWR_SEQ0) Raw Wakeup Bits */
#define REG_AON_PWR_SEQ0_PD_WAKEUP_BITS (*(__I  uint16_t*)0x4000E304U) /**< (AON_PWR_SEQ0) Individual Power Domain Wakeup Bits */
#define REG_AON_PWR_SEQ0_SERVICED_REQUEST (*(__I  uint16_t*)0x4000E308U) /**< (AON_PWR_SEQ0) Serviced Request Status Bits */
#define REG_AON_PWR_SEQ0_ACTIVE_REQUEST (*(__I  uint16_t*)0x4000E30CU) /**< (AON_PWR_SEQ0) Active Request Status Bits */
#define REG_AON_PWR_SEQ0_LOGIC_FSM_STATES (*(__I  uint32_t*)0x4000E3F0U) /**< (AON_PWR_SEQ0) Current Logic FSM States */

#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMB11_AON_PWR_SEQ0_INSTANCE_ */
