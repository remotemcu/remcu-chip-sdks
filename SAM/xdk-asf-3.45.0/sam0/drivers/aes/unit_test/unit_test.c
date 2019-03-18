/**
 * \file
 *
 * \brief Unit tests for AES driver.
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

/**
 * \mainpage SAM AES Unit Test
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This unit test carries out tests for the AES driver.
 * It consists of test cases for the following functionalities:
 * - Electronic Codebook (ECB)
 * - Cipher Block Chaining (CBC)
 * - Output Feedback (OFB)
 * - Cipher Feedback (CFB)
 * - Counter (CTR)
 */

/**
 * \page appdoc_main SAM AES Unit Test
 *
 * Overview:
 * - \ref appdoc_sam0_aes_unit_test_intro
 * - \ref appdoc_sam0_aes_unit_test_setup
 * - \ref appdoc_sam0_aes_unit_test_usage
 * - \ref appdoc_sam0_aes_unit_test_compinfo
 * - \ref appdoc_sam0_aes_unit_test_contactinfo
 *
 * \section appdoc_sam0_aes_unit_test_intro Introduction
 * \copydetails appdoc_preface
 *
 * Tests will be performed for AES verious modes.
 *
 * The following kit is required for carrying out the test:
 *  - SAM L21 Xplained Pro board
 *  - SAM L22 Xplained Pro board
 *
 * \section appdoc_sam0_aes_unit_test_setup Setup
 * The following connections has to be made using wires:
 *  - \b None
 *
 * To run the test:
 *  - Connect the SAM Xplained Pro board to the computer using a
 *    micro USB cable.
 *  - Open the virtual COM port in a terminal application.
 *    \note The USB composite firmware running on the Embedded Debugger (EDBG)
 *          will enumerate as debugger, virtual COM port and EDBG data
 *          gateway.
 *  - Build the project, program the target and run the application.
 *    The terminal shows the results of the unit test.
 *
 * \section appdoc_sam0_aes_unit_test_usage Usage
 *  - The unit test carries out five AES modes of operation for internal checks.
 *
 * \section appdoc_sam0_aes_unit_test_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_aes_unit_test_contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com">http://www.microchip.com</a>.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <stdio_serial.h>
#include <string.h>

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

/* Output data array */
static uint32_t output_data[AES_EXAMPLE_REFBUF_SIZE];

/** AES configuration */
struct aes_config g_aes_cfg;
/* State flag */
volatile bool flag = false;
/* AES module instance */
struct aes_module aes_instance;
/* USART module instance */
struct usart_module usart_instance;
/* DNA resource */
struct dma_resource example_resource_tx;
struct dma_resource example_resource_rx;

COMPILER_ALIGNED(16)
DmacDescriptor example_descriptor_tx SECTION_DMAC_DESCRIPTOR;
DmacDescriptor example_descriptor_rx SECTION_DMAC_DESCRIPTOR;

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
 * \brief Configure DMA AES DATA write trigger.
 */
static void configure_dma_aes_wr(void)
{
	struct dma_resource_config tx_config;
	dma_get_config_defaults(&tx_config);

	tx_config.peripheral_trigger = AES_DMAC_ID_WR;
	tx_config.trigger_action = DMA_TRIGGER_ACTION_BLOCK;

	/* Allocate DMA resource.*/
	dma_allocate(&example_resource_tx, &tx_config);

	struct dma_descriptor_config tx_descriptor_config;

	dma_descriptor_get_config_defaults(&tx_descriptor_config);

	tx_descriptor_config.beat_size = DMA_BEAT_SIZE_WORD;
	tx_descriptor_config.dst_increment_enable = false;
	tx_descriptor_config.block_transfer_count = AES_EXAMPLE_REFBUF_SIZE;
	tx_descriptor_config.source_address = (uint32_t)ref_plain_text + sizeof(ref_plain_text);
	tx_descriptor_config.destination_address =(uint32_t) &(AES->INDATA);
	dma_descriptor_create(&example_descriptor_tx, &tx_descriptor_config);

	/*  Add DMA transfer descriptor to DMA resource.*/
	dma_add_descriptor(&example_resource_tx, &example_descriptor_tx);
}

/**
 * \brief Configure DMA AES DATA read trigger.
 */
static void configure_dma_aes_rd(void)
{

	struct dma_resource_config rx_config;

	dma_get_config_defaults(&rx_config);

	rx_config.peripheral_trigger = AES_DMAC_ID_RD;
	rx_config.trigger_action = DMA_TRIGGER_ACTION_BLOCK;

	/* Allocate DMA resource.*/
	dma_allocate(&example_resource_rx, &rx_config);

	struct dma_descriptor_config rx_descriptor_config;
	dma_descriptor_get_config_defaults(&rx_descriptor_config);

	rx_descriptor_config.beat_size = DMA_BEAT_SIZE_WORD;
	rx_descriptor_config.src_increment_enable = false;
	rx_descriptor_config.block_transfer_count = AES_EXAMPLE_REFBUF_SIZE;
	rx_descriptor_config.source_address = (uint32_t)&(AES->INDATA);
	rx_descriptor_config.destination_address =
		(uint32_t)output_data + sizeof(output_data);

	/* Create a DMA transfer descriptor.*/
	dma_descriptor_create(&example_descriptor_rx, &rx_descriptor_config);

	/* Add DMA transfer descriptor to DMA resource.*/
	dma_add_descriptor(&example_resource_rx, &example_descriptor_rx);
}

/**
 * \brief Test ECB mode encryption with DMA.
 *
 * \param test Current test case.
 */
static void run_ecb_mode_test_dma(const struct test_case *test)
{
	/* Configure DMAC. */
	configure_dma_aes_wr();
	configure_dma_aes_rd();

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

	dma_start_transfer_job(&example_resource_tx);
	aes_set_new_message(&aes_instance);
	aes_clear_new_message(&aes_instance);
	/* Wait for the end of the encryption process. */
	delay_ms(30);
	dma_start_transfer_job(&example_resource_rx);
	delay_ms(30);
	if ((ref_cipher_text_ecb[0] != output_data[0]) ||
			(ref_cipher_text_ecb[1] != output_data[1]) ||
			(ref_cipher_text_ecb[2] != output_data[2]) ||
			(ref_cipher_text_ecb[3] != output_data[3])) {
		flag = false;
	} else {
		flag = true;
	}

	test_assert_true(test, flag == true, "ECB mode encryption with DMA not work!");
}

/**
 * \brief Test ECB mode encryption and decryption.
 *
 * \param test Current test case.
 */
static void run_ecb_mode_test(const struct test_case *test)
{
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
	delay_ms(30);

	aes_read_output_data(&aes_instance,output_data);
	if ((ref_cipher_text_ecb[0] != output_data[0]) ||
			(ref_cipher_text_ecb[1] != output_data[1]) ||
			(ref_cipher_text_ecb[2] != output_data[2]) ||
			(ref_cipher_text_ecb[3] != output_data[3])) {
		flag = false;
	} else {
		flag = true;
	}

	test_assert_true(test, flag == true, "ECB mode encryption not work!");

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
	delay_ms(30);

	aes_read_output_data(&aes_instance,output_data);
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
	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_ENCRYPTION;
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
	/* Write the data to be ciphered to the input data registers. */
	aes_write_input_data(&aes_instance, ref_plain_text);
	aes_clear_new_message(&aes_instance);

	/* Wait for the end of the encryption process. */
	delay_ms(30);

	aes_read_output_data(&aes_instance,output_data);
	if ((ref_cipher_text_cbc[0] != output_data[0]) ||
			(ref_cipher_text_cbc[1] != output_data[1]) ||
			(ref_cipher_text_cbc[2] != output_data[2]) ||
			(ref_cipher_text_cbc[3] != output_data[3])) {
		flag = false;
	} else {
		flag = true;
	}

	test_assert_true(test, flag == true, "CBC mode encryption not work!");

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
	delay_ms(30);

	aes_read_output_data(&aes_instance,output_data);
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
	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_ENCRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_AUTO_START;
	g_aes_cfg.opmode = AES_CFB_MODE;
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
	delay_ms(30);

	aes_read_output_data(&aes_instance,output_data);
	/* check the result. */
	if ((ref_cipher_text_cfb128[0] != output_data[0]) ||
			(ref_cipher_text_cfb128[1] != output_data[1]) ||
			(ref_cipher_text_cfb128[2] != output_data[2]) ||
			(ref_cipher_text_cfb128[3] != output_data[3])) {
		flag = false;
	} else {
		flag = true;
	}

	test_assert_true(test, flag == true,
			"CFB128 mode encryption not work!");

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_DECRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_AUTO_START;
	g_aes_cfg.opmode = AES_CFB_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(&aes_instance,AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(&aes_instance, key128);

	/* Set the initialization vector. */
	aes_write_init_vector(&aes_instance, init_vector);

	aes_set_new_message(&aes_instance);
	/* Write the data to be deciphered to the input data registers. */
	aes_write_input_data(&aes_instance, ref_cipher_text_cfb128);
	aes_clear_new_message(&aes_instance);

	/* Wait for the end of the decryption process. */
	delay_ms(30);

	aes_read_output_data(&aes_instance,output_data);
	/* check the result. */
	if ((ref_plain_text[0] != output_data[0]) ||
			(ref_plain_text[1] != output_data[1]) ||
			(ref_plain_text[2] != output_data[2]) ||
			(ref_plain_text[3] != output_data[3])) {
		flag = false;
	} else {
		flag = true;
	}

	test_assert_true(test, flag == true,
			"CFB128 mode decryption not work!");
}

/**
 * \brief Test OFB mode encryption and decryption.
 *
 * \param test Current test case.
 */
static void run_ofb_mode_test(const struct test_case *test)
{
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
	delay_ms(30);

	aes_read_output_data(&aes_instance,output_data);
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

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_DECRYPTION;
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
	/* Write the data to be deciphered to the input data registers. */
	aes_write_input_data(&aes_instance, ref_cipher_text_ofb);
	aes_clear_new_message(&aes_instance);

	/* Wait for the end of the decryption process. */
	delay_ms(30);

	aes_read_output_data(&aes_instance,output_data);
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
	delay_ms(30);

	aes_read_output_data(&aes_instance,output_data);
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

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_DECRYPTION;
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
	/* Write the data to be deciphered to the input data registers. */
	aes_write_input_data(&aes_instance, ref_cipher_text_ctr);
	aes_clear_new_message(&aes_instance);

	/* Wait for the end of the decryption process. */
	delay_ms(30);

	aes_read_output_data(&aes_instance,output_data);
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
	/* Initialize the system and console*/
	system_init();
	configure_usart();

	/*Initialize the delay driver*/
	delay_init();

	/* Enable the AES module. */
	aes_get_config_defaults(&g_aes_cfg);
	aes_init(&aes_instance,AES, &g_aes_cfg);
	aes_enable(&aes_instance);

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
	DEFINE_TEST_CASE(ecb_mode_test_dma, NULL, run_ecb_mode_test_dma, NULL,
			"SAM AES ECB mode encryption and decryption with DMA test.");

	/* Put test case addresses in an array. */
	DEFINE_TEST_ARRAY(aes_tests) = {
		&ecb_mode_test,
		&cbc_mode_test,
		&cfb128_mode_test,
		&ofb_mode_test,
		&ctr_mode_test,
		&ecb_mode_test_dma,
	};

	/* Define the test suite. */
	DEFINE_TEST_SUITE(aes_suite, aes_tests, "SAM AES driver test suite");

	/* Run all tests in the test suite. */
	test_suite_run(&aes_suite);

	while (1) {
		/* Busy-wait forever. */
	}
}
