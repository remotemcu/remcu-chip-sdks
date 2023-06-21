/**
 * \file
 *
 * \brief SAM Digital-to-Analog Interrupt Driver
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
#ifndef DAC_CALLBACK_H_INCLUDED
#define DAC_CALLBACK_H_INCLUDED

#include <compiler.h>
#include "dac.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup asfdoc_sam0_dac_group
 *
 * @{
 */

/** \name Callback Configuration and Initialization
 * @{
 */
enum status_code dac_chan_write_buffer_job(
		struct dac_module *const module_inst,
		const enum dac_channel channel,
		uint16_t *buffer,
		uint32_t buffer_size);

enum status_code dac_chan_write_job(
		struct dac_module *const module_inst,
		const enum dac_channel channel,
		uint16_t data);

enum status_code dac_register_callback(
		struct dac_module *const module,
		const enum dac_channel channel,
		const dac_callback_t callback,
		const enum dac_callback type);

enum status_code dac_unregister_callback(
		struct dac_module *const module,
		const enum dac_channel channel,
		const enum dac_callback type);

/** @} */

/** \name Callback Enabling and Disabling (Channel)
 * @{
 */

enum status_code dac_chan_enable_callback(
		struct dac_module *const module,
		const enum dac_channel channel,
		const enum dac_callback type);

enum status_code dac_chan_disable_callback(
		struct dac_module *const module,
		const enum dac_channel channel,
		const enum dac_callback type);

enum status_code dac_chan_get_job_status(
		struct dac_module *module_inst,
		const enum dac_channel channel);

void dac_chan_abort_job(
		struct dac_module *module_inst,
		const enum dac_channel channel);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif
