/**
 * \file
 *
 * \brief APIs and data types for cryptographic algorithms.
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

#ifndef __CRYPTO_H__
#define __CRYPTO_H__

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
INCLUDES
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#include "crypto_types.h"
#include "driver/include/ecc_types.h"

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 MACROS
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

/*======*======*======*======*
HASH RELATED DEFINITIONS
*======*======*======*======*/

#define SHA512_BLOCK_SIZE					(128)
#define SHA_BLOCK_SIZE						(64)

#define MD4_DIGEST_SIZE						(16)
#define MD5_DIGEST_SIZE						(16)
#define SHA1_DIGEST_SIZE					(20)
#define SHA224_DIGEST_SIZE					(28)
#define SHA256_DIGEST_SIZE 					(32)
#define SHA384_DIGEST_SIZE					(48)
#define SHA512_DIGEST_SIZE					(64)
#define SHA_MAX_DIGEST_SIZE					SHA512_DIGEST_SIZE

#define SHA_FLAGS_INIT						0x01
/*!<
	A flag to tell the hash function to start hash from 
	the initial state.
*/


#define SHA_FLAGS_UPDATE					0x02
/*!< 
	Update the current hash with the given data.
*/


#define SHA_FLAGS_FINISH					0x04
/*!< 
	Finalize the hashing and calculate the final result.
*/


#define SHA_FLAGS_FULL_HASH					(SHA_FLAGS_INIT | SHA_FLAGS_UPDATE | SHA_FLAGS_FINISH)
/*!< 
	Perform Full hash operation with the DIGEST
	returned to the caller.
*/



#define SHA1_INIT(ctxt)						SHA1_Hash((ctxt), SHA_FLAGS_INIT, NULL, 0, NULL)
#define SHA1_UPDATE(ctxt,data,dataLen)		SHA1_Hash((ctxt), SHA_FLAGS_UPDATE, (data), (dataLen), NULL)
#define SHA1_FINISH(ctxt,digest)			SHA1_Hash((ctxt), SHA_FLAGS_FINISH, NULL, 0, digest)

#define MD5_INIT(ctxt)						MD5_Hash((ctxt), SHA_FLAGS_INIT, NULL, 0, NULL)
#define MD5_UPDATE(ctxt,data,dataLen)		MD5_Hash((ctxt), SHA_FLAGS_UPDATE, (data), (dataLen), NULL)
#define MD5_FINISH(ctxt,digest)				MD5_Hash((ctxt), SHA_FLAGS_FINISH, NULL, 0, digest)

#define SHA256_INIT(ctxt)					SHA256_Hash((ctxt), SHA_FLAGS_INIT, NULL, 0, NULL)
#define SHA256_UPDATE(ctxt,data,dataLen)	SHA256_Hash((ctxt), SHA_FLAGS_UPDATE, (data), (dataLen), NULL)
#define SHA256_FINISH(ctxt,digest)			SHA256_Hash((ctxt), SHA_FLAGS_FINISH, NULL, 0, digest)


#define SHA_SHR(x,n) 						((x & 0xFFFFFFFF) >> n)
#define SHA_SHL(x,n) 						((x & 0xFFFFFFFF) << n)

#define SHA_SHR_64(high,low,n,high_o,low_o)	(high_o = SHA_SHR(high,n));\
											(low_o  =  SHA_SHR(low,n) | SHA_SHL(high , (32 - n)))
#define SHA_SHL_64(high,low,n,high_o,low_o) (high_o = SHA_SHL(high,n) | SHA_SHR(low , (32 - n)));\
											(low_o  =  SHA_SHL(low,n))
											
#define SHA_ROTR(x,n) 						(SHA_SHR(x,n) | SHA_SHL(x , (32 - n)))
#define SHA_ROTL(x,n) 						(SHA_SHL(x,n) | SHA_SHR(x , (32 - n)))

#define SHA_ROTR_64(high,low,n,high_o,low_o) (high_o = SHA_SHR(high,n) | SHA_SHL(low , (32 - n)));\
											(low_o  =  SHA_SHR(low,n) | SHA_SHL(high , (32 - n)))
#define SHA_ROTL_64(high,low,n,high_o,low_o) (high_o = SHA_SHL(high,n) | SHA_SHR(low , (32 - n)));\
											(low_o  =  SHA_SHL(low,n) | SHA_SHR(high , (32 - n)))

/*======*======*======*======*
PUBLIC KEY SPECIFIC DATA TYPES
*======*======*======*======*/
typedef enum{
	PUBKEY_ALG_NONE,
	PUBKEY_ALG_RSA,
	PUBKEY_ALG_DH,
	PUBKEY_ALG_ECC
}tenuPubKeyAlg;


/*!
@enum	\
	tenuTlsSignAlg

@brief	TLS Defined Signature Algorithms

	Public Key Signature algorithms mapped to the IDs defined by the TLS protocol specifications. 
	It is used in the signature_algorithms Hello Extension that must be included in the
	TLS.Handshake.ClientHello message starting from TLS 1.2.
*/
typedef enum{
	TLS_SIG_ANON,
	TLS_SIG_ALG_RSA,
	TLS_SIG_ALG_DSA,
	TLS_SIG_ALG_ECDSA
}tenuTlsSignAlg;


/*!
@struct	\
	tstrDHPublicKey
	
@brief	Diffie-Hellman Public Key Definition
*/
typedef struct{
	tstrEllipticCurve	*pstrCurve;
	tstrECPoint			strQ;
}tstrECPublicKey;


/*!
@struct	\
	tstrDHPublicKey
	
@brief	Diffie-Hellman Public Key Definition
*/
typedef struct{
	uint8	*pu8P;
	uint8	*pu8G;
	uint8	*pu8Key;
	uint8	*pu8Priv;
	uint16	u16PSize;
	uint16	u16GSize;
	uint16	u16KeySize;
	uint16	u16PrivSize;
}tstrDHPublicKey;


/*!
@struct	\
	tstrRSAPublicKey
	
@brief	RSA Public Key Definition
*/
typedef struct{
	uint16	u16NSize;
	uint16	u16ESize;
	uint8	*pu8N;
	uint8	*pu8E;
}tstrRSAPublicKey;


/*!
@struct	\
	tstrPublicKey
	
@brief	Generic Public Key Structure
*/
typedef struct{
	tenuPubKeyAlg	enuType;
	/*!<
		Type of the underlying public key algorithm.
	*/
	union{
			tstrRSAPublicKey	strRSAKey;
			tstrDHPublicKey		strDHKey;
			tstrECPublicKey		strEccKey;
		};
}tstrPublicKey;

typedef tstrRSAPublicKey	tstrRSAPrivateKey;


/*======*======*======*======*
HASH SPECIFIC DATA TYPES
*======*======*======*======*/

/*!
@typedef	\
	tpfHashProcessBlock
	
@brief
*/
typedef void (*tpfHashProcessBlock)(uint32* pu32HashState, const uint8* pu8MessageBlock);


/*!
@struct	\
	tstrHashContext
	
@brief
*/
typedef struct{
	uint32				au32HashState[SHA256_DIGEST_SIZE/4];
	uint8				au8CurrentBlock[SHA_BLOCK_SIZE];
	uint32				u32TotalLength;
	tpfHashProcessBlock	fpHash;
	uint8				u8BlockSize;
	uint8				u8DigestSize;
}tstrHashContext;


/*!
@struct	\
	tstrHash512Context
	
@brief
*/
typedef struct{
	uint32				au32HashState[SHA_MAX_DIGEST_SIZE/4];
	uint8				au8CurrentBlock[SHA512_BLOCK_SIZE];
	uint32				u32TotalLength;
	tpfHashProcessBlock	fpHash;
	uint8				u8BlockSize;
	uint8				u8DigestSize;
}tstrHash512Context;


/*!
*/
typedef struct{
	union{
		tstrHashContext		strSha;
		tstrHash512Context	strSha512;
	};
}tstrShaHashContext;


/*!
@typedef	\
	tstrMd5Context
	
@brief
*/
typedef tstrShaHashContext	tstrMd5Context;


/*!
@typedef	\
	tstrSha1Context
	
@brief
*/
typedef tstrShaHashContext	tstrSha1Context;


/*!
@typedef	\
	tstrSha256Context
	
@brief
*/
typedef tstrShaHashContext	tstrSha256Context;


/*!
@typedef	\
	tpfHash
	
@brief
*/
typedef void (*tpfHash)
(
tstrShaHashContext	*pstrHashContext,		
uint8				u8Flags,
uint8				*pu8Data, 
uint32 				u32DataLength, 
uint8				*pu8Digest
);


/*!
@enum	\
	tenuHashAlg

@brief	TLS Defined Hash Algorithms

	Hash algorithms mapped to the IDs defined by the TLS protocol specifications. It is 
	used in the signature_algorithms Hello Extension that must be included in the
	TLS.Handshake.ClientHello message starting from TLS 1.2.
*/
typedef enum{
	HASH_ALG_NONE,
	HASH_ALG_MD5,
	HASH_ALG_SHA1,
	HASH_ALG_SHA224,
	HASH_ALG_SHA256,
	HASH_ALG_SHA384,
	HASH_ALG_SHA512,
	HASH_ALG_MAX
}tenuHashAlg;


typedef struct{
	tpfHash	fpHash;
	uint16	u16HashSz;
	uint16	u16BlockSz;
}tstrHashInfo;

/*======*======*======*======*
HASH ALGORITHMS
*======*======*======*======*/

/*
	SW HASH FUNCTIONS
*/
void 	MD5_HashSW(tstrHash512Context * pstrMD5Cxt, uint8 u8Flags, uint8 * pu8Data, uint32 u32DataLength, uint8 * pu8Digest);
void 	SHA1_HashSW(tstrHash512Context * pstrSha1Cxt, uint8 u8Flags, uint8 * pu8Data, uint32 u32DataLength, uint8 * pu8Digest);
void 	SHA224_HashSW(tstrHash512Context * pstrSha224Cxt, uint8 u8Flags, uint8 * pu8Data, uint32 u32DataLength, uint8 * pu8Digest);
void 	SHA256_HashSW(tstrHash512Context * pstrSha256Cxt, uint8 u8Flags, uint8 * pu8Data, uint32 u32DataLength, uint8 * pu8Digest);
void 	SHA512_HashSW(tstrHash512Context * pstrSha512Cxt, uint8 u8Flags, uint8 * pu8Data, uint32 u32DataLength, uint8 * pu8Digest, uint8 u8IsSHA384);
void 	MD4_Hash(uint8 * pu8Data, uint32 u32DataLength, uint8 * pu8Digest);

/*
	HASH INTERFACE APIs (A unified interface is used for simplicity)
*/
void 	MD5_Hash(tstrShaHashContext * pstrSha1Context, uint8 u8Flags, uint8 * pu8Data, uint32 u32DataLength, uint8 * pu8Digest);
void 	SHA1_Hash(tstrShaHashContext * pstrSha1Context, uint8 u8Flags, uint8 * pu8Data, uint32 u32DataLength, uint8 * pu8Digest);
void 	SHA224_Hash(tstrShaHashContext * pstrSha1Context, uint8 u8Flags, uint8 * pu8Data, uint32 u32DataLength, uint8 * pu8Digest);
void	SHA256_Hash(tstrShaHashContext * pstrSha1Context, uint8 u8Flags, uint8 * pu8Data, uint32 u32DataLength, uint8 * pu8Digest);
void 	SHA384_Hash(tstrShaHashContext * pstrSha1Context, uint8 u8Flags, uint8 * pu8Data, uint32 u32DataLength, uint8 * pu8Digest);
void 	SHA512_Hash(tstrShaHashContext * pstrSha1Context, uint8 u8Flags, uint8 * pu8Data, uint32 u32DataLength, uint8 * pu8Digest);

/*
	HMAC-Hash APIs
*/
void 	hmac_md5(uint8 * pu8Data, uint32 u32DataLength, uint8 * pu8Key, uint32 u32KeyLength, uint8 * pu8Digest);
void 	hmac_sha1(uint8 * pu8Key, uint32 u32KeyLength, uint8 * pu8Data, uint32 u32DataLength, uint8 * pu8Digest);
void 	HMAC_SHA256(uint8 * pu8Data, uint32 u32DataLength, uint8 * pu8Key, uint32 u32KeyLength, uint8 * pu8Digest);
void 	HMAC_Vector(tenuHashAlg enuHashAlg, uint8 * pu8Key, uint32 u32KeyLength, tstrBuffer * pstrInData, uint8 u8NumInputs, uint8 * pu8Out);


/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
EXTERNALS
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

extern tstrHashInfo		eastrTlsHashes[HASH_ALG_MAX];


#endif /* __CRYPTO_H__ */
