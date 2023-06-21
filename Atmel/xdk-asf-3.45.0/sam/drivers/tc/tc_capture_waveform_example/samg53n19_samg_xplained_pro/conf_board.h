/**
 * \file
 *
 * \brief Board configuration.
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

#ifndef CONF_BOARD_H_INCLUDED
#define CONF_BOARD_H_INCLUDED

/** Enable Com Port. */
#define CONF_BOARD_UART_CONSOLE

/**
 * \note For test the example on SAMG53 Xplained Pro, we need to connect pin7
 * in EXT1 and pin7 in EXT3.
 */

/** Use TC Peripheral 0 **/
#define TC             TC0
#define TC_PERIPHERAL  0

/** Configure TC0 channel 0 as waveform output. **/
#define TC_CHANNEL_WAVEFORM 0
#define ID_TC_WAVEFORM      ID_TC0
#define PIN_TC_WAVEFORM     EXT1_PIN_PWM_0
#define PIN_TC_WAVEFORM_MUX EXT1_PWM_0_MUX

/** Configure TC0 channel 2 as capture input. **/
#define TC_CHANNEL_CAPTURE 2
#define ID_TC_CAPTURE ID_TC2
#define PIN_TC_CAPTURE EXT3_PIN_PWM_0
#define PIN_TC_CAPTURE_MUX EXT3_PWM_0_MUX

/** Use TC2_Handler for TC capture interrupt**/
#define TC_Handler  TC2_Handler
#define TC_IRQn     TC2_IRQn

#endif /* CONF_BOARD_H_INCLUDED */
