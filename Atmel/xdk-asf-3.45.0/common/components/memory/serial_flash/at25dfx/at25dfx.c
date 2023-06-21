/**
 * \file
 *
 * \brief Management of the AT25DFx SerialFlash driver through SPI.
 * This file manages the accesses to the AT25DFx SerialFlash components.
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

#include "board.h"
#include "status_codes.h"
#include "conf_at25dfx.h"
#include "at25dfx.h"
#include "spi_master.h"
#include "at25dfx_hal_spi.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \defgroup at25dfx_group AT25DFx SerialFlash component driver.
 *
 * See \ref at25dfx_quickstart.
 *
 * This is a driver for the AT25DFx SerialFlash memories.
 * It provides functions for initialization, read and write operations.
 *
 * \section dependencies Dependencies
 * This driver depends on the following modules:
 * - \ref spi_group for SPI master interface.
 *
 * @{
 */

#if AT25DFX_MEM_TYPE == AT25DFX_041A
/** AT25 device ID */
#define AT25DFX_DEV_ID                   0x0001441F
/** AT25 total size */
#define AT25DFX_SIZE                     (512 * 1024)
/** AT25 block size */
#define AT25DFX_BLOCK_SIZE               (64*1024)
/** AT25 block erase command */
#define AT25DFX_BLOCK_ERASE_CMD    AT25_BLOCK_ERASE_64K

#elif AT25DFX_MEM_TYPE == AT25DFX_161
/** AT25 device ID */
#define AT25DFX_DEV_ID                     0x0002461F
/** AT25 total size */
#define AT25DFX_SIZE                       (2 * 1024 * 1024)
/** AT25 block size */
#define AT25DFX_BLOCK_SIZE                 (64 * 1024)
/** AT25 block erase command */
#define AT25DFX_BLOCK_ERASE_CMD    AT25_BLOCK_ERASE_64K

#elif AT25DFX_MEM_TYPE == AT25DFX_081A
/** AT25 device ID */
#define AT25DFX_DEV_ID                     0x0001451F
/** AT25 total size */
#define AT25DFX_SIZE                       (1 * 1024 * 1024)
/** AT25 block size */
#define AT25DFX_BLOCK_SIZE                 (64 * 1024)
/** AT25 block erase command */
#define AT25DFX_BLOCK_ERASE_CMD    AT25_BLOCK_ERASE_64K

#elif AT25DFX_MEM_TYPE == AT25DFX_0161
/** AT25 device ID */
#define AT25DFX_DEV_ID                     0x0000461F
/** AT25 total size */
#define AT25DFX_SIZE                       (2 * 1024 * 1024)
/** AT25 block size */
#define AT25DFX_BLOCK_SIZE                 (64 * 1024)
/** AT25 block erase command */
#define AT25DFX_BLOCK_ERASE_CMD    AT25_BLOCK_ERASE_64K

#elif AT25DFX_MEM_TYPE == AT25DFX_161A
/** AT25 device ID */
#define AT25DFX_DEV_ID                     0x0001461F
/** AT25 total size */
#define AT25DFX_SIZE                       (2 * 1024 * 1024)
/** AT25 block size */
#define AT25DFX_BLOCK_SIZE                 (64 * 1024)
/** AT25 block erase command */
#define AT25DFX_BLOCK_ERASE_CMD    AT25_BLOCK_ERASE_64K

#elif AT25DFX_MEM_TYPE == AT25DFX_321
/** AT25 device ID */
#define AT25DFX_DEV_ID                     0x0000471F
/** AT25 total size */
#define AT25DFX_SIZE                       (4 * 1024 * 1024)
/** AT25 block size */
#define AT25DFX_BLOCK_SIZE                 (64 * 1024)
/** AT25 block erase command */
#define AT25DFX_BLOCK_ERASE_CMD    AT25_BLOCK_ERASE_64K

#elif AT25DFX_MEM_TYPE == AT25DFX_321A
/** AT25 device ID */
#define AT25DFX_DEV_ID                     0x0001471F
/** AT25 total size */
#define AT25DFX_SIZE                       (4 * 1024 * 1024)
/** AT25 block size */
#define AT25DFX_BLOCK_SIZE                 (64 * 1024)
/** AT25 block erase command */
#define AT25DFX_BLOCK_ERASE_CMD    AT25_BLOCK_ERASE_64K

#elif AT25DFX_MEM_TYPE == AT25DFX_512B
/** AT25 device ID */
#define AT25DFX_DEV_ID                     0x0001651F
/** AT25 total size */
#define AT25DFX_SIZE                       (64 * 1024)
/** AT25 block size */
#define AT25DFX_BLOCK_SIZE                 (32 * 1024)
/** AT25 block erase command */
#define AT25DFX_BLOCK_ERASE_CMD    AT25_BLOCK_ERASE_32K

#elif AT25DFX_MEM_TYPE == AT25DFX_021
/** AT25 device ID */
#define AT25DFX_DEV_ID                     0x0000431F
/** AT25 total size */
#define AT25DFX_SIZE                       (256 * 1024)
/** AT25 block size */
#define AT25DFX_BLOCK_SIZE                 (64 * 1024)
/** AT25 block erase command */
#define AT25DFX_BLOCK_ERASE_CMD    AT25_BLOCK_ERASE_64K

#elif AT25DFX_MEM_TYPE == AT25DFX_641A
/** AT25 device ID */
#define AT25DFX_DEV_ID                     0x0000481F
/** AT25 total size */
#define AT25DFX_SIZE                       (8 * 1024 * 1024)
/** AT25 block size */
#define AT25DFX_BLOCK_SIZE                 (64 * 1024)
/** AT25 block erase command */
#define AT25DFX_BLOCK_ERASE_CMD    AT25_BLOCK_ERASE_64K

#else
#error AT25DFX_MEM_TYPE is not defined to a supported value
#endif

/** The page size of AT25DF series is always 256 */
#define AT25DFX_PAGE_SIZE              256

/** SerialFlash transfers request prepared by the AT25 driver. This structure is sent to the 
 at25_send_command function which is application dependent. This function transforms 
 at25_cmd_t request into api command request. */
typedef struct at25_cmd {
	/** Data buffer to be sent or received */
	uint8_t *data;
	/** SerialFlash internal address */
	uint32_t address;
	/** Number of bytes to send/receive */
	uint16_t data_size;
	/** Command byte opcode */
	uint8_t cmd;
	/** Size of command (command byte + address bytes + dummy bytes) in bytes */
	uint8_t cmd_size;
} at25_cmd_t;

/** Activated SerialFlash chip select, default to device 1 */
static uint8_t active_sf_cs = AT25DFX_MEM_ID;

/**
 * \brief Start an AT25DFx command transfer. This is a non blocking function. It will
 *  return as soon as the transfer is started.
 *
 * \param pat25_cmd_t  Pointer to the command transfer request.
 *
 * \return AT25_SUCCESS if the transfer has been started successfully; otherwise return
 * AT25_ERROR_SPI if the driver is in use.
 */
static at25_status_t at25dfx_send_command(at25_cmd_t *at25cmd)
{
	uint32_t cmd_buffer[2];
	status_code_t spi_stat;

	/* Enable Chip select corresponding to the SerialFlash */
	at25dfx_spi_select_device(active_sf_cs);

	/* Store command and address in command buffer */
	cmd_buffer[0] = (at25cmd->cmd & 0x000000FF)
			| ((at25cmd->address & 0x0000FF) << 24)
			| ((at25cmd->address & 0x00FF00) << 8)
			| ((at25cmd->address & 0xFF0000) >> 8);

	/* Send the Status Register Read command followed by a dummy data */
	spi_stat = at25dfx_spi_write_packet((uint16_t *) cmd_buffer,
			at25cmd->cmd_size);

	if (spi_stat != STATUS_OK) {
		return AT25_ERROR_SPI;
	}

	/* Receive the manufacturer and device ID */
	if ((at25cmd->cmd == AT25_BYTE_PAGE_PROGRAM)
			|| (at25cmd->cmd == AT25_WRITE_STATUS)) {
		spi_stat = at25dfx_spi_write_packet(at25cmd->data, 
				at25cmd->data_size);
	} else {
		spi_stat = at25dfx_spi_read_packet(at25cmd->data, 
				at25cmd->data_size);
	}

	if (spi_stat != STATUS_OK) {
		return AT25_ERROR_SPI;
	}

	/* Disable chip select */
	at25dfx_spi_deselect_device(active_sf_cs);

	return (AT25_SUCCESS);
}

/**
 * \brief  Wait for the SerialFlash device to be ready to accept new commands.
 *
 * \return AT25_SUCCESS if successful; otherwise failed.
 */
static at25_status_t at25dfx_wait_ready(void)
{
	at25_status_t op_stat;
	uint8_t at25_stat;
	uint8_t ready = 0;

	/* Read status register and check busy bit */
	while (!ready) {
		op_stat = at25dfx_read_status(&at25_stat);
		if (op_stat != AT25_SUCCESS) {
			return op_stat;
		}

		/* Exit when the device is ready */
		if ((at25_stat & AT25_STATUS_RDYBSY) == AT25_STATUS_RDYBSY_READY) {
			ready = 1;
		}
	}
	return AT25_SUCCESS;
}

/**
 * \brief Read and return the SerialFlash device ID.
 *
 * \param p_dev_id  Pointer to the data of the device ID.
 *
 * \return AT25_SUCCESS if the device ID has been read out; otherwise failed.
 */
static at25_status_t at25dfx_read_dev_id(uint32_t *dev_id)
{
	at25_status_t op_stat;
	at25_cmd_t at25cmd;

	/* Issue a read ID command */
	at25cmd.cmd = AT25_READ_JEDEC_ID;
	at25cmd.cmd_size = 1;
	at25cmd.data = (uint8_t *) dev_id;
	at25cmd.data_size = 3;
	at25cmd.address = 0;
	op_stat = at25dfx_send_command(&at25cmd);
	*dev_id &= 0x00FFFFFF;

	return op_stat;
}

/**
 * \brief Enable critical write operation on a SerialFlash device, such as sector
 * protection, status register, etc.
 *
 * \return AT25_SUCCESS if the device has been unprotected; otherwise return
 * AT25_ERROR_PROTECTED.
 */
static at25_status_t at25dfx_enable_write(void)
{
	at25_status_t op_stat;
	at25_cmd_t at25cmd;

	/* Issue a write enable command */
	at25cmd.cmd = AT25_WRITE_ENABLE;
	at25cmd.cmd_size = 1;
	at25cmd.data = NULL;
	at25cmd.data_size = 0;
	at25cmd.address = 0;
	op_stat = at25dfx_send_command(&at25cmd);

	return op_stat;
}

/**
 * \brief Initialize the SerialFlash.
 *
 * \return AT25_SUCCESS for success, AT25_ERROR_INIT for error.
 */
at25_status_t at25dfx_initialize(void)
{
	at25dfx_spi_init();

	return AT25_SUCCESS;
}

/**
 * \brief Select the SerialFlash by the corresponding chip select.
 *
 * \param cs  SerialFlash chip select.
 */
void at25dfx_set_mem_active(uint8_t cs)
{
	active_sf_cs = cs;
}

/**
 * \brief Check if the SerialFlash is valid. It will read the device id from the device and compare the
 * value set in the configuration file.
 *
 * \return AT25_SUCCESS for success, AT25_ERROR_NOT_FOUND for error.
 */
at25_status_t at25dfx_mem_check(void)
{
	uint32_t dev_id = 0x0;

	/* Read SerialFlash device id */
	at25dfx_read_dev_id(&dev_id);

	if (dev_id == AT25DFX_DEV_ID) {
		return AT25_SUCCESS;
	} else {
		return AT25_ERROR_NOT_FOUND;
	}
}

/**
 * \brief Read and return the status register of the SerialFlash.
 *
 * \param status  Pointer to an AT25 device status.
 *
 * \return AT25_SUCCESS for success, otherwise for error.
 */
at25_status_t at25dfx_read_status(uint8_t *status)
{
	at25_status_t op_stat;
	at25_cmd_t at25cmd;

	/* Issue a read status command */
	at25cmd.cmd = AT25_READ_STATUS;
	at25cmd.cmd_size = 1;
	at25cmd.data = status;
	at25cmd.data_size = 1;
	at25cmd.address = 0;
	op_stat = at25dfx_send_command(&at25cmd);

	return op_stat;
}

/**
 * \brief Write the given value in the status register of the SerialFlash device.
 *
 * \param status  Status to write.
 *
 * \return AT25_SUCCESS if successful; otherwise failed. 
 */
at25_status_t at25dfx_write_status(uint8_t status)
{
	at25_status_t op_stat;
	at25_cmd_t at25cmd;

	/* Issue a write status command */
	at25cmd.cmd = AT25_WRITE_STATUS;
	at25cmd.cmd_size = 1;
	at25cmd.data = (uint8_t *)&status;
	at25cmd.data_size = 1;
	at25cmd.address = 0;
	op_stat = at25dfx_send_command(&at25cmd);

	return op_stat;
}

/**
 * \brief Read sector protection status.
 *
 * \param ul_address  Sector address to be read.
 *
 * \return Sector protect status, AT25_ERROR when failed.
 */
at25_status_t at25dfx_read_sector_protect_status(uint32_t address)
{
	at25_cmd_t at25cmd;
	uint8_t at25_stat;

	/* Issue a read sector protection status command */
	at25cmd.cmd = AT25_READ_SECTOR_PROT;
	at25cmd.cmd_size = 4;
	at25cmd.data = (uint8_t *)&at25_stat;
	at25cmd.data_size = 1;
	at25cmd.address = address;
	at25dfx_send_command(&at25cmd);

	switch (at25_stat) {
	case AT25_SECTOR_PROTECTED_VALUE:
		return AT25_SECTOR_PROTECTED;

	case AT25_SECTOR_UNPROTECTED_VALUE:
		return AT25_SECTOR_UNPROTECTED;

	default:
		return AT25_ERROR;
	}
}

/**
 * \brief Protect/unprotect the specific sector.
 *
 * \param address  Address to be protected.
 * \param protect_type  AT25_TYPE_PROTECT to protect the sector, AT25_TYPE_UNPROTECT to unprotect. 
 *
 * \return Sector protect operation status.
 */
at25_status_t at25dfx_protect_sector(uint32_t address, uint8_t protect_type)
{
	at25_status_t op_stat;
	at25_cmd_t at25cmd;

	/* Enable write operation first */
	at25dfx_enable_write();

	/* Issue a read ID command */
	if (protect_type == AT25_TYPE_PROTECT) {
		at25cmd.cmd = AT25_PROTECT_SECTOR;
	} else {
		at25cmd.cmd = AT25_UNPROTECT_SECTOR;
	}

	at25cmd.cmd_size = 4;
	at25cmd.data = NULL;
	at25cmd.data_size = 0;
	at25cmd.address = address;
	op_stat = at25dfx_send_command(&at25cmd);

	return op_stat;
}

/**
 * \brief Protect the SerialFlash device.
 *
 * \param protect_type  AT25_TYPE_PROTECT to protect the sector, AT25_TYPE_UNPROTECT to unprotect. 
 *
 * \return AT25_SUCCESS if the device has been protected; otherwise return the AT25 error code.
 */
at25_status_t at25dfx_protect_chip(uint8_t protect_type)
{
	at25_status_t op_stat;
	uint8_t at25_stat;

	/* Perform a global unprotect command */
	op_stat = at25dfx_enable_write();
	if (op_stat != AT25_SUCCESS)
		return op_stat;

	if (protect_type == AT25_TYPE_PROTECT) {
		/* Check the new status */
		op_stat = at25dfx_read_status(&at25_stat);
		if (op_stat != AT25_SUCCESS) {
			return op_stat;
		}

		op_stat = at25dfx_write_status(at25_stat | 
				AT25_GLOBAL_PROTECT_VALUE);
		if (op_stat != AT25_SUCCESS) {
			return op_stat;
		}
	} else {
		op_stat = at25dfx_write_status(0);
		if (op_stat != AT25_SUCCESS) {
			return op_stat;
		}
	}

	/* Check the new status */
	op_stat = at25dfx_read_status(&at25_stat);
	if (op_stat != AT25_SUCCESS) {
		return op_stat;
	}

	if (protect_type == AT25_TYPE_PROTECT) {
		if ((at25_stat & AT25_STATUS_SWP) != AT25_STATUS_SWP) {
			return AT25_ERROR;
		}
	} else {
		if ((at25_stat & (AT25_STATUS_SPRL | AT25_STATUS_SWP)) != 0) {
			return AT25_ERROR;
		}
	}
	return AT25_SUCCESS;
}

/**
 * \brief Erase all the content of the memory chip.
 *
 * \return AT25_SUCCESS if the device has been unprotected; otherwise return
 * AT25_ERROR_PROTECTED.
 */
at25_status_t at25dfx_erase_chip(void)
{
	at25_status_t op_stat;
	uint8_t at25_stat;
	at25_cmd_t at25cmd;

	/* Check if the flash is unprotected */
	op_stat = at25dfx_read_status(&at25_stat);
	if (op_stat != AT25_SUCCESS) {
		return op_stat;
	}

	if ((at25_stat & AT25_STATUS_SWP) != AT25_STATUS_SWP_PROTNONE) {
		return AT25_ERROR_PROTECTED;
	}

	/* Enable critical write operation */
	op_stat = at25dfx_enable_write();
	if (op_stat != AT25_SUCCESS) {
		return op_stat;
	}

	/* Erase the chip */
	at25cmd.cmd = AT25_CHIP_ERASE_2;
	at25cmd.cmd_size = 1;
	at25cmd.data = NULL;
	at25cmd.data_size = 0;
	at25cmd.address = 0;
	op_stat = at25dfx_send_command(&at25cmd);

	if (op_stat != AT25_SUCCESS) {
		return op_stat;
	}

	/* Wait for transfer to finish */
	op_stat = at25dfx_wait_ready();
	return op_stat;
}

/**
 *\brief  Erase the specified block of the SerialFlash.
 *
 * \param address  Address of the block to erase.
 *
 * \return AT25_SUCCESS if successful; otherwise return AT25_ERROR_PROTECTED if the
 * device is protected or AT25_ERROR_BUSY if busy executing a command.
 */
at25_status_t at25dfx_erase_block(uint32_t address)
{
	at25_status_t op_stat;
	uint8_t at25_stat;
	at25_cmd_t at25cmd;

	/* Check if beyond the memory size */
	if (address > AT25DFX_SIZE) {
		return AT25_ERROR;
	}

	/* Check if the flash is ready and unprotected */
	op_stat = at25dfx_read_status(&at25_stat);
	if (op_stat != AT25_SUCCESS) {
		return op_stat;
	}

	if ((at25_stat & AT25_STATUS_RDYBSY) != AT25_STATUS_RDYBSY_READY) {
		return AT25_ERROR_BUSY;
	} else if ((at25_stat & AT25_STATUS_SWP) !=
			AT25_STATUS_SWP_PROTNONE) {
		return AT25_ERROR_PROTECTED;
	}

	/* Enable critical write operation */
	op_stat = at25dfx_enable_write();
	if (op_stat != AT25_SUCCESS) {
		return op_stat;
	}

	/* Start the block erase command */
	at25cmd.cmd = AT25DFX_BLOCK_ERASE_CMD;
	at25cmd.cmd_size = 4;
	at25cmd.data = NULL;
	at25cmd.data_size = 0;
	at25cmd.address = address;
	op_stat = at25dfx_send_command(&at25cmd);

	if (op_stat != AT25_SUCCESS) {
		return op_stat;
	}

	/* Wait for transfer to finish */
	op_stat = at25dfx_wait_ready();
	if (op_stat != AT25_SUCCESS) {
		return op_stat;
	}

	return AT25_SUCCESS;
}

/**
 * \brief Write data at the specified address on the serial firmware SerialFlash. The
 * page(s) to program must have been erased prior to writing. This function
 * handles page boundary crossing automatically.
 *
 * \param data  Data buffer.
 * \param size  Number of bytes in buffer.
 * \param address  Write address.
 *
 * \return AT25_SUCCESS if successful; otherwise, return AT25_WRITE_ERROR if there has
 * been an error during the data programming.
 */
at25_status_t at25dfx_write(uint8_t *data, uint16_t size, uint32_t address)
{
	uint32_t write_size;
	at25_status_t op_stat;
	uint8_t at25_stat;
	at25_cmd_t at25cmd;

	/* Check if beyond the memory size */
	if ((size + address) > AT25DFX_SIZE) {
		return AT25_ERROR;
	}

	/* Program one page after another */
	while (size > 0) {
		/* Compute the number of bytes to program in page */
		write_size = Min(size,AT25DFX_PAGE_SIZE -
				(address % AT25DFX_PAGE_SIZE));

		/* Enable critical write operation */
		at25dfx_enable_write();

		at25cmd.cmd = AT25_BYTE_PAGE_PROGRAM;
		at25cmd.cmd_size = 4;
		at25cmd.data = data;
		at25cmd.data_size = write_size;
		at25cmd.address = address;

		/* Program page */
		op_stat = at25dfx_send_command(&at25cmd);
		if (op_stat != AT25_SUCCESS) {
			return op_stat;
		}

		/* Poll the SerialFlash status register until the operation is achieved */
		op_stat = at25dfx_wait_ready();
		if (op_stat != AT25_SUCCESS) {
			return op_stat;
		}

		/* Make sure that the write has no error */
		op_stat = at25dfx_read_status(&at25_stat);
		if (op_stat != AT25_SUCCESS) {
			return op_stat;
		}

		if ((at25_stat & AT25_STATUS_EPE) == AT25_STATUS_EPE_ERROR) {
			return AT25_ERROR_WRITE;
		}

		data += write_size;
		size -= write_size;
		address += write_size;
	}

	return AT25_SUCCESS;
}

/**
 * \brief Read data from the specified address on the SerialFlash.
 *
 * \param data  Data buffer.
 * \param size  Number of bytes to read.
 * \param address  Read address.
 *
 * \return AT25_SUCCESS if successful; otherwise, failed.
 */
at25_status_t at25dfx_read(uint8_t *data, uint16_t size, uint32_t address)
{
	at25_status_t op_stat;
	at25_cmd_t at25cmd;

	/* Check if beyond the memory size */
	if ((size + address) > AT25DFX_SIZE) {
		return AT25_ERROR;
	}

	/* Initialize a Read command to be sent through SPI */
	at25cmd.cmd = AT25_READ_ARRAY_LF;
	at25cmd.cmd_size = 4;
	at25cmd.data = data;
	at25cmd.data_size = size;
	at25cmd.address = address;

	/* Start a read operation */
	op_stat = at25dfx_send_command(&at25cmd);

	return op_stat;
}

//@}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
