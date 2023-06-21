/**
 *
 * \file
 *
 * \brief AES example for SAM.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <string.h>

//! [cipher_data]
#define AES_EXAMPLE_REFBUF_SIZE 4

/**
 * \name sample data from NIST-800-38A appendix F
 */
/* @{ */
/** Reference plain data. */
uint32_t ref_plain_text[AES_EXAMPLE_REFBUF_SIZE] = {
	0xe2bec16b,
	0x969f402e,
	0x117e3de9,
	0x2a179373
};

/** Reference ECB cipher data. */
uint32_t ref_cipher_text_ecb[AES_EXAMPLE_REFBUF_SIZE] = {
	0xb47bd73a,
	0x60367a0d,
	0xf3ca9ea8,
	0x97ef6624
};

/** Reference CBC cipher data. */
uint32_t ref_cipher_text_cbc[AES_EXAMPLE_REFBUF_SIZE] = {
	0xacab4976,
	0x46b21981,
	0x9b8ee9ce,
	0x7d19e912
};

/** Reference CFB128 cipher data. */
uint32_t ref_cipher_text_cfb128[AES_EXAMPLE_REFBUF_SIZE] = {
	0x2ed93f3b,
	0x20ad2db7,
	0xf8493433,
	0x4afb3ce8
};

/** Reference OFB cipher data. */
uint32_t ref_cipher_text_ofb[AES_EXAMPLE_REFBUF_SIZE] = {
	0x2ed93f3b,
	0x20ad2db7,
	0xf8493433,
	0x4afb3ce8
};

/** Reference CTR cipher data. */
uint32_t ref_cipher_text_ctr[AES_EXAMPLE_REFBUF_SIZE] = {
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
//! [cipher_data]

//! [module_var]
/* Output data array */
static uint32_t output_data[AES_EXAMPLE_REFBUF_SIZE];
/* State indicate */
volatile bool state = false;

/** AES configuration */
struct aes_config g_aes_cfg;
struct aes_module aes_instance;
struct usart_module usart_instance;
//! [module_var]

//! [setup]

static void configure_usart(void)
{

	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);
	config_usart.baudrate    = 38400;
	config_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	stdio_serial_init(&usart_instance, EDBG_CDC_MODULE, &config_usart);
	usart_enable(&usart_instance);
}


/**
 * \brief The AES interrupt call back function.
 */
static void aes_callback(void)
{
	/* Read the output. */
	aes_read_output_data(&aes_instance, output_data);
	state = true;
}

/**
 * \brief ECB mode encryption and decryption test.
 */
static void ecb_mode_test(void)
{
	printf("\r\n-----------------------------------\r\n");
	printf("- 128bit cryptographic key\r\n");
	printf("- ECB cipher mode\r\n");
	printf("- Auto start mode\r\n");
	printf("- 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_ENCRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_AUTO_START;
	g_aes_cfg.opmode = AES_ECB_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(&aes_instance,AES, &g_aes_cfg);
	/* Set the cryptographic key. */
	aes_write_key(&aes_instance, key128);

	/* The initialization vector is not used by the ECB cipher mode. */

	aes_set_new_message(&aes_instance);
	/* Write the data to be ciphered to the input data registers. */
	aes_write_input_data(&aes_instance, ref_plain_text);
	aes_clear_new_message(&aes_instance);

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
	printf("- Auto start mode\r\n");
	printf("- 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_DECRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_AUTO_START;
	g_aes_cfg.opmode = AES_ECB_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(&aes_instance,AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(&aes_instance, key128);

	/* The initialization vector is not used by the ECB cipher mode. */
	aes_set_new_message(&aes_instance);
	/* Write the data to be deciphered to the input data registers. */
	aes_write_input_data(&aes_instance, ref_cipher_text_ecb);
	aes_clear_new_message(&aes_instance);
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
	printf("- Auto start mode\r\n");
	printf("- 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_ENCRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_MANUAL_START;
	g_aes_cfg.opmode = AES_CBC_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(&aes_instance,AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(&aes_instance, key128);

	/* Set the initialization vector. */
	aes_write_init_vector(&aes_instance, init_vector);

	/* Write the data to be ciphered to the input data registers. */
	aes_write_input_data(&aes_instance, ref_plain_text);
	aes_set_new_message(&aes_instance);
	aes_start(&aes_instance);
	aes_clear_new_message(&aes_instance);
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
	printf("- Auto start mode\r\n");
	printf("- 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_DECRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_AUTO_START;
	g_aes_cfg.opmode = AES_CBC_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(&aes_instance,AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(&aes_instance, key128);

	/* Set the initialization vector. */
	aes_write_init_vector(&aes_instance, init_vector);

	aes_set_new_message(&aes_instance);
	/* Write the data to be deciphered to the input data registers. */
	aes_write_input_data(&aes_instance, ref_cipher_text_cbc);
	aes_clear_new_message(&aes_instance);

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
	printf("- Auto start mode\r\n");
	printf("- 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_ENCRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_MANUAL_START;
	g_aes_cfg.opmode = AES_CFB_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(&aes_instance,AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(&aes_instance, key128);

	/* Set the initialization vector. */
	aes_write_init_vector(&aes_instance, init_vector);

	/* Write the data to be ciphered to the input data registers. */
	aes_write_input_data(&aes_instance, ref_plain_text);
	aes_set_new_message(&aes_instance);
	aes_start(&aes_instance);
	aes_clear_new_message(&aes_instance);
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
	printf("- Auto start mode\r\n");
	printf("- 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_DECRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_MANUAL_START;
	g_aes_cfg.opmode = AES_CFB_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(&aes_instance,AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(&aes_instance, key128);

	/* Set the initialization vector. */
	aes_write_init_vector(&aes_instance, init_vector);

	/* Write the data to be deciphered to the input data registers. */
	aes_write_input_data(&aes_instance, ref_cipher_text_cfb128);
	aes_set_new_message(&aes_instance);
	aes_start(&aes_instance);
	aes_clear_new_message(&aes_instance);
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
	printf("- Auto start mode\r\n");
	printf("- 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_ENCRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_AUTO_START;
	g_aes_cfg.opmode = AES_OFB_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(&aes_instance,AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(&aes_instance, key128);

	/* Set the initialization vector. */
	aes_write_init_vector(&aes_instance, init_vector);
	aes_set_new_message(&aes_instance);
	/* Write the data to be ciphered to the input data registers. */
	aes_write_input_data(&aes_instance, ref_plain_text);
	aes_clear_new_message(&aes_instance);
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
	printf("- Auto start mode\r\n");
	printf("- 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_DECRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_MANUAL_START;
	g_aes_cfg.opmode = AES_OFB_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(&aes_instance,AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(&aes_instance, key128);

	/* Set the initialization vector. */
	aes_write_init_vector(&aes_instance, init_vector);

	/* Write the data to be deciphered to the input data registers. */
	aes_write_input_data(&aes_instance, ref_cipher_text_ofb);

	aes_set_new_message(&aes_instance);
	aes_start(&aes_instance);
	aes_clear_new_message(&aes_instance);

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
	printf("- Auto start mode\r\n");
	printf("- 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_ENCRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_AUTO_START;
	g_aes_cfg.opmode = AES_CTR_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(&aes_instance,AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(&aes_instance, key128);

	/* Set the initialization vector. */
	aes_write_init_vector(&aes_instance, init_vector_ctr);
	aes_set_new_message(&aes_instance);
	/* Write the data to be ciphered to the input data registers. */
	aes_write_input_data(&aes_instance, ref_plain_text);
	aes_clear_new_message(&aes_instance);

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
	printf("- Auto start mode\r\n");
	printf("- 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_DECRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_MANUAL_START;
	g_aes_cfg.opmode = AES_CTR_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(&aes_instance,AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(&aes_instance, key128);

	/* Set the initialization vector. */
	aes_write_init_vector(&aes_instance, init_vector_ctr);

	/* Write the data to be deciphered to the input data registers. */
	aes_write_input_data(&aes_instance, ref_cipher_text_ctr);

	aes_set_new_message(&aes_instance);
	aes_start(&aes_instance);
	aes_clear_new_message(&aes_instance);
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
//! [setup]

/**
 * \brief The main function.
 */
int main(void)
{
//! [setup_init]

	/* Initialize the system and console*/
	system_init();
	configure_usart();

//! [setup_config]
	aes_get_config_defaults(&g_aes_cfg);
//! [setup_config]
//! [setup_config_defaults]
	aes_init(&aes_instance,AES, &g_aes_cfg);
//! [setup_config_defaults]

//! [module_enable]
	aes_enable(&aes_instance);
//! [module_enable]

//! [module_enable_register]
	/* Enable AES interrupt. */
	aes_register_callback(aes_callback,AES_CALLBACK_ENCRYPTION_COMPLETE);
	aes_enable_callback(&aes_instance,AES_CALLBACK_ENCRYPTION_COMPLETE);
//! [module_enable_register]

//! [setup_init]
	printf("Start test\r\n");
//! [encryption_decryption]
//![ECB_MODE]
	ecb_mode_test();
//![ECB_MODE]
//![CBC_MODE]
	cbc_mode_test();
//![CBC_MODE]
//![CFB_MODE]
	cfb128_mode_test();
//![CFB_MODE]
//![OFB_MODE]
	ofb_mode_test();
//![OFB_MODE]
//![CTR_MODE]
	ctr_mode_test();
//![CTR_MODE]

//! [encryption_decryption]

	while(1) ;

}
