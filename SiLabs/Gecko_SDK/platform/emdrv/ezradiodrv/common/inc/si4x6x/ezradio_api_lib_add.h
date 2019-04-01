/***************************************************************************//**
 * @file si4x6x/ezradio_api_lib_add.h
 * @brief This file contains the additional API library for the listed members of
 * the EZRadioPRO family: Si4460_revC2A, Si4461_revC2A, Si4463_revC2A.
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

#ifdef EZRADIO_DRIVER_EXTENDED_SUPPORT
/* Extended driver support functions */

#ifdef EZRADIO_DRIVER_FULL_SUPPORT
/* Full driver support functions */

void ezradio_get_adc_reading( uint8_t adc_en, uint8_t adc_cfg, ezradio_cmd_reply_t *ezradioReply );

void ezradio_ircal(uint8_t searching_step_size, uint8_t searching_rssi_avg, uint8_t rx_chain_setting1, uint8_t rx_chain_setting2);
void ezradio_ircal_manual(uint8_t ircal_amp, uint8_t ircal_ph, ezradio_cmd_reply_t *ezradioReply );

void ezradio_tx_hop(uint8_t inte, uint8_t frac2, uint8_t frac1, uint8_t frac0, uint8_t vco_cnt1, uint8_t vco_cnt0, uint8_t pll_settle_time1, uint8_t pll_settle_time0);
void ezradio_rx_hop(uint8_t inte, uint8_t frac2, uint8_t frac1, uint8_t frac0, uint8_t vco_cnt1, uint8_t vco_cnt0);

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
