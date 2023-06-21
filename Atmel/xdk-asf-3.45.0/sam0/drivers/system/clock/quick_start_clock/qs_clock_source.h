/**
 * \file
 *
 * \brief SAM System Clock Driver Quick Start
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
 */

/**
 * \page asfdoc_sam0_system_clock_basic_use_case Quick Start Guide for SYSTEM CLOCK - Basic
 *
 * In this case we apply the following configuration:
 * - RC8MHz (internal 8MHz RC oscillator)
 *  - Divide by four, giving a frequency of 2MHz
 * - DFLL (Digital frequency locked loop)
 *  - Open loop mode
 *  - 48MHz frequency
 * - CPU clock
 *  - Use two wait states when reading from flash memory
 *  - Use the DFLL, configured to 48MHz
 *
 * \section asfdoc_sam0_system_clock_basic_use_case_setup Setup
 *
 * \subsection asfdoc_sam0_system_clock_basic_use_case_setup_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_sam0_system_clock_basic_use_case_setup_code Code
 * Copy-paste the following setup code to your application:
 * \snippet qs_clock_source.c setup
 *
 * \subsection asfdoc_sam0_system_clock_basic_use_case_setup_flow Workflow
 * -# Create a EXTOSC32K module configuration struct, which can be filled
 *    out to adjust the configuration of the external 32KHz oscillator channel.
 *    \snippet qs_clock_source.c config_extosc32k_config
 *
 * -# Initialize the oscillator configuration struct with the module's default
 *    values.
 *    \snippet qs_clock_source.c config_extosc32k_get_defaults
 *    \note This should always be performed before using the configuration
 *          struct to ensure that all values are initialized to known default
 *          settings.
 *
 * -# Alter the EXTOSC32K module configuration struct to require a start-up time
 *    of 4096 clock cycles.
 *    \snippet qs_clock_source.c config_extosc32k_change_defaults
 *
 * -# Write the new configuration to the EXTOSC32K module.
 *    \snippet qs_clock_source.c config_extosc32k_set_config
 *
 * -# Create a DFLL module configuration struct, which can be filled
 *    out to adjust the configuration of the external 32KHz oscillator channel.
 *    \snippet qs_clock_source.c config_dfll_config
 *
 * -# Initialize the DFLL oscillator configuration struct with the module's
 *    default values.
 *    \snippet qs_clock_source.c config_dfll_get_defaults
 *    \note This should always be performed before using the configuration
 *          struct to ensure that all values are initialized to known default
 *          settings.
 *
 * -# Write the new configuration to the DFLL module.
 *    \snippet qs_clock_source.c config_dfll_set_config
 *
 *
 * \section asfdoc_sam0_system_clock_basic_use_case_use_main Use Case
 *
 * \subsection asfdoc_sam0_system_clock_basic_use_case_code Code
 *
 * Copy-paste the following code to your user application:
 * \snippet qs_clock_source.c main
 *
 * \subsection asfdoc_sam0_system_clock_basic_use_case_flow Workflow
 * -# Configure the external 32KHz oscillator source using the previously
 *    defined setup function.
 *    \snippet qs_clock_source.c config_extosc32k_main
 *
 * -# Enable the configured external 32KHz oscillator source.
 *    \snippet qs_clock_source.c enable_extosc32k_main
 *
 * -# Configure the DFLL oscillator source using the previously defined setup
 *    function.
 *    \snippet qs_clock_source.c config_dfll_main
 *
 * -# Enable the configured DFLL oscillator source.
 *    \snippet qs_clock_source.c enable_dfll_main
 *
 * -# Configure the flash wait states to have two wait states per read, as the
 *    high speed DFLL will be used as the system clock. If insufficient wait
 *    states are used, the device may crash randomly due to misread instructions.
 *    \snippet qs_clock_source.c set_sys_wait_states
 *
 * -# Switch the system clock source to the DFLL, by reconfiguring the main
 *    clock generator.
 *    \snippet qs_clock_source.c set_sys_clk_src
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
