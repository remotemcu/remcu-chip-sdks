/**
 * \file
 *
 * \brief Unit test for PARC driver
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

#include <asf.h>
#include "conf_test.h"

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the PARC driver.
 * It contains 3 test case for the PARC module:
 * - Test PARC register write/read function.
 * - Test PARC data capture in polling way.
 * - Test PARC data capture in callback way.
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_uart_serial.h
 *
 * \section device_info Device Info
 * Only SAM4L devices can be used.
 * The unit tests have been tested with the following setup:
 * - sam4lc4c_sam4l_xplained_pro
 * - sam4lc8c_sam4l8_xplained_pro
 *
 * \section connection Board Connection
 * The connections on SAM4L Xplained Pro or SAM4L8 Xplained Pro should be:
 *  EXT3-P9 (PIN_PA06) -- EXT3-P15(PCCK)
 *  EXT1-P7 (PIN_PC00) -- EXT3-P8 (PCDATA0)
 *  EXT1-P8 (PIN_PC01) -- EXT3-P10(PCDATA1)
 *  EXT1-P6 (PIN_PC02) -- EXT4-P15(PCDATA2)
 *  EXT1-P15(PIN_PC03) -- EXT4-P7 (PCDATA3)
 *  EXT2-P7 (PIN_PC04) -- EXT4-P8 (PCDATA4)
 *  EXT2-P8 (PIN_PC05) -- EXT4-P10(PCDATA6)
 *  EXT2-P9 (PIN_PC06) -- EXT4-P9 (PCDATA7)
 *  EXT4-P5 (PIN_PC17) -- EXT4-P18(PCEN1)
 *  EXT4-P6 (PIN_PC18) -- EXT4-P17(PCEN2)
 * Please note the PCDATA5 is only connected to LCD connector (EXT5)
 * which can not be connected easily by plugging wires. So in this example
 * PCDATA5 is nor required to be connected.
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for ARM. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */

/* delay time between two captures */
#define DELAY_TIME          100

/* PARC module instance*/
struct parc_module module_inst;
/** PARC configure stuct */
struct parc_config config;

uint32_t captured_data = 0;
static bool callback_data_ready = false;


/**
 * \brief PARC input signal generating through GPIO port.
 *
 * \param risingedge  PARC sampling edge, rising edge(true),fall edge (false)
 * \param data        Data to send
 */
static void parc_port_input_simulation(bool risingedge, uint32_t data)
{
	/* PCCK signal simulation */
	if (risingedge) {
		ioport_set_pin_level(PIN_PCCK, IOPORT_PIN_LEVEL_LOW);
	} else {
		ioport_set_pin_level(PIN_PCCK, IOPORT_PIN_LEVEL_HIGH);
	}

	/* Place the data on port */
	place_data_to_port(data);

	/* PCCK signal simulation */
	if (risingedge) {
		ioport_set_pin_level(PIN_PCCK, IOPORT_PIN_LEVEL_HIGH);
	} else {
		ioport_set_pin_level(PIN_PCCK, IOPORT_PIN_LEVEL_LOW);
	}
}

/**
 * \brief Test PARC functions in polling way.
 *
 * \param test Current test case.
 */
static void run_parc_polled_test(const struct test_case *test)
{
	uint32_t input_data = 0x01;

	/* PARC config */
	parc_get_config_defaults(&config);
	parc_init(&module_inst, PARC, &config);
	parc_enable(&module_inst);
	parc_start_capture(&module_inst);

	for (uint32_t i = 0; i < 8; i++) {
		parc_port_input_simulation(true, input_data);
		delay_ms(DELAY_TIME);
		test_assert_true(test, parc_is_data_ready(&module_inst) == true,
				"Capture on rising edge failure!");
		parc_read(&module_inst, &captured_data);
		test_assert_true(test, captured_data == (input_data & DATA_MASK),
				"Wrong captured data!");
		input_data = 1 << i;
	}
	parc_stop_capture(&module_inst);
	parc_disable(&module_inst);
}

/**
 * \brief callback handler for PARC data ready interrupt.
 *
 * \param module The parc_module instance.
 */
static void parc_complete_callback(struct parc_module *const module)
{
	callback_data_ready = true;
	parc_read(module, &captured_data);
}

/**
 * \brief Test PARC functions in callback way.
 *
 * \param test Current test case.
 */
static void run_parc_callback_test(const struct test_case *test)
{
	uint32_t input_data = 0x01;
	parc_get_config_defaults(&config);
	parc_init(&module_inst, PARC, &config);
	parc_enable(&module_inst);

	parc_register_callback(&module_inst,
			(parc_callback_t)parc_complete_callback, PARC_CALLBACK_DATA_READY);
	parc_enable_interrupts(&module_inst, PARC_INTERRUPT_DRDY);
	parc_enable_callback(&module_inst, PARC_CALLBACK_DATA_READY);
	parc_start_capture(&module_inst);

	for (uint32_t i = 0; i < 8; i++) {
		callback_data_ready = false;
		parc_port_input_simulation(true, input_data);
		delay_ms(DELAY_TIME);
		test_assert_true(test, callback_data_ready == true,
				"Capture data failure");
		test_assert_true(test, captured_data == (input_data & DATA_MASK),
				"Wrong captured data!");
		input_data = 1 << i;
	}
	parc_disable_interrupts(&module_inst, PARC_INTERRUPT_DRDY);
	parc_disable_callback(&module_inst,PARC_CALLBACK_DATA_READY);
	parc_stop_capture(&module_inst);
	parc_disable(&module_inst);
}

/**
 * \brief Test PARC register write/read.
 *
 * \param test Current test case.
 */
static void run_parc_ctrl_test(const struct test_case *test)
{
	parc_get_config_defaults(&config);
	parc_init(&module_inst, PARC, &config);
	parc_enable(&module_inst);

	test_assert_true(test, parc_get_status(&module_inst) == PARC_STATUS_EN,
			"Test PARC enable: enable failed");

	parc_start_capture(&module_inst);
	test_assert_true(test, parc_get_status(&module_inst) ==
			(PARC_STATUS_CS | PARC_STATUS_EN),
			"Test PARC start: start failed");
	parc_stop_capture(&module_inst);
	parc_disable(&module_inst);
}

/**
 * \brief Run PARC driver unit tests.
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_UART_BAUDRATE,
		.charlength = CONF_UART_CHAR_LENGTH,
		.paritytype = CONF_UART_PARITY,
		.stopbits   = CONF_UART_STOP_BITS
	};
	/* Initialize the SAM system. */
	sysclk_init();
	board_init();
	/* Configure console USART. */
	stdio_serial_init(CONF_UART, &usart_serial_options);

	parc_port_source_simulation_config();

	/* Define all the test cases. */
	DEFINE_TEST_CASE(parc_ctrl_test, NULL, run_parc_ctrl_test, NULL,
			"SAM PARC enable/disable test");
	DEFINE_TEST_CASE(parc_polled_test, NULL, run_parc_polled_test, NULL,
			"SAM PARC polled test.");
	DEFINE_TEST_CASE(parc_callback_test, NULL, run_parc_callback_test, NULL,
			"SAM PARC callback test.");

	/* Put test case addresses in an array. */
	DEFINE_TEST_ARRAY(parc_tests) = {
		&parc_ctrl_test,
		&parc_polled_test,
		&parc_callback_test
	};

	/* Define the test suite. */
	DEFINE_TEST_SUITE(parc_suite, parc_tests, "SAM PARC driver test suite");

	/* Run all tests in the test suite. */
	test_suite_run(&parc_suite);

	while(1){
		/* Busy-wait forever. */
	}
}
