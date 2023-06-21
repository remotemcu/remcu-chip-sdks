/**
 * \file
 *
 * \brief Raw flash operation.
 *
 * This file contains definitions and functions for raw NAND Flash operation.
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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

#include <string.h>
#include "nand_flash_raw.h"
#include "conf_board.h"
#include "gpio.h"
#include "smc.h"
#include "pmc.h"
#include "dmac.h"
#include "delay.h"

/* SMC NFC address cycle configuration */
#if CONF_NF_NEED_FIVE_ADDRESS_CYCLES
#define CONF_NF_ADDRESS_CYCLE_CMD  NFCADDR_CMD_ACYCLE_FIVE
#else
#define CONF_NF_ADDRESS_CYCLE_CMD  NFCADDR_CMD_ACYCLE_FOUR
#endif
#ifndef CONF_NF_DMA_CHANNEL
#warning There are no NAND Flash module on the board.
/* define something for pass the jenkins. */
#define CONF_NF_DMA_CHANNEL    0
#endif

#define READ_DATA8(raw) \
		(*((volatile uint8_t *)raw->data_address))
#define READ_DATA16(raw) \
		(*((volatile uint16_t *)raw->data_address))

/* Internal cast macros */
#define MODEL(raw)  ((struct nand_flash_model *)raw)

/**
 * \brief Translate the given column and row address into first and other (1-4)
 * address cycles. The resulting values are stored in the provided variables
 * if they are not null.
 *
 * \param raw  Pointer to a nand_flash_raw instance.
 * \param column_address  Column address to translate.
 * \param row_address  Row address to translate.
 * \param p_address_cycle0  First address cycle.
 * \param p_address_cycle1234 four address cycles.
 * \param five_address Flag for five address cycles.
 */
static void nfc_translate_address(const struct nand_flash_raw *raw,
		uint32_t column_address, uint32_t row_address,
		uint32_t *p_address_cycle0, uint32_t *p_address_cycle1234,
		uint32_t five_address)
{
	uint16_t page_data_size = nand_flash_model_get_page_data_size(MODEL(raw));
	uint32_t num_page =	nand_flash_model_get_device_size_in_pages(MODEL(raw));
	uint32_t address_cycles = 0;
	uint32_t address_cycle0 = 0;
	uint32_t address_cycle1234 = 0;

	/* Check the data bus width of the NAND Flash */
	if (nand_flash_model_get_data_bus_width(MODEL(raw)) == 16) {
		/* Div 2 is because we address in word and not in byte */
		column_address >>= 1;
	}

	/* When 5 address cycle are used. */
	if (five_address) {
		while (page_data_size > 0) {
			if (address_cycles == 0) {
				address_cycle0 = (column_address & 0xFF);
			} else {
				address_cycle1234 |= ((column_address & 0xFF) <<
						((address_cycles - 1) * 8));
			}

			page_data_size >>= 8;
			column_address >>= 8;
			address_cycles++;
		}
		while (num_page > 0) {
			if (address_cycles == 0) {
				address_cycle0 = (row_address & 0xFF);
			} else {
				address_cycle1234 |= ((row_address & 0xFF) <<
						((address_cycles - 1) * 8));
			}

			num_page >>= 8;
			row_address >>= 8;
			address_cycles++;
		}
	}
	/* When less than 5 address cycle are used. */
	else {
		while (num_page > 0) {
			address_cycle1234 |= ((row_address & 0xFF) <<
					((address_cycles) * 8));
			num_page >>= 8;
			row_address >>= 8;
			address_cycles++;
		}
	}

	/* Store values */
	if (p_address_cycle0) {
		*p_address_cycle0 = address_cycle0;
	}

	if (p_address_cycle1234) {
		*p_address_cycle1234 = address_cycle1234;
	}

	return;
}

/**
 * \brief Check if program or erase operation is completed in current operation.
 *
 * \param raw  Pointer to a nand_flash_raw instance.
 */
static uint32_t check_status(const struct nand_flash_raw *raw)
{
	uint32_t status;

	smc_nfc_send_command(SMC,
			NFCADDR_CMD_NFCCMD          | /* Command. */
			NFCADDR_CMD_NFC_READ        | /* NFC read data. */
			0                           | /* NFC auto R/W is disabled. */
			NFCADDR_CMD_CSID(BOARD_NAND_CS)          | /* CSID. */
			NFCADDR_CMD_ACYCLE_NONE     | /* No address cycle. */
			(NAND_COMMAND_STATUS << 2),   /* CMD1 (COMMAND_STATUS). */
			0,                            /* Dummy address cycle 1,2,3,4. */
			0                             /* Dummy address cycle 0. */
			);
	status = READ_DATA8(raw);
	if (((status & NAND_STATUS_READY) != NAND_STATUS_READY) ||
			((status & NAND_STATUS_ERROR) != 0)) {
		return 0;
	}
	return 1;
}

/**
 * \brief Send data to the NFC sram from the provided buffer.
 *
 * \param data  Pointer to where the data stored.
 * \param sram_offset  NFC internal sram start offset.
 * \param size   Number of data bytes to send.
 */
static void nfc_copy_data_to_internal_sram(uint8_t *data,
		uint32_t sram_offset, uint16_t size)
{
#ifdef CONF_NF_USE_DMA
	dma_transfer_descriptor_t desc;

	/* Initialize single buffer transfer */
	desc.ul_source_addr = (uint32_t)data;
	desc.ul_destination_addr = (uint32_t)(NFC_RAM_ADDR + sram_offset);
	desc.ul_ctrlA = 
			DMAC_CTRLA_BTSIZE(size >> 2) | /* Set Buffer Transfer Size */
			DMAC_CTRLA_SRC_WIDTH_WORD    | /* Source transfer size is set to 32-bit width */
			DMAC_CTRLA_DST_WIDTH_WORD;     /* Destination transfer size is set to 32-bit width */
	desc.ul_ctrlB = 
			DMAC_CTRLB_SRC_DSCR_FETCH_DISABLE | /* Buffer Descriptor Fetch operation is disabled for the source */
			DMAC_CTRLB_DST_DSCR_FETCH_DISABLE | /* Buffer Descriptor Fetch operation is disabled for the destination */
			DMAC_CTRLB_FC_MEM2MEM_DMA_FC      | /* Memory-to-Memory Transfer */
			DMAC_CTRLB_SRC_INCR_INCREMENTING  | /* The source address is incremented */
			DMAC_CTRLB_DST_INCR_INCREMENTING;   /* The destination address is incremented */
	desc.ul_descriptor_addr = NULL; /* No descriptor for single transfer */
	dmac_channel_single_buf_transfer_init(DMAC, CONF_NF_DMA_CHANNEL, &desc);

	/* Start DMA transfer and wait for finish */
	dmac_channel_enable(DMAC, CONF_NF_DMA_CHANNEL);
	while (!dmac_channel_is_transfer_done(DMAC, CONF_NF_DMA_CHANNEL)) {
	}	
#else
	uint8_t *p_buffer;
	uint32_t i;
	p_buffer = (uint8_t *) (NFC_RAM_ADDR + sram_offset);
	for (i = 0; i < size; i++) {
		*p_buffer = *data;
		p_buffer++;
		data++;
	}
#endif
}

/**
 * \brief Copy data from the NFC sram to the provided buffer.
 *
 * \param data  Buffer where the data area will be stored.
 * \param sram_offset  NFC internal sram start offset.
 * \param size Number of data bytes to receive.
 */
static void nfc_copy_data_from_internal_sram(uint8_t *data,
		uint32_t sram_offset, uint16_t size)
{
#ifdef CONF_NF_USE_DMA
	dma_transfer_descriptor_t desc;

	/* Initialize single buffer transfer */
	desc.ul_source_addr = (uint32_t)(NFC_RAM_ADDR + sram_offset);
	desc.ul_destination_addr = (uint32_t)data;
	desc.ul_ctrlA = 
			DMAC_CTRLA_BTSIZE(size >> 2) | /* Set Buffer Transfer Size */
			DMAC_CTRLA_SRC_WIDTH_WORD    | /* Source transfer size is set to 32-bit width */
			DMAC_CTRLA_DST_WIDTH_WORD;     /* Destination transfer size is set to 32-bit width */
	desc.ul_ctrlB = 
			DMAC_CTRLB_SRC_DSCR_FETCH_DISABLE | /* Buffer Descriptor Fetch operation is disabled for the source */
			DMAC_CTRLB_DST_DSCR_FETCH_DISABLE | /* Buffer Descriptor Fetch operation is disabled for the destination */
			DMAC_CTRLB_FC_MEM2MEM_DMA_FC      | /* Memory-to-Memory Transfer */
			DMAC_CTRLB_SRC_INCR_INCREMENTING  | /* The source address is incremented */
			DMAC_CTRLB_DST_INCR_INCREMENTING;   /* The destination address is incremented */
	desc.ul_descriptor_addr = NULL; /* No descriptor for single transfer */
	dmac_channel_single_buf_transfer_init(DMAC, CONF_NF_DMA_CHANNEL, &desc);

	/* Start DMA transfer and wait for finish */
	dmac_channel_enable(DMAC, CONF_NF_DMA_CHANNEL);
	while (!dmac_channel_is_transfer_done(DMAC, CONF_NF_DMA_CHANNEL)) {
	}
#else
	uint8_t *p_buffer;
	uint32_t i;
	p_buffer = (uint8_t *)(NFC_RAM_ADDR + sram_offset);
	for (i = 0; i < size; i++) {
		*data = *p_buffer;
		data++;
		p_buffer++;
	}
#endif
}

/**
 * \brief Erase the specified block of the NAND Flash chip.
 *
 * \param raw  Pointer to a nand_flash_raw instance.
 * \param block  Number of the physical block to erase.
 *
 * \return 0 if successful; otherwise return the error code.
 */
static uint32_t erase_block(const struct nand_flash_raw *raw, uint16_t block)
{
	uint32_t error = 0;
	uint32_t row_address;
	uint32_t address_cycle1234;

	/* Calculate address used for erase */
	row_address = block *
			nand_flash_model_get_block_size_in_pages(MODEL(raw));

	nfc_translate_address(raw, 0, row_address, 0, &address_cycle1234,
			0);

	/* Start erase */
	smc_nfc_send_command(SMC, 
			NFCADDR_CMD_NFCCMD           | /* Command. */
			NFCADDR_CMD_NFC_READ         | /* NFC read data. */
			0                            | /* NFC auto R/W is disabled. */
			NFCADDR_CMD_CSID(BOARD_NAND_CS)           | /* CSID. */
			NFCADDR_CMD_ACYCLE_THREE     | /* Number of address cycle. */
			NFCADDR_CMD_VCMD2            | /* CMD2 enabled. */
			(NAND_COMMAND_ERASE_2 << 10) | /* CMD2 (ERASE CONFIRME). */
			(NAND_COMMAND_ERASE_1 << 2),   /* CMD1 (ERASE). */
			address_cycle1234,             /* Address cycle 1, 2, 3, 4. */
			0                              /* Dummy address cycle 0. */
			);

	/* make sure for erase ready */
	delay_ms(3);

	while (!(smc_nfc_get_status(SMC) & SMC_SR_RB_EDGE0)) {
	}

	if (!check_status(raw)) {
		error = NAND_COMMON_ERROR_CANNOTERASE;
	}

	return error;
}

/**
 * \brief Write the data and/or the spare area of a page on a NAND Flash chip.
 *
 * \param raw  Pointer to a nand_flash_raw instance.
 * \param block  Number of the physical block to erase.
 * \param page  Number of the page to write inside the given block.
 * \param data  Buffer containing the data area.
 * \param spare  Buffer containing the spare area.
 *
 * \return 0 if successful; otherwise return the error code.
 *
 * \note If one of the buffer pointer is 0, the corresponding area is not
 * written.
 */
static uint32_t write_page(const struct nand_flash_raw *raw,
		uint16_t block, uint16_t page, void *data, void *spare)
{
	uint32_t error = 0;
	uint32_t page_data_size =
			nand_flash_model_get_page_data_size(MODEL(raw));
	uint32_t page_spare_size =
			nand_flash_model_get_page_spare_size(MODEL(raw));
	uint32_t row_address;
	uint32_t address_cycle0;
	uint32_t address_cycle1234;

	/* Calculate physical address of the page */
	row_address = block *
			nand_flash_model_get_block_size_in_pages(MODEL(raw)) + page;

	/**
	 * Note: special case when ECC parity generation.
	 * ECC results are available as soon as the counter reaches the end of
	 * the main area. But when reach page_size for an example, it could not
	 * generate last ECC_PR, The workaround enable SPARE_WRITE, whatever
	 * real spare area write or not.
	 */
	smc_nfc_enable_spare_write(SMC);

	/* Write data area if needed */
	if (data) {
		nfc_copy_data_to_internal_sram((uint8_t *)data, 0,
				page_data_size);
		if (spare) {
			nfc_copy_data_to_internal_sram((uint8_t *)spare,
					page_data_size, page_spare_size);
		}
		nfc_translate_address(raw, 0, row_address, &address_cycle0,
				&address_cycle1234, CONF_NF_NEED_FIVE_ADDRESS_CYCLES);
	}
	if (spare && !data) {
		nfc_copy_data_to_internal_sram((uint8_t *)spare, 0,
				page_spare_size);
		nfc_translate_address(raw, page_data_size, row_address,	&address_cycle0,
				&address_cycle1234, CONF_NF_NEED_FIVE_ADDRESS_CYCLES);
	}

	if (data || spare) {
		/* Start write operation */
		smc_nfc_send_command(SMC, 
				NFCADDR_CMD_NFCCMD         | /* Command. */
				NFCADDR_CMD_NFC_WIRTE      | /* NFC write data. */
				NFCADDR_CMD_NFCEN          | /* NFC auto R/W is enabled. */
				NFCADDR_CMD_CSID(BOARD_NAND_CS)         | /* CSID. */
				CONF_NF_ADDRESS_CYCLE_CMD  | /* Number of address cycle. */
				0                          | /* CMD2 disabled. */
				0                          | /* CMD2. */
				(NAND_COMMAND_WRITE_1 << 2), /* CMD1. */
				address_cycle1234,           /* Address cycle 1, 2, 3, 4. */
				address_cycle0               /* Address cycle 0. */
				);
		while (!(smc_nfc_get_status(SMC) & SMC_SR_XFRDONE)) {
		}

		smc_nfc_send_command(SMC, 
				NFCADDR_CMD_NFCCMD         | /* Command. */
				NFCADDR_CMD_NFC_READ       | /* No data Transfer. */
				0                          | /* NFC auto R/W is disabled. */
				NFCADDR_CMD_CSID(BOARD_NAND_CS)         | /* CSID. */
				NFCADDR_CMD_ACYCLE_NONE    | /* No address cycle. */
				0                          | /* CMD2 disabled. */
				0                          | /* CMD2. */
				(NAND_COMMAND_WRITE_2 << 2), /* CMD1. */
				0,                           /* Dummy address cycle 1, 2, 3, 4. */
				0                            /* Dummy address cycle 0. */
				);
		while (!(smc_nfc_get_status(SMC) & SMC_SR_RB_EDGE0));
		if (!check_status(raw)) {
			error = NAND_COMMON_ERROR_CANNOTWRITE;
		}
	}
	smc_nfc_disable_spare_write(SMC);
	return error;
}


/**
 * \brief Copy the data in a page of the NAND Flash device to an other page on
 * that same chip.
 *
 * \param raw  Pointer to a nand_flash_raw instance.
 * \param source_block  Source block number.
 * \param source_page  Source page number inside the source block.
 * \param dest_block  Destination block number.
 * \param dest_page  Destination page number inside the destination block.
 *
 * \return 0 if successful; otherwise return the error code.
 */
static uint32_t copy_page(const struct nand_flash_raw *raw,
		uint16_t source_block, uint16_t source_page,
		uint16_t dest_block, uint16_t dest_page)
{
	uint16_t num_page =
			nand_flash_model_get_block_size_in_pages(MODEL(raw));
	uint32_t source_row_address = source_block * num_page + source_page;
	uint32_t dest_row_address = dest_block * num_page + dest_page;
	uint32_t error = 0;
	uint32_t address_cycle0;
	uint32_t address_cycle1234;

	/* Use the copy-back facility if available */
	if (nand_flash_model_copy_back(MODEL(raw))) {
		/* Start operation */
		nfc_translate_address(raw, 0, source_row_address, &address_cycle0,
				&address_cycle1234, CONF_NF_NEED_FIVE_ADDRESS_CYCLES);
		/* Start copy-back read */
		smc_nfc_send_command(SMC, 
				NFCADDR_CMD_NFCCMD                   | /* Command. */
				NFCADDR_CMD_NFC_READ                 | /* NFC read data. */
				0                                    | /* NFC auto R/W is disabled. */
				NFCADDR_CMD_CSID(BOARD_NAND_CS)                   | /* CSID. */
				CONF_NF_ADDRESS_CYCLE_CMD            | /* Number of address cycle. */
				NFCADDR_CMD_VCMD2                    | /* CMD2 enabled. */
				(NAND_COMMAND_COPYBACK_READ_2 << 10) | /* CMD2. */
				(NAND_COMMAND_COPYBACK_READ_1 << 2),   /* CMD1. */
				address_cycle1234,                     /* Address cycle 1, 2, 3, 4. */
				address_cycle0                         /* Address cycle 0. */
				);
		while (!(smc_nfc_get_status(SMC) & SMC_SR_RB_EDGE0)) {
		}

		/* Start copy-back write */
		nfc_translate_address(raw, 0, dest_row_address, &address_cycle0,
				&address_cycle1234, CONF_NF_NEED_FIVE_ADDRESS_CYCLES);
		smc_nfc_send_command(SMC, 
				NFCADDR_CMD_NFCCMD                      | /* Command. */
				NFCADDR_CMD_NFC_READ                    | /* No data transfer. */
				0                                       | /* NFC auto R/W is disabled. */
				NFCADDR_CMD_CSID(BOARD_NAND_CS)                      | /* CSID. */
				CONF_NF_ADDRESS_CYCLE_CMD               | /* Number of address cycle. */
				NFCADDR_CMD_VCMD2                       | /* CMD2 enabled. */
				(NAND_COMMAND_COPYBACK_PROGRAM_2 << 10) | /* CMD2. */
				(NAND_COMMAND_COPYBACK_PROGRAM_1 << 2),   /* CMD1. */
				address_cycle1234,                        /* Address cycle 1, 2, 3, 4. */
				address_cycle0                            /* Address cycle 0. */
				);
		while (!(smc_nfc_get_status(SMC) & SMC_SR_RB_EDGE0)) {
		}

		/* Check status */
		if (!check_status(raw)) {
			error = NAND_COMMON_ERROR_CANNOTCOPY;
		}
	} else {
		/* Software copy */
		uint8_t data[NAND_COMMON_MAX_PAGE_SIZE];
		uint8_t spare[NAND_COMMON_MAX_PAGE_SPARE_SIZE];
		nand_flash_raw_read_page(raw, source_block, source_page,
				data, spare);
		if (nand_flash_raw_write_page(raw, dest_block, dest_page,
				data, spare)) {
			error = NAND_COMMON_ERROR_CANNOTWRITE;
		}
	}

	return error;
}


/**
 * \brief Initialize a nand_flash_raw instance based on the given model and
 * physical interface.
 *
 * \param raw  Pointer to a nand_flash_raw instance.
 * \param model  Pointer to the underlying nand chip model. Can be 0.
 * \param command_address  Address at which commands are sent.
 * \param address_address  Address at which addresses are sent.
 * \param data_address  Address at which data is sent.
 *
 * \return 0 if successful; otherwise returns NAND_COMMON_ERROR_UNKNOWNMODEL.
 */
uint32_t nand_flash_raw_initialize(struct nand_flash_raw *raw,
		const struct nand_flash_model *model, uint32_t command_address,
		uint32_t address_address, uint32_t data_address)
{
	uint32_t page_size_cfg;

#ifdef CONF_NF_USE_DMA
	uint32_t cfg;

	/* Initialize and enable DMA controller */
	pmc_enable_periph_clk(ID_DMAC);
	dmac_init(DMAC);
	dmac_set_priority_mode(DMAC, DMAC_PRIORITY_ROUND_ROBIN);
	dmac_enable(DMAC);

	/* Set for channel configuration register */
	cfg = DMAC_CFG_SOD_ENABLE        | /* Enable stop on done */
			DMAC_CFG_AHB_PROT(1)     | /* Set AHB Protection */
			DMAC_CFG_FIFOCFG_ALAP_CFG; /* FIFO Configuration */
	dmac_channel_set_configuration(DMAC, CONF_NF_DMA_CHANNEL, cfg);
#endif

	/* Configure SMC for NAND Flash accesses */
	pmc_enable_periph_clk(ID_SMC);

	/* Configure SMC interface for NAND Flash */
	smc_set_setup_timing(SMC, BOARD_NAND_CS, CONF_NF_SETUP_TIMING);
	smc_set_pulse_timing(SMC, BOARD_NAND_CS, CONF_NF_PULSE_TIMING);
	smc_set_cycle_timing(SMC, BOARD_NAND_CS, CONF_NF_CYCLE_TIMING);
	smc_set_nand_timing(SMC, BOARD_NAND_CS, CONF_NF_TIMING);
	if (CONF_NF_BUSWIDTH == 8) {
		smc_set_mode(SMC, BOARD_NAND_CS, SMC_MODE_READ_MODE
				| SMC_MODE_WRITE_MODE | SMC_MODE_DBW_BIT_8);
	}

	if (CONF_NF_BUSWIDTH == 16) {
		smc_set_mode(SMC, BOARD_NAND_CS, SMC_MODE_READ_MODE
				| SMC_MODE_WRITE_MODE | SMC_MODE_DBW_BIT_16);
	}

	/* Initialize NFC controller */
	smc_nfc_enable(SMC);

	/* Initialize fields */
	raw->command_address = command_address;
	raw->address_address = address_address;
	raw->data_address = data_address;

	/* Reset */
	nand_flash_raw_reset(raw);

	/* make sure for reset ready */
	delay_ms(1);

	/* If model is not provided, autodetect it */
	if (!model) {
		if (nand_flash_model_find(nand_flash_model_list,
				NAND_FLASH_MODEL_LIST_SIZE,
				nand_flash_raw_read_id(raw), &(raw->model))) {
			return NAND_COMMON_ERROR_UNKNOWNMODEL;
		}
	} else {
		/* Copy provided model */
		raw->model = *model;
	}

	switch (model->page_size_in_bytes) {
	case 512:
		page_size_cfg = SMC_CFG_PAGESIZE_PS512_16;
		break;

	case 1024:
		page_size_cfg = SMC_CFG_PAGESIZE_PS1024_32;
		break;

	case 2048:
		page_size_cfg = SMC_CFG_PAGESIZE_PS2048_64;
		break;

	case 4096:
		page_size_cfg = SMC_CFG_PAGESIZE_PS4096_128;
		break;

	default:
		page_size_cfg = SMC_CFG_PAGESIZE_PS2048_64;
		break;
	}

	smc_nfc_init(SMC, page_size_cfg | SMC_CFG_DTOMUL_X1048576 | 
			SMC_CFG_EDGECTRL | SMC_CFG_DTOCYC(0xF) | SMC_CFG_RSPARE);

	return 0;
}

/**
 * \brief Reset a NAND Flash device.
 *
 * \param raw  Pointer to a nand_flash_raw instance.
 */
void nand_flash_raw_reset(const struct nand_flash_raw *raw)
{
	/* avoid Cppcheck Warning */
	UNUSED(raw);

	smc_nfc_send_command(SMC, 
			NFCADDR_CMD_NFCCMD       | /* Command. */
			NFCADDR_CMD_NFC_READ     | /* NFC read data. */
			0                        | /* NFC auto R/W is disabled. */
			NFCADDR_CMD_CSID(BOARD_NAND_CS)       | /* CSID. */
			NFCADDR_CMD_ACYCLE_NONE  | /* No address Cycle. */
			(NAND_COMMAND_RESET << 2), /* CMD1 (COMMAND_RESET). */
			0,                         /* Dummy address cycle 1,2,3,4. */
			0                          /* Dummy address cycle 0. */
			);
	while (!(smc_nfc_get_status(SMC) & SMC_SR_RB_EDGE0)) {
	}
}

/**
 * \brief Reads and returns the identifiers of a NAND Flash chip.
 *
 * \param raw  Pointer to a nand_flash_raw instance.
 *
 * \return id1|(id2<<8)|(id3<<16)|(id4<<24)
 */
uint32_t nand_flash_raw_read_id(const struct nand_flash_raw *raw)
{
	uint32_t chip_id;

	smc_nfc_send_command(SMC, 
			NFCADDR_CMD_NFCCMD        | /* Command. */
			NFCADDR_CMD_NFC_READ      | /* NFC read Data. */
			0                         | /* NFC auto R/W is disabled. */
			NFCADDR_CMD_CSID(BOARD_NAND_CS)        | /* CSID. */
			NFCADDR_CMD_ACYCLE_ONE    | /* One address Cycle. */
			(NAND_COMMAND_READID << 2), /* CMD1 (COMMAND_READID). */
			0,                          /* Dummy address cycle 1,2,3,4. */
			0                           /* Dummy address cycle 0. */
			);

	/* make sure ready */
	delay_us(1);

	chip_id = READ_DATA8(raw);
	chip_id |= (READ_DATA8(raw) << 8);
	chip_id |= (READ_DATA8(raw) << 16);
	chip_id |= (READ_DATA8(raw) << 24);
	return chip_id;
}

/**
 * \brief Erase the specified block of the device, retrying several time if
 * it fails.
 *
 * \param raw  Pointer to a nand_flash_raw instance.
 * \param block  Number of the physical block to erase.
 *
 * \return 0 if successful; otherwise returns NAND_COMMON_ERROR_BADBLOCK.
 */
uint32_t nand_flash_raw_erase_block(const struct nand_flash_raw *raw,
		uint16_t block)
{
	uint32_t num_try = CONF_NF_ERASE_NUM_TRY;

	while (num_try > 0) {
		if (!erase_block(raw, block)) {
			return 0;
		}
		num_try--;
	}

	return NAND_COMMON_ERROR_BADBLOCK;
}

/**
 * \brief Read the data and/or the spare areas of a page of a NAND Flash into
 * the  provided buffers.
 *
 * \param raw  Pointer to a nand_flash_raw instance.
 * \param block  Number of the physical block to read.
 * \param page  Number of the page to read inside the given block.
 * \param data  Buffer where the data area will be read.
 * \param spare  Buffer where the spare area will be read.
 *
 * \note If one of the buffer pointer is 0, the corresponding area is not read.
 */
void nand_flash_raw_read_page(const struct nand_flash_raw *raw,
		uint16_t block, uint16_t page, uint8_t *data, uint8_t *spare)
{
	volatile uint32_t num_try = 0;

	uint32_t small_block = nand_flash_model_small_block(MODEL(raw));
	uint32_t page_data_size =
			nand_flash_model_get_page_data_size(MODEL(raw));
	uint32_t page_spare_size =
			nand_flash_model_get_page_spare_size(MODEL(raw));
	uint32_t col_address;
	uint32_t row_address;
	uint32_t address_cycle0;
	uint32_t address_cycle1234;

	/* Calculate actual address of the page */
	row_address = block *
			nand_flash_model_get_block_size_in_pages(MODEL(raw)) + page;
	/* Start operation */
	if (data) {
		col_address = 0;
	} else {
		/* to read spare area in sequential access */
		col_address = page_data_size;
	}

	if (spare) {
		smc_nfc_enable_spare_read(SMC);
	} else {
		smc_nfc_disable_spare_read(SMC);
	}
	nfc_translate_address(raw, col_address, row_address, &address_cycle0,
			&address_cycle1234, CONF_NF_NEED_FIVE_ADDRESS_CYCLES);
	/* Use either small blocks or large blocks data area read */
	if (small_block) {
		smc_nfc_send_command(SMC, 
				NFCADDR_CMD_NFCCMD        | /* Command. */
				NFCADDR_CMD_NFC_READ      | /* NFC read data. */
				NFCADDR_CMD_NFCEN         | /* NFC auto R/W is enable. */
				NFCADDR_CMD_CSID(BOARD_NAND_CS)        | /* CSID. */
				CONF_NF_ADDRESS_CYCLE_CMD | /* Number of address cycle. */
				0                         | /* CMD2 disabled. */
				0                         | /* CMD2. */
				(NAND_COMMAND_READ_A << 2), /* CMD1. */
				address_cycle1234,          /* Address cycle 1, 2, 3, 4. */
				address_cycle0              /* Address cycle 0. */
				);
	} else {
		smc_nfc_send_command(SMC, 
				NFCADDR_CMD_NFCCMD          | /* Command. */
				NFCADDR_CMD_NFC_READ        | /* NFC read data. */
				NFCADDR_CMD_NFCEN           | /* NFC auto R/W is enabled. */
				NFCADDR_CMD_CSID(BOARD_NAND_CS)          | /* CSID. */
				CONF_NF_ADDRESS_CYCLE_CMD   | /* Number of address cycle. */
				NFCADDR_CMD_VCMD2           | /* CMD2 enabled. */
				(NAND_COMMAND_READ_2 << 10) | /* CMD2. */
				(NAND_COMMAND_READ_1 << 2),   /* CMD1. */
				address_cycle1234,            /* Address cycle 1, 2, 3, 4. */
				address_cycle0                /* Address cycle 0. */
				);
	}
	/* Wait for the nand to be ready */
	num_try = 0;
	while ((!(smc_nfc_get_status(SMC) & SMC_SR_RB_EDGE0)) &&
			((num_try++) < 1000000)) {
	}
	num_try = 0;
	while ((!(smc_nfc_get_status(SMC) & SMC_SR_XFRDONE)) &&
			((num_try++) < 1000000)) {
	}
	/* Read data area if needed */
	if (data) {
		nfc_copy_data_from_internal_sram(data, 0, page_data_size);
		if (spare) {
			nfc_copy_data_from_internal_sram(spare,
					page_data_size, page_spare_size);
		}
	} else {
		/* Read spare area only */
		nfc_copy_data_from_internal_sram(spare, 0, page_spare_size);
	}

}

/**
 * \brief Write the data and/or the spare areas of a page of a NAND Flash into
 * the  provided buffers.
 *
 * \param raw  Pointer to a nand_flash_raw instance.
 * \param block  Number of the physical block to write resides.
 * \param page Number of the page to write inside the given block.
 * \param data  Buffer where the data area will be stored.
 * \param spare  Buffer where the spare area will be stored.
 *
 * \return 0 if successful; otherwise returns NAND_COMMON_ERROR_BADBLOCK.
 *
 * \note If one of the buffer pointer is 0, the corresponding area is not
 * written.
 */
uint32_t nand_flash_raw_write_page(const struct nand_flash_raw *raw,
		uint16_t block, uint16_t page, uint8_t *data, uint8_t *spare)
{
	uint32_t num_try = CONF_NF_WRITE_NUM_TRY;

	while (num_try > 0) {
		if (!write_page(raw, block, page, data, spare)) {
			return 0;
		}
		num_try--;
	}

	return NAND_COMMON_ERROR_BADBLOCK;
}

/**
 * \brief Copy the data in a page of the NAND Flash device to an other page on
 * that same chip.
 *
 * \param raw  Pointer to a nand_flash_raw instance.
 * \param source_block  Source block number.
 * \param source_page  Source page number inside the source block.
 * \param dest_block  Destination block number.
 * \param dest_page  Destination page number inside the destination block.
 *
 * \return 0 if successful; otherwise returns an NAND_COMMON_ERROR_BADBLOCK.
 *
 * \note Reference the Flash datasheet for the block and page address
 * restriction.
 */
uint32_t nand_flash_raw_copy_page(const struct nand_flash_raw *raw,
		uint16_t source_block, uint16_t source_page,
		uint16_t dest_block, uint16_t dest_page)
{
	uint32_t num_try = CONF_NF_COPY_NUM_TRY;

	while (num_try) {
		if (!copy_page(raw, source_block, source_page, dest_block,
				dest_page)) {
			return 0;
		}
		num_try--;
	}

	return NAND_COMMON_ERROR_BADBLOCK;
}

/**
 * \brief Copy the data of one whole block of a NAND Flash device to another
 * block.
 *
 * \param raw  Pointer to a nand_flash_raw instance.
 * \param source_block  Source block number.
 * \param dest_block  Destination block number.
 *
 * \return 0 if successful; otherwise returns an NAND_COMMON_ERROR_BADBLOCK.
 *
 * \note Reference the Flash datasheet for the block address restriction.
 */
uint32_t nand_flash_raw_copy_block(const struct nand_flash_raw *raw,
		uint16_t source_block, uint16_t dest_block)
{
	uint16_t num_page =
			nand_flash_model_get_block_size_in_pages(MODEL(raw));
	uint32_t i;

	/* Check: Source block must be different from dest block */
	Assert(source_block != dest_block);

	/* Copy all pages */
	for (i = 0; i < num_page; i++) {
		if (nand_flash_raw_copy_page(raw, source_block, i, dest_block, i)) {
			return NAND_COMMON_ERROR_BADBLOCK;
		}
	}
	return 0;
}
