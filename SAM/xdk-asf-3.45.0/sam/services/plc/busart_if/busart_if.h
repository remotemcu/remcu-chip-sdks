/**
 * \file
 *
 * \brief PLC USART Buffered Interface
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

#ifndef BUSART_IF_H_INCLUDED
#define BUSART_IF_H_INCLUDED

#include "compiler.h"
#include "conf_busart_if.h"
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
 * \defgroup busart_plc_group PLC Buffered PDC USART
 *
 * This module provides configuration and utils for PLC Buffered USART service
 * interface.
 *
 * @{
 */

/* \name Frequency to poll internal usart buffer (Hz) */
/* @{ */
#define FREQ_TIMER_POLL_USART     100
/* @} */

/* \name Manage interruption priorities */

/* \note In case of use of FreeRTOS, GROUP_PRIO is same value than
 * configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY */
/* @{ */
#define TIMER_USART_PRIO         10
#define USART0_PRIO              10
#define USART1_PRIO              10
/* @} */

/* \name USART definitions */
/* @{ */
#define SERIAL_USART_0           0
#define SERIAL_USART_1           1
/* @} */

#ifdef CONF_BOARD_USART0_RXD
extern uint8_t *const usartRxBuf0;
extern uint8_t *const usartTxBuf0;
#endif

#ifdef CONF_BOARD_USART1_RXD
extern uint8_t *const usartRxBuf1;
extern uint8_t *const usartTxBuf1;
#endif

/* \name PLC USART Buffered Interface */
/* @{ */
int8_t busart_if_open(uint8_t chn, uint32_t bauds);
int8_t busart_if_close(uint8_t chn);
uint16_t busart_if_read(uint8_t chn, void *buffer, uint16_t len);
uint16_t busart_if_write(uint8_t chn, const void *buffer, uint16_t len);
int busart_if_rx_char(uint8_t chn);
uint16_t busart_if_tx_char(uint8_t chn, char data);

/* @} */
/* @} */

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/* @endcond */

#endif /* BUSART_IF_H_INCLUDED */
