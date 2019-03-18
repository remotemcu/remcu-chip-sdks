/**
 * \file
 *
 * \brief Main functions for USB host unit tests
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

#include <stdio.h>
#include <asf.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <conf_test.h>
#include "delay.h"

/**
 * \mainpage ASF USB Host core unit tests
 *
 * \section intro Introduction
 * This example implements a USB host to test the USB host stack core
 * and drivers, called UHC and UHD modules.
 * This example uses the USB HID mouse driver for these tests
 * and it is associated to a specific USB device generator.
 *
 * \section startup Startup
 * First, the USB device generator firmware must be loaded
 * on an EVK1104 board, which will act as the USB device. This firmware is
 * provided in ASF,
 * see "Specific USB device generator to test USB host core".
 *
 * The USB Virtual Com Port (device) from the board is used to output
 * the test results.
 *
 * After loading the test firmware (this example), connect the board
 * (EVKxxx,...) to the USB device generator via the USB OTG cable.
 *
 * Then, the test firmware starts.
 */

//! \name Unit test configuration for AVR and SAM3/SAM4
//@{
/**
 * \def CONF_TEST_USART
 * \brief USART to redirect STDIO to
 */
/**
 * \def CONF_TEST_BAUDRATE
 * \brief Baudrate of USART
 */
/**
 * \def CONF_TEST_CHARLENGTH
 * \brief Character length (bits) of USART
 */
/**
 * \def CONF_TEST_PARITY
 * \brief Parity mode of USART
 */
/**
 * \def CONF_TEST_STOPBITS
 * \brief Stopbit configuration of USART
 */
//@}

#if (UC3C || SAM4L || SAM3XA || SAMD21 || SAML21 || SAMDA1)
// USBC(UC3C and SAM4L) have no hardware limit about endpoint size
// UOTGHS(SAM3XA) has no hardware limit about ep0
// USB(SAMD21 and SAML21) have no hardware limit about endpoint size
#  define TST_15_DIS
#endif

#if (UC3C) // USBC downstream fails (ERRATA)
#  define TST_18_DIS
#endif

#define MAIN_EVENT_HOST_MODE                     (1u<<0)
#define MAIN_EVENT_DEVICE_MODE                   (1u<<1)
#define MAIN_EVENT_VBUS_PRESENT                  (1u<<2)
#define MAIN_EVENT_VBUS_NOT_PRESENT              (1u<<3)
#define MAIN_EVENT_CONNECTION                    (1u<<4)
#define MAIN_EVENT_DISCONNECTION                 (1u<<5)
#define MAIN_EVENT_ENUM_SUCCESS_LOW_SPEEP        (1u<<6)
#define MAIN_EVENT_ENUM_SUCCESS_FULL_SPEEP       (1u<<7)
#define MAIN_EVENT_ENUM_SUCCESS_HIGH_SPEEP       (1u<<8)
#define MAIN_EVENT_ENUM_UNSUPPORTED              (1u<<9)
#define MAIN_EVENT_ENUM_OVERCURRENT              (1u<<10)
#define MAIN_EVENT_ENUM_FAIL                     (1u<<11)
#define MAIN_EVENT_ENUM_HARDWARE_LIMIT           (1u<<12)
#define MAIN_EVENT_ENUM_UNKNOW                   (1u<<13)
#define MAIN_EVENT_WAKEUP                        (1u<<14)

volatile uint32_t main_events = 0;

#if SAMD21 || SAML21 || SAMDA1
/* Structure for UART module connected to EDBG (used for unit test output) */
struct usart_module cdc_uart_module;
#endif

#if 0 // To help the debug of unit tests
#  define NB_EVENTS 250
typedef struct{
uint32_t event;
uint32_t timestamp;
}event_t;
event_t list_event[NB_EVENTS];

static void record_events(void)
{
	uint16_t i=0;
	while(1) {
		while (!main_events) {
			sleepmgr_enter_sleep(); \
		}
		if (i < NB_EVENTS) {
			// Register events
			irqflags_t flags = cpu_irq_save();
			list_event[i].event = main_events;
			list_event[i++].timestamp =
				cpu_cy_2_us(Get_system_register(AVR32_COUNT),sysclk_get_cpu_hz());
			main_events=0;
			cpu_irq_restore(flags);
		}
	}
}
#else
#  define record_events()
#endif


#define CHECK_EVENT(event,msg) \
	while (!main_events) { \
		sleepmgr_enter_sleep(); \
	} \
	if (!(main_events & event)) { \
		main_display_event(); } \
	test_assert_true(test, main_events & event, msg); \
	main_events &= (unsigned)~event;

#define CHECK_EVENT_HOST_MODE()             \
	CHECK_EVENT( MAIN_EVENT_HOST_MODE              ,"Event MAIN_EVENT_HOST_MODE               not received")
#define CHECK_EVENT_DEVICE_MODE()           \
	CHECK_EVENT( MAIN_EVENT_DEVICE_MODE            ,"Event MAIN_EVENT_DEVICE_MODE             not received")
#define CHECK_EVENT_VBUS_PRESENT()          \
	CHECK_EVENT( MAIN_EVENT_VBUS_PRESENT           ,"Event MAIN_EVENT_VBUS_PRESENT            not received")
#define CHECK_EVENT_VBUS_NOT_PRESENT()      \
	CHECK_EVENT( MAIN_EVENT_VBUS_NOT_PRESENT       ,"Event MAIN_EVENT_VBUS_NOT_PRESENT        not received")
#define CHECK_EVENT_CONNECTION()            \
	CHECK_EVENT( MAIN_EVENT_CONNECTION             ,"Event MAIN_EVENT_CONNECTION              not received")
#define CHECK_EVENT_DISCONNECTION()         \
	CHECK_EVENT( MAIN_EVENT_DISCONNECTION          ,"Event MAIN_EVENT_DISCONNECTION           not received")
#define CHECK_EVENT_ENUM_SUCCESS_LOW_SPEEP() \
	CHECK_EVENT( MAIN_EVENT_ENUM_SUCCESS_LOW_SPEEP ,"Event MAIN_EVENT_ENUM_SUCCESS_LOW_SPEEP  not received")
#define CHECK_EVENT_ENUM_SUCCESS_FULL_SPEEP() \
	CHECK_EVENT( MAIN_EVENT_ENUM_SUCCESS_FULL_SPEEP,"Event MAIN_EVENT_ENUM_SUCCESS_FULL_SPEEP not received")
#define CHECK_EVENT_ENUM_SUCCESS_HIGH_SPEEP() \
	CHECK_EVENT( MAIN_EVENT_ENUM_SUCCESS_HIGH_SPEEP,"Event MAIN_EVENT_ENUM_SUCCESS_HIGH_SPEEP not received")
#define CHECK_EVENT_ENUM_UNSUPPORTED()      \
	CHECK_EVENT( MAIN_EVENT_ENUM_UNSUPPORTED       ,"Event MAIN_EVENT_ENUM_UNSUPPORTED        not received")
#define CHECK_EVENT_ENUM_OVERCURRENT()      \
	CHECK_EVENT( MAIN_EVENT_ENUM_OVERCURRENT       ,"Event MAIN_EVENT_ENUM_OVERCURRENT        not received")
#define CHECK_EVENT_ENUM_FAIL()             \
	CHECK_EVENT( MAIN_EVENT_ENUM_FAIL              ,"Event MAIN_EVENT_ENUM_FAIL               not received")
#define CHECK_EVENT_ENUM_HARDWARE_LIMIT()   \
	CHECK_EVENT( MAIN_EVENT_ENUM_HARDWARE_LIMIT    ,"Event MAIN_EVENT_ENUM_HARDWARE_LIMIT     not received")
#define CHECK_EVENT_ENUM_UNKNOW()           \
	CHECK_EVENT( MAIN_EVENT_ENUM_UNKNOW            ,"Event MAIN_EVENT_ENUM_UNKNOW             not received")
#define CHECK_EVENT_WAKEUP()                \
	CHECK_EVENT( MAIN_EVENT_WAKEUP                 ,"Event MAIN_EVENT_WAKEUP                  not received")

static void main_display_event(void)
{
	uint32_t capture_val = main_events;
	if (capture_val & MAIN_EVENT_HOST_MODE              ) {
		printf("Event MAIN_EVENT_HOST_MODE               received\n");
	}
	if (capture_val & MAIN_EVENT_DEVICE_MODE            ) {
		printf("Event MAIN_EVENT_DEVICE_MODE             received\n");
	}
	if (capture_val & MAIN_EVENT_VBUS_PRESENT           ) {
		printf("Event MAIN_EVENT_VBUS_PRESENT            received\n");
	}
	if (capture_val & MAIN_EVENT_VBUS_NOT_PRESENT       ) {
		printf("Event MAIN_EVENT_VBUS_NOT_PRESENT        received\n");
	}
	if (capture_val & MAIN_EVENT_CONNECTION             ) {
		printf("Event MAIN_EVENT_CONNECTION              received\n");
	}
	if (capture_val & MAIN_EVENT_DISCONNECTION          ) {
		printf("Event MAIN_EVENT_DISCONNECTION           received\n");
	}
	if (capture_val & MAIN_EVENT_ENUM_SUCCESS_LOW_SPEEP ) {
		printf("Event MAIN_EVENT_ENUM_SUCCESS_LOW_SPEEP  received\n");
	}
	if (capture_val & MAIN_EVENT_ENUM_SUCCESS_FULL_SPEEP) {
		printf("Event MAIN_EVENT_ENUM_SUCCESS_FULL_SPEEP received\n");
	}
	if (capture_val & MAIN_EVENT_ENUM_SUCCESS_HIGH_SPEEP) {
		printf("Event MAIN_EVENT_ENUM_SUCCESS_HIGH_SPEEP received\n");
	}
	if (capture_val & MAIN_EVENT_ENUM_UNSUPPORTED       ) {
		printf("Event MAIN_EVENT_ENUM_UNSUPPORTED        received\n");
	}
	if (capture_val & MAIN_EVENT_ENUM_OVERCURRENT       ) {
		printf("Event MAIN_EVENT_ENUM_OVERCURRENT        received\n");
	}
	if (capture_val & MAIN_EVENT_ENUM_FAIL              ) {
		printf("Event MAIN_EVENT_ENUM_FAIL               received\n");
	}
	if (capture_val & MAIN_EVENT_ENUM_HARDWARE_LIMIT    ) {
		printf("Event MAIN_EVENT_ENUM_HARDWARE_LIMIT     received\n");
	}
	if (capture_val & MAIN_EVENT_ENUM_UNKNOW            ) {
		printf("Event MAIN_EVENT_ENUM_UNKNOW             received\n");
	}
	if (capture_val & MAIN_EVENT_WAKEUP                 ) {
		printf("Event MAIN_EVENT_WAKEUP                  received\n");
	}
}

static void run_test_start_uhc(const struct test_case *test)
{
	// Start USB host stack
	uhc_start();
	record_events();
	CHECK_EVENT_HOST_MODE();
	CHECK_EVENT_VBUS_PRESENT();
}

static void run_test_stop_uhc(const struct test_case *test)
{
	// Stop USB host stack
	uhc_stop(true);
	test_assert_true(test, main_events == 0, "A USB event has been received after USB stack stop");
}

static void run_test_disconnection(const struct test_case *test)
{
	CHECK_EVENT_CONNECTION();
	CHECK_EVENT_DISCONNECTION();
}
static void run_test_enum_fail(const struct test_case *test)
{
	CHECK_EVENT_CONNECTION();
	CHECK_EVENT_ENUM_FAIL();
	CHECK_EVENT_DISCONNECTION();
}
static void run_test_enum_overcurrent(const struct test_case *test)
{
	CHECK_EVENT_CONNECTION();
	CHECK_EVENT_ENUM_OVERCURRENT();
	CHECK_EVENT_DISCONNECTION();
}
static void run_test_enum_unsupported(const struct test_case *test)
{
	CHECK_EVENT_CONNECTION();
	CHECK_EVENT_ENUM_UNSUPPORTED();
	CHECK_EVENT_DISCONNECTION();
}
#ifndef TST_15_DIS
static void run_test_enum_hardwarelimit(const struct test_case *test)
{
	CHECK_EVENT_CONNECTION();
	CHECK_EVENT_ENUM_HARDWARE_LIMIT();
	CHECK_EVENT_DISCONNECTION();
}
#endif
static void run_test_enum_success_ls(const struct test_case *test)
{
	CHECK_EVENT_CONNECTION();
	CHECK_EVENT_ENUM_SUCCESS_LOW_SPEEP();
}
static void run_test_enum_success_fs(const struct test_case *test)
{
	CHECK_EVENT_CONNECTION();
	CHECK_EVENT_ENUM_SUCCESS_FULL_SPEEP();
}
static void run_test_enum_success_hs(const struct test_case *test)
{
	CHECK_EVENT_CONNECTION();
	CHECK_EVENT_ENUM_SUCCESS_HIGH_SPEEP();
}
static void run_test_downstream(const struct test_case *test)
{
	uhc_suspend(false);
	delay_ms(30);
	uhc_resume();
	CHECK_EVENT_WAKEUP();
}
static void run_test_downstream_disconnection(const struct test_case *test)
{
	uhc_suspend(false);
	delay_ms(30);
	uhc_resume();
	CHECK_EVENT_DISCONNECTION();
}
static void run_test_upstream_ls(const struct test_case *test)
{
	CHECK_EVENT_CONNECTION();
	CHECK_EVENT_ENUM_SUCCESS_LOW_SPEEP();
	uhc_suspend(true);
	CHECK_EVENT_WAKEUP();
}
static void run_test_upstream_fs(const struct test_case *test)
{
	CHECK_EVENT_CONNECTION();
	CHECK_EVENT_ENUM_SUCCESS_FULL_SPEEP();
	uhc_suspend(true);
	CHECK_EVENT_WAKEUP();
}
static void run_test_upstream_hs(const struct test_case *test)
{
	CHECK_EVENT_CONNECTION();
	CHECK_EVENT_ENUM_SUCCESS_HIGH_SPEEP();
	uhc_suspend(true);
	CHECK_EVENT_WAKEUP();
}
static void run_test_disconnection_in_suspend(const struct test_case *test)
{
	uhc_suspend(false);
	CHECK_EVENT_DISCONNECTION();
}

#if SAMD21 || SAML21 || SAMDA1
/**
 * \brief Initialize the USART for unit test
 *
 * Initializes the SERCOM USART used for sending the unit test status to the
 * computer via the EDBG CDC gateway.
 */
static void cdc_uart_init(void)
{
	struct usart_config usart_conf;

	/* Configure USART for unit test output */
	usart_get_config_defaults(&usart_conf);
	usart_conf.mux_setting = CONF_STDIO_MUX_SETTING;
	usart_conf.pinmux_pad0 = CONF_STDIO_PINMUX_PAD0;
	usart_conf.pinmux_pad1 = CONF_STDIO_PINMUX_PAD1;
	usart_conf.pinmux_pad2 = CONF_STDIO_PINMUX_PAD2;
	usart_conf.pinmux_pad3 = CONF_STDIO_PINMUX_PAD3;
	usart_conf.baudrate    = CONF_STDIO_BAUDRATE;

	stdio_serial_init(&cdc_uart_module, CONF_STDIO_USART, &usart_conf);
	usart_enable(&cdc_uart_module);
}
#endif

/**
 * \brief Run usb host core unit tests
 *
 * Initializes the clock system, board and serial output, then sets up the
 * usb unit test suite and runs it.
 */
int main(void)
{
#if SAMD21 || SAML21 || SAMDA1
	system_init();
	delay_init();
	cdc_uart_init();
#else
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits   = CONF_TEST_STOPBITS,
	};

	sysclk_init();
	board_init();
	delay_init(sysclk_get_cpu_hz());
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);
#endif

	irq_initialize_vectors();
	cpu_irq_enable();

	// Initialize the sleep manager
	sleepmgr_init();

	// Define all the timestamp to date test cases

	DEFINE_TEST_CASE(usb_test_start, NULL, run_test_start_uhc, NULL, "Start host stack");
	DEFINE_TEST_CASE(usb_test_stop, NULL, run_test_stop_uhc, NULL, "Stop host stack");

	DEFINE_TEST_CASE(usb_test_1 , NULL, run_test_enum_fail ,
		NULL, "1  - Attach and no response");
	DEFINE_TEST_CASE(usb_test_2 , NULL, run_test_enum_fail ,
		NULL, "2  - Disable endpoint 0 after first setup packet");
	DEFINE_TEST_CASE(usb_test_3 , NULL, run_test_disconnection ,
		NULL, "3  - Detach after first setup packet");
	DEFINE_TEST_CASE(usb_test_4 , NULL, run_test_disconnection ,
		NULL, "4  - No response data (NACK IN) after first setup packet");
	DEFINE_TEST_CASE(usb_test_5 , NULL, run_test_disconnection ,
		NULL, "5  - Detach after IN data phase of first setup request");
	DEFINE_TEST_CASE(usb_test_6 , NULL, run_test_enum_fail ,
		NULL, "6  - Wrong value in first setup request get descriptor");
	DEFINE_TEST_CASE(usb_test_7 , NULL, run_test_disconnection ,
		NULL, "7  - Detach before reset");
	DEFINE_TEST_CASE(usb_test_8 , NULL, run_test_disconnection ,
		NULL, "8  - Detach during reset after first setup request get descriptor");
	DEFINE_TEST_CASE(usb_test_9 , NULL, run_test_disconnection ,
		NULL, "9  - Detach after reset after first setup request get descriptor");
	DEFINE_TEST_CASE(usb_test_10, NULL, run_test_disconnection,
		NULL, "10 - No send ZLP (NAK IN) after second setup packet (set address)");
	DEFINE_TEST_CASE(usb_test_11, NULL, run_test_enum_fail,
		NULL, "11 - Wrong value in first setup request get configuration 0");
	DEFINE_TEST_CASE(usb_test_12, NULL, run_test_enum_fail,
		NULL, "12 - Wrong transfer value in second setup request get configuration 0");
	DEFINE_TEST_CASE(usb_test_13, NULL, run_test_enum_overcurrent,
		NULL, "13 - Too high power consumption in setup request get configuration 0");
	DEFINE_TEST_CASE(usb_test_14, NULL, run_test_enum_unsupported,
		NULL, "14 - No supported interface (interface subclass not possible)");
#ifndef TST_15_DIS
	DEFINE_TEST_CASE(usb_test_15, NULL, run_test_enum_hardwarelimit,
		NULL, "15 - HID mouse with too large endpoint size (hardware limit)");
#endif
	DEFINE_TEST_CASE(usb_test_16, NULL, run_test_enum_fail,
		NULL, "16 - Stall SET CONFIGURATION (Note SELF/300mA is tested)");
	DEFINE_TEST_CASE(usb_test_17ls, NULL, run_test_enum_success_ls,
		NULL, "17 - Regular LS enumeration");
	DEFINE_TEST_CASE(usb_test_17fs, NULL, run_test_enum_success_fs,
		NULL, "17 - Regular FS enumeration");
	DEFINE_TEST_CASE(usb_test_17hs, NULL, run_test_enum_success_hs,
		NULL, "17 - Regular HS enumeration");
	DEFINE_TEST_CASE(usb_test_18, NULL, run_test_downstream,
		NULL, "18 - Regular downstream (from Host)");
	DEFINE_TEST_CASE(usb_test_19, NULL, run_test_downstream_disconnection,
		NULL, "19 - Regular disconnection during downstream (from Host)");
	DEFINE_TEST_CASE(usb_test_20ls, NULL, run_test_upstream_ls,
		NULL, "20 - Regular upstream (from Device)");
	DEFINE_TEST_CASE(usb_test_20fs, NULL, run_test_upstream_fs,
		NULL, "20 - Regular upstream (from Device)");
	DEFINE_TEST_CASE(usb_test_20hs, NULL, run_test_upstream_hs,
		NULL, "20 - Regular upstream (from Device)");
	DEFINE_TEST_CASE(usb_test_21, NULL, run_test_disconnection_in_suspend,
		NULL, "21 - Regular disconnection during USB suspend mode");

	// Put test case addresses in an array
	DEFINE_TEST_ARRAY(usb_host_tests_host) = {
		&usb_test_start,
		// Low speed tests
		&usb_test_1 ,
		&usb_test_2 ,
		&usb_test_3 ,
		&usb_test_4 ,
		&usb_test_5 ,
		&usb_test_6 ,
		&usb_test_7 ,
		&usb_test_8 ,
		&usb_test_9 ,
		&usb_test_10,
		&usb_test_11,
		&usb_test_12,
		&usb_test_13,
		&usb_test_14,
#ifndef TST_15_DIS
		&usb_test_15,
#endif
		&usb_test_16,
		&usb_test_17ls,
#ifndef TST_18_DIS
		&usb_test_18,
#endif
		&usb_test_19,
		&usb_test_20ls,
		&usb_test_21,
		// Full speed tests
		&usb_test_1 ,
		&usb_test_2 ,
		&usb_test_3 ,
		&usb_test_4 ,
		&usb_test_5 ,
		&usb_test_6 ,
		&usb_test_7 ,
		&usb_test_8 ,
		&usb_test_9 ,
		&usb_test_10,
		&usb_test_11,
		&usb_test_12,
		&usb_test_13,
		&usb_test_14,
#ifndef TST_15_DIS
		&usb_test_15,
#endif
		&usb_test_16,
		&usb_test_17fs,
#ifndef TST_18_DIS
		&usb_test_18,
#endif
		&usb_test_19,
		&usb_test_20fs,
		&usb_test_21,
		// High speed tests
		&usb_test_1 ,
		&usb_test_2 ,
		&usb_test_3 ,
		&usb_test_4 ,
		&usb_test_5 ,
		&usb_test_6 ,
		&usb_test_7 ,
		&usb_test_8 ,
		&usb_test_9 ,
		&usb_test_10,
		&usb_test_11,
		&usb_test_12,
		&usb_test_13,
		&usb_test_14,
#ifndef TST_15_DIS
		&usb_test_15,
#endif
		&usb_test_16,
#ifndef USB_HOST_HS_SUPPORT
		&usb_test_17fs,
#else
		&usb_test_17hs,
#endif
#ifndef TST_18_DIS
		&usb_test_18,
#endif
		&usb_test_19,
#ifndef USB_HOST_HS_SUPPORT
		&usb_test_20fs,
#else
		&usb_test_20hs,
#endif
		&usb_test_21,
		&usb_test_stop,
	};

	// Define the test suite
	DEFINE_TEST_SUITE(usb_host_suite_host, usb_host_tests_host,
			"Common usb host service test suite");

	// The unit test prints message via UART which does not support deep sleep mode.
#if SAM
	sleepmgr_lock_mode(SLEEPMGR_ACTIVE);
#else
	sleepmgr_lock_mode(SLEEPMGR_IDLE);
#endif

	// Run all tests in the suite
	test_suite_run(&usb_host_suite_host);
	while (1) {
		// Intentionally left empty.
	}
}

void main_usb_mode_change(bool b_host_mode)
{
	if (b_host_mode) {
		main_events |= MAIN_EVENT_HOST_MODE;
	} else {
		main_events |= MAIN_EVENT_DEVICE_MODE;
	}
}

void main_usb_vbus_change(bool b_vbus_present)
{
	if (b_vbus_present) {
		main_events |= MAIN_EVENT_VBUS_PRESENT;
	} else {
		main_events |= MAIN_EVENT_VBUS_NOT_PRESENT;
	}
}

void main_usb_vbus_error(void)
{
}

void main_usb_connection_event(uhc_device_t *dev, bool b_present)
{
	UNUSED(dev);
	if (b_present) {
		if (main_events & MAIN_EVENT_DISCONNECTION) {
			main_events = 0; // To debounce connection state on line
		} else {
			main_events |= MAIN_EVENT_CONNECTION;
		}
	} else {
		if (main_events & MAIN_EVENT_CONNECTION) {
			main_events = 0; // To debounce connection state on line
		} else {
			main_events |= MAIN_EVENT_DISCONNECTION;
		}
	}
}

void main_usb_enum_event(uhc_device_t *dev, uhc_enum_status_t status)
{
	switch (status) {
		//! Device is bus enumerated with at least one supported interface
	case UHC_ENUM_SUCCESS:
		switch (dev->speed) {
		case UHD_SPEED_HIGH:
			main_events |= MAIN_EVENT_ENUM_SUCCESS_HIGH_SPEEP;
			break;
		case UHD_SPEED_FULL:
			main_events |= MAIN_EVENT_ENUM_SUCCESS_FULL_SPEEP;
			break;
		case UHD_SPEED_LOW:
			main_events |= MAIN_EVENT_ENUM_SUCCESS_LOW_SPEEP ;
			break;
		default:
			main_events |= MAIN_EVENT_ENUM_UNKNOW;
			break;
		}
		break;

		//! All interfaces are not supported by UHIs
	case UHC_ENUM_UNSUPPORTED:
		main_events |= MAIN_EVENT_ENUM_UNSUPPORTED;
		break;

		//! Device power can not be supported
	case UHC_ENUM_OVERCURRENT:
		main_events |= MAIN_EVENT_ENUM_OVERCURRENT;
		break;

		//! A problem has been occurred during USB enumeration
	case UHC_ENUM_FAIL:
		main_events |= MAIN_EVENT_ENUM_FAIL;
		break;

		//! USB hardware can not support it. Not enough free pipes.
	case UHC_ENUM_HARDWARE_LIMIT:
		main_events |= MAIN_EVENT_ENUM_HARDWARE_LIMIT;
		break;
	default:
		main_events |= MAIN_EVENT_ENUM_UNKNOW;
		break;
	}
}

void main_usb_wakeup_event(void)
{
	main_events |= MAIN_EVENT_WAKEUP;
}

void main_usb_sof_event(void)
{
}


