/******************************************************************************
 * Software License Agreement
 *
 * Copyright (c) 2015-2016, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of the copyright holders nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share
 * modifications, enhancements or bug fixes with Infineon Technologies AG
 * (dave@infineon.com).
 *
 *****************************************************************************/
/**
 * @file uart.c
 * @date 30 July, 2016
 * @version 1.0.0
 *
 * @brief Implements service layer for UART communication <br>
 *
 * <b>Detailed description of file</b> <br>
 * The file implements functions for buffering received data, transmit data, provide event
 * flags etc.
 *
 * History
 *
 * 01 Jul 2014 Version 1.0.0 <br>
 * Initial version
 */
#include "uart.h"

/*USIC channel configuration*/
const XMC_UART_CH_CONFIG_t UART_channel_config =
{
  .baudrate      = 19200U,
  .data_bits     = 8U,
  .frame_length  = 8U,
  .stop_bits     = 1U,
  .oversampling  = 16U,
  .parity_mode   = XMC_USIC_CH_PARITY_MODE_NONE
};
/*Transmit pin configuration*/
const XMC_GPIO_CONFIG_t UART_tx_pin_config   =
{
  .mode             = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
  .output_level     = XMC_GPIO_OUTPUT_LEVEL_HIGH,
  .output_strength  = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
};

uint8_t UART_RX_Buffer[UART_RX_BUFF_SIZE];

/*Initialization function to configure USIC 0 channel 0 as UART
 * using pins Rx=P1.4, Tx=P1.5 using FIFO for transmission and reception*/
void UART_init(void)
{
  XMC_GPIO_SetMode((XMC_GPIO_PORT_t *)PORT1_BASE, 4U, XMC_GPIO_MODE_INPUT_TRISTATE);
  /* Initialize USIC channel in UART mode*/
  XMC_UART_CH_Init(XMC_UART0_CH0, &UART_channel_config);
    /*Set input source path*/
  XMC_USIC_CH_SetInputSource(XMC_UART0_CH0, XMC_USIC_CH_INPUT_DX0, 1U);
  /*Configure transmit FIFO*/
  XMC_USIC_CH_TXFIFO_Configure(XMC_UART0_CH0,
        16U,
        XMC_USIC_CH_FIFO_SIZE_16WORDS,
        1U);
  /*Configure receive FIFO*/
  XMC_USIC_CH_RXFIFO_Configure(XMC_UART0_CH0,
        0U,
        XMC_USIC_CH_FIFO_SIZE_16WORDS,
        15U);
  /* Start UART */
  XMC_UART_CH_Start(XMC_UART0_CH0);
    /* Initialize UART TX pin */
  XMC_GPIO_Init((XMC_GPIO_PORT_t *)PORT1_BASE, 5U, &UART_tx_pin_config);
}

/*Function to transmit data using Tx FIFO.
 * The return value indicates the number of bytes actually transmitted*/
uint32_t UART_Transmit(uint8_t * data, uint32_t count)
{
  uint32_t data_index = 0;
  while((!XMC_USIC_CH_TXFIFO_IsFull(XMC_UART0_CH0)) && (data_index < count))
  {
    XMC_UART_CH_Transmit(XMC_UART0_CH0, (uint16_t)data[data_index]);
    data_index++;
  }
  return data_index;
}

/*Function checks if any data is received on the Rx FIFO.
 * It reads the data from Rx FIFO and stores it in UART_RX_Buffer*/
uint32_t UART_CheckRxData(void)
{
  uint32_t data_index = 0;
  while((!XMC_USIC_CH_RXFIFO_IsEmpty(XMC_UART0_CH0)) && (data_index < UART_RX_BUFF_SIZE))
  {
    UART_RX_Buffer[data_index] = (uint8_t)XMC_UART_CH_GetReceivedData(XMC_UART0_CH0);
    data_index++;
  }
  return data_index;
}
