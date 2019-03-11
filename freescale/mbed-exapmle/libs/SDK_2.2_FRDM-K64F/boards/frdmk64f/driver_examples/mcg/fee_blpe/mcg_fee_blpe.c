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

#include "clock_config.h"
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
uint32_t g_frdivValue = 0U; /* The FRDIV value.*/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Get the available FRDIV. The FLL reference clock after FRDIV must
 * be in the range of 31250Hz to 39062.5Hz.
 */
bool APP_GetAvailableFrdiv(void)
{
    const uint32_t allowedRefFreq[][2U] =
    {
        /*  Min          Max   */
        {1000000U, 1250000U},
        {2000000U, 2500000U},
        {4000000U, 5000000U},
        {8000000U, 10000000U},
        {16000000U, 20000000U},
        {32000000U, 40000000U},
#if (defined(FSL_FEATURE_MCG_FRDIV_SUPPORT_1280) && FSL_FEATURE_MCG_FRDIV_SUPPORT_1280)
        {40000000U, 50000000U},
#endif /* FSL_FEATURE_MCG_FRDIV_SUPPORT_1280 */
#if (defined(FSL_FEATURE_MCG_FRDIV_SUPPORT_1536) && FSL_FEATURE_MCG_FRDIV_SUPPORT_1536)
        {48000000U, 60000000U}
#endif /* FSL_FEATURE_MCG_FRDIV_SUPPORT_1536 */
    };
    uint32_t size = (sizeof(allowedRefFreq) / sizeof(allowedRefFreq[0U]));

    if (32768U == g_xtal0Freq)
    {
        g_frdivValue = 0U;
        return true;
    }
    for (g_frdivValue = 0U; g_frdivValue < size; g_frdivValue++)
    {
        if ((g_xtal0Freq >= allowedRefFreq[g_frdivValue][0U]) && (g_xtal0Freq <= allowedRefFreq[g_frdivValue][1U]))
        {
            return true;
        }
    }
    return false;
}

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
 * @brief Example function to show how to change from FEE to BLPE mode.
 * MCG transition: FEE -> FBE -> BLPE
 */
void APP_ChangeFeeToBlpeExample(void)
{
    /* Change FEE -> FBE
    * It's transitional mode, don't need to wait for FLL stable,
    * so NULL is passed as variable here.
    */
    CLOCK_SetFbeMode(g_frdivValue, kMCG_Dmx32Default, kMCG_DrsLow, NULL);
    assert(kMCG_ModeFBE == CLOCK_GetMode());

    /* Change FBE -> BLPE */
    CLOCK_SetLowPowerEnable(true);
    assert(kMCG_ModeBLPE == CLOCK_GetMode());
}

/*!
 * @brief Example function to show how to change from BLPE to FEE mode.
 * MCG transition: BLPE -> FBE -> FEE
 */
void APP_ChangeBlpeToFeeExample(void)
{
    /* Change BLPE -> FBE */
    CLOCK_SetLowPowerEnable(false);
    assert(kMCG_ModeFBE == CLOCK_GetMode());

    /* Change FBE -> FEE */
    CLOCK_SetFeeMode(g_frdivValue, kMCG_Dmx32Default, kMCG_DrsLow, APP_FllStableDelay);
    assert(kMCG_ModeFEE == CLOCK_GetMode());
}

void APP_BootToFeeExample(void)
{
    /* Boot to Fee mode */
    CLOCK_BootToFeeMode(kMCG_OscselOsc, g_frdivValue, kMCG_Dmx32Default, kMCG_DrsLow, APP_FllStableDelay);
    assert(kMCG_ModeFEE == CLOCK_GetMode());
}

/*!
 * @brief Main function
 */
int main(void)
{
    volatile uint32_t i;
    uint32_t sysFreq;

    /* Structure for OSC configuration */
    osc_config_t oscConfig;
    oscConfig.freq = BOARD_XTAL0_CLK_HZ;
    oscConfig.capLoad = 0U;
    oscConfig.workMode = kOSC_ModeOscLowPower;
    oscConfig.oscerConfig.enableMode = kOSC_ErClkEnable;

    BOARD_InitPins();
    CLOCK_InitOsc0(&oscConfig);

    CLOCK_SetXtal0Freq(BOARD_XTAL0_CLK_HZ);

    /* Set clock divider to safe value to switch mode */
    CLOCK_SetSimSafeDivs();

    /* Calculate frdiv */
    if (!APP_GetAvailableFrdiv())
    {
        while (1)
        {
        }
    }
    /* Boot to Fee mode */
    APP_BootToFeeExample();

    /* Change clock FEE -> FBE -> BLPE */
    APP_ChangeFeeToBlpeExample();

    /* Change clock BLPE -> FBE -> FEE */
    APP_ChangeBlpeToFeeExample();
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
