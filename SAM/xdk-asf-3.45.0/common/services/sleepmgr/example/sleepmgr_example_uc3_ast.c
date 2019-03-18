/**
 * \file
 *
 * \brief Sleep manager example for AVR UC3 C & AVR UC3 L series
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
#include <ast.h>
#include <eic.h>
#include <gpio.h>
#include <board.h>
#include <sysclk.h>
#include <compiler.h>
#include <sleepmgr.h>
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

int main(void)
{
	enum sleepmgr_mode      current_sleep_mode = SLEEPMGR_ACTIVE;
	uint32_t                ast_counter = 0;

	/*
	 * Initialize the synchronous clock system to the default configuration
	 * set in conf_clock.h.
	 * \note All non-essential peripheral clocks are initially disabled.
	 */
	sysclk_init();

	/*
	 * Initialize the resources used by this example to the default
	 * configuration set in conf_board.h
	 */
	board_init();

	/*
	 * Turn the activity status LED on to inform the user that the device
	 * is active.
	 */
	gpio_set_pin_low(LED_ACTIVITY_STATUS_PIN);

	/*
	 * Configure pin change interrupt for asynchronous wake-up (required to
	 * wake up from the STATIC sleep mode) and enable the EIC clock.
	 *
	 * First, enable the clock for the EIC module.
	 */
	sysclk_enable_pba_module(SYSCLK_EIC);
	/*
	 * Map the interrupt line to the GPIO pin with the right peripheral
	 * function.
	 */
	gpio_enable_module_pin(WAKE_BUTTON_EIC_PIN, WAKE_BUTTON_EIC_FUNCTION);
	/*
	 * Enable the internal pull-up resistor on that pin (because the EIC is
	 * configured such that the interrupt will trigger on low-level, see
	 * eic_options.eic_level).
	 */
	gpio_enable_pin_pull_up(WAKE_BUTTON_EIC_PIN);
	// Init the EIC controller with the options
	eic_init(&AVR32_EIC, &eic_options, sizeof(eic_options) /
			sizeof(eic_options_t));
	// Enable External Interrupt Controller Line
	eic_enable_line(&AVR32_EIC, WAKE_BUTTON_EIC_LINE);

	// Enable the AST clock.
	sysclk_enable_pba_module(SYSCLK_AST);
	// Initialize the AST in Counter mode
	ast_init_counter(&AVR32_AST, AST_OSC_RC, AST_PSEL_RC_1_76HZ,
			ast_counter);
	/*
	 * Configure the AST to wake up the CPU when the counter reaches the
	 * selected alarm0 value.
	 */
	AVR32_AST.WER.alarm0 = 1;
	// Enable the AST
	ast_enable(&AVR32_AST);

	// Initialize the sleep manager, lock initial mode.
	sleepmgr_init();
	sleepmgr_lock_mode(current_sleep_mode);

	while (1) {
		ast_counter = ast_get_counter_value(&AVR32_AST);
		// disable alarm 0
		ast_disable_alarm0(&AVR32_AST);
		// Set Alarm to current time + (6/1.76) seconds
		ast_counter += 6;
		ast_set_alarm0_value(&AVR32_AST, ast_counter);
		// Enable alarm 0
		ast_enable_alarm0(&AVR32_AST);

		/*
		 * Turn the activity status LED off to inform the user that the
		 * device is in a sleep mode.
		 */
		gpio_set_pin_high(LED_ACTIVITY_STATUS_PIN);

		/*
		 * Go to sleep in the deepest allowed sleep mode (i.e. no
		 * deeper than the currently locked sleep mode).
		 */
		sleepmgr_enter_sleep();

		/*
		 * Turn the activity status LED on to inform the user that the
		 * device is active.
		 */
		gpio_set_pin_low(LED_ACTIVITY_STATUS_PIN);

		// After wake up, clear the Alarm0
		AVR32_AST.SCR.alarm0 = 1;

		// Unlock the current sleep mode.
		sleepmgr_unlock_mode(current_sleep_mode);

		// Add a 3s delay
		cpu_delay_ms(3000, sysclk_get_cpu_hz());

		// Clear the External Interrupt Line (in case it was raised).
		eic_clear_interrupt_line(&AVR32_EIC, WAKE_BUTTON_EIC_LINE);

		// Lock the next sleep mode.
		++current_sleep_mode;
		if ((current_sleep_mode >= SLEEPMGR_NR_OF_MODES)
#if UC3L && (BOARD == UC3L_EK)
		/* Note concerning the SHUTDOWN sleep mode: the shutdown sleep
		 * mode can only be used when the UC3L supply mode is the 3.3V
		 * Supply Mode with 1.8V Regulated I/O Lines. That is not how
		 * the UC3L is powered on the ATUC3L-EK so the SHUTDOWN mode
		 * cannot be used on this board. Thus we skip this sleep mode
		 * in this example for this board.
		 */
			|| (current_sleep_mode == SLEEPMGR_SHUTDOWN)
#endif
			) {
			current_sleep_mode = SLEEPMGR_ACTIVE;
		}

		sleepmgr_lock_mode(current_sleep_mode);
	}
}

/**
 * \mainpage
 *
 * \section intro Introduction
 * This simple example shows how to use the \ref sleepmgr_group.
 *
 * \section files Main files:
 * - sleepmgr_example_uc3c_uc3l.c: Sleep manager example application
 * - conf_example.h: configuration of I/O pins
 *
 * \section apiinfo Sleep manager API
 * The sleep manager API can be found \ref sleepmgr_group "here".
 *
 * \section deviceinfo Device Info
 * All AVR UC3 C and UC3 L series devices can be used.
 * The example has been tested on the UC3C-EK and UC3L-EK boards.
 *
 * \section exampledescription Description of the example
 * The device is put to sleep in sleep modes with increasing "depth", and is
 * periodically woken up by the AST or asynchronously by an external interrupt
 * for the modes which also disable the RTC.
 * The device will remain in ACTIVE mode for approximately 3 seconds after wake-
 * up, before it goes to sleep in the next mode.
 *
 * The AST wakes the CPU every 3.5 seconds. If the device remains in sleep (LED
 * turned off), the device has gone into a too deep sleep mode for the AST to
 * operate (in the case of this example, the chosen source clock for the AST is
 * the RCOSC and the RCOSC is stopped in the STATIC sleep mode). In that case,
 * the user must wake the device up by applying a low-level on the external
 * interrupt pin, e.g., by pushing a button connected to the pin
 * (\ref WAKE_BUTTON_EIC_PIN).
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
