/**
 * \file
 *
 * \brief Bootloader configuration.
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

//! Configuration of the bootloader

#ifndef CONF_BOOTLOADER_H_
#define CONF_BOOTLOADER_H_

//! Enable/disable the CRC check
#define FIRMWARE_CRC_CHECK           ENABLE
//! Enable/disable the Console message output
#define CONSOLE_OUTPUT_ENABLED       DISABLE

//! Firmware file input name
#define FIRMWARE_IN_FILE_NAME        "0:firmware.bin"

//! Application starting offset - Verify with bootloader footprint*/
#define APP_START_OFFSET             0x10000
//! Application starting address in Flash
#define APP_START_ADDRESS            (FLASH_ADDR + APP_START_OFFSET)
//! Maximum possible size of the Application
#define APP_MAX_SIZE                 (FLASH_ADDR + FLASH_SIZE  \
										- APP_START_ADDRESS)
//! Buffer size to be used for programming
#define FLASH_BUFFER_SIZE            (FLASH_PAGE_SIZE)

//! Offset for the firmware in the input application binary - 16 bytes
#define APP_BINARY_OFFSET            (APP_CRC_SIZE + APP_SIGNATURE_SIZE)
//! CRCCU Polynomial Selection
#define APP_CRC_POLYNOMIAL_TYPE      CRC_TYPE_32 //32-bit CRC
//! Application Signature
#define APP_SIGNATURE                "ATMEL SAMD21"
//! Size of signature in bytes
#define APP_SIGNATURE_SIZE           12
//! Size of CRC32 in bytes
#define APP_CRC_SIZE                 4




#endif /* CONF_BOOTLOADER_H_ */
