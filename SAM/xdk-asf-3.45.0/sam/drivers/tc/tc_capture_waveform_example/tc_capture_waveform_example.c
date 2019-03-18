/**
 * \file
 *
 * \brief TC Capture Waveform Example for SAM.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <conf_board.h>
#include <conf_clock.h>

/// @cond
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

#define STRING_EOL    "\r"
#define STRING_HEADER "--TC capture waveform Example --\r\n" \
		"-- "BOARD_NAME " --\r\n" \
		"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

//! [tc_capture_selection]
#define TC_CAPTURE_TIMER_SELECTION TC_CMR_TCCLKS_TIMER_CLOCK3
//! [tc_capture_selection]

struct waveconfig_t {
	/** Internal clock signals selection. */
	uint32_t ul_intclock;
	/** Waveform frequency (in Hz). */
	uint16_t us_frequency;
	/** Duty cycle in percent (positive).*/
	uint16_t us_dutycycle;
};

/** TC waveform configurations */
static const struct waveconfig_t gc_waveconfig[] = {
	{TC_CMR_TCCLKS_TIMER_CLOCK4, 178, 30},
	{TC_CMR_TCCLKS_TIMER_CLOCK3, 375, 50},
	{TC_CMR_TCCLKS_TIMER_CLOCK3, 800, 75},
	{TC_CMR_TCCLKS_TIMER_CLOCK2, 1000, 80},
	{TC_CMR_TCCLKS_TIMER_CLOCK2, 4000, 55}
};

#if (SAM4L)
/* The first one is meaningless */
static const uint32_t divisors[5] = { 0, 2, 8, 32, 128};
#else
/* The last one is meaningless */
static const uint32_t divisors[5] = { 2, 8, 32, 128, 0};
#endif

/** Current wave configuration*/
static uint8_t gs_uc_configuration = 0;

/** Number of available wave configurations */
const uint8_t gc_uc_nbconfig = sizeof(gc_waveconfig)
		/ sizeof(struct waveconfig_t);

/** Capture status*/
static uint32_t gs_ul_captured_pulses;
static uint32_t gs_ul_captured_ra;
static uint32_t gs_ul_captured_rb;

/**
 * \brief Display the user menu on the UART.
 */
static void display_menu(void)
{
	uint8_t i;
	puts("\n\rMenu :\n\r"
			"------\n\r"
			"  Output waveform property:\r");
	for (i = 0; i < gc_uc_nbconfig; i++) {
		printf("  %d: Set Frequency = %4u Hz, Duty Cycle = %2u%%\n\r", i,
				(unsigned int)gc_waveconfig[i].us_frequency,
				(unsigned int)gc_waveconfig[i].us_dutycycle);
	}
	printf("  -------------------------------------------\n\r"
			"  c: Capture waveform from TC%d channel %d\n\r"
			"  s: Stop capture and display captured information \n\r"
			"  h: Display menu \n\r"
			"------\n\r\r", TC_PERIPHERAL,TC_CHANNEL_CAPTURE);
}

/**
 * \brief Configure TC TC_CHANNEL_WAVEFORM in waveform operating mode.
 */
static void tc_waveform_initialize(void)
{
	uint32_t ra, rc;

	/* Configure the PMC to enable the TC module. */
	sysclk_enable_peripheral_clock(ID_TC_WAVEFORM);
#if SAMG55
	/* Enable PCK output */
	pmc_disable_pck(PMC_PCK_3);
	pmc_switch_pck_to_mck(PMC_PCK_3, PMC_PCK_PRES(0));
	pmc_enable_pck(PMC_PCK_3);
#endif

	/* Init TC to waveform mode. */
	tc_init(TC, TC_CHANNEL_WAVEFORM,
			/* Waveform Clock Selection */
			gc_waveconfig[gs_uc_configuration].ul_intclock
			| TC_CMR_WAVE /* Waveform mode is enabled */
			| TC_CMR_ACPA_SET /* RA Compare Effect: set */
			| TC_CMR_ACPC_CLEAR /* RC Compare Effect: clear */
			| TC_CMR_CPCTRG /* UP mode with automatic trigger on RC Compare */
	);

	/* Configure waveform frequency and duty cycle. */
	rc = (sysclk_get_peripheral_bus_hz(TC) /
			divisors[gc_waveconfig[gs_uc_configuration].ul_intclock]) /
			gc_waveconfig[gs_uc_configuration].us_frequency;
	tc_write_rc(TC, TC_CHANNEL_WAVEFORM, rc);
	ra = (100 - gc_waveconfig[gs_uc_configuration].us_dutycycle) * rc / 100;
	tc_write_ra(TC, TC_CHANNEL_WAVEFORM, ra);

	/* Enable TC TC_CHANNEL_WAVEFORM. */
	tc_start(TC, TC_CHANNEL_WAVEFORM);
	printf("Start waveform: Frequency = %d Hz,Duty Cycle = %2d%%\n\r",
			gc_waveconfig[gs_uc_configuration].us_frequency,
			gc_waveconfig[gs_uc_configuration].us_dutycycle);
}

/**
 * \brief Configure TC TC_CHANNEL_CAPTURE in capture operating mode.
 */
//! [tc_capture_init]
static void tc_capture_initialize(void)
{
	/* Configure the PMC to enable the TC module */
	sysclk_enable_peripheral_clock(ID_TC_CAPTURE);
#if SAMG55
	/* Enable PCK output */
	pmc_disable_pck(PMC_PCK_3);
	pmc_switch_pck_to_mck(PMC_PCK_3, PMC_PCK_PRES(0));
	pmc_enable_pck(PMC_PCK_3);
#endif

	/* Init TC to capture mode. */
	tc_init(TC, TC_CHANNEL_CAPTURE,
			TC_CAPTURE_TIMER_SELECTION /* Clock Selection */
			| TC_CMR_LDRA_RISING /* RA Loading: rising edge of TIOA */
			| TC_CMR_LDRB_FALLING /* RB Loading: falling edge of TIOA */
			| TC_CMR_ABETRG /* External Trigger: TIOA */
			| TC_CMR_ETRGEDG_FALLING /* External Trigger Edge: Falling edge */
	);
}
//! [tc_capture_init]

/**
 * \brief Interrupt handler for the TC TC_CHANNEL_CAPTURE
 */
//! [tc_capture_irq_handler_start]
void TC_Handler(void)
{
	//! [tc_capture_irq_handler_start]
	//! [tc_capture_irq_handler_status]
	if ((tc_get_status(TC, TC_CHANNEL_CAPTURE) & TC_SR_LDRBS) == TC_SR_LDRBS) {
		//! [tc_capture_irq_handler_status]
		gs_ul_captured_pulses++;
		//! [tc_capture_irq_handler_read_ra]
		gs_ul_captured_ra = tc_read_ra(TC, TC_CHANNEL_CAPTURE);
		//! [tc_capture_irq_handler_read_ra]
		//! [tc_capture_irq_handler_read_rb]
		gs_ul_captured_rb = tc_read_rb(TC, TC_CHANNEL_CAPTURE);
		//! [tc_capture_irq_handler_read_rb]
	}
//! [tc_capture_irq_handler_end]
}
//! [tc_capture_irq_handler_end]

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
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief Application entry point for tc_capture_waveform example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t key;
	uint16_t frequence, dutycycle;

	/* Initialize the SAM system */
	sysclk_init();
	board_init();

	/* Initialize the console uart */
	configure_console();

	/* Output example information */
	printf("-- TC capture waveform Example --\r\n");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	//! [tc_waveform_gpio]
	/** Configure PIO Pins for TC */
	ioport_set_pin_mode(PIN_TC_WAVEFORM, PIN_TC_WAVEFORM_MUX);
	/** Disable I/O to enable peripheral mode) */
	ioport_disable_pin(PIN_TC_WAVEFORM);
	//! [tc_waveform_gpio]
	
	//! [tc_capture_gpio]
	/** Configure PIO Pins for TC */
	ioport_set_pin_mode(PIN_TC_CAPTURE, PIN_TC_CAPTURE_MUX);
	/** Disable I/O to enable peripheral mode) */
	ioport_disable_pin(PIN_TC_CAPTURE);
	//! [tc_capture_gpio]

	/* Configure TC TC_CHANNEL_WAVEFORM as waveform operating mode */
	printf("Configure TC%d channel %d as waveform operating mode \n\r",
			TC_PERIPHERAL, TC_CHANNEL_WAVEFORM);
	//! [tc_waveform_init_call]
	tc_waveform_initialize();
	//! [tc_waveform_init_call]
        
	/* Configure TC TC_CHANNEL_CAPTURE as capture operating mode */
	printf("Configure TC%d channel %d as capture operating mode \n\r",
			TC_PERIPHERAL, TC_CHANNEL_CAPTURE);
	//! [tc_capture_init_call]
	tc_capture_initialize();
	//! [tc_capture_init_call]

	//! [tc_capture_init_irq]
	/** Configure TC interrupts for TC TC_CHANNEL_CAPTURE only */
	NVIC_DisableIRQ(TC_IRQn);
	NVIC_ClearPendingIRQ(TC_IRQn);
	NVIC_SetPriority(TC_IRQn, 0);
	NVIC_EnableIRQ(TC_IRQn);
	//! [tc_capture_init_irq]

	/* Display menu */
	display_menu();

	while (1) {
		scanf("%c", (char *)&key);

		switch (key) {
		case 'h':
			display_menu();
			break;

		case 's':
			if (gs_ul_captured_pulses) {
				tc_disable_interrupt(TC, TC_CHANNEL_CAPTURE, TC_IDR_LDRBS);
				printf("Captured %u pulses from TC%d channel %d, RA = %u, RB = %u \n\r",
						(unsigned)gs_ul_captured_pulses, TC_PERIPHERAL,
						TC_CHANNEL_CAPTURE,	(unsigned)gs_ul_captured_ra,
						(unsigned)gs_ul_captured_rb);
				frequence = (sysclk_get_peripheral_bus_hz(TC) /
						divisors[TC_CAPTURE_TIMER_SELECTION]) /
						gs_ul_captured_rb;
				dutycycle
					= (gs_ul_captured_rb - gs_ul_captured_ra) * 100 /
						gs_ul_captured_rb;
				printf("Captured wave frequency = %d Hz, Duty cycle = %d%% \n\r",
						frequence, dutycycle);

				gs_ul_captured_pulses = 0;
				gs_ul_captured_ra = 0;
				gs_ul_captured_rb = 0;
			} else {
				puts("No waveform has been captured\r");
			}

			puts("\n\rPress 'h' to display menu\r");
			break;

		case 'c':
			puts("Start capture, press 's' to stop \r");
			//! [tc_capture_init_module_irq]
			tc_enable_interrupt(TC, TC_CHANNEL_CAPTURE, TC_IER_LDRBS);
			//! [tc_capture_init_module_irq]
			/* Start the timer counter on TC TC_CHANNEL_CAPTURE */
			//! [tc_capture_start_now]
			tc_start(TC, TC_CHANNEL_CAPTURE);
			//! [tc_capture_start_now]
			break;

		default:
			/* Set waveform configuration #n */
			if ((key >= '0') && (key <= ('0' + gc_uc_nbconfig - 1))) {
				if (!gs_ul_captured_pulses) {
					gs_uc_configuration = key - '0';
					tc_waveform_initialize();
				} else {
					puts("Capturing ... , press 's' to stop capture first \r");
				}
			}

			break;
		}
	}
}

/// @cond
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
