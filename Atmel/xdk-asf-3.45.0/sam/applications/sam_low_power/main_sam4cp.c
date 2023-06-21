/**
 * \file
 *
 * \brief Low Power Application.
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
 * \mainpage Low Power Application
 *
 * \section Purpose
 *
 * This example shows all the different low power modes with several types
 * of wake-up sources. And the consumption of the core in different power
 * modes can be measured.
 *
 * \section Requirements
 *
 * This package can be used with SAM evaluation kits.
 *
 * \section Description
 *
 * The program will display a menu on console. It allows users to change the
 * configuration and enter into a different power mode, and then measure the
 * power consumption.
 *
 * An amperemeter has to be plugged on the board instead of the VDDx jumper.
 *
 * Note that for better consumption measurement:
 * - Run program out of flash without ICE connected.
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
 *     -- Low Power Example xxx --
 *     -- xxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *
 *     ===============================================
 *     Menu: press a key to continue.
 *     ===============================================
 *     Configure:
 *       F : 128-bit flash access
 *       G : 64-bit flash access
 *     Mode:
 *       A : Active Mode
 *       S : Sleep Mode
 *       W : Wait Mode
 *       B : Backup Mode(Entered 1 times).
 *     Quit:
 *       Q : Quit test.
 *
 *     -----------------------------------------------
 *     Current configuration:
 *       CPU Clock         : MCK=24000000 Hz
 *       Flash access mode : 128-bit
 *     -----------------------------------------------
 *    \endcode
 * -# Press one of the keys listed in the menu to perform the corresponding
 *    action.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "stdio_serial.h"
#include "conf_board.h"
#include "conf_clock.h"
#include "conf_uart_serial.h"
#include "low_power_board.h"
#include "led.h"
#include "supc.h"




#if !defined(PMC_PCK_PRES_CLK_1)
#define PMC_PCK_PRES_CLK_1   PMC_PCK_PRES(0)
#define PMC_PCK_PRES_CLK_2   PMC_PCK_PRES(1)
#define PMC_PCK_PRES_CLK_4   PMC_PCK_PRES(2)
#define PMC_PCK_PRES_CLK_8   PMC_PCK_PRES(3)
#define PMC_PCK_PRES_CLK_16  PMC_PCK_PRES(4)
#define PMC_PCK_PRES_CLK_32  PMC_PCK_PRES(5)
#define PMC_PCK_PRES_CLK_64  PMC_PCK_PRES(6)
#endif

#define STRING_EOL    "\r"
#define STRING_HEADER "-- Low Power Example --\r\n" \
	"-- "BOARD_NAME " --\r\n" \
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

#ifndef PLL_DEFAULT_MUL
#define PLL_DEFAULT_MUL  7
#endif

#ifndef PLL_DEFAULT_DIV
#define PLL_DEFAULT_DIV  1
#endif

#ifndef MCK_DEFAULT_DIV
#define MCK_DEFAULT_DIV  PMC_MCKR_PRES_CLK_4
#endif

#ifndef example_switch_clock
#define example_switch_clock(a, b, c, d) \
	do {                                 \
		pmc_enable_pllack(a, b, c);      \
		pmc_switch_mck_to_pllack(d);     \
	} while (0)
#endif

#ifndef example_disable_pll
#define example_disable_pll()  pmc_disable_pllack()
#endif

#ifndef example_set_wakeup_from_backup_mode
#define example_set_wakeup_from_backup_mode() \
	supc_set_wakeup_inputs(SUPC, WAKEUP_BACKUP_INPUT_ID, \
			WAKEUP_BACKUP_INPUT_ID)
#endif

/** Current MCK in Hz */
uint32_t g_ul_current_mck;

/** Button pressed flag */
volatile uint32_t g_ul_button_pressed = 0;

static inline void configure_button_FWUP(void);
static inline void disable_button_FWUP(void);
static inline void configure_button_TMP0(void);
static inline void disable_button_TMP0(void);

/**
 * \brief Set default clock (MCK = 24MHz).
 */
static void set_default_working_clock(void)
{
	/* Switch MCK to slow clock  */
	pmc_switch_mck_to_sclk(PMC_MCKR_PRES_CLK_1);

	/* Switch mainck to external xtal */
	pmc_switch_mainck_to_xtal(0, BOARD_OSC_STARTUP_US);

	/*
	 * Configure PLL and switch clock.
	 * MCK = XTAL * (PLL_DEFAULT_MUL+1) / PLL_DEFAULT_DIV / MCK_DEFAULT_DIV
	 *     = 24 MHz
	 */
	example_switch_clock(PLL_DEFAULT_MUL, PLL_COUNT, PLL_DEFAULT_DIV,
			MCK_DEFAULT_DIV);

	/* Disable unused clock to save power */
	pmc_osc_disable_fastrc();

	/* Save current clock */
	g_ul_current_mck = 240000000; /* 24 MHz */
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
	pio_configure_pin_group(PINS_UART_PIO, PINS_UART_PORT,
			PINS_UART_FLAGS);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 *  Reconfigure UART console for changed MCK and baudrate.
 */
static void reconfigure_console(uint32_t ul_mck, uint32_t ul_baudrate)
{
	const sam_uart_opt_t uart_console_settings =
			{ ul_mck, ul_baudrate, UART_MR_PAR_NO };

	/* Configure PMC */
	pmc_enable_periph_clk(CONSOLE_UART_ID);

	/* Configure PIO */
	pio_configure_pin_group(PINS_UART_PIO, PINS_UART_PORT,
			PINS_UART_FLAGS);

	/* Configure UART */
	uart_init(CONF_UART, &uart_console_settings);
}

/**
 * \brief Initialize the chip for low power test.
 */
static void init_chip(void)
{
	/* Wait for the transmission done before changing clock */
	while (!uart_is_tx_empty(CONSOLE_UART)) {
	}

	/* Disable all the peripheral clocks */
	pmc_disable_all_periph_clk();

	/* Disable brownout detector */
	supc_disable_brownout_detector(SUPC);

	/* Initialize the specific board */
	init_specific_board();
}

/**
 * \brief Change clock configuration.
 *
 * \param p_uc_str Hint string to be output on console before changing clock.
 */
static void user_change_clock(uint8_t *p_uc_str)
{
	uint8_t uc_key;
	uint32_t ul_id;

	/* Print menu */
	puts(CLOCK_LIST_MENU);

	while (uart_read(CONSOLE_UART, &uc_key)) {
	}
	printf("Select option is: %c\n\r\n\r", uc_key);
	if (p_uc_str) {
		puts((char const *)p_uc_str);
	}

	while (!uart_is_tx_empty(CONSOLE_UART)) {
	}

	if ((uc_key >= MIN_CLOCK_FAST_RC_ITEM) &&
			(uc_key <= MAX_CLOCK_FAST_RC_ITEM)) {
		ul_id = uc_key - MIN_CLOCK_FAST_RC_ITEM;

		/* Save current clock */
		g_ul_current_mck = g_fastrc_clock_list[ul_id][0];

		/* Switch MCK to Slow clock  */
		pmc_switch_mck_to_sclk(PMC_MCKR_PRES_CLK_1);

		/* Switch mainck to fast RC */
		pmc_osc_enable_fastrc(CKGR_MOR_MOSCRCF_4_MHz);
		pmc_switch_mainck_to_fastrc(g_fastrc_clock_list[ul_id][1]);

		/* Switch MCK to mainck */
		pmc_switch_mck_to_mainck(g_fastrc_clock_list[ul_id][2]);

		/* Disable unused clock to save power */
		pmc_osc_disable_xtal(0);
		example_disable_pll();

	} else if ((uc_key >= MIN_CLOCK_PLL_ITEM) &&
			(uc_key <= MAX_CLOCK_PLL_ITEM)) {
		ul_id = uc_key - MIN_CLOCK_PLL_ITEM;

		/* Save current clock */
		g_ul_current_mck = g_pll_clock_list[ul_id][0];

		/* Switch MCK to slow clock  */
		pmc_switch_mck_to_sclk(PMC_MCKR_PRES_CLK_1);

		/* Switch mainck to external xtal */
		pmc_switch_mainck_to_xtal(0, BOARD_OSC_STARTUP_US);
		/* Configure PLL and switch clock */
		example_switch_clock(g_pll_clock_list[ul_id][1], PLL_COUNT,
				g_pll_clock_list[ul_id][2], g_pll_clock_list[ul_id][3]);

		/* Disable unused clock to save power */
		pmc_osc_disable_fastrc();
	} else {
		puts("Clock is not changed.\r");
	}
}

/**
 * \brief Handler for button interrupt.
 *
 * \note This interrupt is for waking up from sleep mode or exiting from active
 * mode.
 */
static void button_handler(uint32_t ul_id, uint32_t ul_mask)
{
	if(PIN_PUSHBUTTON_WAKEUP_ID==ul_id && PIN_PUSHBUTTON_WAKEUP_MASK==ul_mask){
		g_ul_button_pressed = 1;
	}
}



/**
 *  \brief Configure the push button.
 *
 *  Configure the PIO as inputs and generate corresponding interrupt when
 *  pressed or released.
 */
static void configure_button(void)
{
	/* Adjust PIO debounce filter parameters, using 10 Hz filter. */
	pio_set_debounce_filter(PIN_PUSHBUTTON_WAKEUP_PIO,
			PIN_PUSHBUTTON_WAKEUP_MASK, 10);

	/* Initialize PIO interrupt handlers, see PIO definition in board.h. */
	pio_handler_set(PIN_PUSHBUTTON_WAKEUP_PIO, PIN_PUSHBUTTON_WAKEUP_ID,
			PIN_PUSHBUTTON_WAKEUP_MASK, PIN_PUSHBUTTON_WAKEUP_ATTR,
			button_handler);

	/* Enable PIO controller IRQs. */
	NVIC_EnableIRQ((IRQn_Type)PIN_PUSHBUTTON_WAKEUP_ID);

	/* Enable PIO line interrupts. */
	pio_enable_interrupt(PIN_PUSHBUTTON_WAKEUP_PIO,
			PIN_PUSHBUTTON_WAKEUP_MASK);




}

static inline void configure_button_FWUP(void)
{
	supc_set_wakeup_mode(SUPC, SUPC_WUMR_FWUPDBC_32_SCLK);
	supc_set_wakeup_mode(SUPC, SUPC_WUMR_WKUPDBC_32_SCLK);
	supc_set_wakeup_mode(SUPC, SUPC_WUMR_FWUPEN_ENABLE);
}

static inline void disable_button_FWUP(void)
{
	supc_set_wakeup_mode(SUPC, SUPC_WUMR_FWUPDBC_IMMEDIATE);
	supc_set_wakeup_mode(SUPC, SUPC_WUMR_FWUPEN_NOT_ENABLE);
}

static inline void configure_button_TMP0(void)
{
	supc_set_wakeup_mode(SUPC,SUPC_WUMR_LPDBC_2_RTCOUT0);
	supc_set_wakeup_mode(SUPC, SUPC_WUMR_LPDBCEN0_ENABLE);
}

static inline void disable_button_TMP0(void)
{
	supc_set_wakeup_mode(SUPC,SUPC_WUMR_LPDBC_DISABLE);
	supc_set_wakeup_mode(SUPC, SUPC_WUMR_LPDBCEN0_NOT_ENABLE);
}

/**
 * \brief Fibonacci calculation.
 *
 * \param ul_n Number N.
 */
static uint32_t fib(uint32_t ul_n)
{
	if (ul_n < 2) {
		return ul_n;
	} else {
		return fib(ul_n - 1) + fib(ul_n - 2);
	}
}

/**
 * \brief Test active mode.
 */
static void test_active_mode(void)
{
	/* Configure button for exiting from active mode */
	configure_button();

	g_ul_button_pressed = 0;

	/* Select clock for active mode */
	user_change_clock(STRING_ACTIVE);

	/* Test active mode */
	do {
		/* Run Fibonacci calculation, n = 10 (may be changed) */
		fib(10);
	} while (!g_ul_button_pressed);

	/* Set default clock and re-configure UART */
	set_default_working_clock();
	reconfigure_console(g_ul_current_mck, CONF_UART_BAUDRATE);

	puts("Exit from active mode.\r");
}

/**
 * \brief Test sleep Mode.
 */
static void test_sleep_mode(void)
{
	/* Configure button for waking up sleep mode */
	configure_button();

	/* Select clock for sleep mode */
	user_change_clock(STRING_SLEEP);

	/* Enter into sleep Mode */
	pmc_enable_sleepmode(0);

	/* Set default clock and re-configure UART */
	set_default_working_clock();
	reconfigure_console(g_ul_current_mck, CONF_UART_BAUDRATE);

	puts("Exit from sleep Mode.\r");
}

/**
 * \brief Test wait mode.
 */
static void test_wait_mode(void)
{
	puts(STRING_WAIT);

	/* Wait for the transmission done before changing clock */
	while (!uart_is_tx_empty(CONSOLE_UART)) {
	}

	/* Configure 4Mhz fast RC oscillator */
	pmc_switch_mck_to_sclk(PMC_MCKR_PRES_CLK_1);
	pmc_switch_mainck_to_fastrc(CKGR_MOR_MOSCRCF_4_MHz);
	pmc_switch_mck_to_mainck(PMC_PCK_PRES_CLK_1);

	g_ul_current_mck = 4000000; /* 4MHz */

	/* Disable unused clock to save power */
	pmc_osc_disable_xtal(0);
	example_disable_pll();

	/* Set wakeup input for fast startup */
	pmc_set_fast_startup_input(WAKEUP_WAIT_INPUT_ID);

	/* Enter into wait Mode */
	pmc_enable_waitmode();

	/* Set default clock and re-configure UART */
	set_default_working_clock();
	reconfigure_console(g_ul_current_mck, CONF_UART_BAUDRATE);

	puts("Exit from wait Mode.\r");
}

/**
 * \brief Test backup mode.
 *
 * \note To test backup mode, the program must run out of flash.
 */
static void test_backup_mode(void)
{
	puts(STRING_BACKUP);

	/* Wait for the transmission done before changing clock */
	while (!uart_is_tx_empty(CONSOLE_UART)) {
	}


	/* GPBR0 is for recording times of entering into backup mode */
	gpbr_write(GPBR0, gpbr_read(GPBR0) + 1);

	/* Enable the PIO for wake-up */
	example_set_wakeup_from_backup_mode();
	configure_button_FWUP();
	/* Switch MCK to slow clock  */
	pmc_switch_mck_to_sclk(PMC_MCKR_PRES_CLK_1);

	/* ENABLE XTAL CLOCK */
	pmc_osc_disable_xtal(0);
	/*  disable PLL */
	pmc_disable_pllack();


	/* Enter into backup mode */
	pmc_enable_backupmode();

	/* Note: The core will reset when exiting from backup mode. */
}

/**
 * \brief Display test core menu.
 */
static void display_menu_core(void)
{


	printf ("\n\r");
	printf("===============================================\n\r");
	printf("Menu: press a key to continue.\n\r");
	printf("===============================================\n\r");
	printf("Configure:\n\r");
	printf("  F : 128-bit flash access\n\r");
	printf("  G : 64-bit flash access\n\r");
	printf("Mode:\n\r");
	printf("  A : Active Mode\n\r");
	printf("  S : Sleep Mode\n\r");
	printf("  W : Wait Mode\n\r");
	printf("  B : Backup Mode(Entered %d times).\n\r", (int)gpbr_read(GPBR0));
	printf("Quit:\n\r");
	printf("  Q : Quit test.\n\r");

	printf("\n\r");
	printf("-----------------------------------------------\n\r");
	printf("Current configuration:\n\r");
	printf("  CPU Clock         : MCK=%d Hz\n\r", (int)g_ul_current_mck);
	if ((efc_get_flash_access_mode(EFC) & EEFC_FMR_FAM) == EEFC_FMR_FAM) {
		printf("  Flash access mode : 64-bit\n\r");
	} else {
		printf("  Flash access mode : 128-bit\n\r");
	}

	printf("-----------------------------------------------\n\r");
	printf("\n\r");
}

/**
 * \brief Test Core consumption.
 */
static void test_core(void)
{
	uint8_t uc_key = 0;

	while (1) {
		/* Display menu */
		display_menu_core();

		/* Read a key from console */
		while (uart_read(CONSOLE_UART, &uc_key)) {
		}

		switch (uc_key) {
		/* Configuration */
		case 'f':
		case 'F':
			efc_set_flash_access_mode(EFC, 0); /* 128-bit */
			break;
		case 'g':
		case 'G':
			efc_set_flash_access_mode(EFC, EEFC_FMR_FAM); /* 64-bit */
			break;
		/* Mode test */
		case 'a':
		case 'A':
			test_active_mode();
			break;
		case 's':
		case 'S':
			test_sleep_mode();
			break;
		case 'w':
		case 'W':
			test_wait_mode();
			break;
		case 'b':
		case 'B':
			test_backup_mode();
			break;
		/* Quit test */
		case 'q':
		case 'Q':
			goto test_core_end;

		default:
			puts("This menu does not exist !\r");
			break;
		}       /* Switch */
	}

test_core_end:
	puts(" Exit from core consumption test mode.\r");
}




/**
 * \brief Low power application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Initialize the SAM system */
	sysclk_init();
	g_ul_current_mck = sysclk_get_cpu_hz();

	board_init();

	/* Initialize the console uart */
	configure_console();

	/* Output example information */
	puts(STRING_HEADER);

	/* Test core consumption */
	test_core();

	while (1) {

	}
}
