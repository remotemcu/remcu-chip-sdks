/**
 * \file
 *
 * \brief CDC Application Main functions
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

static volatile bool main_b_cdc_enable = false;

/*! \brief Main function. Execution starts here.
 */
int main(void)
{

	irq_initialize_vectors();
	cpu_irq_enable();

	// Initialize the sleep manager
	sleepmgr_init();

	system_init();

	ui_init();
	ui_powerdown();

	// Start USB stack to authorize VBus monitoring
	udc_start();

	// The main loop manages only the power mode
	// because the USB management is done by interrupt
	while (true) {
		sleepmgr_enter_sleep();
		if (!main_b_cdc_enable) {
			continue;
		}
		if (udi_cdc_is_rx_ready()) {
			udi_cdc_putc(udi_cdc_getc());
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
	if (!main_b_cdc_enable)
		return;

	ui_process(udd_get_frame_number());
}

bool main_cdc_enable(uint8_t port)
{
	main_b_cdc_enable = true;
	return true;
}

void main_cdc_disable(uint8_t port)
{
	main_b_cdc_enable = false;
}

/**
 * \mainpage ASF USB Device CDC
 *
 * \section intro Introduction
 * This example shows how to implement an echo application by USB Device CDC
 * on Atmel MCU with USB module.
 *
 * \section desc Description of the Communication Device Class (CDC)
 * The Communication Device Class (CDC) is a general-purpose way to enable all
 * types of communications on the Universal Serial Bus (USB).
 * This class makes it possible to connect communication devices such as
 * digital telephones or analog modems, as well as networking devices
 * like ADSL or Cable modems.
 * While a CDC device enables the implementation of quite complex devices,
 * it can also be used as a very simple method for communication on the USB.
 * For example, a CDC device can appear as a virtual COM port, which greatly
 * simplifies application development on the host side.
 *
 * \section startup Startup
 * The example is an echo application by USB CDC interface.
 *
 * In this example, we will use a PC as a USB host:
 * it connects to the USB.
 * - Connect the application to a USB host (e.g. a PC)
 *   with a mini-B (embedded side) to A (PC host side) cable.
 * The application will behave as a virtual COM (see Windows Device Manager).
 * - Open a HyperTerminal on COM port (Virtual COM)
 * - Select the same configuration for COM ports up to 115200 baud.
 * - Type a character in one HyperTerminal and it will echo.
 *
 * \note
 * On the first connection of the board on the PC,
 * the operating system will detect a new peripheral:
 * - This will open a new hardware installation window.
 * - Choose "No, not this time" to connect to Windows Update for this installation
 * - click "Next"
 * - When requested by Windows for a driver INF file, select the
 *   atmel_devices_cdc.inf file in the directory indicated in the Atmel Studio
 *   "Solution Explorer" window.
 * - click "Next"
 *
 * \copydoc UI
 *
 * \section example About example
 *
 * The example uses the following module groups:
 * - Basic modules:
 *   Startup, board, clock, interrupt, power management
 * - USB Device stack and CDC modules:
 *   <br>services/usb/
 *   <br>services/usb/udc/
 *   <br>services/usb/class/cdc/
 * - Specific implementation:
 *    - main.c,
 *      <br>initializes clock
 *      <br>initializes interrupt
 *      <br>manages UI
 *    - specific implementation for each target "./examples/product_board/":
 *       - conf_foo.h  configuration of each module
 *       - ui.c        implement of user's interface (leds,buttons...)
 */
