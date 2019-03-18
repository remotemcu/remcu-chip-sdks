/**
 * \file
 *
 * \brief SDRAMC on EBI example for SAM.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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
 *
 * \mainpage SDRAM Example for IS42S16100E
 *
 * \section Purpose
 *
 * This example shows how to configure the IS42S16100E.
 * It will perform write and read operations to check the configuration.
 *
 *  \par Requirements
 *
 *  This package can be used with SAMV71 XPlAINED ULTRA,SAME70 XPlAINED.
 *
 * \section Description
 *
 * An accurate one-to-one comparison is processed after the complete SDRAM
 * configuration.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR EWARM.
 * Other compilers may or may not work.
 *
 * \section Usage
 *
 * -# Build the program and download it into the evaluation board.
 * -# On the computer, open and configure a terminal application
 *    (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear
 *    (values depend on the board and the chip used):
 *    \code
	-- SDRAMC Example --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
	...
\endcode
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "conf_board.h"

/** SDRAM benchmark test size */
#define SDRAMC_TEST_BUFF_SIZE        (30 * 1024)

/** SDRAM benchmark test page number */
#define SDRAMC_TEST_PAGE_NUM        (1024)

/** SDRAMC access test length */
#define SDRAMC_TEST_LENGTH        (10 * 1024)

/** SDRAMC access test data in even address */
#define SDRAMC_TEST_EVEN_TAG        (0x55aaaa55)

/** SDRAMC access test data in odd address */
#define SDRAMC_TEST_ODD_TAG        (0xaa5555aa)

#define STRING_EOL    "\r"
#define STRING_HEADER "-- SDRAMC Example --\r\n" \
	"-- "BOARD_NAME " --\r\n" \
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

/** SDRAM benchmark buffer */
static volatile uint16_t gs_pus_mem_buff[SDRAMC_TEST_BUFF_SIZE];

/* Ticks in 1ms */
static volatile uint32_t gs_ul_ms_ticks = 0;

/** SDRAMC status */
typedef enum {
	SDRAMC_OK = 0,
	SDRAMC_TIMEOUT = 1,
	SDRAMC_ERROR = 2,
} sdramc_status_t;

/**
 * \brief Systick handler to manage timestamp and delay.
 */
void SysTick_Handler(void)
{
	gs_ul_ms_ticks++;
}

/**
 *  \brief Get current tick count (in ms).
 *
 * \return Current tick count value.
 */
static uint32_t tick_get_count(void)
{
	return gs_ul_ms_ticks;
}

/**
 * \brief Get delayed number of ticks.
 *
 * \param ul_start_tick Start tick point.
 * \param ul_end_tick   End tick point.
 *
 * \return Delayed number of ticks.
 */
static uint32_t get_delay_in_ticks(uint32_t ul_start_tick, uint32_t ul_end_tick)
{
	if (ul_end_tick > ul_start_tick) {
		return (ul_end_tick - ul_start_tick);
	}

	return (ul_end_tick + (0xFFFFFFFF - ul_start_tick));
}

/**
 * \brief Access test of the first 10K bytes of external SDRAM.
 *
 * \return SDRAMC_OK if test is passed, else SDRAMC_ERROR.
 */
static uint8_t sdram_access_test(void)
{
	uint32_t i;
	uint32_t *pul = (uint32_t *)BOARD_SDRAM_ADDR;

	for (i = 0; i < SDRAMC_TEST_LENGTH; ++i) {
		if (i & 1) {
			pul[i] = SDRAMC_TEST_ODD_TAG | (1 << i);
		} else {
			pul[i] = SDRAMC_TEST_EVEN_TAG | (1 << i);
		}
	}

	for (i = 0; i < SDRAMC_TEST_LENGTH; ++i) {
		if (i & 1) {
			if (pul[i] != (SDRAMC_TEST_ODD_TAG | (1 << i))) {
				return SDRAMC_ERROR;
			}
		} else {
			if (pul[i] != (SDRAMC_TEST_EVEN_TAG | (1 << i))) {
				return SDRAMC_ERROR;
			}
		}
	}

	return SDRAMC_OK;
}

/**
 * \brief SDRAM benchmark test.
 *
 * \return SDRAMC_OK for success and SDRAMC_ERROR for error.
 */
static uint32_t sdram_benchmarks(void)
{
	uint16_t i;
	uint16_t *pus = (uint16_t *)BOARD_SDRAM_ADDR;
	uint32_t ul_tick_start, ul_tick_end, ul_rw_speed;
	uint32_t ul_ticks = 0;
	uint32_t ul_page_num = 0;

	puts("Start SDRAMC benchmarks.\r");

	for (i = 0; i < SDRAMC_TEST_BUFF_SIZE; i++) {
		gs_pus_mem_buff[i] = (uint16_t)(i & 0xffff);
	}

	/* Start SDRAM write test */
	ul_tick_start = tick_get_count();
	for (ul_page_num = 0; ul_page_num < SDRAMC_TEST_PAGE_NUM;
			ul_page_num++) {
		for (i = 0; i < SDRAMC_TEST_BUFF_SIZE; i++) {
			pus[i + ul_page_num *
			SDRAMC_TEST_BUFF_SIZE]
				= gs_pus_mem_buff[i];
		}
	}
	ul_tick_end = tick_get_count();
	ul_ticks = get_delay_in_ticks(ul_tick_start, ul_tick_end);
	ul_rw_speed = SDRAMC_TEST_BUFF_SIZE * SDRAMC_TEST_PAGE_NUM *
			sizeof(uint16_t) / ul_ticks;
	printf("SDRAMC write speed: %uK/s\n\r", (uint32_t)ul_rw_speed);

	/* Start SDRAM read test */
	ul_tick_start = tick_get_count();
	for (ul_page_num = 0; ul_page_num < SDRAMC_TEST_PAGE_NUM;
			ul_page_num++) {
		for (i = 0; i < SDRAMC_TEST_BUFF_SIZE; i++) {
			gs_pus_mem_buff[i]
				= pus[i + ul_page_num *
					SDRAMC_TEST_BUFF_SIZE];
		}
	}
	ul_tick_end = tick_get_count();
	ul_ticks = get_delay_in_ticks(ul_tick_start, ul_tick_end);
	ul_rw_speed = SDRAMC_TEST_BUFF_SIZE * SDRAMC_TEST_PAGE_NUM *
			sizeof(uint16_t) / ul_ticks;
	printf("SDRAMC read speed: %uK/s\n\r", (uint32_t)ul_rw_speed);

	for (i = 0; i < SDRAMC_TEST_BUFF_SIZE; i++) {
		if (gs_pus_mem_buff[i] != (i & 0xffff)) {
			puts("-F- SDRAMC read data error\r");
			return SDRAMC_ERROR;
		}
	}

	return SDRAMC_OK;
}

/**
 *  \brief Configure the console uart.
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

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
#if defined(__GNUC__)
	setbuf(stdout, NULL);
#endif
}

/**
 * \brief Application entry point for sdramc_example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Initialize the system */
	sysclk_init();
	board_init();
	sleepmgr_init();

	/* Configure the console uart */
	configure_console();

	/* Output example information */
	puts(STRING_HEADER);

	/* Systick configuration */
	if (SysTick_Config(SystemCoreClock / (1000))) {
		puts("-F- Systick configuration error.\r");
	}

	/* Enable SDRAMC peripheral clock */
	pmc_enable_periph_clk(ID_SDRAMC);

	/* Complete SDRAM configuration */
	sdramc_init((sdramc_memory_dev_t *)&SDRAM_ISSI_IS42S16100E,
			sysclk_get_cpu_hz());
	sdram_enable_unaligned_support();

	/* Test external SDRAM access */
	puts("Test external SDRAM access. \r");
	
	SCB_CleanInvalidateDCache();
	
	if (sdram_access_test() == SDRAMC_OK) {
		puts("SDRAM access is successful.\n\r");
	} else {
		puts("SDRAM access is failed.\r");
	}

	if (sdram_benchmarks() == SDRAMC_OK) {
		puts("SDRAM test: pass.\r");
	}

	for (;;) {
		sleepmgr_enter_sleep();
	}
}
