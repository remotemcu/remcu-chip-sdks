/**
 * \file
 *
 * \brief Real-Time Clock (RTC) tamper example for SAM.
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
 * \mainpage RTC Tamper Example
 *
 * \section Purpose
 *
 * This basic example shows how to use the Real-Time Clock (RTC) tamper
 * function in SAM.
 *
 * \section Requirements
 *
 * This example can be used with SAM4C evaluation kits.
 *
 * \section Description
 *
 * Upon startup, the system set the tamper pin TMP0 and TMP2 as wake-up
 * source. After press any key, the system will enter backup mode. By
 * pressing the BP3(TMP0) or BP6(TMP2) button, the system will wake up and clear
 * GPBR0~7 register automatically, display the tamper event happen time/date.
 *
 * \note Because this example need use RTCOUT pin, which is common PIO with TDO,
 * To debug normally, please select SWD interface.
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
 * -# In the terminal window, the following text should appear:
 *    \code
	-- RTC Tamper Example xxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/** GPBR const written data */
#define GPBR_CONST_DATA              (0xdeadbeef)

/** The RTC output config */
#define RTC_OUT_CHN                  0
#define RTC_OUT_SRC                  3

#define STRING_EOL    "\r"
#define STRING_HEADER "-- RTC Tamper Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

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
 * \brief Application entry point for RTC tamper example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint32_t ul_read_value[8] = {0, 0 ,0, 0, 0, 0, 0, 0};
	uint32_t ul_hour0, ul_minute0, ul_second0;
	uint32_t ul_year0, ul_month0, ul_day0, ul_week0;
	uint32_t ul_hour1, ul_minute1, ul_second1;
	uint32_t ul_year1, ul_month1, ul_day1, ul_week1;
	uint32_t tmp_src0, tmp_src1, tmp_cnt;
	uint8_t uc_key;

	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	/* Initialize the console uart */
	configure_console();

	/* Output example information */
	puts(STRING_HEADER);

	/* Default RTC configuration, 24-hour mode */
	rtc_set_hour_mode(RTC, 0);
	rtc_set_waveform(RTC, RTC_OUT_CHN, RTC_OUT_SRC);

	if(rstc_get_reset_cause(RSTC) == RSTC_SR_RSTTYP_BackupReset) {
		/* Read the data from GPBR0 ~ 7 */
		ul_read_value[0] = gpbr_read(GPBR0);
		ul_read_value[1] = gpbr_read(GPBR1);
		ul_read_value[2] = gpbr_read(GPBR2);
		ul_read_value[3] = gpbr_read(GPBR3);
		ul_read_value[4] = gpbr_read(GPBR4);
		ul_read_value[5] = gpbr_read(GPBR5);
		ul_read_value[6] = gpbr_read(GPBR6);
		ul_read_value[7] = gpbr_read(GPBR7);

		if((ul_read_value[0] == 0) &&
				(ul_read_value[1] == 0) &&
				(ul_read_value[2] == 0) &&
				(ul_read_value[3] == 0) &&
				(ul_read_value[4] == 0) &&
				(ul_read_value[5] == 0) &&
				(ul_read_value[6] == 0) &&
				(ul_read_value[7] == 0)) {
			printf("The backup register is cleared when tamper event happen!\r\n");
		} else {
			printf("The backup register is not cleared when tamper event happen!\r\n");
		}

		/* Retrieve tamper date and time */
		rtc_get_tamper_time(RTC, &ul_hour0, &ul_minute0, &ul_second0, 0);
		rtc_get_tamper_date(RTC, &ul_year0, &ul_month0, &ul_day0, &ul_week0, 0);
		rtc_get_tamper_time(RTC, &ul_hour1, &ul_minute1, &ul_second1, 1);
		rtc_get_tamper_date(RTC, &ul_year1, &ul_month1, &ul_day1, &ul_week1, 1);
		tmp_cnt = rtc_get_tamper_event_counter(RTC);
		tmp_src0 = rtc_get_tamper_source(RTC, 0);
		tmp_src1 = rtc_get_tamper_source(RTC, 1);
		printf("The first tamper event TMP%u happen in %02u:%02u:%02u,%02u/%02u/%04u\r\n",
				(unsigned int)tmp_src0, (unsigned int)ul_hour0, (unsigned int)ul_minute0,
				(unsigned int)ul_second0, (unsigned int)ul_month0, (unsigned int)ul_day0,
				(unsigned int)ul_year0);
		printf("The last tamper event TMP%u happen in %02u:%02u:%02u,%02u/%02u/%04u\r\n",
				(unsigned int)tmp_src1, (unsigned int)ul_hour1, (unsigned int)ul_minute1,
				(unsigned int)ul_second1, (unsigned int)ul_month1, (unsigned int)ul_day1,
				(unsigned int)ul_year1);
		printf("The tamper event counter is %u \r\n", (unsigned int)tmp_cnt);
	}

	printf("Press any key to Enter Backup Mode!\r\n");

	while (uart_read(CONSOLE_UART, &uc_key));

	/* Write the data to the backup register GPBR0 ~ 7 */
	gpbr_write(GPBR0, GPBR_CONST_DATA);
	gpbr_write(GPBR1, GPBR_CONST_DATA);
	gpbr_write(GPBR2, GPBR_CONST_DATA);
	gpbr_write(GPBR3, GPBR_CONST_DATA);
	gpbr_write(GPBR4, GPBR_CONST_DATA);
	gpbr_write(GPBR5, GPBR_CONST_DATA);
	gpbr_write(GPBR6, GPBR_CONST_DATA);
	gpbr_write(GPBR7, GPBR_CONST_DATA);

	/* Enable TMP0 and TMP2 low power debouncer and clear GPBR when event happen */
	supc_set_wakeup_mode(SUPC, SUPC_WUMR_LPDBCEN0_ENABLE |
			SUPC_WUMR_LPDBCCLR_ENABLE | SUPC_WUMR_LPDBCEN2_ENABLE |
			SUPC_WUMR_LPDBC_2_RTCOUT0);
	/* Enable TMP0 and TMP2 wake-up input and set input type*/
	supc_set_wakeup_inputs(SUPC, SUPC_WUIR_WKUPEN0_ENABLE |
			SUPC_WUIR_WKUPEN14_ENABLE,
			SUPC_WUIR_WKUPT0_LOW | SUPC_WUIR_WKUPT14_LOW);

	printf("Enter Backup Mode!\r\n");
	printf("Please press button TMP0 or TMP2 to wake up!\r\n\r\n");

	/* Ensure TX is done before enter backup mode */
	while (!uart_is_tx_empty(CONSOLE_UART)) {
	}

	/* Enter backup mode */
	pmc_enable_backupmode();

	while (1) {
	}
}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

