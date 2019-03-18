/**
 * \file
 *
 * \brief PLC USART Buffered Interface
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
#include "stdarg.h"
#include "stdio.h"
#include "sysclk.h"
#include "tc.h"
#include "usart.h"
#include "pdc.h"
#include "pmc.h"
#include "busart_if.h"
#include "conf_busart_if.h"
#include "conf_board.h"

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/* @endcond */

/**
 * \weakgroup busart_plc_group
 * @{
 */

#ifdef CONF_BOARD_USART0_RXD
/* Reception Buffer 0 */
static uint8_t rx_usart_buf0[RX_USART_BUF0_SIZE];
/* Transmission Buffer 0 */
static uint8_t tx_usart_buf0[TX_USART_BUF0_SIZE];
/* Pointers to Reception Buffer 0 */
uint8_t *const ptr_rx_usart_buf0 = &rx_usart_buf0[0];
/* Pointers to Transmission Buffer 0 */
uint8_t *const ptr_tx_usart_buf0 = &tx_usart_buf0[0];
#endif

#ifdef CONF_BOARD_USART1_RXD
/* Reception Buffer 1 */
static uint8_t rx_usart_buf1[RX_USART_BUF1_SIZE];
/* Transmission Buffer 1 */
static uint8_t tx_usart_buf1[TX_USART_BUF1_SIZE];
/* Pointers to Reception Buffer 1 */
uint8_t *const ptr_rx_usart_buf1 = &rx_usart_buf1[0];
/* Pointers to Transmission Buffer 1 */
uint8_t *const ptr_tx_usart_buf1 = &tx_usart_buf1[0];
#endif

/*! \brief Communications Queue Info */
typedef struct {
	/** Pointer to transmission queue. Buffer */
	uint8_t *puc_tq_buf;
	/** Pointer to reception queue. Buffer */
	uint8_t *puc_rq_buf;
	/** Reception queue. Read index */
	uint16_t us_rq_idx;
	/** Reception queue. Write index */
	uint16_t us_wq_idx;
	/** Reception queue. Occupation count */
	uint16_t us_rq_count;
} busart_comm_data_t;

/* \name Size of the receive buffer used by the PDC, in bytes */
/* @{ */
#define USART_BUFFER_SIZE                       1024
/* @} */

#ifdef CONF_BOARD_USART0_RXD
/* Data struct to use with USART0 */
static busart_comm_data_t busart_comm_data_0;
/* Receive buffer use 2 fast buffers */
static uint8_t gs_puc_usart_buf0[USART_BUFFER_SIZE];
/* Current bytes in buffer. */
static uint32_t gs_ul_size_usart_buf0 = USART_BUFFER_SIZE;
/* PDC RX data packet. */
pdc_packet_t g_st_usart_rx_packet0;
/* PDC TX data packet. */
pdc_packet_t g_st_usart_tx_packet0;
/* Pointer to PDC register base. */
Pdc *g_p_usart_pdc0;
/* Number of bytes received in USART0 */
static uint16_t num_bytes_rx_usart0;
#endif

#ifdef CONF_BOARD_USART1_RXD
/* Data struct to use with USART0 */
static busart_comm_data_t busart_comm_data_1;
/* Receive buffer use 2 fast buffers */
static uint8_t gs_puc_usart_buf1[USART_BUFFER_SIZE];
/* Current bytes in buffer. */
static uint32_t gs_ul_size_usart_buf1 = USART_BUFFER_SIZE;
/* PDC RX data packet. */
pdc_packet_t g_st_usart_rx_packet1;
/* PDC TX data packet. */
pdc_packet_t g_st_usart_tx_packet1;
/* Pointer to PDC register base. */
Pdc *g_p_usart_pdc1;
/* Number of bytes received in USART1 */
static uint16_t num_bytes_rx_usart1;
#endif

/* Uart channel open / closed */
static uint8_t busart_chn_open[2] = {
	false,
	false
};

#if defined(CONF_BOARD_USART0_RXD) || defined(CONF_BOARD_USART1_RXD)

/**
 * \brief Configure Timer Counter to generate an interrupt every 10ms.
 * This interrupt will be used to flush USART input and echo back.
 */
static void _configure_TC_usart(void)
{
	uint32_t ul_div;
	uint32_t ul_tcclks;
	uint32_t ul_sysclk;
	uint32_t ul_frec_hz = (uint32_t)FREQ_TIMER_POLL_USART;

	/* Get system clock. */
	ul_sysclk = sysclk_get_cpu_hz();

	/* Configure PMC. */
	pmc_enable_periph_clk(ID_TC_USART);

	/* Configure TC for a TC_FREQ frequency and trigger on RC compare. */
	tc_find_mck_divisor(ul_frec_hz, ul_sysclk, &ul_div, &ul_tcclks,
			ul_sysclk);
	tc_init(TC_USART, TC_USART_CHN, ul_tcclks | TC_CMR_CPCTRG);
	tc_write_rc(TC_USART, TC_USART_CHN, (ul_sysclk / ul_div) / ul_frec_hz);

	/* Configure and enable interrupt on RC compare. */
	NVIC_SetPriority((IRQn_Type)ID_TC_USART, TIMER_USART_PRIO);
	NVIC_EnableIRQ((IRQn_Type)ID_TC_USART);
	tc_enable_interrupt(TC_USART, TC_USART_CHN, TC_IER_CPCS);
}

/**
 * \brief Interrupt handler. Record the number of bytes received,
 * and then restart a read transfer on the USART if the transfer was stopped.
 */
void TC_USART_Handler(void)
{
	uint32_t ul_status;
#if defined(CONF_BOARD_USART0_RXD) || defined(CONF_BOARD_USART1_RXD)
	uint32_t ul_byte_total = 0;
#endif

	/* Read TC_USART Status. */
	ul_status = tc_get_status(TC_USART, TC_USART_CHN);

	/* RC compare. */
	if ((ul_status & TC_SR_CPCS) == TC_SR_CPCS) {
#ifdef CONF_BOARD_USART0_RXD
		if (busart_chn_open[0]) {
			/* Flush PDC buffer. */
			ul_byte_total = USART_BUFFER_SIZE - pdc_read_rx_counter(g_p_usart_pdc0);
			if (ul_byte_total > 0) {
				if (ul_byte_total == num_bytes_rx_usart0) {
					/* Disable timer. */
					tc_stop(TC_USART, TC_USART_CHN);

					/* Log current size */
					gs_ul_size_usart_buf0 = ul_byte_total;

					/* Stop DMA USART_RX -> force Uart Handler*/
					g_st_usart_rx_packet0.ul_size = 0;
					pdc_rx_init(g_p_usart_pdc0, &g_st_usart_rx_packet0, NULL);
				} else {
					num_bytes_rx_usart0 = ul_byte_total;
				}
			} else {
				num_bytes_rx_usart0 = 0;
			}
		}
#endif

#ifdef CONF_BOARD_USART1_RXD
		if (busart_chn_open[1]) {
			/* Flush PDC buffer. */
			ul_byte_total = USART_BUFFER_SIZE - pdc_read_rx_counter(g_p_usart_pdc1);
			if (ul_byte_total > 0) {
				if (ul_byte_total == num_bytes_rx_usart1) {
					/* Disable timer. */
					tc_stop(TC_USART, TC_USART_CHN);

					/* Log current size */
					gs_ul_size_usart_buf1 = ul_byte_total;

					/* Stop DMA USART_RX -> force Uart Handler*/
					g_st_usart_rx_packet1.ul_size = 0;
					pdc_rx_init(g_p_usart_pdc1, &g_st_usart_rx_packet1, NULL);
				} else {
					num_bytes_rx_usart1 = ul_byte_total;
				}
			} else {
				num_bytes_rx_usart1 = 0;
			}
		}
#endif
	}
}

#ifdef CONF_BOARD_USART0_RXD

/** @brief	Interruption handler for USART0
 *
 */
void USART0_Handler(void)
{
	uint32_t ul_status;
	uint16_t us_wr_idx, us_data_count;
	uint16_t us_end_size, us_free_size, us_part_size;

	/* Read USART Status. */
	ul_status = usart_get_status(USART0);

	/* Receive buffer is full. */
	if (ul_status & US_CSR_ENDRX) {
		/* manage data */
		us_wr_idx = busart_comm_data_0.us_wq_idx;
		us_data_count = busart_comm_data_0.us_rq_count;
		us_free_size = RX_USART_BUF0_SIZE - us_data_count;
		if (gs_ul_size_usart_buf0 <= us_free_size) {
			/* there is enough space to write all data */
			us_end_size = RX_USART_BUF0_SIZE - us_wr_idx;
			if (us_end_size >= gs_ul_size_usart_buf0) {
				/* there is no overflow of us_wq_idx */
				memcpy(&busart_comm_data_0.puc_rq_buf[us_wr_idx],
						gs_puc_usart_buf0, gs_ul_size_usart_buf0);
				/* update counters */
				busart_comm_data_0.us_rq_count += gs_ul_size_usart_buf0;
				busart_comm_data_0.us_wq_idx += gs_ul_size_usart_buf0;
			} else {
				/* there is overflow of us_wq_idx -> write in 2
				 * steps	*/
				memcpy(&busart_comm_data_0.puc_rq_buf[us_wr_idx],
						gs_puc_usart_buf0, us_end_size);
				us_part_size = gs_ul_size_usart_buf0 - us_end_size;
				memcpy(&busart_comm_data_0.puc_rq_buf[0],
						&gs_puc_usart_buf0[us_end_size], us_part_size);
				/* update counters */
				busart_comm_data_0.us_rq_count += gs_ul_size_usart_buf0;
				busart_comm_data_0.us_wq_idx = us_part_size;
			}
		} else {
			/* there is not enough space to write all data */
			tc_start(TC_USART, TC_USART_CHN);
		}

		/* change RX buffer */
		gs_ul_size_usart_buf0 = USART_BUFFER_SIZE;

		/* Restart read on buffer. */
		g_st_usart_rx_packet0.ul_addr = (uint32_t)gs_puc_usart_buf0;
		g_st_usart_rx_packet0.ul_size = USART_BUFFER_SIZE;
		pdc_rx_init(g_p_usart_pdc0, &g_st_usart_rx_packet0, NULL);

		/* Restart timer. */
		tc_start(TC_USART, TC_USART_CHN);
	}
}

#endif

#ifdef CONF_BOARD_USART1_RXD

/** @brief	Interruption handler for USART1
 *
 */
void USART1_Handler(void)
{
	uint32_t ul_status;
	uint16_t us_wr_idx, us_data_count;
	uint16_t us_end_size, us_free_size, us_part_size;

	/* Read USART Status. */
	ul_status = usart_get_status(USART1);

	/* Receive buffer is full. */
	if (ul_status & US_CSR_ENDRX) {
		/* manage data */
		us_wr_idx = busart_comm_data_1.us_wq_idx;
		us_data_count = busart_comm_data_1.us_rq_count;
		us_free_size = RX_USART_BUF1_SIZE - us_data_count;
		if (gs_ul_size_usart_buf1 <= us_free_size) {
			/* there is enough space to write all data */
			us_end_size = RX_USART_BUF1_SIZE - us_wr_idx;
			if (us_end_size >= gs_ul_size_usart_buf1) {
				/* there is no overflow of us_wq_idx */
				memcpy(&busart_comm_data_1.puc_rq_buf[us_wr_idx],
						gs_puc_usart_buf1, gs_ul_size_usart_buf1);
				/* update counters */
				busart_comm_data_1.us_rq_count += gs_ul_size_usart_buf1;
				busart_comm_data_1.us_wq_idx += gs_ul_size_usart_buf1;
			} else {
				/* there is overflow of us_wq_idx -> write in 2
				 * steps	*/
				memcpy(&busart_comm_data_1.puc_rq_buf[us_wr_idx],
						gs_puc_usart_buf1, us_end_size);
				us_part_size = gs_ul_size_usart_buf1 - us_end_size;
				memcpy(&busart_comm_data_1.puc_rq_buf[0],
						&gs_puc_usart_buf1[us_end_size], us_part_size);
				/* update counters */
				busart_comm_data_1.us_rq_count += gs_ul_size_usart_buf1;
				busart_comm_data_1.us_wq_idx = us_part_size;
			}
		} else {
			/* there is not enough space to write all data */
			tc_start(TC_USART, TC_USART_CHN);
		}

		/* change RX buffer */
		gs_ul_size_usart_buf1 = USART_BUFFER_SIZE;

		/* Restart read on buffer. */
		g_st_usart_rx_packet1.ul_addr = (uint32_t)gs_puc_usart_buf1;
		g_st_usart_rx_packet1.ul_size = USART_BUFFER_SIZE;
		pdc_rx_init(g_p_usart_pdc1, &g_st_usart_rx_packet1, NULL);

		/* Restart timer. */
		tc_start(TC_USART, TC_USART_CHN);
	}
}

#endif
#endif

/**
 * \brief This function opens an USART
 *
 * \note Opening of the specified USART implies initializing local variables and
 * opening required hardware with the following configuration:
 * - bauds as specified
 * - 8 bits, no parity, 1 stop bit
 * - enable interrupts
 *
 * \param chn			Communication channel [0, 1]
 * \param bauds			Communication speed in bauds
 *
 * \retval true on success.
 * \retval false on failure.
 */
int8_t busart_if_open(uint8_t chn, uint32_t bauds)
{
#if defined(CONF_BOARD_USART0_RXD) || defined(CONF_BOARD_USART1_RXD)
	sam_usart_opt_t usart_console_settings;

	/* Expected baud rate. */
	usart_console_settings.baudrate = bauds;

	/* Configure channel mode (Normal, Automatic, Local_loopback or
	 * Remote_loopback) */
	usart_console_settings.channel_mode = US_MR_CHMODE_NORMAL;
	/* Initialize value for USART mode register */
	usart_console_settings.parity_type = US_MR_PAR_NO;
	usart_console_settings.char_length = US_MR_CHRL_8_BIT;
	usart_console_settings.stop_bits = US_MR_NBSTOP_1_BIT;
#else
	UNUSED(bauds);
#endif
	/* check usart and it is close */
	if (chn >= 2) {
		return false;
	}

	if (busart_chn_open[chn]) {
		return false;
	}

	switch (chn) {
#ifdef CONF_BOARD_USART0_RXD
	case 0:
	{
		/* Configure PMC. */
		pmc_enable_periph_clk(ID_USART0);
		/* Configure USART. */
		usart_init_rs232(USART0, &usart_console_settings,
				sysclk_get_peripheral_hz());

		/* Assign buffers to pointers */
		busart_comm_data_0.puc_tq_buf = ptr_tx_usart_buf0;
		busart_comm_data_0.puc_rq_buf = ptr_rx_usart_buf0;
		busart_comm_data_0.us_rq_count = 0;
		busart_comm_data_0.us_rq_idx = 0;
		busart_comm_data_0.us_wq_idx = 0;

		/* Get board USART0 PDC base address and enable receiver and
		 * transmitter. */
		g_p_usart_pdc0 = usart_get_pdc_base(USART0);
		pdc_enable_transfer(g_p_usart_pdc0,
				PERIPH_PTCR_RXTEN | PERIPH_PTCR_TXTEN);

		/* Start receiving data and start timer. */
		g_st_usart_rx_packet0.ul_addr = (uint32_t)gs_puc_usart_buf0;
		g_st_usart_rx_packet0.ul_size = USART_BUFFER_SIZE;
		pdc_rx_init(g_p_usart_pdc0, &g_st_usart_rx_packet0, NULL);

		/* Stop transmitting data */
		g_st_usart_tx_packet0.ul_addr = (uint32_t)busart_comm_data_0.puc_tq_buf;
		g_st_usart_tx_packet0.ul_size = 0;
		pdc_tx_init(g_p_usart_pdc0, &g_st_usart_tx_packet0, NULL);

		gs_ul_size_usart_buf0 = USART_BUFFER_SIZE;

		/* Transfer to PDC communication mode, disable RXRDY interrupt
		 * and enable RXBUFF interrupt. */
		usart_disable_interrupt(USART0, US_IDR_RXRDY);
		usart_enable_interrupt(USART0, US_IER_RXBUFF);

		/* Enable the receiver and transmitter. */
		usart_enable_tx(USART0);
		usart_enable_rx(USART0);

		/* Configure and enable interrupt of USART. */
		NVIC_SetPriority((IRQn_Type)USART0_IRQn, USART0_PRIO);
		NVIC_EnableIRQ(USART0_IRQn);

		busart_chn_open[chn] = true;
		num_bytes_rx_usart0 = 0;

		/* Configure TC usart */
		_configure_TC_usart();
		tc_start(TC_USART, TC_USART_CHN);

		return true;
	}
	break;
#endif
#ifdef CONF_BOARD_USART1_RXD
	case 1:
	{
		/* Configure PMC. */
		pmc_enable_periph_clk(ID_USART1);
		/* Configure USART. */
		usart_init_rs232(USART1, &usart_console_settings,
				sysclk_get_peripheral_hz());

		/* Assign buffers to pointers */
		busart_comm_data_1.puc_tq_buf = ptr_tx_usart_buf1;
		busart_comm_data_1.puc_rq_buf = ptr_rx_usart_buf1;
		busart_comm_data_1.us_rq_count = 0;
		busart_comm_data_1.us_rq_idx = 0;
		busart_comm_data_1.us_wq_idx = 0;

		/* Get board USART1 PDC base address and enable receiver and
		 * transmitter. */
		g_p_usart_pdc1 = usart_get_pdc_base(USART1);
		pdc_enable_transfer(g_p_usart_pdc1,
				PERIPH_PTCR_RXTEN | PERIPH_PTCR_TXTEN);

		/* Start receiving data and start timer. */
		g_st_usart_rx_packet1.ul_addr = (uint32_t)gs_puc_usart_buf1;
		g_st_usart_rx_packet1.ul_size = USART_BUFFER_SIZE;
		pdc_rx_init(g_p_usart_pdc1, &g_st_usart_rx_packet1, NULL);

		/* Stop transmitting data */
		g_st_usart_tx_packet1.ul_addr = (uint32_t)busart_comm_data_1.puc_tq_buf;
		g_st_usart_tx_packet1.ul_size = 0;
		pdc_tx_init(g_p_usart_pdc1, &g_st_usart_tx_packet1, NULL);

		gs_ul_size_usart_buf1 = USART_BUFFER_SIZE;

		/* Transfer to PDC communication mode, disable RXRDY interrupt
		 * and enable RXBUFF interrupt. */
		usart_disable_interrupt(USART1, US_IDR_RXRDY);
		usart_enable_interrupt(USART1, US_IER_RXBUFF);

		/* Enable the receiver and transmitter. */
		usart_enable_tx(USART1);
		usart_enable_rx(USART1);

		/* Configure and enable interrupt of USART. */
		NVIC_SetPriority((IRQn_Type)USART1_IRQn, USART1_PRIO);
		NVIC_EnableIRQ(USART1_IRQn);

		busart_chn_open[chn] = true;
		num_bytes_rx_usart1 = 0;

		/* Configure TC usart */
		_configure_TC_usart();
		tc_start(TC_USART, TC_USART_CHN);

		return true;
	}
	break;
#endif
	default:
		return false;
	}
}

/**
 * \brief This function closes and disables communication in the specified
 * USART.
 *
 * \param chn  Communication channel [0, 1]
 *
 * \retval true on success.
 * \retval false on failure.
 */
int8_t busart_if_close(uint8_t chn)
{
	if (!busart_chn_open[chn]) {
		return false;
	}

	switch (chn) {
#ifdef CONF_BOARD_USART0_RXD
	case 0:
	{
		usart_disable_tx(USART0);
		usart_disable_rx(USART0);

		usart_disable_interrupt(USART0, US_IDR_RXRDY);
		usart_disable_interrupt(USART0, US_IER_ENDRX);

		/* Stop TC */
		if (!busart_chn_open[1]) {
			tc_stop(TC_USART, TC_USART_CHN);
		}

		return true;
	}
	break;
#endif

#ifdef CONF_BOARD_USART1_RXD
	case 1:
	{
		usart_disable_tx(USART1);
		usart_disable_rx(USART1);

		usart_disable_interrupt(USART1, US_IDR_RXRDY);
		usart_disable_interrupt(USART1, US_IER_ENDRX);

		/* Stop TC */
		if (!busart_chn_open[0]) {
			tc_stop(TC_USART, TC_USART_CHN);
		}

		return true;
	}
	break;
#endif
	default:
		return false;
	}
}

/**
 * \brief This function receives a message.
 *
 * \note This function receives a given number of characters from the specified
 * USART. If so configured, the function waits until all characters are
 * received. In this case, the watchdog timer must be reloaded to avoid a
 * program reset.
 *
 * \param  chn     Communication channel [0, 1]
 * \param  buffer  Pointer to buffer for information
 * \param  len     Number of characters to receive
 *
 * \retval Number of received characters
 */
uint16_t busart_if_read(uint8_t chn, void *buffer, uint16_t len)
{
#if defined(CONF_BOARD_USART0_RXD) || defined(CONF_BOARD_USART1_RXD)
	uint16_t us_rd_idx = 0;
	uint16_t us_num_bytes_read, us_num_bytes_to_end, us_num_bytes_to_start;
	uint16_t us_total_pos;
	uint16_t us_buf_size;

	uint8_t *msg = (uint8_t *)buffer;
#else
	UNUSED(buffer);
	UNUSED(len);
#endif

	/* check usart is open */
	if (!busart_chn_open[chn]) {
		return 0;
	}

	switch (chn) {
#ifdef CONF_BOARD_USART0_RXD
	case 0:
		us_buf_size = RX_USART_BUF0_SIZE;
		/* check if there is any byte in rx queue */
		if (busart_comm_data_0.us_rq_count == 0) {
			return 0;
		}

		/* get counters */
		us_rd_idx = busart_comm_data_0.us_rq_idx;
		/* get number of bytes to read */
		if (busart_comm_data_0.us_rq_count >= len) {
			us_num_bytes_read = len;
		} else {
			us_num_bytes_read = busart_comm_data_0.us_rq_count;
		}

		/* check overflow us_rd_idx counter */
		us_total_pos = us_rd_idx + us_num_bytes_read;
		if (us_total_pos <= us_buf_size) {
			/* copy data to buffer */
			memcpy(msg, &busart_comm_data_0.puc_rq_buf[us_rd_idx],
					us_num_bytes_read);
			/* update counters */
			busart_comm_data_0.us_rq_count -= us_num_bytes_read;
			busart_comm_data_0.us_rq_idx += us_num_bytes_read;
		} else {
			/* copy data to buffer in fragments -> overflow
			 * us_rq_idx counter */
			us_num_bytes_to_start = us_total_pos - us_buf_size;
			us_num_bytes_to_end = us_num_bytes_read - us_num_bytes_to_start;
			memcpy(msg, &busart_comm_data_0.puc_rq_buf[us_rd_idx],
					us_num_bytes_to_end);
			msg += us_num_bytes_to_end;
			memcpy(msg, &busart_comm_data_0.puc_rq_buf[0],
					us_num_bytes_to_start);
			/* update counters */
			busart_comm_data_0.us_rq_count -= us_num_bytes_read;
			busart_comm_data_0.us_rq_idx = us_num_bytes_to_start;
		}

		return us_num_bytes_read;
#endif

#ifdef CONF_BOARD_USART1_RXD
	case 1:
		us_buf_size = RX_USART_BUF1_SIZE;
		/* check if there is any byte in rx queue */
		if (busart_comm_data_1.us_rq_count == 0) {
			return 0;
		}

		/* get counters */
		us_rd_idx = busart_comm_data_1.us_rq_idx;
		/* get number of bytes to read */
		if (busart_comm_data_1.us_rq_count >= len) {
			us_num_bytes_read = len;
		} else {
			us_num_bytes_read = busart_comm_data_1.us_rq_count;
		}

		/* check overflow us_rd_idx counter */
		us_total_pos = us_rd_idx + us_num_bytes_read;
		if (us_total_pos <= us_buf_size) {
			/* copy data to buffer */
			memcpy(msg, &busart_comm_data_1.puc_rq_buf[us_rd_idx],
					us_num_bytes_read);
			/* update counters */
			busart_comm_data_1.us_rq_count -= us_num_bytes_read;
			busart_comm_data_1.us_rq_idx += us_num_bytes_read;
		} else {
			/* copy data to buffer in fragments -> overflow
			 * us_rq_idx counter */
			us_num_bytes_to_start = us_total_pos - us_buf_size;
			us_num_bytes_to_end = us_num_bytes_read - us_num_bytes_to_start;
			memcpy(msg, &busart_comm_data_1.puc_rq_buf[us_rd_idx],
					us_num_bytes_to_end);
			msg += us_num_bytes_to_end;
			memcpy(msg, &busart_comm_data_1.puc_rq_buf[0],
					us_num_bytes_to_start);
			/* update counters */
			busart_comm_data_1.us_rq_count -= us_num_bytes_read;
			busart_comm_data_1.us_rq_idx = us_num_bytes_to_start;
		}
		return us_num_bytes_read;
#endif
	default:
		return 0;
	}
}

/**
 * \brief This function transmits a message.
 *
 * \note This function transmits characters via the specified USART.
 * If so configured, the function waits until all characters are inserted
 * in the transmission queue. In this case, the watchdog timer must be
 * reloaded to avoid a program reset.
 *
 * \param  chn     Communication channel [0, 1]
 * \param  buffer  Pointer to information to transmit
 * \param  len     Number of characters to transmit
 *
 * \retval Number of characters sent
 */
uint16_t busart_if_write(uint8_t chn, const void *buffer, uint16_t len)
{
#if !defined(CONF_BOARD_USART0_RXD) || !defined(CONF_BOARD_USART1_RXD)
	UNUSED(buffer);
	UNUSED(len);
#endif
	/* check usart is open */
	if (!busart_chn_open[chn]) {
		return 0;
	}

	switch (chn) {
#ifdef CONF_BOARD_USART0_RXD
	case 0:
		if (len > TX_USART_BUF0_SIZE) {
			return 0;
		}

		while (pdc_read_tx_counter(g_p_usart_pdc0) > 0) {
		}
		memcpy(&busart_comm_data_0.puc_tq_buf[0], buffer, len);
		g_st_usart_tx_packet0.ul_addr = (uint32_t)&busart_comm_data_0.puc_tq_buf[0];
		g_st_usart_tx_packet0.ul_size = len;
		pdc_tx_init(g_p_usart_pdc0, &g_st_usart_tx_packet0, NULL);
		return len;
#endif

#ifdef CONF_BOARD_USART1_RXD
	case 1:
		if (len > TX_USART_BUF1_SIZE) {
			return 0;
		}

		while (pdc_read_tx_counter(g_p_usart_pdc1) > 0) {
		}
		memcpy(&busart_comm_data_1.puc_tq_buf[0], buffer, len);
		g_st_usart_tx_packet1.ul_addr = (uint32_t)&busart_comm_data_1.puc_tq_buf[0];
		g_st_usart_tx_packet1.ul_size = len;
		pdc_tx_init(g_p_usart_pdc1, &g_st_usart_tx_packet1, NULL);
		return len;
#endif

	default:
		return 0;
	}
}

/**
 * \brief Get byte from USART.
 *
 * \param  chn  Communication channel [0, 1]
 *
 * \retval Byte received
 * \retval -1 in case of no reception
 */
int busart_if_rx_char(uint8_t chn)
{
	uint8_t buf[4] = {0, 0, 0, 0};

	if (busart_if_read(chn, buf, 1) <= 0) {
		return (-1);
	}

	return buf[0];
}

/**
 * \brief Sent byte to USART.
 *
 * \param  chn   Communication channel [0, 1]
 * \param  data  Data to sent
 *
 * \retval Number of characters sent
 */
uint16_t busart_if_tx_char(uint8_t chn, char data)
{
	return (busart_if_write(chn, &data, 1));
}

/* @} */

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/* @endcond */
