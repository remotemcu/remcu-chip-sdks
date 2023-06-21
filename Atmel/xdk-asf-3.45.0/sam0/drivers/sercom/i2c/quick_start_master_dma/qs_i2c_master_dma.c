/**
 * \file
 *
 * \brief SAM SERCOM I2C Master with DMA Quick Start Guide
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

//! [packet_data]
#define DATA_LENGTH 10
static uint8_t buffer[DATA_LENGTH] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
};

#define SLAVE_ADDRESS 0x12
//! [packet_data]

/* Number of times to try to send packet if failed. */
//! [timeout]
#define TIMEOUT 1000
//! [timeout]

/* Init software module. */
//! [dev_i2c_inst]
struct i2c_master_module i2c_master_instance;
//! [dev_i2c_inst]

//! [initialize_i2c]
static void configure_i2c_master(void)
{
	/* Initialize config structure and software module. */
	//! [init_conf]
	struct i2c_master_config config_i2c_master;
	i2c_master_get_config_defaults(&config_i2c_master);
	//! [init_conf]

	/* Change buffer timeout to something longer. */
	//! [conf_change]
	config_i2c_master.buffer_timeout = 10000;
#if SAMR30
config_i2c_master.pinmux_pad0    = CONF_MASTER_SDA_PINMUX;
config_i2c_master.pinmux_pad1    = CONF_MASTER_SCK_PINMUX;
#endif
	//! [conf_change]

	/* Initialize and enable device with config. */
	//! [init_module]
	i2c_master_init(&i2c_master_instance, CONF_I2C_MASTER_MODULE, &config_i2c_master);
	//! [init_module]

	//! [enable_module]
	i2c_master_enable(&i2c_master_instance);
	//! [enable_module]
}
//! [initialize_i2c]

//! [dma_resource]
struct dma_resource example_resource;
//! [dma_resource]

//! [transfer_done_flag]
static volatile bool transfer_is_done = false;
//! [transfer_done_flag]

//! [transfer_descriptor]
COMPILER_ALIGNED(16)
DmacDescriptor example_descriptor SECTION_DMAC_DESCRIPTOR;
//! [transfer_descriptor]

//! [transfer_done]
static void transfer_done(struct dma_resource* const resource )
{
	UNUSED(resource);

	transfer_is_done = true;
}
//! [transfer_done]

//! [config_dma_resource]
static void configure_dma_resource(struct dma_resource *resource)
{
	//! [dma_setup_1]
	struct dma_resource_config config;
	//! [dma_setup_1]

	//! [dma_setup_2]
	dma_get_config_defaults(&config);
	//! [dma_setup_2]

	//! [dma_setup_3]
	config.peripheral_trigger = CONF_I2C_DMA_TRIGGER;
	config.trigger_action = DMA_TRIGGER_ACTION_BEAT;
	//! [dma_setup_3]

	//! [dma_setup_4]
	dma_allocate(resource, &config);
	//! [dma_setup_4]
}
//! [config_dma_resource]

//! [setup_dma_transfer_descriptor]
static void setup_dma_descriptor(DmacDescriptor *descriptor)
{
	//! [dma_setup_5]
	struct dma_descriptor_config descriptor_config;
	//! [dma_setup_5]

	//! [dma_setup_6]
	dma_descriptor_get_config_defaults(&descriptor_config);
	//! [dma_setup_6]

	//! [dma_setup_7]
	descriptor_config.beat_size = DMA_BEAT_SIZE_BYTE;
	descriptor_config.dst_increment_enable = false;
	descriptor_config.block_transfer_count = DATA_LENGTH;
	descriptor_config.source_address = (uint32_t)buffer + DATA_LENGTH;
	descriptor_config.destination_address =
			(uint32_t)(&i2c_master_instance.hw->I2CM.DATA.reg);
	//! [dma_setup_7]

	//! [dma_setup_8]
	dma_descriptor_create(descriptor, &descriptor_config);
	//! [dma_setup_8]
}
//! [setup_dma_transfer_descriptor]

int main(void)
{
	system_init();

	//! [init]
	//! [config_i2c]
	configure_i2c_master();
	//! [config_i2c]

	//! [config_dma]
	configure_dma_resource(&example_resource);
	setup_dma_descriptor(&example_descriptor);
	dma_add_descriptor(&example_resource, &example_descriptor);
	dma_register_callback(&example_resource, transfer_done,
			DMA_CALLBACK_TRANSFER_DONE);
	dma_enable_callback(&example_resource, DMA_CALLBACK_TRANSFER_DONE);
	//! [config_dma]
	//! [init]

	//! [main]
	//! [start_transfer_job]
	dma_start_transfer_job(&example_resource);
	//! [start_transfer_job]

	//! [set_i2c_addr]
	i2c_master_dma_set_transfer(&i2c_master_instance, SLAVE_ADDRESS,
			DATA_LENGTH, I2C_TRANSFER_WRITE);
	//! [set_i2c_addr]

	//! [waiting_for_complete]
	while (!transfer_is_done) {
		/* Wait for transfer done */
	}
	//! [waiting_for_complete]

	//! [inf_loop]
	while (true) {
	}
	//! [inf_loop]
	//! [main]
}
