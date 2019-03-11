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

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "fsl_debug_console.h"
#include "board.h"

#include "fsl_wdog.h"
#include "fsl_rcm.h"

#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define WDOG_WCT_INSTRUCITON_COUNT (256U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
* Variables
******************************************************************************/
static WDOG_Type *wdog_base = WDOG;
static RCM_Type *rcm_base = RCM;

/*******************************************************************************
 * Code
 ******************************************************************************/

static void WaitWctClose(WDOG_Type *base)
{
    /* Accessing register by bus clock */
    for (uint32_t i = 0; i < WDOG_WCT_INSTRUCITON_COUNT; i++)
    {
        (void)base->RSTCNT;
    }
}

/*!
 * @brief Gets the Watchdog timer output.
 *
 * @param base WDOG peripheral base address
 * @return Current value of watchdog timer counter.
 */
static inline uint32_t GetTimerOutputValue(WDOG_Type *base)
{
    return (uint32_t)((((uint32_t)base->TMROUTH) << 16U) | (base->TMROUTL));
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint16_t wdog_reset_count = 0;
    wdog_test_config_t test_config;
    wdog_config_t config;

    /* Init hardware*/
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /*If not wdog reset*/
    if (!(RCM_GetPreviousResetSources(rcm_base) & kRCM_SourceWdog))
    {
        WDOG_ClearResetCount(wdog_base);
    }
    wdog_reset_count = WDOG_GetResetCount(wdog_base);
    if (wdog_reset_count == 0)
    {
        /*quick test*/
        test_config.testMode = kWDOG_QuickTest;
        test_config.timeoutValue = 0xfffffu;
        /*Not necessary to configure tested byte for quick test, just to get rid of using uninitialized value check*/
        test_config.testedByte = kWDOG_TestByte0;
        PRINTF("\r\n--- Quick test ---\r\n");
        WDOG_SetTestModeConfig(wdog_base, &test_config);
        WaitWctClose(wdog_base);

        /*wait for timeout reset*/
        while (1)
        {
        }
    }
    else if (wdog_reset_count == 1)
    {
        PRINTF("--- Quick test done ---\r\n");
    /*
     * config.enableWdog = true;
     * config.clockSource = kWDOG_LpoClockSource;
     * config.prescaler = kWDOG_ClockPrescalerDivide1;
     * config.enableUpdate = true;
     * config.enableInterrupt = false;
     * config.enableWindowMode = false;
     * config.windowValue = 0U;
     * config.timeoutValue = 0xFFFFU;
     */
        WDOG_GetDefaultConfig(&config);
        config.timeoutValue = 0x7ffU;
        /* wdog refresh test in none-window mode */
        PRINTF("\r\n--- None-window mode refresh test start---\r\n");
        WDOG_Init(wdog_base, &config);
        WaitWctClose(wdog_base);
        for (uint32_t i = 0; i < 10; i++)
        {
            WDOG_Refresh(wdog_base);
            PRINTF("--- Refresh wdog %d time ---\r\n", i + 1);

            while (GetTimerOutputValue(wdog_base) < (config.timeoutValue >> 3U))
            {
            }
        }
        /* wait for wdog timeout reset */
        while (1)
        {
        }
    }
    else if (wdog_reset_count == 2)
    {
        PRINTF("--- None-window mode refresh test done ---\r\n");
    /*
     * config.enableWdog = true;
     * config.clockSource = kWDOG_LpoClockSource;
     * config.prescaler = kWDOG_ClockPrescalerDivide1;
     * config.enableUpdate = true;
     * config.enableInterrupt = false;
     * config.enableWindowMode = false;
     * config.windowValue = 0U;
     * config.timeoutValue = 0xFFFFU;
     */
        WDOG_GetDefaultConfig(&config);
        config.timeoutValue = 0x7ffU;
        config.enableWindowMode = true;
        config.windowValue = 0x1ffU;
        /* wdog refresh test in window mode */
        PRINTF("\r\n--- Window mode refresh test start---\r\n");
        WDOG_Init(wdog_base, &config);
        WaitWctClose(wdog_base);

        while (GetTimerOutputValue(wdog_base) < config.windowValue)
        {
        }

        for (uint32_t i = 0; i < 10; i++)
        {
            WDOG_Refresh(wdog_base);
            PRINTF("--- Refresh wdog %d time ---\r\n", i + 1);
            while (GetTimerOutputValue(wdog_base) < config.windowValue)
            {
            }
        }
        WDOG_Refresh(wdog_base);
        /*Wait until refresh squence takes effect*/
        while (GetTimerOutputValue(wdog_base) >= config.windowValue)
        {
        }
        /*Refresh before window value to trigger reset*/
        WDOG_Refresh(wdog_base);
        /*If reset is not generated, you will see this log*/
        PRINTF("\r\n--- Reset failed---\r\n");
    }
    else
    {
        PRINTF("--- Window mode refresh test done---\r\n");
        PRINTF("\r\nEnd of Wdog example!\r\n");
    }
    while (1)
    {
    }
}
