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
#include "fsl_ftm.h"

#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* The Flextimer instance/channel pair used for board */
#define BOARD_FTM_BASEADDR FTM0
/* FTM channel pair 0 works with FTM channels 0 and 1 */
#define BOARD_FTM_CHANNEL_PAIR kFTM_Chnl_0

/* Interrupt number and interrupt handler for the FTM instance used */
#define FTM_INTERRUPT_NUMBER FTM0_IRQn
#define FTM_LED_HANDLER FTM0_IRQHandler

/* Interrupt to enable and flag to read; depends on the FTM channel used */
#define FTM_CHANNEL_INTERRUPT_ENABLE kFTM_Chnl0InterruptEnable
#define FTM_CHANNEL_FLAG kFTM_Chnl0Flag

/* Get source clock for FTM driver */
#define FTM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief delay a while.
 */
void delay(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool ftmIsrFlag = false;
volatile bool brightnessUp = true; /* Indicate LED is brighter or dimmer */
volatile uint8_t updatedDutycycle = 10U;

/*******************************************************************************
 * Code
 ******************************************************************************/
void delay(void)
{
    volatile uint32_t i = 0U;
    for (i = 0U; i < 80000U; ++i)
    {
        __asm("NOP"); /* delay */
    }
}

void FTM_LED_HANDLER(void)
{
    ftmIsrFlag = true;

    if (brightnessUp)
    {
        /* Increase duty cycle until it reach limited value, don't want to go upto 100% duty cycle
         * as channel interrupt will not be set for 100%
         */
        if (++updatedDutycycle >= 99U)
        {
            updatedDutycycle = 99U;
            brightnessUp = false;
        }
    }
    else
    {
        /* Decrease duty cycle until it reach limited value */
        if (--updatedDutycycle == 1U)
        {
            brightnessUp = true;
        }
    }

    if ((FTM_GetStatusFlags(BOARD_FTM_BASEADDR) & FTM_CHANNEL_FLAG) == FTM_CHANNEL_FLAG)
    {
        /* Clear interrupt flag.*/
        FTM_ClearStatusFlags(BOARD_FTM_BASEADDR, FTM_CHANNEL_FLAG);
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    ftm_config_t ftmInfo;
    ftm_chnl_pwm_signal_param_t ftmParam;
    ftm_pwm_level_select_t pwmLevel = kFTM_LowTrue;

    /* Configure ftm params with frequency 24kHZ */
    ftmParam.chnlNumber = BOARD_FTM_CHANNEL_PAIR;
    ftmParam.level = pwmLevel;
    ftmParam.dutyCyclePercent = updatedDutycycle;
    ftmParam.firstEdgeDelayPercent = 0U;

    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Print a note to terminal */
    PRINTF("\r\nFTM example to output combined complementary PWM signals on two channels\r\n");
    PRINTF("\r\nYou will see a change in LED brightness if an LED is connected to the FTM pin");
    PRINTF("\r\nIf no LED is connected to the FTM pin, then probe the signal using an oscilloscope");

    FTM_GetDefaultConfig(&ftmInfo);
    /* Update deadTimePrescale for fast clock*/
    ftmInfo.deadTimePrescale = kFTM_Deadtime_Prescale_16;
    /* Need a deadtime value of about 650nsec */
    ftmInfo.deadTimeValue = ((uint64_t)FTM_SOURCE_CLOCK * 650) / 1000000000;

    /* Initialize FTM module */
    FTM_Init(BOARD_FTM_BASEADDR, &ftmInfo);

    /* Setup output of a combined PWM signal */
    FTM_SetupPwm(BOARD_FTM_BASEADDR, &ftmParam, 1U, kFTM_CombinedPwm, 24000U, FTM_SOURCE_CLOCK);

    /* Enable complementary output on the channel pair */
    FTM_SetComplementaryEnable(BOARD_FTM_BASEADDR, BOARD_FTM_CHANNEL_PAIR, true);

    /* Enable Deadtime insertion on the channel pair */
    FTM_SetDeadTimeEnable(BOARD_FTM_BASEADDR, BOARD_FTM_CHANNEL_PAIR, true);

    /* Enable interrupt flag on one of the channels from the pair */
    FTM_EnableInterrupts(BOARD_FTM_BASEADDR, FTM_CHANNEL_INTERRUPT_ENABLE);

    /* Enable at the NVIC */
    EnableIRQ(FTM_INTERRUPT_NUMBER);

    FTM_StartTimer(BOARD_FTM_BASEADDR, kFTM_SystemClock);

    while (1)
    {
        /* Use interrupt to update the PWM dutycycle */
        if (true == ftmIsrFlag)
        {
            /* Disable interrupt to retain current dutycycle for a few seconds */
            FTM_DisableInterrupts(BOARD_FTM_BASEADDR, FTM_CHANNEL_INTERRUPT_ENABLE);

            ftmIsrFlag = false;

            /* Disable output on each channel of the pair before updating the dutycycle */
            FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR, (ftm_chnl_t)(BOARD_FTM_CHANNEL_PAIR * 2), 0U);
            FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR, (ftm_chnl_t)((BOARD_FTM_CHANNEL_PAIR * 2) + 1), 0U);

            /* Update PWM duty cycle on the channel pair */
            FTM_UpdatePwmDutycycle(BOARD_FTM_BASEADDR, BOARD_FTM_CHANNEL_PAIR, kFTM_CombinedPwm, updatedDutycycle);

            /* Software trigger to update registers */
            FTM_SetSoftwareTrigger(BOARD_FTM_BASEADDR, true);

            /* Start output on each channel of the pair with updated dutycycle */
            FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR, (ftm_chnl_t)(BOARD_FTM_CHANNEL_PAIR * 2), pwmLevel);
            FTM_UpdateChnlEdgeLevelSelect(BOARD_FTM_BASEADDR, (ftm_chnl_t)((BOARD_FTM_CHANNEL_PAIR * 2) + 1), pwmLevel);

            /* Delay to view the updated PWM dutycycle */
            delay();

            /* Enable interrupt flag to update PWM dutycycle */
            FTM_EnableInterrupts(BOARD_FTM_BASEADDR, FTM_CHANNEL_INTERRUPT_ENABLE);
        }
    }
}
