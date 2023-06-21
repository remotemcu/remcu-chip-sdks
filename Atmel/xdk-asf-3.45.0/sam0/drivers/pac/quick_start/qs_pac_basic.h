/**
 * \file
 *
 * \brief SAM PAC Quick Start
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
 * \page asfdoc_sam0_pac_basic_use_case Quick Start Guide for PAC - Basic
 *
 * In this use case, the peripheral-lock will be used to lock and unlock the
 * PORT peripheral access, and show how to implement the PAC module when the
 * PORT registers needs to be altered. The PORT will be set up as follows:
 * - One pin in input mode, with pull-up and falling edge-detect
 * - One pin in output mode
 *
 * \section asfdoc_sam0_pac_basic_use_case_setup Setup
 *
 * \subsection asfdoc_sam0_pac_basic_use_case_setup_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_sam0_pac_basic_use_case_setup_code Code
 * Copy-paste the following setup code to your user application:
 * \snippet qs_pac_basic.c pin_setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_pac_basic.c init
 *
 * \section asfdoc_sam0_pac_basic_use_case_use_main Use Case
 *
 * \subsection asfdoc_sam0_pac_basic_use_case_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_pac_basic.c main
 *
 * \subsection asfdoc_sam0_pac_basic_use_case_flow Workflow
 * -# Configure some GPIO port pins for input and output.
 *    \snippet qs_pac_basic.c init
 * -# Lock peripheral access for the PORT module; attempting to update the
 *    module while it is in a protected state will cause a CPU exception.
 *    For SAM D20/D21/D10/D11/R21/DA0/DA1/HA1, it is Hard Fault exception;
 *    For SAM L21/C21, it is system exception, see \ref SYSTEM_Handler().
 *    \snippet qs_pac_basic.c init_lock
 * -# Enable global interrupts.
 *    \snippet qs_pac_basic.c enable_interrupts
 * -# Loop to wait for a button press before continuing.
 *    \snippet qs_pac_basic.c button_press
 * -# Enter a critical section, so that the PAC module can be unlocked safely
 *    and the peripheral manipulated without the possibility of an interrupt
 *    modifying the protected module's state.
 *    \snippet qs_pac_basic.c disable_interrupts
 * -# Unlock the PORT peripheral registers.
 *    \snippet qs_pac_basic.c unlock_perph
 * -# Toggle pin 11, and clear edge detect flag.
 *    \snippet qs_pac_basic.c alter_config
 * -# Lock the PORT peripheral registers.
 *    \snippet qs_pac_basic.c lock_perph
 * -# Exit the critical section to allow interrupts to function normally again.
 *    \snippet qs_pac_basic.c enable_interrupts_2
 * -# Enter an infinite while loop once the module state has been modified
 *    successfully.
 *    \snippet qs_pac_basic.c inf_loop
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */










