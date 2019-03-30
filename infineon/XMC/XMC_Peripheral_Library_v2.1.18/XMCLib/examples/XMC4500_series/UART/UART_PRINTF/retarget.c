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
 * @version 1.0.0
 *
 * @brief UART demo example
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 */

#include <stdio.h>
#include <xmc_uart.h>

#if defined(__GNUC__)
int _write(int fd, char *ptr, int len)
{
  for (int i = 0; i < len; ++i)
  {
    XMC_UART_CH_Transmit(XMC_UART0_CH0, ptr[i]);
  }
  return len;
}
#endif

#if defined(__ICCARM__)
size_t __write(int Handle, const unsigned char * Buf, size_t Bufsize)
{
  for (int i = 0; i < Bufsize; ++i)
  {
    XMC_UART_CH_Transmit(XMC_UART0_CH0, Buf[i]);
  }
  return Bufsize;
}
#endif

#if defined(__CC_ARM)

/*----------------------------------------------------------------------------
 * Name:    Retarget.c
 * Purpose: 'Retarget' layer for target-dependent low level functions
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the µVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <rt_misc.h>

#pragma import(__use_no_semihosting_swi)


struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;


int fputc(int c, FILE *f) {
  XMC_UART_CH_Transmit(XMC_UART0_CH0, c);
  return c;
}

int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}


void _ttywrch(int c) {
  XMC_UART_CH_Transmit(XMC_UART0_CH0, c);
  while ((XMC_UART_CH_GetStatusFlag(XMC_UART0_CH0) & XMC_UART_CH_STATUS_FLAG_TRANSMIT_BUFFER_INDICATION) == 0);
}


void _sys_exit(int return_code) {
label:  goto label;  /* endless loop */
}
#endif

