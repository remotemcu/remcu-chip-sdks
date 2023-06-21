/**
 * \file
 *
 * \brief Main functions for USB device and host (dual rual) mouse example
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include "conf_usb.h"
#include "conf_usb_host.h"
#include "ui.h"

/*! \brief Main function. Execution starts here.
 */
int main(void)
{
#if SAMD21 || SAML21 || SAMDA1 || SAMR30
	system_init();
#else
	sysclk_init();
	board_init();
#endif

	irq_initialize_vectors();
	cpu_irq_enable();

	// Initialize the sleep manager
	sleepmgr_init();

	ui_init();

	// Start USB dual mode which will start the correct mode (device or host)
	// corresponding at USB ID signal.
	uhc_start();

	// The main loop manages only the power mode
	// because the USB stack is full interrupt driven.
	while (true) {
		sleepmgr_enter_sleep();
	}
}

/**
 * \mainpage ASF USB host and device HID mouse
 *
 * \section intro Introduction
 * This example shows how to implement a USB dual mode (device and host)
 * HID Mouse on Atmel MCU with USB module.
 *
 * \section startup Startup
 * In device mode, the example uses the buttons or sensors available
 * on the board to simulate a standard mouse.
 * After loading firmware, connect the board to the USB Host.
 * When connected to a USB host system this application provides
 * a mouse application in the Unix/Mac/Windows operating systems.
 * This example uses the native HID driver for these operating systems.
 *
 * In host mode, after loading firmware, connect the board
 * to a USB device mouse.
 *
 * \copydoc UI
 *
 * \section example About example
 *
 * The example uses the following module groups:
 * - Basic modules:
 *   Startup, board, clock, interrupt, power management
 * - USB device and host stack and HID modules:
 *   <br>services/usb/
 *   <br>services/usb/udc/
 *   <br>services/usb/uhc/
 *   <br>services/usb/class/hid/
 *   <br>services/usb/class/hid/device/mouse/
 *   <br>services/usb/class/hid/host/mouse/
 * - Specific implementation:
 *    - main.c,
 *      <br>initializes clock
 *      <br>initializes interrupt
 *      <br>manages UI
 *    - specific implementation for each target "./examples/product_board/":
 *       - conf_foo.h   configuration of each module
 *       - ui.c        implement of user's interface (buttons, leds)
 */
