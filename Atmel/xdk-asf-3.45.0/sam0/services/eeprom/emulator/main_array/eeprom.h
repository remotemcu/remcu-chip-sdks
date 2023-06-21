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
#ifndef EEPROM_H_INCLUDED
#define EEPROM_H_INCLUDED

/**
 * \defgroup asfdoc_sam0_eeprom_group SAM EEPROM Emulator (EEPROM) Service
 *
 * This driver for Atmel&reg; | SMART ARM&reg;-based microcontrollers provides an emulated EEPROM memory space in
 * the device's FLASH memory, for the storage and retrieval of user-application
 * configuration data into and out of non-volatile memory.
 *
 * The following peripherals are used by this module:
 *  - NVM (Non-Volatile Memory Controller)
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM D20/D21
 *  - Atmel | SMART SAM R21
 *  - Atmel | SMART SAM D10/D11
 *  - Atmel | SMART SAM L21/L22
 *  - Atmel | SMART SAM C20/C21
 *  - Atmel | SMART SAM DA1
 *  - Atmel | SMART SAM HA1
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_sam0_eeprom_prerequisites
 *  - \ref asfdoc_sam0_eeprom_module_overview
 *  - \ref asfdoc_sam0_eeprom_special_considerations
 *  - \ref asfdoc_sam0_eeprom_extra_info
 *  - \ref asfdoc_sam0_eeprom_examples
 *  - \ref asfdoc_sam0_eeprom_api_overview
 *
 *
 * \section asfdoc_sam0_eeprom_prerequisites Prerequisites
 *
 * The SAM device fuses must be configured via an external programmer or
 * debugger, so that an EEPROM section is allocated in the main NVM flash
 * memory contents. If a NVM section is not allocated for the EEPROM emulator,
 * or if insufficient space for the emulator is reserved, the module will fail
 * to initialize.
 *
 *
 * \section asfdoc_sam0_eeprom_module_overview Module Overview
 *
 * As the SAM devices do not contain any physical EEPROM memory, the storage
 * of non-volatile user data is instead emulated using a special section of the
 * device's main FLASH memory. The use of FLASH memory technology over EEPROM
 * presents several difficulties over true EEPROM memory; data must be written
 * as a number of physical memory pages (of several bytes each) rather than
 * being individually byte addressable, and entire rows of FLASH must be erased
 * before new data may be stored. To help abstract these characteristics away
 * from the user application an emulation scheme is implemented to present a
 * more user-friendly API for data storage and retrieval.
 *
 * This module provides an EEPROM emulation layer on top of the device's
 * internal NVM controller, to provide a standard interface for the reading and
 * writing of non-volatile configuration data. This data is placed into the
 * EEPROM emulated section of the device's main FLASH memory storage section,
 * the size of which is configured using the device's fuses. Emulated EEPROM is
 * exempt from the usual device NVM region lock bits, so that it may be read
 * from or written to at any point in the user application.
 *
 * There are many different algorithms that may be employed for EEPROM emulation
 * using FLASH memory, to tune the write and read latencies, RAM usage, wear
 * levelling and other characteristics. As a result, multiple different emulator
 * schemes may be implemented, so that the most appropriate scheme for a
 * specific application's requirements may be used.
 *
 * \subsection asfdoc_sam0_eeprom_module_overview_implementation Implementation Details
 * The following information is relevant for <b>EEPROM Emulator scheme 1,
 * version 1.0.0</b>, as implemented by this module. Other revisions or
 * emulation schemes may vary in their implementation details and may have
 * different wear-leveling, latency, and other characteristics.
 *
 * \subsubsection asfdoc_sam0_eeprom_module_overview_implementation_ec Emulator Characteristics
 * This emulator is designed for <b>best reliability, with a good balance of
 * available storage and write-cycle limits</b>. It is designed to ensure that
 * page data is automatically updated so that in the event of a failed update the
 * previous data is not lost (when used correctly). With the exception of a
 * system reset with data cached to the internal write-cache buffer, at most
 * only the latest write to physical non-volatile memory will be lost in the
 * event of a failed write.
 *
 * This emulator scheme is tuned to give best write-cycle longevity when writes
 * are confined to the same logical EEPROM page (where possible) and when writes
 * across multiple logical EEPROM pages are made in a linear fashion through the
 * entire emulated EEPROM space.
 *
 * \subsubsection asfdoc_sam0_eeprom_module_overview_implementation_pf Physical Memory
 * The SAM non-volatile FLASH is divided into a number of physical rows, each
 * containing four identically sized flash pages. Pages may be read or written
 * to individually, however pages must be erased before being reprogrammed and
 * the smallest granularity available for erasure is one single row.
 *
 * This discrepancy results in the need for an emulator scheme that is able to
 * handle the versioning and moving of page data to different physical rows as
 * needed, erasing old rows ready for re-use by future page write operations.
 *
 * Physically, the emulated EEPROM segment is located at the end of the physical
 * FLASH memory space, as shown in
 * \ref asfdoc_sam0_eeprom_module_mem_layout "the figure below".
 *
 * \anchor asfdoc_sam0_eeprom_module_mem_layout
 * \dot
 * digraph memory_layout {
 *  size="5,5"
 *  node [shape=plaintext]
 *  memory [label=<
 *   <table border="0" cellborder="1" cellspacing="0" >
 *    <tr>
 *     <td align="right" border="0"> End of NVM Memory </td>
 *     <td rowspan="3" align="center"> Reserved EEPROM Section </td>
 *    </tr>
 *    <tr>
 *     <td align="right" border="0"> </td>
 *    </tr>
 *    <tr>
 *     <td align="right" border="0"> Start of EEPROM Memory </td>
 *    </tr>
 *    <tr>
 *     <td align="right" border="0"> End of Application Memory </td>
 *     <td rowspan="3" align="center"> Application Section </td>
 *    </tr>
 *    <tr>
 *     <td height="300" align="right" border="0"> </td>
 *    </tr>
 *    <tr>
 *     <td align="right" border="0"> Start of Application Memory </td>
 *    </tr>
 *    <tr>
 *     <td align="right" border="0"> End of Bootloader Memory </td>
 *     <td rowspan="3" align="center"> BOOT Section </td>
 *    </tr>
 *    <tr>
 *     <td align="right" border="0"> </td>
 *    </tr>
 *    <tr>
 *     <td align="right" border="0"> Start of NVM Memory</td>
 *    </tr>
 *   </table>
 *  >]
 * }
 * \enddot
 *
 * \subsubsection asfdoc_sam0_eeprom_module_overview_implementation_mp Master Row
 * One physical FLASH row at the end of the emulated EEPROM memory space is
 * reserved for use by the emulator to store configuration data. The master row
 * is not user-accessible, and is reserved solely for internal use by the
 * emulator.
 *
 * \subsubsection asfdoc_sam0_eeprom_module_overview_implementation_sr Spare Row
 * As data needs to be preserved between row erasures, a single FLASH row is kept
 * unused to act as destination for copied data when a write request is made to
 * an already full row. When the write request is made, any logical pages of
 * data in the full row that need to be preserved are written to the spare row
 * along with the new (updated) logical page data, before the old row is erased
 * and marked as the new spare.
 *
 * \subsubsection asfdoc_sam0_eeprom_module_overview_implementation_rc Row Contents
 * Each physical FLASH row initially stores the contents of two logical EEPROM
 * memory pages. This halves the available storage space for the emulated EEPROM
 * but reduces the overall number of row erases that are required, by reserving
 * two pages within each row for updated versions of the logical page contents.
 * See \ref asfdoc_sam0_eeprom_init_layout "here" for a visual layout of the
 * EEPROM Emulator physical memory.
 *
 * As logical pages within a physical row are updated, the new data is filled
 * into the remaining unused pages in the row. Once the entire row is full, a
 * new write request will copy the logical page not being written to in the
 * current row to the spare row with the new (updated) logical page data, before
 * the old row is erased.
 *
 * This system allows for the same logical page to be updated up to three times
 * into physical memory before a row erasure procedure is needed. In the case of
 * multiple versions of the same logical EEPROM page being stored in the same
 * physical row, the right-most (highest physical FLASH memory page address)
 * version is considered to be the most current.
 *
 * \subsubsection asfdoc_sam0_eeprom_module_overview_implementation_wc Write Cache
 * As a typical EEPROM use case is to write to multiple sections of the same
 * EEPROM page sequentially, the emulator is optimized with a single logical
 * EEPROM page write cache to buffer writes before they are written to the
 * physical backing memory store. The cache is automatically committed when a
 * new write request to a different logical EEPROM memory page is requested, or
 * when the user manually commits the write cache.
 *
 * Without the write cache, each write request to an EEPROM memory page would
 * require a full page write, reducing the system performance and significantly
 * reducing the lifespan of the non-volatile memory.
 *
 * \subsection asfdoc_sam0_eeprom_special_considerations_memlayout Memory Layout
 * A single logical EEPROM page is physically stored as the page contents and a
 * header inside a single physical FLASH page, as shown in
 * \ref asfdoc_sam0_eeprom_page_layout "the following figure".
 *
 * \anchor asfdoc_sam0_eeprom_page_layout
 * \image html page_layout.svg "Internal Layout of An Emulated EEPROM Page"
 *
 * Within the EEPROM memory reservation section at the top of the NVM memory
 * space, this emulator will produce the layout as shown in
 * \ref asfdoc_sam0_eeprom_init_layout "the figure below" when initialized for
 * the first time.
 *
 * \anchor asfdoc_sam0_eeprom_init_layout
 * \image html init_layout.svg "Initial Physical Layout of The Emulated EEPROM Memory"
 *
 * When an EEPROM page needs to be committed to physical memory, the next free
 * FLASH page in the same row will be chosen - this makes recovery simple, as the
 * right-most version of a logical page in a row is considered the most current.
 * With four pages to a physical NVM row, this allows for up to three updates to
 * the same logical page to be made before an erase is needed.
 * \ref asfdoc_sam0_eeprom_page_write1 "The figure below" shows the result of
 * the user writing an updated version of logical EEPROM page <tt>N-1</tt> to
 * the physical memory.
 *
 * \anchor asfdoc_sam0_eeprom_page_write1
 * \image html nm1_page_write.svg "First Write to Logical EEPROM Page N-1"
 *
 * A second write of the same logical EEPROM page results in the layout shown
 * in \ref asfdoc_sam0_eeprom_page_write2 "the figure below".
 *
 * \anchor asfdoc_sam0_eeprom_page_write2
 * \image html nm1_page_write2.svg "Second Write to Logical EEPROM Page N-1"
 *
 * A third write of the same logical page requires that the EEPROM emulator
 * erase the row, as it has become full. Prior to this, the contents of the
 * unmodified page in the same row as the page being updated will be copied into
 * the spare row, along with the new version of the page being updated. The old
 * (full) row is then erased, resulting in the layout shown in
 * \ref asfdoc_sam0_eeprom_page_write3 "the figure below".
 *
 * \anchor asfdoc_sam0_eeprom_page_write3
 * \image html nm1_page_write3.svg "Third Write to Logical EEPROM Page N-1"
 *
 *
 * \section asfdoc_sam0_eeprom_special_considerations Special Considerations
 *
 * \subsection asfdoc_sam0_eeprom_special_considerations_nvm_config NVM Controller Configuration
 * The EEPROM Emulator service will initialize the NVM controller as part of its
 * own initialization routine; the NVM controller will be placed in Manual Write
 * mode, so that explicit write commands must be sent to the controller to
 * commit a buffered page to physical memory. The manual write command must thus
 * be issued to the NVM controller whenever the user application wishes to write
 * to a NVM page for its own purposes.
 *
 * \subsection asfdoc_sam0_eeprom_special_considerations_pagesize Logical EEPROM Page Size
 * As a small amount of information needs to be stored in a header before the
 * contents of a logical EEPROM page in memory (for use by the emulation
 * service), the available data in each EEPROM page is less than the total size
 * of a single NVM memory page by several bytes.
 *
 * \subsection asfdoc_sam0_eeprom_special_considerations_committing Committing of the Write Cache
 * A single-page write cache is used internally to buffer data written to pages
 * in order to reduce the number of physical writes required to store the user
 * data, and to preserve the physical memory lifespan. As a result, it is
 * important that the write cache is committed to physical memory <b>as soon as
 * possible after a BOD low power condition</b>, to ensure that enough power is
 * available to guarantee a completed write so that no data is lost.
 *
 * The write cache must also be manually committed to physical memory if the
 * user application is to perform any NVM operations using the NVM controller
 * directly.
 *
 *
 * \section asfdoc_sam0_eeprom_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_sam0_eeprom_extra. This includes:
 *  - \ref asfdoc_sam0_eeprom_extra_acronyms
 *  - \ref asfdoc_sam0_eeprom_extra_dependencies
 *  - \ref asfdoc_sam0_eeprom_extra_errata
 *  - \ref asfdoc_sam0_eeprom_extra_history
 *
 *
 * \section asfdoc_sam0_eeprom_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_sam0_eeprom_exqsg.
 *
 *
 * \section asfdoc_sam0_eeprom_api_overview API Overview
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <compiler.h>

#if !defined(__DOXYGEN__)
#  define EEPROM_MAX_PAGES            (64 * NVMCTRL_ROW_PAGES)
#  define EEPROM_MASTER_PAGE_NUMBER   (_eeprom_instance.physical_pages - 1)
#  define EEPROM_INVALID_PAGE_NUMBER  0xFF
#  define EEPROM_INVALID_ROW_NUMBER   (EEPROM_INVALID_PAGE_NUMBER / NVMCTRL_ROW_PAGES)
#  define EEPROM_HEADER_SIZE          4
#endif


/** \name EEPROM Emulator Information
 * @{
 */

/** Emulator scheme ID, identifying the scheme used to emulated EEPROM storage. */
#define EEPROM_EMULATOR_ID          1

/** Emulator major version number, identifying the emulator major version. */
#define EEPROM_MAJOR_VERSION        1

/** Emulator minor version number, identifying the emulator minor version. */
#define EEPROM_MINOR_VERSION        0

/** Emulator revision version number, identifying the emulator revision. */
#define EEPROM_REVISION             0

/** Size of the user data portion of each logical EEPROM page, in bytes. */
#define EEPROM_PAGE_SIZE            (NVMCTRL_PAGE_SIZE - EEPROM_HEADER_SIZE)

/**
 * \brief EEPROM memory parameter structure.
 *
 * Structure containing the memory layout parameters of the EEPROM emulator module.
 */
struct eeprom_emulator_parameters {
	/** Number of bytes per emulated EEPROM page. */
	uint8_t  page_size;
	/** Number of emulated pages of EEPROM. */
	uint16_t eeprom_number_of_pages;
};

/** @} */

/** \name Configuration and Initialization
 * @{
 */

enum status_code eeprom_emulator_init(void);

void eeprom_emulator_erase_memory(void);

enum status_code eeprom_emulator_get_parameters(
		struct eeprom_emulator_parameters *const parameters);

/** @} */


/** \name Logical EEPROM Page Reading/Writing
 * @{
 */

enum status_code eeprom_emulator_commit_page_buffer(void);

enum status_code eeprom_emulator_write_page(
		const uint8_t logical_page,
		const uint8_t *const data);

enum status_code eeprom_emulator_read_page(
		const uint8_t logical_page,
		uint8_t *const data);

/** @} */

/** \name Buffer EEPROM Reading/Writing
 * @{
 */

enum status_code eeprom_emulator_write_buffer(
		const uint16_t offset,
		const uint8_t *const data,
		const uint16_t length);

enum status_code eeprom_emulator_read_buffer(
		const uint16_t offset,
		uint8_t *const data,
		const uint16_t length);

/** @} */

#ifdef __cplusplus
}
#endif

/** @} */

/**
 * \page asfdoc_sam0_eeprom_extra Extra Information
 *
 * \section asfdoc_sam0_eeprom_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 *
 * <table>
 *	<tr>
 *		<th>Acronym</th>
 *		<th>Description</th>
 *	</tr>
 *	<tr>
 *		<td>EEPROM</td>
 *		<td>Electronically Erasable Read-Only Memory</td>
 *	</tr>
 *	<tr>
 *		<td>NVM</td>
 *		<td>Non-Volatile Memory</td>
 *	</tr>
 * </table>
 *
 *
 * \section asfdoc_sam0_eeprom_extra_dependencies Dependencies
 * This driver has the following dependencies:
 *
 *  - \ref asfdoc_sam0_nvm_group "Non-Volatile Memory Controller Driver"
 *
 *
 * \section asfdoc_sam0_eeprom_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_sam0_eeprom_extra_history Module History
 * An overview of the module history is presented in the table below, with
 * details on the enhancements and fixes made to the module since its first
 * release. The current version of this corresponds to the newest version in
 * the table.
 *
 * <table>
 *	<tr>
 *		<th>Changelog</th>
 *	</tr>
 *	<tr>
 *		<td>Fix warnings</td>
 *	</tr>
 *	<tr>
 *		<td>Initial Release</td>
 *	</tr>
 * </table>
 */

/**
 * \page asfdoc_sam0_eeprom_exqsg Examples for Emulated EEPROM Service
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_sam0_eeprom_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that QSGs can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_sam0_eeprom_basic_use_case
 *
 * \page asfdoc_sam0_eeprom_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *		<th>Doc. Rev.</th>
 *		<th>Date</th>
 *		<th>Comments</th>
 *	</tr>
 *	<tr>
 *		<td>42125F</td>
 *		<td>12/2015</td>
 *		<td>Added support for SAM L22, SAM DA1, and SAM C20/C21</td>
 *	</tr>
 *	<tr>
 *		<td>42125E</td>
 *		<td>11/2014</td>
 *		<td>Added support for SAM L21</td>
 *	</tr>
 *	<tr>
 *		<td>42125D</td>
 *		<td>09/2014</td>
 *		<td>Added support for SAM R21, and SAM D10/D11</td>
 *	</tr>
 *	<tr>
 *		<td>42125C</td>
 *		<td>07/2014</td>
 *		<td>Add support for SAM D21</td>
 *	</tr>
 *  <tr>
 *	   <td>42125B</td>
 *	   <td>11/2013</td>
 *     <td>
 *        - ASF 3.13: Fixed bugs related to eeprom_emulator_write_buffer() and
 *          eeprom_emulator_read_buffer(). The functions now handle offsets that
 *          are multiples of 60. The length can now be smaller than one page without
 *          risking corruption. Addresses that are multiples of 60 will be written
 *          correctly
 *        - Updated module figures and re-worded the module overview. Corrected
 *          documentation typos
 *     </td>
 *	</tr>
 *	<tr>
 *		<td>42125A</td>
 *		<td>06/2013</td>
 *		<td>Initial release</td>
 *	</tr>
 * </table>
 */

#endif /* EEPROM_H_INCLUDED */
