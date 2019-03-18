/**
 * \file
 *
 * \brief SAM QUAD DECODER Driver Quick Start for SAMB11
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
#include <asf.h>

volatile int16_t	qdec_axis_x,
					qdec_axis_y,
					qdec_axis_z;
volatile bool       qdec_x_overflow,
					qdec_y_overflow,
					qdec_z_overflow;
					
//! [callback_funcs]
static void quad_decoder0_callback(void)
{
	qdec_x_overflow = true;
}

static void quad_decoder1_callback(void)
{
	qdec_y_overflow = true;
}

static void quad_decoder2_callback(void)
{
	qdec_z_overflow = true;
}
//! [callback_funcs]

//! [setup]
static void configure_quad_decoder(void)
{
//! [set_conf]
	struct quad_decoder_config config_quad_decoder;
//! [set_conf]
//! [get_def]
	quad_decoder_get_config_defaults(&config_quad_decoder);
//! [get_def]
//! [setup_pinmux]
	config_quad_decoder.qdec0.pin_number_pad[0] = CONF_QUAD_DECODER_PIN_X_A;
	config_quad_decoder.qdec0.pin_number_pad[1] = CONF_QUAD_DECODER_PIN_X_B;
	config_quad_decoder.qdec1.pin_number_pad[0] = CONF_QUAD_DECODER_PIN_Y_A;
	config_quad_decoder.qdec1.pin_number_pad[1] = CONF_QUAD_DECODER_PIN_Y_B;
	config_quad_decoder.qdec2.pin_number_pad[0] = CONF_QUAD_DECODER_PIN_Z_A;
	config_quad_decoder.qdec2.pin_number_pad[1] = CONF_QUAD_DECODER_PIN_Z_B;

	config_quad_decoder.qdec0.pinmux_sel_pad[0] = CONF_QUAD_DECODER_MUX_X_A;
	config_quad_decoder.qdec0.pinmux_sel_pad[1] = CONF_QUAD_DECODER_MUX_X_B;
	config_quad_decoder.qdec1.pinmux_sel_pad[0] = CONF_QUAD_DECODER_MUX_Y_A;
	config_quad_decoder.qdec1.pinmux_sel_pad[1] = CONF_QUAD_DECODER_MUX_Y_B;
	config_quad_decoder.qdec2.pinmux_sel_pad[0] = CONF_QUAD_DECODER_MUX_Z_A;
	config_quad_decoder.qdec2.pinmux_sel_pad[1] = CONF_QUAD_DECODER_MUX_Z_B;
//! [setup_pinmux]
//! [init_qdec]
	quad_decoder_init(&config_quad_decoder);
//! [init_qdec]

}

static void configure_quad_decoder_callback(void)
{
//! [setup_register_callback]
	quad_decoder_register_callback(QDEC_AXIS_X, quad_decoder0_callback);
	quad_decoder_register_callback(QDEC_AXIS_Y, quad_decoder1_callback);
	quad_decoder_register_callback(QDEC_AXIS_Z, quad_decoder2_callback);
//! [setup_register_callback]
//! [enable_IRQ]
	NVIC_EnableIRQ(25);
//! [enable_IRQ]
}

//! [setup]

int main(void)
{
//! [add_main]
//! [sys_clock]
	system_clock_config(CLOCK_RESOURCE_XO_26_MHZ, CLOCK_FREQ_26_MHZ);
//! [sys_clock]
//! [conf_qdec]
	configure_quad_decoder();
//! [conf_qdec]
//! [conf_callback]	
	configure_quad_decoder_callback();
//! [conf_callback]
//! [add_main]

//! [main_imp]
//! [main_loop]
	while (true) {
//! [main_loop]

//! [get_counter]
		/* Get x,y,z axis current counter */
		qdec_axis_x = quad_decoder_get_counter(QDEC_AXIS_X);
		qdec_axis_y = quad_decoder_get_counter(QDEC_AXIS_Y);
		qdec_axis_z = quad_decoder_get_counter(QDEC_AXIS_Z);
//! [get_counter]
	}
//! [main_imp]
}
