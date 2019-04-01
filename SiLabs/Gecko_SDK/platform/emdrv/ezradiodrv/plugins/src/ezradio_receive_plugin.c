/***************************************************************************//**
 * @file ezradio_receive_plugin.c
 * @brief EzRadio receive plug-in managed by the plug-in manager if enabled.
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

#include <stddef.h>
#include "em_device.h"

#include "ezradio_cmd.h"
#include "ezradio_prop.h"
#include "ezradio_api_lib.h"
#include "ezradio_api_lib_add.h"
#include "ezradio_plugin_manager.h"
#include "ezradio_receive_plugin.h"

#if defined(EZRADIO_PLUGIN_RECEIVE)

/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN

#if defined( EZRADIO_PLUGIN_AUTO_ACK) && defined(EZRADIO_PLUGIN_TRANSMIT)
Ecode_t ezradioTransmitAutoAck(EZRADIODRV_Handle_t radioHandle);
#endif

/// @endcond

/**************************************************************************//**
 * @brief Set Radio to RX mode, packet length is always coming from
 *        the radio configuration.
 *
 *  @param radioHandle Handler of the EzRadio driver instance where packet
 *         buffer, callback and channel configurations are set.
 *
 *  @return
 *    @ref ECODE_EMDRV_EZRADIODRV_OK on success. On failure an appropriate EZRADIODRV
 *    @ref Ecode_t is returned.
 *****************************************************************************/
Ecode_t ezradioStartRx(EZRADIODRV_Handle_t radioHandle)
{
  /* Start Receiving packet, channel 0, START immediately, Packet n bytes long */
    ezradio_start_rx(radioHandle->packetRx.channel, 0u, 0u,
                  EZRADIO_CMD_START_RX_ARG_NEXT_STATE1_RXTIMEOUT_STATE_ENUM_NOCHANGE,
                  EZRADIO_CMD_START_RX_ARG_NEXT_STATE2_RXVALID_STATE_ENUM_READY,
                  EZRADIO_CMD_START_RX_ARG_NEXT_STATE3_RXINVALID_STATE_ENUM_RX );

    return ECODE_EMDRV_EZRADIODRV_OK;
}

/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN
//  Note: These are internal routines used by ezradio plugin manager.

/**************************************************************************//**
 * @brief EzRadio driver receive plug-in handler routine.
 *
 *  @param radioHandle EzRadio driver instance handler.
 *  @param radioReplyHandle EZRadio communication reply handler.
 *
 *  @return
 *    @ref ECODE_EMDRV_EZRADIODRV_OK on success. On failure an appropriate EZRADIODRV
 *    @ref Ecode_t is returned.
 *****************************************************************************/
Ecode_t ezradioHandleReceivePlugin( EZRADIODRV_Handle_t radioHandle, EZRADIODRV_ReplyHandle_t radioReplyHandle )
{
  if ( radioHandle == NULL )
  {
    return ECODE_EMDRV_EZRADIODRV_ILLEGAL_HANDLE;
  }

  /* Check if Pkt Rxd IT is received */
  if ( radioReplyHandle->GET_INT_STATUS.PH_PEND & EZRADIO_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_RX_PEND_BIT)
  {

    ezradio_cmd_reply_t radioReplyLocal;

    /* Check how many bytes we received. */
    ezradio_fifo_info(0u, &radioReplyLocal);

    /* Read out the RX FIFO content. */
    ezradio_read_rx_fifo(radioReplyLocal.FIFO_INFO.RX_FIFO_COUNT, radioHandle->packetRx.pktBuf);

    if ( radioHandle->packetRx.userCallback != NULL )
    {
      radioHandle->packetRx.userCallback( radioHandle, ECODE_EMDRV_EZRADIODRV_OK );
    }

    /* Note: Workaround for some FIFO issue. */
    ezradio_fifo_info(EZRADIO_CMD_FIFO_INFO_ARG_FIFO_RX_BIT, NULL);
    ezradioStartRx( radioHandle );

#if defined(EZRADIO_PLUGIN_AUTO_ACK) && defined(EZRADIO_PLUGIN_TRANSMIT)
    /* Transmit auto acknowledge packet if enabled */
    if (radioHandle->autoAck.ackMode  == ezradiodrvAutoAckSkipOne)
    {
      radioHandle->autoAck.ackMode  = ezradiodrvAutoAckImmediate;
    }
    else if (radioHandle->autoAck.ackMode  == ezradiodrvAutoAckImmediate)
    {
      ezradioTransmitAutoAck(radioHandle);
    }
#endif

    return ECODE_EMDRV_EZRADIODRV_OK;
  }

  /* Reset FIFO */
  ezradio_fifo_info(EZRADIO_CMD_FIFO_INFO_ARG_FIFO_RX_BIT, NULL);

  return ECODE_EMDRV_EZRADIODRV_OK;
}

/// @endcond

#endif //#if defined( EZRADIO_PLUGIN_RECEIVE )
