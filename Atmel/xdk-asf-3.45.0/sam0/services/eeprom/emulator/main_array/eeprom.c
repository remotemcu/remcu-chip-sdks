/**
 * \file
 *
 * \brief SAM EEPROM Emulator
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
#include "eeprom.h"
#include <string.h>
#include <nvm.h>

/**
 * \internal
 * Magic key is the sequence "AtEEPROMEmu." in ASCII. The key is encoded as a
 * sequence of 32-bit values to speed up checking of the key, which can be
 * implemented as a number of simple integer comparisons,
 */
#define EEPROM_MAGIC_KEY                 {0x41744545, 0x50524f4d, 0x456d752e}

/** \internal
 *  Length of the magic key, in 32-bit elements.
 */
#define EEPROM_MAGIC_KEY_COUNT           3

COMPILER_PACK_SET(1);
/**
 * \internal
 * \brief Structure describing the EEPROM Emulation master page.
 */
struct _eeprom_master_page {
	/** Magic key which in ASCII will show as AtEEPROMEmu. */
	uint32_t magic_key[EEPROM_MAGIC_KEY_COUNT];

	/** Emulator major version information. */
	uint8_t  major_version;
	/** Emulator minor version information. */
	uint8_t  minor_version;
	/** Emulator revision version information. */
	uint8_t  revision;

	/** Emulator identification value (to distinguish between different emulator
	 *  schemes that carry the same version numbers). */
	uint8_t  emulator_id;

	/** Unused reserved bytes in the master page. */
	uint8_t  reserved[48];
};

/**
 * \internal
 * \brief Structure describing emulated pages of EEPROM data.
 */
struct _eeprom_page {
	/** Header information of the EEPROM page. */
	struct {
		uint8_t logical_page;
		uint8_t reserved[EEPROM_HEADER_SIZE - 1];
	} header;

	/** Data content of the EEPROM page. */
	uint8_t data[EEPROM_PAGE_SIZE];
};
COMPILER_PACK_RESET();

/**
 * \internal
 * \brief Internal device instance struct.
 */
struct _eeprom_module {
	/** Initialization state of the EEPROM emulator. */
	bool initialized;

	/** Absolute byte pointer to the first byte of FLASH where the emulated
	 *  EEPROM is stored. */
	const struct _eeprom_page *flash;

	/** Number of physical FLASH pages occupied by the EEPROM emulator. */
	uint16_t physical_pages;
	/** Number of logical FLASH pages occupied by the EEPROM emulator. */
	uint8_t  logical_pages;

	/** Mapping array from logical EEPROM pages to physical FLASH pages. */
	uint8_t page_map[EEPROM_MAX_PAGES / 2 - 4];

	/** Row number for the spare row (used by next write). */
	uint8_t spare_row;

	/** Buffer to hold the currently cached page. */
	struct _eeprom_page cache;
	/** Indicates if the cache contains valid data. */
	bool cache_active;
};

/**
 * \internal
 * \brief Internal EEPROM emulator instance.
 */
static struct _eeprom_module _eeprom_instance = {
	.initialized = false,
};


/** \internal
 *  \brief Erases a given row within the physical EEPROM memory space.
 *
 *  \param[in] row  Physical row in EEPROM space to erase
 */
static void _eeprom_emulator_nvm_erase_row(
		const uint8_t row)
{
	enum status_code error_code = STATUS_OK;

	do {
		error_code = nvm_erase_row(
				(uint32_t)&_eeprom_instance.flash[row * NVMCTRL_ROW_PAGES]);
	} while (error_code == STATUS_BUSY);
}

/** \internal
 *  \brief Fills the internal NVM controller page buffer in physical EEPROM memory space.
 *
 *  \param[in] physical_page  Physical page in EEPROM space to fill
 *  \param[in] data           Data to write to the physical memory page
 */
static void _eeprom_emulator_nvm_fill_cache(
		const uint16_t physical_page,
		const void* const data)
{
	enum status_code error_code = STATUS_OK;

	do {
		error_code = nvm_write_buffer(
				(uint32_t)&_eeprom_instance.flash[physical_page],
				(uint8_t*)data,
				NVMCTRL_PAGE_SIZE);
	} while (error_code == STATUS_BUSY);
}

/** \internal
 *  \brief Commits the internal NVM controller page buffer to physical memory.
 *
 *  \param[in] physical_page  Physical page in EEPROM space to commit
 */
static void _eeprom_emulator_nvm_commit_cache(
		const uint16_t physical_page)
{
	enum status_code error_code = STATUS_OK;

	do {
		error_code = nvm_execute_command(
				NVM_COMMAND_WRITE_PAGE,
				(uint32_t)&_eeprom_instance.flash[physical_page], 0);
	} while (error_code == STATUS_BUSY);
}

/** \internal
 *  \brief Reads a page of data stored in physical EEPROM memory space.
 *
 *  \param[in]  physical_page  Physical page in EEPROM space to read
 *  \param[out] data           Destination buffer to fill with the read data
 */
static void _eeprom_emulator_nvm_read_page(
		const uint16_t physical_page,
		void* const data)
{
	enum status_code error_code = STATUS_OK;

	do {
		error_code = nvm_read_buffer(
				(uint32_t)&_eeprom_instance.flash[physical_page],
				(uint8_t*)data,
				NVMCTRL_PAGE_SIZE);
	} while (error_code == STATUS_BUSY);
}

/**
 * \brief Initializes the emulated EEPROM memory, destroying the current contents.
 */
static void _eeprom_emulator_format_memory(void)
{
	uint16_t logical_page = 0;

	/* Set row 0 as the spare row */
	_eeprom_instance.spare_row = 0;
	_eeprom_emulator_nvm_erase_row(_eeprom_instance.spare_row);

	for (uint16_t physical_page = NVMCTRL_ROW_PAGES;
			physical_page < _eeprom_instance.physical_pages; physical_page++) {

		if (physical_page == EEPROM_MASTER_PAGE_NUMBER) {
			continue;
		}

		/* If we are at the first page in a new row, erase the entire row */
		if ((physical_page % NVMCTRL_ROW_PAGES) == 0) {
			_eeprom_emulator_nvm_erase_row(physical_page / NVMCTRL_ROW_PAGES);
		}

		/* Two logical pages are stored in each physical row; program in a
		 * pair of initialized but blank set of emulated EEPROM pages */
		if ((physical_page % NVMCTRL_ROW_PAGES) < 2) {
			/* Make a buffer to hold the initialized EEPROM page */
			struct _eeprom_page data;
			memset(&data, 0xFF, sizeof(data));

			/* Set up the new EEPROM row's header */
			data.header.logical_page = logical_page;

			/* Write the page out to physical memory */
			_eeprom_emulator_nvm_fill_cache(physical_page, &data);
			_eeprom_emulator_nvm_commit_cache(physical_page);

			/* Increment the logical EEPROM page address now that the current
			 * address' page has been initialized */
			logical_page++;
		}
	}
}

/**
 * \brief Check if a row is a full row
 *  because the page is a invalid page, so if two pages have data,
 *  it is the full row.
 *
 *  \param[in]  phy_page  Physical page that in a row
 */
static bool _eeprom_emulator_is_full_row(uint16_t phy_page)
{
	if((_eeprom_instance.flash[phy_page].header.logical_page
		== _eeprom_instance.flash[phy_page+2].header.logical_page)
		|| (_eeprom_instance.flash[phy_page+1].header.logical_page
		== _eeprom_instance.flash[phy_page+2].header.logical_page )) {
		return true;
	} else {
		return false;
	}
}

/**
 * \brief Erase one invalid page according to two invalid physical page
 *
 *  \param[in]  pre_phy_page  One physical invalid page
 *  \param[in]  next_phy_page Another physical invalid page
 */
static void _eeprom_emulator_erase_invalid_page(uint16_t pre_phy_page,uint16_t next_phy_page)
{
 	/* Erase the old/full row*/
	if(_eeprom_emulator_is_full_row(pre_phy_page)) {
		 _eeprom_emulator_nvm_erase_row(pre_phy_page/4);
	} else {
		_eeprom_emulator_nvm_erase_row(next_phy_page/4);
	}
}

/**
 * \brief Check if there exist rows with same logical pages due to power drop
 *  when writing or erasing page.
 *  when existed same logical page, the old(full) row will be erased.
 */
static void _eeprom_emulator_check_logical_page(void)
{
	uint16_t i = 0, j = 0;
	for (i = 0; i < _eeprom_instance.physical_pages; i=i+4) {

		uint16_t pre_logical_page = _eeprom_instance.flash[i].header.logical_page;
		if( pre_logical_page == EEPROM_INVALID_PAGE_NUMBER) {
			continue;
		}

		for (j = NVMCTRL_ROW_PAGES+i; j < _eeprom_instance.physical_pages; j=j+4) {

			if (j == EEPROM_MASTER_PAGE_NUMBER) {
				continue;
			}
			uint16_t next_logical_page = _eeprom_instance.flash[j].header.logical_page;
			if( next_logical_page == EEPROM_INVALID_PAGE_NUMBER) {
				continue;
			}

			if(pre_logical_page == next_logical_page) {
				/* Found invalid logical page and erase it */
				_eeprom_emulator_erase_invalid_page(i,j);
			}
		}
	}
}


/**
 * \brief Creates a map in SRAM to translate logical EEPROM pages to physical FLASH pages.
 */
static void _eeprom_emulator_update_page_mapping(void)
{
	/* Check if exists invalid logical page */
	_eeprom_emulator_check_logical_page();

	/* Scan through all physical pages, to map physical and logical pages */
	for (uint16_t c = 0; c < _eeprom_instance.physical_pages; c++) {
		if (c == EEPROM_MASTER_PAGE_NUMBER) {
			continue;
		}

		/* Read in the logical page stored in the current physical page */
		uint16_t logical_page = _eeprom_instance.flash[c].header.logical_page;

		/* If the logical page number is valid, add it to the mapping */
		if ((logical_page != EEPROM_INVALID_PAGE_NUMBER) &&
				(logical_page < _eeprom_instance.logical_pages)) {
			_eeprom_instance.page_map[logical_page] = c;
		}
	}

	/* Use an invalid page number as the spare row until a valid one has been
	 * found */
	_eeprom_instance.spare_row = EEPROM_INVALID_ROW_NUMBER;

	/* Scan through all physical rows, to find an erased row to use as the
	 * spare */
	for (uint16_t c = 0; c < (_eeprom_instance.physical_pages / NVMCTRL_ROW_PAGES); c++) {
		bool spare_row_found = true;

		/* Look through pages within the row to see if they are all erased */
		for (uint8_t c2 = 0; c2 < NVMCTRL_ROW_PAGES; c2++) {
			uint16_t physical_page = (c * NVMCTRL_ROW_PAGES) + c2;

			if (physical_page == EEPROM_MASTER_PAGE_NUMBER) {
				continue;
			}

			if (_eeprom_instance.flash[physical_page].header.logical_page !=
					EEPROM_INVALID_PAGE_NUMBER) {
				spare_row_found = false;
			}
		}

		/* If we've now found the spare row, store it and abort the search */
		if (spare_row_found == true) {
			_eeprom_instance.spare_row = c;
			break;
		}
	}
}

/**
 * \brief Finds the next free page in the given row if one is available.
 *
 * \param[in]  start_physical_page  Physical FLASH page index of the row to
 *                                  search
 * \param[out] free_physical_page   Index of the physical FLASH page that is
 *                                  currently free (if one was found)
 *
 * \return Whether a free page was found in the specified row.
 *
 * \retval \c true   If a free page was found
 * \retval \c false  If the specified row was full and needs an erase
 */
static bool _eeprom_emulator_is_page_free_on_row(
		const uint8_t start_physical_page,
		uint8_t *const free_physical_page)
{
	/* Convert physical page number to a FLASH row and page within the row */
	uint8_t row         = (start_physical_page / NVMCTRL_ROW_PAGES);
	uint8_t page_in_row = (start_physical_page % NVMCTRL_ROW_PAGES);

	/* Look in the current row for a page that isn't currently used */
	for (uint8_t c = page_in_row; c < NVMCTRL_ROW_PAGES; c++) {
		/* Calculate the page number for the current page being examined */
		uint8_t page = (row * NVMCTRL_ROW_PAGES) + c;

		/* If the page is free, pass it to the caller and exit */
		if (_eeprom_instance.flash[page].header.logical_page ==
				EEPROM_INVALID_PAGE_NUMBER) {
			*free_physical_page = page;
			return true;
		}
	}

	/* No free page in the current row was found */
	return false;
}

/**
 * \brief Moves data from the specified logical page to the spare row.
 *
 * Moves the contents of the specified row into the spare row, so that the
 * original row can be erased and re-used. The contents of the given logical
 * page is replaced with a new buffer of data.
 *
 * \param[in] row_number    Physical row to examine
 * \param[in] logical_page  Logical EEPROM page number in the row to update
 * \param[in] data          New data to replace the old in the logical page
 *
 * \return Status code indicating the status of the operation.
 */
static enum status_code _eeprom_emulator_move_data_to_spare(
		const uint8_t row_number,
		const uint8_t logical_page,
		const uint8_t *const data)
{
	enum status_code error_code = STATUS_OK;
	struct {
		uint8_t logical_page;
		uint8_t physical_page;
	} page_trans[2];

	const struct _eeprom_page *row_data =
			(struct _eeprom_page *)&_eeprom_instance.flash[row_number * NVMCTRL_ROW_PAGES];

	/* There should be two logical pages of data in each row, possibly with
	 * multiple revisions (right-most version is the newest). Start by assuming
	 * the left-most two pages contain the newest page revisions. */
	page_trans[0].logical_page  = row_data[0].header.logical_page;
	page_trans[0].physical_page = (row_number * NVMCTRL_ROW_PAGES);

	page_trans[1].logical_page  = row_data[1].header.logical_page;
	page_trans[1].physical_page = (row_number * NVMCTRL_ROW_PAGES) + 1;

	/* Look for newer revisions of the two logical pages stored in the row */
	for (uint8_t c = 0; c < 2; c++) {
		/* Look through the remaining pages in the row for any newer revisions */
		for (uint8_t c2 = 2; c2 < NVMCTRL_ROW_PAGES; c2++) {
			if (page_trans[c].logical_page == row_data[c2].header.logical_page) {
				page_trans[c].physical_page =
						(row_number * NVMCTRL_ROW_PAGES) + c2;
			}
		}
	}

	/* Need to move both saved logical pages stored in the same row */
	for (uint8_t c = 0; c < 2; c++) {
		/* Find the physical page index for the new spare row pages */
		uint32_t new_page =
				((_eeprom_instance.spare_row * NVMCTRL_ROW_PAGES) + c);

		/* Commit any cached data to physical non-volatile memory */
		eeprom_emulator_commit_page_buffer();

		/* Check if we we are looking at the page the calling function wishes
		 * to change during the move operation */
		if (logical_page == page_trans[c].logical_page) {
			/* Fill out new (updated) logical page's header in the cache */
			_eeprom_instance.cache.header.logical_page = logical_page;

			/* Write data to SRAM cache */
			memcpy(_eeprom_instance.cache.data, data, EEPROM_PAGE_SIZE);
		} else {
			/* Copy existing EEPROM page to cache buffer wholesale */
			_eeprom_emulator_nvm_read_page(
					page_trans[c].physical_page, &_eeprom_instance.cache);
		}

		/* Fill the physical NVM buffer with the new data so that it can be
		 * quickly committed in the future if needed due to a low power
		 * condition */
		_eeprom_emulator_nvm_fill_cache(new_page, &_eeprom_instance.cache);

		/* Update the page map with the new page location and indicate that
		 * the cache now holds new data */
		_eeprom_instance.page_map[page_trans[c].logical_page] = new_page;
		_eeprom_instance.cache_active = true;
	}

	/* Erase the row that was moved and set it as the new spare row */
	_eeprom_emulator_nvm_erase_row(row_number);

	/* Keep the index of the new spare row */
	_eeprom_instance.spare_row = row_number;

	return error_code;
}

/**
 * \brief Create master emulated EEPROM management page.
 *
 * Creates a new master page in emulated EEPROM, giving information on the
 * emulator used to store the EEPROM data.
 */
static void _eeprom_emulator_create_master_page(void)
{
	const uint32_t magic_key[] = EEPROM_MAGIC_KEY;

	struct _eeprom_master_page master_page;
	memset(&master_page, 0xFF, sizeof(master_page));

	/* Fill out the magic key header to indicate an initialized master page */
	for (uint8_t c = 0; c < EEPROM_MAGIC_KEY_COUNT; c++) {
		master_page.magic_key[c] = magic_key[c];
	}

	/* Update master header with version information of this emulator */
	master_page.emulator_id   = EEPROM_EMULATOR_ID;
	master_page.major_version = EEPROM_MAJOR_VERSION;
	master_page.minor_version = EEPROM_MINOR_VERSION;
	master_page.revision      = EEPROM_REVISION;

	_eeprom_emulator_nvm_erase_row(
			EEPROM_MASTER_PAGE_NUMBER / NVMCTRL_ROW_PAGES);

	/* Write the new master page data to physical memory */
	_eeprom_emulator_nvm_fill_cache(EEPROM_MASTER_PAGE_NUMBER, &master_page);
	_eeprom_emulator_nvm_commit_cache(EEPROM_MASTER_PAGE_NUMBER);
}

/**
 * \brief Verify the contents of a master EEPROM page.
 *
 * Verify the contents of a master EEPROM page to ensure that it contains the
 * correct information for this version of the EEPROM emulation service.
 *
 * \retval STATUS_OK              Given master page contents is valid
 * \retval STATUS_ERR_BAD_FORMAT  Master page contents was invalid
 * \retval STATUS_ERR_IO          Master page indicates the data is incompatible
 *                                with this version of the EEPROM emulator
 */
static enum status_code _eeprom_emulator_verify_master_page(void)
{
	const uint32_t magic_key[] = EEPROM_MAGIC_KEY;
	struct _eeprom_master_page master_page;

	/* Copy the master page to the RAM buffer so that it can be inspected */
	_eeprom_emulator_nvm_read_page(EEPROM_MASTER_PAGE_NUMBER, &master_page);

	/* Verify magic key is correct in the master page header */
	for (uint8_t c = 0; c < EEPROM_MAGIC_KEY_COUNT; c++) {
		if (master_page.magic_key[c] != magic_key[c]) {
			return STATUS_ERR_BAD_FORMAT;
		}
	}

	/* Verify emulator ID in header to ensure the same scheme is used */
	if (master_page.emulator_id   != EEPROM_EMULATOR_ID) {
		return STATUS_ERR_IO;
	}

	/* Verify major version in header to ensure the same version is used */
	if (master_page.major_version != EEPROM_MAJOR_VERSION) {
		return STATUS_ERR_IO;
	}

	/* Verify minor version in header to ensure the same version is used */
	if (master_page.minor_version != EEPROM_MINOR_VERSION) {
		return STATUS_ERR_IO;
	}

	/* Don't verify revision number - same major/minor is considered enough
	 * to ensure the stored data is compatible. */

	return STATUS_OK;
}


/**
 * \brief Retrieves the parameters of the EEPROM Emulator memory layout.
 *
 * Retrieves the configuration parameters of the EEPROM Emulator, after it has
 * been initialized.
 *
 * \param[out] parameters  EEPROM Emulator parameter struct to fill
 *
 * \return Status of the operation.
 *
 * \retval STATUS_OK                    If the emulator parameters were retrieved
 *                                      successfully
 * \retval STATUS_ERR_NOT_INITIALIZED   If the EEPROM Emulator is not initialized
 */
enum status_code eeprom_emulator_get_parameters(
	struct eeprom_emulator_parameters *const parameters)
{
	if (_eeprom_instance.initialized == false) {
		return STATUS_ERR_NOT_INITIALIZED;
	}

	parameters->page_size              = EEPROM_PAGE_SIZE;
	parameters->eeprom_number_of_pages = _eeprom_instance.logical_pages;

	return STATUS_OK;
}

/**
 * \brief Initializes the EEPROM Emulator service.
 *
 * Initializes the emulated EEPROM memory space; if the emulated EEPROM memory
 * has not been previously initialized, it will need to be explicitly formatted
 * via \ref eeprom_emulator_erase_memory(). The EEPROM memory space will \b not
 * be automatically erased by the initialization function, so that partial data
 * may be recovered by the user application manually if the service is unable to
 * initialize successfully.
 *
 * \return Status code indicating the status of the operation.
 *
 * \retval STATUS_OK              EEPROM emulation service was successfully
 *                                initialized
 * \retval STATUS_ERR_NO_MEMORY   No EEPROM section has been allocated in the
 *                                device
 * \retval STATUS_ERR_BAD_FORMAT  Emulated EEPROM memory is corrupt or not
 *                                formatted
 * \retval STATUS_ERR_IO          EEPROM data is incompatible with this version
 *                                or scheme of the EEPROM emulator
 */
enum status_code eeprom_emulator_init(void)
{
	enum status_code error_code = STATUS_OK;
	struct nvm_config config;
	struct nvm_parameters parameters;

	/* Retrieve the NVM controller configuration - enable manual page writing
	 * mode so that the emulator has exclusive control over page writes to
	 * allow for caching */
	nvm_get_config_defaults(&config);
	config.manual_page_write = true;

	/* Apply new NVM configuration */
	do {
		error_code = nvm_set_config(&config);
	} while (error_code == STATUS_BUSY);

	/* Get the NVM controller configuration parameters */
	nvm_get_parameters(&parameters);

	/* Ensure the device fuses are configured for at least one master page row,
	 * one user EEPROM data row and one spare row */
	if (parameters.eeprom_number_of_pages < (3 * NVMCTRL_ROW_PAGES)) {
		return STATUS_ERR_NO_MEMORY;
	}

	/* Configure the EEPROM instance physical and logical number of pages:
	 *  - One row is reserved for the master page
	 *  - One row is reserved for the spare row
	 *  - Two logical pages can be stored in one physical row
	 */
	_eeprom_instance.physical_pages =
			parameters.eeprom_number_of_pages;
	_eeprom_instance.logical_pages  =
			(parameters.eeprom_number_of_pages - (2 * NVMCTRL_ROW_PAGES)) / 2;

	/* Configure the EEPROM instance starting physical address in FLASH and
	 * pre-compute the index of the first page in FLASH used for EEPROM */
	_eeprom_instance.flash =
			(void*)(FLASH_SIZE -
			((uint32_t)_eeprom_instance.physical_pages * NVMCTRL_PAGE_SIZE));

	/* Clear EEPROM page write cache on initialization */
	_eeprom_instance.cache_active = false;

	/* Scan physical memory and re-create logical to physical page mapping
	 * table to locate logical pages of EEPROM data in physical FLASH */
	_eeprom_emulator_update_page_mapping();

	/* Could not find spare row - abort as the memory appears to be corrupt */
	if (_eeprom_instance.spare_row == EEPROM_INVALID_ROW_NUMBER) {
		return STATUS_ERR_BAD_FORMAT;
	}

	/* Verify that the master page contains valid data for this service */
	error_code = _eeprom_emulator_verify_master_page();
	if (error_code != STATUS_OK) {
		return error_code;
	}

	/* Mark initialization as complete */
	_eeprom_instance.initialized = true;

	return error_code;
}

/**
 * \brief Erases the entire emulated EEPROM memory space.
 *
 * Erases and re-initializes the emulated EEPROM memory space, destroying any
 * existing data.
 */
void eeprom_emulator_erase_memory(void)
{
	/* Create new EEPROM memory block in EEPROM emulation section */
	_eeprom_emulator_format_memory();

	/* Write EEPROM emulation master block */
	_eeprom_emulator_create_master_page();

	/* Map the newly created EEPROM memory block */
	_eeprom_emulator_update_page_mapping();
}

/**
 * \brief Writes a page of data to an emulated EEPROM memory page.
 *
 * Writes an emulated EEPROM page of data to the emulated EEPROM memory space.
 *
 * \note Data stored in pages may be cached in volatile RAM memory; to commit
 *       any cached data to physical non-volatile memory, the
 *       \ref eeprom_emulator_commit_page_buffer() function should be called.
 *
 * \param[in] logical_page  Logical EEPROM page number to write to
 * \param[in] data          Pointer to the data buffer containing source data to
 *                          write
 *
 * \return Status code indicating the status of the operation.
 *
 * \retval STATUS_OK                    If the page was successfully read
 * \retval STATUS_ERR_NOT_INITIALIZED   If the EEPROM emulator is not initialized
 * \retval STATUS_ERR_BAD_ADDRESS       If an address outside the valid emulated
 *                                      EEPROM memory space was supplied
 */
enum status_code eeprom_emulator_write_page(
		const uint8_t logical_page,
		const uint8_t *const data)
{
	/* Ensure the emulated EEPROM has been initialized first */
	if (_eeprom_instance.initialized == false) {
		return STATUS_ERR_NOT_INITIALIZED;
	}

	/* Make sure the write address is within the allowable address space */
	if (logical_page >= _eeprom_instance.logical_pages) {
		return STATUS_ERR_BAD_ADDRESS;
	}

	/* Check if the cache is active and the currently cached page is not the
	 * page that is being written (if not, we need to commit and cache the new
	 * page) */
	if ((_eeprom_instance.cache_active == true) &&
			(_eeprom_instance.cache.header.logical_page != logical_page)) {
		/* Commit the currently cached data buffer to non-volatile memory */
		eeprom_emulator_commit_page_buffer();
	}

	/* Check if we have space in the current page location's physical row for
	 * a new version, and if so get the new page index */
	uint8_t new_page = 0;
	bool page_spare  = _eeprom_emulator_is_page_free_on_row(
			_eeprom_instance.page_map[logical_page], &new_page);

	/* Check if the current row is full, and we need to swap it out with a
	 * spare row */
	if (page_spare == false) {
		/* Move the other page we aren't writing that is stored in the same
		 * page to the new row, and replace the old current page with the
		 * new page contents (cache is updated to match) */
		_eeprom_emulator_move_data_to_spare(
				_eeprom_instance.page_map[logical_page] / NVMCTRL_ROW_PAGES,
				logical_page,
				data);

		/* New data is now written and the cache is updated, exit */
		return STATUS_OK;
	}

	/* Update the page cache header section with the new page header */
	_eeprom_instance.cache.header.logical_page = logical_page;

	/* Update the page cache contents with the new data */
	memcpy(&_eeprom_instance.cache.data,
			data,
			EEPROM_PAGE_SIZE);

	/* Fill the physical NVM buffer with the new data so that it can be quickly
	 * committed in the future if needed due to a low power condition */
	_eeprom_emulator_nvm_fill_cache(new_page, &_eeprom_instance.cache);

	/* Update the cache parameters and mark the cache as active */
	_eeprom_instance.page_map[logical_page] = new_page;
	barrier(); // Enforce ordering to prevent incorrect cache state
	_eeprom_instance.cache_active           = true;

	return STATUS_OK;
}

/**
 * \brief Reads a page of data from an emulated EEPROM memory page.
 *
 * Reads an emulated EEPROM page of data from the emulated EEPROM memory space.
 *
 * \param[in]  logical_page  Logical EEPROM page number to read from
 * \param[out] data          Pointer to the destination data buffer to fill
 *
 * \return Status code indicating the status of the operation.
 *
 * \retval STATUS_OK                    If the page was successfully read
 * \retval STATUS_ERR_NOT_INITIALIZED   If the EEPROM emulator is not initialized
 * \retval STATUS_ERR_BAD_ADDRESS       If an address outside the valid emulated
 *                                      EEPROM memory space was supplied
 */
enum status_code eeprom_emulator_read_page(
		const uint8_t logical_page,
		uint8_t *const data)
{
	/* Ensure the emulated EEPROM has been initialized first */
	if (_eeprom_instance.initialized == false) {
		return STATUS_ERR_NOT_INITIALIZED;
	}

	/* Make sure the read address is within the allowable address space */
	if (logical_page >= _eeprom_instance.logical_pages) {
		return STATUS_ERR_BAD_ADDRESS;
	}

	/* Check if the page to read is currently cached (and potentially out of
	 * sync/newer than the physical memory) */
	if ((_eeprom_instance.cache_active == true) &&
		 (_eeprom_instance.cache.header.logical_page == logical_page)) {
		/* Copy the potentially newer cached data into the user buffer */
		memcpy(data, _eeprom_instance.cache.data, EEPROM_PAGE_SIZE);
	} else {
		struct _eeprom_page temp;

		/* Copy the data from non-volatile memory into the temporary buffer */
		_eeprom_emulator_nvm_read_page(
				_eeprom_instance.page_map[logical_page], &temp);

		/* Copy the data portion of the read page to the user's buffer */
		memcpy(data, temp.data, EEPROM_PAGE_SIZE);
	}

	return STATUS_OK;
}

/**
 * \brief Writes a buffer of data to the emulated EEPROM memory space.
 *
 * Writes a buffer of data to a section of emulated EEPROM memory space. The
 * source buffer may be of any size, and the destination may lie outside of an
 * emulated EEPROM page boundary.
 *
 * \note Data stored in pages may be cached in volatile RAM memory; to commit
 *       any cached data to physical non-volatile memory, the
 *       \ref eeprom_emulator_commit_page_buffer() function should be called.
 *
 * \param[in] offset  Starting byte offset to write to, in emulated EEPROM
 *                    memory space
 * \param[in] data    Pointer to the data buffer containing source data to write
 * \param[in] length  Length of the data to write, in bytes
 *
 * \return Status code indicating the status of the operation.
 *
 * \retval STATUS_OK                    If the page was successfully read
 * \retval STATUS_ERR_NOT_INITIALIZED   If the EEPROM emulator is not initialized
 * \retval STATUS_ERR_BAD_ADDRESS       If an address outside the valid emulated
 *                                      EEPROM memory space was supplied
 */
enum status_code eeprom_emulator_write_buffer(
		const uint16_t offset,
		const uint8_t *const data,
		const uint16_t length)
{
	enum status_code error_code = STATUS_OK;
	uint8_t buffer[EEPROM_PAGE_SIZE];
	uint8_t logical_page = offset / EEPROM_PAGE_SIZE;
	uint16_t c = offset;
	/* Keep track of whether the currently updated page has been written */
	bool page_dirty = false;
	/** Perform the initial page read if necessary*/
	if ((offset % EEPROM_PAGE_SIZE) || length < EEPROM_PAGE_SIZE) {
		error_code = eeprom_emulator_read_page(logical_page, buffer);

		if (error_code != STATUS_OK) {
			return error_code;
		}
	}

	/* To avoid entering into the initial if in the loop the first time */
	if ((offset % EEPROM_PAGE_SIZE) == 0) {
		buffer[c % EEPROM_PAGE_SIZE] = data[c - offset];
		page_dirty = true;
		c=c+1;
	}

	/* Write the specified data to the emulated EEPROM memory space */
	for (; c < (length + offset); c++) {
		/* Check if we have written up to a new EEPROM page boundary */
		if ((c % EEPROM_PAGE_SIZE) == 0) {
			/* Write the current page to non-volatile memory from the temporary
			 * buffer */
			error_code = eeprom_emulator_write_page(logical_page, buffer);
			page_dirty = false;

			if (error_code != STATUS_OK) {
				break;
			}

			/* Increment the page number we are looking at */
			logical_page++;

			/* Read the next page from non-volatile memory into the temporary
			 * buffer in case of a partial page write */
			error_code = eeprom_emulator_read_page(logical_page, buffer);

			if (error_code != STATUS_OK) {
				return error_code;
			}
		}
		/* Copy the next byte of data from the user's buffer to the temporary
		 * buffer */
		buffer[c % EEPROM_PAGE_SIZE] = data[c - offset];
		page_dirty = true;
	}

	/* If the current page is dirty, write it */
	if (page_dirty) {
		error_code = eeprom_emulator_write_page(logical_page, buffer);
	}

	return error_code;
}

/**
 * \brief Reads a buffer of data from the emulated EEPROM memory space.
 *
 * Reads a buffer of data from a section of emulated EEPROM memory space. The
 * destination buffer may be of any size, and the source may lie outside of an
 * emulated EEPROM page boundary.
 *
 * \param[in]  offset  Starting byte offset to read from, in emulated EEPROM
 *                     memory space
 * \param[out] data    Pointer to the data buffer containing source data to read
 * \param[in]  length  Length of the data to read, in bytes
 *
 * \return Status code indicating the status of the operation.
 *
 * \retval STATUS_OK                    If the page was successfully read
 * \retval STATUS_ERR_NOT_INITIALIZED   If the EEPROM emulator is not initialized
 * \retval STATUS_ERR_BAD_ADDRESS       If an address outside the valid emulated
 *                                      EEPROM memory space was supplied
 */
enum status_code eeprom_emulator_read_buffer(
		const uint16_t offset,
		uint8_t *const data,
		const uint16_t length)
{
	enum status_code error_code;
	uint8_t buffer[EEPROM_PAGE_SIZE];
	uint8_t logical_page = offset / EEPROM_PAGE_SIZE;
	uint16_t c = offset;

	/** Perform the initial page read  */
	error_code = eeprom_emulator_read_page(logical_page, buffer);
	if (error_code != STATUS_OK) {
		return error_code;
	}

	/* To avoid entering into the initial if in the loop the first time */
	if ((offset % EEPROM_PAGE_SIZE) == 0) {
		data[0] = buffer[0];
		c=c+1;
	}

	/* Read in the specified data from the emulated EEPROM memory space */
	for (; c < (length + offset); c++) {
		/* Check if we have read up to a new EEPROM page boundary */
		if ((c % EEPROM_PAGE_SIZE) == 0) {
			/* Increment the page number we are looking at */
			logical_page++;

			/* Read the next page from non-volatile memory into the temporary
			 * buffer */
			error_code = eeprom_emulator_read_page(logical_page, buffer);

			if (error_code != STATUS_OK) {
				return error_code;
			}
		}

		/* Copy the next byte of data from the temporary buffer to the user's
		 * buffer */
		data[c - offset] = buffer[c % EEPROM_PAGE_SIZE];
	}

	return error_code;
}

/**
 * \brief Commits any cached data to physical non-volatile memory.
 *
 * Commits the internal SRAM caches to physical non-volatile memory, to ensure
 * that any outstanding cached data is preserved. This function should be called
 * prior to a system reset or shutdown to prevent data loss.
 *
 * \note This should be the first function executed in a BOD33 Early Warning
 *       callback to ensure that any outstanding cache data is fully written to
 *       prevent data loss.
 *
 *
 * \note This function should also be called before using the NVM controller
 *       directly in the user-application for any other purposes to prevent
 *       data loss.
 *
 * \return Status code indicating the status of the operation.
 */
enum status_code eeprom_emulator_commit_page_buffer(void)
{
	enum status_code error_code = STATUS_OK;

	/* If cache is inactive, no need to commit anything to physical memory */
	if (_eeprom_instance.cache_active == false) {
		return STATUS_OK;
	}

	uint8_t cached_logical_page = _eeprom_instance.cache.header.logical_page;

	/* Perform the page write to commit the NVM page buffer to FLASH */
	_eeprom_emulator_nvm_commit_cache(
			_eeprom_instance.page_map[cached_logical_page]);

	barrier(); // Enforce ordering to prevent incorrect cache state
	_eeprom_instance.cache_active = false;

	return error_code;
}
