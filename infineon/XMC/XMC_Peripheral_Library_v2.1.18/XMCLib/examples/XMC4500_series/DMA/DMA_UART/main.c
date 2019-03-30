/**
 * @file main.c
 * @date 2015-07-20
 *
 * @cond
  *********************************************************************************************************************
 * XMClib v2.1.8 - DMA_UART XMC Peripheral Driver Library Example
 *
 * Copyright (c) 2015-2016, Infineon Technologies AG
 * All rights reserved.                        
 *                                             
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the 
 * following conditions are met:   
 *                                                                              
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following 
 * disclaimer.                        
 * 
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following 
 * disclaimer in the documentation and/or other materials provided with the distribution.                       
 * 
 * Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote 
 * products derived from this software without specific prior written permission.                                           
 *                                                                              
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE  
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR  
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                                                  
 *                                                                              
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes with 
 * Infineon Technologies AG dave@infineon.com).                                                          
 *********************************************************************************************************************
 *
 * Change History
 * --------------
 *
 * 2015-07-20:
 *     - Initial version
 *
 * @endcond
 *
 */

#include <xmc_gpio.h>
#include <xmc_uart.h>
#include <xmc_dma.h>

#define UART_TX P1_5
#define UART_RX P1_4

#define BUFFER_LENGTH 256

uint8_t buffer1[BUFFER_LENGTH];
uint8_t buffer2[BUFFER_LENGTH];

XMC_UART_CH_CONFIG_t uart_config =
{
  .data_bits = 8U,
  .stop_bits = 1U,
  .baudrate = 115200U
};

XMC_DMA_CH_CONFIG_t dma_ch_config =
{
  .dst_addr = (uint32_t)&(XMC_UART0_CH0->TBUF[0]),
  .src_transfer_width = XMC_DMA_CH_TRANSFER_WIDTH_8,
  .dst_transfer_width = XMC_DMA_CH_TRANSFER_WIDTH_8,
  .src_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_INCREMENT,
  .dst_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE,
  .src_burst_length = XMC_DMA_CH_BURST_LENGTH_8,
  .dst_burst_length = XMC_DMA_CH_BURST_LENGTH_1,
  .transfer_flow = XMC_DMA_CH_TRANSFER_FLOW_M2P_DMA,
  .transfer_type = XMC_DMA_CH_TRANSFER_TYPE_SINGLE_BLOCK,
  .dst_handshaking = XMC_DMA_CH_DST_HANDSHAKING_HARDWARE,
  .dst_peripheral_request = DMA0_PERIPHERAL_REQUEST_USIC0_SR0_0,
  .enable_interrupt = true
};

volatile bool transfer_done = false;

void GPDMA0_0_IRQHandler(void)
{
  transfer_done = true;
  XMC_DMA_CH_ClearEventStatus(XMC_DMA0, 2, XMC_DMA_CH_EVENT_BLOCK_TRANSFER_COMPLETE);
}

int main(void)
{
  uint32_t i;
  for (i = 0; i < BUFFER_LENGTH; ++i)
  {
    buffer1[i] = i;
    buffer2[i] = 255 - i;
  }

  XMC_DMA_Init(XMC_DMA0);
  XMC_DMA_CH_Init(XMC_DMA0, 2, &dma_ch_config);
  XMC_DMA_CH_EnableEvent(XMC_DMA0, 2, XMC_DMA_CH_EVENT_BLOCK_TRANSFER_COMPLETE);

  /* Enable DMA event handling */
  NVIC_SetPriority(GPDMA0_0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 63, 0));
  NVIC_EnableIRQ(GPDMA0_0_IRQn);

  XMC_UART_CH_Init(XMC_UART0_CH0, &uart_config);

  XMC_GPIO_SetMode(UART_RX, XMC_GPIO_MODE_INPUT_TRISTATE);
  XMC_UART_CH_SetInputSource(XMC_UART0_CH0, XMC_UART_CH_INPUT_RXD, USIC0_C0_DX0_P1_4);

  XMC_UART_CH_EnableEvent(XMC_UART0_CH0, XMC_UART_CH_EVENT_TRANSMIT_BUFFER);
  XMC_USIC_CH_SetInterruptNodePointer(XMC_UART0_CH0, XMC_USIC_CH_INTERRUPT_NODE_POINTER_TRANSMIT_BUFFER, 0);

  XMC_UART_CH_Start(XMC_UART0_CH0);
  XMC_USIC_CH_TriggerServiceRequest(XMC_UART0_CH0, 0); /* make DMA ready */

  XMC_GPIO_SetMode(UART_TX, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2);

  XMC_DMA_CH_SetBlockSize(XMC_DMA0, 2, BUFFER_LENGTH);
  XMC_DMA_CH_SetSourceAddress(XMC_DMA0, 2, (uint32_t)&buffer1[0]);
  XMC_DMA_CH_Enable(XMC_DMA0, 2);

  while (transfer_done == false);

  XMC_DMA_CH_SetBlockSize(XMC_DMA0, 2, BUFFER_LENGTH);
  XMC_DMA_CH_SetSourceAddress(XMC_DMA0, 2, (uint32_t)&buffer2[0]);
  XMC_DMA_CH_Enable(XMC_DMA0, 2);


  while(1);
}
