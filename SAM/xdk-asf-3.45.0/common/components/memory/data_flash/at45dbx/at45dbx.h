/**
 * \file
 *
 * \brief Management of the AT45DBX DataFlash component.
 *
 * Copyright (c) 2010-2018 Microchip Technology Inc. and its subsidiaries.
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
#ifndef _AT45DBX_H_
#define _AT45DBX_H_

#include "conf_at45dbx.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup at45dbx_group AT45dbx DataFlash component driver.
 *
 * This is a driver for the AT45dbX series DataFlash memories.
 * It provides functions for initialization, read and write operations at
 * byte or sector level.
 * The DataFlash driver can be used either with SPI Master Service or
 * USART_SPI Service. The SPI service configuration depends on
 * AT45DBX_USES_SPI_MASTER_SERVICE or AT45DBX_USES_USART_SPI_SERVICE
 * defined in conf_at45dbx.h.
 *
 * \section dependencies Dependencies
 * This driver depends on the following modules:
 * - \ref spi_group for SPI master interface.
 *
 * @{
 */
//_____ D E F I N I T I O N S ______________________________________________

/*! \name Available AT45DBX Sizes
 *
 * Number of address bits of available AT45DBX data flash memories.
 *
 * \note All memories from page sizes of 256 bytes to 1024 bytes are
 *       supported.
 */
//! @{
#define AT45DBX_500KB           19
#define AT45DBX_1MB             20
#define AT45DBX_2MB             21
#define AT45DBX_4MB             22
#define AT45DBX_8MB             23
//! @}

//! Number of bits for addresses within logical sectors of file system.
#ifdef AT45DB641E
#define AT45DBX_SECTOR_BITS     8
#else
#define AT45DBX_SECTOR_BITS     9
#endif

//! Logical sector size of file system in bytes.
#define AT45DBX_SECTOR_SIZE     (1 << AT45DBX_SECTOR_BITS)


//_____ D E C L A R A T I O N S ____________________________________________

/*! \name Control Functions
 */
//! @{

/*! \brief Initializes the data flash controller and the SPI channel by which
 *         the DF is controlled.
 *
 * \retval true Success.
 * \retval false Failure.
 */
extern bool at45dbx_init(void);

/*! \brief Performs a memory check on all DataFlash memories.
 *
 * \retval true Success.
 * \retval false Failure.
 */
extern bool at45dbx_mem_check(void);

/*! \brief Opens a DataFlash memory in read mode at a given sector.
 *
 * \param sector  Start sector.
 *
 * \retval true Success.
 * \retval false Failure.
 *
 * \note Sector may be page-unaligned (depending on the DataFlash page size).
 */
extern bool at45dbx_read_sector_open(uint32_t sector);

/*! \brief Opens a DataFlash memory in read mode at a given byte address.
 *
 * \param ad  Start address.
 *
 * \retval true Success.
 * \retval false Failure.
 */
extern bool at45dbx_read_byte_open(uint32_t ad);


/*! \brief Unselects the current DataFlash memory.
 */
extern void at45dbx_read_close(void);

/*! \brief This function opens a DataFlash memory in write mode at a given sector.
 *
 * \param sector  Start sector.
 *
 * \retval true Success.
 * \retval false Failure.
 *
 * \note Sector may be page-unaligned (depending on the DF page size).
 *
 * \note If \ref AT45DBX_PAGE_SIZE > \ref AT45DBX_SECTOR_SIZE, page content is
 *       first loaded in buffer to then be partially updated by write byte or
 *       write sector functions.
 */
extern bool at45dbx_write_sector_open(uint32_t sector);

/*! \brief This function opens a DataFlash memory in write mode at a given address.
 *
 * \param ad  Start address.
 *
 * \retval true Success.
 * \retval false Failure.
 *
 */
extern bool at45dbx_write_byte_open(uint32_t ad);

/*! \brief Fills the end of the current logical sector and launches page programming.
 */
extern void at45dbx_write_close(void);

//! @}


/*! \name Single-Byte Access Functions
 */
//! @{

/*! \brief Performs a single byte read from DataFlash memory.
 *
 * \return The read byte.
 *
 * \note First call must be preceded by a call to the \ref at45dbx_read_byte_open
 *       function.
 */
extern uint8_t at45dbx_read_byte(void);

/*! \brief Performs a single byte write to DataFlash memory.
 *
 * \param b The byte to write.
 *
 * \retval true Success.
 * \retval false Failure.
 *
 * \note First call must be preceded by a call to the \ref at45dbx_write_byte_open
 *       function.
 */
extern bool at45dbx_write_byte(uint8_t b);

//! @}




/*! \name Single-Sector Access Functions
 */
//! @{

/*! \brief Reads one DataFlash sector to a RAM buffer.
 *
 * Data flow is: DataFlash -> RAM.
 *
 * \param ram Pointer to RAM buffer.
 *
 * \retval true Success.
 * \retval false Failure.
 *
 * \note First call must be preceded by a call to the \ref at45dbx_read_sector_open
 *       function.
 */
extern bool at45dbx_read_sector_to_ram(void *ram);

/*! \brief Writes one DataFlash sector from a RAM buffer.
 *
 * Data flow is: RAM -> DataFlash.
 *
 * \param ram Pointer to RAM buffer.
 *
 * \retval true Success.
 * \retval false Failure.
 *
 * \note First call must be preceded by a call to the \ref at45dbx_write_sector_open
 *       function.
 */
extern bool at45dbx_write_sector_from_ram(const void *ram);

//! @}

/*! \name Functions to connect the DataFlash driver with the SPI Multiple-Sector Access Functions
 */
//! @{
extern void at45dbx_spi_init(void);
extern void at45dbx_spi_select_device(uint8_t mem_id);
extern void at45dbx_spi_deselect_device(uint8_t mem_id);
extern void at45dbx_spi_write_byte(uint8_t data);
extern void at45dbx_spi_read_byte(uint8_t *data);
extern void at45dbx_spi_read_packet(void const *data, size_t len);
extern void at45dbx_spi_write_packet(void const *data, size_t len);
//! @}

//! @}

/**
 * \internal
 * \brief Check the address passed is valid.
 *
 * Driver-internal function for checking the DataFlash address is in memory
 * range configuration.
 *
 * \param  address  The address to be checked
 *
 * \return true when the address is valid, false when out of memory range.
 */
static inline bool at45dbx_check_address(uint32_t address)
{
	if (address >= (((uint32_t)1<<AT45DBX_MEM_SIZE)*AT45DBX_MEM_CNT)) {
		return false;
	} else {
		return true;
	}
}

#ifdef __cplusplus
}
#endif

#endif  // _AT45DBX_H_
