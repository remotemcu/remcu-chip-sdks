/**
 * \file
 *
 * \brief SAM4L Analog Comparator Interfacer (ACIFC) example.
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

#ifndef ACIFC_EXAMPLE_H_INCLUDED
#define ACIFC_EXAMPLE_H_INCLUDED

/**
 * \page asfdoc_sam_drivers_acifc_example Analog Comparator Interface Controller - Example Using Comparison Interrupt
 *
 * \section asfdoc_sam_drivers_acifc_example_purpose Purpose
 *
 * This example demonstrates how to use the ACIFC module and its interrupt to get
 * a comparison result from a pair of inputs.
 *
 * \section asfdoc_sam_drivers_acifc_example_requirements Requirements
 *
 * This example has been tested on the following evaluation kits:
 * - SAM4L EK
 * - SAM4L Xplained Pro
 * - SAM4L8 Xplained Pro
 *
 * \section asfdoc_sam_drivers_acifc_example_description Description
 *
 * This example demonstrates usage of the ACIFC module. The device pins PA06
 * and PA07 are selected as inputs. The connection can be as follows:
 *
 * <b>For SAM4L EK</b>
 *
 * - PA06(J100.2) -- ADC SENSOR VBAT(J105.1)
 * - PA07(J4.4) -- VCC(J4.10)
 *
 * Or
 *
 * - PA06(J100.2) -- ADC SENSOR VBAT(J105.1)
 * - PA07(J4.4) -- GND(J4.9)
 *
 * <b>For SAM4L/SAM4L8 Xplained Pro:</b>
 * - PA06(EXT3/PIN9) -- GND(EXT3/PIN19)
 * - PA07(EXT2/PIN3) -- VCC(EXT2/PIN20)
 *
 * Or
 *
 * - PA06(EXT3/PIN9) -- VCC(EXT3/PIN20)
 * - PA07(EXT2/PIN3) -- GND(EXT2/PIN19)

 *
 * \section asfdoc_sam_drivers_acifc_example_files Main Files
 * - acifc.c: Analog Comparator Interface Controller driver
 * - acifc.h: Analog Comparator Interface Controller driver header file
 * - acifc_example.c: Analog Comparator Interface Controller example application
 *
 * \section asfdoc_sam_drivers_acigc_example_compilinfo Compilation Information
 * This software is written for GNU GCC and IAR Embedded Workbench&reg;
 * for Atmel&reg;. Other compilers may or may not work.
 *
 * \section asfdoc_sam_drivers_acifc_example_usage Usage
 *
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
 * \code
 * -- ACIFC IRQ Example xxx --
 * -- xxxxxx-xx
 * -- Compiled: xxx xx xxxx xx:xx:xx -- \endcode
 * -# The application will output a different message if the voltage on pin.
 * PA06 is lower or higher than the voltage on pin PA07 :
 * \code -ISR- Voltage Comparison Result: ACAP0 > ACAN0 \endcode
 *   or
 * \code -ISR- Voltage Comparison Result: ACAP0 < ACAN0 \endcode
 */
 
#endif /* ACIFC_EXAMPLE_H_INCLUDED */
