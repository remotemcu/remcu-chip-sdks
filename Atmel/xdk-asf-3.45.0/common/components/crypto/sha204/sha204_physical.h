/*
 * \file
 *
 * \brief ATSHA204 header file for the I2C layer for the device
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

#ifndef SHA204_PHYSICAL_H
#   define SHA204_PHYSICAL_H

#include "sha204_config.h"                           //!< configuration values

#define SHA204_RSP_SIZE_MIN          ((uint8_t)  4)  //!< minimum number of bytes in response
#define SHA204_RSP_SIZE_MAX          ((uint8_t) 35)  //!< maximum size of response packet

#define SHA204_BUFFER_POS_COUNT      (0)             //!< buffer index of count byte in command or response
#define SHA204_BUFFER_POS_DATA       (1)             //!< buffer index of data in response

//! delay between Wakeup pulse and communication in ms
#define SHA204_WAKEUP_DELAY          (3)
/**
 * \defgroup sha204_communication_physical_group SHA204 Service - hardware dependent communication functions
 *
 * @{
 */
void    sha204p_init(void);
void    sha204p_set_device_id(uint8_t id);
uint8_t sha204p_send_command(uint8_t count, uint8_t *command);
uint8_t sha204p_receive_response(uint8_t size, uint8_t *response);
uint8_t sha204p_wakeup(void);
uint8_t sha204p_idle(void);
uint8_t sha204p_sleep(void);
uint8_t sha204p_reset_io(void);
uint8_t sha204p_resync(uint8_t size, uint8_t *response);
//! @}

#endif
