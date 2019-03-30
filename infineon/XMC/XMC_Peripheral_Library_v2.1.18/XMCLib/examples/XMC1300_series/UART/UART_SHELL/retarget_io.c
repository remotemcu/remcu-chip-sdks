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

#include <stdio.h>
#include "serial.h"

int _write(int fd, const void *buf, size_t count)
{
  (void)fd;

  for (int i = 0; i < count; ++i)
  {
    XMC_UART_CH_Transmit(SERIAL_UART, *(const uint8_t *)buf);
    buf++;
  }
  return count;
}

int _read(int fd, void *buf, size_t count)
{
  int char_cnt = 0;
  (void)fd;

#if 0
  for (int i = 0; i < count; ++i)
  {
#endif
    while ((XMC_UART_CH_GetStatusFlag(SERIAL_UART) & (XMC_UART_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION |
                                                      XMC_UART_CH_STATUS_FLAG_RECEIVE_INDICATION)) == 0);

    char_cnt++;
    *(uint8_t *)buf = XMC_UART_CH_GetReceivedData(SERIAL_UART);

    XMC_UART_CH_ClearStatusFlag(SERIAL_UART, XMC_UART_CH_STATUS_FLAG_ALTERNATIVE_RECEIVE_INDICATION |
                                             XMC_UART_CH_STATUS_FLAG_RECEIVE_INDICATION);

#if 0
    /* Stop reading if CR (Ox0D) character is received */
    if (*(uint8_t *)buf == 0x0DU)
    {
      /* New line character (CR) received ? */
      *(uint8_t*)buf = '\n';           /* Yes, convert LF to '\n' char. */
      break;                           /* Stop loop and return received char(s) */
    }

    buf++;
  }
#endif

  return char_cnt;
}
