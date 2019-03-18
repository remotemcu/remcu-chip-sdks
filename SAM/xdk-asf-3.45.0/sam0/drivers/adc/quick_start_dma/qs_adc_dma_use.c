/**
 * \file
 *
 * \brief SAM D21/D11/L21/DA1/C21/HA1G16A ADC with DMA quick start
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

void configure_dma_resource(struct dma_resource *resource);
void setup_transfer_descriptor(DmacDescriptor *descriptor);

void configure_adc(void);
void configure_dac(void);
void configure_dac_channel(void);

//! [dac_module_inst]
struct dac_module dac_instance;
//! [dac_module_inst]

//! [adc_module_inst]
struct adc_module adc_instance;
//! [adc_module_inst]

//! [dma_resource]
struct dma_resource example_resource;
//! [dma_resource]

// [transfer_descriptor]
COMPILER_ALIGNED(16)
DmacDescriptor example_descriptor SECTION_DMAC_DESCRIPTOR;
// [transfer_descriptor]

//! [setup]
//! [configure_adc]
void configure_adc(void)
{
//! [setup_adc_config]
	struct adc_config config_adc;
//! [setup_adc_config]

//! [setup_adc_config_defaults]
	adc_get_config_defaults(&config_adc);
//! [setup_adc_config_defaults]

//! [setup_adc_config_extra]
#if !(SAML21)
#if !(SAMC21)
	config_adc.gain_factor     = ADC_GAIN_FACTOR_DIV2;
#endif
	config_adc.resolution      = ADC_RESOLUTION_10BIT;
#endif
	config_adc.clock_prescaler = ADC_CLOCK_PRESCALER_DIV16;
	config_adc.reference       = ADC_REFERENCE_INTVCC1;
	config_adc.positive_input  = ADC_POSITIVE_INPUT_PIN4;
	config_adc.freerunning     = true;
	config_adc.left_adjust     = false;
//! [setup_adc_config_extra]

//! [setup_adc_set_config]
#if (SAMC21)
	adc_init(&adc_instance, ADC1, &config_adc);
#else
	adc_init(&adc_instance, ADC, &config_adc);
#endif
//! [setup_adc_set_config]

//! [setup_adc_enable]
	adc_enable(&adc_instance);
//! [setup_adc_enable]
}
//! [configure_adc]

//! [configure_dac]
void configure_dac(void)
{
//! [setup_dac_config]
	struct dac_config config_dac;
//! [setup_dac_config]

//! [setup_dac_config_defaults]
	dac_get_config_defaults(&config_dac);
//! [setup_dac_config_defaults]

//! [setup_dac_config_extra]
#if (SAML21)
	config_dac.reference = DAC_REFERENCE_INTREF;
#else
	config_dac.reference = DAC_REFERENCE_AVCC;
#endif
//! [setup_dac_config_extra]

//! [setup_dac_set_config]
	dac_init(&dac_instance, DAC, &config_dac);
//! [setup_dac_set_config]

}
//! [configure_dac]

//! [configure_dac_channel]
void configure_dac_channel(void)
{
//! [setup_dac_ch_config]
	struct dac_chan_config config_dac_chan;
//! [setup_dac_ch_config]

//! [setup_dac_ch_config_defaults]
	dac_chan_get_config_defaults(&config_dac_chan);
//! [setup_dac_ch_config_defaults]

//! [setup_dac_ch_set_config]
	dac_chan_set_config(&dac_instance, DAC_CHANNEL_0, &config_dac_chan);
//! [setup_dac_ch_set_config]

//! [setup_dac_ch_enable]
	dac_chan_enable(&dac_instance, DAC_CHANNEL_0);
//! [setup_dac_ch_enable]
}
//! [configure_dac_channel]

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
#if (SAMC21)
	config.peripheral_trigger = ADC1_DMAC_ID_RESRDY;
#else
	config.peripheral_trigger = ADC_DMAC_ID_RESRDY;
#endif
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
	descriptor_config.beat_size = DMA_BEAT_SIZE_HWORD;
	descriptor_config.dst_increment_enable = false;
	descriptor_config.src_increment_enable = false;
	descriptor_config.block_transfer_count = 1000;
	descriptor_config.source_address = (uint32_t)(&adc_instance.hw->RESULT.reg);
#if (SAML21)
	descriptor_config.destination_address = (uint32_t)(&dac_instance.hw->DATA[DAC_CHANNEL_0].reg);
#else
	descriptor_config.destination_address = (uint32_t)(&dac_instance.hw->DATA.reg);
#endif
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
	system_init();

//! [setup_init]
//! [setup_adc]
	configure_adc();
//! [setup_adc]

//! [setup_dac]
	configure_dac();
//! [setup_dac]

//! [setup_dac_channel]
	configure_dac_channel();
//! [setup_dac_channel]

//! [setup_dac_enable]
	dac_enable(&dac_instance);
//! [setup_dac_enable]

//! [setup_dma_resource]
	configure_dma_resource(&example_resource);
//! [setup_dma_resource]

//! [setup_transfer_descriptor]
	setup_transfer_descriptor(&example_descriptor);
//! [setup_transfer_descriptor]

//! [add_descriptor_to_resource]
	dma_add_descriptor(&example_resource, &example_descriptor);
//! [add_descriptor_to_resource]
//! [setup_init]

//! [main]
//! [start_adc_conversion]
	adc_start_conversion(&adc_instance);
//! [start_adc_conversion]

//! [start_transfer]
	dma_start_transfer_job(&example_resource);
//! [start_transfer]

//! [endless_loop]
	while (true) {
	}
//! [endless_loop]
//! [main]
}
