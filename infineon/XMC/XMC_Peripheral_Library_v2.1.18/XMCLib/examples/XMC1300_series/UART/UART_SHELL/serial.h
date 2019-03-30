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

#include <xmc_uart.h>

#ifndef SERIAL_H
#define SERIAL_H

#define SERIAL_BAUDRATE 115200

#define SERIAL_UART XMC_UART0_CH1
#define SERIAL_TX P1_2
#define SERIAL_TX_AF P1_2_AF_U0C1_DOUT0
#define SERIAL_RX P1_3
#define SERIAL_RX_USIC_INPUT USIC0_C1_DX0_P1_3


#ifdef __cplusplus
extern "C" {
#endif

void serial_init(void);

#ifdef __cplusplus
}
#endif

#endif
