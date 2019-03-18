/*
 * \file
 *
 * \brief ATSHA204 header file for the communication layer for the device
 *
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef SHA204_COMM_H
#   define SHA204_COMM_H

#include <compiler.h>               //!< compiler dependent definitions

#include "sha204_physical.h"        //!< declarations that are common to all interface implementations

//! maximum command delay
#define SHA204_COMMAND_EXEC_MAX      (69)

//! minimum number of bytes in command (from count byte to second CRC byte)
#define SHA204_CMD_SIZE_MIN          ((uint8_t)  7)

//! maximum size of command packet (CheckMac)
#define SHA204_CMD_SIZE_MAX          ((uint8_t) 84)

//! number of CRC bytes
#define SHA204_CRC_SIZE              ((uint8_t)  2)

//! buffer index of status byte in status response
#define SHA204_BUFFER_POS_STATUS     (1)

//! buffer index of first data byte in data response
#define SHA204_BUFFER_POS_DATA       (1)

//! status byte after wake-up
#define SHA204_STATUS_BYTE_WAKEUP    ((uint8_t) 0x11)

//! command parse error
#define SHA204_STATUS_BYTE_PARSE     ((uint8_t) 0x03)

//! command execution error
#define SHA204_STATUS_BYTE_EXEC      ((uint8_t) 0x0F)

//! communication error
#define SHA204_STATUS_BYTE_COMM      ((uint8_t) 0xFF)

/** 
 * \brief This structure contains the parameters for the \ref sha204c_send_and_receive function.
 */
struct sha204_send_and_receive_parameters {
	uint8_t *tx_buffer;         //!< pointer to send buffer
	uint8_t rx_size;            //!< size of receive buffer
	uint8_t *rx_buffer;         //!< pointer to receive buffer
	uint8_t poll_delay;         //!< how long to wait before polling for response-ready
	uint8_t poll_timeout;       //!< how long to poll before timing out
};

/**
 * \defgroup sha204_communication_group SHA204 Service - hardware independent communication functions
 * @{
 */
void sha204c_calculate_crc(uint8_t length, uint8_t *data, uint8_t *crc);
uint8_t sha204c_wakeup(uint8_t *response);
uint8_t sha204c_send_and_receive(struct sha204_send_and_receive_parameters *args);
//! @}

#endif
