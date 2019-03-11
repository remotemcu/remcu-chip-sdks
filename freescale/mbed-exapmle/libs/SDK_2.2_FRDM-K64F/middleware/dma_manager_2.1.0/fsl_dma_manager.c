/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
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

#include "fsl_dma_manager.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Array to map DMA instance number to base pointer. */
static DMA_Type *const s_dmaBases[] = DMA_BASE_PTRS;

/*! @brief Array to map DMAMUX instance number to base pointer. */
static DMAMUX_Type *const s_dmamuxBases[] = DMAMUX_BASE_PTRS;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

static uint32_t DMA_GetInstance(DMA_Type *base)
{
    uint32_t DmaInstance;
#if defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT > 0U
    uint32_t count = FSL_FEATURE_SOC_DMA_COUNT;
#endif /* FSL_FEATURE_SOC_DMA_COUNT */

#if defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT > 0U
    uint32_t count = FSL_FEATURE_SOC_EDMA_COUNT;
#endif /* FSL_FEATURE_SOC_DMA_COUNT */

    /* Find the instance index from base address mappings. */
    for (DmaInstance = 0; DmaInstance < count; DmaInstance++)
    {
        if (s_dmaBases[DmaInstance] == base)
        {
            break;
        }
    }

    assert(DmaInstance < count);
    return DmaInstance;
}

void DMAMGR_Init(dmamanager_handle_t *dmamanager_handle, DMA_Type *dma_base, uint32_t channelNum, uint32_t startChannel)
{
    assert(dmamanager_handle != NULL);
    assert(dma_base != NULL);

    uint32_t i = 0U;
    dmamanager_handle->startChannel = startChannel;
    dmamanager_handle->channelNum = channelNum;
    dmamanager_handle->dma_base = dma_base;
    memset(dmamanager_handle->s_DMAMGR_Channels, false, sizeof(dmamanager_handle->s_DMAMGR_Channels));

/* Initialize DMAMUX. */
#if defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT > 0U
    dmamanager_handle->multiple = FSL_FEATURE_SOC_DMAMUX_COUNT / FSL_FEATURE_SOC_DMA_COUNT;
#endif /* FSL_FEATURE_SOC_DMA_COUNT */

#if defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT > 0U
    dmamanager_handle->multiple = FSL_FEATURE_SOC_DMAMUX_COUNT / FSL_FEATURE_SOC_EDMA_COUNT;
#endif /* FSL_FEATURE_SOC_DMA_COUNT */
    if (dmamanager_handle->multiple < 1U)
    {
        dmamanager_handle->multiple = 1U;
    }
    dmamanager_handle->DmamuxInstanceStart = dmamanager_handle->multiple * DMA_GetInstance(dmamanager_handle->dma_base);
    for (i = dmamanager_handle->DmamuxInstanceStart;
         i < dmamanager_handle->DmamuxInstanceStart + dmamanager_handle->multiple; i++)
    {
        DMAMUX_Init(s_dmamuxBases[i]);
    }

/* Initialize DMA or EDMA */
#if defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT > 0U
    DMA_Init(dmamanager_handle->dma_base);
#endif /* FSL_FEATURE_SOC_DMA_COUNT */

#if defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT > 0U
    edma_config_t config;

    EDMA_GetDefaultConfig(&config);
    EDMA_Init(dmamanager_handle->dma_base, &config);
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */
}

void DMAMGR_Deinit(dmamanager_handle_t *dmamanager_handle)
{
    uint32_t i;
    uint32_t j;
    for (i = dmamanager_handle->DmamuxInstanceStart;
         i < dmamanager_handle->DmamuxInstanceStart + dmamanager_handle->multiple; i++)
    {
        for (j = 0; j < dmamanager_handle->channelNum; j++)
        {
            DMAMUX_DisableChannel(s_dmamuxBases[i], j);
        }
        DMAMUX_Deinit(s_dmamuxBases[i]);
    }

/* Deinitialize DMA or EDMA */
#if defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT > 0U
    DMA_Deinit(dmamanager_handle->dma_base);
#endif /* FSL_FEATURE_SOC_DMA_COUNT */

#if defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT > 0U
    EDMA_Deinit(dmamanager_handle->dma_base);
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */
}

status_t DMAMGR_RequestChannel(dmamanager_handle_t *dmamanager_handle,
                               uint32_t requestSource,
                               uint32_t channel,
                               void *handle)
{
    assert(handle != NULL);
    assert(dmamanager_handle != NULL);

    status_t retval;
    uint32_t primask;
    uint32_t DmamuxInstance;

    /* Dynamic channel allocate mechanism */
    if (channel == DMAMGR_DYNAMIC_ALLOCATE)
    {
#if defined(FSL_FEATURE_EDMA_CHANNEL_GROUP_COUNT) && FSL_FEATURE_EDMA_CHANNEL_GROUP_COUNT > 1U
        /*
            For chip like MKV56/MKV58, it has only 1 DMAMUX(32 channels), but 2 source groups(16 channels per
           group).
        */
        uint32_t dmamux_channelNum = dmamanager_handle->channelNum / FSL_FEATURE_EDMA_CHANNEL_GROUP_COUNT;
        dmamanager_handle->channelNum = dmamux_channelNum;
#else
        uint32_t dmamux_channelNum = 0U;
#endif /* FSL_FEATURE_EDMA_CHANNEL_GROUP_COUNT */

        uint32_t i = 0U;
        uint32_t j = 0U;
        uint32_t startChannel = 0U;
        uint32_t map = ((uint32_t)requestSource) >> 8U;
        bool channel_found = false;

        while (map != 0U)
        {
            if (map & (1U << i))
            {
                map &= ~(0x1U << i);
                startChannel = dmamanager_handle->startChannel + i * dmamux_channelNum;
                for (j = startChannel; j < dmamanager_handle->channelNum + startChannel; j++)
                {
                    primask = DisableGlobalIRQ();
                    if (dmamanager_handle->s_DMAMGR_Channels[j] == false)
                    {
                        dmamanager_handle->s_DMAMGR_Channels[j] = true;
                        EnableGlobalIRQ(primask);
                        /* Configure DMAMUX channel */
                        DmamuxInstance =
                            dmamanager_handle->DmamuxInstanceStart +
                            j * dmamanager_handle->multiple / (dmamanager_handle->channelNum + startChannel);
                        DMAMUX_SetSource(
                            s_dmamuxBases[DmamuxInstance],
                            j % ((dmamanager_handle->channelNum + startChannel) / dmamanager_handle->multiple),
                            (uint8_t)requestSource);
                        DMAMUX_EnableChannel(
                            s_dmamuxBases[DmamuxInstance],
                            j % ((dmamanager_handle->channelNum + startChannel) / dmamanager_handle->multiple));
/* Creat DMA or EDMA handle */
#if defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT > 0U
                        DMA_CreateHandle((dma_handle_t *)handle, dmamanager_handle->dma_base, j);
#endif /* FSL_FEATURE_SOC_DMA_COUNT */

#if defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT > 0U
                        EDMA_CreateHandle((edma_handle_t *)handle, dmamanager_handle->dma_base, j);
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

                        channel_found = true;
                        break;
                    }
                    else /* Channel has been occupied, so continue to search. */
                    {
                        EnableGlobalIRQ(primask);
                        continue;
                    }
                }
            }
            else
            {
                i++;
            }
        }
        if (channel_found)
        {
            retval = kStatus_Success;
        }
        else
        {
            retval = kStatus_DMAMGR_NoFreeChannel;
        }
    }
    else /* Static channel allocate mechanism */
    {
        primask = DisableGlobalIRQ();
        if ((dmamanager_handle->s_DMAMGR_Channels[channel] != 0U))
        {
            EnableGlobalIRQ(primask);
            retval = kStatus_DMAMGR_ChannelOccupied;
        }
        else
        {
            dmamanager_handle->s_DMAMGR_Channels[channel] = 1U;
            EnableGlobalIRQ(primask);
            /* Configure DMAMUX channel */
            DmamuxInstance = dmamanager_handle->DmamuxInstanceStart +
                             channel * dmamanager_handle->multiple / dmamanager_handle->channelNum;
            DMAMUX_SetSource(s_dmamuxBases[DmamuxInstance],
                             channel % (dmamanager_handle->channelNum / dmamanager_handle->multiple),
                             (uint32_t)requestSource);
            DMAMUX_EnableChannel(s_dmamuxBases[DmamuxInstance],
                                 channel % (dmamanager_handle->channelNum / dmamanager_handle->multiple));
/* Creat DMA or EDMA handle */
#if defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT > 0U
            DMA_CreateHandle((dma_handle_t *)handle, dmamanager_handle->dma_base, channel);
#endif /* FSL_FEATURE_SOC_DMA_COUNT */

#if defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT > 0U
            EDMA_CreateHandle((edma_handle_t *)handle, dmamanager_handle->dma_base, channel);
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

            retval = kStatus_Success;
        }
    }

    return retval;
}

status_t DMAMGR_ReleaseChannel(dmamanager_handle_t *dmamanager_handle, void *handle)
{
    assert(handle != NULL);
    uint32_t DmamuxInstance;

#if defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT > 0U
    uint32_t channel = ((dma_handle_t *)handle)->channel;
#endif /* FSL_FEATURE_SOC_DMA_COUNT */

#if defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT > 0U
    uint32_t channel = ((edma_handle_t *)handle)->channel;
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

    /* Check if channel is used */
    if ((dmamanager_handle->s_DMAMGR_Channels[channel] == 0U))
    {
        return kStatus_DMAMGR_ChannelNotUsed;
    }
    dmamanager_handle->s_DMAMGR_Channels[channel] = 0;
    DmamuxInstance =
        dmamanager_handle->DmamuxInstanceStart + channel * dmamanager_handle->multiple / dmamanager_handle->channelNum;
    DMAMUX_DisableChannel(s_dmamuxBases[DmamuxInstance],
                          channel % (dmamanager_handle->channelNum / dmamanager_handle->multiple));

    return kStatus_Success;
}

bool DMAMGR_IsChannelOccupied(dmamanager_handle_t *dmamanager_handle, uint32_t channel)
{
    return dmamanager_handle->s_DMAMGR_Channels[channel];
}
