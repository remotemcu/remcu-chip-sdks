/**
 * \file
 *
 * \brief TWI EEPROM PDC Example for SAM.
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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
 * \mainpage TWI EEPROM Example
 *
 * \section intro Introduction
 *
 * The application demonstrates how to use the SAM TWI PDC driver to access an
 * external serial EEPROM chip.
 *
 * \section Requirements
 *
 * This package can be used with the following setup:
 *  - SAMG53 Xplained Pro kit
 *  - SAM3X evaluation kit
 *
 * \section files Main files:
 *  - twi.c SAM Two-Wire Interface driver implementation.
 *  - twi.h SAM Two-Wire Interface driver definitions.
 *  - twi_eeprom_example.c Example application.
 *
 * \section example description Description of the Example
 * Upon startup, the program configures PIOs for console UART, LEDs and TWI
 * connected to EEPROM on board. Then it configures the TWI driver and data
 * package. The clock of I2C bus is set as 100kHz.
 * After initializing the master mode, the example sends test pattern to the
 * EEPROM. When sending is complete, TWI driver reads the memory and saves the
 * content in the reception buffer. Then the program compares the content
 * received with the test pattern sent before and prints the comparison result.
 * The corresponding LED is turned on.
 *
 * On SAM Xplained Pro, the EEPROM is simulated though the twi_slave_example,
 * which means 2 SAM Xplained Pro boards are required to run this example.
 * One board executes this example as the twi master and another runs
 * twi_salve_example as the simulated EEPROM.
 * The TWI PINs and GND PIN should be connected between these 2 boards.
 * More information of the simulated EEPROM implementation can be referred in
 * the description of twi_slave_example.
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
#include "led.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/** EEPROM Wait Time */
#define WAIT_TIME   10
/** TWI Bus Clock 100kHz */
#define TWI_CLK     100000
/** Address of AT24C chips */
#define AT24C_ADDRESS           0x40
#define EEPROM_MEM_ADDR         0
#define EEPROM_MEM_ADDR_LENGTH  2

/** Data to be sent */
#define TEST_DATA_LENGTH  (sizeof(test_data_tx)/sizeof(uint8_t))

#define STRING_EOL    "\r"
#define STRING_HEADER "--TWI EEPROM Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

#if SAM4N
/** TWI ID for simulated EEPROM application to use */
#define BOARD_ID_TWI_EEPROM    ID_TWI0
/** TWI Base for simulated TWI EEPROM application to use */
#define BOARD_BASE_TWI_EEPROM  TWI0
/** The address for simulated TWI EEPROM application */
#undef  AT24C_ADDRESS
#define AT24C_ADDRESS          0x40
#endif

#if SAMG53
/** TWI ID for simulated EEPROM application to use */
#define BOARD_ID_TWI_EEPROM         ID_TWI2
/** TWI Base for simulated TWI EEPROM application to use */
#define BOARD_BASE_TWI_EEPROM       TWI2
/** The address for simulated TWI EEPROM application */
#undef  AT24C_ADDRESS
#define AT24C_ADDRESS        0x40
#endif

#if SAMG55
/** TWI ID for simulated EEPROM application to use */
#define BOARD_ID_TWI_EEPROM         ID_TWI4
/** TWI Base for simulated TWI EEPROM application to use */
#define BOARD_BASE_TWI_EEPROM       TWI4
/** The address for simulated TWI EEPROM application */
#undef  AT24C_ADDRESS
#define AT24C_ADDRESS        0x40
#endif

static const volatile uint8_t test_data_tx[] = {
	/** SAM TWI EEPROM EXAMPLE */
	'S', 'A', 'M', ' ', 'T', 'W', 'I', ' ',
	'E', 'E', 'P', 'R', 'O', 'M', ' ',
	'E', 'X', 'A', 'M', 'P', 'L', 'E'
};

/* Pointer to TWI PDC register base */
Pdc *g_p_twim_pdc;

/** Reception buffer */
static uint8_t gs_uc_test_data_rx[TEST_DATA_LENGTH] = { 0 };

/** Global timestamp in milliseconds since start of application */
volatile uint32_t g_ul_ms_ticks = 0;

/** Define TX and RX packet */
twi_packet_t packet_tx, packet_rx;

/** Define interrupt flag */
volatile uint32_t Write_Interrupt_Flag = 0;
volatile uint32_t Read_Interrupt_Flag = 0;

/**
 *  \brief Handler for System Tick interrupt.
 *
 *  Process System Tick Event
 *  increments the timestamp counter.
 */
void SysTick_Handler(void)
{
	g_ul_ms_ticks++;
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
 *  \brief Wait for the given number of milliseconds (using the dwTimeStamp
 *         generated by the SAM microcontrollers' system tick).
 *  \param ul_dly_ticks  Delay to wait for, in milliseconds.
 */
static void mdelay(uint32_t ul_dly_ticks)
{
	uint32_t ul_cur_ticks;

	ul_cur_ticks = g_ul_ms_ticks;
	while ((g_ul_ms_ticks - ul_cur_ticks) < ul_dly_ticks);
}

/**
 * \brief Read status register.
 *
 * \param p_twi Pointer to an TWI instance.
 *
 * \return TWI status register value.
 */
static inline uint32_t twi_read_status(Twi *p_twi)
{
	return p_twi->TWI_SR;
}

/**
 * \brief Write multiple bytes to a TWI compatible slave device.
 *
 * \param p_twi Pointer to a TWI instance.
 * \param p_packet Packet information and data (see \ref twi_packet_t).
 */
static void twi_master_pdc_write(Twi *p_twi, twi_packet_t *p_packet)
{
	pdc_packet_t pdc_twi_packet;
    uint8_t *buffer = p_packet->buffer;

	pdc_disable_transfer(g_p_twim_pdc, PERIPH_PTCR_TXTDIS | PERIPH_PTCR_RXTDIS);
	
	pdc_twi_packet.ul_addr = (uint32_t)buffer;
#if SAMG53
	pdc_twi_packet.ul_size = (p_packet->length - 1);
#else
    pdc_twi_packet.ul_size = (p_packet->length);
#endif
	pdc_tx_init(g_p_twim_pdc, &pdc_twi_packet, NULL);

	/* Set write mode, slave address and 3 internal address byte lengths */
	p_twi->TWI_MMR = 0;
	p_twi->TWI_MMR = TWI_MMR_DADR(p_packet->chip) |
	((p_packet->addr_length << TWI_MMR_IADRSZ_Pos) &
	TWI_MMR_IADRSZ_Msk);

	/* Set internal address for remote chip */
	p_twi->TWI_IADR = 0;
	p_twi->TWI_IADR = twi_mk_addr(p_packet->addr, p_packet->addr_length);
	
	Write_Interrupt_Flag = 1;
	
	twi_enable_interrupt(BOARD_BASE_TWI_EEPROM, TWI_SR_TXCOMP);
		
	/* Enable the TX PDC transfer requests */
	pdc_enable_transfer(g_p_twim_pdc, PERIPH_PTCR_TXTEN);

	/* Waiting transfer done*/
	while((twi_read_status(BOARD_BASE_TWI_EEPROM) & TWI_SR_ENDTX) == 0);

	/* Disable the RX and TX PDC transfer requests */
	pdc_disable_transfer(g_p_twim_pdc, PERIPH_PTCR_TXTDIS | PERIPH_PTCR_RXTDIS);

	while((twi_read_status(BOARD_BASE_TWI_EEPROM) & TWI_SR_TXRDY) == 0);

	p_twi->TWI_CR = TWI_CR_STOP;
#if SAMG53	
	p_twi->TWI_THR = *(buffer + p_packet->length - 1);
#endif
	while (!(p_twi->TWI_SR & TWI_SR_TXCOMP)) {
	}
}

/**
 * \brief Read multiple bytes from a TWI compatible slave device.
 *
 * \param p_twi Pointer to a TWI instance.
 * \param p_packet Packet information and data (see \ref twi_packet_t).
 */
static void twi_master_pdc_read(Twi *p_twi, twi_packet_t *p_packet)
{
	pdc_packet_t pdc_twi_packet;
	uint8_t *buffer = p_packet->buffer;
	
	pdc_disable_transfer(g_p_twim_pdc, PERIPH_PTCR_TXTDIS | PERIPH_PTCR_RXTDIS);
	
	pdc_twi_packet.ul_addr = (uint32_t)buffer;
#if SAMG53
	pdc_twi_packet.ul_size = (p_packet->length - 2);
#else
    pdc_twi_packet.ul_size = (p_packet->length);
#endif
	pdc_rx_init(g_p_twim_pdc, &pdc_twi_packet, NULL);

	/* Set write mode, slave address and 2 internal address byte lengths */
	p_twi->TWI_MMR = 0;
	p_twi->TWI_MMR = TWI_MMR_MREAD | TWI_MMR_DADR(p_packet->chip) |
	((p_packet->addr_length << TWI_MMR_IADRSZ_Pos) &
	TWI_MMR_IADRSZ_Msk);

	/* Set internal address for remote chip */
	p_twi->TWI_IADR = 0;
	p_twi->TWI_IADR = twi_mk_addr(p_packet->addr, p_packet->addr_length);

    Read_Interrupt_Flag = 1;

	twi_enable_interrupt(BOARD_BASE_TWI_EEPROM, TWI_SR_TXCOMP);
	
	/* Enable the RX PDC transfer requests */
	pdc_enable_transfer(g_p_twim_pdc, PERIPH_PTCR_RXTEN);
	
	p_twi->TWI_CR = TWI_CR_START;
	
	/* Waiting transfer done*/
	while((twi_read_status(BOARD_BASE_TWI_EEPROM) & TWI_SR_ENDRX) == 0);
	
	/* Disable the RX PDC transfer requests */
	pdc_disable_transfer(g_p_twim_pdc, PERIPH_PTCR_RXTDIS);

	while((twi_read_status(BOARD_BASE_TWI_EEPROM) & TWI_SR_RXRDY) == 0);
	
	p_twi->TWI_CR = TWI_CR_STOP;
#if SAMG53	
	*(buffer + p_packet->length - 2) = p_twi->TWI_RHR;
	
	while((twi_read_status(BOARD_BASE_TWI_EEPROM) & TWI_SR_RXRDY) == 0);

	*(buffer + p_packet->length - 1) = p_twi->TWI_RHR;
#endif
	while (!(p_twi->TWI_SR & TWI_SR_TXCOMP)) {
	}
}

void BOARD_TWI_Handler(void)
{
	uint32_t status;
	
	status = twi_get_interrupt_mask(BOARD_BASE_TWI_EEPROM);
	
	if(((status & TWI_IMR_TXCOMP) == TWI_IMR_TXCOMP)
	    && (Write_Interrupt_Flag == 1)) {
		printf("PDC Write transfer:\tOK!\n\r");
		Write_Interrupt_Flag = 0;
		twi_disable_interrupt(BOARD_BASE_TWI_EEPROM, TWI_SR_TXCOMP);	
	} else if(((status & TWI_IMR_TXCOMP) == TWI_IMR_TXCOMP)
		&&(Read_Interrupt_Flag == 1)) {			
	    printf("PDC Read transfer:\tOK!\n\r");
		Read_Interrupt_Flag = 0;
		twi_disable_interrupt(BOARD_BASE_TWI_EEPROM, TWI_IMR_TXCOMP);
	}
}

/**
 * \brief Application entry point for TWI EEPROM example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint32_t i;
	twi_options_t opt;

	/* Initialize the SAM system */
	sysclk_init();

	/* Initialize the board */
	board_init();

	/* Turn off LEDs */
#if SAM3XA
	LED_Off(LED0_GPIO);
	LED_Off(LED1_GPIO);
#else
	LED_Off(LED0);
#endif
	/* Initialize the console UART */
	configure_console();

	/* Output example information */
	puts(STRING_HEADER);

	/* Configure systick for 1 ms */
	puts("Configure system tick to get 1ms tick period.\r");
	if (SysTick_Config(sysclk_get_cpu_hz() / 1000)) {
		puts("-E- Systick configuration error\r");
		while (1) {
			/* Capture error */
		}
	}

#if SAMG55
	/* Enable the peripheral and set TWI mode. */
	flexcom_enable(BOARD_FLEXCOM_TWI);
	flexcom_set_opmode(BOARD_FLEXCOM_TWI, FLEXCOM_TWI);
#else
	/* Enable the peripheral clock for TWI */
	pmc_enable_periph_clk(BOARD_ID_TWI_EEPROM);
#endif

	/* Configure the options of TWI driver */
	opt.master_clk = sysclk_get_peripheral_hz();
	opt.speed      = TWI_CLK;

	/* Configure the data packet to be transmitted */
	packet_tx.chip        = AT24C_ADDRESS;
	packet_tx.addr[0]     = EEPROM_MEM_ADDR >> 8;
	packet_tx.addr[1]     = EEPROM_MEM_ADDR;
	packet_tx.addr_length = EEPROM_MEM_ADDR_LENGTH;
	packet_tx.buffer      = (uint8_t *) test_data_tx;
	packet_tx.length      = TEST_DATA_LENGTH;

	/* Configure the data packet to be received */
	packet_rx.chip        = packet_tx.chip;
	packet_rx.addr[0]     = packet_tx.addr[0];
	packet_rx.addr[1]     = packet_tx.addr[1];
	packet_rx.addr_length = packet_tx.addr_length;
	packet_rx.buffer      = gs_uc_test_data_rx;
	packet_rx.length      = packet_tx.length;

	if (twi_master_init(BOARD_BASE_TWI_EEPROM, &opt) != TWI_SUCCESS) {
		puts("-E-\tTWI master initialization failed.\r");
#if SAM3XA
		LED_On(LED0_GPIO);
		LED_On(LED1_GPIO);
#endif
		while (1) {
			/* Capture error */
		}
	}

    /* Configure TWI interrupts */
	NVIC_DisableIRQ(BOARD_TWI_IRQn);
	NVIC_ClearPendingIRQ(BOARD_TWI_IRQn);
	NVIC_SetPriority(BOARD_TWI_IRQn, 0);
	NVIC_EnableIRQ(BOARD_TWI_IRQn);
	
	/* Get pointer to TWI master PDC register base */	
	g_p_twim_pdc = twi_get_pdc_base(BOARD_BASE_TWI_EEPROM);
	
#if SAMG55	
	twi_enable_alternative_command(BOARD_BASE_TWI_EEPROM);
#endif	
	twi_master_pdc_write(BOARD_BASE_TWI_EEPROM, &packet_tx);

	/* Wait at least 10 ms */
	mdelay(WAIT_TIME);

	twi_master_pdc_read(BOARD_BASE_TWI_EEPROM, &packet_rx);

	/* Compare the sent and the received */
	for (i = 0; i < (TEST_DATA_LENGTH); i++) {
		if (test_data_tx[i] != gs_uc_test_data_rx[i]) {
			/* No match */
			puts("Data comparison:\tUnmatched!\r");
#if SAM3XA
			LED_On(LED0_GPIO);
#endif
			while (1) {
				/* Capture error */
			}
		}
	}
	/* Match */
	puts("Data comparison:\tMatched!\r");
#if SAM3XA
	LED_On(LED1_GPIO);
#else
	LED_On(LED0);
#endif
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
