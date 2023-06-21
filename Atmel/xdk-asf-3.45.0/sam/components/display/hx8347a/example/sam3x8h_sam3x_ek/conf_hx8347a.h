/**
 * \file
 *
 * \brief HX8347A configuration.
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

//! Configuration of the HX8347A LCD display driver

#ifndef CONF_HX8347A_H_INCLUDED
#define CONF_HX8347A_H_INCLUDED

#include "compiler.h"
#include "board.h"

/*! \brief Interface configuration
 *
 * Currently only EBI mode supported
 */
#if BOARD == SAM3U_EK

	/*! \brief address used to write to the index register
	 */
	#define HX8347A_LCD_BASE     (BOARD_LCD_BASE)

	/*! \brief address used to read/write from/to registers or RAM
	 */
	#define HX8347A_LCD_RS       (BOARD_LCD_RS)

#elif BOARD == SAM3X_EK

	/*! \brief address used to write to the index register
	 */
	#define HX8347A_LCD_BASE     (BOARD_LCD_BASE)

	/*! \brief address used to read/write from/to registers or RAM
	 */
	#define HX8347A_LCD_RS       (BOARD_LCD_RS)

#else

	#warning The HX8347A setups configuration to use in the driver is missing. Default configuration is used.

	#define HX8347A_LCD_BASE     0
	#define HX8347A_LCD_RS       0

#endif

#endif /* CONF_HX8347A_H_INCLUDED */
