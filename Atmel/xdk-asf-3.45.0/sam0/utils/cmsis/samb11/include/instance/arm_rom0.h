/**
 * \file
 *
 * \brief Instance description for ARM_ROM0
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

#ifndef _SAMB11_ARM_ROM0_INSTANCE_
#define _SAMB11_ARM_ROM0_INSTANCE_

/* ========== Register definition for ARM_ROM0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_ARM_ROM0_ROM_SCS    (0xE00FF000U) /**< (ARM_ROM0) Points to the SCS at 0xE000E000 */
#define REG_ARM_ROM0_ROM_DWT    (0xE00FF010U) /**< (ARM_ROM0) Points to the DWT at 0xE0001000 */
#define REG_ARM_ROM0_ROM_BPU    (0xE00FF020U) /**< (ARM_ROM0) Points to the BPU at 0xE0002000 */
#define REG_ARM_ROM0_ROM_EOT    (0xE00FF030U) /**< (ARM_ROM0) End of Table Marker */
#define REG_ARM_ROM0_ROM_CSMT   (0xE00FFFCCU) /**< (ARM_ROM0) System Memory accessible through DAP */
#define REG_ARM_ROM0_ROM_PID4   (0xE00FFFD0U) /**< (ARM_ROM0) Peripheral ID Register 4 */
#define REG_ARM_ROM0_ROM_PID0   (0xE00FFFE0U) /**< (ARM_ROM0) Peripheral ID Register 0 */
#define REG_ARM_ROM0_ROM_PID1   (0xE00FFFE4U) /**< (ARM_ROM0) Peripheral ID Register 1 */
#define REG_ARM_ROM0_ROM_PID2   (0xE00FFFE8U) /**< (ARM_ROM0) Peripheral ID Register 2 */
#define REG_ARM_ROM0_ROM_PID3   (0xE00FFFECU) /**< (ARM_ROM0) Peripheral ID Register 3 */
#define REG_ARM_ROM0_ROM_CID0   (0xE00FFFF0U) /**< (ARM_ROM0) Component ID Register 0 */
#define REG_ARM_ROM0_ROM_CID1   (0xE00FFFF4U) /**< (ARM_ROM0) Component ID Register 1 */
#define REG_ARM_ROM0_ROM_CID2   (0xE00FFFF8U) /**< (ARM_ROM0) Component ID Register 2 */
#define REG_ARM_ROM0_ROM_CID3   (0xE00FFFFCU) /**< (ARM_ROM0) Component ID Register 3 */

#else

#define REG_ARM_ROM0_ROM_SCS    (*(__I  uint32_t*)0xE00FF000U) /**< (ARM_ROM0) Points to the SCS at 0xE000E000 */
#define REG_ARM_ROM0_ROM_DWT    (*(__I  uint32_t*)0xE00FF010U) /**< (ARM_ROM0) Points to the DWT at 0xE0001000 */
#define REG_ARM_ROM0_ROM_BPU    (*(__I  uint32_t*)0xE00FF020U) /**< (ARM_ROM0) Points to the BPU at 0xE0002000 */
#define REG_ARM_ROM0_ROM_EOT    (*(__I  uint32_t*)0xE00FF030U) /**< (ARM_ROM0) End of Table Marker */
#define REG_ARM_ROM0_ROM_CSMT   (*(__I  uint8_t*)0xE00FFFCCU) /**< (ARM_ROM0) System Memory accessible through DAP */
#define REG_ARM_ROM0_ROM_PID4   (*(__I  uint8_t*)0xE00FFFD0U) /**< (ARM_ROM0) Peripheral ID Register 4 */
#define REG_ARM_ROM0_ROM_PID0   (*(__I  uint8_t*)0xE00FFFE0U) /**< (ARM_ROM0) Peripheral ID Register 0 */
#define REG_ARM_ROM0_ROM_PID1   (*(__I  uint8_t*)0xE00FFFE4U) /**< (ARM_ROM0) Peripheral ID Register 1 */
#define REG_ARM_ROM0_ROM_PID2   (*(__I  uint8_t*)0xE00FFFE8U) /**< (ARM_ROM0) Peripheral ID Register 2 */
#define REG_ARM_ROM0_ROM_PID3   (*(__I  uint8_t*)0xE00FFFECU) /**< (ARM_ROM0) Peripheral ID Register 3 */
#define REG_ARM_ROM0_ROM_CID0   (*(__I  uint8_t*)0xE00FFFF0U) /**< (ARM_ROM0) Component ID Register 0 */
#define REG_ARM_ROM0_ROM_CID1   (*(__I  uint8_t*)0xE00FFFF4U) /**< (ARM_ROM0) Component ID Register 1 */
#define REG_ARM_ROM0_ROM_CID2   (*(__I  uint8_t*)0xE00FFFF8U) /**< (ARM_ROM0) Component ID Register 2 */
#define REG_ARM_ROM0_ROM_CID3   (*(__I  uint8_t*)0xE00FFFFCU) /**< (ARM_ROM0) Component ID Register 3 */

#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMB11_ARM_ROM0_INSTANCE_ */
