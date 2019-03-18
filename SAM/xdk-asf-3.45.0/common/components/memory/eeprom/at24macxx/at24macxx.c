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

/**
 * \defgroup common_components_memory_eeprom_at24macxx_group EEPROM AT24Cxx Series
 *
 * Low-level driver for the AT24MACXX Series EEPROM controller. This driver provides access to the main
 * features of the AT24MACXX Series EEPROM.
 *
 * \{
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "at24macxx.h"
#include "ioport.h"
#include "delay.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

#ifndef AT24MAC_MEM_ADDR_LEN
#  error Please define AT24MAC_MEM_ADDR_LEN according to the using AT24MAC
#else
#  if AT24MAC_MEM_ADDR_LEN>3
#    error AT24MAC_MEM_ADDR_LEN over 3 not supported
#  elif AT24MAC_MEM_ADDR_LEN>2
#    define at24mac_build_word_address(p_u8, addr) \
	do {\
		p_u8[0] = (uint8_t)(addr >> 16);\
		p_u8[1] = (uint8_t)(addr >>  8);\
		p_u8[2] = (uint8_t)(addr >>> 0);\
	} while (0)
#  elif AT24MAC_MEM_ADDR_LEN>1
#    define at24mac_build_word_address(p_u8, addr) \
	do {\
		p_u8[0] = (uint8_t)(addr >> 8);\
		p_u8[1] = (uint8_t)(addr >> 0);\
	} while (0)
#  else /* 1 */
#    define at24mac_build_word_address(p_u8, addr) \
	do {\
		p_u8[0] = (uint8_t)(addr >> 0);\
	} while (0)
#  endif
#endif /* AT24MAC_MEM_ADDR_LEN */

/**
 * \brief Poll the acknowledge from AT24MACXX.
 *
 * \param twihs_package Pointer to TWI data package. Only the slave address is
 * used in the acknowledge polling.
 */
static void at24macxx_acknowledge_polling(twihs_package_t *twihs_package)
{
	uint8_t data = 0;

	/* Store the package parameters */
	uint8_t addr = twihs_package->addr[0];
	uint32_t addr_length = twihs_package->addr_length;
	void *buffer = twihs_package->buffer;
	uint32_t length = twihs_package->length;

	/* Configure the data packet to be transmitted */
	twihs_package->addr[0] = 0;
	twihs_package->addr_length = 0;
	twihs_package->buffer = &data;
	twihs_package->length = 1;

	while (twihs_master_write(BOARD_AT24MAC_TWIHS_INSTANCE, twihs_package) !=
		TWIHS_SUCCESS);

	/* Restore the package parameters */
	twihs_package->addr[0] = addr;
	twihs_package->addr_length = addr_length;
	twihs_package->buffer = buffer;
	twihs_package->length = length;
}

/**
 * \brief Reset AT24MACXX.
 *
 * Send 9 clock cycles to reset memory state.
 *
 * \note IO mode is used in this function, so it can be used even if TWI is not
 *       enabled.
 */
void at24macxx_reset(void)
{
	uint32_t i;
	/* MEM reset
	 * a) Clock up to 9 cycles (use 100K)
	 * b) look for SDA high in each cycle while SCL is high and then
	 * c) Create a start condition as SDA is high
	 */
	/* - Enable pin output mode */
	ioport_set_pin_dir(BOARD_CLK_TWIHS_EEPROM, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(BOARD_CLK_TWIHS_EEPROM, 1);
	ioport_enable_pin(BOARD_CLK_TWIHS_EEPROM);
	for (i = 0; i < 10; i ++) {
		delay_us(5);
		ioport_set_pin_level(BOARD_CLK_TWIHS_EEPROM, 0);
		delay_us(5);
		ioport_set_pin_level(BOARD_CLK_TWIHS_EEPROM, 1);
	}
	/* - Restore pin peripheral mode */
	ioport_set_pin_mode(BOARD_CLK_TWIHS_EEPROM, BOARD_CLK_TWIHS_MUX_EEPROM);
	ioport_disable_pin(BOARD_CLK_TWIHS_EEPROM);
	/* - Start condition will do on R/W start */
}

/**
 * \brief Write single byte to AT24MACXX.
 *
 * \param u32_address Address of the byte to write.
 * \param u8_value Value that will be written to the specified address.
 *
 * \return AT24MAC_WRITE_SUCCESS if single byte was written, AT24MAC_WRITE_FAIL
 * otherwise.
 */
uint32_t at24macxx_write_byte(uint32_t u32_address, uint8_t u8_value)
{
	twihs_package_t twihs_package;

	/* Configure the data packet to be transmitted */
	twihs_package.chip = BOARD_AT24MAC_ADDRESS;
	at24mac_build_word_address(twihs_package.addr, u32_address);
	twihs_package.addr_length = AT24MAC_MEM_ADDR_LEN;
	twihs_package.buffer = &u8_value;
	twihs_package.length = 1;

	if (twihs_master_write(BOARD_AT24MAC_TWIHS_INSTANCE, &twihs_package) != TWIHS_SUCCESS) {
		return AT24MAC_WRITE_FAIL;
	}
	at24macxx_acknowledge_polling(&twihs_package);

	return AT24MAC_WRITE_SUCCESS;
}

/**
 * \brief Write multiple bytes continuously to AT24MACXX.
 *
 * \param u32_start_address Address of the first byte in transaction.
 * \param u16_length Number of bytes to write.
 * \param p_wr_buffer Pointer to array where the bytes to be written are stored.
 *
 * \return AT24MAC_WRITE_SUCCESS if single byte was written, AT24MAC_WRITE_FAIL
 * otherwise.
 */
uint32_t at24macxx_write_continuous(uint32_t u32_start_address,
		uint16_t u16_length, uint8_t const *p_wr_buffer)
{
	uint32_t i;

	for(i=0;i<u16_length;i++) {
		if (at24macxx_write_byte(u32_start_address, *p_wr_buffer) != AT24MAC_WRITE_SUCCESS) {
			return AT24MAC_WRITE_FAIL;
		}
		u32_start_address++;
		p_wr_buffer++;
	}

	return AT24MAC_WRITE_SUCCESS;
}

/**
 * \brief Read single byte from AT24MACXX.
 *
 * \param u32_address Address of the byte to read.
 * \param p_rd_byte Pointer to memory where the read byte will be stored.
 *
 * \return AT24MAC_READ_SUCCESS if one byte was read, AT24MAC_READ_FAIL otherwise.
 */
uint32_t at24macxx_read_byte(uint32_t u32_address, uint8_t *p_rd_byte)
{
	twihs_package_t twihs_package;

	/* Configure the data packet to be received */
	twihs_package.chip = BOARD_AT24MAC_ADDRESS;
	at24mac_build_word_address(twihs_package.addr, u32_address);
	twihs_package.addr_length = AT24MAC_MEM_ADDR_LEN;
	twihs_package.buffer = p_rd_byte;
	twihs_package.length = 1;

	if (twihs_master_read(BOARD_AT24MAC_TWIHS_INSTANCE, &twihs_package) !=
			TWIHS_SUCCESS) {
		return AT24MAC_READ_FAIL;
	}

	return AT24MAC_READ_SUCCESS;
}

/**
 * \brief Read multiple bytes continuously from AT24MACXX.
 *
 * \param u32_start_address Address of the first byte to read.
 * \param u16_length Number of bytes to read.
 * \param p_rd_buffer Pointer to memory where the read bytes will be stored.
 *
 * \return AT24MAC_READ_SUCCESS if one byte was read, AT24MAC_READ_FAIL otherwise.
 */
uint32_t at24macxx_read_continuous(uint32_t u32_start_address,
		uint16_t u16_length, uint8_t *p_rd_buffer)
{
	twihs_package_t twihs_package;

	/* Configure the data packet to be received */
	twihs_package.chip = BOARD_AT24MAC_ADDRESS;
	at24mac_build_word_address(twihs_package.addr, u32_start_address);
	twihs_package.addr_length = AT24MAC_MEM_ADDR_LEN;
	twihs_package.buffer = p_rd_buffer;
	twihs_package.length = u16_length;

	if (twihs_master_read(BOARD_AT24MAC_TWIHS_INSTANCE, &twihs_package) !=
			TWIHS_SUCCESS) {
		return AT24MAC_READ_FAIL;
	}

	return AT24MAC_READ_SUCCESS;
}

/**
 * \brief Write data to the specified page in AT24MACXX.
 *
 * \param u32_page_address  The page number.
 * \param u32_page_size The size of the page (which varies with the chips).
 * \param p_wr_buffer Pointer to array where the bytes to be written are stored.
 *
 * \return AT24MAC_WRITE_SUCCESS if the page was written, AT24MAC_WRITE_FAIL
 * otherwise.
 */
uint32_t at24macxx_write_page(uint32_t u32_page_address,
		uint32_t u32_page_size, uint8_t const *p_wr_buffer)
{
	twihs_package_t twihs_package;
	uint32_t start_address = (u32_page_address * u32_page_size) & 0xFFFF;

	/* Configure the data packet to be transmitted */
	twihs_package.chip = BOARD_AT24MAC_ADDRESS;
	at24mac_build_word_address(twihs_package.addr, start_address);
	twihs_package.addr_length = AT24MAC_MEM_ADDR_LEN;
	twihs_package.buffer = (uint8_t *)p_wr_buffer;
	twihs_package.length = u32_page_size;

	if (twihs_master_write(BOARD_AT24MAC_TWIHS_INSTANCE, &twihs_package) !=
	TWIHS_SUCCESS) {
		return AT24MAC_WRITE_FAIL;
	}
	at24macxx_acknowledge_polling(&twihs_package);

	return AT24MAC_WRITE_SUCCESS;
}

/**
 * \brief Read data from the specified page in AT24MACXX.
 *
 * \param u32_page_address  The page number.
 * \param u32_page_size The size of the page (which varies with the chips).
 * \param p_rd_buffer Pointer to array where the bytes read are to be stored.
 *
 * \return AT24MAC_READ_SUCCESS if the page was read, AT24MAC_READ_FAIL otherwise.
 */
uint32_t at24macxx_read_page(uint32_t u32_page_address,
		uint32_t u32_page_size, uint8_t *p_rd_buffer)
{
	twihs_package_t twihs_package;
	uint32_t start_address = (u32_page_address * u32_page_size) & 0xFFFF;

	/* Configure the data packet to be received */
	twihs_package.chip = BOARD_AT24MAC_ADDRESS;
	at24mac_build_word_address(twihs_package.addr, start_address);
	twihs_package.addr_length = AT24MAC_MEM_ADDR_LEN;
	twihs_package.buffer = p_rd_buffer;
	twihs_package.length = u32_page_size;

	if (twihs_master_read(BOARD_AT24MAC_TWIHS_INSTANCE, &twihs_package) !=
			TWIHS_SUCCESS) {
		return AT24MAC_READ_FAIL;
	}

	return AT24MAC_READ_SUCCESS;
}

/**
 * \brief Fill the specified pattern to AT24MACXX.
 *
 * \param u32_start_address  The first address to be filled.
 * \param u32_end_address  The last address to be filled.
 * \param u8_pattern  The pattern to be filled.
 *
 * \return AT24MAC_WRITE_SUCCESS if the pattern was filled, AT24MAC_WRITE_FAIL
 * otherwise.
 */
uint32_t at24macxx_fill_pattern(uint32_t u32_start_address,
		uint32_t u32_end_address, uint8_t u8_pattern)
{
	uint32_t addr;

	for (addr = u32_start_address; addr < u32_end_address + 1; addr++) {
		if (at24macxx_write_byte((uint16_t)addr, u8_pattern) !=
				AT24MAC_WRITE_SUCCESS) {
			printf("addr = %d\n", addr);
			return AT24MAC_WRITE_FAIL;
		}
	}

	return AT24MAC_WRITE_SUCCESS;
}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \}
 */
