/**
 * \file
 *
 * \brief SAM SPI Flash Driver for SAMB11
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
#include "spi_flash.h"

/**
 *  \brief SPI flash write enable.
 *
 * Enable SPI flash write
 */
static void spi_flash_write_enable(void)
{
	SPI_FLASH0->READ_CTRL.reg = SPI_FLASH_READ_CTRL_RDATA_COUNT(0);
	SPI_FLASH0->CMD_BUFFER0.reg = SPI_FLASH_CMD_WRITE_ENABLE;
	SPI_FLASH0->DIRECTION.reg = SPI_FLASH_DIRECTION_CMD;
	SPI_FLASH0->DMA_START_ADDRESS.reg = SPI_FLASH_DMA_START_ADDRESS_RESETVALUE;

	SPI_FLASH0->TRANSACTION_CTRL.reg = \
			SPI_FLASH_TRANSACTION_CTRL_FLASH_TRANS_START | \
			SPI_FLASH_TRANSACTION_CTRL_CMD_COUNT(0x01);

	while (SPI_FLASH0->IRQ_STATUS.bit.FLASH_TRANS_DONE != \
			SPI_FLASH_IRQ_STATUS_FLASH_TRANS_DONE) {
		/* Wait for current flash transaction done. */
	}
}

/**
 *  \brief SPI flash write disable.
 *
 * Disable SPI flash write
 */
static void spi_flash_write_disable(void)
{
	SPI_FLASH0->READ_CTRL.reg = SPI_FLASH_READ_CTRL_RDATA_COUNT(0);
	SPI_FLASH0->CMD_BUFFER0.reg = SPI_FLASH_CMD_WRITE_DISABLE;
	SPI_FLASH0->DIRECTION.reg = SPI_FLASH_DIRECTION_CMD;
	SPI_FLASH0->DMA_START_ADDRESS.reg = SPI_FLASH_DMA_START_ADDRESS_MASK;

	SPI_FLASH0->TRANSACTION_CTRL.reg = \
			SPI_FLASH_TRANSACTION_CTRL_FLASH_TRANS_START | \
			SPI_FLASH_TRANSACTION_CTRL_CMD_COUNT(0x01);

	while (SPI_FLASH0->IRQ_STATUS.bit.FLASH_TRANS_DONE != \
			SPI_FLASH_IRQ_STATUS_FLASH_TRANS_DONE) {
		/* Wait for current flash transaction done. */
	}
}

/**
 *  \brief SPI flash read status register.
 *
 * Read SPI flash status
 *
 * \return Status register value.
 */
static uint8_t spi_flash_read_status_reg(void)
{
	volatile uint32_t status_value;

	SPI_FLASH0->READ_CTRL.reg = SPI_FLASH_READ_CTRL_RDATA_COUNT(0x01);
	SPI_FLASH0->CMD_BUFFER0.reg = SPI_FLASH_CMD_READ_STATUS;
	SPI_FLASH0->DIRECTION.reg = SPI_FLASH_DIRECTION_CMD;
	SPI_FLASH0->DMA_START_ADDRESS.reg = (uint32_t)&status_value;

	SPI_FLASH0->TRANSACTION_CTRL.reg = \
			SPI_FLASH_TRANSACTION_CTRL_FLASH_TRANS_START | \
			SPI_FLASH_TRANSACTION_CTRL_CMD_COUNT(0x01);

	while (SPI_FLASH0->IRQ_STATUS.bit.FLASH_TRANS_DONE != \
			SPI_FLASH_IRQ_STATUS_FLASH_TRANS_DONE) {
		/* Wait for current flash transaction done. */
	}

	return (status_value & 0xFF);
}

/**
 * \brief Program SPI Flash page
 *
 * Program SPI Flash page
 *
 * \param[in]  memory_addr    Start address of memory
 * \param[in]  flash_addr     Start address of the spi flash
 * \param[in]  size           Number of bytes to be programmed to flash
 */
static void spi_flash_page_program(uint32_t flash_addr, uint32_t memory_addr, uint16_t size)
{
	unsigned char cmd[8];
	volatile uint32_t opt_delay = 0;

	spi_flash_write_enable();

	cmd[0] = SPI_FLASH_CMD_PAGE_PROGRAM;
	cmd[1] = (unsigned char) (flash_addr >> 16);
	cmd[2] = (unsigned char) (flash_addr >> 8);
	cmd[3] = (unsigned char) (flash_addr);

	SPI_FLASH0->READ_CTRL.reg = SPI_FLASH_READ_CTRL_RDATA_COUNT(0x0);
	SPI_FLASH0->CMD_BUFFER0.reg = cmd[0] | (cmd[1] << 8) | (cmd[2] << 16) | (cmd[3] << 24);
	SPI_FLASH0->DIRECTION.reg = SPI_FLASH_DIRECTION_PRO;
	SPI_FLASH0->DMA_START_ADDRESS.reg = memory_addr;

	SPI_FLASH0->TRANSACTION_CTRL.reg = \
			SPI_FLASH_TRANSACTION_CTRL_FLASH_TRANS_START | \
			SPI_FLASH_TRANSACTION_CTRL_CMD_COUNT(0x04) | \
			SPI_FLASH_TRANSACTION_CTRL_WDATA_COUNT(size);

	while (SPI_FLASH0->IRQ_STATUS.bit.FLASH_TRANS_DONE != \
			SPI_FLASH_IRQ_STATUS_FLASH_TRANS_DONE) {
		/* Wait for current flash transaction done. */
	}

	/* add additional read_status_reg before the while this gives the flash
	 * memory time to update the registers.
	 */
	for(uint16_t i = 0; i < 0xFFFF; i++) {
		/* Waiting... */
		opt_delay++;
	}
	//spi_flash_read_status_reg();
	while(spi_flash_read_status_reg() & 0x01);
	spi_flash_write_disable();
	(void)(opt_delay);
}

/**
 * \brief Initializes the SPI Flash module
 *
 * Initializes the SPI Flash module
 */
void spi_flash_init(void)
{
	/* PINMUX init */
	LPMCU_MISC_REGS0->PINMUX_SEL_3.reg = \
							LPMCU_MISC_REGS_PINMUX_SEL_3_LP_SIP_0_SEL_SPI_FLASH0_SCK | \
							LPMCU_MISC_REGS_PINMUX_SEL_3_LP_SIP_1_SEL_SPI_FLASH0_TXD | \
							LPMCU_MISC_REGS_PINMUX_SEL_3_LP_SIP_2_SEL_SPI_FLASH0_SSN | \
							LPMCU_MISC_REGS_PINMUX_SEL_3_LP_SIP_3_SEL_SPI_FLASH0_RXD;

	SPI_FLASH0->MODE_CTRL.reg = SPI_FLASH_MODE_CTRL_RESETVALUE;
	spi_flash_leave_low_power_mode();
}

/**
 * \brief Read SPI Flash Chip ID
 *
 * Reads SPI Flash Chip ID
 */
uint32_t spi_flash_rdid(void)
{
	volatile uint32_t register_value;

	SPI_FLASH0->READ_CTRL.reg = SPI_FLASH_READ_CTRL_RDATA_COUNT(0x04);
	SPI_FLASH0->CMD_BUFFER0.reg = SPI_FLASH_CMD_READ_ID;
	SPI_FLASH0->DIRECTION.reg = SPI_FLASH_DIRECTION_CMD;
	SPI_FLASH0->DMA_START_ADDRESS.reg = (uint32_t)&register_value;

	SPI_FLASH0->TRANSACTION_CTRL.reg = \
			SPI_FLASH_TRANSACTION_CTRL_FLASH_TRANS_START | \
			SPI_FLASH_TRANSACTION_CTRL_CMD_COUNT(0x01);

	while (SPI_FLASH0->IRQ_STATUS.bit.FLASH_TRANS_DONE != \
			SPI_FLASH_IRQ_STATUS_FLASH_TRANS_DONE) {
		/* Wait for current flash transaction done. */
	}

	return (register_value);
}

/**
 * \brief Read SPI Flash memory
 *
 * Reads SPI Flash memory with up to page size (256 bytes) length
 * \param[in]  read_buf    Pointer to buffer to read into
 * \param[in]  flash_addr  Flash memory address to read from
 * \param[in]  size        Data length to be read, must be less than or equal to FLASH_PAGE_SIZE
 */
void spi_flash_read(uint8_t *read_buf, uint32_t flash_addr, uint32_t size)
{
	uint8_t   cmd[8] = {0, };
	uint32_t  memory_addr;
	uint32_t  i=0;
	uint8_t   *data = read_buf;
	volatile uint32_t opt_delay = 0;

	/* Get the destination buffer Address. */
	if((flash_addr + size) > FLASH_MEMORY_SIZE) {
		for(i=0; i < size; i++) {
			data[i] = 0;
		}
	}

	memory_addr = (unsigned long)read_buf;

	/* Perform read operation. */
	cmd[0] = SPI_FLASH_CMD_READ_HIGH_SPEED;
	cmd[1] = (unsigned char) (flash_addr >> 16);
	cmd[2] = (unsigned char) (flash_addr >> 8);
	cmd[3] = (unsigned char) (flash_addr);
	cmd[4] = 0xA5;

	SPI_FLASH0->READ_CTRL.reg = SPI_FLASH_READ_CTRL_RDATA_COUNT(size);
	SPI_FLASH0->CMD_BUFFER0.reg = cmd[0] | (cmd[1] << 8) | (cmd[2] << 16) | (cmd[3] << 24);
	SPI_FLASH0->CMD_BUFFER1.reg = cmd[4];
	SPI_FLASH0->DIRECTION.reg = SPI_FLASH_DIRECTION_READ;
	SPI_FLASH0->DMA_START_ADDRESS.reg = memory_addr;

	SPI_FLASH0->TRANSACTION_CTRL.reg = \
			SPI_FLASH_TRANSACTION_CTRL_FLASH_TRANS_START | \
			SPI_FLASH_TRANSACTION_CTRL_CMD_COUNT(0x05);

	for (i = 0; i < 0xFF; i++) {
		/* Waiting...*/
		opt_delay++;
	}
	(void)(opt_delay);
	while ((SPI_FLASH0->IRQ_STATUS.bit.FLASH_TRANS_DONE != \
			SPI_FLASH_IRQ_STATUS_FLASH_TRANS_DONE) && \
			(spi_flash_read_status_reg() & 0x01)){
		/* Wait for current flash transaction done. */
	}
}

/**
 * \brief Write SPI Flash memory
 *
 * Writes SPI Flash memory with up to page size (256 bytes) length
 * \param[in]  write_buf    Pointer to buffer to write from
 * \param[in]  flash_addr   Flash memory address to write to
 * \param[in]  size         Data length to be written, must be less than or
 *                          equal to FLASH_PAGE_SIZE
 */
int8_t spi_flash_write(void *write_buf, uint32_t flash_addr, uint32_t size)
{
	int8_t      ret = -1;
	uint32_t    write_size;
	uint32_t    offset;
	uint32_t    memory_addr;
	volatile uint32_t opt_delay = 0;

	for (uint32_t i = 0; i < 0x1FFFF; i++) {
		/* Waiting...*/
		opt_delay++;
	}
	if((write_buf != NULL) && (size != 0)) {
		/* Ensure the write size does not exceed the flash limit. */
		if((flash_addr + size) <= FLASH_MEMORY_SIZE) {
			/* Get the destination buffer Address. */
			memory_addr = (unsigned long)write_buf;
			/* Perform read operation. */
			offset = flash_addr % FLASH_PAGE_SIZE;

			/* First part of data in the address page. */
			if (offset) {
				write_size = FLASH_PAGE_SIZE - offset;
				spi_flash_page_program(flash_addr, memory_addr, min(size, write_size));
				if (size < write_size) {
					ret = 0;
					goto EXIT;
				}
				memory_addr += write_size;
				flash_addr += write_size;
				size -= write_size;
			}
			do {
				write_size = min(size, FLASH_PAGE_SIZE);

				/* Write complete page or the remaining data. */
				spi_flash_page_program(flash_addr, memory_addr, write_size);
				memory_addr += write_size;
				flash_addr += write_size;
				size -= write_size;
			} while (size > 0);
			ret = 0;
		}
	}
	(void)(opt_delay);
	EXIT:
	return ret;
}

/**
 * \brief Erase SPI Flash sector
 *
 * Erases SPI Flash Sector
 * \param[in]  flash_addr  Flash memory address within the sector to erase
 */
void spi_flash_sector_erase(uint32_t flash_addr)
{
	uint8_t cmd[8] = {0,};
	uint32_t  i=0;
	volatile uint32_t opt_delay = 0;

	cmd[0] = SPI_FLASH_CMD_SECTOR_ERASE;
	cmd[1] = (char)(flash_addr >> 16);
	cmd[2] = (char)(flash_addr >> 8);
	cmd[3] = (char)(flash_addr);

	spi_flash_write_enable();
	spi_flash_read_status_reg();

	SPI_FLASH0->READ_CTRL.reg = SPI_FLASH_READ_CTRL_RDATA_COUNT(0x0);
	SPI_FLASH0->CMD_BUFFER0.reg = cmd[0] | (cmd[1] << 8) | (cmd[2] << 16) | (cmd[3] << 24);
	SPI_FLASH0->DIRECTION.reg = SPI_FLASH_DIRECTION_PRO;
	SPI_FLASH0->DMA_START_ADDRESS.reg = 0x0;

	SPI_FLASH0->TRANSACTION_CTRL.reg = \
			SPI_FLASH_TRANSACTION_CTRL_FLASH_TRANS_START | \
			SPI_FLASH_TRANSACTION_CTRL_CMD_COUNT(0x04);

	for (i = 0; i < 0xFF; i++) {
		/* Waiting...*/
		opt_delay++;
	}

	while ((SPI_FLASH0->IRQ_STATUS.bit.FLASH_TRANS_DONE != \
			SPI_FLASH_IRQ_STATUS_FLASH_TRANS_DONE) && \
			(spi_flash_read_status_reg() & 0x01)){
		/* Wait for current flash transaction done. */
	}
	(void)(opt_delay);
}

/**
 * \brief Erase SPI Flash sector
 *
 * Erases SPI Flash Sector
 * \param[in]  start_offset   Start address of the spi flash
 * \param[in]  size           Size of the spi flash
 *
 * \retval 1    Address over spi flash memory size
 * \retval 0    Operation complete
 */
unsigned char spi_flash_erase(uint32_t start_offset, uint32_t size)
{
    unsigned long end_offset = start_offset + size;


    /* Check address overflow */
    if (end_offset > FLASH_MEMORY_SIZE) {
        return 1;
    }

    /* Align to previous sector boundary */
    start_offset = start_offset & FLASH_SECT_MASK;

    /* Erase next sectors */
    spi_flash_write_enable();
    while(start_offset < end_offset) {
			spi_flash_sector_erase(start_offset);
			while(spi_flash_read_status_reg() & 0x01) {
				/* Waiting. */
			}
			start_offset += FLASH_SECTOR_SIZE;
    }

	spi_flash_write_disable();

    return 0;
}

/**
 * \brief Enter SPI Flash low power mode
 *
 * Enter SPI Flash low power mode
 */
void spi_flash_enter_low_power_mode(void)
{
	SPI_FLASH0->READ_CTRL.reg = SPI_FLASH_READ_CTRL_RDATA_COUNT(0x0);
	SPI_FLASH0->CMD_BUFFER0.reg = SPI_FLASH_CMD_ENTER_LOW_POWER;
	SPI_FLASH0->DIRECTION.reg = SPI_FLASH_DIRECTION_CMD;
	SPI_FLASH0->DMA_START_ADDRESS.reg = 0x0;

	SPI_FLASH0->TRANSACTION_CTRL.reg = \
			SPI_FLASH_TRANSACTION_CTRL_FLASH_TRANS_START | \
			SPI_FLASH_TRANSACTION_CTRL_CMD_COUNT(0x01);

	while (SPI_FLASH0->IRQ_STATUS.bit.FLASH_TRANS_DONE != \
			SPI_FLASH_IRQ_STATUS_FLASH_TRANS_DONE) {
		/* Wait for current flash transaction done. */
	}
}

/**
 * \brief Exit SPI Flash Low power mode
 *
 * Exit SPI Flash Low power mode
 */
void spi_flash_leave_low_power_mode(void)
{
	SPI_FLASH0->READ_CTRL.reg = SPI_FLASH_READ_CTRL_RDATA_COUNT(0x0);
	SPI_FLASH0->CMD_BUFFER0.reg = SPI_FLASH_CMD_LEAVE_LOW_POWER;
	SPI_FLASH0->DIRECTION.reg = SPI_FLASH_DIRECTION_CMD;
	SPI_FLASH0->DMA_START_ADDRESS.reg = 0x0;

	SPI_FLASH0->TRANSACTION_CTRL.reg = \
			SPI_FLASH_TRANSACTION_CTRL_FLASH_TRANS_START | \
			SPI_FLASH_TRANSACTION_CTRL_CMD_COUNT(0x01);

	while (SPI_FLASH0->IRQ_STATUS.bit.FLASH_TRANS_DONE != \
			SPI_FLASH_IRQ_STATUS_FLASH_TRANS_DONE) {
		/* Wait for current flash transaction done. */
	}
}

/**
 * \brief Initializes the SPI Flash module
 */
void spi_flash_clock_init(void)
{	
	/* Reset SPI_Flash */
	system_peripheral_reset(PERIPHERAL_SPI_FLASH);
	system_peripheral_reset(PERIPHERAL_SPI_FLASH_IF);
	/* SPI_Flash core clock enable */
	system_clock_peripheral_enable(PERIPHERAL_SPI_FLASH);
	/* change clock speed */
	system_clock_peripheral_freq_config(PERIPHERAL_SPI_FLASH, CLOCK_FREQ_13_MHZ);
}

/**
 * \brief Turns off the supply to SPI_Flash Core
 *
 * This functions turns off the supply to SPI_Flash core.
 * Since SPI_Flash won't be used on every wakeup it is safe to disable
 * the power to SPI_Flash core and enable it when required.
 *
 */
void spi_flash_turn_off(void)
{
	LPMCU_MISC_REGS0->PULL_ENABLE.reg &= ~LPMCU_MISC_REGS_PULL_ENABLE_LP_SIP__Msk;
	
	LPMCU_MISC_REGS0->SPIFLASH_VDDIO_CTRL.reg = 0x0;
}

/**
 * \brief Turns on the supply to SPI_Flash Core
 *
 * This functions turns on the supply to SPI_Flash core.
 *
 */
void spi_flash_turn_on(void)
{
	LPMCU_MISC_REGS0->PULL_ENABLE.reg |= LPMCU_MISC_REGS_PULL_ENABLE_LP_SIP__Msk;
	
	LPMCU_MISC_REGS0->SPIFLASH_VDDIO_CTRL.reg = LPMCU_MISC_REGS_SPIFLASH_VDDIO_CTRL_ENABLE;
}