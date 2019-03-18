/**
 * \file
 *
 * \brief Unit tests for OV7740 driver.
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
 * \mainpage Unit tests for OV7740 driver.
 *
 * \section Purpose
 *
 * This is the unit test application for the OV7740 driver.
 * It consists of test cases for the following functionality:
 * - OV7740 color test
 *
 * \section Requirements
 *
 * This package can be used with sam4s_wpir_rd board.
 *
 * \section Description
 *
 * This Units test first sets the PLLB to the system core clock and PLLA to
 * clock PCK0 (used to get data from image sensor). Then UART console is
 * configured to display information about the unit test.
 * Next step is to initialize OV7740 cmos image sensor with a special test
 * configuration. With this configuration the same picture will be received
 * from sensor. This picture is a reference picture with 8 different color
 * (black, blue, red, purple, green, cyan, yellow, white).
 * Finaly this Unit test configures PIO capture, and capture the reference
 * picture data from image sensor and compare it with the reference value
 * to check if the image sensor and PIO capture are operating fine.
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include <unit_test/suite.h>
#include "stdio_serial.h"
#include "conf_board.h"
#include "conf_clock.h"
#include "conf_test.h"

#ifndef PIO_PCMR_DSIZE_WORD
#  define PIO_PCMR_DSIZE_WORD PIO_PCMR_DSIZE(2)
#endif

/* TWI clock frequency in Hz (400KHz). */
#define TWI_CLK     (400000UL)

/* Buffer which contains data of one third of the picture. */
uint8_t g_auc_capture_buffer[51200];

/* Vsync signal information (true if it's triggered and false otherwise). */
static volatile uint32_t g_ul_vsync_flag = false;

/* Initialization status (true if it's triggered and false otherwise). */
static volatile uint32_t g_ul_init_error_flag = false;

/* Value in YUV format for black color. */
const uint8_t g_auc_data_black_color[4] = {
	0xFF, /* Y1 value */
	0x80, /* U value */
	0xFF, /* Y2 value */
	0x80  /* V value */
};

/* Value in YUV format for blue color. */
const uint8_t g_auc_data_blue_color[4] = {
	0xE5, /* Y1 value */
	0x04, /* U value */
	0xE5, /* Y2 value */
	0x90  /* V value */
};

/* Value in YUV format for red color. */
const uint8_t g_auc_data_red_color[4] = {
	0xBD, /* Y1 value */
	0x94, /* U value */
	0xBD, /* Y2 value */
	0x04  /* V value */
};

/* Value in YUV format for purple color. */
const uint8_t g_auc_data_purple_color[4] = {
	0xA3, /* Y1 value */
	0x04, /* U value */
	0xA3, /* Y2 value */
	0x04  /* V value */
};

/* Value in YUV format for green color. */
const uint8_t g_auc_data_green_color[4] = {
	0x88, /* Y1 value */
	0xFB, /* U value */
	0x88, /* Y2 value */
	0xFB  /* V value */
};

/* Value in YUV format for cyan color. */
const uint8_t g_auc_data_cyan_color[4] = {
	0x6F, /* Y1 value */
	0x6F, /* U value */
	0x6F, /* Y2 value */
	0xFB  /* V value */
};

/* Value in YUV format for yellow color. */
const uint8_t g_auc_data_yellow_color[4] = {
	0x49, /* Y1 value */
	0xFB, /* U value */
	0x49, /* Y2 value */
	0x72  /* V value */
};

/* Value in YUV format for white color. */
const uint8_t g_auc_data_white_color[4] = {
	0x33, /* Y1 value */
	0x80, /* U value */
	0x33, /* Y2 value */
	0x80  /* V value */
};

/* Define UART configuration. */
const usart_serial_options_t usart_serial_options = {
	.baudrate   = CONF_TEST_BAUDRATE,
	.charlength = CONF_TEST_CHARLENGTH,
	.paritytype = CONF_TEST_PARITY,
	.stopbits   = CONF_TEST_STOPBITS
};

/**
 * \brief Vertical synchronisation handler for the OV7740 image sensor.
 */
static void vsync_handler(uint32_t ul_id, uint32_t ul_mask)
{
	UNUSED(ul_id) ;
	UNUSED(ul_mask) ;

	g_ul_vsync_flag=true;
}

/**
 * \brief Intialize Vsync_Handler.
 */
static void init_vsync_interrupts(void)
{
	/* Initialize PIO interrupt handlers, see PIO definition in conf_board.h
	**/
	pio_handler_set(OV7740_VSYNC_PIO, OV7740_VSYNC_ID, OV7740_VSYNC_MASK,
			OV7740_VSYNC_TYPE, vsync_handler);

	/* Enable PIO controller IRQs */
	NVIC_EnableIRQ((IRQn_Type)OV7740_VSYNC_ID);
}

/**
 * \brief Initialize PIO capture for the OV7740 image sensor communication.
 *
 * \param p_pio PIO instance to be configured in PIO capture mode.
 * \param ul_id Corresponding PIO ID.
 */
static void pio_capture_init(Pio* const p_pio, uint32_t ul_id)
{
	/* Enable peripheral clock */
	pmc_enable_periph_clk(ul_id);

	/* Disable PIO capture */
	p_pio->PIO_PCMR &= ~((uint32_t)PIO_PCMR_PCEN);

	/* Disable rxbuff interrupt */
	p_pio->PIO_PCIDR = PIO_PCIDR_RXBUFF;

	/* 32bit width */
	p_pio->PIO_PCMR &= ~((uint32_t)PIO_PCMR_DSIZE_Msk);
	p_pio->PIO_PCMR |= PIO_PCMR_DSIZE_WORD;

	/* Only HSYNC and VSYNC are enabled */
	p_pio->PIO_PCMR &= ~((uint32_t)PIO_PCMR_ALWYS);
	p_pio->PIO_PCMR &= ~((uint32_t)PIO_PCMR_HALFS);
}

/**
 * \brief Capture OV7740 data to a buffer.
 *
 * \param p_pio PIO instance which will capture data from OV7740 iamge sensor.
 * \param p_uc_buf Buffer address where captured data must be stored.
 * \param ul_size Data frame size.
 */
static void pio_capture_to_buffer(Pio* const p_pio, uint8_t *p_uc_buf,
		uint32_t ul_size)
{
	/* Link the current PDC buffer to the buffer which contains the first
	 * third of captured data from the OV7740 sensor. */
	p_pio->PIO_RPR = (uint32_t)p_uc_buf;
	p_pio->PIO_RCR = ul_size / 4;

	/* Enable channel */
	p_pio->PIO_PTCR = PIO_PTCR_RXTEN;
}

/**
 * \brief Initialize PIO capture and the OV7740 image sensor.
 *
 * \return 0 on success, 1 otherwise.
 */
static uint32_t capture_init(void)
{
	twi_options_t opt;

	/* Init Vsync handler */
	init_vsync_interrupts();

	/* Init PIO capture */
	pio_capture_init(OV_DATA_BUS_PIO, OV_DATA_BUS_ID);

	/* Turn on OV7740 image sensor using power pin */
	ov_power(true, OV_POWER_PIO, OV_POWER_MASK);

	/* Init PCK0 at 24 Mhz */
	PMC->PMC_PCK[0] = (PMC_PCK_PRES_CLK_4 | PMC_PCK_CSS_PLLA_CLK);
	PMC->PMC_SCER = PMC_SCER_PCK0;
	while (!(PMC->PMC_SCSR & PMC_SCSR_PCK0)) {
	}

	/* Enable TWI peripheral */
	pmc_enable_periph_clk(ID_BOARD_TWI);

	/* Init TWI peripheral */
	opt.master_clk = sysclk_get_cpu_hz();
	opt.speed      = TWI_CLK;
	twi_master_init(BOARD_TWI, &opt);

	/* Configure TWI interrupts */
	NVIC_DisableIRQ(BOARD_TWI_IRQn);
	NVIC_ClearPendingIRQ(BOARD_TWI_IRQn);
	NVIC_SetPriority(BOARD_TWI_IRQn, 0);
	NVIC_EnableIRQ(BOARD_TWI_IRQn);

	/* OV7740 initialization*/
	delay_ms(1000);
	if (ov_init(BOARD_TWI) == 0) {
		/* OV7740 configuration */
		ov_configure(BOARD_TWI, TEST_PATTERN);

		/* Wait 3 seconds to let the image sensor to adapt to the
		 * environment */
		delay_ms(3000);

		return 0;
	} else {
		return 1;
	}
}

/**
 * \brief Test color of a reference picture.
 *
 * \param p_uc_ref_color Buffer which contains the reference color.
 * \param p_uc_capture_data Buffer which contains data from the captured
 * picture.
 * \param ul_index_capture Index in p_uc_capture_data.
 * \return 1 on error; 0 if no difference between picture data and corresponding
 * color reference was found.
 */
static uint32_t test_color(uint8_t *p_uc_ref_color, uint8_t *p_uc_capture_data,
		uint32_t ul_index_capture)
{
	if (((p_uc_ref_color[0] - 3) < p_uc_capture_data[ul_index_capture]) &&
			(p_uc_capture_data[ul_index_capture] <
			(p_uc_ref_color[0] + 3)) &&
			((p_uc_ref_color[1] - 3) <
			p_uc_capture_data[ul_index_capture + 1]) &&
			(p_uc_capture_data[ul_index_capture + 1] <
			(p_uc_ref_color[1] + 3)) &&
			((p_uc_ref_color[2] - 3) <
			p_uc_capture_data[ul_index_capture + 2]) &&
			(p_uc_capture_data[ul_index_capture + 2] <
			(p_uc_ref_color[2] + 3)) &&
			((p_uc_ref_color[3] - 3) <
			p_uc_capture_data[ul_index_capture + 3]) &&
			(p_uc_capture_data[ul_index_capture + 3] <
			(p_uc_ref_color[3] + 3))) {
		return 0;
	} else {
		return 1;
	}
}

/**
 * \brief Test the OV7740 initialization.
 *
 * \param test Current test case.
 */
static void ov7740_test_initialization_run(const struct test_case* const test)
{
	volatile uint32_t ul_error = 0;

	ul_error = capture_init();

	/* if initialization test failed, set g_ul_init_error_flag to avoid
	 * other tests to lock up */
	if (ul_error == 1) {
		g_ul_init_error_flag = true;
	}

	/* Check Result of the previous test */
	test_assert_true(test, ul_error == 0,
			"OV7740 initialization test failed!");
}

/**
 * \brief Start capture process.
 *
 */
static void ov7740_test_capture_process_run(const struct test_case* const test)
{
	if (g_ul_init_error_flag == true) {
		/* Return error if previous test about initialization failed */
		test_assert_true(test, 0, "OV7740 capture test failed!");
	} else {
		/* Enable vsync interrupt */
		pio_enable_interrupt(OV7740_VSYNC_PIO, OV7740_VSYNC_MASK);

		/* Capture acquisition will start on rising edge of Vsync
		 * signal.
		 * So wait vsync_flag = 1 before starting the process
		 */
		while (!g_ul_vsync_flag) {
		}

		/* Enable vsync interrupt */
		pio_disable_interrupt(OV7740_VSYNC_PIO, OV7740_VSYNC_MASK);

		/* Reset vsync flag */
		g_ul_vsync_flag = false;

		/* Configure the PDC Buffer and next Buffer for image capture */
		pio_capture_to_buffer(OV7740_VSYNC_PIO, g_auc_capture_buffer,
				sizeof(g_auc_capture_buffer));

		/* Enable PIO capture */
		pio_capture_enable(OV7740_DATA_BUS_PIO);

		/* Wait for the end of capture of the g_auc_capture_buffer */
		while (!((OV7740_DATA_BUS_PIO->PIO_PCISR & PIO_PCIMR_ENDRX) ==
				PIO_PCIMR_ENDRX)) {
		}
	}
}

/**
 * \brief Test color of the reference picture from OV7740 image sensor.
 *
 * \param test Current test case.
 */
static void ov7740_test_color_run(const struct test_case* const test)
{
	uint32_t ul_error = 0;
	volatile uint32_t ul_index = 25600UL; /* put the index at the middle of
																					* data buffer */

	/* Check if picture color is similar to reference color. There are 8
	 * reference colors
	 * (Black, Blue, Red, Purple, Green, Cyan, Yellow, White) and each of
	 * these contains 80 pixel.
	 * So put the index to the middle of the testing color area of picture
	 * and test this color.
	 */
	/* Test black color */
	ul_error += test_color((uint8_t *)g_auc_data_black_color,
			g_auc_capture_buffer, ul_index + 40 );
	/* Test blue color */
	ul_error += test_color((uint8_t *)g_auc_data_blue_color, g_auc_capture_buffer,
			ul_index + 120);

	/* Test red color */
	ul_error += test_color((uint8_t *)g_auc_data_red_color, g_auc_capture_buffer,
			ul_index + 200);

	/* Test purple color */
	ul_error += test_color((uint8_t *)g_auc_data_purple_color,
			g_auc_capture_buffer, ul_index + 280);

	/* Test green color */
	ul_error += test_color((uint8_t *)g_auc_data_green_color,
			g_auc_capture_buffer, ul_index + 360);

	/* Test cyan color */
	ul_error += test_color((uint8_t *)g_auc_data_cyan_color, g_auc_capture_buffer,
			ul_index + 440);

	/* Test yellow color */
	ul_error += test_color((uint8_t *)g_auc_data_yellow_color,
			g_auc_capture_buffer, ul_index + 520 );

	/* Test white color */
	ul_error += test_color((uint8_t *)g_auc_data_white_color,
			g_auc_capture_buffer, ul_index + 600);
	/* Check Result of previous test */
	test_assert_true(test, ul_error == 0, "OV7740 color test failed!");
}

/**
 * \brief Application entry point for image sensor capture example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	sysclk_init();
	board_init();

	/* OV7740 send image sensor data at 24 Mhz. For best performances, PCK0
	 * which will capture OV7740 data, has to work at 24Mhz. It's easier and
	 * optimum to use one PLL for core (PLLB) and one other for PCK0 (PLLA).
	 */
	pmc_enable_pllack(7, 0x1, 1); /* PLLA work at 96 Mhz */

	/* Configure UART */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Define test for capture initialization */
	DEFINE_TEST_CASE(ov7740_test_initialization, NULL,
			 ov7740_test_initialization_run, NULL,
			 "OV7740 initialization test");

	/* Define function for capture process but do not test it */
	DEFINE_TEST_CASE(ov7740_test_capture_process, NULL, ov7740_test_capture_process_run, NULL,
			 "OV7740 capture process test");

	/* Define test for color */
	DEFINE_TEST_CASE(ov7740_test_color, NULL, ov7740_test_color_run, NULL,
			 "OV7740 color test");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(ov7740_test_array) = {
          &ov7740_test_initialization,
          &ov7740_test_capture_process,
          &ov7740_test_color
        };

	/* Define the test suite */
	DEFINE_TEST_SUITE(ov7740_test_suite, ov7740_test_array,
			  "OV7740 driver test suite");

	/* Run all tests in the test suite */
	test_suite_run(&ov7740_test_suite);

	while (1) {
		/* Busy-wait forever. */
	}
}
