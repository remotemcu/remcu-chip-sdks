/**
 * \file
 *
 * \brief Boot process definition for uc3 parts.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _BOOT_H_
#define _BOOT_H_

#include "flash_api.h"

/**
 * \ingroup isp
 * \defgroup boot_uc3 Boot Process definition for UC3 parts
 *
 * The behavior of the UC3 boot process for bootloader is defined
 * by the fuses values and two Words in the user page.
 *
 * The AT32UC3 boot process is described in both documents:
 * - in application note AVR32806 for AT32UC3 USB bootloader (Version >1.1.0).
 * - in application note AVR32728 for AT32UC3 UART bootloader.
 * @{
 */

/**
 * \name User page word1 definition
 */
//@{
#define BOOT_CFG1                      (*(volatile uint32_t *)BOOT_CFG1_ADDRESS)
#define BOOT_CFG1_ADDRESS              \
	(FLASH_API_USER_PAGE_ADDRESS + BOOT_CFG1_OFFSET)
#define BOOT_CFG1_OFFSET               \
	(FLASH_API_USER_PAGE_SIZE - BOOT_CFG1_SIZE)
#define BOOT_CFG1_SIZE                 4

#define BOOT_CFG1_BOOT_KEY1            16
#define BOOT_CFG1_BOOT_KEY1_MASK       0xFFFF0000
#define BOOT_CFG1_BOOT_KEY1_OFFSET     16
#define BOOT_CFG1_BOOT_KEY1_SIZE       16
#define BOOT_CFG1_BOOT_KEY1_VALUE      0xE11E

#define BOOT_CFG1_FORCE                9
#define BOOT_CFG1_FORCE_MASK           0x00000200
#define BOOT_CFG1_FORCE_OFFSET         9
#define BOOT_CFG1_FORCE_SIZE           1

#define BOOT_CFG1_IO_COND_EN           8
#define BOOT_CFG1_IO_COND_EN_MASK      0x00000100
#define BOOT_CFG1_IO_COND_EN_OFFSET    8
#define BOOT_CFG1_IO_COND_EN_SIZE      1

#define BOOT_CFG1_CRC8                 0
#define BOOT_CFG1_CRC8_MASK            0x000000FF
#define BOOT_CFG1_CRC8_OFFSET          0
#define BOOT_CFG1_CRC8_SIZE            8
#define BOOT_CFG1_CRC8_POLYNOMIAL      0x107
//@}

/**
 * \name User page word2 definition
 */
//@{
#define BOOT_CFG2                      (*(volatile U32 *)BOOT_CFG2_ADDRESS)
#define BOOT_CFG2_ADDRESS              \
	(FLASH_API_USER_PAGE_ADDRESS + BOOT_CFG2_OFFSET)
#define BOOT_CFG2_OFFSET               \
	(FLASH_API_USER_PAGE_SIZE - BOOT_CFG1_SIZE - BOOT_CFG2_SIZE)
#define BOOT_CFG2_SIZE                 4

#define BOOT_CFG2_BOOT_KEY             17
#define BOOT_CFG2_BOOT_KEY_MASK        0xFFFE0000
#define BOOT_CFG2_BOOT_KEY_OFFSET      17
#define BOOT_CFG2_BOOT_KEY_SIZE        15
#define BOOT_CFG2_BOOT_KEY_VALUE       0x494F

#define BOOT_CFG2_IO_COND_LEVEL        16
#define BOOT_CFG2_IO_COND_LEVEL_MASK   0x00010000
#define BOOT_CFG2_IO_COND_LEVEL_OFFSET 16
#define BOOT_CFG2_IO_COND_LEVEL_SIZE   1

#define BOOT_CFG2_IO_COND_PIN          8
#define BOOT_CFG2_IO_COND_PIN_MASK     0x0000FF00
#define BOOT_CFG2_IO_COND_PIN_OFFSET   8
#define BOOT_CFG2_IO_COND_PIN_SIZE     8

#define BOOT_CFG2_CRC8                 0
#define BOOT_CFG2_CRC8_MASK            0x000000FF
#define BOOT_CFG2_CRC8_OFFSET          0
#define BOOT_CFG2_CRC8_SIZE            8
#define BOOT_CFG2_CRC8_POLYNOMIAL      0x107
//@}

/**
 * \name SRAM key definition
 * It is used by boot process after a hot CPU reset
 */
//@{
#define BOOT_KEY                       (*(volatile U32 *)BOOT_KEY_ADDRESS)
#define BOOT_KEY_ADDRESS               (AVR32_SRAM_ADDRESS + BOOT_KEY_OFFSET)
#define BOOT_KEY_OFFSET                0x00000000
#define BOOT_KEY_SIZE                  4
#define BOOT_KEY_VALUE                 ('I' << 24 | 'S' << 16 | 'P' << 8 | 'K')
//@}

/**
 * \name User program start address definition
 */
//@{
#define PROGRAM_START_ADDRESS         \
	(AVR32_FLASH_ADDRESS + PROGRAM_START_OFFSET)
#define PROGRAM_START_OFFSET          0x00002000
//@}

//@}


#endif // _BOOT_H_
