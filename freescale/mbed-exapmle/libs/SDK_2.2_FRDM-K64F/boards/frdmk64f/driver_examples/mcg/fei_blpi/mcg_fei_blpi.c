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

#include "board.h"
#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_gpio.h"

#include "pin_mux.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define LED_INIT() LED_RED_INIT(LOGIC_LED_ON)
#define LED_TOGGLE() LED_RED_TOGGLE()
#define CORE_CLK_FREQ CLOCK_GetFreq(kCLOCK_CoreSysClk)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Delay function used to wait FLL stable.
 */
static void APP_FllStableDelay(void)
{
    volatile uint32_t i = 30000U;
    while (i--)
    {
        __NOP();
    }
}

/*!
 * @brief Example function to show how to change from FEI to BLPI mode.
 * MCG transition: FEI -> FBI -> BLPI
 */
void APP_ChangeFeiToBlpiExample(void)
{
    /* Change FEI -> FBI
    * It's transitional mode, don't need to wait for FLL stable,
    * so NULL is passed as variable here.
    */
    CLOCK_SetFbiMode(kMCG_Dmx32Default, kMCG_DrsLow, NULL);
    assert(kMCG_ModeFBI == CLOCK_GetMode());

    /* Change FBI -> BLPI */
    CLOCK_SetLowPowerEnable(true);
    assert(kMCG_ModeBLPI == CLOCK_GetMode());
}

/*!
 * @brief Example function to show how to change from BLPI to FEI mode.
 * MCG transition: BLPI -> FBI -> FEI
 */
void APP_ChangeBlpiToFeiExample(void)
{
    /* Change BLPI -> FBI */
    CLOCK_SetLowPowerEnable(false);
    assert(kMCG_ModeFBI == CLOCK_GetMode());

    /* Change FBI -> FEI */
    CLOCK_SetFeiMode(kMCG_Dmx32Default, kMCG_DrsLow, APP_FllStableDelay);
    assert(kMCG_ModeFEI == CLOCK_GetMode());
}

/*!
 * @brief Main function
 */
int main(void)
{
    volatile uint32_t i;
    uint32_t sysFreq;

    BOARD_InitPins();

    /* Set clock divider to safe value to switch mode */
    CLOCK_SetSimSafeDivs();

#if (defined(FSL_FEATURE_MCG_RESET_IS_BLPI) && FSL_FEATURE_MCG_RESET_IS_BLPI)
    /* Change clock BLPI -> FBI -> FEI */
    APP_ChangeBlpiToFeiExample();
    /* Change clock FEI -> FBI -> BLPI */
    APP_ChangeFeiToBlpiExample();
#else
    /* Change clock FEI -> FBI -> BLPI */
    APP_ChangeFeiToBlpiExample();
    /* Change clock BLPI -> FBI -> FEI */
    APP_ChangeBlpiToFeiExample();
#endif

    /* Get System clock to blink a LED */
    sysFreq = CORE_CLK_FREQ / 20U;
    /* Enable a LED */
    LED_INIT();
    /* Blink a LED */
    while (1)
    {
        for (i = 0; i < sysFreq; i++)
        {
            __NOP();
        }
        LED_TOGGLE();
    }
}
