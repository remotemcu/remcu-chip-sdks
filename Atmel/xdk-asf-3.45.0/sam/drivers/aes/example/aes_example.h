/**
 *
 * \file
 *
 * \brief AES example for SAM.
 *
 * This file defines a useful set of functions for the AES on SAM devices.
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

 #ifndef AES_EXAMPLE_H_INCLUDED
 #define AES_EXAMPLE_H_INCLUDED
 
/** \page asfdoc_sam_drivers_aes_example1 Advanced Encryption Standard - Example Cipher Operating Modes and DMA
 *
 * \section asfdoc_sam_drivers_aes_example1_purpose Purpose
 *
 * This example demonstrates how to use the AES driver to perform:
 * - ECB encryption and decryption
 * - CBC encryption and decryption
 * - CFB encryption and decryption
 * - OFB encryption and decryption
 * - CTR encryption and decryption
 * - ECB encryption and decryption using DMA/PDC
 *
 *
 * \section asfdoc_sam_drivers_aes_example1_requirements Requirements
 * All SAM devices with an AES module can be used. This example has been
 * tested with the following evaluation kits:
 * - SAM4E EK
 * - SAM4C EK
 *
 * \section asfdoc_sam_drivers_aes_example1_description Description
 * Upon startup, the program uses the USART driver to display a menu
 * from which several encryption/decryption modes can be tested.
 *
 *
 * \section asfdoc_sam_drivers_aes_example1_files Main Files
 * - aes.c : AES driver
 * - aes.h : AES header file
 * - aes_example.c : AES code example
 *
 *
 * \section asfdoc_sam_drivers_aes_example1_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR Systems compiler.
 * Other compilers may or may not work.
 *
 *
 * \section asfdoc_sam_drivers_aes_example1_setupinfo Usage
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
 * \verbatim
       -- AES Example --
       -- xxxxxx-xx
       -- Compiled: xxx xx xxxx xx:xx:xx --

       Menu :
         -- Select operation:
         h: Display menu
         1: ECB mode test.
         2: CBC mode test.
         3: CFB128 mode test.
         4: OFB mode test.
         5: CTR mode test.
         d: ECB mode test with DMA
         p: ECB mode test with PDC \endverbatim
 */

#endif /* AES_EXAMPLE_H_INCLUDED */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
