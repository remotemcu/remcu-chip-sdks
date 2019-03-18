/**
 * \file
 *
 * \brief Instance description for PROV_DMA_CTRL0
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

#ifndef _SAMB11_PROV_DMA_CTRL0_INSTANCE_
#define _SAMB11_PROV_DMA_CTRL0_INSTANCE_

/* ========== Register definition for PROV_DMA_CTRL0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_PROV_DMA_CTRL0_CH0_CMD_REG0 (0x40002000U) /**< (PROV_DMA_CTRL0) Channel 0 First Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH0_CMD_REG1 (0x40002004U) /**< (PROV_DMA_CTRL0) Channel 0 Second Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH0_CMD_REG2 (0x40002008U) /**< (PROV_DMA_CTRL0) Channel 0 Third Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH0_CMD_REG3 (0x4000200CU) /**< (PROV_DMA_CTRL0) Channel 0 Fourth Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH0_STATIC_REG0 (0x40002010U) /**< (PROV_DMA_CTRL0) Channel 0 Static Configuration Read */
#define REG_PROV_DMA_CTRL0_CH0_STATIC_REG1 (0x40002014U) /**< (PROV_DMA_CTRL0) Channel 0 Static Configuration Write */
#define REG_PROV_DMA_CTRL0_CH0_STATIC_REG2 (0x40002018U) /**< (PROV_DMA_CTRL0) Channel 0 Block Mode */
#define REG_PROV_DMA_CTRL0_CH0_STATIC_REG4 (0x40002020U) /**< (PROV_DMA_CTRL0) Channel 0 Static Configuration Peripheral */
#define REG_PROV_DMA_CTRL0_CH0_RESRICT_REG (0x4000202CU) /**< (PROV_DMA_CTRL0) Channel 0 Restrictions Status Register */
#define REG_PROV_DMA_CTRL0_CH0_FIFO_FULLNESS_REG (0x40002038U) /**< (PROV_DMA_CTRL0) Channel 0 FIFO Fullness Status Register */
#define REG_PROV_DMA_CTRL0_CH0_CH_ENABLE_REG (0x40002040U) /**< (PROV_DMA_CTRL0) Channel 0 Channel Enable Register */
#define REG_PROV_DMA_CTRL0_CH0_CH_START_REG (0x40002044U) /**< (PROV_DMA_CTRL0) Channel 0 Channel Start Register */
#define REG_PROV_DMA_CTRL0_CH0_CH_ACTIVE_REG (0x40002048U) /**< (PROV_DMA_CTRL0) Channel 0 Channel Active Status Register */
#define REG_PROV_DMA_CTRL0_CH0_COUNT_REG (0x40002050U) /**< (PROV_DMA_CTRL0) Channel 0 Buffer Counter Status Register */
#define REG_PROV_DMA_CTRL0_CH0_INT_RAWSTAT_REG (0x400020A0U) /**< (PROV_DMA_CTRL0) Channel 0 Interrupt Raw Status (Write 1 to any field to issue interrupt) */
#define REG_PROV_DMA_CTRL0_CH0_INT_CLEAR_REG (0x400020A4U) /**< (PROV_DMA_CTRL0) Channel 0 Interrupt Clear (Write 1 to clear) */
#define REG_PROV_DMA_CTRL0_CH0_INT_ENABLE_REG (0x400020A8U) /**< (PROV_DMA_CTRL0) Channel 0 Interrupt Enable */
#define REG_PROV_DMA_CTRL0_CH0_INT_STATUS_REG (0x400020ACU) /**< (PROV_DMA_CTRL0) Channel 0 Interrupt Status */
#define REG_PROV_DMA_CTRL0_CH1_CMD_REG0 (0x40002100U) /**< (PROV_DMA_CTRL0) Channel 1 First Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH1_CMD_REG1 (0x40002104U) /**< (PROV_DMA_CTRL0) Channel 1 Second Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH1_CMD_REG2 (0x40002108U) /**< (PROV_DMA_CTRL0) Channel 1 Third Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH1_CMD_REG3 (0x4000210CU) /**< (PROV_DMA_CTRL0) Channel 1 Fourth Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH1_STATIC_REG0 (0x40002110U) /**< (PROV_DMA_CTRL0) Channel 1 Static Configuration Read */
#define REG_PROV_DMA_CTRL0_CH1_STATIC_REG1 (0x40002114U) /**< (PROV_DMA_CTRL0) Channel 1 Static Configuration Write */
#define REG_PROV_DMA_CTRL0_CH1_STATIC_REG2 (0x40002118U) /**< (PROV_DMA_CTRL0) Channel 1 Block Mode */
#define REG_PROV_DMA_CTRL0_CH1_STATIC_REG4 (0x40002120U) /**< (PROV_DMA_CTRL0) Channel 1 Static Configuration Peripheral */
#define REG_PROV_DMA_CTRL0_CH1_RESRICT_REG (0x4000212CU) /**< (PROV_DMA_CTRL0) Channel 1 Restrictions Status Register */
#define REG_PROV_DMA_CTRL0_CH1_FIFO_FULLNESS_REG (0x40002138U) /**< (PROV_DMA_CTRL0) Channel 1 FIFO Fullness Status Register */
#define REG_PROV_DMA_CTRL0_CH1_CH_ENABLE_REG (0x40002140U) /**< (PROV_DMA_CTRL0) Channel 1 Channel Enable Register */
#define REG_PROV_DMA_CTRL0_CH1_CH_START_REG (0x40002144U) /**< (PROV_DMA_CTRL0) Channel 1 Channel Start Register */
#define REG_PROV_DMA_CTRL0_CH1_CH_ACTIVE_REG (0x40002148U) /**< (PROV_DMA_CTRL0) Channel 1 Channel Active Status Register */
#define REG_PROV_DMA_CTRL0_CH1_COUNT_REG (0x40002150U) /**< (PROV_DMA_CTRL0) Channel 1 Buffer Counter Status Register */
#define REG_PROV_DMA_CTRL0_CH1_INT_RAWSTAT_REG (0x400021A0U) /**< (PROV_DMA_CTRL0) Channel 1 Interrupt Raw Status (Write 1 to any field to issue interrupt) */
#define REG_PROV_DMA_CTRL0_CH1_INT_CLEAR_REG (0x400021A4U) /**< (PROV_DMA_CTRL0) Channel 1 Interrupt Clear (Write 1 to clear) */
#define REG_PROV_DMA_CTRL0_CH1_INT_ENABLE_REG (0x400021A8U) /**< (PROV_DMA_CTRL0) Channel 1 Interrupt Enable */
#define REG_PROV_DMA_CTRL0_CH1_INT_STATUS_REG (0x400021ACU) /**< (PROV_DMA_CTRL0) Channel 1 Interrupt Status */
#define REG_PROV_DMA_CTRL0_CH2_CMD_REG0 (0x40002200U) /**< (PROV_DMA_CTRL0) Channel 2 First Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH2_CMD_REG1 (0x40002204U) /**< (PROV_DMA_CTRL0) Channel 2 Second Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH2_CMD_REG2 (0x40002208U) /**< (PROV_DMA_CTRL0) Channel 2 Third Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH2_CMD_REG3 (0x4000220CU) /**< (PROV_DMA_CTRL0) Channel 2 Fourth Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH2_STATIC_REG0 (0x40002210U) /**< (PROV_DMA_CTRL0) Channel 2 Static Configuration Read */
#define REG_PROV_DMA_CTRL0_CH2_STATIC_REG1 (0x40002214U) /**< (PROV_DMA_CTRL0) Channel 2 Static Configuration Write */
#define REG_PROV_DMA_CTRL0_CH2_STATIC_REG2 (0x40002218U) /**< (PROV_DMA_CTRL0) Channel 2 Block Mode */
#define REG_PROV_DMA_CTRL0_CH2_STATIC_REG4 (0x40002220U) /**< (PROV_DMA_CTRL0) Channel 2 Static Configuration Peripheral */
#define REG_PROV_DMA_CTRL0_CH2_RESRICT_REG (0x4000222CU) /**< (PROV_DMA_CTRL0) Channel 2 Restrictions Status Register */
#define REG_PROV_DMA_CTRL0_CH2_FIFO_FULLNESS_REG (0x40002238U) /**< (PROV_DMA_CTRL0) Channel 2 FIFO Fullness Status Register */
#define REG_PROV_DMA_CTRL0_CH2_CH_ENABLE_REG (0x40002240U) /**< (PROV_DMA_CTRL0) Channel 2 Channel Enable Register */
#define REG_PROV_DMA_CTRL0_CH2_CH_START_REG (0x40002244U) /**< (PROV_DMA_CTRL0) Channel 2 Channel Start Register */
#define REG_PROV_DMA_CTRL0_CH2_CH_ACTIVE_REG (0x40002248U) /**< (PROV_DMA_CTRL0) Channel 2 Channel Active Status Register */
#define REG_PROV_DMA_CTRL0_CH2_COUNT_REG (0x40002250U) /**< (PROV_DMA_CTRL0) Channel 2 Buffer Counter Status Register */
#define REG_PROV_DMA_CTRL0_CH2_INT_RAWSTAT_REG (0x400022A0U) /**< (PROV_DMA_CTRL0) Channel 2 Interrupt Raw Status (Write 1 to any field to issue interrupt) */
#define REG_PROV_DMA_CTRL0_CH2_INT_CLEAR_REG (0x400022A4U) /**< (PROV_DMA_CTRL0) Channel 2 Interrupt Clear (Write 1 to clear) */
#define REG_PROV_DMA_CTRL0_CH2_INT_ENABLE_REG (0x400022A8U) /**< (PROV_DMA_CTRL0) Channel 2 Interrupt Enable */
#define REG_PROV_DMA_CTRL0_CH2_INT_STATUS_REG (0x400022ACU) /**< (PROV_DMA_CTRL0) Channel 2 Interrupt Status */
#define REG_PROV_DMA_CTRL0_CH3_CMD_REG0 (0x40002300U) /**< (PROV_DMA_CTRL0) Channel 3 First Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH3_CMD_REG1 (0x40002304U) /**< (PROV_DMA_CTRL0) Channel 3 Second Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH3_CMD_REG2 (0x40002308U) /**< (PROV_DMA_CTRL0) Channel 3 Third Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH3_CMD_REG3 (0x4000230CU) /**< (PROV_DMA_CTRL0) Channel 3 Fourth Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH3_STATIC_REG0 (0x40002310U) /**< (PROV_DMA_CTRL0) Channel 3 Static Configuration Read */
#define REG_PROV_DMA_CTRL0_CH3_STATIC_REG1 (0x40002314U) /**< (PROV_DMA_CTRL0) Channel 3 Static Configuration Write */
#define REG_PROV_DMA_CTRL0_CH3_STATIC_REG2 (0x40002318U) /**< (PROV_DMA_CTRL0) Channel 3 Block Mode */
#define REG_PROV_DMA_CTRL0_CH3_STATIC_REG4 (0x40002320U) /**< (PROV_DMA_CTRL0) Channel 3 Static Configuration Peripheral */
#define REG_PROV_DMA_CTRL0_CH3_RESRICT_REG (0x4000232CU) /**< (PROV_DMA_CTRL0) Channel 3 Restrictions Status Register */
#define REG_PROV_DMA_CTRL0_CH3_FIFO_FULLNESS_REG (0x40002338U) /**< (PROV_DMA_CTRL0) Channel 3 FIFO Fullness Status Register */
#define REG_PROV_DMA_CTRL0_CH3_CH_ENABLE_REG (0x40002340U) /**< (PROV_DMA_CTRL0) Channel 3 Channel Enable Register */
#define REG_PROV_DMA_CTRL0_CH3_CH_START_REG (0x40002344U) /**< (PROV_DMA_CTRL0) Channel 3 Channel Start Register */
#define REG_PROV_DMA_CTRL0_CH3_CH_ACTIVE_REG (0x40002348U) /**< (PROV_DMA_CTRL0) Channel 3 Channel Active Status Register */
#define REG_PROV_DMA_CTRL0_CH3_COUNT_REG (0x40002350U) /**< (PROV_DMA_CTRL0) Channel 3 Buffer Counter Status Register */
#define REG_PROV_DMA_CTRL0_CH3_INT_RAWSTAT_REG (0x400023A0U) /**< (PROV_DMA_CTRL0) Channel 3 Interrupt Raw Status (Write 1 to any field to issue interrupt) */
#define REG_PROV_DMA_CTRL0_CH3_INT_CLEAR_REG (0x400023A4U) /**< (PROV_DMA_CTRL0) Channel 3 Interrupt Clear (Write 1 to clear) */
#define REG_PROV_DMA_CTRL0_CH3_INT_ENABLE_REG (0x400023A8U) /**< (PROV_DMA_CTRL0) Channel 3 Interrupt Enable */
#define REG_PROV_DMA_CTRL0_CH3_INT_STATUS_REG (0x400023ACU) /**< (PROV_DMA_CTRL0) Channel 3 Interrupt Status */
#define REG_PROV_DMA_CTRL0_CORE_INT_STATUS (0x40002800U) /**< (PROV_DMA_CTRL0) Indicates which channels caused interrupt */
#define REG_PROV_DMA_CTRL0_CORE_JOINT_MODE (0x40002830U) /**< (PROV_DMA_CTRL0) If set, core works in joint mode */
#define REG_PROV_DMA_CTRL0_CORE_PRIORITY (0x40002838U) /**< (PROV_DMA_CTRL0) Core Priority Channels */
#define REG_PROV_DMA_CTRL0_CORE_CLKDIV (0x40002840U) /**< (PROV_DMA_CTRL0) Ratio between main clock and core clock */
#define REG_PROV_DMA_CTRL0_CORE_CH_START (0x40002848U) /**< (PROV_DMA_CTRL0) Channel Start */
#define REG_PROV_DMA_CTRL0_PERIPH_RX_CTRL (0x40002850U) /**< (PROV_DMA_CTRL0) Direct control of peripheral RX request */
#define REG_PROV_DMA_CTRL0_PERIPH_TX_CTRL (0x40002860U) /**< (PROV_DMA_CTRL0) Direct control of peripheral TX request */
#define REG_PROV_DMA_CTRL0_CORE_IDLE (0x400028D0U) /**< (PROV_DMA_CTRL0) Indicates all channels have stopped and transactions have completed */
#define REG_PROV_DMA_CTRL0_USER_DEF_STATUS (0x400028E0U) /**< (PROV_DMA_CTRL0) User Defined Configurations */
#define REG_PROV_DMA_CTRL0_CORE_DEF_STATUS0 (0x400028F0U) /**< (PROV_DMA_CTRL0) User Defined Core Configurations 0 */
#define REG_PROV_DMA_CTRL0_CORE_DEF_STATUS1 (0x400028F4U) /**< (PROV_DMA_CTRL0) User Defined Core Configurations 1 */

#else

#define REG_PROV_DMA_CTRL0_CH0_CMD_REG0 (*(__IO uint32_t*)0x40002000U) /**< (PROV_DMA_CTRL0) Channel 0 First Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH0_CMD_REG1 (*(__IO uint32_t*)0x40002004U) /**< (PROV_DMA_CTRL0) Channel 0 Second Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH0_CMD_REG2 (*(__IO uint16_t*)0x40002008U) /**< (PROV_DMA_CTRL0) Channel 0 Third Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH0_CMD_REG3 (*(__IO uint32_t*)0x4000200CU) /**< (PROV_DMA_CTRL0) Channel 0 Fourth Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH0_STATIC_REG0 (*(__IO uint32_t*)0x40002010U) /**< (PROV_DMA_CTRL0) Channel 0 Static Configuration Read */
#define REG_PROV_DMA_CTRL0_CH0_STATIC_REG1 (*(__IO uint32_t*)0x40002014U) /**< (PROV_DMA_CTRL0) Channel 0 Static Configuration Write */
#define REG_PROV_DMA_CTRL0_CH0_STATIC_REG2 (*(__IO uint32_t*)0x40002018U) /**< (PROV_DMA_CTRL0) Channel 0 Block Mode */
#define REG_PROV_DMA_CTRL0_CH0_STATIC_REG4 (*(__IO uint32_t*)0x40002020U) /**< (PROV_DMA_CTRL0) Channel 0 Static Configuration Peripheral */
#define REG_PROV_DMA_CTRL0_CH0_RESRICT_REG (*(__I  uint16_t*)0x4000202CU) /**< (PROV_DMA_CTRL0) Channel 0 Restrictions Status Register */
#define REG_PROV_DMA_CTRL0_CH0_FIFO_FULLNESS_REG (*(__I  uint32_t*)0x40002038U) /**< (PROV_DMA_CTRL0) Channel 0 FIFO Fullness Status Register */
#define REG_PROV_DMA_CTRL0_CH0_CH_ENABLE_REG (*(__IO uint8_t*)0x40002040U) /**< (PROV_DMA_CTRL0) Channel 0 Channel Enable Register */
#define REG_PROV_DMA_CTRL0_CH0_CH_START_REG (*(__O  uint8_t*)0x40002044U) /**< (PROV_DMA_CTRL0) Channel 0 Channel Start Register */
#define REG_PROV_DMA_CTRL0_CH0_CH_ACTIVE_REG (*(__I  uint8_t*)0x40002048U) /**< (PROV_DMA_CTRL0) Channel 0 Channel Active Status Register */
#define REG_PROV_DMA_CTRL0_CH0_COUNT_REG (*(__I  uint32_t*)0x40002050U) /**< (PROV_DMA_CTRL0) Channel 0 Buffer Counter Status Register */
#define REG_PROV_DMA_CTRL0_CH0_INT_RAWSTAT_REG (*(__IO uint8_t*)0x400020A0U) /**< (PROV_DMA_CTRL0) Channel 0 Interrupt Raw Status (Write 1 to any field to issue interrupt) */
#define REG_PROV_DMA_CTRL0_CH0_INT_CLEAR_REG (*(__IO uint8_t*)0x400020A4U) /**< (PROV_DMA_CTRL0) Channel 0 Interrupt Clear (Write 1 to clear) */
#define REG_PROV_DMA_CTRL0_CH0_INT_ENABLE_REG (*(__IO uint8_t*)0x400020A8U) /**< (PROV_DMA_CTRL0) Channel 0 Interrupt Enable */
#define REG_PROV_DMA_CTRL0_CH0_INT_STATUS_REG (*(__IO uint8_t*)0x400020ACU) /**< (PROV_DMA_CTRL0) Channel 0 Interrupt Status */
#define REG_PROV_DMA_CTRL0_CH1_CMD_REG0 (*(__IO uint32_t*)0x40002100U) /**< (PROV_DMA_CTRL0) Channel 1 First Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH1_CMD_REG1 (*(__IO uint32_t*)0x40002104U) /**< (PROV_DMA_CTRL0) Channel 1 Second Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH1_CMD_REG2 (*(__IO uint16_t*)0x40002108U) /**< (PROV_DMA_CTRL0) Channel 1 Third Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH1_CMD_REG3 (*(__IO uint32_t*)0x4000210CU) /**< (PROV_DMA_CTRL0) Channel 1 Fourth Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH1_STATIC_REG0 (*(__IO uint32_t*)0x40002110U) /**< (PROV_DMA_CTRL0) Channel 1 Static Configuration Read */
#define REG_PROV_DMA_CTRL0_CH1_STATIC_REG1 (*(__IO uint32_t*)0x40002114U) /**< (PROV_DMA_CTRL0) Channel 1 Static Configuration Write */
#define REG_PROV_DMA_CTRL0_CH1_STATIC_REG2 (*(__IO uint32_t*)0x40002118U) /**< (PROV_DMA_CTRL0) Channel 1 Block Mode */
#define REG_PROV_DMA_CTRL0_CH1_STATIC_REG4 (*(__IO uint32_t*)0x40002120U) /**< (PROV_DMA_CTRL0) Channel 1 Static Configuration Peripheral */
#define REG_PROV_DMA_CTRL0_CH1_RESRICT_REG (*(__I  uint16_t*)0x4000212CU) /**< (PROV_DMA_CTRL0) Channel 1 Restrictions Status Register */
#define REG_PROV_DMA_CTRL0_CH1_FIFO_FULLNESS_REG (*(__I  uint32_t*)0x40002138U) /**< (PROV_DMA_CTRL0) Channel 1 FIFO Fullness Status Register */
#define REG_PROV_DMA_CTRL0_CH1_CH_ENABLE_REG (*(__IO uint8_t*)0x40002140U) /**< (PROV_DMA_CTRL0) Channel 1 Channel Enable Register */
#define REG_PROV_DMA_CTRL0_CH1_CH_START_REG (*(__O  uint8_t*)0x40002144U) /**< (PROV_DMA_CTRL0) Channel 1 Channel Start Register */
#define REG_PROV_DMA_CTRL0_CH1_CH_ACTIVE_REG (*(__I  uint8_t*)0x40002148U) /**< (PROV_DMA_CTRL0) Channel 1 Channel Active Status Register */
#define REG_PROV_DMA_CTRL0_CH1_COUNT_REG (*(__I  uint32_t*)0x40002150U) /**< (PROV_DMA_CTRL0) Channel 1 Buffer Counter Status Register */
#define REG_PROV_DMA_CTRL0_CH1_INT_RAWSTAT_REG (*(__IO uint8_t*)0x400021A0U) /**< (PROV_DMA_CTRL0) Channel 1 Interrupt Raw Status (Write 1 to any field to issue interrupt) */
#define REG_PROV_DMA_CTRL0_CH1_INT_CLEAR_REG (*(__IO uint8_t*)0x400021A4U) /**< (PROV_DMA_CTRL0) Channel 1 Interrupt Clear (Write 1 to clear) */
#define REG_PROV_DMA_CTRL0_CH1_INT_ENABLE_REG (*(__IO uint8_t*)0x400021A8U) /**< (PROV_DMA_CTRL0) Channel 1 Interrupt Enable */
#define REG_PROV_DMA_CTRL0_CH1_INT_STATUS_REG (*(__IO uint8_t*)0x400021ACU) /**< (PROV_DMA_CTRL0) Channel 1 Interrupt Status */
#define REG_PROV_DMA_CTRL0_CH2_CMD_REG0 (*(__IO uint32_t*)0x40002200U) /**< (PROV_DMA_CTRL0) Channel 2 First Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH2_CMD_REG1 (*(__IO uint32_t*)0x40002204U) /**< (PROV_DMA_CTRL0) Channel 2 Second Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH2_CMD_REG2 (*(__IO uint16_t*)0x40002208U) /**< (PROV_DMA_CTRL0) Channel 2 Third Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH2_CMD_REG3 (*(__IO uint32_t*)0x4000220CU) /**< (PROV_DMA_CTRL0) Channel 2 Fourth Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH2_STATIC_REG0 (*(__IO uint32_t*)0x40002210U) /**< (PROV_DMA_CTRL0) Channel 2 Static Configuration Read */
#define REG_PROV_DMA_CTRL0_CH2_STATIC_REG1 (*(__IO uint32_t*)0x40002214U) /**< (PROV_DMA_CTRL0) Channel 2 Static Configuration Write */
#define REG_PROV_DMA_CTRL0_CH2_STATIC_REG2 (*(__IO uint32_t*)0x40002218U) /**< (PROV_DMA_CTRL0) Channel 2 Block Mode */
#define REG_PROV_DMA_CTRL0_CH2_STATIC_REG4 (*(__IO uint32_t*)0x40002220U) /**< (PROV_DMA_CTRL0) Channel 2 Static Configuration Peripheral */
#define REG_PROV_DMA_CTRL0_CH2_RESRICT_REG (*(__I  uint16_t*)0x4000222CU) /**< (PROV_DMA_CTRL0) Channel 2 Restrictions Status Register */
#define REG_PROV_DMA_CTRL0_CH2_FIFO_FULLNESS_REG (*(__I  uint32_t*)0x40002238U) /**< (PROV_DMA_CTRL0) Channel 2 FIFO Fullness Status Register */
#define REG_PROV_DMA_CTRL0_CH2_CH_ENABLE_REG (*(__IO uint8_t*)0x40002240U) /**< (PROV_DMA_CTRL0) Channel 2 Channel Enable Register */
#define REG_PROV_DMA_CTRL0_CH2_CH_START_REG (*(__O  uint8_t*)0x40002244U) /**< (PROV_DMA_CTRL0) Channel 2 Channel Start Register */
#define REG_PROV_DMA_CTRL0_CH2_CH_ACTIVE_REG (*(__I  uint8_t*)0x40002248U) /**< (PROV_DMA_CTRL0) Channel 2 Channel Active Status Register */
#define REG_PROV_DMA_CTRL0_CH2_COUNT_REG (*(__I  uint32_t*)0x40002250U) /**< (PROV_DMA_CTRL0) Channel 2 Buffer Counter Status Register */
#define REG_PROV_DMA_CTRL0_CH2_INT_RAWSTAT_REG (*(__IO uint8_t*)0x400022A0U) /**< (PROV_DMA_CTRL0) Channel 2 Interrupt Raw Status (Write 1 to any field to issue interrupt) */
#define REG_PROV_DMA_CTRL0_CH2_INT_CLEAR_REG (*(__IO uint8_t*)0x400022A4U) /**< (PROV_DMA_CTRL0) Channel 2 Interrupt Clear (Write 1 to clear) */
#define REG_PROV_DMA_CTRL0_CH2_INT_ENABLE_REG (*(__IO uint8_t*)0x400022A8U) /**< (PROV_DMA_CTRL0) Channel 2 Interrupt Enable */
#define REG_PROV_DMA_CTRL0_CH2_INT_STATUS_REG (*(__IO uint8_t*)0x400022ACU) /**< (PROV_DMA_CTRL0) Channel 2 Interrupt Status */
#define REG_PROV_DMA_CTRL0_CH3_CMD_REG0 (*(__IO uint32_t*)0x40002300U) /**< (PROV_DMA_CTRL0) Channel 3 First Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH3_CMD_REG1 (*(__IO uint32_t*)0x40002304U) /**< (PROV_DMA_CTRL0) Channel 3 Second Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH3_CMD_REG2 (*(__IO uint16_t*)0x40002308U) /**< (PROV_DMA_CTRL0) Channel 3 Third Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH3_CMD_REG3 (*(__IO uint32_t*)0x4000230CU) /**< (PROV_DMA_CTRL0) Channel 3 Fourth Line Channel Command */
#define REG_PROV_DMA_CTRL0_CH3_STATIC_REG0 (*(__IO uint32_t*)0x40002310U) /**< (PROV_DMA_CTRL0) Channel 3 Static Configuration Read */
#define REG_PROV_DMA_CTRL0_CH3_STATIC_REG1 (*(__IO uint32_t*)0x40002314U) /**< (PROV_DMA_CTRL0) Channel 3 Static Configuration Write */
#define REG_PROV_DMA_CTRL0_CH3_STATIC_REG2 (*(__IO uint32_t*)0x40002318U) /**< (PROV_DMA_CTRL0) Channel 3 Block Mode */
#define REG_PROV_DMA_CTRL0_CH3_STATIC_REG4 (*(__IO uint32_t*)0x40002320U) /**< (PROV_DMA_CTRL0) Channel 3 Static Configuration Peripheral */
#define REG_PROV_DMA_CTRL0_CH3_RESRICT_REG (*(__I  uint16_t*)0x4000232CU) /**< (PROV_DMA_CTRL0) Channel 3 Restrictions Status Register */
#define REG_PROV_DMA_CTRL0_CH3_FIFO_FULLNESS_REG (*(__I  uint32_t*)0x40002338U) /**< (PROV_DMA_CTRL0) Channel 3 FIFO Fullness Status Register */
#define REG_PROV_DMA_CTRL0_CH3_CH_ENABLE_REG (*(__IO uint8_t*)0x40002340U) /**< (PROV_DMA_CTRL0) Channel 3 Channel Enable Register */
#define REG_PROV_DMA_CTRL0_CH3_CH_START_REG (*(__O  uint8_t*)0x40002344U) /**< (PROV_DMA_CTRL0) Channel 3 Channel Start Register */
#define REG_PROV_DMA_CTRL0_CH3_CH_ACTIVE_REG (*(__I  uint8_t*)0x40002348U) /**< (PROV_DMA_CTRL0) Channel 3 Channel Active Status Register */
#define REG_PROV_DMA_CTRL0_CH3_COUNT_REG (*(__I  uint32_t*)0x40002350U) /**< (PROV_DMA_CTRL0) Channel 3 Buffer Counter Status Register */
#define REG_PROV_DMA_CTRL0_CH3_INT_RAWSTAT_REG (*(__IO uint8_t*)0x400023A0U) /**< (PROV_DMA_CTRL0) Channel 3 Interrupt Raw Status (Write 1 to any field to issue interrupt) */
#define REG_PROV_DMA_CTRL0_CH3_INT_CLEAR_REG (*(__IO uint8_t*)0x400023A4U) /**< (PROV_DMA_CTRL0) Channel 3 Interrupt Clear (Write 1 to clear) */
#define REG_PROV_DMA_CTRL0_CH3_INT_ENABLE_REG (*(__IO uint8_t*)0x400023A8U) /**< (PROV_DMA_CTRL0) Channel 3 Interrupt Enable */
#define REG_PROV_DMA_CTRL0_CH3_INT_STATUS_REG (*(__IO uint8_t*)0x400023ACU) /**< (PROV_DMA_CTRL0) Channel 3 Interrupt Status */
#define REG_PROV_DMA_CTRL0_CORE_INT_STATUS (*(__I  uint8_t*)0x40002800U) /**< (PROV_DMA_CTRL0) Indicates which channels caused interrupt */
#define REG_PROV_DMA_CTRL0_CORE_JOINT_MODE (*(__IO uint8_t*)0x40002830U) /**< (PROV_DMA_CTRL0) If set, core works in joint mode */
#define REG_PROV_DMA_CTRL0_CORE_PRIORITY (*(__IO uint16_t*)0x40002838U) /**< (PROV_DMA_CTRL0) Core Priority Channels */
#define REG_PROV_DMA_CTRL0_CORE_CLKDIV (*(__IO uint8_t*)0x40002840U) /**< (PROV_DMA_CTRL0) Ratio between main clock and core clock */
#define REG_PROV_DMA_CTRL0_CORE_CH_START (*(__O  uint8_t*)0x40002848U) /**< (PROV_DMA_CTRL0) Channel Start */
#define REG_PROV_DMA_CTRL0_PERIPH_RX_CTRL (*(__IO uint32_t*)0x40002850U) /**< (PROV_DMA_CTRL0) Direct control of peripheral RX request */
#define REG_PROV_DMA_CTRL0_PERIPH_TX_CTRL (*(__IO uint32_t*)0x40002860U) /**< (PROV_DMA_CTRL0) Direct control of peripheral TX request */
#define REG_PROV_DMA_CTRL0_CORE_IDLE (*(__I  uint8_t*)0x400028D0U) /**< (PROV_DMA_CTRL0) Indicates all channels have stopped and transactions have completed */
#define REG_PROV_DMA_CTRL0_USER_DEF_STATUS (*(__I  uint32_t*)0x400028E0U) /**< (PROV_DMA_CTRL0) User Defined Configurations */
#define REG_PROV_DMA_CTRL0_CORE_DEF_STATUS0 (*(__I  uint32_t*)0x400028F0U) /**< (PROV_DMA_CTRL0) User Defined Core Configurations 0 */
#define REG_PROV_DMA_CTRL0_CORE_DEF_STATUS1 (*(__I  uint16_t*)0x400028F4U) /**< (PROV_DMA_CTRL0) User Defined Core Configurations 1 */

#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMB11_PROV_DMA_CTRL0_INSTANCE_ */
