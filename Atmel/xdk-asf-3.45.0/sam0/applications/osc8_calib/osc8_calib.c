/**
 * \file
 *
 * \brief SAM OSC8MHz Calibration Application
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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
#include "conf_example.h"

/**
 * \mainpage SAM OSC8M Calibration Example
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This application calibrates the internal OSC8M (8MHz) oscillator of the
 * device against a known, accurate external clock or crystal frequency.
 */

/**
 * \page appdoc_main SAM OSC8M Calibration Example
 *
 * Overview:
 * - \ref appdoc_sam0_osc8m_cal_intro
 * - \ref appdoc_sam0_osc8m_cal_usage
 * - \ref appdoc_sam0_osc8m_cal_compinfo
 * - \ref appdoc_sam0_osc8m_cal_contactinfo
 *
 * \section appdoc_sam0_osc8m_cal_intro Introduction
 * While some devices require exact timing, and therefore require an external
 * calibration crystal or other high-accuracy clock source, other applications
 * with looser accuracy requirements may use the internal RC Oscillator(s) for
 * space and/or cost reasons. However, this can lead to unstable communication
 * interfaces if the internal oscillator is not first calibrated against an
 * accurate reference clock.
 *
 * This application uses a known external reference frequency to calibrate the
 * internal 8MHz (nominal) RC Oscillator, OSC8M, so that it is as close as
 * possible to the desired 8MHz frequency.
 *
 * This application has been tested on following boards:
 * - SAM D20/D21 Xplained Pro
 *
 * \section appdoc_sam0_osc8m_cal_usage Usage Instructions
 * On startup, the application will immediately begin calibration of the OSC8M
 * internal oscillator, against a 32.768KHz watch crystal attached to the device
 * XOSC32K pins (see device datasheet). As the possible calibration values are
 * cycled through, the board LED will turn on each time a better match is found,
 * and turn off when an equal or lesser calibration value is tested. Once the
 * best values are found, the results are printed to the device USART and the
 * board LED will flash rapidly to signal the end of the calibration sequence.
 *
 * \note The calibration values are \b not stored to the device's non-volatile
 *       memory. The example execution time is depend on the configuration in
 *       conf_example file. It's about (2<<CONF_CALIBRATION_RESOLUTION)
 *       *(2<<CONF_FRANGE_CAL -1)*(2<<CONF_TEMP_CAL -1)*128/32768
 *       seconds. To get more accurate result, we can increase the value of
 *       CONF_FRANGE_CAL, CONF_TEMP_CAL and CONF_CALIBRATION_RESOLUTION,
 *       but the execution time is also longer.
 *
 * \section appdoc_sam0_osc8m_cal_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_osc8m_cal_contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com">http://www.microchip.com</a>.
 */

/** OSC8M calibration info */
#define FRANGE_CAL_MIN       0x00
#define FRANGE_CAL_MAX       0x03
#define TEMP_CAL_OFFSET      0x07
#define TEMP_CAL_MIN         0x00
#define TEMP_CAL_MAX         0x1F
#define COMM_CAL_MIN         0x00
#define COMM_CAL_MAX         0x7F

/** Target OSC8M calibration frequency */
#define TARGET_FREQUENCY         8000000

/** Resolution of the calibration binary divider; lower powers of two will
 *  reduce the calibration resolution.
 */
#define CALIBRATION_RESOLUTION   CONF_CALIBRATION_RESOLUTION

/** Calibration reference clock generator index. */
#define REFERENCE_CLOCK          GCLK_GENERATOR_3

/** Frequency of the calibration reference clock in Hz */
#define REFERENCE_CLOCK_HZ       32768

/** Software instance of the USART upon which to transmit the results. */
static struct usart_module usart_edbg;

/** Software instance of the TC module used for calibration measurement. */
static struct tc_module tc_calib;

/** Software instance of the TC module used for calibration comparison. */
static struct tc_module tc_comp;


/** Set up the measurement and comparison timers for calibration.
 *   - Configure the measurement timer to run from the CPU clock, in capture
 *     mode.
 *   - Configure the reference timer to run from the reference clock, generating
 *     a capture every time the calibration resolution count is met.
 */
static void setup_tc_channels(void)
{
	struct tc_config config;
	tc_get_config_defaults(&config);

	/* Configure measurement timer to run from Fcpu and capture */
	config.counter_size    = TC_COUNTER_SIZE_32BIT;
	config.clock_prescaler = TC_CLOCK_PRESCALER_DIV1;
	config.wave_generation = TC_WAVE_GENERATION_NORMAL_FREQ;
	config.enable_capture_on_channel[0] = true;
	tc_init(&tc_calib, CONF_TC_MEASUREMENT, &config);

	/* Configure reference timer to run from reference clock and capture when the resolution count is met */
	config.counter_size    = TC_COUNTER_SIZE_16BIT;
	config.clock_source    = REFERENCE_CLOCK;
	config.enable_capture_on_channel[0] = false;
	config.counter_16_bit.compare_capture_channel[0] = (1 << CALIBRATION_RESOLUTION);
	tc_init(&tc_comp, CONF_TC_REFERENCE, &config);
}

/** Set up the measurement and comparison timer events.
 *   - Configure the reference timer to generate an event upon comparison
 *     match with channel 0.
 *   - Configure the measurement timer to trigger a capture when an event is
 *     received.
 */
static void setup_tc_events(void)
{
	/* Enable incoming events on on measurement timer */
	struct tc_events events_calib = { .on_event_perform_action = true };
	tc_enable_events(&tc_calib, &events_calib);

	/* Generate events from the reference timer on channel 0 compare match */
	struct tc_events events_comp = { .generate_event_on_compare_channel[0] = true };
	tc_enable_events(&tc_comp, &events_comp);

	tc_enable(&tc_calib);
	tc_enable(&tc_comp);
}

/** Set up the event system, linking the measurement and comparison timers so
 *  that events generated from the reference timer are linked to the measurement
 *  timer.
 */
static void setup_events(struct events_resource *event)
{
	struct events_config config;

	events_get_config_defaults(&config);

	/* The event channel detects rising edges of the reference timer output
	 * event */
	config.edge_detect    = EVENTS_EDGE_DETECT_RISING;
	config.path           = EVENTS_PATH_SYNCHRONOUS;
	config.generator      = CONF_EVENT_GENERATOR_ID;

	events_allocate(event, &config);
	events_attach_user(event, CONF_EVENT_USED_ID);

}

/** Set up the USART for transmit-only communication at a fixed baud rate. */
static void setup_usart_channel(void)
{
	struct usart_config cdc_uart_config;
	usart_get_config_defaults(&cdc_uart_config);

	/* Configure the USART settings and initialize the standard I/O library */
	cdc_uart_config.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	cdc_uart_config.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	cdc_uart_config.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	cdc_uart_config.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	cdc_uart_config.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	cdc_uart_config.baudrate    = 115200;
	stdio_serial_init(&usart_edbg, EDBG_CDC_MODULE, &cdc_uart_config);

	usart_enable(&usart_edbg);
}

/** Set up the clock output pin so that the current system clock frequency can
 *  be monitored via an external frequency counter or oscilloscope. */
static void setup_clock_out_pin(void)
{
	struct system_pinmux_config pin_mux;
	system_pinmux_get_config_defaults(&pin_mux);

	/* MUX out the system clock to a I/O pin of the device */
	pin_mux.mux_position = CONF_CLOCK_PIN_MUX;
	system_pinmux_pin_set_config(CONF_CLOCK_PIN_OUT, &pin_mux);
}

/** Retrieves the current system clock frequency, computed from the reference
 *  clock.
 *
 * \return Current system clock frequency in Hz.
 */
static uint32_t get_osc_frequency(void)
{
	/* Clear any existing match status on the measurement timer */
	tc_clear_status(&tc_comp, TC_STATUS_CHANNEL_0_MATCH);

	/* Restart both measurement and reference timers */
	tc_start_counter(&tc_calib);
	tc_start_counter(&tc_comp);

	/* Wait for the measurement timer to signal a compare match */
	while (!(tc_get_status(&tc_comp) & TC_STATUS_CHANNEL_0_MATCH)) {
		/* Wait for channel 0 match */
	}

	/* Compute the real clock frequency from the measurement timer count and
	 * reference count */
	uint64_t tmp = tc_get_capture_value(&tc_calib, TC_COMPARE_CAPTURE_CHANNEL_0);
	return ((tmp * REFERENCE_CLOCK_HZ) >> CALIBRATION_RESOLUTION);
}

int main(void)
{
	struct events_resource event;

	/* System initialization */
	system_init();
	delay_init();

	/* Module initialization */
	setup_tc_channels();
	setup_tc_events();
	setup_events(&event);
	setup_clock_out_pin();

	/* Init the variables with default calibration settings */
	uint8_t frange_cal = SYSCTRL->OSC8M.bit.FRANGE;
	uint8_t temp_cal = SYSCTRL->OSC8M.bit.CALIB >> TEMP_CAL_OFFSET;
	uint8_t comm_cal = SYSCTRL->OSC8M.bit.CALIB & COMM_CAL_MAX;
	/* Set the calibration test range */
	uint8_t frange_cal_min = max((frange_cal - CONF_FRANGE_CAL), FRANGE_CAL_MIN);
	uint8_t frange_cal_max = min((frange_cal + CONF_FRANGE_CAL), FRANGE_CAL_MAX);
	uint8_t temp_cal_min = max((temp_cal - CONF_TEMP_CAL), TEMP_CAL_MIN);
	uint8_t temp_cal_max = min((temp_cal + CONF_TEMP_CAL), TEMP_CAL_MAX);

	/* Variables to track the previous and best calibration settings */
	uint16_t comm_best   = 0;
	uint8_t  frange_best = 0;
	uint32_t freq_best   = 0;
	uint32_t freq_before = get_osc_frequency();

	/* Run calibration loop */
	for (frange_cal = frange_cal_min; frange_cal <= frange_cal_max; frange_cal++) {
		for (temp_cal = temp_cal_min; temp_cal <= temp_cal_max; temp_cal++) {
			for (comm_cal = COMM_CAL_MIN; comm_cal <= COMM_CAL_MAX; comm_cal++) {
				/* Set the test calibration values */
				system_clock_source_write_calibration(
						SYSTEM_CLOCK_SOURCE_OSC8M, (temp_cal << 7) | comm_cal, frange_cal);

				/* Wait for stabilization */
				delay_cycles(1000);

				/* Compute the deltas of the current and best system clock
				 * frequencies, save current settings if they are closer to the
				 * ideal frequency than the previous best values
				 */
				uint32_t freq_current = get_osc_frequency();
				if (abs(freq_current - TARGET_FREQUENCY) < abs(freq_best - TARGET_FREQUENCY)) {
					freq_best   = freq_current;
					comm_best   = comm_cal;
					frange_best = frange_cal;

					port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
				} else {
					port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
				}
			}
		}
	}

	/* Set the found best calibration values */
	system_clock_source_write_calibration(
			SYSTEM_CLOCK_SOURCE_OSC8M, (temp_cal << 7) | comm_best, frange_best);

	/* Setup USART module to output results */
	setup_usart_channel();

	/* Write previous and current frequency and new calibration settings to the
	 * USART
	 */
	printf("Freq Before: %lu\r\n", freq_before);
	printf("Freq Best: %lu\r\n", freq_best);

	printf("Freq Range: %u\r\n", frange_best);
	printf("Calib Value: 0x%x\r\n", (temp_cal << 7) | comm_best);

	/* Rapidly flash the board LED to signal the calibration completion */
	while (1) {
		port_pin_toggle_output_level(LED_0_PIN);
		delay_ms(200);
	}
}
