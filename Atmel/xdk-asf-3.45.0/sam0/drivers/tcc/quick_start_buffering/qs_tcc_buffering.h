/**
 * \file
 *
 * \brief SAM TCC Driver Double Buffering Quick Start
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
 * \page asfdoc_sam0_tcc_buffering_use_case Quick Start Guide for TCC - Double Buffering and Circular
 *
 * The supported board list:
 *    - SAM D21/R21/L21/L22/DA1/C21/HA1G16A Xplained Pro
 *
 * In this use case, the TCC will be used to generate a PWM signal. Here
 * the pulse width alters in one quarter and three quarter of the period.
 * When the PWM signal connects to LED, LED will light. To see the waveform,
 * you may need an oscilloscope.
 * SAMHA1G16A Xpro LED is PA00 which isn't connected out, use PA04 instead,
 * so we can't see LED blink but only see the waveform from oscilloscope.
 *
 * The PWM output is set up as follows:
 * <table>
 *  <tr><th> Board             </td><th> Pin  </td><th> Connect to </td></tr>
 *  <tr><td> SAM D21 Xpro      </td><td> PB30 </td><td> LED0       </td></tr>
 *  <tr><td> SAM R21 Xpro      </td><td> PA19 </td><td> LED0       </td></tr>
 *  <tr><td> SAM L21 Xpro      </td><td> PB10 </td><td> LED0       </td></tr>
 *  <tr><td> SAM L22 Xpro      </td><td> PC27 </td><td> LED0       </td></tr>
 *  <tr><td> SAM DA1 Xpro      </td><td> PB30 </td><td> LED0       </td></tr>
 *  <tr><td> SAM C21 Xpro      </td><td> PA15 </td><td> LED0       </td></tr>
 *  <tr><td> SAM HA1G16A Xpro  </td><td> PA04 </td><td> NULL       </td></tr>
 * </table>
 *
 * The TCC module will be set up as follows:
 * - GCLK generator 0 (GCLK main) clock source
 * - Use double buffering write when set top, compare, or pattern through API
 * - No dithering on the counter or compare
 * - Prescaler is set to 1024
 * - Single Slope PWM wave generation
 * - GCLK reload action
 * - Don't run in standby
 * - No fault or waveform extensions
 * - No inversion of waveform output
 * - No capture enabled
 * - Count upward
 * - Don't perform one-shot operations
 * - No event input enabled
 * - No event action
 * - No event generation enabled
 * - Counter starts on 0
 * - Counter top set to 8000
 * - Capture compare channel set to 8000/4
 * - Capture compare channel buffer set to 8000*3/4
 * - Circular option for compare channel is enabled so that the compare
 *   values keep switching on update condition
 *
 * \section asfdoc_sam0_tcc_buffering_use_case_setup Quick Start
 *
 * \subsection asfdoc_sam0_tcc_buffering_use_case_prereq Prerequisites
 * There are no prerequisites for this use case.
 *
 * \subsection asfdoc_sam0_tcc_buffering_use_case_setup_code Code
 *
 * Add to the main application source file, before any functions:
 * \snippet conf_quick_start_buffering.h definition_pwm
 *
 * Add to the main application source file, outside of any functions:
 * \snippet qs_tcc_buffering.c module_inst
 *
 * Copy-paste the following setup code to your user application:
 * \snippet qs_tcc_buffering.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_tcc_buffering.c setup_init
 *
 * \subsection asfdoc_sam0_tcc_buffering_use_case_setup_flow Workflow
 * -# Create a module software instance structure for the TCC module to store
 *    the TCC driver state while it is in use.
 *    \snippet qs_tcc_buffering.c module_inst
 *    \note This should never go out of scope as long as the module is in use.
 *          In most cases, this should be global.
 *
 * -# Configure the TCC module.
 *  -# Create a TCC module configuration struct, which can be filled out to
 *     adjust the configuration of a physical TCC peripheral.
 *     \snippet qs_tcc_buffering.c setup_config
 *  -# Initialize the TCC configuration struct with the module's default values.
 *     \snippet qs_tcc_buffering.c setup_config_defaults
 *     \note This should always be performed before using the configuration
 *           struct to ensure that all values are initialized to known default
 *           settings.
 *
 *  -# Alter the TCC settings to configure the counter width, wave generation
 *     mode, and the compare channel 0 value.
 *     \snippet qs_tcc_buffering.c setup_change_config
 *  -# Alter the TCC settings to configure the PWM output on a physical device
 *     pin.
 *     \snippet qs_tcc_buffering.c setup_change_config_pwm
 *  -# Configure the TCC module with the desired settings.
 *     \snippet qs_tcc_buffering.c setup_set_config
 *  -# Set to compare buffer value and enable circular of double buffered
 *     compare values.
 *     \snippet qs_tcc_buffering.c setup_set_buffering
 *  -# Enable the TCC module to start the timer and begin PWM signal generation.
 *     \snippet qs_tcc_buffering.c setup_enable
 *
 *
 * \section asfdoc_sam0_tcc_buffering_use_case_main Use Case
 *
 * \subsection asfdoc_sam0_tcc_buffering_use_case_main_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_tcc_buffering.c main
 *
 * \subsection asfdoc_sam0_tcc_buffering_use_case_main_flow Workflow
 * -# Enter an infinite loop while the PWM wave is generated via the TCC module.
 *  \snippet qs_tcc_buffering.c main_loop
 */
