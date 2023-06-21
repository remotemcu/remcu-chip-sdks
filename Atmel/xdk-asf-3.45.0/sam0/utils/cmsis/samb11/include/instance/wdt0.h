/**
 * \file
 *
 * \brief Instance description for WDT0
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

#ifndef _SAMB11_WDT0_INSTANCE_
#define _SAMB11_WDT0_INSTANCE_

/* ========== Register definition for WDT0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_WDT0_WDOGLOAD       (0x40008000U) /**< (WDT0) Watchdog Load Register */
#define REG_WDT0_WDOGVALUE      (0x40008004U) /**< (WDT0) Watchdog Value Register */
#define REG_WDT0_WDOGCONTROL    (0x40008008U) /**< (WDT0) Watchdog Control Register */
#define REG_WDT0_WDOGINTCLR     (0x4000800CU) /**< (WDT0) Watchdog Clear Interrupt Register */
#define REG_WDT0_WDOGRIS        (0x40008010U) /**< (WDT0) Watchdog Raw Interrupt Status Register */
#define REG_WDT0_WDOGMIS        (0x40008014U) /**< (WDT0) Watchdog Interrupt Status Register */
#define REG_WDT0_WDOGLOCK       (0x40008C00U) /**< (WDT0) Watchdog Lock Register (Write 0x1ACCE551 to enable write access to all other registers) */
#define REG_WDT0_WDOGITCR       (0x40008F00U) /**< (WDT0) Watchdog Integration Test Control Register */
#define REG_WDT0_WDOGITOP       (0x40008F04U) /**< (WDT0) Watchdog Integration Test Output Set Register */
#define REG_WDT0_WDOGPERIPHID4  (0x40008FD0U) /**< (WDT0) Peripheral ID Register 4 */
#define REG_WDT0_WDOGPERIPHID5  (0x40008FD4U) /**< (WDT0) Peripheral ID Register 5 */
#define REG_WDT0_WDOGPERIPHID6  (0x40008FD8U) /**< (WDT0) Peripheral ID Register 6 */
#define REG_WDT0_WDOGPERIPHID7  (0x40008FDCU) /**< (WDT0) Peripheral ID Register 7 */
#define REG_WDT0_WDOGPERIPHID0  (0x40008FE0U) /**< (WDT0) Peripheral ID Register 0 */
#define REG_WDT0_WDOGPERIPHID1  (0x40008FE4U) /**< (WDT0) Peripheral ID Register 1 */
#define REG_WDT0_WDOGPERIPHID2  (0x40008FE8U) /**< (WDT0) Peripheral ID Register 2 */
#define REG_WDT0_WDOGPERIPHID3  (0x40008FECU) /**< (WDT0) Peripheral ID Register 3 */
#define REG_WDT0_WDOGPCELLID0   (0x40008FF0U) /**< (WDT0) Component ID Register 0 */
#define REG_WDT0_WDOGPCELLID1   (0x40008FF4U) /**< (WDT0) Component ID Register 1 */
#define REG_WDT0_WDOGPCELLID2   (0x40008FF8U) /**< (WDT0) Component ID Register 2 */
#define REG_WDT0_WDOGPCELLID3   (0x40008FFCU) /**< (WDT0) Component ID Register 3 */

#else

#define REG_WDT0_WDOGLOAD       (*(__IO uint32_t*)0x40008000U) /**< (WDT0) Watchdog Load Register */
#define REG_WDT0_WDOGVALUE      (*(__I  uint32_t*)0x40008004U) /**< (WDT0) Watchdog Value Register */
#define REG_WDT0_WDOGCONTROL    (*(__IO uint8_t*)0x40008008U) /**< (WDT0) Watchdog Control Register */
#define REG_WDT0_WDOGINTCLR     (*(__O  uint8_t*)0x4000800CU) /**< (WDT0) Watchdog Clear Interrupt Register */
#define REG_WDT0_WDOGRIS        (*(__I  uint8_t*)0x40008010U) /**< (WDT0) Watchdog Raw Interrupt Status Register */
#define REG_WDT0_WDOGMIS        (*(__I  uint8_t*)0x40008014U) /**< (WDT0) Watchdog Interrupt Status Register */
#define REG_WDT0_WDOGLOCK       (*(__IO uint32_t*)0x40008C00U) /**< (WDT0) Watchdog Lock Register (Write 0x1ACCE551 to enable write access to all other registers) */
#define REG_WDT0_WDOGITCR       (*(__IO uint8_t*)0x40008F00U) /**< (WDT0) Watchdog Integration Test Control Register */
#define REG_WDT0_WDOGITOP       (*(__IO uint8_t*)0x40008F04U) /**< (WDT0) Watchdog Integration Test Output Set Register */
#define REG_WDT0_WDOGPERIPHID4  (*(__I  uint8_t*)0x40008FD0U) /**< (WDT0) Peripheral ID Register 4 */
#define REG_WDT0_WDOGPERIPHID5  (*(__I  uint8_t*)0x40008FD4U) /**< (WDT0) Peripheral ID Register 5 */
#define REG_WDT0_WDOGPERIPHID6  (*(__I  uint8_t*)0x40008FD8U) /**< (WDT0) Peripheral ID Register 6 */
#define REG_WDT0_WDOGPERIPHID7  (*(__I  uint8_t*)0x40008FDCU) /**< (WDT0) Peripheral ID Register 7 */
#define REG_WDT0_WDOGPERIPHID0  (*(__I  uint8_t*)0x40008FE0U) /**< (WDT0) Peripheral ID Register 0 */
#define REG_WDT0_WDOGPERIPHID1  (*(__I  uint8_t*)0x40008FE4U) /**< (WDT0) Peripheral ID Register 1 */
#define REG_WDT0_WDOGPERIPHID2  (*(__I  uint8_t*)0x40008FE8U) /**< (WDT0) Peripheral ID Register 2 */
#define REG_WDT0_WDOGPERIPHID3  (*(__I  uint8_t*)0x40008FECU) /**< (WDT0) Peripheral ID Register 3 */
#define REG_WDT0_WDOGPCELLID0   (*(__I  uint8_t*)0x40008FF0U) /**< (WDT0) Component ID Register 0 */
#define REG_WDT0_WDOGPCELLID1   (*(__I  uint8_t*)0x40008FF4U) /**< (WDT0) Component ID Register 1 */
#define REG_WDT0_WDOGPCELLID2   (*(__I  uint8_t*)0x40008FF8U) /**< (WDT0) Component ID Register 2 */
#define REG_WDT0_WDOGPCELLID3   (*(__I  uint8_t*)0x40008FFCU) /**< (WDT0) Component ID Register 3 */

#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMB11_WDT0_INSTANCE_ */
