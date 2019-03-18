/**
 * \file
 *
 * \brief Unit tests for SPI driver.
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

#include <stdint.h>
#include <stdbool.h>
#include <board.h>
#include <sysclk.h>
#include <spi.h>
#include <string.h>
#include <unit_test/suite.h>
#include <stdio_serial.h>
#include <conf_test.h>
#include <conf_board.h>

/**
 * \mainpage
 *
 * \section intro Introduction
 * This is the unit test application for the SPI driver.
 * It consists of test cases for the following functionalities:
 * - SPI Reset/Enable/Disable
 * - SPI Tx/Rx (loopback)
 * - SPI DataFlash operations (if there is DataFlash on board)
 * - SPI Write Protection
 *
 * \section files Main Files
 * - \ref unit_tests.c
 * - \ref conf_test.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_usart_serial.h
 *
 * \section device_info Device Info
 * All SAM devices can be used.
 * This example has been tested with the following setup:
 * - sam3n4c_sam3n_ek
 * - sam3s4c_sam3s_ek
 * - sam3sd8c_sam3s_ek2
 * - sam3u4e_sam3u_ek
 * - sam3x8h_sam3x_ek
 * - sam4s16c_sam4s_ek
 * - sam4sd32c_sam4s_ek2
 * - sam4e16e_sam4e_ek
 * - sam4lc4c_sam4l_ek
 * - sam4lc4c_sam4l_xplained_pro
 * - sam4lc8c_sam4l8_xplained_pro
 * - sam4n16c_sam4n_xplained_pro
 * - sam4c16c_sam4c_ek
 * - sam4cp16b_sam4cp16bmb
 * - sam4cmp16c_sam4cmp_db
 * - sam4cms16c_sam4cms_db
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for ARM. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */

//! \name Unit test configuration
//@{
/**
 * \def CONF_TEST_SPI
 * \brief SPI instance to perform unit tests on.
 */
/**
 * \def CONF_TEST_USART
 * \brief USART to redirect STDIO to.
 */
/**
 * \def CONF_TEST_BAUDRATE
 * \brief Baudrate of USART.
 */
/**
 * \def CONF_TEST_CHARLENGTH
 * \brief Character length (bits) of USART.
 */
/**
 * \def CONF_TEST_PARITY
 * \brief Parity mode of USART.
 */
/**
 * \def CONF_TEST_STOPBITS
 * \brief Stopbit configuration of USART.
 */

/**
 * \def CONF_TEST_SPI
 * \brief SPI base for test.
 */
/**
 * \def CONF_TEST_SPI_ID
 * \brief SPI ID for test.
 */
/**
 * \def CONF_TEST_SPI_NPCS
 * \brief NPCS used for test.
 */
/**
 * \def CONF_TEST_SPI_HANDLER
 * \brief SPI handler for vector table.
 * \see exceptions.h
 */

/**
 * \def CONF_TEST_DF
 * \brief Defined to enable on-board dataflash test.
 * \note DataFlash test will use the previously defined Base and ID of SPI.
 * \note The following *_DF_* is used only when \ref CONF_TEST_DF is defined.
 */
/**
 * \def CONF_TEST_DF_NPCS
 * \brief NPCS used for SPI to communicate with DataFlash.
 */
/**
 * \def CONF_TEST_DF_ID
 * \brief DataFlash ID expected.
 */
/**
 * \def CONF_TEST_DF_PAGE_SIZE
 * \brief Page size for the DataFlash.
 */
/**
 * \def CONF_TEST_DF_ADDRESS
 * \brief DataFlash address used for Erase-Write-Read test.
 */
//@}

/** Convert ns to SPI DLYBS */
#define ns_to_dlybs(ck, ns)   ((((ns) * ((ck) / 1000000)) / 1000) + 1)
/** Convert ns to SPI DLYBCT */
#define ns_to_dlybct(ck, ns)  ((((ns) / 32 * ((ck) / 1000000)) / 1000) + 1)

/** Clock polarity */
#define SPI_CLK_POLARITY 1
/** Clock phase */
#define SPI_CLK_PHASE    0
/** Delay before SPCK */
#define SPI_DLYBS        0x40
/** Delay between consecutive transfers */
#define SPI_DLYBCT       0x10

/** PCS to use for test */
#define TEST_PCS         ((~(1u << CONF_TEST_SPI_NPCS)) & 0xF)
/** Byte to transfer for test */
#define TEST_PATTERN     0xA5
/** Test SPI clock */
#define TEST_CLOCK       10000000

#ifdef CONF_TEST_DF
/** PCS to use for DF test */
# define TEST_DF_PCS     ((~(1u << CONF_TEST_DF_NPCS)) & 0xF)
/** DLYBS to use for DF */
# define TEST_DF_DLYBS   ns_to_dlybs(sysclk_get_cpu_hz(), 10)
/** DLYBCT to use for DF */
# define TEST_DF_DLYBCT  ns_to_dlybct(sysclk_get_cpu_hz(), 5)
#endif

/** Register offset for _MR */
#define OFFSET_MR        0x04
/** Register offset for _IMR */
#define OFFSET_IER       0x14
/** Register offset for _CSR */
#define OFFSET_CSR       0x30

/** TX interrupt occurred */
volatile bool g_b_spi_interrupt_tx_ready = false;
/** RX interrupt occurred */
volatile bool g_b_spi_interrupt_rx_ready = false;

/**
 * \brief Test SPI interrupt handler.
 */
void CONF_TEST_SPI_HANDLER(void)
{
	uint32_t status = spi_read_status(CONF_TEST_SPI);

	if (status & SPI_SR_TDRE) {
		g_b_spi_interrupt_tx_ready = true;
		spi_disable_interrupt(CONF_TEST_SPI, SPI_IDR_TDRE);
	}

	if (status & SPI_SR_RDRF) {
		g_b_spi_interrupt_rx_ready = true;
		spi_disable_interrupt(CONF_TEST_SPI, SPI_IDR_RDRF);
	}
}

/**
 * \brief Test SPI setting.
 *
 * This test tests SPI reset/enable/disable.
 *
 * \param test Current test case.
 */
static void run_spi_ctrl_test(const struct test_case *test)
{
	spi_enable_clock(CONF_TEST_SPI);

	/* Test enable */
	spi_enable(CONF_TEST_SPI);
	test_assert_true(test,  spi_is_enabled(CONF_TEST_SPI),
		"Test SPI enable: enable failed");

	/* Test reset */
	spi_reset(CONF_TEST_SPI);
	test_assert_true(test,
		!spi_is_enabled(CONF_TEST_SPI) &&
		CONF_TEST_SPI->SPI_MR == 0 &&
		CONF_TEST_SPI->SPI_IMR == 0 &&
		CONF_TEST_SPI->SPI_CSR[0] == 0 &&
		CONF_TEST_SPI->SPI_CSR[1] == 0 &&
		CONF_TEST_SPI->SPI_CSR[2] == 0 &&
		CONF_TEST_SPI->SPI_CSR[3] == 0 &&
#if SAM4L
		CONF_TEST_SPI->SPI_WPCR == 0,
#else
		CONF_TEST_SPI->SPI_WPMR == 0,
#endif
		"Test SPI reset: should have read 0");
}

/**
 * \brief Test SPI transfer.
 *
 * This test tests SPI read/write.
 *
 * \param test Current test case.
 */
static void run_spi_trans_test(const struct test_case *test)
{
	spi_status_t rc;
	uint16_t     spi_data;
	uint8_t      spi_pcs;

	spi_reset(CONF_TEST_SPI);
	spi_set_lastxfer(CONF_TEST_SPI);
	spi_set_master_mode(CONF_TEST_SPI);
	spi_disable_mode_fault_detect(CONF_TEST_SPI);
	spi_set_peripheral_chip_select_value(CONF_TEST_SPI, CONF_TEST_SPI_NPCS);
	spi_set_clock_polarity(CONF_TEST_SPI,
		CONF_TEST_SPI_NPCS, SPI_CLK_POLARITY);
	spi_set_clock_phase(CONF_TEST_SPI, CONF_TEST_SPI_NPCS, SPI_CLK_PHASE);
	spi_set_bits_per_transfer(CONF_TEST_SPI,
		CONF_TEST_SPI_NPCS, SPI_CSR_BITS_8_BIT);
	spi_set_baudrate_div(CONF_TEST_SPI,
		CONF_TEST_SPI_NPCS,
		(
#if (SAM4L)
		sysclk_get_pba_hz()
#else
		sysclk_get_peripheral_hz()
#endif
		/ TEST_CLOCK));
	spi_set_transfer_delay(CONF_TEST_SPI,
		CONF_TEST_SPI_NPCS, SPI_DLYBS, SPI_DLYBCT);
	spi_set_variable_peripheral_select(CONF_TEST_SPI);
	spi_enable_loopback(CONF_TEST_SPI);

	/* Test read/write timeout: should return SPI_ERROR_TIMEOUT. */
	rc = spi_write(CONF_TEST_SPI, TEST_PATTERN, TEST_PCS, 1);
	test_assert_true(test, rc == SPI_ERROR_TIMEOUT,
		"Test SPI Write timeout: return code should not be %d", rc);

	rc = spi_read(CONF_TEST_SPI, &spi_data, &spi_pcs);
	test_assert_true(test, rc == SPI_ERROR_TIMEOUT,
		"Test SPI Read timeout: return code should not be %d", rc);

	spi_enable(CONF_TEST_SPI);
	spi_enable_interrupt(CONF_TEST_SPI, SPI_IER_TDRE|SPI_IER_RDRF);
	NVIC_EnableIRQ((IRQn_Type)CONF_TEST_SPI_ID);

	/* Test write: should return OK. */
	rc = spi_write(CONF_TEST_SPI, TEST_PATTERN, TEST_PCS, 1);
	test_assert_true(test, rc == SPI_OK,
		"Test SPI Write: return code should not be %d", rc);

	/* Test read: should return OK with what is sent. */
	rc = spi_read(CONF_TEST_SPI, &spi_data, &spi_pcs);
	test_assert_true(test, rc == SPI_OK,
		"Test SPI Read: return code should not be %d", rc);
	test_assert_true(test, spi_data == TEST_PATTERN,
		"Unexpected SPI data: %x, should be %x",
		spi_data, TEST_PATTERN);
	test_assert_true(test, spi_pcs == TEST_PCS,
		"Unexpected SPI PCS: %x, should be %x",
		spi_pcs, TEST_PCS);

	/* Check interrupts. */
	test_assert_true(test, g_b_spi_interrupt_tx_ready,
		"Test SPI TX interrupt not detected");
	test_assert_true(test, g_b_spi_interrupt_rx_ready,
		"Test SPI RX interrupt not detected");

	/* Done, disable SPI and all interrupts. */
	spi_disable_loopback(CONF_TEST_SPI);
	spi_disable(CONF_TEST_SPI);
	spi_disable_interrupt(CONF_TEST_SPI, 0xFFFFFFFF);
	NVIC_DisableIRQ((IRQn_Type)CONF_TEST_SPI_ID);
}


#ifdef CONF_TEST_DF
/** SPI command to send */
typedef struct spi_command {
	uint8_t* data;
	uint8_t* cmd;
	uint16_t data_size;
	uint8_t  cmd_size:7,
	         cmd_rx:1;
	uint8_t  dummy_size;
} spi_cmd_t;

/** AT25 command struct */
typedef struct at25_command {
	uint32_t op_code:8,  /** Opcode */
		address_h:8,     /** Address high byte */
		address_m:8,     /** Address medium byte */
		address_l;       /** Address low byte */
} at25_cmd_t;

/** Device ready/busy status bit. */
#define AT25_STATUS_RDYBSY          (1 << 0)
/** Device is ready. */
#define AT25_STATUS_RDYBSY_READY    (0 << 0)
/** Device is busy with internal operations. */
#define AT25_STATUS_RDYBSY_BUSY     (1 << 0)
/** Write enable latch status bit. */
#define AT25_STATUS_WEL             (1 << 1)
/** Device is not write enabled. */
#define AT25_STATUS_WEL_DISABLED    (0 << 1)
/** Device is write enabled. */
#define AT25_STATUS_WEL_ENABLED     (1 << 1)
/** Software protection status bitfield. */
#define AT25_STATUS_SWP             (3 << 2)
/** All sectors are software protected. */
#define AT25_STATUS_SWP_PROTALL     (3 << 2)
/** Some sectors are software protected. */
#define AT25_STATUS_SWP_PROTSOME    (1 << 2)
/** No sector is software protected. */
#define AT25_STATUS_SWP_PROTNONE    (0 << 2)
/** Write protect pin status bit. */
#define AT25_STATUS_WPP             (1 << 4)
/** Write protect signal is not asserted. */
#define AT25_STATUS_WPP_NOTASSERTED (0 << 4)
/** Write protect signal is asserted. */
#define AT25_STATUS_WPP_ASSERTED    (1 << 4)
/** Erase/program error bit. */
#define AT25_STATUS_EPE             (1 << 5)
/** Erase or program operation is successful. */
#define AT25_STATUS_EPE_SUCCESS     (0 << 5)
/** Erase or program error detected. */
#define AT25_STATUS_EPE_ERROR       (1 << 5)
/** Sector protection registers locked bit. */
#define AT25_STATUS_SPRL            (1 << 7)
/** Sector protection registers are unlocked. */
#define AT25_STATUS_SPRL_UNLOCKED   (0 << 7)
/** Sector protection registers are locked. */
#define AT25_STATUS_SPRL_LOCKED     (1 << 7)

/** Read array command code. */
#define AT25_READ_ARRAY             0x0B
/** Read array (low frequency) command code. */
#define AT25_READ_ARRAY_LF          0x03
/** Block erase command code (4K block). */
#define AT25_BLOCK_ERASE_4K         0x20
/** Block erase command code (32K block). */
#define AT25_BLOCK_ERASE_32K        0x52
/** Block erase command code (64K block). */
#define AT25_BLOCK_ERASE_64K        0xD8
/** Chip erase command code 1. */
#define AT25_CHIP_ERASE_1           0x60
/** Chip erase command code 2. */
#define AT25_CHIP_ERASE_2           0xC7
/** Byte/page program command code. */
#define AT25_BYTE_PAGE_PROGRAM      0x02
/** Sequential program mode command code 1. */
#define AT25_SEQUENTIAL_PROGRAM_1   0xAD
/** Sequential program mode command code 2. */
#define AT25_SEQUENTIAL_PROGRAM_2   0xAF
/** Write enable command code. */
#define AT25_WRITE_ENABLE           0x06
/** Write disable command code. */
#define AT25_WRITE_DISABLE          0x04
/** Protect sector command code. */
#define AT25_PROTECT_SECTOR         0x36
/** Unprotect sector command code. */
#define AT25_UNPROTECT_SECTOR       0x39
/** Read sector protection registers command code. */
#define AT25_READ_SECTOR_PROT       0x3C
/** Read status register command code. */
#define AT25_READ_STATUS            0x05
/** Write status register command code. */
#define AT25_WRITE_STATUS           0x01
/** Read manufacturer and device ID command code. */
#define AT25_READ_JEDEC_ID          0x9F
/** Deep power-down command code. */
#define AT25_DEEP_PDOWN             0xB9
/** Resume from deep power-down command code. */
#define AT25_RES_DEEP_PDOWN         0xAB

/**
 * \brief Send command to dataflash.
 * \return True for OK.
 */
static bool spi_send_cmd(spi_cmd_t *p_cmd)
{
	spi_status_t rc;
	int i;
	uint16_t data;
	uint8_t pcs, last = 0;

	/* Clear dummy byte */
	if (spi_is_rx_full(CONF_TEST_SPI))
		spi_read(CONF_TEST_SPI, &data, &pcs);

	/* Wait until no activity on bus */
	while(!spi_is_tx_empty(CONF_TEST_SPI));

	/* Send command */
	for (i = 0; i < p_cmd->cmd_size; i ++) {
		last = (i == (p_cmd->cmd_size-1)) &&
			(p_cmd->dummy_size == 0) &&
			(p_cmd->data_size == 0);
		rc = spi_write(CONF_TEST_SPI, p_cmd->cmd[i], TEST_DF_PCS, last);

		if (p_cmd->cmd_rx)
			rc |= spi_read(CONF_TEST_SPI, &data, &pcs);

		if (rc != SPI_OK)
			return false;
	}

	/* Send dummy clocks */
	for (i = 0; i < p_cmd->dummy_size; i ++) {
		rc  = spi_write(CONF_TEST_SPI, 0xFF, TEST_DF_PCS, 0);

		if (p_cmd->cmd_rx)
			rc |= spi_read(CONF_TEST_SPI, &data, &pcs);

		if (rc != SPI_OK)
			return false;
	}
	if (p_cmd->data_size == 0)
		return true;

	/* Read/Write data */
	for (i = 0; i < p_cmd->data_size; i ++) {
		last = (i == (p_cmd->data_size-1));

		rc  = spi_write(CONF_TEST_SPI, p_cmd->data[i], TEST_DF_PCS, last);

		if (p_cmd->cmd_rx)
			rc |= spi_read(CONF_TEST_SPI, &data, &pcs);

		if (rc != SPI_OK)
			return false;

		if (p_cmd->cmd_rx)
			p_cmd->data[i] = (uint8_t)data;
	}
	return true;
}

/**
 * \brief Read status register of serial flash.
 * \param p_status Pointer to fill status result.
 * \return True if OK.
 */
static bool at25_read_status(uint8_t *p_status)
{
	at25_cmd_t at25_cmd = {
		.op_code = AT25_READ_STATUS,
	};

	spi_cmd_t  spi_cmd = {
		.data = p_status,
		.cmd  = (uint8_t*)&at25_cmd,
		.cmd_size = 1,
		.cmd_rx = 1,
		.dummy_size = 1,
		.data_size = 1
	};

	return spi_send_cmd(&spi_cmd);
}

/**
 * \brief Wait until serial flash is ready.
 * \param p_status Optional pointer to return the latest status.
 * \return True if OK.
 */
static bool at25_wait(uint8_t *p_status)
{
	uint8_t status = AT25_STATUS_RDYBSY;

	while (status & AT25_STATUS_RDYBSY) {
		if (at25_read_status(&status) == false)
			return false;
	}

	if (p_status)
		*p_status = status;
	return true;
}

/**
 * \brief Read the ID of serial flash.
 * \param p_id Pointer to fill ID result (word of 4 bytes).
 * \return True if OK.
 */
static bool at25_read_id(uint32_t *p_id)
{
	at25_cmd_t at25_cmd = {
		.op_code = AT25_READ_JEDEC_ID,
	};

	spi_cmd_t  spi_cmd = {
		.data = (uint8_t*)p_id,
		.cmd  = (uint8_t*)&at25_cmd,
		.cmd_size = 1,
		.cmd_rx = 1,
		.dummy_size = 0,
		.data_size = 4
	};

	return spi_send_cmd(&spi_cmd);
}

/**
 * \brief Enable serial flash write.
 * \return True if OK.
 */
static bool at25_enable_write(void)
{
	at25_cmd_t at25_cmd = {
		.op_code = AT25_WRITE_ENABLE,
	};

	spi_cmd_t  spi_cmd = {
		.data = NULL,
		.cmd  = (uint8_t*)&at25_cmd,
		.cmd_size = 1,
		.cmd_rx = 0,
		.dummy_size = 0,
		.data_size = 0
	};

	return spi_send_cmd(&spi_cmd);
}

/**
 * \brief Erase 4K block.
 * \param address Serial flash internal address.
 * \return True if OK.
 */
static bool at25_erase_block_4k(const uint32_t address)
{
	bool rc;
	uint8_t status;

	at25_cmd_t at25_cmd = {
		.op_code = AT25_BLOCK_ERASE_4K
	};

	spi_cmd_t  spi_cmd = {
		.data = NULL,
		.cmd  = (uint8_t*)&at25_cmd,
		.cmd_size = 4,
		.cmd_rx = 0,
		.dummy_size = 0,
		.data_size = 0
	};

	at25_cmd.address_h = (address & 0xFF0000) >> 16;
	at25_cmd.address_m = (address & 0x00FF00) >>  8;
	at25_cmd.address_l = (address & 0x0000FF) >>  0;
	rc = at25_enable_write();
	if (!rc)
		return false;

	rc = spi_send_cmd(&spi_cmd);
	if (!rc)
		return false;

	rc = at25_wait(&status);
	if (!rc)
		return false;
	if (status & AT25_STATUS_EPE)
		return false;

	return true;
}

/**
 * \brief Unprotect a sector.
 * \param address Serial flash internal address.
 * \return True if OK.
 */
static bool at25_unprotect_sector(const uint32_t address)
{
	bool rc;
	uint8_t status;

	at25_cmd_t at25_cmd = {
		.op_code = AT25_UNPROTECT_SECTOR
	};

	spi_cmd_t  spi_cmd = {
		.data = NULL,
		.cmd  = (uint8_t*)&at25_cmd,
		.cmd_size = 4,
		.cmd_rx = 0,
		.dummy_size = 0,
		.data_size = 0
	};

	at25_cmd.address_h = (address & 0xFF0000) >> 16;
	at25_cmd.address_m = (address & 0x00FF00) >>  8;
	at25_cmd.address_l = (address & 0x0000FF) >>  0;
	rc = at25_enable_write();
	if (!rc)
		return false;

	rc = spi_send_cmd(&spi_cmd);
	if (!rc)
		return false;

	rc = at25_wait(&status);
	if (!rc)
		return false;
	if (status & AT25_STATUS_EPE)
		return false;

	return true;
}

/**
 * \brief Read from serial flash.
 * \param address Serial flash internal address.
 * \param p_buf Pointer to data buffer to fill.
 * \param size Data buffer size.
 * \return True if OK.
 */
static bool at25_read(const uint32_t address, uint8_t *p_buf, uint32_t size)
{
	at25_cmd_t at25_cmd = {
		.op_code = AT25_READ_ARRAY
	};

	spi_cmd_t  spi_cmd = {
		.data = p_buf,
		.cmd  = (uint8_t*)&at25_cmd,
		.cmd_size = 4,
		.cmd_rx = 1,
		.dummy_size = 1,
		.data_size = size
	};

	at25_cmd.address_h = (address & 0xFF0000) >> 16;
	at25_cmd.address_m = (address & 0x00FF00) >>  8;
	at25_cmd.address_l = (address & 0x0000FF) >>  0;

	return spi_send_cmd(&spi_cmd);
}

/**
 * \brief Write to serial flash.
 * \param address Serial flash internal address.
 * \param p_buf Pointer to data buffer to send.
 * \param size Data buffer size.
 * \return True if OK.
 */
static bool at25_write(const uint32_t address, uint8_t *p_buf, uint32_t size)
{
	bool rc;
	uint8_t status;

	at25_cmd_t at25_cmd = {
		.op_code = AT25_BYTE_PAGE_PROGRAM
	};

	spi_cmd_t  spi_cmd = {
		.data = p_buf,
		.cmd  = (uint8_t*)&at25_cmd,
		.cmd_size = 4,
		.cmd_rx = 0,
		.dummy_size = 0,
		.data_size = size
	};

	at25_cmd.address_h = (address & 0xFF0000) >> 16;
	at25_cmd.address_m = (address & 0x00FF00) >>  8;
	at25_cmd.address_l = (address & 0x0000FF) >>  0;
	rc = at25_enable_write();

	if (!rc)
		return false;

	rc = spi_send_cmd(&spi_cmd);
	if (!rc)
		return false;

	rc = at25_wait(&status);
	if (!rc)
		return false;
	if (status & AT25_STATUS_EPE)
		return false;

	return true;
}

/**
 * \brief Test SPI dataflash operations.
 * \param test Current test case.
 */
static void run_spi_dataflash_test(const struct test_case *test)
{
	bool rc;
	uint32_t spi_id;
	uint8_t  status = 0;
	uint8_t  pageBuffer[CONF_TEST_DF_PAGE_SIZE];
	uint32_t i;

	/* Initialize SPI for dataflash access */
	spi_set_master_mode(CONF_TEST_SPI);
	spi_set_variable_peripheral_select(CONF_TEST_SPI);
	spi_set_peripheral_chip_select_value(CONF_TEST_SPI, CONF_TEST_DF_NPCS);
	spi_set_clock_polarity(CONF_TEST_SPI,
		CONF_TEST_DF_NPCS, SPI_CLK_POLARITY);
	spi_set_clock_phase(CONF_TEST_SPI, CONF_TEST_DF_NPCS, SPI_CLK_PHASE);
	spi_set_bits_per_transfer(CONF_TEST_SPI,
		CONF_TEST_DF_NPCS, SPI_CSR_BITS_8_BIT);
	spi_set_baudrate_div(CONF_TEST_SPI,
		CONF_TEST_DF_NPCS,
        (
#if (SAM4L)
		sysclk_get_pba_hz()
#else
		sysclk_get_peripheral_hz()
#endif
		/ TEST_CLOCK));
	spi_set_transfer_delay(CONF_TEST_SPI,
		CONF_TEST_DF_NPCS,
		TEST_DF_DLYBS, TEST_DF_DLYBCT);
	spi_configure_cs_behavior(CONF_TEST_SPI,
		CONF_TEST_DF_NPCS, SPI_CS_KEEP_LOW);
	spi_enable(CONF_TEST_SPI);

	/* Read ID test */
	rc = at25_read_id(&spi_id);
	spi_id &= 0x00FFFFFF;
	test_assert_true(test, rc, "DataFlash ReadID failed");
	test_assert_true(test, spi_id == CONF_TEST_DF_ID,
		"DataFlash ID %x but expected is %x",
		spi_id, CONF_TEST_DF_ID);

	/* Unprotect flash */
	rc = at25_enable_write();
	test_assert_true(test, rc, "DataFlash enable Write failed");
	rc = at25_read_status(&status);
	test_assert_true(test, rc, "DataFlash read status failed");

	/* Unprotect sector */
	rc = at25_unprotect_sector(CONF_TEST_DF_ADDRESS);
	test_assert_true(test, rc, "DataFlash Unprotect sector failed");

	/* Erase a block for test */
	rc = at25_erase_block_4k(CONF_TEST_DF_ADDRESS);
	test_assert_true(test, rc, "DataFlash Erase4K failed");

	/* Read the page */
	rc = at25_read(CONF_TEST_DF_ADDRESS,
		pageBuffer, CONF_TEST_DF_PAGE_SIZE);
	test_assert_true(test, rc, "DataFlash Read failed");

	/* Blank check */
	for (i = 0; i < CONF_TEST_DF_PAGE_SIZE; i ++) {
		test_assert_true(test, pageBuffer[i] == 0xFF,
			"Page data @ %d is %x, expected 0xFF",
			i, pageBuffer[i]);
	}

	/* Program page test */
	for (i = 0; i < CONF_TEST_DF_PAGE_SIZE; i ++) {
		pageBuffer[i] = i;
	}
	rc = at25_write(CONF_TEST_DF_ADDRESS,
		pageBuffer, CONF_TEST_DF_PAGE_SIZE);
	test_assert_true(test, rc, "DataFlash Write failed");

	/* Check bytes */
	rc = at25_read(CONF_TEST_DF_ADDRESS, pageBuffer, CONF_TEST_DF_PAGE_SIZE);
	test_assert_true(test, rc, "DataFlash Read failed");
	for (i = 0; i < CONF_TEST_DF_PAGE_SIZE; i ++) {
		test_assert_true(test, pageBuffer[i] == i,
			"DataFlash data is not what expected, "
			"expected %x but got %x",
			i, pageBuffer[i]);
	}
}
#endif /* CONF_TEST_DF */


/**
 * \brief Test SPI write protection.
 * \param test Current test case.
 */
static void run_spi_writeprotect_test(const struct test_case *test)
{
	uint32_t wp_status;
	uint32_t wp_vsrc;
	uint32_t reg_backup;

	/* Enable write protect */
	spi_set_writeprotect(CONF_TEST_SPI, 1);

	/* Access _MR to generate violation */
	reg_backup = CONF_TEST_SPI->SPI_MR;
	CONF_TEST_SPI->SPI_MR = 0xFF;
	wp_status = spi_get_writeprotect_status(CONF_TEST_SPI);

	wp_vsrc = (wp_status&SPI_WPSR_WPVSRC_Msk) >> SPI_WPSR_WPVSRC_Pos;

	test_assert_true(test, (wp_status & SPI_WPSR_WPVS_Msk),
		"WriteProtection on _MR not detected");

	test_assert_true(test, wp_vsrc == OFFSET_MR,
		"WriteProtection on _MR src error, "
		"got %x but expect %x",
		wp_vsrc, OFFSET_MR);

	test_assert_true(test, reg_backup == CONF_TEST_SPI->SPI_MR,
		"_MR write not blocked");

	/* Access _CSR to generate violation */
	reg_backup = CONF_TEST_SPI->SPI_CSR[CONF_TEST_SPI_NPCS];
	CONF_TEST_SPI->SPI_CSR[CONF_TEST_SPI_NPCS] = 0;
	wp_status = spi_get_writeprotect_status(CONF_TEST_SPI);

	wp_vsrc = (wp_status&SPI_WPSR_WPVSRC_Msk) >> SPI_WPSR_WPVSRC_Pos;

	test_assert_true(test, (wp_status & SPI_WPSR_WPVS_Msk),
		"WriteProtection on _CS not detected");

	test_assert_true(test, wp_vsrc == (OFFSET_CSR + 4 * CONF_TEST_SPI_NPCS),
		"WriteProtection on _CSR src error, "
		"got %x but expect %x",
		wp_vsrc, (OFFSET_CSR + 4 * CONF_TEST_SPI_NPCS));

	test_assert_true(test, reg_backup ==
		CONF_TEST_SPI->SPI_CSR[CONF_TEST_SPI_NPCS],
		"_CSR write not blocked");

	/* Disable write protect */
	spi_set_writeprotect(CONF_TEST_SPI, 0);
}

/**
 * \brief Run SPI driver unit test.
 */
int main(void)
{
	const usart_serial_options_t usart_serial_options = {
		.baudrate   = CONF_TEST_BAUDRATE,
		.charlength = CONF_TEST_CHARLENGTH,
		.paritytype = CONF_TEST_PARITY,
		.stopbits   = CONF_TEST_STOPBITS
	};

	sysclk_init();
	board_init();

	stdio_serial_init(CONF_TEST_USART, &usart_serial_options);

	/* Define all the test cases */
	DEFINE_TEST_CASE(spi_ctrl_test, NULL, run_spi_ctrl_test, NULL,
		"SPI enable/disable and reset");
	DEFINE_TEST_CASE(spi_trans_test, NULL, run_spi_trans_test, NULL,
		"SPI transfer");
#ifdef CONF_TEST_DF
	DEFINE_TEST_CASE(spi_dataflash_test, NULL, run_spi_dataflash_test, NULL,
		"SPI flash");
#endif
	DEFINE_TEST_CASE(spi_wp_test, NULL, run_spi_writeprotect_test, NULL,
		"SPI write protection");

	/* Put test case addresses in an array */
	DEFINE_TEST_ARRAY(spi_tests) = {
		&spi_ctrl_test,
		&spi_trans_test,
#ifdef CONF_TEST_DF
		&spi_dataflash_test,
#endif
		&spi_wp_test
	};

	/* Define the test suite */
	DEFINE_TEST_SUITE(spi_suite, spi_tests, "SAM SPI driver test suite");

	/* Run all tests in the test suite */
	test_suite_run(&spi_suite);

	while (1) {
		/* Busy-wait forever */
	}
}
