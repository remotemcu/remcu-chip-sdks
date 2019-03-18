/**
 * \file
 *
 * \brief Sleep manager example for SAM series
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
 * \mainpage Sleep manager example
 *
 * \section intro Introduction
 * This simple example shows how to use the \ref sleepmgr_group.
 *
 * \section files Main files:
 * - sleepmgr_example_sam_rtt.c: Sleep manager example application
 * - conf_example.h: configuration of I/O pins
 *
 * \section apiinfo Sleep manager API
 * The sleep manager API can be found \ref sleepmgr_group "here".
 *
 * \section deviceinfo Device Info
 * All SAM series devices can be used.
 * The example has been tested on the boards:
 *  - SAM4N Xplained Pro kit
 *  - SAMG53 Xplained Pro kit
 *  - SAMG55 Xplained Pro kit
 *  - SAM4C evaluation kit
 *  - SAMV71 Xplained Ultra kit
 *  - SAME70 Xplained Pro kit
 *
 * \section exampledescription Description of the example
 * The device is put to sleep in sleep modes with increasing "depth", and is
 * periodically woken up by the RTT_ALARM.  The RTT_ALARM wakes the CPU
 * every 5 seconds.
 * The device will remain in ACTIVE mode for approximately 3 seconds after wake-
 * up, before it goes to sleep in the next mode.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <conf_example.h>

#define SLEEP_TIME    5
#define ACTIVE_TIME   3

void RTT_Handler(void)
{
	rtt_get_status(RTT);
}

int main(void)
{
	enum sleepmgr_mode current_sleep_mode = SLEEPMGR_ACTIVE;

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

	rtt_init(RTT, 32768);

	/* Enable RTT interrupt */
	NVIC_DisableIRQ(RTT_IRQn);
	NVIC_ClearPendingIRQ(RTT_IRQn);
	NVIC_SetPriority(RTT_IRQn, 0);
	NVIC_EnableIRQ(RTT_IRQn);
	rtt_enable_interrupt(RTT, RTT_MR_ALMIEN);

	/* Set wakeup source to rtt_alarm */
	pmc_set_fast_startup_input(PMC_FSMR_RTTAL);
#if (!(SAMG51 || SAMG53 || SAMG54))
	supc_set_wakeup_mode(SUPC, SUPC_WUMR_RTTEN_ENABLE);
#endif
	/* Initialize the sleep manager, lock initial mode. */
	sleepmgr_init();
	sleepmgr_lock_mode(current_sleep_mode);

	while (1) {

		rtt_write_alarm_time(RTT, rtt_read_timer_value(RTT) + SLEEP_TIME);
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
		delay_s(ACTIVE_TIME);

		/* Lock the next sleep mode. */
		++current_sleep_mode;
		if ((current_sleep_mode >= SLEEPMGR_NR_OF_MODES)) {
			current_sleep_mode = SLEEPMGR_ACTIVE;
		}

		sleepmgr_lock_mode(current_sleep_mode);
	}
}
