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

#include <stdio.h>
#include <string.h>

#include "conf_usi.h"
#include "asf.h"

/* / @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/* / @endcond */

/**
 * \weakgroup usi_plc_group
 * @{
 */

/* Default empty PHY serialization function */
uint8_t Dummy_serial_parser(uint8_t *puc_rx_msg, uint16_t us_len);

#ifdef __GNUC__
uint8_t mngl_rcv_cmd(uint8_t *puc_rx_msg, uint16_t us_len) __attribute__ ((weak, alias("Dummy_serial_parser")));
uint8_t serial_if_api_parser(uint8_t *puc_rx_msg, uint16_t us_len) __attribute__ ((weak, alias("Dummy_serial_parser")));
uint8_t serial_if_sniffer_api_parser(uint8_t *puc_rx_msg, uint16_t us_len) __attribute__ ((weak, alias("Dummy_serial_parser")));
uint8_t serial_if_mac_api_parser(uint8_t *puc_rx_msg, uint16_t us_len) __attribute__ ((weak, alias("Dummy_serial_parser")));
uint8_t serial_if_mlme_api_parser(uint8_t *puc_rx_msg, uint16_t us_len) __attribute__ ((weak, alias("Dummy_serial_parser")));
uint8_t serial_if_plme_api_parser(uint8_t *puc_rx_msg, uint16_t us_len) __attribute__ ((weak, alias("Dummy_serial_parser")));
uint8_t serial_432_if_api_parser(uint8_t *puc_rx_msg, uint16_t us_len) __attribute__ ((weak, alias("Dummy_serial_parser")));
uint8_t serial_if_user_def_api_parser(uint8_t *puc_rx_msg, uint16_t us_len) __attribute__ ((weak, alias("Dummy_serial_parser")));
uint8_t baseMng_receivedCmd(uint8_t *puc_rx_msg, uint16_t us_len) __attribute__ ((weak, alias("Dummy_serial_parser")));
uint8_t phySerial_receivedCmd(uint8_t *puc_rx_msg, uint16_t us_len) __attribute__ ((weak, alias("Dummy_serial_parser")));

#endif

#ifdef __ICCARM__
extern uint8_t mngl_rcv_cmd(uint8_t *puc_rx_msg, uint16_t us_len);

#pragma weak mngl_rcv_cmd=Dummy_serial_parser
extern uint8_t serial_if_api_parser(uint8_t *puc_rx_msg, uint16_t us_len);

#pragma weak serial_if_api_parser=Dummy_serial_parser
extern uint8_t serial_if_sniffer_api_parser(uint8_t *puc_rx_msg, uint16_t us_len);

#pragma weak serial_if_sniffer_api_parser=Dummy_serial_parser
extern uint8_t serial_if_mac_api_parser(uint8_t *puc_rx_msg, uint16_t us_len);

#pragma weak serial_if_mac_api_parser=Dummy_serial_parser
extern uint8_t serial_if_mlme_api_parser(uint8_t *puc_rx_msg, uint16_t us_len);

#pragma weak serial_if_mlme_api_parser=Dummy_serial_parser
extern uint8_t serial_if_plme_api_parser(uint8_t *puc_rx_msg, uint16_t us_len);

#pragma weak serial_if_plme_api_parser=Dummy_serial_parser
extern uint8_t serial_432_if_api_parser(uint8_t *puc_rx_msg, uint16_t us_len);

#pragma weak serial_432_if_api_parser=Dummy_serial_parser
extern uint8_t serial_if_user_def_api_parser(uint8_t *puc_rx_msg, uint16_t us_len);

#pragma weak serial_if_user_def_api_parser=Dummy_serial_parser
extern uint8_t baseMng_receivedCmd(uint8_t *puc_rx_msg, uint16_t us_len);

#pragma weak baseMng_receivedCmd=Dummy_serial_parser
extern uint8_t phySerial_receivedCmd(uint8_t *puc_rx_msg, uint16_t us_len);

#pragma weak phySerial_receivedCmd=Dummy_serial_parser
#endif

#if defined (USE_PROTOCOL_PRIME_SERIAL_PORT)
  #pragma message("USI_CFG: USE_PROTOCOL_PRIME_SERIAL_PORT")
uint8_t phySerial_receivedCmd(uint8_t *rxBuff, uint16_t length);
pf_usi_decode_cmd cbFnPhySerial  = (pf_usi_decode_cmd)phySerial_receivedCmd;
#else
pf_usi_decode_cmd cbFnPhySerial  = NULL;
#endif

/* \name Minimum overhead introduced by the USI protocol */
/* \note (1 Start Byte, 2 Bytes (Len+Protocol), 1 End Byte, 1 CRC Byte) */
#define MIN_OVERHEAD    5

/* \name Special characters used by USI */
/* @{ */
/* Start/end mark in message */
#define MSGMARK       0x7e
/* Escaped start/end mark */
#define ESC_MSGMARK   0x5e
/* Escape mark in message */
#define ESCMARK       0x7d
/* Escaped escape mark */
#define ESC_ESCMARK   0x5d
/* @} */

/* \name MSG started and ended flags */
/* @{ */
#define MSG_START 1
#define MSG_END   0
/* @} */

/* \name USI header and CRC lengths */
/* @{ */
#define HEADER_LEN  2
#define CRC8_LEN    1
#define CRC16_LEN   2
#define CRC32_LEN   4
/* @} */

/** \name USI flow control internal protocol
 *  \note This internal protocol has no effect on NUM_PROTOCOLS and NUM_PORTS
 *  constants defined in conf_usi.h because it has no interaction with other
 *  modules messages. It aims to provide flow control between the embedded USI
 *  and the USI Host.
 */
/* @{ */
/* Internal protocol ID */
#define PROTOCOL_INTERNAL  0x3F
/* Commands for internal protocol messages */
#define CMD_LOCK_PORT        0
#define CMD_UNLOCK_PORT      1
/* Lenght of internal messages */
#define INTERNAL_MSG_LEN               1
#define MAX_ESCAPED_INTERNAL_MSG_LEN  10
/* Timeouts for port blocking (in ms) and update function callback */
#define TX_BLOCK_TIMEOUT   50
#define RX_BLOCK_TIMEOUT   50
#define TXRX_BLOCK_UPDATE   1
/* @} */

/* \name USI protocol header format */
/* @{ */
#define TYPE_PROTOCOL_OFFSET       1
#define TYPE_PROTOCOL_MSK       0x3F
#define LEN_PROTOCOL_HI_OFFSET     0
#define LEN_PROTOCOL_HI_MSK     0xFF
#define LEN_PROTOCOL_HI_SHIFT      2
#define LEN_PROTOCOL_LO_OFFSET     1
#define LEN_PROTOCOL_LO_MSK     0xC0
#define LEN_PROTOCOL_LO_SHIFT      6
#define XLEN_PROTOCOL_OFFSET       2
#define XLEN_PROTOCOL_MSK       0xC0
#define XLEN_PROTOCOL_SHIFT_L      4
#define XLEN_PROTOCOL_SHIFT_R     10
#define PAYLOAD_OFFSET             2
#define CMD_PROTOCOL_OFFSET        2
#define CMD_PROTOCOL_MSK        0x3F
/* @} */

/** \name Macro operators
 * \note A: HI, B: LO, C:Xlen
 */
/* @{ */
#define TYPE_PROTOCOL(A)      ((A)&TYPE_PROTOCOL_MSK)
#define LEN_PROTOCOL(A, B)     ((((uint16_t)(A)) << LEN_PROTOCOL_HI_SHIFT) + ((B) >> LEN_PROTOCOL_LO_SHIFT))
#define XLEN_PROTOCOL(A, B, C)  ((((uint16_t)(A)) << LEN_PROTOCOL_HI_SHIFT) + ((B) >> LEN_PROTOCOL_LO_SHIFT) + (((uint16_t)(C)&XLEN_PROTOCOL_MSK) << XLEN_PROTOCOL_SHIFT_L))
#define LEN_HI_PROTOCOL(A)    (((uint16_t)(A) >> LEN_PROTOCOL_HI_SHIFT) & LEN_PROTOCOL_HI_MSK)
#define LEN_LO_PROTOCOL(A)    (((uint16_t)(A) << LEN_PROTOCOL_LO_SHIFT) & LEN_PROTOCOL_LO_MSK)
#define LEN_EX_PROTOCOL(A)    (((uint16_t)(A & 0x0c00)) >> 4)
#define CMD_PROTOCOL(A)       ((A)&CMD_PROTOCOL_MSK)
/* @} */

/* USI command structure */
typedef struct {
	/* Protocol Type */
	uint8_t uc_p_type;
	/* Pointer to data buffer */
	uint8_t *puc_buf;
	/* Length of data */
	uint16_t us_len;
} cmd_params_t;

/* USI communication control parameters structure */
typedef struct {
	/* Reception index */
	uint16_t us_idx_in;
	/* Timer to unlock RX port by timeout */
	uint16_t us_rx_block_timer;
	/* Timer to unlock TX port by timeout */
	uint16_t us_tx_block_timer;
} USI_param_t;

/* Reception states */
enum {
	/* Inactive */
	RX_IDLE,
	/* Receiving message */
	RX_MSG,
	/* Processing escape char */
	RX_ESC,
	/* Message received correctly */
	RX_EORX
};

/* Transmission states */
enum {
	/* Inactive */
	TX_IDLE,
	/* Transmitting message */
	TX_MSG
};

/* USI communication control parameters (one entry per port) */
static USI_param_t usi_cfg_param[NUM_PORTS];

/* \name USI message boundary control flag */
/* @{ */
static uint8_t uc_message_status;
/* @} */

/* \name USI flow control internal protocol variables */
/* @{ */
cmd_params_t internal_command;
uint8_t uc_int_cmd_lock = CMD_LOCK_PORT;
uint8_t uc_int_cmd_unlock = CMD_UNLOCK_PORT;
/* @} */

/* \name Types of serial port */
#define UART_TYPE   0
#define USART_TYPE  1

/* Protocol port mapping */
typedef struct {
	/* Protocol Type */
	uint8_t uc_p_type;
	/* Communication Port */
	uint8_t uc_port;
} map_protocols_t;

/* Port configuration */
typedef struct {
	/* Serial Communication Type */
	uint8_t uc_s_type;
	/* Port number */
	uint8_t uc_chn;
	/* Port speed (bauds) */
	uint32_t ul_speed;
	/* Port buffer size in transmission */
	uint16_t us_tx_size;
	/* Port buffer size in reception */
	uint16_t us_rx_size;
} map_ports_t;

/* Buffer handling structure */
typedef struct {
	/* Current size of data in the buffer */
	uint16_t us_size;
	/* Pointer to the buffer */
	uint8_t *const puc_buf;
} map_buffers_t;

/* Function Pointers for USI protocols */
#undef CONF_PORT
#define CONF_PORT(type, channel, speed, tx_size, rx_size) {type, channel, speed, tx_size, rx_size}

/**
 * \name Port Mapping. Configured with the values provided in conf_usi.h:
 * MapPorts[PORT TYPE, PORT CHANNEL, PORT SPEED, TX BUFFER SIZE, RX BUFFER SIZE]
 */
static const map_ports_t usiMapPorts[NUM_PORTS + 1] = {
#ifdef PORT_0
	PORT_0,
#endif
#ifdef PORT_1
	PORT_1,
#endif
#ifdef PORT_2
	PORT_2,
#endif
#ifdef PORT_3
	PORT_3,
#endif
	{0xff, 0xff, 0, 0, 0}
};

/**
 * \name Protocol Mapping. Configured with the values provided in conf_usi.h:
 * MapProtocols[PROTOCOL TYPE, PORT INDEX]
 */
/* @{ */
static const map_protocols_t usi_map_protocols[NUM_PROTOCOLS + 1] = {
#ifdef USE_MNGP_PRIME_PORT
	{MNGP_PRIME_PROT, USE_MNGP_PRIME_PORT},
#endif

#ifdef USE_PROTOCOL_PHY_1010_PORT
	{PROTOCOL_PHY_1010, USE_PROTOCOL_PHY_1010_PORT},
#endif

#ifdef USE_PROTOCOL_PHY_1020_PORT
	{PROTOCOL_PHY_1020, USE_PROTOCOL_PHY_1020_PORT},
#endif

#ifdef USE_PROTOCOL_ATPL230_PORT
	{PROTOCOL_ATPL230, USE_PROTOCOL_ATPL230_PORT},
#endif

#ifdef USE_PROTOCOL_SNIF_ECSS_PORT
	{PROTOCOL_SNIF_ECSS, USE_PROTOCOL_SNIF_ECSS_PORT},
#endif

#ifdef USE_PROTOCOL_SNIF_PRIME_PORT
	{PROTOCOL_SNIF_PRIME, USE_PROTOCOL_SNIF_PRIME_PORT},
#endif

#ifdef USE_PROTOCOL_MNGP_ECSS_PORT
	{PROTOCOL_MNGP_ECSS, USE_PROTOCOL_MNGP_ECSS_PORT},
#endif

#ifdef USE_PROTOCOL_432_ECSS_PORT
	{PROTOCOL_432_ECSS, USE_PROTOCOL_432_ECSS_PORT},
#endif

#ifdef USE_PROTOCOL_PHY_PRIME_PORT
	{PROTOCOL_PHY_PRIME, USE_PROTOCOL_PHY_PRIME_PORT},
#endif

#ifdef USE_PROTOCOL_MAC_PRIME_PORT
	{PROTOCOL_MAC_PRIME, USE_PROTOCOL_MAC_PRIME_PORT},
#endif

#ifdef USE_PROTOCOL_MLME_PRIME_PORT
	{PROTOCOL_MLME_PRIME, USE_PROTOCOL_MLME_PRIME_PORT},
#endif

#ifdef USE_PROTOCOL_PLME_PRIME_PORT
	{PROTOCOL_PLME_PRIME, USE_PROTOCOL_PLME_PRIME_PORT},
#endif

#ifdef USE_PROTOCOL_432_PRIME_PORT
	{PROTOCOL_432_PRIME, USE_PROTOCOL_432_PRIME_PORT},
#endif

#ifdef USE_PROTOCOL_DOM_CASA_PORT
	{PROTOCOL_DOM_CASA, USE_PROTOCOL_DOM_CASA_PORT},
#endif

#ifdef USE_PROTOCOL_PHY_MIMO_PORT
	{PROTOCOL_PHY_MIMO, USE_PROTOCOL_PHY_MIMO_PORT},
#endif

#ifdef USE_PROTOCOL_FUP_PORT
	{PROTOCOL_FUP, USE_PROTOCOL_FUP_PORT},
#endif

#ifdef USE_PROTOCOL_PRIME_DEBUG_PORT
	{PROTOCOL_PRIME_DEBUG, USE_PROTOCOL_PRIME_DEBUG_PORT},
#endif

#ifdef USE_PROTOCOL_BASEMNG_PORT
	{PROTOCOL_BASEMNG_PRIME, USE_PROTOCOL_BASEMNG_PORT},
#endif
#ifdef USE_PROTOCOL_PRIME_SERIAL_PORT
	{PROTOCOL_PRIME_SERIAL, USE_PROTOCOL_PRIME_SERIAL_PORT},
#endif
	{0xff, 0xff}
};
/* @} */

/* \name Por configuration for buffers */
/* @{ */
#undef CONF_PORT
#define CONF_PORT(type, channel, speed, tx_size, rx_size) rx_size
/* @} */

/* \name Reception buffers */
/* @{ */
#ifdef PORT_0
static uint8_t puc_rxbuf0[PORT_0];
#endif

#ifdef PORT_1
static uint8_t puc_rxbuf1[PORT_1];
#endif

#ifdef PORT_2
static uint8_t puc_rxbuf2[PORT_2];
#endif

#ifdef PORT_3
static uint8_t puc_rxbuf3[PORT_3];
#endif
/* @} */

/* \name Reception Buffers mapping */
/* @{ */
static map_buffers_t usi_rx_buf[NUM_PORTS + 1] = {
#ifdef PORT_0
	{0, &puc_rxbuf0[0]},
#endif
#ifdef PORT_1
	{0, &puc_rxbuf1[0]},
#endif
#ifdef PORT_2
	{0, &puc_rxbuf2[0]},
#endif
#ifdef PORT_3
	{0, &puc_rxbuf3[0]},
#endif
	{0xFF, NULL}
};
/* @} */

/* \name Port configuration for buffers */
/* @{ */
#undef CONF_PORT
#define CONF_PORT(type, channel, speed, tx_size, rx_size) tx_size
/* @} */

/* \name Transmission Buffers */
/* @{ */
#ifdef PORT_0
static uint8_t puc_txbuf0[PORT_0];
#endif
#ifdef PORT_1
static uint8_t puc_txbuf1[PORT_1];
#endif
#ifdef PORT_2
static uint8_t puc_txbuf2[PORT_2];
#endif
#ifdef PORT_3
static uint8_t puc_txbuf3[PORT_3];
#endif
/* @} */

/* \name Transmission Buffers mapping */
/* @{ */
static const map_buffers_t usi_tx_buf[NUM_PORTS + 1] = {
#ifdef PORT_0
	{PORT_0, &puc_txbuf0[0]},
#endif
#ifdef PORT_1
	{PORT_1, &puc_txbuf1[0]},
#endif
#ifdef PORT_2
	{PORT_2, &puc_txbuf2[0]},
#endif
#ifdef PORT_3
	{PORT_3, &puc_txbuf3[0]},
#endif
	{0xFF, NULL}
};
/* @} */

/* \name Transmission buffers size configuration */
/* @{ */
#define TXAUX_SIZE 0
#ifdef PORT_0
  #if (PORT_0 > TXAUX_SIZE)
    #undef TXAUX_SIZE
    #define TXAUX_SIZE     PORT_0
  #endif
#endif
#ifdef PORT_1
  #if (PORT_1 > TXAUX_SIZE)
    #undef TXAUX_SIZE
    #define TXAUX_SIZE     PORT_1
  #endif
#endif
#ifdef PORT_2
  #if (PORT_2 > TXAUX_SIZE)
    #undef TXAUX_SIZE
    #define TXAUX_SIZE     PORT_2
  #endif
#endif
#ifdef PORT_3
  #if (PORT_3 > TXAUX_SIZE)
    #undef TXAUX_SIZE
    #define TXAUX_SIZE     PORT_3
  #endif
#endif
/* @} */

static uint8_t puc_tx_aux_buf[TXAUX_SIZE + 2];
static const map_buffers_t usi_aux_tx_buf = {TXAUX_SIZE + 2, &puc_tx_aux_buf[0]};
static uint8_t puc_rx_aux_buf[TXAUX_SIZE + 2];
static const map_buffers_t usi_aux_rx_buf = {2 * TXAUX_SIZE + 2, &puc_rx_aux_buf[0]};

const map_ports_t *const usi_cfg_map_ports = &usiMapPorts[0];
const map_protocols_t *const usi_cfg_map_protocols = &usi_map_protocols[0];
const map_buffers_t *const usi_cfg_tx_buf = &usi_tx_buf[0];
const map_buffers_t *const usi_cfg_aux_rx_buf = &usi_aux_rx_buf;
const map_buffers_t *const usi_cfg_aux_tx_buf = &usi_aux_tx_buf;
map_buffers_t *const usi_cfg_rx_buf = &usi_rx_buf[0];

/**
 * \brief  This function extracts the port where the protocol is mapped to.
 *
 * \param    uc_p_type      Protocol Type
 *
 * \retval   USI_STATUS_PROTOCOL_NOT_FOUND       , if protocol is not found
 *           number of port for the protocol, otherwise
 */
static uint8_t _getPortFromProtocol(uint8_t uc_p_type)
{
	uint8_t i;

	for (i = 0; i < NUM_PROTOCOLS; i++) {
		if ((uc_p_type < 0x10) && (usi_cfg_map_protocols[i].uc_p_type == MNGP_PRIME_PROT)) {
			return usi_cfg_map_protocols[i].uc_port;
		}

		if (usi_cfg_map_protocols[i].uc_p_type == uc_p_type) {
			return usi_cfg_map_protocols[i].uc_port;
		}
	}

	return (uint8_t)USI_STATUS_PROTOCOL_NOT_FOUND;
}

/** \brief  This function decodes internal protocol messages.
 *
 * \param    uc_port_idx  Port on which message is received
 * \param    uc_cmd       Command identifier
 */
static void _cbInternalProtocol(uint8_t uc_port_idx, uint8_t uc_cmd)
{
	switch (uc_cmd) {
	case CMD_LOCK_PORT:
		usi_cfg_param[uc_port_idx].us_tx_block_timer = TX_BLOCK_TIMEOUT;
		break;

	case CMD_UNLOCK_PORT:
		usi_cfg_param[uc_port_idx].us_tx_block_timer = 0;
		break;

	default:
		break;
	}
}

/**
 * \brief  This function processes the complete received message.
 *
 * \param    uc_port  Port where message is received
 */
static uint8_t _process_msg(uint8_t uc_port)
{
	uint16_t us_len;
	uint8_t uc_type;
	uint8_t *puc_rx_buf;
	uint8_t uc_result = false;

	/* Get Reception buffer */
	puc_rx_buf = &usi_cfg_rx_buf[uc_port].puc_buf[0];

	/* Extract protocol */
	uc_type = TYPE_PROTOCOL(puc_rx_buf[TYPE_PROTOCOL_OFFSET]);

	/* Extract length */
	if ((uc_type == PROTOCOL_MAC_PRIME) || (uc_type == PROTOCOL_432_PRIME)) {
		/* Extract LEN using XLEN */
		us_len = XLEN_PROTOCOL(puc_rx_buf[LEN_PROTOCOL_HI_OFFSET], puc_rx_buf[LEN_PROTOCOL_LO_OFFSET], puc_rx_buf[XLEN_PROTOCOL_OFFSET]);
	} else {
		/* Extract LEN using LEN */
		us_len = LEN_PROTOCOL(puc_rx_buf[LEN_PROTOCOL_HI_OFFSET], puc_rx_buf[LEN_PROTOCOL_LO_OFFSET]);
	}

	/* Call decoding function depending on uc_type */
	switch (uc_type) {
	/* PRIME spec.v.1.3.E */
	case MNGP_PRIME_GETQRY:
	case MNGP_PRIME_GETRSP:
	case MNGP_PRIME_SET:
	case MNGP_PRIME_RESET:
	case MNGP_PRIME_REBOOT:
	case MNGP_PRIME_FU:
	case MNGP_PRIME_EN_PIBQRY:
	case MNGP_PRIME_EN_PIBRSP:
		uc_result = mngl_rcv_cmd(puc_rx_buf, us_len + 2);
		break;

	/* Atmel's serialized protocols */
	case PROTOCOL_ATPL230:
		uc_result = serial_if_api_parser(&puc_rx_buf[PAYLOAD_OFFSET], us_len);
		break;

	case PROTOCOL_SNIF_PRIME:
		uc_result = serial_if_sniffer_api_parser(&puc_rx_buf[PAYLOAD_OFFSET], us_len);
		break;

	case PROTOCOL_MAC_PRIME:
		uc_result = serial_if_mac_api_parser(&puc_rx_buf[PAYLOAD_OFFSET], us_len);
		break;

	case PROTOCOL_MLME_PRIME:
		uc_result = serial_if_mlme_api_parser(&puc_rx_buf[PAYLOAD_OFFSET], us_len);
		break;

	case PROTOCOL_PLME_PRIME:
		uc_result = serial_if_plme_api_parser(&puc_rx_buf[PAYLOAD_OFFSET], us_len);
		break;

	case PROTOCOL_432_PRIME:
		uc_result = serial_432_if_api_parser(&puc_rx_buf[PAYLOAD_OFFSET], us_len);
		break;

	case PROTOCOL_INTERNAL:
		_cbInternalProtocol(uc_port, puc_rx_buf[PAYLOAD_OFFSET]);
		uc_result = true;
		break;

	case PROTOCOL_BASEMNG_PRIME:
		uc_result = baseMng_receivedCmd(&puc_rx_buf[PAYLOAD_OFFSET], us_len);
		break;

	case PROTOCOL_PRIME_SERIAL:
		uc_result = phySerial_receivedCmd(&puc_rx_buf[PAYLOAD_OFFSET], us_len);
		break;

	case PROTOCOL_USER_DEFINED:
		uc_result = serial_if_user_def_api_parser(&puc_rx_buf[PAYLOAD_OFFSET], us_len);
		break;

	default:
		break;
	}

	return uc_result;
}

/**
 * \brief  This function processes received message
 *
 *  \param  uc_port   Communication Port
 *  \return true      if message is OK
 *          false     if message is not OK
 */
static uint8_t _doEoMsg(uint8_t uc_port)
{
	uint8_t *puc_tb;
	uint8_t uc_type;
	uint16_t us_count;
	uint16_t us_len;
	uint8_t *puc_rx_buf;
	uint32_t ul_rx_crc;
	uint32_t ul_ev_crc;

	/* Get buffer and number of bytes */
	us_count = usi_cfg_rx_buf[uc_port].us_size;
	puc_rx_buf = &usi_cfg_rx_buf[uc_port].puc_buf[0];
	if (us_count < 4) {    /* insufficient data */
		return false;
	}

	/* Extract length and protocol */
	us_len = LEN_PROTOCOL(puc_rx_buf[LEN_PROTOCOL_HI_OFFSET], puc_rx_buf[LEN_PROTOCOL_LO_OFFSET]);
	uc_type = TYPE_PROTOCOL(puc_rx_buf[TYPE_PROTOCOL_OFFSET]);

	/* Evaluate CRC depending on protocol */
	switch (uc_type) {
	case MNGP_PRIME_GETQRY:
	case MNGP_PRIME_GETRSP:
	case MNGP_PRIME_SET:
	case MNGP_PRIME_RESET:
	case MNGP_PRIME_REBOOT:
	case MNGP_PRIME_FU:
	case MNGP_PRIME_EN_PIBQRY:
	case MNGP_PRIME_EN_PIBRSP:
		/* Get received CRC 32 */
		puc_tb = &puc_rx_buf[us_count - 4];
		ul_rx_crc = (((uint32_t)puc_tb[0]) << 24) | (((uint32_t)puc_tb[1]) << 16) | (((uint32_t)puc_tb[2]) << 8) | ((uint32_t)puc_tb[3]);
		/* Correct length (exclude CRC) */
		usi_cfg_rx_buf[uc_port].us_size -= 4;
		/* Calculate CRC */
		ul_ev_crc = pcrc_calculate_prime_crc(puc_rx_buf, us_len + 2, PCRC_HT_USI, PCRC_CRC_TYPE_32); 
		break;

	case PROTOCOL_SNIF_PRIME:
	case PROTOCOL_BASEMNG_PRIME:
	case PROTOCOL_PRIME_SERIAL:
	case PROTOCOL_ATPL230:
	case PROTOCOL_USER_DEFINED:
		/* Get received CRC 16 */
		puc_tb = &puc_rx_buf[us_count - 2];
		ul_rx_crc = (((uint32_t)puc_tb[0]) << 8) | ((uint32_t)puc_tb[1]);
		/* Correct length (exclude CRC) */
		usi_cfg_rx_buf[uc_port].us_size -= 2;
		/* Calculate CRC */
		ul_ev_crc = pcrc_calculate_prime_crc(puc_rx_buf, us_len + 2, PCRC_HT_USI, PCRC_CRC_TYPE_16); 
		break;

	case PROTOCOL_MLME_PRIME:
	case PROTOCOL_PLME_PRIME:
		/* Get received CRC 8 */
		puc_tb = &puc_rx_buf[us_count - 1];
		ul_rx_crc = (uint32_t)puc_tb[0];
		/* Correct length (exclude CRC) */
		usi_cfg_rx_buf[uc_port].us_size -= 1;
		/* Calculate CRC */
		ul_ev_crc = pcrc_calculate_prime_crc(puc_rx_buf, us_len + 2, PCRC_HT_USI, PCRC_CRC_TYPE_8); 
		break;

	case PROTOCOL_MAC_PRIME: /* Length is up to 2Kb ... use XLEN field */
	case PROTOCOL_432_PRIME: /* Length is up to 2Kb ... use XLEN field */
		/* Get received CRC 8 */
		/* use XLEN */
		us_len = XLEN_PROTOCOL(puc_rx_buf[LEN_PROTOCOL_HI_OFFSET],
				puc_rx_buf[LEN_PROTOCOL_LO_OFFSET],
				puc_rx_buf[XLEN_PROTOCOL_OFFSET]);
		puc_tb = &puc_rx_buf[us_count - 1];
		ul_rx_crc = (uint32_t)puc_tb[0];
		/* Correct length (exclude CRC) */
		usi_cfg_rx_buf[uc_port].us_size -= 1;
		/* Calculate CRC */
		ul_ev_crc = pcrc_calculate_prime_crc(puc_rx_buf, us_len + 2, PCRC_HT_USI, PCRC_CRC_TYPE_8); 
		break;

	default:
		return false;
	}

	/* Return CRC ok or not */
	return (ul_rx_crc == ul_ev_crc);
}

/**
 * \brief     Encodes the escape characters and transmits the message
 *
 *  \param    uc_port_idx  Port to transmit through
 *  \param    msg       Pointer to data to be transmitted
 *
 *
 *  \return   Result of operation:  USI_OK: Sent
 *                                  USI_STATUS_TX_FAILED: Not sent
 */
static usi_status_t _usi_encode_and_send(uint8_t uc_port_idx, cmd_params_t *msg)
{
	uint32_t ul_crc;
	uint8_t *puc_tx_buf;
	uint8_t *puc_aux_tx_buf;
	uint8_t uc_cmd;
	uint32_t ul_idx_in_orig;
	uint32_t ul_idx_aux = 0;
	uint16_t us_put_chars = 0;
	uint8_t uc_delimiter = MSGMARK;
	uint8_t uc_escape    = ESCMARK;
	uint8_t uc_escaped_byte = 0;
	uint8_t *puc_next_token = NULL;
	uint8_t *puc_aux_next_token = NULL;
	uint32_t ul_size_coded = 0;
	uint8_t uc_p_type = msg->uc_p_type;
	uint16_t us_len_token = 0;
	uint16_t us_len = msg->us_len;
	uint16_t us_sent_chars;

	/* Get ptr to TxBuffer */
	puc_tx_buf = usi_cfg_tx_buf[uc_port_idx].puc_buf;
	puc_aux_tx_buf = usi_cfg_aux_tx_buf->puc_buf;

	/* Copy message to aux buffer including header */
	puc_aux_tx_buf[0] = LEN_HI_PROTOCOL(us_len);
	puc_aux_tx_buf[1] = LEN_LO_PROTOCOL(us_len) + TYPE_PROTOCOL(uc_p_type);
	memcpy(&puc_aux_tx_buf[2], msg->puc_buf, us_len);

	/* Adjust XLEN if uc_p_type is internal protocol */
	uc_cmd = puc_aux_tx_buf[CMD_PROTOCOL_OFFSET];
	if ((uc_p_type == PROTOCOL_432_PRIME) || (uc_p_type == PROTOCOL_MAC_PRIME)) {
		puc_aux_tx_buf[CMD_PROTOCOL_OFFSET] = LEN_EX_PROTOCOL(us_len) + CMD_PROTOCOL(uc_cmd);
	}

	/* Add 2 header bytes to LEN */
	us_len += 2;

	/* Calculate CRC */
	switch (uc_p_type) {
	case MNGP_PRIME_GETQRY:
	case MNGP_PRIME_GETRSP:
	case MNGP_PRIME_SET:
	case MNGP_PRIME_RESET:
	case MNGP_PRIME_REBOOT:
	case MNGP_PRIME_FU:
	case MNGP_PRIME_EN_PIBQRY:
	case MNGP_PRIME_EN_PIBRSP:
		ul_crc = pcrc_calculate_prime_crc(puc_aux_tx_buf, us_len, PCRC_HT_USI, PCRC_CRC_TYPE_32);
		puc_aux_tx_buf[us_len] = (uint8_t)(ul_crc >> 24);
		puc_aux_tx_buf[us_len + 1] = (uint8_t)(ul_crc >> 16);
		puc_aux_tx_buf[us_len + 2] = (uint8_t)(ul_crc >> 8);
		puc_aux_tx_buf[us_len + 3] = (uint8_t)ul_crc;
		us_len += 4;
		break;

	case PROTOCOL_SNIF_PRIME:
	case PROTOCOL_BASEMNG_PRIME:
	case PROTOCOL_PRIME_SERIAL:
	case PROTOCOL_ATPL230:
	case PROTOCOL_USER_DEFINED:
		ul_crc = pcrc_calculate_prime_crc(puc_aux_tx_buf, us_len, PCRC_HT_USI, PCRC_CRC_TYPE_16);
		puc_aux_tx_buf[us_len] = (uint8_t)(ul_crc >> 8);
		puc_aux_tx_buf[us_len + 1] = (uint8_t)(ul_crc);
		us_len += 2;
		break;

	case PROTOCOL_MAC_PRIME:
	case PROTOCOL_MLME_PRIME:
	case PROTOCOL_PLME_PRIME:
	case PROTOCOL_432_PRIME:
	case PROTOCOL_INTERNAL:
	default:
		ul_crc = pcrc_calculate_prime_crc(puc_aux_tx_buf, us_len, PCRC_HT_USI, PCRC_CRC_TYPE_8);
		puc_aux_tx_buf[us_len] = (uint8_t)(ul_crc);
		us_len += 1;
		break;
	}

	/* Fill tx buffer adding required escapes */
	ul_idx_in_orig = usi_cfg_param[uc_port_idx].us_idx_in;

	ul_size_coded = us_len + 2 /* for MSGMARKs */;
	/* Check if there is still room */
	if (ul_idx_in_orig + ul_size_coded > usi_cfg_tx_buf[uc_port_idx].us_size) {
		/* No Room. Return error */
		return USI_STATUS_TX_BUFFER_OVERFLOW;
	}

	/* Start Escape */
	puc_tx_buf[usi_cfg_param[uc_port_idx].us_idx_in++] = MSGMARK;
	us_put_chars++;

	while (us_len) {
		/* Look for the next MSGMARK present within the data */
		puc_next_token = memchr(&puc_aux_tx_buf[ul_idx_aux], uc_delimiter, us_len);
		if (puc_next_token == NULL) {
			/* MSGMARK not found -> look for the next ESCMARK
			 * present within the data */
			puc_next_token = memchr(&puc_aux_tx_buf[ul_idx_aux], uc_escape, us_len);
			if (puc_next_token != NULL) {
				uc_escaped_byte = ESC_ESCMARK;
			}
		} else {
			/* Check if there is an ESCMARK before the MSGMARK */
			puc_aux_next_token = memchr(&puc_aux_tx_buf[ul_idx_aux], uc_escape, puc_next_token - &puc_aux_tx_buf[ul_idx_aux]);
			if (puc_aux_next_token != NULL) {
				uc_escaped_byte = ESC_ESCMARK;
				puc_next_token = puc_aux_next_token;
			} else {
				uc_escaped_byte = ESC_MSGMARK;
			}
		}

		/* Perform the codification of the MSGMARK or the ESCMARK */
		if (puc_next_token != NULL) {
			ul_size_coded++;

			/* Check if there is still room */
			if (ul_idx_in_orig + ul_size_coded > usi_cfg_tx_buf[uc_port_idx].us_size) {
				/* No Room. Reset index and return error */
				return USI_STATUS_TX_BUFFER_OVERFLOW;
			}

			us_len_token = puc_next_token - &puc_aux_tx_buf[ul_idx_aux];

			/* Copy the part without special bytes into the tx buf */
			memcpy(&puc_tx_buf[usi_cfg_param[uc_port_idx].us_idx_in], &puc_aux_tx_buf[ul_idx_aux], us_len_token);
			us_len -= us_len_token + 1;
			ul_idx_aux += us_len_token + 1;
			usi_cfg_param[uc_port_idx].us_idx_in += us_len_token;

			/* Encode the special character */
			puc_tx_buf[usi_cfg_param[uc_port_idx].us_idx_in++] = ESCMARK;
			puc_tx_buf[usi_cfg_param[uc_port_idx].us_idx_in++] = uc_escaped_byte;
			us_put_chars += us_len_token + 2;
		} else { 
			memcpy(&puc_tx_buf[usi_cfg_param[uc_port_idx].us_idx_in], &puc_aux_tx_buf[ul_idx_aux], us_len);
			usi_cfg_param[uc_port_idx].us_idx_in += us_len;
			us_put_chars += us_len;
			us_len = 0;
		}
	}

	puc_tx_buf[usi_cfg_param[uc_port_idx].us_idx_in++] = MSGMARK;
	us_put_chars++;

	/* Message ready to be sent */
	us_len = usi_cfg_param[uc_port_idx].us_idx_in;

	/* Check if there is something to transmit */
	if (usi_cfg_param[uc_port_idx].us_tx_block_timer == 0) {
		while (usi_cfg_param[uc_port_idx].us_idx_in) {
			/* Send chars to device, checking how many have been really processed by device */
			if (usi_cfg_map_ports[uc_port_idx].uc_s_type == UART_TYPE) {
				us_sent_chars = buart_if_write(usi_cfg_map_ports[uc_port_idx].uc_chn, usi_cfg_tx_buf[uc_port_idx].puc_buf, us_len);
			} else if (usi_cfg_map_ports[uc_port_idx].uc_s_type == USART_TYPE) {
				us_sent_chars = busart_if_write(usi_cfg_map_ports[uc_port_idx].uc_chn, usi_cfg_tx_buf[uc_port_idx].puc_buf, us_len);
			} else {
				us_sent_chars = us_len; /* Port wrongly mapped */
			}

			if (us_sent_chars > 0) {
				/* Adjust buffer values depending on sent chars */
				usi_cfg_param[uc_port_idx].us_idx_in -= us_sent_chars;
			} else {
				/* USI_ERROR: UART/USART error */
				return USI_STATUS_UART_ERROR;
			}
		}
	} else {
		/* USI_ERROR: TX blocked */
		return USI_STATUS_TX_BLOCKED;
	}

	return USI_STATUS_OK;
}

/** \brief   Decodes the escape sequences and copies the result into the
 *           destination buffer.
 *
 *  \param   puc_dest  pointer to the destination buffer
 *  \param   puc_orig  pointer to the source buffer
 *  \param   us_size   size of the data to process
 *
 *  \return  Length of the decoded array,
 *           -1 if error.
 */
static uint16_t _decode_copy(uint8_t *puc_dest, uint8_t *puc_orig, uint16_t us_size)
{
	uint16_t i = 0;
	uint16_t j = 0;

	while (i < us_size) {
		if (puc_orig[i] == ESCMARK) {
			/* If the escaped byte is the MSGMARK, */
			/* copy it to the destination buffer */
			if (puc_orig[i + 1] == ESC_MSGMARK) {
				puc_dest[j++] = MSGMARK;
				i += 2;
			} else if (puc_orig[i + 1] == ESC_ESCMARK) {
				puc_dest[j++] = ESCMARK;
				i += 2;
			} else { /* Error: unknown escaped character */
				return (uint16_t)USI_STATUS_FORMAT_ERROR;
			}
		} else {
			 /* No escape mark */
			puc_dest[j++] = puc_orig[i];
			i++;
		}
	}

	return(j);
}

/**
 * \brief Function that updates the USI flow control timers.
 */
void usi_txrx_block_timer(void)
{
	uint8_t i;

	for (i = 0; i < NUM_PORTS; i++) {
		if (usi_cfg_param[i].us_rx_block_timer) {
			usi_cfg_param[i].us_rx_block_timer--;
		}

		if (usi_cfg_param[i].us_tx_block_timer) {
			usi_cfg_param[i].us_tx_block_timer--;
		}
	}
}

/**
 * \brief Function to perform the USI RX process.
 */
void usi_process(void)
{
	uint8_t i;
	int nr_ch = 0;
	uint8_t uc_delimiter = MSGMARK;
	uint8_t *puc_next_token;
	uint8_t *puc_rx_aux;
	uint16_t us_token_size;

	/* Check reception on every port */
	for (i = 0; i < NUM_PORTS; i++) {
		puc_rx_aux = &usi_cfg_aux_rx_buf[i].puc_buf[0];

		/* Read all the data in the respective buffer (UART or USART) */
		if (usi_cfg_map_ports[i].uc_s_type == UART_TYPE) {
			nr_ch = buart_if_read(usi_cfg_map_ports[i].uc_chn, puc_rx_aux,
					usi_cfg_map_ports[i].us_rx_size);
		} else if (usi_cfg_map_ports[i].uc_s_type == USART_TYPE) {
			nr_ch = busart_if_read(usi_cfg_map_ports[i].uc_chn, puc_rx_aux,
					usi_cfg_map_ports[i].us_rx_size);
		}

		/* Go through the received data */
		while (nr_ch > 0) {
			/* Process received data */
			puc_next_token = memchr(puc_rx_aux, uc_delimiter, nr_ch);

			/* If token found */
			if (puc_next_token != NULL) {
				/* Update token size */
				us_token_size = (puc_next_token - puc_rx_aux);

				/* Skip the MSGMARK(s) */
				if (us_token_size == 0) {
					puc_rx_aux++;
					nr_ch--;
					uc_message_status = 1 - uc_message_status;

					/* Corner case: the data starts with two MSGMARKs: one to close
					 * the previously received incomplete message, and the following
					 * to start a new one. */
					if ((uc_message_status == MSG_END) && (usi_cfg_rx_buf[i].us_size > 0)) {
						if (puc_rx_aux[0] == MSGMARK) {
							if (_doEoMsg(i)) {
								/* CRC is OK: process the message */
								if (_process_msg(i)) {
									if (usi_cfg_param[i].us_rx_block_timer != 0) {
										/* Send internal command CMD_UNLOCK_PORT */
										internal_command.puc_buf = &uc_int_cmd_unlock;
										if (_usi_encode_and_send(i, &internal_command)) {
											usi_cfg_param[i].us_rx_block_timer = 0;
										}
									}
								} else {
									if (usi_cfg_param[i].us_rx_block_timer == 0) {
										/* Send internal command CMD_LOCK_PORT */
										internal_command.puc_buf = &uc_int_cmd_lock;
										if (_usi_encode_and_send(i, &internal_command)) {
											usi_cfg_param[i].us_rx_block_timer = RX_BLOCK_TIMEOUT;
										}
									}
								}
							}
						} else { 
							/* The next byte is not a MSGMARK: the incomplete data in 
							 * puc_rx_buf is discarded */
							uc_message_status = 1 - uc_message_status;
						}

						/* Update the buffer pointers and sizes */
						usi_cfg_rx_buf[i].us_size = 0;
						puc_rx_aux += us_token_size;
						nr_ch -= us_token_size;
					}
				} else {
					/* If a message or part of an incomplete message is expected */
					if (uc_message_status == MSG_START) {
						/* Compose the whole message */
						usi_cfg_rx_buf[i].us_size += _decode_copy(&usi_cfg_rx_buf[i].puc_buf[0] + usi_cfg_rx_buf[i].us_size,
								puc_rx_aux, us_token_size);

						/* Calculate CRC */
						if (_doEoMsg(i)) {
							/* CRC is OK: process the message */
							if (_process_msg(i)) {
								/* If port was previously blocked, send message to indicate 
								 * that now it is open. */
								if (usi_cfg_param[i].us_rx_block_timer != 0) {
									/* Send  internal command CMD_UNLOCK_PORT */
									internal_command.puc_buf = &uc_int_cmd_unlock;
									if (_usi_encode_and_send(i, &internal_command)) {
										/* If sent, change block status so message is not
										 * sent again. */
										usi_cfg_param[i].us_rx_block_timer = 0;
									}
								}
							} else {
								/* Message could not be processed. Send Flow Control message
								 * to block port. */
								if (usi_cfg_param[i].us_rx_block_timer == 0) {
									/* Send internal command CMD_LOCK_PORT */
									internal_command.puc_buf = &uc_int_cmd_lock;
									if (_usi_encode_and_send(i, &internal_command)) {
										/* If sent, change block status so message is not
										 * sent again. */
										usi_cfg_param[i].us_rx_block_timer = RX_BLOCK_TIMEOUT;
									}
								}
							}
						}
					} else {
						/* USI protocol error: discard */
					}

					/* Update the buffer pointers and sizes */
					usi_cfg_rx_buf[i].us_size = 0;
					puc_rx_aux += us_token_size;
					nr_ch -= us_token_size;
				}
			} /* end if (puc_next_token != NULL) */
			else { /* No token found */
				if (uc_message_status == MSG_START) {
					usi_cfg_rx_buf[i].us_size
						+= _decode_copy(&usi_cfg_rx_buf[i].puc_buf[0] + usi_cfg_rx_buf[i].us_size,
							puc_rx_aux, nr_ch);
				} else {
					/* USI protocol error: discard */
				}

				nr_ch = 0;
			}
		} /* end while (nr_ch > 0) */
	} /* end for (i = 0; i < NUM_PORTS; i++) */
}

/**
 * \brief Create RX and TX USI tasks, and timer to update internal counters.
 */
void usi_init(void)
{
	uint8_t i;

	/* Initialize Universal Serial Interface and start ports */
	for (i = 0; i < NUM_PORTS; i++) {
		/* Init Rx Parameters */
		usi_cfg_param[i].us_rx_block_timer = 0;

		/* Init Tx Parameters */
		usi_cfg_param[i].us_idx_in = 0;
		usi_cfg_param[i].us_tx_block_timer = 0;

		/* Start USI port */
		if (usi_cfg_map_ports[i].uc_s_type == UART_TYPE) {
			buart_if_open(usi_cfg_map_ports[i].uc_chn, usi_cfg_map_ports[i].ul_speed);
		} else if (usi_cfg_map_ports[i].uc_s_type == USART_TYPE) {
			busart_if_open(usi_cfg_map_ports[i].uc_chn, usi_cfg_map_ports[i].ul_speed);
		}
	}

	/* USI internal command structure initialization */
	internal_command.us_len = INTERNAL_MSG_LEN;
	internal_command.uc_p_type = PROTOCOL_INTERNAL;

	/* USI message boundary control flag initialization */
	uc_message_status = MSG_END;
}

/** @brief  Function to transmit data through USI
 *
 *  @param    msg    Pointer to message to be transmitted.
 *
 *  @return   USI operation result
 */
usi_status_t usi_send_cmd(void *msg)
{
	uint8_t uc_port_idx;
	uint16_t us_available_len;

	uint8_t uc_p_type = ((cmd_params_t *)msg)->uc_p_type;
	uint16_t us_len = ((cmd_params_t *)msg)->us_len;

	/* Get port index from protocol */
	uc_port_idx = _getPortFromProtocol(uc_p_type);
	if (uc_port_idx == USI_STATUS_PROTOCOL_NOT_FOUND) {
		return USI_STATUS_PROTOCOL_NOT_FOUND;
	}

	/* Check if TX flow control blocking is active */
	if (usi_cfg_param[uc_port_idx].us_tx_block_timer != 0) {
		return USI_STATUS_RX_BLOCKED;
	}

	/* Get available length in buffer */
	us_available_len = usi_cfg_tx_buf[uc_port_idx].us_size - usi_cfg_param[uc_port_idx].us_idx_in;

	/* First checking, available length at least equal to minimum required space */
	if (us_available_len < (us_len + MIN_OVERHEAD)) {
		return USI_STATUS_RX_BUFFER_OVERFLOW;
	}

	return (_usi_encode_and_send(uc_port_idx, (cmd_params_t *)msg));
}

/**
 * \brief Dummy serialization function.
 */
uint8_t Dummy_serial_parser(uint8_t *puc_rx_msg, uint16_t us_len)
{
	UNUSED(puc_rx_msg);
	UNUSED(us_len);

	return(0);
}

/* @} */

/* / @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/* / @endcond */
