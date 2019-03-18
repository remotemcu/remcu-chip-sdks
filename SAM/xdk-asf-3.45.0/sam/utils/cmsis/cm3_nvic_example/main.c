/**
 * \file
 *
 * \brief NVIC Example.
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
 * \mainpage NVIC Example
 *
 * \section Purpose
 *
 * This example shows how to use the NVIC especially nested and priority
 * management.
 *
 * \section Requirements
 *
 * This example can be used with SAM3 evaluation kits.
 *
 * \section Description
 *
 * In this example, two interrupt sources will be configured. One is from User Button,
 * and the other is from PIO output. They are called INT1 and INT2. INT1 is triggered
 * by pressing user button #1, and INT2 is triggered by pressing user button #2.\n
 * \n
 * In INT1 handler:
 * <ul>
 * <li> At the entrance, an enter message will be printed and LED1 will be
 * turned on.
 * <li> Then delay for a while.
 * <li> At the exit, an exit message will be printed and LED1 will be turned off.
 * </ul>
 * In INT2 handler:
 * <ul>
 * <li> At the entrance, an enter message will be printed and LED2 will be
 * turned on.
 * <li> Then delay for a while.
 * <li> At the exit, an exit message will be printed and LED2 will be turned off.
 * </ul>
 * Users can change the priorities of INT1 and INT2. Nest and priority features can be
 * watched in terminal window or by LEDs.
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
 * -# In the terminal window, the following text should appear:
 *    \code
	     -- Cortex-M3 NVIC Example --
	     -- Compiled: xxx xx xxxx xx:xx:xx --
	     Set INT1's priority higher than INT2.

	     Menu:
	     ===================================================
	     1: Set INT2's priority higher than INT1.
	     2: Set INT1's priority higher than INT2.
	     h: Show this menu.

	     ===================================================
	     Press button USR-LEFT to trigger the interrupts.
\endcode
 * -# Choose options in the above menu to set interrupt priority.
 * -# Press buttons to trigger the interrupts. \n
 *    If INT2's priority is higher than INT1's, the following text should appear
 *    in the terminal window:
 *    \code
	===================================================
	Enter _Int1Handler.
	***************************************************
	Enter _Int2Handler.
	Exit _Int2Handler.
	***************************************************
	Exit _Int1Handler.
	===================================================
\endcode
 *    If INT1's priority is higher than INT2's, the following text should appear
 *    in the terminal window:
 *    \code
	===================================================
	Enter _Int1Handler.
	Exit _Int1Handler.
	===================================================
	***************************************************
	Enter _Int2Handler.
	Exit _Int2Handler.
	***************************************************
\endcode
 *    The result is also shown by LEDs.
 *
 * \section References
 * - main.c
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "conf_board.h"
#include "stdio_serial.h"

/* Systick Counter. */
volatile uint32_t g_ul_ms_ticks = 0;

/**
 * Define interrupt priority (0-15). A higher level corresponds to a lower
 * priority, so level 0 is the highest interrupt priority.
 */
#define INT_PRIOR_HIGH    4
#define INT_PRIOR_LOW     6

#define STRING_EOL    "\r"
#define STRING_HEADER "-- Cortex-M3 NVIC Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \brief Delay number of tick Systicks (happens roughly every 1 ms).
 *
 * Note: As the systick has the lowest priority, lower than the PIO, the systick
 * is not used here.
 */
__INLINE static void delay_ticks(uint32_t ul_dly_ticks)
{
	volatile uint32_t ul_delay_tick = (ul_dly_ticks * (BOARD_MCK / 18000));

	while (ul_delay_tick--);

}

 /**
 * \brief Configure LED pins.
 */
__INLINE static void led_config(void)
{
	gpio_set_pin_high(LED0_GPIO);
	gpio_set_pin_high(LED1_GPIO);
}

/**
 * \brief Handler for INT1, rising edge interrupt. In INT1, it will trigger
 *        INT2.
 */
static void Int1Handler(uint32_t ul_id, uint32_t ul_mask)
{
	if (PIN_PUSHBUTTON_1_ID != ul_id || PIN_PUSHBUTTON_1_MASK != ul_mask)
		return;

	pio_disable_interrupt(PIN_PUSHBUTTON_1_PIO, PIN_PUSHBUTTON_1_MASK);

	/* Trigger INT1 & Delay for a while. */
	puts("===================================================\r");
	puts("Enter _Int1Handler.\r");

	gpio_set_pin_low(LED0_GPIO);

	delay_ticks(2000);

	gpio_set_pin_high(LED0_GPIO);

	puts("Exit _Int1Handler.\r");
	puts("===================================================\r");

	pio_enable_interrupt(PIN_PUSHBUTTON_1_PIO, PIN_PUSHBUTTON_1_MASK);
}

/**
 * \brief Handler for INT2, rising edge interrupt.
 */
static void Int2Handler(uint32_t ul_id, uint32_t ul_mask)
{
	if (PIN_PUSHBUTTON_2_ID != ul_id || PIN_PUSHBUTTON_2_MASK != ul_mask)
		return;

	pio_disable_interrupt(PIN_PUSHBUTTON_2_PIO, PIN_PUSHBUTTON_2_MASK);

	puts("***************************************************\r");
	puts("Enter _Int2Handler.\r");
	/* Enter INT2. */
	gpio_set_pin_low(LED1_GPIO);

	/* Delay for a while. */
	delay_ticks(2000);

	/* Exit INT2. */
	gpio_set_pin_high(LED1_GPIO);

	puts("Exit _Int2Handler.\r");
	puts("***************************************************\r");

	pio_enable_interrupt(PIN_PUSHBUTTON_2_PIO, PIN_PUSHBUTTON_2_MASK);
}

/**
 * \brief Set interrupt priority of INT1 and INT2.
 *
 * \param int1Prior Priority of interrupt 1.
 * \param int2Prior Priority of interrupt 2.
 *
 * Steps to change the IRQ priority:
 * 1. Disable the interrupt service handler.
 * 2. Clear the pending interrupt service handler.
 * 3. Set the new priority.
 * 4. Enable the interrupt service handler.
 */
static void set_interrupt_priority(uint8_t int1Prior, uint8_t int2Prior)
{
	/* Set INT1 priority. */
	NVIC_DisableIRQ((IRQn_Type) PIN_PUSHBUTTON_1_ID);
	NVIC_ClearPendingIRQ((IRQn_Type) PIN_PUSHBUTTON_1_ID);
	NVIC_SetPriority((IRQn_Type) PIN_PUSHBUTTON_1_ID, int1Prior);
	NVIC_EnableIRQ((IRQn_Type) PIN_PUSHBUTTON_1_ID);

	/* Set INT2 priority. */
	NVIC_DisableIRQ((IRQn_Type) PIN_PUSHBUTTON_2_ID);
	NVIC_ClearPendingIRQ((IRQn_Type) PIN_PUSHBUTTON_2_ID);
	NVIC_SetPriority((IRQn_Type) PIN_PUSHBUTTON_2_ID, int2Prior);
	NVIC_EnableIRQ((IRQn_Type) PIN_PUSHBUTTON_2_ID);
}

/**
*  \brief Configure the push buttons.
*
*  Configure the PIOs as inputs and generate corresponding interrupt when
*  the push buttons are pressed or released.
*/
static void configure_buttons(void)
{
	/* Enable the pmc clocks of the push buttons for all SAM3. */
	pmc_enable_periph_clk(PIN_PUSHBUTTON_1_ID);
	pmc_enable_periph_clk(PIN_PUSHBUTTON_2_ID);

	/* Adjust PIO debouncing filter patameters, using 10 Hz filter. */
	pio_set_debounce_filter(PIN_PUSHBUTTON_1_PIO, PIN_PUSHBUTTON_1_MASK,
			10);
	pio_set_debounce_filter(PIN_PUSHBUTTON_2_PIO, PIN_PUSHBUTTON_2_MASK,
			10);

	/* Initialize PIOs interrupt handlers (see PIO definition in board.h). */
	pio_handler_set(PIN_PUSHBUTTON_1_PIO, PIN_PUSHBUTTON_1_ID, PIN_PUSHBUTTON_1_MASK, PIN_PUSHBUTTON_1_ATTR, Int1Handler);	/* Interrupt on rising edge.  */
	pio_handler_set(PIN_PUSHBUTTON_2_PIO, PIN_PUSHBUTTON_2_ID, PIN_PUSHBUTTON_2_MASK, PIN_PUSHBUTTON_2_ATTR, Int2Handler);	/* Interrupt on falling edge. */

	/* Enable PIO controller IRQs. */
	NVIC_EnableIRQ((IRQn_Type) PIN_PUSHBUTTON_1_ID);
	NVIC_EnableIRQ((IRQn_Type) PIN_PUSHBUTTON_2_ID);

	/* PIO configuration for Buttons. */
	pio_handler_set_priority(PIN_PUSHBUTTON_1_PIO, (IRQn_Type) PIN_PUSHBUTTON_1_ID, 0);
	pio_handler_set_priority(PIN_PUSHBUTTON_2_PIO, (IRQn_Type) PIN_PUSHBUTTON_2_ID, 0);

	/* Enable PIO line interrupts. */
	pio_enable_interrupt(PIN_PUSHBUTTON_1_PIO, PIN_PUSHBUTTON_1_MASK);
	pio_enable_interrupt(PIN_PUSHBUTTON_2_PIO, PIN_PUSHBUTTON_2_MASK);
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
 * \brief Display menu.
 */
static void display_menu(void)
{
	puts("\n\r"
		"Menu:\n\r"
		"===================================================\n\r"
		"1: Set INT2's priority higher than INT1.\n\r"
		"2: Set INT1's priority higher than INT2.\n\r"
		"h: Show this menu.\n\r"
		"===================================================\n\r"
		"Press button USR-LEFT/USR-RIGHT to trigger the interrupts.\n\r"
		"\r");
}

/**
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t uc_key;

	/* Initialize the SAM3 system */
	SystemInit();
	board_init();

	WDT->WDT_MR = WDT_MR_WDDIS;

	/* Initialize the console uart */
	configure_console();

	/* Output example information */
	puts(STRING_HEADER);

	/* configure LED. */
	led_config();

	/* configure push buttons. */
	configure_buttons();

	/* Set default priorities for 2 buttons. */
	puts("Set INT1's priority higher than INT2.\r");
	set_interrupt_priority(INT_PRIOR_HIGH, INT_PRIOR_LOW);

	/* Display the main menu. */
	display_menu();

	// Flash the LED.
	while (1) {
		while (uart_read(CONSOLE_UART, &uc_key));

		switch (uc_key) {
		case '1':
			set_interrupt_priority(INT_PRIOR_LOW, INT_PRIOR_HIGH);
			puts("Set INT2's priority higher than INT1.\n\r\r");
			break;

		case '2':
			set_interrupt_priority(INT_PRIOR_HIGH, INT_PRIOR_LOW);
			puts("Set INT1's priority higher than INT2.\n\r\r");
			break;

		case 'h':
			display_menu();
			break;

		default:
			puts("Invalid input.\r");
			break;
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
