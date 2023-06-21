/**
 *
 * \file
 *
 * \brief Bootloader for Host OTA firmware upgrade example.
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
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

/** \mainpage
 * \section intro Introduction
 * This example is bootloader with the SAM Xplained Pro
 * board to perform an Host MCU OTA Firmware upgrade.
 * The bootloader checks the trigger flag in the
 * \ref regions_info first. The \ref region_info is at the INFO_ADDR
 * of Flash which size is defined by \ref MEM_ERASE_SIZE in the
 * conf_bootloader.h. If the \ref trigger matched, it will try to find a
 * firmware file on WINC SPI Flash and updates the application firmware from
 * that file.
 * It uses the following hardware:
 * - the SAM Xplained Pro.
 * - the WINC1500 on EXT1.
 *
 * \section Bootloader Operation
 * The bootloader occupies the first part of the flash memory. The size is
 * defined by \ref BOOTLOAD_SIZE which is configurable in conf_bootloader.h.
 * The application has to be shifted by the this offset + info region offset
 * so that the bootloader can load and execute it rightly. It need to modify
 * the linker scripts for the application project: Increase the flash origion
 * address by \ref BOOTLOAD_SIZE and decrease the flash size by 
 * \ref BOOTLOAD_SIZE
 *
 * On startup, the bootloader will check the \ref trigger, if it was found,
 * it will start firmware update. If there was no trigger, it will jump to 
 * main application.
 *
 * Software trigger offers a method for application to start a customized
 * firmware upgrade. The application can modified the boot information block to
 * enable once trigger for update. Once the system is reset the bootloader
 * will use this specified setting to upgrade.The trigger is cleared after upgrade.
 *
 * -# Memory configurations
 *    - Some importent definitions for memory access
 *      - \ref MEM_BLOCK_SIZE : block size while writing
 *      - \ref MEM_ERASE_SIZE : erase block size
 *      - \ref BOOTLOAD_SIZE : reserved size for bootloader code
 *      - \ref APP_SIZE : reserved size for application with boot information
 *      - \ref INFO_SIZE : reserved size for boot information
 *        - By default information size is one erase block
 *
 * \section compinfo Compilation Information
 * This software was written for the GNU GCC compiler using Atmel Studio 6.2
 * Other compilers may or may not work.
 *
 */

#include "asf.h"
#include <string.h>
#include "spi_flash/include/spi_flash.h"
#include "driver/include/m2m_wifi.h"
#include "spi_flash/include/flexible_flash.h"
#include "driver/source/nmasic.h"
#include "memory_flash.h"
#include "bootloader.h"

#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- WINC1500 Host Firmware Upgrade- Bootloader code --"STRING_EOL \
	"-- "BOARD_NAME " --"STRING_EOL	\
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

#define none_blank(v32) (((v32)==0xFFFFFFFF)?0:(v32))
#define TRIGGER_BOOTLAOAD (1)
#define CRC16_INIT (0x1D0F)
#define CRC16_POLYNOMIAL (0x1021)
#define CRC_SIZE (4)


/** Boot informations (for regions) */
typedef struct regions_info {
	/** Firmware length in regions */
	uint32_t length;
	/** Software trigger to force action */
	uint32_t trigger;
	uint8_t padding[IFLASH_PAGE_SIZE-8];
} regions_info_t;

uint32 u32FlashHFDStart = 0;

void jump_to_app(void *code_addr);

/**
 * \brief Configure UART console.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate =		CONF_UART_BAUDRATE,
		.charlength =	CONF_UART_CHAR_LENGTH,
		.paritytype =	CONF_UART_PARITY,
		.stopbits =		CONF_UART_STOP_BITS,
	};

	/* Configure UART console. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief crc16-ccitt calculation
 */
static uint16_t crc16_add(uint16_t crc, unsigned char data)
{
	 int i;

	crc = crc ^ ((uint16_t)data << 8);
	for (i=0; i<8; i++)
	{
		if (crc & 0x8000)
			crc = (crc << 1) ^ CRC16_POLYNOMIAL; //(polynomial = 0x1021)
		else
			crc <<= 1;
	}
	return crc;
}


/**
 * \brief crc16-ccitt calculation for accumulated data
 */
static uint16_t crc16_data( unsigned char *data, uint32_t len, uint16_t acc)
{
	uint32_t j;
	for(j = 0; j < len; ++j) {
		acc = crc16_add(acc,*data);
		++data;
	}
	return acc;
}

/**
 * \brief Invalidate the Info region.
 */
static void region_info_clear(void)
{
	void *info_addr;

	info_addr = (void *)INFO_ADDR_START;
	printf("Clear info area ...\r\n");
	memory_unlock(info_addr, (void *)((uint32_t)info_addr + INFO_SIZE - 1));
	memory_erase(info_addr, INFO_SIZE);
	memory_lock(info_addr, (void *)((uint32_t)info_addr + INFO_SIZE - 1));
	printf("Clear info area done\r\n");
}

/**
 * Read region information
 * \param addr Address to read
 * \param info Pointer to region information to store
 */
static bool region_info_read(void *addr, regions_info_t *info)
{
	regions_info_t *p = (regions_info_t *) addr;
	info->length    = none_blank(p->length);
	info->trigger = p->trigger;
	printf("Read Info region ...\r\n");
	if(info->trigger == TRIGGER_BOOTLAOAD)
	{
		printf("Boot Trigger is Set\r\n");
		return true;
	}
	else
	{
		printf("No New image found\r\n");
		return false;
	}
}

/**
 * Checks that image in WINC SPI Flash is valid
 * \return true if image is valid
 */
static sint8 region_check_valid(uint32_t size)
{
	uint16_t crc_read = 0,crc_calc;
	sint8 ret;
	uint32 u32FlashHFDSize  = 0;
	uint32 CrcOffset,Offset,read_size,remain_size;
	uint8_t readBuf[IFLASH_PAGE_SIZE];
	bool last_page = false;

	/* Check length */
	if (size > APP_SIZE || size == 0) {
		return false;
	}

	/* Initialize WINC IOs. */
	nm_bsp_init();

	ret = m2m_wifi_download_mode();
	if (ret != M2M_SUCCESS) {
		puts("Failed to put the WiFi Chip in download mode!\n");
		return M2M_ERR_INIT;
	}

	ret = spi_flexible_flash_find_section(ENTRY_ID_HOSTFILE, &u32FlashHFDStart, &u32FlashHFDSize);
	if(M2M_SUCCESS != ret)
		return ret;

	CrcOffset =	size - CRC_SIZE;
	if((CrcOffset >= u32FlashHFDSize) || (size   >  u32FlashHFDSize))
	{
		ret = M2M_ERR_FAIL;
		return ret;
	}

	/* Calculate crc16 ccitt */
	remain_size = size;
	crc_calc = CRC16_INIT;
	Offset = 0;
	for(uint32_t i=0;i<size;)
	{
		if(remain_size >= IFLASH_PAGE_SIZE)
		{
			i= i+IFLASH_PAGE_SIZE;
			read_size = IFLASH_PAGE_SIZE;
			remain_size = remain_size-IFLASH_PAGE_SIZE;
		}
		else
		{
			i= i+remain_size;
			read_size = remain_size;
			remain_size = 0;
			last_page = true;
		}

		ret = spi_flash_read((uint8*)readBuf, u32FlashHFDStart+FLASH_SECTOR_SZ+Offset, read_size);
		if(M2M_SUCCESS != ret)
		{
			M2M_ERR("Unable to read SPI Flash\n");
			return ret;
		}

		if(last_page)
		{
			read_size = read_size-CRC_SIZE;
			crc_read = (uint16_t)(readBuf[read_size+3] << 8);
			crc_read = crc_read | readBuf[read_size+2];
		}

		crc_calc= crc16_data(readBuf,read_size,crc_calc);
		Offset = Offset+read_size;
	}

	if (crc_read != crc_calc)
	{
		printf("crc diff, crc_calc %x <> crc_read %x\r\n",
			(unsigned)crc_calc, (unsigned)crc_read);
		/* Invalidate info region as new image is not valid image */
		region_info_clear();
		return false;
	}
	printf("Valid new image is found\r\n");
	return true;
}

/**
 * Write new image to application section
 * \return true if writing is success
 */
static bool application_flash_write(void *code_addr, uint32_t size)
{
	uint8_t readBuf[IFLASH_PAGE_SIZE];
	sint8 ret;
	uint32 Offset=0,read_size,remain_size;

	memory_init();
	printf("Write new image to application section ...\r\n");
	memory_unlock(code_addr, (void *)((uint32_t)code_addr + APP_SIZE - 1));
	memory_erase(code_addr, APP_SIZE);

	remain_size = size;
	for(uint32_t i=0;i<size;)
	{
		if(remain_size >= IFLASH_PAGE_SIZE)
		{
			i= i+IFLASH_PAGE_SIZE;
			read_size = IFLASH_PAGE_SIZE;
			remain_size = remain_size-IFLASH_PAGE_SIZE;
		}
		else
		{
			i= i+remain_size;
			read_size = remain_size;
			remain_size = 0;
			read_size = read_size-CRC_SIZE;
			for(uint16_t j=0;j<IFLASH_PAGE_SIZE;j++)
				readBuf[j] = MEM_BLANK_VALUE;
		}

		ret = spi_flash_read((uint8*)readBuf, u32FlashHFDStart+FLASH_SECTOR_SZ+Offset, read_size);
		if(M2M_SUCCESS != ret)
		{
			M2M_ERR("Unable to read SPI Flash\n");
			return false;
		}

		memory_write((void *)((uint32_t)code_addr+Offset), readBuf);
		Offset = Offset+read_size;
	}

	memory_lock(code_addr, (void *)((uint32_t)code_addr + APP_SIZE - 1));
	printf("Write new image to application section done\r\n");

	return true;
}

/**
 * Jump to CM vector table
 *
 * \param code_addr Application start address (vector table address)
 */
#if defined   (__CC_ARM)     /* Keil µVision 4 */
__asm__ void jump_to_app(void *code_addr)
{
	mov r1, r0
	ldr r0, [r1, # 4]
	ldr sp, [r1]
	blx r0
}

#elif defined (__ICCARM__)   /* IAR Ewarm 5.41+ */
void jump_to_app(void *code_addr)
{
	UNUSED(code_addr);
	__asm(
			"mov     r1, r0        \n"
			"ldr     r0, [r1, #4]  \n"
			"ldr     sp, [r1]      \n"
			"blx     r0"
			);
}

#elif defined (__GNUC__)     /* GCC CS3 2009q3-68 */
void jump_to_app(void *code_addr)
{
	__asm__(
			"mov   r1, r0        \n"
			"ldr   r0, [r1, #4]  \n"
			"ldr   sp, [r1]      \n"
			"blx   r0"
			);
}

#else /* General C, no stack reset */
void jump_to_app(void *code_addr)
{
	void (*pFct)(void) = NULL;
	/* Point on __main address located in the second word in vector table */
	pFct = (void (*)(void))(*(uint32_t *)((uint32_t)code_addr + 4));
	pFct();
}

#endif

/**
 * Execute the application binary
 *
 * \param addr Application start address.
 * \return If success, no return;
 *         1 - address alignment error;
 *         2 - address not executable.
 */
static uint8_t _app_exec(void *addr)
{
	uint32_t i;
	/* Check parameters */
	if ((uint32_t)addr & 0x7F) {
		return 1;
	}

	__disable_irq();
	/* Disable SysTick */
	SysTick->CTRL = 0;
	/* Disable IRQs & clear pending IRQs */
	for (i = 0; i < 8; i++) {
		NVIC->ICER[i] = 0xFFFFFFFF;
		NVIC->ICPR[i] = 0xFFFFFFFF;
	}

	/* Switch clock to slow RC */
	osc_enable(OSC_SLCK_32K_RC);
	osc_wait_ready(OSC_SLCK_32K_RC);
	pmc_switch_mck_to_sclk(SYSCLK_PRES_1);
	/* Switch clock to fast RC */
#if SAMG55
	osc_enable(OSC_MAINCK_24M_RC);
	osc_wait_ready(OSC_MAINCK_24M_RC);
#else
	osc_enable(OSC_MAINCK_12M_RC);
	osc_wait_ready(OSC_MAINCK_12M_RC);
#endif	
	pmc_switch_mck_to_mainck(SYSCLK_PRES_1);

	/* Modify vector table location */
	__DSB();
	__ISB();
	SCB->VTOR = ((uint32_t)addr & SCB_VTOR_TBLOFF_Msk);
	__DSB();
	__ISB();
	__enable_irq();
	/* Jump to application */
	jump_to_app(addr);
	/* Never be here */
	return 0;
}


/**
 * \brief Main application function.
 *
 * Application entry point.
 *
 * \return program return value.
 */
int main(void)
{
	void *app_addr = NULL;
	regions_info_t info;

	/* Initialize the board. */
	sysclk_init();
	board_init();

	/* Initialize the UART console. */
	configure_console();
	printf(STRING_HEADER);

	app_addr = (void *)(APP_START);
	/* Read for boot */
	if(region_info_read((void *)INFO_ADDR_START, &info))
	{
		if(region_check_valid(info.length))
			{
				if(!application_flash_write(app_addr,info.length))
				/* Perform the software reset as failure in reading the application code*/
				rstc_start_software_reset(RSTC);
				else
				/* Invalidate info region as new image is loaded on application section */
				region_info_clear();
			}
	}

	/* run application */
	printf("Jump to Application Section\r\n\n");
	_app_exec(app_addr);

	return (int)app_addr;
}
