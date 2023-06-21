/**
 * \file
 *
 * \brief Configuration of the USI example application
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

#ifndef CONF_EXAMPLE_INCLUDED
#define CONF_EXAMPLE_INCLUDED

//! Maximum length of the input command
#define MAX_COMMAND_LENGTH  20

//! LED blinking rate in msec
#define COUNT_MS_SWAP_LED   500

//! \name TC configuration for msec timer
// @{
#define ID_TC_1MS		    ID_TC3
#define TC_1MS			    TC1
#define TC_1MS_CHN		  0
#define TC_1MS_IRQn		  TC3_IRQn
#define TC_1MS_Handler	TC3_Handler
// @}

#define STRING_EOL    "\r"
#define STRING_HEADER "-- ATMEL PLC USI Example Application --\r\n" \
		" -- "BOARD_NAME" --\r\n" \
		" -- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

#define PROGRAM_MAIN_MENU "Introduce command:\n"STRING_EOL



#endif /* CONF_EXAMPLE_INCLUDED */
