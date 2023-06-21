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

#include <asf.h>
#include <string.h>
#include "iot/stream_writer.h"

void stream_writer_init(struct stream_writer * writer, char *buffer, size_t max_length, stream_writer_write_func_t func, void *priv_data)
{
	writer->max_size = max_length;
	writer->buffer = buffer;
	writer->written = 0;
	writer->write_func = func;
	writer->priv_data = priv_data;
}

void stream_writer_send_8(struct stream_writer * writer, int8_t value)
{
	int remain = writer->max_size - writer->written;
	
	if (remain < 1) {
		stream_writer_send_remain(writer);
	}
	
	writer->buffer[writer->written++] = (char)value;
}

void stream_writer_send_16BE(struct stream_writer * writer, int16_t value)
{
	stream_writer_send_8(writer, (value >> 8) & 0xFF);
	stream_writer_send_8(writer, value & 0xFF);
}

void stream_writer_send_16LE(struct stream_writer * writer, int16_t value)
{
	stream_writer_send_8(writer, value & 0xFF);
	stream_writer_send_8(writer, (value >> 8) & 0xFF);
}	

void stream_writer_send_32BE(struct stream_writer * writer, int32_t value)
{
	stream_writer_send_8(writer, (value >> 24) & 0xFF);
	stream_writer_send_8(writer, (value >> 16) & 0xFF);
	stream_writer_send_8(writer, (value >> 8) & 0xFF);
	stream_writer_send_8(writer, value & 0xFF);
}

void stream_writer_send_32LE(struct stream_writer * writer, int32_t value)
{
	stream_writer_send_8(writer, value & 0xFF);
	stream_writer_send_8(writer, (value >> 8) & 0xFF);
	stream_writer_send_8(writer, (value >> 16) & 0xFF);
	stream_writer_send_8(writer, (value >> 24) & 0xFF);
}

void stream_writer_send_buffer(struct stream_writer * writer, const char *buffer, size_t length)
{
	for (; length > 0; length--, buffer++) {
		stream_writer_send_8(writer, *buffer);
	}
}

void stream_writer_send_remain(struct stream_writer * writer)
{
	if(writer->written > 0) {
		writer->write_func(writer->priv_data, writer->buffer, writer->written);
		writer->written = 0;
	}
}
