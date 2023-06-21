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

/*! \brief Main function. Execution starts here.
 */
int main(void)
{
	// Map interrupt vectors table in bootloader section
	ccp_write_io((uint8_t*)&PMIC.CTRL, PMIC_IVSEL_bm | PMIC_LOLVLEN_bm
			| PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm);

	sysclk_init();
	cpu_irq_enable();

	// Start USB stack to authorize VBus monitoring
	udc_start();

	while (true) {
	}
}


/**
 * \mainpage ASF USB Device DFU
 *
 * \section intro Introduction
 * This application is the official Atmel USB DFU bootloader for XMEGA.
 *
 * A USB DFU bootloader guide is proposed for all AVR XMEGA parts with USB interface:
 *
 * \section files Application Files
 * The specific files of application are:
 * - main.c: the main file to start clock and USB DFU Device.
 * - specific linker script
 * - specific optimized codes to fit with boot section size
 */
