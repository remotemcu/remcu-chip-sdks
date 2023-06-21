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
#include "main.h"

#if FIRMWARE_AES_ENABLED
#include "aesa.h"
#endif

/* Small delay to ensure that the MSC device is ready */
#define MSC_DELAY_SOF_COUNT     100  // 100ms

/*****************************************************************************/
/*                              GLOBAL VARIABLES                             */
/*****************************************************************************/

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

/* CRC descriptor - Should be 512 byte aligned */
COMPILER_ALIGNED(512)
static crccu_dscr_type_t crc_dscr;

/* File Data Buffer */
COMPILER_WORD_ALIGNED
volatile uint8_t buffer[FLASH_BUFFER_SIZE];

#if FIRMWARE_AES_ENABLED
/* AES instance */
struct aes_dev_inst g_aes_inst;

/* AES configuration */
struct aes_config   g_aes_cfg;

/* AES Output Buffer */
COMPILER_WORD_ALIGNED
volatile uint32_t aes_output[FLASH_BUFFER_SIZE/4];
#endif


/*****************************************************************************/
/*                             FUNCTION DECLARATIONS                         */
/*****************************************************************************/

static void firmware_gen_system_init(void);

static bool generate_firmware(void);

static void generate_crc(void);


#if FIRMWARE_AES_ENABLED

static void init_aes(void);

static void aes_encrypt(uint32_t *input_data, uint32_t size);

#endif

#if CONSOLE_OUTPUT_ENABLED

static void console_init(void);

#endif

/*****************************************************************************/
/*                             FUNCTION DEFINITIONS                          */
/*****************************************************************************/
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

#if FIRMWARE_AES_ENABLED
	/* Initialize the AES Module */
	init_aes();

	/* Encrypt the CRC32 and Signature bytes */
	aes_encrypt((uint32_t *)buffer, buffer_size/4);

	/* Update the output buffer */
	buf = (void *) aes_output;
#else
	/* Update the output buffer */
	buf = (void *) buffer;
#endif

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

#if FIRMWARE_AES_ENABLED
		/* Encrypt the binary data */
		aes_encrypt((uint32_t *)buffer, buffer_size/4);
		/* Update the output buffer */
		buf = (void *)aes_output;
#else
		/* Update the output buffer */
		buf = (void *)buffer;
#endif

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

	/* Enable CRCCU peripheral clock */
	sysclk_enable_peripheral_clock(CRCCU);

	/* Reset the CRCCU */
	crccu_reset(CRCCU);

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

		/* Set the memory address for CRCCU DMA transfer */
		crc_dscr.ul_tr_addr = (uint32_t) buffer;

		/* Transfer width: byte, interrupt disable */
		crc_dscr.ul_tr_ctrl = CRCCU_TR_CTRL_TRWIDTH_BYTE | buffer_size
								| CRCCU_TR_CTRL_IEN_DISABLE;

		/* Configure the CRCCU descriptor */
		crccu_configure_descriptor(CRCCU, (uint32_t) &crc_dscr);

		/* Configure CRCCU mode */
		crccu_configure_mode(CRCCU, CRCCU_MR_ENABLE | APP_CRC_POLYNOMIAL_TYPE);

		/* Start the CRC calculation */
		crccu_enable_dma(CRCCU);

		/* Wait for calculation ready */
		while ((crccu_get_dma_status(CRCCU) == CRCCU_DMA_SR_DMASR)) {
		}
	}

	/* Store the CRC32 Value */
	firmware_crc = crccu_read_crc_value(CRCCU);

	/* Enable CRCCU peripheral clock */
	sysclk_disable_peripheral_clock(CRCCU);

	/* Close the input file */
	f_close(&file_object1);
}


#if FIRMWARE_AES_ENABLED
/**
 * \brief AES Initialization routine
 */
static void init_aes()
{
	uint32_t aes_key[FIRMWARE_AES_KEY_SIZE >> 5] = {
		 FIRMWARE_AES_KEY_WORD0
		,FIRMWARE_AES_KEY_WORD1
		,FIRMWARE_AES_KEY_WORD2
		,FIRMWARE_AES_KEY_WORD3
#if FIRMWARE_AES_KEY_SIZE > 128
		,FIRMWARE_AES_KEY_WORD4
		,FIRMWARE_AES_KEY_WORD5
#endif
#if FIRMWARE_AES_KEY_SIZE > 192
		,FIRMWARE_AES_KEY_WORD6
		,FIRMWARE_AES_KEY_WORD7
#endif
	};

	uint32_t aes_initvect[4] = {
		FIRMWARE_AES_INITVECT_WORD0,
		FIRMWARE_AES_INITVECT_WORD1,
		FIRMWARE_AES_INITVECT_WORD2,
		FIRMWARE_AES_INITVECT_WORD3
	};

	/* Enable the AES module. */
	aes_get_config_defaults(&g_aes_cfg);
	aes_init(&g_aes_inst, AESA, &g_aes_cfg);

	/* Enable the AES Module */
	aes_enable(&g_aes_inst);

	/* Configure the AES. */
	g_aes_inst.aes_cfg->encrypt_mode = AES_ENCRYPTION;
	g_aes_inst.aes_cfg->key_size = AES_KEY_SIZE_128;
	g_aes_inst.aes_cfg->dma_mode = AES_MANUAL_MODE;
	g_aes_inst.aes_cfg->opmode = AES_CBC_MODE;
	g_aes_inst.aes_cfg->cfb_size = AES_CFB_SIZE_128;
	g_aes_inst.aes_cfg->countermeasure_mask = AES_COUNTERMEASURE_TYPE_ALL;
	aes_set_config(&g_aes_inst);

	/* Beginning of a new message. */
	aes_set_new_message(&g_aes_inst);

	/* Set the cryptographic key. */
	aes_write_key(&g_aes_inst, aes_key);

	/* Set the initialization vector. */
	aes_write_initvector(&g_aes_inst, aes_initvect);
}


/**
 * \brief AES Decryption routine
 */
static void aes_encrypt(uint32_t *decrypted_data, uint32_t size)
{
	uint16_t i;
	for (i = 0; i < size ; i+=4) {
		/* Write the data to be ciphered to the input data registers. */
		aes_write_input_data(&g_aes_inst, (decrypted_data[i]));
		aes_write_input_data(&g_aes_inst, (decrypted_data[i+1]));
		aes_write_input_data(&g_aes_inst, (decrypted_data[i+2]));
		aes_write_input_data(&g_aes_inst, (decrypted_data[i+3]));

		/* Wait until the output data is ready */
		while(!(aes_read_status(&g_aes_inst) & AESA_SR_ODATARDY));

		/* Read the decrypted output data */
		aes_output[i]     = aes_read_output_data(&g_aes_inst);
		aes_output[i + 1] = aes_read_output_data(&g_aes_inst);
		aes_output[i + 2] = aes_read_output_data(&g_aes_inst);
		aes_output[i + 3] = aes_read_output_data(&g_aes_inst);
	}
}

#endif

#if CONSOLE_OUTPUT_ENABLED
/**
 * \brief Initializes the console output
 */
static void console_init(void)
{
	const sam_usart_opt_t usart_serial_options = {
		.baudrate     = CONSOLE_UART_BAUDRATE,
		.parity_type  = CONSOLE_UART_PARITY,
		.char_length  = CONSOLE_UART_CHAR_LENGTH,
		.stop_bits    = CONSOLE_UART_STOPBITS,
		.channel_mode = US_MR_CHMODE_NORMAL
	};
	/* Enable the clock for the console UART */
	sysclk_enable_peripheral_clock(CONSOLE_UART);
	/* Initialize the UART Module for console output */
	usart_init_rs232(CONSOLE_UART, &usart_serial_options,
						sysclk_get_peripheral_bus_hz(CONSOLE_UART));
	/* Enable the transmitter. */
	usart_enable_tx(CONSOLE_UART);
}
#endif


/**
 * \brief Initializes the device for the bootloader
 */
static void firmware_gen_system_init()
{
	/* Initialize the system clocks */
	sysclk_init();

	/* Initialize the board components */
	board_init();

	/* Initialize the sleep manager */
	sleepmgr_init();

#if CONSOLE_OUTPUT_ENABLED
	/* Initialize the console */
	console_init();
	/* Print a header */
	CONSOLE_PUTS(APP_HEADER);
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
#if FIRMWARE_AES_ENABLED
	uint32_t temp;
	uint8_t i;
#endif

	/* Device initialization for the bootloader */
	firmware_gen_system_init();

#if CONSOLE_OUTPUT_ENABLED
		/* Print a header */
		CONSOLE_PUTS("\n\rInsert device");
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
		CONSOLE_PUTS("\n\rDevice Connected");
#endif
		/* Go through the different LUN and check for the file. */
		for (lun = 0; (lun < uhi_msc_mem_get_lun()) && (lun < 8); lun++) {

			TCHAR root_directory[3] = "0:";
			root_directory[0] = '0' + lun;

			/* Initialize the file system object */
			memset(&fs, 0, sizeof(FATFS));

#if CONSOLE_OUTPUT_ENABLED
			/* Print the current task */
			CONSOLE_PUTS("\n\rMounting the device...");
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
				CONSOLE_PUTS(TASK_FAILED);
#endif
				/* Check the next LUN */
				continue;
			}

#if CONSOLE_OUTPUT_ENABLED
			/* Print the current task */
			CONSOLE_PUTS("\n\rSearch firmware...");
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
				CONSOLE_PUTS(TASK_FAILED);
#endif
				/* LUN error */
				f_close(&file_object1);
				continue;
			}

			/* Close the File after operation. */
			f_close(&file_object1);
            
#if FIRMWARE_AES_ENABLED
			/* Check for required padding for AES operation - 16byte aligned*/
			temp = (file_size + APP_BINARY_OFFSET) % 16;
			if (temp){
				/* Open the input file */
				f_open(&file_object1, (char const *)input_file_name,
					FA_OPEN_EXISTING | FA_WRITE);

				/* Required padding size */
				temp = 16 - temp;

				for (i = 0; i < temp; i++) {
					/* Fill with 0xFF */
					buffer[i] = 0xFF;
				}

				/* Seek to the end of the file */
				f_lseek(&file_object1, file_size);

				/* Store the buffer into the output file */
				f_write(&file_object1, (void const *)buffer, temp, &temp);

				/* Flush the data into the file */
				f_sync(&file_object1);

				/* Close the output file */
				f_close(&file_object1);
			}
#endif

#if CONSOLE_OUTPUT_ENABLED
			/* Print the current task */
			CONSOLE_PUTS(TASK_PASSED);
			CONSOLE_PUTS("\n\rCRC32 Generation...");
#endif
			/* Generate the CRC32 for the firmware file */
			generate_crc();

#if CONSOLE_OUTPUT_ENABLED
			/* Print the current task */
			CONSOLE_PUTS(TASK_PASSED);
			CONSOLE_PUTS("\n\rGenerating output firmware...");
#endif
			/* Generate the final firmware */
			if (generate_firmware()) {
#if CONSOLE_OUTPUT_ENABLED
				/* Print the current task */
				CONSOLE_PUTS(TASK_PASSED);
				CONSOLE_PUTS("\n\rPlease remove the device.");
#endif
			} else {
#if CONSOLE_OUTPUT_ENABLED
				/* Print task output */
				CONSOLE_PUTS(TASK_FAILED);
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
 * \mainpage ASF SAM4L Firmware Generator for USB Host Mass Storage Bootloader
 *
 * \section intro Introduction
 * SAM4L Firmware generator application is to provide a easy way to generate
 * AES encrypted firmware with CRC32 and signature bytes. The firmware is fully
 * compatible for the SAM4L USB Host MSC Bootloader.
 * - Do complete chip erase.
 * - Program the firmware generator application
 * - Load the application firmware into U-disk. Connect it to the SAM4L-EK USB
 *   MSC Host.
 * - Application generates & appends CRC32 with signature bytes and encrypts
 *   the whole binary.
 *
 * \section config Bootloader Configuration
 * Bootloader Configurations are managed in conf_bootloader.h
 *   - FIRMWARE_AES_ENABLED       -> Enable/disable the AES Decryption
 *   - CONSOLE_OUTPUT_ENABLED     -> Enable/disable the Console message output
 *   - APP_START_OFFSET           -> Application starting offset from Flash
 *   - FIRMWARE_IN_FILE_NAME      -> Input Application Firmware
 *   - FIRMWARE_OUT_FILE_NAME     -> Encrypted/Unencrypted Application Firmware
 *                                   for bootloader
 *   - APP_SIGNATURE              -> Signature bytes to be verified
 * 
 * \section board Board Configuration
 * Board Configurations are managed in conf_board.h
 * - SAM4L-EK configuration
 *   - Has an IO configured for VBUS Detect. VBUS Pin jumper PA06/USB
 *     should be set
 *   - CONF_BOARD_USB_PORT           -> Enable USB pins
 *   - CONF_BOARD_USB_VBUS_CONTROL   -> VBUS control enabled, jumper PC08/USB
 *                                      should be set
 *   - CONF_BOARD_USB_VBUS_ERR_DETECT-> VBUS error control enabled, jumper
 *                                      PC07/USB should be set
 *   - An external power supply should be used since the VBUS is powered only
 *     through the external power supply controlled by the VBUS Control(VBOF)
 *     pin. Refer the SAM4L-EK schematics for more details.
 *   - Console message output is sent through the Embedded Debugger(onboard)'s 
 *     COM PORT.
 * - SAM4L Xplained Pro configuration
 *   - Has an IO configured for VBUS Detect.
 *   - CONF_BOARD_USB_PORT           -> Enable USB pins
 *   - CONF_BOARD_USB_VBUS_CONTROL   -> VBUS control enabled
 *   - An external power supply should be used if the EDBG USB port is not able
 *     to provide enough power to the USB MSC device.
 *   - Console message output is sent through the Embedded Debugger(onboard)'s 
 *     COM PORT.
 * 
 * \section func Application Output Format
 * The application binary structure is modified by the firmware generator. The
 * final application binary structure would be as below
 * - AES Enabled:
 *   - 4 bytes   -> Encrypted CRC32
 *   - 12 bytes  -> Encrypted Signature Data
 *   - Rest data -> Encrypted Input Firmware
 * - AES Disabled:
 *   - 4 bytes   -> CRC32
 *   - 12 bytes  -> Signature Data
 *   - Rest data -> Input Firmware
 * - A sample application binary output (AES encrypted) is provided for testing
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
 *    - conf_clock.h
 *    - conf_fatfs.h
 *    - conf_access.h
 *    - conf_aesa.h
 *    - conf_ast.h
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
