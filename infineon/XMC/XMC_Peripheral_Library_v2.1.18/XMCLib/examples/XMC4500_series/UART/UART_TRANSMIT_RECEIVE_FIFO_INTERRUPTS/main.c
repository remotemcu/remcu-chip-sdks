/*
 * Copyright (C) 2015 Infineon Technologies AG. All rights reserved.
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
 * @date 13 November,2015
 * @version 1.0.0
 *
 * @brief UART FIFO interrupts Relax Kit demo example
 *
 * Send 251 bytes by USIC0_CH0 using TX FIFO size of 8 bytes and receiving the data in USIC1_CH0 using a RX FIFO 8 bytes size.
 * Transmission and reception are non blocking,TX and RX FIFO limit interrupts are being used.
 * If reception is successful the onboard LED 1 will be switched on, otherwise it will remain switched off.
 * Note: Please connect USIC0_CH0_TX (P1.4) to USIC1_CH0_RX (P2.15) via external cable.
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 */

#include <xmc_gpio.h>
#include <xmc_uart.h>

/* Pins macro definition */

#define LED1    P1_1
#define UART_TX P1_5
#define UART_RX P2_15

/* Number of data to tx/rx and limits for the TX and RX FIFOs */

#define NUM_DATA 251
#define RX_FIFO_INITIAL_LIMIT 7
#define TX_FIFO_INITIAL_LIMIT 1

/* Initialization structures */

XMC_GPIO_CONFIG_t uart_tx =
{
  .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2,
  .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
};

XMC_GPIO_CONFIG_t uart_rx =
{
  .mode = XMC_GPIO_MODE_INPUT_TRISTATE
};

XMC_GPIO_CONFIG_t led =
{
  .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
  .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
};

/* Initialization structure for both USIC0_CH0 and USIC0_CH1 channels */
XMC_UART_CH_CONFIG_t uart_config =
{
  .data_bits = 8U,
  .stop_bits = 1U,
  .baudrate = 9600U
};

/* Global variables initialization. Tx and rx indexes and tx and rx arrays */
uint32_t tx_index=0;
uint32_t rx_index=0;
uint8_t tx_data[NUM_DATA];
uint8_t rx_data[NUM_DATA];


/* Transmit handling IRQ */
void USIC0_0_IRQHandler(void)
{
  /* If still remaining data to be send */
  if(tx_index < NUM_DATA)
  {
    /* Fill the TX FIFO till it is full */
    while(!XMC_USIC_CH_TXFIFO_IsFull(XMC_UART0_CH0))
    {
	  XMC_UART_CH_Transmit(XMC_UART0_CH0, tx_data[tx_index]);
	  tx_index++;
    }
  }
}

/* Receive handling IRQ */
void USIC1_1_IRQHandler(void)
{
  /* Read the RX FIFO till it is empty */
  while(!XMC_USIC_CH_RXFIFO_IsEmpty(XMC_UART1_CH0))
  {
    rx_data[rx_index++] = XMC_UART_CH_GetReceivedData(XMC_UART1_CH0);
  }

  /* If all the data have been received */
  if(rx_index == (NUM_DATA))
  {
    /* Check if every received data match with the transmitted data */
    for (int tmp=0; tmp<NUM_DATA; tmp++)
    {
      /* If reception fails stays in an infinite while loop and switch off the LED */
      if (tx_data[tmp]!=rx_data[tmp])
      {
        while(1)
        {
          XMC_GPIO_SetOutputLow(LED1);
        }
      }
      else
      {
        /* If reception is successful switch on the LED */
        XMC_GPIO_SetOutputHigh(LED1);
      }
    }
  }

  /* If the remaining data to be received is smaller than the initial RX FTFO Limit
   * it is modified to the remaining data minus 1 in order react when we have all the data received*/
  if((NUM_DATA-rx_index) < RX_FIFO_INITIAL_LIMIT)
  {
    XMC_USIC_CH_RXFIFO_SetSizeTriggerLimit(XMC_UART1_CH0, XMC_USIC_CH_FIFO_SIZE_8WORDS, (NUM_DATA-rx_index)-1);
  }
}

int main(void)
{

  /* USIC channels initialization */
  XMC_UART_CH_Init(XMC_UART0_CH0, &uart_config);
  XMC_UART_CH_Init(XMC_UART1_CH0, &uart_config);

  /* Input multiplexer configuration for UART1_CH0 */
  XMC_UART_CH_SetInputSource(XMC_UART1_CH0, XMC_UART_CH_INPUT_RXD, USIC1_C0_DX0_P2_15);

  /* FIFOs initialization for both channels:
   *  8 entries for TxFIFO from point 0, LIMIT=1
   *  8 entries for RxFIFO from point 8, LIMIT=7 (SRBI is set if all 8*data has been received)
   *  */
  XMC_USIC_CH_TXFIFO_Configure(XMC_UART0_CH0, 0, XMC_USIC_CH_FIFO_SIZE_8WORDS, TX_FIFO_INITIAL_LIMIT);
  XMC_USIC_CH_RXFIFO_Configure(XMC_UART1_CH0, 8, XMC_USIC_CH_FIFO_SIZE_8WORDS, RX_FIFO_INITIAL_LIMIT);

  /* Enabling events for TX FIFO and RX FIFO */
  XMC_USIC_CH_TXFIFO_EnableEvent(XMC_UART0_CH0,XMC_USIC_CH_TXFIFO_EVENT_CONF_STANDARD);
  XMC_USIC_CH_RXFIFO_EnableEvent(XMC_UART1_CH0,XMC_USIC_CH_RXFIFO_EVENT_CONF_STANDARD |
		                                       XMC_USIC_CH_RXFIFO_EVENT_CONF_ALTERNATE);

  /* Connecting the previously enabled events to a Service Request line number */
  XMC_USIC_CH_TXFIFO_SetInterruptNodePointer(XMC_UART0_CH0,XMC_USIC_CH_TXFIFO_INTERRUPT_NODE_POINTER_STANDARD,0);
  XMC_USIC_CH_RXFIFO_SetInterruptNodePointer(XMC_UART1_CH0,XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_STANDARD,1);
  XMC_USIC_CH_RXFIFO_SetInterruptNodePointer(XMC_UART1_CH0,XMC_USIC_CH_RXFIFO_INTERRUPT_NODE_POINTER_ALTERNATE,1);

  /* Start USIC operation as UART */
  XMC_UART_CH_Start(XMC_UART0_CH0);
  XMC_UART_CH_Start(XMC_UART1_CH0);

  /*Initialization of the necessary ports*/
  XMC_GPIO_Init(UART_TX,&uart_tx);
  XMC_GPIO_Init(UART_RX,&uart_rx);
  XMC_GPIO_Init(LED1,&led);

  /*Configuring priority and enabling NVIC IRQ for the defined Service Request line number */
  NVIC_SetPriority(USIC0_0_IRQn,63U);
  NVIC_EnableIRQ(USIC0_0_IRQn);
  NVIC_SetPriority(USIC1_1_IRQn,62U);
  NVIC_EnableIRQ(USIC1_1_IRQn);

  /* Filling the tx array */
  for (uint32_t i = 0; i < NUM_DATA; i++)
  {
    tx_data[i]=i;
  }

  /* Filling the the first time TX FIFO. Successive fillings will be done in the TX FIFO IRQ*/
  while(!XMC_USIC_CH_TXFIFO_IsFull(XMC_UART0_CH0))
  {
    XMC_UART_CH_Transmit(XMC_UART0_CH0,tx_data[tx_index++]);
  }

  while(1)
  {
	/* Infinite loop */
  }
}
