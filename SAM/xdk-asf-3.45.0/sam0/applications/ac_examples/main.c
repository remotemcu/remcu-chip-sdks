/**
 * \file
 *
 * \brief SAM D21 Analog Comparator Examples
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
 * \mainpage SAM D21 Analog Comparator Examples
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 * \page appdoc_preface Overview
 * This example demonstrates the different functional modes of Analog
 * Comparator (AC) module in SAM D21 devices.
 */

/**
 * \page appdoc_main SAM D21 Analog Comparator Examples
 *
 * Overview:
 * - \ref appdoc_sam0_ac_examples_intro
 * - \ref appdoc_sam0_ac_examples_setup
 * - \ref appdoc_sam0_ac_examples_usage
 * - \ref appdoc_sam0_ac_examples_compinfo
 * - \ref appdoc_sam0_ac_examples_contactinfo
 *
 * \section appdoc_sam0_ac_examples_intro Introduction
 * This example demonstrates the different functional modes of Analog
 * Comparator (AC) module in SAM D21 devices.
 *
 * Analog comparator is configured in different modes like level crossing
 * detector, window mode detector, false spike avoider or SleepWalking one
 * at a time by commenting / uncommenting the macro  AC_MODE in the 
 * application example.
 *
 * This application has been tested on following board:
 * - SAM D21 Xplained Pro
 *
 * \section appdoc_sam0_ac_examples_setup Hardware Setup
 * A sine wave signal should be applied on pin PA04 in the SAM D21 Xplained
 * pro board. More details on analog input signal specification can be found
 * in application note 'Analog Comparator Application Examples'.
 * The device's analog comparator output pin (PA12) should be connected to an
 * oscilloscope so that the generated waveform can be monitored.
 *
 * \section appdoc_sam0_ac_examples_usage Usage
 * The waveform selection macro AC_MODE should be set to required AC example.
 *
 * The application will first configure the system clock and then configures
 * the analog comparator based on selected example mode. 
 * In level crossing application, the output pin PA12 will be set when the 
 * analog input is above a threshold level. 
 * In window mode application, the output pin will be set whenever the input 
 * signal goes out of a window with two threshold levels. 
 * In false spike avoider application, hysteresis and filter mode are enabled 
 * which avoid frequent toggling of AC output when the analog input oscillates 
 * around the detect threshold. 
 * In SleepWalking mode, the analog comparator is configured in single shot 
 * mode which performs comparison every 10ms which is timed from RTC and 
 * triggered through Event System that reduces the overall current consumption 
 * of the system.
 *
 * \section appdoc_sam0_ac_examples_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_ac_examples_contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com">http://www.microchip.com</a>.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>

/* Application macro assignments */
#define AC_LEVEL_CROSS_DETECTOR		0
#define AC_WINDOW_DETECTOR			1
#define AC_FALSE_SPIKE_PREVENTER	2
#define AC_SLEEP_WALKING			3

/* Event system macro assignments - used in SleepWalking example */
#define CONF_EVENT_GENERATOR  EVSYS_ID_GEN_RTC_OVF
#define CONF_EVENT_USER       EVSYS_ID_USER_AC_SOC_0 

/* Application selection macros. Uncomment required application macro
   definition and comment all other macros */
#define AC_MODE					AC_LEVEL_CROSS_DETECTOR
//#define AC_MODE					AC_WINDOW_DETECTOR
//#define AC_MODE					AC_FALSE_SPIKE_PREVENTER
//#define AC_MODE					AC_SLEEP_WALKING	

/* ASF peripheral drivers structure definitions */
struct ac_module ac_instance;
struct rtc_module rtc_instance;
struct events_resource resource;

/* Function prototypes */
void ac_detect_callback(struct ac_module *const module_inst);
void configure_ac(void);
void configure_rtc(void);
void configure_event(void);

/* AC level cross detector or false spike preventer application */
#if (AC_MODE == AC_LEVEL_CROSS_DETECTOR || AC_MODE == AC_FALSE_SPIKE_PREVENTER)

/* Analog comparator configuration function */
void configure_ac(void)
{
	struct ac_config conf_ac;
	struct ac_chan_config conf_ac_channel;
	struct system_pinmux_config conf_pinmux;
	
	/* Enable alternate function H for pin PA12 */
	conf_pinmux.direction = SYSTEM_PINMUX_PIN_DIR_OUTPUT;
	conf_pinmux.input_pull = SYSTEM_PINMUX_PIN_PULL_NONE;
	conf_pinmux.mux_position = 7;
	conf_pinmux.powersave = false;
	system_pinmux_pin_set_config(PIN_PA12, &conf_pinmux);
	
	ac_get_config_defaults(&conf_ac);
	ac_init(&ac_instance, AC, &conf_ac);
	
	conf_ac_channel.sample_mode = AC_CHAN_MODE_CONTINUOUS;
	#if (AC_MODE == AC_LEVEL_CROSS_DETECTOR)
	conf_ac_channel.filter = AC_CHAN_FILTER_NONE;
	conf_ac_channel.enable_hysteresis = false;
	#else
	conf_ac_channel.filter = AC_CHAN_FILTER_MAJORITY_5;
	conf_ac_channel.enable_hysteresis = true;
	#endif
	conf_ac_channel.output_mode = AC_CHAN_OUTPUT_SYNCHRONOUS;
	conf_ac_channel.positive_input = AC_CHAN_POS_MUX_PIN0;
	conf_ac_channel.negative_input = AC_CHAN_NEG_MUX_SCALED_VCC;
	/* Detect threshold 0.515625V */
	conf_ac_channel.vcc_scale_factor = 9+1;	
	conf_ac_channel.interrupt_selection = AC_CHAN_INTERRUPT_SELECTION_TOGGLE;
	ac_chan_set_config(&ac_instance, AC_CHAN_CHANNEL_0, &conf_ac_channel);
	ac_chan_enable(&ac_instance, AC_CHAN_CHANNEL_0);
	
	ac_enable(&ac_instance);
}

/* AC window detector application */
#elif (AC_MODE == AC_WINDOW_DETECTOR)

volatile bool out_of_window = false;

/* Analog comparator detect callback function */
void ac_detect_callback(struct ac_module *const module_inst)
{
	out_of_window = true;
}

/* Analog comparator configuration function */
void configure_ac(void)
{
	struct ac_config conf_ac;
	struct ac_chan_config conf_ac_channel;
	struct ac_win_config conf_ac_win;
	struct port_config pin_conf;
	
	pin_conf.direction = PORT_PIN_DIR_OUTPUT;
	pin_conf.input_pull = PORT_PIN_PULL_NONE;
	pin_conf.powersave = false;
	port_pin_set_config(PIN_PA12, &pin_conf);
	port_pin_set_output_level(PIN_PA12, false);
	
	ac_get_config_defaults(&conf_ac);
	ac_init(&ac_instance, AC, &conf_ac);
	
	conf_ac_channel.sample_mode = AC_CHAN_MODE_CONTINUOUS;
	conf_ac_channel.filter = AC_CHAN_FILTER_NONE;
	conf_ac_channel.enable_hysteresis = false;
	conf_ac_channel.output_mode = AC_CHAN_OUTPUT_INTERNAL;
	conf_ac_channel.positive_input = AC_CHAN_POS_MUX_PIN0;
	conf_ac_channel.negative_input = AC_CHAN_NEG_MUX_SCALED_VCC;
	/* Window upper threshold 0.7734V */
	conf_ac_channel.vcc_scale_factor = 14+1;
	conf_ac_channel.interrupt_selection = AC_CHAN_INTERRUPT_SELECTION_TOGGLE;
	ac_chan_set_config(&ac_instance, AC_CHAN_CHANNEL_0, &conf_ac_channel);
	
	/* Window lower threshold 0.2578V */
	conf_ac_channel.vcc_scale_factor = 4+1;
	ac_chan_set_config(&ac_instance, AC_CHAN_CHANNEL_1, &conf_ac_channel);
	
	ac_chan_enable(&ac_instance, AC_CHAN_CHANNEL_0);
	ac_chan_enable(&ac_instance, AC_CHAN_CHANNEL_1);
	
	conf_ac_win.interrupt_selection = AC_WIN_INTERRUPT_SELECTION_OUTSIDE;
	ac_win_set_config(&ac_instance, AC_WIN_CHANNEL_0, &conf_ac_win);
	ac_win_enable(&ac_instance, AC_WIN_CHANNEL_0);
	
	ac_register_callback(&ac_instance, ac_detect_callback, \
							AC_CALLBACK_WINDOW_0);
	ac_enable_callback(&ac_instance, AC_CALLBACK_WINDOW_0);
	
	ac_enable(&ac_instance);

}

/* AC SleepWalking application */
#elif (AC_MODE == AC_SLEEP_WALKING)

/* Analog comparator detect callback function */
void ac_detect_callback(struct ac_module *const module_inst)
{
	port_pin_toggle_output_level(PIN_PA12);
}

/* Event system configuration */
void configure_event(void)
{
	struct events_config conf_event;
	events_get_config_defaults(&conf_event);
	conf_event.generator = EVSYS_ID_GEN_RTC_OVF;
	conf_event.edge_detect = EVENTS_EDGE_DETECT_NONE;
	conf_event.path       = EVENTS_PATH_ASYNCHRONOUS;
	
	events_allocate(&resource, &conf_event);
	events_attach_user(&resource, EVSYS_ID_USER_AC_SOC_0);
}

/* RTC configuration */
void configure_rtc(void)
{
	struct rtc_count_config conf_rtc_count;
	struct rtc_count_events conf_rtc_events = {0};
	
	rtc_count_get_config_defaults(&conf_rtc_count);
	conf_rtc_count.prescaler  = RTC_COUNT_PRESCALER_DIV_1;
	conf_rtc_count.mode       = RTC_COUNT_MODE_16BIT;
	conf_rtc_count.continuously_update =  true;
	rtc_count_init(&rtc_instance, RTC, &conf_rtc_count);
	rtc_count_set_period(&rtc_instance, 10);
	conf_rtc_events.generate_event_on_overflow = true;
	
	rtc_count_enable_events(&rtc_instance, &conf_rtc_events);
	rtc_count_enable(&rtc_instance);
}

/* Analog comparator configuration function */
void configure_ac(void)
{
	struct ac_config conf_ac;
	struct ac_events conf_ac_events = {{0}};
	
	struct ac_chan_config conf_ac_channel;
	struct port_config pin_conf;
	
	pin_conf.direction = PORT_PIN_DIR_OUTPUT;
	pin_conf.input_pull = PORT_PIN_PULL_NONE;
	pin_conf.powersave = false;
	port_pin_set_config(PIN_PA12, &pin_conf);
	port_pin_set_output_level(PIN_PA12, false);
	
	ac_get_config_defaults(&conf_ac);
	conf_ac.run_in_standby[0] = true;
	conf_ac.dig_source_generator = GCLK_GENERATOR_1;
	ac_init(&ac_instance, AC, &conf_ac);
	
	conf_ac_channel.sample_mode = AC_CHAN_MODE_SINGLE_SHOT;
	conf_ac_channel.filter = AC_CHAN_FILTER_NONE;
	conf_ac_channel.enable_hysteresis = false;
	conf_ac_channel.output_mode = AC_CHAN_OUTPUT_INTERNAL;
	conf_ac_channel.positive_input = AC_CHAN_POS_MUX_PIN0;
	conf_ac_channel.negative_input = AC_CHAN_NEG_MUX_SCALED_VCC;
	/* Detect threshold 0.515625V */
	conf_ac_channel.vcc_scale_factor = 9+1;
	conf_ac_channel.interrupt_selection = AC_CHAN_INTERRUPT_SELECTION_TOGGLE;
	ac_chan_set_config(&ac_instance, AC_CHAN_CHANNEL_0, &conf_ac_channel);
	ac_chan_enable(&ac_instance, AC_CHAN_CHANNEL_0);
	
	conf_ac_events.on_event_sample[0] = true;
	ac_enable_events(&ac_instance ,&conf_ac_events);
	
	ac_enable(&ac_instance);
	
	ac_register_callback(&ac_instance, ac_detect_callback, \
							AC_CALLBACK_COMPARATOR_0);
	ac_enable_callback(&ac_instance, AC_CALLBACK_COMPARATOR_0);
}
#endif

/* main function */
int main (void)
{
	/* Initialize the system - clock, board, 
	   external interrupt and event system driver */
	system_init();
	/* Configure Analog Comparator based on selected mode */
	configure_ac();
	/* Initialize RTC and event system if selected mode is SleepWalking */
#if (AC_MODE == AC_SLEEP_WALKING)
	configure_rtc();
	configure_event();
	/* Set device sleep mode as standby sleep */
	system_set_sleepmode(SYSTEM_SLEEPMODE_STANDBY);
#endif
	
	/* while(1) loop */
	while (1) {
		/* If selected mode is window detector mode then perform pin toggle
		   based on window status */
		#if (AC_MODE == AC_WINDOW_DETECTOR)
		
		while(!out_of_window);
		out_of_window = false;
		if (ac_win_get_status(&ac_instance, AC_WIN_CHANNEL_0) == \
				AC_WIN_STATUS_ABOVE) {
			port_pin_set_output_level(PIN_PA12, true);
			while(ac_win_get_status(&ac_instance, AC_WIN_CHANNEL_0) == \
					AC_WIN_STATUS_ABOVE);
			port_pin_set_output_level(PIN_PA12, false);
		}
		else if (ac_win_get_status(&ac_instance, AC_WIN_CHANNEL_0) == \
					AC_WIN_STATUS_BELOW) {
			port_pin_set_output_level(PIN_PA12, true);
			while(ac_win_get_status(&ac_instance, AC_WIN_CHANNEL_0) == \
					AC_WIN_STATUS_BELOW);
			port_pin_set_output_level(PIN_PA12, false);
		}
		
		/* Else if selected mode is SleepWalking mode make the device
		   to enter into standby sleep mode */
		#elif (AC_MODE == AC_SLEEP_WALKING)
		system_sleep();
		#endif
		
		/* For other modes do nothing inside while(1) loop */
	}
}
