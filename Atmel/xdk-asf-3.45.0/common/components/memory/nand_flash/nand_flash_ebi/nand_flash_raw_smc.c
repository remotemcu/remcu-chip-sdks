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

#include "nand_flash_raw.h"
#include "conf_board.h"
#include "conf_nf.h"
#include "gpio.h"
#include "smc.h"
#if SAM
#include "matrix.h"
#include "pmc.h"
#else
#include "sysclk.h"
#include "conf_ebi.h"
#endif
#include "delay.h"
#if (SAM4E)
#include <ioport.h>
#endif

#ifndef PIN_NF_CE_IDX
#warning There are no NAND Flash module on the board.
/* define something for pass the jenkins. */
#define PIN_NF_CE_IDX    0
#define PIN_NF_RB_IDX    0
#define NF_WP_PIN        0
#define BOARD_NAND_CS    0
#define CONF_NF_BUSWIDTH     0
#define CONF_NF_SETUP_TIMING 0
#define CONF_NF_PULSE_TIMING 0
#define CONF_NF_CYCLE_TIMING 0
#endif

#if SAM4S || SAM4E /* For compatible */
#define SMC_MODE_DBW_8_BIT  0
#endif

#define ENABLE_CE(raw)        gpio_set_pin_low(PIN_NF_CE_IDX)
#define DISABLE_CE(raw)       gpio_set_pin_high(PIN_NF_CE_IDX)

#define WRITE_COMMAND(raw, command) \
		{*((volatile uint8_t *)raw->command_address) = (uint8_t)command;}
#define WRITE_COMMAND16(raw, command) \
		{*((volatile uint16_t *)raw->command_address) = (uint16_t)command;}
#define WRITE_ADDRESS(raw, address) \
		{*((volatile uint8_t *)raw->address_address) = (uint8_t)address;}
#define WRITE_ADDRESS16(raw, address) \
		{*((volatile uint16_t *)raw->address_address) = (uint16_t)address;}
#define WRITE_DATA8(raw, data) \
		{*((volatile uint8_t *)raw->data_address) = (uint8_t)data;}
#define READ_DATA8(raw) \
		(*((volatile uint8_t *)raw->data_address))
#define WRITE_DATA16(raw, data) \
		{*((volatile uint16_t *)raw->data_address) = (uint16_t)data;}
#define READ_DATA16(raw) \
		(*((volatile uint16_t *)raw->data_address))

/* Internal cast macros */
#define MODEL(raw)  ((struct nand_flash_model *)raw)

/**
 * \brief Send the column address to the NAND Flash chip.
 *
 * \param raw  Pointer to a nand_flash_raw instance.
 * \param column_address  Column address to send.
 */
static void write_column_address(const struct nand_flash_raw *raw,
		uint16_t column_address)
{
	uint16_t page_data_size =
			nand_flash_model_get_page_data_size(MODEL(raw));

	/* Check the data bus width of the NAND Flash */
	if (nand_flash_model_get_data_bus_width(MODEL(raw)) == 16) {
		/* Div 2 is because we address in word and not in byte */
		column_address >>= 1;
	}
	/*
	 * Send single column address byte for small block devices,
	 * or two column address bytes for large block devices.
	 */
	while (page_data_size > 2) {
		if (nand_flash_model_get_data_bus_width(MODEL(raw)) == 16) {
			WRITE_ADDRESS16(raw, (column_address & 0xFF));
		} else {
			WRITE_ADDRESS(raw, (column_address & 0xFF));
		}

		page_data_size >>= 8;
		column_address >>= 8;
	}
}

/**
 * \brief Send the row address to the NAND Flash chip.
 *
 * \param raw  Pointer to a nand_flash_raw instance.
 * \param row_address  Row address to send.
 */
static void write_row_address(const struct nand_flash_raw *raw,
		uint32_t row_address)
{
	uint32_t num_page =
			nand_flash_model_get_device_size_in_pages(MODEL(raw));

	while (num_page > 0) {
		if (nand_flash_model_get_data_bus_width(MODEL(raw)) == 16) {
			WRITE_ADDRESS16(raw, (row_address & 0xFF));
		} else {
			WRITE_ADDRESS(raw, (row_address & 0xFF));
		}

		num_page >>= 8;
		row_address >>= 8;
	}
}

/**
 * \brief Check for program or erase operation is completed.
 *
 * \param raw  Pointer to a nand_flash_raw instance.
 * \return 1 operation is completed; otherwise, return 0.
 */
static uint32_t check_status(const struct nand_flash_raw *raw)
{
	uint32_t status;

	WRITE_COMMAND(raw, NAND_COMMAND_STATUS);

	status = READ_DATA8(raw);

	if (((status & NAND_STATUS_READY) != NAND_STATUS_READY) ||
			((status & NAND_STATUS_ERROR) != 0)) {
		return 0;
	}
	return 1;
}

/**
 * \brief Wait for the completion of a page program, erase and random read completion.
 */
static void wait_ready(void)
{
	while (gpio_pin_is_low(PIN_NF_RB_IDX)) {
	}
}

/**
 * \brief Send data to the NAND Flash chip from the provided buffer.
 *
 * \param raw  Pointer to a nand_flash_raw instance.
 * \param buffer  Pointer to data buffer.
 * \param size  Number of bytes that will be written.
 */
static void write_data(const struct nand_flash_raw *raw,
		uint8_t *buffer, uint32_t size)
{
	uint32_t i;

	/* Check the data bus width of the NAND Flash */
	if (nand_flash_model_get_data_bus_width(MODEL(raw)) == 16) {
		/* Not aligned, get data by byte */
		if (((uint32_t)buffer & 0x1u) || (size & 0x1u)) {
			uint16_t tmp16;
			for (i = 0; i < size;) {
				tmp16 = buffer[i++];
				if (i < size) {
					tmp16 += buffer[i++] << 8;
				} else {
					tmp16 += 0xFF00; // Write FF if no data
				}
				WRITE_DATA16(raw, tmp16);
			}
		} else {
			uint16_t *buffer16 = (uint16_t *)(uint32_t)buffer;
			size >>= 1;
			for (i = 0; i < size; i++) {
				WRITE_DATA16(raw, buffer16[i]);
			}
		}
	} else {
		for (i = 0; i < size; i++) {
			WRITE_DATA8(raw, buffer[i]);
		}
	}
}

/**
 * \brief Read data from the NAND Flash chip into the provided buffer.
 *
 * \param raw  Pointer to a nand_flash_raw instance.
 * \param buffer  Pointer to data buffer.
 * \param size  Number of bytes that will be written.
 */
static void read_data(const struct nand_flash_raw *raw,
		uint8_t *buffer, uint32_t size)
{
	uint32_t i;

	/* Check the chip data bus width */
	if (nand_flash_model_get_data_bus_width(MODEL(raw)) == 16) {
		/* Not aligned: read 16-bit and store by byte */
		if (((uint32_t)buffer & 0x1u) || (size & 0x1u))  {
			uint16_t tmp16;
			for (i = 0; i < size;) {
				tmp16 = READ_DATA16(raw);
				buffer[i++] = tmp16 & 0xFF;
				if (i < size) {
					buffer[i++] = (tmp16 >> 8) & 0xFF;
				} else {
					/* No fill on size limit */
				}
			}
		} else {
			/* Aligned, uses 16b pointer */
			uint16_t *buffer16 = (uint16_t *)(uint32_t)buffer;
			size >>= 1;

			for (i = 0; i < size; i++) {
				buffer16[i] = READ_DATA16(raw);
			}
		}
	} else {
		for (i = 0; i < size; i++) {
			buffer[i] = READ_DATA8(raw);
		}
	}
}

/**
 * \brief Erase the specified block of the device.
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

	/* Calculate address used for erase */
	row_address = block *
			nand_flash_model_get_block_size_in_pages(MODEL(raw));

	/* Start erase */
	ENABLE_CE(raw);
	WRITE_COMMAND(raw, NAND_COMMAND_ERASE_1);
	write_row_address(raw, row_address);
	WRITE_COMMAND(raw, NAND_COMMAND_ERASE_2);

	/* make sure for erase ready */
	delay_ms(3);

	wait_ready();

	if (!check_status(raw)) {
		error = NAND_COMMON_ERROR_CANNOTERASE;
	}

	DISABLE_CE(raw);

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
	uint16_t dummy_byte;
	uint32_t row_address;

	/* Calculate physical address of the page */
	row_address = block *
			nand_flash_model_get_block_size_in_pages(MODEL(raw)) + page;

	/* Start write operation */
	ENABLE_CE(raw);

	/* Write data area if needed */
	if (data) {
		WRITE_COMMAND(raw, NAND_COMMAND_WRITE_1);
		write_column_address(raw, 0);
		write_row_address(raw, row_address);
		write_data(raw, (uint8_t *)data, page_data_size);

		/* Spare is written here as well since it is more efficient */
		if (spare) {
			write_data(raw, (uint8_t *)spare, page_spare_size);
		} else {
			/*
			 * Note: special case when ECC parity generation.
			 * ECC results are available as soon as the counter reaches the
			 * end of the main area. But when reach page size for an example,
			 * it could not generate last ECC_PR. The workaround is to receive
			 * page size plus one.
			 */
			read_data(raw, (uint8_t *)(&dummy_byte), 2);
		}

		WRITE_COMMAND(raw, NAND_COMMAND_WRITE_2);

		wait_ready();
		if (!check_status(raw)) {
			error = NAND_COMMON_ERROR_CANNOTWRITE;
		}
	}

	/* Write spare area alone if needed */
	if (spare && (!data)) {
		WRITE_COMMAND(raw, NAND_COMMAND_WRITE_1);
		write_column_address(raw, page_data_size);
		write_row_address(raw, row_address);
		write_data(raw, (uint8_t *)spare, page_spare_size);
		WRITE_COMMAND(raw, NAND_COMMAND_WRITE_2);

		wait_ready();
		if (!check_status(raw)) {
			error = NAND_COMMON_ERROR_CANNOTWRITE;
		}
	}

	/* Disable chip */
	DISABLE_CE(raw);

	return error;
}

/**
 * \brief Copy the data in a page of the NAND Flash device to an other page
 * on that same chip.
 *
 * \param raw  Pointer to a nand_flash_raw instance.
 * \param source_block  Source block number.
 * \param source_page  Source page number inside the source block.
 * \param dest_block  Destination block number.
 * \param dest_page  Destination page number inside the destination block.
 *
 * \return 0 if successful; otherwise return the error code.
 *
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

	/* Use the copy-back facility if available */
	if (nand_flash_model_copy_back(MODEL(raw))) {
		/* Start operation */
		ENABLE_CE(raw);

		/* Start copy-back read */
		WRITE_COMMAND(raw, NAND_COMMAND_COPYBACK_READ_1);
		write_column_address(raw, 0);
		write_row_address(raw, source_row_address);
		WRITE_COMMAND(raw, NAND_COMMAND_COPYBACK_READ_2);
		wait_ready();

		/* Start copy-back write */
		WRITE_COMMAND(raw, NAND_COMMAND_COPYBACK_PROGRAM_1);
		write_column_address(raw, 0);
		write_row_address(raw, dest_row_address);
		WRITE_COMMAND(raw, NAND_COMMAND_COPYBACK_PROGRAM_2);
		wait_ready();

		/* Check status */
		if (!check_status(raw)) {
			error = NAND_COMMON_ERROR_CANNOTCOPY;
		}

		/* Finish operation */
		DISABLE_CE(raw);
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
 * \brief Initializes a nand_flash_raw instance based on the given model and physical interface.
 *
 * \param raw  Pointer to a nand_flash_raw instance.
 * \param model  Pointer to the underlying NAND chip model. Can be 0.
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
#if SAM
	/* Configure SMC for NAND Flash accesses */
	/* Enable peripheral clock */
	pmc_enable_periph_clk(ID_SMC);
	pmc_enable_periph_clk(ID_PIOC),

	/* CS setting in matrix */
	matrix_set_nandflash_cs(0x1u << BOARD_NAND_CS);
#if (SAM4E) 
	if (PIN_NF_RB_IDX == PIO_PB12_IDX) {
		matrix_set_system_io(CCFG_SYSIO_SYSIO12);	
		ioport_set_pin_dir(PIN_NF_RB_IDX, IOPORT_DIR_INPUT);
		ioport_set_pin_mode(PIN_NF_RB_IDX, IOPORT_MODE_PULLUP);
	}
#endif
	/* Configure SMC interface for NAND Flash */
	smc_set_setup_timing(SMC, BOARD_NAND_CS, CONF_NF_SETUP_TIMING);
	smc_set_pulse_timing(SMC, BOARD_NAND_CS, CONF_NF_PULSE_TIMING);
	smc_set_cycle_timing(SMC, BOARD_NAND_CS, CONF_NF_CYCLE_TIMING);
	if (CONF_NF_BUSWIDTH == 8) {
		smc_set_mode(SMC, BOARD_NAND_CS, SMC_MODE_READ_MODE
				| SMC_MODE_WRITE_MODE | SMC_MODE_DBW_8_BIT);
	}
#if !defined(SAM4S)
	if (CONF_NF_BUSWIDTH == 16) {
		smc_set_mode(SMC, BOARD_NAND_CS, SMC_MODE_READ_MODE
				| SMC_MODE_WRITE_MODE | SMC_MODE_DBW_16_BIT);
	}
#endif
#else
	static const gpio_map_t SMC_NF_EBI_GPIO_MAP = {
		{ATPASTE2(AVR32_EBI_NANDOE_0, _PIN),ATPASTE2(AVR32_EBI_NANDOE_0, _FUNCTION)},
		{ATPASTE2(AVR32_EBI_NANDWE_0, _PIN),ATPASTE2(AVR32_EBI_NANDWE_0, _FUNCTION)},
	};

	gpio_enable_module(SMC_NF_EBI_GPIO_MAP,
			(sizeof(SMC_NF_EBI_GPIO_MAP) / sizeof(SMC_NF_EBI_GPIO_MAP[0])));
	smc_init(sysclk_get_cpu_hz());

	/* Enable NAND Flash Chip Select */
	AVR32_HMATRIX.sfr[AVR32_EBI_HMATRIX_NR] |= (1 << AVR32_EBI_NAND_CS);

	/* Set the CE and RB pin */
	gpio_configure_pin(PIN_NF_RB_IDX, GPIO_DIR_INPUT);
	gpio_configure_pin(PIN_NF_CE_IDX, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH);

	/* Unprotect all the flashes */
	gpio_set_gpio_pin(NF_WP_PIN);
#endif

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
				NAND_FLASH_MODEL_LIST_SIZE, nand_flash_raw_read_id(raw),
				&(raw->model))) {
			return NAND_COMMON_ERROR_UNKNOWNMODEL;
		}
	} else {
		/* Copy provided model */
		raw->model = *model;
	}

	return 0;
}

/**
 * \brief Reset a NAND Flash device.
 *
 * \param raw  Pointer to a nand_flash_raw instance.
 */
void nand_flash_raw_reset(const struct nand_flash_raw *raw)
{
	ENABLE_CE(raw);
	WRITE_COMMAND(raw, NAND_COMMAND_RESET);
	wait_ready();
	DISABLE_CE(raw);
}

/**
 * \brief Read and return the identifiers of a NAND Flash chip.
 *
 * \param raw  Pointer to a nand_flash_raw instance.
 *
 * \return id1|(id2<<8)|(id3<<16)|(id4<<24)
 */
uint32_t nand_flash_raw_read_id(const struct nand_flash_raw *raw)
{
	uint32_t chip_id;

	ENABLE_CE(raw);

	WRITE_COMMAND(raw, NAND_COMMAND_READID);
	WRITE_ADDRESS(raw, 0);

	/* make sure ready */
	delay_us(1);

	chip_id = READ_DATA8(raw);
	chip_id |= (READ_DATA8(raw) << 8);
	chip_id |= (READ_DATA8(raw) << 16);
	chip_id |= (READ_DATA8(raw) << 24);
	DISABLE_CE(raw);

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
 * the provided buffers.
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
	uint32_t small_block = nand_flash_model_small_block(MODEL(raw));
	uint32_t page_data_size =
			nand_flash_model_get_page_data_size(MODEL(raw));
	uint32_t page_spare_size =
			nand_flash_model_get_page_spare_size(MODEL(raw));
	uint32_t col_address;
	uint32_t row_address;

	/* Calculate actual address of the page */
	row_address = block *
			nand_flash_model_get_block_size_in_pages(MODEL(raw)) + page;

	/* Start operation */
	ENABLE_CE(raw);

	if (data) {
		col_address = 0;
	} else {
		/* to read spare area in sequential access */
		col_address = page_data_size;
	}

	/* Use either small blocks or large blocks data area read */
	if (small_block) {
		if (col_address == 0) {
			WRITE_COMMAND(raw, NAND_COMMAND_READ_A);
		} else if (col_address == page_data_size) {
			WRITE_COMMAND(raw, NAND_COMMAND_READ_C);
		}

		write_column_address(raw, col_address);
		write_row_address(raw, row_address);
	} else {
		WRITE_COMMAND(raw, NAND_COMMAND_READ_1);
		write_column_address(raw, col_address);
		write_row_address(raw, row_address);
		WRITE_COMMAND(raw, NAND_COMMAND_READ_2);
	}

	/* make sure ready */
	delay_us(30);
	/* Wait for the NAND to be ready */
	wait_ready();

	/* Read data area if needed */
	if (data) {
		WRITE_COMMAND(raw, NAND_COMMAND_READ_1);
		/* make sure ready */
		delay_us(1);

		read_data(raw, data, page_data_size);

		if (spare) {
			read_data(raw, spare, page_spare_size);
		}
	} else {
		/* Read spare area only */
		WRITE_COMMAND(raw, NAND_COMMAND_READ_1);
		read_data(raw, spare, page_spare_size);
	}

	/* Disable CE */
	DISABLE_CE(raw);
}

/**
 * \brief Write the data and/or the spare areas of a page into a NAND Flash.
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
 * \brief Copy the data in a page of the NAND Flash device to an other page
 * on that same chip.
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
 * \brief Copies the data of one whole block of a NAND Flash device to another
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
