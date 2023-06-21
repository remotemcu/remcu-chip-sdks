/**
 * \file
 *
 * \brief SAM TSENS Quick Start
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

//! [result]
int32_t tsens_result;
//! [result]

//! [module_inst]
struct tsens_module tsens_instance;
//! [module_inst]

//! [job_complete_callback]
volatile bool tsens_read_done = false;

static void tsens_complete_callback(enum tsens_callback i)
{
	tsens_read_done = true;
}
//! [job_complete_callback]

//! [setup]
static void configure_tsens(void)
{
//! [setup_config]
	struct tsens_config config_tsens;
//! [setup_config]
//! [setup_config_defaults]
	tsens_get_config_defaults(&config_tsens);
//! [setup_config_defaults]

//! [setup_set_config]
	tsens_init(&config_tsens);
//! [setup_set_config]

//! [setup_enable]
	tsens_enable();
//! [setup_enable]
}

static void configure_tsens_callbacks(void)
{
//! [setup_register_callback]
	tsens_register_callback(&tsens_instance,
			tsens_complete_callback, TSENS_CALLBACK_RESULT_READY);
//! [setup_register_callback]
//! [setup_enable_callback]
	tsens_enable_callback(TSENS_CALLBACK_RESULT_READY);
//! [setup_enable_callback]
}
//! [setup]

int main(void)
{
	system_init();

//! [setup_init]
	configure_tsens();
	configure_tsens_callbacks();
//! [setup_init]

//! [main]
//! [enable_interrupts]
	system_interrupt_enable(SYSTEM_INTERRUPT_MODULE_TSENS);
	system_interrupt_enable_global();
//! [enable_interrupts]

//! [start_tsens_job]
	tsens_read_job(&tsens_instance, &tsens_result);
//! [start_tsens_job]

//! [job_complete_poll]
	while (tsens_read_done == false) {
		/* Wait for asynchronous TSENS read to complete */
	}
//! [job_complete_poll]

//! [inf_loop]
	while (1) {
		/* Infinite loop */
	}
//! [inf_loop]
//! [main]
}
