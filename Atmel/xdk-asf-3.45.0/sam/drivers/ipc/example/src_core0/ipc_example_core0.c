/**
 * \file
 *
 * \brief Interprocessor Communication (IPC) example on core 0 for SAM.
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
 * \mainpage Interprocessor Communication (IPC) example on core 0
 *
 * \section Purpose
 *
 * This example demonstrates how core 0 communicates with core 1 via IPC.
 *
 * \section Requirements
 *
 * This package can be used with SAM dual-core device with IPC. The core 1
 * example must be built before.
 *
 * \section Descriptions
 *
 * The program initializes the console with given parameters and configures IPC0
 * IRQ0 handler to deal with the interrupt command from core 1. Then it loads
 * the binary of core 1 example to SRAM1, resets core 1 and waits for the
 * interrupt triggered by core 1. When the interrupt is triggered, the
 * console will output the information and one LED will be turned off.
 * The variable in the SHARED_MEMORY_ADDR will be updated by core 1. The updated
 * value will be printed every time the interrupt occurs.
 *
 * \section Usage
 *
 * -# Compile the application.
 * -# Connect the UART port of the evaluation board to the computer and open
 * it in a terminal.
 *    - Settings: 115200 bauds, 8 bits, 1 stop bit, no parity, no flow control.
 * -# Download the core 0 example into the evaluation board and run it.
 * -# Upon startup, the application will output the following lines on console:
 *    \code
 *     -- Interprocessor Communication Example (Core 0) --
 *     -- xxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *    \endcode
 * -# When the IPC0 IRQ0 is set by core 1 x:
 *    \code
 *     Got IRQ signal from core1 nn
 *    \endcode
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "conf_board.h"
#include "conf_example.h"
#include "led.h"
#include <stdio.h>
#include <string.h>

#define STRING_EOL    "\r"
#define STRING_HEADER "-- Interprocessor Communication Example (Core 0) --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

static volatile bool is_core1_signal = false;
static volatile SHARED_MEMORY_TYPE *cnt = SHARED_MEMORY_ADDR;

/**
 *  \brief Handler for IPC interrupt request.
 */
static void ipc_core1_signal_handler(Ipc *p, enum ipc_interrupt_source mask)
{
	is_core1_signal = true;
	ipc_clear_command(p, mask);
}

/* Extern symbols to locate the binary address of core1 image  */
#if (defined __GNUC__)
extern uint8_t core1_image_start;
extern uint8_t core1_image_end;
#elif defined ( __ICCARM__ )
extern uint8_t core1_image;
#endif

static void copy_core1_image_into_sram1(void)
{
#if (defined __GNUC__)
	memcpy((char *)IRAM1_ADDR,(char *)&core1_image_start,
			(int)&core1_image_end - (int)&core1_image_start);
#elif defined ( __ICCARM__ )
	memcpy((char *)IRAM1_ADDR,(char *)&core1_image, IRAM1_SIZE);
#else
#error This compiler is not supported for now.
#endif
}

/**
 *  \brief Configure the Console UART.
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
 *  \brief Configure the IPC.
 */
static void configure_ipc(void)
{
	ipc_enable(IPC0);
	ipc_enable(IPC1);

	ipc_set_handler(IPC0, IPC_INTERRUPT_SRC_IRQ0, ipc_core1_signal_handler);
	ipc_enable_interrupt(IPC0, IPC_INTERRUPT_SRC_IRQ0);
	NVIC_EnableIRQ(IPC0_IRQn);
}

/**
 * \brief Application entry point for IPC example on core 0.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Initialize the system */
	sysclk_init();
	board_init();

	configure_ipc();
	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);

	copy_core1_image_into_sram1();
	rstc_deassert_reset_of_coprocessor(RSTC, RSTC_CPMR_CPROCEN);

	while (1) {
		if (is_core1_signal == true) {
			is_core1_signal = false;
			LED_Off(LED0);
			printf("Got IRQ signal from core1 %d\r\n", (int)*cnt);
			delay_s(1);
			ipc_set_command(IPC1, IPC_INTERRUPT_SRC_IRQ0);
		}
	}
}

