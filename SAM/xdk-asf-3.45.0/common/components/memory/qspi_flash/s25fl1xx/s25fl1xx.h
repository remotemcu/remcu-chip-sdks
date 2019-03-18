/**
 * \file
 *
 * \brief QSPI flash memory driver for S25FL116K.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */


#ifndef S25FL1XX_H
#define S25FL1XX_H

#include "qspi.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/** Device is protected, operation cannot be carried out. */
#define S25FL1XX_ERROR_PROTECTED                  1
/** Device is busy executing a command. */
#define S25FL1XX_ERROR_BUSY                       2
/** There was a problem while trying to program page data. */
#define S25FL1XX_ERROR_PROGRAM                    3
/** There was an SPI communication error. */
#define S25FL1XX_ERROR_SPI                        4

/** Device ready/busy status bit. */
#define S25FL1XX_STATUS_RDYBSY                    (1 << 0)
/** Device is ready. */
#define S25FL1XX_STATUS_RDYBSY_READY              (0 << 0)
/** Device is busy with internal operations. */
#define S25FL1XX_STATUS_RDYBSY_BUSY               (1 << 0)
/** Write enable latch status bit. */
#define S25FL1XX_STATUS_WEL                       (1 << 1)
/** Device is not write enabled. */
#define S25FL1XX_STATUS_WEL_DISABLED              (0 << 1)
/** Device is write enabled. */
#define S25FL1XX_STATUS_WEL_ENABLED               (1 << 1)
/** Software protection status bit-field. */
#define S25FL1XX_STATUS_SWP                       (3 << 2)
/** All sectors are software protected. */
#define S25FL1XX_STATUS_SWP_PROTALL               (3 << 2)
/** Some sectors are software protected. */
#define S25FL1XX_STATUS_SWP_PROTSOME              (1 << 2)
/** No sector is software protected. */
#define S25FL1XX_STATUS_SWP_PROTNONE              (0 << 2)
/** Write protect pin status bit. */
#define S25FL1XX_STATUS_WPP                       (1 << 4)
/** Write protect signal is not asserted. */
#define S25FL1XX_STATUS_WPP_NOTASSERTED           (0 << 4)
/** Write protect signal is asserted. */
#define S25FL1XX_STATUS_WPP_ASSERTED              (1 << 4)
/** Erase/program error bit. */
#define S25FL1XX_STATUS_EPE                       (1 << 5)
/** Erase or program operation was successful. */
#define S25FL1XX_STATUS_EPE_SUCCESS               (0 << 5)
/** Erase or program error detected. */
#define S25FL1XX_STATUS_EPE_ERROR                 (1 << 5)
/** Sector protection registers locked bit. */
#define S25FL1XX_STATUS_SPRL                      (1 << 7)
/** Sector protection registers are unlocked. */
#define S25FL1XX_STATUS_SPRL_UNLOCKED             (0 << 7)
/** Sector protection registers are locked. */
#define S25FL1XX_STATUS_SPRL_LOCKED               (1 << 7)
/** Quad enable bit */
#define S25FL1XX_STATUS_QUAD_ENABLE               (1 << 1)
/** Quad enable bit */
#define S25FL1XX_STATUS_WRAP_ENABLE               (0 << 4)
/** Latency control bits */
#define S25FL1XX_STATUS_LATENCY_CTRL              (0xF << 0)
#define S25FL1XX_STATUS_WRAP_BYTE                 (1 << 5)
#define S25FL1XX_BLOCK_PROTECT_Msk                (7 << 2)
#define S25FL1XX_TOP_BTM_PROTECT_Msk              (1 << 5)
#define S25FL1XX_SEC_PROTECT_Msk                  (1 << 6)
#define S25FL1XX_CHIP_PROTECT_Msk                 (0x1F << 2)

/** Sequential program mode command code 1. */
#define S25FL1XX_SEQUENTIAL_PROGRAM_1             0xAD
/** Sequential program mode command code 2. */
#define S25FL1XX_SEQUENTIAL_PROGRAM_2             0xAF
/** Protect sector command code. */
#define S25FL1XX_PROTECT_SECTOR                   0x36
/** Unprotected sector command code. */
#define S25FL1XX_UNPROTECT_SECTOR                 0x39
/** Read sector protection registers command code. */
#define S25FL1XX_READ_SECTOR_PROT                 0x3C
/** Resume from deep power-down command code. */
#define S25FL1XX_SOFT_RESET_ENABLE                0x66
/** Resume from deep power-down command code. */
#define S25FL1XX_SOFT_RESET                       0x99
/** Read status register command code. */
#define S25FL1XX_READ_STATUS_1                    0x05
/** Read status register command code. */
#define S25FL1XX_READ_STATUS_2                    0x35
/** Read status register command code. */
#define S25FL1XX_READ_STATUS_3                    0x33
/** Write enable command code. */
#define S25FL1XX_WRITE_ENABLE                     0x06
/** Write Enable for Volatile Status Register. */
#define S25FL1XX_WRITE_ENABLE_FOR_VOLATILE_STATUS 0x50
/** Write disable command code. */
#define S25FL1XX_WRITE_DISABLE                    0x04
/** Write status register command code. */
#define S25FL1XX_WRITE_STATUS                     0x01
/** Resume from deep power-down command code. */
#define S25FL1XX_WRAP_ENABLE                      0x77
/** Byte/page program command code. */
#define S25FL1XX_BYTE_PAGE_PROGRAM                0x02
/** Block erase command code (4K block). */
#define S25FL1XX_BLOCK_ERASE_4K                   0x20
/** Block erase command code (32K block). */
#define S25FL1XX_BLOCK_ERASE_32K                  0x52
/** Block erase command code (64K block). */
#define S25FL1XX_BLOCK_ERASE_64K                  0xD8
/** Chip erase command code 1. */
#define S25FL1XX_CHIP_ERASE_1                     0x60
/** Chip erase command code 2. */
#define S25FL1XX_CHIP_ERASE_2                     0xC7
/** Read array (low frequency) command code. */
#define S25FL1XX_READ_ARRAY_LF                    0x03
/** Read array command code. */
#define S25FL1XX_READ_ARRAY                       0x0B
/** Fast Read array  command code. */
#define S25FL1XX_READ_ARRAY_DUAL                  0x3B
/** Fast Read array  command code. */
#define S25FL1XX_READ_ARRAY_QUAD                  0x6B
/** Fast Read array  command code. */
#define S25FL1XX_READ_ARRAY_DUAL_IO               0xBB
/** Fast Read array  command code. */
#define S25FL1XX_READ_ARRAY_QUAD_IO               0xEB
/** Deep power-down command code. */
#define S25FL1XX_DEEP_PDOWN                       0xB9
/** Resume from deep power-down command code. */
#define S25FL1XX_RES_DEEP_PDOWN                   0xAB
/** Manufacturer/ Device ID command code. */
#define S25FL1XX_MANUFACTURER_DEVICE_ID           0x90
/** Read manufacturer and device ID command code. */
#define S25FL1XX_READ_JEDEC_ID                    0x9F
/** Continuous Read Mode Reset command code. */
#define S25FL1XX_CONT_MODE_RESET                  0xFF

/** QSPI Flash Manufacturer JEDEC ID */
#define S25FL1XX_ATMEL_SPI_FLASH                  0x1F
#define S25FL1XX_ST_SPI_FLASH                     0x20
#define S25FL1XX_WINBOND_SPI_FLASH                0xEF
#define S25FL1XX_MACRONIX_SPI_FLASH               0xC2
#define S25FL1XX_SST_SPI_FLASH                    0xBF

enum block_size {
	S25FL1XX_SIZE_4K = 0,
	S25FL1XX_SIZE_8K,
	S25FL1XX_SIZE_16K,
	S25FL1XX_SIZE_32K,
	S25FL1XX_SIZE_64K,
	S25FL1XX_SIZE_128K,
	S25FL1XX_SIZE_256K,
	S25FL1XX_SIZE_512K,
	S25FL1XX_SIZE_1M,
	S25FL1XX_SIZE_2M
};

enum status_code s25fl1xx_initialize(Qspi *qspi, struct qspi_config_t *mode_config, uint32_t use_default_config);
uint32_t s25fl1xx_read_jedec_id(struct qspid_t *qspid);
void s25fl1xx_soft_reset(struct qspid_t *qspid);
uint8_t s25fl1xx_protect(struct qspid_t *qspid);
uint8_t s25fl1xx_unprotect(struct qspid_t *qspid);
uint8_t s25fl1xx_data_protect(struct qspid_t *qspid, bool dir, enum block_size protect_size);
uint8_t s25fl1xx_data_unprotect(struct qspid_t *qspid);
void s25fl1xx_set_quad_mode(struct qspid_t *qspid, uint8_t mode);
void s25fl1xx_enable_wrap(struct qspid_t *qspid, uint8_t byte_align);
void s25fl1xx_set_read_latency_control(struct qspid_t *qspid, uint8_t latency);
uint8_t s25fl1xx_erase_chip(struct qspid_t *qspid);
uint8_t s25fl1xx_erase_sector(struct qspid_t *qspid, uint32_t address);
uint8_t s25fl1xx_erase_64k_block(struct qspid_t *qspid, uint32_t address);
uint8_t s25fl1xx_write(struct qspid_t *qspid, uint32_t *pdata, uint32_t size, uint32_t address, uint8_t secure);
uint8_t s25fl1xx_read(struct qspid_t *qspid, uint32_t *data,  uint32_t size, uint32_t address);
uint8_t s25fl1xx_read_dual(struct qspid_t *qspid, uint32_t *data, uint32_t size, uint32_t address);
uint8_t s25fl1xx_read_quad(struct qspid_t *qspid, uint32_t *data, uint32_t size, uint32_t address);
uint8_t s25fl1xx_read_dual_io(struct qspid_t *qspid, uint32_t *data, uint32_t size, uint32_t address,
		uint8_t cont_mode, uint8_t secure);
uint8_t s25fl1xx_read_quad_io(struct qspid_t *qspid, uint32_t *data, uint32_t size, uint32_t address,
		uint8_t cont_mode, uint8_t secure);
void s25fl1xx_continous_read_mode_reset(struct qspid_t *qspid);
void s25fl1xx_enter_continous_read_mode(struct qspid_t *qspid);

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

#endif // #ifndef S25FL1_H

