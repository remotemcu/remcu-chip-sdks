/**
 * \file
 * 
 * \brief SAM L22 TCC Features Example Application
 *        Refer following application note for details.
 *        AT10842-Using the Timer Counter for Control Applications in SAML22.
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
 /**
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include "string.h"
#include "conf_example.h"

struct tcc_module tcc_instance;
enum status_code stat = STATUS_OK;

#ifdef TCC_MODE_PATTERN_GENERATION
// Generic Pattern for half size Bipolar Stepper Motor.
uint8_t sm_pattern[PATTERN_SIZE] = {8, 2, 4, 1};
uint8_t iIndex = 0;
#endif

#ifdef TCC_MODE_FAULT 
//! [events_resource]
struct events_resource event_resource;
#endif

#ifdef TCC_MODE_COUNTER
//counter callback to toggle LED.
static void tcc_callback_to_toggle_led(struct tcc_module *const module_inst);
#endif

#ifdef  TCC_MODE_FAULT 
// configure event, for event trigger.
static void configure_event(void);
#endif

#ifdef TCC_MODE_FAULT
static void configure_eic(void);
static void eic_callback_to_fault_detect(void);
#endif

#ifdef  TCC_MODE_CAPTURE
void configure_usart(void);
void configu_eic(void);
void configu_tcc(void);
void configure_evsys (void);
#endif

//////////////////// END OF FUNCTION DECLARATION ////////////////////////////

/* 
 * Description: This example project helps you to configure the TCC Module
 * for different Features/Modes available in TCC module of SAML22 
 */
  
/* Configure the TCC module as per the application requirement */

/* Example -1.  Circular Buffer
			2.  Oneshot Operation 
			3.  Pattern Generation
			4.  PWM with OTMX(Output Matrix) and DTI(Dead Time Insertion) 
			5.  RAMP2 Operation
			6.  SWAP Operation
			----Added for Revision 2 of TCC App Note!!!.
			7.  RAMP2A Operation
			8.  Dual Slope Operation
			9.  DITHERING
			10. FAULT Operation
			11. CAPTURE Operation
			12. COUNTER Operation
*/

/*
 * PWM Waveforms are generated for most of the features based on the feature
 * selected by user.The waveform output will match the expected waveform 
 * desired for the feature chosen by the user.Below are some special features
 * which needs special mention in which the feature is demonstrated based on
 * other characteristics like LED state/ USART output. 

 * 1. FAULT Operation - On a button press toggle the Fault Line is toggled to 
 * trigger/clear fault.The LED state indicates the Fault is available or 
 * cleared.
 * 2. COUNTER Operation -> The LED toggles at different speed to indicate 
 * different triggered events based on different counter values. For counter
 * there won't be any waveform generation.
 * 3. CAPTURE Operation -> This captures a fixed waveform and displays the 
 * captured waveform results to indicate the different period captured is 
 * one of the period values of the PWM waveform. The captured period values are
 * displayed using USART of 96008N1 serial configuration 
 */

#ifdef TCC_MODE_CAPTURE
/* 
 * Function to configure usart, eic,tcc and event system. 
 * configures the usart with CONF_BAUD_RATE baud rate.
 */
struct usart_module usart_instances;
struct tcc_module tcc_instances;
struct events_resource event_resources;

uint32_t period, pulse_width;

void configure_usart(void)
{
	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);
	config_usart.baudrate                 = 115200;
	config_usart.mux_setting              = EDBG_CDC_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0              = EDBG_CDC_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1              = EDBG_CDC_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2              = EDBG_CDC_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3              = EDBG_CDC_SERCOM_PINMUX_PAD3;
	stdio_serial_init(&usart_instances,EDBG_CDC_MODULE, &config_usart);
	usart_enable(&usart_instances);
}

void configu_eic(void)
{
	struct extint_chan_conf config_extint_chan;
	extint_chan_get_config_defaults(&config_extint_chan);
	config_extint_chan.gpio_pin           = PIN_PA07A_EIC_EXTINT7;
	config_extint_chan.gpio_pin_mux       = MUX_PA07A_EIC_EXTINT7;
	config_extint_chan.gpio_pin_pull      = EXTINT_PULL_NONE;
	config_extint_chan.detection_criteria = EXTINT_DETECT_HIGH;
	extint_chan_set_config(7, &config_extint_chan);
	struct extint_events config_events = {
		.generate_event_on_detect[7] = true
	};
	extint_enable_events(&config_events);
}

void configu_tcc(void)
{
	struct tcc_config config_tcc;
	tcc_get_config_defaults(&config_tcc, TCC0);
	config_tcc.counter.clock_source         = GCLK_GENERATOR_3;
	config_tcc.counter.clock_prescaler      = TCC_CLOCK_PRESCALER_DIV1;
	config_tcc.compare.channel_function[0]  = TCC_CHANNEL_FUNCTION_CAPTURE;
	config_tcc.compare.channel_function[1]  = TCC_CHANNEL_FUNCTION_CAPTURE;
	config_tcc.compare.channel_function[2]  = TCC_CHANNEL_FUNCTION_CAPTURE;
	config_tcc.compare.channel_function[3]  = TCC_CHANNEL_FUNCTION_CAPTURE;
	config_tcc.double_buffering_enabled     = false;
	tcc_init(&tcc_instances, TCC0, &config_tcc);

	struct tcc_events events_tcc = {
		.input_config[0].modify_action      = false,
		.input_config[1].modify_action      = true,
		.on_input_event_perform_action[1]   = true,
		.input_config[1].action             = TCC_EVENT1_ACTION_PULSE_WIDTH_PERIOD_CAPTURE,
	};
	tcc_enable_events(&tcc_instances, &events_tcc);
	tcc_enable(&tcc_instances);
}

void configure_evsys(void)
{
	struct events_config config;
	events_get_config_defaults(&config);
	config.clock_source = GCLK_GENERATOR_3;
	config.generator    = EVSYS_ID_GEN_EIC_EXTINT_7;
	config.path         = EVENTS_PATH_ASYNCHRONOUS;
	config.edge_detect  = EVENTS_EDGE_DETECT_BOTH;
	events_allocate(&event_resources, &config);
	events_attach_user(&event_resources, EVSYS_ID_USER_TCC0_EV_1);
}
#endif

/* 
 * Function to configure TCC, this will configure TCC for other than Capture,
 * Counter and Fault mode related operations.
 */
void configure_tcc(void)
{
// Structure used to store the TCC configuration parameters
	struct tcc_config config_tcc;

// Fill the Structure with the default values
	tcc_get_config_defaults(&config_tcc, CONF_PWM_MODULE);
	config_tcc.compare.match[TCC_MATCH_CAPTURE_CHANNEL_0]   = CONF_DEFAULT_MATCH_COMPARE;
	config_tcc.counter.period                               = CONF_DEFAULT_PERIOD;

#ifdef TCC_MODE_DUAL_SLOPE
	config_tcc.compare.wave_generation = TCC_WAVE_GENERATION_DOUBLE_SLOPE_TOP;
#elif defined (TCC_MODE_COUNTER)
// Configure different channels with different compare match values
	config_tcc.compare.match[TCC_MATCH_CAPTURE_CHANNEL_0]   =  TCC_MODE_COUNTER_MATCH_0;
	config_tcc.compare.match[TCC_MATCH_CAPTURE_CHANNEL_1]   =  TCC_MODE_COUNTER_MATCH_1;
	config_tcc.compare.match[TCC_MATCH_CAPTURE_CHANNEL_2]   = TCC_MODE_COUNTER_MATCH_2;
	config_tcc.compare.match[TCC_MATCH_CAPTURE_CHANNEL_3]   = TCC_MODE_COUNTER_MATCH_3;
// Configure the value for TOP value.
	config_tcc.counter.period                               = TCC_PERIOD_VALUE;
#else
// Configure the single slope PWM waveform generation for waveform output.
	config_tcc.compare.wave_generation                      = TCC_WAVE_GENERATION_SINGLE_SLOPE_PWM;
#endif
// Configure the TCC clock source and its divider value.
	config_tcc.counter.clock_source                         = GLCK_SOURCE;
	config_tcc.counter.clock_prescaler                      = TCC_CLOCK_DIVIDER;

#if defined (TCC_MODE_CIRCULAR_BUFFER) || defined (TCC_MODE_DUAL_SLOPE) || defined (TCC_MODE_DITHERING) || defined (TCC_MODE_FAULT) 
// Configure the TCC Waveform Output pins for waveform generation output
	config_tcc.pins.enable_wave_out_pin[TCC_MATCH_CAPTURE_CHANNEL_0]    = true;
	config_tcc.pins.wave_out_pin[TCC_MATCH_CAPTURE_CHANNEL_0]           = PIN_PB18F_TCC0_WO0;
// Configure the Alternate function of GPIO pins for TCC functionality.
	config_tcc.pins.wave_out_pin_mux[TCC_MATCH_CAPTURE_CHANNEL_0]       = MUX_PB18F_TCC0_WO0;
#endif

#ifdef TCC_MODE_ONESHOT
// Configure the TCC Waveform Output pins for waveform generation output
	config_tcc.pins.enable_wave_out_pin[TCC_CHANNEL_NUM_3]  = true;
	config_tcc.pins.wave_out_pin[TCC_CHANNEL_NUM_3]         = PIN_PC27F_TCC0_WO3;
// Configure the alternate function of GPIO pins for TCC functionality
	config_tcc.pins.wave_out_pin_mux[TCC_CHANNEL_NUM_3]     = MUX_PC27F_TCC0_WO3;
// Configure the Match value for the compare channel 2 for LED0 ON time
	config_tcc.compare.match[TCC_MATCH_CAPTURE_CHANNEL_2]   = 31250;
	config_tcc.counter.period                               = TCC_PERIOD_VALUE;
	config_tcc.counter.clock_source                         = GLCK_SOURCE;
	config_tcc.counter.clock_prescaler                      = TCC_CLOCK_DIVIDER;
// Invert the Waveform output[6] channel to drive LED0
	config_tcc.wave_ext.invert[TCC_CHANNEL_NUM_3]           = true;
// Enable the One shot Feature
	config_tcc.counter.oneshot                              = true;
#endif

#ifdef TCC_MODE_OTMX_DTI
// Configure the TCC Waveform Output pins for waveform generation output
	config_tcc.pins.enable_wave_out_pin[TCC_CHANNEL_NUM_0]  = true;
	config_tcc.pins.enable_wave_out_pin[TCC_CHANNEL_NUM_1]  = true;
	config_tcc.pins.enable_wave_out_pin[TCC_CHANNEL_NUM_2]  = true;
	config_tcc.pins.enable_wave_out_pin[TCC_CHANNEL_NUM_6]  = true;
	config_tcc.pins.wave_out_pin[TCC_CHANNEL_NUM_0]         = PIN_PB18F_TCC0_WO0;
	config_tcc.pins.wave_out_pin[TCC_CHANNEL_NUM_1]         = PIN_PA09E_TCC0_WO1;
	config_tcc.pins.wave_out_pin[TCC_CHANNEL_NUM_2]         = PIN_PA18F_TCC0_WO2;
	config_tcc.pins.wave_out_pin[TCC_CHANNEL_NUM_6]         = PIN_PA12F_TCC0_WO6;
// Configure the Alternate function of GPIO pins for TCC functionality
	config_tcc.pins.wave_out_pin_mux[TCC_CHANNEL_NUM_0]     = MUX_PB18F_TCC0_WO0;
	config_tcc.pins.wave_out_pin_mux[TCC_CHANNEL_NUM_1]     = MUX_PA09E_TCC0_WO1;
	config_tcc.pins.wave_out_pin_mux[TCC_CHANNEL_NUM_2]     = MUX_PA18F_TCC0_WO2;
	config_tcc.pins.wave_out_pin_mux[TCC_CHANNEL_NUM_6]     = MUX_PA12F_TCC0_WO6;
/* 
 * Configure the compare channel values for the duty cycle control 
 * Load the 0x80 value for 50% duty cycle 
 */
	config_tcc.counter.period = TCC_PERIOD_VALUE;
	config_tcc.compare.match[TCC_MATCH_CAPTURE_CHANNEL_0]   = TCC_PERIOD_VALUE/2;
	config_tcc.compare.match[TCC_MATCH_CAPTURE_CHANNEL_1]   = TCC_PERIOD_VALUE/2;
	config_tcc.compare.match[TCC_MATCH_CAPTURE_CHANNEL_2]   = TCC_PERIOD_VALUE/2;
// Invert the Waveform output[1] channel to view the DTI effect
	config_tcc.wave_ext.invert[TCC_CHANNEL_NUM_1]           = true;
#endif

#ifdef TCC_MODE_SWAP
// Configure the TCC Waveform Output pins for waveform generation output 
	config_tcc.pins.enable_wave_out_pin[TCC_CHANNEL_NUM_0]  = true;
	config_tcc.pins.enable_wave_out_pin[TCC_CHANNEL_NUM_4]  = true;
	config_tcc.pins.wave_out_pin[TCC_CHANNEL_NUM_0]         = PIN_PA04E_TCC0_WO0;
	config_tcc.pins.wave_out_pin[TCC_CHANNEL_NUM_4]         = PIN_PA22F_TCC0_WO4;
// Configure the alternate function of GPIO pins for TCC functionality
	config_tcc.pins.wave_out_pin_mux[TCC_CHANNEL_NUM_0]     = MUX_PA04E_TCC0_WO0;
	config_tcc.pins.wave_out_pin_mux[TCC_CHANNEL_NUM_4]     = MUX_PA22F_TCC0_WO4;
/* 
 * Configure the compare channel values for the duty cycle control
 * Load the 0x80 value for 50% duty cycle
 */
	config_tcc.compare.match[TCC_MATCH_CAPTURE_CHANNEL_0]   = 0X80;
#endif

#ifdef TCC_MODE_PATTERN_GENERATION
	config_tcc.counter.period                               = TCC_PERIOD_VALUE;
// Configure the TCC Waveform Output pins for waveform generation output
	config_tcc.pins.enable_wave_out_pin[TCC_CHANNEL_NUM_0]  = true;
	config_tcc.pins.enable_wave_out_pin[TCC_CHANNEL_NUM_1]  = true;
	config_tcc.pins.enable_wave_out_pin[TCC_CHANNEL_NUM_2]  = true;
	config_tcc.pins.enable_wave_out_pin[TCC_CHANNEL_NUM_3]  = true;
	config_tcc.pins.wave_out_pin[TCC_CHANNEL_NUM_0]         = PIN_PB18F_TCC0_WO0;
	config_tcc.pins.wave_out_pin[TCC_CHANNEL_NUM_1]         = PIN_PA09E_TCC0_WO1;
	config_tcc.pins.wave_out_pin[TCC_CHANNEL_NUM_2]         = PIN_PA18F_TCC0_WO2;
	config_tcc.pins.wave_out_pin[TCC_CHANNEL_NUM_3]         = PIN_PB21F_TCC0_WO3;
// Configure the Alternate function of GPIO pins for TCC functionality
	config_tcc.pins.wave_out_pin_mux[TCC_CHANNEL_NUM_0]     = MUX_PB18F_TCC0_WO0;
	config_tcc.pins.wave_out_pin_mux[TCC_CHANNEL_NUM_1]     = MUX_PA09E_TCC0_WO1;
	config_tcc.pins.wave_out_pin_mux[TCC_CHANNEL_NUM_2]     = MUX_PA18F_TCC0_WO2;
	config_tcc.pins.wave_out_pin_mux[TCC_CHANNEL_NUM_3]     = MUX_PB21F_TCC0_WO3;
	config_tcc.double_buffering_enabled                     = true;
/* 
 * Configure the compare channel values for the duty cycle control 
 * Load the 0x7FFF value for 50% duty cycle
 */
	config_tcc.compare.match[TCC_MATCH_CAPTURE_CHANNEL_0]   = TCC_MATCH_VALUE_PATTERN_GEN;
#endif

#ifdef TCC_MODE_RAMP2
// Configure the TCC Waveform Output pins for waveform generation output
	config_tcc.pins.enable_wave_out_pin[TCC_CHANNEL_NUM_0]  = true;
	config_tcc.pins.enable_wave_out_pin[TCC_CHANNEL_NUM_1]  = true;
	config_tcc.pins.wave_out_pin[TCC_CHANNEL_NUM_0]         = PIN_PB18F_TCC0_WO0;
	config_tcc.pins.wave_out_pin[TCC_CHANNEL_NUM_1]         = PIN_PA09E_TCC0_WO1;
// Configure the Alternate function of GPIO pins for TCC functionality
	config_tcc.pins.wave_out_pin_mux[TCC_CHANNEL_NUM_0]     = MUX_PB18F_TCC0_WO0;
	config_tcc.pins.wave_out_pin_mux[TCC_CHANNEL_NUM_1]     = MUX_PA09E_TCC0_WO1;
// Configure the RAMP mode operation as RAMP2 mode
	config_tcc.compare.wave_ramp                            = TCC_RAMP_RAMP2;
/* 
 * Configure the compare channel values for the duty cycle control
 * Load the 0xB333 value for 70% duty cycle 
 */
	config_tcc.compare.match[TCC_MATCH_CAPTURE_CHANNEL_0]   = TCC_RAMP2_MATCH_CHANNEL_0;
// Load the 0x4CCC value for 30% duty cycle
	config_tcc.compare.match[TCC_MATCH_CAPTURE_CHANNEL_1]   = TCC_RAMP2_MATCH_CHANNEL_1;
	config_tcc.counter.period                               = TCC_PERIOD_VALUE;
#endif

#ifdef TCC_MODE_RAMP2A
// Configure the TCC Waveform Output pins for waveform generation output
	config_tcc.pins.enable_wave_out_pin[TCC_CHANNEL_NUM_0]  = true;
	config_tcc.pins.enable_wave_out_pin[TCC_CHANNEL_NUM_1]  = true;
	config_tcc.pins.wave_out_pin[TCC_CHANNEL_NUM_0]         = PIN_PB18F_TCC0_WO0;
	config_tcc.pins.wave_out_pin[TCC_CHANNEL_NUM_1]         = PIN_PA09E_TCC0_WO1;
// Configure the Alternate function of GPIO pins for TCC functionality
	config_tcc.pins.wave_out_pin_mux[TCC_CHANNEL_NUM_0]     = MUX_PB18F_TCC0_WO0;
	config_tcc.pins.wave_out_pin_mux[TCC_CHANNEL_NUM_1]     = MUX_PA09E_TCC0_WO1;
// Configure the RAMP mode operation as RAMP2A mode
	config_tcc.compare.wave_ramp                            = TCC_RAMP_RAMP2A;
/* 
 * Configure the compare channel values for the duty cycle control
 * Load the 0xB333 value for 70% duty cycle 
 */
	config_tcc.compare.match[TCC_MATCH_CAPTURE_CHANNEL_0]   = TCC_RAMP2_MATCH_CHANNEL_0;
	config_tcc.counter.period                               = TCC_PERIOD_VALUE;
#endif

#ifdef TCC_MODE_FAULT
	config_tcc.wave_ext.recoverable_fault[TCC_CHANNEL_NUM_0].source      = TCC_FAULT_SOURCE_ENABLE;
	config_tcc.wave_ext.recoverable_fault[TCC_CHANNEL_NUM_0].halt_action = TCC_FAULT_HALT_ACTION_SW_HALT;
#endif

#ifdef TCC_MODE_CIRCULAR_BUFFER
// Configure the value for TOP value
	config_tcc.counter.period                               = TCC_PERIOD_VALUE;
	config_tcc.compare.match[TCC_MATCH_CAPTURE_CHANNEL_0]   = TCC_PERIOD_VALUE;
#endif

/* 
 * Initialize the TCC0 channel and define the its registers with 
 * configuration defined in the config_tcc 
 */
	stat = tcc_init(&tcc_instance, CONF_PWM_MODULE, &config_tcc);

// The main configuration for Circular Buffering
#ifdef TCC_MODE_CIRCULAR_BUFFER	
/* 
 * Load the CC0 and CCB0 values respectively for the 
 * circular buffer operation 
 */
	stat = tcc_set_double_buffer_compare_values(&tcc_instance, TCC_MATCH_CAPTURE_CHANNEL_0, CC0_Value, CCB0_Value);
// Enable the Circular Buffer feature for the Compare Channel 0
	stat = tcc_enable_circular_buffer_compare(&tcc_instance, TCC_MATCH_CAPTURE_CHANNEL_0);
#endif

// The main configuration for Dead time Insertion
#ifdef TCC_MODE_OTMX_DTI
// Enable the Dead Time Insertion Generator for the channel 2 (CC2)
	CONF_PWM_MODULE->WEXCTRL.reg |=  TCC_WEXCTRL_DTIEN2;
// Define the High side time and Low side time for Dead Time generation 
	CONF_PWM_MODULE->WEXCTRL.reg |= TCC_WEXCTRL_DTLS(DTI_LOW_TIME) | TCC_WEXCTRL_DTHS(DTI_HIGH_TIME);
#endif

// The main configuration for PATTERN GENERATION
#ifdef TCC_MODE_PATTERN_GENERATION
/* 
 * Configure the Output Matrix Channel for Pattern Generation of 
 * Stepper Motor 
 */
	CONF_PWM_MODULE->WEXCTRL.reg |= TCC_WEXCTRL_OTMX(2);
/* 
 * Enable the Pattern Generator Output for 4 Waveform Outputs and 
 * Load the PATT and PATTB register values respectively for Stepper Motor 
 * Pattern Generation 
 */
	CONF_PWM_MODULE->PATT.reg = TCC_PATT_PGE(TCC_PATTERN_PAGE_VAL) | TCC_PATT_PGV(sm_pattern[iIndex++]);
	while (CONF_PWM_MODULE->SYNCBUSY.reg & TCC_SYNCBUSY_PATT);
	CONF_PWM_MODULE->PATTBUF.reg = TCC_PATTBUF_PGEB(TCC_PATTERN_PAGE_VAL) | TCC_PATTBUF_PGVB(sm_pattern[iIndex++]);
	while (CONF_PWM_MODULE->SYNCBUSY.reg & (1u << 16));
#endif

// The main configuration for SWAP
#ifdef TCC_MODE_SWAP
// Enable the Dead Time Insertion Generator for the channel 0 (CC0)
	CONF_PWM_MODULE->WEXCTRL.reg |=  TCC_WEXCTRL_DTIEN0;
// Define the High side time and Low side time for Dead Time generation
	CONF_PWM_MODULE->WEXCTRL.reg |= TCC_WEXCTRL_DTLS(TCC_SWAP_DT_LS) | TCC_WEXCTRL_DTHS(TCC_SWAP_DT_HS);
#endif

// The main configuration for DITHERING
#ifdef TCC_MODE_DITHERING
	CONF_PWM_MODULE->CTRLA.bit.RESOLUTION = DITH_CYCLES;
	while (CONF_PWM_MODULE->SYNCBUSY.reg & TCC_SYNCBUSY_CTRLB) {
		// Wait for sync
	}
#endif

#ifdef TCC_MODE_FAULT
	struct tcc_events events;
	memset(&events, 0, sizeof(struct tcc_events));
	events.on_event_perform_channel_action[TCC_MATCH_CAPTURE_CHANNEL_0] = true;
	tcc_enable_events(&tcc_instance, &events);
#endif

// Enable the TCC module 
	tcc_enable(&tcc_instance);
	tcc_restart_counter(&tcc_instance);
}

/*
 * This Function loads the Stepper Motor Pattern into the Pattern Buffer 
 * register respectively in the PGVB continuously. Please note that here 
 * we have not added any delay between the pattern on the wave output pin. 
 * Hence please add the appropriate delay before load the pattern into 
 * Pattern Generation Value Buffer (PGVB register) as mentioned 
 * in the stepper motor  datasheet
 */

#ifdef TCC_MODE_PATTERN_GENERATION
void pattern_generation(void)
{
	if (iIndex == PATTERN_SIZE) {
		iIndex = 0;
	}
	while (!(TCC0->INTFLAG.reg & TCC_INTFLAG_MC0)); 
	CONF_PWM_MODULE->INTFLAG.reg = TCC_INTFLAG_MC0; //TCC0->INTFLAG.bit.MC0 = 1; 
	CONF_PWM_MODULE->PATTBUF.reg = TCC_PATTBUF_PGEB(TCC_PATTERN_PAGE_VAL) | TCC_PATTBUF_PGVB(sm_pattern[iIndex++]);
	while (CONF_PWM_MODULE->SYNCBUSY.reg & (1u << 16));
}
#endif

/*
 * This function Waits for the user input(Button Press) BUTTON_0_PIN 
 * then clears the counter value and restart the counter for the 
 * Oneshot Operation 
 */

#ifdef TCC_MODE_ONESHOT
void oneshot_operation(void)
{
	while (port_pin_get_input_level(BUTTON_0_PIN)) {
	}
	while (!port_pin_get_input_level(BUTTON_0_PIN)){
	}
	tcc_set_count_value(&tcc_instance, 0);
	tcc_restart_counter(&tcc_instance);
}
#endif


/* 
 * This function waits for the user input(Button Press) BUTTON_0_PIN 
 * then toggles the SWAP bit for the SWAP continuously 
 */
#ifdef TCC_MODE_SWAP
void swap_operation(void)
{
	while (port_pin_get_input_level(BUTTON_0_PIN)) {
	}
	while (!port_pin_get_input_level(BUTTON_0_PIN)) {
	}
	CONF_PWM_MODULE->WAVE.reg ^= TCC_WAVE_SWAP0;
	while (CONF_PWM_MODULE->SYNCBUSY.reg & TCC_SYNCBUSY_WAVE) {
	}
}
#endif


#ifdef TCC_MODE_COUNTER
// This function will toggle the LED, when triggered
static void tcc_callback_to_toggle_led(struct tcc_module *const module_inst)
{
	port_pin_toggle_output_level(LED0_PIN);
}
#endif

#ifdef TCC_MODE_COUNTER
/*
 * This function will configure (register and enable)
 * the callback to be triggered on different TCC channels for overflow,
 * this is used to show case the TCC toggling the LED at different speed, 
 * because of variable time required for overflow on each TCC channel. 
 */
void configure_tcc_callback(void)
{

	//! [setup_register_callback]
	tcc_register_callback(&tcc_instance, tcc_callback_to_toggle_led, TCC_CALLBACK_OVERFLOW);
	tcc_register_callback(&tcc_instance, tcc_callback_to_toggle_led, TCC_CALLBACK_CHANNEL_0);
	tcc_register_callback(&tcc_instance, tcc_callback_to_toggle_led, TCC_CALLBACK_CHANNEL_1);
	tcc_register_callback(&tcc_instance, tcc_callback_to_toggle_led, TCC_CALLBACK_CHANNEL_2);
	tcc_register_callback(&tcc_instance, tcc_callback_to_toggle_led, TCC_CALLBACK_CHANNEL_3);
	//! [setup_enable_callback]
	tcc_enable_callback(&tcc_instance, TCC_CALLBACK_OVERFLOW);
	tcc_enable_callback(&tcc_instance, TCC_CALLBACK_CHANNEL_0);
	tcc_enable_callback(&tcc_instance, TCC_CALLBACK_CHANNEL_1);
	tcc_enable_callback(&tcc_instance, TCC_CALLBACK_CHANNEL_2);
	tcc_enable_callback(&tcc_instance, TCC_CALLBACK_CHANNEL_3);
	//! [setup_change_events_faults]
}
//! [setup]
#endif

#ifdef TCC_MODE_FAULT
//! [callback_eic]
/*
 * This function will be triggered, when fault/ gpio pin state is changed, 
 * based on which the test pin is driven high, this is used to detect that 
 * fault is cleared. 
 */

static void eic_callback_to_fault_detect(void)
{
	port_pin_set_output_level(CONF_TEST_PIN_OUT, true);
}
//! [callback_eic]

/*
 * This function is used to configure the gpio pin to act as a fault line and
 * to trigger when the gpio pin state changes
 * to identify fault is cleared. 
 */

static void configure_eic(void)
{
	struct extint_chan_conf config;
	struct extint_events events;
	extint_chan_get_config_defaults(&config);
	config.filter_input_signal  = true;
	config.detection_criteria   = EXTINT_DETECT_BOTH;
	config.gpio_pin             = CONF_FAULT_EIC_PIN;
	config.gpio_pin_mux         = CONF_FAULT_EIC_PIN_MUX;
	extint_chan_set_config(CONF_FAULT_EIC_LINE, &config);
	memset(&events, 0, sizeof(struct extint_events));
	events.generate_event_on_detect[CONF_FAULT_EIC_LINE] = true;
	extint_enable_events(&events);
	extint_register_callback(eic_callback_to_fault_detect, CONF_FAULT_EIC_LINE, EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_enable_callback(CONF_FAULT_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);
}
#endif

#ifdef TCC_MODE_FAULT
/*
 * This function is used to configure an event for fault mode.
 * In fault mode overflow of TCC is driven by external interrupt
 */
static void configure_event(void)
{
	struct events_config config;
	events_get_config_defaults(&config);
	config.generator = CONF_EVENT_GENERATOR_ID;
	config.path      = EVENTS_PATH_ASYNCHRONOUS;
	events_allocate(&event_resource, &config);
	events_attach_user(&event_resource, CONF_FAULT_EVENT_USER);
}
#endif

///////////START OF MAIN ENTRY//////////////////////////////////////////

int main (void)
{
#ifdef TCC_MODE_FAULT
	uint32_t tcStatus = 0;
	unsigned long temp = TCC_STATUS_RECOVERABLE_FAULT_OCCUR(0);
	struct port_config config_pin;
	port_get_config_defaults(&config_pin);
	config_pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(CONF_TEST_PIN_OUT, &config_pin);
	port_pin_set_output_level(CONF_TEST_PIN_OUT, true); 
#endif

// system initialization - includes, clock and board initialization.
	system_init();
	system_interrupt_enable_global();

#ifdef TCC_MODE_CAPTURE
	configu_tcc();
#else
	configure_tcc();
#endif

#ifdef TCC_MODE_COUNTER
	configure_tcc_callback();
#elif defined (TCC_MODE_FAULT)
	configure_eic();
	configure_event();
	tcc_clear_status(&tcc_instance,TCC_STATUS_RECOVERABLE_FAULT_OCCUR(0));
#endif

	while (1){
#ifdef TCC_MODE_ONESHOT
		oneshot_operation();
#endif

#ifdef TCC_MODE_PATTERN_GENERATION
		pattern_generation();
#endif

#ifdef TCC_MODE_SWAP
		swap_operation();
#endif

#ifdef TCC_MODE_FAULT 
		if (!port_pin_get_input_level(SW0_PIN)){
			// Set fault 
			while (!port_pin_get_input_level(SW0_PIN));
			port_pin_set_output_level(CONF_TEST_PIN_OUT, false);
			tcStatus = tcc_get_status(&tcc_instance);
			if (!port_pin_get_output_level(LED_0_PIN)){
				// Turn off LED and clear alarm status..
				tcc_clear_status(&tcc_instance,TCC_STATUS_RECOVERABLE_FAULT_OCCUR(0));
				LED_Off(LED_0_PIN);
			}else if ((tcStatus & temp) == temp){
				// If alarm set, drive LED.
				LED_On(LED_0_PIN);
				port_pin_set_output_level(CONF_TEST_PIN_OUT, true);
			}
		} // end of common fault and capture condition
#endif

#ifdef TCC_MODE_CAPTURE
		configure_usart();
		configu_eic();
		configure_evsys();
		while (1) {
			while(!(TCC0->INTFLAG.reg & TCC_INTFLAG_MC1));
			TCC0->INTFLAG.reg = TCC_INTFLAG_MC1;
			period                  = tcc_get_capture_value(&tcc_instances, 1);
			pulse_width             = tcc_get_capture_value(&tcc_instances, 0);
			printf("period=%ld , pulse width =%ld \r\n", period , pulse_width);
		}
#endif // end of while (1)
	}
}

