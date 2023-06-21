/**
 * \file
 *
 * \brief AT30TSE75X Temperature Sensor driver Quick Start
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

/**
 * \page asfdoc_sam0_at30tse75x_qs Quick Start Guide for the SAM AT30TSE75X Temperature Sensor Driver
 * In this use case we will interface the temperature sensor, set a resolution and read
 * the temperature.
 *
 * \section asfdoc_sam0_at30tse75x_qs_prereq Prerequisites
 * The temperature sensor must be connected to the device.
 *
 * \section asfdoc_sam0_at30tse75x_qs_setup Setup
 *
 * \subsection asfdoc_sam0_at30tse75x_qs_init_code Initialization Code
 * Add a global variable to store the temperature:
 * \snippet qs_at30tse75x.c temp_res
 * Copy-paste the following setup code to your application main function:
 * \snippet qs_at30tse75x.c init
 *
 * \subsection asfdoc_sam0_at30tse75x_qs_workflow Workflow
 * -# Initialize system
 *  \snippet qs_at30tse75x.c system_init
 * -# Initialize I2C interface
 *  \snippet qs_at30tse75x.c temp_init
 *
 * \section asfdoc_sam0_at30tse75x_qs_implement Implementation
 *
 * \subsection asfdoc_sam0_at30tse75x_qs_imp_code Code
 * Add after initialization in main.
 * \snippet qs_at30tse75x.c impl
 *
 * \subsection asfdoc_sam0_at30tse75x_qs_imp_workflow Workflow
 * -# Read THIGH register from temperature sensor:
 *  \snippet qs_at30tse75x.c read_thigh
 * -# Read TLOW register from temperature sensor:
 *  \snippet qs_at30tse75x.c read_tlow
 * -# Set temperature sensor resolution to 12-bit:
 *  \snippet qs_at30tse75x.c write_conf
 * -# Continuously read the temperature:
 *  \snippet qs_at30tse75x.c read_temp
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
