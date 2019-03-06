/***************************************************************************//**
 * @file ezradio_unmod_carrier_plugin.h
 * @brief EzRadio unmodulated carrier plug-in managed by the plug-in manager if enabled.
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


#ifndef EZRADIO_UNMOD_CARRIER_PLUGIN_H_
#define EZRADIO_UNMOD_CARRIER_PLUGIN_H_

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
 * @addtogroup Plugin_System
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup Unmod_Carrier_Plugin
 * @brief Unmodulated Carrier plugin, see @ref ezradiodrv_plugin 
 *        for detailed documentation. 
 * @{
 ******************************************************************************/

#if defined( EZRADIO_PLUGIN_UNMOD_CARRIER )

/// EzRadio unmodulated carrier plug-in instance initialization and handler structure.
typedef struct EZRADIODRV_UnmodCarrierHandle
{
  uint8_t channel;      ///< Unmodulated carrier transmit channel.
} EZRADIODRV_UnmodCarrierHandle_t;

Ecode_t ezradioStartUnmodulatedCarrier(EZRADIODRV_Handle_t radioHandle );
Ecode_t ezradioStopUnmodulatedCarrier( void );

/// Configuration data for EzRadio unmodulated carrier plug-in.
#define EZRADIODRV_UNMOD_CARRIER_PLUGIN_INIT_DEFAULT                         \
{                               /* Unmodulated Carrier              */  \
  0,                            /* Channel                          */  \
},

#else //#if defined( EZRADIO_PLUGIN_UNMOD_CARRIER )
#define EZRADIODRV_UNMOD_CARRIER_PLUGIN_INIT_DEFAULT
#endif  //#if defined( EZRADIO_PLUGIN_UNMOD_CARRIER )

/** @} (end addtogroup Unmod_Carrier_Plugin) */
/** @} (end addtogroup Plugin_System) */
/** @} (end addtogroup EZRADIODRV) */
/** @} (end addtogroup emdrv) */

#ifdef __cplusplus
}
#endif

#endif /* EZRADIO_UNMOD_CARRIER_PLUGIN_H_ */
