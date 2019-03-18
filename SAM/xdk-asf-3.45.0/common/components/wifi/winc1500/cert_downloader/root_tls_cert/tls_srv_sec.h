/**
 *
 * \file
 *
 * \brief This module implements TLS Server Certificate Installation.
 *
 * Copyright (c) 2017-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef __TLS_SRV_SEC_H__
#define __TLS_SRV_SEC_H__

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
INCLUDES
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#include "root_tls_cert/crypto/crypto_api.h"
#include "programmer/programmer.h"
#include "pem.h"

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
MACROS
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#define TLS_SRV_SEC_MAX_FILES			8
#define TLS_SRV_SEC_START_PATTERN_LEN	8
#define TLS_SRV_SEC_START_PATTERN		{0xAB, 0xFE, 0x18, 0x5B, 0x70, 0xC3, 0x46, 0x92}
#define TLS_SRV_SEC_FILE_NAME_MAX		(48)

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
DATA TYPES
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

typedef enum{
	TLS_SRV_SEC_MODE_WRITE = 0,
	TLS_SRV_SEC_MODE_APPEND
}tenuWriteMode;


typedef struct{
	uint16	u16BufferSize;
	uint8	*pu8Data;
}tstrBuff;


typedef struct certEntry{
	txtrX509CertInfo	strX509;
	tstrBuff			strX509ASN1Buff;
	char				acFileName[60];
	struct certEntry	*pstrNext;
}tstrX509Entry;


typedef enum{
	FILE_MODE_READ,
	FILE_MODE_WRITE
}tenuTlsSrvSecFileMode;


typedef struct{
	tstrTlsSrvSecFileEntry		*pstrFile;
	uint32						u32Offset;
}tstrTlsSrvSecFileHandle;


typedef struct{
	uint32	u32FileSz;
	uint8	*pu8FileData;
}tstrFileInfo;


/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
FUNCTION PROTOTYPES
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

sint8 TlsSrvSecWriteCertChain(uint8 *pu8PrivKey, uint32 u32PrivKeySz, tstrFileInfo *pstrCertChain, uint8 u8ChainDepth, uint8 *pu8TlsSrvSecBuff, uint32 *pu32SecSz, tenuWriteMode enuMode);

#endif  /* __TLS_SRV_SEC_H__ */