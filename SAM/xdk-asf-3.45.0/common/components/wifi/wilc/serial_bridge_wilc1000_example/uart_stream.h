/**
 * \file
 *
 * \brief Configurations for the WILC1000 Serial Bridge Application
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef USART_STREAM_H_INCLUDED
#define USART_STREAM_H_INCLUDED

#include <inttypes.h>
#include <asf.h>

#define USART_BUFFER_MAX (2 * 1024)

/**
 * \brief Initialize USART module.
 *
 * \param baud_rate Baudrate of USART.
 */
void configure_usart(uint32_t baud_rate);

/**
 * \brief Clear USART buffer and flush USART module.
 */
void usart_stream_reset(void);

/**
 * \brief Write one byte of data.
 *
 * \param data Data to send.
 */
void usart_stream_write(uint8_t data);

/**
 * \brief Write multiple bytes of data.
 *
 * \param data Pointer to data to send.
 * \param size Size of data.
 */
void usart_stream_write_buffer(uint8_t *data, uint32_t size);

/**
 * \brief Read data from USART module.
 *
 * \param data Pointer to USART buffer.
 * \param data Pointer to USART buffer size.
 */
int usart_stream_read(uint8_t **data, uint32_t *size);

/**
 * \brief Move back USART buffer.
 *
 * \param offset Size of data to remove.
 */
void usart_stream_move(uint32_t offset);

#endif /* USART_STREAM_H_INCLUDED */
