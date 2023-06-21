/**
 * \file
 *
 * \brief SAM Timer/Counter Driver for Control Applications DMA Quickstart
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
#include <conf_quick_start_dma.h>

static void configure_tcc(void);

//! [module_inst]
struct tcc_module tcc_instance;
//! [module_inst]

//! [compare_variables]
uint16_t compare_values[3] = {
	(0x1000 / 4), (0x1000 * 2 / 4), (0x1000 * 3 / 4)
};
//! [compare_dma_resource]
struct dma_resource compare_dma_resource;
//! [compare_dma_resource]
//! [compare_dma_descriptor]
COMPILER_ALIGNED(16) DmacDescriptor compare_dma_descriptor SECTION_DMAC_DESCRIPTOR;
//! [compare_dma_descriptor]
//! [compare_variables]

//! [capture_variables]
uint16_t capture_values[3] = {0, 0, 0};
//! [capture_dma_resource]
struct dma_resource capture_dma_resource;
//! [capture_dma_resource]
//! [capture_dma_descriptor]
COMPILER_ALIGNED(16) DmacDescriptor capture_dma_descriptor SECTION_DMAC_DESCRIPTOR;
//! [capture_dma_descriptor]
//! [capture_event_resource]
struct events_resource capture_event_resource;
//! [capture_event_resource]
//! [capture_variables]

//! [config_event_for_capture]
static void config_event_for_capture(void)
{
	//! [event_setup_1]
	struct events_config config;
	//! [event_setup_1]

	//! [event_setup_2]
	events_get_config_defaults(&config);
	//! [event_setup_2]

	//! [event_setup_3]
	config.generator      = CONF_TCC_EVENT_GENERATOR;
	config.edge_detect    = EVENTS_EDGE_DETECT_RISING;
	config.path           = EVENTS_PATH_SYNCHRONOUS;
	config.clock_source   = GCLK_GENERATOR_0;
	//! [event_setup_3]

	//! [event_setup_4]
	events_allocate(&capture_event_resource, &config);
	//! [event_setup_4]

	//! [event_setup_5]
	events_attach_user(&capture_event_resource, CONF_TCC_EVENT_USER);
	//! [event_setup_5]
}
//! [config_event_for_capture]

//! [config_dma_for_capture]
static void config_dma_for_capture(void)
{
	//! [config_dma_resource_for_capture]
	//! [dma_setup_1]
	struct dma_resource_config config;
	//! [dma_setup_1]

	//! [dma_setup_2]
	dma_get_config_defaults(&config);
	//! [dma_setup_2]

	//! [dma_setup_3]
	config.trigger_action = DMA_TRIGGER_ACTION_BEAT;
	config.peripheral_trigger = CONF_CAPTURE_TRIGGER;
	//! [dma_setup_3]

	//! [dma_setup_4]
	dma_allocate(&capture_dma_resource, &config);
	//! [dma_setup_4]
	//! [config_dma_resource_for_capture]

	//! [config_dma_descriptor_for_capture]
	//! [dma_setup_5]
	struct dma_descriptor_config descriptor_config;
	//! [dma_setup_5]

	//! [dma_setup_6]
	dma_descriptor_get_config_defaults(&descriptor_config);
	//! [dma_setup_6]

	//! [dma_setup_7]
	descriptor_config.block_transfer_count = 3;
	descriptor_config.beat_size = DMA_BEAT_SIZE_HWORD;
	descriptor_config.step_selection = DMA_STEPSEL_SRC;
	descriptor_config.src_increment_enable = false;
	descriptor_config.source_address =
			(uint32_t)&CONF_PWM_MODULE->CC[CONF_TCC_CAPTURE_CHANNEL];
	descriptor_config.destination_address =
			(uint32_t)capture_values + sizeof(capture_values);
	//! [dma_setup_7]

	//! [dma_setup_8]
	dma_descriptor_create(&capture_dma_descriptor, &descriptor_config);
	//! [dma_setup_8]
	//! [config_dma_descriptor_for_capture]

	//! [config_dma_job_for_capture]
	//! [dma_setup_10]
	dma_add_descriptor(&capture_dma_resource, &capture_dma_descriptor);
	dma_add_descriptor(&capture_dma_resource, &capture_dma_descriptor);
	//! [dma_setup_10]
	//! [dma_setup_11]
	dma_start_transfer_job(&capture_dma_resource);
	//! [dma_setup_11]
	//! [config_dma_job_for_capture]
}
//! [config_dma_for_capture]

//! [config_dma_for_wave]
static void config_dma_for_wave(void)
{
	//! [config_dma_resource_for_wave]
	struct dma_resource_config config;
	dma_get_config_defaults(&config);
	config.trigger_action = DMA_TRIGGER_ACTION_BEAT;
	config.peripheral_trigger = CONF_COMPARE_TRIGGER;
	dma_allocate(&compare_dma_resource, &config);
	//! [config_dma_resource_for_wave]

	//! [config_dma_descriptor_for_wave]
	struct dma_descriptor_config descriptor_config;

	dma_descriptor_get_config_defaults(&descriptor_config);

	descriptor_config.block_transfer_count = 3;
	descriptor_config.beat_size = DMA_BEAT_SIZE_HWORD;
	descriptor_config.dst_increment_enable = false;
	descriptor_config.source_address =
			(uint32_t)compare_values + sizeof(compare_values);
#if (SAMR21) || (SAMD21) || (SAMDA1) || (SAMHA1)
	descriptor_config.destination_address =
			(uint32_t)&CONF_PWM_MODULE->CC[CONF_PWM_CHANNEL];
#else
	descriptor_config.destination_address =
			(uint32_t)&CONF_PWM_MODULE->CCBUF[CONF_PWM_CHANNEL];
#endif

	dma_descriptor_create(&compare_dma_descriptor, &descriptor_config);
	//! [config_dma_descriptor_for_wave]

	//! [config_dma_job_for_wave]
	dma_add_descriptor(&compare_dma_resource, &compare_dma_descriptor);
	dma_add_descriptor(&compare_dma_resource, &compare_dma_descriptor);
	dma_start_transfer_job(&compare_dma_resource);
	//! [config_dma_job_for_wave]
}
//! [config_dma_for_wave]

//! [setup]
static void configure_tcc(void)
{
	//! [setup_config]
	struct tcc_config config_tcc;
	//! [setup_config]
	//! [setup_config_defaults]
	tcc_get_config_defaults(&config_tcc, CONF_PWM_MODULE);
	//! [setup_config_defaults]

	//! [setup_change_config]
	config_tcc.counter.clock_prescaler = TCC_CLOCK_PRESCALER_DIV1024;
	config_tcc.counter.period = 0x1000;
	config_tcc.compare.channel_function[CONF_TCC_CAPTURE_CHANNEL] =
			TCC_CHANNEL_FUNCTION_CAPTURE;
	config_tcc.compare.wave_generation = TCC_WAVE_GENERATION_SINGLE_SLOPE_PWM;
	config_tcc.compare.wave_polarity[CONF_PWM_CHANNEL] = TCC_WAVE_POLARITY_0;
	config_tcc.compare.match[CONF_PWM_CHANNEL] = compare_values[2];
	//! [setup_change_config]

	//! [setup_change_config_pwm]
	config_tcc.pins.enable_wave_out_pin[CONF_PWM_OUTPUT] = true;
	config_tcc.pins.wave_out_pin[CONF_PWM_OUTPUT]        = CONF_PWM_OUT_PIN;
	config_tcc.pins.wave_out_pin_mux[CONF_PWM_OUTPUT]    = CONF_PWM_OUT_MUX;
	//! [setup_change_config_pwm]

	//! [setup_set_config]
	tcc_init(&tcc_instance, CONF_PWM_MODULE, &config_tcc);
	//! [setup_set_config]

	//! [setup_events]
	struct tcc_events events_tcc = {
		.input_config[0].modify_action = false,
		.input_config[1].modify_action = false,
		.output_config.modify_generation_selection = false,
		.generate_event_on_channel[CONF_PWM_CHANNEL] = true,
		.on_event_perform_channel_action[CONF_TCC_CAPTURE_CHANNEL] = true
	};
	tcc_enable_events(&tcc_instance, &events_tcc);
	//! [setup_events]

	//! [setup_event_sys]
	config_event_for_capture();
	//! [setup_event_sys]

	//! [setup_dma]
	config_dma_for_capture();
	config_dma_for_wave();
	//! [setup_dma]

	//! [setup_enable]
	tcc_enable(&tcc_instance);
	//! [setup_enable]
}
//! [setup]

int main(void)
{
	system_init();

	//! [setup_init]
	configure_tcc();
	//! [setup_init]

//! [main]
	//! [main_loop]
	while (true) {
		/* Infinite loop */
	}
	//! [main_loop]
//! [main]
}
