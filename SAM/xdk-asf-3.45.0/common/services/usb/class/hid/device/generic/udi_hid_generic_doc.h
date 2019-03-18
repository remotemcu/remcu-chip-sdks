/**
 * \file
 *
 * \brief USB device driver for Human Interface Device (HID) generic interface.
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
 * \defgroup asfdoc_udi_hid_generic_group USB Device Interface (UDI) for Human Interface Device Generic (HID Generic)
 *
 * USB Device Interface (UDI) for Human Interface Device generic (HID generic) provides an
 * interface for the configuration and management of USB HID generic device.
 *
 * The outline of this documentation is as follows:
 * - \ref asfdoc_udi_hid_generic_api_overview
 * - \ref asfdoc_udi_hid_generic_exqsg
 * - \ref asfdoc_udi_hid_generic_config_examples
 *
 * For more details for Atmel&reg; Software Framework (ASF) USB Device Stack and
 * USB Device HID generic, refer to following application notes:
 * - <a href="http://ww1.microchip.com/downloads/en/appnotes/doc8360.pdf">
 *   AVR4900: ASF - USB Device Stack</a>
 * - <a href="http://ww1.microchip.com/downloads/en/appnotes/doc8499.pdf">
 *   AVR4905: ASF - USB Device HID Generic Application</a>
 * - <a href="http://ww1.microchip.com/downloads/en/appnotes/doc8410.pdf">
 *   AVR4920: ASF - USB Device Stack - Compliance and Performance Figures</a>
 * - <a href="http://ww1.microchip.com/downloads/en/appnotes/doc8411.pdf">
 *   AVR4921: ASF - USB Device Stack Differences between ASF V1 and V2</a>
 *
 * \section asfdoc_udi_hid_generic_api_overview API Overview
 * @{
 */

/**
 * \name Interface with USB Device Core (UDC)
 *
 * Structure required by UDC.
 *
 * @{
 */

/** Global structure which contains standard UDI API for UDC. */
extern UDC_DESC_STORAGE udi_api_t udi_api_hid_generic;
/**@}*/

/**
 * \name USB Interface Descriptors
 *
 * The following structures provide predefined USB interface descriptors.
 * It must be used to define the final USB descriptors.
 *
 * @{
 */

 /** Interface descriptor structure for HID generic. */
typedef struct {
	/** Standard USB interface descriptor structure */
	usb_iface_desc_t iface;
	/**  HID Descriptor */
	usb_hid_descriptor_t hid;
	/** Standard USB endpoint descriptor structure */
	usb_ep_desc_t ep_in;
	/** Standard USB endpoint descriptor structure */
	usb_ep_desc_t ep_out;
} udi_hid_generic_desc_t;

/** Report descriptor for HID generic. */
typedef struct {
	/** Array to put detailed report data */
	uint8_t array[53];
} udi_hid_generic_report_desc_t;


/** By default no string associated to this interface. */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#ifndef UDI_HID_GENERIC_STRING_ID
#define UDI_HID_GENERIC_STRING_ID 0
#endif

/** Content of HID generic interface descriptor for all speed. */
#define UDI_HID_GENERIC_DESC    {\
   .iface.bLength             = sizeof(usb_iface_desc_t),\
   .iface.bDescriptorType     = USB_DT_INTERFACE,\
   .iface.bInterfaceNumber    = UDI_HID_GENERIC_IFACE_NUMBER,\
   .iface.bAlternateSetting   = 0,\
   .iface.bNumEndpoints       = 2,\
   .iface.bInterfaceClass     = HID_CLASS,\
   .iface.bInterfaceSubClass  = HID_SUB_CLASS_NOBOOT,\
   .iface.bInterfaceProtocol  = HID_PROTOCOL_GENERIC,\
   .iface.iInterface          = UDI_HID_GENERIC_STRING_ID,\
   .hid.bLength               = sizeof(usb_hid_descriptor_t),\
   .hid.bDescriptorType       = USB_DT_HID,\
   .hid.bcdHID                = LE16(USB_HID_BDC_V1_11),\
   .hid.bCountryCode          = USB_HID_NO_COUNTRY_CODE,\
   .hid.bNumDescriptors       = USB_HID_NUM_DESC,\
   .hid.bRDescriptorType      = USB_DT_HID_REPORT,\
   .hid.wDescriptorLength     = LE16(sizeof(udi_hid_generic_report_desc_t)),\
   .ep_in.bLength             = sizeof(usb_ep_desc_t),\
   .ep_in.bDescriptorType     = USB_DT_ENDPOINT,\
   .ep_in.bEndpointAddress    = UDI_HID_GENERIC_EP_IN,\
   .ep_in.bmAttributes        = USB_EP_TYPE_INTERRUPT,\
   .ep_in.wMaxPacketSize      = LE16(UDI_HID_GENERIC_EP_SIZE),\
   .ep_in.bInterval           = 4,\
   .ep_out.bLength            = sizeof(usb_ep_desc_t),\
   .ep_out.bDescriptorType    = USB_DT_ENDPOINT,\
   .ep_out.bEndpointAddress   = UDI_HID_GENERIC_EP_OUT,\
   .ep_out.bmAttributes       = USB_EP_TYPE_INTERRUPT,\
   .ep_out.wMaxPacketSize     = LE16(UDI_HID_GENERIC_EP_SIZE),\
   .ep_out.bInterval          = 4,\
   }
/**@}*/

/**
 * \name USB Device Interface (UDI) for Human Interface Device (HID) Generic Class
 *
 * Common APIs used by high level application to use this USB class.
 * @{
 */

/**
 * \brief Routine used to send a report to USB Host
 *
 * \param[in] data     Pointer on the report to send (size = UDI_HID_REPORT_IN_SIZE)
 *
 * \return \c 1 if function was successfully done, otherwise \c 0.
 */
bool udi_hid_generic_send_report_in(uint8_t *data);
/**@}*/
/**@}*/

/**
 * \page asfdoc_udi_hid_generic_exqsg Quick Start Guide for USB Device Generic Module (UDI Generic)
 *
 * This is the quick start guide for the \ref asfdoc_udi_hid_generic_group
 * "USB Device Generic Module (UDI Generic)" with step-by-step instructions on
 * how to configure and use the modules in a selection of use cases.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section udi_hid_generic_basic_use_case Basic Use Case
 * In this basic use case, the "USB HID generic (Single Interface Device)" module is used.
 * The "USB HID generic (Composite Device)" module usage is described in \ref udi_hid_generic_use_cases
 * "Advanced Use Cases".
 *
 * \section udi_hid_generic_basic_use_case_setup Setup Steps
 * As a USB device, it follows common USB device setup steps. Refer to
 * \ref asfdoc_udc_basic_use_case_setup "USB Device Basic Setup".
 *
 * \section udi_hid_generic_basic_use_case_usage Usage Steps
 *
 * \subsection udi_hid_generic_basic_use_case_usage_code Example Code
 * Content of conf_usb.h:
 * \code
 #define UDI_HID_generic_ENABLE_EXT() my_callback_generic_enable()
 extern bool my_callback_generic_enable(void);
 #define UDI_HID_generic_DISABLE_EXT() my_callback_generic_disable()
 extern void my_callback_generic_disable(void);
 #include "udi_hid_generic_conf.h" // At the end of conf_usb.h file
 \endcode
 *
 * Add to application C-file:
 * \code
 #define UDI_HID_GENERIC_ENABLE_EXT() my_callback_generic_enable()
 extern bool my_callback_generic_enable(void);
 #define UDI_HID_GENERIC_DISABLE_EXT() my_callback_generic_disable()
 extern void my_callback_generic_disable(void);
 #define  UDI_HID_GENERIC_REPORT_OUT(ptr) my_callback_generic_report_out(ptr)
 extern void my_callback_generic_report_out(uint8_t *report);
 #define  UDI_HID_GENERIC_SET_FEATURE(f) my_callback_generic_set_feature(f)
 extern void my_callback_generic_set_feature(uint8_t *report_feature);

 #define  UDI_HID_REPORT_IN_SIZE             64
 #define  UDI_HID_REPORT_OUT_SIZE            64
 #define  UDI_HID_REPORT_FEATURE_SIZE        4
 #define  UDI_HID_GENERIC_EP_SIZE            64

 #include "udi_hid_generic_conf.h" // At the end of conf_usb.h file
 \endcode
 *
 * Add to application C-file:
 * \code
 static bool my_flag_autorize_generic_events = false;
 bool my_callback_generic_enable(void)
 {
    my_flag_autorize_generic_events = true;
    return true;
 }
 void my_callback_generic_disable(void)
 {
    my_flag_autorize_generic_events = false;
 }

 void my_button_press_event(void)
 {
    if (!my_flag_autorize_generic_events) {
       return;
    }
    uint8_t report[] = {0x00,0x01,0x02...};
    udi_hid_generic_send_report_in(report);
 }

 void my_callback_generic_report_out(uint8_t *report)
 {
    if ((report[0] == MY_VALUE_0)
        (report[1] == MY_VALUE_1)) {
       // The report is correct
    }
 }

 void my_callback_generic_set_feature(uint8_t *report_feature)
 {
    if ((report_feature[0] == MY_VALUE_0)
        (report_feature[1] == MY_VALUE_1)) {
       // The report feature is correct
    }
 }
 \endcode
 *
 * \subsection udi_hid_generic_basic_use_case_setup_flow Workflow
 * -# Ensure that conf_usb.h is available and contains the following configuration
 * which is the USB device generic configuration:
 * \code
 #define UDI_HID_GENERIC_ENABLE_EXT() my_callback_generic_enable()
 extern bool my_callback_generic_enable(void);
 \endcode
 * \note After the device enumeration (detecting and identifying USB devices),
 *       the USB host starts the device configuration. When the USB generic interface
 *       from the device is accepted by the host, the USB host enables this interface and the
 *       UDI_HID_GENERIC_ENABLE_EXT() callback function is called and return true.
 *       Thus, it is recommended to enable sensors used by the generic in this function.
 *
 * \code
 #define UDI_HID_GENERIC_DISABLE_EXT() my_callback_generic_disable()
 extern void my_callback_generic_disable(void);
 \endcode
 * \note When the USB device is unplugged or is reset by the USB host, the USB
 *       interface is disabled and the UDI_HID_GENERIC_DISABLE_EXT() callback function
 *       is called. Thus, it is recommended to disable sensors used by the HID generic
 *       interface in this function.
 *
 * \code
 #define  UDI_HID_GENERIC_REPORT_OUT(ptr) my_callback_generic_report_out(ptr)
 extern void my_callback_generic_report_out(uint8_t *report);
 \endcode
 * \note Callback used to receive the OUT report.
 *
 * \code
 #define  UDI_HID_GENERIC_SET_FEATURE(f) my_callback_generic_set_feature(f)
 extern void my_callback_generic_set_feature(uint8_t *report_feature);
 \endcode
 * \note Callback used to receive the SET FEATURE report.
 *
 * \code
 #define  UDI_HID_REPORT_IN_SIZE             64
 #define  UDI_HID_REPORT_OUT_SIZE            64
 #define  UDI_HID_REPORT_FEATURE_SIZE        4
 \endcode
 * \note The report size are defined by the final application.
 *
 * \code
 #define  UDI_HID_GENERIC_EP_SIZE 64
 \endcode
 * \note The interrupt endpoint size is defined by the final application.

 * -# Send a IN report:
 * \code
 uint8_t report[] = {0x00,0x01,0x02...};
 udi_hid_generic_send_report_in(report);
 \endcode
 *
 * \section udi_hid_generic_use_cases Advanced Use Cases
 * \ifnot ASF_MANUAL
 * For more advanced use of the UHI HID generic module, see the following use cases:
 * - \subpage udi_hid_generic_use_case_composite
 * - \subpage udc_use_case_1
 * - \subpage udc_use_case_2
 * - \subpage udc_use_case_3
 * - \subpage udc_use_case_5
 * - \subpage udc_use_case_6
 * \else
 * For multiple interface use of UDI HID module, see the following:
 * - \subpage udi_hid_generic_use_case_composite
 *
 * For more advanced use of the UDI HID generic module, see the following:
 * - \ref asfdoc_udc_use_cases
 * \endif
 */

/**
 * \page udi_hid_generic_use_case_composite HID Generic in a Composite Device
 *
 * A USB Composite Device is a USB Device which uses more than one USB class.
 * In this use case, the "USB HID Generic (Composite Device)" module is used to
 * create a USB composite device. Thus, this USB module can be associated with
 * another "Composite Device" module, like "USB MSC (Composite Device)".
 *
 * Also, you can refer to application note
 * <A href="http://ww1.microchip.com/downloads/en/appnotes/doc8445.pdf">
 * AVR4902 ASF - USB Composite Device</A>.
 *
 * \section udi_hid_generic_use_case_composite_setup Setup Steps
 * For the setup code of this use case to work, the
 * \ref udi_hid_generic_basic_use_case "Basic Use Case" must be followed.
 *
 * \section udi_hid_generic_use_case_composite_usage Usage Steps
 *
 * \subsection udi_hid_generic_use_case_composite_usage_code Example Code
 * Content of conf_usb.h:
 * \code
 #define USB_DEVICE_EP_CTRL_SIZE  64
 #define USB_DEVICE_NB_INTERFACE (X+1)
 #define USB_DEVICE_MAX_EP (X+2)

 #define UDI_HID_GENERIC_EP_IN    (1 | USB_EP_DIR_IN)
 #define UDI_HID_GENERIC_EP_OUT   (2 | USB_EP_DIR_OUT)
 #define UDI_HID_GENERIC_IFACE_NUMBER  X

 #define UDI_COMPOSITE_DESC_T \
    udi_hid_generic_desc_t udi_hid_generic; \
    ...
 #define UDI_COMPOSITE_DESC_FS \
    .udi_hid_generic = UDI_HID_GENERIC_DESC, \
    ...
 #define UDI_COMPOSITE_DESC_HS \
    .udi_hid_generic = UDI_HID_GENERIC_DESC, \
    ...
 #define UDI_COMPOSITE_API \
    &udi_api_hid_generic, \
    ...
 \endcode
 *
 * \subsection udi_hid_generic_use_case_composite_usage_flow Workflow
 * -# Ensure that conf_usb.h is available and contains the following parameters
 * required for a USB composite device configuration:
 * \code
 // Endpoint control size, This must be:
 // - 8 for low speed
 // - 8, 16, 32 or 64 for full speed device (8 is recommended to save RAM)
 // - 64 for a high speed device
 #define USB_DEVICE_EP_CTRL_SIZE  64
 // Total Number of interfaces on this USB device.
 // Add 1 for HID generic.
 #define USB_DEVICE_NB_INTERFACE (X+1)
 // Total number of endpoints on this USB device.
 // This must include each endpoint for each interface.
 // Add 1 for HID generic.
 #define USB_DEVICE_MAX_EP (X+2)
 \endcode
 * -# Ensure that conf_usb.h contains the description of
 * composite device:
 * \code
 // The endpoint number chosen by you for the generic.
 // The endpoint number starting from 1.
 #define UDI_HID_GENERIC_EP_IN    (1 | USB_EP_DIR_IN)
 #define UDI_HID_GENERIC_EP_OUT   (2 | USB_EP_DIR_OUT)
 // The interface index of an interface starting from 0
 #define UDI_HID_GENERIC_IFACE_NUMBER  X
 \endcode
 * -# Ensure that conf_usb.h contains the following parameters
 * required for a USB composite device configuration:
 * \code
	// USB Interfaces descriptor structure
	#define UDI_COMPOSITE_DESC_T \
	   ...
	   udi_hid_generic_desc_t udi_hid_generic; \
	   ...
	// USB Interfaces descriptor value for Full Speed
	#define UDI_COMPOSITE_DESC_FS \
	   ...
	   .udi_hid_generic = UDI_HID_GENERIC_DESC, \
	   ...
	// USB Interfaces descriptor value for High Speed
	#define UDI_COMPOSITE_DESC_HS \
	   ...
	   .udi_hid_generic = UDI_HID_GENERIC_DESC, \
	   ...
	// USB Interface APIs
	#define UDI_COMPOSITE_API \
	   ...
	   &udi_api_hid_generic, \
	   ...
 \endcode
 * \note The descriptors order given in the four lists above must be the
 *       same as the order defined by all interface indexes. The interface index
 *       orders are defined through UDI_X_IFACE_NUMBER defines.
 */

/**
 * \page asfdoc_udi_hid_generic_config_examples Configuration File Examples
 *
 * \section asfdoc_udi_hid_generic_config_examples_1 conf_usb.h
 * \subsection asfdoc_udi_hid_generic_config_examples_1_1  UDI HID GENERIC Single
 * \include module_config/conf_usb.h
 * \subsection asfdoc_udi_hid_generic_config_examples_1_2  UDI HID GENERIC Multiple (Composite)
 * \include composite/device/module_config/conf_usb.h
 *
 * \section asfdoc_udi_hid_generic_config_examples_2 conf_clock.h
 *
 * \subsection asfdoc_udi_hid_generic_config_examples_2_1 AT32UC3C, ATUCXXD, ATUCXXL3U, ATUCXXL4U Devices (USBC)
 * \include example/at32uc3c0512c_uc3c_ek/conf_clock.h
 *
 * \subsection asfdoc_udi_hid_generic_config_examples_2_2 SAM3X and SAM3A Devices (UOTGHS: USB OTG High Speed)
 * \include example/sam3x8h_sam3x_ek/conf_clock.h
 *
 * \section asfdoc_udi_hid_generic_config_examples_3 conf_clocks.h
 *
 * \subsection asfdoc_udi_hid_generic_config_examples_3_1 SAM D21 Device (USB)
 * \include example/samd21j18a_samd21_xplained_pro/conf_clocks.h
 *
 * \section asfdoc_udi_hid_generic_config_examples_4 conf_board.h
 *
 * \subsection asfdoc_udi_hid_generic_config_examples_4_1 AT32UC3C, ATUCXXD, ATUCXXL3U, ATUCXXL4U Devices (USBC)
 * \include example/at32uc3c0512c_uc3c_ek/conf_board.h
 *
 * \subsection asfdoc_udi_hid_generic_config_examples_4_2 SAM3X and SAM3A Devices (UOTGHS: USB OTG High Speed)
 * \include example/sam3x8h_sam3x_ek/conf_board.h
 *
 * \subsection asfdoc_udi_hid_generic_config_examples_4_3 SAM D21 Device (USB)
 * \include example/samd21j18a_samd21_xplained_pro/conf_board.h
 */

/**
 * \page asfdoc_udi_hid_generic_document_revision_history Document Revision History
 *
 * <table>
 * <tr>
 *    <th>Doc. Rev.</th>
 *    <th>Date</th>
 *    <th>Comments</th>
 * </tr>
 * <tr>
 *    <td>42339B</td>
 *    <td>12/2015</td>
 *    <td>Fixed typos</td>
 * </tr>
 * <tr>
 *    <td>42339A</td>
 *    <td>12/2014</td>
 *    <td>Initial release</td>
 * </tr>
 * </table>
 */