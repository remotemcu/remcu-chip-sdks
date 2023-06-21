/**
 * \file
 *
 * \brief CCL Example Application
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \license
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

#include <asf.h>
#include "conf_ccl_example.h"

/** Create structs for TC and DMA. */
struct tc_module tc_def;
struct tc_module tc_alt;
struct dma_resource dma_ch_0;
struct dma_resource dma_ch_1;

/** Create arrays for storing modulator signal period and compare value. */
#define BUF_LENGTH 10
uint8_t period_buffer[BUF_LENGTH] = {0x7,0x7,0x7,0x7,0x7,0x7,0x7,0x7,0x7,0x7};
uint8_t value_buffer[BUF_LENGTH] = {0x2,0x2,0x2,0x2,0x2,0x5,0x5,0x5,0x5,0x5};

/** Create descriptors for DMA. */
COMPILER_ALIGNED(16)
DmacDescriptor descriptor0;
DmacDescriptor descriptor1;

void configure_ccl_lut0(void);
void configure_tc_def(void);
void configure_tc_alt(void);
void configure_tc_evsys(void);
void configure_dma_evsys(void);
void configure_dmac(void);
static void configure_dma_resource(struct dma_resource *resource);
static void configure_dma_channel_0(DmacDescriptor *descriptor);
static void configure_dma_channel_1(DmacDescriptor *descriptor);

void configure_ccl_lut0(void)
{
	/** Creates a new configuration structure for CCL. */
	struct ccl_config conf;

	/** Apply the default settings. */
	ccl_get_config_defaults(&conf);
	conf.clock_source   = GCLK_GENERATOR_1;
	conf.run_in_standby = true;

	/** Initialize CCL with the user settings. */
	ccl_init(&conf);
	
	/** Creates a new configuration structure for LUT0. */
	struct ccl_lut_config conf_ccl_lut0;
	
	/** Apply the default settings. */
	ccl_lut_get_config_defaults(&conf_ccl_lut0);

	/** Configure LUT0. */
	conf_ccl_lut0.truth_table_value = 0x01;
	conf_ccl_lut0.input0_src_sel    = CCL_LUT_INPUT_SRC_TC;
	conf_ccl_lut0.input1_src_sel    = CCL_LUT_INPUT_SRC_ALTTC;
	conf_ccl_lut0.input2_src_sel    = CCL_LUT_INPUT_SRC_MASK;

	/** Set up LUT0 output pin. */
	struct system_pinmux_config lut0_out_pin_conf;
	system_pinmux_get_config_defaults(&lut0_out_pin_conf);
	lut0_out_pin_conf.direction    = SYSTEM_PINMUX_PIN_DIR_OUTPUT;
	lut0_out_pin_conf.mux_position = MUX_CCL_OUTPUT;
	system_pinmux_pin_set_config(PIN_CCL_OUTPUT, &lut0_out_pin_conf);

	/** Initialize and enable LUT0 with the user settings. */
	ccl_lut_set_config(CCL_LUT_0, &conf_ccl_lut0);

	/** Enable CCL module. */
	ccl_lut_enable(CCL_LUT_0);
	ccl_module_enable();
}

void configure_tc_def(void)
{
	/** Creates a new configuration structure for CCL_TC. */
	struct tc_config config_tc;

	/** Apply the default settings. */
	tc_get_config_defaults(&config_tc);

	/** Configure CCL_TC. */
	config_tc.clock_source             = GCLK_GENERATOR_1;
	config_tc.counter_size             = TC_COUNTER_SIZE_8BIT;
	config_tc.clock_prescaler          = TC_CLOCK_PRESCALER_DIV1;
	config_tc.wave_generation          = TC_WAVE_GENERATION_NORMAL_PWM;
	config_tc.reload_action            = TC_RELOAD_ACTION_GCLK;
	config_tc.run_in_standby           = true;
	config_tc.on_demand                = false;
	config_tc.double_buffering_enabled = false;
	config_tc.waveform_invert_output   = TC_WAVEFORM_INVERT_OUTPUT_NONE;
	config_tc.pwm_channel[0].enabled   = true;
	config_tc.pwm_channel[0].pin_mux   = MUX_CCL_TC_OUT;
	config_tc.pwm_channel[0].pin_out   = PIN_CCL_TC_OUT;
	config_tc.count_direction          = TC_COUNT_DIRECTION_UP;
	config_tc.counter_8_bit.value      = 0x00;
	config_tc.counter_8_bit.period     = 0x01;
	config_tc.counter_8_bit.compare_capture_channel[TC_COMPARE_CAPTURE_CHANNEL_0] = 0x1;

	/** Initialize and enable CCL_TC with the user settings. */
	tc_init(&tc_def, CCL_TC, &config_tc);

	/** Creates a new configuration structure for CCL_TC event. */
	struct tc_events conf_tcev;

	/** Configure CCL_TC event. */
	conf_tcev.event_action = TC_EVENT_ACTION_OFF;
	conf_tcev.generate_event_on_compare_channel[0] = false;
	conf_tcev.generate_event_on_compare_channel[1] = false;
	conf_tcev.generate_event_on_overflow           = true;
	conf_tcev.invert_event_input                   = false;
	conf_tcev.on_event_perform_action              = false;

	/** Enable CCL_TC event. */
	tc_enable_events(&tc_def, &conf_tcev);
}

void configure_tc_alt(void)
{
	/** Creates a new configuration structure for CCL_ALTTC. */
	struct tc_config config_tc;

	/** Apply the default settings. */
	tc_get_config_defaults(&config_tc);

	/** Configure CCL_ALTTC. */
	config_tc.clock_source             = GCLK_GENERATOR_1;
	config_tc.counter_size             = TC_COUNTER_SIZE_8BIT;
	config_tc.clock_prescaler          = TC_CLOCK_PRESCALER_DIV1;
	config_tc.wave_generation          = TC_WAVE_GENERATION_NORMAL_PWM;
	config_tc.reload_action            = TC_RELOAD_ACTION_RESYNC;
	config_tc.run_in_standby           = true;
	config_tc.on_demand                = false;
	config_tc.double_buffering_enabled = false;
	config_tc.waveform_invert_output   = TC_WAVEFORM_INVERT_OUTPUT_NONE;
	config_tc.pwm_channel[0].enabled   = true;
	config_tc.pwm_channel[0].pin_mux   = MUX_CCL_ALTTC_OUT;
	config_tc.pwm_channel[0].pin_out   = PIN_CCL_ALTTC_OUT;
	config_tc.count_direction          = TC_COUNT_DIRECTION_UP;
	config_tc.counter_8_bit.value      = 0x00;
	config_tc.counter_8_bit.period     = 0x01;
	config_tc.counter_8_bit.compare_capture_channel[TC_COMPARE_CAPTURE_CHANNEL_0] = 0x1;

	/** Initialize and enable CCL_ALTTC with the user settings. */
	tc_init(&tc_alt, CCL_ALTTC, &config_tc);

	/** Creates a new configuration structure for CCL_ALTTC event. */
	struct tc_events conf_tcev;

	/** Configure CCL_ALTTC event. */
	conf_tcev.event_action = TC_EVENT_ACTION_INCREMENT_COUNTER;
	conf_tcev.generate_event_on_compare_channel[0] = false;
	conf_tcev.generate_event_on_compare_channel[1] = false;
	conf_tcev.generate_event_on_overflow           = true;
	conf_tcev.invert_event_input                   = false;
	conf_tcev.on_event_perform_action              = true;

	/** Enable CCL_ALTTC event. */
	tc_enable_events(&tc_alt, &conf_tcev);
}

void configure_tc_evsys(void)
{
	/** Create new event structs. */
	struct events_resource resource;
	struct events_config config;
	events_get_config_defaults(&config);

	/** Use generator CCL_TC overflow. */
	config.generator      = EVSYS_GEN_CCL_TC_OVF;
	config.edge_detect    = EVENTS_EDGE_DETECT_NONE;
	config.path           = EVENTS_PATH_ASYNCHRONOUS;
	config.clock_source   = GCLK_GENERATOR_1;
	config.run_in_standby = true;

	/** Attach CCL_ALTTC as user. */
	events_allocate(&resource, &config);
	events_attach_user(&resource, EVSYS_USER_CCL_ALTTC);
}

void configure_dma_evsys(void)
{
	/** Create new event structs. */
	struct events_resource resource;
	struct events_config config;
	events_get_config_defaults(&config);

	/** Use generator CCL_ALTTC overflow. */
	config.generator      = EVSYS_GEN_CCL_ALTTC_OVF;
	config.edge_detect    = EVENTS_EDGE_DETECT_NONE;
	config.path           = EVENTS_PATH_RESYNCHRONIZED;
	config.clock_source   = GCLK_GENERATOR_1;
	config.run_in_standby = true;

	/** Attach DMAC channel 0/1 as users. */
	events_allocate(&resource, &config);
	events_attach_user(&resource, EVSYS_ID_USER_DMAC_CH_0);
	events_attach_user(&resource, EVSYS_ID_USER_DMAC_CH_1);
}

static void configure_dma_resource(struct dma_resource *resource)
{
	/** Creates a new configuration structure for the DMA resource. */
	struct dma_resource_config config;

	/** Apply the default settings. */
	dma_get_config_defaults(&config);

	/** Configure DMAC channel 0/1 to transfer data on TC overflow. */
	config.peripheral_trigger = CCL_ALTTC_DMAC_OVF;
	config.run_in_standby     = true;
	config.trigger_action     = DMA_TRIGGER_ACTION_BEAT;

	/** Allocate DMAC channel 0/1. */
	dma_allocate(resource, &config);
}

static void configure_dma_channel_0(DmacDescriptor *descriptor)
{
	/** Creates a new configuration structure for the DMA descriptor. */
	struct dma_descriptor_config descriptor_config;

	/** Apply the default settings. */
	dma_descriptor_get_config_defaults(&descriptor_config);

	/** Configure the DMA descriptor. */
	descriptor_config.beat_size               = DMA_BEAT_SIZE_BYTE;
	descriptor_config.block_action            = DMA_BLOCK_ACTION_NOACT;
	descriptor_config.destination_address     = (uint32_t)(&tc_alt.hw->COUNT8.PER.reg);
	descriptor_config.source_address          = (uint32_t)&period_buffer[BUF_LENGTH];
	descriptor_config.step_selection          = DMA_STEPSEL_SRC;
	descriptor_config.step_size               = DMA_ADDRESS_INCREMENT_STEP_SIZE_1;
	descriptor_config.block_transfer_count    = BUF_LENGTH;
	descriptor_config.dst_increment_enable    = false;
	descriptor_config.src_increment_enable    = true;
	descriptor_config.next_descriptor_address = (uint32_t)&descriptor_section[0];

	dma_descriptor_create(descriptor, &descriptor_config);
}

static void configure_dma_channel_1(DmacDescriptor *descriptor)
{
	/** Creates a new configuration structure for the DMA descriptor. */
	struct dma_descriptor_config descriptor_config;

	/** Apply the default settings. */
	dma_descriptor_get_config_defaults(&descriptor_config);

	/** Configure the DMA descriptor. */
	descriptor_config.beat_size               = DMA_BEAT_SIZE_BYTE;
	descriptor_config.block_action            = DMA_BLOCK_ACTION_NOACT;
	descriptor_config.destination_address     = (uint32_t)(&tc_alt.hw->COUNT8.CC[0].reg);
	descriptor_config.source_address          = (uint32_t)&value_buffer[BUF_LENGTH];
	descriptor_config.step_selection          = DMA_STEPSEL_SRC;
	descriptor_config.step_size               = DMA_ADDRESS_INCREMENT_STEP_SIZE_1;
	descriptor_config.block_transfer_count    = BUF_LENGTH;
	descriptor_config.dst_increment_enable    = false;
	descriptor_config.src_increment_enable    = true;
	descriptor_config.next_descriptor_address = (uint32_t)&descriptor_section[1];

	dma_descriptor_create(descriptor, &descriptor_config);
}

void configure_dmac(void)
{
	/** Configure the DMA resources and channels. */
	configure_dma_resource(&dma_ch_0);
	configure_dma_resource(&dma_ch_1);
	configure_dma_channel_0(&descriptor0);
	configure_dma_channel_1(&descriptor1);

	/** Add both descriptors. */
	dma_add_descriptor(&dma_ch_0, &descriptor0);
	dma_add_descriptor(&dma_ch_1, &descriptor1);

	/** Enable both channels for transfer. */
	dma_start_transfer_job(&dma_ch_0);
	dma_start_transfer_job(&dma_ch_1);
}

int main(void)
{
	system_init();

	/** Configure TC, DMAC and CCL. */
	configure_tc_def();
	configure_tc_alt();
	configure_dmac();
	configure_ccl_lut0();

	/** Configure event system. */
	configure_tc_evsys();
	configure_dma_evsys();

	/** Enable CCL_TC and CCL_ALTTC. */
	tc_enable(&tc_def);
	tc_enable(&tc_alt);

	/** Enter Standby sleep mode. */
	system_set_sleepmode(SYSTEM_SLEEPMODE_STANDBY);
	system_sleep();

	while (1) {
		/** Keep alive while generating IR encoded signal. */
	}
}
