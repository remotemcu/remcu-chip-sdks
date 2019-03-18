/**
 * \file
 *
 * \brief AT25DFx configuration.
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

#ifndef CONF_AT25DFX_H_INCLUDED
#define CONF_AT25DFX_H_INCLUDED

#include "at25dfx.h"
#include "board.h"

/* Connect AT25DFx driver to SPI master service */
#define AT25DFX_USES_SPI_MASTER_SERVICE

/* Number of AT25DFx components to manage */
#define AT25DFX_MEM_CNT           1

/* Memory ID of AT25DFx components to manage */
#define AT25DFX_MEM_ID            1

/* SPI master speed in Hz */
#define AT25DFX_SPI_MASTER_SPEED  12000000

/* Number of bits in each SPI transfer */
#define AT25DFX_SPI_BITS          8

/** AT25DFx device type */
#define AT25DFX_MEM_TYPE          AT25DFX_321A

#endif  /* CONF_AT25DFX_H_INCLUDED */
