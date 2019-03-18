/**
 * \file
 *
 * \brief Serial USART service configuration
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

#ifndef CONF_USART_SERIAL_H
#define CONF_USART_SERIAL_H

#define OUT_BUFFER_LENGTH    2048

//! USART initialize with the CONFIG_PBA_HZ
extern int usart_ready;

static inline int usart_write_char_buf(volatile avr32_usart_t *usart, int c)
{
	static int c_count;
	static unsigned char c_buf[OUT_BUFFER_LENGTH];
	static bool buf_output_flag = 0;
	int i;
	if(usart_ready != 1) {
		c_buf[c_count] = c;
		c_count++;
		if(c_count >= OUT_BUFFER_LENGTH)
			c_count = 0;
		return 1;
	}
	if((usart_ready==1) && !buf_output_flag) {
		buf_output_flag = 1;
		c_buf[c_count] = c;
		for(i=0; i<= c_count; i++){
			while (usart_write_char(usart, c_buf[i])!=USART_SUCCESS);
		}
		return 1;
	}
	while (usart_write_char(usart, c)!=USART_SUCCESS);
	return 1;
}

#endif
