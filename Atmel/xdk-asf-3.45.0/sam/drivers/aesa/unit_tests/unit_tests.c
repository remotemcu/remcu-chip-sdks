/**
 * \file
 *
 * \brief Unit tests for AES driver.
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <conf_test.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the AES driver.
 * It contains two test case for the AES module:
 * - Test alarm interrupt and wakeup functions in calendar/counter mode.
 * - Test periodic interrupt and wakeup functions in counter mode.
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_uart_serial.h
 *
 * \section device_info Device Info
 * Only SAM4L devices can be used.
 * This example has been tested with the following setup:
 * - sam4lc4c_sam4l_ek
 * - sam4lc4c_sam4l_xplained_pro
 * - sam4lc8c_sam4l8_xplained_pro
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for ARM. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */

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

/** AES instance */
struct aes_dev_inst g_aes_inst;

/** AES configuration */
struct aes_config   g_aes_cfg;

/* State indicate */
volatile bool state = false;

volatile bool flag = false;

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
 * \brief Test ECB mode encryption and decryption with PDCA.
 *
 * \param test Current test case.
 */
static void run_ecb_mode_test_pdca(const struct test_case *test)
{
	/* Change the AES interrupt callback function. */
	aes_set_callback(&g_aes_inst, AES_INTERRUPT_INPUT_BUFFER_READY,
			aes_callback_pdca, 1);

	/* Enable PDCA module clock */
	pdca_enable(PDCA);

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
	delay_ms(30);

	/* Disable PDCA channel. */
	pdca_channel_disable(PDCA_RX_CHANNEL);
	pdca_channel_disable(PDCA_TX_CHANNEL);

	if ((ref_cipher_text_ecb[0] != output_data[0]) ||
			(ref_cipher_text_ecb[1] != output_data[1]) ||
			(ref_cipher_text_ecb[2] != output_data[2]) ||
			(ref_cipher_text_ecb[3] != output_data[3])) {
		flag = false;
	} else {
		flag = true;
	}

	test_assert_true(test, flag == true, "ECB mode encryption not work!");

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
	delay_ms(30);

	/* Disable PDCA channel. */
	pdca_channel_disable(PDCA_RX_CHANNEL);
	pdca_channel_disable(PDCA_TX_CHANNEL);

	/* check the result. */
	if ((ref_plain_text[0] != output_data[0]) ||
			(ref_plain_text[1] != output_data[1]) ||
			(ref_plain_text[2] != output_data[2]) ||
			(ref_plain_text[3] != output_data[3])) {
		flag = false;
	} else {
		flag = true;
	}

	test_assert_true(test, flag == true, "ECB mode decryption not work!");

	/* Disable PDCA module clock */
	pdca_disable(PDCA);

	/* Change back the AES interrupt callback function. */
	aes_set_callback(&g_aes_inst, AES_INTERRUPT_INPUT_BUFFER_READY,
			aes_callback, 1);
}

/**
 * \brief Test ECB mode encryption and decryption.
 *
 * \param test Current test case.
 */
static void run_ecb_mode_test(const struct test_case *test)
{
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
	delay_ms(30);

	if ((ref_cipher_text_ecb[0] != output_data[0]) ||
			(ref_cipher_text_ecb[1] != output_data[1]) ||
			(ref_cipher_text_ecb[2] != output_data[2]) ||
			(ref_cipher_text_ecb[3] != output_data[3])) {
		flag = false;
	} else {
		flag = true;
	}

	test_assert_true(test, flag == true, "ECB mode encryption not work!");

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
	delay_ms(30);

	/* check the result. */
	if ((ref_plain_text[0] != output_data[0]) ||
			(ref_plain_text[1] != output_data[1]) ||
			(ref_plain_text[2] != output_data[2]) ||
			(ref_plain_text[3] != output_data[3])) {
		flag = false;
	} else {
		flag = true;
	}

	test_assert_true(test, flag == true, "ECB mode decryption not work!");
}

/**
 * \brief Test CBC mode encryption and decryption.
 *
 * \param test Current test case.
 */
static void run_cbc_mode_test(const struct test_case *test)
{
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
	delay_ms(30);

	if ((ref_cipher_text_cbc[0] != output_data[0]) ||
			(ref_cipher_text_cbc[1] != output_data[1]) ||
			(ref_cipher_text_cbc[2] != output_data[2]) ||
			(ref_cipher_text_cbc[3] != output_data[3])) {
		flag = false;
	} else {
		flag = true;
	}

	test_assert_true(test, flag == true, "CBC mode encryption not work!");

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
	delay_ms(30);

	if ((ref_plain_text[0] != output_data[0]) ||
			(ref_plain_text[1] != output_data[1]) ||
			(ref_plain_text[2] != output_data[2]) ||
			(ref_plain_text[3] != output_data[3])) {
		flag = false;
	} else {
		flag = true;
	}

	test_assert_true(test, flag == true, "CBC mode decryption not work!");
}

/**
 * \brief Test CFB128 mode encryption and decryption.
 *
 * \param test Current test case.
 */
static void run_cfb128_mode_test(const struct test_case *test)
{
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
	delay_ms(30);

	/* check the result. */
	if ((ref_cipher_text_cfb128[0] != output_data[0]) ||
			(ref_cipher_text_cfb128[1] != output_data[1]) ||
			(ref_cipher_text_cfb128[2] != output_data[2]) ||
			(ref_cipher_text_cfb128[3] != output_data[3])) {
		flag = false;
	} else {
		flag = true;
	}

	test_assert_true(test, flag == true, "CFB128 mode encryption not work!");

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
	delay_ms(30);

	/* check the result. */
	if ((ref_plain_text[0] != output_data[0]) ||
			(ref_plain_text[1] != output_data[1]) ||
			(ref_plain_text[2] != output_data[2]) ||
			(ref_plain_text[3] != output_data[3])) {
		flag = false;
	} else {
		flag = true;
	}

	test_assert_true(test, flag == true, "CFB128 mode decryption not work!");
}

/**
 * \brief Test OFB mode encryption and decryption.
 *
 * \param test Current test case.
 */
static void run_ofb_mode_test(const struct test_case *test)
{
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
	delay_ms(30);

	/* check the result. */
	if ((ref_cipher_text_ofb[0] != output_data[0]) ||
			(ref_cipher_text_ofb[1] != output_data[1]) ||
			(ref_cipher_text_ofb[2] != output_data[2]) ||
			(ref_cipher_text_ofb[3] != output_data[3])) {
		flag = false;
	} else {
		flag = true;
	}

	test_assert_true(test, flag == true, "OFB mode encryption not work!");

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
	delay_ms(30);

	/* check the result. */
	if ((ref_plain_text[0] != output_data[0]) ||
			(ref_plain_text[1] != output_data[1]) ||
			(ref_plain_text[2] != output_data[2]) ||
			(ref_plain_text[3] != output_data[3])) {
		flag = false;
	} else {
		flag = true;
	}

	test_assert_true(test, flag == true, "OFB mode decryption not work!");
}

/**
 * \brief Test CTR mode encryption and decryption.
 *
 * \param test Current test case.
 */
static void run_ctr_mode_test(const struct test_case *test)
{
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
	delay_ms(30);

	/* check the result. */
	if ((ref_cipher_text_ctr[0] != output_data[0]) ||
			(ref_cipher_text_ctr[1] != output_data[1]) ||
			(ref_cipher_text_ctr[2] != output_data[2]) ||
			(ref_cipher_text_ctr[3] != output_data[3])) {
		flag = false;
	} else {
		flag = true;
	}

	test_assert_true(test, flag == true, "CTR mode encryption not work!");

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
	delay_ms(30);

	/* check the result. */
	if ((ref_plain_text[0] != output_data[0]) ||
			(ref_plain_text[1] != output_data[1]) ||
			(ref_plain_text[2] != output_data[2]) ||
			(ref_plain_text[3] != output_data[3])) {
		flag = false;
	} else {
		flag = true;
	}

	test_assert_true(test, flag == true, "CTR mode decryption not work!");
}

/**
 * \brief Run AES driver unit tests.
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits = CONF_TEST_STOPBITS
	};

	sysclk_init();
	board_init();
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Enable the AES module. */
	aes_get_config_defaults(&g_aes_cfg);
	aes_init(&g_aes_inst, AESA, &g_aes_cfg);
	aes_enable(&g_aes_inst);

	/* Enable AES interrupt. */
	aes_set_callback(&g_aes_inst, AES_INTERRUPT_INPUT_BUFFER_READY,
			aes_callback, 1);

	/* Define all the test cases. */
	DEFINE_TEST_CASE(ecb_mode_test, NULL, run_ecb_mode_test, NULL,
			"SAM AES ECB mode encryption and decryption test.");
	DEFINE_TEST_CASE(cbc_mode_test, NULL, run_cbc_mode_test, NULL,
			"SAM AES CBC mode encryption and decryption test.");
	DEFINE_TEST_CASE(cfb128_mode_test, NULL, run_cfb128_mode_test, NULL,
			"SAM AES CFB128 mode encryption and decryption test.");
	DEFINE_TEST_CASE(ofb_mode_test, NULL, run_ofb_mode_test, NULL,
			"SAM AES OFB mode encryption and decryption test.");
	DEFINE_TEST_CASE(ctr_mode_test, NULL, run_ctr_mode_test, NULL,
			"SAM AES CTR mode encryption and decryption test.");
	DEFINE_TEST_CASE(ecb_mode_test_pdca, NULL, run_ecb_mode_test_pdca, NULL,
			"SAM AES ECB mode encryption and decryption with PDCA test.");

	/* Put test case addresses in an array. */
	DEFINE_TEST_ARRAY(aes_tests) = {
		&ecb_mode_test,
		&cbc_mode_test,
		&cfb128_mode_test,
		&ofb_mode_test,
		&ctr_mode_test,
		&ecb_mode_test_pdca,
	};

	/* Define the test suite. */
	DEFINE_TEST_SUITE(aes_suite, aes_tests, "SAM AES driver test suite");

	/* Run all tests in the test suite. */
	test_suite_run(&aes_suite);

	while (1) {
		/* Busy-wait forever. */
	}
}
