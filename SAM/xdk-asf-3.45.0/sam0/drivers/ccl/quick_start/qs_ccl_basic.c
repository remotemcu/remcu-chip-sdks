/**
 * \file
 *
 * \brief SAM CCL Driver Quick Start
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
#include <asf.h>

void configure_ccl(void);
void configure_ccl_lut0(void);
void configure_ccl_lut1(void);

//! [setup]
void configure_ccl(void)
{
	/** Creates a new configuration structure for the CCL. */
	//! [setup_1]
	struct ccl_config conf;
	//! [setup_1]

	/** Settings and fill with the default settings. */
	//! [setup_2]
	ccl_get_config_defaults(&conf);
	//! [setup_2]

	/** Initialize the CCL with the user settings. */
	//! [setup_3]
	ccl_init(&conf);
	//! [setup_3]
}

void configure_ccl_lut0(void)
{
	/** Creates a new configuration structure for the LUT0. */
	//! [setup_4]
	struct ccl_lut_config conf;
	//! [setup_4]

	/** Settings and fill with the default settings. */
	//! [setup_5]
	ccl_lut_get_config_defaults(&conf);
	//! [setup_5]

	/** Set the LUT0. */
	//! [setup_6]
	conf.truth_table_value = 0x02;
	conf.input0_src_sel = CCL_LUT_INPUT_SRC_IO;
	conf.input1_src_sel = CCL_LUT_INPUT_SRC_IO;
	conf.input2_src_sel = CCL_LUT_INPUT_SRC_IO;
	conf.filter_sel = CCL_LUTCTRL_FILTSEL_FILTER;
	//! [setup_6]

	/** Set up LUT0 input and output pin. */
	//! [setup_7]
	struct system_pinmux_config lut0_input_pin0_conf, lut0_input_pin1_conf, lut0_input_pin2_conf;
	system_pinmux_get_config_defaults(&lut0_input_pin0_conf);
	system_pinmux_get_config_defaults(&lut0_input_pin1_conf);
	system_pinmux_get_config_defaults(&lut0_input_pin2_conf);
	lut0_input_pin0_conf.direction    = SYSTEM_PINMUX_PIN_DIR_INPUT;
	lut0_input_pin0_conf.mux_position = CCL_LUT0_IN0_MUX;
	lut0_input_pin1_conf.direction    = SYSTEM_PINMUX_PIN_DIR_INPUT;
	lut0_input_pin1_conf.mux_position = CCL_LUT0_IN1_MUX;
	lut0_input_pin2_conf.direction    = SYSTEM_PINMUX_PIN_DIR_INPUT;
	lut0_input_pin2_conf.mux_position = CCL_LUT0_IN2_MUX;
	system_pinmux_pin_set_config(CCL_LUT0_IN0_PIN, &lut0_input_pin0_conf);
	system_pinmux_pin_set_config(CCL_LUT0_IN1_PIN, &lut0_input_pin1_conf);
	system_pinmux_pin_set_config(CCL_LUT0_IN2_PIN, &lut0_input_pin2_conf);
	struct system_pinmux_config lut0_out_pin_conf;
	system_pinmux_get_config_defaults(&lut0_out_pin_conf);
	lut0_out_pin_conf.direction    = SYSTEM_PINMUX_PIN_DIR_OUTPUT;
	lut0_out_pin_conf.mux_position = CCL_LUT0_OUT_MUX;
	system_pinmux_pin_set_config(CCL_LUT0_OUT_PIN, &lut0_out_pin_conf);
	//! [setup_7]

	/** Initialize and enable the LUT0 with the user settings. */
	//! [setup_8]
	ccl_lut_set_config(CCL_LUT_0, &conf);
	//! [setup_8]
}

void configure_ccl_lut1(void)
{
	/** Creates a new configuration structure for the LUT1. */
	//! [setup_9]
	struct ccl_lut_config conf;
	//! [setup_9]

	/** Settings and fill with the default settings. */
	//! [setup_10]
	ccl_lut_get_config_defaults(&conf);
	//! [setup_10]

	/** Set the LUT1. */
	//! [setup_11]
	conf.truth_table_value = 0x02;
	conf.input0_src_sel = CCL_LUT_INPUT_SRC_IO;
	conf.input1_src_sel = CCL_LUT_INPUT_SRC_IO;
	conf.input2_src_sel = CCL_LUT_INPUT_SRC_IO;
	conf.filter_sel = CCL_LUTCTRL_FILTSEL_FILTER;
	//! [setup_11]

	/** Set up LUT1 input and output pin. */
	//! [setup_12]
	struct system_pinmux_config lut1_input_pin0_conf, lut1_input_pin1_conf, lut1_input_pin2_conf;
	system_pinmux_get_config_defaults(&lut1_input_pin0_conf);
	system_pinmux_get_config_defaults(&lut1_input_pin1_conf);
	system_pinmux_get_config_defaults(&lut1_input_pin2_conf);
	lut1_input_pin0_conf.direction    = SYSTEM_PINMUX_PIN_DIR_INPUT;
	lut1_input_pin0_conf.mux_position = CCL_LUT1_IN0_MUX;
	lut1_input_pin1_conf.direction    = SYSTEM_PINMUX_PIN_DIR_INPUT;
	lut1_input_pin1_conf.mux_position = CCL_LUT1_IN1_MUX;
	lut1_input_pin2_conf.direction    = SYSTEM_PINMUX_PIN_DIR_INPUT;
	lut1_input_pin2_conf.mux_position = CCL_LUT1_IN2_MUX;
	system_pinmux_pin_set_config(CCL_LUT1_IN0_PIN, &lut1_input_pin0_conf);
	system_pinmux_pin_set_config(CCL_LUT1_IN1_PIN, &lut1_input_pin1_conf);
	system_pinmux_pin_set_config(CCL_LUT1_IN2_MUX, &lut1_input_pin2_conf);
	struct system_pinmux_config lut1_out_pin_conf;
	system_pinmux_get_config_defaults(&lut1_out_pin_conf);
	lut1_out_pin_conf.direction    = SYSTEM_PINMUX_PIN_DIR_OUTPUT;
	lut1_out_pin_conf.mux_position = CCL_LUT1_OUT_MUX;
	system_pinmux_pin_set_config(CCL_LUT1_OUT_PIN, &lut1_out_pin_conf);
	//! [setup_12]

	/** Initialize and enable the LUT1 with the user settings. */
	//! [setup_13]
	ccl_lut_set_config(CCL_LUT_1, &conf);
	//! [setup_13]
}
//! [setup]

int main(void)
{
	system_init();

	//! [setup_init]
	configure_ccl();
	configure_ccl_lut0();
	configure_ccl_lut1();
	/** Configure the sequential logic with the D flip flop mode. */
	//! [setup_14]
	ccl_seq_config(CCL_SEQ_0, CCL_SEQ_D_FLIP_FLOP);
	//! [setup_14]
	//! [setup_init]

	//! [setup_enable]
	/** Enable CCL module. */
	ccl_lut_enable(CCL_LUT_0);
	ccl_lut_enable(CCL_LUT_1);
	ccl_module_enable();
	//! [setup_enable]

	//! [main]
	while (true) {
		/* Do nothing */
	}
	//! [main]
}
