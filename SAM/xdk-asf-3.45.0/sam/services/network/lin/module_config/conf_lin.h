/**
 * \file
 *
 * \brief Usart LIN driver configuration file.
 *
 * This file contains basic functions for the SAM USART, with support for all
 * modes, settings and clock speeds.
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

#ifndef CONF_LIN_H_INCLUDED
#define CONF_LIN_H_INCLUDED

#ifndef USART_LIN_VERSION
	#warning USART LIN version configuration to be used in the driver is missing. Default configuration is used.
	/** LIN Version Supported LIN_13 or LIN_20 */
	#define USART_LIN_VERSION                   LIN_2x
#endif

#ifndef LIN_NODE_NUM
	#warning USART LIN node number used in the driver is missing. Default configuration is used.
	/** LIN node number */
	#define LIN_NODE_NUM                   2
#endif

#ifndef LIN_BUFF_SIZE
	#warning Size of LIN buffer used in the driver is missing. Default configuration is used.
	/** LIN buffer size */
	#define LIN_BUFF_SIZE                   256
#endif

/* NUMBER_OF_LIN_FRAMES_NODE */
#ifndef NUMBER_OF_LIN_FRAMES_NODE
	#warning LIN frame node in the driver is missing. Default configuration is used.
	#define NUMBER_OF_LIN_FRAMES_NODE    8
#endif

#endif  /* CONF_LIN_H_INCLUDED */
