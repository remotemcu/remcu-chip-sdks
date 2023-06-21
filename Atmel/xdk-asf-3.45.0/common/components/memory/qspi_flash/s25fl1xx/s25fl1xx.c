/**
 * \file
 *
 * \brief QSPI flash memory driver for S25FL1XX.
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

/**
 * \defgroup group_common_components_memory_qspi_flash_s25fl1xx QSPI Flash S25FL1XX Series
 *
 * Low-level driver for the S25FL1XX Series QSPI Flash controller. This driver provides access to the main
 * features of the S25FL1XX Series QSPI Flash.
 *
 * \{
 */

#include <board.h>
#include <assert.h>
#include "stdlib.h"
#include "string.h"
#include "s25fl1xx.h"
#include "delay.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

struct qspi_inst_frame_t *dev;
struct qspi_inst_frame_t *mem;

#define PAGE_SIZE       256

/**
 * \brief Initialize QSPI serial memory mode.
 * \param qspi                      Pointer to an S25FL1 qspid_t struct.
 * \param mode_config               Configure settings to config qspid.
 * \param use_default_config Config QSPI use default configures.
 * \return status S23FL1XX initialize result.
 */
enum status_code s25fl1xx_initialize(Qspi *qspi, struct qspi_config_t *mode_config, uint32_t use_default_config)
{
	enum status_code status = STATUS_OK;

	dev = (struct qspi_inst_frame_t *)malloc (sizeof(struct qspi_inst_frame_t));
	memset(dev, 0, sizeof(struct qspi_inst_frame_t));
	dev->inst_frame.bm.b_width = QSPI_IFR_WIDTH_SINGLE_BIT_SPI;

	mem = (struct qspi_inst_frame_t *)malloc (sizeof(struct qspi_inst_frame_t));
	memset(mem, 0, sizeof(struct qspi_inst_frame_t));
	mem->inst_frame.bm.b_width = QSPI_IFR_WIDTH_SINGLE_BIT_SPI;

	if (use_default_config) {
		qspi_get_config_default(mode_config);
	}

	status = qspi_initialize(qspi, mode_config);
	return status;
}

/**
 * \brief Send command to the serial flash.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 * \param instr  Instruction to be execute.
 * \param tx_data  Data buffer to send data.
 * \param rx_data  Data buffer to receive data.
 * \param read_write  Read/write access.
 * \param size  Data size to be read/write.
 */
static void s25fl1xx_exec_command(struct qspid_t *qspid, uint8_t instr, uint32_t *tx_data, uint32_t *rx_data, enum qspi_access read_write, uint32_t size)
{
	qspid->qspi_command.instruction = instr;
	dev->inst_frame.bm.b_inst_en = 1;
	qspid->qspi_frame = dev;
	qspid->qspi_buffer.data_tx = tx_data;
	qspid->qspi_buffer.data_rx = rx_data;

	/** To prevent unaligned access */
	if((size % sizeof(uint32_t)) && size > 1) {
		size += (sizeof(uint32_t) - (size % sizeof(uint32_t)));
	}

	if(read_write == QSPI_CMD_ACCESS) {
		dev->inst_frame.bm.b_tfr_type = (QSPI_IFR_TFRTYP_TRSFR_READ >> QSPI_IFR_TFRTYP_Pos);
		dev->inst_frame.bm.b_data_en = 0;
	} else if (read_write == QSPI_WRITE_ACCESS) {
		dev->inst_frame.bm.b_data_en = 1;
		dev->inst_frame.bm.b_tfr_type = (QSPI_IFR_TFRTYP_TRSFR_WRITE >> QSPI_IFR_TFRTYP_Pos);
		qspid->qspi_buffer.tx_data_size = size;
	} else {
		dev->inst_frame.bm.b_tfr_type = (QSPI_IFR_TFRTYP_TRSFR_READ >> QSPI_IFR_TFRTYP_Pos);
		dev->inst_frame.bm.b_data_en = 1;
		qspid->qspi_buffer.rx_data_size = size;
	}
	qspi_flash_execute_command(qspid, read_write);
}

/**
 * \brief Reads and returns the status register of the serial flash.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 * \return QSPI status1
 */
static uint8_t s25fl1xx_read_status1(struct qspid_t *qspid)
{
	uint8_t status;
	s25fl1xx_exec_command(qspid, S25FL1XX_READ_STATUS_1, 0, (uint32_t *)(&status), QSPI_READ_ACCESS, 1);
	return status;
}

/**
 * \brief Reads and returns the status register of the serial flash.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 * \return QSPI status2
 */
static uint8_t s25fl1xx_read_status2(struct qspid_t *qspid)
{
	uint8_t status;
	s25fl1xx_exec_command(qspid, S25FL1XX_READ_STATUS_2, 0, (uint32_t *)&status, QSPI_READ_ACCESS, 1);
	return status;
}

/**
 * \brief Reads and returns the status register of the serial flash.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 * \return QSPI status3
 */
static uint8_t s25fl1xx_read_status3(struct qspid_t *qspid)
{
	uint8_t status;
	s25fl1xx_exec_command(qspid, S25FL1XX_READ_STATUS_3, 0, (uint32_t *)&status, QSPI_READ_ACCESS, 1);
	return status;
}

/**
 * \brief Reads and returns the status register of the serial flash.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 * \return QSPI status1/2/3
 */
static uint32_t s25fl1xx_read_status(struct qspid_t *qspid)
{
	uint32_t status;
	status = s25fl1xx_read_status1(qspid) | (s25fl1xx_read_status2(qspid) << 8) | (s25fl1xx_read_status3(qspid) << 16);
	return status;
}

/**
 * \brief Wait for transfer to finish calling the SPI driver ISR. (interrupts are disabled)
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 */
static void s25fl1xx_wait_memory_access_end(struct qspid_t *qspid)
{
	while(s25fl1xx_read_status1(qspid) & S25FL1XX_STATUS_RDYBSY);
}

/**
 * \brief Enable write option to serial flash memory.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 */
static void s25fl1xx_enable_write(struct qspid_t *qspid)
{
	uint8_t status = 0;
	while(!(status & S25FL1XX_STATUS_WEL)) {
		s25fl1xx_exec_command(qspid, S25FL1XX_WRITE_ENABLE, 0, 0, QSPI_CMD_ACCESS, 0);
		status = s25fl1xx_read_status1(qspid);
	}
}

/**
 * \brief Disable write option to serial flash memory.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 */
static void s25fl1xx_disable_write(struct qspid_t *qspid)
{
	uint8_t status;
	status = s25fl1xx_read_status1(qspid);
	while((status & S25FL1XX_STATUS_WEL) != 0) {
		s25fl1xx_exec_command(qspid, S25FL1XX_WRITE_DISABLE, 0, 0, QSPI_CMD_ACCESS, 0);
		status = s25fl1xx_read_status1(qspid);
	}
}

/**
 * \brief Read/write data from serial flash memory.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct..
 * \param instr Instruction to be execute.
 * \param addr  Address to send frame.
 * \param tx_data  Data buffer to send data.
 * \param rx_data  Data buffer to receive data.
 * \param read_write  Read/write access.
 * \param size  Data size to be read/write.
 * \param secure  Enable or disable scramble on QSPI.
 */
static void s25fl1xx_memory_access(struct qspid_t *qspid, uint8_t instr, uint32_t addr, uint32_t *tx_data, uint32_t *rx_data, enum qspi_access read_write, uint32_t size, uint8_t secure)
{
	qspid->qspi_command.instruction = instr;
	qspid->qspi_buffer.data_tx = tx_data;
	qspid->qspi_buffer.data_rx = rx_data;
	mem->addr = addr;
	mem->inst_frame.bm.b_inst_en = 1;
	mem->inst_frame.bm.b_data_en = 1;
	mem->inst_frame.bm.b_addr_en = 1;
	qspid->qspi_frame = mem;

	if (read_write == QSPI_WRITE_ACCESS) {
		mem->inst_frame.bm.b_tfr_type = (QSPI_IFR_TFRTYP_TRSFR_WRITE_MEMORY >> QSPI_IFR_TFRTYP_Pos);
		qspid->qspi_buffer.tx_data_size = size;
	} else {
		mem->inst_frame.bm.b_tfr_type = (QSPI_IFR_TFRTYP_TRSFR_READ_MEMORY >> QSPI_IFR_TFRTYP_Pos);
		qspid->qspi_buffer.rx_data_size = size;
	}
	qspi_flash_access_memory(qspid, read_write, secure);
}

/**
 * \brief Writes the given value in the status register of the serial flash device.
 *
 * \param qspid   Pointer to an S25FL1 qspid_t struct.
 * \param status  Status to write.
 */
static void s25fl1xx_write_status(struct qspid_t *qspid, uint8_t *status)
{
	s25fl1xx_enable_write(qspid);
	s25fl1xx_exec_command(qspid, S25FL1XX_WRITE_STATUS, (uint32_t *)status, 0, QSPI_WRITE_ACCESS, 3);
	s25fl1xx_disable_write(qspid);
}

/**
 * \brief Writes the given value in the status register of the serial flash device.
 *
 * \param qspid   Pointer to an S25FL1 qspid_t struct.
 * \param status  Status to write.
 */
static void s25fl1xx_write_volatile_status(struct qspid_t *qspid, uint8_t *status)
{
	s25fl1xx_exec_command(qspid, 0x50, 0, 0 , QSPI_CMD_ACCESS, 0);
	s25fl1xx_exec_command(qspid, S25FL1XX_WRITE_STATUS, (uint32_t *)status, 0 , QSPI_WRITE_ACCESS, 3);
	s25fl1xx_disable_write(qspid);
}

/**
 * \brief Check weather the address of addr is protected.
 *
 * \param qspid Pointer to an S25FL1 qspid_t struct.
 * \param addr  Address to be checked.
 * \return If 0 returned, addr is unprotected, else protected.
 */
static uint8_t s25fl1xx_check_protected_addr(uint8_t status1, uint32_t addr)
{
  const uint32_t addr_ump = (status1 & S25FL1XX_SEC_PROTECT_Msk) ? 0x001000UL : 0x010000UL;
  static uint8_t is_protected = 0;

  const uint8_t block_bits = ((status1 & S25FL1XX_BLOCK_PROTECT_Msk) >> 2);

  switch(block_bits) {
	case 1:
	if (status1 & S25FL1XX_TOP_BTM_PROTECT_Msk) {
		if((addr > 0x000000) && (addr < (0x000000 + addr_ump - 1))) {
			is_protected = 1;
		}
	} else {
		if((addr > (0x1FFFFF - addr_ump + 1)) && (addr < 0x1FFFFF)) {
			is_protected = 1;
		}
	}
	break;

  case 2:
	if (status1 & S25FL1XX_TOP_BTM_PROTECT_Msk) {
		if((addr > 0x000000) && (addr < (0x000000 + (2* addr_ump)- 1))) {
			is_protected = 1;
		}
	} else {
		if((addr > (0x1FFFFF - (2*addr_ump) + 1)) && (addr < 0x1FFFFF)) {
			is_protected = 1;
		}
	}
	break;

  case 3:
	if (status1 & S25FL1XX_TOP_BTM_PROTECT_Msk) {
		if((addr > 0x000000) && (addr < (0x000000 + (4 * addr_ump) - 1))) {
			is_protected = 1;
		}
	} else {
		if((addr > (0x1FFFFF - (4*addr_ump) + 1)) && (addr < 0x1FFFFF)) {
			is_protected = 1;
		}
	}
	break;

  case 4:
	if (status1 & S25FL1XX_TOP_BTM_PROTECT_Msk) {
		if((addr > 0x000000) && (addr < (0x000000 + (8 * addr_ump) - 1))) {
			is_protected = 1;
		}
	} else {
		if((addr > (0x1FFFFF - (8*addr_ump) + 1)) && (addr < 0x1FFFFF)) {
			is_protected = 1;
		}
	}
	break;

  case 5:
	if(!(status1 & S25FL1XX_SEC_PROTECT_Msk)) {
		if (status1 & S25FL1XX_TOP_BTM_PROTECT_Msk) {
			if((addr > 0x000000) && (addr < (0x000000 + (16 * addr_ump) - 1))) {
				is_protected = 1;
			}
		} else {
			if((addr > (0x1FFFFF - (16*addr_ump) + 1)) && (addr < 0x1FFFFF)) {
				is_protected = 1;
			}
		}
	}
	break;

  case 6:
	if(!(status1 & S25FL1XX_SEC_PROTECT_Msk)) {
		if (status1 & S25FL1XX_TOP_BTM_PROTECT_Msk) {
			if((addr > 0x000000) && (addr < (0x000000 + (32 * addr_ump) - 1))) {
				is_protected = 1;
			}
		}
	}
	break;
  }

  return is_protected;
}

/**
 * \brief Reads and returns the serial flash device ID.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 * \return Jedec id read from chip.
 */
uint32_t s25fl1xx_read_jedec_id(struct qspid_t *qspid)
{
	static uint32_t id;
	s25fl1xx_exec_command(qspid, S25FL1XX_READ_JEDEC_ID, 0, &id, QSPI_READ_ACCESS, 3);
	return id;
}

/**
 * \brief Enables critical writes operation on a serial flash device, such as sector
 * protection, status register, etc.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 * \param mode  Mode to be set.
 */
void s25fl1xx_set_quad_mode(struct qspid_t *qspid, uint8_t mode)
{
	uint8_t status[3];

	status[0] = s25fl1xx_read_status1(qspid);
	status[1] = s25fl1xx_read_status2(qspid);
	status[2] = s25fl1xx_read_status3(qspid);

	if(mode) {
		while(!(status[1] & S25FL1XX_STATUS_QUAD_ENABLE)) {
			status[1] |= S25FL1XX_STATUS_QUAD_ENABLE;
			s25fl1xx_write_status(qspid, status);
			status[1] = s25fl1xx_read_status2(qspid);
			delay_ms(50);
		}
	} else {
		while((status[1] & S25FL1XX_STATUS_QUAD_ENABLE)) {
			status[1] &= (~S25FL1XX_STATUS_QUAD_ENABLE)  ;
			s25fl1xx_write_status(qspid, status);
			status[1] = s25fl1xx_read_status2(qspid);
			delay_ms(50);
		}
	}
}

/**
 * \brief Enables critical writes operation on a serial flash device, such as sector
 * protection, status register, etc.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 * \param byte_align  Burst wrap length to be set.
 */
void s25fl1xx_enable_wrap(struct qspid_t *qspid, uint8_t byte_align)
{
	uint8_t status[3];

	status[0] = s25fl1xx_read_status1(qspid);
	status[1] = s25fl1xx_read_status2(qspid);
	status[2] = s25fl1xx_read_status3(qspid);

	status[2] |= (byte_align << 5);

	dev->inst_frame.bm.b_dummy_cycles = 24;
	s25fl1xx_exec_command(qspid, S25FL1XX_WRAP_ENABLE,(uint32_t *)&status[2], 0,  QSPI_WRITE_ACCESS, 1);

	s25fl1xx_write_volatile_status(qspid, status);
	status[2] = s25fl1xx_read_status3(qspid);
	while(!(status[2] & 0x10));
}

/**
 * \brief Enables critical writes operation on a serial flash device, such as sector
 * protection, status register, etc.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 * \param latency Latency control.
 */
void s25fl1xx_set_read_latency_control(struct qspid_t *qspid, uint8_t latency)
{
	uint8_t status[3];

	status[0] = s25fl1xx_read_status1(qspid);
	status[1] = s25fl1xx_read_status2(qspid);
	status[2] = s25fl1xx_read_status3(qspid);

	status[2] |= latency;

	qspid->qspi_buffer.data_tx = (uint32_t *)&status[2];
	while((status[2] & S25FL1XX_STATUS_LATENCY_CTRL) != latency) {
		s25fl1xx_write_volatile_status(qspid, status);
		status[2] = s25fl1xx_read_status3(qspid);
		delay_ms(50);
	}
}

/**
 * \brief s25fl1d software reset.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 */
void s25fl1xx_soft_reset(struct qspid_t *qspid)
{
	s25fl1xx_exec_command(qspid, S25FL1XX_SOFT_RESET_ENABLE,0, 0,  QSPI_CMD_ACCESS, 0);
	s25fl1xx_exec_command(qspid, S25FL1XX_SOFT_RESET, 0, 0, QSPI_CMD_ACCESS, 0);
}

/**
 * \brief Unprotected the contents of the serial flash device.
 *
 * \param qspid  Pointer to an S25FL1 driver instance.
 *
 * \return 0 if the device has been protected; otherwise returns
 * S25FL1D_ERROR_PROTECTED.
 */
uint8_t s25fl1xx_protect(struct qspid_t *qspid)
{
	uint8_t status[3];
	/* Get the status register value to check the current protection */
	status[0]= s25fl1xx_read_status1(qspid);
	status[1]= s25fl1xx_read_status2(qspid);
	status[2]= s25fl1xx_read_status3(qspid);

	/* Check if sector protection registers are locked */
	if ((status[0] & S25FL1XX_STATUS_SPRL) == S25FL1XX_STATUS_SPRL_LOCKED) {
		return 0;
	}

	status[0] |= (S25FL1XX_STATUS_SWP | S25FL1XX_STATUS_SPRL);
	s25fl1xx_write_status(qspid, status);

	/* Check the new status */
	status[0] = s25fl1xx_read_status(qspid);
	if ((status[0] & (S25FL1XX_STATUS_SPRL | S25FL1XX_STATUS_SWP)) != (S25FL1XX_STATUS_SPRL | S25FL1XX_STATUS_SWP)) {
		return S25FL1XX_ERROR_PROTECTED;
	}
	else {
		return 0;
	}
}

/**
 * \brief Unprotected the control bits of the serial flash device.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 *
 * \return 0 if the device has been unprotected; otherwise returns
 * S25FL1D_ERROR_PROTECTED.
 * \return S25FL1 protection status.
 */
uint8_t s25fl1xx_unprotect(struct qspid_t *qspid)
{
	uint8_t status[3];
	/* Get the status register value to check the current protection */
	status[0]= s25fl1xx_read_status1(qspid);
	status[1]= s25fl1xx_read_status2(qspid);
	status[2]= s25fl1xx_read_status3(qspid);
	if ((status[0] & S25FL1XX_STATUS_SWP) == S25FL1XX_STATUS_SWP_PROTNONE) {
		/* Protection already disabled */
		return 0;
	}

	status[0] &= (~S25FL1XX_STATUS_SWP);
	/* Check if sector protection registers are locked */
	if ((status[0] & S25FL1XX_STATUS_SPRL) == S25FL1XX_STATUS_SPRL_LOCKED) {
		status[0] &= (~S25FL1XX_STATUS_SPRL);
		/* Unprotected sector protection registers by writing the status reg. */
		s25fl1xx_write_status(qspid, status);
	}
	s25fl1xx_write_status(qspid, status);

	/* Check the new status */
	status[0] = s25fl1xx_read_status1(qspid);
	if (status[0] & (S25FL1XX_STATUS_SPRL | S25FL1XX_STATUS_SWP)) {
		return S25FL1XX_ERROR_PROTECTED;
	}
	else {
		return 0;
	}
}

/**
 * \brief Protect the contents of the serial flash device.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 * \param dir  Data protect direction.
 * \param size  Data size to be protect.
 *
 * \return 0 if the device has been unprotected; otherwise returns
 * S25FL1D_ERROR_PROTECTED.
 */
uint8_t s25fl1xx_data_protect(struct qspid_t *qspid, bool dir, enum block_size protect_size)
{
	uint8_t status[3];
	uint32_t mask = (dir << 5);
	if(protect_size >= S25FL1XX_SIZE_64K) {
		mask |= (1 << 6);
		mask |= ((protect_size - S25FL1XX_SIZE_32K) << 2);
	} else {
		mask |= (protect_size << 2);
	}

	/* Get the status register value to check the current protection */
	status[0]= s25fl1xx_read_status1(qspid);
	status[1]= s25fl1xx_read_status2(qspid);
	status[2]= s25fl1xx_read_status3(qspid);

	if ((status[0] & mask) == mask) {
		/* Protection already enabled */
		return 0;
	}

	status[0] = mask;
	s25fl1xx_write_status(qspid, status);

	/* Check the new status */
	status[0] = s25fl1xx_read_status(qspid);
	if ((status[0] & mask) != mask) {
		return S25FL1XX_ERROR_PROTECTED;
	}
	else {
		return 0;
	}
}

/**
 * \brief Unprotected the contents of the serial flash device.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 *
 * \return 0 if the device has been unprotected; otherwise returns
 * S25FL1D_ERROR_PROTECTED.
 */
uint8_t s25fl1xx_data_unprotect(struct qspid_t *qspid)
{
	uint8_t status[3];
	/* Get the status register value to check the current protection */
	status[0]= s25fl1xx_read_status1(qspid);
	status[1]= s25fl1xx_read_status2(qspid);
	status[2]= s25fl1xx_read_status3(qspid);
	if (!(status[0] & S25FL1XX_CHIP_PROTECT_Msk)) {
		/* Protection already disabled */
		return 0;
	}

	status[0] &= (~S25FL1XX_CHIP_PROTECT_Msk);
	s25fl1xx_write_status(qspid, status);

	/* Check the new status */
	status[0] = s25fl1xx_read_status(qspid);
	if (status[0] & S25FL1XX_CHIP_PROTECT_Msk) {
		return S25FL1XX_ERROR_PROTECTED;
	}
	else {
		return 0;
	}
}

/**
 * \brief Erases all the content of the memory chip.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 *
 * \return 0 if the device has been unprotected; otherwise returns
 * ERROR_PROTECTED.
 */
uint8_t s25fl1xx_erase_chip(struct qspid_t *qspid)
{
	uint8_t i=0;
	uint8_t status = S25FL1XX_STATUS_RDYBSY;
	uint8_t chip_status= s25fl1xx_read_status1(qspid);

	if(chip_status & S25FL1XX_CHIP_PROTECT_Msk) {
		return 1;
	} else {
		s25fl1xx_enable_write(qspid);
		s25fl1xx_exec_command(qspid, S25FL1XX_CHIP_ERASE_2, 0, 0, QSPI_CMD_ACCESS, 0);

		while(status & S25FL1XX_STATUS_RDYBSY) {
			delay_ms(200);
			i++;
			status = s25fl1xx_read_status1(qspid);
			i = i % 4;
		}
		return 0;
	}
}

/**
 *\brief  Erases the specified block of the serial firmware dataflash.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 * \param address  Address of the block to erase.
 *
 * \return 0 if successful; otherwise returns ERROR_PROTECTED if the
 * device is protected or ERROR_BUSY if it is busy executing a command.
 */
uint8_t s25fl1xx_erase_sector(struct qspid_t *qspid,uint32_t address)
{
	uint8_t status;
	/* Check that the flash is ready and unprotected */
	status = s25fl1xx_read_status1(qspid);
	if ((status & S25FL1XX_STATUS_RDYBSY) != S25FL1XX_STATUS_RDYBSY_READY) {
		return S25FL1XX_ERROR_BUSY;
	}
	else if (status & S25FL1XX_BLOCK_PROTECT_Msk) {
		if(s25fl1xx_check_protected_addr(status, address)) {
			return S25FL1XX_ERROR_PROTECTED;
		}
	}

	/* Enable critical write operation */
	s25fl1xx_enable_write(qspid);

	dev->addr = address;
	dev->inst_frame.bm.b_addr_en = 1;
	/* Start the block erase command */
	s25fl1xx_exec_command(qspid, S25FL1XX_BLOCK_ERASE_4K, 0, 0, QSPI_CMD_ACCESS, 0);

	/* Wait for transfer to finish */
	s25fl1xx_wait_memory_access_end(qspid);

	return 0;
}

/**
 *\brief  Erases the specified 64KB block of the serial firmware dataflash.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 * \param address  Address of the block to erase.
 *
 * \return 0 if successful; otherwise returns ERROR_PROTECTED if the
 * device is protected or ERROR_BUSY if it is busy executing a command.
 */
uint8_t s25fl1xx_erase_64k_block(struct qspid_t *qspid, uint32_t address)
{
	uint8_t status;

	/* Check that the flash is ready and unprotected */
	status = s25fl1xx_read_status(qspid);
	if ((status & S25FL1XX_STATUS_RDYBSY) != S25FL1XX_STATUS_RDYBSY_READY) {
		return S25FL1XX_ERROR_BUSY;
	}
	else if ((status & S25FL1XX_STATUS_SWP) != S25FL1XX_STATUS_SWP_PROTNONE) {
		return S25FL1XX_ERROR_PROTECTED;
	}

	/* Enable critical write operation */
	s25fl1xx_enable_write(qspid);

	dev->addr = address;
	dev->inst_frame.bm.b_addr_en = 1;
	/* Start the block erase command */
	s25fl1xx_exec_command(qspid, S25FL1XX_BLOCK_ERASE_64K, 0, 0, QSPI_CMD_ACCESS, 0);

	/* Wait for transfer to finish */
	s25fl1xx_wait_memory_access_end(qspid);

	return 0;
}

/**
 * \brief Writes data at the specified address on the serial firmware dataflash. The
 * page(s) to program must have been erased prior to writing. This function
 * handles page boundary crossing automatically.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 * \param pData  Data buffer.
 * \param size  Number of bytes in buffer.
 * \param address  Write address.
 * \param secure  Enable or disable scramble on QSPI.
 *
 * \return 0 if successful; otherwise, returns ERROR_PROGRAM is there has
 * been an error during the data programming.
 */
 uint8_t s25fl1xx_write(struct qspid_t *qspid, uint32_t *pdata, uint32_t size, uint32_t address, uint8_t secure)
{
	uint32_t i = 0;

	 /** Size / page_zize */
	uint32_t  number_of_writes = (size >> 8);
	uint32_t addr = address;

	/** If less than page size */
	if(number_of_writes == 0) {
		s25fl1xx_enable_write(qspid);
		s25fl1xx_wait_memory_access_end(qspid);
		s25fl1xx_memory_access(qspid, S25FL1XX_BYTE_PAGE_PROGRAM , addr, pdata, 0,  QSPI_WRITE_ACCESS, size, secure);
		s25fl1xx_wait_memory_access_end(qspid);
		s25fl1xx_disable_write(qspid);
	} else {
		/** Multiple page */
		for(i=0; i< number_of_writes; i++) {
			s25fl1xx_enable_write(qspid);
			s25fl1xx_wait_memory_access_end(qspid);
			s25fl1xx_memory_access(qspid, S25FL1XX_BYTE_PAGE_PROGRAM , addr, pdata, 0, QSPI_WRITE_ACCESS, PAGE_SIZE, secure);
			s25fl1xx_wait_memory_access_end(qspid);
			s25fl1xx_disable_write(qspid);
			pdata += (PAGE_SIZE >> 2);
			addr += PAGE_SIZE;
		}
		if(size % PAGE_SIZE) {
			s25fl1xx_enable_write(qspid);
			s25fl1xx_wait_memory_access_end(qspid);
			s25fl1xx_memory_access(qspid, S25FL1XX_BYTE_PAGE_PROGRAM , addr, pdata, 0, QSPI_WRITE_ACCESS, (size - (number_of_writes * PAGE_SIZE)), secure);
			s25fl1xx_wait_memory_access_end(qspid);
			s25fl1xx_disable_write(qspid);
		}
	}
	return 0;
}

/**
 * \brief Reads data from the specified address on the serial flash.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 * \param data  Data buffer.
 * \param size  Number of bytes to read.
 * \param address  Read address.
 *
 * \return 0 if successful; otherwise, fail.
 */
 uint8_t s25fl1xx_read(struct qspid_t *qspid, uint32_t *data,  uint32_t size, uint32_t address)
{
	uint8_t secure = 0;
	mem->inst_frame.bm.b_dummy_cycles = 8;
	s25fl1xx_memory_access(qspid, S25FL1XX_READ_ARRAY , address, 0, data, QSPI_READ_ACCESS, size, secure);

	return 0;
}

/**
 * \brief Reads data from the specified address on the serial flash.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 * \param data  Data buffer.
 * \param size  Number of bytes to read.
 * \param address  Read address.
 *
 * \return 0 if successful; otherwise, fail.
 */
 uint8_t s25fl1xx_read_dual(struct qspid_t *qspid, uint32_t *data, uint32_t size, uint32_t address)
{
	uint8_t secure = 0;

	mem->inst_frame.bm.b_dummy_cycles = 8;
	mem->inst_frame.bm.b_width = QSPI_IFR_WIDTH_DUAL_OUTPUT;

	s25fl1xx_memory_access(qspid, S25FL1XX_READ_ARRAY_DUAL , address, 0, data, QSPI_READ_ACCESS, size, secure);

	return 0;
}

/**
 * \brief Reads data from the specified address on the serial flash.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 * \param data  Data buffer.
 * \param size  Number of bytes to read.
 * \param address  Read address.
 *
 * \return 0 if successful; otherwise, fail.
 */
 uint8_t s25fl1xx_read_quad(struct qspid_t *qspid, uint32_t *data, uint32_t size, uint32_t address)
{
	uint8_t secure = 0;
	mem->inst_frame.bm.b_dummy_cycles  = 8;
	mem->inst_frame.bm.b_width = QSPI_IFR_WIDTH_QUAD_OUTPUT;
	s25fl1xx_memory_access(qspid, S25FL1XX_READ_ARRAY_QUAD,  address, 0, data, QSPI_READ_ACCESS, size, secure);

	return 0;
}

/**
 * \brief Reads data from the specified address on the serial flash.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 * \param data  Data buffer.
 * \param size  Number of bytes to read.
 * \param address  Read address.
 * \param cont_mode  Continue read mode.
 * \param secure  Enable or disable scramble on QSPI.
 *
 * \return 0 if successful; otherwise, fail.
 */
 uint8_t s25fl1xx_read_dual_io(struct qspid_t *qspid, uint32_t *data, uint32_t size, uint32_t address,
									uint8_t cont_mode, uint8_t secure)
{
	mem->inst_frame.bm.b_dummy_cycles = 4;
	if(cont_mode) {
		mem->inst_frame.bm.b_opt_len= (QSPI_IFR_OPTL_OPTION_4BIT >> QSPI_IFR_OPTL_Pos);
		qspid->qspi_command.option = 0x02;

		mem->inst_frame.bm.b_continues_read = cont_mode;
		mem->inst_frame.bm.b_dummy_cycles = 3;
	}

	mem->inst_frame.bm.b_width = QSPI_IFR_WIDTH_DUAL_IO;

	s25fl1xx_memory_access(qspid, S25FL1XX_READ_ARRAY_DUAL_IO , address, 0, data, QSPI_READ_ACCESS, size, secure);

	mem->inst_frame.bm.b_opt_en = 0;
	mem->inst_frame.bm.b_continues_read  = 0;

	return 0;
}

/**
 * \brief Reads data from the specified address on the serial flash.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 * \param data  Data buffer.
 * \param size  Number of bytes to read.
 * \param address  Read address.
 * \param cont_mode  Continue read mode.
 * \param secure  Enable or disable scramble on QSPI.
 *
 * \return 0 if successful; otherwise, fail.
 */
 uint8_t s25fl1xx_read_quad_io(struct qspid_t *qspid, uint32_t *data, uint32_t size, uint32_t address,
									uint8_t cont_mode, uint8_t secure)
{
	mem->inst_frame.bm.b_dummy_cycles = 6;
	if(cont_mode) {
		mem->inst_frame.bm.b_opt_len= (QSPI_IFR_OPTL_OPTION_4BIT >> QSPI_IFR_OPTL_Pos);
		qspid->qspi_command.option = 0x02;
		mem->inst_frame.bm.b_continues_read = cont_mode;
		mem->inst_frame.bm.b_dummy_cycles = 5;
		mem->inst_frame.bm.b_opt_en = 1;
	}

	mem->inst_frame.bm.b_width = QSPI_IFR_WIDTH_QUAD_IO;

	s25fl1xx_memory_access(qspid, S25FL1XX_READ_ARRAY_QUAD_IO , address, 0, data, QSPI_READ_ACCESS, size, secure);

	mem->inst_frame.bm.b_opt_en = 0;
	mem->inst_frame.bm.b_continues_read  = 0;

	return 0;
}

/**
 * \brief Issue 'CContinuous Read Mode' command, the device can return to normal
 * SPI command mode, in which all commands can be accepts.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 */
void s25fl1xx_continous_read_mode_reset(struct qspid_t *qspid)
{
	s25fl1xx_exec_command(qspid, S25FL1XX_CONT_MODE_RESET, 0, 0, QSPI_CMD_ACCESS, 0);
}

/**
 * \brief Reads data from the specified address on the serial flash.
 *
 * \param qspid  Pointer to an S25FL1 qspid_t struct.
 */
void s25fl1xx_enter_continous_read_mode(struct qspid_t *qspid)
{
	uint32_t data;
	mem->inst_frame.bm.b_opt_len= (QSPI_IFR_OPTL_OPTION_4BIT >> QSPI_IFR_OPTL_Pos);
	qspid->qspi_command.option = 0x02;
	mem->inst_frame.bm.b_continues_read = 1;
	mem->inst_frame.bm.b_dummy_cycles = 5;
	mem->inst_frame.bm.b_opt_en = 1;
	mem->inst_frame.bm.b_width = QSPI_IFR_WIDTH_QUAD_IO;

	s25fl1xx_memory_access(qspid, S25FL1XX_READ_ARRAY_QUAD_IO , 0, 0, &data, QSPI_READ_ACCESS, 1, 0);

	mem->inst_frame.bm.b_opt_en = 0;
	mem->inst_frame.bm.b_continues_read  = 0;
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