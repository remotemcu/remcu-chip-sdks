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

#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_PDB_BASE PDB0
#define DEMO_PDB_IRQ_ID PDB0_IRQn
#define DEMO_PDB_IRQ_HANDLER PDB0_IRQHandler

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t g_PdbDelayInterruptCounter;
volatile bool g_PdbDelayInterruptFlag;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief ISR for PDB interrupt function
 */
void DEMO_PDB_IRQ_HANDLER(void)
{
    PDB_ClearStatusFlags(DEMO_PDB_BASE, kPDB_DelayEventFlag);
    g_PdbDelayInterruptCounter++;
    g_PdbDelayInterruptFlag = true;
}

/*!
 * @brief Main function
 */
int main(void)
{
    pdb_config_t pdbConfigStruct;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    EnableIRQ(DEMO_PDB_IRQ_ID);

    PRINTF("\r\nPDB Delay Interrupt Example.\r\n");

    /* Configure the PDB counter. */
    /*
     * pdbConfigStruct.loadValueMode = kPDB_LoadValueImmediately;
     * pdbConfigStruct.prescalerDivider = kPDB_PrescalerDivider1;
     * pdbConfigStruct.dividerMultiplicationFactor = kPDB_DividerMultiplicationFactor1;
     * pdbConfigStruct.triggerInputSource = kPDB_TriggerSoftware;
     * pdbConfigStruct.enableContinuousMode = false;
     */
    PDB_GetDefaultConfig(&pdbConfigStruct);
    PDB_Init(DEMO_PDB_BASE, &pdbConfigStruct);

    /* Configure the delay interrupt. */
    PDB_SetModulusValue(DEMO_PDB_BASE, 1000U);

    /* The available delay value is less than or equal to the modulus value. */
    PDB_SetCounterDelayValue(DEMO_PDB_BASE, 1000U);
    PDB_EnableInterrupts(DEMO_PDB_BASE, kPDB_DelayInterruptEnable);
    PDB_DoLoadValues(DEMO_PDB_BASE);

    while (1)
    {
        PRINTF("\r\nType any key into terminal to trigger the PDB counter ...\r\n");
        GETCHAR();

        g_PdbDelayInterruptFlag = false;
        PDB_DoSoftwareTrigger(DEMO_PDB_BASE);
        while (!g_PdbDelayInterruptFlag)
        {
        }

        PRINTF("PDB Delay Interrupt Counter: %d\r\n", g_PdbDelayInterruptCounter);
    }
}
