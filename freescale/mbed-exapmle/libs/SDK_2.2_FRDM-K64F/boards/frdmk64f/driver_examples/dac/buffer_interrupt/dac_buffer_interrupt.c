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
#include "fsl_dac.h"

#include "fsl_common.h"
#include "clock_config.h"
#include "pin_mux.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_DAC_BASEADDR DAC0
#define DEMO_DAC_IRQ_ID DAC0_IRQn
#define DEMO_DAC_IRQ_HANDLER_FUNC DAC0_IRQHandler

#define DEMO_DAC_USED_BUFFER_SIZE DAC_DATL_COUNT

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined(FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION) && FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION
volatile bool g_DacBufferWatermarkInterruptFlag;
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION */
volatile bool g_DacBufferReadPointerTopPositionInterruptFlag;
volatile bool g_DacBufferReadPointerBottomPositionInterruptFlag;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief IRQ function for DAC buffer interrupt
 */
void DEMO_DAC_IRQ_HANDLER_FUNC(void)
{
    uint32_t flags = DAC_GetBufferStatusFlags(DEMO_DAC_BASEADDR);

#if defined(FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION) && FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION
    if (kDAC_BufferWatermarkFlag == (kDAC_BufferWatermarkFlag & flags))
    {
        g_DacBufferWatermarkInterruptFlag = true;
    }
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION */
    if (kDAC_BufferReadPointerTopPositionFlag == (kDAC_BufferReadPointerTopPositionFlag & flags))
    {
        g_DacBufferReadPointerTopPositionInterruptFlag = true;
    }
    if (kDAC_BufferReadPointerBottomPositionFlag == (kDAC_BufferReadPointerBottomPositionFlag & flags))
    {
        g_DacBufferReadPointerBottomPositionInterruptFlag = true;
    }
    DAC_ClearBufferStatusFlags(DEMO_DAC_BASEADDR, flags); /* Clear flags. */
}

/*!
 * @brief Main function
 */
int main(void)
{
    dac_config_t dacConfigStruct;
    dac_buffer_config_t dacBufferConfigStruct;
    uint8_t index;
    uint16_t dacValue;
    uint32_t mask;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    EnableIRQ(DEMO_DAC_IRQ_ID);

    PRINTF("\r\nDAC buffer interrupt Example.\r\n");

    /* Configure the DAC. */
    /*
     * dacConfigStruct.referenceVoltageSource = kDAC_ReferenceVoltageSourceVref2;
     * dacConfigStruct.enableLowPowerMode = false;
     */
    DAC_GetDefaultConfig(&dacConfigStruct);
    DAC_Init(DEMO_DAC_BASEADDR, &dacConfigStruct);
    DAC_Enable(DEMO_DAC_BASEADDR, true); /* Enable output. */

    /* Configure the DAC buffer. */
    DAC_GetDefaultBufferConfig(&dacBufferConfigStruct);
    DAC_SetBufferConfig(DEMO_DAC_BASEADDR, &dacBufferConfigStruct);
    DAC_SetBufferReadPointer(DEMO_DAC_BASEADDR, 0U); /* Make sure the read pointer to the start. */
    dacValue = 0U;
    for (index = 0U; index < DEMO_DAC_USED_BUFFER_SIZE; index++)
    {
        DAC_SetBufferValue(DEMO_DAC_BASEADDR, index, dacValue);
        dacValue += (0xFFFU / DEMO_DAC_USED_BUFFER_SIZE);
    }
/* Clear flags. */
#if defined(FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION) && FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION
    g_DacBufferWatermarkInterruptFlag = false;
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION */
    g_DacBufferReadPointerTopPositionInterruptFlag = false;
    g_DacBufferReadPointerBottomPositionInterruptFlag = false;

    /* Enable interrupts. */
    mask = 0U;
#if defined(FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION) && FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION
    mask |= kDAC_BufferWatermarkInterruptEnable;
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION */
    mask |= kDAC_BufferReadPointerTopInterruptEnable | kDAC_BufferReadPointerBottomInterruptEnable;
    DAC_EnableBuffer(DEMO_DAC_BASEADDR, true);
    DAC_EnableBufferInterrupts(DEMO_DAC_BASEADDR, mask);

    PRINTF("\r\nDAC Buffer Information\r\n");
    PRINTF("\t  Buffer index max  : %d\r\n", dacBufferConfigStruct.upperLimit);
#if defined(FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION) && FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION
    PRINTF("\t  Buffer watermark  : %d\r\n",
           dacBufferConfigStruct.upperLimit - (uint8_t)(dacBufferConfigStruct.watermark) - 1U);
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION */
    PRINTF("Press any key in terminal to trigger the buffer ...\r\n");
    index = 0U;
    while (1)
    {
        if (0U == index)
        {
            PRINTF("\r\n");
        }
        PRINTF("Buffer Index %2d: ", index);
#if defined(FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION) && FSL_FEATURE_DAC_HAS_WATERMARK_SELECTION
        if (g_DacBufferWatermarkInterruptFlag)
        {
            PRINTF("WatermarkEvent \t");
            g_DacBufferWatermarkInterruptFlag = false;
        }
#endif /* FSL_FEATURE_DAC_HAS_WATERMARK_DETECTION */
        if (g_DacBufferReadPointerTopPositionInterruptFlag)
        {
            PRINTF("ReadPointerTopPositionEvent \t");
            g_DacBufferReadPointerTopPositionInterruptFlag = false;
        }
        if (g_DacBufferReadPointerBottomPositionInterruptFlag)
        {
            PRINTF("ReadPointerBottomPositionEvent \t");
            g_DacBufferReadPointerBottomPositionInterruptFlag = false;
        }
        PRINTF("\r\n");

        /* Trigger the buffer and move the pointer. */
        GETCHAR();
        DAC_DoSoftwareTriggerBuffer(DEMO_DAC_BASEADDR);
        index++;
        if (index >= DEMO_DAC_USED_BUFFER_SIZE)
        {
            index = 0U;
        }
    }
}
