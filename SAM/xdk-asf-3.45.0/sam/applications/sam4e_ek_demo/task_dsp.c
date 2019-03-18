/**
 * \file
 *
 * \brief DSP task for the FreeRTOS Web/DSP Demo.
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

#include "task_demo.h"
#include "arm_math.h"
#if (__CM4_CMSIS_VERSION_MAIN >= (0x04))
#include "arm_const_structs.h"
#endif
#include "sound.h"
#include "pdc.h"
#include "afec.h"
#include "tc.h"
#include "dacc.h"
#include "conf_uart_serial.h"
#include "pio.h"
#include "pio_handler.h"
#include <stdio_serial.h>
#include <serial.h>

/** Sound sampling frequency. */
#define SAMPLING_FREQUENCY  22050UL

/** ADC definitions. */
#define ADC_CHANNEL_POTENTIOMETER  AFEC_CHANNEL_5
#define ADC_CHANNEL_MICROPHONE     AFEC_CHANNEL_4
#define ADC_POTENTIOMETER_NOISE    10

/** DACC related definitions. */
#define SPEAKER_CHANNEL_R          DACC_MR_USER_SEL_CHANNEL0
#define SPEAKER_CHANNEL_L          DACC_MR_USER_SEL_CHANNEL1
#define DACC_REFRESH               1

/** TC related definitions */
#define TC_RC                      (BOARD_MCK / 2 / SAMPLING_FREQUENCY)
#define TC_RA                      (TC_RC / 2)

/** IRQ priority for PIO (The lower the value, the greater the priority). */
#define IRQ_PRIOR_PIO              5

/** Voice changer step in hertz. */
#define VOICE_CHANGER_DELTA        100UL

/** Numbers Definitions related to the FFT calculation */
#define SAMPLE_BLOCK_SIZE          256UL

/** Wave file offset in bytes. */
/* Normal wave offset should be 44. But the next 4 bytes are meaningless. */
#define WAVE_OFFSET                (44 + 4)

/**
 * Interrupt priorities. (lowest value = highest priority)
 * ISRs using FreeRTOS *FromISR APIs must have priorities below or equal to
 * configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY.
 */
#define INT_PRIORITY_DACC   configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY
#define INT_PRI_PUSHBUTTON  (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 2)

static void dsp_task(void *pvParameters);
static void dsp_configure_tc(void);
static void dsp_configure_adc(void);
static void dsp_configure_dacc(void);
static void dsp_sin_init(void);
static void dsp_sin_input(float32_t freq);
static void dsp_configure_button2(void);
static void dsp_event_button2(uint32_t id, uint32_t mask);
static void dsp_clean_buffer(uint16_t *buffer, uint32_t size);

static const portTickType max_block_time_ticks = 200UL / portTICK_RATE_MS;
static portBASE_TYPE higher_priority_task_woken = pdFALSE;

/** PDC data packet. */
pdc_packet_t g_pdc_packet, g_pdc_nextpacket;

/** Pointer to current PDC buffer in use. */
static uint32_t cur_dac_buffer = 2;

/** Pointer to PDC register base. */
Pdc *dacc_pdc;

/** Wave/Sinus mode selection. */
uint32_t g_mode_select = 1;

/** Notification semaphores. */
xSemaphoreHandle dacc_notification_semaphore = NULL;
xSemaphoreHandle gfx_notification_semaphore = NULL;

/** Backup previous adc potentiometer value. */
static uint32_t adc_potentiometer_old = 0;

/** Output buffer for DACC. */
static uint16_t dacc_out_buffer[3][SAMPLE_BLOCK_SIZE];

/** Generated sinus signal for voice modulation. */
static float32_t sin_buffer[SLIDER_SELECTOR_NB][SAMPLE_BLOCK_SIZE];

float32_t wav_in_buffer[SAMPLE_BLOCK_SIZE * 2];

/** q15 cFFT buffer declaration */
static q15_t cfft_q15[SAMPLE_BLOCK_SIZE * 2];
/** q15 Magnitude buffer declaration */
static q15_t mag_in_buffer_q15[SAMPLE_BLOCK_SIZE];

/** Magnitude buffer converted in float */
float32_t mag_in_buffer[SAMPLE_BLOCK_SIZE];
/** Magnitude buffer converted in float */
uint32_t mag_in_buffer_int[SAMPLE_BLOCK_SIZE];

/** Slider position, used as sin_buffer table index. */
extern uint8_t slider_pos;

/** Pointer to the wave file. */
uint32_t offset = WAVE_OFFSET;

/**
 * \brief DACC interrupt handler.
 */
void DACC_Handler(void)
{
	uint32_t isr = dacc_get_interrupt_status(DACC);

	/** Check if one PDC buffer has been received. */
	if (isr & DACC_ISR_ENDTX) {
		/** Add cur_dac_buffer as next transfert for PDC. */
		g_pdc_nextpacket.ul_addr = (uint32_t) dacc_out_buffer[cur_dac_buffer];
		g_pdc_nextpacket.ul_size = SAMPLE_BLOCK_SIZE;
		pdc_tx_init(dacc_pdc, NULL, &g_pdc_nextpacket);

		/** Notify DSP task to start data processing. */
		xSemaphoreGiveFromISR(dacc_notification_semaphore,
				&higher_priority_task_woken);

		/** Use next PDC buffer for ADC and DACC. */
		cur_dac_buffer = (cur_dac_buffer + 1) % 3;
	}
}

/**
 * \brief Create the DSP task.
 *
 * \param stack_depth_words Task stack size in 32 bits word.
 * \param task_priority Task priority.
 */
void create_dsp_task(uint16_t stack_depth_words,
		unsigned portBASE_TYPE task_priority)
{
	/*
	 * Asynchronous operation requires a notification semaphore.
	 * First, create the semaphore.
	 */
	vSemaphoreCreateBinary(dacc_notification_semaphore);
	vSemaphoreCreateBinary(gfx_notification_semaphore);

	/* Then set the semaphore into the correct initial state. */
	xSemaphoreTake(dacc_notification_semaphore, 0);
	xSemaphoreTake(gfx_notification_semaphore, 0);

	/* Create the task as described above. */
	xTaskCreate(dsp_task, (const signed char *const) "DSP",
			stack_depth_words, NULL, task_priority,
			NULL);
}

/**
 * \brief DSP task core function.
 *
 * \param pvParameters Junk parameter.
 */
static void dsp_task(void *pvParameters)
{
	uint32_t i, j;
	uint32_t adc_potentiometer = 0;
	const float32_t display_factor = 700;
	float32_t bin;
	float32_t tmp;

	/* Just to avoid compiler warnings. */
	UNUSED(pvParameters);

	/* Wait for user to read instructions. */
	WAIT_FOR_TOUCH_EVENT;

	dsp_configure_button2();
	dsp_configure_tc();
	dsp_configure_adc();
	dsp_configure_dacc();
	dsp_sin_init();

	/* Enable PDC transfer. */
	dsp_clean_buffer(dacc_out_buffer[0], SAMPLE_BLOCK_SIZE);
	dsp_clean_buffer(dacc_out_buffer[1], SAMPLE_BLOCK_SIZE);
	dsp_clean_buffer(dacc_out_buffer[2], SAMPLE_BLOCK_SIZE);
	g_pdc_packet.ul_addr = (uint32_t) dacc_out_buffer[0];
	g_pdc_packet.ul_size = SAMPLE_BLOCK_SIZE;
	g_pdc_nextpacket.ul_addr = (uint32_t) dacc_out_buffer[1];
	g_pdc_nextpacket.ul_size = SAMPLE_BLOCK_SIZE;
	pdc_tx_init(dacc_pdc, &g_pdc_packet, &g_pdc_nextpacket);
	pdc_enable_transfer(dacc_pdc, PERIPH_PTCR_TXTEN);

	/* Start Timer counter 0 channel 0 for ADC-DACC trigger. */
	tc_start(TC0, 1);

	/** DSP task loop. */
	while (1) {
		/* Using input wave signal. */
		if (g_mode_select == 1) {
			if (xSemaphoreTake(dacc_notification_semaphore, max_block_time_ticks)) {
				/* Copy dsp_sfx into wav_in_buffer and prepare Q15 format. */
				for (i = 0, j = 0; i < 512; ++j) {
					tmp = (((dsp_sfx[offset] - (float) 128)) / 100);

					/* Store Audio sample real part in memory. */
					wav_in_buffer[i++] = tmp;

					/* Store Audio sample imaginary part in memory. */
					wav_in_buffer[i++] = 0;

					/* Prepare buffer for DACC. */
					dacc_out_buffer[cur_dac_buffer][j] = (uint16_t)((tmp * 100
							* sin_buffer[slider_pos][j]) + 128);

					/* Update the wave file offset pointer. */
					if (offset < dsp_sfx_size - 1) {
						offset++;
					} else {
						offset = WAVE_OFFSET;
					}
				}
			} else {
				/* Ensure we take the semaphore. */
				continue;
			}
		} else {
			/* Using generated input sinus signal. */
			if (xSemaphoreTake(dacc_notification_semaphore, max_block_time_ticks)) {
				/*
				 * Read potentiometer value and generate
				 * sinus signal accordingly.
				 */
				adc_potentiometer_old = adc_potentiometer;
				adc_potentiometer = (afec_channel_get_value(AFEC0,
						ADC_CHANNEL_POTENTIOMETER));
				adc_potentiometer = adc_potentiometer * 10000 / 4096;
				if (adc_potentiometer > adc_potentiometer_old &&
						adc_potentiometer -
						adc_potentiometer_old < ADC_POTENTIOMETER_NOISE) {
					adc_potentiometer = adc_potentiometer_old;
				} else if (adc_potentiometer_old > adc_potentiometer &&
						adc_potentiometer_old -
						adc_potentiometer < ADC_POTENTIOMETER_NOISE) {
					adc_potentiometer = adc_potentiometer_old;
				}

				/* Generate the sinus signal. */
				dsp_sin_input(adc_potentiometer);

				/* Prepare buffer for DACC. */
				for (i = 0, j = 0; i < 512; ++j, i += 2) {
					/*
					 * 2048 is the 0 position for DACC.
					 * 50 is an amplification factor.
					 */
					dacc_out_buffer[cur_dac_buffer][j] =
					(uint16_t)((wav_in_buffer[i] * sin_buffer[slider_pos][j])
							* 50 + 2048);
				}

			}
		}

		afec_start_software_conversion(AFEC0);

		/* Perform FFT and bin Magnitude calculation */
		arm_float_to_q15(wav_in_buffer, cfft_q15, SAMPLE_BLOCK_SIZE * 2);
#if (__CM4_CMSIS_VERSION_MAIN >= (0x04))
		arm_cfft_q15(&arm_cfft_sR_q15_len256, cfft_q15, 0, 1);
#else
		/** cFFT configuration instance declaration */
		arm_cfft_radix4_instance_q15 cfft_instance;
		arm_cfft_radix4_init_q15(&cfft_instance, SAMPLE_BLOCK_SIZE, 0, 1);
		arm_cfft_radix4_q15(&cfft_instance, cfft_q15);
#endif
		arm_cmplx_mag_q15(cfft_q15, mag_in_buffer_q15, SAMPLE_BLOCK_SIZE);
		arm_q15_to_float(mag_in_buffer_q15, mag_in_buffer, 128);

		/*
		 * Prepare bins rendering for web page and display.
		 * Limit to 99, even if we got 128 magnitudes to display.
		 * Bins are printed using col, incremented by mean of 2 to keep
		 * a clean rendering. Hence we cannot render all the magnitudes,
		 * because of the screen width. It would require a 128*2 space.
		 */
		for (i = 0; i < 99; ++i) {
			bin = (mag_in_buffer[i] * display_factor);
			if (bin > 0) {
				if (bin > 98) {
					bin = 98;
				}
				mag_in_buffer_int[i] = (uint32_t)bin;
			} else {
				mag_in_buffer_int[i] = 0;
			}
		}

		/* Notify GFX task to start refreshing screen (if necessary). */
		if (g_mode_select == 1 || (g_mode_select == 0 &&
				adc_potentiometer != adc_potentiometer_old)) {
			xSemaphoreGive(gfx_notification_semaphore);
		}
	}
}

/**
 * \brief TC configuration.
 */
static void dsp_configure_tc(void)
{
	pmc_enable_periph_clk(ID_TC1);

	/*
	 * Init timer counter 0
	 * RC Compare Effect on TIOA "SET"
	 * Waveform Mode is enabled
	 * UP mode with automatic trigger on RC Compare
	 */
	tc_init(TC0, 1,
			TC_CMR_ACPC_SET | TC_CMR_WAVE |
			TC_CMR_WAVSEL_UP_RC |TC_CMR_ACPA_CLEAR );

	/* Load in TC RA register */
	tc_write_ra(TC0, 1, TC_RA);
	/* Load in TC RC register */
	tc_write_rc(TC0, 1, TC_RC);
}

/**
 * \brief AFEC(ADC) configuration.
 */
static void dsp_configure_adc(void)
{
	pmc_enable_periph_clk(ID_AFEC0);

	struct afec_config afec_cfg;
	struct afec_ch_config afec_ch_cfg;

	/* AFEC0 enable, init and configuration*/
	afec_enable(AFEC0);
	afec_get_config_defaults(&afec_cfg);
	afec_init(AFEC0, &afec_cfg);

	/* Set to Software trigger*/
	afec_set_trigger(AFEC0, AFEC_TRIG_SW);

	/* AFEC0 channals configuration*/
	afec_channel_enable(AFEC0,ADC_CHANNEL_POTENTIOMETER);
	afec_ch_get_config_defaults(&afec_ch_cfg);
	afec_ch_set_config(AFEC0, ADC_CHANNEL_POTENTIOMETER,&afec_ch_cfg);
	afec_ch_set_config(AFEC0, AFEC_TEMPERATURE_SENSOR, &afec_ch_cfg);

	/*
	 * Because the internal ADC offset is 0x800, it should cancel it and
	 * shift down to 0.
	 */
	afec_channel_set_analog_offset(AFEC0, ADC_CHANNEL_POTENTIOMETER, 0x800);
	afec_channel_set_analog_offset(AFEC0, AFEC_TEMPERATURE_SENSOR, 0x800);

	afec_channel_enable(AFEC0,AFEC_TEMPERATURE_SENSOR);
	afec_channel_enable(AFEC0,ADC_CHANNEL_MICROPHONE);

	struct afec_temp_sensor_config afec_temp_sensor_cfg;

	afec_temp_sensor_get_config_defaults(&afec_temp_sensor_cfg);
	afec_temp_sensor_cfg.rctc = true;
	afec_temp_sensor_set_config(AFEC0, &afec_temp_sensor_cfg);

	/* Perform an auto cab on the ADC Channel 4. */
	afec_start_calibration(AFEC0);
	while((afec_get_interrupt_status(AFEC0) & AFEC_ISR_EOCAL) !=
			AFEC_ISR_EOCAL);

	/* Enable potentiometer channel, disable microphone. */
	afec_channel_disable(AFEC0, ADC_CHANNEL_MICROPHONE);
	afec_channel_enable(AFEC0, AFEC_TEMPERATURE_SENSOR);
	afec_channel_enable(AFEC0, ADC_CHANNEL_MICROPHONE);

	/* Start the first conversion*/
	afec_start_software_conversion(AFEC0);
}

/**
 * \brief DACC configuration.
 */
static void dsp_configure_dacc(void)
{
	pmc_enable_periph_clk(ID_DACC);

	/*
	 * DACC setting
	 * -No max Speed Mode
	 * -Startup time of 0 periods of DACClock
	 */
	dacc_set_timing(DACC, 0, DACC_MR_STARTUP_0);

	/* Set TIO Output of TC Channel 1 as trigger */
	dacc_set_trigger(DACC,2);

	/* Set to half word transfer */
	dacc_set_transfer_mode(DACC, DACC_MR_WORD_HALF);

#if (SAM3S) || (SAM3XA)
	/* Set to No Sleep Mode and No Fast Wake Up Mode*/
	dacc_set_power_save(DACC, 0, 0);
#endif

	/* Select both left/right speaker channels. */
	dacc_set_channel_selection(DACC, SPEAKER_CHANNEL_R);
	dacc_set_channel_selection(DACC, SPEAKER_CHANNEL_L);

	/* Enable DACC channels. */
	dacc_enable_channel(DACC, SPEAKER_CHANNEL_R);
	dacc_enable_channel(DACC, SPEAKER_CHANNEL_L);

	/* Tag selection mode enabled. */
	dacc_enable_flexible_selection(DACC);

	/* Get board DACC PDC base address. */
	dacc_pdc = dacc_get_pdc_base(DACC);

	/* Enable DACC interrupt. */
	dacc_enable_interrupt(DACC,DACC_IER_ENDTX);
	NVIC_SetPriority(DACC_IRQn, INT_PRIORITY_DACC);
	NVIC_EnableIRQ(DACC_IRQn);
}

/**
 * \brief Generate sinusoidale signals for voice changing.
 */
static void dsp_sin_init(void)
{
	uint32_t i;
	uint32_t j;
	float32_t ratio;
	float32_t freq;

	freq = SAMPLING_FREQUENCY;

	for (j = 0; j < SLIDER_SELECTOR_NB; ++j) {

		/* Generate a sinus based on sampling freq with a delta. */
		ratio = freq / SAMPLING_FREQUENCY;

		for (i = 0 ; i < SAMPLE_BLOCK_SIZE; i++) {
			/* Amplification is set to 1. */
			if (ratio <= 1.0) {
				/* It won't change anything. */
				sin_buffer[j][i] = 1;
			} else {
				sin_buffer[j][i] = arm_sin_f32(2 * PI * i * ratio);
			}
		}

		/* Increase delta. */
		freq += VOICE_CHANGER_DELTA;
	}
}

/**
 * \brief Generate a sinus input signal.
 *
 * \param freq Sinus frequency.
 */
static void dsp_sin_input(float32_t freq)
{
	uint32_t i;
	uint32_t y;
	float32_t ratio;

	if (freq < 1) {
		freq = 1;
	}

	ratio = freq / SAMPLING_FREQUENCY;

	for (i = 0, y = 0; i < SAMPLE_BLOCK_SIZE; i++) {
		/* Amplification is set to 1. */
		wav_in_buffer[y++] = arm_sin_f32(2 * PI * i * ratio);
		wav_in_buffer[y++] = 0;
	}
}

/**
 * \brief Clean the specified sound buffer with the 8 bits mediane value.
 *
 * \param buffer Buffer to clean..
 * \param size Buffer size.
 */
static void dsp_clean_buffer(uint16_t *buffer, uint32_t size)
{
	uint32_t i;

	for (i = 0; i < size; ++i){
		buffer[i] = 128;
	}
}

/**
 * \brief Configure the push button 1.
 *
 * \note Configure the PIO as input and generate corresponding interrupt
 * when pressed or released.
 */
static void dsp_configure_button2(void)
{
	/* Configure Pushbutton 1. */
	pmc_enable_periph_clk(PIN_PUSHBUTTON_2_ID);
	pio_set_debounce_filter(PIN_PUSHBUTTON_2_PIO,
			PIN_PUSHBUTTON_2_MASK, 10);
	pio_handler_set(PIN_PUSHBUTTON_2_PIO, PIN_PUSHBUTTON_2_ID,
			PIN_PUSHBUTTON_2_MASK, PIN_PUSHBUTTON_2_ATTR,
			dsp_event_button2);

	/* Take care of NVIC_SetPriority. */
	pio_handler_set_priority(PIN_PUSHBUTTON_2_PIO,
			(IRQn_Type) PIN_PUSHBUTTON_2_ID,
			INT_PRI_PUSHBUTTON);
	pio_enable_interrupt(PIN_PUSHBUTTON_2_PIO, PIN_PUSHBUTTON_2_MASK);
}

/**
 * \brief Handler for Button 1 rising edge interrupt.
 *
 * \param id The pressed button ID.
 * \param mask Button mask.
 */
static void dsp_event_button2(uint32_t id, uint32_t mask)
{
	if (PIN_PUSHBUTTON_2_ID == id && PIN_PUSHBUTTON_2_MASK == mask) {
		if (g_mode_select == 1) {
			/* Set acquisition mode to sinus generation. */
			g_mode_select = 0;
		} else {
			/* Set acquisition mode to wave file. */
			g_mode_select = 1;
		}
	}
}
