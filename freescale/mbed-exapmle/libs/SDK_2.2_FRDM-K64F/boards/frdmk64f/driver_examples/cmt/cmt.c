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
#include "fsl_cmt.h"

#include "clock_config.h"
#include "pin_mux.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define BUS_CLK_FREQ CLOCK_GetFreq(kCLOCK_BusClk)

#define CMT_TEST_DATA_BITS 11       /*! The data test bit numbers. */
#define CMT_DATA_MODULATE_RATE 9600 /*! The data modulation transmit rate */
#define CMT_CG_FREQUENCY 40000      /*! The carrier generator frequency */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

volatile uint32_t g_CmtDataBitLen = 0;
volatile bool g_CmtFinish = false;
uint32_t g_CmtModDataOneMarkCount;
uint32_t g_CmtModDataOneSpaceCount;
uint32_t g_CmtModDataZeroMarkCount;
uint32_t g_CmtModDataZeroSpaceCount;
uint32_t data = 0x875631;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Prepare the CMT modulate configuration for
 * mode - TimeMode.
 * carrier generator - 50% duty cycle, CMT_CG_FREQUENCY.
 */
void CMT_PrepareModulateConfig(cmt_modulate_config_t *modulateConfig, uint32_t busClock)
{
    uint32_t cgHighCount;
    uint32_t cgLowCount;
    uint32_t cmTotalCount;
    uint32_t cmMarkCount;
    uint32_t cmSpaceCount;
    uint32_t frequency;

    /* Prepare the cmt modulate configuration. */
    frequency = CMT_GetCMTFrequency(CMT, busClock);

    /* Get the carrier generator for 50% duty cycle. */
    cgHighCount = (frequency / CMT_CG_FREQUENCY) / 2;
    cgLowCount = cgHighCount;
    /* Get the carrier modulator total counts.
    Set the modulate mark space count for the first transmitted data. */
    cmTotalCount = (frequency / 8) / CMT_DATA_MODULATE_RATE;
    /* LSB. */
    if (data & 0x1)
    {
        /* Data bit "1" - set the space time to min. */
        cmMarkCount = cmTotalCount - 1;
        cmSpaceCount = 0;
    }
    else
    {
        /* Data bit "0" - set the mark time to min. */
        cmMarkCount = 0;
        cmSpaceCount = cmTotalCount - 1;
    }
    modulateConfig->highCount1 = cgHighCount;
    modulateConfig->lowCount1 = cgLowCount;
    modulateConfig->markCount = cmMarkCount;
    modulateConfig->spaceCount = cmSpaceCount;

    /* CMT carrier modulate mark and space set for bit 1 and bit 0. */
    g_CmtModDataOneMarkCount = cmTotalCount - 1;
    g_CmtModDataOneSpaceCount = 0;
    g_CmtModDataZeroMarkCount = 0;
    g_CmtModDataZeroSpaceCount = cmTotalCount - 1;

    /* The initialized mark/space count is for the first Data. */
    g_CmtDataBitLen = 1;
}

/*!
 * @brief System default IRQ handler defined in startup code.
 *
 */
void CMT_IRQHandler(void)
{
    if (CMT_GetStatusFlags(CMT))
    {
        if (g_CmtDataBitLen <= CMT_TEST_DATA_BITS)
        {
            if (g_CmtDataBitLen == CMT_TEST_DATA_BITS)
            {
                /* Stop CG if the required data has been transmitted. */
                CMT_SetMode(CMT, kCMT_DirectIROCtl, NULL);

                CMT_DisableInterrupts(CMT, kCMT_EndOfCycleInterruptEnable);

                g_CmtFinish = true;
            }

            /* LSB. */
            if (data & ((uint32_t)0x01 << g_CmtDataBitLen))
            {
                CMT_SetModulateMarkSpace(CMT, g_CmtModDataOneMarkCount, g_CmtModDataOneSpaceCount);
            }
            else
            {
                CMT_SetModulateMarkSpace(CMT, g_CmtModDataZeroMarkCount, g_CmtModDataZeroSpaceCount);
            }
            g_CmtDataBitLen++;
        }
    }
}

int main(void)
{
    uint32_t busClock;
    cmt_config_t config;
    cmt_modulate_config_t modulateConfig;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Configure CMT_IRO Drive strength. */
    SIM->SOPT2 |= SIM_SOPT2_PTD7PAD_MASK;

    PRINTF("\r\nCMT Example Start.\r\n");

    busClock = BUS_CLK_FREQ;

    /*
     * config.isInterruptEnabled = false;
     * config.isIroEnabled = true;
     * config.iroPolarity = kCMT_IROActiveHigh;
     * config.divider = kCMT_SecondClkDiv1;
     */
    CMT_GetDefaultConfig(&config);
    /* Interrupt is enabled to change the modulate mark and space count. */
    config.isInterruptEnabled = true;
    CMT_Init(CMT, &config, busClock);

    /* Prepare the modulate configuration. */
    CMT_PrepareModulateConfig(&modulateConfig, busClock);

    /* Set the time mode. */
    CMT_SetMode(CMT, kCMT_TimeMode, &modulateConfig);

    while (1)
    {
        if (g_CmtFinish)
        {
            PRINTF("\r\nCMT DATA Modulate Finished.\r\n");
            PRINTF("\r\nCMT Example End.\r\n");
            g_CmtFinish = false;
        }
    }
}
