/**
 * \file
 *
 * \brief Instance description for TIMER0
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

#ifndef _SAMB11_TIMER0_INSTANCE_
#define _SAMB11_TIMER0_INSTANCE_

/* ========== Register definition for TIMER0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_TIMER0_CTRL         (0x40000000U) /**< (TIMER0) Timer Control */
#define REG_TIMER0_VALUE        (0x40000004U) /**< (TIMER0) Current Value */
#define REG_TIMER0_RELOAD       (0x40000008U) /**< (TIMER0) Reload Value */
#define REG_TIMER0_INTSTATUSCLEAR (0x4000000CU) /**< (TIMER0) Timer Interrupt, write 1 to clear */
#define REG_TIMER0_PID4         (0x40000FD0U) /**< (TIMER0) Peripheral ID Register 4 */
#define REG_TIMER0_PID5         (0x40000FD4U) /**< (TIMER0) Peripheral ID Register 5 */
#define REG_TIMER0_PID6         (0x40000FD8U) /**< (TIMER0) Peripheral ID Register 6 */
#define REG_TIMER0_PID7         (0x40000FDCU) /**< (TIMER0) Peripheral ID Register 7 */
#define REG_TIMER0_PID0         (0x40000FE0U) /**< (TIMER0) Peripheral ID Register 0 */
#define REG_TIMER0_PID1         (0x40000FE4U) /**< (TIMER0) Peripheral ID Register 1 */
#define REG_TIMER0_PID2         (0x40000FE8U) /**< (TIMER0) Peripheral ID Register 2 */
#define REG_TIMER0_PID3         (0x40000FECU) /**< (TIMER0) Peripheral ID Register 3 */
#define REG_TIMER0_CID0         (0x40000FF0U) /**< (TIMER0) Component ID Register 0 */
#define REG_TIMER0_CID1         (0x40000FF4U) /**< (TIMER0) Component ID Register 1 */
#define REG_TIMER0_CID2         (0x40000FF8U) /**< (TIMER0) Component ID Register 2 */
#define REG_TIMER0_CID3         (0x40000FFCU) /**< (TIMER0) Component ID Register 3 */

#else

#define REG_TIMER0_CTRL         (*(__IO uint8_t*)0x40000000U) /**< (TIMER0) Timer Control */
#define REG_TIMER0_VALUE        (*(__IO uint32_t*)0x40000004U) /**< (TIMER0) Current Value */
#define REG_TIMER0_RELOAD       (*(__IO uint32_t*)0x40000008U) /**< (TIMER0) Reload Value */
#define REG_TIMER0_INTSTATUSCLEAR (*(__IO uint8_t*)0x4000000CU) /**< (TIMER0) Timer Interrupt, write 1 to clear */
#define REG_TIMER0_PID4         (*(__I  uint8_t*)0x40000FD0U) /**< (TIMER0) Peripheral ID Register 4 */
#define REG_TIMER0_PID5         (*(__I  uint8_t*)0x40000FD4U) /**< (TIMER0) Peripheral ID Register 5 */
#define REG_TIMER0_PID6         (*(__I  uint8_t*)0x40000FD8U) /**< (TIMER0) Peripheral ID Register 6 */
#define REG_TIMER0_PID7         (*(__I  uint8_t*)0x40000FDCU) /**< (TIMER0) Peripheral ID Register 7 */
#define REG_TIMER0_PID0         (*(__I  uint8_t*)0x40000FE0U) /**< (TIMER0) Peripheral ID Register 0 */
#define REG_TIMER0_PID1         (*(__I  uint8_t*)0x40000FE4U) /**< (TIMER0) Peripheral ID Register 1 */
#define REG_TIMER0_PID2         (*(__I  uint8_t*)0x40000FE8U) /**< (TIMER0) Peripheral ID Register 2 */
#define REG_TIMER0_PID3         (*(__I  uint8_t*)0x40000FECU) /**< (TIMER0) Peripheral ID Register 3 */
#define REG_TIMER0_CID0         (*(__I  uint8_t*)0x40000FF0U) /**< (TIMER0) Component ID Register 0 */
#define REG_TIMER0_CID1         (*(__I  uint8_t*)0x40000FF4U) /**< (TIMER0) Component ID Register 1 */
#define REG_TIMER0_CID2         (*(__I  uint8_t*)0x40000FF8U) /**< (TIMER0) Component ID Register 2 */
#define REG_TIMER0_CID3         (*(__I  uint8_t*)0x40000FFCU) /**< (TIMER0) Component ID Register 3 */

#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMB11_TIMER0_INSTANCE_ */
