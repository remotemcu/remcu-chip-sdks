/*
 * Copyright (C) 2018 Infineon Technologies AG. All rights reserved.
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

#include "serial.h"

#include <xmc_uart.h>
#include <xmc_gpio.h>

const XMC_UART_CH_CONFIG_t uart_config =
{
  .baudrate = SERIAL_BAUDRATE,
  .data_bits = 8,
  .stop_bits = 1,
};

void serial_init(void)
{
  XMC_UART_CH_Init(SERIAL_UART, &uart_config);

  XMC_GPIO_SetMode(SERIAL_RX, XMC_GPIO_MODE_INPUT_TRISTATE);
  XMC_UART_CH_SetInputSource(SERIAL_UART, XMC_UART_CH_INPUT_RXD, SERIAL_RX_USIC_INPUT);

  XMC_UART_CH_Start(SERIAL_UART);

  XMC_GPIO_SetMode(SERIAL_TX, XMC_GPIO_MODE_OUTPUT_PUSH_PULL | SERIAL_TX_AF);
}
