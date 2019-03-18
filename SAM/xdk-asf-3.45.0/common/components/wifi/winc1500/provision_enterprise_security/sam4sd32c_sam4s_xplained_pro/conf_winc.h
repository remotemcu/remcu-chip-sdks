/**
 *
 * \file
 *
 * \brief WINC1500 configuration.
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef CONF_WINC_H_INCLUDED
#define CONF_WINC_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "board.h"

/*
   ---------------------------------
   ---------- PIN settings ---------
   ---------------------------------
*/

#define CONF_WINC_PIN_RESET				IOPORT_CREATE_PIN(PIOA, 24)
#define CONF_WINC_PIN_CHIP_ENABLE		IOPORT_CREATE_PIN(PIOA, 6)
#define CONF_WINC_PIN_WAKE				IOPORT_CREATE_PIN(PIOA, 25)

/*
   ---------------------------------
   ---------- SPI settings ---------
   ---------------------------------
*/

#define CONF_WINC_USE_SPI				(1)

/** SPI pin and instance settings. */
#define CONF_WINC_SPI					SPI
#define CONF_WINC_SPI_ID				ID_SPI
#define CONF_WINC_SPI_MISO_GPIO			SPI_MISO_GPIO
#define CONF_WINC_SPI_MISO_FLAGS		SPI_MISO_FLAGS
#define CONF_WINC_SPI_MOSI_GPIO			SPI_MOSI_GPIO
#define CONF_WINC_SPI_MOSI_FLAGS		SPI_MOSI_FLAGS
#define CONF_WINC_SPI_CLK_GPIO			SPI_SPCK_GPIO
#define CONF_WINC_SPI_CLK_FLAGS			SPI_SPCK_FLAGS
#define CONF_WINC_SPI_CS_GPIO			SPI_NPCS0_GPIO
#define CONF_WINC_SPI_CS_FLAGS			PIO_OUTPUT_1
#define CONF_WINC_SPI_NPCS				(0)

/** SPI delay before SPCK and between consecutive transfer. */
#define CONF_WINC_SPI_DLYBS				(0)
#define CONF_WINC_SPI_DLYBCT 			(0)

/** SPI interrupt pin. */
#define CONF_WINC_SPI_INT_PIN			IOPORT_CREATE_PIN(PIOA, 1)
#define CONF_WINC_SPI_INT_PIO			PIOA
#define CONF_WINC_SPI_INT_PIO_ID		ID_PIOA
#define CONF_WINC_SPI_INT_MASK			(1 << 1)
#define CONF_WINC_SPI_INT_PRIORITY		(0)

/** Clock polarity & phase. */
#define CONF_WINC_SPI_POL				(0)
#define CONF_WINC_SPI_PHA				(1)

/** SPI clock.
 ** Exact SPI frequency will depend on the CPU clock configuration and it
 ** will be less than or equal to what is configured in CONF_WINC_SPI_CLOCK
*/ 
#define CONF_WINC_SPI_CLOCK				(48000000)

/*
   ---------------------------------
   --------- Debug Options ---------
   ---------------------------------
*/

#define CONF_WINC_DEBUG					(1)
#define CONF_WINC_PRINTF				printf

#ifdef __cplusplus
}
#endif

#endif /* CONF_WINC_H_INCLUDED */
