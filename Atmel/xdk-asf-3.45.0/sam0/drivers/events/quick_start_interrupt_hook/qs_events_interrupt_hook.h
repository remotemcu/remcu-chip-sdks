/**
 * \file
 *
 * \brief SAM Event System Driver Quick Start
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

/**
 * \page asfdoc_sam0_events_interrupt_hook_use_case Quick Start Guide for EVENTS - Interrupt Hooks
 *
 * In this use case, the EVENT module is configured for:
 *  \li Synchronous event path with rising edge detection
 *  \li TC4 as event generator on the allocated event channel (TC0 is used for SAM L22)
 *  \li One event channel user attached
 *  \li An event interrupt hook is used to execute some code when an event is detected
 *
 * In this use case TC is used as event generator, generating events on overflow.
 * One user attached, counting events on the channel. To be able to execute
 * some code when an event is detected, an interrupt hook is used. The interrupt
 * hook will also count the number of events detected and toggle a LED on the board
 * each time an event is detected.
 *
 * \note Because this example is showing how to set up an interrupt hook there is no
 *       user attached to the user.
 *
 * \section asfdoc_sam0_events_interrup_hook_setup Setup
 *
 * \subsection asfdoc_sam0_events_interrupt_hook_setup_prereq Prerequisites
 * There are no special setup requirements for this use case.
 *
 * \subsection asfdoc_sam0_events_interrupt_hook_setup_code Code
 * Add to the main application source file, before any functions, according to
 * the kit used:
 * - SAM D20 Xplained Pro:
 *   \snippet samd20_xplained_pro/conf_qs_events_interrupt_hook.h definition_event
 *   \snippet samd20_xplained_pro/conf_qs_events_interrupt_hook.h definition_tc
 * - SAM D21 Xplained Pro:
 *   \snippet samd21_xplained_pro/conf_qs_events_interrupt_hook.h definition_event
 *   \snippet samd21_xplained_pro/conf_qs_events_interrupt_hook.h definition_tc
 * - SAM R21 Xplained Pro:
 *   \snippet samr21_xplained_pro/conf_qs_events_interrupt_hook.h definition_event
 *   \snippet samr21_xplained_pro/conf_qs_events_interrupt_hook.h definition_tc
 * - SAM D11 Xplained Pro:
 *   \snippet samd11_xplained_pro/conf_qs_events_interrupt_hook.h definition_event
 *   \snippet samd11_xplained_pro/conf_qs_events_interrupt_hook.h definition_tc
 * - SAM L21 Xplained Pro:
 *   \snippet saml21_xplained_pro/conf_qs_events_interrupt_hook.h definition_event
 *   \snippet saml21_xplained_pro/conf_qs_events_interrupt_hook.h definition_tc
 * - SAM L22 Xplained Pro:
 *   \snippet saml22_xplained_pro/conf_qs_events_interrupt_hook.h definition_event
 *   \snippet saml22_xplained_pro/conf_qs_events_interrupt_hook.h definition_tc
 * - SAM DA1 Xplained Pro:
 *   \snippet samda1_xplained_pro/conf_qs_events_interrupt_hook.h definition_event
 *   \snippet samda1_xplained_pro/conf_qs_events_interrupt_hook.h definition_tc
 * - SAM C21 Xplained Pro:
 *   \snippet samc21_xplained_pro/conf_qs_events_interrupt_hook.h definition_event
 *   \snippet samc21_xplained_pro/conf_qs_events_interrupt_hook.h definition_tc
 * - SAM HA1G16A Xplained Pro
 *   \snippet samha1g16a_xplained_pro/conf_qs_events_interrupt_hook.h definition_event
 *   \snippet samha1g16a_xplained_pro/conf_qs_events_interrupt_hook.h definition_tc
 *
 * Copy-paste the following setup code to your user application:
 * \snippet qs_events_interrupt_hook.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_events_interrupt_hook.c setup_init
 *
 * \subsection asfdoc_sam0_events_interrupt_hook_setup_flow Workflow
 * -# Create an event channel configuration structure instance which will contain the
 *    configuration for the event.
 *  \snippet qs_events_interrupt_hook.c setup_1
 *  \br
 *
 * -# Initialize the event channel configuration struct with safe default values.
 *    \note This shall always be performed before using the configuration
 *          struct to ensure that all members are initialized to known default
 *          values.
 *
 *  \snippet qs_events_interrupt_hook.c setup_2
 *  \br
 *
 * -# Adjust the configuration structure:
 *      \li Use EXAMPLE_EVENT_GENRATOR as event generator
 *      \li Detect events on rising edge
 *      \li Use the synchronous event path
 *      \li Use GCLK Generator 0 as event channel clock source
 *
 *  \snippet qs_events_interrupt_hook.c setup_3
 *  \br
 *
 * -# Allocate and configure the channel using the configuration structure.
 *
 *  \snippet qs_events_interrupt_hook.c setup_4
 *  \br
 *
 * -# Make sure there is no user attached. To attach a user, change the value
 *    of EXAMPLE_EVENT_USER to the correct peripheral ID.
 *  \snippet qs_events_interrupt_hook.c setup_5
 *  \br
 *
 * -# Create config_tc and config_events configuration structure instances.
 *  \snippet qs_events_interrupt_hook.c setup_6
 *  \br
 *
 * -# Initialize the TC module configuration structure with safe default values.
 * \note This function shall always be called on new configuration structure instances
 *       to make sure that all structure members are initialized.
 *
 * \snippet qs_events_interrupt_hook.c setup_7
 *
 * -# Adjust the config_tc structure:
 *	\li Set counter size to 8-bit
 *	\li Set wave generation mode to normal frequency generation
 *	\li Use GCLK generator 1 to as TC module clock source
 *	\li Prescale the input clock with 64
 *
 * \snippet qs_events_interrupt_hook.c setup_8
 *
 * -# Initialize, configure, and assosiate the tc_instance handle with the TC hardware pointed to by TC_MODULE.
 * \snippet qs_events_interrupt_hook.c setup_9
 *
 * -# Adjust the config_events structure to enable event generation on overflow in the timer and then
 *    enable the event configuration.
 * \snippet qs_events_interrupt_hook.c setup_10
 *
 * -# Enable the timer/counter module.
 * \snippet qs_events_interrupt_hook.c setup_11
 *
 * -# Create a new interrupt hook and use the function event_counter as hook code.
 * \snippet qs_events_interrupt_hook.c setup_12
 *
 * -# Add the newly created hook to the interrupt hook queue and enable the event detected interrupt.
 * \snippet qs_events_interrupt_hook.c setup_13
 *
 * -# Example interrupt hook code. If the hook was triggered by an event detected interrupt on the
 *    event channel this code will toggle the LED on the Xplained PRO board and increase the value
 *    of the event_count variable. The interrupt is then acknowledged.
 *
 * \snippet qs_events_interrupt_hook.c setup_14
 *
 * \section asfdoc_sam0_events_interrupt_hook_main Use Case
 *
 * \subsection asfdoc_sam0_events_interrupt_hook_code_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_events_interrupt_hook.c main
 *
 * \subsection asfdoc_sam0_events_interrupt_hook_code_flow Workflow
 * -# Wait for the event channel to become ready.
 * \snippet qs_events_interrupt_hook.c main_1
 *
 * -# Start the timer/counter.
 * \snippet qs_events_interrupt_hook.c main_2
 */
