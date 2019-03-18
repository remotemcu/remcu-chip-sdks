/**
 * \file
 *
 * \brief Main functions for Generic example
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include "conf_usb.h"
#include "ui.h"

static volatile bool main_b_generic_enable = false;


/*! \brief Main function. Execution starts here.
 */
int main(void)
{
	sysclk_init();
	irq_initialize_vectors();
	cpu_irq_enable();

	// Initialize the sleep manager
	sleepmgr_init();

	board_init();
	ui_init();
	ui_powerdown();


	// Start USB stack to authorize VBus monitoring
	udc_start();

	// The main loop manages only the power mode
	// because the USB management is done by interrupt
	while (true) {
#ifdef   USB_DEVICE_LOW_SPEED
		// No USB "Keep a live" interrupt available in low speed
		// to scan generic interface then use main loop
		if (main_b_generic_enable) {
			static volatile uint16_t virtual_sof_sub = 0;
			static uint16_t virtual_sof = 0;
			if (sysclk_get_cpu_hz()/50000 ==
				virtual_sof_sub++) {
				virtual_sof_sub = 0;
				static uint16_t virtual_sof = 0;
				ui_process(virtual_sof++);
			}
		}
#else
		sleepmgr_enter_sleep();
#endif

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
	if (!main_b_generic_enable)
		return;
	ui_process(udd_get_frame_number());
}

void main_remotewakeup_enable(void)
{
	ui_wakeup_enable();
}

void main_remotewakeup_disable(void)
{
	ui_wakeup_disable();
}

bool main_generic_enable(void)
{
	main_b_generic_enable = true;
	return true;
}

void main_generic_disable(void)
{
	main_b_generic_enable = false;
}

void main_hid_set_feature(uint8_t* report)
{
	if (*((uint32_t*)report)==0x55AA55AA) {
		// Disconnect USB Device
		udc_stop();
		ui_powerdown();
	}
}

/**
 * \mainpage ASF USB Device HID Generic
 *
 * \section intro Introduction
 * This example shows how to implement a USB Device HID Generic
 * on XMEGA-A3BU Xplained that uses QTouch key.
 * The application note AVR1632 provides information about this implementation.
 *
 * \section startup Startup
 * The example uses the buttons or sensors available on the board
 * to simulate a standard generic.
 * After loading firmware, connect the board to the USB Host.
 * When connected to a USB host system this application provides a HID generic
 * application in the Unix/Mac/Windows operating systems.
 * This example uses the native HID driver for these operating systems.
 *
 * A Atmel PC tool allows to communicate with the HID generic device.
 * This document gives information on integrating the Atmel USB HID DLL functions.
 * Simple code examples that demonstrate different types of implementation are given.
 * http://ww1.microchip.com/downloads/en/AppNotes/doc7645.pdf
 * The PC tool is available here:
 * http://ww1.microchip.com/downloads/en/AppNotes/AVR153.zip
 * Note: Use the PID 0x2402 in tool graphic interface,
 * and the button Firmware Upgrade only disconnects the USB device.
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
 *   <br>services/usb/class/hid/
 *   <br>services/usb/class/hid/generic/
 * - Specific implementation:
 *    - main.c,
 *      <br>initializes clock
 *      <br>initializes interrupt
 *      <br>manages UI
 *    - touch.c
 *     <br>initializes touch
 *     <br>initializes timer to measure touch periodically
 *     <br>provides status of QTouch key
 *    - specific implementation for each target "./examples/product_board/":
 *       - conf_foo.h configuration of each module
 *       - ui.c       implement of user's interface (QTouch key, buttons, leds)
 */
