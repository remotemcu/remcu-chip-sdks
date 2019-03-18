/**
 * \file
 *
 * \brief LIN example for SAM.
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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
 *  \mainpage LIN Example
 *
 *  \section Purpose
 *
 *  The LIN management example demonstrates how to use LIN peripheral with
 * master/slave modes.
 *
 *  \section Requirements
 *
 * This package can be used with SAM3X-EK and an additional LIN transceiver board.
 * In this example, the USART-DB board is used as the LIN transceiver board.
 * The USART-DB board is an external board which can be used to demonstrate varity of
 * USART peripheral functions. In this case, the USART-DB board must be configured
 * to LIN mode to enable the LIN access.
 *
 *  \section Description
 *
 * This is the documentation for the data structures, functions, variables,
 * defines, enums, and typedefs for the USART in LIN modes software driver.\n It
 * also comes bundled with an example. This example is a basic example
 * supporting Master and Slave Mode example.\n
 *
 *  \section Usage
 *
 *  -# Build the program and download it into the evaluation board.
 *  -# On the computer, open and configure a terminal application
 *     (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *    - 115200 bauds
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# In the terminal window, the
 *     following text should appear (values depend on the board and the chip
 * used):
 *     \code
	-- LIN Example xxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 *  -# The application will output converted value to hyperterminal and display
 *     a menu for users to set different modes.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "led.h"

#define STRING_EOL    "\r"
#define STRING_HEADER "-- LIN Example --\r\n" \
	"-- "BOARD_NAME " --\r\n" \
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

/** LIN frame number */
#define LIN_FRAME_ID_12       0x12

/** First byte for test */
#define LIN_FIRST_BYTE        0x55

/** Local Buffer for emission */
uint8_t lin_data_node[8];

static uint32_t lin_led1_counter = 0;

/** LIN master node number */
#define LIN_MASTER_NODE_NUM   0

/** Timer counter channel used */
#define TC_CHANNEL            0

/** Timer counter frequency in Hz */
#define TC_FREQ               20

/** LIN slave node number */
#define LIN_SLAVE_NODE_NUM    0

/** LED0 wait count */
#define LIN_LED0_WAIT_COUNTER 10

/**
 * \brief Display the user menu on the UART.
 */
static void display_menu(void)
{
	puts("\n\rMenu :\n\r"
			"------\n\r"
			"  Set LIN node property:\r");

	puts("  -------------------------------------------\n\r"
			"  m: Set LIN node as Master PUBLISH \n\r"
			"  s: Set LIN node as Slave SUBSCRIBER \n\r"
			"  h: Display menu \n\r"
			"------\n\r\r");
}

/**
 * \brief lin_master_task_ID12
 */
static void  lin_master_task_ID12(void)
{
	lin_data_node[0] = LIN_FIRST_BYTE;
	lin_send_cmd(LIN_MASTER_NODE_NUM, LIN_FRAME_ID_12, sizeof(lin_data_node));
}

/**
 * \brief Interrupt handler for TC0. Record the number of bytes received,
 * and then restart a read transfer on the USART if the transfer was stopped.
 */
void TC0_Handler(void)
{
	/* Read TC0 Status. */
	tc_get_status(TC0, 0);

	lin_master_task_ID12();
}

/**
 * \brief Configure Timer Counter 0 (TC0) to generate an interrupt every 200ms.
 * This interrupt will be used to flush USART input and echo back.
 */
static void configure_tc(void)
{
	uint32_t ul_div;
	uint32_t ul_tcclks;
	static uint32_t ul_sysclk;

	/* Get system clock. */
	ul_sysclk = sysclk_get_cpu_hz();

	/* Configure PMC. */
	pmc_enable_periph_clk(ID_TC0);

	/* Configure TC for a 50Hz frequency and trigger on RC compare. */
	tc_find_mck_divisor(TC_FREQ, ul_sysclk, &ul_div, &ul_tcclks, ul_sysclk);
	tc_init(TC0, 0, ul_tcclks | TC_CMR_CPCTRG);
	tc_write_rc(TC0, 0, (ul_sysclk / ul_div) / TC_FREQ);

	/* Configure and enable interrupt on RC compare. */
	NVIC_EnableIRQ((IRQn_Type)ID_TC0);
	tc_enable_interrupt(TC0, 0, TC_IER_CPCS);
}

/**
 * \brief Interrupt handler for USART. Echo the bytes received and start the
 * next receive.
 */
void USART0_Handler(void)
{
	usart_lin_handler(LIN_SLAVE_NODE_NUM);
}

/**
 * \brief lin_slave_task_ID12
 */
static void  lin_slave_task_ID12(uint8_t *uc_buf)
{
	if (uc_buf[0] == LIN_FIRST_BYTE) {
		lin_led1_counter++;
		if (lin_led1_counter == LIN_LED0_WAIT_COUNTER) {
			LED_Toggle(LED0_GPIO);
			lin_led1_counter = 0;
		}
	}

	LED_Toggle(LED1_GPIO);
}
/**
 * \brief Configure UART console.
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
 * \brief This is an example demonstrating the LIN mode of USART IP
 * functionalities using a dedicated USART LIN driver.
 */
int main(void)
{
	st_lin_message lin_desc;
	uint8_t uc_key;

	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	/* Configure UART for debug message output. */
	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);

	/* Enable the peripheral clock in the PMC. */
	pmc_enable_periph_clk(ID_USART0);

	/* Enable LIN transceiver */
	gpio_set_pin_high(PIN_USART0_CTS_IDX);
	gpio_set_pin_high(PIN_USART0_RTS_IDX);

	display_menu();

	while (true) {
		while (uart_read(CONSOLE_UART, &uc_key)) {
		}

		switch (uc_key) {
		case 'm':
		case 'M':
			puts("-- Set LIN to Master mode\n\r");

			/* Node 0:  LIN_MASTER_MODE */
			lin_init(USART0, true, LIN_MASTER_NODE_NUM, 9600,
					sysclk_get_cpu_hz());

			/* Configure lin_descriptor */
			/* Init LIN data Node 0 */
			/* Object 0 */
			lin_desc.uc_id = LIN_FRAME_ID_12;
			lin_desc.uc_dlc = sizeof(lin_data_node);
			lin_desc.lin_cmd = PUBLISH;
			lin_desc.uc_status = 0;
			lin_desc.uc_pt_data = lin_data_node;
			lin_register_descriptor(LIN_MASTER_NODE_NUM, 0, &lin_desc);

			configure_tc();
			/* In case of Master Mode, the timing transmission starts. */
			tc_start(TC0, 0);
			break;

		case 's':
		case 'S':
			puts("-- Set LIN to Slave mode\n\r");
			/* Node 0:  LIN_SLAVE_MODE */
			lin_init(USART0, false, LIN_SLAVE_NODE_NUM, 9600,
					sysclk_get_cpu_hz());

			/* Configure lin_descriptor */
			/* Init LIN data Node 0 */
			/* Object 0 */
			lin_desc.uc_id = LIN_FRAME_ID_12;
			lin_desc.uc_dlc = sizeof(lin_data_node);
			lin_desc.lin_cmd = SUBSCRIBE;
			lin_desc.uc_status = 0;
			lin_desc.uc_pt_data = lin_data_node;
			lin_desc.pt_function = lin_slave_task_ID12;
			lin_register_descriptor(LIN_SLAVE_NODE_NUM, 0, &lin_desc);

			/* Configure and enable interrupt of USART. */
			NVIC_EnableIRQ(USART0_IRQn);
			usart_enable_interrupt(USART0, US_IER_LINID);
			/* In case of Slave Mode, only wait for ID reception. */
			break;

		case 'h':
		case 'H':
			display_menu();
			break;
		}
		puts("Press \'h\' or \'H\' to display the main menu again!!\r");
	}
}
