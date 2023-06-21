/**
 * \file
 *
 * \brief Instance description for OSC32KCTRL
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

#ifndef _SAMC21_OSC32KCTRL_INSTANCE_
#define _SAMC21_OSC32KCTRL_INSTANCE_

/* ========== Register definition for OSC32KCTRL peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_OSC32KCTRL_INTENCLR    (0x40001400U) /**< \brief (OSC32KCTRL) Interrupt Enable Clear */
#define REG_OSC32KCTRL_INTENSET    (0x40001404U) /**< \brief (OSC32KCTRL) Interrupt Enable Set */
#define REG_OSC32KCTRL_INTFLAG     (0x40001408U) /**< \brief (OSC32KCTRL) Interrupt Flag Status and Clear */
#define REG_OSC32KCTRL_STATUS      (0x4000140CU) /**< \brief (OSC32KCTRL) Power and Clocks Status */
#define REG_OSC32KCTRL_RTCCTRL     (0x40001410U) /**< \brief (OSC32KCTRL) Clock selection */
#define REG_OSC32KCTRL_XOSC32K     (0x40001414U) /**< \brief (OSC32KCTRL) 32kHz External Crystal Oscillator (XOSC32K) Control */
#define REG_OSC32KCTRL_CFDCTRL     (0x40001416U) /**< \brief (OSC32KCTRL) Clock Failure Detector Control */
#define REG_OSC32KCTRL_EVCTRL      (0x40001417U) /**< \brief (OSC32KCTRL) Event Control */
#define REG_OSC32KCTRL_OSC32K      (0x40001418U) /**< \brief (OSC32KCTRL) 32kHz Internal Oscillator (OSC32K) Control */
#define REG_OSC32KCTRL_OSCULP32K   (0x4000141CU) /**< \brief (OSC32KCTRL) 32kHz Ultra Low Power Internal Oscillator (OSCULP32K) Control */
#else
#define REG_OSC32KCTRL_INTENCLR    (*(RwReg  *)0x40001400U) /**< \brief (OSC32KCTRL) Interrupt Enable Clear */
#define REG_OSC32KCTRL_INTENSET    (*(RwReg  *)0x40001404U) /**< \brief (OSC32KCTRL) Interrupt Enable Set */
#define REG_OSC32KCTRL_INTFLAG     (*(RwReg  *)0x40001408U) /**< \brief (OSC32KCTRL) Interrupt Flag Status and Clear */
#define REG_OSC32KCTRL_STATUS      (*(RoReg  *)0x4000140CU) /**< \brief (OSC32KCTRL) Power and Clocks Status */
#define REG_OSC32KCTRL_RTCCTRL     (*(RwReg  *)0x40001410U) /**< \brief (OSC32KCTRL) Clock selection */
#define REG_OSC32KCTRL_XOSC32K     (*(RwReg16*)0x40001414U) /**< \brief (OSC32KCTRL) 32kHz External Crystal Oscillator (XOSC32K) Control */
#define REG_OSC32KCTRL_CFDCTRL     (*(RwReg8 *)0x40001416U) /**< \brief (OSC32KCTRL) Clock Failure Detector Control */
#define REG_OSC32KCTRL_EVCTRL      (*(RwReg8 *)0x40001417U) /**< \brief (OSC32KCTRL) Event Control */
#define REG_OSC32KCTRL_OSC32K      (*(RwReg  *)0x40001418U) /**< \brief (OSC32KCTRL) 32kHz Internal Oscillator (OSC32K) Control */
#define REG_OSC32KCTRL_OSCULP32K   (*(RwReg  *)0x4000141CU) /**< \brief (OSC32KCTRL) 32kHz Ultra Low Power Internal Oscillator (OSCULP32K) Control */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for OSC32KCTRL peripheral ========== */
#define OSC32KCTRL_OSC32K_COARSE_CALIB_MSB 6       

#endif /* _SAMC21_OSC32KCTRL_INSTANCE_ */
