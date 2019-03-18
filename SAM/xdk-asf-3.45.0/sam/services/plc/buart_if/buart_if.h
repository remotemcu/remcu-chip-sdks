/**
 * \file
 *
 * \brief PLC UART Buffered Interface
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

#ifndef BUART_IF_H_INCLUDED
#define BUART_IF_H_INCLUDED

#include "compiler.h"
#include "conf_buart_if.h"
#include "conf_board.h"

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/* @endcond */

/**
 * \ingroup plc_group
 * \defgroup buart_plc_group PLC Buffered PDC UART
 *
 * This module provides configuration and utils for PLC Buffered UART service
 * interface.
 *
 * @{
 */

/* \name Frequency to poll internal uart buffer (Hz) */
/* @{ */
#define FREQ_TIMER_POLL_UART     100
/* @} */

/* \name Manage interruption priorities */

/* \note In case of use of FreeRTOS, GROUP_PRIO is same value than
 * configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY */
/* @{ */
#define TIMER_UART_PRIO         10
#define UART0_PRIO              10
#define UART1_PRIO              10
/* @} */

/* \name UART definitions */
/* @{ */
#define SERIAL_UART_0           0
#define SERIAL_UART_1           1
/* @} */

#ifdef CONF_BOARD_UART0
extern uint8_t *const uartRxBuf0;
extern uint8_t *const uartTxBuf0;
#endif

#ifdef CONF_BOARD_UART1
extern uint8_t *const uartRxBuf1;
extern uint8_t *const uartTxBuf1;
#endif

/* \name PLC UART Buffered Interface */
/* @{ */
int8_t buart_if_open(uint8_t chn, uint32_t bauds);
int8_t buart_if_close(uint8_t chn);
uint16_t buart_if_read(uint8_t chn, void *buffer, uint16_t len);
uint16_t buart_if_write(uint8_t chn, const void *buffer, uint16_t len);
int buart_if_rx_char(uint8_t chn);
uint16_t buart_if_tx_char(uint8_t chn, char data);

/* @} */
/* @} */

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/* @endcond */

#endif /* BUART_IF_H_INCLUDED */
