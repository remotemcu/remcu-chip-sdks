/**
 * \file
 *
 * \brief QTouch component example with I2C interface.
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

/**
 * \mainpage
 * \section intro Introduction
 * This example shows how to configure a QTouch device and get device status.
 * Key and slide status will be outputted on terminal windows.
 *
 * \section files Main Files
 * - qt_i2c.c: QTouch component driver with I2C interface implementation;
 * - qt_i2c.h: QTouch component driver with I2C interface header file;
 * - example.c: Example application.
 *
 * \section compilinfo Compilation Information
 * This software is written for GNU GCC and IAR Embedded Workbench
 * for ARM. Other compilers may or may not work.
 *
 * \section deviceinfo Device Information
 * AT42QT2160 on SAM4E-EK can be used.
 *
 * \section Usage
 *  -# Build the program and download it into the evaluation board.
 *  -# Connect a serial cable to the DBGU/UART port on the evaluation kit.
 *  -# On the computer, open and configure a terminal application (e.g.,
 *     HyperTerminal on Microsoft Windows) with these settings:
 *        - 115200 bauds
 *        - 8 data bits
 *        - No parity
 *        - 1 stop bit
 *        - No flow control
 *  -# Start the application. The following traces shall appear on the terminal:
 *     \code
	-- QTouch component example (with I2C interface) --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 *  -# Touch the QTouch key or slide on the EK board, key status will be
 *     outputted on terminal windows.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com">Microchip</A>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include "asf.h"
#include "conf_example.h"
#include "string.h"

/**
 * Configure serial console.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
#ifdef CONF_UART_CHAR_LENGTH
		.charlength = CONF_UART_CHAR_LENGTH,
#endif
		.paritytype = CONF_UART_PARITY,
#ifdef CONF_UART_STOP_BITS
		.stopbits = CONF_UART_STOP_BITS,
#endif
	};

	/* Configure console. */
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief Initialize TWI communication interface.
 */
static void init_interface(void)
{
	/* TWI master initialization options. */
	twi_master_options_t twi_opt;

	memset((void *)&twi_opt, 0, sizeof(twi_master_options_t));
	twi_opt.speed = 100000;    /* 100KHz for I2C speed */

	/* Initialize the TWI master driver. */
	twi_master_setup(BOARD_QT_TWI_INSTANCE, &twi_opt);
}

/** Storage for QT status */
struct qt_status status;
/** Storage for QT setup block */
struct qt_setup_block setup_block;

/**
 * \brief Main entry point for QTouch component example.
 */
int main(void)
{
	enum status_code ret;

	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	/* Initialize the console uart */
	configure_console();

	/* Output example information */
	printf("\r\n\r\n-- QTouch component example with I2C interface --\r\n");
	printf("-- %s\r\n", BOARD_NAME);
	printf("-- Compiled: %s %s --\r\n", __DATE__, __TIME__);

	/* Initialize communication interface */
	init_interface();

	/* Reset QT device */
	qt_hardware_reset();

	/* Check communication is ready and able to read Chip ID */
	ret = qt_get_comm_ready();
	if (ret != STATUS_OK) {
		printf("Communication failed. Abort!\r\n");
		while (1) {
			/* Infinite loop here */
		}
	}

	/* Read setup block */
	qt_read_setup_block(&setup_block);
	/* Modify setup block parameters for specific example */
	example_set_qt_param(&setup_block);
	/* Write setup block */
	qt_write_setup_block(&setup_block);

	/* Read all status bytes to return the CHANGE line to an inactive state */
	qt_get_status(&status);

	while (1) {
		if (qt_is_change_line_low()) {
			/* Read all status bytes */
			qt_get_status(&status);

			/* Process the received data */
			example_process_qt_status(&status);
		}
	}
}
