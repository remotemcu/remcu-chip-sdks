/**
 * \file
 *
 * \brief Analog-to-Digital Converter Interface Example for SAM4L.
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

/**
 * \mainpage Analog-to-Digital Converter Interface Example
 *
 * \section Purpose
 *
 * The adcife_example demonstrates how to set up the module and perform conversions.
 *
 * \section Requirements
 *
 * This example can be used on the following boards:
 * - SAM4L-EK
 * - SAM4L Xplained Pro
 * - SAM4L8 Xplained Pro
 *
 * We select the internal DAC = 826mv and scaled VCC(VCC/10 = 330mv) as positive
 * input to ADCIFE.
 *
 * \section Description
 *
 * This application shows how to use ADCIFE using the several modes:
 * with/without PDC, several types of trigger (Software, Continuous,
 * Internal Timer, etc.),gain selection. The SAM4L controller initialize
 * the ADCIFE and display the converted value in the terminal. Users can
 * also select different modes by configuration menu in the terminal.
 *
 * \section Usage
 *
 * -# On the computer, open and configure a terminal application
 *    (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# In the terminal window, the following text should appear (values depend
 *    on the board and chip used):
 *    \code
	-- ADCIFE Example xxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
	=========================================================
	Menu: press a key to change the configuration.
	---------------------------------------------------------
	[X] 0: Set ADCIFE trigger mode: Software.
	[ ] 1: Set ADCIFE trigger mode: Internal Timer.
	[ ] 2: Set ADCIFE trigger mode: Continuous.
	[D] T: Enable/Disable to transfer with PDCA in multichannel mode.
	[D] G: Enable/Disable to set gain=2 for channel.
	    Q: Quit configuration and start ADCIFE.
	=========================================================
\endcode
 * -# The application will output converted value to HyperTerminal and display
 *    a menu for users to set different modes..
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"

/* Reference voltage in mV */
#define VOLT_REF   1000

/** The maximal digital value*/
#define MAX_DIGITAL        4095

#define STRING_EOL    "\r"
#define STRING_HEADER "-- ADCIFE Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

#define MENU_HEADER "\n\r" \
		"===================================================\n\r" \
		"Menu: press a key to change the configuration.\n\r" \
		"---------------------------------------------------------\n\r"

/** Conversion done flag */
volatile uint8_t g_uc_condone_flag = 0;

/** Conversion value */
uint16_t g_adc_sample_data[2];

/** ADC instance */
struct adc_dev_inst g_adc_inst;

/** ADC CDMA config value */
struct adc_cdma_first_config g_adc_cdma_first_cfg[2] = {
	{
		/* Select Vref for shift cycle */
		.zoomrange = ADC_ZOOMRANGE_0,
		/* Pad Ground */
		.muxneg = ADC_MUXNEG_1,
		/* Scaled Vcc, Vcc/10 */
		.muxpos = ADC_MUXPOS_2,
		/* Enables the internal voltage sources */
		.internal = ADC_INTERNAL_3,
		/* Disables the ADC gain error reduction */
		.gcomp = ADC_GCOMP_DIS,
		/* Disables the HWLA mode */
		.hwla = ADC_HWLA_DIS,
		/* 12-bits resolution */
		.res = ADC_RES_12_BIT,
		/* Enables the single-ended mode */
		.bipolar = ADC_BIPOLAR_SINGLEENDED,
		/* Gain factor is 1x */
		.gain = ADC_GAIN_1X,
		.strig = 1,
		.tss = 1,
		.enstup = 1,
		.dw = 0
	},
	{
		.zoomrange = ADC_ZOOMRANGE_0,
		.muxneg = ADC_MUXNEG_1,
		/* DAC internal */
		.muxpos = ADC_MUXPOS_3,
		.internal = ADC_INTERNAL_3,
		.gcomp = ADC_GCOMP_DIS,
		.hwla = ADC_HWLA_DIS,
		.res = ADC_RES_12_BIT,
		.bipolar = ADC_BIPOLAR_SINGLEENDED,
		.gain = ADC_GAIN_1X,
		.strig = 1,
		.tss = 1,
		.enstup = 1,
		.dw = 0
	}
};
struct adc_pdca_config g_adc_pdca_cfg = {
	/* ADC Window Mode */
	.wm = false,
	/* ADC Nb channel */
	.nb_channels = 2,
	/* ADC Buffer */
	.buffer = g_adc_sample_data,
	/* ADC PDC Rx Channel */
	.pdc_rx_channel = CONFIG_ADC_PDCA_RX_CHANNEL,
	/* ADC PDC Tx Channel */
	.pdc_tx_channel = CONFIG_ADC_PDCA_TX_CHANNEL,
	/* ADC CDMA Configuration Structure */
	.cdma_cfg = (void *)&g_adc_cdma_first_cfg[0]
};

/** ADCIFE test mode structure */
struct {
	uint8_t uc_trigger_mode;
	uint8_t uc_pdc_en;
	uint8_t uc_gain_en;
} g_adc_test_mode;

/** ADCIFE trigger modes */
enum {
	TRIGGER_MODE_SOFTWARE = 0,
	TRIGGER_MODE_ITIMER,
	TRIGGER_MODE_CON,
} e_trigger_mode;

/**
 * \brief Display ADCIFE configuration menu.
 */
static void display_menu(void)
{
	uint8_t uc_char;

	puts(MENU_HEADER);
	uc_char = (g_adc_test_mode.uc_trigger_mode ==
			TRIGGER_MODE_SOFTWARE) ? 'X' : ' ';
	printf("[%c] 0: Set ADCIFE trigger mode: Software.\n\r", uc_char);
	uc_char = (g_adc_test_mode.uc_trigger_mode ==
			TRIGGER_MODE_ITIMER) ? 'X' : ' ';
	printf("[%c] 1: Set ADCIFE trigger mode: Internal Timer.\n\r", uc_char);
	uc_char = (g_adc_test_mode.uc_trigger_mode ==
			TRIGGER_MODE_CON) ? 'X' : ' ';
	printf("[%c] 2: Set ADCIFE trigger mode: Continuous.\n\r", uc_char);
	uc_char = (g_adc_test_mode.uc_pdc_en) ? 'E' : 'D';
	printf("[%c] T: Enable/Disable to transfer with PDCA in multichannel mode.\n\r", uc_char);
	uc_char = (g_adc_test_mode.uc_gain_en) ? 'E' : 'D';
	printf("[%c] G: Enable/Disable to set gain=2 for tested channel.\n\r",
			uc_char);
	puts("    Q: Quit configuration and start ADCIFE.\r");
	puts("=========================================================\r");
}

/**
 * \brief Set ADCIFE test mode.
 */
static void set_adc_test_mode(void)
{
	uint8_t uc_key;
	uint8_t uc_done = 0;

	while (!uc_done) {
		scanf("%c", (char *)&uc_key);

		switch (uc_key) {
		case '0':
			g_adc_test_mode.uc_trigger_mode = TRIGGER_MODE_SOFTWARE;
			break;

		case '1':
			g_adc_test_mode.uc_trigger_mode = TRIGGER_MODE_ITIMER;
			break;

		case '2':
			g_adc_test_mode.uc_trigger_mode = TRIGGER_MODE_CON;
			break;
		case 't':
		case 'T':
			if (g_adc_test_mode.uc_pdc_en) {
				g_adc_test_mode.uc_pdc_en = 0;
			} else {
				g_adc_test_mode.uc_pdc_en = 1;
			}
			break;

		case 'g':
		case 'G':
			if (g_adc_test_mode.uc_gain_en) {
				g_adc_test_mode.uc_gain_en = 0;
			} else {
				g_adc_test_mode.uc_gain_en = 1;
			}
			break;
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
 * \brief Callback function for ADCIFE interrupt.
 */
static void adcife_read_conv_result(void)
{
	if ((adc_get_status(&g_adc_inst) & ADCIFE_SR_SEOC) == ADCIFE_SR_SEOC) {
		g_adc_sample_data[0] = adc_get_last_conv_value(&g_adc_inst);
		g_uc_condone_flag = 1;
		adc_clear_status(&g_adc_inst, ADCIFE_SCR_SEOC);
	}
}

/**
 * \brief Callback function for PDCA interrupt.
 */
static void pdca_transfer_done(enum pdca_channel_status status)
{
	/* Get PDCA RX channel status and check if PDCA transfer complete */
	if (status == PDCA_CH_TRANSFER_COMPLETED) {
		/* Configure PDCA for data transfer */
		pdca_channel_write_load(CONFIG_ADC_PDCA_RX_CHANNEL, g_adc_sample_data, 2);
		pdca_channel_write_load(CONFIG_ADC_PDCA_TX_CHANNEL, g_adc_cdma_first_cfg, 2);
		g_uc_condone_flag = 1;
	}
}

/**
 * \brief Start ADC sample.
 * Initialize ADC, set clock and timing, and set ADC to given mode.
 */
static void start_adc(void)
{
	struct adc_config adc_cfg = {
		/* System clock division factor is 16 */
		.prescal = ADC_PRESCAL_DIV16,
		/* The APB clock is used */
		.clksel = ADC_CLKSEL_APBCLK,
		/* Max speed is 150K */
		.speed = ADC_SPEED_150K,
		/* ADC Reference voltage is internal 1.0V */
		.refsel = ADC_REFSEL_0,
		/* Enables the Startup time */
		.start_up = CONFIG_ADC_STARTUP
	};
	struct adc_seq_config adc_seq_cfg = {
		/* Select Vref for shift cycle */
		.zoomrange = ADC_ZOOMRANGE_0,
		/* Pad Ground */
		.muxneg = ADC_MUXNEG_1,
		/* DAC internal */
		.muxpos = ADC_MUXPOS_3,
		/* Enables the internal voltage sources */
		.internal = ADC_INTERNAL_3,
		/* Disables the ADC gain error reduction */
		.gcomp = ADC_GCOMP_DIS,
		/* Disables the HWLA mode */
		.hwla = ADC_HWLA_DIS,
		/* 12-bits resolution */
		.res = ADC_RES_12_BIT,
		/* Enables the single-ended mode */
		.bipolar = ADC_BIPOLAR_SINGLEENDED
	};
	struct adc_ch_config adc_ch_cfg = {
		.seq_cfg = &adc_seq_cfg,
		/* Internal Timer Max Counter */
		.internal_timer_max_count = 60,
		/* Window monitor mode is off */
		.window_mode = 0,
		.low_threshold = 0,
		.high_threshold = 0,
	};
	if(adc_init(&g_adc_inst, ADCIFE, &adc_cfg) != STATUS_OK) {
		puts("-F- ADC Init Fail!\n\r");
		while(1);
	}
	if(adc_enable(&g_adc_inst) != STATUS_OK) {
		puts("-F- ADC Enable Fail!\n\r");
		while(1);
	}

	if (g_adc_test_mode.uc_pdc_en) {
		adc_disable_interrupt(&g_adc_inst, ADC_SEQ_SEOC);
		adc_pdca_set_config(&g_adc_pdca_cfg);
		pdca_channel_set_callback(CONFIG_ADC_PDCA_RX_CHANNEL, pdca_transfer_done,
				PDCA_0_IRQn, 1, PDCA_IER_TRC);
	} else {
		pdca_channel_disable_interrupt(CONFIG_ADC_PDCA_RX_CHANNEL,
				PDCA_IDR_TRC);
		pdca_channel_disable_interrupt(CONFIG_ADC_PDCA_TX_CHANNEL,
				PDCA_IDR_TRC);
		adc_ch_set_config(&g_adc_inst, &adc_ch_cfg);
		adc_set_callback(&g_adc_inst, ADC_SEQ_SEOC, adcife_read_conv_result,
				ADCIFE_IRQn, 1);
	}

	/* Configure trigger mode and start convention. */
	switch (g_adc_test_mode.uc_trigger_mode) {
	case TRIGGER_MODE_SOFTWARE:
		adc_configure_trigger(&g_adc_inst, ADC_TRIG_SW);
		break;
	case TRIGGER_MODE_CON:
		adc_configure_trigger(&g_adc_inst, ADC_TRIG_CON);
		break;
	case TRIGGER_MODE_ITIMER:
		adc_configure_trigger(&g_adc_inst, ADC_TRIG_INTL_TIMER);
		adc_configure_itimer_period(&g_adc_inst,
				adc_ch_cfg.internal_timer_max_count);
		adc_start_itimer(&g_adc_inst);
		break;
	default:
		break;
	}

	if (g_adc_test_mode.uc_gain_en) {
		adc_configure_gain(&g_adc_inst, ADC_GAIN_2X);
	} else {
		adc_configure_gain(&g_adc_inst, ADC_GAIN_1X);
	}
}

/**
 * \brief Start DAC ouput.
 * Initialize DAC, set clock and timing, and set DAC to given mode.
 */
static void start_dac(void)
{
	sysclk_enable_peripheral_clock(DACC);

	/* Reset DACC registers */
	dacc_reset(DACC);

	/* Half word transfer mode */
	dacc_set_transfer_mode(DACC, 0);

	/* Timing:
	 * startup                - 0x10 (17 clocks)
	 * internal trigger clock - 0x60 (96 clocks)
	 */
	dacc_set_timing(DACC, 0x10, 0x60);

	/* Enable DAC */
	dacc_enable(DACC);

	/* The DAC is 10-bit resolution, so output voltage should be
	 * (3300 * 255) / ((1 << 10) - 1) = 823mv */
	dacc_write_conversion_data(DACC, 0xFF);
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
 * \brief Application entry point for adcife example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint32_t uc_key = 0;

	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	/* Initialize the UART console */
	configure_console();

	/* Output example information */
	puts(STRING_HEADER);

	/* Set default ADCIFE test mode. */
	g_adc_test_mode.uc_trigger_mode = TRIGGER_MODE_SOFTWARE;
	g_adc_test_mode.uc_pdc_en = 1;
	g_adc_test_mode.uc_gain_en = 0;

	display_menu();

	start_dac();

	start_adc();

	while (1) {
		/* ADCIFE software trigger per 1s */
		if (g_adc_test_mode.uc_trigger_mode == TRIGGER_MODE_SOFTWARE) {
			adc_start_software_conversion(&g_adc_inst);
		}
		if (!usart_read(CONF_UART, &uc_key)) {
			adc_disable_interrupt(&g_adc_inst, ADC_SEQ_SEOC);
			display_menu();
			set_adc_test_mode();
			start_adc();
			puts("Press any key to display configuration menu.\r");
		}
		delay_ms(1000);
		if (g_uc_condone_flag == 1) {
			if(g_adc_test_mode.uc_pdc_en == 0) {
				printf("Internal DAC Voltage = %4d mv  \r\n",
						(int)(g_adc_sample_data[0] * VOLT_REF / MAX_DIGITAL));
			} else {
				printf("Internal DAC Voltage = %4d mv  \r\n",
						(int)(g_adc_sample_data[0] * VOLT_REF /
							MAX_DIGITAL));
				printf("Scaled VCC Voltage = %4d mv  \r\n",
						(int)(g_adc_sample_data[1] * VOLT_REF /
							MAX_DIGITAL));
			}
			g_uc_condone_flag = 0;
		}
	}
}
