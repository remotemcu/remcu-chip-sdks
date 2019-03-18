/**
 * \file
 *
 * \brief Application to generate firmware for USB Host Mass Storage Bootloader
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
static FIL file_object1, file_object2;

/* root directory */
static TCHAR root_directory[20] = {'0', ':', 0};

/* Input file name */
static char input_file_name[] = {
	FIRMWARE_IN_FILE_NAME
};

/* Output file name */
static char output_file_name[] = {
	FIRMWARE_OUT_FILE_NAME
};

/* CRC32 Value of the firmware */
static uint32_t firmware_crc = 0;

/* File Data Buffer */
COMPILER_WORD_ALIGNED
volatile uint8_t buffer[FLASH_BUFFER_SIZE];

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
 * \brief Function to generate the final firmware
 */
static bool generate_firmware(void)
{
	uint32_t address_offset = 0;
	void *buf = NULL;
	uint32_t buffer_size = 0;
	uint8_t signature_bytes[] = APP_SIGNATURE;
	uint8_t *temp = (uint8_t *) buffer;
	FRESULT res;

	/* Store the CRC32 value */
	*(uint32_t *)temp = firmware_crc;
	address_offset = 4;

	/* Store the signature bytes */
	while (address_offset < APP_BINARY_OFFSET) {
		temp[address_offset] = signature_bytes[address_offset - 4];
		address_offset++;
	}
	buffer_size = APP_CRC_SIZE + APP_SIGNATURE_SIZE;
	address_offset = 0;

	/* Update the output buffer */
	buf = (void *) buffer;

	/* Open the output file for writing the data */
	res = f_open(&file_object2,
			(char const *)output_file_name,
			FA_WRITE | FA_CREATE_ALWAYS);
	/* Check the return status */
	if (res != FR_OK) {
		/* LUN error */
		f_close(&file_object2);
		return false;
	}

	/* Write the CRC32 and Signature bytes into the output firmware */
	f_write(&file_object2, buf, buffer_size, &buffer_size);

	/* Flush the data into the file */
	f_sync(&file_object2);

	/* Close the input file */
	f_close(&file_object2);

	while (true) {
		/* Open the input file */
		f_open(&file_object1,
				(char const *)input_file_name,
				FA_OPEN_EXISTING | FA_READ);

		/* Seek the file pointer to the current address offset */
		f_lseek(&file_object1, address_offset);

		/* Read the data from the firmware */
		f_read(&file_object1, (uint8_t *)buffer, FLASH_BUFFER_SIZE,
				&buffer_size);

		/* Check if there is any buffer */
		if (!buffer_size) {
			/* Close the open file */
			f_close(&file_object1);
			/* Break out of the loop */
			break;
		}
		/* Close the input file */
		f_close(&file_object1);

		/* Update the output buffer */
		buf = (void *)buffer;

		/* Open the output file for writing */
		f_open(&file_object2,
		(char const *)output_file_name,
		FA_OPEN_EXISTING | FA_WRITE);

		/* Seek the file pointer to the current address offset */
		f_lseek(&file_object2, address_offset + APP_BINARY_OFFSET);

		/* Store the buffer into the output file */
		f_write(&file_object2, buf, buffer_size, &buffer_size);

		/* Flush the data into the file */
		f_sync(&file_object2);

		/* Close the output file */
		f_close(&file_object2);

		/* Update the address offset */
		address_offset += buffer_size;
	}

	return true;
}


/**
 * \brief Generate the CRC value for the firmware
 */
static void generate_crc(void)
{
	uint32_t buffer_size = 0;
	struct dma_crc_config crc_config;

	/* Start the DMA CRC with I/O mode */
	dma_crc_get_config_defaults(&crc_config);
	crc_config.type = APP_CRC_POLYNOMIAL_TYPE;
	crc_config.size = CRC_BEAT_SIZE_WORD;
	dma_crc_io_enable(&crc_config);

	/* Open the input file for CRC32 generation */
	f_open(&file_object1,
			(char const *)input_file_name,
			FA_OPEN_EXISTING | FA_READ);

	/* Generate the CRC32 for the input binary */
	while (true) {
		/* Read the data from the firmware */
		f_read(&file_object1, (uint8_t *)buffer, FLASH_BUFFER_SIZE,
				&buffer_size);

		/* Check if there is any buffer */
		if (!buffer_size) {
			break;
		}

		dma_crc_io_calculation((void *)(buffer), buffer_size / 4);
	}

	/* Store the CRC Value */
	firmware_crc = dma_crc_get_checksum();

	/* stop the DMA CRC with I/O mode */
	dma_crc_disable();

	/* Close the input file */
	f_close(&file_object1);
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
static void firmware_gen_system_init(void)
{
	/* Initialize the system */
	system_init();

	/* Initialize the sleep manager */
	sleepmgr_init();

#if CONSOLE_OUTPUT_ENABLED
	/* Initialize the console */
	console_init();
	/* Wait stdio stable */
	delay_ms(5);
	/* Print a header */
	printf(APP_HEADER);
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

	/* Device initialization for the bootloader */
	firmware_gen_system_init();

#if CONSOLE_OUTPUT_ENABLED
	/* Print a header */
	printf("Insert device\r\n");
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
		printf("Device Connected\r\n");
#endif
		/* Go through the different LUN and check for the file. */
		for (lun = 0; ((lun < uhi_msc_mem_get_lun()) && (lun < 8)); lun++) {

			root_directory[0] = '0' + lun;

			/* Initialize the file system object */
			memset(&fs, 0, sizeof(FATFS));

#if CONSOLE_OUTPUT_ENABLED
			/* Print the current task */
			printf("Mounting the device...\r\n");
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
				printf(TASK_FAILED);
#endif
				/* Check the next LUN */
				continue;
			}

#if CONSOLE_OUTPUT_ENABLED
			/* Print the current task */
			printf("Search firmware...\r\n");
#endif

			/* Firmware files on the disk */
			input_file_name[0] = lun + '0';
			output_file_name[0] = lun + '0';

			/* Open the input file */
			res = f_open(&file_object1,
				(char const *)input_file_name,
				FA_OPEN_EXISTING | FA_READ);

			/* Get the file length */
			file_size = file_object1.fsize;

			/* Check if file size is greater than the possible flash size */
			/* Open the firmware upgrade file in READ mode from the disk */
			if (!(file_size && (file_size < APP_MAX_SIZE)
			&& (res == FR_OK))) {
#if CONSOLE_OUTPUT_ENABLED
				/* Print task output */
				printf(TASK_FAILED);
#endif
				/* LUN error */
				f_close(&file_object1);
				continue;
			}

			/* Close the File after operation. */
			f_close(&file_object1);
            
#if CONSOLE_OUTPUT_ENABLED
			/* Print the current task */
			printf(TASK_PASSED);
			printf("CRC32 Generation...\r\n");
#endif
			/* Generate the CRC32 for the firmware file */
			generate_crc();

#if CONSOLE_OUTPUT_ENABLED
			/* Print the current task */
			printf(TASK_PASSED);
			printf("Generating output firmware...\r\n");
#endif
			/* Generate the final firmware */
			if (generate_firmware()) {
#if CONSOLE_OUTPUT_ENABLED
				/* Print the current task */
				printf(TASK_PASSED);
				printf("Please remove the device.\r\n");
#endif
			} else {
#if CONSOLE_OUTPUT_ENABLED
				/* Print task output */
				printf(TASK_FAILED);
#endif
				continue;
			}

			/* Unmount the MSC device */
			f_mount(lun, NULL);

			/* Stop the USB Host */
			uhc_stop(true);

			/* Disable global interrupts. */
			cpu_irq_disable();
		}
		/* None of the connected LUN has the upgrade file. */
		lun_connected = false;
	}
}

//! \brief Notify that a SOF has been sent (each 1 ms)
void main_usb_sof_event(void)
{
	sof_count++;
}

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
 * \mainpage ASF SAM D21 Firmware Generator for USB Host Mass Storage Bootloader
 *
 * \section intro Introduction
 * SAM D21 Firmware generator application is to provide a easy way to generate
 * firmware with CRC32 and signature bytes. The firmware is fully
 * compatible for the SAM D21 USB Host MSC Bootloader.
 * - Do complete chip erase.
 * - Program the firmware generator application
 * - Load the application firmware into U-disk. Connect it to the SAM D21 USB
 *   MSC Host.
 * - Application generates & appends CRC32 with signature bytes to
 *   the whole binary.
 *
 * \section config Bootloader Configuration
 * Bootloader Configurations are managed in conf_bootloader.h
 *   - CONSOLE_OUTPUT_ENABLED     -> Enable/disable the Console message output
 *   - APP_START_OFFSET           -> Application starting offset from Flash
 *   - FIRMWARE_IN_FILE_NAME      -> Input Application Firmware
 *   - FIRMWARE_OUT_FILE_NAME     -> Output Application Firmware for bootloader
 *   - APP_SIGNATURE              -> Signature bytes to be verified
 * 
 * \section func Application Output Format
 * The application binary structure is modified by the firmware generator. The
 * final application binary structure would be as below
 *   - 4 bytes   -> CRC
 *   - 12 bytes  -> Signature Data
 *   - Rest data -> Input Firmware
 * - A sample application binary output is provided for testing
 *   with the firmware generator.
 *
 * \copydoc UI
 *
 * \section  dependencies Dependencies
 * The application uses the following module groups:
 * - Application Implementation:
 *    - main.c
 *    - main.h
 * - Configuration Files
 *    - conf_bootloader.h
 *    - conf_board.h
 *    - conf_clocks.h
 *    - conf_fatfs.h
 *    - conf_access.h
 *    - conf_dma.h
 *    - conf_extint.h
 *    - conf_uart_serial.h
 *    - conf_usb_host.h
 *    - conf_sleepmgr.h
 * - Basic modules:
 *   <br>Startup, board, clock, interrupt, power management
 * - USB host stack and MSC modules:
 *   <br>services/usb/
 *   <br>services/usb/uhc/
 *   <br>services/usb/class/msc/host/
 * - FATFS File System:
 *   <br>thirdparty/fatfs
 */
