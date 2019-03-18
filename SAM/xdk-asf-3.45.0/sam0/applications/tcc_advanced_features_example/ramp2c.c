/**
 * \file
 *
 * \brief SAM D21 TCC RAMP2C Example Application
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */

#include <asf.h>
#include <string.h>
#include "conf_example.h"
static struct tcc_module tcc_inst;


#if (ENABLE_FAULT_BALNKING == true)

static void configure_eic(void)
{
	struct extint_chan_conf config_extint_chan;
	extint_chan_get_config_defaults(&config_extint_chan);

	config_extint_chan.gpio_pin           = PIN_PA11A_EIC_EXTINT11;
	config_extint_chan.gpio_pin_mux       = PINMUX_PA11A_EIC_EXTINT11;
	config_extint_chan.gpio_pin_pull      = EXTINT_PULL_DOWN;
	config_extint_chan.detection_criteria = EXTINT_DETECT_HIGH;				
	extint_chan_set_config(11 , &config_extint_chan);
	
	struct extint_events conf_extint_event;
	memset(&conf_extint_event, 0, sizeof(struct extint_events));
	
	conf_extint_event.generate_event_on_detect[11] = true;
	extint_enable_events(&conf_extint_event);
}

static void configure_ac(void) 
{
	static struct ac_module ac_instance;
	struct ac_config config_ac;
	
	ac_get_config_defaults(&config_ac);
	config_ac.ana_source_generator = GCLK_GENERATOR_1;
	config_ac.dig_source_generator = GCLK_GENERATOR_1;
	
	/* Initialize and enable the Analog Comparator with the user settings */
	ac_init(&ac_instance, AC1, &config_ac);
	
	/* Create a new configuration structure for the Analog Comparator channel
	 * settings and fill with the default module channel settings. */
	struct ac_chan_config ac_chan_conf;
	ac_chan_get_config_defaults(&ac_chan_conf);
	
	/* Set the Analog Comparator channel configuration settings */
	ac_chan_conf.sample_mode      = AC_CHAN_MODE_CONTINUOUS;
	ac_chan_conf.filter           = AC_CHAN_FILTER_NONE;
	ac_chan_conf.positive_input   = AC_CHAN_POS_MUX_PIN3;
	ac_chan_conf.negative_input   = AC_CHAN_NEG_MUX_SCALED_VCC;
	ac_chan_conf.vcc_scale_factor = AC_SCALING_FACTOR;
	ac_chan_conf.output_mode      = AC_CHAN_OUTPUT_INTERNAL;	
																						
	/* Initialize and enable the Analog Comparator channel with the user
	 * settings */
	ac_chan_set_config(&ac_instance, 0, &ac_chan_conf);

		
	/* Set up a pin as an AC channel input */
	struct system_pinmux_config ac0_pin_conf;
	system_pinmux_get_config_defaults(&ac0_pin_conf);
	
	ac0_pin_conf.direction    = SYSTEM_PINMUX_PIN_DIR_INPUT;
	ac0_pin_conf.mux_position = MUX_PB03B_AC1_AIN3;
	system_pinmux_pin_set_config(PIN_PB03B_AC1_AIN3, &ac0_pin_conf);
	
	/* Setup event output from AC */
	struct ac_events ac_event_conf;
	memset(&ac_event_conf, 0, sizeof(struct ac_events));
	
	ac_event_conf.generate_event_on_state[0] = true;
	ac_enable_events(&ac_instance, &ac_event_conf);
	
	/* enable AC channel */
	ac_chan_enable(&ac_instance, 0);
	ac_enable(&ac_instance);
}
#endif

static void configure_tcc_ramp2c_mode(void)
{
	struct tcc_config config_tcc;
	
	delay_init();
	tcc_get_config_defaults(&config_tcc, TCC0);
	
	/* Set up output pins */
	/* CC2 will be included to generate ramp output WO[0] in RAMP2C mode*/
	config_tcc.pins.enable_wave_out_pin[0] = true;
	config_tcc.pins.wave_out_pin[0]        = PIN_PA04E_TCC0_WO0;
	config_tcc.pins.wave_out_pin_mux[0]    = MUX_PA04E_TCC0_WO0;
	
	/* CC1 will be included to generate ramp output WO[1] RAMP2C mode */	
	config_tcc.pins.enable_wave_out_pin[1] = true;
	config_tcc.pins.wave_out_pin[1]        = PIN_PA09E_TCC0_WO1;
	config_tcc.pins.wave_out_pin_mux[1]    = MUX_PA09E_TCC0_WO1;
		

	/* Generator 1 as clock source */
	config_tcc.counter.clock_source    = GLCK_SOURCE;
	config_tcc.counter.clock_prescaler = TCC_CLOCK_DIVIDER;	
	
	/* Set up initial period */	
	config_tcc.counter.period = PER_Value;
	
	/* set CC0 */
	/* CC0 will act as ramp A top in RAMP2C mode */
	config_tcc.compare.match[0] = CC0_Value;		
	
	/* set compare reg CC1 & CC2 in RAMP2C mode */
	config_tcc.compare.match[1] = CC1_Value;
	config_tcc.compare.match[2] = CC2_Value;		

	/* Set up polarity output ramp */
	config_tcc.compare.wave_polarity[1] = 1;
	config_tcc.compare.wave_polarity[2] = 1;	
	
	/* Normal PWM in RAMP2 mode */
	config_tcc.compare.wave_generation = TCC_WAVE_GENERATION_SINGLE_SLOPE_PWM;
	config_tcc.compare.wave_ramp       = TCC_RAMP_RAMP2;

#if (ENABLE_FAULT_BALNKING == true)	
	
	/* Set up recoverable fault A on virtual pulse */
	config_tcc.wave_ext.recoverable_fault[0].qualification   = true;
	config_tcc.wave_ext.recoverable_fault[0].source          = TCC_FAULT_SOURCE_ENABLE;
	config_tcc.wave_ext.recoverable_fault[0].restart         = true;
	config_tcc.wave_ext.recoverable_fault[0].blanking_cycles = 10;
	config_tcc.wave_ext.recoverable_fault[0].blanking        = TCC_FAULT_BLANKING_RISING_EDGE;
	
	/* Set up recoverable fault A on on WO */
	config_tcc.wave_ext.recoverable_fault[1].qualification   = true;
	config_tcc.wave_ext.recoverable_fault[1].source          = TCC_FAULT_SOURCE_ENABLE;
	config_tcc.wave_ext.recoverable_fault[1].restart         = true;
	config_tcc.wave_ext.recoverable_fault[1].blanking_cycles = 10;
	config_tcc.wave_ext.recoverable_fault[1].blanking        = TCC_FAULT_BLANKING_RISING_EDGE;
	
#endif
	
	/* Initialize with given configuration */
	tcc_init(&tcc_inst, TCC0, &config_tcc);

	/* RAMP2C mode */
	while(TCC0->SYNCBUSY.reg & TCC_SYNCBUSY_WAVE);
	TCC0->WAVE.bit.RAMP = TCC_WAVEB_RAMPB_RAMP2C_Val;
	while(TCC0->SYNCBUSY.reg & TCC_SYNCBUSY_WAVE);	
	
	
#if (ENABLE_FAULT_BALNKING == true)		

	/* set fault blanking prescaler*/
	tcc_inst.hw->FCTRLA.reg |= 1 << BLANKPRESC;
	tcc_inst.hw->FCTRLB.reg |= 1 << BLANKPRESC;

	/* Enable recoverable fault event */
	struct tcc_events events;
	memset(&events, 0, sizeof(struct tcc_events));
	
	events.on_event_perform_channel_action[0] = true;
	events.on_event_perform_channel_action[1] = true;
	tcc_enable_events(&tcc_inst, &events);
	
#endif

	/* Enable TCC */
	tcc_enable(&tcc_inst);
}

#if (ENABLE_FAULT_BALNKING == true)

static void configure_evsys(void)
{
	struct events_resource ev_resource;
	struct events_config ev_conf;
	events_get_config_defaults(&ev_conf);
	
	/*	
		* Configure event system to define even generator and event user  
		* Event Type, edge and path
	*/
	ev_conf.generator   = EVSYS_ID_GEN_EIC_EXTINT_11;
	ev_conf.edge_detect = EVENTS_EDGE_DETECT_NONE;		
	ev_conf.path        = EVENTS_PATH_ASYNCHRONOUS;
	events_allocate(&ev_resource, &ev_conf);
	events_attach_user(&ev_resource, EVSYS_ID_USER_TCC0_MC_1);
	
	ev_conf.generator   = EVSYS_ID_GEN_AC1_COMP_0;
	ev_conf.edge_detect = EVENTS_EDGE_DETECT_NONE;
	ev_conf.path        = EVENTS_PATH_ASYNCHRONOUS;
	events_allocate(&ev_resource, &ev_conf);
	events_attach_user(&ev_resource, EVSYS_ID_USER_TCC0_MC_0);

}


/* Code to generate Fault input */
void TCC0_Handler(void)
{
	TCC0->INTFLAG.reg = TCC_INTFLAG_MC1;
	PORT->Group[0].OUTSET.reg = PORT_PA14;
	
	delay_us(200);
	
	PORT->Group[0].OUTCLR.reg = PORT_PA14;
}
#endif


void config_ramp2c(void)
{
#if (ENABLE_FAULT_BALNKING == true)	
	configure_eic();
	configure_ac();
#endif	
	configure_tcc_ramp2c_mode();
	
#if (ENABLE_FAULT_BALNKING == true)	
	configure_evsys();	
	
	PORT->Group[0].DIRSET.reg = PORT_PA14;
	PORT->Group[0].OUTCLR.reg = PORT_PA14;
	
	TCC0->INTENSET.reg = TCC_INTFLAG_MC1;
	
	NVIC_EnableIRQ(TCC0_IRQn);
	__enable_irq();	
#endif
	
}