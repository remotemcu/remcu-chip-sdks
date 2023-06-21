/**
 * \file
 *
 * \brief SAM External Interrupt Driver Quick Start
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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
 * \page asfdoc_sam0_extint_callback_use_case Quick Start Guide for EXTINT - Callback
 *
 * The supported board list:
 *    - SAM D20 Xplained Pro
 *    - SAM D21 Xplained Pro
 *    - SAM R21 Xplained Pro
 *    - SAM L21 Xplained Pro
 *    - SAM L22 Xplained Pro
 *    - SAM DA1 Xplained Pro
 *    - SAM C21 Xplained Pro
 *    - SAM HA1G16A Xplained Pro
 *
 * In this use case, the EXTINT module is configured for:
 *  - External interrupt channel connected to the board LED is used
 *  - External interrupt channel is configured to detect both input signal edges
 *  - Callbacks are used to handle detections from the External Interrupt
 *
 * This use case configures a physical I/O pin of the device so that it is
 * routed to a logical External Interrupt Controller channel to detect rising
 * and falling edges of the incoming signal. A callback function is used to
 * handle detection events from the External Interrupt module asynchronously.
 *
 * When the board button is pressed, the board LED will light up. When the board
 * button is released, the LED will turn off.
 *
 * \section asfdoc_sam0_extint_callback_setup Setup
 *
 * \subsection asfdoc_sam0_extint_callback_setup_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_sam0_extint_callback_setup_code Code
 * Copy-paste the following setup code to your user application:
 * \snippet qs_extint_callback.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_extint_callback.c setup_init
 *
 * \subsection asfdoc_sam0_extint_callback_setup_flow Workflow
 * -# Create an EXTINT module channel configuration struct, which can be filled
 *    out to adjust the configuration of a single external interrupt channel.
 *    \snippet qs_extint_callback.c setup_1
 * -# Initialize the channel configuration struct with the module's default
 *    values.
 *    \snippet qs_extint_callback.c setup_2
 *    \note This should always be performed before using the configuration
 *          struct to ensure that all values are initialized to known default
 *          settings.
 *
 * -# Adjust the configuration struct to configure the pin MUX (to route the
 *    desired physical pin to the logical channel) to the board button, and to
 *    configure the channel to detect both rising and falling edges.
 *    \snippet qs_extint_callback.c setup_3
 * -# Configure external interrupt channel with the desired channel settings.
 *    \snippet qs_extint_callback.c setup_4
 * -# Register a callback function \c extint_handler() to handle detections from
 *    the External Interrupt controller.
 *    \snippet qs_extint_callback.c setup_5
 * -# Enable the registered callback function for the configured External
 *    Interrupt channel, so that it will be called by the module when the
 *    channel detects an edge.
 *    \snippet qs_extint_callback.c setup_6
 * -# Define the EXTINT callback that will be fired when a detection event
 *    occurs. For this example, a LED will mirror the new button state on each
 *    detection edge.
 *    \snippet qs_extint_callback.c setup_7
 *
 *
 * \section asfdoc_sam0_extint_callback_main Use Case
 *
 * \subsection asfdoc_sam0_extint_callback_main_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_extint_callback.c main
 *
 * \subsection asfdoc_sam0_extint_callback_main_flow Workflow
 * -# External interrupt events from the driver are detected asynchronously; no
 *    special application \c main() code is required.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
