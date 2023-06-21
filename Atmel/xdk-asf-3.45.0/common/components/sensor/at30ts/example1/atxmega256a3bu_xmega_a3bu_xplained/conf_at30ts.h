/**
 * \file
 *
 * \brief AT30TS Temperature Sensor configuration file.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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
#ifndef _CONF_AT30TS_H_
#define _CONF_AT30TS_H_

/** \brief ACK_POLLING_INTERATION
 *
 * With an oscilloscope or logic analyzer, determine the number of NACK
 * iteration required for ts_ack_polling() to span 5ms.  5ms is the
 * maximum time required for a nonvolatile operation to complete.
 *
 * For example: With the F_CPU running at 16MHz and an optimization of -O2,
 * it takes 165 iterations of ts_ack_polling to span 5ms.
 */

/* FOR ACK POLLING */
#define ACK_POLLING_ITERATION  1000

#define TWI_MODULE        &TWIC

/* Device type must be defined in the project options*/
#if    (!_AT30TS75_   && \
	!_AT30TS750_  && \
	!_AT30TSE752_ && \
	!_AT30TSE754_ && \
	!_AT30TSE758_ && \
	!_AT30TSE00_  && \
	!_AT30TSE002B_)

	 #error No Digital Temperature Sensors device defined
#define _AT30TSE758_
#endif

#endif // _CONF_AT30TS_H_
