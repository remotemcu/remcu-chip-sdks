/**
 * \file
 *
 * \brief SAM System Interrupt Driver Quick Start
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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

/**
 * \page asfdoc_sam0_system_interrupt_critsec_use_case Quick Start Guide for SYSTEM INTERRUPT - Critical Section Use Case
 *
 * In this case we perform a critical piece of code, disabling all interrupts
 * while a global shared flag is read. During the critical section, no interrupts
 * may occur.
 *
 * \section asfdoc_sam0_system_interrupt_critsec_use_case_setup Setup
 *
 * \subsection asfdoc_sam0_system_interrupt_critsec_use_case_setup_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \section asfdoc_sam0_system_interrupt_critsec_use_case_use_main Use Case
 *
 * \subsection asfdoc_sam0_system_interrupt_critsec_use_case_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_system_interrupt.c main_1
 *
 * \subsection asfdoc_sam0_system_interrupt_critsec_use_case_flow Workflow
 * -# Enter a critical section to disable global interrupts.
 *    \snippet qs_system_interrupt.c critical_section_start
 *    \note Critical sections <i>may</i> be nested if desired; if nested, global
 *          interrupts will only be re-enabled once the outer-most critical
 *          section has completed.
 *
 * -# Check a global shared flag and perform a response. This code may be any
 *    critical code that requires exclusive access to all resources without the
 *    possibility of interruption.
 *    \snippet qs_system_interrupt.c do_critical_code
 *
 * -# Exit the critical section to re-enable global interrupts.
 *    \snippet qs_system_interrupt.c critical_section_end
 */

/**
 * \page asfdoc_sam0_system_interrupt_enablemodint_use_case Quick Start Guide for SYSTEM INTERRUPT - Enable Module Interrupt Use Case
 *
 * In this case we enable interrupt handling for a specific module, as well as
 * enable interrupts globally for the device.
 *
 * \section asfdoc_sam0_system_interrupt_enablemodint_use_case_setup Setup
 *
 * \subsection asfdoc_sam0_system_interrupt_enablemodint_use_case_setup_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \section asfdoc_sam0_system_interrupt_enablemodint_use_case_use_main Use Case
 *
 * \subsection asfdoc_sam0_system_interrupt_enablemodint_use_case_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_system_interrupt.c main_2
 *
 * \subsection asfdoc_sam0_system_interrupt_enablemodint_use_case_flow Workflow
 * -# Enable interrupt handling for the device's RTC peripheral.
 *    \snippet qs_system_interrupt.c module_int_enable
 *
 * -# Enable global interrupts, so that any enabled and active interrupt sources
 *    can trigger their respective handler functions.
 *    \snippet qs_system_interrupt.c global_int_enable
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
