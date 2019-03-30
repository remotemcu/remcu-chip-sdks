/*
 * Copyright (C) 2014-2017 Infineon Technologies AG. All rights reserved.
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
 * @date 14 Aug, 2017
 * @version 1.0.0
 *
 * @brief SPI + DMA example
 *
 * In this example an SPI transfer is done using DMA. SPI fifos are also used.
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 *
 */

#include <xmc_gpio.h>
#include <xmc_spi.h>
#include <xmc_dma.h>

#define LED1 P1_1
#define LED2 P1_0

// SPI TX/RX using DMA external loop back
#define SPI_TX P0_5
#define SPI_RX P0_4
#define SPI_SS P0_6
#define SPI_SCLK P0_11

// Number of transfers after which we toggle LED1 signaling everything goes fine
#define TICKS_PER_TOGGLE 1000

#define BUFFER_LENGTH 1024

uint8_t buffer1[BUFFER_LENGTH];
uint8_t recv_buffer1[BUFFER_LENGTH];

XMC_SPI_CH_CONFIG_t spi_config =
{
  .baudrate = 10000000U,
  .bus_mode = XMC_SPI_CH_BUS_MODE_MASTER,
  .selo_inversion = XMC_SPI_CH_SLAVE_SEL_INV_TO_MSLS
};

XMC_DMA_CH_CONFIG_t dma_ch_recv_config =
{
  .src_addr = (uint32_t)&(XMC_SPI1_CH0->OUTR),
  .src_transfer_width = XMC_DMA_CH_TRANSFER_WIDTH_8,
  .dst_transfer_width = XMC_DMA_CH_TRANSFER_WIDTH_8,
  .src_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE,
  .dst_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_INCREMENT,
  .src_burst_length = XMC_DMA_CH_BURST_LENGTH_1,
  .dst_burst_length = XMC_DMA_CH_BURST_LENGTH_1,
  .transfer_flow = XMC_DMA_CH_TRANSFER_FLOW_P2M_DMA,
  .transfer_type = XMC_DMA_CH_TRANSFER_TYPE_SINGLE_BLOCK,
  .src_handshaking = XMC_DMA_CH_SRC_HANDSHAKING_HARDWARE,
  .src_peripheral_request = DMA0_PERIPHERAL_REQUEST_USIC1_SR1_2,
  .enable_interrupt = true,
  .priority = 7
};

XMC_DMA_CH_CONFIG_t dma_ch_send_config =
{
  .dst_addr = (uint32_t)&(XMC_SPI1_CH0->IN[0]),
  .src_transfer_width = XMC_DMA_CH_TRANSFER_WIDTH_8,
  .dst_transfer_width = XMC_DMA_CH_TRANSFER_WIDTH_8,
  .src_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_INCREMENT,
  .dst_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE,
  .src_burst_length = XMC_DMA_CH_BURST_LENGTH_8,
  .dst_burst_length = XMC_DMA_CH_BURST_LENGTH_8,
  .transfer_flow = XMC_DMA_CH_TRANSFER_FLOW_M2P_DMA,
  .transfer_type = XMC_DMA_CH_TRANSFER_TYPE_SINGLE_BLOCK,
  .dst_handshaking = XMC_DMA_CH_DST_HANDSHAKING_HARDWARE,
  .dst_peripheral_request = DMA0_PERIPHERAL_REQUEST_USIC1_SR0_0,
};

void transfer_stream(const uint8_t *const src, const uint8_t *const dst, const uint32_t length)
{
  XMC_DMA_CH_ClearDestinationPeripheralRequest(XMC_DMA0, 1); /* clear pending request for transmit DMA Channel */
  XMC_USIC_CH_TriggerServiceRequest(XMC_SPI1_CH0, 0); /* Hardware trigger for DMA sending */

  XMC_SPI_CH_EnableSlaveSelect(XMC_SPI1_CH0, XMC_SPI_CH_SLAVE_SELECT_0);
  XMC_DMA_CH_SetBlockSize(XMC_DMA0, 0, length);
  XMC_DMA_CH_SetBlockSize(XMC_DMA0, 1, length);
  XMC_DMA_CH_SetDestinationAddress(XMC_DMA0, 0, (uint32_t)dst);
  XMC_DMA_CH_SetSourceAddress(XMC_DMA0, 1, (uint32_t)src);
  XMC_DMA_CH_Enable(XMC_DMA0, 0); /* receive DMA Channel */
  XMC_DMA_CH_Enable(XMC_DMA0, 1); /* transmit DMA Channel */
}


void GPDMA0_0_IRQHandler(void)
{
  static uint32_t ticks = 0;

  XMC_DMA_CH_ClearEventStatus(XMC_DMA0, 0, XMC_DMA_CH_EVENT_TRANSFER_COMPLETE);
  XMC_DMA_CH_ClearEventStatus(XMC_DMA0, 1, XMC_DMA_CH_EVENT_TRANSFER_COMPLETE);

  XMC_SPI_CH_DisableSlaveSelect(XMC_SPI1_CH0);

  if (memcmp(buffer1, recv_buffer1, BUFFER_LENGTH) != 0)
  {
	XMC_GPIO_SetOutputHigh(LED2);
    while(1);
  }

  ticks++;
  if (ticks == TICKS_PER_TOGGLE)
  {
	ticks = 0;
	XMC_GPIO_ToggleOutput(LED1);
  }

  transfer_stream(&buffer1[0], &recv_buffer1[0], BUFFER_LENGTH);
}

const XMC_GPIO_CONFIG_t gpio_config =
{
  .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
  .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW
};

int main(void)
{
  for (uint32_t i = 0; i < BUFFER_LENGTH; ++i)
  {
    buffer1[i] = i + 1;
  }

  XMC_GPIO_Init(LED1, &gpio_config);
  XMC_GPIO_Init(LED2, &gpio_config);

  XMC_DMA_Init(XMC_DMA0);
  XMC_DMA_CH_Init(XMC_DMA0, 0, &dma_ch_recv_config);
  XMC_DMA_CH_Init(XMC_DMA0, 1, &dma_ch_send_config);
  XMC_DMA_CH_EnableEvent(XMC_DMA0, 0, XMC_DMA_CH_EVENT_TRANSFER_COMPLETE);

  NVIC_SetPriority(GPDMA0_0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 63, 0));
  NVIC_EnableIRQ(GPDMA0_0_IRQn);

  XMC_SPI_CH_Init(XMC_SPI1_CH0, &spi_config);

  XMC_GPIO_SetMode(SPI_RX, XMC_GPIO_MODE_INPUT_TRISTATE);
  XMC_SPI_CH_SetInputSource(XMC_SPI1_CH0, XMC_SPI_CH_INPUT_DIN0, USIC1_C0_DX0_P0_4);

  XMC_USIC_CH_TXFIFO_EnableEvent(XMC_SPI1_CH0, XMC_USIC_CH_TXFIFO_EVENT_CONF_STANDARD);
  XMC_USIC_CH_TXFIFO_SetInterruptNodePointer(XMC_SPI1_CH0, XMC_USIC_CH_TXFIFO_INTERRUPT_NODE_POINTER_STANDARD, 0);
  XMC_USIC_CH_TXFIFO_Configure(XMC_SPI1_CH0, 32, XMC_USIC_CH_FIFO_SIZE_16WORDS, 7);

  XMC_USIC_CH_SetInterruptNodePointer(XMC_SPI1_CH0, XMC_USIC_CH_INTERRUPT_NODE_POINTER_ALTERNATE_RECEIVE, 1);
  XMC_USIC_CH_SetInterruptNodePointer(XMC_SPI1_CH0, XMC_USIC_CH_INTERRUPT_NODE_POINTER_RECEIVE, 1);
  XMC_SPI_CH_EnableEvent(XMC_SPI1_CH0, XMC_SPI_CH_EVENT_STANDARD_RECEIVE | XMC_SPI_CH_EVENT_ALTERNATIVE_RECEIVE);

  XMC_USIC_CH_RXFIFO_SetInterruptNodePointer(XMC_SPI1_CH0, XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_STANDARD, 1);
  XMC_USIC_CH_RXFIFO_EnableEvent(XMC_SPI1_CH0, XMC_USIC_CH_RXFIFO_EVENT_STANDARD);
  XMC_USIC_CH_RXFIFO_Configure(XMC_SPI1_CH0, 48, XMC_USIC_CH_FIFO_SIZE_16WORDS, 0);

  XMC_SPI_CH_SetBitOrderMsbFirst(XMC_SPI1_CH0);
  XMC_SPI_CH_Start(XMC_SPI1_CH0);

  XMC_GPIO_SetMode(SPI_TX, XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P0_5_AF_U1C0_DOUT0);
  XMC_GPIO_SetMode(SPI_SS, XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P0_6_AF_U1C0_SELO0);
  XMC_GPIO_SetMode(SPI_SCLK, XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P0_11_AF_U1C0_SCLKOUT);

  transfer_stream(&buffer1[0], &recv_buffer1[0], BUFFER_LENGTH);

  while(1);
}
