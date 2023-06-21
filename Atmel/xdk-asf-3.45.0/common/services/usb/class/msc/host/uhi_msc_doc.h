/**
 * \file
 *
 * \brief USB host driver for Mass Storage Class interface.
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

/**
 * \defgroup asfdoc_uhi_msc_group USB Host Interface (UHI) for Mass Storage Class (MSC)
 *
 * USB Host Interface (UHI) for Mass Storage Class (MSC) provides an
 * interface for the configuration and management of USB MSC host.
 *
 * The outline of this documentation is as follows:
 * - \ref asfdoc_uhi_msc_api_overview
 * - \ref asfdoc_uhi_msc_exqsg
 * - \ref asfdoc_uhi_msc_config_examples
 *
 * For more details for Atmel&reg; Software Framework (ASF) USB Host Stack,
 * refer to following application note:
 * - <a href="http://ww1.microchip.com/downloads/en/appnotes/doc8486.pdf">
 *   AVR4950: ASF - USB Host Stack</a>
 *
 * \section asfdoc_uhi_msc_api_overview API Overview
 * @{
 */


/**
 * \name Interface with USB Host Core (UHC)
 *
 * Definition and functions required by UHC.
 *
 * @{
 */

/** Global definition which contains standard UHI API for UHC.
 *  It must be added in USB_HOST_UHI definition from conf_usb_host.h file. */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#define UHI_MSC { \
	.install = uhi_msc_install, \
	.enable = uhi_msc_enable, \
	.uninstall = uhi_msc_uninstall, \
	.sof_notify = NULL, \
}
/**@}*/

/**
 * \name Functions Required by UHC
 * @{
 */

/**
 * \brief Install interface
 *
 * Allocate interface endpoints if supported.
 *
 * \param[in] uhc_device_t	  Device to request
 *
 * \return Status of the install.
 */
uhc_enum_status_t uhi_msc_install(uhc_device_t* dev);

/**
 * \brief Enable the interface.
 *
 * Enable a USB interface corresponding to UHI.
 *
 * \param[in] uhc_device_t	  Device to request
 */
void uhi_msc_enable(uhc_device_t* dev);

/**
 * \brief Uninstall the interface (if installed).
 *
 * \param[in] uhc_device_t	  Device to request
 */
void uhi_msc_uninstall(uhc_device_t* dev);
/**@}*/

/** Status of LUN. */
typedef enum
{
	/** Success, memory ready */
	LUN_GOOD       = 0,
	/** An error occurred */
	LUN_FAIL       = 1,
	/** Memory unplugged */
	LUN_NOT_PRESENT = 2,
	/** Memory not initialized or changed */
	LUN_BUSY       = 3,
} lun_status_t;

/** Callback type used by uhi_msc_scsi() functions. */
typedef void (*uhi_msc_scsi_callback_t) (bool);

/**
 * \name Struct to access at Logical Unit Numbers (LUNs)
 * @{
 */

/** Logical Unit Number (LUN) structure information. */
typedef struct {
	/** SBC-2 read capacity (10) parameter data */
	struct sbc_read_capacity10_data capacity;
	/** Write protect enable */
	bool b_write_protected;
	/** Status of LUN */
	lun_status_t status;
} uhi_msc_lun_t;

/**@}*/

/**
 * \name UHI for Mass Storage Class
 *
 * Common APIs used by high level application to use this USB host class.
 *
 * @{
 */

/**
 * \brief Tests if the interface UHI Mass Storage is available
 *
 * The UHI Mass Storage can be busy during the enumeration of a USB Device MSC.
 *
 * \return True, if UHI Mass Storage is available.
 */
bool uhi_msc_is_available(void);

/**
 * \brief Gives the number of LUN available
 *
 * \note A LUN can be available, but with a status LUN_NOT_PRESENT.
 *
 * It is the case for a card reader without card.
 *
 * \return Number of LUN available.
 */
uint8_t uhi_msc_get_lun(void);

/**
 * \brief Gives information about a LUN
 *
 * \param[in] lun  LUN number
 *
 * \return Pointer on the LUN information structure.
 */
uhi_msc_lun_t* uhi_msc_get_lun_desc(uint8_t lun);

/**
 * \brief Checks and update the status of the LUN
 *
 * \param[in] lun       LUN number
 * \param[in] callback  Callback to call at the end of SCSI command
 *
 * \return True, if the Small Computer System Interface (SCSI) command has
 *         been accepted.
 */
bool uhi_msc_scsi_test_unit_ready(uint8_t lun, uhi_msc_scsi_callback_t callback);

/**
 * \brief Reads a LUN data section to RAM buffer
 *
 * \note The sector size used to define the data section
 * is the sector size returned by LUN in \capacity field.
 *
 * \param[in] lun       LUN number
 * \param[in] addr      Sector address to read
 * \param[out] ram       RAM address used to store the data
 * \param[in] nb_sector Number of sector to read
 * \param[in] callback  Callback to call at the end of SCSI command
 *
 * \return True, if the SCSI command has been accepted.
 */
bool uhi_msc_scsi_read_10(uint8_t lun, uint32_t addr, uint8_t *ram,
		uint8_t nb_sector, uhi_msc_scsi_callback_t callback);

/**
 * \brief Writes a RAM buffer in a LUN data section
 *
 * \note The sector size used to define the data section
 * is the sector size returned by LUN in \capacity field.
 *
 * \param[in] lun       LUN number
 * \param[in] addr      Sector address to write
 * \param[in] ram       RAM address of data to write
 * \param[in] nb_sector Number of sector to write
 * \param[in] callback  Callback to call at the end of SCSI command
 *
 * \return True, if the SCSI command has been accepted.
 */
bool uhi_msc_scsi_write_10(uint8_t lun, uint32_t addr, const uint8_t *ram,
		uint8_t nb_sector, uhi_msc_scsi_callback_t callback);
/**@}*/

/**
 * \name USB Host Mass Storage Interface for Control Access Module
 * Layer added on UHI MSC interface to allow the usage of control access module.
 * The control access module provides a common access at all memories and
 * it is used by the File Systems available in ASF.
 *
 * @{
 */

/**
 * \brief Gives the number of available LUN
 *
 * \note A LUN can be available, but with a status not present.
 *
 * It is the case for a card reader without card.
 *
 * \return Number of available LUN.
 */
uint8_t uhi_msc_mem_get_lun(void);

/**
 * \brief Checks and update the status of the LUN
 *
 * \param[in] lun       LUN number
 *
 * \return Status of the LUN.
 */
Ctrl_status uhi_msc_mem_test_unit_ready(uint8_t lun);

/**
 * \brief Returns the capacity of the LUN
 *
 * \param[in] lun           LUN number
 * \param[in] u32_nb_sector Pointer to store the last sector address possible on this LUN
 *
 * \return Status of the LUN.
 */
Ctrl_status uhi_msc_mem_read_capacity(uint8_t lun, uint32_t *u32_nb_sector);

/**
 * \brief Returns the sector size of the LUN
 *
 * \param[in] lun           LUN number
 *
 * \return Sector size (unit 512B).
 */
uint8_t uhi_msc_mem_read_sector_size(uint8_t lun);

/**
 * \brief Checks if the LUN is write protected
 *
 * \param[in] lun           LUN number
 *
 * \return True, if write protected.
 */
bool uhi_msc_mem_wr_protect(uint8_t lun);

/**
 * \brief Checks if the device is removed
 *
 * \return Always true for USB Device.
 */
bool uhi_msc_mem_removal(void);

/**
 * \brief Reads 512 bytes from the current LUN
 *
 * The LUN is selected by uhi_msc_mem_test_unit_ready()
 * or uhi_msc_mem_read_capacity() function.
 *
 * \param[in] addr Disk address (unit 512B)
 * \param[out] ram   Pointer to store the data
 *
 * \return Status of the LUN.
 */
Ctrl_status uhi_msc_mem_read_10_ram(uint32_t addr, void *ram);

/**
 * \brief Writes 512 bytes to the current LUN
 *
 * The LUN is selected by uhi_msc_mem_test_unit_ready()
 * or uhi_msc_mem_read_capacity() function.
 *
 * \param[in] addr  Disk address (unit 512B)
 * \param[in] ram   Pointer on the data
 *
 * \return Status of the LUN.
 */
Ctrl_status uhi_msc_mem_write_10_ram(uint32_t addr, const void *ram);
/**@}*/

/**@}*/

/**
 * \page asfdoc_uhi_msc_exqsg Quick Start Guide for USB Host Mass-Storage Module (UHI MSC)
 *
 * This is the quick start guide for the \ref asfdoc_uhi_msc_group
 * "USB Host Mass-Storage Module (UHI MSC)" with step-by-step instructions on
 * how to configure and use the modules in a selection of use cases.
 *
 * The use cases highlights several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section uhi_msc_mem_basic_use_case Basic Use Case
 * In this basic use case, the "USB Host MSC (Single Class support)" module is used.
 *
 * The "USB Host MSC (Multiple Classes support)" module usage is described
 * in \ref uhi_msc_mem_use_cases "Advanced Use Cases".
 *
 * This example do a simple physical memory access, but a file system module
 * can be added to decode the USB memory file system, see FatFS examples.
 *
 * \subsection uhi_msc_mem_basic_use_case_setup Setup Steps
 * As a USB host, it follows common USB host setup steps. Refer to
 * \ref asfdoc_uhc_basic_use_case_setup "USB Host Basic Setup".
 *
 * \subsection uhi_msc_mem_basic_use_case_usage Usage Steps
 *
 * \subsubsection uhi_msc_mem_basic_use_case_usage_code Example Code
 * Content of conf_usb_host.h:
 * \code
	#define USB_HOST_UHI        UHI_MSC
	#define UHI_MSC_CHANGE(dev, b_plug) my_callback_msc_change(dev, b_plug)
	extern bool my_callback_msc_change(uhc_device_t* dev, bool b_plug);
	#include "uhi_msc_mem.h" // At the end of conf_usb_host.h file
 \endcode
 *
 * Add to application C-file:
 * \code
	 static bool my_flag_autorize_msc_check = false;
	 bool my_callback_msc_change(uhc_device_t* dev, bool b_plug)
	 {
	    if (b_plug) {
	       my_flag_autorize_msc_check = true;
	    } else {
	       my_flag_autorize_msc_check = false;
	    }
	 }

	 void my_task(void)
	 {
	    if (!my_flag_autorize_msc_check) {
	       return;
	    }
	    my_flag_autorize_msc_check = false;

	    // Check all new USB disks plugged
	    for (uint8_t lun=0; lun < uhi_msc_mem_get_lun(); lun++) {
	       // Wait the end of USB disk install
	       while (CTRL_BUSY == uhi_msc_mem_test_unit_ready(lun));
	       if (CTRL_GOOD != uhi_msc_mem_test_unit_ready(lun)) {
	          // Removal disk not present or fail
	          continue;
	       }
	       // Read capacity
	       uint32_t max_lba;
	       uhi_msc_mem_read_capacity(lun, &max_lba);
	    }
	 }
 \endcode
 *
 * \subsubsection uhi_msc_mem_basic_use_case_setup_flow Workflow
 * -# Ensure that conf_usb_host.h is available and contains the following configuration,
 *  which is the USB host MSC configuration:
 * \code
 #define USB_HOST_UHI   UHI_MSC
 \endcode
 * \note It defines the list of UHI supported by USB host.
 *
 * \code
 #define UHI_MSC_CHANGE(dev, b_plug) my_callback_msc_change(dev, b_plug)
 extern bool my_callback_msc_change(uhc_device_t* dev, bool b_plug);
 \endcode
 * \note This callback is called when a USB device MSC is plugged or unplugged.
 *
 * -# The access of the USB memories is allowed through functions described in \ref asfdoc_uhi_msc_api_overview.
 *
 * \section uhi_msc_mem_use_cases Advanced Use Cases
 * \ifnot ASF_MANUAL
 * For more advanced use of the UHI MSC module, see the following use cases:
 * - \subpage uhc_use_case_1
 * - \subpage uhc_use_case_2
 * - \subpage uhc_use_case_3
 * \else
 * For more advanced use of the UHI MSC module, see the following:
 * - \ref asfdoc_uhc_use_cases
 * \endif
 */

/**
 * \page asfdoc_uhi_msc_config_examples Configuration File Examples
 *
 * \section asfdoc_uhi_msc_config_examples_1 conf_usb_host.h
 * \subsection asfdoc_uhi_msc_config_examples_1_1  UHI MSC Single
 * \include module_config/conf_usb_host.h
 * \subsection asfdoc_uhi_msc_config_examples_1_2  UHI MSC Multiple (Composite)
 * \include composite/host/module_config/conf_usb_host.h
 *
 * \section asfdoc_uhi_msc_config_examples_2 conf_clock.h
 *
 * \subsection asfdoc_uhi_msc_config_examples_2_1 AT32UC3A0, AT32UC3A1, and AT32UC3B Devices (USBB)
 * \include example/at32uc3a0512_evk1100/conf_clock.h
 *
 * \subsection asfdoc_uhi_msc_config_examples_2_2 AT32UC3A3 and AT32UC3A4 Devices (USBB with High Speed Support)
 * \include example/at32uc3a3256_evk1104/conf_clock.h
 *
 * \subsection asfdoc_uhi_msc_config_examples_2_3 AT32UC3C, ATUCXXD, ATUCXXL3U, and ATUCXXL4U Devices (USBC)
 * \include example/at32uc3c0512c_uc3c_ek/conf_clock.h
 *
 * \subsection asfdoc_uhi_msc_config_examples_2_4 SAM3X and SAM3A Devices (UOTGHS: USB OTG High Speed)
 * \include example2/sam3x8h_sam3x_ek/conf_clock.h
 *
 * \section asfdoc_uhi_msc_config_examples_3 conf_clocks.h
 *
 * \subsection asfdoc_uhi_msc_config_examples_3_1 SAM D21 Devices (USB)
 * \include example2/samd21j18a_samd21_xplained_pro/conf_clocks.h
 *
 * \section asfdoc_uhi_msc_config_examples_4 conf_board.h
 *
 * \subsection asfdoc_uhi_msc_config_examples_4_1 AT32UC3A0, AT32UC3A1, and AT32UC3B Devices (USBB)
 * \include example/at32uc3a0512_evk1100/conf_board.h
 *
 * \subsection asfdoc_uhi_msc_config_examples_4_2 AT32UC3A3 and AT32UC3A4 Devices (USBB with High Speed Support)
 * \include example/at32uc3a3256_evk1104/conf_board.h
 *
 * \subsection asfdoc_uhi_msc_config_examples_42_3 AT32UC3C, ATUCXXD, ATUCXXL3U, and ATUCXXL4U Devices (USBC)
 * \include example/at32uc3c0512c_uc3c_ek/conf_board.h
 *
 * \subsection asfdoc_uhi_msc_config_examples_4_4 SAM3X and SAM3A Devices (UOTGHS: USB OTG High Speed)
 * \include example2/sam3x8h_sam3x_ek/conf_board.h
 *
 * \subsection asfdoc_uhi_msc_config_examples_4_5 SAM D21 Devices (USB)
 * \include example2/samd21j18a_samd21_xplained_pro/conf_board.h
 */

/**
 * \page asfdoc_uhi_msc_document_revision_history Document Revision History
 *
 * <table>
 * <tr>
 *    <th>Doc. Rev.</th>
 *    <th>Date</th>
 *    <th>Comments</th>
 * </tr>
 * <tr>
 *    <td>42344B</td>
 *    <td>12/2015</td>
 *    <td>Fixed typos</td>
 * </tr>
 * <tr>
 *    <td>42344A</td>
 *    <td>12/2014</td>
 *    <td>Initial release</td>
 * </tr>
 * </table>
 */

