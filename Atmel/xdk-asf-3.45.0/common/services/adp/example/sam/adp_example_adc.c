/**
 * \file
 *
 * \brief ADP service example ADC functions for SAM
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

#include <compiler.h>
#include <asf.h>
#include "adp_example_adc.h"

#define ADC_CLOCK  6000000

void adp_example_adc_init(void)
{
	// Enable ADC clock
	pmc_enable_periph_clk(ID_ADC);

	adc_init(ADC, sysclk_get_main_hz(), ADC_CLOCK, ADC_STARTUP_TIME_4);
	adc_configure_timing(ADC, 1, ADC_SETTLING_TIME_3, 1);
	adc_set_resolution(ADC, ADC_12_BITS);
	adc_enable_channel(ADC, ADC_CHANNEL_0);
	adc_configure_trigger(ADC, ADC_TRIG_SW, ADC_MR_FREERUN_OFF);
}

uint16_t adp_example_adc_get_value(void)
{
	adc_start(ADC);
	while ((adc_get_status(ADC) & ADC_ISR_DRDY) != ADC_ISR_DRDY);
	return adc_get_latest_value(ADC) & 0xFFF;
}
