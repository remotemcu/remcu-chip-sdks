/**
 * \file
 *
 * \brief SAM ADC Quick Start
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
#include <asf.h>

void configure_adc(void);
void configure_adc_callbacks(void);
void adc_complete_callback(
		struct adc_module *const module);

//! [result_buffer]
#define ADC_SAMPLES 128
uint16_t adc_result_buffer[ADC_SAMPLES];
//! [result_buffer]

//! [module_inst]
struct adc_module adc_instance;
//! [module_inst]

//! [job_complete_callback]
volatile bool adc_read_done = false;

void adc_complete_callback(
		struct adc_module *const module)
{
	adc_read_done = true;
}
//! [job_complete_callback]

//! [setup]
void configure_adc(void)
{
//! [setup_config]
	struct adc_config config_adc;
//! [setup_config]
//! [setup_config_defaults]
	adc_get_config_defaults(&config_adc);
//! [setup_config_defaults]

//! [setup_modify_conf]
#if (!SAML21) && (!SAML22) && (!SAMC21) && (!SAMR30)
	config_adc.gain_factor     = ADC_GAIN_FACTOR_DIV2;
#endif
	config_adc.clock_prescaler = ADC_CLOCK_PRESCALER_DIV8;
	config_adc.reference       = ADC_REFERENCE_INTVCC1;
#if (SAMC21)
	config_adc.positive_input  = ADC_POSITIVE_INPUT_PIN5;
#else
	config_adc.positive_input  = ADC_POSITIVE_INPUT_PIN6;
#endif
	config_adc.resolution      = ADC_RESOLUTION_12BIT;
//! [setup_modify_conf]

//! [setup_set_config]
#if (SAMC21)
	adc_init(&adc_instance, ADC1, &config_adc);
#else
	adc_init(&adc_instance, ADC, &config_adc);
#endif
//! [setup_set_config]

//! [setup_enable]
	adc_enable(&adc_instance);
//! [setup_enable]
}

void configure_adc_callbacks(void)
{
//! [setup_register_callback]
	adc_register_callback(&adc_instance,
			adc_complete_callback, ADC_CALLBACK_READ_BUFFER);
//! [setup_register_callback]
//! [setup_enable_callback]
	adc_enable_callback(&adc_instance, ADC_CALLBACK_READ_BUFFER);
//! [setup_enable_callback]
}
//! [setup]

int main(void)
{
	system_init();

//! [setup_init]
	configure_adc();
	configure_adc_callbacks();
//! [setup_init]

//! [main]
//! [enable_global_interrupts]
	system_interrupt_enable_global();
//! [enable_global_interrupts]

//! [start_adc_job]
	adc_read_buffer_job(&adc_instance, adc_result_buffer, ADC_SAMPLES);
//! [start_adc_job]

//! [job_complete_poll]
	while (adc_read_done == false) {
		/* Wait for asynchronous ADC read to complete */
	}
//! [job_complete_poll]

//! [inf_loop]
	while (1) {
		/* Infinite loop */
	}
//! [inf_loop]
//! [main]
}
