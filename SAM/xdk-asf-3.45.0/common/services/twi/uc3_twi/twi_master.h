/*****************************************************************************
 *
 * \file
 *
 * \brief TWI Master driver for AVR UC3.
 *
 * This file defines a useful set of functions for the TWI interface on AVR UC3
 * devices.
 *
 * Copyright (c) 2009-2018 Microchip Technology Inc. and its subsidiaries.
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
 ******************************************************************************/
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */


#ifndef _TWI_MASTER_H_
#define _TWI_MASTER_H_

#include "compiler.h"
#include "sysclk.h"
#include "status_codes.h"
#include "twi.h"

typedef volatile avr32_twi_t *twi_master_t;
typedef twi_options_t twi_master_options_t;

static inline int twi_master_setup(twi_master_t twi, twi_master_options_t *opt)
{
  int status;
  opt->pba_hz = sysclk_get_pba_hz();
  sysclk_enable_pba_module(SYSCLK_TWI);
  status = twi_master_init(twi, (const twi_master_options_t *)opt);
  return(status);
}

#endif  // _TWI_MASTER_H_
