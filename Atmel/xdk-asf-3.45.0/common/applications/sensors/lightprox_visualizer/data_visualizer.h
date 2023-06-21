/**
 * \file
 *
 * \brief Atmel Data Visualizer definitions
 *
 * This file contains various definitions related to applications producing
 * data streams expected by the Atmel Data Visualizer tool.
 *
 * The Atmel Data Visualizer (ADV) tool is a standalone Windows application
 * that provides a graphical display of data sent from a remote target.  It
 * is available as a separate download.  For more information on downloading
 * and installing the ADV tool, visit 
 * <A href="http://www.microchip.com/mplab/avr-support/data-visualizer">Atmel Data Visualizer</A>
 *
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


#ifndef _data_visualizer_h_
#define _data_visualizer_h_

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>



// Symbol Definitions

#define FIELD_FORMAT_SIGNED       1       // data field is signed integer
#define FIELD_FORMAT_UNSIGNED     2       // data field is unsigned integer
#define FIELD_FORMAT_FLOAT        3       // data field is floating point

#define STREAM_NAME_LEN     25      // length of stream name (incl. null term.)
#define FIELD_UNIT_LEN      20      // length of field.units (incl. null)
#define FIELD_NAME_LEN      11      // length of field name (incl. null)

#define ADV_PKT_HEADER_1  0xFF    // first byte of header sequence
#define ADV_PKT_HEADER_2  0x5A    // second byte of header sequence
#define ADV_PKT_END       0x06    // 8-bit end-of-packet value

#define ADV_PKT_CONFIG_START      0x01    // config start packet
#define ADV_PKT_CONFIG_END        0x02    // config start packet
#define ADV_PKT_CONFIG_STREAM     0x03    // stream config packet
#define ADV_PKT_CONFIG_FIELD      0x04    // data field config packet
#define ADV_PKT_DATA              0x05    // data packet



// Data Structure Definitions

COMPILER_PACK_SET(1)        // pack structures (1-byte align all fields)


//! \brief Atmel Data Visualizer start-of-configuration packet
//
// This packet type is sent to indicate the beginning of a series of
// configuration packets.  After this packet is sent, one more
// stream configuration packet (adv_config_stream_t) will be sent for
// each logical stream to be displayed, and one or more data field
// configuration packets (adv_data_field_t) will be sent for each 
// stream.
//
typedef struct {
	uint8_t         header1;        // header bytes - always 0xFF5A
	uint8_t         header2;        // header bytes - always 0xFF5A
	uint16_t        length;         // packet length (bytes)
	uint8_t         type;           // packet type
	uint8_t         num_streams;    // total number of data streams to follow
	uint8_t         crc;            // 8-bit checksum
	uint8_t         mark;           // 1-byte end-of-packet marker
} adv_config_start_t;



//! \brief Atmel Data Visualizer data stream configuration packet
//
// This packet type is used during configuration of the Atmel Data Visualizer
// to describe a logical data stream that will be used.  
//
// The packet includes a name string that will be used in the
// ADV display tool to label the display of the stream.
//
// Each logical stream contains one or more data fields.  The number
// of data fields to be used for this stream is specified in this packet.
// Each data field must be separately described in subsequent 
// adv_config_field_t packets, which must immediately follow the transmission
// of this stream configuration packet.
//
typedef struct {
	uint8_t         header1;        // header bytes - always 0xFF5A
	uint8_t         header2;        // header bytes - always 0xFF5A
	uint16_t        length;         // packet length (bytes)
	uint8_t         type;           // packet type
	uint8_t         stream_num;     // stream number (to match later data pkts)
	uint32_t        tick_res;       // timer tick resolution (Hz)
	uint8_t         num_fields;     // number of data fields per data packet
	char            stream_name[STREAM_NAME_LEN];
	                                // stream name (w/ null terminator)
	uint8_t         crc;            // 8-bit checksum
	uint8_t         mark;           // 1-byte end-of-packet marker
} adv_config_stream_t;


//! \brief Atmel Data Visualizer data field configuration packet
//
// This packet type is used during configuration of the Atmel Data Visualizer
// to describe a single data field that will be transmitted inside subsequent
// data packets.  The packet includes strings that will be used in the
// ADV display tool to label the display of the corresponding data element.
// The minimum and maximum values to be displayed are also provided, along
// with information about the numeric representation format.
//
typedef struct {
	uint8_t         header1;        // header bytes - always 0xFF5A
	uint8_t         header2;        // header bytes - always 0xFF5A
	uint16_t        length;         // packet length (bytes)
	uint8_t         type;           // packet type
	uint8_t         stream_num;     // stream number
	uint8_t         field_num;      // field number
	                                // stream name (w/ null terminator)
	uint8_t         field_length;   // length of data field (bytes)
	uint8_t         format;         // signed / unsigned / float
	int32_t         min;            // minimum expected value
	int32_t         max;            // maximum expected value
	char            units [FIELD_UNIT_LEN];
	                                // data units label (w/ null terminator)
	char            name [FIELD_NAME_LEN];
	                                // data field name (w/ null terminator)
	uint8_t         crc;            // 8-bit checksum
	uint8_t         mark;       // 1-byte end-of-packet marker
} adv_config_field_t;


//! \brief Atmel Data Visualizer end-of-configuration packet
//
// This packet type is sent to indicate the completion of a series of
// configuration packets.  After this packet is sent, the application
// may begin transmitting regular stream data packets for display.
//
typedef struct 
	{
	uint8_t         header1;        // header bytes - always 0xFF5A
	uint8_t         header2;        // header bytes - always 0xFF5A
	uint16_t        length;         // packet length (bytes)
	uint8_t         type;           // packet type
	uint8_t         num_streams;    // total number of data streams 
	uint8_t         crc;            // 8-bit checksum
	uint8_t         mark;           // 1-byte end-of-packet marker
} adv_config_end_t;



/*! \brief Atmel Data Visualizer data packet components
 *
 * A complete data packet consists of an adv_data_start_t structure, followed
 * by one or more adv_data_field_t structures containing the actual data
 * values, followed by an adv_data_end_t structure.
 */

typedef struct {
	uint8_t         header1;        // header bytes - always 0xFF5A
	uint8_t         header2;        // header bytes - always 0xFF5A
	uint16_t        length;         // packet length (bytes)
	uint8_t         type;           // packet type
	uint8_t         stream_num;     // stream number (to match later data pkts)
	uint32_t        time_stamp;     // time stamp (tick count)
} adv_data_start_t;


typedef struct {
	int32_t         value;          // data field value
} adv_data_field_t;


typedef struct {
	uint8_t         crc;            // 8-bit checksum
	uint8_t         mark;           // 1-byte end-of-packet marker
} adv_data_end_t;

// @}


COMPILER_PACK_RESET()               // reset to default structure packing


/*! \brief Write Atmel Data Visualizer data buffer via USB or serial port.
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
void adv_write_buf(uint8_t * buf, int num_bytes);

/*! \brief  Send Atmel Data Visualizer data packet with 1 data field
 *
 * This routine constructs a data visualizer data packet with one data value 
 * field and then transmits it.  All multi-byte transmitted values
 * use little endian byte order.
 *
 * \param   stream_num  The ID number of the visualizer data stream
 * \param   timestamp   A 32-bit timestamp value, in microseconds
 * \param   value       The data value to include in the transmitted packet
 *
 * \return  Nothing.
 */
void adv_data_send_1(uint8_t stream_num, uint32_t timestamp, int32_t value);

/*! \brief  Send Atmel Data Visualizer data packet w/ 3 data fields
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
 *
 * \return  Nothing.
 */
void adv_data_send_3(uint8_t stream_num, uint32_t timestamp, int32_t value0,
		int32_t value1, int32_t value2);

//! @
#endif
