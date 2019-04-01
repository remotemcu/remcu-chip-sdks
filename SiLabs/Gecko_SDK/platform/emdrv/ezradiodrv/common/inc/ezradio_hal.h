/**************************************************************************//**
 * @file ezradio_hal.h
 * @brief This file contains EZRadio HAL.
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

#ifndef _EZRADIO_HAL_H_
#define _EZRADIO_HAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ezradiodrv_config.h"

/***************************************************************************//**
 * @addtogroup emdrv
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup EZRADIODRV
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup HAL_Layer
 * @brief EzRadio HAL Layer
 * @{
 ******************************************************************************/

void    ezradio_hal_GpioInit( GPIOINT_IrqCallbackPtr_t ezradioIrqCallback, bool enablePTI );
void    ezradio_hal_SpiInit( void );

void    ezradio_hal_AssertShutdown  (void);
void    ezradio_hal_DeassertShutdown(void);
void    ezradio_hal_ClearNsel       (void);
void    ezradio_hal_SetNsel         (void);
uint8_t ezradio_hal_NirqLevel       (void);

#if defined(EZRADIODRV_DISABLE_PTI) && defined(EZRADIODRV_COMM_USE_GPIO1_FOR_CTS)
uint8_t ezradio_hal_Gpio1Level(void);
#endif

void    ezradio_hal_SpiWriteByte    (uint8_t byteToWrite);
void    ezradio_hal_SpiReadByte     (uint8_t* readByte);

void    ezradio_hal_SpiWriteData    (uint8_t byteCount, uint8_t* pData);
void    ezradio_hal_SpiReadData     (uint8_t byteCount, uint8_t* pData);

void ezradio_hal_SpiWriteReadData(uint8_t byteCount, uint8_t* txData, uint8_t* rxData);

/** @} (end addtogroup HAL_Layer) */
/** @} (end addtogroup EZRADIODRV) */
/** @} (end addtogroup emdrv) */

#ifdef __cplusplus
}
#endif

#endif //_EZRADIO_HAL_H_
