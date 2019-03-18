/**
 * \file
 *
 * \brief Serial Peripheral Interface (SPI) PDC example for SAM.
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
 * \mainpage SPI PDC Example
 *
 * \par Purpose
 *
 * This example uses Serial Peripheral Interface (SPI) of one EK board in
 * slave mode to communicate with another EK board's SPI in master mode
 * by PDC function.
 *
 * \par Requirements
 *
 * This package can be used with two SAM evaluation kits boards.
 * Please connect the SPI pins from one board to another.
 * \copydoc spi_example_pin_defs
 *
 * \par Descriptions
 *
 * This example shows control of the SPI, and how to configure and
 * transfer data with SPI. By default, example runs in SPI slave mode,
 * waiting SPI slave & UART inputs.
 *
 * This example has been tested with the following board:
 * - sam3n4c_sam3n_ek
 * - sam3s4c_sam3s_ek
 * - sam3sd8c_sam3s_ek2
 * - sam4s16c_sam4s_ek
 * - sam4sd32c_sam4s_ek2
 * - sam4n16c_sam4n_xplained_pro
 * - sam4c16c_sam4c_ek
 * - samg53n19_samg_xplained_pro
 * - sam4cp16b_sam4cp16bmb
 * - samg55j19_samg_xplained_pro
 *
 * The code can be roughly broken down as follows:
 * <ul>
 * <li> 't' will start SPI transfer test.
 * <ol>
 * <li>Configure SPI as master, and set up SPI clock.
 * <li>Send 64-byte data and receive data from slave at same time, after that
 * compare the result.
 * </ol>
 * <li>Setup SPI clock for master.
 * </ul>
 *
 * \par Usage
 *
 * -# Compile the application.
 * -# Connect the UART port of the evaluation board to the computer and open
 * it in a terminal.
 *    - Settings: 115200 bauds, 8 bits, 1 stop bit, no parity, no flow control.
 * -# Download the program into the evaluation board and run it.
 * -# Upon startup, the application will output the following line on the terminal:
 *    \code
	-- Spi Pdc Example  --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 * -# The following traces detail operations on the SPI PDC example,
 *  displaying success or error messages depending on the results of the
 *  commands.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "conf_board.h"
#include "conf_spi_pdc_example.h"
#include "delay.h"
#if (SAMG55)
#include "flexcom.h"
#endif

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/* Chip select. */
#define SPI_CHIP_SEL 0

/* Clock polarity. */
#define SPI_CLK_POLARITY 0

/* Clock phase. */
#define SPI_CLK_PHASE 0

/* Delay before SPCK. */
#define SPI_DLYBS 0x40

/* Delay between consecutive transfers. */
#define SPI_DLYBCT 0x10

/* SPI Communicate buffer size. */
#define COMM_BUFFER_SIZE   64

/* UART baudrate. */
#define UART_BAUDRATE      115200

/* Number of SPI clock configurations. */
#define NUM_SPCK_CONFIGURATIONS 4

#define STRING_EOL    "\r"
#define STRING_HEADER "-- Spi Pdc Example  --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/* SPI clock setting (Hz). */
static uint32_t gs_ul_spi_clock = 500000;

/* 64 bytes data buffer for SPI transfer and receive. */
static uint8_t gs_uc_spi_m_tbuffer[COMM_BUFFER_SIZE];
static uint8_t gs_uc_spi_m_rbuffer[COMM_BUFFER_SIZE];
static uint8_t gs_uc_spi_s_tbuffer[COMM_BUFFER_SIZE];
static uint8_t gs_uc_spi_s_rbuffer[COMM_BUFFER_SIZE];

/* SPI clock configuration. */
static const uint32_t gs_ul_clock_configurations[] =
		{ 500000, 1000000, 2000000, 5000000 };

/* Pointer to UART PDC register base */
Pdc *g_p_spim_pdc, *g_p_spis_pdc;

/**
 * \brief Display the user menu on the terminal.
 */
static void display_menu(void)
{
	uint32_t i;

	puts("\n\rMenu :\n\r"
			"------\r");

	for (i = 0; i < NUM_SPCK_CONFIGURATIONS; i++) {
		printf("  %u: Set SPCK = %7lu Hz\n\r", (unsigned)i,
			(unsigned long)gs_ul_clock_configurations[i]);
	}
	puts("  t: Perform SPI master\n\r"
			"  h: Display this menu again\n\r\r");
}

/**
 * \brief Set SPI slave transfer.
 *
 * \param p_buf Pointer to buffer to transfer.
 * \param size Size of the buffer. 
 */
static void spi_slave_transfer(void *p_tbuf, uint32_t tsize, void *p_rbuf,
		uint32_t rsize)
{
	uint32_t spi_ier;
	pdc_packet_t pdc_spi_packet;

	pdc_spi_packet.ul_addr = (uint32_t)p_rbuf;
	pdc_spi_packet.ul_size = rsize;
	pdc_rx_init(g_p_spis_pdc, &pdc_spi_packet, NULL);

	pdc_spi_packet.ul_addr = (uint32_t)p_tbuf;
	pdc_spi_packet.ul_size = tsize;
	pdc_tx_init(g_p_spis_pdc, &pdc_spi_packet, NULL);
	
	/* Enable the RX and TX PDC transfer requests */
	pdc_enable_transfer(g_p_spis_pdc, PERIPH_PTCR_RXTEN | PERIPH_PTCR_TXTEN);

	/* Transfer done handler is in ISR */
	spi_ier = SPI_IER_NSSR | SPI_IER_RXBUFF;
	spi_enable_interrupt(SPI_SLAVE_BASE, spi_ier) ;
}

/**
 * \brief Interrupt handler for the SPI slave.
 */
void SPI_Handler(void)
{
	uint32_t status;
	
	status = spi_read_status(SPI_SLAVE_BASE) ;

	if(status & SPI_SR_NSSR) {
		if ( status & SPI_SR_RXBUFF ) {
			spi_slave_transfer(gs_uc_spi_s_tbuffer, COMM_BUFFER_SIZE,
					gs_uc_spi_s_rbuffer, COMM_BUFFER_SIZE);
		}
	}
}

/**
 * \brief Initialize SPI as slave.
 */
static void spi_slave_initialize(void)
{
	uint32_t i;

	/* Get pointer to SPI slave PDC register base */
	g_p_spis_pdc = spi_get_pdc_base(SPI_MASTER_BASE);
	
	puts("-I- Initialize SPI as slave \r");

	for (i = 0; i < COMM_BUFFER_SIZE; i++) {
		gs_uc_spi_s_tbuffer[i] = i;
	}
#if (SAMG55)
	/* Enable the peripheral and set SPI mode. */
	flexcom_enable(BOARD_FLEXCOM_SPI);
	flexcom_set_opmode(BOARD_FLEXCOM_SPI, FLEXCOM_SPI);
#else
	/* Configure an SPI peripheral. */
	pmc_enable_periph_clk(SPI_ID);
#endif
	spi_disable(SPI_SLAVE_BASE);
	spi_reset(SPI_SLAVE_BASE);
	spi_set_slave_mode(SPI_SLAVE_BASE);
	spi_disable_mode_fault_detect(SPI_SLAVE_BASE);
	spi_set_peripheral_chip_select_value(SPI_SLAVE_BASE, SPI_CHIP_SEL);
	spi_set_clock_polarity(SPI_SLAVE_BASE, SPI_CHIP_SEL, SPI_CLK_POLARITY);
	spi_set_clock_phase(SPI_SLAVE_BASE, SPI_CHIP_SEL, SPI_CLK_PHASE);
	spi_set_bits_per_transfer(SPI_SLAVE_BASE, SPI_CHIP_SEL,
			SPI_CSR_BITS_8_BIT);
	spi_enable(SPI_SLAVE_BASE);
	
	pdc_disable_transfer(g_p_spis_pdc, PERIPH_PTCR_RXTDIS |
			PERIPH_PTCR_TXTDIS);
	spi_slave_transfer(gs_uc_spi_s_tbuffer, COMM_BUFFER_SIZE,
			gs_uc_spi_s_rbuffer, COMM_BUFFER_SIZE);
}

/**
 * \brief Initialize SPI as master.
 */
static void spi_master_initialize(void)
{
	uint32_t i;
	
	puts("-I- Initialize SPI as master\r");
	
	for (i = 0; i < COMM_BUFFER_SIZE; i++) {
		gs_uc_spi_m_tbuffer[i] = i;
	}
	
	/* Get pointer to SPI master PDC register base */
	g_p_spim_pdc = spi_get_pdc_base(SPI_MASTER_BASE);

#if (SAMG55)
	/* Enable the peripheral and set SPI mode. */
	flexcom_enable(BOARD_FLEXCOM_SPI);
	flexcom_set_opmode(BOARD_FLEXCOM_SPI, FLEXCOM_SPI);
#else
	/* Configure an SPI peripheral. */
	pmc_enable_periph_clk(SPI_ID);
#endif
	spi_disable(SPI_MASTER_BASE);
	spi_reset(SPI_MASTER_BASE);
	spi_set_lastxfer(SPI_MASTER_BASE);
	spi_set_master_mode(SPI_MASTER_BASE);
	spi_disable_mode_fault_detect(SPI_MASTER_BASE);
	spi_set_peripheral_chip_select_value(SPI_MASTER_BASE, SPI_CHIP_SEL);
	spi_set_clock_polarity(SPI_MASTER_BASE, SPI_CHIP_SEL, SPI_CLK_POLARITY);
	spi_set_clock_phase(SPI_MASTER_BASE, SPI_CHIP_SEL, SPI_CLK_PHASE);
	spi_set_bits_per_transfer(SPI_MASTER_BASE, SPI_CHIP_SEL,
			SPI_CSR_BITS_8_BIT);
	spi_set_baudrate_div(SPI_MASTER_BASE, SPI_CHIP_SEL,
			(sysclk_get_peripheral_hz() / gs_ul_spi_clock));
	spi_set_transfer_delay(SPI_MASTER_BASE, SPI_CHIP_SEL, SPI_DLYBS,
			SPI_DLYBCT);
	spi_enable(SPI_MASTER_BASE);
	
	pdc_disable_transfer(g_p_spim_pdc, PERIPH_PTCR_RXTDIS |
			PERIPH_PTCR_TXTDIS);
}

/**
 * \brief Set the specified SPI clock configuration.
 *
 * \param configuration  Index of the configuration to set.
 */
static void spi_set_clock_configuration(uint8_t configuration)
{
	gs_ul_spi_clock = gs_ul_clock_configurations[configuration];
	printf("Setting SPI clock #%lu ... \n\r", (unsigned long)gs_ul_spi_clock);
	spi_set_baudrate_div(SPI_MASTER_BASE, SPI_CHIP_SEL,
			(sysclk_get_peripheral_hz() / gs_ul_spi_clock));
}

/**
 * \brief Perform SPI master transfer.
 *
 * \param pbuf Pointer to buffer to transfer.
 * \param size Size of the buffer. 
 */
static void spi_master_transfer(void *p_tbuf, uint32_t tsize, void *p_rbuf,
		uint32_t rsize)
{
	pdc_packet_t pdc_spi_packet;

	pdc_spi_packet.ul_addr = (uint32_t)p_rbuf;
	pdc_spi_packet.ul_size = rsize;
	pdc_rx_init(g_p_spim_pdc, &pdc_spi_packet, NULL);

	pdc_spi_packet.ul_addr = (uint32_t)p_tbuf;
	pdc_spi_packet.ul_size = tsize;
	pdc_tx_init(g_p_spim_pdc, &pdc_spi_packet, NULL);
	
	/* Enable the RX and TX PDC transfer requests */
	pdc_enable_transfer(g_p_spim_pdc, PERIPH_PTCR_RXTEN | PERIPH_PTCR_TXTEN);

	/* Waiting transfer done*/
	while((spi_read_status(SPI_MASTER_BASE) & SPI_SR_RXBUFF) == 0);
	
	/* Disable the RX and TX PDC transfer requests */
	pdc_disable_transfer(g_p_spim_pdc, PERIPH_PTCR_RXTDIS |
			PERIPH_PTCR_TXTDIS);
}


/**
 * \brief Start SPI transfer test.
 */
static void spi_master_go(void)
{
	uint32_t i;
        /* Configure SPI as master, set up SPI clock. */
	spi_master_initialize();

	spi_master_transfer(gs_uc_spi_m_tbuffer, COMM_BUFFER_SIZE,
			gs_uc_spi_m_rbuffer, COMM_BUFFER_SIZE);
	for (i = 0; i < COMM_BUFFER_SIZE; i++) {
		if(gs_uc_spi_m_rbuffer[i] !=gs_uc_spi_m_tbuffer[i]) {
			break;
		}	
	}
	if(i == COMM_BUFFER_SIZE) {
		puts("SPI transfer test success! \r");
	} else {
		puts("SPI transfer test fail! \r");
	}
}

/**
 *  \brief Configure the Console UART.
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
 * \brief Application entry point for SPI PDC example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t uc_key;

	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	/* Initialize the console UART. */
	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);

	/* Configure SPI interrupts for slave only. */
	NVIC_DisableIRQ(SPI_IRQn);
	NVIC_ClearPendingIRQ(SPI_IRQn);
	NVIC_SetPriority(SPI_IRQn, 0);
	NVIC_EnableIRQ(SPI_IRQn);

	spi_slave_initialize();

	/* Display menu. */
	display_menu();

	while (1) {
		scanf("%c", (char *)&uc_key);

		switch (uc_key) {
		case 'h':
			display_menu();
			break;

		case 't':
			spi_master_go();
			break;

		default:
			/* Set configuration #n. */
			if ((uc_key >= '0')
					&& (uc_key <= ('0' + NUM_SPCK_CONFIGURATIONS - 1))) {
				spi_set_clock_configuration(uc_key - '0');
			}
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
