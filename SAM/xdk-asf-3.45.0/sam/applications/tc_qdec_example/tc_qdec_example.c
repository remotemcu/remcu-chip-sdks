/**
 * \file
 *
 * \brief TC Quadrature Decoder Example for SAM4E.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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
 * \mainpage TC Quadrature Decoder Example
 *
 * \section Purpose
 *
 * This example indicates how to use TC Quadrature Decoder features like 
 * position and Rotation measurement, Speed measurement, Direction status and 
 * change detection. 
 *
 * \section Requirements
 *
 * This package can be used with SAM4E-EK evaluation kit.
 * It Quadrature Encoder signal is fed to the TC PIN_TC_QDECx_PHA,
 * PIN_TC_QDECx_PHA, PIN_TC_QDECx_Index and it works as per the QDEC mode
 * configured. Look at the conf_example file to check these previous define.
 *
 * \section Usage
 *
 * -# Configure the required QDEC and respective mode to measure the Position,
 *    Rotation measurement, Speed measurement, Direction status and change detection.
 *    Connect the input signals in the mentioned pins and configure the
 *    following in the conf_example.h.
 *		1, select the required TC QDEC module by changing 'DISABLE' to 'ENABLE'
 *			Exp:-
 *				#define TC_QDEC0_ACTIVATION			DISABLE
 *				#define TC_QDEC1_ACTIVATION			ENABLE
 *		2, Select the TC QDEC mode for each QDEC (ie, QDEC0, QDEC1, QDEC2)
 *			Options:- TC_QDEC_MODE_POSITION (or) TC_QDEC_MODE_SPEED (or)
 *               TC_QDEC_MODE_TEST_BASETIMER.
 *			Exp:-
 *			#define  TC_QDEC0_mode TC_QDEC_MODE_POSITION
 *		Note :-
 *		This Example developed and tested for QDEC1 in SAM4E-EK only. 
 *		(other options provided for flexible porting for different evaluation kits).
 *		So enable TC_QDEC1 and select TC QDEC mode for QDEC1.
 * -# Compile the application.
 * -# Connect the UART port of the evaluation board to the computer and open
 *    it in a terminal.
 *    - Settings: 115200 bauds, 8 bits, 1 stop bit, no parity, no flow control.
 * -# Download the program into the evaluation board and run it.
 *
 */

#include "asf.h"
#include "conf_example.h"
#include "conf_board.h"
#include "conf_clock.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

#define STRING_EOL    "\r"
#define STRING_HEADER "--TC Quadrature Decoder Example --\r\n" \
		"-- "BOARD_NAME " --\r\n" \
		"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

#if (SAM4L)
/* The first one is meaningless */
static const uint32_t divisors[5] = { 0, 2, 8, 32, 128};
#else
/* The last one is meaningless */
static const uint32_t divisors[5] = { 2, 8, 32, 128, 0};
#endif

/**
 * \brief Configuration struct for the TCC module output pins
 *
 * Structure which is used to feed the QDEC signals
 */
struct tc_qdec_pins_config {
	/** Specifies input pin for each channel. */
	uint32_t qdec_input_pha_pin;
	/** Specifies input pin for each channel. */
	uint32_t qdec_input_pha_pin_mux;

	/** Specifies input pin for each channel. */
	uint32_t qdec_input_phb_pin;
	/** Specifies input pin for each channel. */
	uint32_t qdec_input_phb_pin_mux;

	/** Specifies input pin for each channel. */
	uint32_t qdec_input_index_pin;
	/** Specifies input pin for each channel. */
	uint32_t qdec_input_index_pin_mux;

	/** Specifies pin output for each channel. */
	uint32_t qdec_test_basetimer_out_pin;
	/** Specifies MUX setting for each output channel pin. */
	uint32_t qdec_test_basetimer_out_pin_mux;

	/** When \c true, PWM output pin for the given channel is enabled. */
	bool enable_qdec_test_wave_out_pin;
};

/**
 * \brief TC QDEC configuration structure
 *
 * Configuration struct for a TC qdec instance. 
 */
struct tc_qdec_config {
	/** enum for configuring TC QDEC instance */
	Tc *qdec;

	/** enum for configuring TC QDEC mode */
	enum tc_qdec_mode mode;
	
	/** enum for configuring TC QDEC channel id */	
	enum id_tc_qdec_channel channelid[ID_TC_QDEC_CHANNEL_MAX];	

	/** Structure for configuring TC QDEC output pins */
	struct tc_qdec_pins_config pins;
};

struct tc_qdec_config qdec_config[QDEC_INSTANCE_MAX] =
{
	{
		TC_QDEC0_INSTANCE,
		TC_QDEC0_MODE,
		{
			ID_TC_QDEC0_CHANNEL0,
			ID_TC_QDEC0_CHANNEL1,
			ID_TC_QDEC0_CHANNEL2
		},
		{
			PIN_TC_QDEC0_PHA,
			PIN_TC_QDEC0_PHA_MUX,
			PIN_TC_QDEC0_PHB,
			PIN_TC_QDEC0_PHB_MUX,
			PIN_TC_QDEC0_INDEX,
			PIN_TC_QDEC0_INDEX_MUX,
			PIN_TC_QDEC0_WAVEFORM,
			PIN_TC_QDEC0_WAVEFORM_MUX,
			true
		}
	},
	{
		TC_QDEC1_INSTANCE,
		TC_QDEC1_MODE,
		{
			ID_TC_QDEC1_CHANNEL0,
			ID_TC_QDEC1_CHANNEL1,
			ID_TC_QDEC1_CHANNEL2
		},
		{
			PIN_TC_QDEC1_PHA,
			PIN_TC_QDEC1_PHA_MUX,
			PIN_TC_QDEC1_PHB,
			PIN_TC_QDEC1_PHB_MUX,
			PIN_TC_QDEC1_INDEX,
			PIN_TC_QDEC1_INDEX_MUX,
			PIN_TC_QDEC1_WAVEFORM,
			PIN_TC_QDEC1_WAVEFORM_MUX,
			true
		}
	},
	{
		TC_QDEC2_INSTANCE,
		TC_QDEC2_MODE,
		{
			ID_TC_QDEC2_CHANNEL0,
			ID_TC_QDEC2_CHANNEL1,
			ID_TC_QDEC2_CHANNEL2
		},
		{
			PIN_TC_QDEC2_PHA,
			PIN_TC_QDEC2_PHA_MUX,
			PIN_TC_QDEC2_PHB,
			PIN_TC_QDEC2_PHB_MUX,
			PIN_TC_QDEC2_INDEX,
			PIN_TC_QDEC2_INDEX_MUX,
			PIN_TC_QDEC2_WAVEFORM,
			PIN_TC_QDEC2_WAVEFORM_MUX,
			true
		}
	}
};


/**
 * \brief TC QDEC configuration structure
 *
 * Configuration struct for a TC qdec instance. 
 */
struct tc_qdec_results {
	/** Variable for QDEC position value */
	int16_t qdec_cv0;
	/** Variable for QDEC Rotation value */
	int16_t qdec_cv1; 
	/** Variable for QDEC speed value */
	int16_t qdec_speed;
	/** Variable for QDEC direction value */
	bool qdec_dir;
};

/** current values of position, speed, direction*/
volatile struct tc_qdec_results qdec_results[QDEC_INSTANCE_MAX];

/**
 * \brief Display the user menu on the UART.
 */
static void display_menu(void)
{
	printf("-- TC QDEC Example for SAM4E-EK--\r\n");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);
	puts("---------------------------\r");

	if(qdec_config[QDEC_INSTANCE0].qdec){
		puts("Phase A connected to PA0\r");
		puts("Phase B connected to PA1\r");
		puts("Index   connected to PA16\r");
	}

	if(qdec_config[QDEC_INSTANCE1].qdec){
		puts("Phase A connected to PC23\r");
		puts("Phase B connected to PC24\r");
		puts("Index   connected to PC27\r");
	}
	if(qdec_config[QDEC_INSTANCE2].qdec){
		puts("Phase A connected to PC5\r");
		puts("Phase B connected to PC6\r");
		puts("Index   connected to PC9\r");
	}
	puts("---------------------------\r");
	puts("NOTE: Use 'TC_BMR_EDGPHA' bit filed in TC_BMR Register to count\r\n");
	puts("the pulses on Phase A and Phase B or Phase A alone.\n\r");
	
}

/**
* \brief configure TC QDEC IO pins.
*/
static void config_tc_qdec_iopins(
		Tc *const hw,
		const struct tc_qdec_config *const config)
{
	/* Connect the pin to the QDEC PHA input signal */
	ioport_set_pin_mode(config->pins.qdec_input_pha_pin, config->pins.qdec_input_pha_pin_mux);
	ioport_disable_pin(config->pins.qdec_input_pha_pin);

	/* Connect the pin to the QDEC PHB input signal */
	ioport_set_pin_mode(config->pins.qdec_input_phb_pin, config->pins.qdec_input_phb_pin_mux);
	ioport_disable_pin(config->pins.qdec_input_phb_pin);

	/* Connect the pin to the QDEC Index input signal */
	ioport_set_pin_mode(config->pins.qdec_input_index_pin, config->pins.qdec_input_index_pin_mux);
	ioport_disable_pin(config->pins.qdec_input_index_pin);
}

/**
* \brief configure TC QDEC for position mode.
*/
static void config_tc_qdec_mode_position(
		Tc *const hw,
		const struct tc_qdec_config *const config)
{
	/*Configure the TC QDEC IO Pins*/
	config_tc_qdec_iopins(hw,config);

	/*Enable the QDEC channel 0 clock*/
	sysclk_enable_peripheral_clock(config->channelid[ID_TC_QDEC_CHANNEL0]);
	/*Enable the QDEC channel 1 clock*/
	sysclk_enable_peripheral_clock(config->channelid[ID_TC_QDEC_CHANNEL1]);

	/* Init TC channel 0 to QDEC Position mode */
	tc_init(hw, 0,
		/* QDEC Clock Selection */
		TC_CMR_TCCLKS_XC0
		| TC_CMR_ETRGEDG_RISING /*To clear the counter on a rising edge of the TIOA signal*/
		| TC_CMR_ABETRG /*To select TIOA as a trigger for this channel 0 */
	);

	/* Init TC channel 1 to QDEC Rotation mode */
	tc_init(hw, 1,
		/* QDEC Clock Selection */
		TC_CMR_TCCLKS_XC0
	);

	/* Enable TC QDEC channel 0 in QDEC Position mode */
	tc_set_block_mode(hw, TC_BMR_QDEN /*  QDEC mode enabled */
		| TC_BMR_POSEN /* Position measure is enabled */
		| TC_BMR_EDGPHA /* Detect quadrature on both PHA and PHB (4X decoding)*/
		| (0<< TC_BMR_MAXFILT_Pos) /* enable filter on input signal*/
	);
}

/**
* \brief configure TC QDEC for speed mode.
*/
static void config_tc_qdec_mode_speed(
		Tc *const hw,
		const struct tc_qdec_config *const config)
{
	volatile uint32_t qdec_rc=0;
	
	/*Configure the TC QDEC IO Pins*/
	config_tc_qdec_iopins(hw,config);

	/*Enable the QDEC channel 0 clock*/
	sysclk_enable_peripheral_clock(config->channelid[ID_TC_QDEC_CHANNEL0]);
	/*Enable the QDEC channel 1 clock*/
	sysclk_enable_peripheral_clock(config->channelid[ID_TC_QDEC_CHANNEL1]);
	/*Enable the QDEC channel 2 clock */
	sysclk_enable_peripheral_clock(config->channelid[ID_TC_QDEC_CHANNEL2]);

	/* Init TC channel 0 to QDEC Position mode */
	tc_init(hw, 0,
		/* QDEC Clock Selection */
		TC_CMR_TCCLKS_XC0
		| TC_CMR_ETRGEDG_RISING /*To clear the counter on a rising edge of the TIOA signal*/
		| TC_CMR_ABETRG /*To select TIOA as a trigger for this channel 0 */
		| TC_CMR_LDRA_RISING /*To load TC_RA0 at the same time as the counter is cleared */
	);
	/* Init TC channel 1 to QDEC Rotation mode */
	tc_init(hw, 1,
		/* QDEC Clock Selection */
		TC_CMR_TCCLKS_XC0
	);

	/* Init TC channel 2 as a base timer for Speed measurement */
	tc_init(hw, 2,
		/* Waveform Clock Selection */
		TC_CMR_TCCLKS_TIMER_CLOCK4 | TC_CMR_WAVE
		| TC_CMR_WAVSEL_UP_RC /* Waveform mode is enabled */
		| TC_CMR_ACPC_TOGGLE /* RC Compare Effect: clear */
		| TC_CMR_CPCTRG /* UP mode with automatic trigger on RC Compare */
	);

	/* Configure waveform frequency and duty cycle. */
	qdec_rc = (sysclk_get_peripheral_bus_hz(hw));
	qdec_rc = qdec_rc / divisors[TC_CMR_TCCLKS_TIMER_CLOCK4] ;
	qdec_rc = qdec_rc * (4.0E-03); /*base time for x ms*/
	tc_write_rc(hw, 2, qdec_rc );

	/* Enable TC QDEC channel 0 in QDEC Speed mode */
	tc_set_block_mode(hw, TC_BMR_QDEN /*  QDEC mode enabled */
		| TC_BMR_SPEEDEN /* Speed measure is enabled */
		| TC_BMR_EDGPHA /* Detect quadrature on both PHA and PHB (4X decoding)*/
		| (0<< TC_BMR_MAXFILT_Pos) /* enable filter on input signal*/
	);
}

/**
* \brief configure TC QDEC for test_basetimer mode.
*/
static void config_tc_qdec_mode_test_basetimer(
		Tc *const hw,
		const struct tc_qdec_config *const config)
{
	volatile uint32_t qdec_rc=0;
	/* Test pin of QDEC base time wave out signal */
	if (config->pins.enable_qdec_test_wave_out_pin != false) {
		ioport_set_pin_mode(config->pins.qdec_test_basetimer_out_pin,
			config->pins.qdec_test_basetimer_out_pin_mux);
		ioport_disable_pin(config->pins.qdec_test_basetimer_out_pin);
	}

	/*Enable the QDEC channel 2 clock */
	sysclk_enable_peripheral_clock(config->channelid[ID_TC_QDEC_CHANNEL2]);

	/* Init TC channel 2 as a base timer for Speed measurement */
	tc_init(hw, 2,
		/* Waveform Clock Selection */
		TC_CMR_TCCLKS_TIMER_CLOCK4 | TC_CMR_WAVE
		| TC_CMR_WAVSEL_UP_RC /* Waveform mode is enabled */
		| TC_CMR_ACPC_TOGGLE /* RC Compare Effect: clear */
		| TC_CMR_CPCTRG /* UP mode with automatic trigger on RC Compare */
	);

	/* Configure waveform frequency and duty cycle. */
	qdec_rc = (sysclk_get_peripheral_bus_hz(hw));
	qdec_rc = qdec_rc / divisors[TC_CMR_TCCLKS_TIMER_CLOCK4] ;
	qdec_rc = qdec_rc * (4.0E-03); /*base time for x ms*/
	tc_write_rc(hw, 2, qdec_rc );

	/* Start TC channel 2 as a base timer for Speed measurement */
	tc_start(hw, 2);
}

/**
* \brief Initialize TC QDEC.
*/
static void tc_qdec_init(
		Tc *const hw,
		const struct tc_qdec_config *const config)
{
	switch(config->mode){
	case TC_QDEC_MODE_POSITION:
		config_tc_qdec_mode_position(hw, config);
		break;
	case TC_QDEC_MODE_SPEED:
		config_tc_qdec_mode_speed(hw, config);	
		break;
	case TC_QDEC_MODE_TEST_BASETIMER:
		config_tc_qdec_mode_test_basetimer(hw, config);
		break;
	default:
		break;
	}

	/* Start TC channel 0 for Speed/position measurement */
	tc_start(hw, 0);
	/* Start TC channel 1 for Rotation measurement */
	tc_start(hw, 1);

	/* Start TC channel 2 as a base timer for Speed measurement */
	if (config->mode == TC_QDEC_MODE_SPEED){
		tc_start(hw, 2);
	}
}

/**
* \brief configure TC QDEC.
*/
static void configure_tc_qdec(void)
{
	uint8_t qdec_channel_count = 0;
	
	while(qdec_channel_count < QDEC_INSTANCE_MAX)
	{
		if(qdec_config[qdec_channel_count].qdec)
		{
			/* Initialize with given configuration */
			tc_qdec_init(qdec_config[qdec_channel_count].qdec, &qdec_config[qdec_channel_count]);
		}
		qdec_channel_count++;
	}
}

/**
* \brief TC QDEC get results.
*/
static void tc_qdec_getresult(void){
	uint8_t qdec_channel_count = 0;
		
	while(qdec_channel_count < QDEC_INSTANCE_MAX)
	{
		if(qdec_config[qdec_channel_count].qdec)
		{
			qdec_results[qdec_channel_count].qdec_cv0	= (qdec_config[qdec_channel_count].qdec)->TC_CHANNEL[0].TC_CV;
			qdec_results[qdec_channel_count].qdec_cv1	= (qdec_config[qdec_channel_count].qdec)->TC_CHANNEL[1].TC_CV;
			qdec_results[qdec_channel_count].qdec_speed	= (qdec_config[qdec_channel_count].qdec)->TC_CHANNEL[0].TC_RA;
			qdec_results[qdec_channel_count].qdec_dir	= (((qdec_config[qdec_channel_count].qdec)->TC_QISR) & TC_QISR_DIR) / TC_QISR_DIR;
		}
		qdec_channel_count++;
	}
}

/**
* \brief TC QDEC print results.
*/
static void tc_qdec_printresults(void){
	uint8_t qdec_channel_count = 0;
	
	while(qdec_channel_count < QDEC_INSTANCE_MAX)
	{
		if(qdec_config[qdec_channel_count].qdec)
		{
			printf("# Results of QDEC%d...  ", qdec_channel_count);
			if (qdec_config[qdec_channel_count].mode == TC_QDEC_MODE_POSITION){
				printf("Phase A-B Position count = %07d ", qdec_results[qdec_channel_count].qdec_cv0);
			}
			else if (qdec_config[qdec_channel_count].mode == TC_QDEC_MODE_SPEED){
				printf("Speed results RA0 = %07d, ", qdec_results[qdec_channel_count].qdec_speed);
			}
			else{
				printf("Test base timer waveform output will get on respective pin");
				printf("For QDEC0 - PC26, QDEC1 - PC29, QDEC2 - PC11 \n\r");
			}

			if ((qdec_config[qdec_channel_count].mode == TC_QDEC_MODE_SPEED ) 
					|| (qdec_config[qdec_channel_count].mode == TC_QDEC_MODE_POSITION))	{
				printf("Index count = %06d DIR bit = %d ", qdec_results[qdec_channel_count].qdec_cv1,
					qdec_results[qdec_channel_count].qdec_dir);
				if (qdec_results[qdec_channel_count].qdec_dir == 0) {
					printf("Direction = CW \r");
					} else {
					printf("Direction = CCW \r");
				}
			}
			delay_us(20000);
		}
		qdec_channel_count++;
	}
}

/**
* \brief Configure UART console.
*/
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		#ifdef CONF_UART_CHAR_LENGTH
		.charlength = CONF_UART_CHAR_LENGTH,
		#endif
		.paritytype = CONF_UART_PARITY,
		#ifdef CONF_UART_STOP_BITS
		.stopbits = CONF_UART_STOP_BITS,
		#endif
	};

	/* Configure console UART. */
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief Application entry point for tc_capture_waveform example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Initialize the SAM system */
	sysclk_init();
	board_init();
	wdt_disable(WDT);
	/* Initialize the console uart */
	configure_console();

	/* Output example information */
	display_menu();
	configure_tc_qdec();

	while(1){
		tc_qdec_getresult();
		/*blink rate not visible but just in case required*/
		gpio_toggle_pin(LED0_GPIO);
		tc_qdec_printresults();
	}
}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
