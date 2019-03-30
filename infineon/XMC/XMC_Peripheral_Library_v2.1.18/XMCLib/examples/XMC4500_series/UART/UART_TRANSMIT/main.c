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
 * @version 1.0.1
 *
 * @brief UART demo example
 *
 * Send a periodic message via UART
 * Connect PC_TX to P1.4
 * Connect PC_RX to P1.5
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 * Version 1.0.1 Changed XMC_GPIO_SetMode() to XMC_GPIO_Init() for code clarity reasons <br>
 */

#include <xmc_gpio.h>
#include <xmc_uart.h>

#define TICKS_PER_SECOND 1000
#define TICKS_WAIT 1000

const uint8_t message[] = "Hello world!!\n";

#define LED1    P1_1
#define UART_TX P1_5
#define UART_RX P1_4

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

XMC_UART_CH_CONFIG_t uart_config =
{
  .data_bits = 8U,
  .stop_bits = 1U,
  .baudrate = 115200U
};

void SysTick_Handler(void)
{
  static uint32_t ticks = 0;
  uint32_t index;

  ticks++;
  if (ticks == TICKS_WAIT)
  {
	  XMC_GPIO_ToggleOutput(LED1);

	  for (index = 0; index < sizeof(message) - 1; index++)
	  {
	    XMC_UART_CH_Transmit(XMC_UART0_CH0, message[index]);
	  }
	  ticks = 0;
  }
}

int main(void)
{
  XMC_UART_CH_Init(XMC_UART0_CH0, &uart_config);
  XMC_UART_CH_SetInputSource(XMC_UART0_CH0, XMC_UART_CH_INPUT_RXD, USIC0_C0_DX0_P1_4);
  XMC_UART_CH_Start(XMC_UART0_CH0);
  XMC_GPIO_Init(UART_TX,&uart_tx);
  XMC_GPIO_Init(UART_RX,&uart_rx);
  XMC_GPIO_Init(LED1,&led);

  /* Send a message via UART periodically */
  SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

  while(1)
  {
	/* Infinite loop */
  }
}
