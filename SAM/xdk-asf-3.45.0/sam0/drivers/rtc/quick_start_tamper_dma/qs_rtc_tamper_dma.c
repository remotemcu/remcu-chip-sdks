/**
 * \file
 *
 * \brief SAM RTC Tamper DMA Quick Start
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

void configure_dma_resource(struct dma_resource *resource);
void setup_transfer_descriptor(DmacDescriptor *descriptor);

void rtc_tamper_callback(void);
void configure_rtc(void);
void configure_rtc_callbacks(void);

//! [rtc_module_instance]
struct rtc_module rtc_instance;
//! [rtc_module_instance]

//! [dma_resource]
struct dma_resource example_resource;
//! [dma_resource]

// [transfer_descriptor]
COMPILER_ALIGNED(16)
DmacDescriptor example_descriptor SECTION_DMAC_DESCRIPTOR;
// [transfer_descriptor]

static uint32_t buffer_rtc_tamper;

//! [callback]
void rtc_tamper_callback(void)
{
	//! [Tamper_act]
	/* Do something on RTC tamper capture here */
	LED_On(LED_0_PIN);
	//! [Tamper_act]
}
//! [callback]

//! [initialize_rtc]
void configure_rtc(void)
{
//! [init_rtc]
	struct rtc_count_config config_rtc_count;
	rtc_count_get_config_defaults(&config_rtc_count);
	config_rtc_count.prescaler = RTC_COUNT_PRESCALER_DIV_1;
	rtc_count_init(&rtc_instance, RTC, &config_rtc_count);
//! [init_rtc]

//! [set_tamper_config]
	struct rtc_tamper_config config_rtc_tamper;
	rtc_tamper_get_config_defaults(&config_rtc_tamper);
	config_rtc_tamper.dma_tamper_enable = true;
	config_rtc_tamper.in_cfg[0].level = RTC_TAMPER_LEVEL_RISING;
	config_rtc_tamper.in_cfg[0].action = RTC_TAMPER_INPUT_ACTION_CAPTURE;
	rtc_tamper_set_config(&rtc_instance, &config_rtc_tamper);
//! [set_tamper_config]

//! [enable]
	rtc_count_enable(&rtc_instance);
//! [enable]
}
//! [initialize_rtc]

//! [setup_callback]
void configure_rtc_callbacks(void)
{
	//! [reg_callback]
	rtc_count_register_callback(
			&rtc_instance, rtc_tamper_callback, RTC_COUNT_CALLBACK_TAMPER);
	//! [reg_callback]
	//! [en_callback]
	rtc_count_enable_callback(&rtc_instance, RTC_COUNT_CALLBACK_TAMPER);
	//! [en_callback]
}
//! [setup_callback]

//! [config_dma_resource]
void configure_dma_resource(struct dma_resource *resource)
{
//! [setup_dma_config]
	struct dma_resource_config config;
//! [setup_dma_config]

//! [setup_dma_set_config_default]
	dma_get_config_defaults(&config);
//! [setup_dma_set_config_default]

//! [setup_dma_set_config_extra]
	config.peripheral_trigger = RTC_DMAC_ID_TIMESTAMP;
	config.trigger_action = DMA_TRIGGER_ACTION_BEAT;
//! [setup_dma_set_config_extra]

//! [allocate_dma_resource]
	dma_allocate(resource, &config);
//! [allocate_dma_resource]
}
//! [config_dma_resource]

//! [setup_dma_transfer_descriptor]
void setup_transfer_descriptor(DmacDescriptor *descriptor)
{
//! [setup_dma_desc_config]
	struct dma_descriptor_config descriptor_config;
//! [setup_dma_desc_config]

//! [setup_dma_desc_config_set_default]
	dma_descriptor_get_config_defaults(&descriptor_config);
//! [setup_dma_desc_config_set_default]

//! [setup_dma_desc_config_set_extra]
	descriptor_config.beat_size = DMA_BEAT_SIZE_WORD;
	descriptor_config.dst_increment_enable = false;
	descriptor_config.src_increment_enable = false;
	descriptor_config.block_transfer_count = 1;
	descriptor_config.source_address = (uint32_t)(&rtc_instance.hw->MODE0.TIMESTAMP.reg);
	descriptor_config.destination_address = (uint32_t)(buffer_rtc_tamper);
	descriptor_config.next_descriptor_address = (uint32_t)descriptor;
//! [setup_dma_desc_config_set_extra]

//! [setup_dma_desc_config_create]
	dma_descriptor_create(descriptor, &descriptor_config);
//! [setup_dma_desc_config_create]
}
//! [setup_dma_transfer_descriptor]
//! [setup]

int main(void)
{
//! [main]
	/* Initialize system. Must configure conf_clocks.h first. */
//! [system_init]
	system_init();
//! [system_init]

	/* Configure and enable RTC */
//! [run_conf]
	configure_rtc();
//! [run_conf]

	/* Configure and enable callback */
//! [run_callback]
	configure_rtc_callbacks();
//! [run_callback]

//! [setup_dma_resource]
	configure_dma_resource(&example_resource);
//! [setup_dma_resource]

//! [setup_transfer_descriptor]
	setup_transfer_descriptor(&example_descriptor);
//! [setup_transfer_descriptor]

//! [add_descriptor_to_resource]
	dma_add_descriptor(&example_resource, &example_descriptor);
//! [add_descriptor_to_resource]

//! [while]
	while (true) {
		/* Infinite while loop */
	}
//! [while]
//! [main]
}
