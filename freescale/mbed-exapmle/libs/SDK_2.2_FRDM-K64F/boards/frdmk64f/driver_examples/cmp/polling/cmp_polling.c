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

#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_cmp.h"

#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define LED_INIT() LED_RED_INIT(LOGIC_LED_OFF)
#define LED_ON() LED_RED_ON()
#define LED_OFF() LED_RED_OFF()

#define DEMO_CMP_BASE CMP0
#define DEMO_CMP_USER_CHANNEL 1U /* PTC7, CMP0_IN1, J1-13 on FRDM-K64F. */
#define DEMO_CMP_DAC_CHANNEL 7U

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
 * @brief Main function
 */
int main(void)
{
    cmp_config_t mCmpConfigStruct;
    cmp_dac_config_t mCmpDacConfigStruct;

    /* Initialize hardware */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\nCMP polling Example.\r\n");

    /*
     * mCmpConfigStruct.enableCmp = true;
     * mCmpConfigStruct.hysteresisMode = kCMP_HysteresisLevel0;
     * mCmpConfigStruct.enableHighSpeed = false;
     * mCmpConfigStruct.enableInvertOutput = false;
     * mCmpConfigStruct.useUnfilteredOutput = false;
     * mCmpConfigStruct.enablePinOut = false;
     * mCmpConfigStruct.enableTriggerMode = false;
     */
    CMP_GetDefaultConfig(&mCmpConfigStruct);
    /* Init the CMP comparator. */
    CMP_Init(DEMO_CMP_BASE, &mCmpConfigStruct);

    /* Configure the DAC channel. */
    mCmpDacConfigStruct.referenceVoltageSource = kCMP_VrefSourceVin2; /* VCC. */
    mCmpDacConfigStruct.DACValue = 32U;                               /* Half voltage of logic high level. */
    CMP_SetDACConfig(DEMO_CMP_BASE, &mCmpDacConfigStruct);
    CMP_SetInputChannels(DEMO_CMP_BASE, DEMO_CMP_USER_CHANNEL, DEMO_CMP_DAC_CHANNEL);

    /* Configure the LED. */
    LED_INIT();

    while (1)
    {
        if (kCMP_OutputAssertEventFlag == (kCMP_OutputAssertEventFlag & CMP_GetStatusFlags(DEMO_CMP_BASE)))
        {
            LED_ON(); /* Turn on led. */
        }
        else
        {
            LED_OFF(); /* Turn off led. */
        }
    }
}
