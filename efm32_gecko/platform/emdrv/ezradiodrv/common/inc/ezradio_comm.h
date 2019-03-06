/**************************************************************************//**
 * @file ezradio_comm.h
 * @brief This file contains the EZRadio communication layer.
 * @version 5.1.2
 ******************************************************************************
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

#ifndef _EZRADIO_COMM_H_
#define _EZRADIO_COMM_H_

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
 * @addtogroup COMM_Layer
 * @brief EzRadio Communication Layer
 * @{
 ******************************************************************************/

#if defined(EZRADIODRV_SPI_4WIRE_MODE)
#define EZRADIODRV_MAX_CTS_BUFF_SIZE 257
#endif

extern uint8_t ezradio_comm_CtsWentHigh;

uint8_t ezradio_comm_GetResp(uint8_t byteCount, uint8_t* pData);
void ezradio_comm_SendCmd(uint8_t byteCount, uint8_t* pData);
void ezradio_comm_ReadData(uint8_t cmd, uint8_t pollCts, uint8_t byteCount, uint8_t* pData);
void ezradio_comm_WriteData(uint8_t cmd, uint8_t pollCts, uint8_t byteCount, uint8_t* pData);

uint8_t ezradio_comm_PollCTS(void);
uint8_t ezradio_comm_SendCmdGetResp(uint8_t cmdByteCount, uint8_t* pCmdData,
                                  uint8_t respByteCount, uint8_t* pRespData);
void ezradio_comm_ClearCTS(void);

/** @} (end addtogroup Comm_Layer) */
/** @} (end addtogroup EZRADIODRV) */
/** @} (end addtogroup emdrv) */

#ifdef __cplusplus
}
#endif

#endif //_EZRADIO_COMM_H_
