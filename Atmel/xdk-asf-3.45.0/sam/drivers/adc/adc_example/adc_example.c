/**
 * \file
 *
 * \brief Analog-to-Digital Converter (ADC/ADC12B) example for SAM.
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
 * \mainpage ADC Example
 *
 * \section Purpose
 *
 * The ADC example demonstrates how to use ADC/ADC12B peripheral with several
 * modes.
 *
 * \section Requirements
 *
 * This example can be used on any SAM3/4 boards.
 *
 * ADVREF must be set to 3300 mv in order to enable full scale measurement
 * of the potentiometer. Please refer to the board schematics for ADVREF
 * jumper configuration.
 *
 * We use one push button for ADTGR, so please connect ADTRG to relative button pin
 *  \copydoc adc_example_pin_defs
 *
 * \section Description
 *
 * This application shows how to use the ADC using the several modes:
 * with/without PDC, several types of trigger (Software, ADTRG, Timer, etc.),
 * gain and offset selection, using sequencer. Users can select different modes
 * by configuration menu in the terminal.
 *
 * \note
 * The sequence number allowed for sam3s8 is 0 up to 7, so the channel 15 used for
 * TempSensor is not allowed to be set as the sequencer. Two times of capture on
 * channel 5 are used instead in the user sequence mode demo.
 *
 * \section Usage
 *
 * -# Build the program and download it into the evaluation board.
 * -# On the computer, open and configure a terminal application
 *    (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# In the terminal window, the
 *    following text should appear (values depend on the board and the chip used):
 *    \code
	-- ADC Example xxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
	=========================================================
	Menu: press a key to change the configuration.
	---------------------------------------------------------
	[X] 0: Set ADC trigger mode: Software.
	[ ] 1: Set ADC trigger mode: ADTRG.
	[ ] 2: Set ADC trigger mode: Timer TIOA.
	[ ] 3: Set ADC trigger mode: PWM Event Line.
	[ ] 4: Set ADC trigger mode: Free run mode.
	[E] T: Enable/Disable to transfer with PDC.
	[D] S: Enable/Disable to use user sequence mode.
	[D] P: Enable/Disable ADC power save mode.
	[D] G: Enable/Disable to set gain=2 for potentiometer channel.
	[D] O: Enable/Disable offset for potentiometer channel.
	    Q: Quit configuration and start ADC.
	=========================================================
\endcode
 * -# The application will output converted value to HyperTerminal and display
 *    a menu for users to set different modes.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <string.h>
#include "asf.h"
#include "conf_board.h"

/*
 * We use two ADC channels for this example:
 *    ADC_CHANNEL_5  (potentiometer)
 *    ADC_CHANNEL_15 (temperature sensor)
 */

/** There are two peripherals ADC and ADC12B in SAM3U, you can select one of them. */
#if SAM3U
//#define ADC_12B
#endif

#if SAM3S || SAM4S || SAM3XA || SAM3N || SAM4C
/* Tracking Time*/
#define TRACKING_TIME         1
/* Transfer Period */
#define TRANSFER_PERIOD       1
#endif

#if SAM3U
#ifdef ADC_12B
/* Start Up Time */
#define STARTUP_TIME               7
/* Off Mode Startup Time */
#define OFF_MODE_STARTUP_TIME      7
#else
#define STARTUP_TIME               3
#endif
/* Sample & Hold Time */
#define SAMPLE_HOLD_TIME   6
#endif

/** Total number of ADC channels in use */
#if SAM3S || SAM3XA || SAM4S || SAM4C
#define NUM_CHANNELS    (2)
#elif SAM3U|| SAM3N
#define NUM_CHANNELS    (1)
#endif
/** ADC convention done mask. */
#define ADC_DONE_MASK   ( (1<<NUM_CHANNELS) - 1 )

/** Size of the receive buffer and transmit buffer. */
#define BUFFER_SIZE     NUM_CHANNELS

/** Reference voltage for ADC, in mv. */
#define VOLT_REF        (3300)

#if SAM3S || SAM3XA || SAM4S
/** The maximal digital value */
#define MAX_DIGITAL     (4095)
#elif SAM3N || SAM4C
#define MAX_DIGITAL     (1023)
#elif SAM3U
#ifdef ADC_12B
#define MAX_DIGITAL     (4095)
#else
#define MAX_DIGITAL     (1023)
#endif
#endif

/** ADC channel for potentiometer */
#if SAM3S || SAM3N || SAM4S
#define ADC_CHANNEL_POTENTIOMETER  ADC_CHANNEL_5
#elif SAM3XA || SAM4C
#define ADC_CHANNEL_POTENTIOMETER  ADC_CHANNEL_1
#elif SAM3U
#define ADC_CHANNEL_POTENTIOMETER  ADC_CHANNEL_3
#endif

#define STRING_EOL    "\r"
#define STRING_HEADER "-- ADC Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL
#define MENU_HEADER "\n\r" \
		"===================================================\n\r" \
		"Menu: press a key to change the configuration.\n\r" \
		"---------------------------------------------------------\n\r"

/** ADC test mode structure */
struct {
	uint8_t uc_trigger_mode;
	uint8_t uc_pdc_en;
	uint8_t uc_sequence_en;
	uint8_t uc_gain_en;
	uint8_t uc_offset_en;
#if  SAM3S8 || SAM3SD8 || SAM4S || SAM3N || SAM3U || SAM4C
	uint8_t uc_power_save_en;
#endif
#if  SAM3S8 || SAM3SD8 || SAM4S
	uint8_t uc_auto_calib_en;
#endif
} g_adc_test_mode;

/** ADC trigger modes */
enum {
	TRIGGER_MODE_SOFTWARE = 0,
	TRIGGER_MODE_ADTRG,
	TRIGGER_MODE_TIMER,
#if SAM3S || SAM3U || SAM3XA || SAM4S
	TRIGGER_MODE_PWM,
#endif
#if SAM3S || SAM3N || SAM3XA || SAM4S || SAM4C
	TRIGGER_MODE_FREERUN
#endif
} e_trigger_mode;

/** ADC sample data */
struct {
	uint8_t uc_ch_num[NUM_CHANNELS];
	uint16_t us_value[NUM_CHANNELS];
	uint16_t us_done;
} g_adc_sample_data;

#if SAM3S || SAM3XA || SAM3N || SAM4S || SAM4C
/**Channel list for sequence*/
enum adc_channel_num_t ch_list[2] = {
	ADC_TEMPERATURE_SENSOR,
	ADC_CHANNEL_POTENTIOMETER
};
#endif
/** Global timestamp in milliseconds since start of application */
static volatile uint32_t gs_ul_ms_ticks = 0;

/**
 * \brief Display ADC configuration menu.
 */
static void display_menu(void)
{
	uint8_t uc_char;

	puts(MENU_HEADER);
	uc_char = (g_adc_test_mode.uc_trigger_mode ==
			TRIGGER_MODE_SOFTWARE) ? 'X' : ' ';
	printf("[%c] 0: Set ADC trigger mode: Software.\n\r", uc_char);
	uc_char = (g_adc_test_mode.uc_trigger_mode == TRIGGER_MODE_ADTRG) ? 'X' : ' ';
	printf("[%c] 1: Set ADC trigger mode: ADTRG.\n\r", uc_char);
	uc_char = (g_adc_test_mode.uc_trigger_mode == TRIGGER_MODE_TIMER) ? 'X' : ' ';
	printf("[%c] 2: Set ADC trigger mode: Timer TIOA.\n\r", uc_char);
#if SAM3S || SAM3U || SAM3XA || SAM4S
	uc_char = (g_adc_test_mode.uc_trigger_mode == TRIGGER_MODE_PWM) ? 'X' : ' ';
	printf("[%c] 3: Set ADC trigger mode: PWM Event Line.\n\r", uc_char);
#endif
#if SAM3S || SAM3N || SAM3XA || SAM4S || SAM4C
	uc_char = (g_adc_test_mode.uc_trigger_mode ==
			TRIGGER_MODE_FREERUN) ? 'X' : ' ';
	printf("[%c] 4: Set ADC trigger mode: Free run mode.\n\r", uc_char);
#endif
	uc_char = (g_adc_test_mode.uc_pdc_en) ? 'E' : 'D';
	printf("[%c] T: Enable/Disable to transfer with PDC.\n\r", uc_char);
#if SAM3S || SAM3N || SAM3XA || SAM4S || SAM4C
	uc_char = (g_adc_test_mode.uc_sequence_en) ? 'E' : 'D';
	printf("[%c] S: Enable/Disable to use user sequence mode.\n\r", uc_char);
#endif
#if  SAM3S8 || SAM3SD8 || SAM4S || SAM3N || SAM3U || SAM4C
	uc_char = (g_adc_test_mode.uc_power_save_en) ? 'E' : 'D';
	printf("[%c] P: Enable/Disable ADC power save mode.\n\r", uc_char);
#endif
#if SAM3S || SAM3U || SAM3XA || SAM4S
	uc_char = (g_adc_test_mode.uc_gain_en) ? 'E' : 'D';
	printf("[%c] G: Enable/Disable to set gain=2 for potentiometer channel.\n\r",
		uc_char);
	uc_char = (g_adc_test_mode.uc_offset_en) ? 'E' : 'D';
	printf("[%c] O: Enable/Disable offset for potentiometer channel.\n\r",
			uc_char);
#endif
#if  SAM3S8 || SAM3SD8 || SAM4S
	uc_char = (g_adc_test_mode.uc_auto_calib_en) ? 'E' : 'D';
	printf("[%c] C: Enable Auto Calibration Mode.\n\r", uc_char);
#endif
	puts("    Q: Quit configuration and start ADC.\r");
	puts("=========================================================\r");
}

/**
 * \brief Set ADC test mode.
 */
static void set_adc_test_mode(void)
{
	uint8_t uc_key;
	uint8_t uc_done = 0;

	while (!uc_done) {
		while (uart_read(CONSOLE_UART, &uc_key));

		switch (uc_key) {
		case '0':
			g_adc_test_mode.uc_trigger_mode = TRIGGER_MODE_SOFTWARE;
			break;

		case '1':
			g_adc_test_mode.uc_trigger_mode = TRIGGER_MODE_ADTRG;
			break;

		case '2':
			g_adc_test_mode.uc_trigger_mode = TRIGGER_MODE_TIMER;
			break;
#if SAM3S || SAM3U || SAM3XA || SAM4S
		case '3':
			g_adc_test_mode.uc_trigger_mode = TRIGGER_MODE_PWM;
			break;
#endif
#if SAM3S || SAM3N || SAM3XA || SAM4S || SAM4C
		case '4':
			g_adc_test_mode.uc_trigger_mode = TRIGGER_MODE_FREERUN;
			break;
#endif
		case 't':
		case 'T':
			if (g_adc_test_mode.uc_pdc_en) {
				g_adc_test_mode.uc_pdc_en = 0;
			} else {
				g_adc_test_mode.uc_pdc_en = 1;
			}
			break;
#if SAM3S || SAM3N || SAM3XA || SAM4S || SAM4C
		case 's':
		case 'S':
			if (g_adc_test_mode.uc_sequence_en) {
				g_adc_test_mode.uc_sequence_en = 0;
			} else {
				g_adc_test_mode.uc_sequence_en = 1;
			}
			break;
#endif
#if  SAM3S8 || SAM3SD8 || SAM4S || SAM3N || SAM3U || SAM4C
		case 'p':
		case 'P':
			if (g_adc_test_mode.uc_power_save_en) {
				g_adc_test_mode.uc_power_save_en = 0;
			} else {
				g_adc_test_mode.uc_power_save_en = 1;
			}
			break;
#endif
#if SAM3S || SAM3U || SAM3XA || SAM4S
		case 'g':
		case 'G':
			if (g_adc_test_mode.uc_gain_en) {
				g_adc_test_mode.uc_gain_en = 0;
			} else {
				g_adc_test_mode.uc_gain_en = 1;
			}
			break;

		case 'o':
		case 'O':
			if (g_adc_test_mode.uc_offset_en) {
				g_adc_test_mode.uc_offset_en = 0;
			} else {
				g_adc_test_mode.uc_offset_en = 1;
			}
			break;
#endif
#if  SAM3S8 || SAM3SD8 || SAM4S
		case 'c':
		case 'C':
			if (g_adc_test_mode.uc_auto_calib_en) {
				g_adc_test_mode.uc_auto_calib_en = 0;
			} else {
				g_adc_test_mode.uc_auto_calib_en = 1;
			}
			break;
#endif
		case 'q':
		case 'Q':
			uc_done = 1;
			break;

		default:
			break;
		}

		display_menu();
	}
}

/**
 * \brief Configure to trigger ADC by TIOA output of timer.
 */
static void configure_time_trigger(void)
{
	uint32_t ul_div = 0;
	uint32_t ul_tc_clks = 0;
	uint32_t ul_sysclk = sysclk_get_cpu_hz();

	/* Enable peripheral clock. */
	pmc_enable_periph_clk(ID_TC0);

	/* TIOA configuration */
	gpio_configure_pin(PIN_TC0_TIOA0, PIN_TC0_TIOA0_FLAGS);

	/* Configure TC for a 1Hz frequency and trigger on RC compare. */
	tc_find_mck_divisor(1, ul_sysclk, &ul_div, &ul_tc_clks, ul_sysclk);
	tc_init(TC0, 0, ul_tc_clks | TC_CMR_CPCTRG | TC_CMR_WAVE |
			TC_CMR_ACPA_CLEAR | TC_CMR_ACPC_SET);
	TC0->TC_CHANNEL[0].TC_RA = (ul_sysclk / ul_div) / 2;
	TC0->TC_CHANNEL[0].TC_RC = (ul_sysclk / ul_div) / 1;

	/* Start the Timer. */
	tc_start(TC0, 0);
	/* Set TIOA0 trigger. */
#if SAM3S || SAM3N || SAM3XA || SAM4S || SAM4C
	adc_configure_trigger(ADC, ADC_TRIG_TIO_CH_0, 0);
#elif SAM3U
#ifdef ADC_12B
	adc12b_configure_trigger(ADC12B, ADC12B_TRIG_TIO_CH_0);
#else
	adc_configure_trigger(ADC, ADC_TRIG_TIO_CH_0);
#endif
#endif
}

#if SAM3S || SAM3U || SAM3XA || SAM4S
/**
 * \brief Configure to trigger ADC by PWM Event Line.
 */
static void configure_pwm_trigger(void)
{
	/* PWM frequency in Hz. */
#define PWM_FREQUENCY               2
	/* Maximum duty cycle value. */
#define MAX_DUTY_CYCLE              1000

	/* Enable PWMC peripheral clock. */
	pmc_enable_periph_clk(ID_PWM);

	/* Disable PWM channel 0. */
	pwm_channel_disable(PWM, PWM_CHANNEL_0);

	gpio_configure_pin(PIN_PWMC_PWMH0_TRIG, PIN_PWMC_PWMH0_TRIG_FLAG);

	/* Set clock A to run at PWM_FREQUENCY * MAX_DUTY_CYCLE (clock B is not used). */
	pwm_clock_t pwm_clock_setting = {
		.ul_clka = PWM_FREQUENCY * MAX_DUTY_CYCLE,
		.ul_clkb = 0,
		.ul_mck = sysclk_get_cpu_hz()
	};
	pwm_init(PWM, &pwm_clock_setting);

	/* Configure PWMC for channel 0 (left-aligned). */
		pwm_channel_t pwm_trigger_channel = {
			.channel = PWM_CHANNEL_0,
			.alignment = PWM_ALIGN_LEFT,
			.polarity = PWM_LOW,
		.ul_prescaler = PWM_CMR_CPRE_CLKA,
		.ul_period = MAX_DUTY_CYCLE,
		.ul_duty = MAX_DUTY_CYCLE / 2
	};
	pwm_channel_init(PWM, &pwm_trigger_channel);

	pwm_cmp_t pwm_comparison_setting = {
		.unit = PWM_CMP_UNIT_0,
		.b_enable = true,
		.ul_value = MAX_DUTY_CYCLE / 2,
		.b_pulse_on_line_0 = true
	};
	pwm_cmp_init(PWM, &pwm_comparison_setting);


	/* Enable PWM channel 0. */
	pwm_channel_enable(PWM, PWM_CHANNEL_0);
	/* Set PWM Event Line 0 trigger. */
#if SAM3S || SAM3XA || SAM4S
	adc_configure_trigger(ADC, ADC_TRIG_PWM_EVENT_LINE_0, 0);
#elif SAM3U
#ifdef ADC_12B
	adc12b_configure_trigger(ADC12B, ADC12B_TRIG_PWM_EVENT_LINE_0);
#else
	adc_configure_trigger(ADC, ADC_TRIG_PWM_EVENT_LINE_0);
#endif
#endif
}
#endif

/**
 * \brief Read converted data through PDC channel.
 *
 * \param p_adc The pointer of adc peripheral.
 * \param p_s_buffer The destination buffer.
 * \param ul_size The size of the buffer.
 */
#if SAM3S || SAM3N || SAM3XA || SAM4S || SAM4C
static uint32_t adc_read_buffer(Adc * p_adc, uint16_t * p_s_buffer, uint32_t ul_size)
{
	/* Check if the first PDC bank is free. */
	if ((p_adc->ADC_RCR == 0) && (p_adc->ADC_RNCR == 0)) {
		p_adc->ADC_RPR = (uint32_t) p_s_buffer;
		p_adc->ADC_RCR = ul_size;
		p_adc->ADC_PTCR = ADC_PTCR_RXTEN;

		return 1;
	} else { /* Check if the second PDC bank is free. */
		if (p_adc->ADC_RNCR == 0) {
			p_adc->ADC_RNPR = (uint32_t) p_s_buffer;
			p_adc->ADC_RNCR = ul_size;

			return 1;
		} else {
			return 0;
		}
	}
}
#elif SAM3U
#ifdef ADC_12B
static uint32_t adc12_read_buffer(Adc12b * p_adc, uint16_t * p_s_buffer,
		uint32_t ul_size)
{
	/* Check if the first PDC bank is free. */
	if ((p_adc->ADC12B_RCR == 0) && (p_adc->ADC12B_RNCR == 0)) {
		p_adc->ADC12B_RPR = (uint32_t) p_s_buffer;
		p_adc->ADC12B_RCR = ul_size;
		p_adc->ADC12B_PTCR = ADC12B_PTCR_RXTEN;

		return 1;
	} else {	/* Check if the second PDC bank is free. */
		if (p_adc->ADC12B_RNCR == 0) {
			p_adc->ADC12B_RNPR = (uint32_t) p_s_buffer;
			p_adc->ADC12B_RNCR = ul_size;

			return 1;
		} else {
			return 0;
		}
	}
}
#else
static uint32_t adc_read_buffer(Adc * p_adc, uint16_t * p_s_buffer, uint32_t ul_size)
{
	/* Check if the first PDC bank is free. */
	if ((p_adc->ADC_RCR == 0) && (p_adc->ADC_RNCR == 0)) {
		p_adc->ADC_RPR = (uint32_t) p_s_buffer;
		p_adc->ADC_RCR = ul_size;
		p_adc->ADC_PTCR = ADC_PTCR_RXTEN;

		return 1;
	} else {	/* Check if the second PDC bank is free. */
		if (p_adc->ADC_RNCR == 0) {
			p_adc->ADC_RNPR = (uint32_t) p_s_buffer;
			p_adc->ADC_RNCR = ul_size;

			return 1;
		} else {
			return 0;
		}
	}
}
#endif
#endif

/**
 * \brief Start ADC sample.
 * Initialize ADC, set clock and timing, and set ADC to given mode.
 */
static void start_adc(void)
{
	/* Enable peripheral clock. */
#if SAM3S || SAM3N || SAM3XA || SAM4S || SAM4C
	uint32_t i;
	pmc_enable_periph_clk(ID_ADC);
#elif SAM3U
#ifdef ADC_12B
	pmc_enable_periph_clk(ID_ADC12B);
#else
	pmc_enable_periph_clk(ID_ADC);
#endif
#endif

	/* Initialize ADC. */
	/*
	 * Formula: ADCClock = MCK / ( (PRESCAL+1) * 2 )
	 * For example, MCK = 64MHZ, PRESCAL = 4, then:
	 * ADCClock = 64 / ((4+1) * 2) = 6.4MHz;
	 */
#if SAM3S || SAM3N || SAM3XA || SAM4S || SAM4C
	/* Formula:
	 *     Startup  Time = startup value / ADCClock
	 *     Startup time = 64 / 6.4MHz = 10 us
	 */
	adc_init(ADC, sysclk_get_cpu_hz(), 6400000, ADC_STARTUP_TIME_4);
#elif SAM3U
#ifdef ADC_12B
	/* Formula:
	 *     Startup  Time = (startup value + 1) * 8 / ADCClock
	 *     Startup time = (7 + 1) * 8 / 6.4MHz = 10 us
	 */
	adc12b_init(ADC12B, sysclk_get_cpu_hz(), 6400000, STARTUP_TIME, OFF_MODE_STARTUP_TIME);
#else
	/* Formula:
	 *     Startup  Time = (startup value + 1) * 8 / ADCClock
	 *     Startup time = (3 + 1) * 8 / 3.2MHz = 10 us
	 */
	adc_init(ADC, sysclk_get_cpu_hz(), 3200000, STARTUP_TIME);
#endif
#endif

	memset((void *)&g_adc_sample_data, 0, sizeof(g_adc_sample_data));

	/* Set ADC timing. */
#if SAM3S ||  SAM3XA || SAM4S
	/* Formula:
	 *     Transfer Time = (TRANSFER * 2 + 3) / ADCClock
	 *     Tracking Time = (TRACKTIM + 1) / ADCClock
	 *     Settling Time = settling value / ADCClock
	 *
	 *     Transfer Time = (1 * 2 + 3) / 6.4MHz = 781 ns
	 *     Tracking Time = (1 + 1) / 6.4MHz = 312 ns
	 *     Settling Time = 3 / 6.4MHz = 469 ns
	 */
	adc_configure_timing(ADC, TRACKING_TIME, ADC_SETTLING_TIME_3, TRANSFER_PERIOD);
#elif  SAM3N || SAM4C
	adc_configure_timing(ADC, TRACKING_TIME);
#elif SAM3U
	/* Formula:
	 *     Sample & Hold Time = SHTIM/ADCClock
	 *
	 *     Sample & Hold Time = 6 / 6.4 = 938 ns
	 */
#ifdef ADC_12B
	adc12b_configure_timing(ADC12B, SAMPLE_HOLD_TIME);
#else
	adc_configure_timing(ADC, SAMPLE_HOLD_TIME);
#endif
#endif

#if SAM3S || SAM3N || SAM3XA || SAM4S || SAM4C
	/* Enable channel number tag. */
	adc_enable_tag(ADC);
	/* Enable/disable sequencer. */
	if (g_adc_test_mode.uc_sequence_en) {
		/* Set user defined channel sequence. */
		adc_configure_sequence(ADC, ch_list, 2);

		/* Enable sequencer. */
		adc_start_sequencer(ADC);

		/* Enable channels. */
		for (i = 0; i < 2; i++) {
			adc_enable_channel(ADC, (enum adc_channel_num_t)i);
		}
		/* Update channel number. */
		g_adc_sample_data.uc_ch_num[0] = ch_list[0];
		g_adc_sample_data.uc_ch_num[1] = ch_list[1];
	} else {
		/* Disable sequencer. */
		adc_stop_sequencer(ADC);

		/* Enable channels. */
		adc_enable_channel(ADC, ADC_CHANNEL_POTENTIOMETER);
#if SAM3S || SAM3XA || SAM4S || SAM4C
		adc_enable_channel(ADC, ADC_TEMPERATURE_SENSOR);
#endif
		/* Update channel number. */
		g_adc_sample_data.uc_ch_num[0] = ADC_CHANNEL_POTENTIOMETER;
#if SAM3S || SAM3XA || SAM4S || SAM4C
		g_adc_sample_data.uc_ch_num[1] = ADC_TEMPERATURE_SENSOR;
#else
		g_adc_sample_data.uc_ch_num[1] = ADC_CHANNEL_POTENTIOMETER;
#endif
	}
#elif SAM3U
#ifdef ADC_12B
	adc12b_enable_channel(ADC12B, ADC_CHANNEL_POTENTIOMETER);
#else
	adc_enable_channel(ADC, ADC_CHANNEL_POTENTIOMETER);
#endif
	g_adc_sample_data.uc_ch_num[0] = ADC_CHANNEL_POTENTIOMETER;
	g_adc_sample_data.uc_ch_num[1] = ADC_CHANNEL_POTENTIOMETER;
#endif

#if SAM3S ||  SAM3XA || SAM4S || SAM4C
	/* Enable the temperature sensor. */
	adc_enable_ts(ADC);
#endif
	/* Set gain and offset (only single ended mode used here). */
#if SAM3S || SAM3XA || SAM4S
	adc_disable_anch(ADC); /* Disable analog change. */
#endif
	if (g_adc_test_mode.uc_gain_en) {
#if SAM3S || SAM3XA || SAM4S
		adc_enable_anch(ADC);
		/* gain = 2 */
		adc_set_channel_input_gain(ADC, ADC_CHANNEL_POTENTIOMETER, ADC_GAINVALUE_2);
#elif SAM3U
#ifdef ADC_12B
		adc12b_set_input_gain(ADC12B, ADC_GAINVALUE_2);
#endif
#endif
	} else {
#if SAM3S || SAM3XA || SAM4S
		/* gain = 1 */
		adc_set_channel_input_gain(ADC, ADC_CHANNEL_POTENTIOMETER, ADC_GAINVALUE_0);
#elif SAM3U
#ifdef ADC_12B
		adc12b_set_input_gain(ADC12B, ADC_GAINVALUE_0);
#endif
#endif
	}

	if (g_adc_test_mode.uc_offset_en) {
#if SAM3S || SAM3XA || SAM4S
		adc_enable_anch(ADC);
		adc_enable_channel_input_offset(ADC, ADC_CHANNEL_POTENTIOMETER);
#elif 	SAM3U
#ifdef ADC_12B
		adc12b_enable_input_offset(ADC12B);
#endif
#endif
	} else {
#if SAM3S || SAM3XA || SAM4S
		adc_disable_channel_input_offset(ADC, ADC_CHANNEL_POTENTIOMETER);
#elif 	SAM3U
#ifdef ADC_12B
		adc12b_disable_input_offset(ADC12B);
#endif
#endif
	}
	/* Set Auto Calibration Mode. */
#if  SAM3S8 || SAM3SD8 || SAM4S
	if (g_adc_test_mode.uc_auto_calib_en) {
		adc_set_calibmode(ADC);
		while (1) {
			if ((adc_get_status(ADC) & ADC_ISR_EOCAL) ==
					ADC_ISR_EOCAL)
				break;
		}
	}
#endif

#if SAM3S8 || SAM4S || SAM3N || SAM3SD8
	/* Set power save. */
	if (g_adc_test_mode.uc_power_save_en) {
		adc_configure_power_save(ADC, 1, 0);
	} else {
		adc_configure_power_save(ADC, 0, 0);;
	}
#elif SAM3U || SAM4C
#ifdef ADC_12B
	/* Set power save. */
	if (g_adc_test_mode.uc_power_save_en) {
		adc12b_configure_power_save(ADC12B, 1, 0);
	} else {
		adc12b_configure_power_save(ADC12B, 0, 0);;
	}

#else
	/* Set power save. */
	if (g_adc_test_mode.uc_power_save_en) {
		adc_configure_power_save(ADC, 1);
	} else {
		adc_configure_power_save(ADC, 0);;
	}
#endif
#endif

#if SAM3S || SAM3N || SAM3XA || SAM4S || SAM4C
	/* Transfer with/without PDC. */
	if (g_adc_test_mode.uc_pdc_en) {
		adc_read_buffer(ADC, g_adc_sample_data.us_value, BUFFER_SIZE);
		/* Enable PDC channel interrupt. */
		adc_enable_interrupt(ADC, ADC_IER_RXBUFF);
	} else {
		/* Enable Data ready interrupt. */
		adc_enable_interrupt(ADC, ADC_IER_DRDY);
	}
	/* Enable ADC interrupt. */
	NVIC_EnableIRQ(ADC_IRQn);
#elif SAM3U
#ifdef ADC_12B
	/* Transfer with/without PDC. */
	if (g_adc_test_mode.uc_pdc_en) {
		adc12_read_buffer(ADC12B, g_adc_sample_data.us_value, BUFFER_SIZE);
		/* Enable PDC channel interrupt. */
		adc12b_enable_interrupt(ADC12B, ADC12B_IER_RXBUFF);
	} else {
		/* Enable Data ready interrupt. */
		adc12b_enable_interrupt(ADC12B, ADC12B_IER_DRDY);

	}
	/* Enable ADC interrupt. */
	NVIC_EnableIRQ(ADC12B_IRQn);
#else
	/* Transfer with/without PDC. */
	if (g_adc_test_mode.uc_pdc_en) {
		adc_read_buffer(ADC, g_adc_sample_data.us_value, BUFFER_SIZE);
		/* Enable PDC channel interrupt. */
		adc_enable_interrupt(ADC, ADC_IER_RXBUFF);
	} else {
		/* Enable Data ready interrupt. */
		adc_enable_interrupt(ADC, ADC_IER_DRDY);

	}
	/* Enable ADC interrupt. */
	NVIC_EnableIRQ(ADC_IRQn);
#endif
#endif
	/* Configure trigger mode and start convention. */
	switch (g_adc_test_mode.uc_trigger_mode) {
	case TRIGGER_MODE_SOFTWARE:
#if SAM3S || SAM3N || SAM3XA || SAM4S || SAM4C
		adc_configure_trigger(ADC, ADC_TRIG_SW, 0);	/* Disable hardware trigger. */
#elif SAM3U
#ifdef ADC_12B
		adc12b_configure_trigger(ADC12B, ADC12B_TRIG_SW);
#else
		adc_configure_trigger(ADC, ADC_TRIG_SW);
#endif
#endif
		break;

	case TRIGGER_MODE_ADTRG:
#if SAM3S || SAM3N || SAM3XA || SAM4S || SAM4C
		gpio_configure_pin(PINS_ADC_TRIG, PINS_ADC_TRIG_FLAG);
		adc_configure_trigger(ADC, ADC_TRIG_EXT, 0);
#elif SAM3U
#ifdef ADC_12B
		gpio_configure_pin(PINS_ADC12B_TRIG, PINS_ADC12B_TRIG_FLAG);
		adc12b_configure_trigger(ADC12B, ADC12B_TRIG_EXT);
#else
		gpio_configure_pin(PINS_ADC_TRIG, PINS_ADC_TRIG_FLAG);
		adc_configure_trigger(ADC, ADC_TRIG_EXT);
#endif
#endif
		break;

	case TRIGGER_MODE_TIMER:
		configure_time_trigger();
		break;
#if SAM3S || SAM3U || SAM3XA || SAM4S
	case TRIGGER_MODE_PWM:
		configure_pwm_trigger();
		break;
#endif
#if SAM3S || SAM3N || SAM3XA || SAM4S || SAM4C
	case TRIGGER_MODE_FREERUN:
		adc_configure_trigger(ADC, ADC_TRIG_SW, 1);
		break;
#endif
	default:
		break;
	}
}

/**
 * \brief Systick handler.
 */
void SysTick_Handler(void)
{
	gs_ul_ms_ticks++;
}

#if SAM3S || SAM3N || SAM3XA || SAM4S || SAM4C
/**
 * \brief Interrupt handler for the ADC.
 */
void ADC_Handler(void)
{
	uint32_t i;
	uint32_t ul_temp;
	uint8_t uc_ch_num;

	/* With PDC transfer */
	if (g_adc_test_mode.uc_pdc_en) {
		if ((adc_get_status(ADC) & ADC_ISR_RXBUFF) ==
				ADC_ISR_RXBUFF) {
			g_adc_sample_data.us_done = ADC_DONE_MASK;
			adc_read_buffer(ADC, g_adc_sample_data.us_value, BUFFER_SIZE);
			/* Only keep sample value, and discard channel number. */
			for (i = 0; i < NUM_CHANNELS; i++) {
				g_adc_sample_data.us_value[i] &= ADC_LCDR_LDATA_Msk;
			}
		}
	} else {	/* Without PDC transfer */
		if ((adc_get_status(ADC) & ADC_ISR_DRDY) ==
				ADC_ISR_DRDY) {
			ul_temp = adc_get_latest_value(ADC);
			for (i = 0; i < NUM_CHANNELS; i++) {
				uc_ch_num = (ul_temp & ADC_LCDR_CHNB_Msk) >>
						ADC_LCDR_CHNB_Pos;
				if (g_adc_sample_data.uc_ch_num[i] == uc_ch_num) {
					g_adc_sample_data.us_value[i] =
							ul_temp &
							ADC_LCDR_LDATA_Msk;
					g_adc_sample_data.us_done |= 1 << i;
				}
			}
		}
	}
}
#elif SAM3U
#ifdef ADC_12B
void ADC12B_Handler(void)
{
	uint32_t i;
	uint32_t ul_temp;

	/* With PDC transfer */
	if (g_adc_test_mode.uc_pdc_en) {
		if ((adc12b_get_status(ADC12B) & ADC12B_SR_RXBUFF) ==
				ADC12B_SR_RXBUFF) {
			g_adc_sample_data.us_done = ADC_DONE_MASK;
			adc12_read_buffer(ADC12B, g_adc_sample_data.us_value,
					BUFFER_SIZE);

			/* Only keep sample value, and discard channel number. */
			for (i = 0; i < NUM_CHANNELS; i++) {
				g_adc_sample_data.us_value[i] &=
						ADC12B_LCDR_LDATA_Msk;
			}
		}
	} else {	/* Without PDC transfer */
		if ((adc12b_get_status(ADC12B) & ADC12B_SR_DRDY) ==
				ADC12B_SR_DRDY) {
			ul_temp = adc12b_get_latest_value(ADC12B);
			for (i = 0; i < NUM_CHANNELS; i++) {
				g_adc_sample_data.us_value[i] =
						ul_temp & ADC12B_LCDR_LDATA_Msk;
				g_adc_sample_data.us_done |= 1 << i;
			}
		}
	}
}
#else
void ADC_Handler(void)
{
	uint32_t i;
	uint32_t ul_temp;

	/* With PDC transfer */
	if (g_adc_test_mode.uc_pdc_en) {
		if ((adc_get_status(ADC) & ADC_SR_RXBUFF) ==
				ADC_SR_RXBUFF) {
			g_adc_sample_data.us_done = ADC_DONE_MASK;
			adc_read_buffer(ADC, g_adc_sample_data.us_value, BUFFER_SIZE);

			/* Only keep sample value, and discard channel number. */
			for (i = 0; i < NUM_CHANNELS; i++) {
				g_adc_sample_data.us_value[i] &= ADC_LCDR_LDATA_Msk;
			}
		}
	} else {
		if ((adc_get_status(ADC) & ADC_SR_DRDY) ==
				ADC_SR_DRDY) {
			ul_temp = adc_get_latest_value(ADC);
			for (i = 0; i < NUM_CHANNELS; i++) {
				g_adc_sample_data.us_value[i] =
						ul_temp & ADC_LCDR_LDATA_Msk;
				g_adc_sample_data.us_done |= 1 << i;
			}
		}
	}
}
#endif
#endif
/**
 *  Configure UART console.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 *  Wait for the given number of milliseconds (using the dwTimeStamp generated
 *  by the SAM microcontrollers' system tick).
 *  \param ul_dly_ticks  Delay to wait for, in milliseconds.
 */
static void mdelay(uint32_t ul_dly_ticks)
{
	uint32_t ul_cur_ticks;

	ul_cur_ticks = gs_ul_ms_ticks;
	while ((gs_ul_ms_ticks - ul_cur_ticks) < ul_dly_ticks);
}

/**
 *  \brief adc12 Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint32_t i;
	uint8_t uc_key;
	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);

	puts("Configure system tick to get 1ms tick period.\r");
	if (SysTick_Config(sysclk_get_cpu_hz() / 1000)) {
		puts("-F- Systick configuration error\r");
		while (1);
	}

	/* Set default ADC test mode. */
	memset((void *)&g_adc_test_mode, 0, sizeof(g_adc_test_mode));
	g_adc_test_mode.uc_trigger_mode = TRIGGER_MODE_SOFTWARE;
	g_adc_test_mode.uc_pdc_en = 1;
	g_adc_test_mode.uc_sequence_en = 0;
	g_adc_test_mode.uc_gain_en = 0;
	g_adc_test_mode.uc_offset_en = 0;

	display_menu();
	start_adc();

	puts("Press any key to display configuration menu.\r");
	while (1) {
		/* ADC software trigger per 1s */
		if (g_adc_test_mode.uc_trigger_mode == TRIGGER_MODE_SOFTWARE) {
			mdelay(1000);
#if SAM3S || SAM3N || SAM3XA || SAM4S || SAM4C
			adc_start(ADC);
#elif SAM3U
#ifdef ADC_12B
			adc12b_start(ADC12B);
#else
			adc_start(ADC);
#endif
#endif
		}

		/* Check if the user enters a key. */
		if (!uart_read(CONSOLE_UART, &uc_key)) {
#if SAM3S || SAM3N || SAM3XA || SAM4S || SAM4C
			adc_disable_interrupt(ADC, 0xFFFFFFFF);	/* Disable all adc interrupt. */
#elif SAM3U
#ifdef ADC_12B
			adc12b_disable_interrupt(ADC12B, 0xFFFFFFFF);	/* Disable all adc interrupt. */
#else
			adc_disable_interrupt(ADC, 0xFFFFFFFF);	/* Disable all adc interrupt. */
#endif
#endif
			tc_start(TC0, 0);	/* Stop the Timer. */
#if SAM3S || SAM3U || SAM3XA || SAM4S
			pwm_channel_disable(PWM, 0);
#endif
			display_menu();
			set_adc_test_mode();
			start_adc();
			puts("Press any key to display configuration menu.\r");
		}

		/* Check if ADC sample is done. */
		if (g_adc_sample_data.us_done == ADC_DONE_MASK) {
			for (i = 0; i < NUM_CHANNELS; i++) {
				printf("CH%02d: %04d mv.    ",
						(int)g_adc_sample_data.uc_ch_num[i],
						(int)(g_adc_sample_data.
								us_value[i] *
								VOLT_REF /
								MAX_DIGITAL));
			}
			puts("\r");
			g_adc_sample_data.us_done = 0;
		}
	}
}
