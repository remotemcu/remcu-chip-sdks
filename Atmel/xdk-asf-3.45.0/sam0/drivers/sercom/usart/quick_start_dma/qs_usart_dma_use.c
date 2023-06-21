/**
 * \file
 *
 * \brief SAM Sercom Usart driver with DMA quick start
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

//! [module_inst]
struct usart_module usart_instance;
//! [module_inst]

//! [dma_resource]
struct dma_resource usart_dma_resource_rx;
struct dma_resource usart_dma_resource_tx;
//! [dma_resource]

//! [usart_buffer]
#define BUFFER_LEN    8
static uint16_t string[BUFFER_LEN];
//! [usart_buffer]

//! [transfer_descriptor]
COMPILER_ALIGNED(16)
DmacDescriptor example_descriptor_rx SECTION_DMAC_DESCRIPTOR;
DmacDescriptor example_descriptor_tx SECTION_DMAC_DESCRIPTOR;
//! [transfer_descriptor]

//! [setup]
//! [transfer_done_rx]
static void transfer_done_rx(struct dma_resource* const resource )
{
	dma_start_transfer_job(&usart_dma_resource_tx);
}
//! [transfer_done_rx]

//! [transfer_done_tx]
static void transfer_done_tx(struct dma_resource* const resource )
{
	dma_start_transfer_job(&usart_dma_resource_rx);
}
//! [transfer_done_tx]

//! [config_dma_resource_rx]
static void configure_dma_resource_rx(struct dma_resource *resource)
{
//! [setup_rx_1]
	struct dma_resource_config config;
//! [setup_rx_1]

//! [setup_rx_2]
	dma_get_config_defaults(&config);
//! [setup_rx_2]

//! [setup_rx_3]
#if(SAMR30E)
    config.peripheral_trigger = CDC_SERCOM_DMAC_ID_RX;
#else
	config.peripheral_trigger = EDBG_CDC_SERCOM_DMAC_ID_RX;
#endif
	config.trigger_action = DMA_TRIGGER_ACTION_BEAT;
//! [setup_rx_3]

//! [setup_rx_4]
	dma_allocate(resource, &config);
//! [setup_rx_4]
}
//! [config_dma_resource_rx]

//! [setup_dma_transfer_rx_descriptor]
static void setup_transfer_descriptor_rx(DmacDescriptor *descriptor)
{
//! [setup_rx_5]
	struct dma_descriptor_config descriptor_config;
//! [setup_rx_5]

//! [setup_rx_6]
	dma_descriptor_get_config_defaults(&descriptor_config);
//! [setup_rx_6]

//! [setup_rx_7]
	descriptor_config.beat_size = DMA_BEAT_SIZE_HWORD;
	descriptor_config.src_increment_enable = false;
	descriptor_config.block_transfer_count = BUFFER_LEN;
	descriptor_config.destination_address =
			(uint32_t)string + sizeof(string);
	descriptor_config.source_address =
			(uint32_t)(&usart_instance.hw->USART.DATA.reg);
//! [setup_rx_7]

//! [setup_rx_8]
	dma_descriptor_create(descriptor, &descriptor_config);
//! [setup_rx_8]
}
//! [setup_dma_transfer_rx_descriptor]

//! [config_dma_resource_tx]
static void configure_dma_resource_tx(struct dma_resource *resource)
{
//! [setup_tx_1]
	struct dma_resource_config config;
//! [setup_tx_1]

//! [setup_tx_2]
	dma_get_config_defaults(&config);
//! [setup_tx_2]

//! [setup_tx_3]
#if(SAMR30E)
    config.peripheral_trigger = CDC_SERCOM_DMAC_ID_TX;
#else
	config.peripheral_trigger = EDBG_CDC_SERCOM_DMAC_ID_TX;
#endif
	config.trigger_action = DMA_TRIGGER_ACTION_BEAT;
//! [setup_tx_3]

//! [setup_tx_4]
	dma_allocate(resource, &config);
//! [setup_tx_4]
}
//! [config_dma_resource_tx]

//! [setup_dma_transfer_tx_descriptor]
static void setup_transfer_descriptor_tx(DmacDescriptor *descriptor)
{
//! [setup_tx_5]
	struct dma_descriptor_config descriptor_config;
//! [setup_tx_5]

//! [setup_tx_6]
	dma_descriptor_get_config_defaults(&descriptor_config);
//! [setup_tx_6]

//! [setup_tx_7]
	descriptor_config.beat_size = DMA_BEAT_SIZE_HWORD;
	descriptor_config.dst_increment_enable = false;
	descriptor_config.block_transfer_count = BUFFER_LEN;
	descriptor_config.source_address = (uint32_t)string + sizeof(string);
	descriptor_config.destination_address =
		(uint32_t)(&usart_instance.hw->USART.DATA.reg);
//! [setup_tx_7]

//! [setup_tx_8]
	dma_descriptor_create(descriptor, &descriptor_config);
//! [setup_tx_8]
}
//! [setup_dma_transfer_tx_descriptor]

//! [setup_usart]
static void configure_usart(void)
{
//! [setup_config]
	struct usart_config config_usart;
//! [setup_config]
//! [setup_config_defaults]
	usart_get_config_defaults(&config_usart);
//! [setup_config_defaults]

#if(SAMR30E)
{
	config_usart.baudrate    = 9600;
	config_usart.mux_setting = CDC_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = CDC_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = CDC_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = CDC_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = CDC_SERCOM_PINMUX_PAD3;
	//! [setup_change_config]

	//! [setup_set_config]
	while (usart_init(&usart_instance,
	CDC_MODULE, &config_usart) != STATUS_OK) {
	}
	//! [setup_set_config]
}
#else
{
	config_usart.baudrate    = 9600;
	config_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	//! [setup_change_config]

	//! [setup_set_config]
	while (usart_init(&usart_instance,
	EDBG_CDC_MODULE, &config_usart) != STATUS_OK) {
	}
	//! [setup_set_config]
}
#endif

//! [setup_enable]
	usart_enable(&usart_instance);
//! [setup_enable]
}
//! [setup_usart]
//! [setup]

int main(void)
{
	system_init();

//! [setup_init]
//! [setup_usart]
	configure_usart();
//! [setup_usart]

//! [setup_dma_resource]
	configure_dma_resource_rx(&usart_dma_resource_rx);
	configure_dma_resource_tx(&usart_dma_resource_tx);
//! [setup_dma_resource]

//! [setup_transfer_descriptor]
	setup_transfer_descriptor_rx(&example_descriptor_rx);
	setup_transfer_descriptor_tx(&example_descriptor_tx);
//! [setup_transfer_descriptor]

//! [add_descriptor_to_resource]
	dma_add_descriptor(&usart_dma_resource_rx, &example_descriptor_rx);
	dma_add_descriptor(&usart_dma_resource_tx, &example_descriptor_tx);
//! [add_descriptor_to_resource]

//! [setup_callback_register]
	dma_register_callback(&usart_dma_resource_rx, transfer_done_rx,
			DMA_CALLBACK_TRANSFER_DONE);
	dma_register_callback(&usart_dma_resource_tx, transfer_done_tx,
			DMA_CALLBACK_TRANSFER_DONE);
//! [setup_callback_register]

//! [setup_enable_callback]
	dma_enable_callback(&usart_dma_resource_rx,
			DMA_CALLBACK_TRANSFER_DONE);
	dma_enable_callback(&usart_dma_resource_tx,
			DMA_CALLBACK_TRANSFER_DONE);
//! [setup_enable_callback]
//! [setup_init]

//! [main]
//! [main_1]
	dma_start_transfer_job(&usart_dma_resource_rx);
//! [main_1]

//! [endless_loop]
	while (true) {
	}
//! [endless_loop]
//! [main]
}
