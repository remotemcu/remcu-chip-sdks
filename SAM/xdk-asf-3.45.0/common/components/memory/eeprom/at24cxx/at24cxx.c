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

/**
 * \defgroup common_components_memory_eeprom_at24cxx_group EEPROM AT24Cxx Series
 *
 * Low-level driver for the AT24CXX Series EEPROM controller. This driver provides access to the main
 * features of the AT24CXX Series EEPROM.
 *
 * \{
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "at24cxx.h"
#include "ioport.h"
#include "delay.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

#ifndef AT24C_MEM_ADDR_LEN
#  error Please define AT24C_MEM_ADDR_LEN according to the using AT24C
#else
#  if AT24C_MEM_ADDR_LEN>3
#    error AT24C_MEM_ADDR_LEN over 3 not supported
#  elif AT24C_MEM_ADDR_LEN>2
#    define at24c_build_word_address(p_u8, addr) \
	do {\
		p_u8[0] = (uint8_t)(addr >> 16);\
		p_u8[1] = (uint8_t)(addr >>  8);\
		p_u8[2] = (uint8_t)(addr >>> 0);\
	} while (0)
#  elif AT24C_MEM_ADDR_LEN>1
#    define at24c_build_word_address(p_u8, addr) \
	do {\
		p_u8[0] = (uint8_t)(addr >> 8);\
		p_u8[1] = (uint8_t)(addr >> 0);\
	} while (0)
#  else /* 1 */
#    define at24c_build_word_address(p_u8, addr) \
	do {\
		p_u8[0] = (uint8_t)(addr >> 0);\
	} while (0)
#  endif
#endif /* AT24C_MEM_ADDR_LEN */

/**
 * \brief Poll the acknowledge from AT24CXX.
 *
 * \param twi_package Pointer to TWI data package. Only the slave address is
 * used in the acknowledge polling.
 */
static void at24cxx_acknowledge_polling(twi_package_t *twi_package)
{
	uint8_t data = 0;

	/* Store the package parameters */
	uint8_t addr = twi_package->addr[0];
	uint32_t addr_length = twi_package->addr_length;
	void *buffer = twi_package->buffer;
	uint32_t length = twi_package->length;

	/* Configure the data packet to be transmitted */
	twi_package->addr[0] = 0;
	twi_package->addr_length = 0;
	twi_package->buffer = &data;
	twi_package->length = 1;

	while (twi_master_write(BOARD_AT24C_TWI_INSTANCE, twi_package) !=
		TWI_SUCCESS);

	/* Restore the package parameters */
	twi_package->addr[0] = addr;
	twi_package->addr_length = addr_length;
	twi_package->buffer = buffer;
	twi_package->length = length;
}

/**
 * \brief Reset AT24CXX.
 *
 * Send 9 clock cycles to reset memory state.
 *
 * \note IO mode is used in this function, so it can be used even if TWI is not
 *       enabled.
 */
void at24cxx_reset(void)
{
	uint32_t i;
	/* MEM reset
	 * a) Clock up to 9 cycles (use 100K)
	 * b) look for SDA high in each cycle while SCL is high and then
	 * c) Create a start condition as SDA is high
	 */
	/* - Enable pin output mode */
	ioport_set_pin_dir(BOARD_CLK_TWI_EEPROM, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(BOARD_CLK_TWI_EEPROM, 1);
	ioport_enable_pin(BOARD_CLK_TWI_EEPROM);
	for (i = 0; i < 10; i ++) {
		delay_us(5);
		ioport_set_pin_level(BOARD_CLK_TWI_EEPROM, 0);
		delay_us(5);
		ioport_set_pin_level(BOARD_CLK_TWI_EEPROM, 1);
	}
	/* - Restore pin peripheral mode */
	ioport_set_pin_mode(BOARD_CLK_TWI_EEPROM, BOARD_CLK_TWI_MUX_EEPROM);
	ioport_disable_pin(BOARD_CLK_TWI_EEPROM);
	/* - Start condition will do on R/W start */
}

/**
 * \brief Write single byte to AT24CXX.
 *
 * \param u32_address Address of the byte to write.
 * \param u8_value Value that will be written to the specified address.
 *
 * \return AT24C_WRITE_SUCCESS if single byte was written, AT24C_WRITE_FAIL
 * otherwise.
 */
uint32_t at24cxx_write_byte(uint32_t u32_address, uint8_t u8_value)
{
	twi_package_t twi_package;

	/* Configure the data packet to be transmitted */
	twi_package.chip = BOARD_AT24C_ADDRESS;
	at24c_build_word_address(twi_package.addr, u32_address);
	twi_package.addr_length = AT24C_MEM_ADDR_LEN;
	twi_package.buffer = &u8_value;
	twi_package.length = 1;

	if (twi_master_write(BOARD_AT24C_TWI_INSTANCE, &twi_package) !=
			TWI_SUCCESS) {
		return AT24C_WRITE_FAIL;
	}
	at24cxx_acknowledge_polling(&twi_package);

	return AT24C_WRITE_SUCCESS;
}

/**
 * \brief Write multiple bytes continuously to AT24CXX.
 *
 * \param u32_start_address Address of the first byte in transaction.
 * \param u16_length Number of bytes to write.
 * \param p_wr_buffer Pointer to array where the bytes to be written are stored.
 *
 * \return AT24C_WRITE_SUCCESS if single byte was written, AT24C_WRITE_FAIL
 * otherwise.
 */
uint32_t at24cxx_write_continuous(uint32_t u32_start_address,
		uint16_t u16_length, uint8_t const *p_wr_buffer)
{
	twi_package_t twi_package;

	/* Configure the data packet to be transmitted */
	twi_package.chip = BOARD_AT24C_ADDRESS;
	at24c_build_word_address(twi_package.addr, u32_start_address);
	twi_package.addr_length = AT24C_MEM_ADDR_LEN;
	twi_package.buffer = (uint8_t *) p_wr_buffer;
	twi_package.length = u16_length;

	if (twi_master_write(BOARD_AT24C_TWI_INSTANCE, &twi_package) !=
			TWI_SUCCESS) {
		return AT24C_WRITE_FAIL;
	}
	at24cxx_acknowledge_polling(&twi_package);

	return AT24C_WRITE_SUCCESS;
}

/**
 * \brief Read single byte from AT24CXX.
 *
 * \param u32_address Address of the byte to read.
 * \param p_rd_byte Pointer to memory where the read byte will be stored.
 *
 * \return AT24C_READ_SUCCESS if one byte was read, AT24C_READ_FAIL otherwise.
 */
uint32_t at24cxx_read_byte(uint32_t u32_address, uint8_t *p_rd_byte)
{
	twi_package_t twi_package;

	/* Configure the data packet to be received */
	twi_package.chip = BOARD_AT24C_ADDRESS;
	at24c_build_word_address(twi_package.addr, u32_address);
	twi_package.addr_length = AT24C_MEM_ADDR_LEN;
	twi_package.buffer = p_rd_byte;
	twi_package.length = 1;

	if (twi_master_read(BOARD_AT24C_TWI_INSTANCE, &twi_package) !=
			TWI_SUCCESS) {
		return AT24C_READ_FAIL;
	}

	return AT24C_READ_SUCCESS;
}

/**
 * \brief Read multiple bytes continuously from AT24CXX.
 *
 * \param u32_start_address Address of the first byte to read.
 * \param u16_length Number of bytes to read.
 * \param p_rd_buffer Pointer to memory where the read bytes will be stored.
 *
 * \return AT24C_READ_SUCCESS if one byte was read, AT24C_READ_FAIL otherwise.
 */
uint32_t at24cxx_read_continuous(uint32_t u32_start_address,
		uint16_t u16_length, uint8_t *p_rd_buffer)
{
	twi_package_t twi_package;

	/* Configure the data packet to be received */
	twi_package.chip = BOARD_AT24C_ADDRESS;
	at24c_build_word_address(twi_package.addr, u32_start_address);
	twi_package.addr_length = AT24C_MEM_ADDR_LEN;
	twi_package.buffer = p_rd_buffer;
	twi_package.length = u16_length;

	if (twi_master_read(BOARD_AT24C_TWI_INSTANCE, &twi_package) !=
			TWI_SUCCESS) {
		return AT24C_READ_FAIL;
	}

	return AT24C_READ_SUCCESS;
}

/**
 * \brief Write data to the specified page in AT24CXX.
 *
 * \param u32_page_address  The page number.
 * \param u32_page_size The size of the page (which varies with the chips).
 * \param p_wr_buffer Pointer to array where the bytes to be written are stored.
 *
 * \return AT24C_WRITE_SUCCESS if the page was written, AT24C_WRITE_FAIL
 * otherwise.
 */
uint32_t at24cxx_write_page(uint32_t u32_page_address,
		uint32_t u32_page_size, uint8_t const *p_wr_buffer)
{
	twi_package_t twi_package;
	uint32_t start_address = (u32_page_address * u32_page_size) & 0xFFFF;

	/* Configure the data packet to be transmitted */
	twi_package.chip = BOARD_AT24C_ADDRESS;
	at24c_build_word_address(twi_package.addr, start_address);
	twi_package.addr_length = AT24C_MEM_ADDR_LEN;
	twi_package.buffer = (uint8_t *)p_wr_buffer;
	twi_package.length = u32_page_size;

	if (twi_master_write(BOARD_AT24C_TWI_INSTANCE, &twi_package) !=
			TWI_SUCCESS) {
		return AT24C_WRITE_FAIL;
	}
	at24cxx_acknowledge_polling(&twi_package);

	return AT24C_WRITE_SUCCESS;
}

/**
 * \brief Read data from the specified page in AT24CXX.
 *
 * \param u32_page_address  The page number.
 * \param u32_page_size The size of the page (which varies with the chips).
 * \param p_rd_buffer Pointer to array where the bytes read are to be stored.
 *
 * \return AT24C_READ_SUCCESS if the page was read, AT24C_READ_FAIL otherwise.
 */
uint32_t at24cxx_read_page(uint32_t u32_page_address,
		uint32_t u32_page_size, uint8_t *p_rd_buffer)
{
	twi_package_t twi_package;
	uint32_t start_address = (u32_page_address * u32_page_size) & 0xFFFF;

	/* Configure the data packet to be received */
	twi_package.chip = BOARD_AT24C_ADDRESS;
	at24c_build_word_address(twi_package.addr, start_address);
	twi_package.addr_length = AT24C_MEM_ADDR_LEN;
	twi_package.buffer = p_rd_buffer;
	twi_package.length = u32_page_size;

	if (twi_master_read(BOARD_AT24C_TWI_INSTANCE, &twi_package) !=
			TWI_SUCCESS) {
		return AT24C_READ_FAIL;
	}

	return AT24C_READ_SUCCESS;
}

/**
 * \brief Fill the specified pattern to AT24CXX.
 *
 * \param u32_start_address  The first address to be filled.
 * \param u32_end_address  The last address to be filled.
 * \param u8_pattern  The pattern to be filled.
 *
 * \return AT24C_WRITE_SUCCESS if the pattern was filled, AT24C_WRITE_FAIL
 * otherwise.
 */
uint32_t at24cxx_fill_pattern(uint32_t u32_start_address,
		uint32_t u32_end_address, uint8_t u8_pattern)
{
	uint32_t addr;

	for (addr = u32_start_address; addr < u32_end_address + 1; addr++) {
		if (at24cxx_write_byte((uint16_t)addr, u8_pattern) !=
				AT24C_WRITE_SUCCESS) {
			return AT24C_WRITE_FAIL;
		}
	}

	return AT24C_WRITE_SUCCESS;
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
