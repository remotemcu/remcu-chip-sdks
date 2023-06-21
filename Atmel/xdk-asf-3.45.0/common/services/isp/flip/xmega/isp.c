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
#include "nvm.h"
#include "isp.h"
#include "string.h"


#ifdef __GNUC__
	uint16_t start_app_key __attribute__ ((section (".noinit")));
#else
	__no_init uint16_t start_app_key @"SRAM_NO_INIT";
#endif


/**
 * \ingroup isp
 * \defgroup isp_implementation In System Programming XMEGA implementation
 * This implementation links the XMEGA NVM functions to the common isp API.
 * Also, it manage :
 * - the flash access security
 * - the JTAG ID information storage
 * - the bootloader version storage
 * - the start appli operation through software reset
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
	nvm_flash_read_buffer(src, dst, nbytes);
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
	nvm_flash_erase_and_write_buffer(dst, src, nbytes, true);
}

/**
 * \brief  Copy a eeprom memory section to a RAM buffer
 *
 * \param dst    Pointer to data destination.
 * \param src    Pointer to source flash.
 * \param nbytes Number of bytes to transfer.
 */
static void mem_eeprom_read(void *dst, isp_addr_t src, uint16_t nbytes)
{
	nvm_eeprom_read_buffer( src, dst, nbytes );
}

/**
 * \brief  Copy a RAM buffer to a eeprom memory section
 *
 * \param dst    Pointer to flash destination.
 * \param src    Pointer to source data.
 * \param nbytes Number of bytes to transfer.
 */
static void mem_eeprom_write(isp_addr_t dst, const void *src, uint16_t nbytes)
{
#if (FLASH_SIZE==0x10000)
	// Optimize CODE space (150B), but decrease the speed
   	// 24s to program 2KB instead of 1s
	while (nbytes--) {
		nvm_eeprom_write_byte(dst++, *(uint8_t*)src);
		src = (uint8_t*)src + 1;
	}
#else
	nvm_eeprom_erase_and_write_buffer(dst, src, nbytes);
#endif
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
	memcpy(dst, (uint8_t*)&mem_bootloader + src, nbytes);
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
	memcpy(dst, (uint8_t*)&mem_signature + src, nbytes);
}

//! Interface for memory flash
const isp_mem_t isp_flash = {
	.size        = FLASH_SIZE,
	.fnct_read   = mem_flash_read,
	.fnct_write  = mem_flash_write,
};

//! Interface for memory eeprom
const isp_mem_t isp_eeprom = {
	.size        = EEPROM_SIZE,
	.fnct_read   = mem_eeprom_read,
	.fnct_write  = mem_eeprom_write,
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
	.eeprom      = &isp_eeprom,
	.security    = &isp_no_available,
	.conf        = &isp_no_available,
	.bootloader  = &isp_bootloader,
	.signature   = &isp_signature,
	.user        = &isp_no_available,
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
	mem_signature.manufacture = MCU.DEVID0;
	mem_signature.product_number_msb = MCU.DEVID1;
	mem_signature.product_number_lsb = MCU.DEVID2;
	mem_signature.product_revision = MCU.REVID;
}


bool isp_is_security(void)
{
	return !(NVM.LOCKBITS&NVM_LOCKBITS_LB1_bm);
}


bool isp_erase_chip(void)
{
	nvm_flash_erase_app();
	nvm_eeprom_erase_all();
	return true;
}


void isp_start_appli(void)
{
	cpu_irq_disable();
	// generate soft reset for Xmega
	start_app_key=0x55AA;
	ccp_write_io((uint8_t *)&RST.CTRL, RST.CTRL | RST_SWRST_bm);
	while (1);
}


void isp_force_boot_isp(bool force)
{
	// No available on Xmega
}

//@}


//@}

