/**
 * \file
 *
 * \brief SAM0 USB Host Mass Storage Bootloader Application with CRC Check.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <string.h>
#include "conf_usb_host.h"
#include "conf_bootloader.h"
#if CONSOLE_OUTPUT_ENABLED
#include "conf_uart_serial.h"
#endif
#include "main.h"

/* Small delay to ensure that the MSC device is ready */
#define MSC_DELAY_SOF_COUNT     1000  // 1000ms

/* SOF Event Counter */
static volatile uint32_t sof_count = 0;

/* Flag to track connected LUNs */
static volatile bool lun_connected = false;

/* File System Management object */
static FATFS fs; // Re-use fs for LUNs to reduce memory footprint

/* Directory management */
static DIR file_dir;

/* File object management */
static FIL file_object;

/* root directory */
static TCHAR root_directory[20] = {'0', ':', 0};

/* Input file name */
char input_file_name[] = {
	FIRMWARE_IN_FILE_NAME
};

/* File Data Buffer */
COMPILER_WORD_ALIGNED
volatile uint8_t buffer[FLASH_BUFFER_SIZE];

#if FIRMWARE_CRC_CHECK
/* CRC Value of the firmware */
static uint32_t firmware_crc = 0;
#endif

#if CONSOLE_OUTPUT_ENABLED
//! Console Strings
#define APP_HEADER                   \
					"ATMEL SAM D21 Firmware Generator for USB MSC BOOTLOADER\r\n"
#define TASK_PASSED                  "PASS\r\n"
#define TASK_FAILED                  "FAIL\r\n"

struct usart_module usart_instance;

static void console_init(void);
#endif

/**
 * \brief Function to start the application.
 */
static void start_application(void)
{
	/* Pointer to the Application Section */
	void (*application_code_entry)(void);

	/* Rebase the Stack Pointer */
	__set_MSP(*(uint32_t *)APP_START_ADDRESS);

	/* Rebase the vector table base address */
	SCB->VTOR = ((uint32_t)APP_START_ADDRESS & SCB_VTOR_TBLOFF_Msk);

	/* Load the Reset Handler address of the application */
	application_code_entry = (void (*)(void))(unsigned *)(*(unsigned *)
			(APP_START_ADDRESS + 4));

	/* Jump to user Reset Handler in the application */
	application_code_entry();
}

/**
 * \brief Function to issue a WDT reset to start the application.
 * This will reset the clock & peripheral configurations.
 */
static void start_application_with_wdt(void)
{
	/* Enable the Watchdog module */
	WDT->CTRL.reg = WDT_CTRL_ENABLE;

	while (1) {
		/* Wait indefinitely for a WDT reset */
	}
}

#if FIRMWARE_CRC_CHECK
/**
 * \brief Function to check the integrity of the firmware in usb disk.
 */
static bool integrity_check_in_disk(void)
{
	uint8_t *buf = NULL;
	uint32_t firmware_crc_output = 0;
	uint32_t buffer_size = 0;
	uint8_t *signature_bytes = APP_SIGNATURE;
	struct dma_crc_config crc_config;

	/* Open the input file */
	f_open(&file_object,
			(char const *)input_file_name,
			FA_OPEN_EXISTING | FA_READ);

	/* Routine to check the signature for decryption
	 * Firmware - First 4 bytes - CRC, 12 bytes - Firmware Signature/Password
	 * Remaining bytes - Application binary file
	 */

	/* Read the CRC data & Signature from the firmware */
	f_read(&file_object, (void *)buffer, APP_BINARY_OFFSET, &buffer_size);
	/* Check if there is any buffer */
	if (!buffer_size) {
		/* Close the File after operation. */
		f_close(&file_object);
		return false;
	}

	/* Update the buffer */
	buf = (uint8_t *) buffer;

	/* Store the firmware CRC */
	firmware_crc = *(uint32_t *)buf;
	/* Update the buffer size */
	buffer_size -= 4;
	buf += 4;
	/* Validate the Signature bytes */
	while (buffer_size--) {
		if (*buf++ != *signature_bytes++) {
			/* Signature verification failed */
			/* Close the File after operation. */
			f_close(&file_object);
			return false;
		}
	}

	/*
	 * File pointer didnt get updated at this point to the binary offset value.
	 * Calling F_SEEK again.
	 */
	f_lseek(&file_object, APP_BINARY_OFFSET);

	/* Start the DMA CRC with I/O mode */
	dma_crc_get_config_defaults(&crc_config);
	crc_config.type = APP_CRC_POLYNOMIAL_TYPE;
	dma_crc_io_enable(&crc_config);

	/* Verify the CRC of the entire file before programming */
	while (true) {
		/* Read the data from the firmware */
		f_read(&file_object, (void *)buffer, FLASH_BUFFER_SIZE, &buffer_size);
		/* Check if there is any buffer */
		if (!buffer_size) {
			break;
		}

		/* Calculate the CRC for the buffer */
		dma_crc_io_calculation((void *)(buffer), buffer_size);
	}

	/* Store the CRC Value */
	firmware_crc_output = dma_crc_get_checksum();

	/* stop the DMA CRC with I/O mode */
	dma_crc_disable();

	if (APP_CRC_POLYNOMIAL_TYPE == CRC_TYPE_16) {
		/* 16-bit CRC */
		firmware_crc_output &= 0xFFFF;
		firmware_crc &= 0xFFFF;
	}

	/* Compare the calculated CRC Value */
	if (firmware_crc != firmware_crc_output) {
		/* Close the File after operation. */
		f_close(&file_object);
		/* Return false on compare match fail */
		return false;
	}

	/* Close the File after operation. */
	f_close(&file_object);

	/* Return true on compare match pass */
	return true;
}
#endif

#if FIRMWARE_CRC_CHECK
/**
 * \brief Function to check the integrity of the firmware in internal flash.
 */
static bool integrity_check_in_flash(void)
{
	uint32_t firmware_crc_output = 0;
	struct dma_crc_config crc_config;
	uint32_t curr_address = 0;
	uint32_t current_page = 0;
	uint32_t file_size = 0;
	uint32_t read_size = 0;
	uint8_t page_buffer[NVMCTRL_PAGE_SIZE];

	current_page = APP_START_ADDRESS / NVMCTRL_PAGE_SIZE;
	curr_address = 0;
	file_size = file_object.fsize - APP_BINARY_OFFSET;

	/* Start the DMA CRC with I/O mode */
	dma_crc_get_config_defaults(&crc_config);
	crc_config.type = APP_CRC_POLYNOMIAL_TYPE;
	dma_crc_io_enable(&crc_config);

	/* Verify the CRC of the entire file after programming */
	while (curr_address < file_size) {
		if ((curr_address + FLASH_BUFFER_SIZE) < file_size) {
			read_size = FLASH_BUFFER_SIZE;
		} else {
			read_size = file_size - curr_address;
		}

		/* Read the data from the firmware */
		nvm_read_buffer(current_page * NVMCTRL_PAGE_SIZE,
					page_buffer, FLASH_BUFFER_SIZE);

		curr_address +=  read_size;
		current_page++;

		/* Calculate the CRC for the buffer */
		dma_crc_io_calculation((void *)(page_buffer), read_size);
	};

	/* Store the CRC Value */
	firmware_crc_output = dma_crc_get_checksum();

	/* stop the DMA CRC with I/O mode */
	dma_crc_disable();

	if (APP_CRC_POLYNOMIAL_TYPE == CRC_TYPE_16) {
		/* 16-bit CRC */
		firmware_crc_output &= 0xFFFF;
		firmware_crc &= 0xFFFF;
	}

	/* Compare the calculated CRC Value */
	if (firmware_crc != firmware_crc_output) {
		/* Return false on compare match fail */
		return false;
	}

	/* Return true on compare match pass */
	return true;
}
#endif

/* 
 * This function check if the applicatino or bootloade should be run
 */
static void check_boot_mode(void)
{
	uint32_t app_check_address;
	uint32_t *app_check_address_ptr;

	/* Check if WDT is locked */
	if (!(WDT->CTRL.reg & WDT_CTRL_ALWAYSON)) {
		/* Disable the Watchdog module */
		WDT->CTRL.reg &= ~WDT_CTRL_ENABLE;
	}

	app_check_address = APP_START_ADDRESS;
	app_check_address_ptr = (uint32_t *)app_check_address;

	board_init();

	if (port_pin_get_input_level(BUTTON_0_PIN) == BUTTON_0_ACTIVE) {
		/* Button is pressed, run bootloader */
		return;
	}

	if (*app_check_address_ptr == 0xFFFFFFFF) {
		/* No valid application; run bootloader */
		return;
	}

	/* Enters application mode*/
	start_application();
}

/**
 * \brief Function to program the Flash. Decrypt the firmware and program it.
 */
static bool program_memory(void)
{
	uint32_t buffer_size = 0;
	uint32_t file_size = 0;
	uint32_t curr_address = 0;
	uint32_t current_page = 0;
	uint16_t rows_clear, i;
	enum status_code error_code;
	uint8_t page_buffer[NVMCTRL_PAGE_SIZE];

	/* Open the input file */
	f_open(&file_object,
			(char const *)input_file_name,
			FA_OPEN_EXISTING | FA_READ);

	file_size = file_object.fsize - APP_BINARY_OFFSET;

#if FIRMWARE_CRC_CHECK
	/* Read the CRC data & Signature from the firmware */
	f_read(&file_object, (void *)buffer, APP_BINARY_OFFSET, &buffer_size);

	/* Check if there is any buffer */
	if (!buffer_size) {
		return false;
	}
#endif

	/* Set the busy LED */
	port_pin_set_output_level(LED0_PIN, LED0_ACTIVE);

	current_page = APP_START_ADDRESS / NVMCTRL_PAGE_SIZE;
	curr_address = 0;
	
	/* Erase flash rows to fit new firmware */
	rows_clear = ((file_size / NVMCTRL_ROW_SIZE) + 1);
	for (i = 0; i < rows_clear; i++) {
		do {
			error_code =
			nvm_erase_row(
			(APP_START_ADDRESS) +
			(NVMCTRL_ROW_SIZE * i));
		} while (error_code == STATUS_BUSY);
	}

	/* Program the flash memory page by page */
	do {
		/* Open the input file */
		f_read(&file_object, (void *)page_buffer, FLASH_BUFFER_SIZE, &buffer_size);
		/* Check if there is any buffer */
		if (!buffer_size) {
			break;
		}

		curr_address +=  buffer_size;

		/* Disable the global interrupts */
		cpu_irq_disable();

		/* Program the Flash Memory. */
		/* Write page buffer to flash */
		do {
			error_code = nvm_write_buffer(current_page * NVMCTRL_PAGE_SIZE,
				page_buffer, buffer_size);
		} while (error_code == STATUS_BUSY);

		/* Enable the global interrupts */
		cpu_irq_enable();

		current_page++;
	} while (curr_address < file_size);

	/* Close the File after operation. */
	f_close(&file_object);

#if FIRMWARE_CRC_CHECK
	/* Compare the calculated CRC Value */
	if (!integrity_check_in_flash()) {
		/* Verification Failed */
		return false;
	}
#endif

	/* Clear the busy LED */
	port_pin_set_output_level(LED0_PIN, LED0_INACTIVE);

	/* return true */
	return true;
}

#if CONSOLE_OUTPUT_ENABLED
/**
 * \brief Initializes the console output
 */
static void console_init(void)
{
	struct usart_config usart_conf;
	static struct usart_module cdc_uart_module;

	usart_get_config_defaults(&usart_conf);
	usart_conf.mux_setting = CONF_STDIO_MUX_SETTING;
	usart_conf.pinmux_pad0 = CONF_STDIO_PINMUX_PAD0;
	usart_conf.pinmux_pad1 = CONF_STDIO_PINMUX_PAD1;
	usart_conf.pinmux_pad2 = CONF_STDIO_PINMUX_PAD2;
	usart_conf.pinmux_pad3 = CONF_STDIO_PINMUX_PAD3;
	usart_conf.baudrate    = CONF_STDIO_BAUDRATE;

	stdio_serial_init(&cdc_uart_module, CONF_STDIO_USART_MODULE, &usart_conf);
	usart_enable(&cdc_uart_module);
}
#endif


/**
 * \brief Initializes the device for the bootloader
 */
static void bootloader_system_init(void)
{
	struct nvm_config nvm_cfg;
	struct port_config pin;

	/* Initialize the system */
	system_init();

	/*Configures PORT for LED0*/
	port_get_config_defaults(&pin);
	pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(LED0_PIN, &pin);

	/* Initialize the NVM */
	nvm_get_config_defaults(&nvm_cfg);
	nvm_cfg.manual_page_write = false;
	nvm_set_config(&nvm_cfg);

	/* Initialize the sleep manager */
	sleepmgr_init();

#if CONSOLE_OUTPUT_ENABLED
	/* Initialize the console */
	console_init();
	/* Wait stdio stable */
	delay_ms(5);
	/* Print a header */
	puts(APP_HEADER);
#endif

	/* Enable the global interrupts */
	cpu_irq_enable();

	/* Start USB host stack */
	uhc_start();
}


/**
 * \brief Main function. Execution starts here.
 */
int main(void)
{
	uint32_t file_size = 0;
	uint8_t lun;
	FRESULT res;

	/* Check whether the bootloader mode is activated */
	check_boot_mode();

	/* Device initialization for the bootloader */
	bootloader_system_init();

#if CONSOLE_OUTPUT_ENABLED
	/* Print a header */
	puts("Insert device\r\n");
#endif
	/* The USB management is entirely managed by interrupts. */
	while (true) {
		/* Check if a MSC device and its LUN are configured. */
		if (!lun_connected) {
			continue;
		}
		/* Adding a small delay to ensure that the MSC device is ready */
		while (sof_count < MSC_DELAY_SOF_COUNT);

#if CONSOLE_OUTPUT_ENABLED
		/* Print a header */
		puts("Device Connected\r\n");
#endif
		/* Go through the different LUN and check for the file. */
		for (lun = 0; (lun < uhi_msc_mem_get_lun()) && (lun < 8); lun++) {

			root_directory[0] = '0' + lun;

			/* Initialize the file system object */
			memset(&fs, 0, sizeof(FATFS));

#if CONSOLE_OUTPUT_ENABLED
			/* Print the current task */
			puts("Mounting the device...\r\n");
#endif
			/* 
			 * Set and mount the currently selected LUN as a drive
			 * in Navigator
			 */
			res = f_mount(lun, &fs);
			/* Check the return status */
			if (res != FR_OK) {
				continue;
			}

			/* Open the root directory */
			res = f_opendir(&file_dir, root_directory);
			/* Check the return status */
			if (res != FR_OK) {
#if CONSOLE_OUTPUT_ENABLED
				/* Print task output */
				puts(TASK_FAILED);
#endif
				/* Check the next LUN */
				continue;
			}

#if CONSOLE_OUTPUT_ENABLED
			/* Print the current task */
			puts("Search firmware...\r\n");
#endif
			/* Firmware files on the disk */
			input_file_name[0] = lun + '0';
			/* Open the input file */
			res = f_open(&file_object,
				(char const *)input_file_name,
				FA_OPEN_EXISTING | FA_READ);
			/* Get the file length */
			file_size = file_object.fsize;
			/* Check if file size is greater than the possible flash size */
			/* Open the firmware upgrade file in READ mode from the disk */
			if (!(file_size && (file_size < APP_MAX_SIZE)
					&& (res == FR_OK))) {
#if CONSOLE_OUTPUT_ENABLED
				/* Print task output */
				puts(TASK_FAILED);
#endif
				/* LUN error */
				f_close(&file_object);
				continue;
			}

			/* Close the File after operation. */
			f_close(&file_object);

#if CONSOLE_OUTPUT_ENABLED
			/* Print the current task */
			puts(TASK_PASSED);
			puts("Integrity check...\r\n");
#endif

#if FIRMWARE_CRC_CHECK
			/* Validate the firmware file */
			if (!integrity_check_in_disk()) {
#if CONSOLE_OUTPUT_ENABLED
				/* Print a header */
				puts(TASK_FAILED);
#endif
				continue;
			}
#endif

#if CONSOLE_OUTPUT_ENABLED
			/* Print the current task */
			puts(TASK_PASSED);
#  if FIRMWARE_CRC_CHECK
			puts("Programming & verifying...\r\n");
#  else
			puts("Programming...\r\n");
#  endif
#endif

			/* Program the memory */
			if (!program_memory()) {
#if CONSOLE_OUTPUT_ENABLED
				/* Print task output */
				puts(TASK_FAILED);
#endif
				continue;
			}

			/* Unmount the MSC device */
			f_mount(lun, NULL);

			/* Stop the USB Host */
			uhc_stop(true);

			/* Disable global interrupts. */
			cpu_irq_disable();

#if CONSOLE_OUTPUT_ENABLED
			/* Print the current task */
			puts(TASK_PASSED);
			puts("Starting application...\r\n");
#endif

			/* Start the application with a WDT Reset */
			start_application_with_wdt();
		}
		/* None of the connected LUN has the upgrade file. */
		lun_connected = false;
	}
}

/**
 * \brief Notify that a SOF has been sent (each 1 ms)
 */
void main_usb_sof_event(void)
{
	sof_count++;
}

/**
 * \brief Callback on enumeration status change of a MSC device
 */
void main_usb_connection_event(uhc_device_t * dev, bool b_present)
{
	/* To remove compiler warning */
	UNUSED(dev);

	/* Enumeration status of the connected MSC device */
	lun_connected = b_present;

	/* Reset sof_count to start MSC delay*/
	sof_count = 0;
}



/**
 * \mainpage ASF USB host mass storage
 *
 * \section intro Introduction
 * This application demonstrates a very simple bootloader application for the
 * SAM D21. It use the USB Host capability to read data from a connected
 * USB mass storage device.
 *
 * \section startup Startup
 * After loading firmware, connect a FAT formatted mass storage device to the
 * SAM D21 Xplained Pro with a firmware file called firmware.bin.
 *
 * If the device is blank (never been bootloaded), the bootloader will always
 * start.
 * If the device have been programmed already you need to press the SW0 button
 * on the SAM D21 Xplained Pro after reset to enter the bootloader.
 * When running, the bootloader will search for a file called firmware.bin .
 * If this file is found it will be programmed to the device and the new
 * firmware will be started.
 *
 * \copydoc UI
 *
 * \section example About example
 *
 * The example uses the following module groups:
 * - Basic modules:
 *   Startup, board, clock, interrupt, power management
 * - USB host stack and MSC modules:
 *   <br>services/usb/
 *   <br>services/usb/uhc/
 *   <br>services/usb/class/msc/host/
 * - Thirdparty modules:
 *   <br>thirdparty/fatfs

 */

