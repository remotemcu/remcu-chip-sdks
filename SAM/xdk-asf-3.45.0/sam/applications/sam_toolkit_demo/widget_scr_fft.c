/**
 * \file
 *
 * \brief FFT example for SAM toolkit demo application.
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

#include <board.h>
#include <sysclk.h>
#include <asf.h>
#include "arm_math.h"
#if (__CM4_CMSIS_VERSION_MAIN >= (0x04))
#include "arm_const_structs.h"
#endif
#include "demo.h"
#include "pdc.h"

/* Signal value MAX (12b ADC/DAC) */
#define SIGNAL_VAL_MAX 0xFFF

/* White background color */
#define BGCOLOR GFX_COLOR_WHITE

/* TC configuration for ADC/DAC sample rate */
#define TRIGGER_TC    TC0
#define TRIGGER_TC_ID ID_TC0
#define TRIGGER_TC_CH 0
/* ADC configuration */
#define ADC_CH ADC_CHANNEL_4 /* sam4: MIC */

/* DRAW */
#define DRAW_W 200
#define DRAW_H  90

#define OFFSET_X 10
#define OFFSET_Y 40

/* Q15 maximum value */
#define Q15_MAX (0.99997)

/* Q15 minimum value */
#define Q15_MIN (-1.0)

/* Q15 right most offset */
#define Q15_A   (1)

/* Q15 left most offset */
#define Q15_B   (15)

/* Signed mask for q15 */
#define Q15_SIG_MASK    (0x8000)

/* Data mask for q15 */
#define Q15_DATA_MASK    (0x7fff)

/* 16bits word length */
#define WORD_LENGTH    (16)

/* ADC variables */
uint16_t frame_buffer[AUDIO_NB_BUFFER][AUDIO_FRAME_SIZE];
uint32_t adc_nb_samples = 0;
uint8_t adc_buf_ndx = 0;
uint32_t tc_ch_rc;

/* FFT process variables */
uint16_t proc_buffer[NB_VAL * 2];
uint16_t *p_proc_src = frame_buffer[0];
uint32_t proc_ndx = 0;

/** PDC data packet. */
pdc_packet_t adc_packet, adc_nextpacket;

static void tc_trigger_init(void);
static void adc_input_init(void);
static uint32_t get_available_nb_sample(uint32_t i_index, uint32_t o_index);
static void gui_print_q15_signal(q15_t *signal, uint16_t signal_size,
		gfx_coord_t x, gfx_coord_t y, uint16_t w, uint16_t h,
		gfx_color_t fg_color, gfx_color_t bg_color);
static void gui_print_q15_bar(q15_t *signal, uint16_t signal_size,
		gfx_coord_t x, gfx_coord_t y, uint16_t w, uint16_t h,
		gfx_color_t fg_color, gfx_color_t bg_color);

static void u16_to_q15(uint16_t *p_u16, q15_t *p_q15, uint32_t size,
		uint16_t u16_max, uint16_t u16_min, bool b_centerize);

static void fft_process(q15_t *buffer, uint32_t fft_size);

extern bool fft_update;
extern uint32_t fft_delay;

/**
 * \brief Gain q15 data buffer.
 */
static void gain_q15_buffer(q15_t *buffer, uint32_t size)
{
	uint32_t i;
	for (i = 0; i < size; i++) {
		uint16_t q15_s = buffer[i] & Q15_SIG_MASK;
		int32_t result;
		if (q15_s) {
			result = (int32_t)buffer[i] * FFT_IN_GAIN;
			if (result < -Q15_SIG_MASK) {
				result = -Q15_SIG_MASK;
			}
		} else {
			result = (int32_t)buffer[i] * FFT_IN_GAIN;
			if (result > Q15_DATA_MASK) {
				result = Q15_DATA_MASK;
			}
		}

		result |= q15_s;
		buffer[i] = (q15_t)result;
	}
}

/**
 * \brief Turn on FFT example.
 */
void app_widget_fft_on(void)
{
	/* Do FrameRate test */
	int frm_cnt = 0;
	tc_trigger_init();
	adc_input_init();

	SysTick_Config(sysclk_get_cpu_hz() / SYSTICK_FREQ);

	/* Fill the whole screen with the background color */
	gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(),
			GFX_COLOR_WHITE);

	gfx_draw_string_aligned("FFT example",
			gfx_get_width() / 2, 20, &sysfont,
			BGCOLOR, GFX_COLOR_BLUE,
			TEXT_POS_CENTER, TEXT_ALIGN_LEFT);

	while ((demo_get_special_mode_status(DEMO_FFT_MODE))) {
		/* Copy ADC input to process buffer */
		uint32_t nb_samples = get_available_nb_sample(
				adc_buf_ndx * AUDIO_FRAME_SIZE, proc_ndx);
		if (nb_samples < NB_VAL) {
			/* No display update */
		}

		/* Copy samples to process buffer */
		uint32_t i;
		for (i = 0; i < NB_VAL; i++) {
			proc_buffer[i] = p_proc_src[proc_ndx];
			proc_ndx = (proc_ndx + 1) % AUDIO_BUFFER_SIZE;
		}
		/* Convert to Q15 format */
		u16_to_q15(proc_buffer, (q15_t *)proc_buffer, NB_VAL,
				SIGNAL_VAL_MAX, 0, true);
		gain_q15_buffer((q15_t *)proc_buffer, NB_VAL);

		if (nb_samples >= NB_VAL) {
			/* Draw Wave */
			gui_print_q15_signal((q15_t *)proc_buffer, NB_VAL,
					OFFSET_X + 5,
					OFFSET_Y + 1,
					DRAW_W, DRAW_H,
					GFX_COLOR_BLUE,
					GFX_COLOR_BLACK);
		}

		/* Draw FFT */
		fft_process((q15_t *)proc_buffer, NB_VAL);
		if (nb_samples >= NB_VAL) {
			/* - Draw first values the High F is cut off */
			gui_print_q15_bar((q15_t *)proc_buffer,
					(NB_VAL * MAX_FFT_DISP_FREQ /
					AUDIO_SAMPLE_RATE)
					& 0xFFFFFFFE,
					OFFSET_X + 5,
					OFFSET_Y + 5 + DRAW_H,
					DRAW_W, DRAW_H,
					GFX_COLOR_BLUE,
					GFX_COLOR_BLACK);
		}

		frm_cnt++;
		if (fft_delay >= SYSTICK_FREQ) {
			/* ADC sample rate */
			if (adc_nb_samples < AUDIO_SAMPLE_RATE) {
				/* Faster trigger */
				tc_ch_rc--;
				tc_write_ra(TRIGGER_TC, TRIGGER_TC_CH,
						tc_ch_rc / 2);
				tc_write_rc(TRIGGER_TC, TRIGGER_TC_CH,
						tc_ch_rc);
			} else if (adc_nb_samples > AUDIO_SAMPLE_RATE) {
				/* Slower trigger */
				tc_ch_rc++;
				tc_write_ra(TRIGGER_TC, TRIGGER_TC_CH,
						tc_ch_rc / 2);
				tc_write_rc(TRIGGER_TC, TRIGGER_TC_CH,
						tc_ch_rc);
			}

			adc_nb_samples = 0;

			/* Update  */
			fft_delay = 0;
		}
	}
}

/**
 * \brief Display 1.15 format data with signal.
 *
 * \param signal Signal value.
 * \param signal_size Signal size.
 * \param x Position X.
 * \param y Position Y.
 * \param w Width.
 * \param h Height.
 * \param fg_color foreground color.
 * \param bg_color background color. 
 *
 * \return True if exiting, to destroy the window
 */
static void gui_print_q15_signal(q15_t *signal, uint16_t signal_size,
		gfx_coord_t x, gfx_coord_t y, uint16_t w, uint16_t h,
		gfx_color_t fg_color, gfx_color_t bg_color)
{
	uint16_t t, cur_y;
	uint32_t scale_x, scale_y;
	uint32_t i_signal;
	uint16_t last_y = h / 2;

	/* Compute scaling coefficients */
	scale_y = (uint32_t)(((h / 2) << WORD_LENGTH) / ((uint32_t)(-Q15_MIN)));

	if (signal_size >= w) {
		/* Speed drawing */
		scale_x = (uint32_t)(signal_size << WORD_LENGTH) / w;
		for (t = 0; t < w; t++) {
			/* Clear line */
			gfx_draw_filled_rect(x + t, y, 1, h, bg_color);

			i_signal = ((uint64_t)t * scale_x) >> WORD_LENGTH;
			/* Integer value */
			cur_y = (((uint64_t)signal[i_signal] * scale_y) >> WORD_LENGTH) >> Q15_B;
			cur_y = h / 2 - cur_y - 1;
			gfx_draw_line(x + t, y + last_y, x + t, y + cur_y,
					fg_color);
			last_y = cur_y;
		}
	} else {
		uint16_t prev_t = 0, prev_y = 0;

		/* Fine drawing */
		scale_x = (((uint32_t)(w * (signal_size + 1))
				/ signal_size) << WORD_LENGTH) / signal_size;
		for (i_signal = 0; i_signal < signal_size; i_signal++) {
			t = ((uint64_t)i_signal * scale_x) >> WORD_LENGTH;
			cur_y = (((uint64_t)signal[i_signal] * scale_y)
					>> WORD_LENGTH) >> Q15_B;
			cur_y = h / 2 - cur_y - 1;
			/* Draw a line between points */
			if (i_signal) {
				/* Clear block */
				gfx_draw_filled_rect(
						x + Min(prev_t, t),
						y + Min(prev_y, cur_y),
						Abs(t - prev_t) - 1, h - 1,
						bg_color);
				/* Draw line */
				gfx_draw_line(x + prev_t, prev_y,
						x + t, cur_y, fg_color);
			}

			prev_t = t;
			prev_y = cur_y;
		}
	}
}

/**
 * \brief Display 1.15 format data with bar.
 *
 * \param signal Signal value.
 * \param signal_size Signal size.
 * \param x Position X.
 * \param y Position Y.
 * \param w Width.
 * \param h Height.
 * \param fg_color foreground color.
 * \param bg_color background color. 
 */
static void gui_print_q15_bar(q15_t *signal, uint16_t signal_size,
		gfx_coord_t x, gfx_coord_t y, uint16_t w, uint16_t h,
		gfx_color_t fg_color, gfx_color_t bg_color)
{
	uint16_t t, cur_y;
	uint32_t scale_x, scale_y;
	uint32_t i_signal;
	uint16_t i;

	/* Compute scaling coefficients */
	scale_y = (uint32_t)
			((h << WORD_LENGTH) / ((uint32_t)(-Q15_MIN)));

	if (signal_size >= w) {
		scale_x = (uint32_t)(signal_size << WORD_LENGTH) / w;
		for (t = 0; t < w; t++) {
			/* Clear line */
			gfx_draw_filled_rect(x + t, y, 1, h, bg_color);

			i_signal = ((uint64_t)t * scale_x) >> WORD_LENGTH;
			/* Integer value */
			cur_y = (((uint64_t)signal[i_signal] * scale_y)
					>> WORD_LENGTH) >> Q15_B;
			if (cur_y <= 0) {
				cur_y = 1;
			}

			cur_y = h - cur_y;
			if (cur_y <= 0) {
				cur_y = 1;
			}

			gfx_draw_line(x + t, cur_y, x + t - 1, h - 1, fg_color);
		}
	} else {
		uint16_t prev_t = 0;

		scale_x = (((uint32_t)(w * (signal_size + 1))
				/ signal_size) << WORD_LENGTH) / signal_size;
		for (i_signal = 0; i_signal < signal_size; i_signal++) {
			t = ((uint64_t)i_signal * scale_x) >> WORD_LENGTH;
			cur_y = (((uint64_t)signal[i_signal] * scale_y)
					>> WORD_LENGTH) >> Q15_B;
			if (cur_y <= 0) {
				cur_y = 1;
			}

			cur_y = h - cur_y;
			if (cur_y <= 0) {
				cur_y = 1;
			}

			/* Clear line */
			gfx_draw_filled_rect(x + prev_t, y,
					t - prev_t, h, bg_color);
			#if 0
			gfx_draw_filled_rect(x + prev_t, y + cur_y,
					t - prev_t - 1, h - cur_y - 1,
					fg_color);
			#else
			/* Draw vertical lines */
			for (i = prev_t; i < t; i++) {
				uint16_t temp_y;
				for (temp_y = cur_y; temp_y < h;
						temp_y++) {
					gfx_draw_pixel(x + i, y + temp_y,
							fg_color);
				}
			}
			#endif
			prev_t = t;
		}
	}
}

/**
 * \brief Convert unsigned short to 1.15 format.
 *
 * \param p_u16 Unsigned short value.
 * \param p_q15 Pointer to the converted data.
 * \param size data size.
 * \param u16_max Maximum unsigned short value.
 * \param u16_min Minimum unsigned short value.
 * \param b_centerize Is centerized.
 */
static void u16_to_q15(uint16_t *p_u16, q15_t *p_q15, uint32_t size,
		uint16_t u16_max, uint16_t u16_min, bool b_centerize)
{
	uint32_t i;
	uint16_t u16_pp = u16_max - u16_min;
	if (b_centerize) {
		for (i = 0; i < size; i++) {
			p_u16[i] -= u16_pp / 2;
			p_q15[i]  = (q15_t)
					((uint32_t)p_u16[i] * Q15_SIG_MASK / u16_pp);
		}
	} else {
		for (i = 0; i < size; i++) {
			p_q15[i] = (q15_t)
					((uint32_t)p_u16[i] * Q15_SIG_MASK / u16_pp);
		}
	}
}

/**
 * \brief Process FFT.
 *
 * \param buffer Pointer to the data buffer.
 * \param fft_size Size to process.
 */
static void fft_process(q15_t *buffer, uint32_t fft_size)
{
	uint32_t i;
	uint32_t ifft_flag = 0;
	uint32_t do_bit_reverse = true;
	/* Convert input to {real[0], imag[0], real[1], imag[1],...} */
	for (i = fft_size; i; i--) {
		buffer[2 * i] = buffer[i - 1];
		buffer[2 * i - 1] = 0;
	}

#if (__CM4_CMSIS_VERSION_MAIN >= (0x04))
	arm_cfft_q15(&arm_cfft_sR_q15_len256, buffer, ifft_flag, do_bit_reverse);
#else
	arm_cfft_radix4_instance_q15 S;
	arm_cfft_radix4_init_q15(&S, fft_size, ifft_flag, do_bit_reverse);
	arm_cfft_radix4_q15(&S, buffer);
#endif
	arm_cmplx_mag_q15(buffer, buffer, fft_size);
	/* FFT output gain */
	for (i = 0; i < fft_size; i++) {
		buffer[i] = (buffer[i] * FFT_OUT_GAIN) % Q15_SIG_MASK;
	}
}

/**
 * \brief Initialize TC trigger.
 */
static void tc_trigger_init(void)
{
	uint32_t ra, rc;
	uint32_t tc_div, tc_clks;
	pmc_enable_periph_clk(TRIGGER_TC_ID);
	tc_find_mck_divisor(AUDIO_SAMPLE_RATE, sysclk_get_cpu_hz(),
			&tc_div, &tc_clks, sysclk_get_cpu_hz());
	tc_init(TRIGGER_TC, TRIGGER_TC_CH, (tc_clks << TC_CMR_TCCLKS_Pos)
			| TC_CMR_WAVE | TC_CMR_ACPA_SET | TC_CMR_ACPC_CLEAR
			| TC_CMR_CPCTRG);
	rc = (sysclk_get_cpu_hz() / tc_div) / (AUDIO_SAMPLE_RATE);
	ra = rc / 2;
	tc_ch_rc = rc;
	tc_write_ra(TRIGGER_TC, TRIGGER_TC_CH, ra);
	tc_write_rc(TRIGGER_TC, TRIGGER_TC_CH, rc);
	tc_start(TRIGGER_TC, TRIGGER_TC_CH);
}

/**
 * \brief Initialize ADC input.
 */
static void adc_input_init(void)
{
	Pdc* adc_pdc;
	pmc_enable_periph_clk(ID_ADC);
	/* Init ADC */
	adc_init(ADC, sysclk_get_cpu_hz(), AUDIO_SAMPLE_RATE * 40, ADC_STARTUP_TIME_8);
	/* Set timing */
	adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);
	/* Set trigger */
	adc_configure_trigger(ADC, ADC_TRIG_TIO_CH_0, ADC_MR_FREERUN_OFF);
	/* Disable ADC */
	adc_disable_anch(ADC);

	/* Setup PDC */
	adc_pdc = adc_get_pdc_base(ADC);
	adc_packet.ul_addr = (uint32_t)frame_buffer[0];
	adc_packet.ul_size = AUDIO_FRAME_SIZE;
	adc_nextpacket.ul_addr = (uint32_t)frame_buffer[1];
	adc_nextpacket.ul_size = AUDIO_FRAME_SIZE;
	pdc_rx_init(adc_pdc, &adc_packet, &adc_nextpacket);
	pdc_enable_transfer(adc_pdc, PERIPH_PTCR_RXTEN);

	/* Enable channel */
	adc_enable_channel(ADC, ADC_CH);
	/* Enable ADC interrupt */
	adc_enable_interrupt(ADC, ADC_IER_ENDRX);
	NVIC_EnableIRQ((IRQn_Type)ID_ADC);
}

/**
 * \brief Get available number of sample data.
 */
static uint32_t get_available_nb_sample(uint32_t i_index, uint32_t o_index)
{
	if (i_index >= o_index) {
		return (i_index - o_index);
	}

	return (i_index + AUDIO_BUFFER_SIZE - o_index);
}
