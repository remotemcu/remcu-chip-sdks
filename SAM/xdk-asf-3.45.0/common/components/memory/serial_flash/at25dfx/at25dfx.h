/**
 * \file
 *
 * \brief API driver for AT25DFx SerialFlash component.
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

#ifndef AT25DFX_H_INCLUDED
#define AT25DFX_H_INCLUDED

#include "compiler.h"
#include "conf_at25dfx.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/** Device ready/busy status bit */
#define AT25_STATUS_RDYBSY          (1 << 0)
/** Device is ready */
#define AT25_STATUS_RDYBSY_READY    (0 << 0)
/** Device is busy with internal operations */
#define AT25_STATUS_RDYBSY_BUSY     (1 << 0)
/** Write enable latch status bit */
#define AT25_STATUS_WEL             (1 << 1)
/** Device is not write enabled */
#define AT25_STATUS_WEL_DISABLED    (0 << 1)
/** Device is write enabled */
#define AT25_STATUS_WEL_ENABLED     (1 << 1)
/** Software protection status bitfield */
#define AT25_STATUS_SWP             (3 << 2)
/** All sectors are software protected */
#define AT25_STATUS_SWP_PROTALL     (3 << 2)
/** Some sectors are software protected */
#define AT25_STATUS_SWP_PROTSOME    (1 << 2)
/** No sector is software protected */
#define AT25_STATUS_SWP_PROTNONE    (0 << 2)
/** Write protect pin status bit */
#define AT25_STATUS_WPP             (1 << 4)
/** Write protect signal is not asserted */
#define AT25_STATUS_WPP_NOTASSERTED (0 << 4)
/** Write protect signal is asserted */
#define AT25_STATUS_WPP_ASSERTED    (1 << 4)
/** Erase/program error bit */
#define AT25_STATUS_EPE             (1 << 5)
/** Erase or program operation was successful */
#define AT25_STATUS_EPE_SUCCESS     (0 << 5)
/** Erase or program error is detected */
#define AT25_STATUS_EPE_ERROR       (1 << 5)
/** Sector protection registers locked bit */
#define AT25_STATUS_SPRL            (1 << 7)
/** Sector protection registers are unlocked */
#define AT25_STATUS_SPRL_UNLOCKED   (0 << 7)
/** Sector protection registers are locked */
#define AT25_STATUS_SPRL_LOCKED     (1 << 7)

/** Read array command code */
#define AT25_READ_ARRAY             0x0B
/** Read array (low frequency) command code */
#define AT25_READ_ARRAY_LF          0x03
/** Block erase command code (4K block) */
#define AT25_BLOCK_ERASE_4K         0x20
/** Block erase command code (32K block) */
#define AT25_BLOCK_ERASE_32K        0x52
/** Block erase command code (64K block) */
#define AT25_BLOCK_ERASE_64K        0xD8
/** Chip erase command code 1 */
#define AT25_CHIP_ERASE_1           0x60
/** Chip erase command code 2 */
#define AT25_CHIP_ERASE_2           0xC7
/** Byte/page program command code */
#define AT25_BYTE_PAGE_PROGRAM      0x02
/** Sequential program mode command code 1 */
#define AT25_SEQUENTIAL_PROGRAM_1   0xAD
/** Sequential program mode command code 2 */
#define AT25_SEQUENTIAL_PROGRAM_2   0xAF
/** Write enable command code */
#define AT25_WRITE_ENABLE           0x06
/** Write disable command code */
#define AT25_WRITE_DISABLE          0x04
/** Protect sector command code */
#define AT25_PROTECT_SECTOR         0x36
/** Unprotect sector command code */
#define AT25_UNPROTECT_SECTOR       0x39
/** Read sector protection registers command code */
#define AT25_READ_SECTOR_PROT       0x3C
/** Read status register command code */
#define AT25_READ_STATUS            0x05
/** Write status register command code */
#define AT25_WRITE_STATUS           0x01
/** Read manufacturer and device ID command code */
#define AT25_READ_JEDEC_ID          0x9F
/** Deep power-down command code */
#define AT25_DEEP_PDOWN             0xB9
/** Resume from deep power-down command code */
#define AT25_RES_DEEP_PDOWN         0xAB

/** Global protection data */
#define AT25_GLOBAL_PROTECT_VALUE         0x3C

/** Sector Protection Register value is 1 (sector is protected) */
#define AT25_SECTOR_PROTECTED_VALUE    0xff

/** Sector Protection Register value is 0 (sector is unprotected) */
#define AT25_SECTOR_UNPROTECTED_VALUE    0x0

/** Protect type code */
#define AT25_TYPE_PROTECT  0x1

/** Unprotect type code */
#define AT25_TYPE_UNPROTECT  0x0

/** Supporting AT25 device type */
#define AT25DFX_041A 0 /* AT25DF041A */
#define AT25DFX_161  1 /* AT25DF161  */
#define AT25DFX_081A 2 /* AT26DF081A */
#define AT25DFX_0161 3 /* AT26DF0161 */
#define AT25DFX_161A 4 /* AT26DF161A */
#define AT25DFX_321  5 /* AT25DF321  */
#define AT25DFX_321A 6 /* AT25DF321A */
#define AT25DFX_512B 7 /* AT25DF512B */
#define AT25DFX_021  8 /* AT25DF021  */
#define AT25DFX_641A 9 /* AT25DF641A */

/** AT25 operation status, each operation returns one of the following status */
typedef enum at25_status {
	AT25_SUCCESS = 0,  /** Current operation successful */
	AT25_SECTOR_PROTECTED, /** Sector protected */
	AT25_SECTOR_UNPROTECTED,  /** Sector unprotected */
	AT25_ERROR_INIT,  /** Initialization error: p_at25->pdesc is not initialized */
	AT25_ERROR_NOT_FOUND,  /** The specific SerialFlash Not found  */
	AT25_ERROR_WRITE, /** Write error returned by the SerialFlash */
	AT25_ERROR_BUSY,  /** Current operation failed, SerialFlash is busy */
	AT25_ERROR_PROTECTED,  /** Current operation failed, SerialFlash is protected */
	AT25_ERROR_SPI,  /** SPI transfer failed */
	AT25_ERROR  /** Current operation failed */
} at25_status_t;


at25_status_t at25dfx_initialize(void);
void at25dfx_set_mem_active(uint8_t cs);
at25_status_t at25dfx_mem_check(void);
at25_status_t at25dfx_read_status(uint8_t *status);
at25_status_t at25dfx_write_status(uint8_t status);
at25_status_t at25dfx_read_sector_protect_status(uint32_t address);
at25_status_t at25dfx_protect_sector(uint32_t address, uint8_t protect_type);
at25_status_t at25dfx_protect_chip(uint8_t protect_type);
at25_status_t at25dfx_erase_chip(void);
at25_status_t at25dfx_erase_block(uint32_t address);
at25_status_t at25dfx_read(uint8_t *data, uint16_t size, uint32_t address);
at25_status_t at25dfx_write(uint8_t *data, uint16_t size, uint32_t address);

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \page at25dfx_quickstart Quickstart guide for AT25DFx component.
 *
 * This is the quickstart guide for the \ref at25dfx_group "AT25DFx SerialFlash component",
 * with step-by-step instructions on how to configure and use the driver in a
 * selection of use cases.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section at25dfx_basic_use_case Basic use case
 * In the basic use case, the AT25DFx component are configured for:
 * - The type of the AT25DFx component is AT25DF321 
 * - The AT25DF321 is connected to the module SPI0
 * - The SPI is configured as master mode
 * - The SPI master speed is 12MHz
 * - The SPI transfer uses 8 bits mode
 * - The chip select used by the AT25DF321 is 3
 * - There is one AT25DFx device to be managed
 * - The memory ID used for the AT25DF321 is 1
 * - 1024 bytes of data beginning from block 0 will be written to the AT25DF321
 * - 1024 bytes of data will be read from the block 0 of the AT25DF321
 *
 * \section at25dfx_basic_use_case_setup Setup steps
 *
 * \subsection at25dfx_basic_use_case_setup_prereq Prerequisites
 * -# \ref sysclk_group "System Clock Management (sysclock)"
 * -# \ref pio_group "Parallel Input/Output Controller (pio)"
 * -# \ref pmc_group "Power Management Controller (pmc)"
 * -# \ref spi_group "Serial Peripheral Interface (SPI)"
 *
 * \subsection at25dfx_basic_use_case_setup_code Example code
 * Content of conf_at25dfx.h
 * \code
	#define AT25DFX_USES_SPI_MASTER_SERVICE
	#define AT25DFX_SPI_MODULE          SPI0
	#define AT25DFX_CS                  3
	#define AT25DFX_MEM_CNT             1
	#define AT25DFX_MEM_ID              1
	#define AT25DFX_SPI_MASTER_SPEED    12000000
	#define AT25DFX_SPI_BITS            8
	#define AT25DFX_MEM_TYPE            AT25DFX_321
\endcode
 *
 * A specific size of RAM buffer must be added; The access address and size in the SerialFlash must be defined:
 * \code
	 #define AT25DFX_TEST_BLOCK_ADDR  (0)
	 #define AT25DFX_TEST_DATA_SIZE   (1024)

	  static uint32_t ram_buff[1024];
\endcode
 *
 * Add to application C-file:
 * \code
	   void at25dfx_init(void)
	   {
	       sysclk_init();

	       board_init();

	       at25dfx_initialize();

	       at25dfx_set_mem_active(AT25DFX_MEM_ID);

	       at25dfx_protect_chip(AT25_TYPE_UNPROTECT);
	   }
\endcode
 *
 * \subsection at25dfx_basic_use_case_setup_flow Workflow
 * -# Ensure that conf_at25dfx.h is present and contains the
 * following configuration symbol. This configuration file is used
 * by the driver and should not be included by the user.
 *   - \code 
	#define AT25DFX_USES_SPI_MASTER_SERVICE 
	#define AT25DFX_SPI_MODULE          SPI0
	#define AT25DFX_CS                  3
	#define AT25DFX_MEM_CNT             1
	#define AT25DFX_MEM_ID              1
	#define AT25DFX_SPI_MASTER_SPEED    12000000
	#define AT25DFX_SPI_BITS            8
	#define AT25DFX_MEM_TYPE            AT25DFX_321
\endcode
 * -# Enable the system clock:
 *   - \code sysclk_init(); \endcode
 * -# Enable PIO configurations for SPI master:
 *   - \code board_init(); \endcode
 * -# Initialize the AT25DF321 component; it will set all the configurations
 * defined in the conf_at25dfx.h:
 *   - \code at25dfx_initialize(); \endcode
 * -# Set the target AT25DF321 device active, the AT25DF321 can be accessed from now on:
 *   - \code at25dfx_set_mem_active(AT25DFX_MEM_ID); \endcode
 * -# The AT25DF321 will be protected from writing by default, so a unprotect is necessary:
 *   - \code at25dfx_protect_chip(AT25_TYPE_UNPROTECT); \endcode 
 *
 * \section at25dfx_basic_use_case_usage Usage steps
 * \subsection at25dfx_basic_use_case_usage_code Example code
 * Add to, e.g., main loop in application C-file:
 * \code
	at25dfx_write(ram_buff, AT25DFX_TEST_DATA_SIZE, AT25DFX_TEST_BLOCK_ADDR);
	at25dfx_read(ram_buff, AT25DFX_TEST_DATA_SIZE, AT25DFX_TEST_BLOCK_ADDR);
\endcode
 *
 * \subsection at25dfx_basic_use_case_usage_flow Workflow
 * -# Start writing the data to the AT25DFx321:
 *   - \code at25dfx_write(ram_buff, AT25DFX_TEST_DATA_SIZE, AT25DFX_TEST_BLOCK_ADDR); \endcode
 * -# Start reading the data from the AT25DFx321:
 *   - \code at25dfx_read(ram_buff, AT25DFX_TEST_DATA_SIZE, AT25DFX_TEST_BLOCK_ADDR); \endcode
 */

#endif /* AT25DFX_H_INCLUDED */
