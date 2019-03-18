/**
 * \file
 *
 * \brief Interface Internal Types.
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

#ifndef __CRYPTO_TYPES_H__
#define __CRYPTO_TYPES_H__

/*******************************************************************************************
INCLUDES
*******************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common/include/nm_common.h"
#include "driver/include/m2m_types.h"

typedef uint64_t uint64;

typedef enum{
	BFALSE = 0,
	BTRUE  = 1
}BOOL_T;

typedef struct{
	uint16	u16BufferSize;
	uint8	*pu8Data;
}tstrBuffer;

/*******************************************************************************************
MACROS
*******************************************************************************************/

#define BIT31							0x80000000
#define BIT30							0x40000000
#define BIT29							0x20000000
#define BIT28							0x10000000
#define BIT27							0x08000000
#define BIT26							0x04000000
#define BIT25							0x02000000
#define BIT24							0x01000000
#define BIT23							0x00800000
#define BIT22							0x00400000
#define BIT21							0x00200000
#define BIT20							0x00100000
#define BIT19							0x00080000
#define BIT18							0x00040000
#define BIT17							0x00020000
#define BIT16							0x00010000
#define BIT15							0x00008000
#define BIT14							0x00004000
#define BIT13							0x00002000
#define BIT12							0x00001000
#define BIT11							0x00000800
#define BIT10							0x00000400
#define BIT9							0x00000200
#define BIT8							0x00000100
#define BIT7							0x00000080
#define BIT6							0x00000040
#define BIT5							0x00000020
#define BIT4							0x00000010
#define BIT3							0x00000008
#define BIT2							0x00000004
#define BIT1							0x00000002
#define BIT0							0x00000001

#define SIZE_128_BITS					(16)
#define SIZE_256_BITS					(32)
#define SIZE_512_BITS					(64)
#define SIZE_1024_BITS					(128)
#define SIZE_1536_BITS					(192)
#define SIZE_2048_BITS					(256)

#define GETU32(BUF,OFFSET)				((((uint32)((BUF)[OFFSET]) << 24)) | (((uint32)((BUF)[OFFSET + 1]) << 16)) | \
(((uint32)((BUF)[OFFSET + 2]) << 8)) | ((uint32)((BUF)[OFFSET + 3])))

#define PUTU32(VAL32,BUF,OFFSET)	\
do	\
{	\
	(BUF)[OFFSET	] = BYTE_3((VAL32));	\
	(BUF)[OFFSET +1	] = BYTE_2((VAL32));	\
	(BUF)[OFFSET +2	] = BYTE_1((VAL32));	\
	(BUF)[OFFSET +3	] = BYTE_0((VAL32));	\
}while(0)


#define MAX(A, B)		(((A) > (B))? (A) : (B))
#define MIN(A, B)		(((A) < (B))? (A) : (B))

/*
*/
#define OVERLAY_SEC1_API
#define TLS_CLIENT_API
#define TLS_API


/*
	FUNCTION MACROS
*/
#define X509_GET_SYS_TIME(x)									-1

#define M2M_MEMCMP											memcmp
#define M2M_MEMCPY											memcpy
#define M2M_MEMSET											memset
#define M2M_MALLOC_S(s)										malloc(s)
#define M2M_FREE(p)											free(p)

#define HMAC_SHA1											hmac_sha1
#define HMAC_MD5											hmac_md5
#define SHA256_HASH											SHA256_Hash
#define MD4_HASH											MD4_Hash
#define MD5_HASH											MD5_Hash
#define SHA1_HASH											SHA1_Hash
#define HMAC_SHA256											Hmac_SHA256
#define HMAC_VECTOR											HMAC_Vector
#define MD5_HASH_SW(pCxt, flags, data, dataSz, out)			MD5_HashSW(&(pCxt)->strSha512, flags, data, dataSz, out)
#define SHA1_HASH_SW(pCxt, flags, data, dataSz, out)		SHA1_HashSW(&(pCxt)->strSha512, flags, data, dataSz, out)
#define SHA224_HASH_SW(pCxt, flags, data, dataSz, out)		SHA224_HashSW(&(pCxt)->strSha512, flags, data, dataSz, out)
#define SHA256_HASH_SW(pCxt, flags, data, dataSz, out)		SHA256_HashSW(&(pCxt)->strSha512, flags, data, dataSz, out)
#define SHA384_HASH_SW(pCxt, flags, data, dataSz, out)		SHA512_HashSW(&(pCxt)->strSha512, flags, data, dataSz, out, 1)
#define SHA512_HASH_SW(pCxt, flags, data, dataSz, out)		SHA512_HashSW(&(pCxt)->strSha512, flags, data, dataSz, out, 0)


#define M2M_DUMP_BUF(name,Buffer,size)					\
do														\
{														\
	int k;												\
	uint8	*buf = Buffer;								\
	printf("%s(%08X)(%u)",name,(uint32)buf, size);	\
	for (k = 0; k < size; k++)							\
	{													\
		if (!(k % 16))									\
		printf("\r\n\t");								\
		printf("%02X ", buf[k]);						\
	}													\
	printf("\r\n");									\
}while(0)

#define TLS_LOG(...)					do{printf(__VA_ARGS__);printf("\r");}while(0)
#define TLS_ERR							TLS_LOG
#define TLS_INFO						TLS_LOG

#endif /* __CRYPTO_TYPES_H__ */
