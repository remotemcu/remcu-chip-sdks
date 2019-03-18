/**
 * \file
 *
 * \brief Analog Comparator Controller (ACC) example for SAM.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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

 #ifndef ACC_EXAMPLE_H_INCLUDED
 #define ACC_EXAMPLE_H_INCLUDED
 
/**
 * \page asfdoc_sam_drivers_acc_example_irq Analog Comparator Controller - Example Interrupt Event Generation
 *
 * \section asfdoc_sam_drivers_acc_example_irq_purpose Purpose
 *
 * This example demonstrates how to use the ACC driver to perform a voltage
 * comparison on a pair of inputs and generate an interrupt.
 *
 * \section asfdoc_sam_drivers_acc_example_irq_requirements Requirements
 *
 * This example can be used on the following evaluation kits:
 * - SAM4S EK
 * - SAM4S EK2
 *
 * \section asfdoc_sam_drivers_acc_example_irq_description Description
 *
 * The DAC0 and AD5 signals are selected as the inputs to the analog comparator.
 * The user can change the output voltage of DAC0 and also change the voltage
 * on AD5 by adjusting VR1 on the evaluation kit.
 *
 * The DAC0 output voltage can be adjusted between (1/6)*ADVREF and (5/6)*ADVREF
 * in software, whilst the input voltage on AD5 can vary between 0 and ADVREF.
 *
 * A comparison interrupt event is generated when the input voltages are
 * no longer equal.
 *
 * \section asfdoc_sam_drivers_acc_example_irq_files Main Files
 * - acc.c: Analog Comparator Controller driver
 * - acc.h: Analog Comparator Controller driver header file
 * - acc_example.c: Analog Comparator Controller example application
 *
 * \section asfdoc_sam_drivers_acc_example_irq_compilinfo Compilation Information
 * This software is written for GNU GCC and IAR Embedded Workbench&reg;
 * for Atmel&reg;. Other compilers may or may not work.

 * \section asfdoc_sam_drivers_acc_example_irq_usage Usage
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
 * \verbatim
   -- ACC IRQ Example xxx --
   -- xxxxxx-xx
   -- Compiled: xxx xx xxxx xx:xx:xx --

   -- Menu Choices for this example--
   -- s: Set new DAC0 output voltage.--
   -- v: Get voltage on potentiometer.--
   -- m: Display this menu again.-- \endverbatim
 * -# Enter a character on the terminal to select a menu option.
 * -# Change the voltage on AD5 by adjusting VR1 on the evaluation kit in order.
 * To see what comparison events occur.
 */

#endif /* ACC_EXAMPLE_H_INCLUDED */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
