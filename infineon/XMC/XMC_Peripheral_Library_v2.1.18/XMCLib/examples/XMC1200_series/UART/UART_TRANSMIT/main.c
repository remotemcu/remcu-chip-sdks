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
 * @date 22 July,2015
 * @version 1.0.2
 *
 * @brief UART demo example
 *
 * Send a periodic message via UART
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 * Version 1.0.1  UART Initialization Sequence modified <br>
 * Version 1.0.2 Updated with latest llds<br>
 * Version 1.0.3 Changed XMC_GPIO_SetMode() to XMC_GPIO_Init() for code clarity reasons <br>
 */

#include <xmc_gpio.h>
#include <xmc_uart.h>

#define LED P0_6
#define UART_RX P1_3
#define UART_TX P1_2

#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 1000

const uint8_t message[] = "Hello world!!\n";

/* Pins configuration */
XMC_GPIO_CONFIG_t uart_tx;
XMC_GPIO_CONFIG_t uart_rx;
XMC_GPIO_CONFIG_t led;

/* UART configuration */
const XMC_UART_CH_CONFIG_t uart_config = 
{	
  .data_bits = 8U,
  .stop_bits = 1U,
  .baudrate = 115200
};

void SysTick_Handler(void)
{
  uint32_t index;
  static uint32_t ticks = 0;

  ticks++;
  if (ticks == TICKS_WAIT)
  {
	  XMC_GPIO_ToggleOutput(LED);

	  for (index = 0; index < sizeof(message) - 1; index++)
	  {
	    XMC_UART_CH_Transmit(XMC_UART0_CH1, message[index]);
	  }
	  ticks = 0;
  }
}

int main(void)
{
	/* Pins mode */
	uart_tx.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7;
	uart_rx.mode = XMC_GPIO_MODE_INPUT_TRISTATE;
	led.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
	
  /* Configure UART channel */
  XMC_UART_CH_Init(XMC_UART0_CH1, &uart_config);
  XMC_UART_CH_SetInputSource(XMC_UART0_CH1, XMC_UART_CH_INPUT_RXD,USIC0_C1_DX0_P1_3);
  
	/* Start UART channel */
  XMC_UART_CH_Start(XMC_UART0_CH1);

  /* Configure pins */
	XMC_GPIO_Init(UART_TX, &uart_tx);
  XMC_GPIO_Init(UART_RX, &uart_rx);
	XMC_GPIO_Init(LED, &led);

  /* Send a message via UART periodically */
  SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

  while(1)
  {
	/* Infinite loop */
  }
}
