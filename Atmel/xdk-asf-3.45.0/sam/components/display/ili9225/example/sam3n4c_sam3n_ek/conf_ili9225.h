/**
 * \file
 *
 * \brief ILI9225 configuration.
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

//! Configuration of the ILI9225 LCD display driver

#ifndef CONF_ILI9225_H_INCLUDED
#define CONF_ILI9225_H_INCLUDED

#include "board.h"

#if !defined(BOARD_ILI9225_SPI) || \
	!defined(BOARD_ILI9225_SPI_IRQN) || \
	!defined(BOARD_ILI9225_SPI_NPCS) || \
	!defined(BOARD_ILI9225_RS_GPIO) || \
	!defined(BOARD_ILI9225_RSTN_GPIO)

	#warning The ILI9225 SPI configuration does not exist in the board definition file. Using default settings.

	#define BOARD_ILI9225_SPI               0 /* SPI instance, which can be SPI, SPI0 or SPI1, depends on which SPI channel is used by ILI9225 */
	#define BOARD_ILI9225_SPI_IRQN    0 /* SPI interrupt number, which can be SPI_IRQn, SPI0_IRQn or SPI1_IRQn, depends on which SPI channel is used by ILI9225 */
	#define BOARD_ILI9225_SPI_NPCS    2 /* SPI chip select number, depends on which SPI CS pin is used */
	#define BOARD_ILI9225_RS_GPIO     PIO_PA28_IDX /* PIN index, depends on which pin is connnected with RS of ILI9225 */
	#define BOARD_ILI9225_RSTN_GPIO   PIO_PA29_IDX /* PIN index, depends on which pin is connnected with nRESET of ILI9225 */

#endif

#endif /* CONF_ILI9225_H_INCLUDED */
