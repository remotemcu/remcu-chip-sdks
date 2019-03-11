/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
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
#include "fsl_ftm.h"
#include "fsl_pit.h"

#include "pin_mux.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define PIT_IRQ_HANDLER PIT0_IRQHandler
#define PIT_IRQ_ID PIT0_IRQn
/* Get source clock for PIT driver */
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

/* The Flextimer instance/channel used for board */
#define DEMO_FTM_BASEADDR FTM2

/* Get source clock for FTM driver */
#define FTM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)
#define DEMO_QUAD_DECODER_MODULO 2000U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t encoder_count = 0U;
volatile uint8_t dir_when_overflow = 0U;
volatile uint8_t counter_overflow_flag = 0U;
volatile uint8_t counter_overflow_count = 0U;
volatile uint32_t loop_counter = 0U;
volatile bool encoder_direction = false;
volatile bool gQdFreshReady = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
void PIT_Configuration(void)
{
    pit_config_t pitConfig;

    PIT_GetDefaultConfig(&pitConfig);
    /* Init pit module */
    PIT_Init(PIT, &pitConfig);

    /* Set timer period for channel 0 */
    PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(1000U, PIT_SOURCE_CLOCK)); /* Sample rate 1000hz */

    /* Enable timer interrupts for channel 0 */
    PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);

    /* Enable at the NVIC */
    EnableIRQ(PIT_IRQ_ID);
}

void PIT_IRQ_HANDLER(void)
{
    /* Clear pit interrupt flag */
    PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);

    loop_counter++;
    if (loop_counter > 1000U) /* 1s. */
    {
        loop_counter = 0U;
        gQdFreshReady = true;
        /* Read counter value */
        encoder_count = FTM_GetQuadDecoderCounterValue(DEMO_FTM_BASEADDR);
        /* Clear counter */
        FTM_ClearQuadDecoderCounterValue(DEMO_FTM_BASEADDR);
        /* Read direction */
        if (FTM_GetQuadDecoderFlags(DEMO_FTM_BASEADDR) & kFTM_QuadDecoderCountingIncreaseFlag)
        {
            encoder_direction = true;
        }
        else
        {
            encoder_direction = false;
        }
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    ftm_config_t ftmInfo;
    ftm_phase_params_t phaseParamsConfigStruct;

    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* PIT configuration */
    PIT_Configuration();

    /* Print a note to terminal */
    PRINTF("\r\nFTM quad decoder example\r\n");

    /* Initialize FTM module */
    FTM_GetDefaultConfig(&ftmInfo);
    ftmInfo.prescale = kFTM_Prescale_Divide_32;
    FTM_Init(DEMO_FTM_BASEADDR, &ftmInfo);

    /* Set the modulo values for Quad Decoder. */
    FTM_SetQuadDecoderModuloValue(DEMO_FTM_BASEADDR, 0U, DEMO_QUAD_DECODER_MODULO);

    /* Enable the Quad Decoder mode. */
    phaseParamsConfigStruct.enablePhaseFilter = true;
    phaseParamsConfigStruct.phaseFilterVal = 16;
    phaseParamsConfigStruct.phasePolarity = kFTM_QuadPhaseNormal;
    FTM_SetupQuadDecode(DEMO_FTM_BASEADDR, &phaseParamsConfigStruct, /* Phase A. */
                        &phaseParamsConfigStruct,                    /* Phase B. */
                        kFTM_QuadPhaseEncode);

    PIT_StartTimer(PIT, kPIT_Chnl_0);

    while (1)
    {
        /* Wati for the counter value is ready. */
        while (!gQdFreshReady)
        {
        }
        gQdFreshReady = false;

        /* Print the value. */
        if (encoder_direction)
        {
            PRINTF("Encoder direction: +\r\n");
        }
        else
        {
            PRINTF("Encoder direction: -\r\n");
        }

        PRINTF("Get current counter: %d\r\n", encoder_count);
    }
}
