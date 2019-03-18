/**
 *
 * \file
 *
 * \brief AES example for SAM.
 *
 * This file defines a useful set of functions for the AES on SAM devices.
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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

/** \mainpage
 * \section intro Introduction
 * This is the documentation for the data structures, functions, variables,
 * defines, enums, and typedefs for the AES driver. <BR>It also gives several
 * examples of usage of the AES module: <BR>
 * - ECB ciphering and deciphering.
 * - CBC ciphering and deciphering.
 * - CFB ciphering and deciphering.
 * - OFB ciphering and deciphering.
 * - CTR ciphering and deciphering.
 * - ECB ciphering and deciphering with PDCA.<BR>
 *
 * \section files Main Files
 * - aesa.c : AESA driver
 * - aesa.h : AESA header file
 * - aesa_example.c : AES code example
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR Systems compiler.
 * Other compilers may or may not work.
 *
 * \section deviceinfo Device Info
 * All SAM devices with an AES module can be used. This example has been
 * tested with the following setup:<BR>
 * - SAM4L evaluation kit.
 * - SAM4L Xplained Pro
 * - SAM4L8 Xplained Pro
 *
 * \section setupinfo Setup Information
 * <BR>CPU speed: <i> 12 MHz </i>
 * - Connect the on-board virtual port com to a PC
 * - PC terminal settings:
 *     - 115200 bps,
 *     - 8 data bits,
 *     - no parity bit,
 *     - 1 stop bit,
 *     - no flow control.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com">Microchip</A>.\n
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <string.h>

#define AES_EXAMPLE_REFBUF_SIZE 4

/**
 * \name sample data from NIST-800-38A appendix F
 */
/* @{ */
/** Reference plain data. */
const uint32_t ref_plain_text[AES_EXAMPLE_REFBUF_SIZE] = {
	0xe2bec16b,
	0x969f402e,
	0x117e3de9,
	0x2a179373
};

/** Reference ECB cipher data. */
const uint32_t ref_cipher_text_ecb[AES_EXAMPLE_REFBUF_SIZE] = {
	0xb47bd73a,
	0x60367a0d,
	0xf3ca9ea8,
	0x97ef6624
};

/** Reference CBC cipher data. */
const uint32_t ref_cipher_text_cbc[AES_EXAMPLE_REFBUF_SIZE] = {
	0xacab4976,
	0x46b21981,
	0x9b8ee9ce,
	0x7d19e912
};

/** Reference CFB128 cipher data. */
const uint32_t ref_cipher_text_cfb128[AES_EXAMPLE_REFBUF_SIZE] = {
	0x2ed93f3b,
	0x20ad2db7,
	0xf8493433,
	0x4afb3ce8
};

/** Reference OFB cipher data. */
const uint32_t ref_cipher_text_ofb[AES_EXAMPLE_REFBUF_SIZE] = {
	0x2ed93f3b,
	0x20ad2db7,
	0xf8493433,
	0x4afb3ce8
};

/** Reference CTR cipher data. */
const uint32_t ref_cipher_text_ctr[AES_EXAMPLE_REFBUF_SIZE] = {
	0x91614d87,
	0x26e320b6,
	0x6468ef1b,
	0xceb60d99
};

/** Cipher 128 bits key array. */
const uint32_t key128[4] = {
	0x16157e2b,
	0xa6d2ae28,
	0x8815f7ab,
	0x3c4fcf09
};

/** Init vector array for ECB, CBC, CFB128 and OFB mode. */
const uint32_t init_vector[4] = {
	0x03020100,
	0x07060504,
	0x0b0a0908,
	0x0f0e0d0c
};

/** Init vector array for CTR mode. */
const uint32_t init_vector_ctr[4] = {
	0xf3f2f1f0,
	0xf7f6f5f4,
	0xfbfaf9f8,
	0xfffefdfc
};

/* @} */

/* Output data array */
static uint32_t output_data[AES_EXAMPLE_REFBUF_SIZE];

/* State indicate */
volatile bool state = false;

/** AES instance */
struct aes_dev_inst g_aes_inst;

/** AES configuration */
struct aes_config   g_aes_cfg;

#define PDCA_RX_CHANNEL  0
#define PDCA_TX_CHANNEL  1

/** PDCA channel options. */
pdca_channel_config_t PDCA_RX_OPTIONS, PDCA_TX_OPTIONS;

/**
 * \brief The AES interrupt call back function.
 */
static void aes_callback(void)
{
	/* Read the output(this will clear the DATRDY flag). */
	output_data[0] = aes_read_output_data(&g_aes_inst);
	output_data[1] = aes_read_output_data(&g_aes_inst);
	output_data[2] = aes_read_output_data(&g_aes_inst);
	output_data[3] = aes_read_output_data(&g_aes_inst);
	state = true;
}

/**
 * \brief The AES interrupt call back function.
 */
static void aes_callback_pdca(void)
{
	/* Read the output(this will clear the DATRDY flag) by PDCA. */
	pdca_channel_enable(PDCA_RX_CHANNEL);
	while (pdca_get_channel_status(PDCA_RX_CHANNEL) !=
			PDCA_CH_TRANSFER_COMPLETED) {
	}
	state = true;
}

/**
 * \brief ECB mode encryption and decryption test with PDCA.
 */
static void ecb_mode_test_pdca(void)
{
	/* Change the AES interrupt callback function. */
	aes_set_callback(&g_aes_inst, AES_INTERRUPT_INPUT_BUFFER_READY,
			aes_callback_pdca, 1);

	/* Enable PDCA module clock */
	pdca_enable(PDCA);

	printf("\r\n-----------------------------------\r\n");
	printf("- 128bit cryptographic key\r\n");
	printf("- ECB cipher mode\r\n");
	printf("- all counter measures\r\n");
	printf("- input of 4 32bit words with PDCA\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_inst.aes_cfg->encrypt_mode = AES_ENCRYPTION;
	g_aes_inst.aes_cfg->key_size = AES_KEY_SIZE_128;
	g_aes_inst.aes_cfg->dma_mode = AES_DMA_MODE;
	g_aes_inst.aes_cfg->opmode = AES_ECB_MODE;
	g_aes_inst.aes_cfg->cfb_size = AES_CFB_SIZE_128;
	g_aes_inst.aes_cfg->countermeasure_mask = AES_COUNTERMEASURE_TYPE_ALL;
	aes_set_config(&g_aes_inst);

	/* Beginning of a new message. */
	aes_set_new_message(&g_aes_inst);

	/* Set the cryptographic key. */
	aes_write_key(&g_aes_inst, key128);

	/* The initialization vector is not used by the ECB cipher mode. */

	/* Write the data to be ciphered to the input data registers. */
	/* Init PDCA channel with the pdca_options.*/
	PDCA_TX_OPTIONS.addr = (void *)ref_plain_text; /* memory address */
	PDCA_TX_OPTIONS.pid = AESA_PDCA_ID_TX; /* select peripheral - AESA TX.*/
	PDCA_TX_OPTIONS.size = AES_EXAMPLE_REFBUF_SIZE; /* transfer counter */
	PDCA_TX_OPTIONS.r_addr = (void *)0; /* next memory address */
	PDCA_TX_OPTIONS.r_size = 0; /* next transfer counter */
	PDCA_TX_OPTIONS.transfer_size = PDCA_MR_SIZE_WORD;
	pdca_channel_set_config(PDCA_TX_CHANNEL, &PDCA_TX_OPTIONS);
	PDCA_RX_OPTIONS.addr = (void *)output_data; /* memory address */
	PDCA_RX_OPTIONS.pid = AESA_PDCA_ID_RX; /* select peripheral - AESA RX.*/
	PDCA_RX_OPTIONS.size = AES_EXAMPLE_REFBUF_SIZE; /* transfer counter */
	PDCA_RX_OPTIONS.r_addr = (void *)0; /* next memory address */
	PDCA_RX_OPTIONS.r_size = 0; /* next transfer counter */
	PDCA_RX_OPTIONS.transfer_size = PDCA_MR_SIZE_WORD;
	pdca_channel_set_config(PDCA_RX_CHANNEL, &PDCA_RX_OPTIONS);

	/* Enable PDCA channel, start transfer data. */
	pdca_channel_enable(PDCA_TX_CHANNEL);

	/* Wait for the end of the encryption process. */
	while (false == state) {
	}

	/* Disable PDCA channel. */
	pdca_channel_disable(PDCA_RX_CHANNEL);
	pdca_channel_disable(PDCA_TX_CHANNEL);

	if ((ref_cipher_text_ecb[0] != output_data[0]) ||
			(ref_cipher_text_ecb[1] != output_data[1]) ||
			(ref_cipher_text_ecb[2] != output_data[2]) ||
			(ref_cipher_text_ecb[3] != output_data[3])) {
		printf("\r\nKO!!!\r\n");
	} else {
		printf("\r\nOK!!!\r\n");
	}

	printf("\r\n-----------------------------------\r\n");
	printf("- 128bit cryptographic key\r\n");
	printf("- ECB decipher mode\r\n");
	printf("- all counter measures\r\n");
	printf("- input of 4 32bit words with PDCA\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_inst.aes_cfg->encrypt_mode = AES_DECRYPTION;
	g_aes_inst.aes_cfg->key_size = AES_KEY_SIZE_128;
	g_aes_inst.aes_cfg->dma_mode = AES_DMA_MODE;
	g_aes_inst.aes_cfg->opmode = AES_ECB_MODE;
	g_aes_inst.aes_cfg->cfb_size = AES_CFB_SIZE_128;
	g_aes_inst.aes_cfg->countermeasure_mask = AES_COUNTERMEASURE_TYPE_ALL;
	aes_set_config(&g_aes_inst);

	/* Beginning of a new message. */
	aes_set_new_message(&g_aes_inst);

	/* Set the cryptographic key. */
	aes_write_key(&g_aes_inst, key128);

	/* The initialization vector is not used by the ECB cipher mode. */

	/* Write the data to be deciphered to the input data registers. */
	/* Init PDCA channel with the pdca_options.*/
	PDCA_TX_OPTIONS.addr = (void *)ref_cipher_text_ecb; /* memory address */
	PDCA_TX_OPTIONS.pid = AESA_PDCA_ID_TX; /* select peripheral - AESA TX.*/
	PDCA_TX_OPTIONS.size = AES_EXAMPLE_REFBUF_SIZE; /* transfer counter */
	PDCA_TX_OPTIONS.r_addr = (void *)0; /* next memory address */
	PDCA_TX_OPTIONS.r_size = 0; /* next transfer counter */
	PDCA_TX_OPTIONS.transfer_size = PDCA_MR_SIZE_WORD;
	pdca_channel_set_config(PDCA_TX_CHANNEL, &PDCA_TX_OPTIONS);
	PDCA_RX_OPTIONS.addr = (void *)output_data; /* memory address */
	PDCA_RX_OPTIONS.pid = AESA_PDCA_ID_RX; /* select peripheral - AESA RX.*/
	PDCA_RX_OPTIONS.size = AES_EXAMPLE_REFBUF_SIZE; /* transfer counter */
	PDCA_RX_OPTIONS.r_addr = (void *)0; /* next memory address */
	PDCA_RX_OPTIONS.r_size = 0; /* next transfer counter */
	PDCA_RX_OPTIONS.transfer_size = PDCA_MR_SIZE_WORD;
	pdca_channel_set_config(PDCA_RX_CHANNEL, &PDCA_RX_OPTIONS);

	/* Enable PDCA channel, start transfer data. */
	pdca_channel_enable(PDCA_TX_CHANNEL);

	/* Wait for the end of the decryption process. */
	while (false == state) {
	}

	/* Disable PDCA channel. */
	pdca_channel_disable(PDCA_RX_CHANNEL);
	pdca_channel_disable(PDCA_TX_CHANNEL);

	/* check the result. */
	if ((ref_plain_text[0] != output_data[0]) ||
			(ref_plain_text[1] != output_data[1]) ||
			(ref_plain_text[2] != output_data[2]) ||
			(ref_plain_text[3] != output_data[3])) {
		printf("\r\nKO!!!\r\n");
	} else {
		printf("\r\nOK!!!\r\n");
	}

	/* Disable PDCA module clock */
	pdca_disable(PDCA);

	/* Change back the AES interrupt callback function. */
	aes_set_callback(&g_aes_inst, AES_INTERRUPT_INPUT_BUFFER_READY,
			aes_callback, 1);
}

/**
 * \brief ECB mode encryption and decryption test.
 */
static void ecb_mode_test(void)
{
	printf("\r\n-----------------------------------\r\n");
	printf("- 128bit cryptographic key\r\n");
	printf("- ECB cipher mode\r\n");
	printf("- all counter measures\r\n");
	printf("- input of 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_inst.aes_cfg->encrypt_mode = AES_ENCRYPTION;
	g_aes_inst.aes_cfg->key_size = AES_KEY_SIZE_128;
	g_aes_inst.aes_cfg->dma_mode = AES_MANUAL_MODE;
	g_aes_inst.aes_cfg->opmode = AES_ECB_MODE;
	g_aes_inst.aes_cfg->cfb_size = AES_CFB_SIZE_128;
	g_aes_inst.aes_cfg->countermeasure_mask = AES_COUNTERMEASURE_TYPE_ALL;
	aes_set_config(&g_aes_inst);

	/* Beginning of a new message. */
	aes_set_new_message(&g_aes_inst);

	/* Set the cryptographic key. */
	aes_write_key(&g_aes_inst, key128);

	/* The initialization vector is not used by the ECB cipher mode. */

	/* Write the data to be ciphered to the input data registers. */
	aes_write_input_data(&g_aes_inst, ref_plain_text[0]);
	aes_write_input_data(&g_aes_inst, ref_plain_text[1]);
	aes_write_input_data(&g_aes_inst, ref_plain_text[2]);
	aes_write_input_data(&g_aes_inst, ref_plain_text[3]);

	/* Wait for the end of the encryption process. */
	while (false == state) {
	}

	if ((ref_cipher_text_ecb[0] != output_data[0]) ||
			(ref_cipher_text_ecb[1] != output_data[1]) ||
			(ref_cipher_text_ecb[2] != output_data[2]) ||
			(ref_cipher_text_ecb[3] != output_data[3])) {
		printf("\r\nKO!!!\r\n");
	} else {
		printf("\r\nOK!!!\r\n");
	}

	printf("\r\n-----------------------------------\r\n");
	printf("- 128bit cryptographic key\r\n");
	printf("- ECB decipher mode\r\n");
	printf("- all counter measures\r\n");
	printf("- input of 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_inst.aes_cfg->encrypt_mode = AES_DECRYPTION;
	g_aes_inst.aes_cfg->key_size = AES_KEY_SIZE_128;
	g_aes_inst.aes_cfg->dma_mode = AES_MANUAL_MODE;
	g_aes_inst.aes_cfg->opmode = AES_ECB_MODE;
	g_aes_inst.aes_cfg->cfb_size = AES_CFB_SIZE_128;
	g_aes_inst.aes_cfg->countermeasure_mask = AES_COUNTERMEASURE_TYPE_ALL;
	aes_set_config(&g_aes_inst);

	/* Beginning of a new message. */
	aes_set_new_message(&g_aes_inst);

	/* Set the cryptographic key. */
	aes_write_key(&g_aes_inst, key128);

	/* The initialization vector is not used by the ECB cipher mode. */

	/* Write the data to be deciphered to the input data registers. */
	aes_write_input_data(&g_aes_inst, ref_cipher_text_ecb[0]);
	aes_write_input_data(&g_aes_inst, ref_cipher_text_ecb[1]);
	aes_write_input_data(&g_aes_inst, ref_cipher_text_ecb[2]);
	aes_write_input_data(&g_aes_inst, ref_cipher_text_ecb[3]);

	/* Wait for the end of the decryption process. */
	while (false == state) {
	}

	/* check the result. */
	if ((ref_plain_text[0] != output_data[0]) ||
			(ref_plain_text[1] != output_data[1]) ||
			(ref_plain_text[2] != output_data[2]) ||
			(ref_plain_text[3] != output_data[3])) {
		printf("\r\nKO!!!\r\n");
	} else {
		printf("\r\nOK!!!\r\n");
	}
}

/**
 * \brief CBC mode encryption and decryption test.
 */
static void cbc_mode_test(void)
{
	printf("\r\n-----------------------------------\r\n");
	printf("- 128bit cryptographic key\r\n");
	printf("- CBC cipher mode\r\n");
	printf("- all counter measures\r\n");
	printf("- input of 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_inst.aes_cfg->encrypt_mode = AES_ENCRYPTION;
	g_aes_inst.aes_cfg->key_size = AES_KEY_SIZE_128;
	g_aes_inst.aes_cfg->dma_mode = AES_MANUAL_MODE;
	g_aes_inst.aes_cfg->opmode = AES_CBC_MODE;
	g_aes_inst.aes_cfg->cfb_size = AES_CFB_SIZE_128;
	g_aes_inst.aes_cfg->countermeasure_mask = AES_COUNTERMEASURE_TYPE_ALL;
	aes_set_config(&g_aes_inst);

	/* Beginning of a new message. */
	aes_set_new_message(&g_aes_inst);

	/* Set the cryptographic key. */
	aes_write_key(&g_aes_inst, key128);

	/* Set the initialization vector. */
	aes_write_initvector(&g_aes_inst, init_vector);

	/* Write the data to be ciphered to the input data registers. */
	aes_write_input_data(&g_aes_inst, ref_plain_text[0]);
	aes_write_input_data(&g_aes_inst, ref_plain_text[1]);
	aes_write_input_data(&g_aes_inst, ref_plain_text[2]);
	aes_write_input_data(&g_aes_inst, ref_plain_text[3]);

	/* Wait for the end of the encryption process. */
	while (false == state) {
	}

	if ((ref_cipher_text_cbc[0] != output_data[0]) ||
			(ref_cipher_text_cbc[1] != output_data[1]) ||
			(ref_cipher_text_cbc[2] != output_data[2]) ||
			(ref_cipher_text_cbc[3] != output_data[3])) {
		printf("\r\nKO!!!\r\n");
	} else {
		printf("\r\nOK!!!\r\n");
	}

	printf("\r\n-----------------------------------\r\n");
	printf("- 128bit cryptographic key\r\n");
	printf("- CBC decipher mode\r\n");
	printf("- all counter measures\r\n");
	printf("- input of 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_inst.aes_cfg->encrypt_mode = AES_DECRYPTION;
	g_aes_inst.aes_cfg->key_size = AES_KEY_SIZE_128;
	g_aes_inst.aes_cfg->dma_mode = AES_MANUAL_MODE;
	g_aes_inst.aes_cfg->opmode = AES_CBC_MODE;
	g_aes_inst.aes_cfg->cfb_size = AES_CFB_SIZE_128;
	g_aes_inst.aes_cfg->countermeasure_mask = AES_COUNTERMEASURE_TYPE_ALL;
	aes_set_config(&g_aes_inst);

	/* Beginning of a new message. */
	aes_set_new_message(&g_aes_inst);

	/* Set the cryptographic key. */
	aes_write_key(&g_aes_inst, key128);

	/* Set the initialization vector. */
	aes_write_initvector(&g_aes_inst, init_vector);

	/* Write the data to be deciphered to the input data registers. */
	aes_write_input_data(&g_aes_inst, ref_cipher_text_cbc[0]);
	aes_write_input_data(&g_aes_inst, ref_cipher_text_cbc[1]);
	aes_write_input_data(&g_aes_inst, ref_cipher_text_cbc[2]);
	aes_write_input_data(&g_aes_inst, ref_cipher_text_cbc[3]);

	/* Wait for the end of the decryption process. */
	while (false == state) {
	}

	if ((ref_plain_text[0] != output_data[0]) ||
			(ref_plain_text[1] != output_data[1]) ||
			(ref_plain_text[2] != output_data[2]) ||
			(ref_plain_text[3] != output_data[3])) {
		printf("\r\nKO!!!\r\n");
	} else {
		printf("\r\nOK!!!\r\n");
	}
}

/**
 * \brief CFB128 mode encryption and decryption test.
 */
static void cfb128_mode_test(void)
{
	printf("\r\n-----------------------------------\r\n");
	printf("- 128bit cryptographic key\r\n");
	printf("- CFB128 cipher mode\r\n");
	printf("- all counter measures\r\n");
	printf("- input of 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_inst.aes_cfg->encrypt_mode = AES_ENCRYPTION;
	g_aes_inst.aes_cfg->key_size = AES_KEY_SIZE_128;
	g_aes_inst.aes_cfg->dma_mode = AES_MANUAL_MODE;
	g_aes_inst.aes_cfg->opmode = AES_CFB_MODE;
	g_aes_inst.aes_cfg->cfb_size = AES_CFB_SIZE_128;
	g_aes_inst.aes_cfg->countermeasure_mask = AES_COUNTERMEASURE_TYPE_ALL;
	aes_set_config(&g_aes_inst);

	/* Beginning of a new message. */
	aes_set_new_message(&g_aes_inst);

	/* Set the cryptographic key. */
	aes_write_key(&g_aes_inst, key128);

	/* Set the initialization vector. */
	aes_write_initvector(&g_aes_inst, init_vector);

	/* Write the data to be ciphered to the input data registers. */
	aes_write_input_data(&g_aes_inst, ref_plain_text[0]);
	aes_write_input_data(&g_aes_inst, ref_plain_text[1]);
	aes_write_input_data(&g_aes_inst, ref_plain_text[2]);
	aes_write_input_data(&g_aes_inst, ref_plain_text[3]);

	/* Wait for the end of the encryption process. */
	while (false == state) {
	}

	/* check the result. */
	if ((ref_cipher_text_cfb128[0] != output_data[0]) ||
			(ref_cipher_text_cfb128[1] != output_data[1]) ||
			(ref_cipher_text_cfb128[2] != output_data[2]) ||
			(ref_cipher_text_cfb128[3] != output_data[3])) {
		printf("\r\nKO!!!\r\n");
	} else {
		printf("\r\nOK!!!\r\n");
	}

	printf("\r\n-----------------------------------\r\n");
	printf("- 128bit cryptographic key\r\n");
	printf("- CFB128 decipher mode\r\n");
	printf("- all counter measures\r\n");
	printf("- input of 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_inst.aes_cfg->encrypt_mode = AES_DECRYPTION;
	g_aes_inst.aes_cfg->key_size = AES_KEY_SIZE_128;
	g_aes_inst.aes_cfg->dma_mode = AES_MANUAL_MODE;
	g_aes_inst.aes_cfg->opmode = AES_CFB_MODE;
	g_aes_inst.aes_cfg->cfb_size = AES_CFB_SIZE_128;
	g_aes_inst.aes_cfg->countermeasure_mask = AES_COUNTERMEASURE_TYPE_ALL;
	aes_set_config(&g_aes_inst);

	/* Beginning of a new message. */
	aes_set_new_message(&g_aes_inst);

	/* Set the cryptographic key. */
	aes_write_key(&g_aes_inst, key128);

	/* Set the initialization vector. */
	aes_write_initvector(&g_aes_inst, init_vector);

	/* Write the data to be deciphered to the input data registers. */
	aes_write_input_data(&g_aes_inst, ref_cipher_text_cfb128[0]);
	aes_write_input_data(&g_aes_inst, ref_cipher_text_cfb128[1]);
	aes_write_input_data(&g_aes_inst, ref_cipher_text_cfb128[2]);
	aes_write_input_data(&g_aes_inst, ref_cipher_text_cfb128[3]);

	/* Wait for the end of the decryption process. */
	while (false == state) {
	}

	/* check the result. */
	if ((ref_plain_text[0] != output_data[0]) ||
			(ref_plain_text[1] != output_data[1]) ||
			(ref_plain_text[2] != output_data[2]) ||
			(ref_plain_text[3] != output_data[3])) {
		printf("\r\nKO!!!\r\n");
	} else {
		printf("\r\nOK!!!\r\n");
	}
}

/**
 * \brief OFB mode encryption and decryption test.
 */
static void ofb_mode_test(void)
{
	printf("\r\n-----------------------------------\r\n");
	printf("- 128bit cryptographic key\r\n");
	printf("- OFB cipher mode\r\n");
	printf("- all counter measures\r\n");
	printf("- input of 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_inst.aes_cfg->encrypt_mode = AES_ENCRYPTION;
	g_aes_inst.aes_cfg->key_size = AES_KEY_SIZE_128;
	g_aes_inst.aes_cfg->dma_mode = AES_MANUAL_MODE;
	g_aes_inst.aes_cfg->opmode = AES_OFB_MODE;
	g_aes_inst.aes_cfg->cfb_size = AES_CFB_SIZE_128;
	g_aes_inst.aes_cfg->countermeasure_mask = AES_COUNTERMEASURE_TYPE_ALL;
	aes_set_config(&g_aes_inst);

	/* Beginning of a new message. */
	aes_set_new_message(&g_aes_inst);

	/* Set the cryptographic key. */
	aes_write_key(&g_aes_inst, key128);

	/* Set the initialization vector. */
	aes_write_initvector(&g_aes_inst, init_vector);

	/* Write the data to be ciphered to the input data registers. */
	aes_write_input_data(&g_aes_inst, ref_plain_text[0]);
	aes_write_input_data(&g_aes_inst, ref_plain_text[1]);
	aes_write_input_data(&g_aes_inst, ref_plain_text[2]);
	aes_write_input_data(&g_aes_inst, ref_plain_text[3]);

	/* Wait for the end of the encryption process. */
	while (false == state) {
	}

	/* check the result. */
	if ((ref_cipher_text_ofb[0] != output_data[0]) ||
			(ref_cipher_text_ofb[1] != output_data[1]) ||
			(ref_cipher_text_ofb[2] != output_data[2]) ||
			(ref_cipher_text_ofb[3] != output_data[3])) {
		printf("\r\nKO!!!\r\n");
	} else {
		printf("\r\nOK!!!\r\n");
	}

	printf("\r\n-----------------------------------\r\n");
	printf("- 128bit cryptographic key\r\n");
	printf("- OFB decipher mode\r\n");
	printf("- all counter measures\r\n");
	printf("- input of 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_inst.aes_cfg->encrypt_mode = AES_DECRYPTION;
	g_aes_inst.aes_cfg->key_size = AES_KEY_SIZE_128;
	g_aes_inst.aes_cfg->dma_mode = AES_MANUAL_MODE;
	g_aes_inst.aes_cfg->opmode = AES_OFB_MODE;
	g_aes_inst.aes_cfg->cfb_size = AES_CFB_SIZE_128;
	g_aes_inst.aes_cfg->countermeasure_mask = AES_COUNTERMEASURE_TYPE_ALL;
	aes_set_config(&g_aes_inst);

	/* Beginning of a new message. */
	aes_set_new_message(&g_aes_inst);

	/* Set the cryptographic key. */
	aes_write_key(&g_aes_inst, key128);

	/* Set the initialization vector. */
	aes_write_initvector(&g_aes_inst, init_vector);

	/* Write the data to be deciphered to the input data registers. */
	aes_write_input_data(&g_aes_inst, ref_cipher_text_ofb[0]);
	aes_write_input_data(&g_aes_inst, ref_cipher_text_ofb[1]);
	aes_write_input_data(&g_aes_inst, ref_cipher_text_ofb[2]);
	aes_write_input_data(&g_aes_inst, ref_cipher_text_ofb[3]);

	/* Wait for the end of the decryption process. */
	while (false == state) {
	}

	/* check the result. */
	if ((ref_plain_text[0] != output_data[0]) ||
			(ref_plain_text[1] != output_data[1]) ||
			(ref_plain_text[2] != output_data[2]) ||
			(ref_plain_text[3] != output_data[3])) {
		printf("\r\nKO!!!\r\n");
	} else {
		printf("\r\nOK!!!\r\n");
	}
}

/**
 * \brief CTR mode encryption and decryption test.
 */
static void ctr_mode_test(void)
{
	printf("\r\n-----------------------------------\r\n");
	printf("- 128bit cryptographic key\r\n");
	printf("- CTR cipher mode\r\n");
	printf("- all counter measures\r\n");
	printf("- input of 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_inst.aes_cfg->encrypt_mode = AES_ENCRYPTION;
	g_aes_inst.aes_cfg->key_size = AES_KEY_SIZE_128;
	g_aes_inst.aes_cfg->dma_mode = AES_MANUAL_MODE;
	g_aes_inst.aes_cfg->opmode = AES_CTR_MODE;
	g_aes_inst.aes_cfg->cfb_size = AES_CFB_SIZE_128;
	g_aes_inst.aes_cfg->countermeasure_mask = AES_COUNTERMEASURE_TYPE_ALL;
	aes_set_config(&g_aes_inst);

	/* Beginning of a new message. */
	aes_set_new_message(&g_aes_inst);

	/* Set the cryptographic key. */
	aes_write_key(&g_aes_inst, key128);

	/* Set the initialization vector. */
	aes_write_initvector(&g_aes_inst, init_vector_ctr);

	/* Write the data to be ciphered to the input data registers. */
	aes_write_input_data(&g_aes_inst, ref_plain_text[0]);
	aes_write_input_data(&g_aes_inst, ref_plain_text[1]);
	aes_write_input_data(&g_aes_inst, ref_plain_text[2]);
	aes_write_input_data(&g_aes_inst, ref_plain_text[3]);

	/* Wait for the end of the encryption process. */
	while (false == state) {
	}

	/* check the result. */
	if ((ref_cipher_text_ctr[0] != output_data[0]) ||
			(ref_cipher_text_ctr[1] != output_data[1]) ||
			(ref_cipher_text_ctr[2] != output_data[2]) ||
			(ref_cipher_text_ctr[3] != output_data[3])) {
		printf("\r\nKO!!!\r\n");
	} else {
		printf("\r\nOK!!!\r\n");
	}

	printf("\r\n-----------------------------------\r\n");
	printf("- 128bit cryptographic key\r\n");
	printf("- CTR decipher mode\r\n");
	printf("- all counter measures\r\n");
	printf("- input of 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_inst.aes_cfg->encrypt_mode = AES_DECRYPTION;
	g_aes_inst.aes_cfg->key_size = AES_KEY_SIZE_128;
	g_aes_inst.aes_cfg->dma_mode = AES_MANUAL_MODE;
	g_aes_inst.aes_cfg->opmode = AES_CTR_MODE;
	g_aes_inst.aes_cfg->cfb_size = AES_CFB_SIZE_128;
	g_aes_inst.aes_cfg->countermeasure_mask = AES_COUNTERMEASURE_TYPE_ALL;
	aes_set_config(&g_aes_inst);

	/* Beginning of a new message. */
	aes_set_new_message(&g_aes_inst);

	/* Set the cryptographic key. */
	aes_write_key(&g_aes_inst, key128);

	/* Set the initialization vector. */
	aes_write_initvector(&g_aes_inst, init_vector_ctr);

	/* Write the data to be deciphered to the input data registers. */
	aes_write_input_data(&g_aes_inst, ref_cipher_text_ctr[0]);
	aes_write_input_data(&g_aes_inst, ref_cipher_text_ctr[1]);
	aes_write_input_data(&g_aes_inst, ref_cipher_text_ctr[2]);
	aes_write_input_data(&g_aes_inst, ref_cipher_text_ctr[3]);

	/* Wait for the end of the decryption process. */
	while (false == state) {
	}

	/* check the result. */
	if ((ref_plain_text[0] != output_data[0]) ||
			(ref_plain_text[1] != output_data[1]) ||
			(ref_plain_text[2] != output_data[2]) ||
			(ref_plain_text[3] != output_data[3])) {
		printf("\r\nKO!!!\r\n");
	} else {
		printf("\r\nOK!!!\r\n");
	}
}

/**
 *  Configure serial console.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
#ifdef CONF_UART_CHAR_LENGTH
		.charlength = CONF_UART_CHAR_LENGTH,
#endif
		.paritytype = CONF_UART_PARITY,
#ifdef CONF_UART_STOP_BITS
		.stopbits = CONF_UART_STOP_BITS,
#endif
	};

	/* Configure console. */
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief Display the user menu on the terminal.
 */
static void display_menu(void)
{
	printf("Menu :\n\r"
			"  -- Select operation:\n\r"
			"  h: Display menu \n\r"
			"  1: ECB mode test. \n\r"
			"  2: CBC mode test. \n\r"
			"  3: CFB128 mode test. \n\r"
			"  4: OFB mode test. \n\r"
			"  5: CTR mode test. \n\r"
			"  d: ECB mode test with PDCA \n\r"
			"\n\r\n\r");
}

/**
 * \brief The main function.
 */
int main(void)
{
	uint8_t key;

	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	/* Initialize the console  */
	configure_console();

	/* Output example information */
	printf("-- AES Example --\r\n");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	/* Enable the AES module. */
	aes_get_config_defaults(&g_aes_cfg);
	aes_init(&g_aes_inst, AESA, &g_aes_cfg);
	aes_enable(&g_aes_inst);

	/* Enable AES interrupt. */
	aes_set_callback(&g_aes_inst, AES_INTERRUPT_INPUT_BUFFER_READY,
			aes_callback, 1);

	/* Display menu */
	display_menu();

	while (1) {
		scanf("%c", (char *)&key);

		switch (key) {
		case 'h':
			display_menu();
			break;

		case '1':
			printf("ECB mode encryption and decryption test.\r\n");
			ecb_mode_test();
			break;

		case '2':
			printf("CBC mode encryption and decryption test.\r\n");
			cbc_mode_test();
			break;

		case '3':
			printf("CFB128 mode encryption and decryption test.\r\n");
			cfb128_mode_test();
			break;

		case '4':
			printf("OFB mode encryption and decryption test.\r\n");
			ofb_mode_test();
			break;

		case '5':
			printf("CTR mode encryption and decryption test.\r\n");
			ctr_mode_test();
			break;

		case 'd':
			printf("ECB mode encryption and decryption test with PDCA.\r\n");
			ecb_mode_test_pdca();
			break;

		default:
			break;
		}
	}
}
