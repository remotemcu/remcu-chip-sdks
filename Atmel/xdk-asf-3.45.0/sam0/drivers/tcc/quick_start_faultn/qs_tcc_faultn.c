/**
 * \file
 *
 * \brief SAM TCC - Timer Counter for Control Applications Callback Driver Quick Start (with Recoverable Fault)
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
#include <conf_quick_start_faultn.h>

#ifndef SAMR30
#if (CONF_PWM_CHANNEL != 0) && (CONF_PWM_CHANNEL != 1)
#error Only TCC channel 0 and 1 support Recoverable Fault, please check CONF_PWM_CHANNEL
#endif
#endif

//! [additional_include]
#include <string.h>
//! [additional_include]

//! [module_inst]
struct tcc_module tcc_instance;
//! [module_inst]

//! [events_resource]
struct events_resource event_resource;
//! [events_resource]

//! [callback_funcs]
static void tcc_callback_to_change_duty_cycle(
		struct tcc_module *const module_inst)
{
	static uint32_t delay = 10;
	static uint32_t i = 0;

	if (--delay) {
		return;
	}
	delay = 10;
	i = (i + 0x0800) & 0xFFFF;
	tcc_set_compare_value(module_inst,
			(enum tcc_match_capture_channel)
					(TCC_MATCH_CAPTURE_CHANNEL_0 + CONF_PWM_CHANNEL),
			i + 1);
}
//! [callback_funcs]

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
	config_tcc.counter.period = 0xFFFF;
	config_tcc.compare.wave_generation = TCC_WAVE_GENERATION_SINGLE_SLOPE_PWM;
	config_tcc.compare.match[CONF_PWM_CHANNEL] = 0xFFFF;
	//! [setup_change_config]
	//! [setup_change_config_faults]
	config_tcc.wave_ext.recoverable_fault[CONF_PWM_CHANNEL].source =
			TCC_FAULT_SOURCE_ENABLE;
	config_tcc.wave_ext.recoverable_fault[CONF_PWM_CHANNEL].halt_action =
			TCC_FAULT_HALT_ACTION_SW_HALT;
	//! [setup_change_config_faults]
	//! [setup_change_config_pwm]
	config_tcc.pins.enable_wave_out_pin[CONF_PWM_OUTPUT] = true;
	config_tcc.pins.wave_out_pin[CONF_PWM_OUTPUT]        = CONF_PWM_OUT_PIN;
	config_tcc.pins.wave_out_pin_mux[CONF_PWM_OUTPUT]    = CONF_PWM_OUT_MUX;
	//! [setup_change_config_pwm]

	//! [setup_set_config]
	tcc_init(&tcc_instance, CONF_PWM_MODULE, &config_tcc);
	//! [setup_set_config]

	//! [setup_events]
	struct tcc_events events;
	memset(&events, 0, sizeof(struct tcc_events));
	//! [setup_events]

	//! [setup_change_events_faults]
	events.on_event_perform_channel_action[CONF_PWM_CHANNEL] = true;
	//! [setup_change_events_faults]

	//! [setup_events_enable]
	tcc_enable_events(&tcc_instance, &events);
	//! [setup_events_enable]

	//! [setup_enable]
	tcc_enable(&tcc_instance);
	//! [setup_enable]
}

static void configure_tcc_callbacks(void)
{
	//! [setup_register_callback]
	tcc_register_callback(
			&tcc_instance,
			tcc_callback_to_change_duty_cycle,
			(enum tcc_callback)(TCC_CALLBACK_CHANNEL_0 + CONF_PWM_CHANNEL));
	//! [setup_register_callback]

	//! [setup_enable_callback]
	tcc_enable_callback(&tcc_instance,
			(enum tcc_callback)(TCC_CALLBACK_CHANNEL_0 + CONF_PWM_CHANNEL));
	//! [setup_enable_callback]
}
//! [setup]

//! [callback_eic]
static void eic_callback_to_clear_halt(void)
{
	if (port_pin_get_input_level(CONF_FAULT_EIC_PIN)) {
		tcc_clear_status(&tcc_instance,
				TCC_STATUS_RECOVERABLE_FAULT_OCCUR(CONF_PWM_CHANNEL));
	}
}
//! [callback_eic]

//! [config_eic]
static void configure_eic(void)
{
	//! [eic_chan_setup]
	//! [eic_setup_1]
	struct extint_chan_conf config;
	//! [eic_setup_1]
	//! [eic_setup_2]
	extint_chan_get_config_defaults(&config);
	//! [eic_setup_2]
	//! [eic_setup_3]
	config.filter_input_signal = true;
	config.detection_criteria  = EXTINT_DETECT_BOTH;
	config.gpio_pin     = CONF_FAULT_EIC_PIN;
	config.gpio_pin_mux = CONF_FAULT_EIC_PIN_MUX;
	//! [eic_setup_3]
	//! [eic_setup_4]
	extint_chan_set_config(CONF_FAULT_EIC_LINE, &config);
	//! [eic_setup_4]
	//! [eic_chan_setup]

	//! [eic_event_setup]
	//! [eic_event_setup_1]
	struct extint_events events;
	memset(&events, 0, sizeof(struct extint_events));
	//! [eic_event_setup_1]
	//! [eic_event_setup_2]
	events.generate_event_on_detect[CONF_FAULT_EIC_LINE] = true;
	//! [eic_event_setup_2]
	//! [eic_event_setup_3]
	extint_enable_events(&events);
	//! [eic_event_setup_3]
	//! [eic_event_setup]

	//! [eic_callback_setup]
	//! [eic_callback_setup_1]
	extint_register_callback(eic_callback_to_clear_halt,
			CONF_FAULT_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);
	//! [eic_callback_setup_1]
	//! [eic_callback_setup_2]
	extint_chan_enable_callback(CONF_FAULT_EIC_LINE,
			EXTINT_CALLBACK_TYPE_DETECT);
	//! [eic_callback_setup_2]
	//! [eic_callback_setup]
}
//! [config_eic]

//! [config_event]
static void configure_event(void)
{
	//! [event_setup_1]
	struct events_config config;
	//! [event_setup_1]

	//! [event_setup_2]
	events_get_config_defaults(&config);
	//! [event_setup_2]

	//! [event_setup_3]
	config.generator = CONF_FAULT_EVENT_GENERATOR;
	config.path      = EVENTS_PATH_ASYNCHRONOUS;
	//! [event_setup_3]

	//! [event_setup_4]
	events_allocate(&event_resource, &config);
	//! [event_setup_4]

	//! [event_setup_5]
	events_attach_user(&event_resource, CONF_FAULT_EVENT_USER);
	//! [event_setup_5]
}
//! [config_event]

int main(void)
{
	system_init();

//! [setup_init]
	configure_tcc();
	configure_tcc_callbacks();

	configure_eic();
	configure_event();
//! [setup_init]

//! [main]
	//! [enable_global_interrupts]
	system_interrupt_enable_global();
	//! [enable_global_interrupts]

	//! [main_loop]
	while (true) {
	}
	//! [main_loop]
//! [main]
}
