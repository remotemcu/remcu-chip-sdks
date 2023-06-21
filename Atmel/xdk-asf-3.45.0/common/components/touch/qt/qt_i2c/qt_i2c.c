/**
 * \file
 *
 * \brief QTouch component driver with I2C interface.
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

#include "qt_i2c.h"
#include "delay.h"
#include "ioport.h"

/**
 * \ingroup qt_device_i2c_group
 *
 * @{
 */

/** Timeout for communication with QTouch device  */
#define QT_COMM_TIMEOUT       10000

/** Delay between two continue I2C read or write operation in microsecond */
#define QT_CONTINUE_RW_DELAY  50

/**
 * \brief Perform a hardware reset of the QT device.
 *
 * \note If RESET pin is defined, it will perform a hardware reset,
 *       Otherwise it will do nothing.
 */
void qt_hardware_reset(void)
{
#ifdef BOARD_QT_RESET_PIN_IDX
	/* Pull the reset pin low */
	ioport_set_pin_level(QT_RESET_PIN_IDX, IOPORT_PIN_LEVEL_LOW);

	/* The reset pin must be low at least 10us to cause a reset */
	delay_us(15);

	/* Pull line back to high to resume normal operation */
	ioport_set_pin_level(QT_RESET_PIN_IDX, IOPORT_PIN_LEVEL_HIGH);
#endif
}

/**
 * \brief Check communication is ready and able to read Chip ID.
 *
 * \retval STATUS_OK  If communication is ready.
 * \retval ERR_IO_ERROR If communication failed with the device.
 * \retval ERR_UNSUPPORTED_DEV If the device is not supported.
 */
enum status_code qt_get_comm_ready(void)
{
	enum status_code ret;
	uint8_t chip_id = 0;
	volatile uint32_t timeout = QT_COMM_TIMEOUT;

	/* Read chip ID */
	do {
		ret = qt_read_regs(QT_REG_CHIP_ID, &chip_id, sizeof(uint8_t));
		timeout--;
		if (timeout == 0) {
			return ERR_IO_ERROR;
		}
	} while (ret != STATUS_OK);

	/* Check that the responding device is a intended device */
	if (chip_id != QT_DEVICE_ID) {
		return ERR_UNSUPPORTED_DEV;
	} else {
		return STATUS_OK;
	}
}

/**
 * \brief Read entire setup block from QT device.
 *
 * \param setup_block Pointer to setup block buffer for read.
 *
 * \retval STATUS_OK  If read successful.
 * \retval ERR_IO_ERROR If communication failed with the device.
 */
enum status_code qt_read_setup_block(struct qt_setup_block *setup_block)
{
	return (qt_read_regs(QT_SETUPS_BLOCK_ADDR, (uint8_t *)setup_block,
			sizeof(struct qt_setup_block)));
}

/**
 * \brief Write entire setup block to QT device.
 *
 * \param setup_block Pointer to setup block buffer for write.
 *
 * \retval STATUS_OK  If write successful.
 * \retval ERR_IO_ERROR If communication failed with the device.
 */
enum status_code qt_write_setup_block(struct qt_setup_block *setup_block)
{
	return (qt_write_regs(QT_SETUPS_BLOCK_ADDR, (uint8_t *)setup_block,
			sizeof(struct qt_setup_block)));
}

/**
 * \brief Get all status from QT device.
 *
 * \param qt_status Pointer to QT status buffer for read.
 *
 * \retval STATUS_OK  If read successful.
 * \retval ERR_IO_ERROR If communication failed with the device.
 */
enum status_code qt_get_status(struct qt_status *qt_status)
{
	return (qt_read_regs(QT_REG_GENERAL_STATUS, (uint8_t *)qt_status,
			sizeof(struct qt_status)));
}

/**
 * \brief Check if the CHANGE line is low level.
 *
 * \retval true  The CHANGE line is low level.
 * \retval false The CHANGE line is high level.
 */
bool qt_is_change_line_low(void)
{
#ifdef BOARD_QT_CHANGE_PIN_IDX
	if (ioport_get_pin_level(BOARD_QT_CHANGE_PIN_IDX)) {
		return false;
	} else {
		return true;
	}
#else
#warning The CHANGE pin is not defined. This function is not available.
#endif
}

/**
 * \brief Read registers content from QT device.
 *
 * \param reg_addr    Start register address.
 * \param read_buffer Pointer to byte array for read data.
 * \param length      Read data length.
 *
 * \retval STATUS_OK  If read successful.
 * \retval ERR_IO_ERROR If communication failed with the device.
 */
enum status_code qt_read_regs(uint8_t reg_addr, uint8_t *read_buffer,
		uint8_t length)
{
	/*
	 * Delay between each write or read cycle between TWI Stop and TWI Start.
	 */
	delay_us(QT_CONTINUE_RW_DELAY);

	/*
	 * Write start register address to device
	 */
	twi_package_t packet_wr = {
		.addr_length = 0,             /* TWI slave memory address data size */
		.chip        = BOARD_QT_DEVICE_ADDRESS,/* TWI slave bus address */
		.buffer      = &reg_addr,     /* Transfer data destination buffer */
		.length      = sizeof(uint8_t)/* Transfer data size (bytes) */
	};

	if (twi_master_write(BOARD_QT_TWI_INSTANCE, &packet_wr) != STATUS_OK) {
		return ERR_IO_ERROR;
	}

	/*
	 * Delay between each write or read cycle between TWI Stop and TWI Start.
	 */
	delay_us(QT_CONTINUE_RW_DELAY);

	/*
	 * Read data from Qtouch device register
	 */
	twi_package_t packet_rd = {
		.addr_length = 0,             /* TWI slave memory address data size */
		.chip        = BOARD_QT_DEVICE_ADDRESS,/* TWI slave bus address */
		.buffer      = (void *)read_buffer, /* Transfer data buffer */
		.length      = length         /* Transfer data size (bytes) */
	};

	if (twi_master_read(BOARD_QT_TWI_INSTANCE, &packet_rd) != STATUS_OK) {
		return ERR_IO_ERROR;
	}

	return STATUS_OK;
}

/**
 * \brief Write content to QT device registers.
 *
 * \param reg_addr     Start register address.
 * \param write_buffer Pointer to byte array for write data.
 * \param length       Write data length.
 *
 * \retval STATUS_OK  If write successful.
 * \retval ERR_IO_ERROR If communication failed with the device.
 */
enum status_code qt_write_regs(uint8_t reg_addr, uint8_t *write_buffer,
		uint8_t length)
{
	/*
	 * Delay between each write or read cycle between TWI Stop and TWI Start.
	 */
	delay_us(QT_CONTINUE_RW_DELAY);

	/*
	 * Write data to Qtouch device registers
	 */
	twi_package_t packet_wr = {
		.addr[0]      = reg_addr,       /* TWI slave memory address */
		.addr_length  = sizeof(uint8_t),/* TWI slave memory address data size */
		.chip         = BOARD_QT_DEVICE_ADDRESS, /* TWI slave bus address */
		.buffer       = (void *)write_buffer,/* Transfer data buffer */
		.length       = length          /* Transfer data size (bytes) */
	};

	/* Perform a write access */
	if (twi_master_write(BOARD_QT_TWI_INSTANCE, &packet_wr) != STATUS_OK) {
		return ERR_IO_ERROR;
	}

	return STATUS_OK;
}

/** @} */
