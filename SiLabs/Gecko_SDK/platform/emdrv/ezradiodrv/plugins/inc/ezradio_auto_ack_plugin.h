/***************************************************************************//**
 * @file ezradio_auto_ack_plugin.h
 * @brief EzRadio auto acknowledge plug-in managed by the plug-in manager if enabled.
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


#ifndef EZRADIO_AUTO_ACK_PLUGIN_H_
#define EZRADIO_AUTO_ACK_PLUGIN_H_

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
 * @addtogroup Auto_ACK_Plugin
 * @brief Auto acknowledge plugin, see @ref ezradiodrv_plugin
 *        for detailed documentation. 
 * @{
 ******************************************************************************/

#if defined(EZRADIO_PLUGIN_AUTO_ACK) && defined(EZRADIO_PLUGIN_TRANSMIT) && defined(EZRADIO_PLUGIN_RECEIVE)

/// EzRadio auto acknowledge mode
typedef enum EZRADIODRV_AutoAckMode
{
  ezradiodrvAutoAckDisabled                = 0,    ///< Auto acknowledge transmission disabled
  ezradiodrvAutoAckImmediate               = 1,    ///< Immediate acknowledge transmission
  ezradiodrvAutoAckSkipOne                 = 2,    ///< Acknowledge transmission is skipped for one cycle, eg. not to transmit ACK if ACK is received
} EZRADIODRV_AutoAckMode_t;

/// EzRadio packet mode for auto acknowledge plug-in
typedef enum EZRADIODRV_AutoAckPacketMode
{
  ezradiodrvAutoAckPktDefault           = 0,    ///< Auto acknowledge uses the same transmission configuration as the actual configuration
  ezradiodrvAutoAckPktCustom            = 1,    ///< Auto acknowledge uses custom packet configuration
} EZRADIODRV_AutoAckPacketMode_t;

/// EzRadio auto acknowledge plug-in instance initialization and handler structure.
typedef struct EZRADIODRV_AutoAckHandle
{
  EZRADIODRV_Callback_t   userCallback;         ///< User callback.
  EZRADIODRV_AutoAckMode_t ackMode;             ///< Auto ack mode.
  EZRADIODRV_AutoAckPacketMode_t pktMode;       ///< Packet mode for aut ack.
  EZRADIODRV_PacketLengthConfig_t lenConfig;    ///< Pakcet length config for auto ack.
  uint8_t * pktBuf;                             ///< Pointer to the buffer that holds the auto ack packet.
  uint16_t pktId;                               ///< Auto ack packet ID.
} EZRADIODRV_AutoAckHandle_t;


void ezradioEnableAutoAck(EZRADIODRV_AutoAckHandle_t *autoAckHandle);
void ezradioDisableAutoAck(EZRADIODRV_AutoAckHandle_t *autoAckHandle);
void ezradioSkipAutoAck(EZRADIODRV_AutoAckHandle_t *autoAckHandle);

/// Configuration data for EzRadio auto acknowledge plug-in.
#define EZRADIODRV_AUTO_ACK_PLUGIN_INIT_DEFAULT                         \
{                                    /* Auto acknowledge            */  \
  NULL,                              /* CallBack                    */  \
  ezradiodrvAutoAckDisabled,         /* Ack mode                    */  \
  ezradiodrvAutoAckPktDefault,       /* Ack packet mode             */  \
  {                                  /* Packet length config        */  \
    ezradiodrvTransmitLenghtDefault, /* Default length mode         */  \
    0,                               /* Packet length               */  \
    RADIO_CONFIG_DATA_FIELD_LENGTH,  /* Field lengths               */  \
  },                                                                    \
  NULL,                              /* Packet buffer               */  \
  0,                                 /* Packet ID                   */  \
},

#else //#if defined( EZRADIO_PLUGIN_AUTO_ACK ) && defined( EZRADIO_PLUGIN_TRANSMIT ) && defined( EZRADIO_PLUGIN_RECEIVE )

#define EZRADIODRV_AUTO_ACK_PLUGIN_INIT_DEFAULT

#endif //#if defined( EZRADIO_PLUGIN_AUTO_ACK ) && defined( EZRADIO_PLUGIN_TRANSMIT ) && defined( EZRADIO_PLUGIN_RECEIVE )

/** @} (end addtogroup Auto_ACK_Plugin) */
/** @} (end addtogroup Plugin_System) */
/** @} (end addtogroup EZRADIODRV) */
/** @} (end addtogroup emdrv) */

#ifdef __cplusplus
}
#endif

#endif /* EZRADIO_AUTO_ACK_PLUGIN_H_ */
