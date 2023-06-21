/**
 *
 * \file
 *
 * \brief SDIO Interface for SAMV7.
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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
 
/**@defgroup  SAMSDIO Defines
 * @ingroup sam_sdio
 * @{
 */
#ifndef _SAM_SDIO_H_
#define _SAM_SDIO_H_

#include "compiler.h"
#include "samv71_xplained_ultra.h"
#include "../include/nm_bus_wrapper.h"

#ifdef CONF_WILC_USE_SDIO 
/**
*	@fn		nmi_sdio_cmd52
*	@brief	SDIO Command 52
*	@return	M2M_SUCCESS in case of success and <0 in case of failure
*/ 
int8_t nmi_sdio_cmd52(tstrNmSdioCmd52* cmd);

/**
*	@fn		nmi_sdio_cmd53
*	@brief	SDIO Command 53
*	@return	M2M_SUCCESS in case of success and <0 in case of failure
*/ 
int8_t nmi_sdio_cmd53(tstrNmSdioCmd53* cmd);

/**
*	@fn		Samv7SDIO_init
*	@brief	SamV7 SDIO Init
*	@return	M2M_SUCCESS in case of success and <0 in case of failure
*/ 
int8_t Samv7SDIO_init(void);

/**
*	@fn		sdio_reset
*	@brief	Reset SDIO
*	@return	N.A
*/ 
void sdio_reset(void);
#endif /* CONF_WILC_USE_SDIO */
#endif	/*_SAM_SDIO_H_*/