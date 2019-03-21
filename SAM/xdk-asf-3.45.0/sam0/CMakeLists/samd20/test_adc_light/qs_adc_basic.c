/**
 * \file
 *
 * \brief SAM ADC Quick Start
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "remcu.h"

void configure_adc(void);

//! [module_inst]
struct adc_module adc_instance;
//! [module_inst]

//! [setup]
void configure_adc(void)
{
//! [setup_config]
	struct adc_config config_adc;
//! [setup_config]
//! [setup_config_defaults]
	adc_get_config_defaults(&config_adc);
//! [setup_config_defaults]
	config_adc.positive_input                = 18 ;

//! [setup_set_config]
#if (SAMC21)
	adc_init(&adc_instance, ADC1, &config_adc);
#else
	adc_init(&adc_instance, ADC, &config_adc);
#endif
//! [setup_set_config]

//! [setup_enable]
	adc_enable(&adc_instance);
//! [setup_enable]
}

uint16_t adc_start_read_result(void)
{
	uint16_t adc_result = 0;
	
	adc_start_conversion(&adc_instance);
	//while((adc_get_status(&adc_instance) & ADC_STATUS_RESULT_READY) != 1);
	//sleep(1);
	do {
    } while(adc_read(&(adc_instance), &adc_result) == STATUS_BUSY);   // 12 bit value
	enum status_code ret = adc_read(&adc_instance, &adc_result);
	printf("status_code : %d\n", ret);
	
	return adc_result;
}
//! [setup]

int main(void)
{
	//remcu_connect2GDB("localhost", 3333, 1);
	remcu_connect2OpenOCD("localhost", 6666, 1);
remcu_resetRemoteUnit(__HALT);
remcu_setVerboseLevel(__INFO);

	system_init();

//! [setup_init]
	configure_adc();
//! [setup_init]
	struct system_pinmux_config config;
        system_pinmux_get_config_defaults(&config);

        /* Analog functions are all on MUX setting B */
        config.input_pull   = SYSTEM_PINMUX_PIN_PULL_NONE;
        config.mux_position = 1;

        system_pinmux_pin_set_config(PIN_PA10B_ADC_AIN18, &config);

//! [main]
//! [start_conv]

//! [get_res]
	uint16_t result;

//! [get_res]

//! [inf_loop]
	while (1) {
		/* Infinite loop */
	
	printf("adc_read : %x\n", adc_start_read_result());

	}
//! [inf_loop]
//! [main]
}
