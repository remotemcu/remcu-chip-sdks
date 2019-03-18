/**
 * \file
 *
 * \brief SAM XOSC32K Runtime Failure Detector Application
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
 * \mainpage SAM XOSC32K Runtime Failure Detector Application
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This application demonstrates a hardware XOSC32K external 32KHz crystal
 * oscillator clock source failure detector, using general purpose hardware
 * peripherals.
 */

/**
 * \page appdoc_main SAM XOSC32K Runtime Failure Detector
 *
 * Overview:
 * - \ref appdoc_sam0_xosc32k_fail_detect_intro
 * - \ref appdoc_sam0_xosc32k_fail_detect_compinfo
 * - \ref appdoc_sam0_xosc32k_fail_detect_usageinfo
 * - \ref appdoc_sam0_xosc32k_fail_detect_contactinfo
 *
 * \section appdoc_sam0_xosc32k_fail_detect_intro Introduction
 * This application demonstrates a runtime XOSC32K (external 32KHz crystal
 * oscillator) failure detector, using hardware timer peripherals and the
 * SAM event system.
 *
 * A pair of timers are linked together; one with a clock source from the
 * XOSC32K 32.768KHz external clock, and another from the OSC32K 32.768KHz
 * internal RC clock source. Each time the XOSC32K timer reaches a
 * configurable count value, a hardware event resets the second timer using
 * the OSC32K clock source.
 *
 * If the OSC32K clocked timer reaches a configurable count value before it is
 * reset by the XOSC32K timer, the XOSC32K clock source is considered failed and
 * a callback function is executed. If instead the XOSC32K closed clocked timer
 * resets the OSC32K clocked timer, the oscillator is considered OK and another
 * callback function is executed.
 *
 * In the example application, the DFLL reference clock is automatically
 * switched between the internal and external 32KHz clock sources depending on
 * the external reference availability.
 *
 * This application has been tested on following boards:
 * - SAM D20/D21/R21/L21/D11/R30 Xplained Pro
 *
 * \section appdoc_sam0_xosc32k_fail_detect_usageinfo Usage
 * Connect an oscilloscope to PA28 of the SAM D20/D21 or PB22 of SAMR21 or PA08
 * of SAM D10/D11 or PA27 of SAML21 or PA14 of SAMR30 Xplained Pro. Run the example
 * application, and press and hold the board button to turn off the external XOSC32K
 * crystal clock source to observe the fail-over to the internal clock source. Releasing
 * the button will re-enable the external crystal.
 *
 * The board LED will be turned on when the external crystal is used, and
 *  will be turned off when the internal RC is used due to a crystal failure
 * detection.
 *
 * \section appdoc_sam0_xosc32k_fail_detect_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_xosc32k_fail_detect_contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com">http://www.microchip.com</a>.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include "conf_example.h"

/** Number of cycles on the XOSC32K before resetting the reference timer */
#define CRYSTAL_RESET_CYCLES   200
/** Number of cycles on the OSC32K before assuming a XOSC32K failure */
#define CRYSTAL_FAIL_CYCLES    (CRYSTAL_RESET_CYCLES * 2)
/** Generator index configured to source from the XOSC32K crystal. */
#define GCLK_GENERATOR_XOSC32K GCLK_GENERATOR_2
/** Generator index configured to source from the internal OSC32K oscillator. */
#define GCLK_GENERATOR_OSC32K  GCLK_GENERATOR_1
/** If \c true, the CPU clock will be routed out to GPIO pin */
#define ENABLE_CPU_CLOCK_OUT   true

/** Software instance of the XOSC32K timer */
static struct tc_module tc_xosc32k;
/** Software instance of the OSC32K timer */
static struct tc_module tc_osc32k;

#if SAML21 || SAMR30
#define SYSCTRL_GCLK_ID_DFLL48 REG_GCLK_PCHCTRL0
#endif

/** Configures and starts the DFLL in closed loop mode with the given reference
 *  generator.
 *
 *  \param[in]  source_generator  Reference generator to use for the DFLL
 */
static void init_dfll(
		const enum system_clock_source source_generator)
{
	struct system_gclk_gen_config cpu_clock_conf;
	system_gclk_gen_get_config_defaults(&cpu_clock_conf);
	cpu_clock_conf.output_enable = ENABLE_CPU_CLOCK_OUT;

	/* Switch to OSC8M/OSC16M while the DFLL is being reconfigured */
#if SAML21 || SAMR30
	cpu_clock_conf.source_clock = SYSTEM_CLOCK_SOURCE_OSC16M;
#else
	cpu_clock_conf.source_clock = SYSTEM_CLOCK_SOURCE_OSC8M;
#endif
	system_gclk_gen_set_config(GCLK_GENERATOR_0, &cpu_clock_conf);

	/* Turn off DFLL before adjusting its configuration */
	system_clock_source_disable(SYSTEM_CLOCK_SOURCE_DFLL);

	/* Configure DFLL reference clock, use raw register write to
	 * force-configure the channel even if the currently selected generator
	 * clock has failed */
#if SAML21 || SAMR30
        GCLK->PCHCTRL[SYSCTRL_GCLK_ID_DFLL48].reg = GCLK_PCHCTRL_GEN(source_generator);      
#else
	GCLK->CLKCTRL.reg =
			GCLK_CLKCTRL_ID(SYSCTRL_GCLK_ID_DFLL48) |
			GCLK_CLKCTRL_GEN(source_generator);
#endif
	system_gclk_chan_enable(SYSCTRL_GCLK_ID_DFLL48);

	/* Configure DFLL */
	struct system_clock_source_dfll_config config_dfll;
	system_clock_source_dfll_get_config_defaults(&config_dfll);
	config_dfll.on_demand = false;
	config_dfll.loop_mode = SYSTEM_CLOCK_DFLL_LOOP_MODE_CLOSED;
	config_dfll.multiply_factor =
			(48000000UL / system_gclk_chan_get_hz(SYSCTRL_GCLK_ID_DFLL48));
	system_clock_source_dfll_set_config(&config_dfll);

	/* Restart DFLL */
	system_clock_source_enable(SYSTEM_CLOCK_SOURCE_DFLL);
	while (system_clock_source_is_ready(SYSTEM_CLOCK_SOURCE_DFLL) == false) {
		/* Wait for DFLL to be stable before switch back */
	}

	/* Switch back to the DFLL as the CPU clock source */
	cpu_clock_conf.source_clock = SYSTEM_CLOCK_SOURCE_DFLL;
	system_gclk_gen_set_config(GCLK_GENERATOR_0, &cpu_clock_conf);
};

/** Configures and starts the OSC32K internal clock. */
static void init_osc32k(void)
{
	/* Configure and enable the OSC32K clock source */
	struct system_clock_source_osc32k_config osc32k_conf;
	system_clock_source_osc32k_get_config_defaults(&osc32k_conf);
	system_clock_source_osc32k_set_config(&osc32k_conf);
	system_clock_source_enable(SYSTEM_CLOCK_SOURCE_OSC32K);
}

/** Configures and starts the XOSC32K external crystal. */
static void init_xosc32k(void)
{
	/* Configure and enable the XOSC32K clock source */
	struct system_clock_source_xosc32k_config xosc32k_conf;
	system_clock_source_xosc32k_get_config_defaults(&xosc32k_conf);
#if (!SAML21) && (!SAMR30)
	xosc32k_conf.auto_gain_control = false;
#endif
	xosc32k_conf.on_demand = false;
	system_clock_source_xosc32k_set_config(&xosc32k_conf);
	system_clock_source_enable(SYSTEM_CLOCK_SOURCE_XOSC32K);
	while(!system_clock_source_is_ready(SYSTEM_CLOCK_SOURCE_XOSC32K));
}

/** Callback run when a XOSC32K crystal operation is detected.
 *
 *  \param[in]  instance  Timer instance that triggered the operation
 *                        (\ref CONF_TC_XOSC32K)
 */
static void xosc32k_ok_callback(
		struct tc_module *instance)
{
	/* Turn off the oscillator OK callback, turn on the fail callback */
	tc_disable_callback(&tc_xosc32k, TC_CALLBACK_CC_CHANNEL0);
	tc_enable_callback(&tc_osc32k, TC_CALLBACK_CC_CHANNEL0);

	/* Crystal OK - switch DFLL to XOSC32K */
	init_dfll((enum system_clock_source)GCLK_GENERATOR_XOSC32K);
	port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
}

/** Callback run when a XOSC32K crystal failure is detected.
 *
 *  \param[in]  instance  Timer instance that triggered the failure
 *                        (\ref CONF_TC_OSC32K)
 */
static void xosc32k_fail_callback(
		struct tc_module *instance)
{
	/* Turn on the oscillator OK callback, turn off the fail callback */
	tc_enable_callback(&tc_xosc32k, TC_CALLBACK_CC_CHANNEL0);
	tc_disable_callback(&tc_osc32k, TC_CALLBACK_CC_CHANNEL0);

	/* Crystal failed - switch DFLL to OSC32K */
	init_dfll((enum system_clock_source)GCLK_GENERATOR_OSC32K);
	port_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);
}

/** Initializes the XOSC32K crystal failure detector, and starts it.
 *
 *  \param[in]  ok_callback    Callback function to run upon XOSC32K operational
 *  \param[in]  fail_callback  Callback function to run upon XOSC32K failure
 */
static void init_xosc32k_fail_detector(
		const tc_callback_t ok_callback,
		const tc_callback_t fail_callback)
{
	/* TC pairs share the same clock, ensure reference and crystal timers use
	 * different clocks */
	Assert(Abs(_tc_get_inst_index(CONF_TC_OSC32K) -
			_tc_get_inst_index(CONF_TC_XOSC32K)) >= 2);

	/* The crystal detection cycle count must be less than the reference cycle
	 * count, so that the reference timer is periodically reset before expiry */
	Assert(CRYSTAL_RESET_CYCLES < CRYSTAL_FAIL_CYCLES);

	/* Must use different clock generators for the crystal and reference, must
	 * not be CPU generator 0 */
	Assert(GCLK_GENERATOR_XOSC32K != GCLK_GENERATOR_OSC32K);
	Assert(GCLK_GENERATOR_XOSC32K != GCLK_GENERATOR_0);
	Assert(GCLK_GENERATOR_OSC32K  != GCLK_GENERATOR_0);

	/* Configure and enable the XOSC32K GCLK generator */
	struct system_gclk_gen_config xosc32k_gen_conf;
	system_gclk_gen_get_config_defaults(&xosc32k_gen_conf);
	xosc32k_gen_conf.source_clock = SYSTEM_CLOCK_SOURCE_XOSC32K;
	system_gclk_gen_set_config(GCLK_GENERATOR_XOSC32K, &xosc32k_gen_conf);
	system_gclk_gen_enable(GCLK_GENERATOR_XOSC32K);

	/* Configure and enable the reference clock GCLK generator */
	struct system_gclk_gen_config ref_gen_conf;
	system_gclk_gen_get_config_defaults(&ref_gen_conf);
	ref_gen_conf.source_clock = SYSTEM_CLOCK_SOURCE_OSC32K;
	system_gclk_gen_set_config(GCLK_GENERATOR_OSC32K, &ref_gen_conf);
	system_gclk_gen_enable(GCLK_GENERATOR_OSC32K);

	/* Set up crystal counter - when target count elapses, trigger event */
	struct tc_config tc_xosc32k_conf;
	tc_get_config_defaults(&tc_xosc32k_conf);
	tc_xosc32k_conf.clock_source = GCLK_GENERATOR_XOSC32K;
	tc_xosc32k_conf.counter_16_bit.compare_capture_channel[0] =
			CRYSTAL_RESET_CYCLES;
	tc_xosc32k_conf.wave_generation = TC_WAVE_GENERATION_MATCH_FREQ;
	tc_init(&tc_xosc32k, CONF_TC_XOSC32K, &tc_xosc32k_conf);

	/* Set up reference counter - when event received, restart */
	struct tc_config tc_osc32k_conf;
	tc_get_config_defaults(&tc_osc32k_conf);
	tc_osc32k_conf.clock_source = GCLK_GENERATOR_OSC32K;
	tc_osc32k_conf.counter_16_bit.compare_capture_channel[0] =
			CRYSTAL_FAIL_CYCLES;
	tc_osc32k_conf.wave_generation = TC_WAVE_GENERATION_MATCH_FREQ;
	tc_init(&tc_osc32k, CONF_TC_OSC32K, &tc_osc32k_conf);

	/* Configure event channel and link it to the xosc32k counter */
	struct events_config config;
	struct events_resource event;
	events_get_config_defaults(&config);
	config.edge_detect  = EVENTS_EDGE_DETECT_NONE;
	config.generator    = CONF_EVENT_GENERATOR_ID;
	config.path         = EVENTS_PATH_ASYNCHRONOUS;
	events_allocate(&event, &config);
	/* Configure event user and link it to the osc32k counter */
	events_attach_user(&event, CONF_EVENT_USED_ID);

	/* Enable event generation for crystal counter */
	struct tc_events tc_xosc32k_events = { .generate_event_on_overflow = true };
	tc_enable_events(&tc_xosc32k, &tc_xosc32k_events);

	/* Enable event reception for reference counter */
	struct tc_events tc_osc32k_events = { .on_event_perform_action = true };
	tc_osc32k_events.event_action = TC_EVENT_ACTION_RETRIGGER;
	tc_enable_events(&tc_osc32k, &tc_osc32k_events);

	/* Enable overflow callback for the crystal counter - if crystal count
	 * has been reached, crystal is operational */
	tc_register_callback(&tc_xosc32k, ok_callback, TC_CALLBACK_CC_CHANNEL0);
	tc_enable_callback(&tc_xosc32k, TC_CALLBACK_CC_CHANNEL0);

	/* Enable compare callback for the reference counter - if reference count
	 * has been reached, crystal has failed */
	tc_register_callback(&tc_osc32k, fail_callback, TC_CALLBACK_CC_CHANNEL0);
	tc_enable_callback(&tc_osc32k, TC_CALLBACK_CC_CHANNEL0);

	/* Start both crystal and reference counters */
	tc_enable(&tc_xosc32k);
	tc_enable(&tc_osc32k);
}

/** Main application entry point. */
int main(void)
{
	system_init();

	system_flash_set_waitstates(2);

	init_osc32k();
	init_xosc32k();
	init_xosc32k_fail_detector(
			xosc32k_ok_callback, xosc32k_fail_callback);

#if ENABLE_CPU_CLOCK_OUT == true
	/* Configure a GPIO pin as the CPU clock output */
	struct system_pinmux_config clk_out_pin;
	system_pinmux_get_config_defaults(&clk_out_pin);
	clk_out_pin.direction    = SYSTEM_PINMUX_PIN_DIR_OUTPUT;
	clk_out_pin.mux_position = CONF_CLOCK_PIN_MUX;
	system_pinmux_pin_set_config(CONF_CLOCK_PIN_OUT, &clk_out_pin);
#endif

	for (;;) {
		static bool old_run_osc = true;
		bool new_run_osc =
				(port_pin_get_input_level(BUTTON_0_PIN) == BUTTON_0_INACTIVE);

		/* Check if the XOSC32K needs to be started or stopped when the board
		 * button is pressed or released */
		if (new_run_osc != old_run_osc) {
			if (new_run_osc) {
				system_clock_source_enable(SYSTEM_CLOCK_SOURCE_XOSC32K);
				while(!system_clock_source_is_ready(
						SYSTEM_CLOCK_SOURCE_XOSC32K));
			}
			else {
				system_clock_source_disable(SYSTEM_CLOCK_SOURCE_XOSC32K);
			}

			old_run_osc = new_run_osc;
		}
	}
}
