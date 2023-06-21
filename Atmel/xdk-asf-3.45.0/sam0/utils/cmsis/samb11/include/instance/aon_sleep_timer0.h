/**
 * \file
 *
 * \brief Instance description for AON_SLEEP_TIMER0
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

#ifndef _SAMB11_AON_SLEEP_TIMER0_INSTANCE_
#define _SAMB11_AON_SLEEP_TIMER0_INSTANCE_

/* ========== Register definition for AON_SLEEP_TIMER0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_AON_SLEEP_TIMER0_CONTROL (0x4000D000U) /**< (AON_SLEEP_TIMER0) Control for the Always On Sleep Timer */
#define REG_AON_SLEEP_TIMER0_SINGLE_COUNT_DURATION (0x4000D004U) /**< (AON_SLEEP_TIMER0) Count for the single count AND reload */
#define REG_AON_SLEEP_TIMER0_CURRENT_COUNT_VALUE (0x4000D00CU) /**< (AON_SLEEP_TIMER0) Current count of the sleep timer */

#else

#define REG_AON_SLEEP_TIMER0_CONTROL (*(__IO uint32_t*)0x4000D000U) /**< (AON_SLEEP_TIMER0) Control for the Always On Sleep Timer */
#define REG_AON_SLEEP_TIMER0_SINGLE_COUNT_DURATION (*(__IO uint32_t*)0x4000D004U) /**< (AON_SLEEP_TIMER0) Count for the single count AND reload */
#define REG_AON_SLEEP_TIMER0_CURRENT_COUNT_VALUE (*(__I  uint32_t*)0x4000D00CU) /**< (AON_SLEEP_TIMER0) Current count of the sleep timer */

#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMB11_AON_SLEEP_TIMER0_INSTANCE_ */
