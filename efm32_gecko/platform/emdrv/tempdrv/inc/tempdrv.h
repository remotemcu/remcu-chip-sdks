/***************************************************************************//**
 * @file tempdrv.h
 * @brief TEMPDRV API definition.
 * @version 5.1.2
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
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

#ifndef __SILICON_LABS_TEMPDRV_H__
#define __SILICON_LABS_TEMPDRV_H__

#include "em_device.h"
#include "em_emu.h"
#include "ecode.h"
#include "tempdrv_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup emdrv
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup TEMPDRV 
 * @{
 ******************************************************************************/

#define ECODE_EMDRV_TEMPDRV_OK                (ECODE_OK)                              ///< Success return value.
#define ECODE_EMDRV_TEMPDRV_NO_INIT           (ECODE_EMDRV_TEMPDRV_BASE | 0x00000001) ///< Function requires prior initialization
#define ECODE_EMDRV_TEMPDRV_PARAM_ERROR       (ECODE_EMDRV_TEMPDRV_BASE | 0x00000002) ///< Illegal input parameter.
#define ECODE_EMDRV_TEMPDRV_BAD_LIMIT         (ECODE_EMDRV_TEMPDRV_BASE | 0x00000003) ///< Temperature mismatch with limit.
#define ECODE_EMDRV_TEMPDRV_NO_CALLBACK       (ECODE_EMDRV_TEMPDRV_BASE | 0x00000004) ///< Can't find callback.
#define ECODE_EMDRV_TEMPDRV_NO_SPACE          (ECODE_EMDRV_TEMPDRV_BASE | 0x00000005) ///< No more space to register
#define ECODE_EMDRV_TEMPDRV_TEMP_UNDER        (ECODE_EMDRV_TEMPDRV_BASE | 0x00000006) ///< Requested temperature below measurable range
#define ECODE_EMDRV_TEMPDRV_TEMP_OVER         (ECODE_EMDRV_TEMPDRV_BASE | 0x00000007) ///< Requested temperature above measurable range
#define ECODE_EMDRV_TEMPDRV_DUP_TEMP          (ECODE_EMDRV_TEMPDRV_BASE | 0x00000008) ///< Requested temperature is a duplicate

/**
 * Temperature limit. This is used in the TEMPDRV to specify the
 * direction of temperature change.
 */
typedef enum TEMPDRV_LimitType{
  TEMPDRV_LIMIT_LOW  = 0,   /**< Temperature low. Used to specify that a temperature is decreasing. */
  TEMPDRV_LIMIT_HIGH = 1    /**< Temperature high. Used to specify that a temperature is increasing. */
} TEMPDRV_LimitType_t;

/***************************************************************************//**
 * @brief
 *   TEMPDRV temperature limit callback function.
 *
 * @details
 *   This callback function is called from interrupt context. The callback
 *   function is called when the current temperature is equal to or exceeds
 *   one of the temperature limits that have been registered with the driver.
 *
 * @param[in] temp
 *   The current temperature at the time when the EMU temperature triggers an
 *   interrupt. Note that this is not necessarily the same temperature as was
 *   specified when registering a callback.
 *
 * @param[in] limit
 *   The upper/lower limit reached
 ******************************************************************************/
typedef void (*TEMPDRV_Callback_t)(int8_t temp, TEMPDRV_LimitType_t limit);

/***************************************************************************//**
 * @brief
 *  TEMPDRV IRQ Handler.
 *
 * @details
 *  This IRQ Handler should be called from within the EMU_IRQ_Handler in order
 *  to enable TEMPDRV callbacks. This is included by default with 
 *  EMU_CUSTOM_IRQ_HANDLER defined as false.
 ******************************************************************************/
void TEMPDRV_IRQHandler(void);

Ecode_t TEMPDRV_Init(void);

Ecode_t TEMPDRV_DeInit(void);

Ecode_t TEMPDRV_Enable(bool enable);

uint8_t TEMPDRV_GetActiveCallbacks(TEMPDRV_LimitType_t limit);

int8_t TEMPDRV_GetTemp(void);

Ecode_t TEMPDRV_RegisterCallback(int8_t temp, 
                                 TEMPDRV_LimitType_t limit, 
                                 TEMPDRV_Callback_t callback);

Ecode_t TEMPDRV_UnregisterCallback(TEMPDRV_Callback_t callback);

/** @} (end addtogroup TEMPDRV) */
/** @} (end addtogroup emdrv) */

#ifdef __cplusplus
}
#endif
#endif // __SILICON_LABS_TEMPDRV_H__
