/**
 * \file
 *
 * \brief SAM D20 SPI Slave Bootloader
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
 * \mainpage SAM D20 SPI Slave Bootloader
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Features
 * \li Application for self programming
 * \li Uses SPI Slave interface
 * \li SPI Master sends the data to be programmed over SPI bus
 * \li Resets the device after programming and starts executing application
 */

/**
 * \page appdoc_main SAM D20 SPI Slave Bootloader
 *
 * Overview:
 * - \ref appdoc_samd20_spi_slave_bootloader_features
 * - \ref appdoc_samd20_spi_slave_bootloader_intro
 * - \ref appdoc_samd20_spi_slave_bootloader_mem_org
 * - \ref appdoc_samd20_spi_slave_bootloader_prereq
 * - \ref appdoc_samd20_spi_slave_bootloader_hw
 * - \ref appdoc_samd20_spi_slave_bootloader_process
 *    - \ref appdoc_samd20_spi_slave_bootloader_process_boot_check
 *    - \ref appdoc_samd20_spi_slave_bootloader_process_init
 *    - \ref appdoc_samd20_spi_slave_bootloader_boot_protocol
 *    - \ref appdoc_samd20_spi_slave_bootloader_start_app
 * - \ref appdoc_samd20_spi_slave_bootloader_compinfo
 * - \ref appdoc_samd20_spi_slave_bootloader_contactinfo
 *
 * \section appdoc_samd20_spi_slave_bootloader_features Features
 * \li Application for self programming
 * \li Uses SPI Slave interface
 * \li SPI Master sends the data to be programmed over SPI bus
 * \li Resets the device after programming and starts executing application
 *
 * \section appdoc_samd20_spi_slave_bootloader_intro Introduction
 * As many electronic designs evolve rapidly there is a growing need for being
 * able to update products, which have already been shipped or sold.
 * Microcontrollers that support bootloader which allows updating of the
 * flash without the need of an external programmer, are of
 * great use in situations where the application has to be updated on the field.
 * The boot loader may use various interfaces like SPI, UART, TWI, Ethernet etc.
 * This application implements a SPI Slave bootloader for SAM D20.
 *
 * \section appdoc_samd20_spi_slave_bootloader_mem_org Program Memory Organization
 * This bootloader implementation consumes around 8000 bytes (approximately),
 * which is 32 rows of Program Memory space starting from 0x00000000. BOOTPROT
 * fuses on the device can be set to protect first 32 rows of the program
 * memory which are allocated for the BOOT section. So, the end user application
 * should be generated with starting address as 0x00004000.
 *
 * \section appdoc_samd20_spi_slave_bootloader_prereq Prerequisites
 * There are no prerequisites for this implementation
 *
 * \section appdoc_samd20_spi_slave_bootloader_hw Hardware Setup
 * SAM D20 in SAM D20 Xplained Pro kit is used as the SPI Slave.
 * SPI master should be connected to PIN_PA16 (MOSI), PIN_PA17 (SS), PIN_PA18 (MISO)
 * and PIN_PA19 (SCK) on External header 1 (EXT1) of SAM D20 Xplained Pro.
 * SW0 will be configured as BOOT_LOAD_PIN and LED0 will be used to
 * display the bootloader status. LED0 will be ON when the device is in
 * bootloader mode.
 *
 * \section appdoc_samd20_spi_slave_bootloader_process Bootloader Process
 *
 * \subsection appdoc_samd20_spi_slave_bootloader_process_boot_check Boot Check
 * The bootloader is located at the start of the program memory and is
 * executed at each reset/power-on sequence. Initially check the
 * status of a user configurable BOOT_LOAD_PIN.
 * - If the pin is pulled low continue execution in bootloader mode.
 * - Else read the first location of application section (0x00004000) which
 *   contains the stack pointer address and check whether it is 0xFFFFFFFF.
 *    - If yes, application section is empty and wait indefinitely there.
 *    - If not, jump to the application section and start execution from there.
 * \note Configuring the BOOT_LOAD_PIN and disabling watchdog in this boot mode
 * check routine are made with direct peripheral register access to enable quick
 * decision on application or bootloader mode.
 *
 * \subsection appdoc_samd20_spi_slave_bootloader_process_init Initialization
 * Initialize the following
 *   - Board
 *   - System clock
 *   - SPI Slave module
 *   - NVM module
 *
 * \subsection appdoc_samd20_spi_slave_bootloader_boot_protocol Boot Protocol
 *   - SPI Master first sends 4 bytes of data which contains the length of
 *     the data to be programmed
 *   - Bootloader acknowledges length by sending byte 's'
 *   - Read a block from SPI Master of size NVMCTRL_PAGE_SIZE
 *   - Program the data to program memory starting at APP_START_ADDRESS
 *   - Send an acknowledgement byte 's' to SPI Master to indicate it has
 *     received the data and finished programming
 *   - Repeat until the entire length of data has been programmed to the device
 *
 * \subsection appdoc_samd20_spi_slave_bootloader_start_app Start Application
 * Once the programming is completed, the CMSIS command NVIC_SystemReset() is
 * called to restart the device. If SW0 is high, the previously programmed application
 * will now be run.
 *
 * \section appdoc_samd20_spi_slave_bootloader_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_samd20_spi_slave_bootloader_contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com">http://www.microchip.com</a>.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <conf_bootloader.h>

struct spi_module slave;

uint16_t dummy;

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

	/* Read 4 bytes of data from master */
	while (spi_read_buffer_wait(&slave, read_buffer, 4, dummy) != STATUS_OK);
	MSB0W(len) = read_buffer[0];
	MSB1W(len) = read_buffer[1];
	MSB2W(len) = read_buffer[2];
	MSB3W(len) = read_buffer[3];

	return len;
}

/**
 * \brief Function for fetching data to be programmed
 *
 * This function will read \ref len number of bytes from master for
 * programming the device.
 *
 * \param buffer pointer to the buffer to store data from SPI master
 * \param len    length of the data that will be sent by SPI master
 */
static void fetch_data(uint8_t *buffer, uint16_t len)
{
	/* Read \ref len number of bytes from master */
	while (spi_read_buffer_wait(&slave, buffer, len, dummy) != STATUS_OK);
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

		/* Check if there is data remaining to be programmed */
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
	if (WDT->CTRL.reg & WDT_CTRL_ALWAYSON) {
		/* Watchdog always enabled, unsafe to program */
		while (1);
	}

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

	/* Check the BOOT pin */
	if (boot_en) {
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
 * \brief Function for configuring SPI slave module
 *
 * This function will configure the SPI slave module with
 * the SERCOM module to be used and pinmux settings
 */
static void configure_spi(void)
{
	/* Create and initialize config structure */
	struct spi_config config_spi;
	spi_get_config_defaults(&config_spi);

	/* Change SPI settings to slave */
	config_spi.mode = SPI_MODE_SLAVE;
	config_spi.mux_setting = BOOT_SPI_MUX;
	config_spi.mode_specific.slave.preload_enable = true;
	config_spi.mode_specific.slave.frame_format = SPI_FRAME_FORMAT_SPI_FRAME;
	config_spi.pinmux_pad0 = BOOT_SPI_PAD0;
	config_spi.pinmux_pad1 = BOOT_SPI_PAD1;
	config_spi.pinmux_pad2 = BOOT_SPI_PAD2;
	config_spi.pinmux_pad3 = BOOT_SPI_PAD3;

	/* Initialize and enable device with config */
	spi_init(&slave, BOOT_SERCOM, &config_spi);

	spi_enable(&slave);
}

/**
 * \brief Function for sending acknowledgement to SPI Master
 *
 * This function will send an acknowledgement byte 's' to the master to
 * indicate the master that it has received and programmed the data.
 */
static void send_ack(void)
{
	uint8_t ack = 's';
	spi_write_buffer_wait(&slave, &ack, 1);
}

/**
 * \brief Main application
 */
int main(void)
{
	uint32_t len;
	uint32_t curr_prog_addr;
	uint32_t tmp_len;
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


	/* Configure the SPI slave module */
	configure_spi();

	/* Get NVM default configuration and load the same */
	nvm_get_config_defaults(&config);
	config.manual_page_write = false;
	nvm_set_config(&config);

	/* Turn on LED */
	port_pin_set_output_level(BOOT_LED, false);
	/* Get the length to be programmed */
	len = get_length();

	do {
		/* Get remaining or NVMCTRL_PAGE_SIZE as block length */
		tmp_len = min(NVMCTRL_PAGE_SIZE, len);

		/* Acknowledge last received data */
		send_ack();

		/* Read data from SPI master */
		fetch_data(buff, tmp_len);

		/* Program the data into Flash */
		program_memory(curr_prog_addr, buff, tmp_len);

		/* Increment the current programming address */
		curr_prog_addr += tmp_len;

		/* Update the length to remaining length to be programmed */
		len -= tmp_len;

		/* Do this for entire length */
	} while (len != 0);

	/* Acknowledge last block */
	send_ack();

	/* Reset module and boot into application */
	NVIC_SystemReset();

	while (1) {
		/* Inf loop */
	}

}
