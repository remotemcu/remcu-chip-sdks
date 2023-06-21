/**
 * \file
 *
 * \brief SAM DAC Callback Quick Start
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

//! [transfer_length]
#define DATA_LENGTH (16)
//! [transfer_length]

void dac_callback(uint8_t channel);
void configure_dac(void);
void configure_dac_channel(void);
void configure_rtc_count(void);
void configure_event_resource(void);

//! [dac_module_inst]
struct dac_module dac_instance;
//! [dac_module_inst]

//! [rtc_module_inst]
struct rtc_module rtc_instance;
//! [rtc_module_inst]

//! [event_res]
struct events_resource event_dac;
//! [event_res]

//! [transfer_done_flag]
static volatile bool transfer_is_done = false;
//! [transfer_done_flag]

//! [dac_data]
static uint16_t dac_data[DATA_LENGTH];
//! [dac_data]

//! [setup_event_resource]
void configure_event_resource(void)
{
//! [event_config]
	struct events_config event_config;
//! [event_config]

//! [get_event_default]
	events_get_config_defaults(&event_config);
//! [get_event_default]

//! [set_event_modify_conf]
	event_config.generator      = EVSYS_ID_GEN_RTC_OVF;
	event_config.edge_detect    = EVENTS_EDGE_DETECT_RISING;
	event_config.path           = EVENTS_PATH_ASYNCHRONOUS;
	event_config.clock_source   = GCLK_GENERATOR_0;
//! [set_event_modify_conf]

//! [allocate_event_resource]
	events_allocate(&event_dac, &event_config);
//! [allocate_event_resource]

//! [attach_event_to_dac]
#if (SAML21)
	events_attach_user(&event_dac, EVSYS_ID_USER_DAC_START_0);
#else
	events_attach_user(&event_dac, EVSYS_ID_USER_DAC_START);
#endif
//! [attach_event_to_dac]
}
//! [setup_event_resource]


//! [setup_rtc]
void configure_rtc_count(void)
{
//! [setup_rtc_event]
	struct rtc_count_events  rtc_event;
//! [setup_rtc_event]

//! [setup_rtc_config]
	struct rtc_count_config config_rtc_count;
//! [setup_rtc_config]

//! [setup_rtc_config_defaults]
	rtc_count_get_config_defaults(&config_rtc_count);
//! [setup_rtc_config_defaults]

//! [setup_rtc_modify_conf]
	config_rtc_count.prescaler           = RTC_COUNT_PRESCALER_DIV_1;
	config_rtc_count.mode                = RTC_COUNT_MODE_16BIT;
#ifdef FEATURE_RTC_CONTINUOUSLY_UPDATED
	config_rtc_count.continuously_update = true;
#endif
//! [setup_rtc_modify_conf]

//! [init_rtc_count]
	rtc_count_init(&rtc_instance, RTC, &config_rtc_count);
//! [init_rtc_count]

//! [setup_rtc_overflow_event]
	rtc_event.generate_event_on_overflow = true;
//! [setup_rtc_overflow_event]

//! [enable_rtc_overflow_event]
	rtc_count_enable_events(&rtc_instance, &rtc_event);
//! [enable_rtc_overflow_event]

//! [enable_rtc]
	rtc_count_enable(&rtc_instance);
//! [enable_rtc]
}
//! [setup_rtc]

//! [job_complete_callback]
void dac_callback(uint8_t channel)
{
	UNUSED(channel);

//! [set_transfer_done_flag]
	transfer_is_done = true;
//! [set_transfer_done_flag]
}
//! [job_complete_callback]

//! [setup_dac]
void configure_dac(void)
{
//! [setup_dac_config]
	struct dac_config config_dac;
//! [setup_dac_config]

//! [setup_dac_config_default]
	dac_get_config_defaults(&config_dac);
//! [setup_dac_config_default]

//! [setup_dac_start_on_event]
#if (SAML21)
	dac_instance.start_on_event[DAC_CHANNEL_0] = true;
#else
	dac_instance.start_on_event = true;
#endif
//! [setup_dac_start_on_event]

//! [setup_dac_instance]
	dac_init(&dac_instance, DAC, &config_dac);
//! [setup_dac_instance]

//! [setup_dac_on_event_start_conversion]
	struct dac_events events =
#if (SAML21)
		{ .on_event_chan0_start_conversion = true };
#else
		{ .on_event_start_conversion = true };
#endif
//! [setup_dac_on_event_start_conversion]

//! [enable_dac_event]
	dac_enable_events(&dac_instance, &events);
//! [enable_dac_event]
}
//! [setup_dac]

//! [setup_dac_channel]
void configure_dac_channel(void)
{
//! [setup_dac_chan_config]
	struct dac_chan_config config_dac_chan;
//! [setup_dac_chan_config]

//! [setup_dac_chan_config_default]
	dac_chan_get_config_defaults(&config_dac_chan);
//! [setup_dac_chan_config_default]

//! [set_dac_chan_config]
	dac_chan_set_config(&dac_instance, DAC_CHANNEL_0,
			&config_dac_chan);
//! [set_dac_chan_config]

//! [enable_dac_channel]
	dac_chan_enable(&dac_instance, DAC_CHANNEL_0);
//! [enable_dac_channel]
}
//! [setup_dac_channel]

int main(void)
{
//! [data_length_var]
	uint32_t i;
//! [data_length_var]
	system_init();

//! [setup_init]
//! [init_rtc]
	configure_rtc_count();
//! [init_rtc]

//! [set_rtc_period]
	rtc_count_set_period(&rtc_instance, 1);
//! [set_rtc_period]

//! [init_dac]
	configure_dac();
//! [init_dac]

//! [init_dac_chan]
	configure_dac_channel();
//! [init_dac_chan]

//! [enable_dac]
	dac_enable(&dac_instance);
//! [enable_dac]

//! [init_event_resource]
	configure_event_resource();
//! [init_event_resource]

//! [register_dac_callback]
	dac_register_callback(&dac_instance, DAC_CHANNEL_0,
			dac_callback,DAC_CALLBACK_TRANSFER_COMPLETE);
//! [register_dac_callback]

//! [enable_dac_callback]
	dac_chan_enable_callback(&dac_instance, DAC_CHANNEL_0,
			DAC_CALLBACK_TRANSFER_COMPLETE);
//! [enable_dac_callback]

//! [setup_dac_data]
	for (i = 0;i < DATA_LENGTH;i++) {
		dac_data[i] = 0x3f * i;
	}
//! [setup_dac_data]
//! [setup_init]

//! [main_start]
//! [main_write]
	dac_chan_write_buffer_job(&dac_instance, DAC_CHANNEL_0,
			dac_data, DATA_LENGTH);
//! [main_write]

//! [main_check_transfer_done]
	while (!transfer_is_done) {
		/* Wait for transfer done */
	}
//! [main_check_transfer_done]

//! [main_loop]
	while (1) {
	}
//! [main_loop]
//! [main_start]
}

