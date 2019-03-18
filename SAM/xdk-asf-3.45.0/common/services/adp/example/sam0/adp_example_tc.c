/**
 * \file
 *
 * \brief ADP service example TC functions for SAM0
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

#include <compiler.h>
#include <asf.h>
#include "adp_example_tc.h"
#include "conf_tc.h"

struct tc_module tc_instance;
volatile bool time_out = true;

static void adp_example_tc_callback(struct tc_module *const module_inst)
{
	time_out = true;
}

static void adp_example_tc_configure(void)
{
	struct tc_config config_tc;
	
	tc_get_config_defaults(&config_tc);
	config_tc.clock_source = GCLK_GENERATOR_1;
	config_tc.counter_size = TC_COUNTER_SIZE_8BIT;
	config_tc.clock_prescaler = TC_CLOCK_PRESCALER_DIV16;
	/* Timer = 16*(2^8 - 55 - 1)/32000 = 100ms */
	config_tc.counter_8_bit.value = 0;
	config_tc.counter_8_bit.period = 55;
	
	tc_init(&tc_instance, CONF_TC_MODULE, &config_tc);
	tc_enable(&tc_instance);
}

static void adp_example_tc_configure_callback(void)
{
	tc_register_callback(&tc_instance, adp_example_tc_callback, \
						TC_CALLBACK_OVERFLOW);
	tc_enable_callback(&tc_instance, TC_CALLBACK_OVERFLOW);
}

void adp_example_tc_init(void)
{
 	adp_example_tc_configure();
	adp_example_tc_configure_callback();
}

