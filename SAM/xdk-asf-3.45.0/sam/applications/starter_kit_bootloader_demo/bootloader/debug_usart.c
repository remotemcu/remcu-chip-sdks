/**
 * \file
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

#include "bootloader.h"

#ifdef DBG_USE_USART

#define DBG_USART_BASE ((Usart*)ATPASTE2(DBG_USART_NAME,DBG_USART_NB))
#define DBG_USART_ID   (ATPASTE3(ID_,DBG_USART_NAME,DBG_USART_NB))

#ifndef DBG_USART_PARITY
#  define DBG_USART_PARITY     US_MR_PAR_NO
#endif
#ifndef DBG_USART_CHR_LENGTH
#  define DBG_USART_CHR_LENGTH US_MR_CHRL_8_BIT
#endif
#ifndef DBG_USART_STOP_BITS
#  define DBG_USART_STOP_BITS  US_MR_NBSTOP_1_BIT
#endif
#ifndef DBG_USART_MODE
#  define DBG_USART_MODE       US_MR_CHMODE_NORMAL
#endif

static void _dbg_usart_pins_init(void)
{
#ifdef DBG_USART_PIN_EN
	ioport_set_pin_dir(DBG_USART_PIN_EN, IOPORT_DIR_OUTPUT);
	ioport_enable_pin(DBG_USART_PIN_EN);
	ioport_set_pin_level(DBG_USART_PIN_EN, DBG_USART_PIN_EN_LEVEL);
#endif
#if defined(DBG_USART_PIN_TX)
	ioport_set_pin_mode(DBG_USART_PIN_TX, DBG_USART_PIN_TX_MUX);
	ioport_disable_pin(DBG_USART_PIN_TX);
#endif
#if defined(DBG_USART_PIN_RX)
	ioport_set_pin_mode(DBG_USART_PIN_RX, DBG_USART_PIN_TX_MUX);
	ioport_disable_pin(DBG_USART_PIN_RX);
#endif
}

/**
 * Initialize USART serial as debug communication port
 */
void dbg_usart_init(void)
{
	/* USART pins init */
	_dbg_usart_pins_init();
	/* Configure USART */
    const usart_serial_options_t options = {
        .baudrate   = DBG_USART_BAUDRATE,
		.charlength = DBG_USART_CHR_LENGTH,
		.paritytype = DBG_USART_PARITY,
		.stopbits   = DBG_USART_STOP_BITS
    };
	stdio_serial_init(DBG_USART_BASE, &options);
}

/**
 * Close USART serial debug communication port
 */
void dbg_usart_cleanup(void)
{
	usart_disable_tx(DBG_USART_BASE);
	usart_disable_rx(DBG_USART_BASE);
	usart_reset(DBG_USART_BASE);
	pmc_disable_periph_clk(DBG_USART_ID);
}

/**
 * Check if there is console input
 * \return true if there is input
 */
bool dbg_usart_rx_ready(void)
{
	return usart_serial_is_rx_ready(DBG_USART_BASE);
}

/**
 * Get a byte from console
 * \return byte read
 */
uint8_t dbg_usart_getchar(void)
{
	uint8_t byte;
	usart_serial_getchar(DBG_USART_BASE, &byte);
	return byte;
}

/**
 * Put a byte to console
 * \param c The byte to put
 */
void dbg_usart_putchar(uint8_t c)
{
	usart_serial_putchar(DBG_USART_BASE, c);
}

#endif /* #ifdef DBG_USE_USART */

