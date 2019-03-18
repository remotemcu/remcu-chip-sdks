/**
 * \file
 *
 * \brief Instance description for ARM_SYSCTRL0
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

#ifndef _SAMB11_ARM_SYSCTRL0_INSTANCE_
#define _SAMB11_ARM_SYSCTRL0_INSTANCE_

/* ========== Register definition for ARM_SYSCTRL0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_ARM_SYSCTRL0_ACTLR  (0xE000E008U) /**< (ARM_SYSCTRL0) Auxiliary Control Register (not implemented) */
#define REG_ARM_SYSCTRL0_SYST_CSR (0xE000E010U) /**< (ARM_SYSCTRL0) SysTick Control and Status Register */
#define REG_ARM_SYSCTRL0_SYST_RVR (0xE000E014U) /**< (ARM_SYSCTRL0) SysTick Reload Value Register */
#define REG_ARM_SYSCTRL0_SYST_CVR (0xE000E018U) /**< (ARM_SYSCTRL0) SysTick Current Value Register (Any Write Clears to 0) */
#define REG_ARM_SYSCTRL0_SYST_CALIB (0xE000E01CU) /**< (ARM_SYSCTRL0) SysTick Calibration Value Register */
#define REG_ARM_SYSCTRL0_NVIC_ISER (0xE000E100U) /**< (ARM_SYSCTRL0) Interrupt Set-Enable Register */
#define REG_ARM_SYSCTRL0_NVIC_ICER (0xE000E180U) /**< (ARM_SYSCTRL0) Interrupt Clear Enable Register */
#define REG_ARM_SYSCTRL0_NVIC_ISPR (0xE000E200U) /**< (ARM_SYSCTRL0) Interrupt Set-Pending Register */
#define REG_ARM_SYSCTRL0_NVIC_ICPR (0xE000E280U) /**< (ARM_SYSCTRL0) Interrupt Clear-Pending Register */
#define REG_ARM_SYSCTRL0_NVIC_IPR0 (0xE000E400U) /**< (ARM_SYSCTRL0) Interrupt Priority Register 0 */
#define REG_ARM_SYSCTRL0_NVIC_IPR1 (0xE000E404U) /**< (ARM_SYSCTRL0) Interrupt Priority Register 1 */
#define REG_ARM_SYSCTRL0_NVIC_IPR2 (0xE000E408U) /**< (ARM_SYSCTRL0) Interrupt Priority Register 2 */
#define REG_ARM_SYSCTRL0_NVIC_IPR3 (0xE000E40CU) /**< (ARM_SYSCTRL0) Interrupt Priority Register 3 */
#define REG_ARM_SYSCTRL0_NVIC_IPR4 (0xE000E410U) /**< (ARM_SYSCTRL0) Interrupt Priority Register 4 */
#define REG_ARM_SYSCTRL0_NVIC_IPR5 (0xE000E414U) /**< (ARM_SYSCTRL0) Interrupt Priority Register 5 */
#define REG_ARM_SYSCTRL0_NVIC_IPR6 (0xE000E418U) /**< (ARM_SYSCTRL0) Interrupt Priority Register 6 */
#define REG_ARM_SYSCTRL0_NVIC_IPR7 (0xE000E41CU) /**< (ARM_SYSCTRL0) Interrupt Priority Register 7 */
#define REG_ARM_SYSCTRL0_CPUID  (0xE000ED00U) /**< (ARM_SYSCTRL0) CPU Identification Register */
#define REG_ARM_SYSCTRL0_ICSR   (0xE000ED04U) /**< (ARM_SYSCTRL0) Interrupt Control State Register */
#define REG_ARM_SYSCTRL0_AIRCR  (0xE000ED0CU) /**< (ARM_SYSCTRL0) Application Interrupt and Reset Control Register */
#define REG_ARM_SYSCTRL0_SCR    (0xE000ED10U) /**< (ARM_SYSCTRL0) System Control Register */
#define REG_ARM_SYSCTRL0_CCR    (0xE000ED14U) /**< (ARM_SYSCTRL0) Configuration and Control Register */
#define REG_ARM_SYSCTRL0_SHPR2  (0xE000ED1CU) /**< (ARM_SYSCTRL0) System Handler Priority Register 2 */
#define REG_ARM_SYSCTRL0_SHPR3  (0xE000ED20U) /**< (ARM_SYSCTRL0) System Handler Priority Register 3 */
#define REG_ARM_SYSCTRL0_SHCSR  (0xE000ED24U) /**< (ARM_SYSCTRL0) System Handler Control and State Register */
#define REG_ARM_SYSCTRL0_DFSR   (0xE000ED30U) /**< (ARM_SYSCTRL0) Debug Fault Status Register */
#define REG_ARM_SYSCTRL0_DHCSR  (0xE000EDF0U) /**< (ARM_SYSCTRL0) Debug Halting Control and Status Register */
#define REG_ARM_SYSCTRL0_DCRSR  (0xE000EDF4U) /**< (ARM_SYSCTRL0) Debug Core Register Selector Register */
#define REG_ARM_SYSCTRL0_DCRDR  (0xE000EDF8U) /**< (ARM_SYSCTRL0) Debug Core Register Data Register */
#define REG_ARM_SYSCTRL0_DEMCR  (0xE000EDFCU) /**< (ARM_SYSCTRL0) Debug Exception and Monitor Control Register */
#define REG_ARM_SYSCTRL0_SCS_PID4 (0xE000EFD0U) /**< (ARM_SYSCTRL0) Peripheral ID Register 4 */
#define REG_ARM_SYSCTRL0_SCS_PID0 (0xE000EFE0U) /**< (ARM_SYSCTRL0) Peripheral ID Register 0 */
#define REG_ARM_SYSCTRL0_SCS_PID1 (0xE000EFE4U) /**< (ARM_SYSCTRL0) Peripheral ID Register 1 */
#define REG_ARM_SYSCTRL0_SCS_PID2 (0xE000EFE8U) /**< (ARM_SYSCTRL0) Peripheral ID Register 2 */
#define REG_ARM_SYSCTRL0_SCS_PID3 (0xE000EFECU) /**< (ARM_SYSCTRL0) Peripheral ID Register 3 */
#define REG_ARM_SYSCTRL0_SCS_CID0 (0xE000EFF0U) /**< (ARM_SYSCTRL0) Component ID Register 0 */
#define REG_ARM_SYSCTRL0_SCS_CID1 (0xE000EFF4U) /**< (ARM_SYSCTRL0) Component ID Register 1 */
#define REG_ARM_SYSCTRL0_SCS_CID2 (0xE000EFF8U) /**< (ARM_SYSCTRL0) Component ID Register 2 */
#define REG_ARM_SYSCTRL0_SCS_CID3 (0xE000EFFCU) /**< (ARM_SYSCTRL0) Component ID Register 3 */

#else

#define REG_ARM_SYSCTRL0_ACTLR  (*(__I  uint32_t*)0xE000E008U) /**< (ARM_SYSCTRL0) Auxiliary Control Register (not implemented) */
#define REG_ARM_SYSCTRL0_SYST_CSR (*(__IO uint32_t*)0xE000E010U) /**< (ARM_SYSCTRL0) SysTick Control and Status Register */
#define REG_ARM_SYSCTRL0_SYST_RVR (*(__IO uint32_t*)0xE000E014U) /**< (ARM_SYSCTRL0) SysTick Reload Value Register */
#define REG_ARM_SYSCTRL0_SYST_CVR (*(__IO uint32_t*)0xE000E018U) /**< (ARM_SYSCTRL0) SysTick Current Value Register (Any Write Clears to 0) */
#define REG_ARM_SYSCTRL0_SYST_CALIB (*(__I  uint32_t*)0xE000E01CU) /**< (ARM_SYSCTRL0) SysTick Calibration Value Register */
#define REG_ARM_SYSCTRL0_NVIC_ISER (*(__IO uint32_t*)0xE000E100U) /**< (ARM_SYSCTRL0) Interrupt Set-Enable Register */
#define REG_ARM_SYSCTRL0_NVIC_ICER (*(__IO uint32_t*)0xE000E180U) /**< (ARM_SYSCTRL0) Interrupt Clear Enable Register */
#define REG_ARM_SYSCTRL0_NVIC_ISPR (*(__IO uint32_t*)0xE000E200U) /**< (ARM_SYSCTRL0) Interrupt Set-Pending Register */
#define REG_ARM_SYSCTRL0_NVIC_ICPR (*(__IO uint32_t*)0xE000E280U) /**< (ARM_SYSCTRL0) Interrupt Clear-Pending Register */
#define REG_ARM_SYSCTRL0_NVIC_IPR0 (*(__IO uint32_t*)0xE000E400U) /**< (ARM_SYSCTRL0) Interrupt Priority Register 0 */
#define REG_ARM_SYSCTRL0_NVIC_IPR1 (*(__IO uint32_t*)0xE000E404U) /**< (ARM_SYSCTRL0) Interrupt Priority Register 1 */
#define REG_ARM_SYSCTRL0_NVIC_IPR2 (*(__IO uint32_t*)0xE000E408U) /**< (ARM_SYSCTRL0) Interrupt Priority Register 2 */
#define REG_ARM_SYSCTRL0_NVIC_IPR3 (*(__IO uint32_t*)0xE000E40CU) /**< (ARM_SYSCTRL0) Interrupt Priority Register 3 */
#define REG_ARM_SYSCTRL0_NVIC_IPR4 (*(__IO uint32_t*)0xE000E410U) /**< (ARM_SYSCTRL0) Interrupt Priority Register 4 */
#define REG_ARM_SYSCTRL0_NVIC_IPR5 (*(__IO uint32_t*)0xE000E414U) /**< (ARM_SYSCTRL0) Interrupt Priority Register 5 */
#define REG_ARM_SYSCTRL0_NVIC_IPR6 (*(__IO uint32_t*)0xE000E418U) /**< (ARM_SYSCTRL0) Interrupt Priority Register 6 */
#define REG_ARM_SYSCTRL0_NVIC_IPR7 (*(__IO uint32_t*)0xE000E41CU) /**< (ARM_SYSCTRL0) Interrupt Priority Register 7 */
#define REG_ARM_SYSCTRL0_CPUID  (*(__I  uint32_t*)0xE000ED00U) /**< (ARM_SYSCTRL0) CPU Identification Register */
#define REG_ARM_SYSCTRL0_ICSR   (*(__I  uint32_t*)0xE000ED04U) /**< (ARM_SYSCTRL0) Interrupt Control State Register */
#define REG_ARM_SYSCTRL0_AIRCR  (*(__I  uint32_t*)0xE000ED0CU) /**< (ARM_SYSCTRL0) Application Interrupt and Reset Control Register */
#define REG_ARM_SYSCTRL0_SCR    (*(__IO uint8_t*)0xE000ED10U) /**< (ARM_SYSCTRL0) System Control Register */
#define REG_ARM_SYSCTRL0_CCR    (*(__I  uint16_t*)0xE000ED14U) /**< (ARM_SYSCTRL0) Configuration and Control Register */
#define REG_ARM_SYSCTRL0_SHPR2  (*(__IO uint32_t*)0xE000ED1CU) /**< (ARM_SYSCTRL0) System Handler Priority Register 2 */
#define REG_ARM_SYSCTRL0_SHPR3  (*(__IO uint32_t*)0xE000ED20U) /**< (ARM_SYSCTRL0) System Handler Priority Register 3 */
#define REG_ARM_SYSCTRL0_SHCSR  (*(__IO uint16_t*)0xE000ED24U) /**< (ARM_SYSCTRL0) System Handler Control and State Register */
#define REG_ARM_SYSCTRL0_DFSR   (*(__IO uint8_t*)0xE000ED30U) /**< (ARM_SYSCTRL0) Debug Fault Status Register */
#define REG_ARM_SYSCTRL0_DHCSR  (*(__IO uint32_t*)0xE000EDF0U) /**< (ARM_SYSCTRL0) Debug Halting Control and Status Register */
#define REG_ARM_SYSCTRL0_DCRSR  (*(__IO uint32_t*)0xE000EDF4U) /**< (ARM_SYSCTRL0) Debug Core Register Selector Register */
#define REG_ARM_SYSCTRL0_DCRDR  (*(__IO uint32_t*)0xE000EDF8U) /**< (ARM_SYSCTRL0) Debug Core Register Data Register */
#define REG_ARM_SYSCTRL0_DEMCR  (*(__IO uint32_t*)0xE000EDFCU) /**< (ARM_SYSCTRL0) Debug Exception and Monitor Control Register */
#define REG_ARM_SYSCTRL0_SCS_PID4 (*(__I  uint8_t*)0xE000EFD0U) /**< (ARM_SYSCTRL0) Peripheral ID Register 4 */
#define REG_ARM_SYSCTRL0_SCS_PID0 (*(__I  uint8_t*)0xE000EFE0U) /**< (ARM_SYSCTRL0) Peripheral ID Register 0 */
#define REG_ARM_SYSCTRL0_SCS_PID1 (*(__I  uint8_t*)0xE000EFE4U) /**< (ARM_SYSCTRL0) Peripheral ID Register 1 */
#define REG_ARM_SYSCTRL0_SCS_PID2 (*(__I  uint8_t*)0xE000EFE8U) /**< (ARM_SYSCTRL0) Peripheral ID Register 2 */
#define REG_ARM_SYSCTRL0_SCS_PID3 (*(__I  uint8_t*)0xE000EFECU) /**< (ARM_SYSCTRL0) Peripheral ID Register 3 */
#define REG_ARM_SYSCTRL0_SCS_CID0 (*(__I  uint8_t*)0xE000EFF0U) /**< (ARM_SYSCTRL0) Component ID Register 0 */
#define REG_ARM_SYSCTRL0_SCS_CID1 (*(__I  uint8_t*)0xE000EFF4U) /**< (ARM_SYSCTRL0) Component ID Register 1 */
#define REG_ARM_SYSCTRL0_SCS_CID2 (*(__I  uint8_t*)0xE000EFF8U) /**< (ARM_SYSCTRL0) Component ID Register 2 */
#define REG_ARM_SYSCTRL0_SCS_CID3 (*(__I  uint8_t*)0xE000EFFCU) /**< (ARM_SYSCTRL0) Component ID Register 3 */

#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMB11_ARM_SYSCTRL0_INSTANCE_ */
