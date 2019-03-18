/**
 * \file
 *
 * \brief MMA7341L Accelerometer example.
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

/**
 * \mainpage MMA7341L Accelerometer Example
 *
 * \section Purpose
 *
 * This example demonstrates how to configure MMA7341L accelerometer
 * and check the gravity values of three axes by it.
 *
 * \section Requirements
 *
 * This package can be used with SAM evaluation kits.
 *
 * \section Description
 *
 * This example first set MMA7341L working mode and g-range, then initialize and calibrate it,
 * and last get the gravity values of three axes.
 *
 * \section Usage
 *
 * -# Build the program and download it into the evaluation board.
 * -# On the computer, open and configure a terminal application
 *     (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *    - 115200 bauds
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# In the terminal window, the
 *     following text should appear (values depend on the board and the chip used):
 *     \code
	-- MMA7341L Example xxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"

#define STRING_EOL    "\r"
#define STRING_HEADER "-- MMA7341L  Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/** Global timestamp in milliseconds since start of application */
volatile uint32_t ul_ms_ticks = 0;

/**
 * \brief Systick handler.
 */
void SysTick_Handler(void)
{
	ul_ms_ticks++;
}

/**
 * \brief Configure the console UART.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};
	
	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 *  \brief Wait for the given number of milliseconds (using the dwTimeStamp generated
 *  by the SAM microcontrollers' system tick).
 *
 *  \param dw_dly_ticks Delay to wait for, in milliseconds.
 */
static void mdelay(uint32_t ul_dly_ticks)
{
	uint32_t ul_cur_ticks;

	ul_cur_ticks = ul_ms_ticks;
	while ((ul_ms_ticks - ul_cur_ticks) < ul_dly_ticks);
}

/**
 * \brief Application entry point for MMA7341L accelerometer example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	xyz_g_t xyz_g;

	sysclk_init();
	board_init();

	/* Configure console UART */
	configure_console();

	/* Output example information */
	puts(STRING_HEADER);

	puts("Configure system tick to get 1ms tick period.\r");
	if (SysTick_Config(sysclk_get_cpu_hz() / 1000)) {
		puts("-F- Systick configuration error\r");
		while (1);
	}

	/* Set MMA7341L normal mode */
	mma7341l_set_mode(MMA7341L_NORMAL_MODE);

	/* Initialize MMA7341L */
	mma7341l_init();

	/* Calibrate MMA7341L */
	mma7341l_calibration();

	while (1) {
		xyz_g = mma7341l_get_gravity_value();
		printf("X-g = %f g, Y-g = %f g, Z-g = %f g\n", xyz_g.x_g, xyz_g.y_g, xyz_g.z_g);
		mdelay(200);
	}
}
