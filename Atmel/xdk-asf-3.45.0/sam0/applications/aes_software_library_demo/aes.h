/**
 * \file FIPS-197 AES-128 software library header file 
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


#ifndef AES
#define AES

#include "crypt.h"
#include <compiler.h>

//AES block size in bytes
#define AES_BLOCK_SIZE    16

//Total number of rounds for AES-128
#define AES_NUM_OF_ROUNDS 10

//Key schedule size
#define AES_KEY_SCHEDULE_SIZE ((AES_BLOCK_SIZE) * (AES_NUM_OF_ROUNDS + 1))

/* Status values */
typedef enum {
	STATUS_OKAY = 0,
	ERR_NO_KEY
}aes_ret_status_t;


/*! \brief Performs key expansion to generate key schedule
 * from initial set of Key of 4 words.
 * \param round_key  Holds the pointer to store key schedule 
 * \param key        Initial Key received from the user
 */
void KeyExpansion(uint8_t *round_key, uint8_t *key);


/*! \brief xtime calculation
 * The value is multiplied by 0x02. This 
 * is implemented at the byte level as a
 * left shift and XOR with 0x1b if the MSB 
 * of the value (before) shifting is 1.
 * \param value  Value for which multiplication to be done
 */
uint8_t xtime(uint8_t value);


/*! \brief Performs Sub Byte and Shift rows operation.
 * \param state  variable to store the intermediate result of the algorithm
 */
void SubBytes_ShiftRows(uint8_t *state);


/*! \brief Performs Mix Columns Operation
 * \param state  variable to store the intermediate result of the algorithm
 */
void MixColumnns(uint8_t *state);


/*! \brief Performs Add RoundKey  operation.
 * \param state  variable to store the intermediate result of the algorithm
 */
void AddRoundKey(uint8_t *state, uint8_t round);


/*! \brief Performs Inverse of sub bytes and shift rows operation
 * \param state  variable to store the intermediate result of the algorithm
 */
void Inv_ShiftRows_SubBytes(uint8_t *state);


/*! \brief Performs AddRound Key
 * \param state  variable to store the intermediate result of the algorithm
 * \note inverse of Add round key and Add round key are same.Two separate 
 * functions are defined for ease of understanding the encryption and 
 * decryption process. 
 */
void Inv_AddRoundKey(uint8_t *state, uint8_t round);


/*! \brief Performs Inverse  Mix Columns operation
 * \param state  variable to store the intermediate result of the algorithm
 * \param Number of current ongoing round in AES algorithm
 */
void Inv_MixColumns(uint8_t *state, uint8_t round);


/*! \brief Performs Key Expansion 
 * \param key  Initial Key vectors received from user
 */
void aes_init(uint8_t *key);


/*! \brief Performs AES-128 Encryption
 * \param plainText  Input plain text block
 * \param state Variable to store the intermediate result 
 * \retval ERR_NO_KEY if key expansion is not done vis aes_init()
 * \retval STATUS_OKAY if aes_init() is called before this function.
 */
aes_ret_status_t aes_cipher(uint8_t *plainText, uint8_t *state);


/*! \brief Performs AES-128 Decryption
 * \param cipherText  Input cipher text block
 * \param state Variable to store the intermediate result 
 * \retval ERR_NO_KEY if key expansion is not done vis aes_init()
 * \retval STATUS_OKAY if aes_init() is called before this function.
 */
aes_ret_status_t aes_inverse_cipher(uint8_t *cipherText, uint8_t *state);


#endif
