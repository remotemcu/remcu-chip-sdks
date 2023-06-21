/**
 *
 * \file
 *
 * \brief SAM AES Driver Quick Start
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

/** \page asfdoc_sam0_aes_callback_use_case Quick Start Guide for AES - Callback
 *
 * The supported board list:
 *    - SAM L21 Xplained Pro
 *    - SAM L22 Xplained Pro
 *
 * This example demonstrates how to use the AES driver to perform:
 * - ECB encryption and decryption
 * - CBC encryption and decryption
 * - CFB128 encryption and decryption
 * - OFB encryption and decryption
 * - CTR encryption and decryption
 *
 * Upon startup, the program uses the USART driver to display application
 * output message from which several encryption/decryption modes can be tested.
 *
 * \section asfdoc_sam0_aes_callback_use_case_setup Quick Start Callback
 *
 * \subsection asfdoc_sam0_aes_callback_use_case_prereq Prerequisites
 * There are no prerequisites for this use case.
 *
 * \subsection asfdoc_sam0_aes_callback_use_case_setup_code Code
 *
 * Add to the main application source file, outside of any functions:
 * \snippet quick_start_callback.c cipher_data
 *
 * Add to the main application source file, outside of any functions:
 * \snippet quick_start_callback.c module_var

 * Copy-paste the following setup code to your user application:
 * \snippet quick_start_callback.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet quick_start_callback.c setup_init
 *
 * \subsection asfdoc_sam0_aes_callback_use_case_setup_flow Workflow
 * -# Define sample data from NIST-800-38A appendix F for ECB mode.
 *    \snippet quick_start_callback.c cipher_data
 *
 * -# Create related module variable and software instance structure.
 *    \snippet quick_start_callback.c module_var
 *
 * -# Configure, initialize, and enable AES module.
 *  -# Configuration AES struct, which can be filled out to
 *     adjust the configuration of a physical AES peripheral.
 *     \snippet quick_start_callback.c setup_config
 *  -# Initialize the AES configuration struct with the module's default values.
 *     \snippet quick_start_callback.c setup_config_defaults
 *  -# Enable the AES module.
 *     \snippet quick_start_callback.c module_enable
 *  -# Register and enable the AES module callback.
 *     \snippet quick_start_callback.c module_enable_register
 *

 *
 * \section asfdoc_sam0_aes_callback_use_case_main Use Case
 *
 * \subsection asfdoc_sam0_aes_callback_use_case_main_code Code
 * Copy-paste the following code to your user application:
 * \snippet quick_start_callback.c  encryption_decryption
 *
 * \subsection asfdoc_sam0_aes_callback_use_case_main_flow Workflow
 * -# Configure ECB mode encryption and decryption and run test.
 *    \snippet quick_start_callback.c ECB_MODE
 * -# Configure CBC mode encryption and decryption and run test.
 *    \snippet quick_start_callback.c CBC_MODE
 * -# Configure CFB mode encryption and decryption and run test.
 *    \snippet quick_start_callback.c CFB_MODE
 * -# Configure OFB mode encryption and decryption and run test.
 *    \snippet quick_start_callback.c OFB_MODE
 * -# Configure CTR mode encryption and decryption and run test.
 *    \snippet quick_start_callback.c CTR_MODE
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
