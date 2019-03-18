/**
 * \file
 *
 * \brief Instance description for WDT1
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

#ifndef _SAMB11_WDT1_INSTANCE_
#define _SAMB11_WDT1_INSTANCE_

/* ========== Register definition for WDT1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_WDT1_WDOGLOAD       (0x40009000U) /**< (WDT1) Watchdog Load Register */
#define REG_WDT1_WDOGVALUE      (0x40009004U) /**< (WDT1) Watchdog Value Register */
#define REG_WDT1_WDOGCONTROL    (0x40009008U) /**< (WDT1) Watchdog Control Register */
#define REG_WDT1_WDOGINTCLR     (0x4000900CU) /**< (WDT1) Watchdog Clear Interrupt Register */
#define REG_WDT1_WDOGRIS        (0x40009010U) /**< (WDT1) Watchdog Raw Interrupt Status Register */
#define REG_WDT1_WDOGMIS        (0x40009014U) /**< (WDT1) Watchdog Interrupt Status Register */
#define REG_WDT1_WDOGLOCK       (0x40009C00U) /**< (WDT1) Watchdog Lock Register (Write 0x1ACCE551 to enable write access to all other registers) */
#define REG_WDT1_WDOGITCR       (0x40009F00U) /**< (WDT1) Watchdog Integration Test Control Register */
#define REG_WDT1_WDOGITOP       (0x40009F04U) /**< (WDT1) Watchdog Integration Test Output Set Register */
#define REG_WDT1_WDOGPERIPHID4  (0x40009FD0U) /**< (WDT1) Peripheral ID Register 4 */
#define REG_WDT1_WDOGPERIPHID5  (0x40009FD4U) /**< (WDT1) Peripheral ID Register 5 */
#define REG_WDT1_WDOGPERIPHID6  (0x40009FD8U) /**< (WDT1) Peripheral ID Register 6 */
#define REG_WDT1_WDOGPERIPHID7  (0x40009FDCU) /**< (WDT1) Peripheral ID Register 7 */
#define REG_WDT1_WDOGPERIPHID0  (0x40009FE0U) /**< (WDT1) Peripheral ID Register 0 */
#define REG_WDT1_WDOGPERIPHID1  (0x40009FE4U) /**< (WDT1) Peripheral ID Register 1 */
#define REG_WDT1_WDOGPERIPHID2  (0x40009FE8U) /**< (WDT1) Peripheral ID Register 2 */
#define REG_WDT1_WDOGPERIPHID3  (0x40009FECU) /**< (WDT1) Peripheral ID Register 3 */
#define REG_WDT1_WDOGPCELLID0   (0x40009FF0U) /**< (WDT1) Component ID Register 0 */
#define REG_WDT1_WDOGPCELLID1   (0x40009FF4U) /**< (WDT1) Component ID Register 1 */
#define REG_WDT1_WDOGPCELLID2   (0x40009FF8U) /**< (WDT1) Component ID Register 2 */
#define REG_WDT1_WDOGPCELLID3   (0x40009FFCU) /**< (WDT1) Component ID Register 3 */

#else

#define REG_WDT1_WDOGLOAD       (*(__IO uint32_t*)0x40009000U) /**< (WDT1) Watchdog Load Register */
#define REG_WDT1_WDOGVALUE      (*(__I  uint32_t*)0x40009004U) /**< (WDT1) Watchdog Value Register */
#define REG_WDT1_WDOGCONTROL    (*(__IO uint8_t*)0x40009008U) /**< (WDT1) Watchdog Control Register */
#define REG_WDT1_WDOGINTCLR     (*(__O  uint8_t*)0x4000900CU) /**< (WDT1) Watchdog Clear Interrupt Register */
#define REG_WDT1_WDOGRIS        (*(__I  uint8_t*)0x40009010U) /**< (WDT1) Watchdog Raw Interrupt Status Register */
#define REG_WDT1_WDOGMIS        (*(__I  uint8_t*)0x40009014U) /**< (WDT1) Watchdog Interrupt Status Register */
#define REG_WDT1_WDOGLOCK       (*(__IO uint32_t*)0x40009C00U) /**< (WDT1) Watchdog Lock Register (Write 0x1ACCE551 to enable write access to all other registers) */
#define REG_WDT1_WDOGITCR       (*(__IO uint8_t*)0x40009F00U) /**< (WDT1) Watchdog Integration Test Control Register */
#define REG_WDT1_WDOGITOP       (*(__IO uint8_t*)0x40009F04U) /**< (WDT1) Watchdog Integration Test Output Set Register */
#define REG_WDT1_WDOGPERIPHID4  (*(__I  uint8_t*)0x40009FD0U) /**< (WDT1) Peripheral ID Register 4 */
#define REG_WDT1_WDOGPERIPHID5  (*(__I  uint8_t*)0x40009FD4U) /**< (WDT1) Peripheral ID Register 5 */
#define REG_WDT1_WDOGPERIPHID6  (*(__I  uint8_t*)0x40009FD8U) /**< (WDT1) Peripheral ID Register 6 */
#define REG_WDT1_WDOGPERIPHID7  (*(__I  uint8_t*)0x40009FDCU) /**< (WDT1) Peripheral ID Register 7 */
#define REG_WDT1_WDOGPERIPHID0  (*(__I  uint8_t*)0x40009FE0U) /**< (WDT1) Peripheral ID Register 0 */
#define REG_WDT1_WDOGPERIPHID1  (*(__I  uint8_t*)0x40009FE4U) /**< (WDT1) Peripheral ID Register 1 */
#define REG_WDT1_WDOGPERIPHID2  (*(__I  uint8_t*)0x40009FE8U) /**< (WDT1) Peripheral ID Register 2 */
#define REG_WDT1_WDOGPERIPHID3  (*(__I  uint8_t*)0x40009FECU) /**< (WDT1) Peripheral ID Register 3 */
#define REG_WDT1_WDOGPCELLID0   (*(__I  uint8_t*)0x40009FF0U) /**< (WDT1) Component ID Register 0 */
#define REG_WDT1_WDOGPCELLID1   (*(__I  uint8_t*)0x40009FF4U) /**< (WDT1) Component ID Register 1 */
#define REG_WDT1_WDOGPCELLID2   (*(__I  uint8_t*)0x40009FF8U) /**< (WDT1) Component ID Register 2 */
#define REG_WDT1_WDOGPCELLID3   (*(__I  uint8_t*)0x40009FFCU) /**< (WDT1) Component ID Register 3 */

#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMB11_WDT1_INSTANCE_ */
