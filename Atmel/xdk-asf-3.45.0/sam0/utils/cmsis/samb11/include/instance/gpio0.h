/**
 * \file
 *
 * \brief Instance description for GPIO0
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

#ifndef _SAMB11_GPIO0_INSTANCE_
#define _SAMB11_GPIO0_INSTANCE_

/* ========== Register definition for GPIO0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_GPIO0_DATA          (0x40010000U) /**< (GPIO0) Data Value */
#define REG_GPIO0_DATAOUT       (0x40010004U) /**< (GPIO0) Data Output Register Value */
#define REG_GPIO0_OUTENSET      (0x40010010U) /**< (GPIO0) Output Enable Set */
#define REG_GPIO0_OUTENCLR      (0x40010014U) /**< (GPIO0) Output Enable Clear */
#define REG_GPIO0_INTENSET      (0x40010020U) /**< (GPIO0) Interrupt Enable Set */
#define REG_GPIO0_INTENCLR      (0x40010024U) /**< (GPIO0) Interrupt Enable Clear */
#define REG_GPIO0_INTTYPESET    (0x40010028U) /**< (GPIO0) Interrupt Type Set */
#define REG_GPIO0_INTTYPECLR    (0x4001002CU) /**< (GPIO0) Interrupt Type Clear */
#define REG_GPIO0_INTPOLSET     (0x40010030U) /**< (GPIO0) Polarity-level, edge IRQ Configuration */
#define REG_GPIO0_INTPOLCLR     (0x40010034U) /**< (GPIO0) IRQ Configuration Clear */
#define REG_GPIO0_INTSTATUSCLEAR (0x40010038U) /**< (GPIO0) Interrupt Status */
#define REG_GPIO0_PID4          (0x40010FD0U) /**< (GPIO0) Peripheral ID Register 4 */
#define REG_GPIO0_PID5          (0x40010FD4U) /**< (GPIO0) Peripheral ID Register 5 */
#define REG_GPIO0_PID6          (0x40010FD8U) /**< (GPIO0) Peripheral ID Register 6 */
#define REG_GPIO0_PID7          (0x40010FDCU) /**< (GPIO0) Peripheral ID Register 7 */
#define REG_GPIO0_PID0          (0x40010FE0U) /**< (GPIO0) Peripheral ID Register 0 */
#define REG_GPIO0_PID1          (0x40010FE4U) /**< (GPIO0) Peripheral ID Register 1 */
#define REG_GPIO0_PID2          (0x40010FE8U) /**< (GPIO0) Peripheral ID Register 2 */
#define REG_GPIO0_PID3          (0x40010FECU) /**< (GPIO0) Peripheral ID Register 3 */
#define REG_GPIO0_CID0          (0x40010FF0U) /**< (GPIO0) Component ID Register 0 */
#define REG_GPIO0_CID1          (0x40010FF4U) /**< (GPIO0) Component ID Register 1 */
#define REG_GPIO0_CID2          (0x40010FF8U) /**< (GPIO0) Component ID Register 2 */
#define REG_GPIO0_CID3          (0x40010FFCU) /**< (GPIO0) Component ID Register 3 */

#else

#define REG_GPIO0_DATA          (*(__IO uint16_t*)0x40010000U) /**< (GPIO0) Data Value */
#define REG_GPIO0_DATAOUT       (*(__IO uint16_t*)0x40010004U) /**< (GPIO0) Data Output Register Value */
#define REG_GPIO0_OUTENSET      (*(__IO uint16_t*)0x40010010U) /**< (GPIO0) Output Enable Set */
#define REG_GPIO0_OUTENCLR      (*(__IO uint16_t*)0x40010014U) /**< (GPIO0) Output Enable Clear */
#define REG_GPIO0_INTENSET      (*(__IO uint16_t*)0x40010020U) /**< (GPIO0) Interrupt Enable Set */
#define REG_GPIO0_INTENCLR      (*(__IO uint16_t*)0x40010024U) /**< (GPIO0) Interrupt Enable Clear */
#define REG_GPIO0_INTTYPESET    (*(__IO uint16_t*)0x40010028U) /**< (GPIO0) Interrupt Type Set */
#define REG_GPIO0_INTTYPECLR    (*(__IO uint16_t*)0x4001002CU) /**< (GPIO0) Interrupt Type Clear */
#define REG_GPIO0_INTPOLSET     (*(__IO uint16_t*)0x40010030U) /**< (GPIO0) Polarity-level, edge IRQ Configuration */
#define REG_GPIO0_INTPOLCLR     (*(__IO uint16_t*)0x40010034U) /**< (GPIO0) IRQ Configuration Clear */
#define REG_GPIO0_INTSTATUSCLEAR (*(__IO uint16_t*)0x40010038U) /**< (GPIO0) Interrupt Status */
#define REG_GPIO0_PID4          (*(__I  uint8_t*)0x40010FD0U) /**< (GPIO0) Peripheral ID Register 4 */
#define REG_GPIO0_PID5          (*(__I  uint8_t*)0x40010FD4U) /**< (GPIO0) Peripheral ID Register 5 */
#define REG_GPIO0_PID6          (*(__I  uint8_t*)0x40010FD8U) /**< (GPIO0) Peripheral ID Register 6 */
#define REG_GPIO0_PID7          (*(__I  uint8_t*)0x40010FDCU) /**< (GPIO0) Peripheral ID Register 7 */
#define REG_GPIO0_PID0          (*(__I  uint8_t*)0x40010FE0U) /**< (GPIO0) Peripheral ID Register 0 */
#define REG_GPIO0_PID1          (*(__I  uint8_t*)0x40010FE4U) /**< (GPIO0) Peripheral ID Register 1 */
#define REG_GPIO0_PID2          (*(__I  uint8_t*)0x40010FE8U) /**< (GPIO0) Peripheral ID Register 2 */
#define REG_GPIO0_PID3          (*(__I  uint8_t*)0x40010FECU) /**< (GPIO0) Peripheral ID Register 3 */
#define REG_GPIO0_CID0          (*(__I  uint8_t*)0x40010FF0U) /**< (GPIO0) Component ID Register 0 */
#define REG_GPIO0_CID1          (*(__I  uint8_t*)0x40010FF4U) /**< (GPIO0) Component ID Register 1 */
#define REG_GPIO0_CID2          (*(__I  uint8_t*)0x40010FF8U) /**< (GPIO0) Component ID Register 2 */
#define REG_GPIO0_CID3          (*(__I  uint8_t*)0x40010FFCU) /**< (GPIO0) Component ID Register 3 */

#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMB11_GPIO0_INSTANCE_ */
