/**
 * \file
 *
 * \brief Unit tests for ili93xx driver.
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

#include "asf.h"
#include "conf_test.h"
#include "smc.h"
#include "ili9325_regs.h"
#include "ili9341_regs.h"

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the ili9325 driver.
 * It consists of test cases for the following functionality:
 * - ili93xx init
 * - ili93xx control setting
 * - ili93xx data read/write
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 *
 * \section device_info Device Info
 * SAM3S ans SAM4E devices can be used.
 * This example has been tested with the following setup:
 * - sam4e16e_sam4e_ek
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for ARM. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */

/* ! \name Unit test configuration */
/* @{ */
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
/* @} */

/** Chip select number to be set */
#define ILI93XX_LCD_CS      1

/** RGB888 to RGB565 filter */
#define DATA_FILTER        0x00F8FCF8

struct ili93xx_opt_t g_ili93xx_display_opt;

/**
 * \brief Read data from LCD Register.
 *
 * \param reg Register address.
 *
 * \return Read data.
 */
static uint16_t ili93xx_read_register(uint8_t uc_reg)
{
	uint16_t value;

	LCD_IR(0);
	LCD_IR(uc_reg);

	value = LCD_RD();
	value = (value << 8) | LCD_RD();

	return value;
}

static uint8_t ili93xx_read_register_byte(uint8_t uc_reg)
{
	uint8_t value;

	LCD_IR(0);
	LCD_IR(uc_reg);

	LCD_RD();
	value = LCD_RD();

	return value;
}
/**
 * \brief Test ili9325 initialization setting
 *
 * This test call the initialization function and check the setting value.
 *
 * \param test Current test case.
 */
static void run_test_init(const struct test_case *test)
{
	volatile uint16_t register_value;
	volatile uint8_t register_value_byte;

	/** Test1: Check the initialize function */
	g_ili93xx_display_opt.ul_width = ILI93XX_LCD_WIDTH;
	g_ili93xx_display_opt.ul_height = ILI93XX_LCD_HEIGHT;
	g_ili93xx_display_opt.foreground_color = COLOR_BLACK;
	g_ili93xx_display_opt.background_color = COLOR_WHITE;

	/** Switch off backlight */
	aat31xx_disable_backlight();

	/** Initialize LCD */
	ili93xx_init(&g_ili93xx_display_opt);

	/** Set backlight level */
	aat31xx_set_backlight(AAT31XX_AVG_BACKLIGHT_LEVEL);

	ili93xx_set_foreground_color(COLOR_BLUE);
	ili93xx_draw_filled_rectangle(0, 0, ILI93XX_LCD_WIDTH,
	ILI93XX_LCD_HEIGHT);

	if(ili93xx_device_type() == DEVICE_TYPE_ILI9325){

	/** Check the important none zero setting registers */
	register_value = ili93xx_read_register(ILI9325_DISP_CTRL1);
	test_assert_true(test, register_value == (ILI9325_DISP_CTRL1_GON |
			ILI9325_DISP_CTRL1_DTE | ILI9325_DISP_CTRL1_D(0x03)),
			"R07H initialization setting failed!");
	register_value = ili93xx_read_register(ILI9325_DRIVER_OUTPUT_CTRL1);
	test_assert_true(test, register_value == ILI9325_DRIVER_OUTPUT_CTRL1_SS,
			"R01H initialization setting failed!");
	register_value = ili93xx_read_register(ILI9325_LCD_DRIVING_CTRL);
	test_assert_true(test, register_value == 0x0700,
			"R02H initialization setting failed!");
	register_value = ili93xx_read_register(ILI9325_DISP_CTRL2);
	test_assert_true(test, register_value == 0x0207,
			"R08H initialization setting failed!");
	register_value = ili93xx_read_register(ILI9325_POWER_CTRL2);
	test_assert_true(test, register_value == 0x0227,
			"R11H initialization setting failed!");
	register_value = ili93xx_read_register(ILI9325_POWER_CTRL3);
	test_assert_true(test, register_value == 0x001B,
			"R12H initialization setting failed!");
	register_value = ili93xx_read_register(ILI9325_POWER_CTRL4);
	test_assert_true(test, register_value == 0x1100,
			"R13H initialization setting failed!");
	register_value = ili93xx_read_register(ILI9325_POWER_CTRL7);
	test_assert_true(test, register_value == 0x0019,
			"R29H initialization setting failed!");
	register_value = ili93xx_read_register(ILI9325_FRAME_RATE_AND_COLOR_CTRL);
	test_assert_true(test, register_value == 0x000D,
			"R2BH initialization setting failed!");
	register_value = ili93xx_read_register(ILI9325_ENTRY_MODE);
	test_assert_true(test, register_value == (ILI9325_ENTRY_MODE_TRI |
					ILI9325_ENTRY_MODE_DFM | ILI9325_ENTRY_MODE_ID(0x01) |
					ILI9325_ENTRY_MODE_BGR),
			"R03H initialization setting failed!");
	register_value = ili93xx_read_register(ILI9325_DRIVER_OUTPUT_CTRL2);
	test_assert_true(test,
			register_value == (ILI9325_DRIVER_OUTPUT_CTRL2_GS |
			ILI9325_DRIVER_OUTPUT_CTRL2_NL(0x27)),
			"R60H initialization setting failed!");
	register_value = ili93xx_read_register(ILI9325_BASE_IMG_DISP_CTRL);
	test_assert_true(test, register_value == 0x0001,
			"R61H initialization setting failed!");
	register_value = ili93xx_read_register(ILI9325_PANEL_INTERFACE_CTRL1);
	test_assert_true(test, register_value == 0x0010,
			"R90H initialization setting failed!");
	register_value = ili93xx_read_register(ILI9325_PANEL_INTERFACE_CTRL2);
	test_assert_true(test, register_value == 0x0600,
			"R92H initialization setting failed!");
	register_value = ili93xx_read_register(ILI9325_PANEL_INTERFACE_CTRL4);
	test_assert_true(test, register_value == 0x0110,
			"R95H initialization setting failed!");
	}else if(ili93xx_device_type() == DEVICE_TYPE_ILI9341){

	register_value_byte =
		ili93xx_read_register_byte(ILI9341_CMD_READ_DISP_POWER_MODE);
	test_assert_true(test, register_value_byte == 0x9C,
			"R0AH initialization setting failed");

	register_value_byte =
		ili93xx_read_register_byte(ILI9341_CMD_READ_DISP_MADCTRL);
	test_assert_true(test, register_value_byte == 0x48,
			"R0BH initialization setting failed");
		register_value_byte =
		ili93xx_read_register_byte(ILI9341_CMD_READ_DISP_PIXEL_FORMAT);
	test_assert_true(test, register_value_byte == 0x06,
			"R0CH initialization setting failed");
	register_value_byte =
		ili93xx_read_register_byte(ILI9341_CMD_READ_DISP_IMAGE_FORMAT);
	test_assert_true(test, register_value_byte == 0x00,
			"R0DH initialization setting failed");
	register_value_byte =
		ili93xx_read_register_byte(ILI9341_CMD_READ_DISP_SIGNAL_MODE);
	test_assert_true(test, register_value_byte == 0x00,
			"R0EH initialization setting failed");
	}
}

/**
 * \brief Test control API functions
 *
 * This test call the control API functions and check the setting value.
 *
 * \param test Current test case.
 */
static void run_test_control_setting(const struct test_case *test)
{
	volatile uint16_t register_value;

	/** Test1: Check the ili93xx_display_on() function */
	ili93xx_display_on();
	if(ili93xx_device_type() == DEVICE_TYPE_ILI9325){
		register_value = ili93xx_read_register(ILI9325_DISP_CTRL1);
		test_assert_true(test, register_value == (ILI9325_DISP_CTRL1_BASEE |
			ILI9325_DISP_CTRL1_GON | ILI9325_DISP_CTRL1_DTE |
			ILI9325_DISP_CTRL1_D(0x03)),
			"ili9325_display_on() function failed!");
	}else if(ili93xx_device_type() == DEVICE_TYPE_ILI9341){
		uint8_t value[5];
		LCD_IR(0);
		LCD_IR(ILI9341_CMD_READ_DISP_STATUS);

		value[0] = LCD_RD();
		value[1] = LCD_RD();
		value[2] = LCD_RD();
		value[3] = LCD_RD();
		value[4] = LCD_RD();

		test_assert_true(test, (value[3] & 0x04) == 0x04,
				 "ili93XX_display_on() function failed!");
	}
}

/**
 * \brief Test data read/write API functions
 *
 * This test call the data read/write API functions and check the data consistence.
 *
 * \param test Current test case.
 */
static void run_test_data_read_write(const struct test_case *test)
{
	volatile ili93xx_color_t data;

	/** Test1: Check the one pixel read/write function */
	ili93xx_set_foreground_color(COLOR_SKYBLUE);
	ili93xx_draw_pixel(0, 0);
	data = ili93xx_get_pixel(0, 0);

	test_assert_true(test, (data & DATA_FILTER)==
		(COLOR_SKYBLUE & DATA_FILTER), "Data is not consistent!");
}

/**
 * \brief Run ili93xx driver unit tests
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits   = CONF_TEST_STOPBITS
	};

	sysclk_init();
	board_init();

	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/** Enable peripheral clock */
	pmc_enable_periph_clk(ID_SMC);

	/** Configure SMC interface for Lcd */
	smc_set_setup_timing(SMC,ILI93XX_LCD_CS,SMC_SETUP_NWE_SETUP(2)
			| SMC_SETUP_NCS_WR_SETUP(2)
			| SMC_SETUP_NRD_SETUP(2)
			| SMC_SETUP_NCS_RD_SETUP(2));
	smc_set_pulse_timing(SMC, ILI93XX_LCD_CS , SMC_PULSE_NWE_PULSE(4)
			| SMC_PULSE_NCS_WR_PULSE(4)
			| SMC_PULSE_NRD_PULSE(10)
			| SMC_PULSE_NCS_RD_PULSE(10));
	smc_set_cycle_timing(SMC, ILI93XX_LCD_CS, SMC_CYCLE_NWE_CYCLE(10)
			| SMC_CYCLE_NRD_CYCLE(22));
#if (!defined(SAM4S)) && (!defined(SAM4E))
	smc_set_mode(SMC, ILI93XX_LCD_CS, SMC_MODE_READ_MODE
			| SMC_MODE_WRITE_MODE
			| SMC_MODE_DBW_8_BIT);
#else
	smc_set_mode(SMC, ILI93XX_LCD_CS, SMC_MODE_READ_MODE
			| SMC_MODE_WRITE_MODE);
#endif
	/** Define all the test cases */
	DEFINE_TEST_CASE(ili93xx_test_init, NULL, run_test_init, NULL,
			"ili93xx initialization test");
	DEFINE_TEST_CASE(ili93xx_test_control_setting, NULL,
			run_test_control_setting, NULL,
			"ili93xx control setting test");
	DEFINE_TEST_CASE(ili93xx_test_data_read_write, NULL,
			run_test_data_read_write, NULL,
			"ili93xx data read/write test");

	/** Put test case addresses in an array */
	DEFINE_TEST_ARRAY(ili93xx_test_array) = {
		&ili93xx_test_init,
		&ili93xx_test_control_setting,
		&ili93xx_test_data_read_write,};

	/** Define the test suite */
	DEFINE_TEST_SUITE(ili93xx_suite, ili93xx_test_array,
			"ili93xx driver test suite");

	/** Run all tests in the test suite */
	test_suite_run(&ili93xx_suite);

	while (1) {
		/** Busy-wait forever. */
	}
}
