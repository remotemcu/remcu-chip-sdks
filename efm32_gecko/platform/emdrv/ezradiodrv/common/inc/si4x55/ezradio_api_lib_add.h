/***************************************************************************//**
 * @file si4x55/ezradio_api_lib_add.h
 * @brief This file contains the additional API library for the listed members of
 * the EZRadio family: Si4055_revC2A, Si4355_revC2A, Si4455_revC2A.
 *
 * @note The ezradiodrv API is not settled entirely in the current relase.
 *
 * @version 5.1.2
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2015 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.@n
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.@n
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Silicon Labs has no
 * obligation to support this Software. Silicon Labs is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Silicon Labs will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/
 
#ifndef _EZRADIO_API_LIB_ADD_H_
#define _EZRADIO_API_LIB_ADD_H_

#include "ezradio_api_lib.h"


#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup emdrv
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup EZRADIODRV
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup API_Layer
 * @{
 ******************************************************************************/

EZRADIO_ConfigRet_t ezradio_configuration_init(const uint8_t* pSetPropCmd);

void ezradio_write_ezconfig_array(uint8_t numBytes, uint8_t* pEzConfigArray);
void ezradio_ezconfig_check(uint16_t checksum, ezradio_cmd_reply_t *ezradioReply);

#ifdef EZRADIO_DRIVER_EXTENDED_SUPPORT
/* Extended driver support functions */

#ifdef EZRADIO_DRIVER_FULL_SUPPORT
/* Full driver support functions */

void ezradio_get_adc_reading( uint8_t adc_en, uint8_t adc_cfg, ezradio_cmd_reply_t *ezradioReply);

#endif /* EZRADIO_DRIVER_FULL_SUPPORT */
#endif /* EZRADIO_DRIVER_EXTENDED_SUPPORT */

/** @} (end addtogroup API_Layer) */
/** @} (end addtogroup EZRADIODRV) */
/** @} (end addtogroup emdrv) */

#ifdef __cplusplus
}
#endif

#else //_EZRADIO_API_LIB_ADD_H_
#error Additional EZRadio API library is already defined.
#endif //_EZRADIO_API_LIB_ADD_H_
