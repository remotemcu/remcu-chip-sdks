/**
 *
 * \file
 *
 * \brief AES example for SAM.
 *
 * This file defines a useful set of functions for the AES on SAM devices.
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

/* State indicate */
volatile bool state = false;

/** AES configuration */
struct aes_config g_aes_cfg;

#if SAM4E
/** DMAC transmit channel. */
#define AES_DMA_TX_CH    0

/** DMAC receive channel. */
#define AES_DMA_RX_CH    1
#endif

/**
 * \brief The AES interrupt call back function.
 */
static void aes_callback(void)
{
	/* Read the output. */
	aes_read_output_data(AES, output_data);
	state = true;
}

#if SAM4E

/**
 * \brief DMAC driver configuration.
 */
static void configure_dmac(void)
{
	uint32_t ul_cfg;

	/* Initialize and enable DMA controller. */
	pmc_enable_periph_clk(ID_DMAC);
	dmac_init(DMAC);
	dmac_set_priority_mode(DMAC, DMAC_PRIORITY_ROUND_ROBIN);
	dmac_enable(DMAC);

	/* Configure DMA RX channel. */
	ul_cfg = 0;
	ul_cfg |= DMAC_CFG_SRC_PER(AES_DMA_RX_IDX) |
			DMAC_CFG_SRC_H2SEL |
			DMAC_CFG_SOD | DMAC_CFG_FIFOCFG_ALAP_CFG;
	dmac_channel_set_configuration(DMAC, AES_DMA_RX_CH, ul_cfg);

	/* Configure DMA TX channel. */
	ul_cfg = 0;
	ul_cfg |= DMAC_CFG_DST_PER(AES_DMA_TX_IDX) |
			DMAC_CFG_DST_H2SEL |
			DMAC_CFG_SOD | DMAC_CFG_FIFOCFG_ALAP_CFG;
	dmac_channel_set_configuration(DMAC, AES_DMA_TX_CH, ul_cfg);

	/* Enable receive channel interrupt for DMAC. */
	NVIC_EnableIRQ(DMAC_IRQn);
	dmac_enable_interrupt(DMAC, (DMAC_EBCIER_BTC0 << AES_DMA_RX_CH));
}

/**
 * \brief Config AES DMA receive.
 *
 * \param p_buf   Pointer to buffer to transfer.
 * \param ul_size Size of the buffer.
 */
static void aes_dma_receive_config(void *p_buf, uint32_t ul_size)
{
	dma_transfer_descriptor_t dmac_trans;

	dmac_trans.ul_source_addr = (uint32_t)&AES->AES_ODATAR[0];
	dmac_trans.ul_destination_addr = (uint32_t)p_buf;
	dmac_trans.ul_ctrlA = ul_size | DMAC_CTRLA_SRC_WIDTH_WORD |
			DMAC_CTRLA_DST_WIDTH_WORD;
	dmac_trans.ul_ctrlB = DMAC_CTRLB_SRC_DSCR | DMAC_CTRLB_DST_DSCR |
			DMAC_CTRLB_FC_PER2MEM_DMA_FC |
			DMAC_CTRLB_SRC_INCR_FIXED |
			DMAC_CTRLB_DST_INCR_INCREMENTING;
	dmac_trans.ul_descriptor_addr = 0;
	dmac_channel_single_buf_transfer_init(DMAC, AES_DMA_RX_CH,
			(dma_transfer_descriptor_t *)&dmac_trans);
}

/**
 * \brief Config AES DMA transmit.
 *
 * \param pbuf    Pointer to buffer to transfer.
 * \param ul_size Size of the buffer.
 */
static void aes_dma_transmit_config(void *p_buf, uint32_t ul_size)
{
	dma_transfer_descriptor_t dmac_trans;

	dmac_trans.ul_source_addr = (uint32_t)p_buf;
	dmac_trans.ul_destination_addr = (uint32_t)&AES->AES_IDATAR[0];
	dmac_trans.ul_ctrlA = ul_size | DMAC_CTRLA_SRC_WIDTH_WORD |
			DMAC_CTRLA_DST_WIDTH_WORD;
	dmac_trans.ul_ctrlB = DMAC_CTRLB_SRC_DSCR | DMAC_CTRLB_DST_DSCR |
			DMAC_CTRLB_FC_MEM2PER_DMA_FC |
			DMAC_CTRLB_SRC_INCR_INCREMENTING |
			DMAC_CTRLB_DST_INCR_FIXED;
	dmac_trans.ul_descriptor_addr = 0;
	dmac_channel_single_buf_transfer_init(DMAC, AES_DMA_TX_CH,
			(dma_transfer_descriptor_t *)&dmac_trans);
}

/**
 * \brief Interrupt handler for the DMAC.
 */
void DMAC_Handler(void)
{
	static uint32_t ul_status;

	ul_status = dmac_get_status(DMAC);
	if (ul_status & (1 << AES_DMA_RX_CH)) {
		state = true;
	}
}

/**
 * \brief ECB mode encryption and decryption test with DMA.
 */
static void ecb_mode_test_dma(void)
{
	/* Configure DMAC. */
	configure_dmac();
	/* Disable DMAC channel. */
	dmac_channel_disable(DMAC, AES_DMA_TX_CH);
	dmac_channel_disable(DMAC, AES_DMA_RX_CH);

	printf("\r\n-----------------------------------\r\n");
	printf("- 128bit cryptographic key\r\n");
	printf("- ECB cipher mode\r\n");
	printf("- DMA mode\r\n");
	printf("- input of 4 32bit words with DMA\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_ENCRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_IDATAR0_START;
	g_aes_cfg.opmode = AES_ECB_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(AES, key128);

	/* The initialization vector is not used by the ECB cipher mode. */

	/* Write the data to be ciphered by DMA. */
	aes_dma_transmit_config(ref_plain_text, AES_EXAMPLE_REFBUF_SIZE);
	aes_dma_receive_config(output_data, AES_EXAMPLE_REFBUF_SIZE);
	/* Enable DMAC channel. */
	dmac_channel_enable(DMAC, AES_DMA_RX_CH);
	dmac_channel_enable(DMAC, AES_DMA_TX_CH);

	/* Wait for the end of the encryption process. */
	while (false == state) {
	}

	/* Disable DMAC channel. */
	dmac_channel_disable(DMAC, AES_DMA_TX_CH);
	dmac_channel_disable(DMAC, AES_DMA_RX_CH);

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
	printf("- DMA mode\r\n");
	printf("- input of 4 32bit words with DMA\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_DECRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_IDATAR0_START;
	g_aes_cfg.opmode = AES_ECB_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(AES, key128);

	/* The initialization vector is not used by the ECB cipher mode. */

	/* Write the data to be ciphered by DMA. */
	aes_dma_transmit_config(ref_cipher_text_ecb, AES_EXAMPLE_REFBUF_SIZE);
	aes_dma_receive_config(output_data, AES_EXAMPLE_REFBUF_SIZE);
	/* Enable DMAC channel. */
	dmac_channel_enable(DMAC, AES_DMA_RX_CH);
	dmac_channel_enable(DMAC, AES_DMA_TX_CH);

	/* Wait for the end of the decryption process. */
	while (false == state) {
	}

	/* Disable DMAC channel. */
	dmac_channel_disable(DMAC, AES_DMA_TX_CH);
	dmac_channel_disable(DMAC, AES_DMA_RX_CH);

	/* check the result. */
	if ((ref_plain_text[0] != output_data[0]) ||
			(ref_plain_text[1] != output_data[1]) ||
			(ref_plain_text[2] != output_data[2]) ||
			(ref_plain_text[3] != output_data[3])) {
		printf("\r\nKO!!!\r\n");
	} else {
		printf("\r\nOK!!!\r\n");
	}

	/* Disable DMAC module */
	dmac_disable(DMAC);
}

#endif

#if SAM4C || SAM4CP || SAM4CM
/* PDC data packet for transfer */
pdc_packet_t g_pdc_tx_packet;
pdc_packet_t g_pdc_rx_packet;

/* Pointer to AES PDC register base */
Pdc *g_p_aes_pdc;

/**
 * \brief The AES interrupt call back function under PDC mode.
 */
static void aes_pdc_callback(void)
{
	state = true;
	pdc_disable_transfer(g_p_aes_pdc,
			PERIPH_PTCR_RXTDIS | PERIPH_PTCR_TXTDIS);
	pdc_tx_init(g_p_aes_pdc, &g_pdc_tx_packet, NULL);
	pdc_rx_init(g_p_aes_pdc, &g_pdc_rx_packet, NULL);
}

/**
 * \brief ECB mode encryption and decryption test with PDC.
 */
static void ecb_mode_test_pdc(void)
{
	/* Configure PDC. */
	g_pdc_tx_packet.ul_addr = (uint32_t)ref_plain_text;
	g_pdc_tx_packet.ul_size = AES_EXAMPLE_REFBUF_SIZE;
	g_pdc_rx_packet.ul_addr = (uint32_t)output_data;
	g_pdc_rx_packet.ul_size = AES_EXAMPLE_REFBUF_SIZE;
	g_p_aes_pdc = aes_get_pdc_base(AES);

	/* Configure PDC for data receive & transfer */
	pdc_tx_init(g_p_aes_pdc, &g_pdc_tx_packet, NULL);
	pdc_rx_init(g_p_aes_pdc, &g_pdc_rx_packet, NULL);

	/* Disable PDC transfers. */
	pdc_disable_transfer(g_p_aes_pdc,
			PERIPH_PTCR_RXTDIS | PERIPH_PTCR_TXTDIS);

	printf("\r\n-----------------------------------\r\n");
	printf("- 128bit cryptographic key\r\n");
	printf("- ECB cipher mode\r\n");
	printf("- PDC mode\r\n");
	printf("- input of 4 32bit words with PDC\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_ENCRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode =  AES_IDATAR0_START;
	g_aes_cfg.opmode = AES_ECB_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(AES, key128);

	/* Enable AES interrupt. */
	aes_set_callback(AES, AES_INTERRUPT_END_OF_RECEIVE_BUFFER,
			aes_pdc_callback, 1);

	/* The initialization vector is not used by the ECB cipher mode. */

	/* Enable PDC transfers. */
	pdc_enable_transfer(g_p_aes_pdc, PERIPH_PTCR_RXTEN | PERIPH_PTCR_TXTEN);

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
	printf("- PDC mode\r\n");
	printf("- input of 4 32bit words with PDC\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_DECRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_IDATAR0_START;
	g_aes_cfg.opmode = AES_ECB_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(AES, key128);

	/* The initialization vector is not used by the ECB cipher mode. */

	/* Configure PDC for data transfer */
	g_pdc_tx_packet.ul_addr = (uint32_t)ref_cipher_text_ecb;

	/* Configure PDC for data receive & transfer */
	pdc_tx_init(g_p_aes_pdc, &g_pdc_tx_packet, NULL);
	pdc_rx_init(g_p_aes_pdc, &g_pdc_rx_packet, NULL);

	/* Enable PDC transfers. */
	pdc_enable_transfer(g_p_aes_pdc, PERIPH_PTCR_RXTEN | PERIPH_PTCR_TXTEN);

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

#endif

/**
 * \brief ECB mode encryption and decryption test.
 */
static void ecb_mode_test(void)
{
	printf("\r\n-----------------------------------\r\n");
	printf("- 128bit cryptographic key\r\n");
	printf("- ECB cipher mode\r\n");
	printf("- Auto start mode\r\n");
	printf("- input of 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_ENCRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_AUTO_START;
	g_aes_cfg.opmode = AES_ECB_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(AES, key128);

	/* The initialization vector is not used by the ECB cipher mode. */

	/* Write the data to be ciphered to the input data registers. */
	aes_write_input_data(AES, ref_plain_text);

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
	printf("- input of 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_DECRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_AUTO_START;
	g_aes_cfg.opmode = AES_ECB_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(AES, key128);

	/* The initialization vector is not used by the ECB cipher mode. */

	/* Write the data to be deciphered to the input data registers. */
	aes_write_input_data(AES, ref_cipher_text_ecb);

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
	printf("- input of 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_ENCRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_AUTO_START;
	g_aes_cfg.opmode = AES_CBC_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(AES, key128);

	/* Set the initialization vector. */
	aes_write_initvector(AES, init_vector);

	/* Write the data to be ciphered to the input data registers. */
	aes_write_input_data(AES, ref_plain_text);

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
	printf("- input of 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_DECRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_AUTO_START;
	g_aes_cfg.opmode = AES_CBC_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(AES, key128);

	/* Set the initialization vector. */
	aes_write_initvector(AES, init_vector);

	/* Write the data to be deciphered to the input data registers. */
	aes_write_input_data(AES, ref_cipher_text_cbc);

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
	printf("- input of 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_ENCRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_AUTO_START;
	g_aes_cfg.opmode = AES_CFB_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(AES, key128);

	/* Set the initialization vector. */
	aes_write_initvector(AES, init_vector);

	/* Write the data to be ciphered to the input data registers. */
	aes_write_input_data(AES, ref_plain_text);

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
	printf("- input of 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_DECRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_AUTO_START;
	g_aes_cfg.opmode = AES_CFB_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(AES, key128);

	/* Set the initialization vector. */
	aes_write_initvector(AES, init_vector);

	/* Write the data to be deciphered to the input data registers. */
	aes_write_input_data(AES, ref_cipher_text_cfb128);

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
	printf("- input of 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_ENCRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_AUTO_START;
	g_aes_cfg.opmode = AES_OFB_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(AES, key128);

	/* Set the initialization vector. */
	aes_write_initvector(AES, init_vector);

	/* Write the data to be ciphered to the input data registers. */
	aes_write_input_data(AES, ref_plain_text);

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
	printf("- input of 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_DECRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_AUTO_START;
	g_aes_cfg.opmode = AES_OFB_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(AES, key128);

	/* Set the initialization vector. */
	aes_write_initvector(AES, init_vector);

	/* Write the data to be deciphered to the input data registers. */
	aes_write_input_data(AES, ref_cipher_text_ofb);

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
	printf("- input of 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_ENCRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_AUTO_START;
	g_aes_cfg.opmode = AES_CTR_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(AES, key128);

	/* Set the initialization vector. */
	aes_write_initvector(AES, init_vector_ctr);

	/* Write the data to be ciphered to the input data registers. */
	aes_write_input_data(AES, ref_plain_text);

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
	printf("- input of 4 32bit words\r\n");
	printf("-----------------------------------\r\n");

	state = false;

	/* Configure the AES. */
	g_aes_cfg.encrypt_mode = AES_DECRYPTION;
	g_aes_cfg.key_size = AES_KEY_SIZE_128;
	g_aes_cfg.start_mode = AES_AUTO_START;
	g_aes_cfg.opmode = AES_CTR_MODE;
	g_aes_cfg.cfb_size = AES_CFB_SIZE_128;
	g_aes_cfg.lod = false;
	aes_set_config(AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(AES, key128);

	/* Set the initialization vector. */
	aes_write_initvector(AES, init_vector_ctr);

	/* Write the data to be deciphered to the input data registers. */
	aes_write_input_data(AES, ref_cipher_text_ctr);

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
			"  d: ECB mode test with DMA \n\r"
			"  p: ECB mode test with PDC \n\r"
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
	aes_init(AES, &g_aes_cfg);
	aes_enable();

	/* Enable AES interrupt. */
	aes_set_callback(AES, AES_INTERRUPT_DATA_READY,
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
			#if SAM4E
			printf(
					"ECB mode encryption and decryption test with DMA.\r\n");
			ecb_mode_test_dma();
			#else
			printf("This mode is not supported by device.\r\n");
			#endif
			break;

		case 'p':
			#if SAM4C || SAM4CP || SAM4CM
			printf(
					"ECB mode encryption and decryption test with PDC.\r\n");
			ecb_mode_test_pdc();
			#else
			printf("This mode is not supported by device.\r\n");
			#endif
			break;

		default:
			break;
		}
	}
}
