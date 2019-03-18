/**
 * \file
 *
 * \brief ADC Quick Start for SAMB11
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

/* Define this flag for TDM mode ADC */
//#define TDM_MODE_ADC

//! [setup]
static void configure_adc(void)
{
//! [setup_config]
	struct adc_config config_adc;
//! [setup_config]

//! [setup_config_defaults]
	adc_get_config_defaults(&config_adc);
//! [setup_config_defaults]

//! [setup_config_ch]
#ifdef TDM_MODE_ADC
	config_adc.input_channel = CONF_ADC_INPUT_CH;
	config_adc.channel_mode = ADC_CH_MODE_CH0_TO_CH3;
#else
	config_adc.input_channel = CONF_ADC_INPUT_CH;
#endif

//! [setup_config_ch]

//! [setup_set_config]
	adc_init(&config_adc);
//! [setup_set_config]

//! [setup_enable]
	adc_enable();
//! [setup_enable]
}
//! [setup]

int main(void)
{
	system_clock_config(CLOCK_RESOURCE_XO_26_MHZ, CLOCK_FREQ_26_MHZ);

//! [setup_init]
	configure_adc();
//! [setup_init]

//! [main]

//! [get_res]
#ifdef TDM_MODE_ADC
	uint16_t result[4];
	do {
		/* Wait for conversion to be done and read out result */
	} while (tdm_mode_adc_read(ADC_INPUT_CH_GPIO_MS1, &result[0]) != STATUS_OK);
	
	do {
		/* Wait for conversion to be done and read out result */
	} while (tdm_mode_adc_read(ADC_INPUT_CH_GPIO_MS2, &result[1]) != STATUS_OK);
	
	do {
		/* Wait for conversion to be done and read out result */
	} while (tdm_mode_adc_read(ADC_INPUT_CH_GPIO_MS3, &result[2]) != STATUS_OK);
	
	do {
		/* Wait for conversion to be done and read out result */
	} while (tdm_mode_adc_read(ADC_INPUT_CH_GPIO_MS4, &result[3]) != STATUS_OK);
#else /* Single channel mode */
	uint16_t result;
	do {
		/* Wait for conversion to be done and read out result */
	} while (adc_read(CONF_ADC_INPUT_CH, &result) != STATUS_OK);
#endif
	
//! [get_res]

//! [inf_loop]
	while (1) {
		/* Infinite loop */
	}
//! [inf_loop]
//! [main]
}
