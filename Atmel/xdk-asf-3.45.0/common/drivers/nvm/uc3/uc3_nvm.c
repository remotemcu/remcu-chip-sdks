/**
 * \file
 *
 * \brief Non volatile memories management for UC3 devices
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
#include "common_nvm.h"
#include "conf_nvm.h"
#include "flash_api.h"
#include "string.h"

status_code_t nvm_init(mem_type_t mem)
{
	switch (mem) {
	case INT_FLASH:
	case INT_USERPAGE:
		/* No initialization required for internal memory */
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
	case INT_USERPAGE:
		*data = *((uint8_t *)(address));
		break;

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
	case INT_USERPAGE:
		flash_api_memcpy((volatile void *)address, (const void *)&data,
				1, true);
		break;

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
	case INT_USERPAGE:
		memcpy(buffer, (const void *)address, len);
		break;

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
	case INT_USERPAGE:
		flash_api_memcpy((volatile void *)address, (const void *)buffer,
				len, true);
		break;

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
		if (!flash_api_erase_page(page_number, true)) {
			return ERR_BAD_DATA;
		}

		break;

	case INT_USERPAGE:
		if (!flash_api_erase_user_page(true)) {
			return ERR_BAD_DATA;
		}

		break;

	default:
		return ERR_INVALID_ARG;
	}

	return STATUS_OK;
}

status_code_t nvm_get_size(mem_type_t mem, uint32_t *size)
{
	switch (mem) {
	case INT_FLASH:
		*size = (uint32_t)flash_api_get_flash_size();
		break;

	case INT_USERPAGE:
		*size = (uint32_t)FLASH_API_PAGE_SIZE;
		break;

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
	case INT_USERPAGE:
		*size = (uint32_t)FLASH_API_PAGE_SIZE;
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
		*num = (uint32_t)(address / FLASH_API_PAGE_SIZE);
		break;

	default:
		return ERR_INVALID_ARG;
	}

	return STATUS_OK;
}

status_code_t nvm_set_security_bit(void)
{
	flash_api_activate_security_bit();

	return STATUS_OK;
}
