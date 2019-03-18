/**
 * \file
 *
 * \brief Instance description for SPI_FLASH0
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _SAMB11_SPI_FLASH0_INSTANCE_
#define _SAMB11_SPI_FLASH0_INSTANCE_

/* ========== Register definition for SPI_FLASH0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_SPI_FLASH0_MODE_CTRL (0x40012000U) /**< (SPI_FLASH0) SPI Flash Mode Control */
#define REG_SPI_FLASH0_TRANSACTION_CTRL (0x40012004U) /**< (SPI_FLASH0) Transaction Control (Cleared after each transaction completes) */
#define REG_SPI_FLASH0_READ_CTRL (0x40012008U) /**< (SPI_FLASH0) Read Control (Cleared after each transaction completes) */
#define REG_SPI_FLASH0_CMD_BUFFER0 (0x4001200CU) /**< (SPI_FLASH0) Command Buffer 0 (Bytes 3 - 0) */
#define REG_SPI_FLASH0_CMD_BUFFER1 (0x40012010U) /**< (SPI_FLASH0) Command Buffer 1 (Bytes 7 - 4) */
#define REG_SPI_FLASH0_DIRECTION (0x40012014U) /**< (SPI_FLASH0) Read/Write bit for Bytes 7 - 0 */
#define REG_SPI_FLASH0_IRQ_STATUS (0x40012018U) /**< (SPI_FLASH0) IRQ Status (Write 0 to bit to clear, Read clears interupts) */
#define REG_SPI_FLASH0_DMA_START_ADDRESS (0x4001201CU) /**< (SPI_FLASH0) DMA Starting Address */
#define REG_SPI_FLASH0_CONFIG   (0x40012020U) /**< (SPI_FLASH0) SPI Flash Configuration */
#define REG_SPI_FLASH0_TX_CONTROL (0x40012024U) /**< (SPI_FLASH0) TX Control */
#define REG_SPI_FLASH0_STATUS   (0x40012028U) /**< (SPI_FLASH0) Misc Status */

#else

#define REG_SPI_FLASH0_MODE_CTRL (*(__IO uint8_t*)0x40012000U) /**< (SPI_FLASH0) SPI Flash Mode Control */
#define REG_SPI_FLASH0_TRANSACTION_CTRL (*(__IO uint32_t*)0x40012004U) /**< (SPI_FLASH0) Transaction Control (Cleared after each transaction completes) */
#define REG_SPI_FLASH0_READ_CTRL (*(__IO uint32_t*)0x40012008U) /**< (SPI_FLASH0) Read Control (Cleared after each transaction completes) */
#define REG_SPI_FLASH0_CMD_BUFFER0 (*(__IO uint32_t*)0x4001200CU) /**< (SPI_FLASH0) Command Buffer 0 (Bytes 3 - 0) */
#define REG_SPI_FLASH0_CMD_BUFFER1 (*(__IO uint32_t*)0x40012010U) /**< (SPI_FLASH0) Command Buffer 1 (Bytes 7 - 4) */
#define REG_SPI_FLASH0_DIRECTION (*(__IO uint8_t*)0x40012014U) /**< (SPI_FLASH0) Read/Write bit for Bytes 7 - 0 */
#define REG_SPI_FLASH0_IRQ_STATUS (*(__O  uint8_t*)0x40012018U) /**< (SPI_FLASH0) IRQ Status (Write 0 to bit to clear, Read clears interupts) */
#define REG_SPI_FLASH0_DMA_START_ADDRESS (*(__IO uint32_t*)0x4001201CU) /**< (SPI_FLASH0) DMA Starting Address */
#define REG_SPI_FLASH0_CONFIG   (*(__IO uint16_t*)0x40012020U) /**< (SPI_FLASH0) SPI Flash Configuration */
#define REG_SPI_FLASH0_TX_CONTROL (*(__IO uint16_t*)0x40012024U) /**< (SPI_FLASH0) TX Control */
#define REG_SPI_FLASH0_STATUS   (*(__I  uint16_t*)0x40012028U) /**< (SPI_FLASH0) Misc Status */

#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance Parameter definitions for SPI_FLASH0 peripheral ========== */
#define SPI_FLASH0_FLASH_SIZE                    131072    
#define SPI_FLASH0_ADDRESS_SPACE_REF             extflash  
#define SPI_FLASH0_PAGES                         2048      
#define SPI_FLASH0_PAGE_SIZE                     64        

#endif /* _SAMB11_SPI_FLASH0_INSTANCE_ */
