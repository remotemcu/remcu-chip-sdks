/**
 *
 * \file
 *
 * \brief AES-GCM example for SAM.
 *
 * This file defines a useful set of functions for the AES-GCM mode on SAM
 *devices.
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
#include <string.h>

/* Key Sizes in bytes - 256 bits */
#define AES_KEY_SIZE            8

/* IV Size in bytes - 96 bits */
#define AES_IV_SIZE             3

/* TAG size in bytes - 128 bits */
#define AES_TAG_SIZE            4

/* Max Plain Text Size (16 byte aligned for padding) used in bytes -  bits */
#define AES_PDATA_SIZE          8

/* Max AAD Size (16 byte aligned for padding) used in bytes -  bits */
#define AES_AAD_SIZE            8

/* Effective AAD Size */
#define AES_AAD_EFFECTIVE_SIZE          20

/* Effective Plain Text Size */
#define AES_PDATA_EFFECTIVE_SIZE        20

/**
 * \name reference data for AES-GCM mode
 */
/* @{ */

/* GCM Mode Test Key, 256-bits */
uint32_t aes_key[AES_KEY_SIZE] = {
	0xcf76d4f8,
	0x6cea46d6,
	0x1ccb8423,
	0x5d19d627,
	0xf3a9f1fe,
	0x218d9c7b,
	0xf8219ca7,
	0x89d290cb
};

/* GCM Mode Test Iv, 96-bits */
uint32_t aes_iv[AES_IV_SIZE] = {
	0x63a3d1db,
	0xb4b72460,
	0x6f7dda02
};

/* GCM Mode Test plain text, 160-bits */
uint32_t aes_plain_text[AES_PDATA_SIZE] = {
	0xcf61ae90,
	0x4cbdae7b,
	0xc594e4ad,
	0x70ae294a,
	0x71ec9a26
};

/* GCM Mode Test AAD, 160-bits */
uint32_t aes_aad[AES_AAD_SIZE] = {
	0xa259d87b,
	0x211a9647,
	0x0e383b82,
	0x50b6e89f,
	0xd361ba82
};

/* Reference GCM cipher data */
uint32_t aes_cipher_text[AES_PDATA_SIZE] = {
	0xb42720ce,
	0x5232847a,
	0x83653401,
	0x0ffd754d,
	0x2e752907
};

/* Reference GCM Tag data */
uint32_t aes_tag[AES_TAG_SIZE] = {
	0x3883d8ac,
	0xde0eab37,
	0x8d74f484,
	0x159c89a8
};

/* @} */

/* GCM Input Structure */
struct gcm_input {
	uint32_t iv_len;
	uint32_t text_len;
	uint32_t aad_len;
	uint32_t key_len;
	uint32_t *key;
	uint32_t *iv;
	uint32_t *input;
	uint32_t *output;
	uint32_t *aad;
	uint32_t *tag;
};

/* Output data array */
static uint32_t output_data[AES_PDATA_SIZE];

/* Tag data array */
static uint32_t tag_data[AES_TAG_SIZE];

/** AES configuration */
struct aes_config g_aes_cfg;

/** GCM Input */
struct gcm_input gcm_input_data;

/**
 * \brief Read the GCM Authentication Tag "T" generated in AES_TAGRx registers.
 *
 * \param p_aes             Base address of the AES instance.
 * \param p_auth_tag_buffer Pointer to output buffer of 4 contiguous 32-bit
 *words.
 *
 */
static void aes_read_gcm_auth_tag(Aes *const p_aes, uint32_t *p_auth_tag_buffer)
{
	uint8_t i;
	for (i = 0; i < 4; i++) {
		p_auth_tag_buffer[i] = aes_read_tag(p_aes, i);
	}
}

/**
 * \brief GCM mode encryption and generate tag automatically.
 */
static void gcm_mode_encryption_test(void)
{
	printf("\r\n-----------------------------------\r\n");
	printf("- 256bit cryptographic key\r\n");
	printf("- GCM Encryption\r\n");
	printf("- Auto start mode\r\n");
	printf("- input of 160-bit effective words\r\n");
	printf("-----------------------------------\r\n");

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_ENCRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_256;
	g_aes_cfg.start_mode = AES_AUTO_START;
	g_aes_cfg.opmode = AES_GCM_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;

	/* AES-GCM Input Configuration */
	gcm_input_data.key = aes_key;
	gcm_input_data.key_len = AES_KEY_SIZE;
	gcm_input_data.iv = aes_iv;
	gcm_input_data.iv_len = AES_IV_SIZE;
	gcm_input_data.input = aes_plain_text;
	gcm_input_data.text_len = AES_PDATA_EFFECTIVE_SIZE;
	gcm_input_data.aad = aes_aad;
	gcm_input_data.aad_len = AES_AAD_EFFECTIVE_SIZE;
	gcm_input_data.output = output_data;
	gcm_input_data.tag = tag_data;
	
	/* Set GTAGEN to '1' and generate Tag automatically */
	g_aes_cfg.gtag_en = true;
	aes_set_config(AES, &g_aes_cfg);

	/* Write the key to generate GCMH Subkey */
	aes_write_key(AES, gcm_input_data.key);

	/* Wait for the GCMH to generate */
	while (!(aes_read_interrupt_status(AES) & AES_ISR_DATRDY)) {
	}

	/* Generate J0 using IV(96 Bits) */
	uint32_t i;
	/* J0 data array */
	uint32_t j0[4];

	for (i = 0; i < 3; i++) {
		j0[i] = gcm_input_data.iv[i];
	}
	/* Write the j0 + 1 in IV register */
	j0[3] = 0x02000000;

	aes_write_initvector(AES, j0);

	/* set AADLEN */
	aes_write_authen_datalength(AES, gcm_input_data.aad_len);

	/* Set CLEN */
	aes_write_pctext_length(AES, gcm_input_data.text_len);

	/* Write AAD Data for TAG generation */
	uint32_t offset = 0;
	for (i = 0; i < (AES_AAD_SIZE / 4); i++) {
		/* write the input data */
		aes_write_input_data(AES, (gcm_input_data.aad + offset));
		/* Wait till TAG is ready */
		while (!(aes_read_interrupt_status(AES) & AES_ISR_DATRDY)) {
		}
		/* 16-Byte Boundaries */
		offset += 4;
	}

	/* Reset offset to zero */
	offset = 0;

	/* Write plain text for cipher text generation */
	for (i = 0; i < (AES_PDATA_SIZE / 4); i++) {
		/* write the input data */
		aes_write_input_data(AES, (gcm_input_data.input + offset));
		/* Wait for the operation to complete */
		while (!(aes_read_interrupt_status(AES) & AES_ISR_DATRDY)) {
		}
		aes_read_output_data(AES,
				(uint32_t *)(gcm_input_data.output + offset));
		offset += 4;
	}

	/* Wait for the operation to complete */
	while (!(aes_read_interrupt_status(AES) & AES_ISR_TAGRDY)) {
	}
	/* Read the generated tag */
	aes_read_gcm_auth_tag(AES, gcm_input_data.tag);

	if (memcmp(tag_data, aes_tag, AES_TAG_SIZE) != 0) {
		printf("\n\rTAG GENERATE FAILED! ");
	} else {
		printf("\n\rTAG GENERATE SUCCESS! ");
	}

	if (memcmp(output_data, aes_cipher_text,
			AES_PDATA_EFFECTIVE_SIZE) != 0) {
		printf("\n\rENC COMPARE FAILED! ");
	} else {
		printf("\n\rENC COMPARE SUCCESS! ");
	}
}

/**
 * \brief GCM mode decryption test.
 */
static void gcm_mode_decryption_test(void)
{
	printf("\r\n-----------------------------------\r\n");
	printf("- 256bit cryptographic key\r\n");
	printf("- GCM Decryption\r\n");
	printf("- Auto start mode\r\n");
	printf("- input of 160-bit effective words\r\n");
	printf("-----------------------------------\r\n");

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_DECRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_256;
	g_aes_cfg.start_mode = AES_AUTO_START;
	g_aes_cfg.opmode = AES_GCM_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	g_aes_cfg.gtag_en = false;
	aes_set_config(AES, &g_aes_cfg);

	/* AES-GCM Input Configuration */
	gcm_input_data.key = aes_key;
	gcm_input_data.key_len = AES_KEY_SIZE;
	gcm_input_data.iv = aes_iv;
	gcm_input_data.iv_len = AES_IV_SIZE;
	gcm_input_data.input = aes_cipher_text;
	gcm_input_data.text_len = AES_PDATA_EFFECTIVE_SIZE;
	gcm_input_data.aad = aes_aad;
	gcm_input_data.aad_len = AES_AAD_EFFECTIVE_SIZE;
	gcm_input_data.output = output_data;
	gcm_input_data.tag = tag_data;

	/* Write the key to generate GCMH Subkey */
	aes_write_key(AES, gcm_input_data.key);

	/* Wait for the GCMH to generate */
	while (!(aes_read_interrupt_status(AES) & AES_ISR_DATRDY)) {
	}

	/* Generate J0 using IV(96 Bits) */
	uint32_t i;
	/* J0 data array */
	uint32_t j0[4];

	for (i = 0; i < 3; i++) {
		j0[i] = gcm_input_data.iv[i];
	}
	/* Write the j0 + 1 in IV register */
	j0[3] = 0x02000000;

	aes_write_initvector(AES, (uint32_t *)j0);

	/* set AADLEN */
	aes_write_authen_datalength(AES, gcm_input_data.aad_len);

	/* Set CLEN */
	aes_write_pctext_length(AES, gcm_input_data.text_len);

	/* Write AAD Data for TAG generation */
	uint32_t offset = 0;
	for (i = 0; i < (AES_AAD_SIZE / 4); i++) {
		/* write the input data */
		aes_write_input_data(AES, (gcm_input_data.aad + offset));
		/* Wait till TAG is ready */
		while (!(aes_read_interrupt_status(AES) & AES_ISR_DATRDY)) {
		}
		/* 16-Byte Boundaries */
		offset += 4;
	}

	/* Reset offset to zero */
	offset = 0;

	/* Write plain text for cipher text generation */
	for (i = 0; i < (AES_PDATA_SIZE / 4); i++) {
		/* write the input data */
		aes_write_input_data(AES, (gcm_input_data.input + offset));
		/* Wait for the operation to complete */
		while (!(aes_read_interrupt_status(AES) & AES_ISR_DATRDY)) {
		}
		aes_read_output_data(AES,
				(uint32_t *)(gcm_input_data.output + offset));
		offset += 4;
	}

	if (memcmp(output_data, aes_plain_text,
			AES_PDATA_EFFECTIVE_SIZE) != 0) {
		printf("\n\rDEC COMPARE FAILED! ");
	} else {
		printf("\n\rDEC COMPARE SUCCESS! ");
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
			"  e: GCM mode encryption test. \n\r"
			"  d: GCM mode decryption test. \n\r"
			"  \n\r\n\r");
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
	aes_init(AES, &g_aes_cfg);
	aes_enable();

	/* Enable AES interrupt. */
	aes_enable_interrupt(AES, AES_INTERRUPT_DATA_READY);

	/* Display menu */
	display_menu();

	while (1) {
		scanf("%c", (char *)&key);

		switch (key) {
		case 'h':
			display_menu();
			break;

		case 'e':
			printf("GCM mode encryption test.\r\n");
			gcm_mode_encryption_test();
			break;

		case 'd':
			printf("GCM mode decryption test.\r\n");
			gcm_mode_decryption_test();
			break;

		default:
			break;
		}
	}
}
