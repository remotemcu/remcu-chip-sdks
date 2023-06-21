/**
 * \file
 *
 * \brief In system programming to control security, memories and fuse bits
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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

#include "conf_isp.h"
#include "board.h"
#include "isp.h"
#include "boot.h"
#include "flash_api.h"
#include "string.h"

#if UC3C || UC3D || UC3L3_L4
// These defines are missing from or wrong
// in the toolchain header file ip_xxx.h or part.h
#ifndef AVR32_WDT_KEY_VALUE
  #define AVR32_WDT_KEY_VALUE        0x00000055
#endif
// These defines are missing from or wrong
// in the toolchain header file ip_xxx.h or part.h
#ifndef AVR32_SCIF_RCOSC_FREQUENCY
  #define AVR32_SCIF_RCOSC_FREQUENCY 115200
#endif
#endif


/**
 * \ingroup isp
 * \defgroup isp_implementation In System Programming UC3 implementation
 * This implementation links the UC3 NVM functions to the common isp API.
 * Also, it manage :
 * - the flash access security
 * - the JTAG ID information storage
 * - the bootloader version storage
 * - the ISP force flag
 * - the start appli operation through watchdog reset
 *
 * @{
 */

/**
 * \name Memory APIs
 */
//@{

/**
 * \name Specific memories
 */
//@{

//! Memory signature that stores information about the device
static isp_mem_signature_t mem_signature;

//! Memory bootloader that stores the bootloader version
static isp_mem_bootloader_t mem_bootloader = {
	.version = BOOTLOADER_VERSION,
	.id1 = 0,
	.id2 = 0,
};
//@}

/**
 * \brief  Copy a flash memory section to a RAM buffer
 *
 * \param dst    Pointer to data destination.
 * \param src    Pointer to source flash.
 * \param nbytes Number of bytes to transfer.
 */
static void mem_flash_read(void *dst, isp_addr_t src, uint16_t nbytes)
{
	memcpy(dst, FLASH_API_BASE_ADDRESS + src, nbytes);
}

/**
 * \brief  Copy a RAM buffer to a flash memory section
 *
 * \param dst    Pointer to flash destination.
 * \param src    Pointer to source data.
 * \param nbytes Number of bytes to transfer.
 */
static void mem_flash_write(isp_addr_t dst, const void *src, uint16_t nbytes)
{
	flash_api_memcpy(FLASH_API_BASE_ADDRESS + dst, src, nbytes, false);
}

/**
 * \brief  Copy the security bit value to a RAM buffer
 *
 * \param dst    Pointer to store security bit value.
 * \param src    Not used
 * \param nbytes Must be different of 0
 */
static void mem_security_read(void *dst, isp_addr_t src, uint16_t nbytes)
{
	if (nbytes) {
		*(U8 *) dst = flash_api_is_security_bit_active();
	}
}

/**
 * \brief  Set the security bit
 *
 * \param dst    Not used
 * \param src    Pointer to new security bit value (Must be different of 0)
 * \param nbytes Must be different of 0
 */
static void mem_security_write(isp_addr_t dst, const void *src, uint16_t nbytes)
{
	if (nbytes && *(U8 *) src) {
		flash_api_activate_security_bit();
	}
}

/**
 * \brief  Copy the fuse bits values to a RAM buffer
 *
 * \param dst    Byte array to store fuse bit values (1bit/Byte).
 * \param src    Fuse bit address to read
 * \param nbytes Number of bit to read
 */
static void mem_configuration_read(void *dst, isp_addr_t src, uint16_t nbytes)
{
	U8 *dest = dst;
	while (nbytes--) {
		*dest++ = flash_api_read_gp_fuse_bit(src++);
	}
}

/**
 * \brief  Copy the RAM buffer values to fuse bits
 *
 * \param dst    Fuse bit address to write
 * \param src    Byte array of fuse bit values (1bit/Byte).
 * \param nbytes Number of bit to write
 */
static void mem_configuration_write(isp_addr_t dst, const void *src, uint16_t nbytes)
{
	const U8 *source = src;
	while (nbytes--) {
		flash_api_set_gp_fuse_bit(dst++, *source++);
	}
}

/**
 * \brief  Copy a bootloader version memory section to a RAM buffer
 *
 * \param dst    Pointer to data destination.
 * \param src    Pointer to source memory.
 * \param nbytes Number of bytes to transfer.
 */
static void mem_bootloader_read(void *dst, isp_addr_t src, uint16_t nbytes)
{
	memcpy(dst, &mem_bootloader + src, nbytes);
}

/**
 * \brief  Copy a signature memory section to a RAM buffer
 *
 * \param dst    Pointer to data destination.
 * \param src    Pointer to source memory.
 * \param nbytes Number of bytes to transfer.
 */
static void mem_signature_read(void *dst, isp_addr_t src, uint16_t nbytes)
{
	memcpy(dst, &mem_signature + src, nbytes);
}

/**
 * \brief  Copy an user page memory section to a RAM buffer
 *
 * \param dst    Pointer to data destination.
 * \param src    Pointer to source memory.
 * \param nbytes Number of bytes to transfer.
 */
static void mem_user_read(void *dst, isp_addr_t src, uint16_t nbytes)
{
	memcpy(dst, (U8 *) FLASH_API_USER_PAGE + src, nbytes);
}

/**
 * \brief  Copy a RAM buffer to a user page memory section
 *
 * \param dst    Pointer to user page destination.
 * \param src    Pointer to source data.
 * \param nbytes Number of bytes to transfer.
 */
static void mem_user_write(isp_addr_t dst, const void *src, uint16_t nbytes)
{
	flash_api_memcpy(FLASH_API_USER_PAGE + dst, src, nbytes, true);
}

//! Interface for memory flash
const isp_mem_t isp_flash = {
	.size        = FLASH_API_SIZE,
	.fnct_read   = mem_flash_read,
	.fnct_write  = mem_flash_write,
};

//! Interface for bit security
const isp_mem_t isp_security = {
	.size        = 1,
	.fnct_read   = mem_security_read,
	.fnct_write  = mem_security_write,
};

//! Interface for memory configuration (fuse bits)
const isp_mem_t isp_conf = {
	.size        = FLASH_API_GPF_NUM,
	.fnct_read   = mem_configuration_read,
	.fnct_write  = mem_configuration_write,
};

//! Interface for memory bootloader version
const isp_mem_t isp_bootloader = {
	.size        = sizeof(mem_bootloader),
	.fnct_read   = mem_bootloader_read,
	.fnct_write  = NULL,
};

//! Interface for memory signature
const isp_mem_t isp_signature = {
	.size        = sizeof(mem_signature),
	.fnct_read   = mem_signature_read,
	.fnct_write  = NULL,
};

//! Interface for memory user page
const isp_mem_t isp_user = {
	.size        = FLASH_API_USER_PAGE_SIZE,
	.fnct_read   = mem_user_read,
	.fnct_write  = mem_user_write,
};

//! Interface for memory no available
const isp_mem_t isp_no_available = {
	.size        = 0,
	.fnct_read   = NULL,
	.fnct_write  = NULL,
};

//! \name Memories list declaration
const isp_mems_t isp_memories = {
	.list = {
	.flash       = &isp_flash,
	.eeprom      = &isp_no_available,
	.security    = &isp_security,
	.conf        = &isp_conf,
	.bootloader  = &isp_bootloader,
	.signature   = &isp_signature,
	.user        = &isp_user,
	.int_ram     = &isp_no_available,
	.ext_mem_cs0 = &isp_no_available,
	.ext_mem_cs1 = &isp_no_available,
	.ext_mem_cs2 = &isp_no_available,
	.ext_mem_cs3 = &isp_no_available,
	.ext_mem_cs4 = &isp_no_available,
	.ext_mem_cs5 = &isp_no_available,
	.ext_mem_cs6 = &isp_no_available,
	.ext_mem_cs7 = &isp_no_available,
	.ext_mem_df =  &isp_no_available,
	}
};

//@}


/**
 * \name Miscellaneous functions of the In System Programming module
 */
//@{

void isp_init(void)
{
	uint32_t did_reg = Get_debug_register(AVR32_DID);
	mem_signature.manufacture =
		Rd_bitfield(did_reg, AVR32_DID_MID_MASK);
	mem_signature.product_number_msb =
		Rd_bitfield(did_reg, AVR32_DID_PN_MASK)>>8;
	mem_signature.product_number_lsb =
		Rd_bitfield(did_reg, AVR32_DID_PN_MASK);
	mem_signature.product_revision =
		Rd_bitfield(did_reg, AVR32_DID_RN_MASK);
}


bool isp_is_security(void)
{
	uint8_t value;
	isp_security.fnct_read(&value, 0, 1);
	return value;
}


bool isp_erase_chip(void)
{
	flash_api_lock_all_regions(false);
	flash_api_erase_all_pages(false);
	return true;
}


bool isp_erase_chip_split(void)
{
	static uint16_t isp_page_number=0;
	uint8_t isp_page_number_split;

	if (isp_page_number==0) {
		isp_page_number = flash_api_get_page_count();
		flash_api_lock_all_regions(false);
	}
	isp_page_number_split = 128;
	while (isp_page_number && isp_page_number_split) {
		flash_api_erase_page(--isp_page_number, false);
		isp_page_number_split--;
	}
	return (isp_page_number==0);
}


void isp_start_appli(void)
{
	cpu_irq_disable();
	AVR32_WDT.ctrl = AVR32_WDT_CTRL_EN_MASK |
			(10 << AVR32_WDT_CTRL_PSEL_OFFSET) |
#if (UC3C || UC3D || UC3L3_L4)
			AVR32_WDT_CTRL_CEN_MASK | AVR32_WDT_CTRL_DAR_MASK |
#endif
			(AVR32_WDT_KEY_VALUE << AVR32_WDT_CTRL_KEY_OFFSET);
	AVR32_WDT.ctrl = AVR32_WDT_CTRL_EN_MASK |
			(10 << AVR32_WDT_CTRL_PSEL_OFFSET) |
#if (UC3C || UC3D || UC3L3_L4)
			AVR32_WDT_CTRL_CEN_MASK | AVR32_WDT_CTRL_DAR_MASK |
#endif
			((~AVR32_WDT_KEY_VALUE << AVR32_WDT_CTRL_KEY_OFFSET) &
			AVR32_WDT_CTRL_KEY_MASK);
	while (1);
}

/**
 * \brief Calculates the CRC-8-CCITT
 *
 * CRC-8-CCITT is defined to be x^8 + x^2 + x + 1
 * To use this function use the following template:
 * crc = isp_crc8( crc, data );
 */
static uint8_t isp_crc8(uint8_t inCrc, uint8_t inData)
{
	uint8_t i;
	uint16_t data;

	data = inCrc ^ inData;
	data <<= 8;

	for (i = 0; i < 8; i++) {
		if ((data & 0x8000) != 0) {
			data = data ^ (BOOT_CFG1_CRC8_POLYNOMIAL << 7);
		}
		data = data << 1;
	}
	return (uint8_t)(data >> 8);
}


void isp_force_boot_isp(bool force)
{
	uint32_t tempo;
	uint8_t crc8 = 0;
	uint8_t i;

	// Read the config word1 and set the ISP_FORCE bit to force.
	tempo = (BOOT_CFG1 & ~BOOT_CFG1_FORCE_MASK)
		| ((force << BOOT_CFG1_FORCE_OFFSET) & BOOT_CFG1_FORCE_MASK);
	// Compute the CRC8 on the 3 upper Bytes of the word1.
	for (i = 24; i; i -= 8)
		crc8 = isp_crc8(crc8, tempo >> i);
	// Write CRC8 in word1.
	tempo = (tempo & ~BOOT_CFG1_CRC8_MASK)
		| ((crc8 << BOOT_CFG1_CRC8_OFFSET) & BOOT_CFG1_CRC8_MASK);
	// Write the config word1 in user flash.
	flash_api_memcpy((volatile void*) BOOT_CFG1_ADDRESS, &tempo, 4, true);
}

//@}


//@}

