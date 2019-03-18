/**
 * \file
 *
 * \brief SAM4L USB Host Mass Storage Bootloader Application with CRC Check and 
 * AES decryption support.
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

#define GPIO_BOOT_PIN_PORT      ((volatile GpioPort *)(GPIO_ADDR +         \
									(BOOT_LOAD_PIN >> 5) * sizeof(GpioPort)))
#define GPIO_BOOT_PIN_MASK      (1U << (BOOT_LOAD_PIN & 0x1F))

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
static FIL file_object;

/* Input file name */
char input_file_name[] = {
	FIRMWARE_IN_FILE_NAME
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
static void bootloader_mode_check(void);

static void start_application(void);

static void start_application_with_wdt(void);

static bool program_memory(void);

static bool integrity_check(void);

static void crc32_calculate(uint32_t address, uint32_t size);

static void bootloader_system_init(void);

#if FIRMWARE_AES_ENABLED

static void init_aes(void);

static void aes_decrypt(uint32_t *encrypted_data, uint32_t size);

#endif

#if CONSOLE_OUTPUT_ENABLED

static void console_init(void);

#endif

/*****************************************************************************/
/*                             FUNCTION DEFINITIONS                          */
/*****************************************************************************/

/**
 * \brief Function to start the application.
 */
static void start_application(void)
{
	uint32_t app_start_address;

	/* Rebase the Stack Pointer */
	__set_MSP(*(uint32_t *) APP_START_ADDRESS);

	/* Rebase the vector table base address */
	SCB->VTOR = ((uint32_t) APP_START_ADDRESS & SCB_VTOR_TBLOFF_Msk);

	/* Load the Reset Handler address of the application */
	app_start_address = *(uint32_t *)(APP_START_ADDRESS + 4);

	/* Jump to application Reset Handler in the application */
	asm("bx %0"::"r"(app_start_address));
}


/**
 * \brief Function to check the bootloader mode activaton.
 */
static void bootloader_mode_check()
{
	volatile uint32_t temp;
	volatile bool boot_mode;

	/* Check Force Boot option */
	boot_mode = !(flashcalw_read_gp_fuse_bit(BOOT_GP_FUSE_BIT));
	/* If Force Boot is enabled, ignore other check and start the bootloader */
	if (!boot_mode) {
		/* Get the pointer to the GPIO Port Address */
		temp = (uint32_t)((GPIO_ADDR +
						(BOOT_LOAD_PIN >> 5) * sizeof(GpioPort)));
		/* Enable the input mode in Boot GPIO Pin and enable the internal pull-up*/
		((GpioPort *)temp)->GPIO_ODERC = GPIO_BOOT_PIN_MASK;
		((GpioPort *)temp)->GPIO_STERS = GPIO_BOOT_PIN_MASK;
		((GpioPort *)temp)->GPIO_PUERS = GPIO_BOOT_PIN_MASK;
		/* Activation of bootloader mode pin */
		boot_mode = ((((GpioPort *)temp)->GPIO_PVR & GPIO_BOOT_PIN_MASK)
							== BOOT_LOAD_PIN_ACTIVE_LVL);

		temp = *((uint32_t *)APP_START_ADDRESS);
		/* Check absence of application firmware */
		boot_mode = boot_mode ||( temp == 0xFFFFFFFF);

		/*
		 * Check the following one of the parameters for loading the bootloader
		 * Activation of the boot pin
		 * Absence of Application
		 */
		if (!boot_mode) {
			/* Enters application mode*/
			start_application();
		}
	}
	/* Enters bootloader mode */
}


/**
 * \brief Function to issue a WDT reset to start the application.
 * This will reset the clock & peripheral configurations.
 */
static void start_application_with_wdt()
{
	uint32_t wdt_ctrl_val;

	/* Disable the global interrupts */
	cpu_irq_disable();

	/* Switch on the LED */
	ioport_set_pin_level(BOOT_LED, BOOT_LED_ON_LVL);

	/* Store the WDT Configuration value */
	wdt_ctrl_val = (WDT_CTRL_EN | WDT_CTRL_PSEL(5) | WDT_CTRL_CEN
					| WDT_CTRL_DAR);

	/* Set the WDT to trigger a reset - Two times for the two keys*/
	WDT->WDT_CTRL = wdt_ctrl_val | WDT_CTRL_KEY(0x55u);
	WDT->WDT_CTRL = wdt_ctrl_val | WDT_CTRL_KEY(0xAAu);

	while (1) {
		/* Wait indefinitely for a WDT reset */
	}
}


/**
 * \brief Function to program the Flash. Decrypt the firmware and program it.
 */
static bool program_memory()
{
	uint32_t address_offset = 0;
	void *buf = NULL;
	uint32_t buffer_size = 0;
	bool programming_started = false;
#if VERIFY_PROGRAMMING_ENABLED
	uint32_t firmware_crc_output;
#endif

	/* Open the input file */
	f_open(&file_object,
			(char const *)input_file_name,
			FA_OPEN_EXISTING | FA_READ);

	/* Read the CRC data & Signature from the firmware */
	f_read(&file_object, (void *)buffer, APP_BINARY_OFFSET, &buffer_size);

	/* Check if there is any buffer */
	if (!buffer_size) {
		return false;
	}

#if FIRMWARE_AES_ENABLED
	/* Decrypt as a new message */
	aes_set_new_message(&g_aes_inst);

	/* Decrypt the AES data */
	aes_decrypt((uint32_t *)buffer, APP_BINARY_OFFSET/4);
#endif

	/* Set the busy LED */
	ioport_set_pin_level(BOOT_LED, BOOT_LED_ON_LVL);

	/* Program the flash memory page by page */
	while (true) {
		/* Open the input file */
		f_read(&file_object, (void *)buffer, FLASH_BUFFER_SIZE, &buffer_size);
		/* Check if there is any buffer */
		if (!buffer_size) {
			break;
		}

#if FIRMWARE_AES_ENABLED
		/* Decrypt the binary data */
		aes_decrypt((uint32_t *)buffer, buffer_size/4);
		/* Update the output buffer */
		buf = (void *)aes_output;
#else
		/* Update the output buffer */
		buf = (void *)buffer;
#endif

		/* Disable the global interrupts */
		cpu_irq_disable();

		/* Program the Flash Memory. */
		flashcalw_memcpy((void *)(APP_START_ADDRESS + address_offset),
							buf , buffer_size, true);
		/* Check the error status */
		if (flashcalw_is_lock_error() || flashcalw_is_programming_error()) {
			/* Abort programming */
			if (programming_started) {
				/* Erase the first page in the application */
				flashcalw_erase_page(APP_START_ADDRESS/FLASH_PAGE_SIZE, false);
			}

			/* Enable the global interrupts */
			cpu_irq_enable();

			/* Close the File after operation. */
			f_close(&file_object);

			return false;
		}

		/* Enable the global interrupts */
		cpu_irq_enable();

		/* Update the address and page offset values */
		address_offset += buffer_size;

		/* Update the programming flag */
		programming_started = true;
	}

	/* Close the File after operation. */
	f_close(&file_object);

#if VERIFY_PROGRAMMING_ENABLED
	/* Update the buffer size */
	buffer_size = address_offset;
	/* Re-initialize offset to zero */
	address_offset = 0;

	/* Reset the CRCCU to start fresh calculation */
	crccu_reset(CRCCU);

	/* CRC calculation with max 0xFFF since the CRCCU size limit is 12-bit */
	do {
		/* Calculate the CRC32 of the programmed memory */
		crc32_calculate((uint32_t)(APP_START_ADDRESS + address_offset),
							min(0xFFF, buffer_size));
		buffer_size -= min(0xFFF, buffer_size);
		address_offset += 0xFFF;
	} while (buffer_size!=0);

	/* Get the CRC32 value */
	firmware_crc_output = crccu_read_crc_value(CRCCU);

	if (APP_CRC_POLYNOMIAL_TYPE == CRCCU_MR_PTYPE_CCITT16) {
		/* 16-bit CRC */
		firmware_crc_output &= 0xFFFF;
	}

	/* Compare the calculated CRC Value */
	if (firmware_crc != firmware_crc_output) {
		/* Verification Failed */
		return false;
	}
#endif

	/* Clear the busy LED */
	ioport_set_pin_level(BOOT_LED, BOOT_LED_OFF_LVL);

	/* return true */
	return true;
}


/**
 * \brief Function to check the integrity of the firmware.
 */
static bool integrity_check()
{
	uint8_t *buf = NULL;
	uint32_t firmware_crc_output = 0;
	uint32_t buffer_size = 0;
	uint8_t *signature_bytes = APP_SIGNATURE;

	/* Reset the CRCCU */
	crccu_reset(CRCCU);

	/* Open the input file */
	f_open(&file_object,
			(char const *)input_file_name,
			FA_OPEN_EXISTING | FA_READ);

	/* Routine to check the signature for decryption
	 * Firmware - First 4 bytes - CRC32, 12 bytes - Firmware Signature/Password
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

#if FIRMWARE_AES_ENABLED
	/* Initialize the AES Module */
	init_aes();

	/* Decrypt the AES data */
	aes_decrypt((uint32_t *)buffer, buffer_size/4);

	/* Update the buffer */
	buf = (uint8_t *) aes_output;
#else
	/* Update the buffer */
	buf = (uint8_t *) buffer;
#endif

	/* Store the firmware CRC */
	firmware_crc = *(uint32_t *)buf;
	/* Update the buffer size */
	buffer_size-=4;
	buf+=4;
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
	/* Verify the CRC32 of the entire decrypted file before programming */
	while (true) {
		/* Read the data from the firmware */
		f_read(&file_object, (void *)buffer, FLASH_BUFFER_SIZE, &buffer_size);
		/* Check if there is any buffer */
		if (!buffer_size) {
			break;
		}
#if FIRMWARE_AES_ENABLED
		/* Decrypt the application binary */
		aes_decrypt((uint32_t *)(buffer), buffer_size/4);
		/* Update the output buffer */
		buf = (uint8_t *) aes_output;
#else
		/* Update the output buffer */
		buf = (uint8_t *) buffer;
#endif

		/* Calculate the CRC32 for the buffer */
		crc32_calculate((uint32_t) buf, buffer_size);
	}

	/* Get the CRC32 value */
	firmware_crc_output = crccu_read_crc_value(CRCCU);

	if (APP_CRC_POLYNOMIAL_TYPE == CRCCU_MR_PTYPE_CCITT16) {
		/* 16-bit CRC */
		firmware_crc_output &= 0xFFFF;
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

static void crc32_calculate(uint32_t address, uint32_t size)
{
	/* Set the memory address for CRCCU DMA transfer */
	crc_dscr.ul_tr_addr = address;

	/* Transfer width: byte, interrupt disable(here interrupt mask enabled) */
	crc_dscr.ul_tr_ctrl =
	CRCCU_TR_CTRL_TRWIDTH_BYTE | size |
	CRCCU_TR_CTRL_IEN_DISABLE;

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
	g_aes_inst.aes_cfg->encrypt_mode = AES_DECRYPTION;
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
static void aes_decrypt(uint32_t *encrypted_data, uint32_t size)
{
	uint16_t i;
	for (i = 0; i < size ; i+=4) {
		/* Write the data to be ciphered to the input data registers */
		aes_write_input_data(&g_aes_inst, (encrypted_data[i]));
		aes_write_input_data(&g_aes_inst, (encrypted_data[i+1]));
		aes_write_input_data(&g_aes_inst, (encrypted_data[i+2]));
		aes_write_input_data(&g_aes_inst, (encrypted_data[i+3]));

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
static void bootloader_system_init()
{
	/* Initialize the system clocks */
	sysclk_init();

	/* Initialize the board components */
	board_init();

	/* Initialize the sleep manager */
	sleepmgr_init();

	/* Enable CRCCU peripheral clock */
	sysclk_enable_peripheral_clock(CRCCU);

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

	/* Check whether the bootloader mode is activated */
	bootloader_mode_check();

	/* Device initialization for the bootloader */
	bootloader_system_init();

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
		while (sof_count < 1000);

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
				CONSOLE_PUTS(TASK_FAILED);
#endif
				/* LUN error */
				f_close(&file_object);
				continue;
			}

			/* Close the File after operation. */
			f_close(&file_object);

#if CONSOLE_OUTPUT_ENABLED
			/* Print the current task */
			CONSOLE_PUTS(TASK_PASSED);
			CONSOLE_PUTS("\n\rIntegrity check...");
#endif
			/* Validate the firmware file */
			if (!integrity_check()) {
#if CONSOLE_OUTPUT_ENABLED
				/* Print a header */
				CONSOLE_PUTS(TASK_FAILED);
#endif
				continue;
			}

#if CONSOLE_OUTPUT_ENABLED
			/* Print the current task */
			CONSOLE_PUTS(TASK_PASSED);
#  if VERIFY_PROGRAMMING_ENABLED
			CONSOLE_PUTS("\n\rProgramming & verifying...");
#  else
			CONSOLE_PUTS("\n\rProgramming...");
#  endif
#endif
			/* Program the memory */
			if (!program_memory()) {
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

#if CONSOLE_OUTPUT_ENABLED
			/* Print the current task */
			CONSOLE_PUTS(TASK_PASSED);
			CONSOLE_PUTS("\n\rStarting application...");
#endif
			/* Reset the Force BOOT bit */
			if(!(flashcalw_read_gp_fuse_bit(BOOT_GP_FUSE_BIT))) {
				flashcalw_erase_gp_fuse_bit(BOOT_GP_FUSE_BIT, false);
			}

#if SECURITY_BIT_ENABLED
			/* Enable the security bit feature */
			if(!(flashcalw_is_security_bit_active())) {
				flashcalw_set_security_bit();
			}
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
 * \mainpage ASF SAM4L USB Host Mass Storage Bootloader Solution
 *
 * \section intro Introduction
 * SAM4L USB Host Mass Storage Bootloader application is to facilitate firmware
 * upgrade using USB MSC drives. The application includes CRC check,
 * Signature verification, AES decryption and memory verification functionality
 * offering safe and secure firmware upgradation.
 *
 * \section startup Procedure
 * - Do complete chip erase
 * - Program the bootloader
 * - Load the application firmware into U-disk. Connect it to the SAM4L
 *   USB MSC Host
 * - Press push button on RESET to start the bootloader
 *
 * \section config Bootloader Configuration
 * Bootloader Configurations are managed in conf_bootloader.h
 *   - FIRMWARE_AES_ENABLED       -> Enable/disable the AES Decryption
 *   - CONSOLE_OUTPUT_ENABLED     -> Enable/disable the Console message output
 *   - VERIFY_PROGRAMMING_ENABLED -> Enable/disable the verification of
 *                                   programmed memory
 *   - SECURITY_BIT_ENABLED       -> Enable/disable the security bit feature
 *   - APP_START_OFFSET           -> Application starting offset from Flash
 *   - FIRMWARE_IN_FILE_NAME      -> Application Firmware file to be programmed
 *   - APP_SIGNATURE              -> Signature bytes to be verified
 *   - BOOT_LOAD_PIN              -> IO Pin used for bootloader activation
 *   - BOOT_LOAD_PIN_ACTIVE_LVL   -> Active level to be monitored for the pin
 *   - BOOT_GP_FUSE_BIT           -> GP Fuse bit used for bootloader activation
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
 * \section func Bootloader Operation
 * The bootloader will decrypt the first block (24 bytes of data). It verifies
 * the Signature data. If the verification is successful, it decrypts the
 * entire firmware and generates CRC32 value and compares it with the stored
 * CRC32 value. If it matches, it starts to program the application. Then,
 * verification of the programmed memory (CRC32 check again) is performed.
 * Then it jumps to the application section with WDT reset.
 * - Required Firmware Structure with AES:
 *   - 4 bytes   -> Encrypted CRC32
 *   - 12 bytes  -> Encrypted Signature Data
 *   - Rest data -> Encrypted Input Firmware
 * - Required Firmware Structure without AES:
 *   - 4 bytes   -> CRC32
 *   - 12 bytes  -> Signature Data
 *   - Rest data -> Input Firmware
 * - A sample application binary output (AES encrypted) is provided for testing
 *   with the bootloader.
 *
 * \section app_req Application Requirements
 * The SAM4L USB Host MSC Bootloader occupies the 32KB of the flash memory
 * (may differ on the optimization setting used for build). Hence, the
 * application has to be shifted by the same offset. To offset the application
 * in those linkerscript files, set the flash origin to 0x8000 and decrease the
 * flash size by 0x8000 for the application project.
 * When AES is enabled, the encrypted application binary should be 16-byte
 * aligned. If Firmware Generator is used, it takes care of the alignment.
 *
 * \copydoc UI
 *
 * \section  dependencies Application Dependencies
 *
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
 * - Thirdparty modules:
 *   <br>thirdparty/fatfs

 */
