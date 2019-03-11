/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _POWER_MANAGER_H_
#define _POWER_MANAGER_H_

#include "fsl_common.h"
#include "fsl_notifier.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Power mode definition used in application. */
typedef enum _app_power_mode
{
    kAPP_PowerModeMin = 'A' - 1,
    kAPP_PowerModeRun,   /*!< Run mode. All Kinetis chips. */
    kAPP_PowerModeWait,  /*!< Wait mode. All Kinetis chips. */
    kAPP_PowerModeStop,  /*!< Stop mode. All Kinetis chips. */
    kAPP_PowerModeVlpr,  /*!< Very low power run mode. All Kinetis chips. */
    kAPP_PowerModeVlpw,  /*!< Very low power wait mode. All Kinetis chips. */
    kAPP_PowerModeVlps,  /*!< Very low power stop mode. All Kinetis chips. */
    kAPP_PowerModeLls,   /*!< Low leakage stop mode. All Kinetis chips. */
    kAPP_PowerModeVlls0, /*!< Very low leakage stop 0 mode. Chip-specific. */
    kAPP_PowerModeVlls1, /*!< Very low leakage stop 1 mode. All Kinetis chips. */
    kAPP_PowerModeVlls2, /*!< Very low leakage stop 2 mode. All Kinetis chips. */
    kAPP_PowerModeVlls3, /*!< Very low leakage stop 3 mode. All Kinetis chips. */
    kAPP_PowerModeMax
} app_power_mode_t;

/*!
 * @brief Power mode user configuration structure.
 *
 * This structure defines Kinetis power mode with additional power options and specifies
 * transition to and out of this mode. Application may define multiple power modes and
 * switch between them.
 * List of power mode configuration structure members depends on power options available
 * for specific chip. Complete list contains:
 *  mode - Kinetis power mode. List of available modes is chip-specific. See power_manager_modes_t
 *   list of modes. This item is common for all Kinetis chips.
 *  enableLowPowerWakeUpOnInterrupt - When set to true, system exits to Run mode when any interrupt occurs while in
 *   Very low power run, Very low power wait or Very low power stop mode. This item is chip-specific.
 *  enablePowerOnResetDetection - When set to true, power on reset detection circuit is disabled in
 *   Very low leakage stop 0 mode. When set to false, circuit is enabled. This item is chip-specific.
 *  enableRAM2Powered - When set to true, RAM2 partition content is retained through Very low
 *   leakage stop 2 mode. When set to false, RAM2 partition power is disabled and memory content lost.
 *   This item is chip-specific.
 *  enableLowPowerOscillator - When set to true, the 1 kHz Low power oscillator is disabled in any
 *   Low leakage or Very low leakage stop mode. When set to false, oscillator is enabled in these modes.
 *   This item is chip-specific.
 */
typedef struct power_user_config
{
    app_power_mode_t mode; /*!< Power mode. */

    bool enableLowPowerWakeUpOnInterrupt; /*!< true - system exits to Run mode on interrupt from Very low power run,
                                             Very low power wait or Very low power stop mode, false - Wake-up on
                                             interrupt disabled for these modes. */

    bool enablePorDetectInVlls0; /*!< true - Power on reset detection circuit is enabled in Very low leakage stop 0
                                    mode, false - Power on reset detection circuit is disabled. */

} power_user_config_t;

/* callback data type which is used for power manager user callback */
typedef struct
{
    uint32_t beforeNotificationCounter; /*!< Callback before notification counter */
    uint32_t afterNotificationCounter;  /*!< Callback after notification counter */
    smc_power_state_t originPowerState; /*!< Origin power state before switch */
} user_callback_data_t;

typedef enum _app_wakeup_source
{
    kAPP_WakeupSourceLptmr, /*!< Wakeup by LPTMR.        */
    kAPP_WakeupSourcePin    /*!< Wakeup by external pin. */
} app_wakeup_source_t;

#endif /* _POWER_MANAGER_H_ */
