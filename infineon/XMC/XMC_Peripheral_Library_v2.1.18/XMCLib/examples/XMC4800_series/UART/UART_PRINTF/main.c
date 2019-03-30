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
 * @date 20 October,2015
 * @version 1.0.1
 *
 * @brief UART printf demo example
 *
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 * Version 1.0.1 Changed to avoid compiler warnings <br>
 */

#include <stdio.h>

#include <xmc_gpio.h>
#include <xmc_uart.h>

#define LED1 P1_1
#define UART_TX P1_5
#define UART_RX P1_4

XMC_UART_CH_CONFIG_t uart_config =
{
  .data_bits = 8U,
  .stop_bits = 1U,
  .baudrate = 115200U
};

void XMC_AssertHandler(const char *const msg, const char *const file, uint32_t line)
{
  printf("%s at line %u of %s\n", msg, (unsigned int)line, file);
  while(1);
}


int main(void)
{
  XMC_UART_CH_Init(XMC_UART0_CH0, &uart_config);

  XMC_GPIO_SetMode(UART_RX, XMC_GPIO_MODE_INPUT_TRISTATE);
  XMC_UART_CH_SetInputSource(XMC_UART0_CH0, XMC_UART_CH_INPUT_RXD, USIC0_C0_DX0_P1_4);

  XMC_UART_CH_Start(XMC_UART0_CH0);

  XMC_GPIO_SetMode(UART_TX,(XMC_GPIO_MODE_t)(XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P1_5_AF_U0C0_DOUT0));
  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

  printf("XMClib ASSERT demo\n");

  /* Next line will fail assertion and a message is printed out */
  XMC_GPIO_SetOutputLevel(LED1, XMC_GPIO_OUTPUT_LEVEL_LOW);

  while(1U);
}
