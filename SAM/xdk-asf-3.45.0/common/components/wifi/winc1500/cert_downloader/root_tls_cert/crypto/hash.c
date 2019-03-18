/**
 * \file
 *
 * \brief Implementation of HASH algorithms used in Wi-Fi
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


/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
INCLUDES
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#include "root_tls_cert/crypto/crypto.h"
#include "root_tls_cert/crypto/crypto_types.h"

#define MD4_SEC OVERLAY_SEC1_API

void SHA256ProcessBlock(uint32* pu32Sha256State, const uint8* pu8Data);
void Sha_HashUpdate(tstrHash512Context * pstrHashCxt, uint8 * pu8Data, uint32 u32DataLength);
void Sha_HashFinish(tstrHash512Context * pstrHashCxt,uint8 *pu8LengthPadding, uint32 u32TotalMessageLength);
void SHA512ProcessBlock(uint32* pu32Sha512State, const uint8* pu8Data);
void SHA1ProcessBlock(uint32* pu32Sha1State, const uint8* pu8MessageBlock);
void MD5ProcessBlock(uint32 *pu32Md5State,const uint8* pu8MessageBlock);
MD4_SEC void MD4ProcessBlock(uint32 *pu32Md4State,const uint8* pu8MessageBlock);

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
MACROS
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#define SHA_PAD_BYTE				0x80

#define F1(x, y, z) 					(((x) & (y)) | (~(x) & (z)))
#define F2(x, y, z) 					(((x) & (z)) | ((y) & ~(z)))
#define F3(x, y, z) 					((x) ^ (y) ^ (z))
#define F4(x, y, z)     				(((x) & (y)) | ((x) & (z)) | ((y) & (z)))
#define F5(x, y, z) 					((y) ^ ((x) | ~(z)))

/*======*======*======*======*======*
			MD4 SPECIFIC DEFINES
*======*======*======*======*======*/


#define MD4_F(x,y,z)					F1(x,y,z)
#define MD4_G(x,y,z)					F4(x,y,z)
#define MD4_H(x,y,z)					F3(x,y,z)

#define MD4_INERMEDIATE(A,B,C,D,W,K,S)		\
{	\
	W 	+= A + K;	\
	W 	= SHA_ROTL(W, S);		\
	A 	= D;\
	D 	= C;		\
	C 	= B;	\
	B 	= W;				\
}

/*======*======*======*======*======*
			MD5 SPECIFIC DEFINES
*======*======*======*======*======*/


#define MD5_F(x, y, z) 				F1(x,y,z)
#define MD5_G(x, y, z) 				F2(x,y,z)
#define MD5_H(x, y, z) 				F3(x,y,z)
#define MD5_I(x, y, z) 				F5(x,y,z)

#define MD5_INERMEDIATE(A,B,C,D,W,K,S)		\
{	\
	W 	+= A + K;	\
	W 	= B + SHA_ROTL(W, S);		\
	A 	= D;\
	D 	= C;		\
	C 	= B;	\
	B 	= W;				\
}

/*======*======*======*======*======*
			SHA1 SPECIFIC DEFINES
*======*======*======*======*======*/

#define SHA1_CH(x, y, z)      			F1(x,y,z)
#define SHA1_MAJ(x, y, z)     			F4(x,y,z)
#define SHA_PARITY(x, y, z) 			F3(x,y,z)

#define SHA1_INERMEDIATE(A,B,C,D,E,W,K)		\
{	\
	W += SHA_ROTL(A,5) + E  + K;	\
	E = D;		\
	D = C;		\
	C = SHA_ROTL(B,30);	\
	B = A;				\
	A = W;				\
}

/*======*======*======*======*======*
			SHA256 SPECIFIC DEFINES
*======*======*======*======*======*/

#define SHA256_SMALL_SIGMA0(x) 			(SHA_ROTR(x, 7) ^ SHA_ROTR(x,18) ^  SHA_SHR(x, 3))
#define SHA256_SMALL_SIGMA1(x) 			(SHA_ROTR(x,17) ^ SHA_ROTR(x,19) ^ SHA_SHR(x,10))

#define SHA512_SMALL_SIGMA0(high,low) 	(SHA_ROTR_64(high,low, 1) ^ SHA_ROTR_64(high,low,8) ^  SHA_SHR_64(high,low, 7))
#define SHA512_SMALL_SIGMA1(high,low) 	(SHA_ROTR_64(high,low,19) ^ SHA_ROTR_64(low,high,29) ^ SHA_SHR_64(high,low,6))

#define SHA256_CAP_SIGMA0(x) 			(SHA_ROTR(x, 2) ^ SHA_ROTR(x,13) ^ SHA_ROTR(x,22))
#define SHA256_CAP_SIGMA1(x) 			(SHA_ROTR(x, 6) ^ SHA_ROTR(x,11) ^ SHA_ROTR(x,25))

#define SHA512_CAP_SIGMA0(high,low) 	(SHA_ROTR_64(high,low, 28) ^ SHA_ROTR_64(low,high,2) ^ SHA_ROTR_64(low,high,7))
#define SHA512_CAP_SIGMA1(high,low) 	(SHA_ROTR_64(high,low, 14) ^ SHA_ROTR_64(high,low,18) ^ SHA_ROTR_64(low,high,9))

#define SHA256_MAJ(x,y,z) 				((x & y) | (z & (x | y)))
#define SHA256_CH(x,y,z) 				(z ^ (x & (y ^ z)))


#define SHA512_MAJ_HIGH(x,y,z) 			((x[0] & y[0]) | (z[0] & (x[0] | y[0])))
#define SHA512_MAJ_LOW(x,y,z) 			((x[1] & y[1]) | (z[1] & (x[1] | y[1])))

#define SHA512_CH_HIGH(x,y,z) 			(z[0] ^ (x[0] & (y[0] ^ z[0])))
#define SHA512_CH_LOW(x,y,z) 			(z[1] ^ (x[1] & (y[1] ^ z[1])))



#define GET_UINT64_BE(n,b,i)               		\
    (n)[0] = ( (uint32) (b)[(i)    ] << 24 )       	\
        | ( (uint32) (b)[(i) + 1] << 16 )       		\
        | ( (uint32) (b)[(i) + 2] << 8 )       		\
        | ( (uint32) (b)[(i) + 3]  );       			\
     (n)[1] = ( (uint32) (b)[(i) + 4] << 24 )       	\
        | ( (uint32) (b)[(i) + 5] << 16 )       		\
        | ( (uint32) (b)[(i) + 6] <<  8 )       		\
        | ( (uint32) (b)[(i) + 7]       )

#define INT32_TO_INT64(z,x,y) z = (((uint64)(x)<<32)|((uint64)((y) & 0xffffffff)))


#define UPDATE_SHA512_STATE(state_high,state_low,temp_state,temp_var,var_high,var_low)		INT32_TO_INT64(temp_state, state_high, state_low);\
																							INT32_TO_INT64(temp_var, var_high, var_low );\
																							temp_state += temp_var;\
																							state_high = (uint32)((temp_state & 0xFFFFFFFF00000000) >> 32);\
																							state_low = (uint32)(temp_state & 0x00000000FFFFFFFF)

#define ADD_TWO_32BIT(z,x,y)	(z)[1] = (x)[1]+ (y)[1];	 \
								(z)[0] = (x)[0] + (y)[0]; \
								if((z)[1] < (y)[1])	 \
									((z)[0])++




#define PUTU64_BE(n,b,i)                            \
{                                                       \
    (b)[(i)    ] = (unsigned char) ( (n) >> 56 );       \
    (b)[(i) + 1] = (unsigned char) ( (n) >> 48 );       \
    (b)[(i) + 2] = (unsigned char) ( (n) >> 40 );       \
    (b)[(i) + 3] = (unsigned char) ( (n) >> 32 );       \
    (b)[(i) + 4] = (unsigned char) ( (n) >> 24 );       \
    (b)[(i) + 5] = (unsigned char) ( (n) >> 16 );       \
    (b)[(i) + 6] = (unsigned char) ( (n) >>  8 );       \
    (b)[(i) + 7] = (unsigned char) ( (n)       );       \
}

#define SHA256_MSG_LENGTH		8	
#define SHA512_MSG_LENGTH		16

const uint32 K_SHA1[4] = {
	0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6
};

static const uint32 K_SHA256[] =    {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static const uint32 T_MD5[] =    {
	0xD76AA478, 0xE8C7B756, 0x242070DB, 0xC1BDCEEE, 0xF57C0FAF, 0x4787C62A, 0xA8304613, 0xFD469501,
	0x698098D8, 0x8B44F7AF, 0xFFFF5BB1, 0x895CD7BE, 0x6B901122, 0xFD987193, 0xA679438E, 0x49B40821,
	0xF61E2562, 0xC040B340, 0x265E5A51, 0xE9B6C7AA, 0xD62F105D, 0x02441453, 0xD8A1E681, 0xE7D3FBC8,
	0x21E1CDE6, 0xC33707D6, 0xF4D50D87, 0x455A14ED, 0xA9E3E905, 0xFCEFA3F8, 0x676F02D9, 0x8D2A4C8A,
	0xFFFA3942, 0x8771F681, 0x6D9D6122, 0xFDE5380C, 0xA4BEEA44, 0x4BDECFA9, 0xF6BB4B60, 0xBEBFBC70,
	0x289B7EC6, 0xEAA127FA, 0xD4EF3085, 0x04881D05, 0xD9D4D039, 0xE6DB99E5, 0x1FA27CF8, 0xC4AC5665,
	0xF4292244, 0x432AFF97, 0xAB9423A7, 0xFC93A039, 0x655B59C3, 0x8F0CCC92, 0xFFEFF47D, 0x85845DD1,
	0x6FA87E4F, 0xFE2CE6E0, 0xA3014314, 0x4E0811A1, 0xF7537E82, 0xBD3AF235, 0x2AD7D2BB, 0xEB86D391
};


/*
 * SHA512 Round constants
 */
static const uint64 K_SHA512[][2] = {
	{0x428a2f98, 0xd728ae22}, {0x71374491, 0x23ef65cd}, {0xb5c0fbcf, 0xec4d3b2f}, {0xe9b5dba5, 0x8189dbbc}, {0x3956c25b, 0xf348b538}, 
	{0x59f111f1, 0xb605d019}, {0x923f82a4, 0xaf194f9b}, {0xab1c5ed5, 0xda6d8118}, {0xd807aa98, 0xa3030242}, {0x12835b01, 0x45706fbe}, 
	{0x243185be, 0x4ee4b28c}, {0x550c7dc3, 0xd5ffb4e2}, {0x72be5d74, 0xf27b896f}, {0x80deb1fe, 0x3b1696b1}, {0x9bdc06a7, 0x25c71235}, 
	{0xc19bf174, 0xcf692694}, {0xe49b69c1, 0x9ef14ad2}, {0xefbe4786, 0x384f25e3}, {0x0fc19dc6, 0x8b8cd5b5}, {0x240ca1cc, 0x77ac9c65}, 
	{0x2de92c6f, 0x592b0275}, {0x4a7484aa, 0x6ea6e483}, {0x5cb0a9dc, 0xbd41fbd4}, {0x76f988da, 0x831153b5}, {0x983e5152, 0xee66dfab}, 
	{0xa831c66d, 0x2db43210}, {0xb00327c8, 0x98fb213f}, {0xbf597fc7, 0xbeef0ee4}, {0xc6e00bf3, 0x3da88fc2}, {0xd5a79147, 0x930aa725}, 
	{0x06ca6351, 0xe003826f}, {0x14292967, 0x0a0e6e70}, {0x27b70a85, 0x46d22ffc}, {0x2e1b2138, 0x5c26c926}, {0x4d2c6dfc, 0x5ac42aed}, 
	{0x53380d13, 0x9d95b3df}, {0x650a7354, 0x8baf63de}, {0x766a0abb, 0x3c77b2a8}, {0x81c2c92e, 0x47edaee6}, {0x92722c85, 0x1482353b}, 
	{0xa2bfe8a1, 0x4cf10364}, {0xa81a664b, 0xbc423001}, {0xc24b8b70, 0xd0f89791}, {0xc76c51a3, 0x0654be30}, {0xd192e819, 0xd6ef5218}, 
	{0xd6990624, 0x5565a910}, {0xf40e3585, 0x5771202a}, {0x106aa070, 0x32bbd1b8}, {0x19a4c116, 0xb8d2d0c8}, {0x1e376c08, 0x5141ab53}, 
	{0x2748774c, 0xdf8eeb99}, {0x34b0bcb5, 0xe19b48a8}, {0x391c0cb3, 0xc5c95a63}, {0x4ed8aa4a, 0xe3418acb}, {0x5b9cca4f, 0x7763e373}, 
	{0x682e6ff3, 0xd6b2b8a3}, {0x748f82ee, 0x5defb2fc}, {0x78a5636f, 0x43172f60}, {0x84c87814, 0xa1f0ab72}, {0x8cc70208, 0x1a6439ec}, 
	{0x90befffa, 0x23631e28}, {0xa4506ceb, 0xde82bde9}, {0xbef9a3f7, 0xb2c67915}, {0xc67178f2, 0xe372532b}, {0xca273ece, 0xea26619c}, 
	{0xd186b8c7, 0x21c0c207}, {0xeada7dd6, 0xcde0eb1e}, {0xf57d4f7f, 0xee6ed178}, {0x06f067aa, 0x72176fba}, {0x0a637dc5, 0xa2c898a6}, 
	{0x113f9804, 0xbef90dae}, {0x1b710b35, 0x131c471b}, {0x28db77f5, 0x23047d84}, {0x32caab7b, 0x40c72493}, {0x3c9ebe0a, 0x15c9bebc}, 
	{0x431d67c4, 0x9c100d4c}, {0x4cc5d4be, 0xcb3e42b6}, {0x597f299c, 0xfc657e2a}, {0x5fcb6fab, 0x3ad6faec}, {0x6c44198c, 0x4a475817}
};

tstrHashInfo		eastrTlsHashes[] = 
	{
		{NULL			, 0						},
		{MD5_Hash		, MD5_DIGEST_SIZE		, SHA_BLOCK_SIZE	},
		{SHA1_Hash		, SHA1_DIGEST_SIZE		, SHA_BLOCK_SIZE	},
		{SHA224_Hash	, SHA224_DIGEST_SIZE	, SHA_BLOCK_SIZE	},
		{SHA256_Hash	, SHA256_DIGEST_SIZE	, SHA_BLOCK_SIZE	},
		{SHA384_Hash	, SHA384_DIGEST_SIZE	, SHA512_BLOCK_SIZE	},
		{SHA512_Hash	, SHA512_DIGEST_SIZE	, SHA512_BLOCK_SIZE	},
	};

/*********************************************************************
Function
	MD4ProcessBlock

Description
	MD4 hash algorithm.

Return
	None

Author
	Ahmed Ezzat

Version
	1.0
Date
	3 Oct 2013
*********************************************************************/
MD4_SEC void MD4ProcessBlock(uint32 *pu32Md4State,const uint8* pu8MessageBlock)
{
	if((pu8MessageBlock != NULL) && (pu32Md4State != NULL))
	{
		uint32	A, B, C, D;   /* Word buffers */
		uint32	W = 0;
		uint32	X[16];
		uint8	u8Idx;
		uint8	au8MD4Rot[] = {
			3, 7, 11, 19, 
			3, 5,  9, 13, 
			3, 9, 11, 15
		};


		uint8	round2[] = { 0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15};
		uint8	round3[] = { 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};

		A = pu32Md4State[0];
		B = pu32Md4State[1];
		C = pu32Md4State[2];
		D = pu32Md4State[3];

		M2M_MEMCPY(X , pu8MessageBlock, 64);
	
		for(u8Idx = 0 ; u8Idx < 16 ; u8Idx ++)
		{
			W = MD4_F(B,C,D) + X[u8Idx];
			MD4_INERMEDIATE(A, B, C, D, W, 0, au8MD4Rot[(u8Idx % 4)]);
		}
				
		for(u8Idx = 0 ; u8Idx < 16 ; u8Idx ++)
		{
			W = MD4_G(B,C,D) + X[round2[u8Idx]];
			MD4_INERMEDIATE(A, B, C, D, W, 0x5A827999, au8MD4Rot[(u8Idx % 4) + 4]);
		}
						
		for(u8Idx = 0 ; u8Idx < 16 ; u8Idx ++)
		{
			W = MD4_H(B,C,D) + X[round3[u8Idx]];
			MD4_INERMEDIATE(A, B, C, D, W, 0x6ED9EBA1, au8MD4Rot[(u8Idx % 4) + 8]);
		}
						
		pu32Md4State[0] += A;
		pu32Md4State[1] += B;
		pu32Md4State[2] += C;
		pu32Md4State[3] += D;
	}
}

/*********************************************************************
Function
	MD5ProcessBlock

Description
    MD5 hash algorithm.
Return

Author

Version

Date
*********************************************************************/
void MD5ProcessBlock(uint32 *pu32Md5State,const uint8* pu8MessageBlock)
{
	uint32	A, B, C, D;   /* Word buffers */
	uint32	W = 0;
	uint32	X[16];
	uint8	u8Idx,u8Count;
	uint8	au8MD5Rot[] = {
		7, 12, 17, 22,
		5,  9, 14, 20,
		4, 11, 16, 23,  
		6, 10, 15, 21,
	};
	
	A = pu32Md5State[0];
	B = pu32Md5State[1];
	C = pu32Md5State[2];
	D = pu32Md5State[3];

	M2M_MEMCPY(X , pu8MessageBlock, 64);

	for(u8Idx = 0 ; u8Idx < 16 ; u8Idx ++)
	{
		W = MD5_F(B,C,D) + X[u8Idx];
		MD5_INERMEDIATE(A, B, C, D, W, T_MD5[u8Idx], au8MD5Rot[u8Idx % 4]);
	}

	for(u8Idx = 16 , u8Count = 1; u8Idx < 32 ; u8Idx ++ , u8Count += 5)
	{
		W = MD5_G(B,C,D) + X[u8Count & 0x0F];
		MD5_INERMEDIATE(A, B, C, D, W, T_MD5[u8Idx], au8MD5Rot[(u8Idx % 4) + 4]);
	}

	for(u8Idx = 32 , u8Count = 5; u8Idx < 48 ; u8Idx ++ , u8Count += 3)
	{
		W = MD5_H(B,C,D) + X[u8Count & 0x0F];
		MD5_INERMEDIATE(A, B, C, D, W, T_MD5[u8Idx], au8MD5Rot[(u8Idx % 4) + 8]);
	}

	for(u8Idx = 48 , u8Count = 0; u8Idx < 64 ; u8Idx ++ , u8Count += 7)
	{
		W = MD5_I(B,C,D) + X[u8Count & 0x0F];
		MD5_INERMEDIATE(A, B, C, D, W, T_MD5[u8Idx], au8MD5Rot[(u8Idx % 4) + 12]);
	}

	pu32Md5State[0] += A;
	pu32Md5State[1] += B;
	pu32Md5State[2] += C;
	pu32Md5State[3] += D;
}
/*********************************************************************
Function
	SHA1ProcessBlock

Description
    SHA1 hash algorithm.
Return

Author

Version

Date
*********************************************************************/
void SHA1ProcessBlock(uint32* pu32Sha1State, const uint8* pu8MessageBlock)
{
	int        	t;              /* Loop counter */
	uint32		W[80];          /* Word sequence */
	uint32   	A, B, C, D, E;  /* Word buffers */

	/*
	* Initialize the first 16 words in the array W
	*/
	for (t = 0; t < 16; t++) 
		W[t] = GETU32(pu8MessageBlock, (t * 4));

	for (t = 16; t < 80; t++)
		W[t] = SHA_ROTL((W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16]), 1);

	A = pu32Sha1State[0];
	B = pu32Sha1State[1];
	C = pu32Sha1State[2];
	D = pu32Sha1State[3];
	E = pu32Sha1State[4];

	for (t = 0; t < 20; t++) 
	{
		W[t] += SHA1_CH(B, C, D);
		SHA1_INERMEDIATE(A, B, C, D, E, W[t], K_SHA1[0])
	}

	for (t = 20; t < 40; t++) 
	{
		W[t] += SHA_PARITY(B, C, D);
		SHA1_INERMEDIATE(A, B, C, D, E, W[t], K_SHA1[1])
	}

	for (t = 40; t < 60; t++) 
	{
		W[t] += SHA1_MAJ(B, C, D);
		SHA1_INERMEDIATE(A, B, C, D, E, W[t], K_SHA1[2])
	}

	for (t = 60; t < 80; t++) 
	{
		W[t] += SHA_PARITY(B, C, D);
		SHA1_INERMEDIATE(A, B, C, D, E, W[t], K_SHA1[3])
	}

	pu32Sha1State[0] += A;
	pu32Sha1State[1] += B;
	pu32Sha1State[2] += C;
	pu32Sha1State[3] += D;
	pu32Sha1State[4] += E;
}
/*********************************************************************
Function
	SHA256ProcessBlock

Description
    SHA256 hash algorithm.
Return

Author

Version

Date
*********************************************************************/
void SHA256ProcessBlock(uint32* pu32Sha256State, const uint8* pu8Data)
{

	uint32	t;						/* Loop counter			*/
	uint32	temp1, temp2;			/* Temporary word value	*/
	uint32	W[64];					/* Word sequence		*/
	uint32	A, B, C, D, E, F, G, H;	/* Word buffers			*/

	A = pu32Sha256State[0];
	B = pu32Sha256State[1];
	C = pu32Sha256State[2];
	D = pu32Sha256State[3];
	E = pu32Sha256State[4];
	F = pu32Sha256State[5];
	G = pu32Sha256State[6];
	H = pu32Sha256State[7];

	/*  Initialize the first 16 words in the array W */
	for(t = 16; (t--) != 0;)
	{
		W[t] = pu8Data[t * 4] << 24;
		W[t] |= pu8Data[t * 4 + 1] << 16;
		W[t] |= pu8Data[t * 4 + 2] << 8;
		W[t] |= pu8Data[t * 4 + 3];
	}
	
	for(t = 16; t < 64; t++)
	{
		W[t] = SHA256_SMALL_SIGMA1(W[t-2]) + W[t-7]+
		SHA256_SMALL_SIGMA0(W[t-15]) + W[t-16];
	}

	for(t = 0; t < 64; t++)
	{
		temp1 = H +SHA256_CAP_SIGMA1(E) + SHA256_CH(E,F,G) + K_SHA256[t] + W[t];
		temp2 = SHA256_CAP_SIGMA0(A) + SHA256_MAJ(A,B,C);

		H = G;
		G = F;
		F = E;
		E = D + temp1;
		D = C;
		C = B;
		B = A;
		A = temp1 + temp2;
	}
	
	pu32Sha256State[0] += A;
	pu32Sha256State[1] += B;
	pu32Sha256State[2] += C;
	pu32Sha256State[3] += D;
	pu32Sha256State[4] += E;
	pu32Sha256State[5] += F;
	pu32Sha256State[6] += G;
	pu32Sha256State[7] += H;
}

/*********************************************************************
Function
	SHA512ProcessBlock

Description
    SHA512 hash algorithm.
Return

Author
	Abdelrahman Diab

Version
	1.0

Date: 
*********************************************************************/
void SHA512ProcessBlock(uint32* pu32Sha512State, const uint8* pu8Data)
{

	uint32	t;						/* Loop counter			*/
	uint32	temp1[2], temp2[2];			/* Temporary word value	*/
	uint32	W[80][2];					/* Word sequence		*/
	uint32	A[2], B[2], C[2], D[2], E[2], F[2], G[2], H[2];	/* Word buffers			*/


	A[0] = pu32Sha512State[0];
	A[1] = pu32Sha512State[1];

	B[0] = pu32Sha512State[2];
	B[1] = pu32Sha512State[3];

	C[0] = pu32Sha512State[4];
	C[1] = pu32Sha512State[5];
	
	D[0] = pu32Sha512State[6];
	D[1] = pu32Sha512State[7];
	
	E[0] = pu32Sha512State[8];
	E[1] = pu32Sha512State[9];
	
	F[0] = pu32Sha512State[10];
	F[1] = pu32Sha512State[11];
	
	G[0] = pu32Sha512State[12];
	G[1] = pu32Sha512State[13];
	
	H[0] = pu32Sha512State[14];
	H[1] = pu32Sha512State[15];
	

	/*  Initialize the first 16 words in the array W */
	for(t = 16; (t--) != 0;)
	{
		GET_UINT64_BE(W[t], pu8Data, t*8);
	}

	{
		uint32 s0[2] = {0};
		uint32 s1[2] = {0};
		uint32 S0[2] = {0};
		uint32 S1[2] = {0};
		
		uint32 high = 0;
		uint32 low = 0;

		uint32 Temp_high_out1,Temp_high_out2,Temp_high_out3;
		uint32 Temp_low_out1,Temp_low_out2,Temp_low_out3;

		uint32 temp3[2] = {0};
		
		for(t = 16; t < 80; t++)
		{
			
			/* 

			compute :
				W[t][0] = s0[0] + W[t-7][0] + s1[0] + W[t-16][0];
				W[t][1] = s0[1] + W[t-7][1] + s1[1] + W[t-16][1];
			*/
			high = W[t-2][0];
			low = W[t-2][1];
			 
			SHA_ROTR_64(high, low, 19, Temp_high_out1, Temp_low_out1);
			SHA_ROTR_64(low, high, 29, Temp_high_out2, Temp_low_out2);
			SHA_SHR_64(high, low, 6, Temp_high_out3, Temp_low_out3);
			
			s1[0] = Temp_high_out1 ^ Temp_high_out2 ^  Temp_high_out3;
			s1[1] = Temp_low_out1 ^ Temp_low_out2 ^ Temp_low_out3;


			high = W[t-15][0];
			low = W[t-15][1];
		
			
			SHA_ROTR_64(high, low, 1, Temp_high_out1, Temp_low_out1);
		 	SHA_ROTR_64(high, low, 8, Temp_high_out2, Temp_low_out2);
		   	SHA_SHR_64(high,low, 7, Temp_high_out3, Temp_low_out3);
			
			s0[0] = Temp_high_out1 ^ Temp_high_out2 ^  Temp_high_out3;
			s0[1] =   Temp_low_out1 ^ Temp_low_out2 ^ Temp_low_out3;


			ADD_TWO_32BIT(temp1, s0, W[t-7]);
			ADD_TWO_32BIT(temp2, s1, W[t-16]);
			ADD_TWO_32BIT(W[t],temp1,temp2);
		}
	
		for(t = 0; t < 80; t++)
		{
			/* 
			compute :
				temp1 = H +SHA512_CAP_SIGMA1(E) + SHA512_CH(E,F,G) + K_SHA512[t] + W[t];
			*/

			temp3[0] = SHA512_CH_HIGH(E,F,G);
            temp3[1] = SHA512_CH_LOW(E,F,G);

			high = E[0];
			low = E[1];
			
			SHA_ROTR_64(high, low, 14, Temp_high_out1, Temp_low_out1);
		 	SHA_ROTR_64(high, low, 18, Temp_high_out2, Temp_low_out2);
		   	SHA_ROTR_64(low,high, 9, Temp_high_out3, Temp_low_out3);
			
			S1[0] = Temp_high_out1 ^ Temp_high_out2 ^  Temp_high_out3;
			S1[1] = Temp_low_out1 ^ Temp_low_out2 ^ Temp_low_out3;
			
			ADD_TWO_32BIT(temp1, H, S1);
			ADD_TWO_32BIT(temp2, temp3, K_SHA512[t]);
			ADD_TWO_32BIT(temp3, temp1,temp2);
			ADD_TWO_32BIT(temp1, temp3, W[t]);
				
			
			/* 
			compute :
				temp2 = SHA512_CAP_SIGMA0(A) + SHA512_MAJ(A,B,C);
			*/

			temp3[0] = SHA512_MAJ_HIGH(A,B,C);
			temp3[1] = SHA512_MAJ_LOW(A,B,C);

			high = A[0];
			low = A[1];

			SHA_ROTR_64(high, low, 28, Temp_high_out1, Temp_low_out1);
		 	SHA_ROTR_64(low,high, 2, Temp_high_out2, Temp_low_out2);
		   	SHA_ROTR_64(low,high, 7, Temp_high_out3, Temp_low_out3);

			S0[0] = Temp_high_out1 ^ Temp_high_out2 ^  Temp_high_out3;
			S0[1] = Temp_low_out1 ^ Temp_low_out2 ^ Temp_low_out3;
			

			ADD_TWO_32BIT(temp2, temp3,S0);

			

			M2M_MEMCPY(&H, &G, 8);
			M2M_MEMCPY(&G, &F, 8);
			M2M_MEMCPY(&F, &E, 8);
			
			ADD_TWO_32BIT(E, D, temp1);
			
			M2M_MEMCPY(&D, &C, 8);
			M2M_MEMCPY(&C, &B, 8);
			M2M_MEMCPY(&B, &A, 8);
			
			ADD_TWO_32BIT(A, temp1, temp2);		
		}
	

		ADD_TWO_32BIT(pu32Sha512State, pu32Sha512State, A);
		ADD_TWO_32BIT(pu32Sha512State+2, pu32Sha512State+2, B);
		ADD_TWO_32BIT(pu32Sha512State+4, pu32Sha512State+4, C);
		ADD_TWO_32BIT(pu32Sha512State+6, pu32Sha512State+6, D);
		ADD_TWO_32BIT(pu32Sha512State+8, pu32Sha512State+8, E);
		ADD_TWO_32BIT(pu32Sha512State+10, pu32Sha512State+10, F);
		ADD_TWO_32BIT(pu32Sha512State+12, pu32Sha512State+12, G);
		ADD_TWO_32BIT(pu32Sha512State+14, pu32Sha512State+14, H);
	}
}
/*********************************************************************
Function
	Sha_HashUpdate

Description

Return

Author

Version

Date
*********************************************************************/
void Sha_HashUpdate(tstrHash512Context * pstrHashCxt, uint8 * pu8Data, uint32 u32DataLength)
{
	if((pstrHashCxt != NULL) && (pu8Data != NULL) && (u32DataLength != 0))
	{
		if(pstrHashCxt->fpHash != NULL)
		{
			uint32 	u32ResidualBytes;
			uint32 	u32NBlocks;
			uint32 	u32Offset;
			uint32 	u32BlockCount;

			/* Get the remaining bytes from the previous update (if the length is not block alligned). */
			u32ResidualBytes = pstrHashCxt->u32TotalLength % pstrHashCxt->u8BlockSize;

			/* Update the total data length. */
			pstrHashCxt->u32TotalLength += u32DataLength;

			if(u32ResidualBytes != 0)
			{
				if((u32ResidualBytes + u32DataLength) >= pstrHashCxt->u8BlockSize)
				{
					u32Offset = pstrHashCxt->u8BlockSize - u32ResidualBytes;
					M2M_MEMCPY(&pstrHashCxt->au8CurrentBlock[u32ResidualBytes],pu8Data,u32Offset);
					pu8Data += u32Offset;
					u32DataLength -= u32Offset;
					pstrHashCxt->fpHash(pstrHashCxt->au32HashState, pstrHashCxt->au8CurrentBlock);
				}
				else
				{
					M2M_MEMCPY(&pstrHashCxt->au8CurrentBlock[u32ResidualBytes],pu8Data,u32DataLength);
					u32DataLength = 0;
				}
			}

			/* Get the number of HASH BLOCKs and the residual bytes. */
			u32NBlocks = u32DataLength / pstrHashCxt->u8BlockSize;
			u32ResidualBytes = u32DataLength % pstrHashCxt->u8BlockSize;
			for(u32BlockCount = 0 ; u32BlockCount < u32NBlocks ; u32BlockCount ++)
			{
				pstrHashCxt->fpHash(pstrHashCxt->au32HashState, pu8Data);
				pu8Data += pstrHashCxt->u8BlockSize;
			}
			
			if(u32ResidualBytes != 0)
			{
				M2M_MEMCPY(pstrHashCxt->au8CurrentBlock, pu8Data, u32ResidualBytes);
			}	
		}
	}
}
/*********************************************************************
Function
	Sha_HashFinish

Description

Return

Author

Version

Date
*********************************************************************/
void Sha_HashFinish(tstrHash512Context * pstrHashCxt,uint8 *pu8LengthPadding, uint32 u32TotalMessageLength)
{
	if(pstrHashCxt != NULL)
	{
		if(pstrHashCxt->fpHash != NULL)
		{
			uint32 	u32Offset;
			uint32 	u32PaddingLength;

			/* Calculate the offset of the last data byte in the current block. */
			u32Offset = pstrHashCxt->u32TotalLength % pstrHashCxt->u8BlockSize;

			/* Add the padding byte 0x80. */
			pstrHashCxt->au8CurrentBlock[u32Offset ++] = SHA_PAD_BYTE;

			/* Calculate the required padding to complete 
			one Hash Block Size. 
			*/
			u32PaddingLength = pstrHashCxt->u8BlockSize - u32Offset;
			M2M_MEMSET(&pstrHashCxt->au8CurrentBlock[u32Offset],0,u32PaddingLength);

			/* If the padding count is not enough to hold 64-bit representation of 
			the total input message length, one padding block is required.
			*/
			if(u32PaddingLength < u32TotalMessageLength)
			{
				pstrHashCxt->fpHash(pstrHashCxt->au32HashState,pstrHashCxt->au8CurrentBlock);
				M2M_MEMSET(pstrHashCxt->au8CurrentBlock,0,pstrHashCxt->u8BlockSize);
			}
			M2M_MEMCPY(&pstrHashCxt->au8CurrentBlock[pstrHashCxt->u8BlockSize - u32TotalMessageLength],pu8LengthPadding,u32TotalMessageLength);

			pstrHashCxt->fpHash(pstrHashCxt->au32HashState,pstrHashCxt->au8CurrentBlock);
		}
	}
}

/*********************************************************************
Function
	SHA1_Hash

Description

Return

Author

Version

Date
*********************************************************************/
void SHA1_HashSW
(
tstrHash512Context	*pstrSha1Context,
uint8				u8Flags,
uint8 				*pu8Data, 
uint32 				u32DataLength, 
uint8 				*pu8Digest
)
{
	if(pstrSha1Context != NULL)
	{		
		/*======*======*======*======*======*
					SHA1 HASH INITIALIZATION
		*======*======*======*======*======*/
		if(u8Flags & SHA_FLAGS_INIT)
		{
			/* Initialize the Hash Context. */
			M2M_MEMSET(pstrSha1Context, 0, sizeof(tstrHash512Context));

			/* Define SHA1 Specific parameters. */
			pstrSha1Context->fpHash 		= SHA1ProcessBlock;
			pstrSha1Context->u8BlockSize	= SHA_BLOCK_SIZE;
			pstrSha1Context->u8DigestSize 	= SHA1_DIGEST_SIZE;
			
			/* Set the Hash state to the initial value (specified by the standard). */
			pstrSha1Context->au32HashState[0] = 0x67452301;
			pstrSha1Context->au32HashState[1] = 0xEFCDAB89;
			pstrSha1Context->au32HashState[2] = 0x98BADCFE;
			pstrSha1Context->au32HashState[3] = 0x10325476;
			pstrSha1Context->au32HashState[4] = 0xC3D2E1F0;
		}

		/*======*======*======*
				SHA1 HASH UPDATE
		*======*======*======*/
		if((u8Flags & SHA_FLAGS_UPDATE) && (pu8Data != NULL))
		{
			Sha_HashUpdate(pstrSha1Context, pu8Data, u32DataLength);
		}

		/*======*======*======*
				SHA1 HASH FINISH
		*======*======*======*/
		if(u8Flags & SHA_FLAGS_FINISH)
		{
			uint8	u8Idx;
			uint8	u8ByteIdx;
			uint8	au8Tmp[SHA256_MSG_LENGTH];
		
			/* pack the length at the end of the padding block 
			*/
			PUTU32(pstrSha1Context->u32TotalLength >> 29, au8Tmp,0);
			PUTU32(pstrSha1Context->u32TotalLength << 3, au8Tmp, 4);
			Sha_HashFinish(pstrSha1Context,au8Tmp, SHA256_MSG_LENGTH);

			/* compute digest */
			for(u8ByteIdx = 0, u8Idx = 0; u8Idx < (pstrSha1Context->u8DigestSize / 4) ; u8Idx ++)
			{
				PUTU32(pstrSha1Context->au32HashState[u8Idx], pu8Digest, u8ByteIdx);
				u8ByteIdx += 4;
			}
		}
	}
}
/*********************************************************************
Function
	SHA256_HashSW

Description 

Return
	None
	
Author
	Ahmed Ezzat
	
Version

Date
*********************************************************************/
void SHA256_HashSW
(
tstrHash512Context	*pstrSha256Context,
uint8				u8Flags,
uint8				*pu8Data, 
uint32				u32DataLength, 
uint8				*pu8Digest
)
{
	if(pstrSha256Context != NULL)
	{
		/*======*======*======*======*
				SHA256 HASH INITIALIZATION
		*======*======*======*======*/
		if(u8Flags & SHA_FLAGS_INIT)
		{
			/* Initialize the Hash Context. */
			M2M_MEMSET(pstrSha256Context, 0, sizeof(tstrHash512Context));

			/* Define SHA256 specific parameters. */
			pstrSha256Context->fpHash		= SHA256ProcessBlock;
			pstrSha256Context->u8BlockSize	= SHA_BLOCK_SIZE;
			pstrSha256Context->u8DigestSize	= SHA256_DIGEST_SIZE;
			
			/* Set the Hash state to the initial value (specified by the standard). */
			pstrSha256Context->au32HashState[0] = 0x6A09E667;
			pstrSha256Context->au32HashState[1] = 0xBB67AE85;
			pstrSha256Context->au32HashState[2] = 0x3C6EF372;
			pstrSha256Context->au32HashState[3] = 0xA54FF53A;
			pstrSha256Context->au32HashState[4] = 0x510E527F;
			pstrSha256Context->au32HashState[5] = 0x9B05688C;
			pstrSha256Context->au32HashState[6] = 0x1F83D9AB;
			pstrSha256Context->au32HashState[7] = 0x5BE0CD19;
		}
		
		/*======*======*======*
			SHA256 HASH UPDATE
		*======*======*======*/
		if((u8Flags & SHA_FLAGS_UPDATE) && (pu8Data != NULL))
		{
			Sha_HashUpdate(pstrSha256Context, pu8Data, u32DataLength);
		}

		/*======*======*======*
			SHA256 HASH FINISH
		*======*======*======*/
		if((u8Flags & SHA_FLAGS_FINISH) && (pu8Digest != NULL))
		{
			uint8	u8Idx;
			uint8	u8ByteIdx;
			uint8	au8Tmp[SHA256_MSG_LENGTH];
		
			/* pack the length at the end of the padding block 
			*/
			PUTU32(pstrSha256Context->u32TotalLength >> 29, au8Tmp,0);
			PUTU32(pstrSha256Context->u32TotalLength << 3, au8Tmp, 4);
			Sha_HashFinish(pstrSha256Context, au8Tmp, SHA256_MSG_LENGTH);
			
			/* compute digest */
			for(u8ByteIdx = 0, u8Idx = 0; u8Idx < (pstrSha256Context->u8DigestSize / 4) ; u8Idx ++)
			{
				PUTU32(pstrSha256Context->au32HashState[u8Idx], pu8Digest, u8ByteIdx);
				u8ByteIdx += 4;
			}
		}
	}
}
/*********************************************************************
Function
	MD5_Hash

Description 

Return
	None

Author
	Ahmed Ezzat

Version
	1.0

Date
*********************************************************************/
void MD5_HashSW
(
 tstrHash512Context	*pstrMD5Context,
 uint8				u8Flags,
 uint8 				*pu8Data, 
 uint32 			u32DataLength, 
 uint8 				*pu8Digest
 )
{
	if(pstrMD5Context != NULL)
	{
		/*======*======*======*======*
			MD5 HASH INITIALIZATION
		*======*======*======*======*/
		if(u8Flags & SHA_FLAGS_INIT)
		{
			/* Initialize the Hash Context. */
			M2M_MEMSET(pstrMD5Context, 0, sizeof(tstrHash512Context));

			/* Define SHA256 specific parameters. */
			pstrMD5Context->fpHash 			= MD5ProcessBlock;
			pstrMD5Context->u8BlockSize 	= 64;
			pstrMD5Context->u8DigestSize 	= 16;

			pstrMD5Context->au32HashState[0] = 0x67452301;
			pstrMD5Context->au32HashState[1] = 0xEFCDAB89;
			pstrMD5Context->au32HashState[2] = 0x98BADCFE;
			pstrMD5Context->au32HashState[3] = 0x10325476;
		}

		/*======*======*======*
			MD5 HASH UPDATE
		*======*======*======*/
		if((u8Flags & SHA_FLAGS_UPDATE) && (pu8Data != NULL))
		{
			Sha_HashUpdate(pstrMD5Context, pu8Data, u32DataLength);
		}

		/*======*======*======*
			MD5 HASH FINISH
		*======*======*======*/
		if((u8Flags & SHA_FLAGS_FINISH) && (pu8Digest != NULL))
		{
			uint8	au8Tmp[8] 			= {0};
			uint8	u8Idx,u8ByteIdx 	= 0;
			uint32	u32LengthBits 		= pstrMD5Context->u32TotalLength << 3;

			/* pack the length at the end of the padding block */
			au8Tmp[0] = BYTE_0(u32LengthBits);
			au8Tmp[1] = BYTE_1(u32LengthBits);
			au8Tmp[2] = BYTE_2(u32LengthBits);
			au8Tmp[3] = BYTE_3(u32LengthBits);
			
			Sha_HashFinish(pstrMD5Context, au8Tmp, SHA256_MSG_LENGTH);

			/* compute digest */
			for(u8Idx = 0; u8Idx < (MD5_DIGEST_SIZE / 4) ; u8Idx ++)
			{
				pu8Digest[u8ByteIdx ++] = BYTE_0(pstrMD5Context->au32HashState[u8Idx]);
				pu8Digest[u8ByteIdx ++] = BYTE_1(pstrMD5Context->au32HashState[u8Idx]);
				pu8Digest[u8ByteIdx ++] = BYTE_2(pstrMD5Context->au32HashState[u8Idx]);
				pu8Digest[u8ByteIdx ++] = BYTE_3(pstrMD5Context->au32HashState[u8Idx]);
			}
		}
	}
}
/*********************************************************************
Function
	MD4_Hash

Description


Return
	None

Author
	Ahmed Ezzat

Version
	1.0

Date
	3 Oct 2013
*********************************************************************/
void MD4_Hash
(
uint8		*pu8Data, 
uint32		u32DataLength, 
uint8		*pu8Digest
)
{
	if((pu8Data != NULL) && (pu8Digest != NULL))
	{
		tstrHash512Context	strMD4Ctxt;
		uint8				au8Tmp[8]			= {0};
		uint8				u8Idx,u8ByteIdx 	= 0;
		uint32				u32LengthBits		= u32DataLength << 3;

		M2M_MEMSET(&strMD4Ctxt, 0, sizeof(tstrHash512Context));
		strMD4Ctxt.fpHash				= MD4ProcessBlock;
		strMD4Ctxt.u8BlockSize			= 64;
		strMD4Ctxt.u8DigestSize			= 16;

		strMD4Ctxt.au32HashState[0] 	= 0x67452301;
		strMD4Ctxt.au32HashState[1] 	= 0xEFCDAB89;
		strMD4Ctxt.au32HashState[2] 	= 0x98BADCFE;
		strMD4Ctxt.au32HashState[3] 	= 0x10325476;

		Sha_HashUpdate(&strMD4Ctxt, pu8Data, u32DataLength);

	
		/* pack the length at the end of the padding block */
		au8Tmp[0] = BYTE_0(u32LengthBits);
		au8Tmp[1] = BYTE_1(u32LengthBits);
		au8Tmp[2] = BYTE_2(u32LengthBits);
		au8Tmp[3] = BYTE_3(u32LengthBits);
		
		Sha_HashFinish(&strMD4Ctxt, au8Tmp, SHA256_MSG_LENGTH);
		
		/* compute digest */
		for(u8Idx = 0; u8Idx < (MD4_DIGEST_SIZE / 4) ; u8Idx ++)
		{
			pu8Digest[u8ByteIdx ++] = BYTE_0(strMD4Ctxt.au32HashState[u8Idx]);
			pu8Digest[u8ByteIdx ++] = BYTE_1(strMD4Ctxt.au32HashState[u8Idx]);
			pu8Digest[u8ByteIdx ++] = BYTE_2(strMD4Ctxt.au32HashState[u8Idx]);
			pu8Digest[u8ByteIdx ++] = BYTE_3(strMD4Ctxt.au32HashState[u8Idx]);
		}
	}
}

/*********************************************************************
Function
	SHA256_HashSW

Description 

Return
	None
	
Author
	Ahmed Ezzat
	
Version

Date
*********************************************************************/
void SHA224_HashSW
(
tstrHash512Context	*pstrSha224Cxt,
uint8				u8Flags,
uint8				*pu8Data, 
uint32				u32DataLength, 
uint8				*pu8Digest
)
{
	if(pstrSha224Cxt != NULL)
	{
		/*======*======*======*======*
				SHA256 HASH INITIALIZATION
		*======*======*======*======*/
		if(u8Flags & SHA_FLAGS_INIT)
		{
			/* Initialize the Hash Context. */
			M2M_MEMSET(pstrSha224Cxt , 0, sizeof(tstrHash512Context));

			/* Define SHA256 specific parameters. */
			pstrSha224Cxt->fpHash		= SHA256ProcessBlock;
			pstrSha224Cxt->u8BlockSize	= SHA_BLOCK_SIZE;
			pstrSha224Cxt->u8DigestSize	= SHA224_DIGEST_SIZE;
			
			/* Set the Hash state to the initial value (specified by the standard). */
			pstrSha224Cxt->au32HashState[0] = 0xc1059ed8;
			pstrSha224Cxt->au32HashState[1] = 0x367cd507;
			pstrSha224Cxt->au32HashState[2] = 0x3070dd17;
			pstrSha224Cxt->au32HashState[3] = 0xf70e5939;
			pstrSha224Cxt->au32HashState[4] = 0xffc00b31;
			pstrSha224Cxt->au32HashState[5] = 0x68581511;
			pstrSha224Cxt->au32HashState[6] = 0x64f98fa7;
			pstrSha224Cxt->au32HashState[7] = 0xbefa4fa4;
		}
		
		/*======*======*======*
			SHA256 HASH UPDATE
		*======*======*======*/
		if((u8Flags & SHA_FLAGS_UPDATE) && (pu8Data != NULL))
		{
			Sha_HashUpdate(pstrSha224Cxt, pu8Data, u32DataLength);
		}

		/*======*======*======*
			SHA256 HASH FINISH
		*======*======*======*/
		if((u8Flags & SHA_FLAGS_FINISH) && (pu8Digest != NULL))
		{
			uint8	u8Idx;
			uint8	u8ByteIdx;
			uint8	au8Tmp[SHA256_MSG_LENGTH];
		
			/* pack the length at the end of the padding block 
			*/
			PUTU32(pstrSha224Cxt->u32TotalLength >> 29, au8Tmp,0);
			PUTU32(pstrSha224Cxt->u32TotalLength << 3, au8Tmp, 4);
			Sha_HashFinish(pstrSha224Cxt, au8Tmp, SHA256_MSG_LENGTH);
			
			/* compute digest */
			for(u8ByteIdx = 0, u8Idx = 0; u8Idx < (pstrSha224Cxt->u8DigestSize / 4) ; u8Idx ++)
			{
				PUTU32(pstrSha224Cxt->au32HashState[u8Idx], pu8Digest, u8ByteIdx);
				u8ByteIdx += 4;
			}
		}
	}
}
/*********************************************************************
Function
	SHA512_HashSW

Description 

Return
	None
	
Author
	
Version

Date
*********************************************************************/
void SHA512_HashSW
(
tstrHash512Context	*pstrSha512Context,
uint8				u8Flags,
uint8				*pu8Data, 
uint32				u32DataLength, 
uint8				*pu8Digest,
uint8				u8IsSHA384
)
{
	if(pstrSha512Context != NULL)
	{
		/*======*======*======*======*
				SHA512 HASH INITIALIZATION
		*======*======*======*======*/
		if(u8Flags & SHA_FLAGS_INIT)
		{
			/* Initialize the Hash Context. */
			M2M_MEMSET(pstrSha512Context, 0, sizeof(tstrHash512Context));

			/* Define SHA256 specific parameters. */
			pstrSha512Context->fpHash = SHA512ProcessBlock;
			pstrSha512Context->u8BlockSize = SHA512_BLOCK_SIZE;

			if(!u8IsSHA384)
				pstrSha512Context->u8DigestSize = SHA512_DIGEST_SIZE;
			else
				pstrSha512Context->u8DigestSize = SHA384_DIGEST_SIZE;

			
			/* Set the Hash state to the initial value (specified by the standard). */
			if(!u8IsSHA384)
			{
				/* SHA-512 */
				pstrSha512Context->au32HashState[0] = 0x6A09E667;
				pstrSha512Context->au32HashState[1] = 0xF3BCC908;
				
				pstrSha512Context->au32HashState[2] = 0xBB67AE85;
				pstrSha512Context->au32HashState[3] = 0x84CAA73B;

				pstrSha512Context->au32HashState[4] = 0x3C6EF372;
				pstrSha512Context->au32HashState[5] = 0xFE94F82B;

				pstrSha512Context->au32HashState[6] = 0xA54FF53A;
				pstrSha512Context->au32HashState[7] = 0x5F1D36F1;

				pstrSha512Context->au32HashState[8] = 0x510E527F;
				pstrSha512Context->au32HashState[9] = 0xADE682D1;
								
				pstrSha512Context->au32HashState[10] = 0x9B05688C;
				pstrSha512Context->au32HashState[11] = 0x2B3E6C1F;
				
				pstrSha512Context->au32HashState[12] = 0x1F83D9AB;
				pstrSha512Context->au32HashState[13] = 0xFB41BD6B;

				pstrSha512Context->au32HashState[14] = 0x5BE0CD19;
				pstrSha512Context->au32HashState[15] = 0x137E2179;
			}
			else
			{
				/* SHA-384 */
				pstrSha512Context->au32HashState[0] = 0xCBBB9D5D;
				pstrSha512Context->au32HashState[1] = 0xC1059ED8;

				pstrSha512Context->au32HashState[2] = 0x629A292A;
				pstrSha512Context->au32HashState[3] = 0x367CD507;

				pstrSha512Context->au32HashState[4] = 0x9159015A;
				pstrSha512Context->au32HashState[5] = 0x3070DD17;

				pstrSha512Context->au32HashState[6] = 0x152FECD8;
				pstrSha512Context->au32HashState[7] = 0xF70E5939;

				pstrSha512Context->au32HashState[8] = 0x67332667;
				pstrSha512Context->au32HashState[9] = 0xFFC00B31;

				pstrSha512Context->au32HashState[10] = 0x8EB44A87;
				pstrSha512Context->au32HashState[11] = 0x68581511;

				pstrSha512Context->au32HashState[12] = 0xDB0C2E0D;
				pstrSha512Context->au32HashState[13] = 0x64F98FA7;

				pstrSha512Context->au32HashState[14] = 0x47B5481D;
				pstrSha512Context->au32HashState[15] = 0xBEFA4FA4;
				
			}
		}
		
		/*======*======*======*
			SHA512 HASH UPDATE
		*======*======*======*/
		if((u8Flags & SHA_FLAGS_UPDATE) && (pu8Data != NULL))
		{
			Sha_HashUpdate(pstrSha512Context, pu8Data, u32DataLength);
		}

		/*======*======*======*
			SHA512 HASH FINISH
		*======*======*======*/
		if((u8Flags & SHA_FLAGS_FINISH) && (pu8Digest != NULL))
		{
			uint8	u8Idx;
			uint8	u8ByteIdx;
			uint8	au8Tmp[SHA512_MSG_LENGTH]	= {0};

			/* pack the length at the end of the padding block */
			PUTU32(pstrSha512Context->u32TotalLength >> 29, au8Tmp,0);
			PUTU32(pstrSha512Context->u32TotalLength << 3, au8Tmp, 12);
			Sha_HashFinish(pstrSha512Context, au8Tmp, SHA512_MSG_LENGTH);

			/* compute digest */
			for(u8ByteIdx = 0, u8Idx = 0; u8Idx < (pstrSha512Context->u8DigestSize / 4) ; u8Idx ++)
			{
				PUTU32(pstrSha512Context->au32HashState[u8Idx], pu8Digest, u8ByteIdx);
				u8ByteIdx += 4;
			}
		}
	}
}
/*********************************************************************
Function
	HMAC_Vector

Description
	Perform the HMAC operation on a given vector of data streams using the 
	hash function passed to the HMAC_Vector.

Return
	None.

Author
	Ahmed Ezzat

Version
	1.0

Date
	March 2013
*********************************************************************/
void HMAC_Vector
(
tenuHashAlg 	enuHashAlg,
uint8			*pu8Key,
uint32 			u32KeyLength,
tstrBuffer		*pstrInData,
uint8			u8NumInputs,
uint8			*pu8Out
)
{
	if((pu8Key != NULL) && (pstrInData != NULL) && (pu8Out != NULL) && (enuHashAlg < HASH_ALG_MAX) && (enuHashAlg > HASH_ALG_NONE))
	{
		uint32 				i;
		tpfHash				fpHash;
		uint16				u16HashSz;
		uint16				u16BlockSz;
		tstrShaHashContext	strHashContext;
		uint8				au8TmpBuffer[SHA512_BLOCK_SIZE];
		uint8				au8TmpHash[SHA_MAX_DIGEST_SIZE];
		uint8				au8TmpKey[SHA_MAX_DIGEST_SIZE];
		
		/*=*=*=*=*=*=*=*=*=*=*=*
				HMAC INIT
		*=*=*=*=*=*=*=*=*=*=*=*/

		fpHash		= eastrTlsHashes[enuHashAlg].fpHash;
		u16HashSz	= eastrTlsHashes[enuHashAlg].u16HashSz;
		u16BlockSz	= eastrTlsHashes[enuHashAlg].u16BlockSz;
		
		/* Adjust the key size. */
		if(u32KeyLength > u16BlockSz)
		{
			fpHash(&strHashContext, SHA_FLAGS_FULL_HASH, pu8Key, u32KeyLength, au8TmpKey);
			pu8Key			= au8TmpKey;
			u32KeyLength	= u16HashSz;
		}
		
		M2M_MEMSET(au8TmpBuffer, 0x36, u16BlockSz);
		for(i = 0; i< u32KeyLength ; i++)
		{
			au8TmpBuffer[i] ^= pu8Key[i];
		}

		/* Start hashing. */
		fpHash(&strHashContext , SHA_FLAGS_INIT | SHA_FLAGS_UPDATE, au8TmpBuffer, u16BlockSz, NULL);

		/*=*=*=*=*=*=*=*=*=*=*=*=*
				HMAC UPDATE
		*=*=*=*=*=*=*=*=*=*=*=*=*/
		for(i = 0 ; i < u8NumInputs ; i ++)
		{
			fpHash(
				&strHashContext , SHA_FLAGS_UPDATE , 
				pstrInData[i].pu8Data , pstrInData[i].u16BufferSize , NULL);
		}
		
		fpHash(
			&strHashContext , SHA_FLAGS_FINISH, 
			NULL, 0, au8TmpHash);
		
		/*=*=*=*=*=*=*=*=*=*=*=*=*=*
				HMAC Finalize
		*=*=*=*=*=*=*=*=*=*=*=*=*=*/		
		M2M_MEMSET(au8TmpBuffer, 0x5C, u16BlockSz);
		for(i = 0; i< u32KeyLength ; i++)
		{
			au8TmpBuffer[i] ^= pu8Key[i];
		}

		fpHash(&strHashContext, SHA_FLAGS_INIT | SHA_FLAGS_UPDATE, au8TmpBuffer, u16BlockSz, NULL);
		fpHash(&strHashContext, SHA_FLAGS_UPDATE | SHA_FLAGS_FINISH, au8TmpHash, u16HashSz, pu8Out);
	}
}
/*********************************************************************
Function
		hmac_md5

Description
		

Return
		None.

Author
		Ahmed Ezzat

Version
		1.0

Date
		14 April 2013
*********************************************************************/
void hmac_md5
(	
uint8	*pu8Data, 
uint32 	u32DataLength, 
uint8	*pu8Key, 
uint32 	u32KeyLength,
uint8	*pu8Digest
)
{
	tstrBuffer	strIn;
	strIn.pu8Data		= pu8Data;
	strIn.u16BufferSize	= u32DataLength;
	HMAC_Vector(HASH_ALG_MD5,pu8Key,u32KeyLength,&strIn,1,pu8Digest);
}
/*********************************************************************
Function
		hmac_sha1

Description
		

Return
		None.

Author
		Ahmed Ezzat

Version
		1.0

Date
		14 April 2013
*********************************************************************/
void hmac_sha1
(	
uint8		*pu8Key, 
uint32 	u32KeyLength,
uint8		*pu8Data, 
uint32 	u32DataLength, 
uint8		*pu8Digest
)
{
	tstrBuffer	strIn;
	strIn.pu8Data 		= pu8Data;
	strIn.u16BufferSize	= u32DataLength;
	HMAC_Vector(HASH_ALG_SHA1,pu8Key,u32KeyLength,&strIn,1,pu8Digest);
}
/*********************************************************************
Function
		HMAC_SHA256

Description
		

Return
		None.

Author
		Ahmed Ezzat

Version
		1.0

Date
		15 April 2013
*********************************************************************/
void HMAC_SHA256
(
uint8 	*pu8Data, 
uint32 	u32DataLength, 
uint8 	*pu8Key, 
uint32 	u32KeyLength, 
uint8 	*pu8Digest
)
{
	tstrBuffer	strIn;
	strIn.pu8Data 		= pu8Data;
	strIn.u16BufferSize	= u32DataLength;
	HMAC_Vector(HASH_ALG_SHA256,pu8Key,u32KeyLength,&strIn,1,pu8Digest);
}
/*********************************************************************
Function
	MD5_Hash

Description

Return
	None.

Author
	Ahmed Ezzat

Version
	1.0

Date
	15 June 2016
*********************************************************************/
void MD5_Hash
(
tstrShaHashContext	*pstrMD5Cxt,
uint8				u8Flags,
uint8 				*pu8Data,
uint32 				u32DataLength,
uint8 				*pu8Digest
)
{
	MD5_HASH_SW(pstrMD5Cxt, u8Flags, pu8Data, u32DataLength, pu8Digest);
}
/*********************************************************************
Function
	SHA1_Hash

Description

Return
	None.

Author
	Ahmed Ezzat

Version
	1.0

Date
	15 June 2016
*********************************************************************/
void SHA1_Hash
(
tstrShaHashContext	*pstrSha1Cxt,
uint8				u8Flags,
uint8 				*pu8Data,
uint32 				u32DataLength,
uint8 				*pu8Digest
)
{
	SHA1_HASH_SW(pstrSha1Cxt, u8Flags, pu8Data, u32DataLength, pu8Digest);
}
/*********************************************************************
Function
	SHA224_Hash

Description 

Return
	None
	
Author
	Abdelrahman Diab
	
Version

Date
	15 June 2016
*********************************************************************/
void SHA224_Hash
(
tstrShaHashContext	*pstrSha224Cxt,
uint8				u8Flags,
uint8				*pu8Data, 
uint32				u32DataLength, 
uint8				*pu8Digest
)
{
	SHA224_HASH_SW(pstrSha224Cxt, u8Flags, pu8Data, u32DataLength, pu8Digest);
}
/*********************************************************************
Function
	SHA256_Hash

Description 

Return
	None
	
Author
	Ahmed Ezzat
	
Version

Date
	15 June 2016
*********************************************************************/
void SHA256_Hash
(
tstrShaHashContext 	*pstrSha256Cxt,
uint8				u8Flags,
uint8				*pu8Data, 
uint32				u32DataLength, 
uint8				*pu8Digest
)
{
	SHA256_HASH_SW(pstrSha256Cxt, u8Flags, pu8Data, u32DataLength, pu8Digest);
}
/*********************************************************************
Function
	SHA384_Hash

Description 

Return
	None
	
Author
	Abdelrahman Diab
	
Version

Date

*********************************************************************/
void SHA384_Hash
(
tstrShaHashContext 	*pstrSha384Cxt,
uint8				u8Flags,
uint8				*pu8Data, 
uint32				u32DataLength, 
uint8				*pu8Digest
)
{
	SHA384_HASH_SW(pstrSha384Cxt, u8Flags, pu8Data, u32DataLength, pu8Digest);
}
/*********************************************************************
Function
	SHA512_Hash

Description 

Return
	None
	
Author
	Abdelrahman Diab
	
Version

Date

*********************************************************************/
void SHA512_Hash
(
tstrShaHashContext	*pstrSha512Cxt,
uint8				u8Flags,
uint8				*pu8Data, 
uint32				u32DataLength, 
uint8				*pu8Digest
)
{
	SHA512_HASH_SW(pstrSha512Cxt, u8Flags, pu8Data, u32DataLength, pu8Digest);
}