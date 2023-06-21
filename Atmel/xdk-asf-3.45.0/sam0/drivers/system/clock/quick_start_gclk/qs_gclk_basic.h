/**
 * \file
 *
 * \brief SAM Generic Clock Driver Quick Start
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
 * \page asfdoc_sam0_system_gclk_basic_use_case Quick Start Guide for SYSTEM CLOCK - GCLK Configuration
 *
 * In this use-case, the GCLK module is configured for:
 *  \li One generator attached to the internal 8MHz RC oscillator clock source
 *  \li Generator output equal to input frequency divided by a factor of 128
 *  \li One channel (connected to the TC0 module) enabled with the enabled generator selected
 *
 * This use-case configures a clock channel to output a clock for a peripheral
 * within the device, by first setting up a clock generator from a master clock
 * source, and then linking the generator to the desired channel. This clock
 * can then be used to clock a module within the device.
 *
 * \section asfdoc_sam0_system_gclk_basic_use_case_setup Setup
 *
 * \subsection asfdoc_sam0_system_gclk_basic_use_case_setup_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_sam0_system_gclk_basic_use_case_setup_code Code
 * Copy-paste the following setup code to your user application:
 * \snippet qs_gclk_basic.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_gclk_basic.c setup_init
 *
 * \subsection asfdoc_sam0_system_gclk_basic_use_case_setup_flow Workflow
 * -# Create a GCLK generator configuration struct, which can be filled out to
 *    adjust the configuration of a single clock generator.
 *  \snippet qs_gclk_basic.c setup_1
 * -# Initialize the generator configuration struct with the module's default
 *    values.
 *    \snippet qs_gclk_basic.c setup_2
 *    \note This should always be performed before using the configuration
 *          struct to ensure that all values are initialized to known default
 *          settings.
 *
 * -# Adjust the configuration struct to request the master clock source
 *    channel 0 is used as the source of the generator, and set the generator
 *    output prescaler to divide the input clock by a factor of 128.
 *    \snippet qs_gclk_basic.c setup_3
 * -# Configure the generator using the configuration structure.
 *    \snippet qs_gclk_basic.c setup_4
 *    \note The existing configuration struct may be re-used, as long as any
 *          values that have been altered from the default settings are taken
 *          into account by the user application.
 *
 * -# Enable the generator once it has been properly configured, to begin clock
 *    generation.
 *    \snippet qs_gclk_basic.c setup_5
 *
 * -# Create a GCLK channel configuration struct, which can be filled out to
 *    adjust the configuration of a single generic clock channel.
 *    \snippet qs_gclk_basic.c setup_6
 * -# Initialize the channel configuration struct with the module's default
 *    values.
 *    \snippet qs_gclk_basic.c setup_7
 *    \note This should always be performed before using the configuration
 *          struct to ensure that all values are initialized to known default
 *          settings.
 *
 * -# Adjust the configuration struct to request the previously configured
 *    and enabled clock generator is used as the clock source for the channel.
 *  \snippet qs_gclk_basic.c setup_8
 * -# Configure the channel using the configuration structure.
 *    \snippet qs_gclk_basic.c setup_9
 *    \note The existing configuration struct may be re-used, as long as any
 *          values that have been altered from the default settings are taken
 *          into account by the user application.
 *
 * -# Enable the channel once it has been properly configured, to output the
 *    clock to the channel's peripheral module consumers.
 *    \snippet qs_gclk_basic.c setup_10
 *
 * \section asfdoc_sam0_system_gclk_basic_use_case_main Use-case
 *
 * \subsection asfdoc_sam0_system_gclk_basic_use_case_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_gclk_basic.c main
 *
 * \subsection asfdoc_sam0_system_gclk_basic_use_case_flow Workflow
 * -# As the clock is generated asynchronously to the system core, no special
 *    extra application code is required.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
