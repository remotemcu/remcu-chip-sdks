/**
 * \file
 *
 * \brief USB host driver for Communication Device Class interface.
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
 * \defgroup asfdoc_uhi_cdc_group USB Host Interface (UHI) for Communication Class Device (CDC)
 *
 * USB Host Interface (UHI) for Communication Class Device (CDC) provides an
 * interface for the configuration and management of USB CDC serial host.
 *
 * The outline of this documentation is as follows:
 * - \ref asfdoc_uhi_cdc_api_overview
 * - \ref asfdoc_uhi_cdc_exqsg
 * - \ref asfdoc_uhi_cdc_config_examples
 *
 * For more details for Atmel&reg; Software Framework (ASF) USB Host Stack,
 * refer to following application note:
 * - <a href="http://ww1.microchip.com/downloads/en/appnotes/doc8486.pdf">
 *   AVR4950: ASF - USB Host Stack</a>
 *
 * \section asfdoc_uhi_cdc_api_overview API Overview
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
 *  It must be added in USB_HOST_UHI define from conf_usb_host.h file. */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#define UHI_CDC { \
	.install = uhi_cdc_install, \
	.enable = uhi_cdc_enable, \
	.uninstall = uhi_cdc_uninstall, \
	.sof_notify = uhi_cdc_sof, \
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
uhc_enum_status_t uhi_cdc_install(uhc_device_t* dev);

/**
 * \brief Enable the interface.
 *
 * Enable a USB interface corresponding to UHI.
 *
 * \param[in] uhc_device_t	  Device to request
 */
void uhi_cdc_enable(uhc_device_t* dev);

/**
 * \brief Uninstall the interface (if installed).
 *
 * \param[in] uhc_device_t	  Device to request
 */
void uhi_cdc_uninstall(uhc_device_t* dev);

/**
 * \brief Signal that a SOF has occurred
 */
void uhi_cdc_sof(bool b_micro);
/**@}*/

/**
 * \name UHI for Communication Device Class
 *
 * Common APIs used by high level application to use this USB host class.
 * These routines are used by memory to transfer its data
 * to/from USB CDC endpoint.
 *
 * @{
 */

/**
 * \brief Open a port of UHI CDC interface
 *
 * \param[in] port          Communication port number
 * \param[in] configuration Pointer on port configuration
 *
 * \return \c true if the port is available.
 */
bool uhi_cdc_open(uint8_t port, usb_cdc_line_coding_t *configuration);

/**
 * \brief Close a port
 *
 * \param[in] port       Communication port number
 */
void uhi_cdc_close(uint8_t port);

/**
 * \brief This function checks if a character has been received on the CDC line
 *
 * \param[in] port       Communication port number
 *
 * \return \c true if a byte is ready to be read.
 */
bool uhi_cdc_is_rx_ready(uint8_t port);

/**
 * \brief This function returns the number of character available on the CDC line
 *
 * \param[in] port       Communication port number
 *
 * \return The number of data received.
 */
iram_size_t uhi_cdc_get_nb_received(uint8_t port);

/**
 * \brief Waits and gets a value on CDC line
 *
 * \param[in] port       Communication port number
 *
 * \return Value read on CDC line.
 */
int uhi_cdc_getc(uint8_t port);

/**
 * \brief Reads a RAM buffer on CDC line
 *
 * \param[in] port      Communication port number
 * \param[out] buf      Values read
 * \param[in] size      Number of value read
 *
 * \return The number of data remaining.
 */
iram_size_t uhi_cdc_read_buf(uint8_t port, void* buf, iram_size_t size);

/**
 * \brief This function checks if a new character sent is possible
 *
 * The type int is used to support scanf redirection from compiler LIB.
 *
 * \param[in] port       Communication port number
 *
 * \return \c true if a new character can be sent.
 */
bool uhi_cdc_is_tx_ready(uint8_t port);

/**
 * \brief Puts a byte on CDC line
 *
 * The type int is used to support printf redirection from compiler LIB.
 *
 * \param[in] port       Communication port number
 * \param[in] value      Value to put
 *
 * \return \c true if function was successfully done, otherwise \c false.
 */
int uhi_cdc_putc(uint8_t port, int value);

/**
 * \brief Writes a RAM buffer on CDC line
 *
 * \param[in] port      Communication port number
 * \param[in] buf       Values to write
 * \param[in] size      Number of value to write
 *
 * \return The number of data remaining.
 */
iram_size_t uhi_cdc_write_buf(uint8_t port, const void* buf, iram_size_t size);
/**@}*/

/**@}*/

/**
 * \page asfdoc_uhi_cdc_exqsg Quick Start Guide for USB Host Communication Device Class Module (UHI CDC)
 *
 * This is the quick start guide for the \ref asfdoc_uhi_cdc_group
 * "USB Host Communication Device Class Module (UHI CDC)" with step-by-step instructions on
 * how to configure and use the modules in a selection of use cases.
 *
 * The use cases highlights several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section uhi_cdc_basic_use_case Basic Use Case
 * In this basic use case, the "USB Host CDC (Single Class support)" module is used.
 *
 * The "USB Host CDC (Multiple Classes support)" module usage is described
 * in \ref uhi_cdc_use_cases "Advanced Use Cases".
 *
 * \subsection uhi_cdc_basic_use_case_setup Setup Steps
 * As a USB host, it follows common USB host setup steps. Refer to
 * \ref asfdoc_uhc_basic_use_case_setup "USB Host Basic Setup".
 *
 * \subsection uhi_cdc_basic_use_case_usage Usage Steps
 *
 * \subsubsection uhi_cdc_basic_use_case_usage_code Example Code
 * Content of conf_usb_host.h:
 * \code
 #define USB_HOST_UHI        UHI_CDC
 #define UHI_CDC_CHANGE(dev, b_plug) my_callback_cdc_change(dev, b_plug)
 extern bool my_callback_cdc_change(uhc_device_t* dev, bool b_plug);
 #define UHI_CDC_RX_NOTIFY() my_callback_cdc_rx_notify()
 extern void my_callback_cdc_rx_notify(void);
 #include "uhi_cdc.h" // At the end of conf_usb_host.h file
 \endcode
 *
 * Add to application C-file:
 * \code
 static bool my_flag_cdc_available = false;
 bool my_callback_cdc_change(uhc_device_t* dev, bool b_plug)
 {
    if (b_plug) {

    // USB Device CDC connected
    my_flag_cdc_available = true;
    // Open and configure USB CDC ports
    usb_cdc_line_coding_t cfg = {
          .dwDTERate   = CPU_TO_LE32(115200),
          .bCharFormat = CDC_STOP_BITS_1,
          .bParityType = CDC_PAR_NONE,
          .bDataBits   = 8,
    };
    uhi_cdc_open(0, &cfg);

    } else {

    my_flag_cdc_available = false;

    }
 }

 void my_callback_cdc_rx_notify(void)
 {
    // Wakeup my_task_rx() task
 }

 #define MESSAGE "Hello"
 void my_task(void)
 {
    static bool startup = true;

    if (!my_flag_cdc_available) {
       startup = true;
       return;
    }

    if (startup) {
       startup = false;
       // Send data on CDC communication port
       uhi_cdc_write_buf(0, MESSAGE, sizeof(MESSAGE)-1);
       uhi_cdc_putc(0,'\n');
       return;
    }
 }

 void my_task_rx(void)
 {
    while (uhi_cdc_is_rx_ready(0)) {
       int value = uhi_cdc_getc(0);
    }
 }
 \endcode
 *
 * \subsubsection uhi_cdc_basic_use_case_setup_flow Workflow
 * -# Ensure that conf_usb_host.h is available and contains the following configuration
 * which is the USB host CDC configuration:
 * \code
 #define USB_HOST_UHI   UHI_CDC
 \endcode
 * \note It defines the list of UHI supported by USB host.
 *
 * \code
 #define UHI_CDC_CHANGE(dev, b_plug) my_callback_cdc_change(dev, b_plug)
 extern bool my_callback_cdc_change(uhc_device_t* dev, bool b_plug);
 \endcode
 * \note This callback is called when a USB device CDC is plugged or unplugged.
 *       The communication port can be opened and configured here.
 *
 * \code
 #define UHI_CDC_RX_NOTIFY() my_callback_cdc_rx_notify()
 extern void my_callback_cdc_rx_notify(void);
 \endcode
 * \note This callback is called when a new data are received.
 *       This can be used to manage data reception through interrupt and avoid pooling.
 *
 * -# The CDC data access functions are described in \ref asfdoc_uhi_cdc_api_overview "UHI CDC API Overview".
 *
 * \section uhi_cdc_use_cases Advanced Use Cases
 * \ifnot ASF_MANUAL
 * For more advanced use of the UHI CDC module, see the following use cases:
 * - \subpage uhc_use_case_1
 * - \subpage uhc_use_case_2
 * - \subpage uhc_use_case_3
 * \else
 * For more advanced use of the UHI CDC module, see the following:
 * - \ref asfdoc_uhc_use_cases
 * \endif
 */

/**
 * \page asfdoc_uhi_cdc_config_examples Configuration File Examples
 *
 * \section asfdoc_uhi_cdc_config_examples_1 conf_usb_host.h
 * \subsection asfdoc_uhi_cdc_config_examples_1_1  UHI CDC Single
 * \include module_config/conf_usb_host.h
 * \subsection asfdoc_uhi_cdc_config_examples_1_2  UHI CDC Multiple (Composite)
 * \include composite/host/module_config/conf_usb_host.h
 *
 * \section asfdoc_uhi_cdc_config_examples_2 conf_clock.h
 *
 * \subsection asfdoc_uhi_cdc_config_examples_2_1 AT32UC3A0, AT32UC3A1, AT32UC3B Devices (USBB)
 * \include example/at32uc3a0512_evk1100/conf_clock.h
 *
 * \subsection asfdoc_uhi_cdc_config_examples_2_2 AT32UC3A3 and AT32UC3A4 Devices (USBB with High Speed Support)
 * \include example/at32uc3a3256_evk1104/conf_clock.h
 *
 * \subsection asfdoc_uhi_cdc_config_examples_2_3 AT32UC3C, ATUCXXD, ATUCXXL3U, ATUCXXL4U Devices (USBC)
 * \include example/at32uc3c0512c_uc3c_ek/conf_clock.h
 *
 * \subsection asfdoc_uhi_cdc_config_examples_2_4 SAM3X and SAM3A Devices (UOTGHS: USB OTG High Speed)
 * \include example/sam3x8h_sam3x_ek/conf_clock.h
 *
 * \section asfdoc_uhi_cdc_config_examples_3 conf_clocks.h
 *
 * \subsection asfdoc_uhi_cdc_config_examples_3_1 SAM D21 Devices (USB)
 * \include example/samd21j18a_samd21_xplained_pro/conf_clocks.h
 *
 * \section asfdoc_uhi_cdc_config_examples_4 conf_board.h
 *
 * \subsection asfdoc_uhi_cdc_config_examples_4_1 AT32UC3A0, AT32UC3A1, AT32UC3B Devices (USBB)
 * \include example/at32uc3a0512_evk1100/conf_board.h
 *
 * \subsection asfdoc_uhi_cdc_config_examples_4_2 AT32UC3A3 and AT32UC3A4 Devices (USBB with High Speed Support)
 * \include example/at32uc3a3256_evk1104/conf_board.h
 *
 * \subsection asfdoc_uhi_cdc_config_examples_4_3 AT32UC3C, ATUCXXD, ATUCXXL3U, ATUCXXL4U Devices (USBC)
 * \include example/at32uc3c0512c_uc3c_ek/conf_board.h
 *
 * \subsection asfdoc_uhi_cdc_config_examples_4_4 SAM3X and SAM3A Devices (UOTGHS: USB OTG High Speed)
 * \include example/sam3x8h_sam3x_ek/conf_board.h
 *
 * \subsection asfdoc_uhi_cdc_config_examples_4_5 SAM D21 Devices (USB)
 * \include example/samd21j18a_samd21_xplained_pro/conf_board.h
 */

/**
 * \page asfdoc_uhi_cdc_document_revision_history Document Revision History
 *
 * <table>
 * <tr>
 *    <th>Doc. Rev.</th>
 *    <th>Date</th>
 *    <th>Comments</th>
 * </tr>
 * <tr>
 *    <td>42338B</td>
 *    <td>12/2015</td>
 *    <td>Fixed typos</td>
 * </tr>
 * <tr>
 *    <td>42338A</td>
 *    <td>12/2014</td>
 *    <td>Initial release</td>
 * </tr>
 * </table>
 */

