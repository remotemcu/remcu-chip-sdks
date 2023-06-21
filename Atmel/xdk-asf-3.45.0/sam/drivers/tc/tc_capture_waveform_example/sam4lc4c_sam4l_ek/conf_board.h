/**
 * \file
 *
 * \brief  Configuration File for SAM4L-EK Board.
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef CONF_BOARD_H_INCLUDED
#define CONF_BOARD_H_INCLUDED

/** Enable Com Port. */
#define CONF_BOARD_COM_PORT

/**
 * \note For test the example in SAM4L-EK, we need:
 * 1. Connect pin 3 and pin 7 on J4.
 * 2. Remove jumper on J600, J601 (disconnect from board monitor)
 * 3. Remove jumper on J200, J203 (disconnect from RS485)
 */

#define TC  TC1
#define TC_PERIPHERAL  1

/** Configure TC1 channel 2 as waveform output. **/
#define TC_CHANNEL_WAVEFORM 2
#define ID_TC_WAVEFORM TC1
#define PIN_TC_WAVEFORM PIN_PC04D_TC1_A2
#define PIN_TC_WAVEFORM_MUX MUX_PC04D_TC1_A2

/** Configure TC1 channel 1 as capture input. **/
#define TC_CHANNEL_CAPTURE 1
#define ID_TC_CAPTURE TC1
#define PIN_TC_CAPTURE PIN_PC02D_TC1_A1
#define PIN_TC_CAPTURE_MUX (MUX_PC02D_TC1_A1)

/** Use TC11_Handler for TC capture interrupt**/
#define TC_Handler  TC11_Handler
#define TC_IRQn     TC11_IRQn

#endif  /* CONF_BOARD_H_INCLUDED */
