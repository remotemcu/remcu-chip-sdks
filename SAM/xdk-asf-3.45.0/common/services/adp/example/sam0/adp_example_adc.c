/**
 * \file
 *
 * \brief ADP service example ADC functions for SAM0
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
#include "adp_example_adc.h"

struct adc_module adc_instance;

void adp_example_adc_init(void)
{
 	struct adc_config config_adc;
	adc_get_config_defaults(&config_adc);
#if (SAMD21)
	config_adc.positive_input = ADC_POSITIVE_INPUT_PIN8;
#else
	config_adc.positive_input = ADC_POSITIVE_INPUT_PIN0;
#endif
	config_adc.clock_prescaler = ADC_CLOCK_PRESCALER_DIV64;
	config_adc.reference = ADC_REFERENCE_INTVCC0;
	adc_init(&adc_instance, EXT1_ADC_MODULE, &config_adc);
	adc_enable(&adc_instance);
}

uint16_t adp_example_adc_get_value(void)
{
	uint16_t result;
	adc_start_conversion(&adc_instance);
	while (adc_read(&adc_instance, &result) == STATUS_BUSY);
	return result;
}
