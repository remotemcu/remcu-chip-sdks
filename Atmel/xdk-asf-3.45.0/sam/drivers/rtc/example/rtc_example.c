/**
 * \file
 *
 * \brief Real-Time Clock (RTC) example for SAM.
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
 * \mainpage RTC Example
 *
 * \section Purpose
 *
 * This basic example shows how to use the Real-Time Clock (RTC) peripheral
 * available on the SAM  microcontrollers. The RTC enables easy
 * time and date management and allows the user to monitor events like a
 * configurable alarm, second change, calendar change, and so on.
 *
 * \section Requirements
 *
 * This example can be used with SAM evaluation kits.
 *
 * \section Description
 *
 * Upon startup, the program displays the currently set time and date
 * and a menu to perform the following:
 *     \code
	Menu:
	   t - Set time
	   d - Set date
	   i - Set time alarm
	   m - Set date alarm
	   c - Clear the alarm notification (only if it has been triggered)
	   w - Generate Waveform
\endcode
 *
 * "w" is an additional option for SAM3S8, SAM3SD8, SAM4S, SAM4C, SAM4CP, SAM4CM
 * SAMV71, SAMV70, SAME70 and SAMS70.
 * An RTC output can be programmed to generate several waveforms, including a
 * prescaled clock derived from slow clock.
 *
 * Setting the time, date and time alarm is done by using Menu option, and
 * the display is updated accordingly.
 *
 * The time alarm is triggered only when the second, minute and hour match the 
 * preset values; the date alarm is triggered only when the month and date
 * match the preset values. 
 *
 * Generating waveform is done by using Menu option "w" and a menu to perform
 * the following:
 *     \code
	Menu:
	0 - No Waveform
	1 - 1 Hz square wave
	2 - 32 Hz square wave
	3 - 64 Hz square wave
	4 - 512 Hz square wave
	5 - Toggles when alarm flag rise
	6 - Copy of the alarm flag
	7 - Duty cycle programmable pulse
	8 - Quit
\endcode
 *
 * \note The example is using RC oscillator by default. This would generate an
 * accuracy problem for the RTC if not calibrated. It is recommended to use an
 * external 32KHz crystal to get high accuracy. How to initialize RTC with
 * external 32KHz crystal can be referred at \ref sam_rtc_quickstart.
 *
 * \note In sam4c_ek board, please use SWD instead of JTAG because RTCOUT share pin with
 * JTAG interface. Otherwise there is a debug issue when enable wave output.
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
	     -- RTC Example xxx --
	     -- xxxxxx-xx
	     -- Compiled: xxx xx xxxx xx:xx:xx --

	     Menu:
	     t - Set time
	     d - Set date
	     i - Set time alarm
	     m - Set date alarm
\endcode
 * -# Press one of the keys listed in the menu to perform the corresponding
 * action.
 * 
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "stdio_serial.h"
#include "conf_clock.h"
#include "conf_board.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/* Main menu is being displayed. */
#define STATE_MENU             0
/* Time is being edited. */
#define STATE_SET_TIME         1
/* Date is being edited. */
#define STATE_SET_DATE         2
/* Time alarm is being edited. */
#define STATE_SET_TIME_ALARM   3
/* Date alarm is being edited. */
#define STATE_SET_DATE_ALARM   4
/* Wave generating is being edited. */
#define STATE_WAVEFORM         5

/* Maximum size of edited string. */
#define MAX_EDIT_SIZE          10

/* Macro for converting char to digit. */
#define char_to_digit(c) ((c) - '0')

#define STRING_EOL    "\r"
#define STRING_HEADER "-- RTC Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/* Current state of application. */
static uint32_t gs_ul_state = STATE_MENU;

/* Edited hour. */
static uint32_t gs_ul_new_hour;
/* Edited minute. */
static uint32_t gs_ul_new_minute;
/* Edited second. */
static uint32_t gs_ul_new_second;

/* Edited year. */
static uint32_t gs_ul_new_year;
/* Edited month. */
static uint32_t gs_ul_new_month;
/* Edited day. */
static uint32_t gs_ul_new_day;
/* Edited day-of-the-week. */
static uint32_t gs_ul_new_week;

/* Indicate if alarm has been triggered and not yet cleared */
static uint32_t gs_ul_alarm_triggered = 0;

/* Time string */
static uint8_t gs_uc_rtc_time[8 + 1] =
		{ '0', '0', ':', '0', '0', ':', '0', '0', '\0' };
/* Date string */
static uint8_t gs_uc_date[10 + 1] =
		{ '0', '0', '/', '0', '0', '/', '0', '0', '0', '0', '\0' };
/* Week string */
static uint8_t gs_uc_day_names[7][4] =
		{ "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

/* Flag for refreshing menu */
static uint32_t gs_ul_menu_shown = 0;

/**
 *  Configure UART console.
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
}

/**
 * \brief Get new time. Successful value is put in gs_ul_new_hour,
 * gs_ul_new_minute, gs_ul_new_second.
 */
static uint32_t get_new_time(void)
{
	uint8_t uc_key;
	uint32_t i = 0;

	/* Clear setting variable. */
	gs_ul_new_hour = 0xFFFFFFFF;
	gs_ul_new_minute = 0xFFFFFFFF;
	gs_ul_new_second = 0xFFFFFFFF;

	/* Use gs_uc_rtc_time[] as a format template. */
	while (1) {

		scanf("%c", (char *)&uc_key);

		/* End input */
		if (uc_key == 0x0d || uc_key == 0x0a) {
			puts("\r");
			break;
		}

		/* DEL or BACKSPACE */
		if (uc_key == 0x7f || uc_key == 0x08) {
			if (i > 0) {
				/* End of gs_uc_rtc_time[], then one more back of index */
				if (!gs_uc_rtc_time[i]) {
					--i;
				}

				puts("\b \b");
				--i;

				/* Delimiter ':' for time is uneditable */
				if (!((gs_uc_rtc_time[i]) >= '0' && (gs_uc_rtc_time[i]) <= '9')
						&& i > 0) {
					puts("\b \b");
					--i;
				}
			}
		}

		/*
		 * End of gs_uc_rtc_time[], no more input except the above DEL/BS,
		 * or enter to end.
		 */
		if (!gs_uc_rtc_time[i]) {
			continue;
		}

		printf("%c", uc_key);
		gs_uc_rtc_time[i++] = uc_key;

	}

	if (i == 0) {
		return 0;
	}

	if (i != 0 && gs_uc_rtc_time[i] != '\0') {
		/* Failure input */
		return 1;
	}

	gs_ul_new_hour = char_to_digit(gs_uc_rtc_time[0]) * 10 +
			char_to_digit(gs_uc_rtc_time[1]);
	gs_ul_new_minute = char_to_digit(gs_uc_rtc_time[3]) * 10 +
			char_to_digit(gs_uc_rtc_time[4]);
	gs_ul_new_second = char_to_digit(gs_uc_rtc_time[6]) * 10 +
			char_to_digit(gs_uc_rtc_time[7]);

	/* Success input. Verification of data is left to RTC internal Error Checking. */
	return 0;
}

/**
 * \brief Calculate week from year, month, day.
 */
static uint32_t calculate_week(uint32_t ul_year, uint32_t ul_month,
		uint32_t ul_day)
{
	uint32_t ul_week;

	if (ul_month == 1 || ul_month == 2) {
		ul_month += 12;
		--ul_year;
	}

	ul_week = (ul_day + 2 * ul_month + 3 * (ul_month + 1) / 5 + ul_year +
			ul_year / 4 - ul_year / 100 + ul_year / 400) % 7;

	++ul_week;

	return ul_week;
}

/**
 * \brief Get new time. Successful value is put in gs_ul_new_year,
 * gs_ul_new_month, gs_ul_new_day, gs_ul_new_week.
 */
static uint32_t get_new_date(void)
{
	uint8_t uc_key;
	uint32_t i = 0;

	/* Clear setting variable */
	gs_ul_new_year = 0xFFFFFFFF;
	gs_ul_new_month = 0xFFFFFFFF;
	gs_ul_new_day = 0xFFFFFFFF;
	gs_ul_new_week = 0xFFFFFFFF;

	/* Use gs_uc_rtc_time[] as a format template */
	while (1) {

		scanf("%c", (char *)&uc_key);

		/* End input */
		if (uc_key == 0x0d || uc_key == 0x0a) {
			puts("\r");
			break;
		}

		/* DEL or BACKSPACE */
		if (uc_key == 0x7f || uc_key == 0x08) {
			if (i > 0) {
				/* End of date[], then one more back of index */
				if (!gs_uc_date[i]) {
					--i;
				}

				puts("\b \b");
				--i;

				/* Delimiter '/' for date is uneditable */
				if (!((gs_uc_date[i]) >= '0' && (gs_uc_date[i]) <='9')
						&& i > 0) {
					puts("\b \b");
					--i;
				}
			}
		}

		/*
		 * End of gs_uc_rtc_time[], no more input except the above DEL/BS,
		 * or enter to end.
		 */
		if (!gs_uc_date[i]) {
			continue;
		}

		printf("%c", uc_key);
		gs_uc_date[i++] = uc_key;

	}

	if (i == 0) {
		return 0;
	}

	if (i != 0 && gs_uc_date[i] != '\0' && i != 6) {
		/* Failure input */
		return 1;
	}

	/* MM-DD-YY */
	gs_ul_new_month = char_to_digit(gs_uc_date[0]) * 10
			+ char_to_digit(gs_uc_date[1]);
	gs_ul_new_day = char_to_digit(gs_uc_date[3]) * 10
			+ char_to_digit(gs_uc_date[4]);
	if (i != 6) {
		/* For 'Set Date' option, get the input new year and new week. */
		gs_ul_new_year = char_to_digit(gs_uc_date[6]) * 1000 +
				char_to_digit(gs_uc_date[7]) * 100 +
				char_to_digit(gs_uc_date[8]) * 10 +
				char_to_digit(gs_uc_date[9]);
		gs_ul_new_week = calculate_week(gs_ul_new_year, gs_ul_new_month,
				gs_ul_new_day);
	}

	/*
	 * Success input. Verification of data is left to RTC internal Error
	 * Checking.
	 */
	return 0;
}


/**
 * \brief Display the user interface on the terminal.
 */
static void refresh_display(void)
{
	uint32_t ul_hour, ul_minute, ul_second;
	uint32_t ul_year, ul_month, ul_day, ul_week;

	if (gs_ul_state != STATE_MENU) {
		/* Not in menu display mode, in set mode. */
	} else {
		/* Retrieve date and time */
		rtc_get_time(RTC, &ul_hour, &ul_minute, &ul_second);
		rtc_get_date(RTC, &ul_year, &ul_month, &ul_day, &ul_week);

		/* Display */
		if (!gs_ul_menu_shown) {
			puts("\n\rMenu:\n\r"
					"  t - Set time\n\r"
					"  d - Set date\n\r"
					"  i - Set time alarm\n\r"
					"  m - Set date alarm\r");
#if ((SAM3S8) || (SAM3SD8) || (SAM4S) || (SAM4C) || (SAM4CP) || (SAM4CM) || (SAMV71)|| (SAMV70) || (SAME70) || (SAMS70))
			puts("  w - Generate Waveform\r");
#endif
			if (gs_ul_alarm_triggered) {
				puts("  c - Clear alarm notification\r");
			}

			printf("\n\r");

			gs_ul_menu_shown = 1;
		}

		/* Update current date and time */
		puts("\r");
		printf(" [Time/Date: %02u:%02u:%02u, %02u/%02u/%04u %s ][Alarm status:%s]",
			(unsigned int)ul_hour, (unsigned int)ul_minute, (unsigned int)ul_second,
			(unsigned int)ul_month, (unsigned int)ul_day, (unsigned int)ul_year,
			gs_uc_day_names[ul_week-1], gs_ul_alarm_triggered?"Triggered!":"");
	}
}

/**
 * \brief Interrupt handler for the RTC. Refresh the display.
 */
void RTC_Handler(void)
{
	uint32_t ul_status = rtc_get_status(RTC);

	/* Second increment interrupt */
	if ((ul_status & RTC_SR_SEC) == RTC_SR_SEC) {
		/* Disable RTC interrupt */
		rtc_disable_interrupt(RTC, RTC_IDR_SECDIS);

		refresh_display();

		rtc_clear_status(RTC, RTC_SCCR_SECCLR);

		rtc_enable_interrupt(RTC, RTC_IER_SECEN);
	} else {
		/* Time or date alarm */
		if ((ul_status & RTC_SR_ALARM) == RTC_SR_ALARM) {
			/* Disable RTC interrupt */
			rtc_disable_interrupt(RTC, RTC_IDR_ALRDIS);

			gs_ul_alarm_triggered = 1;
			refresh_display();
			/* Show additional menu item for clear notification */
			gs_ul_menu_shown = 0;
			rtc_clear_status(RTC, RTC_SCCR_ALRCLR);
			rtc_enable_interrupt(RTC, RTC_IER_ALREN);
		}
	}
}


/**
 * \brief Application entry point for RTC example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
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

	/* Configure RTC interrupts */
	NVIC_DisableIRQ(RTC_IRQn);
	NVIC_ClearPendingIRQ(RTC_IRQn);
	NVIC_SetPriority(RTC_IRQn, 0);
	NVIC_EnableIRQ(RTC_IRQn);
	rtc_enable_interrupt(RTC, RTC_IER_SECEN | RTC_IER_ALREN);

	/* Refresh display once */
	refresh_display();

	/* Handle keypresses */
	while (1) {

		scanf("%c", (char *)&uc_key);

		/* Set time */
		if (uc_key == 't') {
			gs_ul_state = STATE_SET_TIME;

			do {
				puts("\n\r\n\r Set time(hh:mm:ss): ");
			} while (get_new_time());

			/* If valid input, none of the variables for time is 0xff. */
			if (gs_ul_new_hour != 0xFFFFFFFF && (gs_uc_rtc_time[2] == ':')
					&& (gs_uc_rtc_time[5] == ':')) {
				if (rtc_set_time(RTC, gs_ul_new_hour, gs_ul_new_minute,
						gs_ul_new_second)) {
					puts("\n\r Time not set, invalid input!\r");
				}
			} else {
				gs_uc_rtc_time[2] = ':';
				gs_uc_rtc_time[5] = ':';
				puts("\n\r Time not set, invalid input!\r");
			}

			gs_ul_state = STATE_MENU;
			gs_ul_menu_shown = 0;
			refresh_display();
		}

		/* Set date */
		if (uc_key == 'd') {
			gs_ul_state = STATE_SET_DATE;

			do {
				puts("\n\r\n\r Set date(mm/dd/yyyy): ");
			} while (get_new_date());

			/* If valid input, none of the variables for date is 0xff(ff). */
			if (gs_ul_new_year != 0xFFFFFFFF && (gs_uc_date[2] == '/')
					&& (gs_uc_date[5] == '/')) {
				if (rtc_set_date(RTC, gs_ul_new_year, gs_ul_new_month,
						gs_ul_new_day, gs_ul_new_week)) {
					puts("\n\r Date not set, invalid input!\r");
				}
			} else {
				gs_uc_date[2] = '/';
				gs_uc_date[5] = '/';
				puts("\n\r Time not set, invalid input!\r");
			}

			/* Only 'mm/dd' is input. */
			if (gs_ul_new_month != 0xFFFFFFFF &&
						gs_ul_new_year == 0xFFFFFFFF) {
				puts("\n\r Not Set for no year field!\r");
			}

			gs_ul_state = STATE_MENU;
			gs_ul_menu_shown = 0;
			refresh_display();
		}

		/* Set time alarm */
		if (uc_key == 'i') {
			gs_ul_state = STATE_SET_TIME_ALARM;

			rtc_clear_date_alarm(RTC);

			do {
				puts("\n\r\n\r Set time alarm(hh:mm:ss): ");
			} while (get_new_time());

			if (gs_ul_new_hour != 0xFFFFFFFF && (gs_uc_rtc_time[2] == ':')
					&& (gs_uc_rtc_time[5] == ':')) {
				if (rtc_set_time_alarm(RTC, 1, gs_ul_new_hour,
						1, gs_ul_new_minute, 1, gs_ul_new_second)) {
					puts("\n\r Time alarm not set, invalid input!\r");
				} else {
					printf("\n\r Time alarm is set at %02u:%02u:%02u!",
						(unsigned int)gs_ul_new_hour, (unsigned int)gs_ul_new_minute,
						(unsigned int)gs_ul_new_second);
				}
			} else {
				gs_uc_rtc_time[2] = ':';
				gs_uc_rtc_time[5] = ':';
				puts("\n\r Time not set, invalid input!\r");
			}
			gs_ul_state = STATE_MENU;
			gs_ul_menu_shown = 0;
			gs_ul_alarm_triggered = 0;
			refresh_display();
		}

		/* Set date alarm */
		if (uc_key == 'm') {
			gs_ul_state = STATE_SET_DATE_ALARM;

			rtc_clear_time_alarm(RTC);

			do {
				puts("\n\r\n\r Set date alarm(mm/dd/yyyy): ");
			} while (get_new_date());

			if (gs_ul_new_year != 0xFFFFFFFF && (gs_uc_date[2] == '/')
					&& (gs_uc_date[5] == '/')) {
				if (rtc_set_date_alarm(RTC, 1, gs_ul_new_month, 1,
						gs_ul_new_day)) {
					puts("\n\r Date alarm not set, invalid input!\r");
				} else {
					printf("\n\r Date alarm is set on %02u/%02u/%4u!",
							(unsigned int)gs_ul_new_month, (unsigned int)gs_ul_new_day,
							(unsigned int)gs_ul_new_year);
				}
			} else {
				gs_uc_date[2] = '/';
				gs_uc_date[5] = '/';
				puts("\n\r Date alarm not set, invalid input!\r");
			}
			gs_ul_state = STATE_MENU;
			gs_ul_menu_shown = 0;
			gs_ul_alarm_triggered = 0;
			refresh_display();
		}

#if ((SAM3S8) || (SAM3SD8) || (SAM4S) || (SAM4C) || (SAM4CP) || (SAM4CM) || (SAMV71)|| (SAMV70) || (SAME70) || (SAMS70))
		/* Generate Waveform */
		if (uc_key == 'w') {
			gs_ul_state = STATE_WAVEFORM;
			puts("\n\rMenu:\n\r"
					"  0 - No Waveform\n\r"
					"  1 - 1 Hz square wave\n\r"
					"  2 - 32 Hz square wave\n\r"
					"  3 - 64 Hz square wave\n\r"
					"  4 - 512 Hz square wave\n\r"
					"  5 - Toggles when alarm flag rise\n\r"
					"  6 - Copy of the alarm flag\n\r"
					"  7 - Duty cycle programmable pulse\n\r"
					"  8 - Quit\r");

			while (1) {
				scanf("%c", (char *)&uc_key);

				if ((uc_key >= '0') && (uc_key <= '7')) {
					rtc_set_waveform(RTC, 0, char_to_digit(uc_key));
				}

				if (uc_key == '8') {
					gs_ul_state = STATE_MENU;
					gs_ul_menu_shown = 0;
					refresh_display();
					break;
				}
			}
		}
#endif
		/* Clear trigger flag */
		if (uc_key == 'c') {
			gs_ul_alarm_triggered = 0;
			gs_ul_menu_shown = 0;
			refresh_display();
		}

	}

}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

