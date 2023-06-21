/**
 * \file
 *
 * \brief SAM DAC Sound Player Application
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \license
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
 * \mainpage SAM DAC Sound Player Application
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This application demonstrates a simple sound player, sourcing a waveform
 * from the device's Non-Volatile Memory and streaming it out of the DAC as
 * an analog waveform.
 */

/**
 * \page appdoc_main SAM DAC Sound Player Application
 *
 * Overview:
 * - \ref appdoc_sam0_dac_sound_player_intro
 * - \ref appdoc_sam0_dac_sound_player_setup
 * - \ref appdoc_sam0_dac_sound_player_usage
 * - \ref appdoc_sam0_dac_sound_player_compinfo
 * - \ref appdoc_sam0_dac_sound_player_contactinfo
 *
 * \section appdoc_sam0_dac_sound_player_intro Introduction
 * This application demonstrates a simple sound player, sourcing a waveform
 * from the device's Non-Volatile Memory and streaming it out of the DAC as
 * an analog waveform.
 *
 * A timer is used to guarantee the DAC conversions are performed at the correct
 * sample rate, using the Event System module of the device to link the periodic
 * timer output events to the DAC module to trigger new sample conversions.
 *
 * This application has been tested on following boards:
 * - SAM D20/D21/L21/C21 Xplained Pro
 *
 * \section appdoc_sam0_dac_sound_player_setup Hardware Setup
 * The device's DAC channel output should be connected to an audio amplifier,
 * speaker, oscilloscope or other similar monitoring equipment so that the
 * generated waveform can be monitored.
 *
 * \section appdoc_sam0_dac_sound_player_usage Usage
 * On startup the device hardware will be configured, and the example will enter
 * an infinite loop. Each time the board button is pressed, the embedded
 * waveform will be output through the DAC and the board LED will be toggled
 *
 * \section appdoc_sam0_dac_sound_player_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_dac_sound_player_contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com">http://www.microchip.com</a>.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>

/** Sample rate of the sound table. */
const uint32_t sample_rate = 16000;

/** Embedded waveform table of sound samples to output. */
const uint16_t wav_samples[] = {
	#include "data.x"
};

/** Number of samples in the waveform. */
const uint32_t number_of_samples =
		(sizeof(wav_samples) / sizeof(wav_samples[0]));


/**
 * \brief Configures the DAC in event triggered mode.
 *
 * Configures the DAC to use the module's default configuration, with output
 * channel mode configured for event triggered conversions.
 *
 * \param dev_inst  Pointer to the DAC module software instance to initialize
 */
static void configure_dac(struct dac_module *dac_module)
{
	struct dac_config config;
	struct dac_chan_config channel_config;

	/* Get the DAC default configuration */
	dac_get_config_defaults(&config);

	/* Switch to GCLK generator 0 */
	config.clock_source = GCLK_GENERATOR_0;

	dac_init(dac_module, DAC, &config);

	/* Get the default DAC channel config */
	dac_chan_get_config_defaults(&channel_config);

#if (SAML21)
	/* Set the channel configuration, and enable it */
	dac_chan_set_config(dac_module, DAC_CHANNEL_1, &channel_config);
	dac_chan_enable(dac_module, DAC_CHANNEL_1);

	/* Enable event triggered conversions */
	struct dac_events events = { .on_event_chan1_start_conversion = true };
#else
	/* Set the channel configuration, and enable it */
	dac_chan_set_config(dac_module, DAC_CHANNEL_0, &channel_config);
	dac_chan_enable(dac_module, DAC_CHANNEL_0);

	/* Enable event triggered conversions */
	struct dac_events events = { .on_event_start_conversion = true };
#endif
	dac_enable_events(dac_module, &events);

	dac_enable(dac_module);
}

/**
 * \brief Configures the TC to generate output events at the sample frequency.
 *
 * Configures the TC in Frequency Generation mode, with an event output once
 * each time the audio sample frequency period expires.
 *
 * \param dev_inst  Pointer to the TC module software instance to initialize
 */
static void configure_tc(struct tc_module *tc_module)
{
	struct tc_config config;
	tc_get_config_defaults(&config);

	config.clock_source    = GCLK_GENERATOR_0;
	config.wave_generation = TC_WAVE_GENERATION_MATCH_FREQ;

	tc_init(tc_module, TC3, &config);

	/* Enable periodic event output generation */
	struct tc_events events = { .generate_event_on_overflow = true };
	tc_enable_events(tc_module, &events);

	/* Set the timer top value to alter the overflow frequency */
	tc_set_top_value(tc_module,
			system_gclk_gen_get_hz(GCLK_GENERATOR_0) / sample_rate);


	tc_enable(tc_module);
}

/**
 * \brief Configures the event system to link the sample timer to the DAC.
 *
 * Configures the event system, linking the TC module used for the audio sample
 * rate timing to the DAC, so that a new conversion is triggered each time the
 * DAC receives an event from the timer.
 */
static void configure_events(struct events_resource *event)
{
	struct events_config config;

	events_get_config_defaults(&config);

	config.generator    = EVSYS_ID_GEN_TC3_OVF;
	config.path         = EVENTS_PATH_ASYNCHRONOUS;

	events_allocate(event, &config);
#if (SAML21)
	events_attach_user(event, EVSYS_ID_USER_DAC_START_1);
#else
	events_attach_user(event, EVSYS_ID_USER_DAC_START);
#endif
}

/**
 * \brief Main application routine
 */
int main(void)
{
	struct dac_module dac_module;
	struct tc_module tc_module;
	struct events_resource event;

	/* Initialize all the system clocks, pm, gclk... */
	system_init();

	/* Enable the internal bandgap to use as reference to the DAC */
#if (SAML21) || (SAMC21)
	system_voltage_reference_enable(SYSTEM_VOLTAGE_REFERENCE_OUTPUT);
#else
	system_voltage_reference_enable(SYSTEM_VOLTAGE_REFERENCE_BANDGAP);
#endif

	/* Module configuration */
	configure_tc(&tc_module);
	configure_dac(&dac_module);
	configure_events(&event);

	/* Start the sample trigger timer */
	tc_start_counter(&tc_module);

	while (true) {
		while (port_pin_get_input_level(SW0_PIN) == SW0_INACTIVE) {
			/* Wait for the button to be pressed */
		}

		port_pin_toggle_output_level(LED0_PIN);

		for (uint32_t i = 0; i < number_of_samples; i++) {
#if (SAML21)
			dac_chan_write(&dac_module, DAC_CHANNEL_1, wav_samples[i] << 2);

			while (!dac_chan_is_end_of_conversion(&dac_module, DAC_CHANNEL_1)) {
#else
			dac_chan_write(&dac_module, DAC_CHANNEL_0, wav_samples[i]);

			while (!(DAC->INTFLAG.reg & DAC_INTFLAG_EMPTY)) {
#endif
				/* Wait for data buffer to be empty */
			}

		}

		while (port_pin_get_input_level(SW0_PIN) == SW0_ACTIVE) {
			/* Wait for the button to be depressed */
		}
	}
}
