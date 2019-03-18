/**
 * \file
 *
 * \brief SAM TCC - Timer Counter for Control Applications Callback Driver Quick Start (with Recoverable Fault)
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
 * \page asfdoc_sam0_tcc_faultn_use_case Quick Start Guide for TCC - Recoverable Fault
 *
 * The supported board list:
 *    - SAM D21/R21/L21/L22/DA1/C21/HA1G16A Xplained Pro
 *
 * In this use case, the TCC will be used to generate a PWM signal, with a
 * varying duty cycle. Here the pulse width is increased each time the timer
 * count matches the set compare value. There is a recoverable fault input
 * which controls PWM output. When this fault is active (low) the PWM output
 * will be frozen (could be off or on, no light changing).
 * When fault is released (input high) the PWM output will go on.
 *
 * When the PWM signal connects to LED, LED will light. If fault input is from
 * a button, the LED will be frozen and not changing it's light
 * when the button is down and will go on when the button is up.
 * To see the PWM waveform, you may need an oscilloscope.
 * SAMHA1G16A Xpro LED is PA00 which isn't connected out, use PA04 instead,
 * so we can't see LED blink but only see the waveform from oscilloscope.
 *
 * The PWM output and fault input is set up as follows:
 * <table>
 *  <tr><th> Board             </td><th> Pin  </td><th> Connect to </td></tr>
 *  <tr><td> SAM D21 Xpro      </td><td> PB30 </td><td> LED0       </td></tr>
 *  <tr><td> SAM D21 Xpro      </td><td> PA15 </td><td> SW0        </td></tr>
 *  <tr><td> SAM R21 Xpro      </td><td> PA06 </td><td> EXT1 Pin 3 </td></tr>
 *  <tr><td> SAM R21 Xpro      </td><td> PA28 </td><td> SW0        </td></tr>
 *  <tr><td> SAM L21 Xpro      </td><td> PB10 </td><td> LED0       </td></tr>
 *  <tr><td> SAM L21 Xpro      </td><td> PA16 </td><td> SW0        </td></tr>
 *  <tr><td> SAM L22 Xpro      </td><td> PB18 </td><td> EXT3 Pin 9 </td></tr>
 *  <tr><td> SAM L22 Xpro      </td><td> PC01 </td><td> SW0        </td></tr>
 *  <tr><td> SAM DA1 Xpro      </td><td> PB30 </td><td> LED0       </td></tr>
 *  <tr><td> SAM DA1 Xpro      </td><td> PA15 </td><td> SW0        </td></tr>
 *  <tr><td> SAM C21 Xpro      </td><td> PA15 </td><td> LED0       </td></tr>
 *  <tr><td> SAM C21 Xpro      </td><td> PA28 </td><td> SW0        </td></tr>
 *  <tr><td> SAM HA1G16A Xpro  </td><td> PA04 </td><td> NULL       </td></tr>
 *  <tr><td> SAM HA1G16A Xpro  </td><td> PB03 </td><td> SW0        </td></tr>
 * </table>
 *
 * The TCC module will be set up as follows:
 * - GCLK generator 0 (GCLK main) clock source
 * - Use double buffering write when set top, compare, or pattern through API
 * - No dithering on the counter or compare
 * - No prescaler
 * - Single Slope PWM wave generation
 * - GCLK reload action
 * - Don't run in standby
 * - No waveform extentions
 * - No inversion of waveform output
 * - No capture enabled
 * - Count upward
 * - Don't perform one-shot operations
 * - No event input except channel 0 event enabled
 * - No event action
 * - No event generation enabled
 * - Counter starts on 0
 * - Recoverable Fault A is generated from channel 0 event input, fault halt
 *   acts as software halt, other actions or options are all disabled
 *
 * \section asfdoc_sam0_tcc_faultn_use_case_setup Quick Start
 *
 * \subsection asfdoc_sam0_tcc_faultn_use_case_prereq Prerequisites
 * There are no prerequisites for this use case.
 *
 * \subsection asfdoc_sam0_tcc_faultn_use_case_setup_code Code
 *
 * Add to the main application source file, before any functions, according to
 * the kit used:
 * - SAM D21 Xplained Pro
 *   \snippet samd21_xplained_pro/conf_quick_start_faultn.h definition_pwm
 *   \snippet samd21_xplained_pro/conf_quick_start_faultn.h definition_fault
 * - SAM R21 Xplained Pro
 *   \snippet samr21_xplained_pro/conf_quick_start_faultn.h definition_pwm
 *   \snippet samr21_xplained_pro/conf_quick_start_faultn.h definition_fault
 * - SAM L21 Xplained Pro
 *   \snippet saml21_xplained_pro/conf_quick_start_faultn.h definition_pwm
 *   \snippet saml21_xplained_pro/conf_quick_start_faultn.h definition_fault
 * - SAM L22 Xplained Pro
 *   \snippet saml22_xplained_pro/conf_quick_start_faultn.h definition_pwm
 *   \snippet saml22_xplained_pro/conf_quick_start_faultn.h definition_fault
 * - SAM DA1 Xplained Pro
 *   \snippet samda1_xplained_pro/conf_quick_start_faultn.h definition_pwm
 *   \snippet samda1_xplained_pro/conf_quick_start_faultn.h definition_fault
 * - SAM C21 Xplained Pro
 *   \snippet samc21_xplained_pro/conf_quick_start_faultx.h definition_pwm
 *   \snippet samc21_xplained_pro/conf_quick_start_faultx.h definition_fault
  * - SAM HA1G16A Xplained Pro:
 *   \snippet samha1g16a_xplained_pro/conf_quick_start_faultx.h definition_pwm
 *   \snippet samha1g16a_xplained_pro/conf_quick_start_faultx.h definition_fault
 *
 * Add to the main application source file, before any functions:
 * \snippet qs_tcc_faultn.c additional_include
 *
 * Add to the main application source file, outside of any functions:
 * \snippet qs_tcc_faultn.c module_inst
 * \snippet qs_tcc_faultn.c events_resource
 *
 * Copy-paste the following callback function code to your user application:
 * \snippet qs_tcc_faultn.c callback_funcs
 * \snippet qs_tcc_faultn.c callback_eic
 *
 * Copy-paste the following setup code to your user application:
 * \snippet qs_tcc_faultn.c setup
 * \snippet qs_tcc_faultn.c config_eic
 * \snippet qs_tcc_faultn.c config_event
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_tcc_faultn.c setup_init
 *
 * \subsection asfdoc_sam0_tcc_faultn_use_case_setup_flow Workflow
 * \subsubsection asfdoc_sam0_tcc_faultn_use_case_setup_flow_tcc Configure TCC
 * -# Create a module software instance struct for the TCC module to store
 *    the TCC driver state while it is in use.
 *    \snippet qs_tcc_faultn.c module_inst
 *    \note This should never go out of scope as long as the module is in use.
 *          In most cases, this should be global.
 *
 * -# Create a TCC module configuration struct, which can be filled out to
 *    adjust the configuration of a physical TCC peripheral.
 *    \snippet qs_tcc_faultn.c setup_config
 * -# Initialize the TCC configuration struct with the module's default values.
 *    \snippet qs_tcc_faultn.c setup_config_defaults
 *    \note This should always be performed before using the configuration
 *          struct to ensure that all values are initialized to known default
 *          settings.
 *
 * -# Alter the TCC settings to configure the counter width, wave generation
 *    mode, and the compare channel 0 value and fault options. Here the
 *    Recoverable Fault input is enabled and halt action is set to
 *    software mode (must use software to clear halt state).
 *    \snippet qs_tcc_faultn.c setup_change_config
 *    \snippet qs_tcc_faultn.c setup_change_config_faults
 * -# Alter the TCC settings to configure the PWM output on a physical device
 *    pin.
 *    \snippet qs_tcc_faultn.c setup_change_config_pwm
 * -# Configure the TCC module with the desired settings.
 *    \snippet qs_tcc_faultn.c setup_set_config
 *
 * -# Create a TCC events configuration struct, which can be filled out to
 *    enable/disable events and configure event settings. Reset all fields
 *    to zero.
 *    \snippet qs_tcc_faultn.c setup_events
 * -# Alter the TCC events settings to enable/disable desired events, to
 *    change event generating options and modify event actions. Here channel
 *    event 0 input is enabled as source of recoverable fault.
 *    \snippet qs_tcc_faultn.c setup_change_events_faults
 * -# Enable and apply events settings.
 *    \snippet qs_tcc_faultn.c setup_events_enable
 *
 * -# Enable the TCC module to start the timer and begin PWM signal generation.
 *    \snippet qs_tcc_faultn.c setup_enable
 *
 * -# Register the Compare Channel 0 Match callback functions with the driver.
 *    \snippet qs_tcc_faultn.c setup_register_callback
 * -# Enable the Compare Channel 0 Match callback so that it will be called by
 *    the driver when appropriate.
 *    \snippet qs_tcc_faultn.c setup_enable_callback
 *
 * \subsubsection asfdoc_sam0_tcc_faultn_use_case_setup_flow_eic Configure EXTINT for fault input
 * -# Create an EXTINT module channel configuration struct, which can be filled
 *    out to adjust the configuration of a single external interrupt channel.
 *    \snippet qs_tcc_faultn.c eic_setup_1
 * -# Initialize the channel configuration struct with the module's default
 *    values.
 *    \snippet qs_tcc_faultn.c eic_setup_2
 *    \note This should always be performed before using the configuration
 *          struct to ensure that all values are initialized to known default
 *          settings.
 *
 * -# Adjust the configuration struct to configure the pin MUX (to route the
 *    desired physical pin to the logical channel) to the board button, and to
 *    configure the channel to detect both rising and falling edges.
 *    \snippet qs_tcc_faultn.c eic_setup_3
 * -# Configure external interrupt channel with the desired channel settings.
 *    \snippet qs_tcc_faultn.c eic_setup_4
 *
 * -# Create a TXTINT events configuration struct, which can be filled out to
 *    enable/disable events. Reset all fields to zero.
 *    \snippet qs_tcc_faultn.c eic_event_setup_1
 * -# Adjust the configuration struct, set the channels to be enabled to
 *    \c true. Here the channel to the board button is used.
 *    \snippet qs_tcc_faultn.c eic_event_setup_2
 * -# Enable the events.
 *    \snippet qs_tcc_faultn.c eic_event_setup_3
 *
 * -# Define the EXTINT callback that will be fired when a detection event
 *    occurs. For this example, when fault line is released, the TCC fault
 *    state is cleared to go on PWM generating.
 *    \snippet qs_tcc_faultn.c callback_eic
 * -# Register a callback function \c eic_callback_to_clear_halt() to handle
 *    detections from the External Interrupt Controller (EIC).
 *    \snippet qs_tcc_faultn.c eic_callback_setup_1
 * -# Enable the registered callback function for the configured External
 *    Interrupt channel, so that it will be called by the module when the
 *    channel detects an edge.
 *    \snippet qs_tcc_faultn.c eic_callback_setup_2
 *
 * \subsubsection asfdoc_sam0_tcc_faultn_use_case_setup_flow_evt Configure EVENTS for fault input
 * -# Create an event resource instance struct for the EVENTS module to store.
 *    \snippet qs_tcc_faultn.c events_resource
 *    \note This should never go out of scope as long as the resource is in use.
 *          In most cases, this should be global.
 * -# Create an event channel configuration struct, which can be filled out to
 *    adjust the configuration of a single event channel.
 *    \snippet qs_tcc_faultn.c event_setup_1
 * -# Initialize the event channel configuration struct with the module's
 *    default values.
 *    \snippet qs_tcc_faultn.c event_setup_2
 *    \note This should always be performed before using the configuration
 *          struct to ensure that all values are initialized to known default
 *          settings.
 *
 * -# Adjust the configuration struct to request that the channel will be attached
 *    to the specified event generator, and that the asynchronous event path will
 *    be used. Here the EIC channel connected to board button is the event
 *    generator.
 *    \snippet qs_tcc_faultn.c event_setup_3
 * -# Allocate and configure the channel using the configuration structure.
 *    \snippet qs_tcc_faultn.c event_setup_4
 *    \note The existing configuration struct may be re-used, as long as any
 *          values that have been altered from the default settings are taken
 *          into account by the user application.
 *
 * -# Attach a user to the channel. Here the user is TCC channel 0 event,
 *    which has been configured as input of Recoverable Fault.
 *    \snippet qs_tcc_faultn.c event_setup_5
 *
 * \section asfdoc_sam0_tcc_faultn_use_case_main Use Case
 *
 * \subsection asfdoc_sam0_tcc_faultn_use_case_main_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_tcc_callback.c main
 *
 * \subsection asfdoc_sam0_tcc_faultn_use_case_main_flow Workflow
 * -# Enter an infinite loop while the PWM wave is generated via the TCC module.
 *  \snippet qs_tcc_callback.c main_loop
 */


#include <asf.h>
#include <conf_clocks.h>