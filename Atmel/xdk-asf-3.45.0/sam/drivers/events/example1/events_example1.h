/**
 * \file
 *
 * \brief SAM Peripheral Event Controller (PEVC) example 1.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef EVENTS_EXAMPLE1_H_INCLUDED
#define EVENTS_EXAMPLE1_H_INCLUDED

/**
 * \page asfdoc_sam_events_ex1 Example for the Peripheral Event System - AST/PDCA
 *
 * \section asfdoc_sam_events_ex1_intro Introduction
 * This example shows how to use the Peripheral Event Controller.
 * In the example, the AST generates a periodic event which is transmitted
 * to the PDCA. Each time a new event occurs, a character is sent to the
 * USART without the use of the CPU. The main loop of the function is a
 * delay 500ms and toggle a LED continuously to show CPU activity.
 *
 * \section asfdoc_sam_events_ex1_files Main Files
 * - events.c: Events driver
 * - events.h: Events driver header file
 * - events_example1.c: Events example 1 application
 *
 * \section asfdoc_sam_events_ex1_compilinfo Compilation Information
 * This software is written for GNU GCC and IAR Embedded Workbench&reg;
 * for Atmel&reg;. Other compilers may or may not work.
 *
 * \section asfdoc_sam_events_ex1_deviceinfo Device Information
 * SAM4L device can be used.
 *
 * \section asfdoc_sam_events_ex1_configinfo Configuration Information
 * This example has been tested with the following configuration:
 * - PC terminal settings:
 *   - 115200 baud
 *   - 8 data bits
 *   - no parity bit
 *   - 1 stop bit
 *   - no flow control
 *
 */
 
#endif /* EVENTS_EXAMPLE1_H_INCLUDED */
