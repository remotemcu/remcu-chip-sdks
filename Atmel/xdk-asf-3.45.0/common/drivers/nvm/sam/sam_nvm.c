/**
 * \file
 *
 * \brief Non volatile memories management for SAM devices
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
#include "common_nvm.h"
#include "conf_board.h"
#include "flash_efc.h"
#include "string.h"

status_code_t nvm_init(mem_type_t mem)
{
	switch (mem) {
	case INT_FLASH:
#if SAM4S
	case INT_USERPAGE:
#endif
		break;

#if defined(USE_EXTMEM) && defined(CONF_BOARD_AT45DBX)
	case AT45DBX:
		/* Initialize dataflash */
		at45dbx_init();
		/* Perform memory check */
		if (!at45dbx_mem_check()) {
			return ERR_NO_MEMORY;
		}
		break;
#endif

	default:
		return ERR_INVALID_ARG;
	}

	return STATUS_OK;
}

status_code_t nvm_read_char(mem_type_t mem, uint32_t address, uint8_t *data)
{
	switch (mem) {
	case INT_FLASH:
		*data = *((uint8_t *)(address));
		break;

#if SAM4S
	case INT_USERPAGE:
	{
		/*! This function creates a buffer of IFLASH_PAGE_SIZE to
		 * read the data from starting of user signature */
		uint32_t buffer[IFLASH_PAGE_SIZE];
		uint32_t offset = address - IFLASH_ADDR;
		if (offset < 0) {
			return ERR_INVALID_ARG;
		}

		flash_read_user_signature(buffer, offset);
		*data = buffer[offset];
		break;
	}
#endif

#if defined(USE_EXTMEM) && defined(CONF_BOARD_AT45DBX)
	case AT45DBX:
		if (!at45dbx_read_byte_open(address)) {
			return ERR_BAD_ADDRESS;
		}

		*data = at45dbx_read_byte();
		at45dbx_read_close();
		break;
#endif

	default:
		return ERR_INVALID_ARG;
	}

	return STATUS_OK;
}

status_code_t nvm_write_char(mem_type_t mem, uint32_t address, uint8_t data)
{
	switch (mem) {
	case INT_FLASH:
#if SAM4S

		if (flash_write(address, (const void *)&data, 1,
				false)) {
			return ERR_INVALID_ARG;
		}

#else
		if (flash_write(address, (const void *)&data, 1, true)) {
			return ERR_INVALID_ARG;
		}

#endif
		break;

#if SAM4S
	case INT_USERPAGE:
		if (flash_write_user_signature((const void *)&data,	1)) {
			return ERR_INVALID_ARG;
		}
		break;
#endif

#if defined(USE_EXTMEM) && defined(CONF_BOARD_AT45DBX)
	case AT45DBX:
		if (!at45dbx_write_byte_open(address)) {
			return ERR_BAD_ADDRESS;
		}

		at45dbx_write_byte(data);
		at45dbx_write_close();
		break;
#endif

	default:
		return ERR_INVALID_ARG;
	}

	return STATUS_OK;
}

status_code_t nvm_read(mem_type_t mem, uint32_t address, void *buffer,
		uint32_t len)
{
	switch (mem) {
	case INT_FLASH:
		memcpy(buffer, (const void *)address, len);
		break;

#if SAM4S
	case INT_USERPAGE:
	{
		/*! This function creates a buffer of IFLASH_PAGE_SIZE to
		 * read the data from starting of user signature */
		uint32_t temp_buff[IFLASH_PAGE_SIZE], *buff = buffer;

		/* Read from the starting of user signature */
		if (flash_read_user_signature(temp_buff, len)) {
			return ERR_INVALID_ARG;
		}

		/* Calculate offset and copy required number of bytes */
		for (uint16_t i = 0; i < len; i++) {
			*buff = temp_buff[address - IFLASH_ADDR + i];
			buff++;
		}
		break;
	}
#endif

#if defined(USE_EXTMEM) && defined(CONF_BOARD_AT45DBX)
	case AT45DBX:
	{
		if (len == AT45DBX_SECTOR_SIZE) {
			uint32_t sector = address / AT45DBX_SECTOR_SIZE;
			if (!at45dbx_read_sector_open(sector)) {
				return ERR_BAD_ADDRESS;
			}

			at45dbx_read_sector_to_ram(buffer);
			at45dbx_read_close();
		} else {
			if (!at45dbx_read_byte_open(address)) {
				return ERR_BAD_ADDRESS;
			}
			uint8_t *buf = (uint8_t *)buffer;
			while (len--) {
				*buf++ = at45dbx_read_byte();
			}
			at45dbx_read_close();
		}
		
	}
	break;
#endif

	default:
		return ERR_INVALID_ARG;
	}

	return STATUS_OK;
}

status_code_t nvm_write(mem_type_t mem, uint32_t address, void *buffer,
		uint32_t len)
{
	switch (mem) {
	case INT_FLASH:
#if SAM4S

		if (flash_write(address, (const void *)buffer, len, false)) {
			return ERR_INVALID_ARG;
		}

#else
		if (flash_write(address, (const void *)buffer, len, true)) {
			return ERR_INVALID_ARG;
		}

#endif
		break;

#if SAM4S
	case INT_USERPAGE:
		if (flash_write_user_signature((const void *)buffer, len)) {
			return ERR_INVALID_ARG;
		}
		break;
#endif

#if defined(USE_EXTMEM) && defined(CONF_BOARD_AT45DBX)
	case AT45DBX:
	{
		if (len == AT45DBX_SECTOR_SIZE) {
			uint32_t sector = address / AT45DBX_SECTOR_SIZE;
			if (!at45dbx_write_sector_open(sector)) {
				return ERR_BAD_ADDRESS;
			}

			at45dbx_write_sector_from_ram((const void *)buffer);
			at45dbx_write_close();
		} else {
			if (!at45dbx_write_byte_open(address)) {
				return ERR_BAD_ADDRESS;
			}
			uint8_t *buf = (uint8_t *)buffer;
			while (len--) {
				at45dbx_write_byte(*buf++);
			}
			at45dbx_write_close();
		}	
	}
	break;
#endif

	default:
		return ERR_INVALID_ARG;
	}

	return STATUS_OK;
}

status_code_t nvm_page_erase(mem_type_t mem, uint32_t page_number)
{
	switch (mem) {
	case INT_FLASH:
	{
#if SAM4S
		/*! Page erase function erases minimum 8 pages in Flash */
		if (flash_erase_page((uint32_t)(page_number * IFLASH_PAGE_SIZE),
				IFLASH_ERASE_PAGES_8)) {
			return ERR_INVALID_ARG;
		}

#else
		uint32_t buffer[IFLASH_PAGE_SIZE], byte_address;
		for (uint16_t i = 0; i < IFLASH_PAGE_SIZE; i++) {
			buffer[i] = 0xFFFFFFFF;
		}
		byte_address = page_number * IFLASH_PAGE_SIZE;

		/* Erase and write FFs to a page as there is no function for
		 * erase */
		if (!flash_write(byte_address, (const void *)buffer,
				IFLASH_PAGE_SIZE, true)) {
			return ERR_INVALID_ARG;
		}

#endif
		break;
	}

#if SAM4S
	case INT_USERPAGE:
		flash_erase_user_signature();
		break;
#endif

	default:
		return ERR_INVALID_ARG;
	}

	return STATUS_OK;
}

status_code_t nvm_get_size(mem_type_t mem, uint32_t *size)
{
	switch (mem) {
	case INT_FLASH:
		*size = (uint32_t)IFLASH_SIZE;
		break;

#if SAM4S
	case INT_USERPAGE:
		*size = (uint32_t)IFLASH_PAGE_SIZE;
		break;
#endif

#if defined(USE_EXTMEM) && defined(CONF_BOARD_AT45DBX)
	case AT45DBX:
		*size = (uint32_t)AT45DBX_MEM_SIZE;
		break;
#endif

	default:
		return ERR_INVALID_ARG;
	}

	return STATUS_OK;
}

status_code_t nvm_get_page_size(mem_type_t mem, uint32_t *size)
{
	switch (mem) {
	case INT_FLASH:
#if SAM4S
	case INT_USERPAGE:
#endif
		*size = (uint32_t)IFLASH_PAGE_SIZE;
		break;

	default:
		return ERR_INVALID_ARG;
	}

	return STATUS_OK;
}

status_code_t nvm_get_pagenumber(mem_type_t mem, uint32_t address,
		uint32_t *num)
{
	switch (mem) {
	case INT_FLASH:
		*num = (uint32_t)(address / IFLASH_PAGE_SIZE);
		break;

	default:
		return ERR_INVALID_ARG;
	}

	return STATUS_OK;
}

status_code_t nvm_set_security_bit(void)
{
	if (!flash_enable_security_bit()) {
		return ERR_INVALID_ARG;
	}

	return STATUS_OK;
}
