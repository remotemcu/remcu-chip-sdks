/**
 * \file
 *
 * \brief SAM Frequency Meter (FREQM) Driver
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

#include "freqm.h"
#include <gclk.h>

#ifndef FREQM_GCLK_ID_REF
#define FREQM_GCLK_ID_REF (FREQM_GCLK_ID_MSR + 1)
#endif

/**
 * \brief Initializes a hardware FREQM module instance.
 *
 * Enables the clock and initializes the FREQM module, based on the given
 * configuration values.
 *
 * \param[in,out] module_inst  Pointer to the software module instance struct
 * \param[in]     hw           Pointer to the FREQM hardware module
 * \param[in]     config       Pointer to the FREQM configuration options struct
 *
 * \return Status of the initialization procedure.
 *
 * \retval STATUS_OK           The module was initialized successfully
 */
enum status_code freqm_init(
		struct freqm_module *const module_inst,
		Freqm *const hw,
		struct freqm_config *const config)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(hw);
	Assert(config);
	Assert(config->ref_clock_circles);

	/* Initialize device instance */
	module_inst->hw = hw;

	/* Turn on the digital interface clock */
	system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBA, MCLK_APBAMASK_FREQM);

	/* Set up the GCLK for the module */
	struct system_gclk_chan_config gclk_chan_conf;
	system_gclk_chan_get_config_defaults(&gclk_chan_conf);
	gclk_chan_conf.source_generator = config->msr_clock_source;
	system_gclk_chan_set_config(FREQM_GCLK_ID_MSR, &gclk_chan_conf);
	system_gclk_chan_enable(FREQM_GCLK_ID_MSR);

	gclk_chan_conf.source_generator = config->ref_clock_source;
	system_gclk_chan_set_config(FREQM_GCLK_ID_REF, &gclk_chan_conf);
	system_gclk_chan_enable(FREQM_GCLK_ID_REF);
	
	module_inst->ref_clock_freq = system_gclk_gen_get_hz(config->ref_clock_source);

	/* Perform a software reset */
	hw->CTRLA.reg = FREQM_CTRLA_SWRST;

	while (freqm_is_syncing()) {
		/* Wait for all hardware modules to complete synchronization */
	}

	/* Initialize the FREQM with new configurations */
	hw->CFGA.reg = config->ref_clock_circles;

#if FREQM_CALLBACK_MODE == true
	/* Initialize parameters */
	for (uint8_t i = 0; i < FREQM_CALLBACK_N; i++) {
		module_inst->callback[i] = NULL;
	}
	/* Register this instance for callbacks*/
	_freqm_instance = module_inst;
#endif

	return STATUS_OK;
}

/**
 * \brief Read the measurement data result
 *
 * Reads the measurement data result.
 *
 * \param[in]  module_inst  Pointer to the FREQM software instance struct
 * \param[out] result       Pointer to store the result value in
 *
 * \return Status of the FREQM read request.
 * \retval FREQM_STATUS_MEASURE_DONE   Measurement result was retrieved successfully
 * \retval FREQM_STATUS_MEASURE_BUSY   Measurement result was not ready
 * \retval FREQM_STATUS_CNT_OVERFLOW   Measurement result was overflow
 *                              
 * \note If overflow occurred, configure faster reference clock or reduce reference clock cycles.
 */
enum freqm_status freqm_get_result_value(
		struct freqm_module *const module_inst, uint32_t *result)
{
	/* Sanity check arguments */
	Assert(module_inst);
	Assert(module_inst->hw);
	Assert(result);

	Freqm *const freqm_hw = module_inst->hw;
	uint32_t result_cal;
	*result = result_cal= 0;

	if (freqm_hw->STATUS.reg & FREQM_STATUS_BUSY) {
		/* Result not ready */
		return FREQM_STATUS_MEASURE_BUSY;
	} else {
		if (freqm_hw->STATUS.reg & FREQM_STATUS_OVF) {
			/* Overflow */
			return FREQM_STATUS_CNT_OVERFLOW;
		} else {
			/* Get measurement output data (it will clear data done flag) */
			result_cal = freqm_hw->VALUE.reg;
			freqm_hw->INTFLAG.reg = FREQM_INTFLAG_DONE;

			*result = result_cal * module_inst->ref_clock_freq / freqm_hw->CFGA.reg;
			return FREQM_STATUS_MEASURE_DONE;
		}
	}
}
