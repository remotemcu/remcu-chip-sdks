/***************************************************************************//**
 * @file ezradio_direct_receive_plugin.h
 * @brief EzRadio direct reception plug-in managed by the plug-in manager if enabled.
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


#ifndef EZRADIO_DIRECT_RECEIVE_PLUGIN_H_
#define EZRADIO_DIRECT_RECEIVE_PLUGIN_H_

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
 * @addtogroup Direct_Receive_Plugin
 * @brief Direct receive plugin, see @ref ezradiodrv_plugin
 *        for detailed documentation. 
 * @{
 ******************************************************************************/

#if defined( EZRADIO_PLUGIN_DIRECT_RECEIVE )

/// EzRadio direct rx plug-in instance initialization and handler structure.
typedef struct EZRADIODRV_DirectRxHandle
{
  uint8_t channel;      ///< Direct receive channel.
} EZRADIODRV_DirectRxHandle_t;

Ecode_t ezradioStartDirectReceive(EZRADIODRV_Handle_t radioHandle );
Ecode_t ezradioStopDirectReceive( void );

/// Configuration data for EzRadio direct rx plug-in.
#define EZRADIODRV_DIRECT_RECEIVE_PLUGIN_INIT_DEFAULT                         \
{                               /* PN9                              */  \
  0,                            /* Channel                          */  \
},

#else //#if defined( EZRADIO_PLUGIN_DIRECT_RECEIVE )
#define EZRADIODRV_DIRECT_RECEIVE_PLUGIN_INIT_DEFAULT
#endif  //#if defined( EZRADIO_PLUGIN_DIRECT_RECEIVE )

/** @} (end addtogroup Direct_Receive_Plugin) */
/** @} (end addtogroup Plugin_System) */
/** @} (end addtogroup EZRADIODRV) */
/** @} (end addtogroup emdrv) */

#ifdef __cplusplus
}
#endif

#endif /* EZRADIO_DIRECT_RECEIVE_PLUGIN_H_ */
