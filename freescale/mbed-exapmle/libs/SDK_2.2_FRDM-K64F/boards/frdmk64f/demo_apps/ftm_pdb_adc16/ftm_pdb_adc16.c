/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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
#include "fsl_pdb.h"
#include "fsl_adc16.h"
#include "fsl_ftm.h"

#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_ADC_BASE0 ADC0
#define DEMO_ADC_BASE1 ADC1
#define DEMO_ADC_USER_CHANNEL1 1U
#define DEMO_ADC_USER_CHANNEL26 26U /* Temperature sensor. */
#define DEMO_ADC_USER_CHANNEL7 7U
#define DEMO_ADC_CHANNEL_GROUP0 0U
#define DEMO_ADC_CHANNEL_GROUP1 1U
#define DEMO_ADC_CLOCK_SOURCE kADC16_ClockSourceAlt2
#define DEMO_ADC_CLOCK_DIVIDER kADC16_ClockDivider4

#define DEMO_ADC_IRQ_ID0 ADC0_IRQn
#define DEMO_ADC_IRQ_ID1 ADC1_IRQn
#define DEMO_ADC_IRQ_HANDLER0 ADC0_IRQHandler
#define DEMO_ADC_IRQ_HANDLER1 ADC1_IRQHandler

#define DEMO_PDB_BASE PDB0
#define DEMO_PDB_TRIGGER_CHANNEL0 0U
#define DEMO_PDB_TRIGGER_CHANNEL1 1U
#define DEMO_PDB_PRETRIGGER_CHANNEL0_MASK 1U
#define DEMO_PDB_PRETRIGGER_CHANNEL1_MASK 2U

#define DEMO_FTM_BASE FTM0

#define FTM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_CoreSysClk)
#define PDB_MODUL_VALUE 2000U
#define PDB_INT_VALUE 1500U
#define PRETRIGGER_DELAY_VALUE 500U
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Initialize the ADC16, PDB, FTM
 */
static void DEMO_Init_ADC(void);
static void DEMO_Init_PDB(void);
static void DEMO_Init_FTM(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

volatile uint16_t u16Result0A[256] = {0};
volatile uint16_t u16Result0B[256] = {0};
volatile uint16_t u16Result1A[256] = {0};
volatile uint16_t u16Result1B[256] = {0};
volatile uint16_t u16CycleTimes = 0;

/*******************************************************************************
 * Code
 ******************************************************************************/
void static DEMO_Init_ADC(void)
{
    adc16_config_t adc16ConfigStruct;
    adc16_channel_config_t adc16ChannelConfigStruct;

    /*
     * adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceVref;
     * adc16ConfigStruct.clockSource = kADC16_ClockSourceAsynchronousClock;
     * adc16ConfigStruct.enableAsynchronousClock = true;
     * adc16ConfigStruct.clockDivider = kADC16_ClockDivider8;
     * adc16ConfigStruct.resolution = kADC16_ResolutionSE12Bit;
     * adc16ConfigStruct.longSampleMode = kADC16_LongSampleDisabled;
     * adc16ConfigStruct.enableHighSpeed = false;
     * adc16ConfigStruct.enableLowPower = false;
     * adc16ConfigStruct.enableContinuousConversion = false;
     */
    ADC16_GetDefaultConfig(&adc16ConfigStruct);
    /* Config ADC */
    adc16ConfigStruct.clockSource = DEMO_ADC_CLOCK_SOURCE;
    adc16ConfigStruct.clockDivider = DEMO_ADC_CLOCK_DIVIDER;
    adc16ConfigStruct.enableAsynchronousClock = false;
    adc16ConfigStruct.enableHighSpeed = true;

    /* Init ADC */
    ADC16_Init(DEMO_ADC_BASE0, &adc16ConfigStruct);
    ADC16_Init(DEMO_ADC_BASE1, &adc16ConfigStruct);

#if defined(FSL_FEATURE_ADC16_HAS_DMA) && FSL_FEATURE_ADC16_HAS_DMA
    ADC16_EnableDMA(DEMO_ADC_BASE0, false);
#endif /* FSL_FEATURE_ADC16_HAS_DMA */

    /* Conversion trigger selection.*/
    ADC16_EnableHardwareTrigger(DEMO_ADC_BASE0, true);
    ADC16_EnableHardwareTrigger(DEMO_ADC_BASE1, true);

#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
    adc16ChannelConfigStruct.enableDifferentialConversion = false;
#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */

    adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = true;
    adc16ChannelConfigStruct.channelNumber = DEMO_ADC_USER_CHANNEL1;
    ADC16_SetChannelConfig(DEMO_ADC_BASE0, DEMO_ADC_CHANNEL_GROUP0, &adc16ChannelConfigStruct);

    adc16ChannelConfigStruct.channelNumber = DEMO_ADC_USER_CHANNEL26;
    ADC16_SetChannelConfig(DEMO_ADC_BASE0, DEMO_ADC_CHANNEL_GROUP1, &adc16ChannelConfigStruct);

    adc16ChannelConfigStruct.channelNumber = DEMO_ADC_USER_CHANNEL1;
    ADC16_SetChannelConfig(DEMO_ADC_BASE1, DEMO_ADC_CHANNEL_GROUP0, &adc16ChannelConfigStruct);

    adc16ChannelConfigStruct.channelNumber = DEMO_ADC_USER_CHANNEL7;
    ADC16_SetChannelConfig(DEMO_ADC_BASE1, DEMO_ADC_CHANNEL_GROUP1, &adc16ChannelConfigStruct);
}

static void DEMO_Init_PDB(void)
{
    pdb_config_t pdbConfigStruct;
    pdb_adc_pretrigger_config_t pdbAdcPreTriggerConfigStruct;

    /*
     * pdbConfigStruct.loadValueMode = kPDB_LoadValueImmediately;
     * pdbConfigStruct.prescalerDivider = kPDB_PrescalerDivider1;
     * pdbConfigStruct.dividerMultiplicationFactor = kPDB_DividerMultiplicationFactor1;
     * pdbConfigStruct.triggerInputSource = kPDB_TriggerSoftware;
     * pdbConfigStruct.enableContinuousMode = false;
     */
    PDB_GetDefaultConfig(&pdbConfigStruct);

    /* Config PDB */
    pdbConfigStruct.triggerInputSource = kPDB_TriggerInput8;

    PDB_Init(DEMO_PDB_BASE, &pdbConfigStruct);
    PDB_EnableDMA(DEMO_PDB_BASE, false);
    PDB_DisableInterrupts(DEMO_PDB_BASE, kPDB_SequenceErrorInterruptEnable);

    /* Configure the delay interrupt. */
    PDB_SetModulusValue(DEMO_PDB_BASE, PDB_MODUL_VALUE);
    PDB_SetCounterDelayValue(DEMO_PDB_BASE, PDB_INT_VALUE);

    /* Configure the ADC Pre-Trigger. */
    PDB_SetADCPreTriggerDelayValue(DEMO_PDB_BASE, DEMO_PDB_TRIGGER_CHANNEL0, DEMO_PDB_PRETRIGGER_CHANNEL0_MASK,
                                   PRETRIGGER_DELAY_VALUE);

    pdbAdcPreTriggerConfigStruct.enableBackToBackOperationMask = DEMO_PDB_PRETRIGGER_CHANNEL1_MASK;
    pdbAdcPreTriggerConfigStruct.enablePreTriggerMask =
        (DEMO_PDB_PRETRIGGER_CHANNEL0_MASK | DEMO_PDB_PRETRIGGER_CHANNEL1_MASK);
    pdbAdcPreTriggerConfigStruct.enableOutputMask =
        (DEMO_PDB_PRETRIGGER_CHANNEL0_MASK | DEMO_PDB_PRETRIGGER_CHANNEL1_MASK);
    PDB_SetADCPreTriggerConfig(DEMO_PDB_BASE, DEMO_PDB_TRIGGER_CHANNEL0, &pdbAdcPreTriggerConfigStruct);

    pdbAdcPreTriggerConfigStruct.enableBackToBackOperationMask =
        (DEMO_PDB_PRETRIGGER_CHANNEL0_MASK | DEMO_PDB_PRETRIGGER_CHANNEL1_MASK);
    ;
    PDB_SetADCPreTriggerConfig(DEMO_PDB_BASE, DEMO_PDB_TRIGGER_CHANNEL1, &pdbAdcPreTriggerConfigStruct);

    /* Load PDB registe */
    PDB_DoLoadValues(DEMO_PDB_BASE);
}

static void DEMO_Init_FTM(void)
{
    ftm_config_t ftmConfigStruct;
    ftm_chnl_pwm_signal_param_t ftmParam;

    /*
     * ftmConfigStruct.prescale = kFTM_Prescale_Divide_1;
     * ftmConfigStruct.bdmMode = kFTM_BdmMode_0;
     * ftmConfigStruct.pwmSyncMode = kFTM_SoftwareTrigger;
     * ftmConfigStruct.reloadPoints = 0;
     * ftmConfigStruct.faultMode = kFTM_Fault_Disable;
     * ftmConfigStruct.faultFilterValue = 0;
     * ftmConfigStruct.deadTimePrescale = kFTM_Deadtime_Prescale_1;
     * ftmConfigStruct.deadTimeValue = 0;
     * ftmConfigStruct.extTriggers = 0;
     * ftmConfigStruct.chnlInitState = 0;
     * ftmConfigStruct.chnlPolarity = 0;
     * ftmConfigStruct.useGlobalTimeBase = false;
     */
    FTM_GetDefaultConfig(&ftmConfigStruct);
    ftmConfigStruct.deadTimePrescale = kFTM_Deadtime_Prescale_4;
    ftmConfigStruct.deadTimeValue = 19U;
    FTM_Init(DEMO_FTM_BASE, &ftmConfigStruct);

    /* FTM config */
    ftmParam.chnlNumber = kFTM_Chnl_0;
    ftmParam.firstEdgeDelayPercent = 20U;
    ftmParam.dutyCyclePercent = 50U;
    ftmParam.level = kFTM_LowTrue;

    /* Configure FTM0 channel ouput period is 16KHz complementary waveform (channel n and n+1) */
    FTM_SetupPwm(DEMO_FTM_BASE, &ftmParam, 1U, kFTM_CombinedPwm, 16000U, FTM_SOURCE_CLOCK);

    FTM_StartTimer(DEMO_FTM_BASE, kFTM_SystemClock);
    FTM_SetWriteProtection(DEMO_FTM_BASE, false);

    /* Configure combine mode */
    /* Enable complementary mode in a channel pair */
    FTM_SetComplementaryEnable(DEMO_FTM_BASE, (ftm_chnl_t)0U, true);

    /* Enable deadtime insertion in a channel pair. */
    FTM_SetDeadTimeEnable(DEMO_FTM_BASE, (ftm_chnl_t)0U, true);

    FTM_SetSoftwareTrigger(DEMO_FTM_BASE, true);

    /* Enable channel select in PWMLOAD register & Load FTM registers like MOD, CnV and INT */
    DEMO_FTM_BASE->PWMLOAD = 0x202;
}

/*!
 * @brief ISR for ADC16 interrupt function
 */
void DEMO_ADC_IRQ_HANDLER0(void)
{
    /* Read to clear COCO flag. */
    if (ADC16_GetChannelStatusFlags(DEMO_ADC_BASE0, DEMO_ADC_CHANNEL_GROUP0))
    {
        u16Result0A[u16CycleTimes] = ADC16_GetChannelConversionValue(DEMO_ADC_BASE0, DEMO_ADC_CHANNEL_GROUP0);
    }

    if (ADC16_GetChannelStatusFlags(DEMO_ADC_BASE0, DEMO_ADC_CHANNEL_GROUP1))
    {
        u16Result0B[u16CycleTimes] = ADC16_GetChannelConversionValue(DEMO_ADC_BASE0, DEMO_ADC_CHANNEL_GROUP1);
    }
}

void DEMO_ADC_IRQ_HANDLER1(void)
{
    /* Read to clear COCO flag. */
    if (ADC16_GetChannelStatusFlags(DEMO_ADC_BASE1, DEMO_ADC_CHANNEL_GROUP0))
    {
        u16Result1A[u16CycleTimes] = ADC16_GetChannelConversionValue(DEMO_ADC_BASE1, DEMO_ADC_CHANNEL_GROUP0);
    }

    if (ADC16_GetChannelStatusFlags(DEMO_ADC_BASE1, DEMO_ADC_CHANNEL_GROUP1))
    {
        u16Result1B[u16CycleTimes] = ADC16_GetChannelConversionValue(DEMO_ADC_BASE1, DEMO_ADC_CHANNEL_GROUP1);

        if (u16CycleTimes < 256)
        {
            u16CycleTimes++;
        }
        else
        {
            u16CycleTimes = 0;
        }
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t i = 0U;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    PRINTF("\r\nRun pdb trig adc with flextimer demo.\r\n");
    EnableIRQ(DEMO_ADC_IRQ_ID0);
    EnableIRQ(DEMO_ADC_IRQ_ID1);

    DEMO_Init_ADC();
    DEMO_Init_PDB();
    DEMO_Init_FTM();

    while (1)
    {
        PRINTF("\r\nInput any character to start demo.\r\n");
        GETCHAR();
        /* Reset counter */
        DEMO_FTM_BASE->CNT &= ~FTM_CNT_COUNT_MASK;

        /* Enable FTM0 channel0 trigger as external trigger */
        DEMO_FTM_BASE->EXTTRIG |= FTM_EXTTRIG_CH0TRIG_MASK;

        while (u16CycleTimes < 256)
        {
        }
        /* Disable FTM0 channel0 trigger and Clear FTM0 channel external trigger flag, it will not trig PDB */
        if (FTM_GetStatusFlags(DEMO_FTM_BASE) & kFTM_ChnlTriggerFlag)
        {
            DEMO_FTM_BASE->EXTTRIG &= ~FTM_EXTTRIG_CH0TRIG_MASK;
            FTM_ClearStatusFlags(DEMO_FTM_BASE, kFTM_ChnlTriggerFlag);
        }

        for (i = 0; i < 256; i++)
        {
            PRINTF("\r\n%d, %d, %d, %d\r\n", u16Result0A[i], u16Result0B[i], u16Result1A[i], u16Result1B[i]);
        }

        for (i = 0; i < 256; i++)
        {
            u16Result0A[i] = 0;
            u16Result0B[i] = 0;
            u16Result1A[i] = 0;
            u16Result1B[i] = 0;
        }

        u16CycleTimes = 0;
    }
}
