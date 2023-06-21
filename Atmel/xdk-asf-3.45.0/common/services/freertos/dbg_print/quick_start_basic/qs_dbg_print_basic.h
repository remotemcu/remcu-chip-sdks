/**
 * \file
 *
 * \brief Debug print basic quick start guide
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

/**
 * \page asfdoc_common_freertos_dbg_print_basic_use_case Quick Start Guide for Debug Print Service for FreeRTOS
 *
 * In this use case, the Debug Print service is configured with the following
 * settings:
 * - 128-byte print buffer
 * - output via the SERCOM UART connected to Embedded Debugger (EDBG) on an
 *    Xplained Pro board
 * - 9600 baud transfer rate
 *
 * A FreeRTOS task is created which every second prints a constant string and
 * a string containing an incrementing 32-bit hexadecimal integer.
 *
 *
 * \section asfdoc_common_freertos_dbg_print_basic_use_setup Setup
 *
 * \subsection asfdoc_common_freertos_dbg_print_basic_use_setup_prereq Prerequisites
 *
 * FreeRTOS must be added to the project, and the clock driver must be
 * configured to initialize GCLK 0 to 48 MHz. Note that FreeRTOS also has a
 * setting for the system clock frequency which must be updated.
 *
 *
 * \subsection asfdoc_common_freertos_dbg_print_basic_use_setup_code Code
 *
 * The following must be added to the file conf_dbg_print.h:
 * \snippet conf_dbg_print.h  config_include
 * \snippet conf_dbg_print.h  config_buffer
 * \snippet conf_dbg_print.h  config_sercom
 *
 *
 * \section asfdoc_common_freertos_dbg_print_basic_use_setup_workflow Workflow
 *
 * -# Include board definition to get settings for output to EDBG:
 *    \snippet conf_dbg_print.h  config_include
 * -# Set buffer size to 128 byte:
 *    \snippet conf_dbg_print.h  config_buffer
 * -# Use SERCOM connected to EDBG CDC for output at 9600 baud:
 *    \snippet conf_dbg_print.h  config_sercom
 *
 *
 * \section asfdoc_common_freertos_dbg_print_basic_use Use Case
 *
 * \subsection asfdoc_common_freertos_dbg_print_basic_use_code Code
 *
 * Add the following to your main application C file:
 * \snippet qs_dbg_print_basic.c  main_task_data
 * \snippet qs_dbg_print_basic.c  main_task
 *
 * Add the following to your application's \c main() function:
 * \snippet qs_dbg_print_basic.c  init_calls
 * \snippet qs_dbg_print_basic.c  main_task_create
 * \snippet qs_dbg_print_basic.c  freertos_start
 *
 *
 * \subsection asfdoc_common_freertos_dbg_print_basic_use_workflow Workflow
 *
 * -# Define debug variables to print out:
 *    \snippet qs_dbg_print_basic.c  main_task_data
 * -# Define a FreeRTOS task for printing debug data forever:
 *    \snippet qs_dbg_print_basic.c  main_task_open
 * -# Print a constant string at the start of the task-loop:
 *    \snippet qs_dbg_print_basic.c  main_task_1
 * -# Write a hexadecimal integer into a string and print it:
 *    \snippet qs_dbg_print_basic.c  main_task_2
 *    \note \ref dbg_sprint_hexint() does not write the \c 0x prefix, only the
 *      hexadecimal digits.
 * -# Add a 1 sec delay at the of the task-loop and close the task definition:
 *    \snippet qs_dbg_print_basic.c main_task_close
 * -# In \c main(), initialize the system and debug print service:
 *    \snippet qs_dbg_print_basic.c  init_calls
 * -# Create an instance of the debug printing task:
 *    \snippet qs_dbg_print_basic.c  main_task_create
 * -# Start the FreeRTOS scheduler:
 *    \snippet qs_dbg_print_basic.c  freertos_start
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
