/**
 * \file FIPS SP800-38A software library source file
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

#include "crypt.h"

/* Array to store the counter value in CTR mode */
uint8_t counter_block[AES_BLOCK_SIZE] = {0};

/*! \brief This function performs ECB encryption on input plain text blocks.
 * \param plainText  pointer to the array containing the plain text bytes
 * \param cipherText pointer to the array where the encrypted cipher output has to be stored
 * \param size       size of the input plain text
 */ 
void ecb_encrypt(uint8_t *plainText, uint8_t *cipherText, uint32_t size)
{
	uint32_t input_block_size = 0;
	uint8_t block_count = 0;

	//Calculate the number of input blocks
	input_block_size = size/AES_BLOCK_SIZE;

	for(block_count = 0;block_count < input_block_size; block_count++){
		//Perform forward cipher for the input blocks
		aes_cipher(plainText+(block_count * AES_BLOCK_SIZE), 
							cipherText+(block_count * AES_BLOCK_SIZE));
	}

}

/*! \brief This function performs ECB decryption on input cipher text blocks.
 * \param cipherText pointer to the array containing the cipher text bytes
 * \param plainText  pointer to the array where the decrypted plain text has to be stored
 * \param size       size of the input plain text
 */ 
void ecb_decrypt(uint8_t *cipherText, uint8_t *plainText, uint32_t size)
{
	uint32_t input_block_size = 0;
	uint8_t block_count = 0;

	//Calculate the number of input blocks
	input_block_size = size/AES_BLOCK_SIZE;

	for(block_count = 0;block_count < input_block_size; block_count++){
		//Perform inverse cipher for the input blocks
		aes_inverse_cipher(cipherText+(block_count * AES_BLOCK_SIZE), 
							plainText + (block_count * AES_BLOCK_SIZE));
	}

}


/*! \brief This function performs CBC encryption on input plain text blocks.
 * \param plainText   pointer to the array containing the plain text bytes
 * \param cipherText  pointer to the array where the encrypted cipher output has to be stored
 * \param init_vector pointer to the array containing the unique initialization vector
 * \param size        size of the input plain text
 */ 
void cbc_encrypt (uint8_t *plainText, uint8_t *cipherText, uint8_t *init_vector, uint32_t size)
{
	uint32_t block_count = 0, input_block_size = 0;
	uint8_t byte_count = 0;

	//Calculate input block size
	input_block_size = (size / AES_BLOCK_SIZE );

	for(byte_count = 0; byte_count < AES_BLOCK_SIZE; byte_count++){
		//XOR plain text with initialization vector to form first input block
		plainText[byte_count] = plainText[byte_count] ^ init_vector[byte_count];
	}

	for(block_count = 0;block_count < input_block_size; block_count++){

		//Sending initialization vector to the cipher function to get further output blocks
		aes_cipher(plainText +(block_count * AES_BLOCK_SIZE), 
						cipherText +(block_count * AES_BLOCK_SIZE));

		if(block_count != (input_block_size -1)){

			//Move the previous cipher block to feedback for next round
			for(byte_count = 0; byte_count < AES_BLOCK_SIZE; byte_count++){
				// XOR plain text with previous cipher text to form input for next block
				plainText[byte_count + ((block_count + 1)*AES_BLOCK_SIZE)] =  
							plainText[byte_count + ((block_count + 1)*AES_BLOCK_SIZE)] ^
							cipherText[byte_count + (block_count* AES_BLOCK_SIZE)];
			}

		}

	}//end of all blocks

}


/*! \brief This function performs CBC decryption on input cipher text blocks.
 * \param cipherText  pointer to the array containing the cipher text bytes
 * \param plainText   pointer to the array where the decrypted plain text has to be stored
 * \param init_vector pointer to the array containing the unique initialization vector
 * \param size        size of the input plain text
 */ 
void cbc_decrypt (uint8_t *cipherText, uint8_t *plainText, uint8_t *init_vector, uint32_t size)
{
	uint32_t block_count = 0, input_block_size = 0;
	uint8_t byte_count = 0;

	//Calculate input block size
	input_block_size = (size / AES_BLOCK_SIZE );

	//Round0
	aes_inverse_cipher(cipherText, plainText);


	for(byte_count = 0; byte_count < AES_BLOCK_SIZE; byte_count++){
		/* Retrieve the first block of input data by XOR round 0 
		 * output with Initialization vector
		 */
		plainText[byte_count] = plainText[byte_count] ^ init_vector[byte_count];
	}

	for(block_count = 1;block_count < input_block_size; block_count++){

		//Perform inverse cipher for the input blocks
		aes_inverse_cipher(cipherText+(block_count * AES_BLOCK_SIZE), 
				plainText+(block_count * AES_BLOCK_SIZE));

		for(byte_count = 0; byte_count < AES_BLOCK_SIZE; byte_count++){
			/* XOR output of previous inverse cipher function with previous cipher text to
			 * form the input for next block
			 */
			plainText[byte_count + (block_count * AES_BLOCK_SIZE)] = 
					plainText[byte_count + (block_count * AES_BLOCK_SIZE)] ^
					cipherText[byte_count + ( (block_count - 1) * AES_BLOCK_SIZE)];
		}

	}

}


/*! \brief This function performs CFB encryption on input plain text blocks.
 * \param plainText   pointer to the array containing the plain text bytes
 * \param cipherText  pointer to the array where the encrypted cipher output has to be stored
 * \param init_vector pointer to the array containing the unique initialization vector
 * \param mode        CFB mode in bits - can be 8, 16, 32, 64, 128.
 * \param size        size of the input plain text
 */ 
void cfb_encrypt(uint8_t *plainText, uint8_t *cipherText, uint8_t *init_vector, uint8_t mode, uint32_t size)
{
	uint32_t input_block_size = 0;
	uint8_t block_count = 0, byte_count = 0, cfb_byte = 0;
	uint8_t init_vector_temp[AES_BLOCK_SIZE] = {0};
	uint8_t index1 = 0, index2 = 0;
	bool index2_flag = false;

	/* calculate cfb bytes
	 * cfb_byte = 16 for 128 bit CFB, 
	 * cfb_byte = 8 for 64-bit CFB, 
	 * cfb_byte = 4 for 32-bit CFB,
	 * cfb_byte = 2 for 16-bit CFB,
	 * cfb_byte = 1 for 8-bit CFB
	 */
	cfb_byte = mode/8;

	//Calculate the number of input blocks
	input_block_size = (size / AES_BLOCK_SIZE );

	 for(byte_count = 0; byte_count < AES_BLOCK_SIZE; byte_count++){
		 //Moving initial vector to a temp array
		init_vector_temp[byte_count] = init_vector[byte_count];
	}

	//Forward cipher of initial vector 1
	aes_cipher(init_vector_temp, cipherText); 
 
	//XOR-ing plain text 's' bits with output block s bits
	for(byte_count = 0; byte_count < cfb_byte; byte_count++){
		cipherText[byte_count] = plainText[byte_count] ^ cipherText[byte_count];
	}
 
	//Encryption of remaining blocks
	for(block_count = 1;block_count < ((AES_BLOCK_SIZE * input_block_size) / cfb_byte); block_count++){

		index1 = 0;
		//Preparation of Initialization vector for the next round
		for (byte_count = 0; byte_count < AES_BLOCK_SIZE; byte_count++){

			if(block_count < ((AES_BLOCK_SIZE/cfb_byte))+1){

				/* For the first few blocks where initialization vector and cipher output 
				 * is used to generate the init_vector_temp
				 */
				if(byte_count < (AES_BLOCK_SIZE - (block_count + cfb_byte - 1))){
					 init_vector_temp[byte_count] = 
							init_vector[byte_count + (cfb_byte + block_count-1)];
				}else{
					init_vector_temp [byte_count] = cipherText[index1++];
				}
				if (block_count == (AES_BLOCK_SIZE / cfb_byte)){
					index2_flag = true;
				}

			}else{

				/* For the remaining blocks where init_vector_temp is generated from the cipher 
				 * output from the previous block. AES Standard FIPS SP800-38A explains more on 
				 * generation of init_vector for each block in different CFB modes
				 */
				init_vector_temp[byte_count] =  cipherText[(cfb_byte * index2) + byte_count];

			}

		}

		if (index2_flag == true){
			index2 = index2+1;
		}

		//Sending initialization vector to the cipher function to get 16 byte output block
		aes_cipher(init_vector_temp, (cipherText + (block_count * cfb_byte)));

		for(byte_count = 0; byte_count < cfb_byte; byte_count++){
			//XOR-ing cipher text 's' bits with output block s bits
			cipherText[(byte_count + (block_count * cfb_byte))] = 
					plainText[(byte_count + (block_count * cfb_byte))] ^ 
					cipherText[byte_count + (block_count * cfb_byte)];
		 }

	} //End of all blocks

}


/*! \brief This function performs CFB decryption on input cipher text blocks.
 * \param cipherText  pointer to the array containing the cipher text bytes
 * \param plainText   pointer to the array where the decrypted plain text has to be stored
 * \param init_vector pointer to the array containing the unique initialization vector
 * \param mode        CFB mode in bits - can be 8, 64, 128.
 * \param size        size of the input plain text
 */ 
void cfb_decrypt(uint8_t *cipherText, uint8_t *plainText, uint8_t *init_vector, uint8_t mode, uint32_t size)
{
	uint32_t input_block_size = 0;
	uint8_t block_count = 0, byte_count = 0, cfb_byte = 0;
	uint8_t init_vector_temp[AES_BLOCK_SIZE] = {0};
	uint8_t index1 = 0, index2 = 0;
	bool index2_flag = false;

	/* calculate cfb bytes
	 * cfb_byte = 16 for 128 bit CFB, 
	 * cfb_byte = 8 for 64-bit CFB, 
	 * cfb_byte = 4 for 32-bit CFB,
	 * cfb_byte = 2 for 16-bit CFB,
	 * cfb_byte = 1 for 8-bit CFB
	 */
	cfb_byte = mode/8;

	//Calculate the number of input blocks
	input_block_size = (size / AES_BLOCK_SIZE );

	for(byte_count = 0; byte_count<AES_BLOCK_SIZE; byte_count++){
		//Moving initial vector to a temp array
		init_vector_temp[byte_count] = init_vector[byte_count];
	}

	//Forward cipher of initial vector 1
	aes_cipher(init_vector_temp, plainText); 

	//XOR-ing cipher text 's' bits with output block s bits
	for(byte_count = 0; byte_count < cfb_byte; byte_count++){
		plainText[byte_count] = cipherText[byte_count] ^ plainText[byte_count];
	}

	//Decryption of remaining blocks
	for(block_count = 1;block_count < ((AES_BLOCK_SIZE * input_block_size) / cfb_byte); block_count++){

		index1 = 0;
		//Preparation of Initialization vector for the next round
		for (byte_count = 0; byte_count < AES_BLOCK_SIZE; byte_count++){

			if(block_count < ((AES_BLOCK_SIZE/cfb_byte))+1){

				/* For the first few blocks where initialization vector and cipher output 
				 * is used to generate the init_vector_temp
				 */
				if(byte_count < (16 - (block_count + cfb_byte -1))){
					init_vector_temp[byte_count] = 
							init_vector[byte_count + (cfb_byte + block_count - 1)];
				}else{
					init_vector_temp [byte_count] = cipherText[index1++];
				}
				if (block_count == (AES_BLOCK_SIZE / cfb_byte)){
					index2_flag = true;
				}

			}else{

				/* For the remaining blocks where init_vector_temp is generated from the cipher 
				 * output from the previous block. AES Standard FIPS SP800-38A explains more on 
				 * generation of init_vector for each block in different CFB modes
				 */
				init_vector_temp[byte_count] =  cipherText[(cfb_byte * index2) + byte_count];

			}

		}
		if (index2_flag == true){
			index2 = index2+1;
		}

		//Sending initialization vector to the cipher function to get 16 byte output block
		aes_cipher(init_vector_temp,  (plainText+(block_count * cfb_byte)));

		//XOR-ing cipher text 's' bits with output block s bits
		for(byte_count = 0; byte_count < cfb_byte; byte_count++){
			plainText[(byte_count + (block_count * cfb_byte))] = 
					cipherText[(byte_count + (block_count * cfb_byte))]^
					plainText[(byte_count + (block_count * cfb_byte))];
		}

	}

}


/*! \brief This function performs OFB encryption on input plain text blocks.
 * \param plainText   pointer to the array containing the plain text bytes
 * \param cipherText  pointer to the array where the encrypted cipher output has to be stored
 * \param init_vector pointer to the array containing the unique initialization vector
 * \param size        size of the input plain text
 */ 
void ofb_encrypt(uint8_t *plainText, uint8_t *cipherText, uint8_t *init_vector, uint32_t size)
{
	uint32_t input_block_size = 0;
	uint8_t block_count = 0, byte_count = 0;
	uint8_t input_block[16] = {0};

	//Calculate the number of blocks
	input_block_size = (size / AES_BLOCK_SIZE );

	for(byte_count = 0; byte_count < AES_BLOCK_SIZE; byte_count++){
		//Moving initial vector to a temp array
		input_block[byte_count] = init_vector[byte_count];
	}

	//Encryption of remaining blocks
	for(block_count = 0;block_count < input_block_size; block_count++){

		//Sending initialization vector to the cipher function to get 16 byte output block
		aes_cipher(input_block,  (cipherText+(block_count * AES_BLOCK_SIZE)));
		
		//XOR cipher output with  plain text to complete the encryption for a block
		for(byte_count = 0; byte_count < AES_BLOCK_SIZE; byte_count++){
			cipherText[byte_count+ (block_count * AES_BLOCK_SIZE)] = 
					plainText[byte_count + (block_count * AES_BLOCK_SIZE)]^
					cipherText[byte_count+ (block_count * AES_BLOCK_SIZE)];
		}
	}
}


 /*! \brief This function performs OFB decryption on input cipher text blocks.
 * \param cipherText  pointer to the array containing the cipher text bytes
 * \param plainText   pointer to the array where the decrypted plain text has to be stored
 * \param init_vector pointer to the array containing the unique initialization vector
 * \param size        size of the input plain text
 */ 
void ofb_decrypt(uint8_t *cipherText, uint8_t *plainText, uint8_t *init_vector, uint32_t size)
{
	uint32_t input_block_size = 0;
	uint8_t block_count = 0, byte_count = 0;
	uint8_t input_block[16] = {0};

	//Calculate the number of input blocks
	input_block_size = size / AES_BLOCK_SIZE;

	for(byte_count = 0; byte_count<AES_BLOCK_SIZE; byte_count++){
		//Moving initial vector to a temp array
		input_block[byte_count] = init_vector[byte_count];
	}

	//Decryption of remaining blocks
	for(block_count = 0;block_count < input_block_size; block_count++){

		//Sending initialization vector to the cipher function to get 16 byte output block
		aes_cipher(input_block, (plainText+(block_count * AES_BLOCK_SIZE)));

		//XOR cipher output with previous cipher text to decrypt the input data
		for(byte_count = 0; byte_count < AES_BLOCK_SIZE; byte_count++){
			plainText[byte_count + (block_count * AES_BLOCK_SIZE)] = 
					cipherText[byte_count + (block_count * AES_BLOCK_SIZE)]^
					plainText[byte_count + (block_count * AES_BLOCK_SIZE)];
		}
	}

}

/*! \brief Performs counter increment to prepare input for next round.
 * \param counter   value of counter used in CTR mode
 */
void ctr_inc_counter(ctr_blk_t *counter)
{
	//Append Nonce to 1st 4 bytes of counter block
	counter_block[0] = ((counter->nonce) >> 24) & 0xFF;
	counter_block[1] = ((counter->nonce) >> 16) & 0xFF;
	counter_block[2] = ((counter->nonce) >> 8) & 0xFF;
	counter_block[3] = ((counter->nonce) >> 0) & 0xFF;
	//Append IV to next 8 bytes of counter block
	counter_block[4] = ((counter->i_vector) >> 56) & 0xFF;
	counter_block[5] = ((counter->i_vector) >> 48) & 0xFF;
	counter_block[6] = ((counter->i_vector) >> 40) & 0xFF;
	counter_block[7] = ((counter->i_vector) >> 32) & 0xFF;
	counter_block[8] = ((counter->i_vector) >> 24) & 0xFF;
	counter_block[9] = ((counter->i_vector) >> 16) & 0xFF;
	counter_block[10] = ((counter->i_vector) >> 8) & 0xFF;
	counter_block[11] = ((counter->i_vector) >> 0) & 0xFF;
	//Increment next counter
	counter->counter += 1;
	//Append Initial Counter value to remaining 4 bytes of counter block
	counter_block[12] = ((counter->counter) >> 24) & 0xFF;
	counter_block[13] = ((counter->counter) >> 16) & 0xFF;
	counter_block[14] = ((counter->counter) >> 8) & 0xFF;
	counter_block[15] = ((counter->counter) >> 0) & 0xFF;
}


/*! \brief This function performs CTR encryption/decryption on input blocks.
  * Note: Both encryption and decryption is same for CTR mode.
  * In both the cases, the input block to the cipher function is the counter.
  * The resulting output is XOR-ed with plain text for encryption.
  * For decryption case, it is XOR-ed with cipher text to retrieve the actual data.
 * \param plainText   pointer to the array containing the plain text bytes
 * \param cipherText  pointer to the array where the encrypted cipher output has to be stored
 * \param counter	  pointer to the structure containing the counter block
 * \param size        size of the input plain text
 */ 
void ctr_encrypt_decrypt (uint8_t *input_block , uint8_t *output_block, ctr_blk_t *counter, uint32_t size)
{
	uint32_t block_count = 0, input_block_size = 0;
	uint8_t byte_count = 0;

	//Calculate input block size
	input_block_size = (size / AES_BLOCK_SIZE );

	//Move the initial counter to local counter block
	//Append Nonce to first 4 bytes of counter block
	counter_block[0] = ((counter->nonce) >> 24) & 0xFF;
	counter_block[1] = ((counter->nonce) >> 16) & 0xFF;
	counter_block[2] = ((counter->nonce) >> 8) & 0xFF;
	counter_block[3] = ((counter->nonce) >> 0) & 0xFF;
	//Append IV to next 8 bytes of counter block
	counter_block[4] = ((counter->i_vector) >> 56) & 0xFF;
	counter_block[5] = ((counter->i_vector) >> 48) & 0xFF;
	counter_block[6] = ((counter->i_vector) >> 40) & 0xFF;
	counter_block[7] = ((counter->i_vector) >> 32) & 0xFF;
	counter_block[8] = ((counter->i_vector) >> 24) & 0xFF;
	counter_block[9] = ((counter->i_vector) >> 16) & 0xFF;
	counter_block[10] = ((counter->i_vector) >> 8) & 0xFF;
	counter_block[11] = ((counter->i_vector) >> 0) & 0xFF;
	//Append Initial Counter value to remaining 4 bytes of counter block
	counter_block[12] = ((counter->counter) >> 24) & 0xFF;
	counter_block[13] = ((counter->counter) >> 16) & 0xFF;
	counter_block[14] = ((counter->counter) >> 8) & 0xFF;
	counter_block[15] = ((counter->counter) >> 0) & 0xFF;

	//Run Encryption for input blocks
	for(block_count = 0; block_count < input_block_size; block_count++){
		if (0 != block_count)
			ctr_inc_counter(counter);

		//Forward cipher of counter
		aes_cipher(counter_block, output_block + (block_count * AES_BLOCK_SIZE));

		//XOR of plain text with the output block
		for (byte_count =0; byte_count < AES_BLOCK_SIZE; byte_count++){
			output_block[byte_count + (block_count * AES_BLOCK_SIZE)] = 
					input_block[byte_count + (block_count * AES_BLOCK_SIZE)] ^
					output_block[byte_count + (block_count * AES_BLOCK_SIZE)];
			
		}
 
	}

}


  
  


