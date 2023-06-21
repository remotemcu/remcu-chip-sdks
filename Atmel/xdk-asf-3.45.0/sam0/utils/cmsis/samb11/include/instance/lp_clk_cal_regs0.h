/**
 * \file
 *
 * \brief Instance description for LP_CLK_CAL_REGS0
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

#ifndef _SAMB11_LP_CLK_CAL_REGS0_INSTANCE_
#define _SAMB11_LP_CLK_CAL_REGS0_INSTANCE_

/* ========== Register definition for LP_CLK_CAL_REGS0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_LP_CLK_CAL_REGS0_CONFIG_REG (0x4000C000U) /**< (LP_CLK_CAL_REGS0) Configuration of the calibration clocks and the enable of calibration */
#define REG_LP_CLK_CAL_REGS0_CALIB_OSC_COUNT_REG (0x4000C004U) /**< (LP_CLK_CAL_REGS0) Calibration OSC Count Register (Any write sets bit 15 and clears bit 31) */
#define REG_LP_CLK_CAL_REGS0_CALIB_RTC_COUNT_REG (0x4000C008U) /**< (LP_CLK_CAL_REGS0) Calibration RTC Count Register (Any write sets bit 15 and clears bit 31) */
#define REG_LP_CLK_CAL_REGS0_CALIB_STATUS_REG (0x4000C00CU) /**< (LP_CLK_CAL_REGS0) Calibration Status Register */

#else

#define REG_LP_CLK_CAL_REGS0_CONFIG_REG (*(__IO uint16_t*)0x4000C000U) /**< (LP_CLK_CAL_REGS0) Configuration of the calibration clocks and the enable of calibration */
#define REG_LP_CLK_CAL_REGS0_CALIB_OSC_COUNT_REG (*(__I  uint32_t*)0x4000C004U) /**< (LP_CLK_CAL_REGS0) Calibration OSC Count Register (Any write sets bit 15 and clears bit 31) */
#define REG_LP_CLK_CAL_REGS0_CALIB_RTC_COUNT_REG (*(__I  uint32_t*)0x4000C008U) /**< (LP_CLK_CAL_REGS0) Calibration RTC Count Register (Any write sets bit 15 and clears bit 31) */
#define REG_LP_CLK_CAL_REGS0_CALIB_STATUS_REG (*(__I  uint8_t*)0x4000C00CU) /**< (LP_CLK_CAL_REGS0) Calibration Status Register */

#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMB11_LP_CLK_CAL_REGS0_INSTANCE_ */
