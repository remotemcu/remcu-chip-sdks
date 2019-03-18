/**
 * \file
 *
 * \brief Configuration for the ADS7843 component.
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

//! Configuration of the ADS7843 touch driver

#ifndef CONF_ADS7843_H_INCLUDED
#define CONF_ADS7843_H_INCLUDED

#include "board.h"

#if !defined(BOARD_ADS7843_SPI_NPCS) || \
	!defined(BOARD_ADS7843_SPI_BASE)

	#warning The ADS7843 SPI configuration does not exist in the board definition file. Using default settings.
	/**
	 * SPI instance, which can be SPI, SPI0 or SPI1, depends on which SPI
	 * channel is used.
	 */
	#define BOARD_ADS7843_SPI_BASE    SPI

	/* SPI chip select NO., depends on which SPI CS pin is used by ADS7843. */
	#define BOARD_ADS7843_SPI_NPCS    0
#endif

#if !defined(BOARD_ADS7843_IRQ_FLAGS) || \
	!defined(BOARD_ADS7843_IRQ_GPIO)

	/** IRQ pin connected to nPENIRQ of ADS7843 */
	#define BOARD_ADS7843_IRQ_GPIO    PIO_PA16_IDX

	/**
	 * PIO type and attribute of the pin connected with nPENIRQ,
	 * normally should be (PIO_INPUT | PIO_PULLUP)
	 */
	#define BOARD_ADS7843_IRQ_FLAGS    IOPORT_MODE_PULLUP

#endif

#endif /* CONF_ADS7843_H_INCLUDED */
