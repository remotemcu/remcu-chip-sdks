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

#include "fsl_host.h"
#include "event.h"
#include "board.h"
#include "fsl_port.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static uint32_t g_sdhcAdmaTable[SDHC_ADMA_TABLE_WORDS];
/*! @brief Card detect flag. */
static volatile uint32_t g_sdInsertedFlag;
extern volatile uint32_t g_timeMilliseconds;
/*******************************************************************************
 * Code
 ******************************************************************************/

/* Delay some time united in milliseconds. */
static void Delay(uint32_t milliseconds)
{
    uint32_t startTime = g_timeMilliseconds;
    uint32_t periodTime = 0;
    while (periodTime < milliseconds)
    {
        periodTime = g_timeMilliseconds - startTime;
    }
}

static void DetectCardByGpio(void)
{
    if (GPIO_ReadPinInput(BOARD_SDHC_CD_GPIO_BASE, BOARD_SDHC_CD_GPIO_PIN))
#if defined BOARD_SDHC_CD_LOGIC_RISING
    {
        g_sdInsertedFlag = 1U;
    }
    else
    {
        g_sdInsertedFlag = 0U;
    }
#else
    {
        g_sdInsertedFlag = 0U;
    }
    else
    {
        g_sdInsertedFlag = 1U;
    }
#endif
}

/* Card detect. */
status_t CardInsertDetect(HOST_TYPE *hostBase)
{
    EVENT_InitTimer();

    if (!EVENT_Create(kEVENT_CardDetect))
    {
        return kStatus_Fail;
    }

    /* Card detection pin will generate interrupt on either eage */
    PORT_SetPinInterruptConfig(BOARD_SDHC_CD_PORT_BASE, BOARD_SDHC_CD_GPIO_PIN, kPORT_InterruptEitherEdge);
    /* Open card detection pin NVIC. */
    NVIC_EnableIRQ(BOARD_SDHC_CD_PORT_IRQ);

    DetectCardByGpio();

    if (!g_sdInsertedFlag)
    {
        /* Wait card inserted. */
        do
        {
            if (!EVENT_Wait(kEVENT_CardDetect, EVENT_TIMEOUT_CARD_DETECT))
            {
                return kStatus_Fail;
            }
        } while (!g_sdInsertedFlag);
    }

    EVENT_Delete(kEVENT_CardDetect);

    /* Delat some time to make card stable. */
    Delay(1000U);

    return kStatus_Success;
}

#if defined(__IAR_SYSTEMS_ICC__)
#pragma weak BOARD_SDHC_CD_PORT_IRQ_HANDLER = CardInsertDetectHandle
#endif

/* Card detect pin port interrupt handler. */
void CardInsertDetectHandle(void)
{
    if (PORT_GetPinsInterruptFlags(BOARD_SDHC_CD_PORT_BASE) == (1U << BOARD_SDHC_CD_GPIO_PIN))
    {
        DetectCardByGpio();
    }
    /* Clear interrupt flag.*/
    PORT_ClearPinsInterruptFlags(BOARD_SDHC_CD_PORT_BASE, ~0U);
    EVENT_Notify(kEVENT_CardDetect);
}

/* User defined transfer function. */
static status_t SDHC_TransferFunction(SDHC_Type *base, sdhc_transfer_t *content)
{
    status_t error = kStatus_Success;

    if (kStatus_Success != SDHC_TransferBlocking(base, g_sdhcAdmaTable, SDHC_ADMA_TABLE_WORDS, content))
    {
        error = kStatus_Fail;
    }

    return error;
}

status_t HOST_Init(void *host)
{
    sdhc_host_t *sdhcHost = (sdhc_host_t *)host;

    /* Initializes SDHC. */
    sdhcHost->config.cardDetectDat3 = false;
    sdhcHost->config.endianMode = SDHC_ENDIAN_MODE;
    sdhcHost->config.dmaMode = SDHC_DMA_MODE;
    sdhcHost->config.readWatermarkLevel = SDHC_READ_WATERMARK_LEVEL;
    sdhcHost->config.writeWatermarkLevel = SDHC_WRITE_WATERMARK_LEVEL;
    SDHC_Init(sdhcHost->base, &(sdhcHost->config));

    /* Define transfer function. */
    sdhcHost->transfer = SDHC_TransferFunction;

    return kStatus_Success;
}

void HOST_Deinit(void *host)
{
    sdhc_host_t *sdhcHost = (sdhc_host_t *)host;
    SDHC_Deinit(sdhcHost->base);
}
