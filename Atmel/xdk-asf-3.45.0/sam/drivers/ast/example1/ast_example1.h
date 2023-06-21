/**
 * \file
 *
 * \brief SAM Asynchronous Timer (AST) Example 1 Calendar Mode
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef AST_EXAMPLE1_H_INCLUDED
#define AST_EXAMPLE1_H_INCLUDED
 
/**
 * \page asfdoc_sam_drivers_ast_example1 Asynchronous Timer (AST) -  Example 1 Calendar Mode
 *
 * \section asfdoc_sam_drivers_ast_example1_purpose Purpose
 * This example demonstrates how to use the AST driver with the 32kHz
 * oscillator crystal.
 *
 * \section asfdoc_sam_drivers_ast_example1_requirements Requirements
 * This example can be used with SAM4L evaluation kits.
 *
 * \section asfdoc_sam_drivers_ast_example1_description Description
 * Upon startup, the program uses the USART driver to display a real time
 * counter incremented every second.
 * The display is triggered by the interrupt controller module.
 *
 * \section asfdoc_sam_drivers_ast_example1_files Main Files
 * - ast.c: Asynchronous Timer driver
 * - ast.h: Asynchronous Timer driver header file
 * - ast_example1.c: Asynchronous Timer example application
 *
 * \section asfdoc_sam_drivers_ast_example1_compilinfo Compilation Information
 * This software is written for GNU GCC and IAR Embedded Workbench&reg;
 * for Atmel&reg;. Other compilers may or may not work.
 *
 * \section asfdoc_sam_drivers_ast_example1_configinfo Usage
 * -# Build the program and download it into the evaluation board.
 * -# On the computer, open, and configure a terminal application
 *    (e.g., HyperTerminal on Microsoft&reg; Windows&reg;) with these settings:
 *   - 115200 baud
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *     \code
 *     -- AST Example 1 in Calendar Mode --
 *     -- xxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *
 *     Config AST with 32 KHz oscillator.
 *
 *     Calendar: Year:XX Month:XX Day:XX, XXhXXmXXs \endcode
 * -# Approximately every second the time should increment.
 *
 */

#endif /* AST_EXAMPLE1_H_INCLUDED */
