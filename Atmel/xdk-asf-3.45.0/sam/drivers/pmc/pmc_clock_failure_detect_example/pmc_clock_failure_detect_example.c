/**
 * \file
 *
 * \brief PMC Clock Failure Detection Example
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

/**
 * \mainpage PMC Clock Failure Detection Example
 *
 * \par Purpose
 *
 *  This example shows how to use the Clock Failure Detection feature of the
 *  SAM MCUs when the external oscillator fails.
 *
 * \par Usage
 *
 * -# After startup, the example enables Main Crystal Clock Failure Detector.
 * -# The Clock Failure Detector Event interrupt is enabled as well. Then if a
 *    failure of crystal oscillator clock is detected, the MCU will generate an
 *    interrupt.
 * -# Users could trigger the Clock Failure Detector Event by means of shorting
 *    XIN or XOUT pin to ground.
 * -# In the interrupt handler, the example will turn a LED on to indicate that
 *    a clock failure has been detected.
 *
 * \note
 *
 *  The example requires the chip configured to run on external oscillator,
 *  which is normally the case when using the sysclk_init().
 *  When the external oscillator is activated, the XIN pin is automatically set
 *  in XIN mode, and no more in PIO mode.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include "conf_example.h"

/** Console UART baud rate: 115200 bps */
#define CONSOLE_UART_BAUDRATE  (115200)

#define STRING_EOL    "\r"
#define STRING_HEADER "-- PMC Clock Failure Detection Example --\r\n" \
	"-- "BOARD_NAME " --\r\n" \
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

/**
 * \brief Handler for PMC interrupt. Toggle LED to indicate the event.
 */
void PMC_Handler(void)
{
	if (pmc_get_status() & PMC_SR_CFDEV) {
		/* A clock failure has been detected. */
#if (SAM4E || SAM4N || SAM4C)
		LED_On(LED0);
#elif (SAM4CM)
		LED_On(LED4);
#else
		LED_On(EXAMPLE_LED);
#endif
	}
}

/**
 *  \brief Configure the Console UART
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
#if defined(__GNUC__)
	setbuf(stdout, NULL);
#endif
}

/**
 *  \brief pmc_clock_failure_detect_example Application entry point.
 *
 *  Enable Clock Failure Detection function in PMC, turn on a LED to indicate
 *  that a clock failure is detected.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	/* Initialize the console UART. */
	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);

	/* Turn off the LED. */
#if (SAM4E || SAM4N || SAM4C)
		LED_Off(LED0);
#elif (SAM4CM)
		LED_Off(LED4);
#else
		LED_Off(EXAMPLE_LED);
#endif

	/* Enable Clock Failure Detector. */
	pmc_enable_clock_failure_detector();

	/* Enable Clock Failure Detector Event interrupt. */
	NVIC_EnableIRQ(PMC_IRQn);
	pmc_enable_interrupt(PMC_IER_CFDEV);

	puts("-I- Short XIN or XOUT to ground to force a clock failure.\n\r");

	while (1) {
		/* Infinite loop */
	}
}
