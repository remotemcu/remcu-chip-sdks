/**
 * \file
 *
 * \brief USB host driver for Vendor interface.
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
 * \defgroup asfdoc_uhi_vendor_group USB Host Interface (UHI) for Vendor Class Device
 *
 * USB Host Interface (UHI) for Vendor Class Device provides an
 * interface for the configuration and management of USB Vendor host.
 *
 * The outline of this documentation is as follows:
 * - \ref asfdoc_uhi_vendor_api_overview
 * - \ref asfdoc_uhi_vendor_exqsg
 * - \ref asfdoc_uhi_vendor_config_examples
 *
 * For more details for Atmel&reg; Software Framework (ASF) USB Host Stack,
 * refer to following application note:
 * - <a href="http://ww1.microchip.com/downloads/en/appnotes/doc8486.pdf">
 *   AVR4950: ASF - USB Host Stack</a>
 *
 * \section asfdoc_uhi_vendor_api_overview API Overview
 * @{
 */

/**
 * \name Interface with USB Host Core (UHC)
 *
 * Definition and functions required by UHC.
 *
 * @{
 */

/** Global definition which contains standard UHI API for UHC
 *  It must be added in USB_HOST_UHI definition from conf_usb_host.h file. */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#define UHI_VENDOR { \
	.install = uhi_vendor_install, \
	.enable = uhi_vendor_enable, \
	.uninstall = uhi_vendor_uninstall, \
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
extern uhc_enum_status_t uhi_vendor_install(uhc_device_t* dev);

/**
 * \brief Enable the interface.
 *
 * Enable a USB interface corresponding to UHI.
 *
 * \param[in] uhc_device_t	  Device to request
 */
extern void uhi_vendor_enable(uhc_device_t* dev);

/**
 * \brief Uninstall the interface (if installed).
 *
 * \param[in] uhc_device_t	  Device to request
 */
extern void uhi_vendor_uninstall(uhc_device_t* dev);
/**@}*/


/**
 * \name UHI for Vendor Class
 *
 * Common APIs used by high level application to use this USB host class.
 *
 * This Vendor Class implementation supports one endpoint for all endpoint
 * types on all directions: Control IN, control OUT, interrupt IN,
 * interrupt OUT, bulk IN, bulk OUT, isochronous IN, isochronous OUT.
 *
 * This implementation is an example and can be a base to create another Vendor Class
 * which supports more endpoint as two bulk IN endpoints.
 *
 * @{
 */

/**
 * \brief Start a transfer on control IN
 *
 * When the transfer is finished or aborted (stall, reset, ...), the \a callback
 * is called.
 * The \a callback returns the transfer status and eventually the number of bytes
 * transferred.
 *
 * \param[out] buf          Buffer on Internal RAM to send or fill.
 *                          It must be align, then use COMPILER_WORD_ALIGNED.
 * \param[in] buf_size      Buffer size to send or fill
 * \param[in] callback      NULL or function to call at the end of transfer
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
bool uhi_vendor_control_in_run(uint8_t * buf, iram_size_t buf_size,
		uhd_callback_setup_end_t callback);

/**
 * \brief Start a transfer on control OUT
 *
 * When the transfer is finished or aborted (stall, reset, ...), the \a callback
 * is called.
 * The \a callback returns the transfer status and eventually the number of byte
 * transferred.
 *
 * \param[in] buf           Buffer on Internal RAM to send or fill.
 *                      It must be align, then use COMPILER_WORD_ALIGNED.
 * \param[in] buf_size      Buffer size to send or fill
 * \param[in] callback      NULL or function to call at the end of transfer
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
bool uhi_vendor_control_out_run(uint8_t * buf, iram_size_t buf_size,
		uhd_callback_setup_end_t callback);

/**
 * \brief Start a transfer on bulk IN
 *
 * When the transfer is finished or aborted (stall, reset, ...), the \a callback
 * is called.
 * The \a callback returns the transfer status and eventually the number of byte
 * transferred.
 *
 * \param[out] buf           Buffer on Internal RAM to send or fill.
 *                      It must be align, then use COMPILER_WORD_ALIGNED.
 * \param[in] buf_size      Buffer size to send or fill
 * \param[in] callback      NULL or function to call at the end of transfer
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
bool uhi_vendor_bulk_in_run(uint8_t * buf, iram_size_t buf_size,
		uhd_callback_trans_t callback);

/**
 * \brief Start a transfer on bulk OUT
 *
 * When the transfer is finished or aborted (stall, reset, ...), the \a callback
 * is called.
 * The \a callback returns the transfer status and eventually the number of byte
 * transferred.
 *
 * \param[in] buf           Buffer on Internal RAM to send or fill.
 *                      It must be align, then use COMPILER_WORD_ALIGNED.
 * \param[in] buf_size      Buffer size to send or fill
 * \param[in] callback      NULL or function to call at the end of transfer
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
bool uhi_vendor_bulk_out_run(uint8_t * buf, iram_size_t buf_size,
		uhd_callback_trans_t callback);

/**
 * \brief Start a transfer on interrupt IN
 *
 * When the transfer is finished or aborted (stall, reset, ...), the \a callback
 * is called.
 * The \a callback returns the transfer status and eventually the number of byte
 * transferred.
 *
 * \param[out] buf           Buffer on Internal RAM to send or fill.
 *                      It must be align, then use COMPILER_WORD_ALIGNED.
 * \param[in] buf_size      Buffer size to send or fill
 * \param[in] callback      NULL or function to call at the end of transfer
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
bool uhi_vendor_int_in_run(uint8_t * buf, iram_size_t buf_size,
		uhd_callback_trans_t callback);

/**
 * \brief Start a transfer on interrupt OUT
 *
 * When the transfer is finished or aborted (stall, reset, ...), the \a callback
 * is called.
 * The \a callback returns the transfer status and eventually the number of byte
 * transferred.
 *
 * \param[in] buf           Buffer on Internal RAM to send or fill.
 *                      It must be align, then use COMPILER_WORD_ALIGNED.
 * \param[in] buf_size      Buffer size to send or fill
 * \param[in] callback      NULL or function to call at the end of transfer
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 *
 */
bool uhi_vendor_int_out_run(uint8_t * buf, iram_size_t buf_size,
		uhd_callback_trans_t callback);

/**
 * \brief Start a transfer on ISO IN
 *
 * When the transfer is finished or aborted (stall, reset, ...), the \a callback
 * is called.
 * The \a callback returns the transfer status and eventually the number of byte
 * transferred.
 *
 * \param[out] buf           Buffer on Internal RAM to send or fill.
 *                      It must be align, then use COMPILER_WORD_ALIGNED.
 * \param[in] buf_size      Buffer size to send or fill
 * \param[in] callback      NULL or function to call at the end of transfer
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
bool uhi_vendor_iso_in_run(uint8_t * buf, iram_size_t buf_size,
		uhd_callback_trans_t callback);

/**
 * \brief Start a transfer on ISO OUT
 *
 * When the transfer is finished or aborted (stall, reset, ...), the \a callback
 * is called.
 * The \a callback returns the transfer status and eventually the number of byte
 * transferred.
 *
 * \param[in] buf           Buffer on Internal RAM to send or fill.
 *                      It must be align, then use COMPILER_WORD_ALIGNED.
 * \param[in] buf_size      Buffer size to send or fill
 * \param[in] callback      NULL or function to call at the end of transfer
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 *
 */
bool uhi_vendor_iso_out_run(uint8_t * buf, iram_size_t buf_size,
		uhd_callback_trans_t callback);

/**
 * \brief Check if a transfer on BULK is possible
 *
 * \return \c 1 if possible, otherwise \c 0.
 */
bool uhi_vendor_bulk_is_available(void);

/**
 * \brief Check if a transfer on INTERRUPT is possible
 *
 * \return \c 1 if possible, otherwise \c 0.
 */
bool uhi_vendor_int_is_available(void);

/**
 * \brief Check if a transfer on ISO is possible
 *
 * \return \c 1 if possible, otherwise \c 0.
 */
bool uhi_vendor_iso_is_available(void);
/**@}*/

/**@}*/

/**
 * \page asfdoc_uhi_vendor_exqsg Quick Start Guide for USB Host Vendor Module (UHI Vendor)
 *
 * This is the quick start guide for the \ref asfdoc_uhi_vendor_group
 * "USB Host Vendor Module (UHI Vendor)" with step-by-step instructions on
 * how to configure and use the modules in a selection of use cases.
 *
 * The use cases highlights several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section uhi_vendor_basic_use_case Basic Use Case
 * In this basic use case, the "USB Vendor (Single Class support)" module is
 * used.
 *
 * The "USB Vendor (Composite)" module usage is described in
 * \ref uhi_vendor_use_cases "Advanced Use Cases".
 *
 * \subsection uhi_vendor_basic_use_case_setup Setup Steps
 * As a USB host, it follows common USB host setup steps. Refer to
 * \ref asfdoc_uhc_basic_use_case_setup "USB Host Basic Setup".

 *
 * \subsection uhi_vendor_basic_use_case_usage Usage Steps
 *
 * \subsubsection uhi_vendor_basic_use_case_usage_code Example Code
 * Content of conf_usb_host.h:
 * \code
	#define USB_HOST_UHI        UHI_VENDOR
	#define UHI_VENDOR_CHANGE(dev, b_plug) my_callback_vendor_change(dev, b_plug)
	extern void my_callback_vendor_change(uhc_device_t* dev, bool b_plug);
	#define UHI_VENDOR_VID_PID_LIST {USB_VID_ATMEL, USB_PID_ATMEL_ASF_VENDOR_CLASS}
	#include "uhi_vendor.h" // At the end of conf_usb_host.h file
 \endcode
 *
 * Add to application C-file:
 * \code
 static bool my_flag_vendor_test_start = false;
 void my_callback_vendor_change(uhc_device_t* dev, bool b_plug)
 {
    // USB Device Vendor connected
    my_flag_vendor_test_start = b_plug;
 }

 static void my_callback_bulk_in_done (usb_add_t add,
         usb_ep_t ep, uhd_trans_status_t status, iram_size_t nb_transfered)
 {
   if (status != UHD_TRANS_NOERROR) {
     return; // Error during transfer
   }
   // Data received then restart test
   my_flag_vendor_test_start = true;
 }

 #define MESSAGE "Hello bulk"
 #define HELLO_SIZE 5
 #define HELLO_BULK_SIZE 10
 uint8_t my_out_buffer[MESSAGE_SIZE+1] = MESSAGE;
 uint8_t my_in_buffer[MESSAGE_SIZE+1];
 void my_task(void)
 {
    if (!my_flag_vendor_test_start) {
      return;
    }
    my_flag_vendor_test_start = false;

    // Send data through control endpoint
    uhi_vendor_control_out_run(my_out_buffer, HELLO_SIZE, NULL);

    // Check if bulk endpoints are available
    if (uhi_vendor_bulk_is_available()) {
      // Send data through bulk OUT endpoint
      uhi_vendor_bulk_out_run(my_out_buffer, HELLO_BULK_SIZE, NULL);
      // Receive data through bulk IN endpoint
      uhi_vendor_bulk_in_run(my_in_buffer, sizeof(my_in_buffer),
              my_callback_bulk_in_done);
    }
 }
 \endcode
 *
 * \subsubsection uhi_vendor_basic_use_case_setup_flow Workflow
 * -# Ensure that conf_usb_host.h is available and contains the following
 * configurations, which is the USB host vendor configuration:
 * \code
 #define USB_HOST_UHI   UHI_HID_VENDOR
 \endcode
 * \note It defines the list of UHI supported by USB host.
 *
 * \code
 #define UHI_VENDOR_CHANGE(dev, b_plug) my_callback_vendor_change(dev, b_plug)
 extern bool my_callback_vendor_change(uhc_device_t* dev, bool b_plug);
 \endcode
 * \note This callback is called when a USB device vendor is plugged or unplugged.
 *
 * \code
 #define UHI_VENDOR_VID_PID_LIST {USB_VID_ATMEL, USB_PID_ATMEL_ASF_VENDOR_CLASS}
 \endcode
 * \note It defines the list of devices supported by USB host (defined by VID and PID).
 *
 * -# The Vendor data transfert functions are described in \ref uhi_vendor_group.
 * \code
 uhi_vendor_control_out_run(), uhi_vendor_bulk_out_run(),...
 \endcode
 *
 * \section uhi_vendor_use_cases Advanced Use Cases
 * \ifnot ASF_MANUAL
 * For more advanced use of the UHI vendor module, see the following use cases:
 * - \subpage uhc_use_case_1
 * - \subpage uhc_use_case_2
 * - \subpage uhc_use_case_3
* \else
 * For more advanced use of the UHI vendor module, see the following:
 * - \ref asfdoc_uhc_use_cases
 * \endif
 */

/**
 * \page asfdoc_uhi_vendor_config_examples Configuration File Examples
 *
 * \section asfdoc_uhi_vendor_config_examples_1 conf_usb_host.h
 * \subsection asfdoc_uhi_vendor_config_examples_1_1  UHI Vendor Single
 * \include module_config/conf_usb_host.h
 * \subsection asfdoc_uhi_vendor_config_examples_1_2  UHI Vendor Multiple (Composite)
 * \include composite/host/module_config/conf_usb_host.h
 *
 * \section asfdoc_uhi_vendor_config_examples_2 conf_clock.h
 *
 * \subsection asfdoc_uhi_vendor_config_examples_2_1 SAM3X and SAM3A Devices (UOTGHS: USB OTG High Speed)
 * \include example/sam3x8h_sam3x_ek/conf_clock.h
 *
 * \subsection asfdoc_uhi_vendor_config_examples_2_2 SAM4L Device (USBC)
 * \include example/sam4lc4c_sam4l_ek/conf_clock.h
  *
 * \section asfdoc_uhi_vendor_config_examples_3 conf_clocks.h
 *
 * \subsection asfdoc_uhi_vendor_config_examples_3_1 SAM D21 Devices (USB)
 * \include example/samd21j18a_samd21_xplained_pro/conf_clocks.h
 *
 * \section asfdoc_uhi_vendor_config_examples_4 conf_board.h
 *
 * \subsection asfdoc_uhi_vendor_config_examples_4_1 SAM3X and SAM3A Devices (UOTGHS: USB OTG High Speed)
 * \include example/sam3x8h_sam3x_ek/conf_board.h
 *
 * \subsection asfdoc_uhi_vendor_config_examples_4_2 SAM4L Device (USBC)
 * \include example/sam4lc4c_sam4l_ek/conf_board.h
 *
 * \subsection asfdoc_uhi_vendor_config_examples_4_3 SAM D21 Devices (USB)
 * \include example/samd21j18a_samd21_xplained_pro/conf_board.h
 */

/**
 * \page asfdoc_uhi_vendor_document_revision_history Document Revision History
 *
 * <table>
 * <tr>
 *    <th>Doc. Rev.</th>
 *    <th>Date</th>
 *    <th>Comments</th>
 * </tr>
 * <tr>
 *    <td>42346B</td>
 *    <td>12/2015</td>
 *    <td>Fixed typos</td>
 * </tr>
 * <tr>
 *    <td>42346A</td>
 *    <td>12/2014</td>
 *    <td>Initial release</td>
 * </tr>
 * </table>
 */

