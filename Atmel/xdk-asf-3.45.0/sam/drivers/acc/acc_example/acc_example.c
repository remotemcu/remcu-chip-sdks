/**
 * \file
 *
 * \brief Analog Comparator Controller (ACC) example for SAM.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <stdio_serial.h>
#include <conf_board.h>
#include <conf_clock.h>

/** Reference voltage for DACC,in mv */
#define VOLT_REF   (3300)

/** The maximal digital value */
#define MAX_DIGITAL (4095)

/** The DAC Channel value */
#define DACC_CHANNEL_0 0

/** Analog control value */
#define DACC_ANALOG_CONTROL (DACC_ACR_IBCTLCH0(0x02) \
						  | DACC_ACR_IBCTLCH1(0x02) \
						  | DACC_ACR_IBCTLDACCORE(0x01))

/** The ADC Clock value */
#define ADC_CLOCK 6400000

/** The ADC Start Up Time value */
#define ADC_STARTUP_TIME_SETTING 0x8u

/** The ADC Start Up Time value */
#define ADC_TRACK_SETTING 0x0u

/** The ADC Start Up Time value */
#define ADC_TRANSFER_SETTING 0x1u

#define STRING_EOL    "\r"
#define STRING_HEADER "-- ACC IRQ Example  --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/**
 * Interrupt handler for the ACC.
 */
//! [acc_irq_handler_start]
void ACC_Handler(void)
{
//! [acc_irq_handler_start]

	//! [acc_irq_handler_status]
	uint32_t ul_status;

	ul_status = acc_get_interrupt_status(ACC);

	/** Compare Output Interrupt */
	if ((ul_status & ACC_ISR_CE) == ACC_ISR_CE) {
		//! [acc_irq_handler_status]
		//! [acc_irq_handler_result_1]
		if (acc_get_comparison_result(ACC)) {
			//! [acc_irq_handler_result_1]
			puts("-ISR- Voltage Comparison Result: AD5 > DAC0\r");
		//! [acc_irq_handler_result_2]
		} else {
			//! [acc_irq_handler_result_2]
			puts("-ISR- Voltage Comparison Result: AD5 < DAC0\r");
		//! [acc_irq_handler_result_3]
		}
	//! [acc_irq_handler_result_3]
	//! [acc_irq_handler_result_end]
	}
	//! [acc_irq_handler_result_end]
	//! [acc_irq_handler_end]
}
//! [acc_irq_handler_end]

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
	uint8_t i = 0, uc_key;
	int16_t us_value = 0;
	int8_t c_length = 0;
	int8_t ac_str_temp[5] = { 0 };

	while (1) {
		while (uart_read(CONSOLE_UART, &uc_key)) {
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
	uint8_t uc_key;
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
	dacc_disable_trigger(DACC);
	/* Half word transfer mode */
	dacc_set_transfer_mode(DACC, 0);
#if (SAM3S) || (SAM3XA)
	/* Power save:
	 * sleep mode  - 0 (disabled)
	 * fast wake-up - 0 (disabled)
	 */
	dacc_set_power_save(DACC, 0, 0);
#endif
	/* Timing:
	 * refresh        - 0x08 (1024*8 dacc clocks)
	 * max speed mode -    0 (disabled)
	 * startup time   - 0xf (960 dacc clocks)
	 */
	dacc_set_timing(DACC, 0x08, 0, 0xf);
	/* Disable TAG and select output channel DACC_CHANNEL */
	dacc_set_channel_selection(DACC, DACC_CHANNEL_0);
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
	dacc_write_conversion_data(DACC, MAX_DIGITAL / 2);
	l_volt_dac0 = (MAX_DIGITAL / 2) * (2 * VOLT_REF / 3) / MAX_DIGITAL +
			VOLT_REF / 6;

	/* Initialize ADC */
	/* Enable clock for ADC */
	pmc_enable_periph_clk(ID_ADC);
	/*
	 * Formula: ADCClock = MCK / ( (PRESCAL+1) * 2 )
	 * For example, MCK = 64MHZ, PRESCAL = 4, then:
	 *     ADCClock = 64 / ((4+1) * 2) = 6.4MHz;
	 */
	adc_init(ADC, sysclk_get_cpu_hz(), ADC_CLOCK, ADC_STARTUP_TIME_SETTING);

	/* Formula:
	 *     Startup  Time = startup value / ADCClock
	 *     Transfer Time = (TRANSFER * 2 + 3) / ADCClock
	 *     Tracking Time = (TRACKTIM + 1) / ADCClock
	 *     Settling Time = settling value / ADCClock
	 * For example, ADC clock = 6MHz (166.7 ns)
	 *     Startup time = 512 / 6MHz = 85.3 us
	 *     Transfer Time = (1 * 2 + 3) / 6MHz = 833.3 ns
	 *     Tracking Time = (0 + 1) / 6MHz = 166.7 ns
	 *     Settling Time = 3 / 6MHz = 500 ns
	 */
	/* Set ADC timing */
	adc_configure_timing(ADC, ADC_TRACK_SETTING, ADC_SETTLING_TIME_3,
			ADC_TRANSFER_SETTING);

	/* Channel 5 has to be compared */
	adc_enable_channel(ADC, ADC_CHANNEL_5);

	//! [acc_enable_clock]
	/** Enable clock for ACC */
	pmc_enable_periph_clk(ID_ACC);
	//! [acc_enable_clock]

	//! [acc_init]
	/** Initialize ACC */
	acc_init(ACC, ACC_MR_SELPLUS_AD5, ACC_MR_SELMINUS_DAC0,
			ACC_MR_EDGETYP_ANY, ACC_MR_INV_DIS);
	//! [acc_init]

	//! [acc_irq_enable]
	/** Enable ACC interrupt */
	NVIC_EnableIRQ(ACC_IRQn);

	/** Enable */
	acc_enable_interrupt(ACC);
	//! [acc_irq_enable]

	dsplay_menu();

	while (1) {
		while (uart_read(CONSOLE_UART, &uc_key)) {
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
				dacc_write_conversion_data(DACC, ul_value);
				puts("-I- Set ok\r");
			} else {
				puts("-I- Input voltage is invalid\r");
			}
			break;
		case 'v':
		case 'V':
			/* Start conversion */
			adc_start(ADC);
			ul_status = adc_get_status(ADC);
			while ((ul_status & ADC_ISR_EOC5) != ADC_ISR_EOC5) {
				ul_status = adc_get_status(ADC);
			}
			/* Conversion is done */
			ul_value = adc_get_channel_value(ADC, ADC_CHANNEL_5);

			/*
			 * Convert ADC sample data to voltage value:
			 * voltage value = (sample data / max. resolution) * reference voltage
			 */
			s_volt = (ul_value * VOLT_REF) / MAX_DIGITAL;
			printf("-I- Voltage on potentiometer(AD5) is %d mv\n\r", s_volt);
			printf("-I- Voltage on DAC0 is %ld mv \n\r", (long)l_volt_dac0);
			break;
			
		case 'm':
		case 'M':
			dsplay_menu();
			break;
		}
	}
}
