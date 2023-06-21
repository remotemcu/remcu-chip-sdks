/**
 * \file
 *
 * \brief Instance description for GPIO1
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

#ifndef _SAMB11_GPIO1_INSTANCE_
#define _SAMB11_GPIO1_INSTANCE_

/* ========== Register definition for GPIO1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_GPIO1_DATA          (0x40011000U) /**< (GPIO1) Data Value */
#define REG_GPIO1_DATAOUT       (0x40011004U) /**< (GPIO1) Data Output Register Value */
#define REG_GPIO1_OUTENSET      (0x40011010U) /**< (GPIO1) Output Enable Set */
#define REG_GPIO1_OUTENCLR      (0x40011014U) /**< (GPIO1) Output Enable Clear */
#define REG_GPIO1_INTENSET      (0x40011020U) /**< (GPIO1) Interrupt Enable Set */
#define REG_GPIO1_INTENCLR      (0x40011024U) /**< (GPIO1) Interrupt Enable Clear */
#define REG_GPIO1_INTTYPESET    (0x40011028U) /**< (GPIO1) Interrupt Type Set */
#define REG_GPIO1_INTTYPECLR    (0x4001102CU) /**< (GPIO1) Interrupt Type Clear */
#define REG_GPIO1_INTPOLSET     (0x40011030U) /**< (GPIO1) Polarity-level, edge IRQ Configuration */
#define REG_GPIO1_INTPOLCLR     (0x40011034U) /**< (GPIO1) IRQ Configuration Clear */
#define REG_GPIO1_INTSTATUSCLEAR (0x40011038U) /**< (GPIO1) Interrupt Status */
#define REG_GPIO1_PID4          (0x40011FD0U) /**< (GPIO1) Peripheral ID Register 4 */
#define REG_GPIO1_PID5          (0x40011FD4U) /**< (GPIO1) Peripheral ID Register 5 */
#define REG_GPIO1_PID6          (0x40011FD8U) /**< (GPIO1) Peripheral ID Register 6 */
#define REG_GPIO1_PID7          (0x40011FDCU) /**< (GPIO1) Peripheral ID Register 7 */
#define REG_GPIO1_PID0          (0x40011FE0U) /**< (GPIO1) Peripheral ID Register 0 */
#define REG_GPIO1_PID1          (0x40011FE4U) /**< (GPIO1) Peripheral ID Register 1 */
#define REG_GPIO1_PID2          (0x40011FE8U) /**< (GPIO1) Peripheral ID Register 2 */
#define REG_GPIO1_PID3          (0x40011FECU) /**< (GPIO1) Peripheral ID Register 3 */
#define REG_GPIO1_CID0          (0x40011FF0U) /**< (GPIO1) Component ID Register 0 */
#define REG_GPIO1_CID1          (0x40011FF4U) /**< (GPIO1) Component ID Register 1 */
#define REG_GPIO1_CID2          (0x40011FF8U) /**< (GPIO1) Component ID Register 2 */
#define REG_GPIO1_CID3          (0x40011FFCU) /**< (GPIO1) Component ID Register 3 */

#else

#define REG_GPIO1_DATA          (*(__IO uint16_t*)0x40011000U) /**< (GPIO1) Data Value */
#define REG_GPIO1_DATAOUT       (*(__IO uint16_t*)0x40011004U) /**< (GPIO1) Data Output Register Value */
#define REG_GPIO1_OUTENSET      (*(__IO uint16_t*)0x40011010U) /**< (GPIO1) Output Enable Set */
#define REG_GPIO1_OUTENCLR      (*(__IO uint16_t*)0x40011014U) /**< (GPIO1) Output Enable Clear */
#define REG_GPIO1_INTENSET      (*(__IO uint16_t*)0x40011020U) /**< (GPIO1) Interrupt Enable Set */
#define REG_GPIO1_INTENCLR      (*(__IO uint16_t*)0x40011024U) /**< (GPIO1) Interrupt Enable Clear */
#define REG_GPIO1_INTTYPESET    (*(__IO uint16_t*)0x40011028U) /**< (GPIO1) Interrupt Type Set */
#define REG_GPIO1_INTTYPECLR    (*(__IO uint16_t*)0x4001102CU) /**< (GPIO1) Interrupt Type Clear */
#define REG_GPIO1_INTPOLSET     (*(__IO uint16_t*)0x40011030U) /**< (GPIO1) Polarity-level, edge IRQ Configuration */
#define REG_GPIO1_INTPOLCLR     (*(__IO uint16_t*)0x40011034U) /**< (GPIO1) IRQ Configuration Clear */
#define REG_GPIO1_INTSTATUSCLEAR (*(__IO uint16_t*)0x40011038U) /**< (GPIO1) Interrupt Status */
#define REG_GPIO1_PID4          (*(__I  uint8_t*)0x40011FD0U) /**< (GPIO1) Peripheral ID Register 4 */
#define REG_GPIO1_PID5          (*(__I  uint8_t*)0x40011FD4U) /**< (GPIO1) Peripheral ID Register 5 */
#define REG_GPIO1_PID6          (*(__I  uint8_t*)0x40011FD8U) /**< (GPIO1) Peripheral ID Register 6 */
#define REG_GPIO1_PID7          (*(__I  uint8_t*)0x40011FDCU) /**< (GPIO1) Peripheral ID Register 7 */
#define REG_GPIO1_PID0          (*(__I  uint8_t*)0x40011FE0U) /**< (GPIO1) Peripheral ID Register 0 */
#define REG_GPIO1_PID1          (*(__I  uint8_t*)0x40011FE4U) /**< (GPIO1) Peripheral ID Register 1 */
#define REG_GPIO1_PID2          (*(__I  uint8_t*)0x40011FE8U) /**< (GPIO1) Peripheral ID Register 2 */
#define REG_GPIO1_PID3          (*(__I  uint8_t*)0x40011FECU) /**< (GPIO1) Peripheral ID Register 3 */
#define REG_GPIO1_CID0          (*(__I  uint8_t*)0x40011FF0U) /**< (GPIO1) Component ID Register 0 */
#define REG_GPIO1_CID1          (*(__I  uint8_t*)0x40011FF4U) /**< (GPIO1) Component ID Register 1 */
#define REG_GPIO1_CID2          (*(__I  uint8_t*)0x40011FF8U) /**< (GPIO1) Component ID Register 2 */
#define REG_GPIO1_CID3          (*(__I  uint8_t*)0x40011FFCU) /**< (GPIO1) Component ID Register 3 */

#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMB11_GPIO1_INSTANCE_ */
