/**
 * \file
 *
 * \brief SAM Power Driver Quick Start
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

 /** \page asfdoc_sam0_power_basic_use_case Quick Start Guide for Power Driver
 *
 * List of supported boards:
 *    - SAM L21 Xplained Pro
 *    - SAM L22 Xplained Pro
 *    - SAM L22 Xplained Pro B
 *
 * This example demonstrates how to use the power driver. BUTTON0 is used to
 * wake up the system from the standby sleep mode and as an external wakeup pin
 * to wake up the system from the backup sleep mode. The wakeup pin level is low.
 * The I/O pins PB22/PB23 are used as GCLK0/GCLK1 outputs so that an oscilloscope
 * can be used to monitor the clock frequencies.
 *
 * After power-on-reset (POR), GCLK0 and GCLK1 runs at 4MHz and LED0 is turned on.
 * After one second, LED0 is turned off and the system enters standby sleep mode.
 * BUTTON0 can then be used to wake up the system. After the system wakeup, LED0
 * is turned on, the performance level is switched to PL2, and the GCLK0 is increased
 * to 48MHz. Further LED0 toggles two times and is turned off before the system
 * enters BACKUP.
 *
 * When BUTTON0 pushes, it connects to low level, system wakes up from the backup
 * sleep mode, LED0 toggles four times. GCLK0/GCLK1 are running at 4MHz.
 *
 * \section asfdoc_sam0_power_basic_use_case_setup Quick Start
 *
 * \subsection asfdoc_sam0_power_basic_use_case_prereq Prerequisites
 * There are no prerequisites for this use case.
 *
 * \subsection asfdoc_sam0_power_basic_use_case_setup_code Code
 *
 * Copy-paste the following setup code to your user application:
 * \snippet quick_start/qs_power.c setup
 *
 * \subsection asfdoc_sam0_power_basic_use_case_setup_flow Workflow
 * -# Switch performance level to PL2.
 *    \snippet quick_start/qs_power.c switch_pl
 *
 * -# Configure GCLK0/GCLK1 output pin and extwakeup pin.
 *    \snippet quick_start/qs_power.c pin_mux
 *
 * -# Config external interrupt.
 *    \snippet quick_start/qs_power.c config_extint
 *
 * \section asfdoc_sam0_power_basic_use_case_main Use Case
 *
 * \subsection asfdoc_sam0_power_basic_use_case_main_code Code
 * Copy-paste the following code to your user application:
 * \snippet quick_start/qs_power.c  setup_init
 *
 * \subsection asfdoc_sam0_power_basic_use_case_main_flow Workflow
 * -# Check if the RESET is caused by external wakeup pin.
 *    \snippet quick_start/qs_power.c ext_wakeup
 * -# Check the standby mode and the backup sleep mode.
 *    \snippet quick_start/qs_power.c backup_stanby_mode
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
