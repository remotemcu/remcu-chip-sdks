/**
 * \file
 *
 * \brief SAM Configurable Custom Logic (CCL) Driver
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

#include "ccl.h"

void ccl_init(struct ccl_config *const config)
{
#if (SAML22) || (SAMC20) || (SAMC21)
	/* Turn on the digital interface clock. */
	system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBC, MCLK_APBCMASK_CCL);
#else
	/* Turn on the digital interface clock. */
	system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBD, MCLK_APBDMASK_CCL);
#endif
	/* Reset module. */
	ccl_module_reset();

	/* Configure GCLK channel and enable clock */
	struct system_gclk_chan_config gclk_chan_conf;
	system_gclk_chan_get_config_defaults(&gclk_chan_conf);
	gclk_chan_conf.source_generator = config->clock_source;
	system_gclk_chan_set_config(CCL_GCLK_ID, &gclk_chan_conf);
	system_gclk_chan_enable(CCL_GCLK_ID);

	if(config->run_in_standby) {
		/* Enable run in standy mode. */
		CCL->CTRL.reg |= CCL_CTRL_RUNSTDBY;
	} else {
		/* Disable run in standy mode. */
		CCL->CTRL.reg &= ~ CCL_CTRL_RUNSTDBY;
	}
}

void ccl_lut_get_config_defaults(struct ccl_lut_config *const config)
{
	/* Sanity check arguments */
	Assert(config);

	/* Default configuration values */
	config->truth_table_value = 0x00;
	config->event_output_enable = false;
	config->event_input_enable = false;
	config->event_input_inverted_enable = false;
	config->input0_src_sel = CCL_LUT_INPUT_SRC_MASK;
	config->input1_src_sel = CCL_LUT_INPUT_SRC_MASK;
	config->input2_src_sel = CCL_LUT_INPUT_SRC_MASK;
	config->edge_selection_enable = false;
	config->filter_sel = CCL_LUT_FILTER_DISABLE;
}

enum status_code ccl_lut_set_config(const enum ccl_lut_id number,
		struct ccl_lut_config *const config)
{
	/* Sanity check arguments */
	Assert(config);

	uint32_t temp = 0;

	if(CCL->CTRL.reg & CCL_CTRL_ENABLE)
		return STATUS_BUSY;

	if (config->event_output_enable) {
		temp |= CCL_LUTCTRL_LUTEO;
	}

	if (config->event_input_enable) {
		temp |= CCL_LUTCTRL_LUTEI;
	}

	if (config->event_input_inverted_enable) {
		temp |= CCL_LUTCTRL_INVEI;
	}

	if (config->edge_selection_enable) {
		temp |= CCL_LUTCTRL_EDGESEL;
	}

	CCL->LUTCTRL[number].reg = temp |
		CCL_LUTCTRL_INSEL0(config->input0_src_sel) |
		CCL_LUTCTRL_INSEL1(config->input1_src_sel) |
		CCL_LUTCTRL_INSEL2(config->input2_src_sel) |
		CCL_LUTCTRL_TRUTH(config->truth_table_value) |
		config->filter_sel;

	return STATUS_OK;
}

enum status_code ccl_seq_config(const enum ccl_seq_id number,
		const enum ccl_seq_selection seq_selection)
{
	if(CCL->CTRL.reg & CCL_CTRL_ENABLE)
		return STATUS_BUSY;

	CCL->SEQCTRL[number].reg = seq_selection;

	return STATUS_OK;
}

void ccl_lut_enable(const enum ccl_lut_id number)
{
	/* Enable the LUTx */
	CCL->LUTCTRL[number].reg |= CCL_LUTCTRL_ENABLE;
}

void ccl_lut_disable(const enum ccl_lut_id number)
{
	/* Disable the LUTx */
	CCL->LUTCTRL[number].reg &= ~CCL_LUTCTRL_ENABLE;
}


