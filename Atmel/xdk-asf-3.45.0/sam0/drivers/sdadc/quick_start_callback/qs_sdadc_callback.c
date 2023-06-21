/**
 * \file
 *
 * \brief SAM SDADC Quick Start
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

void configure_sdadc(void);
void configure_sdadc_callbacks(void);
void sdadc_complete_callback(
		const struct sdadc_module *const module);

//! [result_buffer]
#define SDADC_SAMPLES 128
int32_t sdadc_result_buffer[SDADC_SAMPLES];
//! [result_buffer]

//! [module_inst]
struct sdadc_module sdadc_instance;
//! [module_inst]

//! [job_complete_callback]
volatile bool sdadc_read_done = false;

void sdadc_complete_callback(
		const struct sdadc_module *const module)
{
	sdadc_read_done = true;
}
//! [job_complete_callback]

//! [setup]
void configure_sdadc(void)
{
//! [setup_config]
	struct sdadc_config config_sdadc;
//! [setup_config]
//! [setup_config_defaults]
	sdadc_get_config_defaults(&config_sdadc);
//! [setup_config_defaults]

//! [setup_modify_conf]
	config_sdadc.clock_prescaler = 2;
	config_sdadc.reference.ref_sel = SDADC_REFERENCE_INTREF;
	config_sdadc.osr             = SDADC_OVER_SAMPLING_RATIO1024;
	config_sdadc.mux_input       = SDADC_MUX_INPUT_AIN2;
//! [setup_modify_conf]

//! [setup_set_config]
	sdadc_init(&sdadc_instance, SDADC, &config_sdadc);
//! [setup_set_config]

//! [setup_enable]
	sdadc_enable(&sdadc_instance);
//! [setup_enable]
}

void configure_sdadc_callbacks(void)
{
//! [setup_register_callback]
	sdadc_register_callback(&sdadc_instance,
			sdadc_complete_callback, SDADC_CALLBACK_READ_BUFFER);
//! [setup_register_callback]
//! [setup_enable_callback]
	sdadc_enable_callback(&sdadc_instance, SDADC_CALLBACK_READ_BUFFER);
//! [setup_enable_callback]
}
//! [setup]

int main(void)
{
	system_init();

//! [setup_init]
	configure_sdadc();
	configure_sdadc_callbacks();
//! [setup_init]

//! [main]
//! [enable_global_interrupts]
	system_interrupt_enable_global();
//! [enable_global_interrupts]

//! [start_sdadc_job]
	sdadc_read_buffer_job(&sdadc_instance, sdadc_result_buffer, SDADC_SAMPLES);
//! [start_sdadc_job]

//! [job_complete_poll]
	while (sdadc_read_done == false) {
		/* Wait for asynchronous SDADC read to complete */
	}
//! [job_complete_poll]

//! [inf_loop]
	while (1) {
		/* Infinite loop */
	}
//! [inf_loop]
//! [main]
}
