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

//! Osc frequency (Hz.) and startup time (RCOsc periods).
#define FOSC0                       (12000000)

//! Osc32 frequency (Hz.) and startup time (RCOsc periods).
#define FOSC32                      (32768)

/**
 * \name Board oscillator configuration
 *
 */
//@{
#define BOARD_OSC32_IS_XTAL         true
#define BOARD_OSC32_HZ              FOSC32
#define BOARD_OSC32_STARTUP_US      (1100000)
#define BOARD_OSC32_SELCURR         BSCIF_OSCCTRL32_SELCURR(10)
#define BOARD_OSC0_IS_XTAL          true
#define BOARD_OSC0_HZ               FOSC0
#define BOARD_OSC0_STARTUP_US       (1100)
//@}

//! \name USART connections to GPIO
// @{
#define COM_PORT_USART                 USART2
#define COM_PORT_USART_ID              ID_USART2
#define COM_PORT_RX_PIN                PIN_PC11B_USART2_RXD
#define COM_PORT_RX_GPIO               GPIO_PC11B_USART2_RXD
#define COM_PORT_RX_MUX                MUX_PC11B_USART2_RXD
#define COM_PORT_TX_PIN                PIN_PC12B_USART2_TXD
#define COM_PORT_TX_GPIO               GPIO_PC12B_USART2_TXD
#define COM_PORT_TX_MUX                MUX_PC12B_USART2_TXD
// @}

/* Enable Com Port. */
#define CONF_BOARD_COM_PORT

/* Enable GLOC LUT 0 pins. */
#define CONF_BOARD_GLOC_LUT0_PORT

#endif /* CONF_BOARD_H_INCLUDED */
