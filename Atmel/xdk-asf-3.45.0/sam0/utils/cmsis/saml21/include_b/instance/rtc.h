/**
 * \file
 *
 * \brief Instance description for RTC
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

#ifndef _SAML21_RTC_INSTANCE_
#define _SAML21_RTC_INSTANCE_

/* ========== Register definition for RTC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_RTC_DBGCTRL            (0x4000200EU) /**< \brief (RTC) Debug Control */
#define REG_RTC_FREQCORR           (0x40002014U) /**< \brief (RTC) Frequency Correction */
#define REG_RTC_GP0                (0x40002040U) /**< \brief (RTC) General Purpose 0 */
#define REG_RTC_GP1                (0x40002044U) /**< \brief (RTC) General Purpose 1 */
#define REG_RTC_GP2                (0x40002048U) /**< \brief (RTC) General Purpose 2 */
#define REG_RTC_GP3                (0x4000204CU) /**< \brief (RTC) General Purpose 3 */
#define REG_RTC_MODE0_CTRLA        (0x40002000U) /**< \brief (RTC) MODE0 Control A */
#define REG_RTC_MODE0_EVCTRL       (0x40002004U) /**< \brief (RTC) MODE0 Event Control */
#define REG_RTC_MODE0_INTENCLR     (0x40002008U) /**< \brief (RTC) MODE0 Interrupt Enable Clear */
#define REG_RTC_MODE0_INTENSET     (0x4000200AU) /**< \brief (RTC) MODE0 Interrupt Enable Set */
#define REG_RTC_MODE0_INTFLAG      (0x4000200CU) /**< \brief (RTC) MODE0 Interrupt Flag Status and Clear */
#define REG_RTC_MODE0_SYNCBUSY     (0x40002010U) /**< \brief (RTC) MODE0 Synchronization Busy Status */
#define REG_RTC_MODE0_COUNT        (0x40002018U) /**< \brief (RTC) MODE0 Counter Value */
#define REG_RTC_MODE0_COMP0        (0x40002020U) /**< \brief (RTC) MODE0 Compare 0 Value */
#define REG_RTC_MODE1_CTRLA        (0x40002000U) /**< \brief (RTC) MODE1 Control A */
#define REG_RTC_MODE1_EVCTRL       (0x40002004U) /**< \brief (RTC) MODE1 Event Control */
#define REG_RTC_MODE1_INTENCLR     (0x40002008U) /**< \brief (RTC) MODE1 Interrupt Enable Clear */
#define REG_RTC_MODE1_INTENSET     (0x4000200AU) /**< \brief (RTC) MODE1 Interrupt Enable Set */
#define REG_RTC_MODE1_INTFLAG      (0x4000200CU) /**< \brief (RTC) MODE1 Interrupt Flag Status and Clear */
#define REG_RTC_MODE1_SYNCBUSY     (0x40002010U) /**< \brief (RTC) MODE1 Synchronization Busy Status */
#define REG_RTC_MODE1_COUNT        (0x40002018U) /**< \brief (RTC) MODE1 Counter Value */
#define REG_RTC_MODE1_PER          (0x4000201CU) /**< \brief (RTC) MODE1 Counter Period */
#define REG_RTC_MODE1_COMP0        (0x40002020U) /**< \brief (RTC) MODE1 Compare 0 Value */
#define REG_RTC_MODE1_COMP1        (0x40002022U) /**< \brief (RTC) MODE1 Compare 1 Value */
#define REG_RTC_MODE2_CTRLA        (0x40002000U) /**< \brief (RTC) MODE2 Control A */
#define REG_RTC_MODE2_EVCTRL       (0x40002004U) /**< \brief (RTC) MODE2 Event Control */
#define REG_RTC_MODE2_INTENCLR     (0x40002008U) /**< \brief (RTC) MODE2 Interrupt Enable Clear */
#define REG_RTC_MODE2_INTENSET     (0x4000200AU) /**< \brief (RTC) MODE2 Interrupt Enable Set */
#define REG_RTC_MODE2_INTFLAG      (0x4000200CU) /**< \brief (RTC) MODE2 Interrupt Flag Status and Clear */
#define REG_RTC_MODE2_SYNCBUSY     (0x40002010U) /**< \brief (RTC) MODE2 Synchronization Busy Status */
#define REG_RTC_MODE2_CLOCK        (0x40002018U) /**< \brief (RTC) MODE2 Clock Value */
#define REG_RTC_MODE2_ALARM_ALARM0 (0x40002020U) /**< \brief (RTC) MODE2_ALARM Alarm 0 Value */
#define REG_RTC_MODE2_ALARM_MASK0  (0x40002024U) /**< \brief (RTC) MODE2_ALARM Alarm 0 Mask */
#else
#define REG_RTC_DBGCTRL            (*(RwReg8 *)0x4000200EU) /**< \brief (RTC) Debug Control */
#define REG_RTC_FREQCORR           (*(RwReg8 *)0x40002014U) /**< \brief (RTC) Frequency Correction */
#define REG_RTC_GP0                (*(RwReg  *)0x40002040U) /**< \brief (RTC) General Purpose 0 */
#define REG_RTC_GP1                (*(RwReg  *)0x40002044U) /**< \brief (RTC) General Purpose 1 */
#define REG_RTC_GP2                (*(RwReg  *)0x40002048U) /**< \brief (RTC) General Purpose 2 */
#define REG_RTC_GP3                (*(RwReg  *)0x4000204CU) /**< \brief (RTC) General Purpose 3 */
#define REG_RTC_MODE0_CTRLA        (*(RwReg16*)0x40002000U) /**< \brief (RTC) MODE0 Control A */
#define REG_RTC_MODE0_EVCTRL       (*(RwReg  *)0x40002004U) /**< \brief (RTC) MODE0 Event Control */
#define REG_RTC_MODE0_INTENCLR     (*(RwReg16*)0x40002008U) /**< \brief (RTC) MODE0 Interrupt Enable Clear */
#define REG_RTC_MODE0_INTENSET     (*(RwReg16*)0x4000200AU) /**< \brief (RTC) MODE0 Interrupt Enable Set */
#define REG_RTC_MODE0_INTFLAG      (*(RwReg16*)0x4000200CU) /**< \brief (RTC) MODE0 Interrupt Flag Status and Clear */
#define REG_RTC_MODE0_SYNCBUSY     (*(RoReg  *)0x40002010U) /**< \brief (RTC) MODE0 Synchronization Busy Status */
#define REG_RTC_MODE0_COUNT        (*(RwReg  *)0x40002018U) /**< \brief (RTC) MODE0 Counter Value */
#define REG_RTC_MODE0_COMP0        (*(RwReg  *)0x40002020U) /**< \brief (RTC) MODE0 Compare 0 Value */
#define REG_RTC_MODE1_CTRLA        (*(RwReg16*)0x40002000U) /**< \brief (RTC) MODE1 Control A */
#define REG_RTC_MODE1_EVCTRL       (*(RwReg  *)0x40002004U) /**< \brief (RTC) MODE1 Event Control */
#define REG_RTC_MODE1_INTENCLR     (*(RwReg16*)0x40002008U) /**< \brief (RTC) MODE1 Interrupt Enable Clear */
#define REG_RTC_MODE1_INTENSET     (*(RwReg16*)0x4000200AU) /**< \brief (RTC) MODE1 Interrupt Enable Set */
#define REG_RTC_MODE1_INTFLAG      (*(RwReg16*)0x4000200CU) /**< \brief (RTC) MODE1 Interrupt Flag Status and Clear */
#define REG_RTC_MODE1_SYNCBUSY     (*(RoReg  *)0x40002010U) /**< \brief (RTC) MODE1 Synchronization Busy Status */
#define REG_RTC_MODE1_COUNT        (*(RwReg16*)0x40002018U) /**< \brief (RTC) MODE1 Counter Value */
#define REG_RTC_MODE1_PER          (*(RwReg16*)0x4000201CU) /**< \brief (RTC) MODE1 Counter Period */
#define REG_RTC_MODE1_COMP0        (*(RwReg16*)0x40002020U) /**< \brief (RTC) MODE1 Compare 0 Value */
#define REG_RTC_MODE1_COMP1        (*(RwReg16*)0x40002022U) /**< \brief (RTC) MODE1 Compare 1 Value */
#define REG_RTC_MODE2_CTRLA        (*(RwReg16*)0x40002000U) /**< \brief (RTC) MODE2 Control A */
#define REG_RTC_MODE2_EVCTRL       (*(RwReg  *)0x40002004U) /**< \brief (RTC) MODE2 Event Control */
#define REG_RTC_MODE2_INTENCLR     (*(RwReg16*)0x40002008U) /**< \brief (RTC) MODE2 Interrupt Enable Clear */
#define REG_RTC_MODE2_INTENSET     (*(RwReg16*)0x4000200AU) /**< \brief (RTC) MODE2 Interrupt Enable Set */
#define REG_RTC_MODE2_INTFLAG      (*(RwReg16*)0x4000200CU) /**< \brief (RTC) MODE2 Interrupt Flag Status and Clear */
#define REG_RTC_MODE2_SYNCBUSY     (*(RoReg  *)0x40002010U) /**< \brief (RTC) MODE2 Synchronization Busy Status */
#define REG_RTC_MODE2_CLOCK        (*(RwReg  *)0x40002018U) /**< \brief (RTC) MODE2 Clock Value */
#define REG_RTC_MODE2_ALARM_ALARM0 (*(RwReg  *)0x40002020U) /**< \brief (RTC) MODE2_ALARM Alarm 0 Value */
#define REG_RTC_MODE2_ALARM_MASK0  (*(RwReg  *)0x40002024U) /**< \brief (RTC) MODE2_ALARM Alarm 0 Mask */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for RTC peripheral ========== */
#define RTC_ALARM_NUM               1        // Number of Alarms
#define RTC_COMP16_NUM              2        // Number of 16-bit Comparators
#define RTC_COMP32_NUM              1        // Number of 32-bit Comparators
#define RTC_GPR_NUM                 4        // Number of General-Purpose Registers
#define RTC_PER_NUM                 8        // Number of Periodic Intervals

#endif /* _SAML21_RTC_INSTANCE_ */
