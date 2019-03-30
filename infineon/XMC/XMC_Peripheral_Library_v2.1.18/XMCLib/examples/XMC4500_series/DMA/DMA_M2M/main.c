/*
 * Copyright (C) 2014 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

/**
 * @file
 * @date 22 July, 2015
 * @version 1.0.2
 *
 * @brief DMA demo example
 *
 * Transfer data from flash to SRAM
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 * Version 1.0.1 Enable interrupts <br>
 * Version 1.0.2 Included modifications to avoid Keil MDK warning <br>
 *
 */


#include <string.h>
#include <xmc_dma.h>
#include <xmc_common.h>
#define DATA_LENGTH 10

uint32_t source_data[DATA_LENGTH] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
uint32_t destination_data[DATA_LENGTH];
XMC_DMA_CH_CONFIG_t dma_ch_config;

void GPDMA0_0_IRQHandler(void)
{
  XMC_DMA_CH_ClearEventStatus(XMC_DMA0, 0, XMC_DMA_CH_EVENT_TRANSFER_COMPLETE);

  if (memcmp(source_data, destination_data, DATA_LENGTH) != 0)
  {
	  /* Error array are not equal */
	  __BKPT(0);
  }
}

int main(void)
{
  XMC_STRUCT_INIT(dma_ch_config);	
	
  XMC_DMA_CH_CONFIG_t dma_ch_config =
  {
    .block_size = DATA_LENGTH,
    .src_addr = (uint32_t)&source_data[0],
    .dst_addr = (uint32_t)&destination_data[0],
    .src_transfer_width = XMC_DMA_CH_TRANSFER_WIDTH_32,
    .dst_transfer_width = XMC_DMA_CH_TRANSFER_WIDTH_32,
    .src_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_INCREMENT,
    .dst_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_INCREMENT,
    .src_burst_length = XMC_DMA_CH_BURST_LENGTH_8,
    .dst_burst_length = XMC_DMA_CH_BURST_LENGTH_8,
    .transfer_flow = XMC_DMA_CH_TRANSFER_FLOW_M2M_DMA,
    .transfer_type = XMC_DMA_CH_TRANSFER_TYPE_SINGLE_BLOCK,
    .enable_interrupt = true
  };
	
  XMC_DMA_Init(XMC_DMA0);
  XMC_DMA_CH_Init(XMC_DMA0, 0, &dma_ch_config);
  XMC_DMA_CH_EnableEvent(XMC_DMA0, 0, XMC_DMA_CH_EVENT_TRANSFER_COMPLETE);

  /* Enable DMA event handling */
  NVIC_SetPriority(GPDMA0_0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 63, 0));
  NVIC_EnableIRQ(GPDMA0_0_IRQn);

  /* Start DMA transfer */
  XMC_DMA_CH_Enable(XMC_DMA0, 0);

  while(1)
  {
    /* Infinite loop */
  }
}
