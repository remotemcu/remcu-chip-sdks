/**
 * \file
 *
 * \brief SAM L21 OPAMP as ADC Gain Amplifier
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
 /*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */


/**
 * \mainpage OPAMP as ADC Gain Amplifier Example application
 *
 * \section Purpose
 *
 * The example configures the OPAMP to act as a gain amplifier for the ADC.
 *
 * \section Requirements
 *
 * This package can be used with the SAM L21 xplained pro.
 *
 * This package has been tested on following boards:
 * - SAM L21 Xplained Pro
 *
 * \section Description
 *
 * The example setups the OPAMP to act as a gain amplifier for the ADC.
 * the OPAMP is configured as a non-inverting PGA, with a gain of 4.
 *
 * \section Usage
 *
 * -# Connect a voltage to be measured to pin PA05 (Opamp 2 positive input)
 * -# Build the program and download it to the evaluation board.
 * -# Start a debug session and run the program to completion.
 * -# The measured values can be read in adc_result_buffer.
 *
 */

#include <asf.h>
#include "conf_example.h"

void configure_opamp2(void);
void configure_adc(void);
void configure_adc_callbacks(void);
void adc_complete_callback(struct adc_module *const module);

/* Buffer for ADC sample storage */
#define ADC_SAMPLES 128
uint16_t adc_result_buffer[ADC_SAMPLES];

/* ADC interrupt flag */
volatile bool adc_read_done = false;

/* ADC module */
struct adc_module adc_instance;

/* Configure OPAMP2 and I/O PORT */
void configure_opamp2(void)
{
	/* Creates a new configuration structure for the OPAMP2. */
	struct opamp2_config conf;

	/* Initializes OPAMP module. */
	opamp_module_init();

	/* Fill with the default settings. */
	opamp2_get_config_defaults(&conf);

	/* Set the the OPAMP2 in "Non-Inverted PGA" mode, gain of 4 */
	conf.negative_input           = OPAMP2_NEG_MUX_TAP2;
	conf.positive_input           = OPAMP2_POS_MUX_PIN2;
	conf.r1_connection            = OPAMP2_RES1_MUX_GND;
	conf.config_common.potentiometer_selection = OPAMP_POT_MUX_12R_4R;
	conf.config_common.r1_enable  = true;
	conf.config_common.r2_out     = true;
	conf.config_common.analog_out = true;

	/* Set up OA2POS pin as input. */
	struct system_pinmux_config opamp2_input_pin_conf;
	system_pinmux_get_config_defaults(&opamp2_input_pin_conf);
	opamp2_input_pin_conf.direction    = SYSTEM_PINMUX_PIN_DIR_INPUT;
	opamp2_input_pin_conf.mux_position = OPAMP_INPUT_MUX;
	system_pinmux_pin_set_config(OPAMP_INPUT_PIN, &opamp2_input_pin_conf);

	/* Initialize and enable the OPAMP2 with the user settings. */
	opamp2_set_config(&conf);
	opamp_enable(OPAMP_2);
	
	/* Wait for the output ready. */
	while(!opamp_is_ready(OPAMP_2));
}

/* Configure ADC */
void configure_adc(void)
{
	/* Creates a new configuration structure for the ADC */
	struct adc_config config_adc;

	adc_get_config_defaults(&config_adc);
	
	/* Setup ADC with OPAMP2 output as ADC input */
	config_adc.clock_prescaler = ADC_CLOCK_PRESCALER_DIV8;
	config_adc.positive_input  = ADC_POSITIVE_INPUT_OPAMP2;
	
	/* Initialize and enable ADC */
	adc_init(&adc_instance, ADC, &config_adc);
	adc_enable(&adc_instance);
}

/* Enable ADC Callback Function */
void configure_adc_callbacks(void)
{
	adc_register_callback(&adc_instance,
			adc_complete_callback, ADC_CALLBACK_READ_BUFFER);
	adc_enable_callback(&adc_instance, ADC_CALLBACK_READ_BUFFER);
}

/* ADC Callback Function */
void adc_complete_callback(struct adc_module *const module)
{
	/* Set ADC conversion ended flag */
	adc_read_done = true;
}

/* Main function */
int main(void)
{
	system_init();
	
	/* Initialize OPAMP2 and ADC */
	configure_opamp2();
	configure_adc();
	configure_adc_callbacks();
	
	/* Enable global interrupts */
	system_interrupt_enable_global();
	
	/* Start ADC conversion */
	adc_read_buffer_job(&adc_instance, adc_result_buffer, ADC_SAMPLES);
	
	while (adc_read_done == false) {
		/* Wait for asynchronous ADC read to complete */
	}
	
	while(true) {
		/* Do nothing */
	}
}
