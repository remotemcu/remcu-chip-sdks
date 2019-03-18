/**
 * \file
 *
 * \brief Sleep manager example for AVR UC3 A0/A1/A3/A4 & AVR UC3 B series
 *
 * Copyright (c) 2010-2018 Microchip Technology Inc. and its subsidiaries.
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
#include <compiler.h>
#include <eic.h>
#include <gpio.h>
#include <rtc.h>
#include <sleepmgr.h>
#include <sysclk.h>
#include <conf_example.h>
#include <cycle_counter.h>


//! Structure holding the configuration parameters of the EIC low level driver.
static const eic_options_t      eic_options =
{
	// Choose External Interrupt Controller Line
	.eic_line   = WAKE_BUTTON_EIC_LINE,
	// Enable level-triggered interrupt.
	.eic_mode   = EIC_MODE_LEVEL_TRIGGERED,
	// Don't care value because the chosen eic mode is level-triggered.
	.eic_edge   = 0,
	// Interrupt will trigger on low-level.
	.eic_level  = EIC_LEVEL_LOW_LEVEL,
	// Enable filter.
	.eic_filter = EIC_FILTER_ENABLED,
	// For Wake Up mode, initialize in asynchronous mode
	.eic_async  = EIC_ASYNCH_MODE
};

ISR( rtc_irq_handler, AVR32_RTC_IRQ_GROUP, 3)
{
	// clear the interrupt flag
	rtc_clear_interrupt(&AVR32_RTC);
}

int main(void)
{
	enum sleepmgr_mode current_sleep_mode = SLEEPMGR_ACTIVE;

	/*
	 * Initialize the synchronous clock system to the default configuration
	 * set in conf_clock.h.
	 * Note: all non-essential peripheral clocks are initially disabled.
	 */
	sysclk_init();

	/*
	 * Initialize the resources used by this example to the default
	 * configuration set in conf_board.h
	 */
	board_init();

	/*
	 * Turn the activity status LED on to inform the user that the device is
	 * active.
	 */
	gpio_set_pin_low(LED_ACTIVITY_STATUS_PIN);

	/*
	 * Configure pin change interrupt for asynchronous wake-up (required to
	 * wake up from the STATIC sleep mode).
	 *
	 * First, map the interrupt line to the GPIO pin with the right
	 * peripheral function.
	 */
	gpio_enable_module_pin(WAKE_BUTTON_EIC_PIN, WAKE_BUTTON_EIC_FUNCTION);
	/*
	 * Enable the internal pull-up resistor on that pin (because the EIC is
	 * configured such that the interrupt will trigger on low-level, see
	 * eic_options.eic_level).
	 */
	gpio_enable_pin_pull_up(WAKE_BUTTON_EIC_PIN);
	// Init the EIC controller with the set options.
	eic_init(&AVR32_EIC, &eic_options, sizeof(eic_options) /
			sizeof(eic_options_t));
	// Enable External Interrupt Controller Line
	eic_enable_line(&AVR32_EIC, WAKE_BUTTON_EIC_LINE);

	/*
	 * Configure the RTC to generate an interrupt every second
	 */
	// Disable all interrupts.
	cpu_irq_disable();

	// Initialize interrupt vectors.
	irq_initialize_vectors();

	// Register the RTC interrupt handler to the interrupt controller.
	irq_register_handler(rtc_irq_handler, AVR32_RTC_IRQ, 3);

	// Initialize the RTC
	rtc_init(&AVR32_RTC, RTC_OSC_32KHZ, RTC_PSEL_32KHZ_1HZ);
	// Set top value to 0 to generate an interrupt every second.
	rtc_set_top_value(&AVR32_RTC, 0);
	// Enable the interrupts
	rtc_enable_interrupt(&AVR32_RTC);
	// Enable global interrupts
	cpu_irq_enable();

	// Initialize the sleep manager, lock initial mode.
	sleepmgr_init();
	sleepmgr_lock_mode(current_sleep_mode);

	do {
		/* Turn the activity status LED off to inform the user that the
		 * device is in a sleep mode.
		 */
		gpio_set_pin_high(LED_ACTIVITY_STATUS_PIN);

		// Enable the RTC
		rtc_enable(&AVR32_RTC);

		/* Go to sleep in the deepest allowed sleep mode (i.e. no deeper
		 * than the currently locked sleep mode).
		 */
		sleepmgr_enter_sleep();

		// Disable the RTC
		rtc_disable(&AVR32_RTC);

		/* Turn the activity status LED on to inform the user that the
		 * device is active.
		 */
		gpio_set_pin_low(LED_ACTIVITY_STATUS_PIN);

		// Add a 3s delay
		cpu_delay_ms(3000, sysclk_get_cpu_hz());

		if (current_sleep_mode == SLEEPMGR_STATIC) {
			// Clear the External Interrupt Line.
			eic_clear_interrupt_line(&AVR32_EIC,
				WAKE_BUTTON_EIC_LINE);
		}

		// Unlock the current sleep mode.
		sleepmgr_unlock_mode(current_sleep_mode);

		// Lock the next sleep mode.
		if (++current_sleep_mode < SLEEPMGR_NR_OF_MODES) {
			sleepmgr_lock_mode(current_sleep_mode);
		} else {
			current_sleep_mode = SLEEPMGR_ACTIVE;
			sleepmgr_lock_mode(current_sleep_mode);
		}
	} while (1);
}


#if 0
// Example usage in a peripheral ISR/driver.
ISR( xxx_irq_handler, AVR32_xxx_IRQ_GROUP, 0_to_3)
{
	switch (dummy_status) {
	BEGIN:
		sleepmgr_lock(SLEEPMGR_IDLE);
		...
		break;

	...

	DONE:
		...
		sleepmgr_unlock(SLEEPMGR_IDLE);
		break;
	}
}
#endif

/**
 * \mainpage
 *
 * \section intro Introduction
 * This simple example shows how to use the \ref sleepmgr_group.
 *
 * \section files Main files:
 * - sleepmgr_example_uc3a_uc3b.c: Sleep manager example application
 * - conf_example.h: configuration of I/O pins
 *
 * \section apiinfo Sleep manager API
 * The sleep manager API can be found \ref sleepmgr_group "here".
 *
 * \section deviceinfo Device Info
 * All AVR UC3 A0/A1/A3/A4 and UC3 B series devices can be used.
 * The example has been tested on the EVK1100, EVK1101, EVK1104 and EVK1105
 * boards.
 *
 * \section exampledescription Description of the example
 * The device is put to sleep in sleep modes with increasing "depth", and is
 * periodically woken up by the RTC or asynchronously by an external interrupt
 * for the modes which also disable the RTC.
 * The device will remain in ACTIVE mode for approximately 3 seconds after wake-
 * up, before it goes to sleep in the next mode.
 *
 * The RTC overflows after 1 second, and will then wake the device up. If the
 * device remains in sleep (LED turned off), the device has gone into a too
 * deep sleep mode for the RTC to operate. In this case, the user must wake the
 * device up by applying a low-level on the external interrupt pin, e.g., by
 * pushing a button connected to the pin (\ref WAKE_BUTTON_EIC_PIN).
 *
 * A pin (\ref LED_ACTIVITY_STATUS_PIN) with, e.g., a LED connected is driven
 * low when the device is active and driven high when the device is sleeping.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for AVR.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/">Microchip</A>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */

//! \name Example configuration
//@{
/**
 * \def WAKE_BUTTON_EIC_PIN
 * \brief The active-low GPIO pin to exit the STATIC sleep mode (by generating
 * an external interrupt).
 */
/**
 * \def WAKE_BUTTON_EIC_FUNCTION
 * \brief The EIC function of the wake pin.
 */
/**
 * \def WAKE_BUTTON_EIC_LINE
 * \brief The EIC line of the wake pin.
 */
/**
 * \def LED_ACTIVITY_STATUS_PIN
 * \brief The LED that will be turned off when the device is in a sleep mode
 * and on when it is active.
 */
//@}
