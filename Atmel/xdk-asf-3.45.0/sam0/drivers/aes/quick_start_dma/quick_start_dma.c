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

//! [module_var_dma]
struct dma_resource example_resource_tx;
struct dma_resource example_resource_rx;
COMPILER_ALIGNED(16)
DmacDescriptor example_descriptor_tx SECTION_DMAC_DESCRIPTOR;
DmacDescriptor example_descriptor_rx SECTION_DMAC_DESCRIPTOR;
//! [module_var_dma]

//! [setup]
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
 * \brief ECB mode encryption test with DMA.
 */
static void ecb_mode_test_dma(void)
{
	printf("\r\n-----------------------------------\r\n");
	printf("- 128bit cryptographic key\r\n");
	printf("- ECB cipher mode\r\n");
	printf("- DMA mode\r\n");
	printf("- 4 32bit words with DMA\r\n");
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

	dma_start_transfer_job(&example_resource_tx);
	aes_set_new_message(&aes_instance);
	aes_clear_new_message(&aes_instance);

	/* Wait DMA transfer */
	while (false == state) {
	}

	/* Wait for the end of the encryption process. */
	while (!(aes_get_status(&aes_instance) & AES_ENCRYPTION_COMPLETE)) {
	}

	state = false;
	dma_start_transfer_job(&example_resource_rx);

	/* Wait DMA transfer */
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
//! [encryption_mode]

}

static void transfer_tx_rx_done(struct dma_resource* const resource )
{
	state = true;
}

static void configure_dma_aes_wr(void)
{
	struct dma_resource_config tx_config;
	dma_get_config_defaults(&tx_config);

	tx_config.peripheral_trigger = AES_DMAC_ID_WR;
	tx_config.trigger_action = DMA_TRIGGER_ACTION_BLOCK;

	dma_allocate(&example_resource_tx, &tx_config);

	struct dma_descriptor_config tx_descriptor_config;

	dma_descriptor_get_config_defaults(&tx_descriptor_config);

	tx_descriptor_config.beat_size = DMA_BEAT_SIZE_WORD;
	tx_descriptor_config.dst_increment_enable = false;
	tx_descriptor_config.block_transfer_count = AES_EXAMPLE_REFBUF_SIZE;
	tx_descriptor_config.source_address = (uint32_t)ref_plain_text + sizeof(ref_plain_text);
	tx_descriptor_config.destination_address =(uint32_t) &(AES->INDATA);
	dma_descriptor_create(&example_descriptor_tx, &tx_descriptor_config);

	dma_add_descriptor(&example_resource_tx, &example_descriptor_tx);
}

static void configure_dma_aes_rd(void)
{

	struct dma_resource_config rx_config;

	dma_get_config_defaults(&rx_config);

	rx_config.peripheral_trigger = AES_DMAC_ID_RD;
	rx_config.trigger_action = DMA_TRIGGER_ACTION_BLOCK;

	dma_allocate(&example_resource_rx, &rx_config);

	struct dma_descriptor_config rx_descriptor_config;

	dma_descriptor_get_config_defaults(&rx_descriptor_config);

	rx_descriptor_config.beat_size = DMA_BEAT_SIZE_WORD;
	rx_descriptor_config.src_increment_enable = false;
	rx_descriptor_config.block_transfer_count = AES_EXAMPLE_REFBUF_SIZE;
	rx_descriptor_config.source_address = (uint32_t)&(AES->INDATA);
	rx_descriptor_config.destination_address =
		(uint32_t)output_data + sizeof(output_data);

	dma_descriptor_create(&example_descriptor_rx, &rx_descriptor_config);

	dma_add_descriptor(&example_resource_rx, &example_descriptor_rx);
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

//! [setup_dma]
	/* Configure AES DMA and enable callback */
	configure_dma_aes_wr();
	configure_dma_aes_rd();

	dma_register_callback(&example_resource_tx, transfer_tx_rx_done,
			DMA_CALLBACK_TRANSFER_DONE);
	dma_enable_callback(&example_resource_tx, DMA_CALLBACK_TRANSFER_DONE);

	dma_register_callback(&example_resource_rx, transfer_tx_rx_done,
			DMA_CALLBACK_TRANSFER_DONE);
	dma_enable_callback(&example_resource_rx, DMA_CALLBACK_TRANSFER_DONE);
//! [setup_dma]

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
	/* ECB mode encryption test with DMA */
	ecb_mode_test_dma();
//! [encryption_decryption]

	while(1) ;

}
