/**
 * \file
 *
 * \brief Glue Logic driver for SAM.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "gloc.h"
#include "sysclk.h"
#include "sleepmgr.h"
#include "conf_gloc.h"

/**
 * \brief Initialize the GLOC module.
 *
 * \param dev_inst Device structure pointer.
 * \param gloc     Base address of the GLOC instance.
 */
void gloc_init(struct gloc_dev_inst *const dev_inst, Gloc *const gloc)
{
	/* Sanity check arguments */
	Assert(dev_inst);
	Assert(gloc);

	dev_inst->hw_dev = gloc;
}

/**
 * \brief Enable the GLOC module.
 *
 * \param dev_inst Device structure pointer.
 *
 */
void gloc_enable(struct gloc_dev_inst *const dev_inst)
{
	struct genclk_config gencfg;

	sysclk_enable_peripheral_clock(dev_inst->hw_dev);
	sleepmgr_lock_mode(SLEEPMGR_SLEEP_0);
	genclk_config_defaults(&gencfg, GLOC_GCLK_NUM);
	genclk_enable_source(CONFIG_GLOC_GENCLK_SRC);
	genclk_config_set_source(&gencfg, CONFIG_GLOC_GENCLK_SRC);
	genclk_config_set_divider(&gencfg, CONFIG_GLOC_GENCLK_DIV);
	genclk_enable(&gencfg, GLOC_GCLK_NUM);
}

/**
 * \brief Disable the GLOC module.
 *
 * \param dev_inst Device structure pointer.
 *
 */
void gloc_disable(struct gloc_dev_inst *const dev_inst)
{
	sysclk_disable_peripheral_clock(dev_inst->hw_dev);
	sleepmgr_unlock_mode(SLEEPMGR_SLEEP_0);
}

/**
 * \brief Get the default configuration for lookup table (LUT) unit of GLOC.
 *
 * The default configuration is as follows:
 * - Filter: enable
 * - Input mask: 0xF, all four inputs are enabled
 * - Truth table value: 0x00
 *
 * \param config Pointer to GLOC LUT configuration.
 */
void gloc_lut_get_config_defaults(struct gloc_lut_config *const config)
{
	/* Sanity check arguments */
	Assert(config);

	config->filter = true;
	config->input_mask = 0xF;
	config->truth_table_value = 0x00;
}

/**
 * \brief Configure the lookup table (LUT) unit of GLOC.
 *
 * \param dev_inst Device structure pointer.
 * \param lut_id   LUT ID.
 * \param config Pointer to GLOC LUT configuration.
 */
void gloc_lut_set_config(struct gloc_dev_inst *const dev_inst,
		uint32_t lut_id, struct gloc_lut_config *const config)
{
	if (config->filter) {
		dev_inst->hw_dev->GLOC_LUT[lut_id].GLOC_CR = GLOC_CR_FILTEN |
			GLOC_CR_AEN(config->input_mask);
	} else {
		dev_inst->hw_dev->GLOC_LUT[lut_id].GLOC_CR =
			GLOC_CR_AEN(config->input_mask);
	}
	dev_inst->hw_dev->GLOC_LUT[lut_id].GLOC_TRUTH = config->truth_table_value;
}
