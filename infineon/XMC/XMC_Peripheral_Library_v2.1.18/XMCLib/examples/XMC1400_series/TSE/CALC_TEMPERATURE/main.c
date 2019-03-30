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
 * @date 9 November,2015
 * @version 1.0.0
 *
 * @brief TSE example, ROM function to calculate internal temperature
 *
 *
 * History
 *
 * Version 1.0.0 Initial
 */

#include <stdio.h>

#include <xmc_scu.h>
#include <xmc_gpio.h>
#include <xmc_uart.h>

#define TICKS_PER_SECOND 1000
#define LED1 P4_0

/* UART pins */
#define UART_TX P1_2
#define UART_RX P1_3

const XMC_SCU_CLOCK_CONFIG_t clock_config =
{
  .fdiv = 0,
  .idiv = 1,
  .pclk_src = XMC_SCU_CLOCK_PCLKSRC_DOUBLE_MCLK
};

void SystemCoreClockSetup(void)
{
  XMC_SCU_CLOCK_Init(&clock_config);

  SystemCoreClockUpdate();
}

const XMC_UART_CH_CONFIG_t uart_config =
{
  .data_bits = 8U,
  .stop_bits = 1U,
  .baudrate = 115200U
};

void SysTick_Handler(void)
{
  static uint32_t ticks = 0U;

  ++ticks;
  if (ticks == TICKS_PER_SECOND)
  {
    ticks = 0U;
    XMC_GPIO_ToggleOutput(LED1);

    printf("Chip temperature: %d\r\n", XMC_SCU_CalcTemperature());
  }
}

int main(void)
{
  XMC_UART_CH_Init(XMC_UART0_CH1, &uart_config);

  XMC_GPIO_SetMode(UART_RX, XMC_GPIO_MODE_INPUT_TRISTATE);
  XMC_UART_CH_SetInputSource(XMC_UART0_CH1, XMC_UART_CH_INPUT_RXD, USIC0_C1_DX0_P1_3);

  XMC_UART_CH_Start(XMC_UART0_CH1);

  XMC_GPIO_SetMode(UART_TX, XMC_GPIO_MODE_OUTPUT_PUSH_PULL | P1_2_AF_U0C1_DOUT0);

  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

  XMC_SCU_StartTempMeasurement();

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U);
}
