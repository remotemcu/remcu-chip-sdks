/**
 * \file
 *
 * \brief Atmel Data Visualizer tool support routines
 *
 * This file contains routines for using the Atmel Data Visualizer
 * tool.  Various functions and structure definitions provide initialization,
 * data formatting, and actual transmission of application data to a remote
 * host for display.
 *
 * The Atmel Data Visualizer (ADV) tool is a standalone Windows application
 * that provides a graphical display of data sent from a remote target.  It
 * is available as a separate download.  For more information on downloading
 * and installing the ADV tool, visit
 * <a href="http://www.microchip.com/mplab/avr-support/data-visualizer">Atmel
 *Data Visualizer</a>
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
#include <stdlib.h>
#include <asf.h>
#include "data_visualizer.h"

#define PKT_XMIT_DELAY  2       /* delay after sending ADV packet (msec) */

COMPILER_PACK_SET(1)            /* pack all structures (no padding) */

/*! \brief Write data buffer via USB or serial port.
 *
 * This application uses a serial or USB connection to transmit sensor data.
 * This routine takes the specified input buffer and writes each byte to
 * the appropriate output device.
 *
 * \param   buffer    The address of a buffer containing the data to transmit
 * \param   num_bytes The number of bytes to transmit
 *
 * \return  Nothing.
 */
void adv_write_buf(uint8_t *buffer, int num_bytes)
{
#if UC3
#  if UC3L
	/* Use regular USART stdio output */

	/* Transmit each character */
	while (num_bytes-- > 0) {
		putchar(*buffer++);         /* write char via usart */
	}

#  else
	/* Use internal USB controller (CDC device) */

	/* Check if USB ready to transmit */
	if (!(udi_cdc_is_tx_ready())) {
		return;
	}

	/* Transmit each character */
	while (num_bytes-- > 0) {
		udi_cdc_putc(*buffer++);         /* write char via USB CDC
		                                  * device */
	}
#  endif

#elif XMEGA
	/* Transmit each character */
	while (num_bytes-- > 0) {
		putchar(*buffer++);         /* write char via usart */
	}
#endif

	/* Delay to allow all bytes to output */
	delay_ms(PKT_XMIT_DELAY);

	return;
}

/*! \brief  Send data visualizer data packet with 1 data field
 *
 * This routine constructs a data visualizer data packet with one data value
 * field and then transmits it.  All multi-byte transmitted values
 * use little endian byte order.
 *
 * \param   stream_num  The ID number of the visualizer data stream
 * \param   timestamp   A 32-bit timestamp value, in microseconds
 * \param   value       The data value to include in the transmitted packet
 */
void adv_data_send_1(uint8_t stream_num, uint32_t timestamp, int32_t value)
{
	/* Define packet format with 1 data field */
	struct {
		adv_data_start_t start;       /* Starting fields of packet */
		adv_data_field_t field;       /* 1 data field */
		adv_data_end_t end;           /* Ending fields of packet */
	} packet;

	/* Construct packet */
	packet.start.header1 = ADV_PKT_HEADER_1;
	packet.start.header2 = ADV_PKT_HEADER_2;
	packet.start.length  = cpu_to_le16(sizeof(packet));
	packet.start.type    = ADV_PKT_DATA;
	packet.start.stream_num = stream_num;
	packet.start.time_stamp = cpu_to_le32(timestamp);

	packet.field.value = cpu_to_le32(value);

	packet.end.crc = 0x00; /* Not used */
	packet.end.mark = ADV_PKT_END;

	/* Write packet */
	adv_write_buf((uint8_t*)&packet, sizeof(packet));
}

/*! \brief  Send data visualizer data packet w/ 3 data fields
 *
 * This routine constructs a data visualizer data packet with three data
 * value fields and then transmits it.  All multi-byte transmitted values
 * use little endian byte order.
 *
 * \param   stream_num  The ID number of the visualizer data stream
 * \param   timestamp   A 32-bit timestamp value, in microseconds
 * \param   value0      Data field 0 value
 * \param   value1      Data field 1 value
 * \param   value2      Data field 2 value
 */
void adv_data_send_3(uint8_t stream_num, uint32_t timestamp,
		int32_t value0, int32_t value1, int32_t value2)
{
	/* Define packet format with 3 data fields */
	struct {
		adv_data_start_t start;       /* Starting fields of packet */
		adv_data_field_t field [3];   /* 3 data fields */
		adv_data_end_t end;           /* Ending fields of packet */
	} packet;

	/* Construct packet */
	packet.start.header1 = ADV_PKT_HEADER_1;
	packet.start.header2 = ADV_PKT_HEADER_2;
	packet.start.length  = cpu_to_le16(sizeof(packet));
	packet.start.type    = ADV_PKT_DATA;
	packet.start.stream_num = stream_num;
	packet.start.time_stamp = cpu_to_le32(timestamp);

	packet.field[0].value = cpu_to_le32(value0);
	packet.field[1].value = cpu_to_le32(value1);
	packet.field[2].value = cpu_to_le32(value2);

	packet.end.crc = 0x00;  /* Not used */
	packet.end.mark = ADV_PKT_END;

	/* Write packet */
	adv_write_buf((uint8_t *)&packet, sizeof(packet));
}
