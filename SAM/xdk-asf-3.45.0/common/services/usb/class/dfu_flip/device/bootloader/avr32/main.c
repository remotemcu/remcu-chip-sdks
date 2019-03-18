/**
 * \file
 *
 * \brief Main functions
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
#include "sysclk_auto.h"

/*! \brief Main function. Execution starts here.
 */
int main(void)
{
#if UC3D
	static const gpio_map_t USB_GPIO_MAP =
	{
		{AVR32_USBC_DP_0_PIN, AVR32_USBC_DP_0_FUNCTION},
		{AVR32_USBC_DM_0_PIN, AVR32_USBC_DM_0_FUNCTION},
		{AVR32_USBC_VBUS_0_PIN, AVR32_USBC_VBUS_0_FUNCTION}
	};

	// Assign GPIO pins to USB.
	gpio_enable_module(USB_GPIO_MAP,
			sizeof(USB_GPIO_MAP) / sizeof(USB_GPIO_MAP[0]));
#elif UC3L3_L4
	static const gpio_map_t USB_GPIO_MAP = {
		{AVR32_USBC_DP_0_PIN, AVR32_USBC_DP_0_FUNCTION},
		{AVR32_USBC_DM_0_PIN, AVR32_USBC_DM_0_FUNCTION}
	};

	// Assign GPIO pins to USB.
	gpio_enable_module(USB_GPIO_MAP,
			sizeof(USB_GPIO_MAP) / sizeof(USB_GPIO_MAP[0]));
#endif

	cpu_irq_enable();

	sysclk_auto_init();

	// Start USB stack to authorize VBus monitoring
	udc_start();

	while (true) {
	}
}

/**
 * \mainpage ASF USB Device DFU
 *
 * \section intro Introduction
 * This application is the official Atmel USB DFU bootloader for the UC3 devices.
 *
 * The guide of this bootloader is proposed in the following application note
 * "AVR32806-AVR UC3 USB DFU Bootloader version 1.1.0 and higher".
 *
 * \section files Application Files
 * The specific files of application are:
 * - main.c: the main file to start clock and USB DFU Device.
 * - sysclk_auto.c: specific system clock management to support automatically
 * detection of external oscillator
 * - intc.c: specific INTC driver optimized to save code
 * - specific linker script to store the bootloader in RAM at address 0x0 instead of 0x2000.
 */


