/**
 * \file
 *
 * \brief SAM D20 DAC WAVEFORM GENERATOR
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

/**
 * \mainpage SAM D20 DAC Waveform Generator Application
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This application generates standard waveforms like sine wave, saw-tooth
 * wave and triangular wave using the DAC module in SAM D20 devices.
 */

/**
 * \page appdoc_main SAM D20 Waveform Generator Application
 *
 * Overview:
 * - \ref appdoc_sam0_dac_wave_generator_intro
 * - \ref appdoc_sam0_dac_wave_generator_setup
 * - \ref appdoc_sam0_dac_wave_generator_usage
 * - \ref appdoc_sam0_dac_wave_generator_compinfo
 * - \ref appdoc_sam0_dac_wave_generator_contactinfo
 *
 * \section appdoc_sam0_dac_wave_generator_intro Introduction
 * This application generates standard waveforms like sine wave, saw-tooth
 * wave and triangular wave using the DAC module in SAM D20 devices.
 *
 * A timer is used to guarantee the DAC conversions are performed at the
 * correct sample rate, using the Event System module of the device to link
 * the periodic timer output events to the DAC module to trigger new sample 
 * conversions.
 *
 * This application has been tested on following board:
 * - SAM D20 Xplained Pro
 *
 * \section appdoc_sam0_dac_wave_generator_setup Hardware Setup
 * The device's DAC channel output (PA02) should be connected to an
 * oscilloscope so that the generated waveform can be monitored.
 *
 * \section appdoc_sam0_dac_wave_generator_usage Usage
 * The waveform selection macro WAVE_MODE should be set to required waveform
 * and the macro FREQUENCY should be set to required value before building
 * the project. 
 * When application starts, it will initialize the peripherals (Timer, Event
 * system, DAC and the wave data buffer). After initialization the application
 * will start the timer.
 * The timer will generate both interrupt and event. The event will move the
 * value in DAC DATABUF register to DAC DATA register. The interrupt handler
 * will load next data into DAC DATABUF register.
 *
 * Refer application note 'Waveform Generator and WAV Audio Player using DAC'
 * for more details.
 *
 * \section appdoc_sam0_dac_wave_generator_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_dac_wave_generator_contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com">http://www.microchip.com</a>.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define DEGREES_PER_CYCLE 360
/* one degree is equal to 0.0174532925 radian */
#define DEGREE 0.0174532925
/* Waveform type macros */ 
#define SINE_WAVE		0
#define SAW_TOOTH_WAVE	1
#define TRIANGLE_WAVE	2

/* Waveform selection macro - Selects any one of the three waveforms */
#define WAVE_MODE SINE_WAVE
/* Waveform Frequency in Hz, specify a value less than 970Hz for 
   sine wave and less than 1360Hz for other two waves */
#define FREQUENCY 150

/* Function Prototypes */
void timer_init(void);
void dac_initialize(void);
void evsys_init(void);
void buffer_init(void);

/* Driver module structure declaration */
struct tc_module tc_inst;
struct dac_module dac_inst;

/* Buffer variable declaration */
#if WAVE_MODE==SINE_WAVE
uint16_t sine_wave_buf[DEGREES_PER_CYCLE];
#elif WAVE_MODE==SAW_TOOTH_WAVE
uint16_t sawtooth_wave_buf[256];
#elif WAVE_MODE==TRIANGLE_WAVE
uint16_t triangle_wave_buf[256];
#endif

/* Other global variables */
uint16_t i, arr_index;

/* Timer 0 interrupt handler */
void TC0_Handler(void)
{
	TC0->COUNT16.INTFLAG.reg = TC_INTFLAG_MC0;
#if WAVE_MODE==SINE_WAVE
	dac_chan_write(&dac_inst, 0, sine_wave_buf[arr_index++]);
	if (arr_index == 360) {
		arr_index = 0;
	}
#elif WAVE_MODE==SAW_TOOTH_WAVE
	dac_chan_write(&dac_inst, 0, sawtooth_wave_buf[arr_index++]);
	if (arr_index == 256) {
		arr_index = 0;
	}
#elif WAVE_MODE==TRIANGLE_WAVE
	dac_chan_write(&dac_inst, 0, triangle_wave_buf[arr_index++]);
	if (arr_index == 256) {
		arr_index = 0;
	}
#endif
}

/* Timer 0 Initialization */
void timer_init(void)
{
	struct tc_config conf_tc;
	struct tc_events conf_tc_events = {.generate_event_on_compare_channel[0] = 1};
	tc_get_config_defaults(&conf_tc);
	conf_tc.clock_source = GCLK_GENERATOR_0;
	conf_tc.wave_generation = TC_WAVE_GENERATION_MATCH_FREQ;
	conf_tc.counter_16_bit.compare_capture_channel[0] = 0xFFFF;
	tc_init(&tc_inst, TC0, &conf_tc);
	tc_enable_events(&tc_inst, &conf_tc_events);
	tc_enable(&tc_inst);
	tc_stop_counter(&tc_inst);
	/* Enable TC0 match/capture channel 0 interrupt */
	TC0->COUNT16.INTENSET.reg = TC_INTENSET_MC0;
	/* Enable TC0 module interrupt */
	NVIC_EnableIRQ(TC0_IRQn);
}

/* DAC Initialization */
void dac_initialize(void)
{
	struct dac_config conf_dac;
	struct dac_events conf_dac_events = {.on_event_start_conversion = 1};
	dac_get_config_defaults(&conf_dac);
	conf_dac.clock_source = GCLK_GENERATOR_3;
	conf_dac.reference = DAC_REFERENCE_INT1V;
	dac_init(&dac_inst, DAC, &conf_dac);
	dac_enable_events(&dac_inst, &conf_dac_events);
	dac_enable(&dac_inst);
}

/* Event System Initialization */
void evsys_init(void)
{
	struct events_resource conf_event_resource;
	struct events_config conf_event;
	events_get_config_defaults(&conf_event);
	conf_event.edge_detect = EVENTS_EDGE_DETECT_NONE;
	conf_event.path = EVENTS_PATH_ASYNCHRONOUS;
	conf_event.generator = EVSYS_ID_GEN_TC0_MCX_0;
	events_allocate(&conf_event_resource, &conf_event);
	events_attach_user(&conf_event_resource, EVSYS_ID_USER_DAC_START);
}

/* Initialize the selected waveform buffer with output data */
void buffer_init(void)
{
#if WAVE_MODE==SINE_WAVE
	for (i = 0; i < DEGREES_PER_CYCLE; i++)	{
		sine_wave_buf[i] = (uint16_t)(500 + (500*sin((double)i*DEGREE)));
	}
#elif WAVE_MODE==SAW_TOOTH_WAVE
	for (i = 0; i < 256; i++) {
		sawtooth_wave_buf[i] = i*4;
	}
#elif WAVE_MODE==TRIANGLE_WAVE
	for (i = 0; i < 128; i++) {
		triangle_wave_buf[i] = i*8;
	}
	for (i = 128; i < 256; i++) {
		triangle_wave_buf[i] = 1023 - (i*8);
	}
#endif
}

/* Main function */
int main(void)
{
	system_init();
	timer_init();
	dac_initialize();
	evsys_init();
	buffer_init();
	/* Set the TC0 compare value corresponding to specified frequency */
#if WAVE_MODE==SINE_WAVE
	tc_set_compare_value(&tc_inst, 0, \
		system_gclk_gen_get_hz(GCLK_GENERATOR_0)/(FREQUENCY*360));
#else
	tc_set_compare_value(&tc_inst, 0, \
		system_gclk_gen_get_hz(GCLK_GENERATOR_0)/(FREQUENCY*256));
#endif
	/* Start TC0 timer */
	tc_start_counter(&tc_inst);
	/* Enable global interrupt */
	system_interrupt_enable_global();
	
	while (true) {

	}
}
