/**
 * \file
 *
 * \brief Instance description for OSCCTRL
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

#ifndef _SAMC21_OSCCTRL_INSTANCE_
#define _SAMC21_OSCCTRL_INSTANCE_

/* ========== Register definition for OSCCTRL peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_OSCCTRL_INTENCLR       (0x40001000U) /**< \brief (OSCCTRL) Interrupt Enable Clear */
#define REG_OSCCTRL_INTENSET       (0x40001004U) /**< \brief (OSCCTRL) Interrupt Enable Set */
#define REG_OSCCTRL_INTFLAG        (0x40001008U) /**< \brief (OSCCTRL) Interrupt Flag Status and Clear */
#define REG_OSCCTRL_STATUS         (0x4000100CU) /**< \brief (OSCCTRL) Power and Clocks Status */
#define REG_OSCCTRL_XOSCCTRL       (0x40001010U) /**< \brief (OSCCTRL) External Multipurpose Crystal Oscillator (XOSC) Control */
#define REG_OSCCTRL_CFDPRESC       (0x40001012U) /**< \brief (OSCCTRL) Cloc Failure Detector Prescaler */
#define REG_OSCCTRL_EVCTRL         (0x40001013U) /**< \brief (OSCCTRL) Event Control */
#define REG_OSCCTRL_OSC48MCTRL     (0x40001014U) /**< \brief (OSCCTRL) 48MHz Internal Oscillator (OSC48M) Control */
#define REG_OSCCTRL_OSC48MDIV      (0x40001015U) /**< \brief (OSCCTRL) OSC48M Divider */
#define REG_OSCCTRL_OSC48MSTUP     (0x40001016U) /**< \brief (OSCCTRL) OSC48M Startup Time */
#define REG_OSCCTRL_OSC48MSYNCBUSY (0x40001018U) /**< \brief (OSCCTRL) OSC48M Synchronization Busy */
#define REG_OSCCTRL_DPLLCTRLA      (0x4000101CU) /**< \brief (OSCCTRL) DPLL Control */
#define REG_OSCCTRL_DPLLRATIO      (0x40001020U) /**< \brief (OSCCTRL) DPLL Ratio Control */
#define REG_OSCCTRL_DPLLCTRLB      (0x40001024U) /**< \brief (OSCCTRL) Digital Core Configuration */
#define REG_OSCCTRL_DPLLPRESC      (0x40001028U) /**< \brief (OSCCTRL) DPLL Prescaler */
#define REG_OSCCTRL_DPLLSYNCBUSY   (0x4000102CU) /**< \brief (OSCCTRL) DPLL Synchronization Busy */
#define REG_OSCCTRL_DPLLSTATUS     (0x40001030U) /**< \brief (OSCCTRL) DPLL Status */
#else
#define REG_OSCCTRL_INTENCLR       (*(RwReg  *)0x40001000U) /**< \brief (OSCCTRL) Interrupt Enable Clear */
#define REG_OSCCTRL_INTENSET       (*(RwReg  *)0x40001004U) /**< \brief (OSCCTRL) Interrupt Enable Set */
#define REG_OSCCTRL_INTFLAG        (*(RwReg  *)0x40001008U) /**< \brief (OSCCTRL) Interrupt Flag Status and Clear */
#define REG_OSCCTRL_STATUS         (*(RoReg  *)0x4000100CU) /**< \brief (OSCCTRL) Power and Clocks Status */
#define REG_OSCCTRL_XOSCCTRL       (*(RwReg16*)0x40001010U) /**< \brief (OSCCTRL) External Multipurpose Crystal Oscillator (XOSC) Control */
#define REG_OSCCTRL_CFDPRESC       (*(RwReg8 *)0x40001012U) /**< \brief (OSCCTRL) Cloc Failure Detector Prescaler */
#define REG_OSCCTRL_EVCTRL         (*(RwReg8 *)0x40001013U) /**< \brief (OSCCTRL) Event Control */
#define REG_OSCCTRL_OSC48MCTRL     (*(RwReg8 *)0x40001014U) /**< \brief (OSCCTRL) 48MHz Internal Oscillator (OSC48M) Control */
#define REG_OSCCTRL_OSC48MDIV      (*(RwReg8 *)0x40001015U) /**< \brief (OSCCTRL) OSC48M Divider */
#define REG_OSCCTRL_OSC48MSTUP     (*(RwReg8 *)0x40001016U) /**< \brief (OSCCTRL) OSC48M Startup Time */
#define REG_OSCCTRL_OSC48MSYNCBUSY (*(RoReg  *)0x40001018U) /**< \brief (OSCCTRL) OSC48M Synchronization Busy */
#define REG_OSCCTRL_DPLLCTRLA      (*(RwReg8 *)0x4000101CU) /**< \brief (OSCCTRL) DPLL Control */
#define REG_OSCCTRL_DPLLRATIO      (*(RwReg  *)0x40001020U) /**< \brief (OSCCTRL) DPLL Ratio Control */
#define REG_OSCCTRL_DPLLCTRLB      (*(RwReg  *)0x40001024U) /**< \brief (OSCCTRL) Digital Core Configuration */
#define REG_OSCCTRL_DPLLPRESC      (*(RwReg8 *)0x40001028U) /**< \brief (OSCCTRL) DPLL Prescaler */
#define REG_OSCCTRL_DPLLSYNCBUSY   (*(RoReg8 *)0x4000102CU) /**< \brief (OSCCTRL) DPLL Synchronization Busy */
#define REG_OSCCTRL_DPLLSTATUS     (*(RoReg8 *)0x40001030U) /**< \brief (OSCCTRL) DPLL Status */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for OSCCTRL peripheral ========== */
#define OSCCTRL_GCLK_ID_FDPLL       0        // Index of Generic Clock for DPLL
#define OSCCTRL_GCLK_ID_FDPLL32K    1        // Index of Generic Clock for DPLL 32K
#define OSCCTRL_FDPLL_VERSION       0x211   
#define OSCCTRL_OSC48M_VERSION      0x101   
#define OSCCTRL_XOSC_VERSION        0x201   

#endif /* _SAMC21_OSCCTRL_INSTANCE_ */
