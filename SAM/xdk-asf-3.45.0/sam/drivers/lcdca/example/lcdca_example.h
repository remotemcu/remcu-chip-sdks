/**
 * \file
 *
 * \brief SAM4L LCDCA example.
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

#ifndef LCDCA_EXAMPLE_H_INCLUDED
#define LCDCA_EXAMPLE_H_INCLUDED

/**
 * \page asfdoc_sam_drivers_lcdca_example Liquid Crystal Controller - Example Interfacing to a C42048A Display
 *
 * \section asfdoc_sam_drivers_lcdca_example_intro Purpose
 * This example demonstrates how to use the LCDCA driver to interface to an external
 * LCD (C42048A).
 *
 *
 * \section asfdoc_sam_drivers_lcdca_example_requirements Requirements
 * This example can be used with the SAM4L EK evaluation kit.
 *
 *
 * \section asfdoc_sam_drivers_lcdca_example_description Description
 *
 * The example configures the LCDCA Controller in a mode defined by the LCD
 * glass board connections, and the technical characteristics of the LCD
 * component used. It uses the following LCDCA controller features:
 *  - LCD contrast control
 *  - Hardware blinking
 *  - Autonomous segment animation
 *  - Automated character (sequential and scrolling)
 *  - ASCII digit encoder
 *  - LCD beginning of frame interrupt
 *
 * The LCDCA is set up to use the external 32.768kHz clock to generate LCD frames at
 * 64Hz, using a low power waveform to reduce toggle activity, and hence power
 * consumption. In order to show the LCD Controller's capability of running in
 * a power-saving mode, sleep mode is entered whenever possible.
 *
 *
 * \section asfdoc_sam_drivers_lcdca_example_files Main Files
 *  - lcdca.c: Liquid Crystal Display Controller driver
 *  - lcdca.h: Liquid Crystal Display Controller driver header file
 *  - lcdca_example.c: Liquid Crystal Display Controller example application
 *  - conf_example.h: Liquid Crystal Display Controller example configuration header file
 *
 *
 * \section asfdoc_sam_drivers_lcdca_example_compilinfo Compilation Information
 * This software is written for GNU GCC and IAR Embedded Workbench&reg;
 * for Atmel&reg;. Other compilers may or may not work.
 *
 *
 * \section asfdoc_sam_drivers_lcdca_example_usage Usage
 * -# Build the program, and download it onto the evaluation board.
 * -# On the computer, open, and configure a terminal application
 *    (e.g., HyperTerminal on Microsoft&reg; Windows&reg;) with these settings:
 *   - 115200 baud
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 * \verbatim
   -- LCDCA Controller Example --
   -- xxxxxx-xx
   -- Compiled: xxx xx xxxx xx:xx:xx --

   Press PB0 to stop automated sequential mode and continue. \endverbatim
 */

#endif /* LCDCA_EXAMPLE_H_INCLUDED */
