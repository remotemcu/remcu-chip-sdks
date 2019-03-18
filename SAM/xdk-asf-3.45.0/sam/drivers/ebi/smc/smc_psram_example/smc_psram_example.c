/**
 * \file
 *
 * \brief SMC PSRAM Example for SAM.
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
 * \mainpage SMC PSRAM Example
 *
 * \section Purpose
 *
 * This example shows how to configure the Static Memory Controller (SMC)
 * for PSRAM, and do write and read operations to check the configuration.
 *
 * \section Requirements
 *
 * This package can be used with SAM3U evaluation kits.
 *
 * \section Description
 *
 * An accurate one-to-one comparison is necessary between PSRAM and SMC waveforms for
 * a complete SMC configuration.
 * * The required steps are:
 * <ul>
 * <li> Configure EBI I/O for PSRAM connection </li>
 * <li> Configure PMC to enable the SMC clock.</li>
 * <li> Refer to the "AC Characteristics" section of the customer PSRAM datasheet.</li>
 * <li> Configure SMC timing to fix the characteristics</li>
 * <li>	Configure SMC mode register for page mode if any.</li>
 * <li>	Access the PSRAM for write or read.</li>
 * </ul>
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *    \code
	     -- SMC PSRAM Example --
	     -- xxxxxx-xx
	     -- Compiled: xxx xx xxxx xx:xx:xx --

	     -I- Configure PMC to enable the SMC clock.
	     -I- Configure SMC timing and mode.
	     -I- Test external PSRAM access.
	     -I- Psram access successful.
\endcode
 * 
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "stdio_serial.h"
#include "conf_board.h"

/** Base address of chip select */
#define PSRAM_BASE_ADDRESS         (0x60000000)

#define STRING_EOL    "\r"
#define STRING_HEADER "-- SMC PSRAM Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/**
 * \brief Go/No-Go test of the first 10K-Bytes of external PSRAM access.
   \return 0 if test is failed else 1.
 */
static uint8_t access_psram_test(void)
{
	uint32_t i;
	uint32_t *ptr = (uint32_t *) PSRAM_BASE_ADDRESS;

	for (i = 0; i < 10 * 1024; ++i) {
		if (i & 1) {
			ptr[i] = i;
		} else {
			ptr[i] = 0xEFBEADDE;
		}
	}
	for (i = 0; i < 10 * 1024; ++i) {
		if (i & 1) {
			if (ptr[i] != i) {
				return 0;
			}
		} else {
			if (ptr[i] != 0xEFBEADDE) {
				return 0;
			}
		}
	}
	return 1;
}

/**
 *  Configure UART console.
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
 * \brief Application entry point for smc_psram example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	configure_console();

	/* Output example information */
	puts(STRING_HEADER);

	/* Enable PMC clock for SMC module */
	puts("Configure PMC to enable the SMC clock.\r");
	pmc_enable_periph_clk(ID_SMC);
	
	/* Configure EBI I/O for PSRAM connection */
	puts("Configure SMC timing and mode.\r");
	
	/* complete SMC configuration between PSRAM and SMC waveforms. */
	smc_set_setup_timing(SMC, 0, SMC_SETUP_NWE_SETUP(0)
			| SMC_SETUP_NCS_WR_SETUP(2)
			| SMC_SETUP_NRD_SETUP(2)
			| SMC_SETUP_NCS_RD_SETUP(2));
	smc_set_pulse_timing(SMC, 0, SMC_PULSE_NWE_PULSE(6)
			| SMC_PULSE_NCS_WR_PULSE(6)
			| SMC_PULSE_NRD_PULSE(6)
			| SMC_PULSE_NCS_RD_PULSE(6));
	smc_set_cycle_timing(SMC, 0, SMC_CYCLE_NWE_CYCLE(8)
			| SMC_CYCLE_NRD_CYCLE(8));
	smc_set_mode(SMC, 0, SMC_MODE_READ_MODE | SMC_MODE_WRITE_MODE
			| SMC_MODE_DBW_BIT_16);

	/* Test external PSRAM access */
	puts("Test external PSRAM access. \r");
	uint8_t *ptr = (uint8_t *) PSRAM_BASE_ADDRESS;
	ptr[0] = 0x50;
	ptr[1] = 0x51;
	ptr[2] = 0x52;
	ptr[3] = 0x53;
	if (access_psram_test()) {
		puts("Psram access successful.\r");
	} else {
		puts("Psram access failed.\r");
	}
	
	while (1) {
	}
}
