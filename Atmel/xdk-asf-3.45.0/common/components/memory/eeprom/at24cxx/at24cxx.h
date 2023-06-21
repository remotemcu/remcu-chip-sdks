/**
 * \file
 *
 * \brief API driver for component AT24CXX.
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

#ifndef AT24CXX_H_INCLUDED
#define AT24CXX_H_INCLUDED

#include "twi_master.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

//! Checking board configuration of the AT24C EEPROM
#if !defined(BOARD_AT24C_TWI_INSTANCE)
# warning The AT24C TWI instance has not been defined. Using default settings.
# define BOARD_AT24C_TWI_INSTANCE 0 /* TWI instance (TWI0) */
#endif
#if !defined(BOARD_AT24C_ADDRESS)
# warning The AT24C TWI address has not been defined. Using default settings.
# define BOARD_AT24C_ADDRESS 0 /* TWI eeprom address (0x50u) */
#endif
#if !defined(BOARD_CLK_TWI_EEPROM)
# warning The AT24C TWI CLK pin index has not been defined. Using default.
# define BOARD_CLK_TWI_EEPROM 0 /* TWI eeprom clock pin index */
#endif
#if !defined(BOARD_CLK_TWI_MUX_EEPROM)
# warning The AT24C TWI CLK peripheral has not been defined. Using default.
# define BOARD_CLK_TWI_MUX_EEPROM 0 /* TWI eeprom clock pin peripheral */
#endif

/* AT24CXX internal address length */
#define AT24C_MEM_ADDR_LEN   2

/* Return value for accessing AT24CXX */
#define AT24C_WRITE_SUCCESS     0
#define AT24C_WRITE_FAIL        1
#define AT24C_READ_SUCCESS      0
#define AT24C_READ_FAIL         1

void at24cxx_reset(void);
uint32_t at24cxx_write_byte(uint32_t u32_address, uint8_t uc_value);
uint32_t at24cxx_write_continuous(uint32_t u32_start_address,
		uint16_t u16_length, uint8_t const *p_wr_buffer);
uint32_t at24cxx_read_byte(uint32_t u32_address, uint8_t *p_rd_byte);
uint32_t at24cxx_read_continuous(uint32_t u32_start_address, uint16_t u16_length,
		uint8_t *p_rd_buffer);
uint32_t at24cxx_write_page(uint32_t u32_page_address,
		uint32_t u32_page_size, uint8_t const *p_wr_buffer);
uint32_t at24cxx_read_page(uint32_t u32_page_address,
		uint32_t u32_page_size, uint8_t *p_rd_buffer);
uint32_t at24cxx_fill_pattern(uint32_t u32_start_address,
		uint32_t u32_end_address, uint8_t u8_pattern);

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

#endif /* AT24CXX_H_INCLUDED */
