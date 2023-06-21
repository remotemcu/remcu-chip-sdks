/**
 * \file
 *
 * \brief Glue Logic driver for SAM.
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

#ifndef GLOC_H_INCLUDED
#define GLOC_H_INCLUDED

#include "compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup sam_drivers_gloc_group Glue Logic Controller (GLOC)
 *
 * Driver for the Glue Logic Controller. This driver provides access to the
 * main features of the Glue Logic controller.
 *
 * See \ref sam_gloc_quick_start.
 *
 * @{
 */

/**
 * \brief Glue Logic Controller driver software instance structure.
 *
 * Device instance structure for a Glue Logic Controller driver instance. This
 * structure should be initialized by the \ref gloc_init() function to
 * associate the instance with a particular hardware module of the device.
 */
struct gloc_dev_inst {
	/** Base address of the GLOC module. */
	Gloc *hw_dev;
};

/**
 * \brief GLOC lookup table (LUT) configuration structure.
 *
 * Configuration structure for a GLOC LUT instance. This
 * structure could be initialized by the \ref gloc_lut_get_config_defaults()
 * function before being modified by the user application.
 */
struct gloc_lut_config {
	/** True for enable, false for disable. */
	bool filter;
	/** Input enable mask. */
	uint8_t input_mask;
	/** Truth table value. */
	uint16_t truth_table_value;
};

void gloc_init(struct gloc_dev_inst *const dev_inst, Gloc *const gloc);
void gloc_enable(struct gloc_dev_inst *const dev_inst);
void gloc_disable(struct gloc_dev_inst *const dev_inst);
void gloc_lut_get_config_defaults(struct gloc_lut_config *const config);
void gloc_lut_set_config(struct gloc_dev_inst *const dev_inst,
		uint32_t lut_id, struct gloc_lut_config *const config);

/** @} */

#ifdef __cplusplus
}
#endif

/**
 * \page sam_gloc_quick_start Quick Start Guide for the GLOC driver
 *
 * This is the quick start guide for the \ref sam_drivers_gloc_group, with
 * step-by-step instructions on how to configure and use the driver for
 * a specific use case.The code examples can be copied into e.g the main
 * application loop or any other function that will need to control the
 * GLOC module.
 *
 * \section gloc_qs_use_cases Use cases
 * - \ref gloc_basic "GLOC Basic Usage"
 *
 * \section gloc_basic GLOC Basic Usage
 *
 * This use case will demonstrate how to initialize the GLOC module to
 * match the truth table for simple glue logic functions.
 *
 *
 * \section gloc_basic_setup Setup steps
 *
 * \subsection gloc_basic_prereq Prerequisites
 *
 * This module requires the following service
 * - \ref clk_group "Clock Management (Sysclock)"
 *
 * \subsection gloc_basic_setup_code Code
 *
 * Add this to the main loop or a setup function:
 * \code
	 #define XOR_TRUTH_TABLE_FOUR_INPUT     0x6996u

	 struct gloc_dev_inst dev_inst;
	 struct gloc_lut_config lut_config;

	 gloc_init(&dev_inst, GLOC);
	 gloc_enable(&dev_inst);
	 gloc_lut_get_config_defaults(&lut_config);
	 lut_config.truth_table_value = XOR_TRUTH_TABLE_FOUR_INPUT;
	 gloc_lut_set_config(&dev_inst, 0, &lut_config);
\endcode
 *
 * \subsection gloc_basic_setup_workflow Workflow
 *
 * -# Initialize the GLOC module
 *  - \code gloc_init(&dev_inst, GLOC); \endcode
 * -# Enable the GLOC module
 *  - \code gloc_enable(&dev_inst); \endcode
 * -# Configure 4 inputs XOR truth table value in LUT0
 *    \code
	gloc_lut_get_config_defaults(&lut_config);
	lut_config.truth_table_value = XOR_TRUTH_TABLE_FOUR_INPUT;
	gloc_lut_set_config(&dev_inst, 0, &lut_config);
\endcode
 *
 * \section gloc_basic_usage Usage steps
 *
 * The pin OUT0 will output according to lookup table 0 (LUT0) setting when
 * pin IN0 to IN3 change.
 */

#endif /* GLOC_H_INCLUDED */
