/**
 * \file
 *
 * \brief Sleep manager example for SAM4L series
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

#include <asf.h>
#include <conf_example.h>

static void ast_per_interrupt_callback(void)
{
	ast_clear_interrupt_flag(AST, AST_INTERRUPT_PER);
}

int main(void)
{
	enum sleepmgr_mode current_sleep_mode = SLEEPMGR_ACTIVE;
	uint32_t ast_counter = 0;

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
	ioport_set_pin_level(LED_ACTIVITY_STATUS_PIN, LED_STATUS_ON);

	osc_priv_enable_osc32();

	/* Enable the AST clock. */
	ast_enable(AST);

	/* Initialize the AST in Counter mode. */
	struct ast_config ast_conf;
	ast_conf.mode = AST_COUNTER_MODE;
	ast_conf.osc_type = AST_OSC_1KHZ;
	ast_conf.psel = AST_PSEL_32KHZ_1HZ - 6;
	ast_conf.counter = ast_counter;
	ast_set_config(AST, &ast_conf);

	/*
	 * Configure the AST to wake up the CPU when the counter reaches the
	 * selected periodic0 value.
	 */
	ast_write_periodic0_value(AST, AST_PSEL_32KHZ_1HZ - 3);
	ast_enable_wakeup(AST, AST_WAKEUP_PER);
	ast_enable_event(AST, AST_EVENT_PER);
	ast_clear_interrupt_flag(AST, AST_INTERRUPT_PER);
	ast_set_callback(AST, AST_INTERRUPT_PER, ast_per_interrupt_callback,
			AST_PER_IRQn, 0);

	/* AST can wakeup the device */
	bpm_enable_wakeup_source(BPM, (1 << BPM_BKUPWEN_AST));

	/* Initialize the sleep manager, lock initial mode.*/
	sleepmgr_init();
	sleepmgr_lock_mode(current_sleep_mode);

	while (1) {
		/*
		 * Turn the activity status LED off to inform the user that the
		 * device is in a sleep mode.
		 */
		ioport_set_pin_level(LED_ACTIVITY_STATUS_PIN, LED_STATUS_OFF);

		/*
		 * Go to sleep in the deepest allowed sleep mode (i.e. no
		 * deeper than the currently locked sleep mode).
		 */
		sleepmgr_enter_sleep();

		/*
		 * Turn the activity status LED on to inform the user that the
		 * device is active.
		 */
		ioport_set_pin_level(LED_ACTIVITY_STATUS_PIN, LED_STATUS_ON);

		/* Unlock the current sleep mode. */
		sleepmgr_unlock_mode(current_sleep_mode);

		/* Add a 3s delay. */
		delay_s(3);

		/* Lock the next sleep mode. */
		++current_sleep_mode;
		if ((current_sleep_mode >= SLEEPMGR_NR_OF_MODES)) {
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
 * - sleepmgr_example_sam4l_ast.c: Sleep manager example application
 * - conf_example.h: configuration of I/O pins
 *
 * \section apiinfo Sleep manager API
 * The sleep manager API can be found \ref sleepmgr_group "here".
 *
 * \section deviceinfo Device Info
 * All SAM4L series devices can be used.
 * The example can be applied on:
 * - SAM4L-EK
 * - SAM4L-XPLAINEDPRO
 * - SAM4L8-XPLAINEDPRO
 *
 * \section exampledescription Description of the example
 * The device is put to sleep in sleep modes with increasing "depth", and is
 * periodically woken up by the AST or asynchronously by an external interrupt
 * for the modes which also disable the RTC.
 * The device will remain in ACTIVE mode for approximately 3 seconds after wake-
 * up, before it goes to sleep in the next mode.
 *
 * The AST wakes the CPU every 4 seconds. If the device remains in sleep (LED
 * turned off), the device has gone into a too deep sleep mode for the AST to
 * operate (in the case of this example, the chosen source clock for the AST is
 * the RCOSC and the RCOSC is stopped in the WAIT/RET sleep mode). In that case,
 * the user must wake the device up by applying a low-level on the external
 * interrupt pin, e.g., by pushing a button connected to the pin
 * (\ref WAKE_BUTTON_EIC_PIN).
 *
 * A pin (\ref LED_ACTIVITY_STATUS_PIN) with, e.g., a LED connected is driven
 * low when the device is active and driven high when the device is sleeping.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR.
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
 * \brief The active-low GPIO pin to exit the WAIT/RET mode (by generating
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
