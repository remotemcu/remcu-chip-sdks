/**
 * \file
 *
 * \brief Instance description for ARM_DWT0
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

#ifndef _SAMB11_ARM_DWT0_INSTANCE_
#define _SAMB11_ARM_DWT0_INSTANCE_

/* ========== Register definition for ARM_DWT0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_ARM_DWT0_DWT_CTRL   (0xE0001000U) /**< (ARM_DWT0) Control Register */
#define REG_ARM_DWT0_DWT_PCSR   (0xE000101CU) /**< (ARM_DWT0) Program Counter Sample Register */
#define REG_ARM_DWT0_DWT_COMP0  (0xE0001020U) /**< (ARM_DWT0) DWT Compare Register 0 */
#define REG_ARM_DWT0_DWT_MASK0  (0xE0001024U) /**< (ARM_DWT0) DWT Mask Register 0 */
#define REG_ARM_DWT0_DWT_FUNCTION0 (0xE0001028U) /**< (ARM_DWT0) DWT Function Register 0 */
#define REG_ARM_DWT0_DWT_COMP1  (0xE0001030U) /**< (ARM_DWT0) DWT Compare Register 1 */
#define REG_ARM_DWT0_DWT_MASK1  (0xE0001034U) /**< (ARM_DWT0) DWT Mask Register 1 */
#define REG_ARM_DWT0_DWT_FUNCTION1 (0xE0001038U) /**< (ARM_DWT0) DWT Function Register 1 */
#define REG_ARM_DWT0_DWT_PID4   (0xE0001FD0U) /**< (ARM_DWT0) Peripheral ID Register 4 */
#define REG_ARM_DWT0_DWT_PID0   (0xE0001FE0U) /**< (ARM_DWT0) Peripheral ID Register 0 */
#define REG_ARM_DWT0_DWT_PID1   (0xE0001FE4U) /**< (ARM_DWT0) Peripheral ID Register 1 */
#define REG_ARM_DWT0_DWT_PID2   (0xE0001FE8U) /**< (ARM_DWT0) Peripheral ID Register 2 */
#define REG_ARM_DWT0_DWT_PID3   (0xE0001FECU) /**< (ARM_DWT0) Peripheral ID Register 3 */
#define REG_ARM_DWT0_DWT_CID0   (0xE0001FF0U) /**< (ARM_DWT0) Component ID Register 0 */
#define REG_ARM_DWT0_DWT_CID1   (0xE0001FF4U) /**< (ARM_DWT0) Component ID Register 1 */
#define REG_ARM_DWT0_DWT_CID2   (0xE0001FF8U) /**< (ARM_DWT0) Component ID Register 2 */
#define REG_ARM_DWT0_DWT_CID3   (0xE0001FFCU) /**< (ARM_DWT0) Component ID Register 3 */

#else

#define REG_ARM_DWT0_DWT_CTRL   (*(__I  uint32_t*)0xE0001000U) /**< (ARM_DWT0) Control Register */
#define REG_ARM_DWT0_DWT_PCSR   (*(__I  uint32_t*)0xE000101CU) /**< (ARM_DWT0) Program Counter Sample Register */
#define REG_ARM_DWT0_DWT_COMP0  (*(__IO uint32_t*)0xE0001020U) /**< (ARM_DWT0) DWT Compare Register 0 */
#define REG_ARM_DWT0_DWT_MASK0  (*(__IO uint8_t*)0xE0001024U) /**< (ARM_DWT0) DWT Mask Register 0 */
#define REG_ARM_DWT0_DWT_FUNCTION0 (*(__I  uint32_t*)0xE0001028U) /**< (ARM_DWT0) DWT Function Register 0 */
#define REG_ARM_DWT0_DWT_COMP1  (*(__IO uint32_t*)0xE0001030U) /**< (ARM_DWT0) DWT Compare Register 1 */
#define REG_ARM_DWT0_DWT_MASK1  (*(__IO uint8_t*)0xE0001034U) /**< (ARM_DWT0) DWT Mask Register 1 */
#define REG_ARM_DWT0_DWT_FUNCTION1 (*(__I  uint32_t*)0xE0001038U) /**< (ARM_DWT0) DWT Function Register 1 */
#define REG_ARM_DWT0_DWT_PID4   (*(__I  uint8_t*)0xE0001FD0U) /**< (ARM_DWT0) Peripheral ID Register 4 */
#define REG_ARM_DWT0_DWT_PID0   (*(__I  uint8_t*)0xE0001FE0U) /**< (ARM_DWT0) Peripheral ID Register 0 */
#define REG_ARM_DWT0_DWT_PID1   (*(__I  uint8_t*)0xE0001FE4U) /**< (ARM_DWT0) Peripheral ID Register 1 */
#define REG_ARM_DWT0_DWT_PID2   (*(__I  uint8_t*)0xE0001FE8U) /**< (ARM_DWT0) Peripheral ID Register 2 */
#define REG_ARM_DWT0_DWT_PID3   (*(__I  uint8_t*)0xE0001FECU) /**< (ARM_DWT0) Peripheral ID Register 3 */
#define REG_ARM_DWT0_DWT_CID0   (*(__I  uint8_t*)0xE0001FF0U) /**< (ARM_DWT0) Component ID Register 0 */
#define REG_ARM_DWT0_DWT_CID1   (*(__I  uint8_t*)0xE0001FF4U) /**< (ARM_DWT0) Component ID Register 1 */
#define REG_ARM_DWT0_DWT_CID2   (*(__I  uint8_t*)0xE0001FF8U) /**< (ARM_DWT0) Component ID Register 2 */
#define REG_ARM_DWT0_DWT_CID3   (*(__I  uint8_t*)0xE0001FFCU) /**< (ARM_DWT0) Component ID Register 3 */

#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMB11_ARM_DWT0_INSTANCE_ */
