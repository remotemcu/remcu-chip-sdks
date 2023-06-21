/** \defgroup m2m_coex WLAN
 *
 * \file
 *
 * \brief WILC IoT Application Interface.
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

#ifndef __M2M_COEX_H__
#define __M2M_COEX_H__

#ifdef CONF_WILC_USE_3000_REV_A

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
INCLUDES
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#include "common/include/nm_common.h"
#include "driver/include/m2m_types.h"



/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
MACROS
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
/**@defgroup  CoexEnums Enumeration/Typedef
 * @ingroup m2m_coex
 * @{
 */
/*!
@enum	\
	tenuCoexMode

@brief
	Enumeration for Coexistence mode 
	The following types are used to specify which mode a WILC would operate in.
	
@remarks
	The operation mode is applicable only to WILC devices that supports multiple radio standards
	e.g. Wifi and BT.
*/
typedef enum {
	M2M_COEX_MODE_WIFI            = 0x00,
	/*!< Force Wi-Fi only mode.
	*/
	M2M_COEX_MODE_BT               = 0x01,
	/*!< Force BT only mode.
	*/
	M2M_COEX_MODE_COMBO        = 0x02,
	/*!< Force Wifi/BT combo mode.
	*/
}tenuCoexMode;

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
FUNCTION PROTOTYPES
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
/** \defgroup COEXAPI Function
 *   @ingroup m2m_coex
 */
#ifdef __cplusplus
     extern "C" {
#endif
 
 /**@}*/
 /** @defgroup CoexSetModeFn m2m_coex_set_mode
 *  @ingroup COEXAPI
 *   Synchronous function to set the coexistence mode.
 *   Dinitializes the host interface and frees resources used by the M2M_WIFI layer.
 *   Must be called in the application closing function, to ensure that all resources have been correctly released. 
 *   No arguments are expected to be passed in.
 */
/**@{*/
/*!
@fn	\
	NMI_API sint8  m2m_coex_set_mode(tenuCoexMode* enuCoexMode);
	
@param [in]	enuCoexMode
		Required mode of operation for coexistence.
@return		
	The function returns @ref M2M_SUCCESS for successful operations and a negative value otherwise.
*/
NMI_API sint8  m2m_coex_set_mode(tenuCoexMode enuCoexMode);

#ifdef __cplusplus
}

#endif /* CONF_WILC_USE_3000_REV_A*/
#endif
#endif /* __M2M_COEX_H__ */
