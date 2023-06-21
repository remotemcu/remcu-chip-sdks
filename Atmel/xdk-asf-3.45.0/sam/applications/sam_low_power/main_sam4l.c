/**
 * \file
 *
 * \brief Low Power Application.
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
 * \mainpage Low Power Application
 *
 * \section Purpose
 *
 * This example shows the different low power modes with several types
 * of wake-up sources. And the consumption of the core in different power
 * modes can be measured.
 *
 * \section Requirements
 *
 * This package can be used with SAM4L boards.
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
 *
 * - Build the program and download it to the board.
 * - Start the application.
 *
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
	     -- Low Power Example xxx --
	     -- xxxxxx-xx
	     -- Compiled: xxx xx xxxx xx:xx:xx --

	     ===============================================
	     Menu: press a key to continue.
	     ===============================================
	     Configure:
	       0 : Power Saving Mode 0
	       1 : Power Saving Mode 1
	     Mode:
	       A : Active Mode
	       R : Retention Mode
	       W : Wait Mode
	       B : Backup Mode
	     Quit:
	       Q : Quit test.

\endcode
 * -# Press one of the keys listed in the menu to perform the corresponding
 *    action.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"

#define STRING_EOL    "\r"
#define STRING_HEADER "-- Low Power Demo --\r\n" \
"-- "BOARD_NAME" --\r\n" \
"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/** Button pressed flag */
volatile uint32_t g_ul_button_pressed = 0;

/**
 *  Configure serial console.
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

static void display_menu_core(void)
{
	printf("\n\r");
	printf("===============================================\n\r");
	printf("Menu: press a key to continue.\n\r");
	printf("===============================================\n\r");
	printf("Configure:\n\r");
	printf("  0 : Power Saving Mode 0\n\r");
	printf("  1 : Power Saving Mode 1\n\r");
	printf("Mode:\n\r");
	printf("  A : Active Mode\n\r");
	printf("  W : Wait Mode\n\r");
	printf("  R : Retention Mode\n\r");
	printf("  B : Backup Mode\n\r");
	printf("Quit:\n\r");
	printf("  Q : Quit test.\n\r");

	printf("\n\r");
	printf("-----------------------------------------------\n\r");
	printf("\n\r");
}

static void button_handler(void)
{
	/* Check if EIC push button line interrupt line is pending. */
	if (eic_line_interrupt_is_pending(EIC, BUTTON_0_EIC_LINE)) {
		eic_line_clear_interrupt(EIC, BUTTON_0_EIC_LINE);
		g_ul_button_pressed = 1;
		/* Stop AST and reset the counter */
		ast_write_counter_value(AST, 0);
		ast_stop(AST);
	}
}


static void configure_button(void)
{
	struct eic_line_config eic_line_conf;

	eic_line_conf.eic_mode = EIC_MODE_EDGE_TRIGGERED;
	eic_line_conf.eic_edge = EIC_EDGE_FALLING_EDGE;
	eic_line_conf.eic_level = EIC_LEVEL_LOW_LEVEL;
	eic_line_conf.eic_filter = EIC_FILTER_DISABLED;
	eic_line_conf.eic_async = EIC_ASYNCH_MODE;

	eic_enable(EIC);
	eic_line_set_config(EIC, BUTTON_0_EIC_LINE,
			&eic_line_conf);
	eic_line_set_callback(EIC, BUTTON_0_EIC_LINE, button_handler,
			EIC_1_IRQn, 1);
	eic_line_enable(EIC, BUTTON_0_EIC_LINE);
}

/**
 * AST interrupt handler
 */
static void ast_per_callback(void)
{
	ast_stop(AST);
	ast_clear_interrupt_flag(AST, AST_INTERRUPT_PER);
}

/**
 * Initialize AST to generate 1Hz counter
 */
static void config_ast(void)
{
	struct ast_config ast_conf;

	/* Enable osc32 oscillator */
	if (!osc_is_ready(OSC_ID_OSC32)) {
		osc_enable(OSC_ID_OSC32);
		osc_wait_ready(OSC_ID_OSC32);
	}

	/* Enable the AST. */
	ast_enable(AST);

	ast_conf.mode = AST_COUNTER_MODE;
	ast_conf.osc_type = AST_OSC_1KHZ;
	ast_conf.psel = AST_PSEL_32KHZ_1HZ;
	ast_conf.counter = 0;
	ast_set_config(AST, &ast_conf);
	ast_stop(AST);

	/* Set periodic 0 to interrupt after 8 second in counter mode. */
	ast_clear_interrupt_flag(AST, AST_INTERRUPT_PER);
	ast_write_periodic0_value(AST, AST_PSEL_32KHZ_1HZ - 2);
	ast_enable_wakeup(AST, AST_WAKEUP_PER);
	/* Set callback for periodic0. */
	ast_set_callback(AST, AST_INTERRUPT_PER, ast_per_callback,
			AST_PER_IRQn, 1);
}

/* configurations for backup mode wakeup */
static void config_backup_wakeup(void)
{
	/* Take care the table 11-5 in datasheet, not all pin can been set */

	/* Only AST can wakeup the device */
	bpm_enable_wakeup_source(BPM, (1 << BPM_BKUPWEN_AST));

	/**
	 * Retain I/O lines after wakeup from backup.
	 * Disable to undo the previous retention state then enable.
	 */
	bpm_disable_io_retention(BPM);
	bpm_enable_io_retention(BPM);
	/* Enable fast wakeup */
	bpm_enable_fast_wakeup(BPM);
}

static void app_prime_number_run(void)
{
#define PRIM_NUMS 8
	uint32_t i, d, n;
	uint32_t primes[PRIM_NUMS];


	/* Find prime numbers forever */
	primes[0] = 1;
	for (i = 1; i < PRIM_NUMS;) {
		for (n = primes[i - 1] + 1; ;n++) {
			for (d = 2; d <= n; d++) {
				if (n == d) {
					primes[i] = n;
					goto nexti;
				}
				if (n%d == 0) break;
			}
		}
nexti:
		i++;
	}
}

/**
 * \brief Test active mode.
 */
static void test_active_mode(void)
{
	printf("Press %s to exit Active Mode\r\n", BUTTON_0_NAME);

	g_ul_button_pressed = 0;

	/* Test active mode */
	do {
		/* Run Fibonacci calculation, n = 10 (may be changed) */
		app_prime_number_run();
	} while (!g_ul_button_pressed);

	puts("Exit from Active Mode.\r");
}

static void test_wait_mode(void)
{
	printf("Press %s or wait AST to exit Wait Mode\r\n", BUTTON_0_NAME);
	/*
	 * Wait for the printf operation to finish before setting the device in
	 * a power save mode.
	 */
	delay_ms(30);

	ast_start(AST);
	sleepmgr_sleep(SLEEPMGR_WAIT);

	puts("Exit from Wait Mode.\r");
}

static void test_retention_mode(void)
{
	printf("Press %s or wait AST to exit Retention Mode\r\n", BUTTON_0_NAME);
	/*
	 * Wait for the printf operation to finish before setting the device in
	 * a power save mode.
	 */
	delay_ms(30);

	ast_start(AST);
	sleepmgr_sleep(SLEEPMGR_RET);

	puts("Exit from Retention Mode.\r");
}


static void test_backup_mode(void)
{
	puts("Wait AST to exit Backup Mode\r");
	/*
	 * Wait for the puts operation to finish before setting the device in
	 * a power save mode.
	 */
	delay_ms(30);

	ast_start(AST);
	sleepmgr_sleep(SLEEPMGR_BACKUP);

	/* Note: The core will reset when exiting from backup mode. */
}


/**
 * \brief Test Core consumption.
 */
static void test_core(void)
{
	uint32_t uc_key = 0;

	/* Configure button */
	configure_button();

	/* Configurate the AST */
	config_ast();

	/* Configurate the backup wakeup source */
	config_backup_wakeup();

	puts("Power Scaling Mode 1 selected !\r");
	bpm_configure_power_scaling(BPM,BPM_PMCON_PS(BPM_PS_1),true);
	while((bpm_get_status(BPM) & BPM_SR_PSOK) == 0);

	while (1) {
		/* Display menu */
		display_menu_core();

		/* Read a key from console */
		while (usart_read(CONF_UART, &uc_key)) {
		}

		switch (uc_key) {
		/* Configuration */
		case '0':
			bpm_configure_power_scaling(BPM,BPM_PMCON_PS(BPM_PS_0),true);
			while((bpm_get_status(BPM) & BPM_SR_PSOK) == 0);
			puts("Power Scaling Mode 0 selected !\r");
			break;

		case '1':
			bpm_configure_power_scaling(BPM,BPM_PMCON_PS(BPM_PS_1),true);
			while((bpm_get_status(BPM) & BPM_SR_PSOK) == 0);
			puts("Power Scaling Mode 1 selected !\r");
		break;

		/* Mode test */
		case 'a':
		case 'A':
			test_active_mode();
			break;

		case 'r':
		case 'R':
			test_retention_mode();
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
		}
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
	/* Initialize clock */
	sysclk_init();

	/* Initialize board features */
	board_init();

	/* Configure the console uart */
	configure_console();

	/* Output example information */
	puts(STRING_HEADER);

	/* Test core consumption */
	test_core();

	while (1) {
	}

}
