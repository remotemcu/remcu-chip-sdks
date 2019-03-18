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

/** Cipher 128 bits key array. */
const uint32_t key128[4] = {
	0x16157e2b,
	0xa6d2ae28,
	0x8815f7ab,
	0x3c4fcf09
};
/* @} */
//! [cipher_data]

//! [module_var]
/* Output data array */
static uint32_t output_data[AES_EXAMPLE_REFBUF_SIZE];

/* State indicate */
volatile bool state = false;
/* AES configuration */
struct aes_config g_aes_cfg;
/* AES instance*/
struct aes_module aes_instance;
struct usart_module usart_instance;
//! [module_var]

//! [setup]

/**
 * \brief Configure usart.
 */
static void configure_usart(void)
{

	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);
	config_usart.baudrate	 = 38400;
	config_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	stdio_serial_init(&usart_instance, EDBG_CDC_MODULE, &config_usart);
	usart_enable(&usart_instance);
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

//! [encryption_mode]

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
	while (!(aes_get_status(&aes_instance) & AES_ENCRYPTION_COMPLETE)) {
	}
	aes_read_output_data(&aes_instance,output_data);

	if ((ref_cipher_text_ecb[0] != output_data[0]) ||
			(ref_cipher_text_ecb[1] != output_data[1]) ||
			(ref_cipher_text_ecb[2] != output_data[2]) ||
			(ref_cipher_text_ecb[3] != output_data[3])) {
		printf("\r\nKO!!!\r\n");
	} else {
		printf("\r\nOK!!!\r\n");
	}
//! [encryption_mode]
	printf("\r\n-----------------------------------\r\n");
	printf("- 128bit cryptographic key\r\n");
	printf("- ECB decipher mode\r\n");
	printf("- Auto start mode\r\n");
	printf("- 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

//! [decryption_mode]

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

	/* Write the data to be deciphered to the input data registers. */
	aes_write_input_data(&aes_instance, ref_cipher_text_ecb);

	/* Wait for the end of the decryption process. */
	while (!(aes_get_status(&aes_instance) & AES_ENCRYPTION_COMPLETE)) {
	}
	aes_read_output_data(&aes_instance,output_data);

	/* check the result. */
	if ((ref_plain_text[0] != output_data[0]) ||
			(ref_plain_text[1] != output_data[1]) ||
			(ref_plain_text[2] != output_data[2]) ||
			(ref_plain_text[3] != output_data[3])) {
		printf("\r\nKO!!!\r\n");
	} else {
		printf("\r\nOK!!!\r\n");
	}
//! [decryption_mode]

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

//! [setup_init]

//! [encryption_decryption]
	/* Run ECB mode test*/
	ecb_mode_test();
//! [encryption_decryption]

	while (true) {
		/* Infinite loop */
	}
}

