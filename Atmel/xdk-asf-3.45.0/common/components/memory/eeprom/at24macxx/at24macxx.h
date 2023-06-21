/**
 * \file
 *
 * \brief API driver for component AT24MACXX.
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

#ifndef AT24MACXX_H_INCLUDED
#define AT24MACXX_H_INCLUDED

#include "twihs_master.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

//! Checking board configuration of the AT24MAC EEPROM
#if !defined(BOARD_AT24MAC_TWIHS_INSTANCE)
# warning The AT24MAC TWIHS instance has not been defined. Using default settings.
# define BOARD_AT24MAC_TWIHS_INSTANCE      TWIHS0 /* TWIHS instance (TWIHS0) */
#endif
#if !defined(BOARD_AT24MAC_ADDRESS)
# warning The AT24MAC TWI address has not been defined. Using default settings.
# define BOARD_AT24MAC_ADDRESS             (0xAE >> 1)/* TWIHS eeprom address */
#endif
#if !defined(BOARD_CLK_TWIHS_EEPROM)
# warning The AT24MAC TWIHS CLK pin index has not been defined. Using default.
# define BOARD_CLK_TWIHS_EEPROM            0 /* TWIHS eeprom clock pin index */
#endif
#if !defined(BOARD_CLK_TWIHS_MUX_EEPROM)
# warning The AT24MAC TWIHS CLK peripheral has not been defined. Using default.
# define BOARD_CLK_TWIHS_MUX_EEPROM        0 /* TWIHS eeprom clock pin peripheral */
#endif

/* AT24MACXX internal address length */
#define AT24MAC_MEM_ADDR_LEN               1

/* Return value for accessing AT24MACXX */
#define AT24MAC_WRITE_SUCCESS              0
#define AT24MAC_WRITE_FAIL                 1
#define AT24MAC_READ_SUCCESS               0
#define AT24MAC_READ_FAIL                  1

void at24macxx_reset(void);
uint32_t at24macxx_write_byte(uint32_t u32_address, uint8_t uc_value);
uint32_t at24macxx_write_continuous(uint32_t u32_start_address,
		uint16_t u16_length, uint8_t const *p_wr_buffer);
uint32_t at24macxx_read_byte(uint32_t u32_address, uint8_t *p_rd_byte);
uint32_t at24macxx_read_continuous(uint32_t u32_start_address, uint16_t u16_length,
		uint8_t *p_rd_buffer);
uint32_t at24macxx_write_page(uint32_t u32_page_address,
		uint32_t u32_page_size, uint8_t const *p_wr_buffer);
uint32_t at24macxx_read_page(uint32_t u32_page_address,
		uint32_t u32_page_size, uint8_t *p_rd_buffer);
uint32_t at24macxx_fill_pattern(uint32_t u32_start_address,
		uint32_t u32_end_address, uint8_t u8_pattern);

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

#endif /* AT24MACXX_H_INCLUDED */
