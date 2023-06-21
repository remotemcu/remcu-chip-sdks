/**
 * \file
 *
 * \brief Direct Memory Access Controller(DMAC) Driver Quick Start for SAMB
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
#include <string.h>

//! [setup]
//! [transfer_length]
#define DATA_LENGTH (512)
//! [transfer_length]

//! [source_memory]
static uint8_t source_memory[DATA_LENGTH];
//! [source_memory]

//! [destination_memory]
static uint8_t destination_memory[DATA_LENGTH];
//! [destination_memory]

//! [transfer_done_flag]
static volatile bool transfer_is_done = false;
//! [transfer_done_flag]

//! [transfer_descriptor]
struct dma_descriptor example_descriptor;
//! [transfer_descriptor]

//! [_transfer_done]
static void transfer_done(struct dma_resource* const resource )
{
	transfer_is_done = true;
}
//! [_transfer_done]

//! [config_dma_resource]
static void configure_dma_resource(struct dma_resource *resource)
{
//! [setup_1]
	struct dma_resource_config config;
//! [setup_1]

//! [setup_2]
	dma_get_config_defaults(&config);
//! [setup_2]

//! [setup_3]
	dma_allocate(resource, &config);
//! [setup_3]
}
//! [config_dma_resource]

//! [setup_dma_transfer_descriptor]
static void setup_transfer_descriptor(struct dma_descriptor *descriptor )
{

	//! [setup_5]
	dma_descriptor_get_config_defaults(descriptor);
	//! [setup_5]

	//! [setup_6]
	descriptor->buffer_size = sizeof(source_memory);
	descriptor->read_start_addr = (uint32_t)source_memory;
	descriptor->write_start_addr = (uint32_t)destination_memory;
	//! [setup_6]
}

static void configure_dma_callback(struct dma_resource *resource)
{
	//! [setup_callback_register]
	dma_register_callback(resource, transfer_done,
			DMA_CALLBACK_TRANSFER_DONE);
	//! [setup_callback_register]
	
	//! [setup_enable_callback]
	dma_enable_callback(resource, DMA_CALLBACK_TRANSFER_DONE);
	//! [setup_enable_callback]
	
	//! [enable_IRQ]
	NVIC_EnableIRQ(PROV_DMA_CTRL0_IRQn);
	//! [enable_IRQ]
}

//! [setup]
int main(void)
{
//! [setup_init]
	volatile bool passed;
	//! [sample_resource]
	struct dma_resource example_resource;
	//! [sample_resource]

	system_clock_config(CLOCK_RESOURCE_XO_26_MHZ, CLOCK_FREQ_26_MHZ);

	//! [setup_dma_resource]
	configure_dma_resource(&example_resource);
	//! [setup_dma_resource]

	//! [setup_transfer_descriptor]
	setup_transfer_descriptor(&example_descriptor);
	//! [setup_transfer_descriptor]

	//! [add_descriptor_to_dma_resource]
	dma_add_descriptor(&example_resource, &example_descriptor);
	//! [add_descriptor_to_dma_resource]
	
	//! [setup_callback]
	configure_dma_callback(&example_resource);
	//! [setup_callback]

	//! [setup_source_memory_content]
	for (uint32_t i = 0; i < DATA_LENGTH; i++) {
		source_memory[i] = i;
		destination_memory[i] = 0x0;
	}
	//! [setup_source_memory_content]

	//! [setup_init]
	//! [main]
	//! [main_1]
	dma_start_transfer_job(&example_resource);
	//! [main_1]
	
	//! [main_2]
	transfer_is_done = false;
	while (!transfer_is_done) {
		/* Wait for transfer done */
	}
	//! [main_2]

	//! [main_3]
	passed = false;
	if (!memcmp(source_memory, destination_memory, sizeof(source_memory))) {
		passed = true;
	}
	//! [main_3]
	while (true) {
		/* Nothing to do */
	}
	UNUSED(passed);
	//! [main]
}
