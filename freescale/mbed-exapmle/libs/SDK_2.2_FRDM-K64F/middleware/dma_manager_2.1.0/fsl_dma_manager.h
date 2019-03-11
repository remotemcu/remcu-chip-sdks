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

#ifndef _FSL_DMAMGR_H_
#define _FSL_DMAMGR_H_

#include "fsl_common.h"
#include "fsl_dmamux.h"
#if defined(FSL_FEATURE_SOC_DMA_COUNT) && FSL_FEATURE_SOC_DMA_COUNT > 0U
#include "fsl_dma.h"
#endif /* FSL_FEATURE_SOC_DMA_COUNT */
#if defined(FSL_FEATURE_SOC_EDMA_COUNT) && FSL_FEATURE_SOC_EDMA_COUNT > 0U
#include "fsl_edma.h"
#endif /* FSL_FEATURE_SOC_EDMA_COUNT */

/*!
 * @addtogroup dmamgr
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Dynamic channel allocation mechanism. */
#define DMAMGR_DYNAMIC_ALLOCATE 0xFFU

/*! @brief DMA manager status. */
enum _dma_manager_status
{
    kStatus_DMAMGR_ChannelOccupied = MAKE_STATUS(kStatusGroup_DMAMGR, 0), /*!< Channel has been occupied */
    kStatus_DMAMGR_ChannelNotUsed = MAKE_STATUS(kStatusGroup_DMAMGR, 1),  /*!< Channel has not been used */
    kStatus_DMAMGR_NoFreeChannel = MAKE_STATUS(kStatusGroup_DMAMGR, 2),   /*!< All channels have been occupied */
};

/*!
 * @brief dmamanager handle typedef.
 *
 * @note The contents of this structure are private and subject to change.
 *
 * This dma manager handle structure is used to store the parameters transfered by users.And users shall not free the
 * memory before calling DMAMGR_Deinit, also shall not modify the contents of the memory.
 */
typedef struct _dmamanager_handle
{
    void *dma_base;               /*!< Peripheral DMA instance. */
                                  //    DMAMUX_Type *dmamux_base;     /*!< Peripheral DMAMUX instance. */
    uint32_t channelNum;          /*!< Channel numbers for the DMA instance which need to be managed by dma manager. */
    uint32_t startChannel;        /*!< The start channel that can be managed by dma manager,users need to transfer it
                                     with a certain number or NULL. */
    bool s_DMAMGR_Channels[64];   /*!< The s_DMAMGR_Channels is used to store dma manager state. */
    uint32_t DmamuxInstanceStart; /*!< The DmamuxInstance is used to calculate the DMAMUX Instance according to the DMA
                                     Instance. */
    uint32_t multiple; /*!< The multiple is used to calculate the multiple between DMAMUX count and DMA count. */
} dmamanager_handle_t;
/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name DMAMGR Initialization and De-initialization
 * @{
 */

/*!
 * @brief Initializes the DMA manager.
 *
 * This function initializes the DMA manager, ungates the DMAMUX clocks, and
 * initializes the eDMA or DMA peripherals.
 * @param dmamanager_handle DMA manager handle pointer, this structure is maintained by dma manager internal,users only
 need to transfer the structure to the
                            function. And users shall not free the memory before calling DMAMGR_Deinit, also shall not
 modify the contents of the memory.
 * @param dma_base Peripheral DMA instance base pointer.
 * @param dmamux_base Peripheral DMAMUX instance base pointer.
 * @param channelNum Channel numbers for the DMA instance which need to be managed by dma manager.
 * @param startChannel The start channel that can be managed by dma manager.
 */
void DMAMGR_Init(dmamanager_handle_t *dmamanager_handle,
                 DMA_Type *dma_base,
                 uint32_t channelNum,
                 uint32_t startChannel);

/*!
 * @brief Deinitializes the DMA manager.
 *
 * This function deinitializes the DMA manager, disables the DMAMUX channels,
 * gates the DMAMUX clocks, and deinitializes the eDMA or DMA peripherals.
 *
 * @param dmamanager_handle DMA manager handle pointer, this structure is maintained by dma manager internal,users only
 need to transfer the structure to the
                            function. And users shall not free the memory before calling DMAMGR_Deinit, also shall not
 modify the contents of the memory.
 */
void DMAMGR_Deinit(dmamanager_handle_t *dmamanager_handle);

/* @} */
/*!
 * @name DMAMGR Operation
 * @{
 */

/*!
 * @brief Requests a DMA channel.
 *
 * This function requests a DMA channel which is not occupied. The two channels to allocate the mechanism are dynamic
 * and static channels. For the dynamic allocation mechanism (channe = DMAMGR_DYNAMIC_ALLOCATE), DMAMGR  allocates a DMA
 * channel according to the given request source and startChannel and then configures it. For static allocation
 mechanism, DMAMGR
 * configures the given channel according to the given request source and channel number.
 *
 * @param dmamanager_handle DMA manager handle pointer, this structure is maintained by dma manager internal,users only
 need to transfer the structure to the
                            function. And users shall not free the memory before calling DMAMGR_Deinit, also shall not
 modify the contents of the memory.
 * @param requestSource DMA channel request source number. See the soc.h, see the enum dma_request_source_t
 * @param channel The channel number users want to occupy. If using the dynamic channel allocate mechanism, set the
 *                       channel equal to DMAMGR_DYNAMIC_ALLOCATE.
 * @param handle DMA or eDMA handle pointer.
 * @retval kStatus_Success In a dynamic/static channel allocation mechanism, allocate the DMAMUX channel successfully.
 * @retval kStatus_DMAMGR_NoFreeChannel In a dynamic channel allocation mechanism, all DMAMUX channels are occupied.
 * @retval kStatus_DMAMGR_ChannelOccupied In a static channel allocation mechanism, the given channel is occupied.
 */
status_t DMAMGR_RequestChannel(dmamanager_handle_t *dmamanager_handle,
                               uint32_t requestSource,
                               uint32_t channel,
                               void *handle);

/*!
 * @brief Releases a DMA channel.
 *
 * This function releases an occupied DMA channel.
 *
 * @param dmamanager_handle DMA manager handle pointer, this structure is maintained by dma manager internal,users only
 need to transfer the structure to the
                            function. And users shall not free the memory before calling DMAMGR_Deinit, also shall not
 modify the contents of the memory.
 * @param handle DMA or eDMA handle pointer.
 * @retval kStatus_Success Releases the given channel successfully.
 * @retval kStatus_DMAMGR_ChannelNotUsed The given channel to be released had not been used before.
 */
status_t DMAMGR_ReleaseChannel(dmamanager_handle_t *dmamanager_handle, void *handle);

/*!
 * @brief Get a DMA channel status.
 *
 * This function get a DMA channel status. Return 0 indicates the channel has not been used, return 1 indicates the
 channel has been occupied.
 *
 * @param dmamanager_handle DMA manager handle pointer, this structure is maintained by dma manager internal,users only
 need to transfer the structure to the
                            function. And users shall not free the memory before calling DMAMGR_Deinit, also shall not
 modify the contents of the memory.
 * @param channel The channel number that users want get its status.
*/
bool DMAMGR_IsChannelOccupied(dmamanager_handle_t *dmamanager_handle, uint32_t channel);

/* @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/* @} */

#endif /* _FSL_DMAMGR_H_ */
