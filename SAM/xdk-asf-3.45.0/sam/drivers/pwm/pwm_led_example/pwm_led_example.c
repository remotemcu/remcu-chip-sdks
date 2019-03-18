/**
 * \file
 *
 * \brief PWM LED example for SAM.
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
 * \mainpage PWM LED Example
 *
 * \par Purpose
 *
 * This example demonstrates a simple configuration of 2 PWM channels to
 * generate variable duty cycle signals.
 * The 2 LEDs on the evaluation kit will glow repeatedly.
 *
 * \section Requirements
 *
 * This example can be used on SAM boards. The 2 required leds need to
 * be connected to PWM output pins, else consider probing the PWM output pins
 * with an oscilloscope.
 *
 * \par Usage
 *
 * -# Initialize system clock and pins setting on board
 * -# Initialize PWM clock
 * -# Configure PIN_PWM_LED0_CHANNEL
 * -# Configure PIN_PWM_LED1_CHANNEL
 * -# Enable interrupt of counter event and PIN_PWM_LED0_CHANNEL
 * & PIN_PWM_LED1_CHANNEL
 * -# Change duty cycle in ISR
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "stdio_serial.h"
#include "conf_board.h"
#include "conf_clock.h"

/** PWM frequency in Hz */
#define PWM_FREQUENCY      1000
/** Period value of PWM output waveform */
#define PERIOD_VALUE       100
/** Initial duty cycle value */
#define INIT_DUTY_VALUE    0

#define STRING_EOL    "\r"
#define STRING_HEADER "-- PWM LED Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/** PWM channel instance for LEDs */
pwm_channel_t g_pwm_channel_led;

/**
 * \brief Interrupt handler for the PWM controller.
 */
#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
void PWM0_Handler(void)
#else
void PWM_Handler(void)
#endif
{
	static uint32_t ul_count = 0;  /* PWM counter value */
	static uint32_t ul_duty = INIT_DUTY_VALUE;  /* PWM duty cycle rate */
	static uint8_t fade_in = 1;  /* LED fade in flag */

#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
	uint32_t events = pwm_channel_get_interrupt_status(PWM0);
#else
	uint32_t events = pwm_channel_get_interrupt_status(PWM);
#endif

	/* Interrupt on PIN_PWM_LED0_CHANNEL */
	if ((events & (1 << PIN_PWM_LED0_CHANNEL)) ==
	(1 << PIN_PWM_LED0_CHANNEL)) {
		ul_count++;

		/* Fade in/out */
		if (ul_count == (PWM_FREQUENCY / (PERIOD_VALUE - INIT_DUTY_VALUE))) {
			/* Fade in */
			if (fade_in) {
				ul_duty++;
				if (ul_duty == PERIOD_VALUE) {
					fade_in = 0;
				}
				} else {
				/* Fade out */
				ul_duty--;
				if (ul_duty == INIT_DUTY_VALUE) {
					fade_in = 1;
				}
			}

			/* Set new duty cycle */
			ul_count = 0;
			g_pwm_channel_led.channel = PIN_PWM_LED0_CHANNEL;
#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
			pwm_channel_update_duty(PWM0, &g_pwm_channel_led, ul_duty);
#else
			pwm_channel_update_duty(PWM, &g_pwm_channel_led, ul_duty);
#endif
			g_pwm_channel_led.channel = PIN_PWM_LED1_CHANNEL;
#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
			pwm_channel_update_duty(PWM0, &g_pwm_channel_led, ul_duty);
#else
			pwm_channel_update_duty(PWM, &g_pwm_channel_led, ul_duty);
#endif
		}
	}
}

/**
 *  \brief Configure the Console UART.
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
 * \brief Application entry point for PWM with LED example.
 * Output PWM waves on LEDs to make them fade in and out.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	/* Configure the console uart for debug information */
	configure_console();

	/* Output example information */
	puts(STRING_HEADER);
	
	/* Enable PWM peripheral clock */
#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
	pmc_enable_periph_clk(ID_PWM0);
#else
	pmc_enable_periph_clk(ID_PWM);
#endif

	/* Disable PWM channels for LEDs */
#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
	pwm_channel_disable(PWM0, PIN_PWM_LED0_CHANNEL);
	pwm_channel_disable(PWM0, PIN_PWM_LED1_CHANNEL);
#else
	pwm_channel_disable(PWM, PIN_PWM_LED0_CHANNEL);
	pwm_channel_disable(PWM, PIN_PWM_LED1_CHANNEL);
#endif

	/* Set PWM clock A as PWM_FREQUENCY*PERIOD_VALUE (clock B is not used) */
	pwm_clock_t clock_setting = {
		.ul_clka = PWM_FREQUENCY * PERIOD_VALUE,
		.ul_clkb = 0,
#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
		.ul_mck = sysclk_get_peripheral_hz()
#else
		.ul_mck = sysclk_get_cpu_hz()
#endif
	};
#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
	pwm_init(PWM0, &clock_setting);
#else
	pwm_init(PWM, &clock_setting);
#endif

	/* Initialize PWM channel for LED0 */
	/* Period is left-aligned */
	g_pwm_channel_led.alignment = PWM_ALIGN_LEFT;
	/* Output waveform starts at a low level */
	g_pwm_channel_led.polarity = PWM_LOW;
	/* Use PWM clock A as source clock */
	g_pwm_channel_led.ul_prescaler = PWM_CMR_CPRE_CLKA;
	/* Period value of output waveform */
	g_pwm_channel_led.ul_period = PERIOD_VALUE;
	/* Duty cycle value of output waveform */
	g_pwm_channel_led.ul_duty = INIT_DUTY_VALUE;
	g_pwm_channel_led.channel = PIN_PWM_LED0_CHANNEL;
#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
	pwm_channel_init(PWM0, &g_pwm_channel_led);
#else
	pwm_channel_init(PWM, &g_pwm_channel_led);
#endif

	/* Enable channel counter event interrupt */
#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
	pwm_channel_enable_interrupt(PWM0, PIN_PWM_LED0_CHANNEL, 0);
#else
	pwm_channel_enable_interrupt(PWM, PIN_PWM_LED0_CHANNEL, 0);
#endif

	/* Initialize PWM channel for LED1 */
	/* Period is center-aligned */
	g_pwm_channel_led.alignment = PWM_ALIGN_CENTER;
	/* Output waveform starts at a high level */
	g_pwm_channel_led.polarity = PWM_HIGH;
	/* Use PWM clock A as source clock */
	g_pwm_channel_led.ul_prescaler = PWM_CMR_CPRE_CLKA;
	/* Period value of output waveform */
	g_pwm_channel_led.ul_period = PERIOD_VALUE;
	/* Duty cycle value of output waveform */
	g_pwm_channel_led.ul_duty = INIT_DUTY_VALUE;
	g_pwm_channel_led.channel = PIN_PWM_LED1_CHANNEL;
#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
	pwm_channel_init(PWM0, &g_pwm_channel_led);

	/* Disable channel counter event interrupt */
	pwm_channel_disable_interrupt(PWM0, PIN_PWM_LED1_CHANNEL, 0);
#else
	pwm_channel_init(PWM, &g_pwm_channel_led);

	/* Disable channel counter event interrupt */
	pwm_channel_disable_interrupt(PWM, PIN_PWM_LED1_CHANNEL, 0);
#endif

	/* Configure interrupt and enable PWM interrupt */
#if (SAMV70 || SAMV71 || SAME70 || SAMS70)
	NVIC_DisableIRQ(PWM0_IRQn);
	NVIC_ClearPendingIRQ(PWM0_IRQn);
	NVIC_SetPriority(PWM0_IRQn, 0);
	NVIC_EnableIRQ(PWM0_IRQn);
	
	/* Enable PWM channels for LEDs */
	pwm_channel_enable(PWM0, PIN_PWM_LED0_CHANNEL);
	pwm_channel_enable(PWM0, PIN_PWM_LED1_CHANNEL);
#else
	NVIC_DisableIRQ(PWM_IRQn);
	NVIC_ClearPendingIRQ(PWM_IRQn);
	NVIC_SetPriority(PWM_IRQn, 0);
	NVIC_EnableIRQ(PWM_IRQn);
	
	/* Enable PWM channels for LEDs */
	pwm_channel_enable(PWM, PIN_PWM_LED0_CHANNEL);
	pwm_channel_enable(PWM, PIN_PWM_LED1_CHANNEL);
#endif


	/* Infinite loop */
	while (1) {
	}
}
