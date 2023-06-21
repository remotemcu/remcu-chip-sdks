/**
 * \file
 *
 * \brief CPU reset cause example
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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
 * \mainpage
 * \section intro Introduction
 * This example demonstrates how to use the reset cause interface.
 *
 * \section files Main Files
 *  - reset_cause_example.c example application
 *
 * \section reset_cause_interface_section services/basic/cpu/reset_cause.h interface
 * The reset cause interface is described in the \ref reset_cause_group section.
 *
 * \section device_info Device Info
 * All AVR devices can be used. This example has been tested with the following
 * setup:
 *  - Xplain evaluation kit
 *
 * \section example_description Description of the example
 * The example will set LEDs on the board depending on the reset cause. The
 * LEDs are wired to reset causes in the following order:
 *  - LED0: power-on-reset reset
 *  - LED1: on-chip debug system reset
 *  - LED2: JTAG reset
 *  - LED3: external reset
 *  - LED4: software reset
 *  - LED5: brown-out (on any power domains) detected reset
 *  - LED6: watchdog timeout reset
 *  - LED7: spike detection reset
 *
 * Where boards have less than the number of LEDs given above, the list is
 * shorted to the number of available LEDs.
 *
 * On boards with at least one button, the first available button will be used
 * to trigger a software reset when pressed.
 *
 * Users will observe different LEDs active depending if the device was reset
 * by toggling power, external reset input, reset triggered by programming and
 * debug tools and finally triggered by pressing the on-board button.
 *
 * \section dependencies Dependencies
 * This example depends on the gpio.h interface.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for AVR. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <A href="http://www.microchip.com/">Microchip</A>.\n
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "board.h"
#include "gpio.h"
#include "reset_cause.h"

/**
 * \brief Main function.
 */
int main(void)
{
	board_init();

#ifdef LED0_GPIO
	if (reset_cause_is_power_on_reset())
		gpio_set_pin_low(LED0_GPIO);
#endif
#ifdef LED1_GPIO
	if (reset_cause_is_ocd())
		gpio_set_pin_low(LED1_GPIO);
#endif
#ifdef LED2_GPIO
	if (reset_cause_is_jtag())
		gpio_set_pin_low(LED2_GPIO);
#endif
#ifdef LED3_GPIO
	if (reset_cause_is_external_reset())
		gpio_set_pin_low(LED3_GPIO);
#endif
#ifdef LED4_GPIO
	if (reset_cause_is_software_reset())
		gpio_set_pin_low(LED4_GPIO);
#endif
#ifdef LED5_GPIO
	if (reset_cause_is_brown_out_detected())
		gpio_set_pin_low(LED5_GPIO);
#endif
#ifdef LED6_GPIO
	if (reset_cause_is_watchdog())
		gpio_set_pin_low(LED6_GPIO);
#endif
#ifdef LED7_GPIO
	if (reset_cause_is_spike_detected())
		gpio_set_pin_low(LED7_GPIO);
#endif

	for (;;) {
#if defined(GPIO_PUSH_BUTTON_0)
		if (gpio_pin_is_low(GPIO_PUSH_BUTTON_0)) {
			reset_do_soft_reset();
		}
#elif defined(GPIO_PUSH_BUTTON_SW2)
		if (gpio_pin_is_low(GPIO_PUSH_BUTTON_SW2)) {
			reset_do_soft_reset();
		}
#else
		/* Board has no buttons available, don't do software reset. */
#endif
	}
}
