/**
 * \file
 *
 * \brief Analog Comparator Controller (ACC) example for SAMV71/SAME70.
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
 * \mainpage acc_irq ACC IRQ Example
 *
 * \section Purpose
 *
 * The acc_irq example demonstrates how to use the ACC peripheral to
 * detect comparison event on the input pair.
 *
 * \section Requirements
 *
 * This example can be used on the following boards:<br>
 * - SAMV71-Xplained-Ultra<br>
 * - SAME70-Xplained-Pro<br>
 *
 * \section Description
 *
 * The acc_irq is aimed to demonstrate the usage of ACC peripheral with
 * interrupt support. The DAC0 and AD0 are selected as two inputs.
 * The user can change the output voltage of DAC0 and change the voltage
 * on AD0.
 *
 * The output voltage of DAC0 is ranged from (1/6)*ADVREF to (5/6)*ADVREF,and
 * the input voltage of AD0 is ranged from 0 to ADVREF.
 *
 * The comparison event would be generated if the voltage of one input is
 * changed across the voltage of the other input. Both bigger and less events
 * could be triggered by default.
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# In the terminal window, the
 *    following text should appear (values depend on the board and chip used):
 *    \code
 *     -- ACC IRQ Example xxx --
 *     -- xxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *     -- Menu Choices for this example--
 *     -- s: Set new DAC0 output voltage.--
 *     -- v: Get voltage on potentiometer.--
 *     -- m: Display this menu again.--
 *     \endcode
 * -# Input command according to the menu.
 * -# Change voltage on AD0  to see what comparison event happen.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "stdio_serial.h"
#include "conf_board.h"
#include "conf_clock.h"

/** Reference voltage for DACC,in mv */
#define VOLT_REF   (3300)

/** The maximal digital value */
#define MAX_DIGITAL (4095)

/** The DAC Channel value */
#define DACC_CHANNEL_0 0

/** Analog control value */
#define DACC_ANALOG_CONTROL (DACC_ACR_IBCTLCH0(0x02) \
						  | DACC_ACR_IBCTLCH1(0x02))

#define STRING_EOL    "\r"
#define STRING_HEADER "-- ACC IRQ Example  --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/**
 * Interrupt handler for the ACC.
 */
void ACC_Handler(void)
{
	uint32_t ul_status;

	ul_status = acc_get_interrupt_status(ACC);

	/* Compare Output Interrupt */
	if ((ul_status & ACC_ISR_CE) == ACC_ISR_CE) {
		if (acc_get_comparison_result(ACC)) {
			puts("-ISR- Voltage Comparison Result: AD0 > DAC0\r");
		} else {
			puts("-ISR- Voltage Comparison Result: AD0 < DAC0\r");
		}
	}
}

/**
 *  Configure UART console.
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
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief Display main menu
 */
static void dsplay_menu(void)
{
	puts("-- Menu Choices for this example--\n\r"
			"  s: Set new DAC0 output voltage.\n\r"
			"  v: Get voltage on potentiometer.\n\r"
			"  m: Display this menu again.\r");
}

/**
 * \brief Get voltage from user input, the input range is:
 * (1/6)*ADVREF~(5/6)*ADVREF (mv)
 */
static int16_t get_input_voltage(void)
{
	uint32_t i = 0, uc_key;
	int16_t us_value = 0;
	int8_t c_length = 0;
	int8_t ac_str_temp[5] = { 0 };

	while (1) {
		while (usart_read(CONSOLE_UART, &uc_key)) {
		}
		if (uc_key == '\n' || uc_key == '\r') {
			puts("\r");
			break;
		}

		if ('0' <= uc_key && '9' >= uc_key) {
			printf("%c", uc_key);
			ac_str_temp[i++] = uc_key;

			if (i >= 4)
				break;
		}
	}

	ac_str_temp[i] = '\0';
	/* Input string length */
	c_length = i;
	us_value = 0;

	/* Convert string to integer */
	for (i = 0; i < 4; i++) {
		if (ac_str_temp[i] != '0') {
			switch (c_length - i - 1) {
			case 0:
				us_value += (ac_str_temp[i] - '0');
				break;
			case 1:
				us_value += (ac_str_temp[i] - '0') * 10;
				break;
			case 2:
				us_value += (ac_str_temp[i] - '0') * 100;
				break;
			case 3:
				us_value += (ac_str_temp[i] - '0') * 1000;
				break;
			}
		}
	}

	if (us_value > (5 * VOLT_REF / 6) || us_value < (1 * VOLT_REF / 6)) {
		return -1;
	}

	return us_value;
}

/**
 *  \brief ACC example application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint32_t uc_key;
	int16_t s_volt = 0;
	uint32_t ul_value = 0;
	volatile uint32_t ul_status = 0x0;
	int32_t l_volt_dac0 = 0;

	/* Initialize the system */
	sysclk_init();
	board_init();

	/* Initialize debug console */
	configure_console();

	/* Output example information */
	puts(STRING_HEADER);

	/* Initialize DACC */
	/* Enable clock for DACC */
	pmc_enable_periph_clk(ID_DACC);
	/* Reset DACC registers */
	dacc_reset(DACC);
	/* External trigger mode disabled. DACC in free running mode. */
	dacc_disable_trigger(DACC, DACC_CHANNEL_0);
	/* Half word transfer mode */
	dacc_set_transfer_mode(DACC, 0);
#if (SAM3S) || (SAM3XA)
	/* Power save:
	 * sleep mode  - 0 (disabled)
	 * fast wakeup - 0 (disabled)
	 */
	dacc_set_power_save(DACC, 0, 0);
#endif

	/* Enable output channel DACC_CHANNEL */
	dacc_enable_channel(DACC, DACC_CHANNEL_0);
	/* Setup analog current */
	dacc_set_analog_control(DACC, DACC_ANALOG_CONTROL);

	/* Set DAC0 output at ADVREF/2. The DAC formula is:
	 *
	 * (5/6 * VOLT_REF) - (1/6 * VOLT_REF)     volt - (1/6 * VOLT_REF)
	 * ----------------------------------- = --------------------------
	 *              MAX_DIGITAL                       digit
	 *
	 * Here, digit = MAX_DIGITAL/2
	 */
	dacc_write_conversion_data(DACC, MAX_DIGITAL / 2, DACC_CHANNEL_0);
	l_volt_dac0 = (MAX_DIGITAL / 2) * (2 * VOLT_REF / 3) / MAX_DIGITAL +
			VOLT_REF / 6;

	/* Enable clock for AFEC */
	afec_enable(AFEC0);

	struct afec_config afec_cfg;

	afec_get_config_defaults(&afec_cfg);
	/* Initialize AFEC */
	afec_init(AFEC0, &afec_cfg);

	struct afec_ch_config afec_ch_cfg;
	afec_ch_get_config_defaults(&afec_ch_cfg);
	afec_ch_cfg.gain = AFEC_GAINVALUE_0;
	afec_ch_set_config(AFEC0, AFEC_CHANNEL_POTENTIOMETER, &afec_ch_cfg);
	/*
	 * Because the internal ADC offset is 0x200, it should cancel it and shift
	 * down to 0.
	 */
	afec_channel_set_analog_offset(AFEC0, AFEC_CHANNEL_POTENTIOMETER, 0x200);

	afec_set_trigger(AFEC0, AFEC_TRIG_SW);

	/* Enable channel for potentiometer. */
	afec_channel_enable(AFEC0, AFEC_CHANNEL_POTENTIOMETER);

	/* Enable clock for ACC */
	pmc_enable_periph_clk(ID_ACC);
	
	/* Initialize ACC */
	acc_init(ACC, ACC_MR_SELPLUS_AFE0_AD0, ACC_MR_SELMINUS_DAC0,
			ACC_MR_EDGETYP_ANY, ACC_MR_INV_DIS);

	/* Enable ACC interrupt */
	NVIC_EnableIRQ(ACC_IRQn);

	/* Enable */
	acc_enable_interrupt(ACC);

	dsplay_menu();

	while (1) {
		while (usart_read(CONSOLE_UART, &uc_key)) {
		}

		printf("input: %c\r\n", uc_key);

		switch (uc_key) {
		case 's':
		case 'S':
			printf("Input DAC0 output voltage (%d~%d mv): ",
					(VOLT_REF / 6), (VOLT_REF * 5 / 6));
			s_volt = get_input_voltage();
			puts("\r");

			if (s_volt > 0) {
				l_volt_dac0 = s_volt;
				/* The DAC formula is:
				 *
				 * (5/6 * VOLT_REF) - (1/6 * VOLT_REF)     volt - (1/6 * VOLT_REF)
				 * ----------------------------------- = --------------------------
				 *              MAX_DIGITAL                       digit
				 *
				 */
				ul_value = ((s_volt - (VOLT_REF / 6))
					* (MAX_DIGITAL * 6) / 4) / VOLT_REF;
				dacc_write_conversion_data(DACC, ul_value, DACC_CHANNEL_0);
				puts("-I- Set ok\r");
			} else {
				puts("-I- Input voltage is invalid\r");
			}
			break;
		case 'v':
		case 'V':
			/* Start conversion */
			afec_start_software_conversion(AFEC0);
			ul_status = afec_get_interrupt_status(AFEC0);
			while ((ul_status & AFEC_ISR_EOC0) != AFEC_ISR_EOC0) {
				ul_status = afec_get_interrupt_status(AFEC0);
			}
			/* Conversion is done */
			ul_value = afec_channel_get_value(AFEC0, AFEC_CHANNEL_POTENTIOMETER);

			/*
			 * Convert AFEC sample data to voltage value:
			 * voltage value = (sample data / max. resolution) * reference voltage
			 */
			s_volt = (ul_value * VOLT_REF) / MAX_DIGITAL;
			printf("-I- Voltage on potentiometer(AD0) is %d mv\n\r", s_volt);
			printf("-I- Voltage on DAC0 is %ld mv \n\r", (long)l_volt_dac0);
			break;
			
		case 'm':
		case 'M':
			dsplay_menu();
			break;
		}
	}
}
