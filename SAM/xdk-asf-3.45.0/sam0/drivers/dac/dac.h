/**
 * \file
 *
 * \brief SAM Peripheral Digital-to-Analog Converter Driver
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
#ifndef DAC_H_INCLUDED
#define DAC_H_INCLUDED


#ifdef __cplusplus
extern "C" {
#endif

#include <compiler.h>
#include <clock.h>
#include <gclk.h>

/**
 * \addtogroup asfdoc_sam0_dac_group
 *
 * @{
 */

/**
 * Define DAC features set according to different device families.
 * @{
 */
#if (SAMD21 || SAMD10 || SAMD11 || SAMDA1 || SAMHA1 || SAMHA0)
#  define FEATURE_DAC_DATABUF_WRITE_PROTECTION
#endif
/**@}*/

#ifndef DAC_TIMEOUT
#  define DAC_TIMEOUT 0xFFFF
#endif

#if DAC_CALLBACK_MODE == true
#  include <system_interrupt.h>

/** Forward definition of the device instance. */
struct dac_module;

#if !defined(__DOXYGEN__)
extern struct dac_module *_dac_instances[DAC_INST_NUM];
#endif

/** Type definition for a DAC module callback function. */
typedef void (*dac_callback_t)(uint8_t channel);

/** Enum for the possible callback types for the DAC module. */
enum dac_callback {
	/** Callback type for when a DAC channel data empty condition occurs
	 *  (requires event triggered mode) */
	DAC_CALLBACK_DATA_EMPTY,

	/** Callback type for when a DAC channel data underrun condition occurs
	 *  (requires event triggered mode) */
	DAC_CALLBACK_DATA_UNDERRUN,

	/** Callback type for when a DAC channel write buffer job complete (requires
	 *  event triggered mode) */
	DAC_CALLBACK_TRANSFER_COMPLETE,
#if !defined(__DOXYGEN__)
	DAC_CALLBACK_N,
#endif
};

#endif

#include <dac_feature.h>

/**
 * \name Configuration and Initialization
 * @{
 */

bool dac_is_syncing(
		struct dac_module *const dev_inst);

void dac_get_config_defaults(
		struct dac_config *const config);

enum status_code dac_init(
		struct dac_module *const dev_inst,
		Dac *const module,
		struct dac_config *const config);

void dac_reset(
		struct dac_module *const dev_inst);

void dac_enable(
		struct dac_module *const dev_inst);

void dac_disable(
		struct dac_module *const dev_inst);

void dac_enable_events(
		struct dac_module *const module_inst,
		struct dac_events *const events);

void dac_disable_events(
		struct dac_module *const module_inst,
		struct dac_events *const events);

/** @} */

/**
 * \name Configuration and Initialization (Channel)
 * @{
 */

void dac_chan_get_config_defaults(
		struct dac_chan_config *const config);

void dac_chan_set_config(
		struct dac_module *const dev_inst,
		const enum dac_channel channel,
		struct dac_chan_config *const config);

void dac_chan_enable(
		struct dac_module *const dev_inst,
		enum dac_channel channel);

void dac_chan_disable(
		struct dac_module *const dev_inst,
		enum dac_channel channel);

/** @} */

/**
 * \name Channel Data Management
 * @{
 */

enum status_code dac_chan_write(
		struct dac_module *const dev_inst,
		enum dac_channel channel,
		const uint16_t data);

enum status_code dac_chan_write_buffer_wait(
		struct dac_module *const module_inst,
		enum dac_channel channel,
		uint16_t *buffer,
		uint32_t length);

/** @} */

/**
 * \name Status Management
 * @{
 */
uint32_t dac_get_status(
		struct dac_module *const module_inst);
void dac_clear_status(
		struct dac_module *const module_inst,
		uint32_t status_flags);

/** @} */

#ifdef __cplusplus
}
#endif

/** @} */


#endif /* DAC_H_INCLUDED */
