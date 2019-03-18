/**
 * \file
 *
 * \brief User Interface
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include "ui.h"

void ui_init(void)
{
	LED_On(LED0);
	LED_Off(LED1);
}

void ui_powerdown(void)
{
	LED_Off(LED0);
	LED_Off(LED1);
}

void ui_wakeup(void)
{
	LED_On(LED0);
}

void ui_start_read(void)
{
	LED_On(LED1);
}

void ui_stop_read(void)
{
	LED_Off(LED1);
}

void ui_start_write(void)
{
	LED_On(LED1);
}

void ui_stop_write(void)
{
	LED_Off(LED1);
}

void ui_process(uint16_t framenumber)
{
	if (0 == framenumber) {
		LED_On(LED0);
	}
	if (1000 == framenumber) {
		LED_Off(LED0);
	}
}


/**
 * \defgroup UI User Interface
 *
 * Human interface on SAMV71-Xplained-Ultra:
 * - Led 0 blinks when USB host has checked and enabled MSC interface
 * - Led 1 is on during read and write operation
 *
 */
