/**
 * \file
 *
 * \brief SW Timer component for the IoT(Internet of things) service.
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

#include "sw_timer.h"

/** Tick count of timer. */
 static uint32_t sw_timer_tick = 0;

/**
 * \brief TCC callback of SW timer.
 *
 * This function performs to the increasing the tick count.
 *
 * \param[in] module Instance of the TCC.
 */
static void sw_timer_tcc_callback(struct tcc_module *const module)
{
	sw_timer_tick++;
}

void sw_timer_get_config_defaults(struct sw_timer_config *const config)
{
	Assert(config);

	config->accuracy = 100;
	config->tcc_dev = 0;
	config->tcc_callback_channel = 0;
}

void sw_timer_init(struct sw_timer_module *const module_inst, struct sw_timer_config *const config)
{
	struct tcc_config tcc_conf;
	struct tcc_module *tcc_module;
	Tcc *hw[] = TCC_INSTS;

	Assert(module_inst);
	Assert(config);
	Assert(config->tcc_dev < TCC_INST_NUM);
	Assert(config->tcc_callback_channel < TCC_NUM_CHANNELS);

	module_inst->accuracy = config->accuracy;

	/* Start the TCC module. */
	tcc_module = &module_inst->tcc_inst;
	tcc_get_config_defaults(&tcc_conf, hw[config->tcc_dev]);
	tcc_conf.counter.period = system_cpu_clock_get_hz() / (64 * 1000 / config->accuracy);
	tcc_conf.counter.clock_prescaler = TCC_CLOCK_PRESCALER_DIV64;
	tcc_init(tcc_module, hw[config->tcc_dev], &tcc_conf);
	tcc_register_callback(tcc_module, sw_timer_tcc_callback, config->tcc_callback_channel + TCC_CALLBACK_CHANNEL_0);
	tcc_enable_callback(tcc_module, config->tcc_callback_channel + TCC_CALLBACK_CHANNEL_0);
}

void sw_timer_enable(struct sw_timer_module *const module_inst)
{
	struct tcc_module *tcc_module;

	Assert(module_inst);

	tcc_module = &module_inst->tcc_inst;

	tcc_enable(tcc_module);
}

void sw_timer_disable(struct sw_timer_module *const module_inst)
{
	struct tcc_module *tcc_module;

	Assert(module_inst);

	tcc_module = &module_inst->tcc_inst;
	tcc_disable(tcc_module);
}

int sw_timer_register_callback(struct sw_timer_module *const module_inst,
	sw_timer_callback_t callback, void *context, uint32_t period)
{
	int index;
	struct sw_timer_handle *handler;

	Assert(module_inst);

	for (index = 0; index < CONF_SW_TIMER_COUNT; index++) {
		if (module_inst->handler[index].used == 0) {
			handler = &module_inst->handler[index];
			handler->callback = callback;
			handler->callback_enable = 0;
			handler->context = context;
			handler->period = period / module_inst->accuracy;
			handler->used = 1;
			return index;
		}
	}

	return -1;
}

void sw_timer_unregister_callback(struct sw_timer_module *const module_inst, int timer_id)
{
	struct sw_timer_handle *handler;

	Assert(module_inst);
	Assert((timer_id >= 0 && timer_id < CONF_SW_TIMER_COUNT));

	handler = &module_inst->handler[timer_id];

	handler->used = 0;
}

void sw_timer_enable_callback(struct sw_timer_module *const module_inst, int timer_id, uint32_t delay)
{
	struct sw_timer_handle *handler;

	Assert(module_inst);
	Assert((timer_id >= 0 && timer_id < CONF_SW_TIMER_COUNT));

	handler = &module_inst->handler[timer_id];

	handler->callback_enable = 1;
	handler->expire_time = sw_timer_tick + (delay / module_inst->accuracy);
}

void sw_timer_disable_callback(struct sw_timer_module *const module_inst, int timer_id)
{
	struct sw_timer_handle *handler;

	Assert(module_inst);
	Assert((timer_id >= 0 && timer_id < CONF_SW_TIMER_COUNT));

	handler = &module_inst->handler[timer_id];

	handler->callback_enable = 0;
}

void sw_timer_task(struct sw_timer_module *const module_inst)
{
	int index;
	struct sw_timer_handle *handler;

	Assert(module_inst);

	for (index = 0; index < CONF_SW_TIMER_COUNT; index++) {
		if (module_inst->handler[index].used && module_inst->handler[index].callback_enable) {
			handler = &module_inst->handler[index];
			if ((int)(handler->expire_time - sw_timer_tick) < 0 && handler->busy == 0) {
				/* Enter critical section. */
				handler->busy = 1;
				/* Call callback function. */
				handler->callback(module_inst, index, handler->context, handler->period);
				/* Timer was expired. */
				if (handler->period > 0) {
					handler->expire_time = sw_timer_tick + handler->period;
				} else {
					/* One shot. */
					handler->callback_enable = 0;
				}
				/* Leave critical section. */
				handler->busy = 0;
			}
		}
	}

}

