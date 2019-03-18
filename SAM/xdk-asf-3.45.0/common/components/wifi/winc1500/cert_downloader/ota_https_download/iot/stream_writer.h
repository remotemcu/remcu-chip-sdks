/**
 * \file
 *
 * \brief Stream utility for the IoT service.
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef STREAM_WRITTER_H_INCLUDED
#define STREAM_WRITTER_H_INCLUDED

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*stream_writer_write_func_t)(void *module, char *buffer, size_t buffer_len);

struct stream_writer {
	size_t max_size;
	size_t written;
	stream_writer_write_func_t write_func;
	void *priv_data;
	char *buffer;
};

/**
 * \brief Initialize the Stream writer module.
 *
 * \param[in]  writer          Pointer of stream writer.
 * \param[in]  buffer          Buffer which will be used for the storing the data.
 * \param[in]  max_length      Maximum size of buffer.
 * \param[in]  func            Function to be called when the buffer is full.
 * \param[in]  priv_data       Private data. It is passed along when callback was called.
 */
void stream_writer_init(struct stream_writer * writer, char *buffer, size_t max_length, stream_writer_write_func_t func, void *priv_data);

/**
 * \brief Write 8bit to the writer.
 *
 * \param[in]  writer          Pointer of stream writer.
 * \param[in]  value           Value will be written.
 */
void stream_writer_send_8(struct stream_writer * writer, int8_t value);

/**
 * \brief Write 16bit big endian value to the writer.
 *
 * \param[in]  writer          Pointer of stream writer.
 * \param[in]  value           Value will be written.
 */
void stream_writer_send_16BE(struct stream_writer * writer, int16_t value);

/**
 * \brief Write 16bit little endian value to the writer.
 *
 * \param[in]  writer          Pointer of stream writer.
 * \param[in]  value           Value will be written.
 */
void stream_writer_send_16LE(struct stream_writer * writer, int16_t value);

/**
 * \brief Write 32bit big endian value to the writer.
 *
 * \param[in]  writer          Pointer of stream writer.
 * \param[in]  value           Value will be written.
 */
void stream_writer_send_32BE(struct stream_writer * writer, int32_t value);

/**
 * \brief Write 32bit little endian value to the writer.
 *
 * \param[in]  writer          Pointer of stream writer.
 * \param[in]  value           Value will be written.
 */
void stream_writer_send_32LE(struct stream_writer * writer, int32_t value);

/**
 * \brief Write buffer to the writer.
 *
 * \param[in]  writer          Pointer of stream writer.
 * \param[in]  buffer          Buffer will be written.
 * \param[in]  length          Size of the buffer.
 */
void stream_writer_send_buffer(struct stream_writer * writer, const char *buffer, size_t length);

/**
 * \brief Process remain data in the writer.
 *
 * \param[in]  writer          Pointer of stream writer.
 */
void stream_writer_send_remain(struct stream_writer * writer);


#ifdef __cplusplus
}
#endif

#endif /* STREAM_WRITTER_H_INCLUDED */