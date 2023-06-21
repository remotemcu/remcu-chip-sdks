/**
 *
 * \file
 *
 * \brief Flash Memory Access API's
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
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
 #include "memory_flash.h"
/** The last byte address of internal flash */
#define IFLASH_END (IFLASH_ADDR + IFLASH_SIZE - 1)

/* critical disable irq */
#define mem_flash_op_enter() do {\
		__DSB(); __ISB();        \
		cpu_irq_disable();       \
		__DMB();                 \
	} while (0)
/* critical enable irq */
#define mem_flash_op_exit() do {  \
		__DMB(); __DSB(); __ISB();\
		cpu_irq_enable();         \
	} while (0)

/**
 * Initialize the flash
 */
void mem_flash_init(void)
{
	flash_init(FLASH_ACCESS_MODE_128, 6);
	printf("flash: init done\r\n");
}

/**
 * Cleans up the flash
 */
void mem_flash_cleanup(void)
{
	printf("flash: cleanup ...\r\n");
	printf("flash: cleanup done\r\n");
}

/**
 * Erase area in flash
 *
 * \param addr Flash address in bytes
 * \param size number of bytes to erase
 *
 * \return erased bytes (could be larger than size)
 */
uint32_t mem_flash_erase(void *addr, uint32_t size)
{
#if SAM4S || SAM4E || SAM4N
	uint32_t page_addr = (uint32_t)addr;
	uint32_t page_off  = page_addr % (IFLASH_PAGE_SIZE*8);
	uint32_t rc, erased = 0;
	if (page_off) {
		printf("flash: erase address must be 8 page aligned\r\n");
		page_addr = page_addr - page_off;
		printf("flash: erase from %x\r\n", (unsigned)page_addr);
	}
	for (erased = 0; erased < size;) {
		rc = flash_erase_page((uint32_t)page_addr, IFLASH_ERASE_PAGES_8);
		erased    += IFLASH_PAGE_SIZE*8;
		page_addr += IFLASH_PAGE_SIZE*8;
		if (rc != FLASH_RC_OK) {
			printf("flash: %x erase error\r\n", (unsigned)page_addr);
			break;
		}
	}
	return erased;
#elif SAMG55
	uint32_t page_addr = (uint32_t)addr;
	uint32_t page_off  = page_addr % (IFLASH_PAGE_SIZE*16);
	uint32_t rc, erased = 0;
	if (page_off) {
		printf("flash: erase address must be 16 page aligned\r\n");
		page_addr = page_addr - page_off;
		printf("flash: erase from %x\r\n", (unsigned)page_addr);
	}
	for (erased = 0; erased < size;) {
		rc = flash_erase_page((uint32_t)page_addr, IFLASH_ERASE_PAGES_16);
		erased    += IFLASH_PAGE_SIZE*16;
		page_addr += IFLASH_PAGE_SIZE*16;
		if (rc != FLASH_RC_OK) {
			printf("flash: %x erase error\r\n", (unsigned)page_addr);
			break;
		}
	}
	return erased;
#else
	/* Everything assume to be erased since we use erase and write command */
	UNUSED(addr);
	return size;
#endif
}

/**
 * Write one page to flash
 *
 * \param addr Flash address in bytes
 * \param data Source data buffer
 *
 * \return true if success.
 */
bool mem_flash_page_write(void *addr, void *data)
{
	uint32_t rc = FLASH_RC_OK;
	mem_flash_op_enter();
#if SAM4S || SAM4E || SAM4N || SAMG55
	/* The EWP command can only be used in 8 KBytes sector for SAM4S, SAM4E
	 * and SAM4N, so an erase command is requried before write operation.
	 */
	rc = flash_write((uint32_t)addr, data, IFLASH_PAGE_SIZE, false);
#else
	rc = flash_write((uint32_t)addr, data, IFLASH_PAGE_SIZE, true);
#endif
	mem_flash_op_exit();
	if (FLASH_RC_OK != rc) {
		return false;
	}
	return true;
}

/**
 * Return next page address after/start at input address
 *
 * \param addr Flash address in bytes
 * \return Next page address in bytes
 */
void *mem_flash_page_next(void *addr)
{
	uint32_t address = (uint32_t)addr;
	uint32_t offset = address % IFLASH_PAGE_SIZE;
	if (offset) {
		address += (IFLASH_PAGE_SIZE - offset);
	}
	/* Mapped address to boot area */
	if (address < IFLASH_ADDR) {
		address += IFLASH_ADDR;
	}
	return (void*)address;
}

/**
 * Lock flash region
 *
 * \param start Start physical address
 * \param end   End physical address
 *
 * \return true if success
 */
bool mem_flash_lock(void* start, void* end)
{
	uint32_t rc;
	uint32_t start_addr = (uint32_t)start;
	uint32_t end_addr = (uint32_t)end;
	if (start_addr < IFLASH_ADDR) {
		start_addr = IFLASH_ADDR;
	}
	if (end_addr > IFLASH_END || end_addr == 0) {
		end_addr = IFLASH_END;
	}
	if (start_addr >= end_addr) {
		return false;
	}
	mem_flash_op_enter();
	rc = flash_lock(start_addr, end_addr, NULL, NULL);
	mem_flash_op_exit();
	if (rc) {
		return false;
	}
	return true;
}

/**
 * Unlock flash region
 *
 * \param start Start physical address
 * \param end   End physical address
 *
 * \return true if success 
 */
bool mem_flash_unlock(void *start, void* end)
{
	uint32_t rc;
	uint32_t start_addr = (uint32_t)start;
	uint32_t end_addr = (uint32_t)end;
	if (start_addr < IFLASH_ADDR) {
		start_addr = IFLASH_ADDR;
	}
	if (end_addr > IFLASH_END || end_addr == 0) {
		end_addr = IFLASH_END;
	}
	if (start_addr >= end_addr) {
		return false;
	}
	mem_flash_op_enter();
	rc = flash_unlock(start_addr, end_addr, NULL, NULL);
	mem_flash_op_exit();
	if (rc) {
		return false;
	}
	return true;
}

