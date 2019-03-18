/**
 * \file
 *
 * \brief Main functions to generate USB patterns
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

#include "compiler.h"
#include "preprocessor.h"
#include "board.h"
#include "gpio.h"
#include "sysclk.h"
#if SAM3XA
#include "uotghs_otg.h"
#include "uotghs_device.h"
#else
#include "usbb_otg.h"
#include "usbb_device.h"
#endif
#include "usb_protocol.h"
#include "usb_protocol_hid.h"
#include "delay.h"

/**
 * \mainpage ASF USB Host core unit tests
 *
 * \section intro Introduction
 * This example implements the USB device generator used by
 * the USB host core test.
 *
 * \section startup Startup
 * The default compilation option is to support all Atmel MCU with a USB
 * hardware interface with DPRAM.
 * For other Atmel MCU a compilation opotion must be defined in the
 * unit_tests.c file:
 * - #define  AVR32_USBC_TST     // AVR32 MCU with USBC interface
 * - #define  SAMX_UOTGHS_TST    // SAM MCU with UOTGHS interface
 * - #define  SAM4L_USBC_TST     // SAM4L MCU with USBC interface
 * - #define  SAMD21_USB_TST     // SAMD21 MCU with USB interface
 * - #define  SAML21_USB_TST     // SAML21 MCU with USB interface
 *
 * Please, read "USB host core tests" project documentation for more information.
 */

//#define  AVR32_USBC_TST     // AVR32 MCU with USBC interface
//#define  SAMX_UOTGHS_TST    // SAM MCU with UOTGHS interface
//#define  SAM4L_USBC_TST     // SAM4L MCU with USBC interface
//#define  SAMD21_USB_TST     // SAMD21 MCU with USB interface
#define  SAML21_USB_TST     // SAML21 MCU with USB interface

#ifdef AVR32_USBC_TST
#  define TST_15_DIS
#  define TST_18_DIS
#endif
#ifdef SAMX_UOTGHS_TST
#  define TST_15_DIS
#endif
#if defined(SAM4L_USBC_TST) || defined(SAMD21_USB_TST) || defined(SAML21_USB_TST)
#  define TST_15_DIS
#endif

#if defined(SAM4L_USBC_TST) || defined(SAMD21_USB_TST) || defined(SAML21_USB_TST)
#  define TST_DETACH_DELAY 800 // Delay more since clock slow
#else
#  define TST_DETACH_DELAY 200
#endif

#define  USB_DEVICE_VENDOR_ID             USB_VID_ATMEL
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_ASF_HIDMOUSE
#define  USB_DEVICE_MAJOR_VERSION         1
#define  USB_DEVICE_MINOR_VERSION         0
#define  USB_DEVICE_POWER                 100 // Consumption on Vbus line (mA)
#define  USB_DEVICE_ATTR                  \
	(USB_CONFIG_ATTR_REMOTE_WAKEUP|USB_CONFIG_ATTR_BUS_POWERED)
//(USB_CONFIG_ATTR_REMOTE_WAKEUP|USB_CONFIG_ATTR_SELF_POWERED)
//(USB_CONFIG_ATTR_REMOTE_WAKEUP|USB_CONFIG_ATTR_BUS_POWERED)
//(USB_CONFIG_ATTR_SELF_POWERED)
//(USB_CONFIG_ATTR_BUS_POWERED)

//! USB test speed (0:LS, 1:FS, 2:HS)
static uint8_t speed;
static usb_setup_req_t main_setup_packet;

//! USB HID mouse device descriptor
COMPILER_WORD_ALIGNED
usb_dev_desc_t main_device_desc = {
	.bLength                   = sizeof(usb_dev_desc_t),
	.bDescriptorType           = USB_DT_DEVICE,
	.bcdUSB                    = LE16(USB_V2_0),
	.bDeviceClass              = 0,
	.bDeviceSubClass           = 0,
	.bDeviceProtocol           = 0,
	.bMaxPacketSize0           = 0,
	.idVendor                  = LE16(USB_DEVICE_VENDOR_ID),
	.idProduct                 = LE16(USB_DEVICE_PRODUCT_ID),
	.bcdDevice                 = LE16((USB_DEVICE_MAJOR_VERSION << 8)
			| USB_DEVICE_MINOR_VERSION),
	.iManufacturer             = 0,  // No manufacture string
	.iProduct                  = 0,  // No product string
	.iSerialNumber             = 0,  // No serial string
	.bNumConfigurations        = 1
};

//! USB HID mouse configuration descriptor struct
typedef struct {
	usb_conf_desc_t conf;
	usb_iface_desc_t iface;
	usb_hid_descriptor_t hid;
	usb_ep_desc_t ep;
} main_conf_desc_t;

//! Report descriptor for HID mouse
typedef struct {
	// 52 is the byte size of the standard HID mouse report descriptor
	// defined in USB HID specification.
	uint8_t array[52];
} udi_hid_mouse_report_desc_t;

//! USB HID mouse configuration descriptor default definition
static main_conf_desc_t main_conf_desc = {
	.conf.bLength              = sizeof(usb_conf_desc_t),
	.conf.bDescriptorType      = USB_DT_CONFIGURATION,
	.conf.wTotalLength         = LE16(sizeof(main_conf_desc_t)),
	.conf.bNumInterfaces       = 0,
	.conf.bConfigurationValue  = 1,
	.conf.iConfiguration       = 0,
	.conf.bmAttributes         = USB_CONFIG_ATTR_MUST_SET | USB_DEVICE_ATTR,
	.conf.bMaxPower            = USB_CONFIG_MAX_POWER(USB_DEVICE_POWER),
	.iface.bLength             = sizeof(usb_iface_desc_t),
	.iface.bDescriptorType     = USB_DT_INTERFACE,
	.iface.bInterfaceNumber    = 0,
	.iface.bAlternateSetting   = 0,
	.iface.bNumEndpoints       = 1,
	.iface.bInterfaceClass     = HID_CLASS,
	.iface.bInterfaceSubClass  = HID_SUB_CLASS_BOOT,
	.iface.bInterfaceProtocol  = HID_PROTOCOL_MOUSE,
	.iface.iInterface          = 0,
	.hid.bLength               = sizeof(usb_hid_descriptor_t),
	.hid.bDescriptorType       = USB_DT_HID,
	.hid.bcdHID                = LE16(USB_HID_BDC_V1_11),
	.hid.bCountryCode          = USB_HID_NO_COUNTRY_CODE,
	.hid.bNumDescriptors       = USB_HID_NUM_DESC,
	.hid.bRDescriptorType      = USB_DT_HID_REPORT,
	.hid.wDescriptorLength     = LE16(sizeof(udi_hid_mouse_report_desc_t)),
	.ep.bLength                = sizeof(usb_ep_desc_t),
	.ep.bDescriptorType        = USB_DT_ENDPOINT,
	.ep.bEndpointAddress       = (1 | USB_EP_DIR_IN),
	.ep.bmAttributes           = USB_EP_TYPE_INTERRUPT,
	.ep.wMaxPacketSize         = LE16(8),
	.ep.bInterval              = 10,
};

//! \name Routines USB low level
//! @{

//! \brief Reset and initialize USB OTG peripheral to specified speed mode
static void main_otg_init(void)
{
	otg_disable();
	delay_ms(10);
	otg_enable();

	otg_disable_id_pin();
	otg_force_device_mode();
	otg_enable_pad();
	otg_enable();

	switch (speed) {
	// LS speed
	case 0:
		udd_low_speed_enable();
		udd_high_speed_disable();
		break;
	// FS speed
	case 1:
		udd_low_speed_disable();
		udd_high_speed_disable();
		break;
	// HS speed
	case 2:
		udd_low_speed_disable();
		udd_high_speed_enable();
		break;
	default:
		Assert(false);
		break;
	}

	otg_unfreeze_clock();
	(void)Is_otg_clock_frozen();
}

//! \brief Waits the start of USB reset signal
//! This routine waits the end of SOF
static void main_usb_wait_reset_start(void)
{
	do {
		udd_ack_sof();
		delay_ms(2);
	} while (Is_udd_sof());
}

//! \brief Waits the end of USB reset signal
static void main_usb_wait_end_of_reset(void)
{
	while (!Is_udd_reset()) {};
	udd_ack_reset();
}

//! \brief Waits a USB suspend mode
static void main_usb_wait_suspend(void)
{
	udd_ack_suspend();
	while (!Is_udd_suspend()) {
	}
	udd_ack_suspend();
}

//! \brief Waits a USB downstream resume signal from host
static void main_usb_wait_resume(void)
{
	udd_ack_resume();
	while (!Is_udd_resume()) {
	}
	udd_ack_resume();
}

//! \brief Waits a USB wakeup signal
static void main_usb_wait_wakeup(void)
{
	udd_ack_wake_up();
	while (!Is_udd_wake_up()) {
	}
	udd_ack_wake_up();
}

//! \brief Waits a USB start of frame (or 1ms for USB low speed)
static void main_usb_wait_sof(void)
{
	if (Is_udd_low_speed_enable()) {
		delay_ms(1); // No SOF in Low Speed, replaced by equ. time delay
		return;
	}
	udd_ack_sof();
	while (!Is_udd_sof()) {
	}
	udd_ack_sof();
}

//! \brief Detaches the USB device of the USB line (= remove USB pull_up)
static void main_detach(void)
{
	udd_detach_device();
	delay_ms(TST_DETACH_DELAY);
}

/**
 * \brief Allocation of the control endpoint
 *
 * \param address USB address of endpoint
 * \param ep_size control endpoint size
 */
static void main_usb_enable_ctrl_ep(uint8_t address, uint8_t ep_size)
{
	// Configure USB address
	udd_disable_address();
	udd_configure_address(address);
	udd_enable_address();

	// Alloc and configure control endpoint
	udd_disable_endpoint(0);
	udd_unallocate_memory(0);
#if SAM3XA
	udd_configure_endpoint(0,
			USB_EP_TYPE_CONTROL,
			0,
			ep_size,
			UOTGHS_DEVEPTCFG_EPBK_1_BANK);
#else
	udd_configure_endpoint(0,
			USB_EP_TYPE_CONTROL,
			0,
			ep_size, AVR32_USBB_UECFG0_EPBK_SINGLE);
#endif
	udd_allocate_memory(0);
	udd_enable_endpoint(0);
}

//! \brief Waits a SETUP packet and load data in main_setup_packet[]
static void main_usb_wait_setup_packet(void)
{
	while (!Is_udd_setup_received(0));

	// SETUP packet received
	Assert(8 == udd_byte_count(0));

	uint8_t *ptr = (uint8_t *) & udd_get_endpoint_fifo_access(0,8);
	for (uint8_t i = 0; i < 8; i++) {
		((uint8_t*) &main_setup_packet)[i] = *ptr++;
	}
	udd_ack_setup_received(0);
}

//! \brief Enables the control endpoint STALL after a SETUP packet reception
static void main_usb_stall_after_setup_packet(void)
{
	udd_enable_stall_handshake(0);
	udd_ack_setup_received(0);
}

/**
 * \brief Waits a DATA IN packets on control endpoint
 *
 * \param payload RAM buffer to store data received
 * \param size    Size of RAM buffer waiting
 */
static void main_usb_send_in(uint8_t *payload, uint8_t size)
{
	uint8_t *ptr_dest;

	do {
		while (!Is_udd_in_send(0));

		// Fill buffer of endpoint control
		ptr_dest = (uint8_t *) & udd_get_endpoint_fifo_access(0, 8);

		// Write quickly the IN data
		for (uint8_t i = 0; (i<udd_get_endpoint_size(0)) && size; i++) {
			*ptr_dest++ = *payload++;
			size--;
		}
		// Validate and send the data available in the control endpoint buffer
		udd_ack_in_send(0);
	} while (size);

	while (!Is_udd_in_send(0));
}

/**
 * \brief Sends a DATA OUT packets on control endpoint
 *
 * \param payload Data buffer to send
 * \param size    Size of buffer
 */
static void main_usb_wait_out(uint8_t *payload, uint8_t size)
{
	uint8_t nb_data;

	do {
		while (!Is_udd_out_received(0));

		// Read data received during OUT phase
		nb_data = udd_byte_count(0);
		uint8_t *ptr_src = (uint8_t *) & udd_get_endpoint_fifo_access(0, 8);
		for (uint8_t i = 0; (i < nb_data) && size; i++) {
			*payload++ = *ptr_src++;
			size--;
		}
		// Send IN ZLP to ACK setup request
		udd_ack_out_received(0);
	} while(size);
}
//! @}

//! \name Routines for each step of USB enumeration from USB Host stack core
//! @{

//! \brief step1 of enumeration - wait a USB reset
static void main_usb_enum_step1(void)
{
	main_usb_wait_end_of_reset();
}

//! \brief step2 of enumeration - IDLE 20ms
static void main_usb_enum_step2(void)
{
	main_usb_wait_sof(); // 20ms
}

//! \brief step3 of enumeration - wait a USB reset
static void main_usb_enum_step3(void)
{
	main_usb_wait_end_of_reset();
}

//! \brief step4 of enumeration - IDLE 100ms and initialize control endpoint
static void main_usb_enum_step4(void)
{
	main_usb_enable_ctrl_ep(0, (speed==0)?8:64);
	main_usb_wait_sof(); // 100ms
}

//! \brief step5 of enumeration - Get incomplete USB device descriptor
static void main_usb_enum_step5(void)
{
	// Get Device Descriptor
	main_usb_wait_setup_packet();
	main_device_desc.bDescriptorType = USB_DT_DEVICE;
	main_device_desc.bMaxPacketSize0 = (speed==0)?8:64;
	main_usb_send_in((uint8_t*)&main_device_desc,8);
	main_usb_wait_out(NULL,0);
}

//! \brief step6 of enumeration - IDLE 20ms
static void main_usb_enum_step6(void)
{
	main_usb_wait_sof(); // 20ms
}

//! \brief step7 of enumeration - wait a USB reset
static void main_usb_enum_step7(void)
{
	main_usb_wait_end_of_reset();
}

//! \brief step8 of enumeration - IDLE 100ms
static void main_usb_enum_step8(void)
{
	main_usb_wait_sof(); // 100ms
}

//! \brief step9 of enumeration - Reception of the Set address setup request
static void main_usb_enum_step9(void)
{
	main_usb_enable_ctrl_ep(0, (speed==0)?8:64);

	// Set address
	main_usb_wait_setup_packet();
	main_usb_send_in(NULL,0);

	main_usb_enable_ctrl_ep(le16_to_cpu(main_setup_packet.wValue), (speed==0)?8:64);
}

//! \brief step10 of enumeration - IDLE 20ms
static void main_usb_enum_step10(void)
{
	main_usb_wait_sof(); // 20ms
}

//! \brief step11 of enumeration - Reception of the full Get device descriptor
static void main_usb_enum_step11(void)
{
	// Get full device descriptor
	main_usb_wait_setup_packet();
	main_device_desc.bDescriptorType = USB_DT_DEVICE;
	main_device_desc.bMaxPacketSize0 = (speed==0)?8:64;
	main_usb_send_in((uint8_t*)&main_device_desc, sizeof(main_device_desc));
	main_usb_wait_out(NULL,0);
}

//! \brief step12 of enumeration - Get first struct of USB configuration descriptor
static void main_usb_enum_step12(void)
{
	main_usb_wait_setup_packet();
	main_conf_desc.conf.bDescriptorType = USB_DT_CONFIGURATION;
	main_conf_desc.conf.bLength         = sizeof(usb_conf_desc_t);
	main_conf_desc.conf.bMaxPower       = USB_CONFIG_MAX_POWER(USB_DEVICE_POWER);
	main_conf_desc.conf.bmAttributes         = USB_CONFIG_ATTR_MUST_SET | USB_DEVICE_ATTR,
	main_usb_send_in((uint8_t*)&main_conf_desc, sizeof(usb_conf_desc_t));
	main_usb_wait_out(NULL,0);
}

//! \brief step13 of enumeration - Get all USB configuration descriptor
static void main_usb_enum_step13(void)
{
	// Get configuration descriptor
	main_usb_wait_setup_packet();
	main_conf_desc.conf.bLength         = sizeof(usb_conf_desc_t);
	main_conf_desc.conf.bDescriptorType = USB_DT_CONFIGURATION;
	main_conf_desc.conf.bMaxPower       = USB_CONFIG_MAX_POWER(USB_DEVICE_POWER),
	main_conf_desc.conf.bmAttributes         = USB_CONFIG_ATTR_MUST_SET | USB_DEVICE_ATTR,
	main_conf_desc.iface.bInterfaceProtocol  = HID_PROTOCOL_MOUSE;
	main_conf_desc.ep.wMaxPacketSize         = LE16(8);
	main_usb_send_in((uint8_t*)&main_conf_desc, sizeof(main_conf_desc));
	main_usb_wait_out(NULL,0);
}

//! \brief step14 of enumeration - Reception of the Set configuration setup request
static void main_usb_enum_step14(void)
{
	main_usb_wait_setup_packet();
	main_usb_send_in(NULL,0);
}
//! @}


//! \name Tests of USB Host stack core
//! @{

//! \brief Test 1 - Attach and no response
static void main_test1(void)
{
	uint8_t nb_fail;

	udd_attach_device();
	nb_fail = 4;
	while (nb_fail--) {
		udd_disable_endpoint(0);
		udd_unallocate_memory(0);
		main_usb_enum_step1();
		main_usb_enum_step2();
		main_usb_enum_step3();
		// Here Host try to communicate on control endpoint 0
	}
	main_usb_wait_suspend();
	main_detach();
}
//! \brief Test 2  - Disable endpoint 0 after first setup packet
static void main_test2(void)
{
	uint8_t nb_fail;

	udd_attach_device();
	nb_fail = 4;
	while (nb_fail--) {
		main_usb_enum_step1();
		main_usb_enum_step2();
		main_usb_enum_step3();
		main_usb_enum_step4();
		main_usb_wait_setup_packet();
		udd_disable_endpoint(0);
		// Here Host try to send IN on control endpoint 0
	}
	main_usb_wait_suspend();
	main_detach();
}
//! \brief Test 3  - Detach after first setup packet
static void main_test3(void)
{
	udd_attach_device();
	main_usb_enum_step1();
	main_usb_enum_step2();
	main_usb_enum_step3();
	main_usb_enum_step4();
	main_usb_wait_setup_packet();
	main_usb_wait_sof();
	main_detach();
}

//! \brief Test 4  - No response data (NACK IN) after first setup packet
static void main_test4(void)
{
	main_otg_init();
	udd_attach_device();
	main_usb_enum_step1();
	main_usb_enum_step2();
	main_usb_enum_step3();
	main_usb_enum_step4();
	main_usb_wait_setup_packet();
	main_usb_enum_step1();
	main_usb_enum_step2();
	main_detach();
}

//! \brief Test 5  - Detach after IN data phase of first setup request
static void main_test5(void)
{
	main_otg_init();
	udd_attach_device();
	main_usb_enum_step1();
	main_usb_enum_step2();
	main_usb_enum_step3();
	main_usb_enum_step4();

	// Get Device Descriptor
	main_usb_wait_setup_packet();
	main_device_desc.bDescriptorType = USB_DT_DEVICE;
	main_device_desc.bMaxPacketSize0 = (speed==0)?8:64;
	main_usb_send_in((uint8_t*)&main_device_desc,8);
	main_detach();
}
//! \brief Test 6  - Wrong value in first setup request get descriptor
static void main_test6(void)
{
	uint8_t nb_fail;

	main_otg_init();
	udd_attach_device();
	nb_fail = 4;
	while (nb_fail--) {
		main_usb_enum_step1();
		main_usb_enum_step2();
		main_usb_enum_step3();
		main_usb_enum_step4();

		// Get Device Descriptor
		main_usb_wait_setup_packet();
		main_device_desc.bDescriptorType = 0xFF;
		main_device_desc.bMaxPacketSize0 = 0xFF;
		main_usb_send_in((uint8_t*)&main_device_desc,8);
		main_usb_wait_out(NULL,0);
	}
	main_usb_wait_suspend();
	main_detach();
}
//! \brief Test 7  - Detach before reset
static void main_test7(void)
{
	udd_attach_device();
	main_usb_enum_step1();
	main_usb_enum_step2();
	main_usb_enum_step3();
	main_usb_enum_step4();
	main_usb_enum_step5();
	main_usb_wait_sof();
	main_detach();
}
//! \brief Test 8  - Detach during reset after first setup request get descriptor
static void main_test8(void)
{
	main_otg_init();
	udd_attach_device();
	main_usb_enum_step1();
	main_usb_enum_step2();
	main_usb_enum_step3();
	main_usb_enum_step4();
	main_usb_enum_step5();
	main_usb_enum_step6();
	if (Is_udd_low_speed_enable()) {
		delay_ms(25);
	} else {
		main_usb_wait_reset_start();
	}
	main_detach();
	udd_ack_reset(); // Ack previous reset finish by detach
}
//! \brief Test 9  - Detach after reset after first setup request get descriptor
static void main_test9(void)
{
	main_otg_init();
	udd_attach_device();
	main_usb_enum_step1();
	main_usb_enum_step2();
	main_usb_enum_step3();
	main_usb_enum_step4();
	main_usb_enum_step5();
	main_usb_enum_step6();
	main_usb_enum_step7();
	main_usb_wait_sof();
	main_detach();
}

//! \brief Test 10 - No send ZLP (NAK IN) after second setup packet (set address)
static void main_test10(void)
{
	main_otg_init();
	udd_attach_device();
	main_usb_enum_step1();
	main_usb_enum_step2();
	main_usb_enum_step3();
	main_usb_enum_step4();
	main_usb_enum_step5();
	main_usb_enum_step6();
	main_usb_enum_step7();
	main_usb_enum_step8();
	main_usb_enable_ctrl_ep(0, (speed==0)?8:64);
	main_usb_wait_setup_packet();
	main_usb_enum_step1();
	main_usb_enum_step2();
	main_detach();
}
//! \brief Test 11 - Wrong value in first setup request get configuration 0
static void main_test11(void)
{
	uint8_t nb_fail;

	main_otg_init();
	udd_attach_device();
	nb_fail = 4;
	while (nb_fail--) {
		main_usb_enum_step1();
		main_usb_enum_step2();
		main_usb_enum_step3();
		main_usb_enum_step4();
		main_usb_enum_step5();
		main_usb_enum_step6();
		main_usb_enum_step7();
		main_usb_enum_step8();
		main_usb_enum_step9();
		main_usb_enum_step10();
		main_usb_enum_step11();

		// Get configuration descriptor
		main_usb_wait_setup_packet();
		main_conf_desc.conf.bDescriptorType = 0xFF;
		main_conf_desc.conf.bMaxPower       = USB_CONFIG_MAX_POWER(USB_DEVICE_POWER);
		main_conf_desc.conf.bmAttributes         = USB_CONFIG_ATTR_MUST_SET | USB_DEVICE_ATTR,
		main_usb_send_in((uint8_t*)&main_conf_desc, sizeof(usb_conf_desc_t));
		main_usb_wait_out(NULL,0);
	}
	main_usb_wait_suspend();
	main_detach();
}
//! \brief Test 12 - Wrong transfer value in second setup request get configuration 0
static void main_test12(void)
{
	uint8_t nb_fail;

	udd_attach_device();
	nb_fail = 4;
	while (nb_fail--) {
		main_usb_enum_step1();
		main_usb_enum_step2();
		main_usb_enum_step3();
		main_usb_enum_step4();
		main_usb_enum_step5();
		main_usb_enum_step6();
		main_usb_enum_step7();
		main_usb_enum_step8();
		main_usb_enum_step9();
		main_usb_enum_step10();
		main_usb_enum_step11();
		main_usb_enum_step12();

		// Get configuration descriptor
		main_usb_wait_setup_packet();
		main_conf_desc.conf.bDescriptorType = USB_DT_CONFIGURATION;
		main_conf_desc.conf.bMaxPower       = USB_CONFIG_MAX_POWER(USB_DEVICE_POWER);
		main_conf_desc.conf.bmAttributes         = USB_CONFIG_ATTR_MUST_SET | USB_DEVICE_ATTR,
		main_conf_desc.iface.bInterfaceProtocol  = HID_PROTOCOL_MOUSE;
		main_usb_send_in((uint8_t*)&main_conf_desc, sizeof(main_conf_desc)-7);
		main_usb_wait_out(NULL,0);
	}
	main_usb_wait_suspend();
	main_detach();
}
//! \brief Test 13 - To high power consumption in setup request get configuration 0
static void main_test13(void)
{
	udd_attach_device();
	main_usb_enum_step1();
	main_usb_enum_step2();
	main_usb_enum_step3();
	main_usb_enum_step4();
	main_usb_enum_step5();
	main_usb_enum_step6();
	main_usb_enum_step7();
	main_usb_enum_step8();
	main_usb_enum_step9();
	main_usb_enum_step10();
	main_usb_enum_step11();

	// Get configuration descriptor
	main_usb_wait_setup_packet();
	main_conf_desc.conf.bDescriptorType = USB_DT_CONFIGURATION;
	main_conf_desc.conf.bMaxPower       = USB_CONFIG_MAX_POWER(300);
	main_conf_desc.conf.bmAttributes         = USB_CONFIG_ATTR_MUST_SET | USB_DEVICE_ATTR,
	main_usb_send_in((uint8_t*)&main_conf_desc, sizeof(usb_conf_desc_t));
	main_usb_wait_out(NULL,0);
	main_usb_wait_suspend();
	main_detach();
}
//! \brief Test 14 - No supported interface (!=HID mouse)
static void main_test14(void)
{
	udd_attach_device();
	main_usb_enum_step1();
	main_usb_enum_step2();
	main_usb_enum_step3();
	main_usb_enum_step4();
	main_usb_enum_step5();
	main_usb_enum_step6();
	main_usb_enum_step7();
	main_usb_enum_step8();
	main_usb_enum_step9();
	main_usb_enum_step10();
	main_usb_enum_step11();
	main_usb_enum_step12();

	// Get configuration descriptor
	main_usb_wait_setup_packet();
	main_conf_desc.conf.bDescriptorType = USB_DT_CONFIGURATION;
	main_conf_desc.conf.bMaxPower       = USB_CONFIG_MAX_POWER(USB_DEVICE_POWER),
	main_conf_desc.conf.bmAttributes         = USB_CONFIG_ATTR_MUST_SET | USB_DEVICE_ATTR,
	main_conf_desc.iface.bInterfaceProtocol  = 0xFF;
	main_conf_desc.ep.wMaxPacketSize         = LE16(8);
	main_usb_send_in((uint8_t*)&main_conf_desc, sizeof(main_conf_desc));
	main_usb_wait_out(NULL,0);
	main_usb_wait_suspend();
	main_detach();
}
//! \brief Test 15 - HID mouse with too large endpoint size (USBB hardware limit)
static void main_test15(void)
{
	udd_attach_device();
	main_usb_enum_step1();
	main_usb_enum_step2();
	main_usb_enum_step3();
	main_usb_enum_step4();
	main_usb_enum_step5();
	main_usb_enum_step6();
	main_usb_enum_step7();
	main_usb_enum_step8();
	main_usb_enum_step9();
	main_usb_enum_step10();
	main_usb_enum_step11();
	main_usb_enum_step12();

	// Get configuration descriptor
	main_usb_wait_setup_packet();
	main_conf_desc.conf.bDescriptorType = USB_DT_CONFIGURATION;
	main_conf_desc.conf.bMaxPower       = USB_CONFIG_MAX_POWER(USB_DEVICE_POWER),
	main_conf_desc.conf.bmAttributes         = USB_CONFIG_ATTR_MUST_SET | USB_DEVICE_ATTR,
	main_conf_desc.iface.bInterfaceProtocol  = HID_PROTOCOL_MOUSE;
	main_conf_desc.ep.wMaxPacketSize         = LE16(1023);
	main_usb_send_in((uint8_t*)&main_conf_desc, sizeof(main_conf_desc));
	main_usb_wait_out(NULL,0);
	main_usb_wait_suspend();
	main_detach();
}
//! \brief Test 16 - Stall SET CONFIGURATION (with configuration in SELF + 300mA -> must be pass)
static void main_test16(void)
{
	uint8_t nb_fail;

	udd_attach_device();
	nb_fail = 4;
	while (nb_fail--) {
		main_usb_enum_step1();
		main_usb_enum_step2();
		main_usb_enum_step3();
		main_usb_enum_step4();
		main_usb_enum_step5();
		main_usb_enum_step6();
		main_usb_enum_step7();
		main_usb_enum_step8();
		main_usb_enum_step9();
		main_usb_enum_step10();
		main_usb_enum_step11();
		main_usb_enum_step12();
		// Get configuration descriptor
		main_usb_wait_setup_packet();
		main_conf_desc.conf.bDescriptorType = USB_DT_CONFIGURATION;
		main_conf_desc.conf.bMaxPower       = USB_CONFIG_MAX_POWER(300),
		main_conf_desc.conf.bmAttributes         = USB_CONFIG_ATTR_MUST_SET | USB_CONFIG_ATTR_SELF_POWERED;
		main_conf_desc.iface.bInterfaceProtocol  = HID_PROTOCOL_MOUSE;
		main_conf_desc.ep.wMaxPacketSize         = LE16(8);
		main_usb_send_in((uint8_t*)&main_conf_desc, sizeof(main_conf_desc));
		main_usb_wait_out(NULL,0);
		// Set configuration
		main_usb_wait_setup_packet();
		main_usb_stall_after_setup_packet();
	}
	main_usb_wait_suspend();
	main_detach();
}
//! \brief Test 17 - Enumeration success (with configuration in BUS + 100mA -> must be pass)
static void main_test17(void)
{
	udd_attach_device();
	main_usb_enum_step1();
	main_usb_enum_step2();
	main_usb_enum_step3();
	main_usb_enum_step4();
	main_usb_enum_step5();
	main_usb_enum_step6();
	main_usb_enum_step7();
	main_usb_enum_step8();
	main_usb_enum_step9();
	main_usb_enum_step10();
	main_usb_enum_step11();
	main_usb_enum_step12();
	main_usb_enum_step13();
	main_usb_enum_step14();
}

//! \brief Test 18 - Test downstream resume (from USB host)
static void main_test18(void)
{
	main_usb_wait_suspend();
	main_usb_wait_wakeup();

	// Setup clear remotewakeup
	main_usb_wait_setup_packet();
	main_usb_send_in(NULL,0);
}

//! \brief Test 19 - Test disconnection during downstream resume (from USB host)
static void main_test19(void)
{
	main_usb_wait_suspend();
	main_usb_wait_wakeup();
	main_detach();
}

//! \brief Test 20 - Test upstream resume (from USB device)
static void main_test20(void)
{
	main_otg_init();
	udd_attach_device();
	main_usb_enum_step1();
	main_usb_enum_step2();
	main_usb_enum_step3();
	main_usb_enum_step4();
	main_usb_enum_step5();
	main_usb_enum_step6();
	main_usb_enum_step7();
	main_usb_enum_step8();
	main_usb_enum_step9();
	main_usb_enum_step10();
	main_usb_enum_step11();
	main_usb_enum_step12();
	main_usb_enum_step13();
	main_usb_enum_step14();

	// Setup set remotewakeup
	main_usb_wait_setup_packet();
	main_usb_send_in(NULL,0);

	main_usb_wait_suspend();
	delay_ms(100);

	udd_initiate_remote_wake_up();
	main_usb_wait_wakeup();
	main_usb_wait_sof();

	// Setup clear remotewakeup
	main_usb_wait_setup_packet();
	main_usb_send_in(NULL,0);
}

//! \brief Test 21 - Test detach during suspend
static void main_test21(void)
{
	main_usb_wait_suspend();
	delay_ms(50);
	main_detach();
}
//! @}

/*! \brief Main function. Execution starts here.
 */
int main(void)
{
	sysclk_init();
	board_init();
	delay_init(sysclk_get_cpu_hz());

	sysclk_enable_usb();

	// Enable USB hardware
#if SAM
	pmc_enable_periph_clk(ID_UOTGHS);
#endif

	// Execute all USB core tests for each USB speed (low, full and high)
	for (speed = 0; speed < 3; speed++) {

		main_otg_init();

		main_test1();
		main_test2();
		main_test3();
		main_test4();
		main_test5();
		main_test6();
		main_test7();
		main_test8();
		main_test9();
		main_test10();
		main_test11();
		main_test12();
		main_test13();
		main_test14();
#ifndef TST_15_DIS
		main_test15();
#endif
		main_test16();
		main_test17();
#ifndef TST_18_DIS
		main_test18();
#endif
		main_test19();
		main_test20();
		main_test21();
	}
	while(1);
}

