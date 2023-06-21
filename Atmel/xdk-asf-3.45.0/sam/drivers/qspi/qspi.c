/**
 * \file
 *
 * \brief Quad Serial Peripheral Interface (QSPI) driver for SAMV71.
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

#include "qspi.h"

/**
 * \defgroup sam_drivers_qspi_group Quad Serial Peripheral Interface (QSPI)
 *
 * See \ref sam_qspi_quickstart.
 *
 * The Quad SPI Interface (QSPI) is a synchronous serial data link that provides communication with external
 * devices in Master mode.
 * The QSPI can be used in SPI mode to interface to serial peripherals (such as ADCs, DACs, LCD controllers, CAN
 * controllers and sensors), or in Serial Memory mode to interface to serial Flash memories.
 * The QSPI allows the system to execute code directly from a serial Flash memory (XIP) without code shadowing to
 * RAM. The serial Flash memory mapping is seen in the system as other memories (ROM, SRAM, DRAM,
 * embedded Flash memory, etc.).
 * With the support of the Quad SPI protocol, the QSPI allows the system to use high-performance serial Flash
 * memories which are small and inexpensive, in place of larger and more expensive parallel Flash memories.
 *
 * @{
 */

/**
 * \brief Memory copy function.
 *
 * \param dst  Pointer to destination buffer.
 * \param src  Pointer to source buffer.
 * \param count  Bytes to be copied.
 */
static void _qspi_memcpy(uint8_t* dst, uint8_t* src, uint32_t count)
{
    while (count--) {
		*dst++ = *src++;
	}
}

/**
 * \brief Ends ongoing transfer by releasing CS of QSPI peripheral.
 *
 * \param qspi  Pointer to an Qspi instance.
 */
static inline void qspi_end_transfer(Qspi *qspi)
{
	assert(qspi);
	while(!(qspi->QSPI_SR & QSPI_SR_TXEMPTY));
	qspi->QSPI_CR = QSPI_CR_LASTXFER;
}

/**
 * \brief Set QSPI to Memory mode.
 *
 * \param qspi Pointer to an QSPI instance.
 */
static inline void qspi_set_memory_mode(Qspi *qspi)
{
	qspi->QSPI_MR |= QSPI_MR_SMM_MEMORY;
}

/**
 * \brief Set QSPI to SPI mode (Master mode only).
 *
 * \param qspi Pointer to an QSPI instance.
 */
static inline void qspi_set_spi_mode(Qspi *qspi)
{
	qspi->QSPI_MR &= (~QSPI_MR_SMM_SPI);
}

/**
 * \brief Enable waiting RX_EMPTY before transfer starts.
 *
 * \param qspi Pointer to an QSPI instance.
 */
static inline void qspi_enable_wait_data_read_before_transfer(Qspi *qspi)
{
	qspi->QSPI_MR |= QSPI_MR_WDRBT;
}

/**
 * \brief Disable waiting RX_EMPTY before transfer starts.
 *
 * \param qspi Pointer to an QSPI instance.
 */
static inline void qspi_disable_wait_data_read_before_transfer(Qspi *qspi)
{
	qspi->QSPI_MR &= (~QSPI_MR_WDRBT);
}

/**
 * \brief Set Chip Select Mode.
 *
 * \param qspi    Pointer to an QSPI instance.
 * \param csmode  Chip select mode to be set.
 */
static inline void qspi_set_chip_select_mode(Qspi *qspi, uint32_t csmode)
{
	uint32_t mask = qspi->QSPI_MR & (~QSPI_MR_CSMODE_Msk);
	qspi->QSPI_MR = mask | QSPI_MR_CSMODE(csmode);
}

/**
 * \brief Set the number of data bits transferred.
 *
 * \param qspi Pointer to an QSPI instance.
 * \param bits Bits per transfer.
 */
static inline void qspi_set_bits_per_transfer(Qspi *qspi, uint32_t bits)
{
	uint32_t mask = qspi->QSPI_MR & (~QSPI_MR_NBBITS_Msk);
	qspi->QSPI_MR = mask | bits;
}

/**
 * \brief Set qspi minimum inactive QCS delay.
 *
 * \param qspi      Pointer to a Qspi instance.
 * \param uc_dlybct Time to be delay.
 */
static inline void qspi_set_minimum_inactive_qcs_delay(Qspi *qspi, uint8_t uc_dlybct)
{
	assert(qspi);
	uint32_t mask = qspi->QSPI_MR & (~QSPI_MR_DLYCS_Msk);
	qspi->QSPI_MR = mask | QSPI_MR_DLYCS(uc_dlybct);
}

/**
 * \brief Set qspi delay between consecutive transfers.
 *
 * \param qspi     Pointer to a Qspi instance.
 * \param uc_dlycs Time to be delay.
 */
static inline void qspi_set_delay_between_consecutive_transfers(Qspi *qspi, uint32_t uc_dlycs)
{
	assert(qspi);
	uint32_t mask = qspi->QSPI_MR & (~QSPI_MR_DLYBCT_Msk);
	qspi->QSPI_MR = mask | QSPI_MR_DLYBCT(uc_dlycs);
}

/**
 * \brief Set qspi clock transfer delay.
 *
 * \param qspi     Pointer to a Qspi instance.
 * \param uc_dlybs Delay before QSCK.
 */
static inline void qspi_set_transfer_delay(Qspi *qspi, uint8_t uc_dlybs)
{
	assert(qspi);
	uint32_t mask = qspi->QSPI_SCR & (~QSPI_SCR_DLYBS_Msk);
	qspi->QSPI_SCR = mask | QSPI_SCR_DLYBS(uc_dlybs);
}

/**
 * \brief Read QSPI RDR register for SPI mode
 *
 * \param qspi   Pointer to an Qspi instance.
 * \return status Data value read from QSPI.
 */
static inline uint16_t qspi_read_spi(Qspi *qspi)
{
	assert(qspi);
	while(!(qspi->QSPI_SR & QSPI_SR_RDRF));
	return  qspi->QSPI_RDR;
}

/**
 * \brief Write to QSPI Tx register in SPI mode
 *
 * \param qspi     Pointer to an Qspi instance.
 * \param w_data   Data to transmit
 */
static inline void qspi_write_spi(Qspi *qspi, uint16_t w_data)
{
	assert(qspi);
	/** Send data */
	while(!(qspi->QSPI_SR & QSPI_SR_TXEMPTY));
	qspi->QSPI_TDR = w_data ;
	while(!(qspi->QSPI_SR & QSPI_SR_TDRE));
}

/**
 * \brief Config qspi according the config struct
 *
 * \param pQspi        Pointer to an Qspi instance.
 * \param qspi_config  Pointer to an qspi_config_t struct.
 * \return status QSPI set config result.
 *
 */
static enum status_code qspi_set_config(Qspi *qspi, struct qspi_config_t *qspi_config)
{
	enum status_code status = STATUS_OK;
	if(qspi_config->serial_memory_mode == mem_mode) {
		qspi_set_memory_mode(qspi);
	} else {
		qspi_set_spi_mode(qspi);
	}
	if(qspi_config->loopback_en) {
		qspi_enable_loopback(qspi);
	} else {
		qspi_disable_loopback(qspi);
	}
	if(qspi_config->wait_data_for_transfer) {
		qspi_enable_wait_data_read_before_transfer(qspi);
	} else {
		qspi_disable_wait_data_read_before_transfer(qspi);
	}
	qspi_set_chip_select_mode(qspi, qspi_config->csmode);
	qspi_set_bits_per_transfer(qspi, qspi_config->bits_per_transfer);
	qspi_set_minimum_inactive_qcs_delay(qspi, qspi_config->min_delay_qcs);
	qspi_set_delay_between_consecutive_transfers(qspi, qspi_config->delay_between_ct);
	qspi_set_clock_polarity(qspi, qspi_config->clock_polarity);
	qspi_set_clock_phase(qspi, qspi_config->clock_phase);
	status = qspi_set_baudrate(qspi, qspi_config->baudrate);
	qspi_set_transfer_delay(qspi, qspi_config->transfer_delay);
	qspi_set_scrambling_mode(qspi, qspi_config->scrambling_en, qspi_config->scrambling_random_value_dis);
	qspi_set_scrambing_key(qspi, qspi_config->scrambling_user_key);
	return status;
}

/**
 * \brief Config qspi according the config struct
 *
 * \param pQspi         Pointer to an Qspi instance.
 * \param qspi_config   Pointer to an qspi_config_t struct.
 * \return status       QSPI initialize result.
 *
 */
enum status_code qspi_initialize(Qspi *qspi, struct qspi_config_t *qspi_config)
{
	enum status_code status = STATUS_OK;
	qspi_disable(qspi);
	qspi_reset(qspi);

	/** Configure an QSPI peripheral. */
	status = qspi_set_config(qspi, qspi_config);

	qspi_enable(qspi);
	return status;
}

/**
 * \brief Get default config
 *
 * \param qspi_config     Pointer to an qspi_config_t struct.
 *
 */
void qspi_get_config_default(struct qspi_config_t * qspi_config)
{
	qspi_config->serial_memory_mode = mem_mode;
	qspi_config->loopback_en = false;
	qspi_config->wait_data_for_transfer = false;
	qspi_config->csmode = QSPI_LASTXFER;
	qspi_config->bits_per_transfer = QSPI_MR_NBBITS_8_BIT;
	qspi_config->min_delay_qcs = 0;
	qspi_config->delay_between_ct = 0;
	qspi_config->clock_polarity = 0;
	qspi_config->clock_phase = 0;
	qspi_config->baudrate = 50000000;
	qspi_config->transfer_delay = 0;
	qspi_config->scrambling_en = false;
	qspi_config->scrambling_random_value_dis = false;
	qspi_config->scrambling_user_key = 0;
}

/**
 * \brief Qspi read data.
 *
 * \param qspi         Pointer to a Qspi instance.
 * \param us_data      Pointer to read data.
 * \param num_of_bytes Read data numbers.
 * \return status Read option result.
 */
enum status_code qspi_read(Qspi *qspi, uint16_t *us_data, uint32_t num_of_bytes)
{
	assert(qspi);
	if (num_of_bytes == 0) {
		return STATUS_OK;
	}

	enum status_code status = OPERATION_IN_PROGRESS;
	uint32_t num_of_bytes_read = 0;
	uint32_t num_of_attempt = 0;
	uint8_t *pw_data = (uint8_t *)us_data;
	uint16_t dummy = 0xFF;

	if (num_of_bytes == 1) {
		for(; ;) {
			if (qspi->QSPI_SR & QSPI_SR_RDRF) {
				*us_data = qspi_read_spi(qspi);
				qspi_write_spi(qspi, dummy);
				*us_data = qspi_read_spi(qspi);
				num_of_attempt = 0;
				status = STATUS_OK;
				break;
			} else {
				if(num_of_attempt > 0xFFFF) {
					status = ERR_TIMEOUT;
					break;
				} else {
					status = STATUS_ERR_BUSY;
					num_of_attempt++;
				}
			}
		}
	} else {
		/* Dummy read  and write to discard  first bytes received and start receiving new data */
		dummy = qspi_read_spi(qspi);
		qspi_write_spi(qspi, dummy);
		for(; num_of_bytes_read < num_of_bytes;) {
			if (qspi->QSPI_SR & QSPI_SR_TDRE) {
				*pw_data= qspi_read_spi(qspi);
				if(qspi->QSPI_MR & QSPI_MR_NBBITS_Msk) {
					pw_data += sizeof(uint16_t);
				} else {
					pw_data += sizeof(uint8_t);
				}
				num_of_bytes_read++;
				num_of_attempt = 0;
				status = STATUS_OK;
				qspi_write_spi(qspi, dummy);
			} else {
				if(num_of_attempt > 0xFFFF) {
					status = ERR_TIMEOUT;
					break;
				} else {
					status = STATUS_ERR_BUSY;
					num_of_attempt++;
				}
			}
		}
	}

	return status;
}

/**
 * \brief Qspi write data.
 *
 * \param qspi         Pointer to a Qspi instance.
 * \param us_data      Pointer to data to be written.
 * \param num_of_bytes Write data numbers.
 * \return status      Write option result.
 */
enum status_code qspi_write(Qspi *qspi, uint16_t *us_data, uint32_t num_of_bytes)
{
	assert(qspi);
	if (num_of_bytes == 0) {
		return STATUS_OK;
	}

	enum status_code status = OPERATION_IN_PROGRESS;
	uint32_t num_of_bytes_write = 0;
	uint32_t num_of_attempt = 0;
	uint8_t *pw_data = (uint8_t *)us_data;
	uint8_t Addr_Inc = 0;

	if (num_of_bytes == 1) {
		for(;;) {
			if(qspi->QSPI_SR & QSPI_SR_TDRE) {
				qspi_write_spi(qspi, (uint16_t)(*us_data));
				num_of_attempt = 0;
				status = STATUS_OK;
				break;
			} else {
				status = STATUS_ERR_BUSY;
				num_of_attempt++;
				if(num_of_attempt > 0xFFFF) {
					status = ERR_TIMEOUT;
					break;
				}
			}
		}
	} else {
		if(qspi->QSPI_MR & QSPI_MR_NBBITS_Msk) {
			Addr_Inc = sizeof(uint16_t);
		} else {
			Addr_Inc = sizeof(uint8_t);
		}

		for(; num_of_bytes_write < num_of_bytes; num_of_bytes_write++) {
			if (qspi->QSPI_SR & QSPI_SR_TXEMPTY) {
				qspi_write_spi(qspi, (uint16_t)(*pw_data));
				pw_data += Addr_Inc;
				num_of_attempt = 0;
				status = STATUS_OK;
			} else {
				status = STATUS_ERR_BUSY;
				num_of_attempt++;
				if(num_of_attempt > 0xFFFF) {
					status = ERR_TIMEOUT;
					break;
				}
			}
		}
	}

	return status;
}

/**
 * \brief Set qspi instruction frame.
 *
 * \param qspi  Pointer to a Qspi instance.
 * \param instruction_frame   Frame to be set.
 */
void qspi_set_instruction_frame(Qspi *qspi, struct qspi_inst_frame_t instruction_frame)
{
	assert(qspi);
	uint32_t mask = 0;
	mask |= QSPI_IFR_WIDTH(instruction_frame.inst_frame.bm.b_width);
	if (instruction_frame.inst_frame.bm.b_inst_en) {
		mask |= QSPI_IFR_INSTEN;
	}
	if (instruction_frame.inst_frame.bm.b_addr_en) {
		mask |= QSPI_IFR_ADDREN;
	}
	if (instruction_frame.inst_frame.bm.b_opt_en) {
		mask |= QSPI_IFR_OPTEN;
	}
	if (instruction_frame.inst_frame.bm.b_data_en) {
		mask |= QSPI_IFR_DATAEN;
	}
	mask |= QSPI_IFR_OPTL(instruction_frame.inst_frame.bm.b_opt_len);
	if (instruction_frame.inst_frame.bm.b_addr_len) {
		mask |= QSPI_IFR_ADDRL_32_BIT;
	}
	mask |= QSPI_IFR_TFRTYP(instruction_frame.inst_frame.bm.b_tfr_type);
	if (instruction_frame.inst_frame.bm.b_continues_read) {
		mask |= QSPI_IFR_CRM_ENABLED;
	}
	mask |= QSPI_IFR_NBDUM(instruction_frame.inst_frame.bm.b_dummy_cycles);

	qspi->QSPI_IFR = mask;
}

/**
 * \brief Send instruction over QSPI with data
 *
 * \param qspid        Pointer to an Qspi instance.
 * \param read_write   Flag to indicate read/write QSPI memory access
 *
 * \return Returns 1 if At least one instruction end has been detected since the last read of QSPI_SR.; otherwise
 * returns 0.
 */
enum status_code qspi_flash_execute_command(struct qspid_t *qspid, enum qspi_access read_write)
{
	struct qspi_inst_frame_t * const frame = qspid->qspi_frame;
	struct qspi_mem_cmd_t command = qspid->qspi_command;
	enum status_code status = OPERATION_IN_PROGRESS;

	struct qspi_buffer_t buffer = qspid->qspi_buffer;
	uint32_t *qspi_buffer = (uint32_t *)QSPIMEM_ADDR;

	if (read_write == QSPI_CMD_ACCESS) {
		if(frame->inst_frame.bm.b_addr_en) {
			qspi_set_instruction_addr(qspid->qspi_hw, frame->addr);
		}
		qspi_set_instruction_code(qspid->qspi_hw, command);
		qspi_set_instruction_frame(qspid->qspi_hw, *frame);
	} else if (read_write == QSPI_READ_ACCESS) {
		assert(buffer.rx_data_size);

		qspi_set_instruction_code(qspid->qspi_hw, command);
		qspi_set_instruction_frame(qspid->qspi_hw, *frame);

		/* To synchronize system bus accesses */
		qspi_get_inst_frame(qspid->qspi_hw);
		_qspi_memcpy((uint8_t *)buffer.data_rx , (uint8_t *)qspi_buffer,  buffer.rx_data_size);
	} else if (read_write == QSPI_WRITE_ACCESS) {
		assert(buffer.tx_data_size);

		qspi_set_instruction_code(qspid->qspi_hw, command);
		qspi_set_instruction_frame(qspid->qspi_hw, *frame);
		/* To synchronize system bus accesses */
		qspi_get_inst_frame(qspid->qspi_hw);
		_qspi_memcpy((uint8_t *)qspi_buffer, (uint8_t *)buffer.data_tx, buffer.tx_data_size);
	}

	if (read_write == QSPI_READ_ACCESS || read_write == QSPI_WRITE_ACCESS) {
		__DSB();
		__ISB();
		qspi_end_transfer(qspid->qspi_hw);
	}
	/* Poll CR reg to know status if instruction has end */
	while(!(qspid->qspi_hw->QSPI_SR & QSPI_SR_INSTRE));
	frame->inst_frame.val = 0;

	status = STATUS_OK;
	return status;
};

/**
 * \brief Writes or reads the QSPI memory (0x80000000) to trasmit or receive data from Flash memory
 * \param qspid          Pointer to an Qspi instance.
 * \param read_write     Flag to indicate read/write QSPI memory access
 * \param scramble_flag  Enable or disable scramble on QSPI
 *
 * \return Returns 1 if At least one instruction end has been detected since the last read of QSPI_SR.; otherwise
 * returns 0.
 */
enum status_code qspi_flash_access_memory(struct qspid_t *qspid, enum qspi_access read_write, uint8_t scramble_flag)
{
	enum status_code status = OPERATION_IN_PROGRESS;
	struct qspi_inst_frame_t* const frame = qspid->qspi_frame;
	struct qspi_mem_cmd_t command = qspid->qspi_command;
	uint32_t *qspi_mem = (uint32_t *)(QSPIMEM_ADDR | frame->addr);
	struct qspi_buffer_t *buffer = &qspid->qspi_buffer;

	assert(((read_write > QSPI_CMD_ACCESS) && (read_write <= QSPI_WRITE_ACCESS)) ? true: false);

	qspi_set_instruction_code(qspid->qspi_hw, command);

	if(scramble_flag) {
		qspi_set_scrambling_mode(qspid->qspi_hw, scramble_flag, 1);
	}
	qspi_set_instruction_frame(qspid->qspi_hw, *frame);
	/* To synchronize system bus accesses */
	qspi_get_inst_frame(qspid->qspi_hw);
	frame->inst_frame.val = 0;

	if (read_write == QSPI_WRITE_ACCESS) {
		_qspi_memcpy((uint8_t *)qspi_mem, (uint8_t *)buffer->data_tx , buffer->tx_data_size);
	} else {
		_qspi_memcpy((uint8_t *)buffer->data_rx, (uint8_t *)qspi_mem, buffer->rx_data_size);
	}
	__DSB();
	__ISB();
	/* End transmission after all data has been sent */
	qspi_end_transfer(qspid->qspi_hw);
	/* Poll CR reg to know status if instruction has end */
	while(!(qspid->qspi_hw->QSPI_SR & QSPI_SR_INSTRE));

	status = STATUS_OK;
	return status;
}

/**
 * @}
 */
