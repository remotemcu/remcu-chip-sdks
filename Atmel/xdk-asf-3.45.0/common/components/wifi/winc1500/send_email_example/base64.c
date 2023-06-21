/**
 * \file
 *
 * \brief WINC1500 Send Email Example.
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

static const char g_ccB64Tbl[64]
	= "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void ConvertToBase64(char *pcOutStr, const char *pccInStr, int iLen);

void ConvertToBase64(char *pcOutStr, const char *pccInStr, int iLen)
{
	const char *pccIn = (const char *)pccInStr;
	char *pcOut;
	int iCount;
	pcOut = pcOutStr;

	/* Loop in for Multiple of 24Bits and Convert to Base 64 */
	for (iCount = 0; iLen - iCount >= 3; iCount += 3, pccIn += 3) {
		*pcOut++ = g_ccB64Tbl[pccIn[0] >> 2];
		*pcOut++ = g_ccB64Tbl[((pccIn[0] & 0x03) << 4) | (pccIn[1] >> 4)];
		*pcOut++ = g_ccB64Tbl[((pccIn[1] & 0x0F) << 2) | (pccIn[2] >> 6)];
		*pcOut++ = g_ccB64Tbl[pccIn[2] & 0x3f];
	}

	/* Check if String is not multiple of 3 Bytes */
	if (iCount != iLen) {
		unsigned char ucLastByte;

		*pcOut++ = g_ccB64Tbl[pccIn[0] >> 2];
		ucLastByte = ((pccIn[0] & 0x03) << 4);

		if (iLen - iCount > 1) {
			/* If there are 2 Extra Bytes */
			ucLastByte |= (pccIn[1] >> 4);
			*pcOut++ = g_ccB64Tbl[ucLastByte];
			*pcOut++ = g_ccB64Tbl[((pccIn[1] & 0x0F) << 2)];
		} else {
			/* If there is only 1 Extra Byte */
			*pcOut++ = g_ccB64Tbl[ucLastByte];
			*pcOut++ = '=';
		}

		*pcOut++ = '=';
	}

	*pcOut  = '\0';
}
