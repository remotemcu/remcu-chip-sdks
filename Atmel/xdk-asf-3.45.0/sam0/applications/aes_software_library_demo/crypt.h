/**
 * \file FIPS SP800-38A software library header file
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
#ifndef CRYPT_H
#define CRYPT_H

#include "aes.h"
#include <compiler.h>

//Counter block structure for AES-CTR mode
typedef struct{
	uint32_t nonce;
	uint64_t i_vector;
	uint32_t counter;
} ctr_blk_t;

/*! \brief This function performs ECB encryption on input plain text blocks.
 * \param plainText  pointer to the array containing the plain text bytes
 * \param cipherText pointer to the array where the encrypted cipher output has to be stored
 * \param size       size of the input plain text
 */ 
void ecb_encrypt(uint8_t *plainText, uint8_t *cipherText, uint32_t size);


/*! \brief This function performs ECB decryption on input cipher text blocks.
 * \param cipherText pointer to the array containing the cipher text bytes
 * \param plainText  pointer to the array where the decrypted plain text has to be stored
 * \param size       size of the input plain text
 */ 
void ecb_decrypt(uint8_t *cipherText, uint8_t *plainText, uint32_t size);


/*! \brief This function performs CBC encryption on input plain text blocks.
 * \param plainText   pointer to the array containing the plain text bytes
 * \param cipherText  pointer to the array where the encrypted cipher output has to be stored
 * \param init_vector pointer to the array containing the unique initialization vector
 * \param size        size of the input plain text
 */ 
void cbc_encrypt (uint8_t *plainText, uint8_t *cipherText, uint8_t *init_vector, uint32_t size);


/*! \brief This function performs CBC decryption on input cipher text blocks.
 * \param cipherText  pointer to the array containing the cipher text bytes
 * \param plainText   pointer to the array where the decrypted plain text has to be stored
 * \param init_vector pointer to the array containing the unique initialization vector
 * \param size        size of the input plain text
 */ 
void cbc_decrypt (uint8_t *cipherText, uint8_t *plainText, uint8_t *init_vector, uint32_t size);


/*! \brief This function performs CFB encryption on input plain text blocks.
 * \param plainText   pointer to the array containing the plain text bytes
 * \param cipherText  pointer to the array where the encrypted cipher output has to be stored
 * \param init_vector pointer to the array containing the unique initialization vector
 * \param mode        CFB mode in bits - can be 8, 16, 32, 64, 128.
 * \param size        size of the input plain text
 */ 
void cfb_encrypt(uint8_t *plainText, uint8_t *cipherText, uint8_t *init_vector, uint8_t mode, uint32_t size);


/*! \brief This function performs CFB decryption on input cipher text blocks.
 * \param cipherText  pointer to the array containing the cipher text bytes
 * \param plainText   pointer to the array where the decrypted plain text has to be stored
 * \param init_vector pointer to the array containing the unique initialization vector
 * \param mode        CFB mode in bits - can be 8, 64, 128.
 * \param size        size of the input plain text
 */ 
void cfb_decrypt(uint8_t *cipherText, uint8_t *plainText, uint8_t *init_vector, uint8_t mode, uint32_t size);


/*! \brief This function performs OFB encryption on input plain text blocks.
 * \param plainText   pointer to the array containing the plain text bytes
 * \param cipherText  pointer to the array where the encrypted cipher output has to be stored
 * \param init_vector pointer to the array containing the unique initialization vector
 * \param size        size of the input plain text
 */ 
void ofb_encrypt(uint8_t *plainText, uint8_t *cipherText, uint8_t *init_vector, uint32_t size);

 
 /*! \brief This function performs OFB decryption on input cipher text blocks.
 * \param cipherText  pointer to the array containing the cipher text bytes
 * \param plainText   pointer to the array where the decrypted plain text has to be stored
 * \param init_vector pointer to the array containing the unique initialization vector
 * \param size        size of the input plain text
 */ 
void ofb_decrypt(uint8_t *cipherText, uint8_t *plainText, uint8_t *init_vector, uint32_t size);


/*! \brief Performs counter increment to prepare input for next round.
 * \param counter   value of counter used in CTR mode
 */
void ctr_inc_counter(ctr_blk_t *counter);


/*! \brief This function performs CTR encryption/decryption on input blocks.
  * Note: Both encryption and decryption is same for CTR mode.
  * In both the cases, the input block to the cipher process is the counter.
  * The resulting output is XOR-ed with plain text for encryption.
  * For decryption case, it is XOR-ed with cipher text to retrieve the actual data.
 * \param plainText   pointer to the array containing the plain text bytes
 * \param cipherText  pointer to the array where the encrypted cipher output has to be stored
 * \param init_vector pointer to the array containing the unique initialization vector
 * \param size        size of the input plain text
 */ 
void ctr_encrypt_decrypt (uint8_t *input_block , uint8_t *output_block, ctr_blk_t *counter, uint32_t size);



#endif
