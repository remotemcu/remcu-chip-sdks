/**
 * \file
 *
 * \brief User Interface
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
#include "ui.h"

static volatile bool ui_b_dtr_enable = false;
static volatile bool ui_b_error_occur = false;

void ui_init(void)
{
	LED_Off(LED0);
	LED_Off(LED1);
}

void ui_powerdown(void)
{
	LED_Off(LED0);
	LED_Off(LED1);
}

void ui_wakeup(void)
{
}

void ui_com_open(uint8_t port)
{
	// Here the COM port has been open on terminal
	ui_b_dtr_enable = true;
	ui_b_error_occur = false; // Reset error notification
}

void ui_com_close(uint8_t port)
{
	// Here the COM port has been close on terminal
	ui_b_dtr_enable = false;
	ui_b_error_occur = false; // Reset error notification
}

void ui_com_rx_start(void)
{
	LED_On(LED1);
}

void ui_com_rx_stop(void)
{
}

void ui_com_tx_start(void)
{
	LED_On(LED1);
}

void ui_com_tx_stop(void)
{
}

void ui_com_error(void)
{
	ui_b_error_occur = true;
}

void ui_com_overflow(void)
{
	ui_b_error_occur = true;
}

void ui_process(uint16_t framenumber)
{
	static uint16_t sof_counter=0;
	uint16_t frequency;

	if (!ui_b_dtr_enable) {
		// Port not open by terminal
		// Blink each 1s
		frequency = 1000;
	}else{
		if (!ui_b_error_occur) {
			// Port is open by terminal
			// Blink each 0.5s
			frequency = 500;
		}else{
			// Port is open and an error has occurred
			// Blink each 250ms
			frequency = 250;
		}
	}
	if ((sof_counter++ % frequency) == 0) {
		LED_Toggle(LED0);
		LED_Off(LED1);
	}
}


/**
 * \defgroup UI User Interface
 *
 * Human interface on uc3b board controller:
 * - Led 0 blink (each 1s) when CDC is enumerated by host
 * - Led 0 blink (each 0.5s) when communication port is open by a terminal
 * - Led 0 blink (each 0.25s) when an underflow/overflow occurs
 * - Led 1 is on during data transfer
 */
