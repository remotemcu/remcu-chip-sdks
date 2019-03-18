/**
 * \file
 *
 * \brief AT25DFx SerialFlash driver private SPI HAL interface.
 *
 * Copyright (C) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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
 * Support and FAQ: visit <a href="http://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef AT25DFX_PRIV_HAL_H
#define AT25DFX_PRIV_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

//! \name Private SPI helpers
//@{

/** Alias for SPI lock function */
#define _at25dfx_spi_lock    spi_master_vec_lock
/** Alias for SPI unlock function */
#define _at25dfx_spi_unlock  spi_master_vec_unlock

/**
 * \brief Issue a read command
 *
 * \param chip Address of SerialFlash chip instance to operate on.
 * \param cmd The command to issue.
 */
static inline void _at25dfx_chip_issue_read_command_wait(
		struct at25dfx_chip_module *chip, struct at25dfx_command cmd)
{
	struct spi_master_vec_bufdesc vectors[2];

	enum status_code status;
	uint8_t cmd_buffer[AT25DFX_COMMAND_MAX_SIZE];

	Assert((cmd.command_size) && (cmd.command_size <= AT25DFX_COMMAND_MAX_SIZE));

	// Construct command to send
	cmd_buffer[0] = cmd.opcode;

	if (cmd.command_size > 1) {
		Assert(cmd.command_size >= 4);

		cmd_buffer[3] = cmd.address & 0xff;
		cmd_buffer[2] = (cmd.address >> 8) & 0xff;
		cmd_buffer[1] = (cmd.address >> 16) & 0xff;
	}
	// Don't bother with init of dummy bytes

	// Issue command, then start read
	_at25dfx_chip_select(chip);

	vectors[0].data = cmd_buffer;
	vectors[0].length = cmd.command_size;
	vectors[1].length = 0;

	status = spi_master_vec_transceive_buffer_job(chip->spi, vectors, NULL);
	Assert(status == STATUS_OK);
	status = spi_master_vec_get_job_status_wait(chip->spi);
	Assert(status == STATUS_OK);

	if (cmd.length) {
		vectors[0].data = cmd.data.rx;
		vectors[0].length = cmd.length;

		status = spi_master_vec_transceive_buffer_job(chip->spi, NULL, vectors);
		Assert(status == STATUS_OK);
		status = spi_master_vec_get_job_status_wait(chip->spi);
		Assert(status == STATUS_OK);
	}

	_at25dfx_chip_deselect(chip);
}

/**
 * \brief Issue a read command
 *
 * \param chip Address of SerialFlash chip instance to operate on.
 * \param cmd The command to issue.
 */
static inline void _at25dfx_chip_issue_write_command_wait(
		struct at25dfx_chip_module *chip, struct at25dfx_command cmd)
{
	struct spi_master_vec_bufdesc vectors[2];

	enum status_code status;
	uint8_t cmd_buffer[AT25DFX_COMMAND_MAX_SIZE];

	Assert((cmd.command_size) && (cmd.command_size <= AT25DFX_COMMAND_MAX_SIZE));

	cmd_buffer[0] = cmd.opcode;

	if (cmd.command_size > 1) {
		Assert(cmd.command_size >= 4);

		cmd_buffer[3] = cmd.address & 0xff;
		cmd_buffer[2] = (cmd.address >> 8) & 0xff;
		cmd_buffer[1] = (cmd.address >> 16) & 0xff;
	}

	_at25dfx_chip_select(chip);

	vectors[0].data = cmd_buffer;
	vectors[0].length = cmd.command_size;
	vectors[1].length = 0;

	status = spi_master_vec_transceive_buffer_job(chip->spi, vectors, NULL);
	Assert(status == STATUS_OK);
	status = spi_master_vec_get_job_status_wait(chip->spi);
	Assert(status == STATUS_OK);

	if (cmd.length) {
		// Cast away const to avoid compiler warning
		vectors[0].data = (uint8_t *)cmd.data.tx;
		vectors[0].length = cmd.length;

		status = spi_master_vec_transceive_buffer_job(chip->spi, vectors, NULL);
		Assert(status == STATUS_OK);
		status = spi_master_vec_get_job_status_wait(chip->spi);
		Assert(status == STATUS_OK);
	}

	_at25dfx_chip_deselect(chip);
}

/**
 * \brief Get status after current operation completes
 *
 * This function will issue a command to read out the status, and will then read
 * the status continuously from the chip until it indicates that it is not busy.
 * The error flag of the status is then checked, before returning the result.
 *
 * \param chip Address of SerialFlash chip instance to operate on.
 *
 * \return Status of the operation.
 * \retval STATUS_OK if operation succeeded.
 * \retval STATUS_ERR_IO if an error occurred.
 */
static inline enum status_code _at25dfx_chip_get_nonbusy_status(
		struct at25dfx_chip_module *chip)
{
	struct spi_master_vec_bufdesc vectors[2];

	enum status_code status;
	uint8_t data;

	vectors[0].data = &data;
	vectors[0].length = 1;
	vectors[1].length = 0;

	_at25dfx_chip_select(chip);

	// Issue status read command
	data = AT25DFX_COMMAND_READ_STATUS;

	status = spi_master_vec_transceive_buffer_job(chip->spi, vectors, NULL);
	Assert(status == STATUS_OK);
	status = spi_master_vec_get_job_status_wait(chip->spi);
	Assert(status == STATUS_OK);

	// Keep reading until busy flag clears
	do {
		status = spi_master_vec_transceive_buffer_job(chip->spi, NULL, vectors);
		Assert(status == STATUS_OK);
		status = spi_master_vec_get_job_status_wait(chip->spi);
		Assert(status == STATUS_OK);
	} while (data & AT25DFX_STATUS_BUSY);

	_at25dfx_chip_deselect(chip);

	// Return final status
	if (data & AT25DFX_STATUS_ERROR) {
		return STATUS_ERR_IO;
	}
	return STATUS_OK;
}

//@}

#ifdef __cplusplus
}
#endif

#endif // AT25DFX_PRIV_HAL_H