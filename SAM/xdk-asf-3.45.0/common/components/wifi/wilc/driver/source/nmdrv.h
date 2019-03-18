/**
 *
 * \file
 *
 * \brief This module contains WILC M2M driver APIs declarations.
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

#ifndef _NMDRV_H_
#define _NMDRV_H_

#include "common/include/nm_common.h"
#include "driver/include/m2m_wifi.h"
#include "driver/source/m2m_hif.h"

#ifdef __cplusplus
     extern "C" {
 #endif

/*
*	@fn		nm_drv_init
*	@brief	Initialize NMC1000 driver
*	@return	M2M_SUCCESS in case of success and Negative error code in case of failure
*   @param [in]	arg
*				Generic argument TBD
*	@return	ZERO in case of success and Negative error code in case of failure

*/
sint8 nm_drv_init(void * arg);

/**
*	@fn		nm_drv_deinit
*	@brief	Deinitialize NMC1000 driver
*	@author	M. Abdelmawla
*   @param [in]	arg
*				Generic argument TBD
*	@return	ZERO in case of success and Negative error code in case of failure
*/
sint8 nm_drv_deinit(void * arg);

#ifdef __cplusplus
	 }
 #endif

#endif	/*_NMDRV_H_*/


