/**
 * \file
 *
 * \brief SAM4L PARC driver.
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

#include <parc.h>
#include <sysclk.h>

/**
 * \brief Initialize the PARC module.
 *
 * Initialize the PARC driver structure and the hardware module based on the
 * given configuration structure's contents.
 *
 * \param[in,out] module_inst Pointer to the PARC driver structure
 * \param[in]  hw             Pointer to the PARC module hardware register structure
 * \param[in]  config         Pointer to the PARC configuration structure
 *
 * \return The initialization status.
 * \retval STATUS_OK The initialization was successful
 */
enum status_code parc_init(
	struct parc_module *const module_inst,
	Parc *const hw,
	struct parc_config *const config)
{
	/* Turn on the clock for PARC*/
	sysclk_enable_peripheral_clock(hw);

	/* Associate the software module instance with the hardware module */
	module_inst->hw = hw;

#if PARC_CALLBACK_MODE == true
	for (uint8_t i = 0; i < PARC_CALLBACK_N; i++) {
		module_inst->callback[i] = NULL;
	}

	module_inst->registered_callback_mask = 0;
	module_inst->enabled_callback_mask = 0;

	parc_module_instance = module_inst;
#endif
	return parc_set_config(module_inst, config);
}

/**
 * \brief Configure the PARC module.
 *
 * Configure the PARC module from the supplied configuration structure.
 *
 * \param[in] module_inst Pointer to the PARC driver structure
 * \param[in] config      Pointer to the PARC configuration structure
 *
 * \return The configuration status.
 * \retval STATUS_OK The configuration was successful
 */
enum status_code parc_set_config(
	struct parc_module *const module_inst,
	struct parc_config *config)
{
	Assert(module_inst);
	Assert(module_inst->hw);
	uint32_t tmp_cfg = 0;

	Parc *const parc_module_hw = module_inst->hw;

	tmp_cfg |= PARC_CFG_SMODE(config->smode);
	tmp_cfg |= PARC_CFG_DSIZE(config->dsize);

	if (config->capture_mode == PARC_BOTH_CAPTURE) {
		tmp_cfg &= ~(PARC_CFG_HALF);
	} else if (config->capture_mode == PARC_ODD_CAPTURE) {
		tmp_cfg |= (PARC_CFG_HALF | PARC_CFG_ODD);
	} else if (config->capture_mode == PARC_EVEN_CAPTURE) {
		tmp_cfg |= PARC_CFG_HALF;
		tmp_cfg &= ~(PARC_CFG_ODD);
	}

	if (config->sampling_edge == PARC_FALLING_EDGE) {
		tmp_cfg |= PARC_CFG_EDGE;
	} else if (config->sampling_edge == PARC_RISING_EDGE) {
		tmp_cfg &= ~(PARC_CFG_EDGE);
	}

	parc_module_hw->PARC_CFG = tmp_cfg;

	return STATUS_OK;
}
