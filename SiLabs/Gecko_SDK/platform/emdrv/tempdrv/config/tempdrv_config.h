/***************************************************************************//**
 * @file tempdrv_config.h
 * @brief TEMPDRV configuration file.
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
#ifndef __SILICON_LABS_TEMPDRV_CONFIG_H__
#define __SILICON_LABS_TEMPDRV_CONFIG_H__

/***************************************************************************//**
 * @addtogroup emdrv
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup TEMPDRV
 * @{
 ******************************************************************************/

// Callback table depth (for high and low callbacks each)
#ifndef TEMPDRV_CUSTOM_CALLBACK_DEPTH
#define TEMPDRV_CUSTOM_CALLBACK_DEPTH 5
#endif

// Allow temperature sensor to wake the device up from EM4
#ifndef TEMPDRV_EM4WAKEUP
#define TEMPDRV_EM4WAKEUP false
#endif

// Allow TEMPDRV to define the EMU_IRQ_Handler. Enable if EMU_IRQ_Handler is
// defined elsewhere.
#ifndef EMU_CUSTOM_IRQ_HANDLER
#define EMU_CUSTOM_IRQ_HANDLER false
#endif

/** @} (end addtogroup TEMPDRV) */
/** @} (end addtogroup emdrv) */

#endif /* __SILICON_LABS_TEMPDRV_CONFIG_H__ */
