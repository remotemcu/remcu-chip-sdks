/**
 * \file
 *
 * \brief PLC Service Universal Serial Interface
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

#ifndef USI_H_INCLUDED
#define USI_H_INCLUDED

#include "conf_usi.h"

/* / @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/* / @endcond */

/**
 * \ingroup plc_group
 * \defgroup usi_plc_group PLC Universal Serial Interface
 *
 * This module provides configuration and utils for the serialization of
 * protocols in PLC.
 *
 * @{
 */

/* ! \name Management Plane Protocol Spec. */
/* @{ */
#ifndef MNGP_PRIME_PROT
#define MNGP_PRIME_PROT         0x00
#endif

#ifndef MNGP_PRIME_GETQRY
#define MNGP_PRIME_GETQRY       0x00
#endif

#ifndef MNGP_PRIME_GETRSP
#define MNGP_PRIME_GETRSP       0x01
#endif

#ifndef MNGP_PRIME_SET
#define MNGP_PRIME_SET          0x02
#endif

#ifndef MNGP_PRIME_RESET
#define MNGP_PRIME_RESET        0x03
#endif

#ifndef MNGP_PRIME_REBOOT
#define MNGP_PRIME_REBOOT       0x04
#endif

#ifndef MNGP_PRIME_FU
#define MNGP_PRIME_FU           0x05
#endif

#ifndef MNGP_PRIME_EN_PIBQRY
#define MNGP_PRIME_EN_PIBQRY    0x06
#endif

#ifndef MNGP_PRIME_EN_PIBRSP
#define MNGP_PRIME_EN_PIBRSP    0x07
#endif
/* @} */

/* ! \name ATMEL serialized protocols */
/* @{ */
typedef enum {
	PROTOCOL_SNIF_PRIME    = 0x13,
	PROTOCOL_MAC_PRIME     = 0x17,
	PROTOCOL_MLME_PRIME    = 0x18,
	PROTOCOL_PLME_PRIME    = 0x19,
	PROTOCOL_432_PRIME     = 0x1A,
	PROTOCOL_BASEMNG_PRIME = 0x1D,
	PROTOCOL_PRIME_SERIAL  = 0x1F,
	PROTOCOL_ATPL230       = 0x22,
	PROTOCOL_USER_DEFINED  = 0xFE,
	PROTOCOL_INVALID       = 0xFF
} usi_protocol_t;
/* @} */

/* ! \name USI protocol parameters */
/* @{ */
#define CMD_PRIME_PROTOCOL_MSK       0x3F
#define CMD_PRIME_PROTOCOL(A)        ((A)&CMD_PRIME_PROTOCOL_MSK)
/* @} */

/* ! USI operation results */
typedef enum {
	USI_STATUS_PROTOCOL_NOT_FOUND = 0xFF,
	USI_STATUS_TX_BUFFER_OVERFLOW,
	USI_STATUS_TX_BUSY,
	USI_STATUS_TX_BLOCKED,
	USI_STATUS_RX_BUFFER_OVERFLOW,
	USI_STATUS_RX_BLOCKED,
	USI_STATUS_UART_ERROR,
	USI_STATUS_FORMAT_ERROR,
	USI_STATUS_OK,
	USI_STATUS_INVALID
} usi_status_t;

/* ! Message Structure to communicate with USI layer */
typedef struct {
	uint8_t uc_protocol_type;    /* !<  Protocol Type */
	uint8_t *ptr_buf;            /* !<  Pointer to data buffer */
	uint16_t us_len;             /* !<  Length of data */
} x_usi_serial_cmd_params_t;

/* ! Type for callback function pointers */
typedef uint8_t (*pf_usi_decode_cmd)(uint8_t *, uint16_t);

/* ! \name Types to manage commands */
/* @{ */
typedef uint8_t (*pf_usi_get_cmd)(void);
typedef void (*pf_usi_set_cmd)(uint8_t);
/* @} */

/**
 *  \name Universal Serial Interface API functions
 */
/* @{ */
void usi_init(void);
void usi_process(void);

usi_status_t usi_send_cmd(void *msg);
void usi_txrx_block_timer(void);

/* @} */

/* ! @} */

/* / @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/* / @endcond */

#endif /* USI_H_INCLUDED */
