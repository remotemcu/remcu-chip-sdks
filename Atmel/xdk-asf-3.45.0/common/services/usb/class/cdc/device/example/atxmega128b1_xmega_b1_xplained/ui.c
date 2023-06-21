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

void ui_init(void)
{
	LED_On(LED0_GPIO);
	LED_Off(LED1_GPIO);
	LED_Off(LED2_GPIO);
	LED_Off(LED3_GPIO);
}

void ui_powerdown(void)
{
	LED_Off(LED0_GPIO);
	LED_Off(LED1_GPIO);
	LED_Off(LED2_GPIO);
	LED_Off(LED3_GPIO);
	led_power_off();
}

void ui_wakeup(void)
{
	LED_On(LED0_GPIO);
	led_power_on();
}

void ui_com_open(uint8_t port)
{
	LED_On(LED1_GPIO);
}

void ui_com_close(uint8_t port)
{
	LED_Off(LED1_GPIO);
	LED_Off(LED2_GPIO);
	LED_Off(LED3_GPIO);
}

void ui_com_rx_start(void)
{
	LED_On(LED2_GPIO);
}

void ui_com_rx_stop(void)
{
	LED_Off(LED2_GPIO);
}

void ui_com_tx_start(void)
{
	LED_On(LED3_GPIO);
}

void ui_com_tx_stop(void)
{
	LED_Off(LED3_GPIO);
}

void ui_com_error(void)
{
}

void ui_com_overflow(void)
{
}

void ui_process(uint16_t framenumber)
{
	if (0 == framenumber) {
		LED_On(LED0_GPIO);
	}
	if (1000 == framenumber) {
		LED_Off(LED0_GPIO);
	}
}

/**
 * \defgroup UI User Interface
 *
 * Human interface on XMEGA-B1 Xplained:
 * - Led 0 and the RED led close to USB connector are on
 *   when USB line is in IDLE mode, and off in SUSPEND mode
 * - Led 1 blinks when USB host has checked and enabled CDC interface
 * - Led 2 is on during data transfer from CDC to UART
 * - Led 3 is on during data transfer from UART to CDC
 */
