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
 * All SAM devices with an AES module can be used.
 * This example has been tested with the following setup:
 * - sam4e16e_sam4e_ek
 * - sam4c16c_sam4c_ek
 * - sam4cp16b_sam4cp16bmb
 * - same70q21_same70_xplained_pro
 * - samv71q21_samv71_xplained_ultra
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

volatile bool flag = false;

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
 * \brief Test ECB mode encryption and decryption with DMA.
 *
 * \param test Current test case.
 */
static void run_ecb_mode_test_dma(const struct test_case *test)
{
	/* Configure DMAC. */
	configure_dmac();
	/* Disable DMAC channel. */
	dmac_channel_disable(DMAC, AES_DMA_TX_CH);
	dmac_channel_disable(DMAC, AES_DMA_RX_CH);

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
	delay_ms(30);

	/* Disable DMAC channel. */
	dmac_channel_disable(DMAC, AES_DMA_TX_CH);
	dmac_channel_disable(DMAC, AES_DMA_RX_CH);

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
	delay_ms(30);

	/* Disable DMAC channel. */
	dmac_channel_disable(DMAC, AES_DMA_TX_CH);
	dmac_channel_disable(DMAC, AES_DMA_RX_CH);

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
 * \brief ECB mode encryption and decryption test with PDC.
 */
static void run_ecb_mode_test_pdc(const struct test_case *test)
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

	/* Enable PDC transfers. */
	pdc_enable_transfer(g_p_aes_pdc, PERIPH_PTCR_RXTEN | PERIPH_PTCR_TXTEN);

	/* Wait for the end of the decryption process. */
	delay_ms(30);

	pdc_disable_transfer(g_p_aes_pdc,
			PERIPH_PTCR_RXTDIS | PERIPH_PTCR_TXTDIS);
	pdc_tx_init(g_p_aes_pdc, &g_pdc_tx_packet, NULL);
	pdc_rx_init(g_p_aes_pdc, &g_pdc_rx_packet, NULL);


	if ((ref_cipher_text_ecb[0] != output_data[0]) ||
			(ref_cipher_text_ecb[1] != output_data[1]) ||
			(ref_cipher_text_ecb[2] != output_data[2]) ||
			(ref_cipher_text_ecb[3] != output_data[3])) {
		flag = false;
	} else {
		flag = true;
	}

	test_assert_true(test, flag == true,
			"ECB mode with pdc encryption not work!");

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

	/* Configure PDC for data transfer */
	g_pdc_tx_packet.ul_addr = (uint32_t)ref_cipher_text_ecb;

	/* Configure PDC for data receive & transfer */
	pdc_tx_init(g_p_aes_pdc, &g_pdc_tx_packet, NULL);
	pdc_rx_init(g_p_aes_pdc, &g_pdc_rx_packet, NULL);

	/* Enable PDC transfers. */
	pdc_enable_transfer(g_p_aes_pdc, PERIPH_PTCR_RXTEN | PERIPH_PTCR_TXTEN);

	/* Wait for the end of the decryption process. */
	delay_ms(30);

	pdc_tx_init(g_p_aes_pdc, &g_pdc_tx_packet, NULL);
	pdc_rx_init(g_p_aes_pdc, &g_pdc_rx_packet, NULL);
	pdc_disable_transfer(g_p_aes_pdc,
			PERIPH_PTCR_RXTDIS | PERIPH_PTCR_TXTDIS);

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
			"ECB mode with pdc decryption not work!");
}

#endif

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
	aes_set_config(AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(AES, key128);

	/* The initialization vector is not used by the ECB cipher mode. */

	/* Write the data to be ciphered to the input data registers. */
	aes_write_input_data(AES, ref_plain_text);

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

	test_assert_true(test, flag == true,
			"CFB128 mode encryption not work!");

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
	aes_set_config(AES, &g_aes_cfg);

	/* Set the cryptographic key. */
	aes_write_key(AES, key128);

	/* Set the initialization vector. */
	aes_write_initvector(AES, init_vector);

	/* Write the data to be ciphered to the input data registers. */
	aes_write_input_data(AES, ref_plain_text);

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
#ifdef CONF_TEST_CHAR_LENGTH
		.charlength = CONF_TEST_CHAR_LENGTH,
#endif
		.paritytype = CONF_TEST_PARITY,
#ifdef CONF_TEST_STOP_BITS
		.stopbits = CONF_TEST_STOP_BITS,
#endif
	};

	sysclk_init();
	board_init();
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Enable the AES module. */
	aes_get_config_defaults(&g_aes_cfg);
	aes_init(AES, &g_aes_cfg);
	aes_enable();

	/* Enable AES interrupt. */
	aes_set_callback(AES, AES_INTERRUPT_DATA_READY,
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
#if SAM4E
	DEFINE_TEST_CASE(ecb_mode_test_dma, NULL, run_ecb_mode_test_dma, NULL,
			"SAM AES ECB mode encryption and decryption with DMA test.");
#elif SAM4C || SAM4CP || SAM4CM
	DEFINE_TEST_CASE(ecb_mode_test_pdc, NULL, run_ecb_mode_test_pdc, NULL,
			"SAM AES ECB mode encryption and decryption with pdc test.");
#endif

	/* Put test case addresses in an array. */
	DEFINE_TEST_ARRAY(aes_tests) = {
		&ecb_mode_test,
		&cbc_mode_test,
		&cfb128_mode_test,
		&ofb_mode_test,
		&ctr_mode_test,
#if SAM4E
		&ecb_mode_test_dma,
#elif SAM4C || SAM4CP || SAM4CM
		&ecb_mode_test_pdc,
#endif
	};

	/* Define the test suite. */
	DEFINE_TEST_SUITE(aes_suite, aes_tests, "SAM AES driver test suite");

	/* Run all tests in the test suite. */
	test_suite_run(&aes_suite);

	while (1) {
		/* Busy-wait forever. */
	}
}
