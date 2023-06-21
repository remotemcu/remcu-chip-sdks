/**
 *
 * \file
 *
 * \brief This module contains WINC1500 Host MCU Provisioning implementation.
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

#include "http_content.h"
#include <string.h>
#include <ctype.h>


static const char b64_table[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/'
};

uint32 base64decode(char* src, uint32 len)
{
	uint32 i = 0;
	uint32 j = 0;
	uint32 size = 0;
	uint8 buf[3];
	uint8 tmp[4];
	char* dst = src;
	
	// Skip line which contains '-' (-----BEGIN ...)
	for(;j<len;j++)
	{
		if(src[j] == '-')
		break;
	}
	for(;j<len;j++)
	{
		if(src[j] == '\r' || src[j] == '\n')
		{
			len -= j;
			src = &src[j];
			break;
		}
	}

	for(uint32 k=0;j<len;k++)
	{
		char c = src[k];

		if(c == '\r' || c == '\n') // Ignore new line characters
		continue;
		else if (c == '=' || (!isalnum(c) && c != '+' && c != '/')) // Stop if character is padding (=) or invalid
		break;

		tmp[i++] = c;

		if (i == 4)
		{
			// Translate values in 'tmp' from table
			for (i=0;i<4;i++)
			{
				// Find translation char in 'b64_table'
				for (uint8 x=0;x<64;x++)
				{
					if (tmp[i] == b64_table[x])
					{
						tmp[i] = x;
						break;
					}
				}
			}

			// Decode
			buf[0] = (tmp[0] << 2) + ((tmp[1] & 0x30) >> 4);
			buf[1] = ((tmp[1] & 0xf) << 4) + ((tmp[2] & 0x3c) >> 2);
			buf[2] = ((tmp[2] & 0x3) << 6) + tmp[3];

			memcpy(&dst[size], buf, sizeof(buf));
			size += sizeof(buf);

			i = 0;
		}
	}

	// Remainder
	if (i > 0)
	{
		// Fill remaining chars with '\0'
		for (uint8 l=i;l<4;l++)
		tmp[l] = '\0';

		// Translate remainder
		for (uint8 m=0;m<4;m++)
		{
			// Find translation char in 'b64_table'
			for (uint8 x=0;x<64;x++)
			{
				if(tmp[m] == b64_table[x])
				{
					tmp[m] = x;
					break;
				}
			}
		}

		// Decode remainder
		buf[0] = (tmp[0] << 2) + ((tmp[1] & 0x30) >> 4);
		buf[1] = ((tmp[1] & 0xf) << 4) + ((tmp[2] & 0x3c) >> 2);
		buf[2] = ((tmp[2] & 0x3) << 6) + tmp[3];

		memcpy(&dst[size], buf, i - 1);
		size += i - 1;
	}

	return size;
}

uint32 decodeLength(uint8* buff, uint8* lenBytes)
{
	// The length byte can be in 2 forms:
	// Short form: 8th bit is 0, remaining bits is the length of the section, up to 127 bytes.
	// Long form: 8th bit is 1, remaining bits are how many subsequent bytes make up the length.
	// See ISO/IEC 8825-1 section 8.1.3
	// https://www.itu.int/ITU-T/studygroups/com17/languages/X.690-0207.pdf
	
	uint32 length = buff[0];
	*lenBytes = 0;

	if(length & 0x80) // Long form
	{
		*lenBytes = length & 0x7F; // Get how many bytes make up the length value
		length = 0;
		for(uint8 i=0;i<*lenBytes;i++)
			length += (uint32)(buff[i + 1] << ((*lenBytes - i - 1) * 8));
	}

	return length;
}
