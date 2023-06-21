/**
 *
 * \file
 *
 * \brief OTA Firmware update Example Implementation.
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

#include "asf.h"
#if SAM4SD32
#include "ota_fw_update.h"
#include "FreeRTOS.h"
#include "iot/http/http_client.h"
#include "lwip/ip.h"
#include "lwip/api.h"
#include "lwip/tcpip.h"
#include "lwip/sockets.h"
#include "os/include/net_init.h"
#include "os/include/m2m_wifi_ex.h"
#include "tinyservices.h"
#include "conf_wilc.h"
#include "http_downloader/httpdownloader.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>

uint8 g_page_buffer[IFLASH1_PAGE_SIZE];
static uint32_t g_page_offset = 0;
static uint32_t g_page_addr = IFLASH1_ADDR;

int erase_all_sectors(void);
int lock_all_sectors(void);
int unlock_all_sectors(void);
/**
 * \brief Lock all sectors in flash1
 */
int lock_all_sectors(){
	uint32_t ul_rc;
	uint ul_sector_addr = IFLASH1_ADDR;
	/* lock smaller sectors of sector0 */
	for(int count = 0; count < SMALLERSECTOR_COUNT ; count++){
		ul_rc = flash_lock(ul_sector_addr, ul_sector_addr + SECT0_SMALLERSECTOR_SIZE - 1, 0, 0);
		if (ul_rc != FLASH_RC_OK) {
			printf("-F- Flash locking error %lu\n\r", ul_rc);
			return FAILURE;
		}
		ul_sector_addr += SECT0_SMALLERSECTOR_SIZE;
	}
	/* lock larger sector of sector0 */
	ul_rc = flash_lock(ul_sector_addr, ul_sector_addr + SECT0_LARGERSECTOR_SIZE - 1, 0, 0);
	if (ul_rc != FLASH_RC_OK) {
		printf("-F- Flash locking error %lu\n\r", ul_rc);
		return FAILURE;
	}
	ul_sector_addr += SECT0_LARGERSECTOR_SIZE;
	/* lock sector1 to sector15 */
	for(int count = 0; count < NO_OF_SECTORS -1 ; count++){	
		ul_rc = flash_lock(ul_sector_addr, ul_sector_addr + SECTOR_SIZE - 1, 0, 0);
		if (ul_rc != FLASH_RC_OK) {
			printf("-F- Flash locking error %lu\n\r", ul_rc);
			return FAILURE;
		}
		ul_sector_addr += SECTOR_SIZE;
	}
	return SUCCESS;
}


/**
 * \brief Unlock all sectors in flash1
 */
int unlock_all_sectors(){
	uint32_t ul_rc;
	uint ul_sector_addr = IFLASH1_ADDR;
	
	/* Unlock smaller sectors of sector0 */
	for(int count = 0; count < SMALLERSECTOR_COUNT ; count++){
		ul_rc = flash_unlock(ul_sector_addr, ul_sector_addr + SECT0_SMALLERSECTOR_SIZE - 1, 0, 0);
		if (ul_rc != FLASH_RC_OK) {
			printf("-F- Unlock error %lu\n\r", ul_rc);
			return FAILURE;
		}
		ul_sector_addr += SECT0_SMALLERSECTOR_SIZE;
	}
	/* Unlock larger sector of sector0 */
	ul_rc = flash_unlock(ul_sector_addr, ul_sector_addr + SECT0_LARGERSECTOR_SIZE - 1, 0, 0);
	if (ul_rc != FLASH_RC_OK) {
		printf("-F- Unlock error %lu\n\r", ul_rc);
		return FAILURE;
	}
	ul_sector_addr += SECT0_LARGERSECTOR_SIZE;
	
	/* unlock sector1 to sector15 */		
	for(int count = 0; count < NO_OF_SECTORS - 1 ; count++){
		/* Unlock sector */
		ul_rc = flash_unlock(ul_sector_addr, ul_sector_addr + SECTOR_SIZE - 1, 0, 0);
		if (ul_rc != FLASH_RC_OK) {
			printf("-F- Unlock error %lu\n\r", ul_rc);
			return FAILURE;
		}
		ul_sector_addr += SECTOR_SIZE;
	}
	printf("Flash1 unlocked successfully\r\n");
	return SUCCESS;
}

/**
 * \brief erase all sectors in flash1
 */
int erase_all_sectors(){
	uint32_t ul_rc;
	uint ul_sector_addr = IFLASH1_ADDR;
	/* Erase smaller sectors of sector0 */
	for(int count = 0; count < SMALLERSECTOR_COUNT ; count++){
		ul_rc = flash_erase_sector(ul_sector_addr);
		if (ul_rc != FLASH_RC_OK) {
			printf("-F- Flash programming erase error %lu in small0 sect\n\r", ul_rc);
			return FAILURE;
		}
		ul_sector_addr += SECT0_SMALLERSECTOR_SIZE;
	}
	/* Erase larger sector of sector0 */
	ul_rc = flash_erase_sector(ul_sector_addr);
	if (ul_rc != FLASH_RC_OK) {
		printf("-F- Flash programming erase error %lu in small1 sect\n\r", ul_rc);
		return FAILURE;
	}
	ul_sector_addr += SECT0_LARGERSECTOR_SIZE;
			
	/* Erase sector1 to sector15 */		
	for(int count = 0; count < NO_OF_SECTORS - 1 ; count++){
		/* Erase sector */
		ul_rc = flash_erase_sector(ul_sector_addr);
		if (ul_rc != FLASH_RC_OK) {
			printf("-F- Flash programming erase error  %lu in sector %d\n\r", ul_rc,count+1);
			return FAILURE;
		}
		ul_sector_addr += SECTOR_SIZE;
	}
	printf("Flash1 erased successfully\r\n");
	return SUCCESS;
}

/**
 * \brief Write data to Flash; page by page
 * \param[in] data  Chunk of bin file.
 * \param[in] length  Chunk length.
 * \param[in] is_last_chunk Last chunk of file, Indication to write all remaining data.
 */
int write_to_flash(char *data, uint32_t length, uint16_t is_last_chunk){
	uint32_t data_offset = 0;
	while(length > 0){
		if(g_page_offset + length >= IFLASH1_PAGE_SIZE){
			/* Arrange data in the size of flash page */
			memcpy(g_page_buffer + g_page_offset, data + data_offset, IFLASH1_PAGE_SIZE - g_page_offset);
			length -= (IFLASH1_PAGE_SIZE - g_page_offset);
			data_offset += (IFLASH1_PAGE_SIZE - g_page_offset);
			/* Write to a page in flash */
			uint32_t ul_rc = flash_write(g_page_addr, g_page_buffer, IFLASH1_PAGE_SIZE, 0);
			if (ul_rc != FLASH_RC_OK) {
				printf("-F- Flash programming write error %lu\n\r", ul_rc);
				return FAILURE;
			}
			g_page_addr += IFLASH1_PAGE_SIZE;  // Next page
			g_page_offset = 0;
		}
		else{
			/* Store the remaining data */
			memcpy(g_page_buffer + g_page_offset, data + data_offset, length);
			if(is_last_chunk){
				/* It is the last chunk, so write the remaining data to flash */
				uint32_t ul_rc = flash_write(g_page_addr, g_page_buffer, g_page_offset + length, 0);
				if (ul_rc != FLASH_RC_OK) {
					printf("-F- Flash programming write error %lu\n\r", ul_rc);
					return FAILURE;
				}
			}
			g_page_offset += length;
			length = 0;
		}		
	}

	return SUCCESS;
}

/**
 * \brief ota firmware update function.
 */
void ota_firmware_update(char *fileURL)
{
	uint32_t ul_rc;
	/*Initialize flash service*/
	ul_rc = flash_init(FLASH_ACCESS_MODE_128, 6);
	if (ul_rc != FLASH_RC_OK) {
		printf("-F- Initialization error %lu\n\r", ul_rc);
		return;
	}
	if(flash_is_locked( IFLASH1_ADDR, IFLASH1_ADDR + (NO_OF_SECTORS * SECTOR_SIZE) - 1)){
		/*Unlock flash1 to erase and write */
		if (unlock_all_sectors() != SUCCESS) {
			printf("-F- Unlock error %lu\n\r", ul_rc);
			return;
		}	
	}
	/*Erase flash1 to write later*/
	if (erase_all_sectors() != SUCCESS) {
		printf("-F- Erase error %lu\n\r", ul_rc);
		return;
	}
	setFirmwareDownload(1);
	/*start downloading and writing to flash*/
	if(http_downloader(fileURL) == SUCCESS){
		printf("Switching flash!\r\nReboot board\r\n");
		if(flash_is_gpnvm_set(2)){
			if(flash_clear_gpnvm(2)!=FLASH_RC_OK){
				printf("clear GPNVM failed\r\n");
			}
		}else{
			if(flash_set_gpnvm(2) != FLASH_RC_OK){
				printf("set GPNVM failed\r\n");
			}
		}
	}else{
		printf("Firmware update failed\r\n");
		/*Erase flash1 to clear any partial data written*/
		/*if (erase_all_sectors() != SUCCESS) {
			printf("-F- Erase error %lu\n\r", ul_rc);
			return;
		}*/
	}
	setFirmwareDownload(0);
}
#endif
