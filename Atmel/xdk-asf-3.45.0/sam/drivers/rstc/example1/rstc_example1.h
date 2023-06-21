/**
 * \file
 *
 * \brief SAM Reset Controller (RSTC) Driver Example
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

 #ifndef RSTC_EXAMPLE1_H_INCLUDED
 #define RSTC_EXAMPLE1_H_INCLUDED
 
/**
 * \page asfdoc_sam_drivers_rstc_example1 Reset Controller (RSTC) Example
 *
 * \section asfdoc_sam_drivers_rstc_example1_purpose Purpose
 *
 * This basic example shows how to use the Reset Controller (RSTC) peripheral
 * available on SAM devices. The RSTC handles all the resets of the system,
 * reports which reset occurred last and also drives independently or
 * simultaneously the external reset and the peripheral and processor
 * resets.
 *
 *
 * \section asfdoc_sam_drivers_rstc_example1_requirements Requirements
 *
 * - This example can be used with SAM evaluation kits
 * - Optional: An oscilloscope connected to the evaluation kit's NRST signal
 *
 *
 * \section asfdoc_sam_drivers_rstc_example1_description Description
 *
 * Upon startup, the program displays the reset controller status
 * and a menu to perform the following:
 *     \code
 *     Menu:
 *       0 - Reset Status information.
 *       1 - User Reset enable.
 *       2 - User Reset disable.
 *       3 - User Reset interrupt enable.
 *       4 - User Reset interrupt disable.
 *       5 - Software Reset.
 *       6 - Watchdog Reset.
 *       7 - NRST assert. \endcode
 *
 * The menu can be used to initiate several types of reset and to enable/disable
 * the User Reset interrupt.
 *
 *
 * \section asfdoc_sam_drivers_rstc_example1_files Main Files
 *
 * - rstc.c: Reset Controller driver
 * - rstc.h: Reset Controller driver header file
 * - rstc_example1.c: Reset Controller example application
 *
 *
 * \section asfdoc_sam_drivers_astc_example1_compilinfo Compilation Information
 *
 * This software is written for GNU GCC and IAR Embedded Workbench&reg;
 * for Atmel&reg;. Other compilers may or may not work.
 *
 *
 * \section asfdoc_sam_drivers_rstc_example1_usage Usage
 *
 * -# Build the program and download it into the evaluation board.
 * -# On the computer, open and configure a terminal application
 *    (e.g., HyperTerminal on Microsoft&reg; Windows&reg;) with these settings:
 *   - 115200 baud
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *    \code
 *     -- RSTC Reset Controller Example --
 *     -- xxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *
 *     Reset info : General Reset, NRST=1, User Reset=0
 *
 *     Menu:
 *       0 - Reset Status information.
 *       1 - User Reset enable.
 *       2 - User Reset disable.
 *       3 - User Reset interrupt enable.
 *       4 - User Reset interrupt disable.
 *       5 - Software Reset.
 *       6 - Watchdog Reset.
 *       7 - NRST assert. \endcode
 * -# Press one of the keys listed in the menu to perform the corresponding
 * action.
 *    - Press '1': The following message is displayed:
 * \verbatim User Reset enabled - Press evaluation kit RESET button to test. \endverbatim
 * If the evaluation kit's reset button is pressed the last reset source will be displayed
 * and the menu shown again.
 *    - Press '2': The following message is displayed:
 * \verbatim User Reset enabled - Press evaluation kit RESET button to test. \endverbatim
 * If the evaluation kit's reset button is pressed it will have no effect on the system.
 *    - Press '3': The following message is displayed:
 * \verbatim User Reset interrupt enabled.. \endverbatim
 * If the evaluation kit's reset button is pressed the following message will be displayed.
 * \verbatim User Reset IRQ triggered. Press any console key for the menu \endverbatim
 *    - Press '4': The following message is displayed:
 * \verbatim User Reset interrupt disabled. \endverbatim
 * If the evaluation kit's reset button is pressed it will have no effect on the system.
 *    - Press '5': The following message is displayed:
 * \verbatim Software Reset activated. \endverbatim
 * The evaluation kit will perform a software reset, the last reset source will be
 * displayed and the menu shown again.
 *    - Press '6': The following message is displayed:
 * \verbatim Watchdog Reset will trigger in 3 seconds. \endverbatim
 * The evaluation kit will perform a watchdog reset, the last reset source will be
 * displayed and the menu shown again.
 *    - Press '7': The following message is displayed:
 * \verbatim NRST asserted. \endverbatim
 * The evaluation kit will assert the NRST signal for 60µs.
 * \note The "NRST assert" menu option requires an oscilloscope connected to the
 * evaluation kit's NRST signal. To avoid a hardware conflict during the test do not
 * use the evaluation kit's manual RESET button.
 *
 */
 
 #endif /* RSTC_EXAMPLE1_H_INCLUDED */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
