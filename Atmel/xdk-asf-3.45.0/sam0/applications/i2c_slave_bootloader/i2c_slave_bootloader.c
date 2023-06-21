/**
 * \file
 *
 * \brief SAM I2C Slave Bootloader
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
 * \mainpage SAM I2C Slave Bootloader
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Features
 * \li Application for self programming
 * \li Uses I2C Slave interface
 * \li I2C Master sends the data to be programmed over I2C bus
 * \li Resets the device after programming and starts executing application
 */

/**
 * \page appdoc_main SAM I2C Slave Bootloader
 *
 * Overview:
 * - \ref appdoc_sam0_i2c_slave_bootloader_features
 * - \ref appdoc_sam0_i2c_slave_bootloader_intro
 * - \ref appdoc_sam0_i2c_slave_bootloader_mem_org
 * - \ref appdoc_sam0_i2c_slave_bootloader_prereq
 * - \ref appdoc_sam0_i2c_slave_bootloader_hw
 * - \ref appdoc_sam0_i2c_slave_bootloader_process
 *    - \ref appdoc_sam0_i2c_slave_bootloader_process_boot_check
 *    - \ref appdoc_sam0_i2c_slave_bootloader_process_init
 *    - \ref appdoc_sam0_i2c_slave_bootloader_boot_protocol
 *    - \ref appdoc_sam0_i2c_slave_bootloader_start_app
 * - \ref appdoc_sam0_i2c_slave_bootloader_compinfo
 * - \ref appdoc_sam0_i2c_slave_bootloader_contactinfo
 *
 * \section appdoc_sam0_i2c_slave_bootloader_features Features
 * \li Application for self programming
 * \li Uses I2C Slave interface
 * \li I2C Master sends the data to be programmed over I2C bus
 * \li Resets the device after programming and starts executing application
 *
 * \section appdoc_sam0_i2c_slave_bootloader_intro Introduction
 * As many electronic designs evolve rapidly there is a growing need for being
 * able to update products, which have already been shipped or sold.
 * Microcontrollers that support boot loader facilitates updating the
 * application flash section without the need of an external programmer, are of
 * great use in situations where the application has to be updated on the field.
 * The boot loader may use various interfaces like SPI, UART, TWI, Ethernet etc.
 *
 * This application implements a I2C Slave bootloader for SAM devices.
 *
 * This application has been tested on following boards:
 * - SAM D20/D21/R21/D11/L22/L21 Xplained Pro
 *
 * \section appdoc_sam0_i2c_slave_bootloader_mem_org Program Memory Organization
 * This bootloader implementation consumes around 8000 bytes (approximately),
 * which is 32 rows of Program Memory space starting from 0x00000000. BOOTPROT
 * fuses on the device can be set to protect first 32 rows of the program
 * memory which are allocated for the BOOT section. So, the end user application
 * should be generated with starting address as 0x00002000.
 *
 * \section appdoc_sam0_i2c_slave_bootloader_prereq Prerequisites
 * There are no prerequisites for this implementation
 *
 * \section appdoc_sam0_i2c_slave_bootloader_hw Hardware Setup
 * SAM device in SAM Xplained Pro kit is used as the I2C Slave.
 * I2C master should be connected to PIN11 (PA08 - SDA) and PIN12 (PA09 - SCL)
 * on External header 1 (EXT1) of SAM D20/D21 Xplained Pro.
 * I2C master should be connected to PIN11 (PA16 - SDA) and PIN12 (PA17 - SCL)
 * on External header 1 (EXT1) of SAM R21 Xplained Pro.
 * I2C master should be connected to PIN11 (PA22 - SDA) and PIN12 (PA23 - SCL)
 * on External header 1 (EXT1) of SAM D10/D11 Xplained Pro.
 * I2C master should be connected to PIN11 (PB30 - SDA) and PIN12 (PB31 - SCL)
 * on External header 1 (EXT1) of SAM L22 Xplained Pro.
 * I2C master should be connected to PIN11 (PA08 - SDA) and PIN12 (PA09 - SCL)
 * on External header 1 (EXT1) of SAM L21 Xplained Pro.
 * SW0 will be configured as BOOT_LOAD_PIN and LED0 will be used to
 * display the bootloader status. LED0 will be ON when the device is in
 * bootloader mode.
 *
 * \section appdoc_sam0_i2c_slave_bootloader_process Bootloader Process
 *
 * \subsection appdoc_sam0_i2c_slave_bootloader_process_boot_check Boot Check
 * The bootloader is located at the start of the program memory and is
 * executed at each reset/power-on sequence. Initially check the
 * status of a user configurable BOOT_LOAD_PIN.
 * - If the pin is pulled low continue execution in bootloader mode.
 * - Else read the first location of application section (0x00002000) which
 *   contains the stack pointer address and check whether it is 0xFFFFFFFF.
 *    - If yes, application section is empty and wait indefinitely there.
 *    - If not, jump to the application section and start execution from there.
 * \note Configuring the BOOT_LOAD_PIN and disabling watchdog in this boot mode
 * check routine are made with direct peripheral register access to enable quick
 * decision on application or bootloader mode.
 *
 * \subsection appdoc_sam0_i2c_slave_bootloader_process_init Initialization
 * Initialize the following
 *   - Board
 *   - System clock
 *   - I2C Slave module
 *   - NVM module
 *
 * \subsection appdoc_sam0_i2c_slave_bootloader_boot_protocol Boot Protocol
 *   - I2C Master first sends 4 bytes of data which contains the length of
 *     the data to be programmed
 *   - Read a block from I2C Master of size NVMCTRL_PAGE_SIZE
 *   - Program the data to Program memory starting APP_START_ADDRESS
 *   - Send an acknowledgement byte 's' to I2C Master to indicate it has
 *     received the data and finished programming
 *   - Repeat till entire length of data has been programmed to the device
 *
 * \subsection appdoc_sam0_i2c_slave_bootloader_start_app Start Application
 * Once the programming is completed, enable Watchdog Timer with a timeout
 * period of 256 clock cycles and wait in a loop for Watchdog to reset
 * the device.
 *
 * \section appdoc_sam0_i2c_slave_bootloader_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_i2c_slave_bootloader_contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com">http://www.microchip.com</a>.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include "conf_bootloader.h"

struct i2c_slave_module slave;

struct i2c_slave_packet packet;

/* Function prototypes */
static uint32_t get_length(void);
static void fetch_data(uint8_t *buffer, uint16_t len);
static void program_memory(uint32_t address, uint8_t *buffer, uint16_t len);
static void start_application(void);
static void check_boot_mode(void);
static void configure_i2c(void);
static void send_ack(void);

/**
 * \brief Function for fetching length of file to be programmed
 *
 * Master initially transmits 4 bytes - which is the length of the
 * the data to be programmed to the device.
 */
static uint32_t get_length(void)
{
	uint8_t read_buffer[4];
	uint32_t len = 0;

	packet.data_length = 4;
	packet.data = read_buffer;

	/* Read 4 bytes of data from master */
	while (i2c_slave_read_packet_wait(&slave, &packet) != STATUS_OK);
	MSB0W(len) = read_buffer[0];
	MSB1W(len) = read_buffer[1];
	MSB2W(len) = read_buffer[2];
	MSB3W(len) = read_buffer[3];

	return len;
}

/**
 * \brief Function for fetching data to be programmed
 *
 * This function will read a number of bytes from master for
 * programming the device.
 *
 * \param buffer pointer to the buffer to store data from I2C master
 * \param len    length of the data that will be sent by I2C master
 */
static void fetch_data(uint8_t *buffer, uint16_t len)
{
	packet.data_length = len;
	packet.data = buffer;

	/* Read \ref len number of bytes from master */
	while (i2c_slave_read_packet_wait(&slave, &packet) != STATUS_OK);
}

/**
 * \brief Function for programming data to Flash
 *
 * This function will check whether the data is greater than Flash page size.
 * If it is greater, it splits and writes pagewise.
 *
 * \param address address of the Flash page to be programmed
 * \param buffer  pointer to the buffer containing data to be programmed
 * \param len     length of the data to be programmed to Flash
 */
static void program_memory(uint32_t address, uint8_t *buffer, uint16_t len)
{
	/* Check if length is greater than Flash page size */
	if (len > NVMCTRL_PAGE_SIZE) {
		uint32_t offset = 0;

		while (len > NVMCTRL_PAGE_SIZE) {
			/* Check if it is first page of a row */
			if ((address & 0xFF) == 0) {
				/* Erase row */
				nvm_erase_row(address);
			}
			/* Write one page data to flash */
			nvm_write_buffer(address, buffer + offset, NVMCTRL_PAGE_SIZE);
			/* Increment the address to be programmed */
			address += NVMCTRL_PAGE_SIZE;
			/* Increment the offset of the buffer containing data */
			offset += NVMCTRL_PAGE_SIZE;
			/* Decrement the length */
			len -= NVMCTRL_PAGE_SIZE;
		}

		/* Check if there is data remaining to be programmed*/
		if (len > 0) {
			/* Write the data to flash */
			nvm_write_buffer(address, buffer + offset, len);
		}
	} else {
		/* Check if it is first page of a row) */
		if ((address & 0xFF) == 0) {
			/* Erase row */
			nvm_erase_row(address);
		}
		/* Write the data to flash */
		nvm_write_buffer(address, buffer, len);
	}
}

/**
 * \brief Function for starting application
 *
 * This function will configure the WDT module and enable it. The LED is
 * kept toggling till WDT reset occurs.
 */
static void start_application(void)
{
	struct wdt_conf wdt_config;

	/* Turn off LED */
	port_pin_set_output_level(BOOT_LED, true);

	/* Get WDT default configuration */
	wdt_get_config_defaults(&wdt_config);

	/* Set the required clock source and timeout period */
#if (SAMD) || (SAMR21)
	wdt_config.clock_source   = GCLK_GENERATOR_4;
#endif
	wdt_config.timeout_period = WDT_PERIOD_256CLK;

	/* Initialize and enable the Watchdog with the user settings */
	wdt_set_config(&wdt_config);

	/* Turn ON LED after watchdog has initialized */
	port_pin_set_output_level(BOOT_LED, false);

	while (1) {
		/* Wait for watchdog reset */
	}
}

/**
 * \brief Function for checking whether to enter boot mode or application mode
 *
 * This function will check the state of BOOT_LOAD_PIN. If it is pressed, it
 * continues execution in bootloader mode. Else, it reads the first location
 * from the application section and checks whether it is 0xFFFFFFFF. If yes,
 * then the application section is empty and it waits indefinitely there. If
 * not, it jumps to the application and starts execution from there.
 * Access to direct peripheral registers are made in this routine to enable
 * quick decision on application or bootloader mode.
 */
static void check_boot_mode(void)
{
	uint32_t app_check_address;
	uint32_t *app_check_address_ptr;

	/* Check if WDT is locked */
#if (SAMD) || (SAMR21)
	if (!(WDT->CTRL.reg & WDT_CTRL_ALWAYSON)) {
		/* Disable the Watchdog module */
		WDT->CTRL.reg &= ~WDT_CTRL_ENABLE;
	}
#else
	if (!(WDT->CTRLA.reg & WDT_CTRLA_ALWAYSON)) {
		/* Disable the Watchdog module */
		WDT->CTRLA.reg &= ~WDT_CTRLA_ENABLE;
	}
#endif

	volatile PortGroup *boot_port = (volatile PortGroup *)
			(&(PORT->Group[BOOT_LOAD_PIN / 32]));
	volatile bool boot_en;

	/* Enable the input mode in Boot GPIO Pin */
	boot_port->DIRCLR.reg = GPIO_BOOT_PIN_MASK;
	boot_port->PINCFG[BOOT_LOAD_PIN & 0x1F].reg =
			PORT_PINCFG_INEN | PORT_PINCFG_PULLEN;
	boot_port->OUTSET.reg = GPIO_BOOT_PIN_MASK;

	/* Read the BOOT_LOAD_PIN status */
	boot_en = (boot_port->IN.reg) & GPIO_BOOT_PIN_MASK;

	/* Check the BOOT pin or the reset cause is Watchdog */
#if (SAMD) || (SAMR21)
	if ((boot_en) || (PM->RCAUSE.reg & PM_RCAUSE_WDT)) {
#else
	if ((boot_en) || (RSTC->RCAUSE.reg & RSTC_RCAUSE_WDT)) {
#endif
		app_check_address = APP_START_ADDRESS;
		app_check_address_ptr = (uint32_t *) app_check_address;

		/*
		 * Read the first location of application section
		 * which contains the address of stack pointer.
		 * If it is 0xFFFFFFFF then the application section is empty.
		 */
		if (*app_check_address_ptr == 0xFFFFFFFF) {
			while (1) {
				/* Wait indefinitely */
			}
		}
		/* Pointer to the Application Section */
		void (*application_code_entry)(void);

		/* Rebase the Stack Pointer */
		__set_MSP(*(uint32_t *) APP_START_ADDRESS);

		/* Rebase the vector table base address */
		SCB->VTOR = ((uint32_t) APP_START_ADDRESS & SCB_VTOR_TBLOFF_Msk);

		/* Load the Reset Handler address of the application */
		application_code_entry = (void (*)(void))(unsigned *)(*(unsigned *)
				(APP_START_ADDRESS + 4));

		/* Jump to user Reset Handler in the application */
		application_code_entry();
	}
}

/**
 * \brief Function for configuring I2C slave module
 *
 * This function will configure the I2C slave module with
 * the SERCOM module to be used, required slave address, address mode mask
 * and pinmux settings
 */
static void configure_i2c(void)
{
	/* Create and initialize config structure */
	struct i2c_slave_config config_i2c;
	i2c_slave_get_config_defaults(&config_i2c);

	/* Change address and address_mode */
	config_i2c.address      = SLAVE_ADDRESS;
	config_i2c.address_mode = I2C_SLAVE_ADDRESS_MODE_MASK;
	config_i2c.pinmux_pad0  = BOOT_I2C_PAD0;
	config_i2c.pinmux_pad1  = BOOT_I2C_PAD1;

	/* Initialize and enable device with config */
	i2c_slave_init(&slave, BOOT_SERCOM, &config_i2c);

	i2c_slave_enable(&slave);
}

/**
 * \brief Function for sending acknowledgement to I2C Master
 *
 * This function will write an acknowledgement byte 's' on I2C bus to
 * indicate the master that it has received and programmed the data.
 */
static void send_ack(void)
{
	uint8_t ack = 's';
	packet.data_length = 1;
	packet.data = &ack;
	while (i2c_slave_write_packet_wait(&slave, &packet) != STATUS_OK);
}

/**
 * \brief Main application
 */
int main(void)
{
	static volatile uint32_t len = 0;
	uint32_t remaining_len = 0;
	uint32_t curr_prog_addr;
	uint8_t buff[NVMCTRL_PAGE_SIZE];
	struct nvm_config config;

	/* Check switch state to enter boot mode or application mode */
	check_boot_mode();

	/*
	 * Application to be programmed from APP_START_ADDRESS defined in
	 * conf_bootloader.h
	 */
	curr_prog_addr = APP_START_ADDRESS;

	/* Initialize system */
	system_init();

	/* Configure the I2C slave module */
	configure_i2c();

	/* Get NVM default configuration and load the same */
	nvm_get_config_defaults(&config);
	config.manual_page_write = false;
	nvm_set_config(&config);

	/* Turn on LED */
	port_pin_set_output_level(BOOT_LED, false);

	/* Get the length to be programmed */
	len = get_length();
	remaining_len = len;

	do {
		/* Read data of NVMCTRL_PAGE_SIZE from I2C master */
		fetch_data(buff, min(NVMCTRL_PAGE_SIZE, len));

		/* Program the read data into Flash */
		program_memory(curr_prog_addr, buff, min(NVMCTRL_PAGE_SIZE, len));

		/* Increment the current programming address */
		curr_prog_addr += min(NVMCTRL_PAGE_SIZE, len);

		/* Calculate the remaining length */
		remaining_len -= min(NVMCTRL_PAGE_SIZE, len);

		/* Update the length to remaining length to be programmed */
		len = remaining_len;

		send_ack();

		/* Do this for entire length */
	} while (len != 0);

	start_application();

	while (1) {
		/* Inf loop */
	}

}
