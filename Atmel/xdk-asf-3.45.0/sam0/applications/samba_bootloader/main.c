/**
 * \file
 *
 * \brief SAM SAM-BA Bootloader
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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
 * \mainpage SAM-BA Bootloader Application
 *
 * \section Purpose
 *
 * The example will help new users get familiar with Atmel's SAM0 family microcontrollers
 * bootloader for SAM-BA. This basic application will be used when connecting with SAM-BA.
 *
 * \section Requirements
 *
 * This package can be used with SAM C21/D21/DA1/L21/L22/R21 xplained pro.
 *
 * \section Description
 *
 * The bootloader code will be located at 0x0 and executed before any applicative code.
 * Applications compiled to be executed along with the bootloader will start at 0x2000
 * (not support USBCDC interface) or 0x6000 (supoort USBCDC interface).
 * Before jumping to the application, the bootloader changes the VTOR register
 * to use the interrupt vectors of the application.
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board.
 * -# Start the application.
 * -# Pressing button SW0 the board will enter SAM-BA monitor mode.
 *
 */
 /*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include "conf_board.h"
#include "conf_clocks.h"
#include "conf_bootloader.h"
#include "sam_ba_monitor.h"
#include "usart_sam_ba.h"

static void check_start_application(void);

#ifdef CONF_USBCDC_INTERFACE_SUPPORT
static volatile bool main_b_cdc_enable = false;
#endif
/**
 * \brief Check the application startup condition
 *
 */
static void check_start_application(void)
{
	uint32_t app_start_address;

	/* Load the Reset Handler address of the application */
	app_start_address = *(uint32_t *)(APP_START_ADDRESS + 4);

	/**
	 * Test reset vector of application @APP_START_ADDRESS+4
	 * Stay in SAM-BA if *(APP_START+0x4) == 0xFFFFFFFF
	 * Application erased condition
	 */
	if (app_start_address == 0xFFFFFFFF) {
		/* Stay in bootloader */
		return;
	}

	volatile PortGroup *boot_port = (volatile PortGroup *)(&(PORT->Group[BOOT_LOAD_PIN / 32]));
	volatile bool boot_en;

	/* Enable the input mode in Boot GPIO Pin */
	boot_port->DIRCLR.reg = GPIO_BOOT_PIN_MASK;
	boot_port->PINCFG[BOOT_LOAD_PIN & 0x1F].reg = PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	boot_port->OUTSET.reg = GPIO_BOOT_PIN_MASK;
	/* Read the BOOT_LOAD_PIN status */
	boot_en = (boot_port->IN.reg) & GPIO_BOOT_PIN_MASK;

	/* Check the bootloader enable condition */
	if (!boot_en) {
		/* Stay in bootloader */
		return;
	}

	/* Rebase the Stack Pointer */
	__set_MSP(*(uint32_t *) APP_START_ADDRESS);

	/* Rebase the vector table base address */
	SCB->VTOR = ((uint32_t) APP_START_ADDRESS & SCB_VTOR_TBLOFF_Msk);

	/* Jump to application Reset Handler in the application */
	asm("bx %0"::"r"(app_start_address));
}


#if DEBUG_ENABLE
#	define DEBUG_PIN_HIGH 	port_pin_set_output_level(BOOT_LED, 1)
#	define DEBUG_PIN_LOW 	port_pin_set_output_level(BOOT_LED, 0)
#else
#	define DEBUG_PIN_HIGH 	do{}while(0)
#	define DEBUG_PIN_LOW 	do{}while(0)
#endif

/**
 *  \brief SAM-BA Main loop.
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{

	DEBUG_PIN_HIGH;

	/* Jump in application if condition is satisfied */
	check_start_application();

	/* We have determined we should stay in the monitor. */
	/* System initialization */
	system_init();

#ifdef CONF_USBCDC_INTERFACE_SUPPORT
	/* Start USB stack */
	udc_start();
#endif
	/* UART is enabled in all cases */
	usart_open();

	DEBUG_PIN_LOW;
	/* Wait for a complete enum on usb or a '#' char on serial line */
	while (1) {
#ifdef CONF_USBCDC_INTERFACE_SUPPORT
		/* Check if a USB enumeration has succeeded and com port was opened */
		if(main_b_cdc_enable) {
			sam_ba_monitor_init(SAM_BA_INTERFACE_USBCDC);
			/* SAM-BA on USB loop */
			while(1) {
				sam_ba_monitor_run();
			}
		}
#endif
		/* Check if a '#' has been received */
		if (usart_sharp_received()) {
			sam_ba_monitor_init(SAM_BA_INTERFACE_USART);
			/* SAM-BA on UART loop */
			while(1) {
				sam_ba_monitor_run();
			}
		}
	}
}

#ifdef CONF_USBCDC_INTERFACE_SUPPORT
#ifdef USB_DEVICE_LPM_SUPPORT
void main_suspend_lpm_action(void)
{
}

void main_remotewakeup_lpm_disable(void)
{
}

void main_remotewakeup_lpm_enable(void)
{
}
#endif

bool main_cdc_enable(uint8_t port)
{
	main_b_cdc_enable = true;
	return true;
}

void main_cdc_disable(uint8_t port)
{
	main_b_cdc_enable = false;
}

void main_cdc_set_dtr(uint8_t port, bool b_enable)
{
}

void main_cdc_rx_notify(uint8_t port)
{
}

void main_cdc_set_coding(uint8_t port, usb_cdc_line_coding_t * cfg)
{
}
#endif