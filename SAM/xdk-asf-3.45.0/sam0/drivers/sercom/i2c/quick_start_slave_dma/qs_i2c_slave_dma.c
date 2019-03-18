/**
 * \file
 *
 * \brief SAM SERCOM I2C Slave with DMA Quick Start Guide
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

void configure_i2c_slave(void);
void setup_dma_descriptor(DmacDescriptor *descriptor);
void configure_dma_resource(struct dma_resource *resource);

//! [address]
#define SLAVE_ADDRESS 0x12
//! [address]

//! [packet_data]
#define DATA_LENGTH 10
uint8_t read_buffer[DATA_LENGTH];
//! [packet_data]

//! [module]
struct i2c_slave_module i2c_slave_instance;
//! [module]

//! [initialize_i2c]
void configure_i2c_slave(void)
{
	/* Create and initialize config_i2c_slave structure */
	//! [init_conf]
	struct i2c_slave_config config_i2c_slave;
	i2c_slave_get_config_defaults(&config_i2c_slave);
	//! [init_conf]

	/* Change address and address_mode */
	//! [conf_changes]
	config_i2c_slave.address        = SLAVE_ADDRESS;
	config_i2c_slave.address_mode   = I2C_SLAVE_ADDRESS_MODE_MASK;
	config_i2c_slave.buffer_timeout = 1000;
#if SAMR30
	config_i2c_slave.pinmux_pad0    = CONF_SLAVE_SDA_PINMUX;
	config_i2c_slave.pinmux_pad1    = CONF_SLAVE_SCK_PINMUX;
#endif
	//! [conf_changes]

	/* Initialize and enable device with config_i2c_slave */
	//! [init_module]
	i2c_slave_init(&i2c_slave_instance, CONF_I2C_SLAVE_MODULE, &config_i2c_slave);
	//! [init_module]

	//! [enable_module]
	i2c_slave_enable(&i2c_slave_instance);
	//! [enable_module]
}
//! [initialize_i2c]

//! [dma_resource]
struct dma_resource i2c_dma_resource;
//! [dma_resource]

// [transfer_descriptor]
COMPILER_ALIGNED(16)
DmacDescriptor i2c_dma_descriptor SECTION_DMAC_DESCRIPTOR;
// [transfer_descriptor]

// [config_dma_resource]
void configure_dma_resource(struct dma_resource *resource)
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
// [config_dma_resource]

// [setup_dma_transfer_descriptor]
void setup_dma_descriptor(DmacDescriptor *descriptor)
{
	//! [dma_setup_5]
	struct dma_descriptor_config descriptor_config;
	//! [dma_setup_5]

	//! [dma_setup_6]
	dma_descriptor_get_config_defaults(&descriptor_config);
	//! [dma_setup_6]

	//! [dma_setup_7]
	descriptor_config.beat_size = DMA_BEAT_SIZE_BYTE;
	descriptor_config.src_increment_enable = false;
	descriptor_config.block_transfer_count = DATA_LENGTH;
	descriptor_config.destination_address = (uint32_t)read_buffer + DATA_LENGTH;
	descriptor_config.source_address =
			(uint32_t)(&i2c_slave_instance.hw->I2CS.DATA.reg);
	//! [dma_setup_7]

	//! [dma_setup_8]
	dma_descriptor_create(descriptor, &descriptor_config);
	//! [dma_setup_8]
}
// [setup_dma_transfer_descriptor]

int main(void)
{
	system_init();

	//! [init]
	//! [config_i2c]
	configure_i2c_slave();
	//! [config_i2c]

	//! [config_dma]
	configure_dma_resource(&i2c_dma_resource);
	setup_dma_descriptor(&i2c_dma_descriptor);
	dma_add_descriptor(&i2c_dma_resource, &i2c_dma_descriptor);
	//! [config_dma]
	//! [init]

	//! [main]
	//! [wait_packet]
	dma_start_transfer_job(&i2c_dma_resource);
	//! [wait_packet]

	//! [clear_status]
	while (true) {
		if (i2c_slave_dma_read_interrupt_status(&i2c_slave_instance) &
					SERCOM_I2CS_INTFLAG_AMATCH) {
			i2c_slave_dma_write_interrupt_status(&i2c_slave_instance,
					SERCOM_I2CS_INTFLAG_AMATCH);
		}
	}
	//! [clear_status]
	//! [main]
}
