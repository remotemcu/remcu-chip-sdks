/**
 * \file
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#ifdef DBG_USE_USART
#  define dbg_init     dbg_usart_init
#  define dbg_cleanup  dbg_usart_cleanup
#  define dbg_print    printf
#  define dbg_rx_ready dbg_usart_rx_ready
#  define dbg_getchar  dbg_usart_getchar
#  define dbg_putchar  dbg_usart_putchar

void dbg_usart_init(void);
void dbg_usart_cleanup(void);
bool dbg_usart_rx_ready(void);
uint8_t dbg_usart_getchar(void);
void dbg_usart_putchar(uint8_t c);

#else
#  define dbg_init()
#  define dbg_cleanup()
#  define dbg_print(...)
#  define dbg_rx_ready()   0
#  define dbg_getchar()    0
#  define dbg_putchar(...)
#endif

#endif /* #ifndef DEBUG_H_INCLUDED */

