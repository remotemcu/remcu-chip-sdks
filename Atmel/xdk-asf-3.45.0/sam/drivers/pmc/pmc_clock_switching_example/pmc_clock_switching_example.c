/**
 * \file
 *
 * \brief PMC Clock Switching example for SAM.
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
 * \mainpage PMC Clock Switching example
 *
 * \section intro Introduction
 *
 * This example shows how to switch from a clock to another (PLL, SLCK, MAINCK)
 * or change divider.
 *
 * \section Requirements
 *
 * This package can be used with SAM evaluation kits.
 *
 * \section files Main files:
 *  - pmc.c PMC SAM Power Management Controller driver implementation.
 *  - pmc.h PMC SAM Power Management Controller driver definitions.
 *  - pmc_clock_switching_example.c Example application.
 *
 * \section exampledescription Description of the Example
 * Upon startup, the program configures PIOs for UART, PCK and buttons. The
 * baud rate of UART is configured as 2400 bps. The application performs some
 * printf actions with the current configuration (except 32KHz slow clock )
 * and waits for the button pressed to switch to the next configuration. The
 * PCK clock can be selected among PLLA, UPLL, SLCK, MAINCK and driven on the
 * PCK0(For SAM4C_EK, PCK2 is used) pin. After the clock switches, the PCK output
 * signal can be measured by oscilloscope and compared with the clock configuration.
 *
 * <ul>
 * <li> The Clock Generator integrates a 32,768 Hz low-power oscillator.
 * In order to use this oscillator, the XIN32 and XOUT32 pins must be connected
 * to a 32,768 Hz crystal. The user can select the crystal oscillator to be the
 * source of the slow clock, as it provides a more accurate frequency. The
 * switch is made by function pmc_switch_sclk_to_32kxtal().</li>
 * <li> MAINCK is the output of the Main Clock Oscillator selection: either
 * the Crystal Oscillator or 4/8/12 MHz Fast RC Oscillator. The user can
 * select the output frequency of the Fast RC Oscillator: either 4 MHz, 8 MHz
 * or 12 MHz is available. It can be done through function
 * pmc_switch_mainck_to_fastrc(). The user can also select the 3 to 20 MHz
 * Crystal oscillator to be the source of MAINCK, as it provides a more
 * accurate frequency. The function pmc_switch_mainck_to_xtal() shows how to
 * enable the oscillator. </li>
 * <li> The PMC features a PLL block that permits a wide range of frequencies
 * to be selected on either the master clock, the processor clock or the
 * programmable clock. Function pmc_switch_mck_to_pllack() can be used to
 * configure the PLLA.</li>
 * </ul>
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR EWARM.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/">Microchip</A>.\n
 * Support and FAQ: https://www.microchip.com/support/
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "stdio_serial.h"
#include "conf_board.h"
#include "conf_pmc_clock_switching_example.h"

/** User push button activated flag */
static volatile uint8_t gs_uc_wait_button = 0;

/** PMC External Xtal 12Mhz */
#define PMC_CLOCK_SWITCHING_EXAMPLE_BAUDRATE (2400)

#if SAM4C
/** Fixed PLLA test clock, 8.192Mhz */
#define PMC_CLOCK_SWITCHING_EXAMPLE_FIXED_PLLA	(8192000)
#else
/** Fixed PLLA test clock, 128Mhz */
#define PMC_CLOCK_SWITCHING_EXAMPLE_FIXED_PLLA	(128000000)
#endif

#define STRING_EOL    "\r"
#define STRING_HEADER "-- Pmc Clock Switching Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

#if !defined(PMC_PCK_PRES_CLK_1)
#define PMC_PCK_PRES_CLK_1   PMC_PCK_PRES(0)
#define PMC_PCK_PRES_CLK_2   PMC_PCK_PRES(1)
#define PMC_PCK_PRES_CLK_4   PMC_PCK_PRES(2)
#define PMC_PCK_PRES_CLK_8   PMC_PCK_PRES(3)
#define PMC_PCK_PRES_CLK_16  PMC_PCK_PRES(4)
#define PMC_PCK_PRES_CLK_32  PMC_PCK_PRES(5)
#define PMC_PCK_PRES_CLK_64  PMC_PCK_PRES(6)
#endif

/** Programmable Clock ID for the example by default */
#ifndef GCLK_ID
#define GCLK_ID         PMC_PCK_0
#endif
/** Programmable Clock Pin for the example by default */
#ifndef GCLK_PIN
#define GCLK_PIN        PIN_PCK0
#endif
/** Programmable Clock Pin Mux for the example by default */
#ifndef GCLK_PIN_MUX
#define GCLK_PIN_MUX    PIN_PCK0_MUX
#endif

/**
 * \brief Handler for Button 1 rising edge interrupt.
 *
 * Handle process led1 status change.
 */
static void button1_handler(uint32_t ul_id, uint32_t ul_mask)
{
	if (PIN_PUSHBUTTON_1_ID == ul_id && PIN_PUSHBUTTON_1_MASK == ul_mask)
		gs_uc_wait_button = 0;
}

/**
 * \brief Configure the Push buttons
 *
 * Configure the PIO as inputs and generate corresponding interrupt when
 * pressed or released.
 */
static void configure_buttons(void)
{
	/* Enable the peripheral clock for PCK and push button */
	pmc_enable_periph_clk(PIN_PUSHBUTTON_1_ID);

	/* Adjust PIO debounce filter parameters, using 10 Hz filter. */
	pio_set_debounce_filter(PIN_PUSHBUTTON_1_PIO, PIN_PUSHBUTTON_1_MASK, 10);

	/* Initialize PIOs interrupt handlers, see PIO definition in board.h. */
	/* Interrupt on rising edge  */
	pio_handler_set(PIN_PUSHBUTTON_1_PIO, PIN_PUSHBUTTON_1_ID,
			PIN_PUSHBUTTON_1_MASK, PIN_PUSHBUTTON_1_ATTR, button1_handler);

	/* Enable PIO controller IRQs. */
	NVIC_EnableIRQ((IRQn_Type) PIN_PUSHBUTTON_1_ID);

	/* Enable PIO line interrupts. */
	pio_enable_interrupt(PIN_PUSHBUTTON_1_PIO, PIN_PUSHBUTTON_1_MASK);
}

/**
 *  \brief Configure the Console Uart
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
 * \brief Configure UART with the given master clock, and Configure PCK with
 *  the given divider source of master clock and prescaler.
 *
 * \param ul_clock_source  The master clock divider source.
 * \param ul_prescaler Master Clock prescaler.
 * \param ul_master_clock Frequency of the master clock (in Hz).
 */
static void config_uart_and_pck(uint32_t ul_clock_source,
		uint32_t ul_prescaler, uint32_t ul_master_clock)
{
	if (ul_master_clock > BOARD_FREQ_SLCK_XTAL) {
		/* Configure PMC */
		pmc_enable_periph_clk(CONSOLE_UART_ID);
#if (SAMV71 || SAMV70 || SAMS70 || SAME70)
		sam_usart_opt_t usart_settings;
		usart_settings.baudrate = PMC_CLOCK_SWITCHING_EXAMPLE_BAUDRATE;
		usart_settings.char_length = CONF_UART_CHAR_LENGTH;
		usart_settings.parity_type = CONF_UART_PARITY;
		usart_settings.stop_bits= CONF_UART_STOP_BITS;
		usart_settings.channel_mode= US_MR_CHMODE_NORMAL;
		usart_init_rs232(CONSOLE_UART, &usart_settings,
			ul_master_clock / CONFIG_SYSCLK_DIV);
		usart_enable_tx(CONSOLE_UART);
		usart_enable_rx(CONSOLE_UART);
#else
		const sam_uart_opt_t uart_console_settings = {
			ul_master_clock, PMC_CLOCK_SWITCHING_EXAMPLE_BAUDRATE,
			UART_MR_PAR_NO
		};
		/* Configure UART */
		uart_init(CONSOLE_UART, &uart_console_settings);
#endif
	}

	/* Programmable clock output disabled */
	pmc_disable_pck(GCLK_ID);

	/* Configure PMC Programmable Clock */
	switch (ul_clock_source) {
	case PMC_PCK_CSS_MAIN_CLK:
		pmc_switch_pck_to_mainck(GCLK_ID, ul_prescaler);
		break;

	case PMC_PCK_CSS_SLOW_CLK:
		pmc_switch_pck_to_sclk(GCLK_ID, ul_prescaler);
		break;

	case PMC_PCK_CSS_PLLA_CLK:
		pmc_switch_pck_to_pllack(GCLK_ID, ul_prescaler);
		break;

#if (SAM3S || SAM4S || SAM4C)
	case PMC_PCK_CSS_PLLB_CLK:
		pmc_switch_pck_to_pllbck(GCLK_ID, ul_prescaler);
		break;
#endif

	default:
		pmc_switch_pck_to_mainck(GCLK_ID, ul_prescaler);
	}

	/* Enable the PCK again */
	pmc_enable_pck(GCLK_ID);
}

/**
 * \brief Application entry point for pmc_clock switch example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	/* Initialize the console uart */
	configure_console();

	/* Output example information */
	puts(STRING_HEADER);

	/* Configure PCK */
	ioport_set_pin_mode(GCLK_PIN, GCLK_PIN_MUX);
	ioport_disable_pin(GCLK_PIN);

	/* Configure the push button */
	configure_buttons();

	puts("-I- Press Button "BUTTON_NAME" to continue.\r\n");
	/* Wait for UART transmit done */
#if (SAMV71 || SAMV70 || SAMS70 || SAME70)
	while (!usart_is_tx_empty(CONF_UART)) {
	};
#else
	while (!uart_is_tx_empty(CONF_UART)) {
	};
#endif
	for (gs_uc_wait_button = 1; gs_uc_wait_button;) {
	}

	puts("\n\r-I- Switch 8Mhz fast RC oscillator to be the source of the main clock \n\r"
			"-I- The master clock is main clock divided by 2\n\r"
			"-I- From now on, the UART baud rate is 2400bps. So please change the terminal setting before the next clock switch\r\n"
			"-I- Press Button "BUTTON_NAME" to switch next clock configuration... \r\n");
	/* Wait for UART transmit done */
#if (SAMV71 || SAMV70 || SAMS70 || SAME70)
	while (!usart_is_tx_empty(CONF_UART)) {
	};
#else
	while (!uart_is_tx_empty(CONF_UART)) {
	};
#endif

	/* First switch to slow clock */
	pmc_switch_mck_to_sclk(PMC_MCKR_PRES_CLK_1);

#if (SAM3S || SAM4S || SAM4C)
	/* Then cut the PLL B */
	pmc_disable_pllbck();
#endif

	/* Switch the mainck clock to the Fast RC, parameter '1' stands for 8Mhz */
	pmc_switch_mainck_to_fastrc(CKGR_MOR_MOSCRCF_8_MHz);

	/* And finalize by switching to Fast RC */
	pmc_switch_mck_to_mainck(PMC_MCKR_PRES_CLK_2);

	/* The clock source for the UART is the PCK, so the uart needs re-configuration */
	config_uart_and_pck(PMC_PCK_CSS_MAIN_CLK, PMC_PCK_PRES_CLK_2,
			(CHIP_FREQ_MAINCK_RC_8MHZ / 2));

	for (gs_uc_wait_button = 1; gs_uc_wait_button;) {
	}

#if !(SAME70)
	puts("\n\r-I- Switch the XTAL 32K crystal oscillator to be the source of the slow clock\n\r"
			"-I- The master clock is slow clock\n\r"
			"-I- Press Button "BUTTON_NAME" to switch next clock configuration after it has been measured.\r\n");
	/* Wait for UART transmit done */
#if (SAMV71 || SAMV70 || SAMS70 || SAME70)
	while (!usart_is_tx_empty(CONF_UART)) {
	};
#else
	while (!uart_is_tx_empty(CONF_UART)) {
	};
#endif

	/* Enable the External 32K oscillator */
	pmc_switch_sclk_to_32kxtal(PMC_OSC_XTAL);
#endif

	/* If a new value for CSS field corresponds to Main Clock or Slow Clock,
	 * program the CSS field first.
	 */
	pmc_switch_mck_to_sclk(PMC_MCKR_PRES_CLK_1);

	/* The clock source for the UART is the PCK, so the uart needs
	 *re-configuration.
	 */
	config_uart_and_pck(PMC_PCK_CSS_SLOW_CLK, PMC_PCK_PRES_CLK_1,
			BOARD_FREQ_SLCK_XTAL);

	for (gs_uc_wait_button = 1; gs_uc_wait_button;) {
	}

	/* Switch the mainck to the Fast RC, parameter '2' stands for 12Mhz */
	pmc_switch_mainck_to_fastrc(CKGR_MOR_MOSCRCF_12_MHz);

	/* If a new value for CSS field corresponds to Main Clock or Slow Clock,
	 * program the CSS field first.
	 */
	pmc_switch_mck_to_mainck(PMC_PCK_PRES_CLK_1);

	/* The clock source for the UART is the PCK, so the uart needs
	 * re-configuration.
	 */
	config_uart_and_pck(PMC_PCK_CSS_MAIN_CLK, PMC_PCK_PRES_CLK_1,
			CHIP_FREQ_MAINCK_RC_12MHZ);
	puts("\n\r-I- Switch 12Mhz fast RC oscillator to be the source of the main clock\n\r"
			"-I- The master clock is the main clock\n\r"
			"-I- Press Button "BUTTON_NAME" to switch next clock configuration after it has been measured.\r\n");

	for (gs_uc_wait_button = 1; gs_uc_wait_button;) {
	}
#if SAM4C
	puts("-I- Switch to 8.192Mhz PLLA clock as the source of the master clock \n\r"
			"-I- The master clock is PLLA clock divided by 2 \n\r"
			"-I- Press Button "BUTTON_NAME" to switch next clock configuration... \r\n");
	/* Wait for UART transmit done */
	while (!uart_is_tx_empty(CONF_UART)) {
	};

	/* Enable the PLLA clock, the mainck equals 32.768K * 250 = 8.192Mhz */
	pmc_enable_pllack((250 - 1), 0x3f, 1);
#else
	puts("-I- Switch to 128Mhz PLLA clock as the source of the master clock \n\r"
			"-I- The master clock is PLLA clock divided by 2 \n\r"
			"-I- Press Button "BUTTON_NAME" to switch next clock configuration... \r\n");
	/* Wait for UART transmit done */
#if (SAMV71 || SAMV70 || SAMS70 || SAME70)
	while (!usart_is_tx_empty(CONF_UART)) {
	};
#else
	while (!uart_is_tx_empty(CONF_UART)) {
	};
#endif

	/* Enable the PLLA clock, the mainck equals 12Mhz * (32-1+1) / 3 = 128Mhz */
	pmc_enable_pllack((32 - 1), 0x3f, 3);
#endif
	/* If a new value for CSS field corresponds to PLL Clock, Program the PRES
	 * field first.
	 */
	pmc_switch_mck_to_mainck(PMC_MCKR_PRES_CLK_2);

	/* Delay for a while */
	/* Wait for UART transmit done */
#if (SAMV71 || SAMV70 || SAMS70 || SAME70)
	while (!usart_is_tx_empty(CONF_UART)) {
	};
#else
	while (!uart_is_tx_empty(CONF_UART)) {
	};
#endif

	/* Then program the CSS field. */
	pmc_switch_mck_to_pllack(PMC_MCKR_PRES_CLK_2);

	/* The clock source for the UART is the PCK, so the uart needs
	 * re-configuration
	 */
	config_uart_and_pck(PMC_PCK_CSS_PLLA_CLK, PMC_PCK_PRES_CLK_2,
			PMC_CLOCK_SWITCHING_EXAMPLE_FIXED_PLLA/2);

#if !(SAME70)
	for (gs_uc_wait_button = 1; gs_uc_wait_button;) {
	}

	puts("\n\r-I- Switch the XTAL 32K crystal oscillator to be the source of the slow clock\n\r"
			"-I- The master clock is slow clock\n\r"
			"-I- Press Button "BUTTON_NAME" to switch next clock configuration...\r\n");
	/* Wait for UART transmit done */
#if (SAMV71 || SAMV70 || SAMS70 || SAME70)
	while (!usart_is_tx_empty(CONF_UART)) {
	};
#else
	while (!uart_is_tx_empty(CONF_UART)) {
	};
#endif

	/* Switch slow clck to extern 32k xtal */
	pmc_switch_sclk_to_32kxtal(PMC_OSC_XTAL);
#endif

	/* Delay for a while to make sure the clock is stable */
	/* Wait for UART transmit done */
#if (SAMV71 || SAMV70 || SAMS70 || SAME70)
	while (!usart_is_tx_empty(CONF_UART)) {
	};
#else
	while (!uart_is_tx_empty(CONF_UART)) {
	};
#endif

	/* If a new value for CSS field corresponds to Main Clock or Slow Clock,
	 * program the CSS field first.
	 */
	pmc_switch_mck_to_mainck(PMC_MCKR_PRES_CLK_2);

	/* Switch the mck to sclk but keep the PRES field same */
	pmc_switch_mck_to_sclk(PMC_MCKR_PRES_CLK_2);

	/* Then program the PRES field. */
	pmc_switch_mck_to_sclk(PMC_MCKR_PRES_CLK_1);

	/* The clock source for the UART is the PCK, so the uart needs
	 * re-configuration
	 */
	config_uart_and_pck(PMC_PCK_CSS_SLOW_CLK, PMC_PCK_PRES_CLK_1,
			BOARD_FREQ_SLCK_XTAL);

	for (gs_uc_wait_button = 1; gs_uc_wait_button;) {
	}

	/* Switch mainck to external xtal */
	pmc_switch_mainck_to_xtal(0, BOARD_OSC_STARTUP_US);
	/* If a new value for CSS field corresponds to Main Clock or Slow Clock,
	 * program the CSS field first.
	 */
	pmc_switch_mck_to_mainck(PMC_MCKR_PRES_CLK_1);
	/* Then program the PRES field. */
	pmc_switch_mck_to_mainck(PMC_MCKR_PRES_CLK_16);

	/* The clock source for the UART is the PCK, so the uart needs
	 * re-configuration.
	 */
	config_uart_and_pck(PMC_PCK_CSS_MAIN_CLK, PMC_PCK_PRES_CLK_16,
			(BOARD_FREQ_MAINCK_XTAL / 16));
#if SAM4C
	puts("\n\r-I- Switch the external 8MHz crystal oscillator to be the source of the main clock\n\r"
			"-I- The master clock is main  clock divided by 16\n\r"
			"-I- Press Button "BUTTON_NAME" to switch next clock configuration...\r\n");
#else
	puts("\n\r-I- Switch the external 12MHz crystal oscillator to be the source of the main clock\n\r"
			"-I- The master clock is main  clock divided by 16\n\r"
			"-I- Press Button "BUTTON_NAME" to switch next clock configuration...\r\n");
#endif

#if (SAM3S || SAM4S || SAM4C)
	for (gs_uc_wait_button = 1; gs_uc_wait_button;) {
	}

	puts("-I- Switch to 96Mhz PLLB clock as the source of the master clock\n\r"
			"-I- The master clock is PLLB clock divided by 2 \r");
	/* Wait for UART transmit done */
	while (!uart_is_tx_empty(CONF_UART)) {
	};

#if SAM4C
	/* Enable the PLLB clock, the mainck equals (8Mhz * (11+1) / 1) = 96Mhz
	 * with the initialize counter be 0x3f
	 */
	 pmc_enable_pllbck(11, 0x3f, 1);
#else
	/* Enable the PLLB clock, the mainck equals (12Mhz * (7+1) / 1) = 96Mhz
	 * with the initialize counter be 0x3f
	 */
	pmc_enable_pllbck(7, 0x3f, 1);
#endif

	/* If a new value for CSS field corresponds to PLL Clock, Program the PRES
	 * field first.
	 */
	pmc_switch_mck_to_mainck(PMC_MCKR_PRES_CLK_2);

	/* Then program the CSS field. */
	pmc_switch_mck_to_pllbck(PMC_MCKR_PRES_CLK_2);

	/* The clock source for the UART is the PCK, so the uart needs
	 * re-configuration.
	 */
#if SAM4C
	config_uart_and_pck(PMC_PCK_CSS_PLLB_CLK, PMC_PCK_PRES_CLK_2,
			(BOARD_FREQ_MAINCK_XTAL * 12 / 2));
#else
	config_uart_and_pck(PMC_PCK_CSS_PLLB_CLK, PMC_PCK_PRES_CLK_2,
			(BOARD_FREQ_MAINCK_XTAL * 8 / 2));
#endif
	puts("-I- Press Button "BUTTON_NAME" to switch next clock configuration...\r\n");
#endif

	for (gs_uc_wait_button = 1; gs_uc_wait_button;) {
	}
	puts("\r\n\r\n-I- Done.\r\n");
	/* Wait for UART transmit done */
#if (SAMV71 || SAMV70 || SAMS70 || SAME70)
	while (!usart_is_tx_empty(CONF_UART)) {
	};
#else
	while (!uart_is_tx_empty(CONF_UART)) {
	};
#endif

	while (1) {
	}
}

