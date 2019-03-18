/**
 * \file
 *
 * \brief PWM SYNC example for SAM.
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
 * \mainpage PWM SYNC Example
 *
 * \par Purpose
 *
 * This example demonstrates a simple configuration of 2 PWM synchronous
 * channels to generate variable duty cycle signals. The duty cycle values are
 * updated automatically by the Peripheral DMA Controller (PDC), which makes 2
 * on-board LEDs glow repeatedly.
 *
 * \section Requirements
 *
 * This example can be used on any SAM3/4 boards. The 2 required leds need to
 * be connected to PWM output pins, else consider probing the PWM output pins
 * with an oscilloscope.
 *
 * \par Usage
 *
 * -# Initialize system clock and pins setting on board
 * -# Initialize PWM clock
 * -# Configure PIN_PWM_LED0_CHANNEL
 * -# Configure PIN_PWM_LED1_CHANNEL
 * -# Configure PDC transfer for PWM duty cycle update
 * -# Enable interrupt of PDC Tx end and PIN_PWM_LED0_CHANNEL
 * -# Update synchronous period, dead time and override output via UART Console
 * -# Restart PDC transfer in ISR
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "conf_board.h"

/** PWM frequency in Hz */
#define PWM_FREQUENCY  50
/** PWM period value */
#define PERIOD_VALUE   50
/** Initial duty cycle value */
#define INIT_DUTY_VALUE  0
/** Initial dead time value */
#define INIT_DEAD_TIME   5
/** Maximum synchronous update period */
#define MAX_SYNC_UPDATE_PERIOD  PWM_SCUP_UPR_Msk

/** Duty cycle buffer length for three channels */
#define DUTY_BUFFER_LENGTH      ((PERIOD_VALUE - INIT_DUTY_VALUE + 1) * 3)

#define STRING_EOL    "\r"
#define STRING_HEADER "-- PWM SYNC Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/** Duty cycle buffer for PDC transfer */
uint16_t g_us_duty_buffer[DUTY_BUFFER_LENGTH];

/** PDC transfer packet */
pdc_packet_t g_pdc_tx_packet;

/**
 * \brief Display menu.
 */
static void display_menu(void)
{
	puts("\r\n"
			"===============================================================\r\n"
			"Menu: press a key to change the configuration.\r\n"
			"===============================================================\r\n"
			"  u : Change update period for synchronous channels \r\n"
			"  d : Change dead time of PWM outputs\r\n"
			"  o : Enable/disable output override\r\n"
			"\r\n");
}

/**
 * \brief Get numeric value from console.
 *
 * \return Integer value from the console.
 */
static uint8_t get_num_value(void)
{
	uint32_t ul_numkey;
	uint8_t uc_key1, uc_key2;

	puts("New value : ");
#if defined (  __GNUC__  )
	fflush(stdout);
#endif
	while (uart_read(CONSOLE_UART, &uc_key1));
	printf("%c", uc_key1);
	while (uart_read(CONSOLE_UART, &uc_key2));
	printf("%c", uc_key2);
	puts("\r\n");

	if ('0' <= uc_key1 && '9' >= uc_key1) {
		ul_numkey = (uc_key1 - '0');
	}
	if ('0' <= uc_key2 && '9' >= uc_key2) {
		ul_numkey *= 10;
		ul_numkey += (uc_key2 - '0');
	}

	return (uint8_t) ul_numkey;
}

/**
 * \brief Interrupt handler for the PWM controller.
 */
void PWM_Handler(void)
{
	uint32_t pdc_status = pwm_get_interrupt_status(PWM);

	if ((pdc_status & PWM_PDC_TX_END) == PWM_PDC_TX_END) {
		/* Set up the PDC controller */
		g_pdc_tx_packet.ul_addr = (uint32_t) (&g_us_duty_buffer[0]);
		g_pdc_tx_packet.ul_size = DUTY_BUFFER_LENGTH;

		/* Initialize the PDC transfer */
		pdc_tx_init(PDC_PWM, &g_pdc_tx_packet, 0);

		/* Send the PWM value */
		pdc_enable_transfer(PDC_PWM, PERIPH_PTCR_TXTEN);
	}
}

/**
 *  \brief Configure the Console UART.
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
 * \brief Application entry point for PWM PDC example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint32_t i;
	uint8_t uc_key;
	uint8_t c_numkey;

	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	/* Configure the console uart for debug infomation */
	configure_console();

	/* Output example information */
	puts(STRING_HEADER);

	/* Enable PWM peripheral clock */
	pmc_enable_periph_clk(ID_PWM);

	/* Disable PWM channel of LED1 and LED0 */
	pwm_channel_disable(PWM, PIN_PWM_LED0_CHANNEL);
	pwm_channel_disable(PWM, PIN_PWM_LED1_CHANNEL);

	/*
	 * In PWM synchronisation mode the channel0 is used as reference channel,
	 * so it is necessary to disable, configure and enable it.
	 */
	if (PIN_PWM_LED0_CHANNEL && PIN_PWM_LED1_CHANNEL) {
		pwm_channel_disable(PWM, 0);
	}

	/* Set PWM clock A as PWM_FREQUENCY*PERIOD_VALUE (clock B is not used) */
	pwm_clock_t clock_setting = {
		.ul_clka = PWM_FREQUENCY * PERIOD_VALUE,
		.ul_clkb = 0,
		.ul_mck = sysclk_get_cpu_hz()
	};
	pwm_init(PWM, &clock_setting);

	/* Initialize PWM channels outputs */
	pwm_output_t channel_output = {
		/* Disable override PWMH outputs */
		.b_override_pwmh = false,
		/* Disable override PWML outputs */
		.b_override_pwml = false,
		/* Set override PWMH output level as HIGH */
		.override_level_pwmh = PWM_HIGH,
		/* Set override PWML output level as LOW */
		.override_level_pwml = PWM_LOW
	};

	/* Initialize PWM synchronous channels */
	pwm_channel_t sync_channel = {
		/* Use PWM clock A as source clock */
		.ul_prescaler = PWM_CMR_CPRE_CLKA,
		/* Period value of output waveform */
		.ul_period = PERIOD_VALUE,
		/* Duty cycle value of output waveform */
		.ul_duty = INIT_DUTY_VALUE,
		/* Set it as a synchronous channel */
		.b_sync_ch = true,
		/* Enable dead-time generator */
		.b_deadtime_generator = true,
		/* Dead-time value for PWMH output */
		.us_deadtime_pwmh = INIT_DEAD_TIME,
		/* Dead-time value for PWML output */
		.us_deadtime_pwml = INIT_DEAD_TIME,
		/* Disable override PWMH outputs */
		.output_selection.b_override_pwmh = false,
		/* Disable override PWML outputs */
		.output_selection.b_override_pwml = false
	};

	/*
	 * In PWM synchronisation mode the channel0 is used as reference channel,
	 * so it is necessary to disable, configure and enable it.
	 */
	if (PIN_PWM_LED0_CHANNEL && PIN_PWM_LED1_CHANNEL) {
		sync_channel.channel = 0;
		pwm_channel_init(PWM, &sync_channel);
	}

	/* Initialize PWM channel of LED1 */
	sync_channel.channel = PIN_PWM_LED1_CHANNEL;
	pwm_channel_init(PWM, &sync_channel);

	/* Initialize PWM channel of LED2 */
	sync_channel.channel = PIN_PWM_LED0_CHANNEL;
	pwm_channel_init(PWM, &sync_channel);

	/*
	 * Initialize PWM synchronous channels
	 * Synchronous Update Mode: Automatic update duty cycle value by the PDC
	 * and automatic update of synchronous channels. The update occurs when
	 * the Update Period elapses (MODE 2).
	 * Synchronous Update Period = MAX_SYNC_UPDATE_PERIOD.
	 */
	pwm_sync_init(PWM, PWM_SYNC_UPDATE_MODE_2, MAX_SYNC_UPDATE_PERIOD);

	/*
	 * Request PDC transfer as soon as the synchronous update period elapses
	 * (comparison unit is ignored).
	 */
	pwm_pdc_set_request_mode(PWM, PWM_PDC_UPDATE_PERIOD_ELAPSED, (1 << 0));

	/* Configure interrupt for PDC transfer */
	NVIC_DisableIRQ(PWM_IRQn);
	NVIC_ClearPendingIRQ(PWM_IRQn);
	NVIC_SetPriority(PWM_IRQn, 0);
	NVIC_EnableIRQ(PWM_IRQn);
	pwm_pdc_enable_interrupt(PWM, PWM_PDC_TX_END);

	/* Fill duty cycle buffer for channel #0 and #1 */
	/*
	 * For PWM channel 0 and 1, duty cycle ranges from
	 * MIN_DUTY_CYCLE to MAX_DUTY_CYCLE
	 */
	for (i = 0; i < (DUTY_BUFFER_LENGTH / 3); i++) {
		g_us_duty_buffer[i * 3] = (i + INIT_DUTY_VALUE);
		g_us_duty_buffer[i * 3 + 1] = (i + INIT_DUTY_VALUE);
		g_us_duty_buffer[i * 3 + 2] = (i + INIT_DUTY_VALUE);
	}

	/* Configure the PDC transfer packet and enable PDC transfer */
	g_pdc_tx_packet.ul_addr = (uint32_t) (&(g_us_duty_buffer[0]));
	g_pdc_tx_packet.ul_size = DUTY_BUFFER_LENGTH;
	pdc_tx_init(PDC_PWM, &g_pdc_tx_packet, 0);
	pdc_enable_transfer(PDC_PWM, PERIPH_PTCR_TXTEN);

	/* Enable all synchronous channels by enabling channel 0 */
	/*
	 * In PWM synchronisation mode the channel0 is used as reference channel,
	 * so it is necessary to disable, configure and enable it.
	 */
	if (PIN_PWM_LED0_CHANNEL && PIN_PWM_LED1_CHANNEL) {
		pwm_channel_enable(PWM, 0);
	}
	pwm_channel_enable(PWM, PIN_PWM_LED0_CHANNEL);
	pwm_channel_enable(PWM, PIN_PWM_LED1_CHANNEL);

	while (1) {
		display_menu();
		while (uart_read(CONSOLE_UART, &uc_key));

		switch (uc_key) {
		case 'u':
		case 'U':
			printf("Input update period must be between 0 and %d.\r\n",
					(int)MAX_SYNC_UPDATE_PERIOD);
			c_numkey = get_num_value();
			if (c_numkey <= MAX_SYNC_UPDATE_PERIOD) {
				/* Set new synchronous update period value */
				pwm_sync_change_period(PWM, c_numkey);
				printf("Synchronous update period has been changed to %d.\r\n", (int)c_numkey);

			} else {
				printf("Wrong value, expected value must be one of 0 to %d!\r\n", (int)MAX_SYNC_UPDATE_PERIOD);
			}
			break;
		case 'd':
		case 'D':
			printf("Input dead time for channel #0 must be between %d and %d.\r\n", INIT_DUTY_VALUE, PERIOD_VALUE);
			c_numkey = get_num_value();

			if (c_numkey <= PERIOD_VALUE) {
				/* Set new dead time value for channel 0 */
				pwm_channel_update_dead_time(PWM, &sync_channel,
						c_numkey, c_numkey);
				/* Update all synchronous channels */
				pwm_sync_unlock_update(PWM);
				printf("Dead time has been changed to %d.\r\n", (int)c_numkey);

			} else {
				printf("Wrong value, expected value must be one of %d to %d!\r\n", INIT_DUTY_VALUE, PERIOD_VALUE);
			}
			break;
		case 'o':
		case 'O':
			if (channel_output.b_override_pwmh
					&& channel_output.b_override_pwml) {
				/* Disable override outputs of channel 0 synchronously */
				channel_output.b_override_pwmh = false;
				channel_output.b_override_pwml = false;
				pwm_channel_update_output(PWM, &sync_channel,
						&channel_output, true);
				puts("PWM Channel #0 output override has been disabled.\r\n");
			}
			else {
				/* Enable override outputs of channel 0 synchronously */
				channel_output.b_override_pwmh = true;
				channel_output.b_override_pwml = true;
				pwm_channel_update_output(PWM, &sync_channel,
						&channel_output, true);
				puts("PWM Channel #0 output has been overridden.\r\n");

			}
			break;
		default:
			puts("Unknown input!\r\n");
			break;
		}
	}
}
