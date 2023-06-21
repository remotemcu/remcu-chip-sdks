/**
 * \file
 *
 * \brief Main functions
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
#include "conf_usb.h"
#include "ui.h"
#include "ieee11073_skeleton.h"

static volatile bool main_b_phdc_enable = false;

/*! \brief Main function. Execution starts here.
 */
int main(void)
{
	irq_initialize_vectors();
	cpu_irq_enable();

	/* Initialize the sleep manager */
	sleepmgr_init();
#if !SAM0
	sysclk_init();
	board_init();
#else
	system_init();
#endif
	ui_init();
	ui_powerdown();

	/* Start USB stack to authorize VBus monitoring */
	udc_start();

	/* The main loop manages only the power mode
	 * because the USB management is done by interrupt
	 */
	while (true) {
		sleepmgr_enter_sleep();
		if (main_b_phdc_enable) {
			if (ieee11073_skeleton_process()) {
				ui_association(true); /* Association Ok */
			} else {
				ui_association(false); /* No association */
			}
		}
	}
}

void main_suspend_action(void)
{
	ui_powerdown();
}

void main_resume_action(void)
{
	ui_wakeup();
}

void main_sof_action(void)
{
	if (!main_b_phdc_enable) {
		return;
	}

	ui_process(udd_get_frame_number());
}

bool main_phdc_enable(void)
{
	main_b_phdc_enable = ieee11073_skeleton_enable();
	return main_b_phdc_enable;
}

void main_phdc_disable(void)
{
	main_b_phdc_enable = false;
	ieee11073_skeleton_disable();
}

/**
 * \mainpage ASF USB Device PHDC
 *
 * \section intro Introduction
 * This example shows how to implement a USB Device PHDC
 * on Atmel MCU with USB module.
 * This example uses a IEEE11073 stack skeleton which has the minimum to
 * pass USB Command Verifier 2.0 Tool (CV2.0) tests from usb.org.
 * Note: No USB driver is provided by Atmel for PHDC, but it is not required
 * to execute CV2.0 PHDC tests.
 *
 * \section startup Startup
 * You must compile, load and start example.
 * After, you can start CV2.0 and execute Chapter 9 and PHDC tests.
 *
 * \copydoc UI
 *
 * \section example About example
 *
 * The example uses the following module groups:
 * - Basic modules:
 *   Startup, board, clock, interrupt, power management
 * - USB Device stack and HID modules:
 *   <br>services/usb/
 *   <br>services/usb/udc/
 *   <br>services/usb/class/phdc/device/
 * - Specific implementation:
 *    - main.c,
 *      <br>initializes clock
 *      <br>initializes interrupt
 *      <br>manages UI
 *    - ieee11073_skeleton.c, IEEE11073 stack skeleton
 *    - specific implementation for each target "./examples/product_board/":
 *       - conf_foo.h   configuration of each module
 *       - ui.c        implement of user's interface (buttons, leds)
 */
