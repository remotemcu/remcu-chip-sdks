/**
 * \file
 *
 * \brief Proxy PLC Controller interface layer implementation.
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

#include "string.h"
#include "pplc_if.h"
#include "conf_pplc_if.h"
#include "ioport.h"
#include "sysclk.h"
#include "spi.h"
#include "pdc.h"
#include "pio.h"
#include "pio_handler.h"

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/* @endcond */

/**
 * \weakgroup pplc_plc_group
 * @{
 */

/* PPLC clock setting (Hz). */
static uint32_t gs_ul_pplc_clock = PPLC_CLOCK;

/* PDC buffer us_size. */
#define PDC_PPLC_BUFFER_SIZE       800

/* Max number of folowing reads. */
#define MAX_NUM_READ_RX_COUNTER    10

/* PDC Receive buffer */
static uint8_t gs_pplc_rx_buffer[PDC_PPLC_BUFFER_SIZE];
/* PDC Transmission buffer */
static uint8_t gs_pplc_tx_buffer[PDC_PPLC_BUFFER_SIZE];
/* PDC RX data packet */
pdc_packet_t g_pplc_rx_packet;
/* PDC TX data packet */
pdc_packet_t g_pplc_tx_packet;
/* Pointer to PDC register base */
Pdc *g_pplc_pdc;

/* PPLC busy indication */
static uint8_t uc_pplc_is_busy;

/* PPLC chip select config value */
#define PPLC_PCS    spi_get_pcs(PPLC_CS)

/**
 * Describes an PPLC interrupt handler
 */
static void (*pplc_handler)(void);

static void pplc_if_int_handler(uint32_t ul_id, uint32_t ul_mask)
{
	UNUSED(ul_id);
	UNUSED(ul_mask);
	if (pplc_handler != NULL) {
		pplc_handler();
	}
}

/**
 * \internal
 * \brief Initialize Proxy PLC controller.
 *
 * This function will change the system clock prescaler configuration to
 * match the parameters.
 *
 * \note The parameters to this function are device-specific.
 *
 */
static void _pplc_if_config(void)
{
	uint32_t ul_cpuhz;
	uint8_t uc_div;

	ul_cpuhz = sysclk_get_cpu_hz();
	uc_div = ul_cpuhz / gs_ul_pplc_clock;

	/* Enable SPI peripheral. */
	spi_enable_clock(PPLC_SPI_MODULE);

	/* Reset SPI */
	spi_disable(PPLC_SPI_MODULE);
	spi_reset(PPLC_SPI_MODULE);

	/* Configure SPI */
	spi_set_master_mode(PPLC_SPI_MODULE);
	spi_disable_mode_fault_detect(PPLC_SPI_MODULE);
	spi_set_peripheral_chip_select_value(PPLC_SPI_MODULE, PPLC_PCS);
	spi_set_clock_polarity(PPLC_SPI_MODULE, PPLC_CS, 0);
	spi_set_clock_phase(PPLC_SPI_MODULE, PPLC_CS, 1);
	spi_set_bits_per_transfer(PPLC_SPI_MODULE, PPLC_CS, SPI_CSR_BITS_8_BIT);
	spi_set_fixed_peripheral_select(PPLC_SPI_MODULE);
	spi_set_baudrate_div(PPLC_SPI_MODULE, PPLC_CS, uc_div);
	spi_set_transfer_delay(PPLC_SPI_MODULE, PPLC_CS, PPLC_DLYBS,
			PPLC_DLYBCT);
	spi_configure_cs_behavior(PPLC_SPI_MODULE, PPLC_CS, SPI_CS_RISE_NO_TX);

	/* Get board PPLC PDC base address and enable receiver and transmitter */
	g_pplc_pdc = spi_get_pdc_base(PPLC_SPI_MODULE);
	spi_enable(PPLC_SPI_MODULE);
}

/**
 * \internal
 * \brief Transmit PPLC command to Proxy PLC controller
 *
 *  \param uc_cmd           PPLC command to send
 *  \param us_addr          Address where is the data to apply command
 *  \param us_len           Number of bytes in operation
 *  \param ptr_buf          Pointer to data buffer
 *  \param uc_bytes_rep     Number of repetitions(only use in PPLC_CMD_WRITE_REP
 * command)
 *
 * \retval true if there is no error
 * \retval false if there is an error
 */
static int8_t _pplc_cmd_op(uint8_t uc_cmd, uint16_t us_addr, uint16_t us_len,
		uint8_t *ptr_buf, uint8_t uc_bytes_rep)
{
	uint8_t *ptr_data_buf;
	uint16_t uc_num_tx_bytes;
	uint16_t us_data_len, us_data_len_acc;
	uint16_t us_address;

	Disable_global_interrupt();

	if (!uc_pplc_is_busy) {
		uc_pplc_is_busy = true;
		ptr_data_buf = ptr_buf;
		us_data_len = us_len;
		us_data_len_acc = 0;
		us_address = us_addr;

		while (us_data_len) {
			/* protection to data length */
			if (us_data_len > PDC_PPLC_BUFFER_SIZE) {
				us_data_len = PDC_PPLC_BUFFER_SIZE - 4;
			}

			uc_num_tx_bytes = us_data_len + 4;

			/* Configure PPLC Tx buffer */
			gs_pplc_tx_buffer[0] = uc_cmd;
			gs_pplc_tx_buffer[1] = (uint8_t)(us_address >> 8);
			gs_pplc_tx_buffer[2] = (uint8_t)(us_address);
			if (uc_cmd == PPLC_CMD_WRITE_REP) {
				gs_pplc_tx_buffer[3] = uc_bytes_rep;
			} else {
				gs_pplc_tx_buffer[3] = 0;
			}

			/* Fill data */
			if (uc_cmd == PPLC_CMD_READ) {
				memset(&gs_pplc_tx_buffer[4], 0, us_data_len);
			} else {
				memcpy(&gs_pplc_tx_buffer[4], ptr_data_buf, us_data_len);
			}

			/* Configure DMA channels */
			g_pplc_rx_packet.ul_addr = (uint32_t)gs_pplc_rx_buffer;
			g_pplc_rx_packet.ul_size = uc_num_tx_bytes;
			pdc_rx_init(g_pplc_pdc, &g_pplc_rx_packet, NULL);

			g_pplc_tx_packet.ul_addr = (uint32_t)gs_pplc_tx_buffer;
			g_pplc_tx_packet.ul_size = uc_num_tx_bytes;
			pdc_tx_init(g_pplc_pdc, &g_pplc_tx_packet, NULL);

			/* Enable the RX and TX PDC transfer requests */
			pdc_enable_transfer(g_pplc_pdc,
					PERIPH_PTCR_RXTEN | PERIPH_PTCR_TXTEN);

			/* Waiting transfer done*/
			while ((spi_read_status(PPLC_SPI_MODULE) &
					SPI_SR_RXBUFF) == 0) {
			}

			/* Disable the RX and TX PDC transfer requests */
			pdc_disable_transfer(g_pplc_pdc,
					PERIPH_PTCR_RXTDIS | PERIPH_PTCR_TXTDIS);

			/* copy rcv data */
			if (uc_cmd == PPLC_CMD_READ) {
				memcpy(ptr_data_buf, &gs_pplc_rx_buffer[4], us_data_len);
			}

			/* update buffer pointers */
			ptr_data_buf += us_data_len;
			us_address += us_data_len;
			/* update data length */
			us_data_len_acc += us_data_len;
			us_data_len = us_len - us_data_len_acc;
		}

		uc_pplc_is_busy = false;
		Enable_global_interrupt();
		return true;
	} else {
		Enable_global_interrupt();
		return false;
	}
}

/**
 * \brief Read 8bits from PPLC
 *
 * \param us_addr   Address to read
 *
 * \return Value readed
 */
uint8_t pplc_if_read8(uint16_t us_addr)
{
	uint8_t uc_res;

	_pplc_cmd_op(PPLC_CMD_READ, us_addr, 1, &uc_res, 0);

	return uc_res;
}

/**
 * \brief Write 8 bits to PPLC
 *
 * \param us_addr    Address to destination
 * \param uc_dat     Data to write
 *
 * \retval true if there is no error
 * \retval false if there is an error
 */
uint8_t pplc_if_write8(uint16_t us_addr, uint8_t uc_dat)
{
	return _pplc_cmd_op(PPLC_CMD_WRITE, us_addr, 1, &uc_dat, 0);
}

/**
 * \brief Read 16bits from PPLC
 *
 * \param us_addr    Address to read
 *
 * \return Value readed
 */
uint16_t pplc_if_read16(uint16_t us_addr)
{
	uint16_t us_res;
	uint8_t uc_res_buf[2];

	_pplc_cmd_op(PPLC_CMD_READ, us_addr, 2, uc_res_buf, 0);
	us_res = ((uint16_t)uc_res_buf[0]) << 8;
	us_res |= (uint16_t)uc_res_buf[1];

	return us_res;
}

/**
 * \brief Write 16 bits to PPLC
 *
 * \param us_addr    Address to destination
 * \param us_data    Data to write
 *
 * \retval true if there is no error
 * \retval false if there is an error
 */
uint8_t pplc_if_write16(uint16_t us_addr, uint16_t us_data)
{
	uint8_t uc_data_buf[2];

	uc_data_buf[0] = ((uint8_t)(us_data >> 8));
	uc_data_buf[1] = ((uint8_t)us_data);
	return _pplc_cmd_op(PPLC_CMD_WRITE, us_addr, 2, uc_data_buf, 0);
}

/**
 * \brief Read 32bits from PPLC
 *
 * \param us_addr   Address to read
 *
 * \return Value readed
 */
uint32_t pplc_if_read32(uint16_t us_addr)
{
	uint32_t ul_res;
	uint8_t uc_res_buf[4];

	_pplc_cmd_op(PPLC_CMD_READ, us_addr, 4, uc_res_buf, 0);
	ul_res = ((uint16_t)uc_res_buf[0]) << 24;
	ul_res |= ((uint16_t)uc_res_buf[1]) << 16;
	ul_res |= ((uint16_t)uc_res_buf[2]) << 8;
	ul_res |= (uint16_t)uc_res_buf[3];

	return ul_res;
}

/**
 * \brief Write 32 bits to PPLC
 *
 * \param us_addr   Address to destination
 * \param ul_dat    Data to write
 *
 * \retval true if there is no error
 * \retval false if there is an error
 */
uint8_t pplc_if_write32(uint16_t us_addr, uint32_t ul_dat)
{
	uint8_t uc_data_buf[4];

	uc_data_buf[0] = ((uint8_t)(ul_dat >> 24));
	uc_data_buf[1] = ((uint8_t)(ul_dat >> 16));
	uc_data_buf[2] = ((uint8_t)(ul_dat >> 8));
	uc_data_buf[3] = ((uint8_t)ul_dat);
	return _pplc_cmd_op(PPLC_CMD_WRITE, us_addr, 4, uc_data_buf, 0);
}

/**
 * \brief Write the content of buffer to PPLC
 *
 * \param us_addr     Write address
 * \param ptr_buf     Pointer to data buffer
 * \param us_len      Length of buffer to send
 *
 * \retval true if there is no error
 * \retval false if there is an error
 */
uint8_t pplc_if_read_buf(uint16_t us_addr, uint8_t *ptr_buf, uint16_t us_len)
{
	return _pplc_cmd_op(PPLC_CMD_READ, us_addr, us_len, ptr_buf, 0);
}

/**
 * \brief Write 8 bits to PPLC repetitive at the same address
 *
 * \param us_addr		Write address
 * \param uc_bytes_rep	Number of bytes to repeat
 * \param ptr_buf		Pointer to data buffer
 * \param us_len		Length of buffer to send
 *
 * \retval true if there is no error
 * \retval false if there is an error
 */
uint8_t pplc_if_write_rep(uint16_t us_addr, uint8_t uc_bytes_rep,
		uint8_t *ptr_buf, uint16_t us_len)
{
	return _pplc_cmd_op(PPLC_CMD_WRITE_REP, us_addr, us_len, ptr_buf,
			uc_bytes_rep);
}

/**
 * \brief Read bytes from PPLC
 *
 * \param us_addr		Initial sddress to read
 * \param ptr_buf		Destination of readed data
 * \param us_len		Number of bytes to read
 *
 * \retval true if there is no error
 * \retval false if there is an error
 */
uint8_t pplc_if_write_buf(uint16_t us_addr, uint8_t *ptr_buf, uint16_t us_len)
{
	return _pplc_cmd_op(PPLC_CMD_WRITE, us_addr, us_len, ptr_buf, 0);
}

/**
 * \brief Apply AND mask to 8 bits register
 *
 * \param us_addr       Addres of register to apply uc_mask
 * \param uc_mask       Mask
 */
void pplc_if_and8(uint16_t us_addr, uint8_t uc_mask)
{
	_pplc_cmd_op(PPLC_CMD_AND, us_addr, 1, &uc_mask, 0);
}

/**
 * \brief Apply OR mask to 8 bits register
 *
 * \param us_addr         Addres of register to apply uc_mask
 * \param uc_mask       Mask
 */
void pplc_if_or8(uint16_t us_addr, uint8_t uc_mask)
{
	_pplc_cmd_op(PPLC_CMD_OR, us_addr, 1, &uc_mask, 0);
}

/**
 * \brief Apply XOR mask to 8 bits register
 *
 * \param us_addr         Addres of register to apply uc_mask
 * \param uc_mask       Mask
 */
void pplc_if_xor8(uint16_t us_addr, uint8_t uc_mask)
{
	_pplc_cmd_op(PPLC_CMD_XOR, us_addr, 1, &uc_mask, 0);
}

/**
 * \brief Initialize PPLC interface
 *
 */
void pplc_if_init(void)
{
	/* Initialize PPLC */
	_pplc_if_config();

	/* pplc free */
	uc_pplc_is_busy = false;

	/* Configure PPLC reset pins */
#if SAM4C || SAM4CM
	;
#else
	ioport_set_pin_dir(PPLC_ARST_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PPLC_ARST_GPIO, PPLC_ARST_INACTIVE_LEVEL);

	ioport_set_pin_dir(PPLC_SRST_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PPLC_SRST_GPIO, PPLC_SRST_INACTIVE_LEVEL);
#endif

	/* Configure PPLC interruption pin */
	ioport_set_pin_dir(PPLC_INT_GPIO, IOPORT_DIR_INPUT);

	/* Configure PPLC Interruption */
	pmc_enable_periph_clk(PPLC_INT_ID);
	pio_handler_set(PPLC_INT_PIO, PPLC_INT_ID, PPLC_INT_MASK, \
			PPLC_INT_ATTR, pplc_if_int_handler);

	NVIC_SetPriority(PPLC_INT_IRQn, PPLC_PRIO);
	NVIC_ClearPendingIRQ(PPLC_INT_IRQn);
	NVIC_EnableIRQ(PPLC_INT_IRQn);
	pio_enable_interrupt(PPLC_INT_PIO, PPLC_INT_MASK);

	/* Init PPLC handler */
	pplc_handler = NULL;
}

/**
 * \brief Set an interrupt handler for the specified interrput source.
 */
void pplc_set_handler(void (*p_handler)(void))
{
	pplc_handler = p_handler;
}

/* @} */

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/* @endcond */
