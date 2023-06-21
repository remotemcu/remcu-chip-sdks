/**
 * \file FIPS-197 AES-128 software library source file 
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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
 /**
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "aes.h"

/* Global Variables declaration*/

/*  S-box in hexadecimal format */
uint8_t sbox[256] =   { 
	//0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
	0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,  //0
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,  //1
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,  //2
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,  //3
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,  //4
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,  //5
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,  //6
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,  //7
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,  //8
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,  //9
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,  //A
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,  //B
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,  //C
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,  //D
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,  //E
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16   //F
};   

/* Inverse S-box in hexadecimal format */
uint8_t inv_sbox[256] = {
	//0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,  //0
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,  //1
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,  //2
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,  //3
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,  //4
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,  //5
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,  //6
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,  //7
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,  //8
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,  //9
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,  //A
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,  //B
	0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,  //C
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,  //D
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,  //E
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d   //F
}; 

/* Round constant for Key Expansion */
uint8_t RCon[11] = {
	0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

/* Array to store values after key expansion */
uint8_t key_schedule[AES_KEY_SCHEDULE_SIZE];

/* Check if the key is ready */
bool aes_key_ready = false;


/*! \brief Performs key expansion to generate key schedule
 * from initial set of Key of 4 words.
 * \param round_key  Holds the pointer to store key schedule 
 * \param key        Initial Key received from the user
 */
void KeyExpansion(uint8_t *round_key, uint8_t *key)
{
	uint8_t i, temp;

	//Retain the initial for round 0
	for ( i = 0; i < 16; i++){
		round_key[ i ] = key[ i ];
	}

	// Compute Key schedule of block size for each round
	for ( i = 1; i < (AES_NUM_OF_ROUNDS + 1); i++){
		temp = round_key[ i*16 - 4 ];
		round_key[i*16 +  0] = sbox[ round_key[i*16 - 3] ] ^ round_key[(i-1)*16 + 0] ^ RCon[ i ];
		round_key[i*16 +  1] = sbox[ round_key[i*16 - 2] ] ^ round_key[(i-1)*16 + 1];
		round_key[i*16 +  2] = sbox[ round_key[i*16 - 1] ] ^ round_key[(i-1)*16 + 2];
		round_key[i*16 +  3] = sbox[ temp ] ^ round_key[ (i-1)*16 + 3 ];

		round_key[i*16 +  4] = round_key[(i-1)*16 + 4] ^ round_key[i*16 + 0];
		round_key[i*16 +  5] = round_key[(i-1)*16 + 5] ^ round_key[i*16 + 1];
		round_key[i*16 +  6] = round_key[(i-1)*16 + 6] ^ round_key[i*16 + 2];
		round_key[i*16 +  7] = round_key[(i-1)*16 + 7] ^ round_key[i*16 + 3];

		round_key[i*16 +  8] = round_key[(i-1)*16 + 8] ^ round_key[i*16 + 4];
		round_key[i*16 +  9] = round_key[(i-1)*16 + 9] ^ round_key[i*16 + 5];
		round_key[i*16 + 10] = round_key[(i-1)*16 +10] ^ round_key[i*16 + 6];
		round_key[i*16 + 11] = round_key[(i-1)*16 +11] ^ round_key[i*16 + 7];

		round_key[i*16 + 12] = round_key[(i-1)*16 +12] ^ round_key[i*16 + 8];
		round_key[i*16 + 13] = round_key[(i-1)*16 +13] ^ round_key[i*16 + 9];
		round_key[i*16 + 14] = round_key[(i-1)*16 +14] ^ round_key[i*16 +10];
		round_key[i*16 + 15] = round_key[(i-1)*16 +15] ^ round_key[i*16 +11];
	}
}

/*! \brief xtime calculation
 * The value is multiplied by 0x02. This 
 * is implemented at the byte level as a
 * left shift and XOR with 0x1b if the MSB 
 * of the value (before) shifting is 1.
 * \param value  Value for which multiplication to be done
 */
uint8_t xtime(uint8_t value)
{
	if ( value >> 7 ){
		value = value << 1;
		return ( value ^ 0x1b );
	}else{
		return value << 1;
	}
}

/*! \brief Performs Sub Byte (from sbox array) and Shift rows operation.
 * \param state  variable to store the intermediate result of the algorithm
 */
void SubBytes_ShiftRows(uint8_t *state)
{
	uint8_t temp1 = 0,temp2 = 0;

	// row 0
	state[0]  = sbox[ state[0] ];
	state[4]  = sbox[ state[4] ];
	state[8]  = sbox[ state[8] ];
	state[12] = sbox[ state[12] ];

	// row 1
	temp1 = sbox[ state[1] ];
	state[1]  = sbox[ state[5] ];
	state[5]  = sbox[ state[9] ];
	state[9]  = sbox[ state[13]];
	state[13] = temp1;

	// row 2
	temp1 = sbox[ state[2]];
	temp2 = sbox[ state[6]];
	state[2]  = sbox[ state[10] ];
	state[6]  = sbox[ state[14] ];
	state[10] = temp1;
	state[14] = temp2;

	// row 3
	temp1 = sbox[ state[15] ];
	state[15]  = sbox[ state[11] ];
	state[11]  = sbox[ state[7] ];
	state[7]  = sbox[ state[3] ];
	state[3]  = temp1;
}

/*! \brief Performs Mix Columns Operation
 * \param state  variable to store the intermediate result of the algorithm
 */
void MixColumnns(uint8_t *state)
{
	uint8_t temp1 = 0,temp2 = 0,temp3 = 0;

	// col 1
	temp1 = state[0] ^ state[1] ^ state[2] ^ state[3];
	temp2 = state[0];
	temp3 = state[0] ^ state[1];
	temp3 = xtime( temp3 );
	state[0] = state[0] ^ temp3 ^ temp1;
	temp3 = state[1] ^ state[2];
	temp3 = xtime( temp3 );
	state[1] = state[1] ^ temp3 ^ temp1;
	temp3 = state[2] ^ state[3];
	temp3 = xtime( temp3 );
	state[2] = state[2] ^ temp3 ^ temp1;
	temp3 = state[3] ^ temp2;
	temp3 = xtime( temp3 );
	state[3] = state[3] ^ temp3 ^ temp1;

	// col 2
	temp1 = state[4] ^ state[5] ^ state[6] ^ state[7];
	temp2 = state[4];
	temp3 = state[4] ^state[5];
	temp3 = xtime( temp3 );
	state[4] = state[4] ^ temp3 ^ temp1;
	temp3 = state[5] ^state[6];
	temp3 = xtime( temp3 );
	state[5] = state[5] ^ temp3 ^ temp1;
	temp3 = state[6] ^ state[7];
	temp3 = xtime( temp3 );
	state[6] = state[6] ^ temp3 ^ temp1;
	temp3 = state[7] ^ temp2;
	temp3 = xtime( temp3 );
	state[7] = state[7] ^ temp3 ^ temp1;

	// col 3
	temp1 = state[8] ^ state[9] ^ state[10] ^ state[11];
	temp2 = state[8];
	temp3 = state[8] ^ state[9];
	temp3 = xtime( temp3 );
	state[8] = state[8] ^ temp3 ^ temp1;
	temp3 = state[9] ^ state[10];
	temp3 = xtime( temp3 );
	state[9] = state[9] ^ temp3 ^ temp1;
	temp3 = state[10]^state[11];
	temp3 = xtime( temp3 );
	state[10] = state[10] ^ temp3 ^ temp1;
	temp3 = state[11] ^ temp2;
	temp3 = xtime( temp3 );
	state[11] = state[11] ^ temp3 ^ temp1;

	// col 4
	temp1 = state[12 ] ^ state[13] ^ state[14] ^ state[15];
	temp2 = state[12];
	temp3 = state[12] ^ state[13];
	temp3 = xtime( temp3 );
	state[12] = state[12] ^ temp3 ^ temp1;
	temp3 = state[13] ^ state[14];
	temp3 = xtime( temp3 );
	state[13] = state[13] ^ temp3 ^ temp1;
	temp3 = state[14] ^ state[15];
	temp3 = xtime( temp3 );
	state[14] = state[14] ^ temp3 ^ temp1;
	temp3 = state[15] ^ temp2;
	temp3 = xtime( temp3 );
	state[15] = state[15] ^ temp3 ^ temp1;
}

/*! \brief Performs Add RoundKey  operation.
 * \param state  variable to store the intermediate result of the algorithm
 */
void AddRoundKey(uint8_t *state, uint8_t round)
{
	// row 0
	state[0]  =  ( state[0] ^ key_schedule[(round * 16)] );
	state[4]  =  ( state[4] ^ key_schedule[(round * 16) + 4] );
	state[8]  =  ( state[8] ^ key_schedule[(round * 16) + 8] );
	state[12] =  ( state[12] ^ key_schedule[(round * 16) + 12] );

	// row 1
	state[1]  =  ( state[1] ^ key_schedule[(round * 16) + 1] );
	state[5]  =  ( state[5] ^ key_schedule[(round * 16) + 5] );
	state[9]  =  ( state[9] ^ key_schedule[(round * 16) + 9] );
	state[13] =  ( state[13] ^ key_schedule[(round * 16) +13] );

	// row 2
	state[2]  =  ( state[2] ^ key_schedule[(round * 16) + 2] );
	state[6]  =  ( state[6] ^ key_schedule[(round * 16) + 6] );
	state[10] =  ( state[10] ^ key_schedule[(round * 16) + 10] );
	state[14] =  ( state[14] ^ key_schedule[(round * 16) + 14] );

	// row 3
	state[3]  =  ( state[3] ^ key_schedule[(round * 16) + 3] );
	state[7]  =  ( state[7] ^ key_schedule[(round * 16) + 7] );
	state[11] =  ( state[11] ^ key_schedule[(round * 16) + 11] );
	state[15] =  ( state[15] ^ key_schedule[(round * 16) + 15] );

}

/*! \brief Performs Inverse of sub bytes (from inverse sub-box)
 * and shift rows operation.
 * \param state  variable to store the intermediate result of the algorithm
 */
void Inv_ShiftRows_SubBytes(uint8_t *state)
{

	uint8_t temp1 = 0,temp2 = 0;

	// row 0
	state[0] = inv_sbox[ state[0] ];
	state[4] = inv_sbox[ state[4] ];
	state[8] = inv_sbox[ state[8] ];
	state[12] = inv_sbox[ state[12] ];

	// row 1
	temp1 = inv_sbox[ state[13] ];
	state[13] = inv_sbox[ state[9] ];
	state[9] = inv_sbox[ state[5] ];
	state[5] = inv_sbox[ state[1] ];
	state[1] = temp1;

	// row 2
	temp1 = inv_sbox[ state[2] ] ;
	temp2 = inv_sbox[ state[6] ] ;
	state[2] = inv_sbox[ state[10] ] ;
	state[6] = inv_sbox[ state[14] ] ;
	state[10] = temp1;
	state[14] = temp2;

	// row 3
	temp1 = inv_sbox[ state[3] ];
	state[3] = inv_sbox[ state[7] ];
	state[7] = inv_sbox[ state[11] ] ;
	state[11] = inv_sbox[ state[15] ] ;
	state[15] = temp1;
}

/*! \brief Performs AddRound Key
 * \param state  variable to store the intermediate result of the algorithm
 * \note inverse of Add round key and Add round key are same.Two separate 
 * functions are defined for ease of understanding the encryption and 
 * decryption process. 
 */
void Inv_AddRoundKey(uint8_t *state, uint8_t round)
{
	// row 0
	state[0]  =  ( state[0] ^ key_schedule[(round * 16)] );
	state[4]  =  ( state[4] ^ key_schedule[(round * 16) + 4] );
	state[8]  =  ( state[8] ^ key_schedule[(round * 16) + 8] );
	state[12] =  ( state[12] ^ key_schedule[(round * 16) + 12] );

	// row 1
	state[1]  =  ( state[1] ^ key_schedule[(round * 16) + 1] );
	state[5]  =  ( state[5] ^ key_schedule[(round * 16) + 5] );
	state[9]  =  ( state[9] ^ key_schedule[(round * 16) + 9] );
	state[13] =  ( state[13] ^ key_schedule[(round * 16) +13] );

	// row 2
	state[2]  =  ( state[2] ^ key_schedule[(round * 16) + 2] );
	state[6]  =  ( state[6] ^ key_schedule[(round * 16) + 6] );
	state[10] =  ( state[10] ^ key_schedule[(round * 16) + 10] );
	state[14] =  ( state[14] ^ key_schedule[(round * 16) + 14] );

	// row 3
	state[3]  =  ( state[3] ^ key_schedule[(round * 16) + 3] );
	state[7]  =  ( state[7] ^ key_schedule[(round * 16) + 7] );
	state[11] =  ( state[11] ^ key_schedule[(round * 16) + 11] );
	state[15] =  ( state[15] ^ key_schedule[(round * 16) + 15] );

}


/*! \brief Performs Inverse  Mix Columns operation
 * \param state  variable to store the intermediate result of the algorithm
 * \param Number of current ongoing round in AES algorithm
 */
void Inv_MixColumns(uint8_t *state, uint8_t round)
{
	uint8_t temp1 = 0,temp2 = 0,temp3 = 0;

	//col1
	temp1 = xtime( xtime( state[0] ^ state[2] ) );
	temp2 = xtime( xtime( state[1] ^ state[3] ) );
	state[0] ^= temp1;
	 state[1] ^= temp2;
	state[2] ^= temp1;
	state[3] ^= temp2;

	//col2
	temp1 = xtime( xtime( state[4] ^ state[6] ) );
	temp2 = xtime( xtime( state[5] ^ state[7] ) );
	state[4] ^= temp1;
	state[5] ^= temp2;
	state[6] ^= temp1;
	state[7] ^= temp2;

	//col3
	temp1 = xtime( xtime( state[8] ^ state[10] ) );
	temp2 = xtime( xtime( state[9] ^ state[11] ) );
	state[8] ^= temp1;
	state[9] ^= temp2;
	state[10] ^= temp1;
	state[11] ^= temp2;

	//col4
	temp1 = xtime( xtime( state[12] ^ state[14] ) );
	temp2 = xtime( xtime( state[13] ^ state[15] ) );
	 state[12] ^= temp1;
	 state[13] ^= temp2;
	 state[14] ^= temp1;
	state[15] ^= temp2;

	// col1
	temp1 = state[0] ^ state[1] ^ state[2] ^ state[3];
	temp2 = state[0];
	temp3 = state[0] ^ state[1];
	temp3 = xtime( temp3 );
	state[0] = state[0] ^ temp3 ^ temp1;
	temp3 = state[1] ^ state[2];
	temp3 = xtime( temp3 );
	state[1] = state[1] ^ temp3 ^ temp1;
	temp3 = state[2] ^ state[3];
	temp3 = xtime( temp3 );
	state[2] = state[2] ^ temp3 ^ temp1;
	temp3 = state[3] ^ temp2;
	temp3 = xtime( temp3 );
	state[3] = state[3] ^ temp3 ^ temp1;

	// col2
	temp1 = state[4] ^ state[5] ^ state[6] ^ state[7];
	temp2 = state[4];
	temp3 = state[4] ^ state[5];
	temp3 = xtime( temp3 );
	state[4] = state[4] ^ temp3 ^ temp1;
	temp3 = state[5] ^ state[6];
	temp3 = xtime( temp3 );
	state[5] = state[5] ^ temp3 ^ temp1;
	temp3 = state[6] ^ state[7];
	temp3 = xtime( temp3 );
	state[6] = state[6] ^ temp3 ^ temp1;
	temp3 = state[7] ^ temp2;
	temp3 = xtime( temp3 );
	state[7] = state[7] ^ temp3 ^ temp1;

	// col3
	temp1 = state[8] ^ state[9] ^ state[10] ^ state[11];
	temp2 = state[8];
	temp3 = state[8] ^state[9];
	temp3 = xtime( temp3 );
	state[8] = state[8] ^ temp3 ^ temp1;
	temp3 = state[9] ^ state[10];
	temp3 = xtime( temp3 );
	state[9] = state[9] ^ temp3 ^ temp1;
	temp3 = state[10] ^ state[11];
	temp3 = xtime( temp3 );
	state[10] = state[10] ^ temp3 ^ temp1;
	temp3 = state[11] ^ temp2;
	temp3 = xtime( temp3 );
	state[11] = state[11] ^ temp3 ^ temp1;

	// col4
	temp1 = state[12] ^ state[13] ^ state[14] ^ state[15];
	temp2 = state[12];
	temp3 = state[12] ^ state[13];
	temp3 = xtime( temp3 );
	state[12] = state[12] ^ temp3 ^ temp1;
	temp3 = state[13]^state[14];
	temp3 = xtime( temp3 );
	state[13] = state[13] ^ temp3 ^ temp1;
	temp3 = state[14] ^ state[15];
	temp3 = xtime( temp3 );
	state[14] = state[14] ^ temp3 ^ temp1;
	temp3 = state[15] ^ temp2;
	temp3 = xtime( temp3 );
	state[15] = state[15] ^ temp3 ^ temp1;
}

/*! \brief Performs Key Expansion 
 * \param key  Initial Key vectors received from user
 */
void aes_init(uint8_t *key)
{
	KeyExpansion(key_schedule, key);
	// Set key ready flag to true to indicate key is ready for AES algorithm
	aes_key_ready = true;
}

/*! \brief Performs AES-128 Encryption
 * \param plainText  Input plain text block
 * \param state Variable to store the intermediate result 
 * \retval ERR_NO_KEY if key expansion is not done via aes_init()
 * \retval STATUS_OKAY if aes_init() is called before this function.
 */
aes_ret_status_t aes_cipher(uint8_t *plainText, uint8_t *state)
{
	uint8_t byte_count = 0;
	uint8_t  round = 0;
	

	// Check if the aes_init() is called for key expansion
	if(aes_key_ready != true)
		return ERR_NO_KEY;

	//Copy input buffer to state to form the cipher state
	for (byte_count =0; byte_count < AES_BLOCK_SIZE; byte_count++){
	state[byte_count] = plainText[byte_count];
	}


	// Round 0 
	state[0] ^= key_schedule[0];
	state[1] ^= key_schedule[1];
	state[2] ^= key_schedule[2];
	state[3] ^= key_schedule[3];
	state[4] ^= key_schedule[4];
	state[5] ^= key_schedule[5];
	state[6] ^= key_schedule[6];
	state[7] ^= key_schedule[7];
	state[8] ^= key_schedule[8];
	state[9] ^= key_schedule[9];
	state[10] ^= key_schedule[10];
	state[11] ^= key_schedule[11];
	state[12] ^= key_schedule[12];
	state[13] ^= key_schedule[13];
	state[14] ^= key_schedule[14]; 
	state[15] ^= key_schedule[15];

	//Round 1 to 9
	for (round = 1; round < 10; round ++){
		/* Sub Bytes and Shift Rows */
		SubBytes_ShiftRows(state);
		/* Mix Columns */
		MixColumnns(state);
		/* Add RoundKey */
		AddRoundKey(state,round);
	}

	// 10th round without mix columns
	round = 10;

	/* Sub Bytes and Shift Rows */
	SubBytes_ShiftRows(state);
	/* Add RoundKey */
	AddRoundKey(state,round);

	return STATUS_OKAY;
} 

/*! \brief Performs AES-128 Decryption
 * \param cipherText  Input cipher text block
 * \param state Variable to store the intermediate result 
 * \retval ERR_NO_KEY if key expansion is not done vis aes_init()
 * \retval STATUS_OKAY if aes_init() is called before this function.
 */
aes_ret_status_t aes_inverse_cipher(uint8_t *cipherText, uint8_t *state)
{

	uint8_t round = 0;
	uint8_t byte_count = 0;


	// Check if the aes_init() is called for key expansion
	if(aes_key_ready != true)
		return ERR_NO_KEY;

	//Copy input buffer to state to form the plain text
	for (byte_count =0; byte_count < AES_BLOCK_SIZE; byte_count++){
		state[byte_count] = cipherText[byte_count];
	}

	// Initial addroundkey
	state[0] ^= key_schedule[160];
	state[1] ^= key_schedule[161];
	state[2] ^= key_schedule[162];
	state[3] ^= key_schedule[163];
	state[4] ^= key_schedule[164];
	state[5] ^= key_schedule[165];
	state[6] ^= key_schedule[166];
	state[7] ^= key_schedule[167];
	state[8] ^= key_schedule[168];
	state[9] ^= key_schedule[169];
	state[10] ^= key_schedule[170];
	state[11] ^= key_schedule[171];
	state[12] ^= key_schedule[172];
	state[13] ^= key_schedule[173];
	state[14] ^= key_schedule[174]; 
	state[15] ^= key_schedule[175];

	// Round 9 to 1
	for(round = 9; round>0; round--){
		/* Inverse Sub Bytes and Shift Rows */
		Inv_ShiftRows_SubBytes(state);
		/* Inverse Add Round Key */
		Inv_AddRoundKey(state, round);
		/* Inverse Mix Columns */
		Inv_MixColumns(state, round);
	}

	// Round 0 without mixcols
	round = 0;
	
	/* Inverse Sub Bytes and Shift Rows */
	Inv_ShiftRows_SubBytes(state);
	/* Inverse Add Round Key */
	Inv_AddRoundKey(state, round);


	return STATUS_OKAY;
} 

