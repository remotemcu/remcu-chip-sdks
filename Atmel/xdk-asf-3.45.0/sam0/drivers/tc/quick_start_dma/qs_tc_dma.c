/**
 * \file
 *
 * \brief SAM Timer/Counter Driver with DMA Quickstart
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
#include <conf_quick_start.h>

void configure_tc(void);
void transfer_done(struct dma_resource* const resource);
void configure_dma_resource(struct dma_resource *resource);
void setup_dma_descriptor(DmacDescriptor *descriptor);

//! [module_inst]
struct tc_module tc_instance;
//! [module_inst]

//! [dma_resource]
struct dma_resource example_resource;
//! [dma_resource]

//! [setup]
//! [transfer_length]
#define TRANSFER_SIZE    (16)
//! [transfer_length]

//! [transfer_counter]
#define TRANSFER_COUNTER (32)
//! [transfer_counter]

//! [source_memory]
static uint8_t source_memory[TRANSFER_SIZE*TRANSFER_COUNTER];
//! [source_memory]

//! [destination_memory]
static uint8_t destination_memory[TRANSFER_SIZE*TRANSFER_COUNTER];
//! [destination_memory]

//! [transfer_done_flag]
static volatile bool transfer_is_done = false;
//! [transfer_done_flag]

//! [example_descriptor]
COMPILER_ALIGNED(16)
DmacDescriptor example_descriptor SECTION_DMAC_DESCRIPTOR;
//! [example_descriptor]

//! [config_tc]
void configure_tc(void)
{
	//! [setup_config]
	struct tc_config config_tc;
	//! [setup_config]
	//! [setup_config_defaults]
	tc_get_config_defaults(&config_tc);
	//! [setup_config_defaults]

	//! [setup_change_config]
	config_tc.counter_size    = TC_COUNTER_SIZE_16BIT;
	config_tc.wave_generation = TC_WAVE_GENERATION_NORMAL_PWM;
	config_tc.counter_16_bit.compare_capture_channel[0] = (0xFFFF / 4);
	//! [setup_change_config]

	//! [setup_change_config_pwm]
	config_tc.pwm_channel[0].enabled = true;
	config_tc.pwm_channel[0].pin_out = PWM_OUT_PIN;
	config_tc.pwm_channel[0].pin_mux = PWM_OUT_MUX;
	//! [setup_change_config_pwm]

	//! [setup_set_config]
	tc_init(&tc_instance, PWM_MODULE, &config_tc);
	//! [setup_set_config]

	//! [setup_enable]
	tc_enable(&tc_instance);
	//! [setup_enable]
}
//! [config_tc]

//! [_transfer_done]
void transfer_done(struct dma_resource* const resource )
{
	UNUSED(resource);

	transfer_is_done = true;
}
//! [_transfer_done]

//! [config_dma_resource]
void configure_dma_resource(struct dma_resource *resource)
{
//! [dma_setup_1]
	struct dma_resource_config config;
//! [dma_setup_1]

//! [dma_setup_2]
	dma_get_config_defaults(&config);
	config.peripheral_trigger = M2M_DMAC_TRIGGER_ID;
//! [dma_setup_2]

//! [dma_setup_3]
	dma_allocate(resource, &config);
//! [dma_setup_3]
}
//! [config_dma_resource]

//! [setup_dma_transfer_descriptor]
void setup_dma_descriptor(DmacDescriptor *descriptor)
{
	//! [dma_setup_4]
	struct dma_descriptor_config descriptor_config;
	//! [dma_setup_4]

	//! [dma_setup_5]
	dma_descriptor_get_config_defaults(&descriptor_config);
	//! [dma_setup_5]

	//! [dma_setup_6]
	descriptor_config.block_transfer_count = TRANSFER_SIZE;
	descriptor_config.source_address = (uint32_t)source_memory + TRANSFER_SIZE;
	descriptor_config.destination_address =
			(uint32_t)destination_memory + TRANSFER_SIZE;
	//! [dma_setup_6]

	//! [dma_setup_7]
	dma_descriptor_create(descriptor, &descriptor_config);
	//! [dma_setup_7]
}
//! [setup_dma_transfer_descriptor]

//! [setup]

int main(void)
{
	uint32_t i=0;

	system_init();

	//! [setup_init]
	configure_tc();
	//! [setup_init]

	//! [setup_dma_resource]
	configure_dma_resource(&example_resource);
	//! [setup_dma_resource]

	//! [setup_dma_descriptor]
	setup_dma_descriptor(&example_descriptor);
	//! [setup_dma_descriptor]

	//! [add_descriptor_to_resource]
	dma_add_descriptor(&example_resource, &example_descriptor);
	//! [add_descriptor_to_resource]

	//! [setup_callback_register]
	dma_register_callback(&example_resource, transfer_done,
			DMA_CALLBACK_TRANSFER_DONE);
	//! [setup_callback_register]

	//! [setup_enable_callback]
	dma_enable_callback(&example_resource, DMA_CALLBACK_TRANSFER_DONE);
	//! [setup_enable_callback]

	//! [setup_source_memory_content]
	for (i = 0; i < TRANSFER_SIZE*TRANSFER_COUNTER; i++) {
		source_memory[i] = i;
	}
	//! [setup_source_memory_content]

	//! [main]
	//! [main_transfer_loop]
	for(i=0;i<TRANSFER_COUNTER;i++) {
		//! [main_1]
		transfer_is_done = false;
		//! [main_1]

		//! [main_2]
		dma_start_transfer_job(&example_resource);
		//! [main_2]

		//! [main_3]
		while (!transfer_is_done) {
			/* Wait for transfer done */
		}
		//! [main_3]

		//! [main_4]
		example_descriptor.SRCADDR.reg += TRANSFER_SIZE;
		example_descriptor.DSTADDR.reg += TRANSFER_SIZE;
		//! [main_4]
	}
	//! [main_transfer_loop]

	//! [endless_loop]
	while(1);
	//! [endless_loop]
	//! [main]
}
