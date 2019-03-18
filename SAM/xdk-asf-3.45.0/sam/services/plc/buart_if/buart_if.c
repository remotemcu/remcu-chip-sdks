/**
 * \file
 *
 * \brief PLC UART Buffered Interface
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
#include "uart.h"
#include "pdc.h"
#include "pmc.h"
#include "buart_if.h"
#include "conf_buart_if.h"
#include "conf_board.h"

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/* @endcond */

/**
 * \weakgroup buart_plc_group
 * @{
 */

#ifdef CONF_BOARD_UART0
/* Reception Buffer 0 */
static uint8_t rx_uart_buf0[RX_UART_BUF0_SIZE];
/* Transmission Buffer 0 */
static uint8_t tx_uart_buf0[TX_UART_BUF0_SIZE];
/* Pointers to Reception Buffer 0 */
uint8_t *const ptr_rx_uart_buf0 = &rx_uart_buf0[0];
/* Pointers to Transmission Buffer 0 */
uint8_t *const ptr_tx_uart_buf0 = &tx_uart_buf0[0];
#endif

#ifdef CONF_BOARD_UART1
/* Reception Buffer 1 */
static uint8_t rx_uart_buf1[RX_UART_BUF1_SIZE];
/* Transmission Buffer 1 */
static uint8_t tx_uart_buf1[TX_UART_BUF1_SIZE];
/* Pointers to Reception Buffer 1 */
uint8_t *const ptr_rx_uart_buf1 = &rx_uart_buf1[0];
/* Pointers to Transmission Buffer 1 */
uint8_t *const ptr_tx_uart_buf1 = &tx_uart_buf1[0];
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
} buart_comm_data_t;

/* \name Size of the receive buffer used by the PDC, in bytes */
/* @{ */
#define UART_BUFFER_SIZE                        1024
/* @} */

#ifdef CONF_BOARD_UART0
/* Data struct to use with UART0 */
static buart_comm_data_t buart_comm_data_0;
/* Receive buffer use 2 fast buffers */
static uint8_t gs_puc_uart_buf0[UART_BUFFER_SIZE];
/* Current bytes in buffer. */
static uint32_t gs_ul_size_uart_buf0 = UART_BUFFER_SIZE;
/* PDC RX data packet. */
pdc_packet_t g_st_uart_rx_packet0;
/* PDC TX data packet. */
pdc_packet_t g_st_uart_tx_packet0;
/* Pointer to PDC register base. */
Pdc *g_p_uart_pdc0;
/* Number of bytes received in UART0 */
static uint16_t num_bytes_rx_uart0;
#endif

#ifdef CONF_BOARD_UART1
/* Data struct to use with UART0 */
static buart_comm_data_t buart_comm_data_1;
/* Receive buffer use 2 fast buffers */
static uint8_t gs_puc_uart_buf1[UART_BUFFER_SIZE];
/* Current bytes in buffer. */
static uint32_t gs_ul_size_uart_buf1 = UART_BUFFER_SIZE;
/* PDC RX data packet. */
pdc_packet_t g_st_uart_rx_packet1;
/* PDC TX data packet. */
pdc_packet_t g_st_uart_tx_packet1;
/* Pointer to PDC register base. */
Pdc *g_p_uart_pdc1;
/* Number of bytes received in UART1 */
static uint16_t num_bytes_rx_uart1;
#endif

/* Uart channel open / closed */
static uint8_t buart_chn_open[2] = {
	false,
	false
};

#if defined(CONF_BOARD_UART0) || defined(CONF_BOARD_UART1)

/**
 * \brief Configure Timer Counter to generate an interrupt every 10ms.
 * This interrupt will be used to flush UART input and echo back.
 */
static void _configure_TC_uart(void)
{
	uint32_t ul_div;
	uint32_t ul_tcclks;
	uint32_t ul_sysclk;
	uint32_t ul_frec_hz = (uint32_t)FREQ_TIMER_POLL_UART;

	/* Get system clock. */
	ul_sysclk = sysclk_get_cpu_hz();

	/* Configure PMC. */
	pmc_enable_periph_clk(ID_TC_UART);

	/* Configure TC for a TC_FREQ frequency and trigger on RC compare. */
	tc_find_mck_divisor(ul_frec_hz, ul_sysclk, &ul_div, &ul_tcclks,
			ul_sysclk);
	tc_init(TC_UART, TC_UART_CHN, ul_tcclks | TC_CMR_CPCTRG);
	tc_write_rc(TC_UART, TC_UART_CHN, (ul_sysclk / ul_div) / ul_frec_hz);

	/* Configure and enable interrupt on RC compare. */
	NVIC_SetPriority((IRQn_Type)ID_TC_UART, TIMER_UART_PRIO);
	NVIC_EnableIRQ((IRQn_Type)ID_TC_UART);
	tc_enable_interrupt(TC_UART, TC_UART_CHN, TC_IER_CPCS);
}

/**
 * \brief Interrupt handler. Record the number of bytes received,
 * and then restart a read transfer on the UART if the transfer was stopped.
 */
void TC_UART_Handler(void)
{
	uint32_t ul_status;
	uint32_t ul_byte_total = 0;

	/* Read TC_UART Status. */
	ul_status = tc_get_status(TC_UART, TC_UART_CHN);

	/* RC compare. */
	if ((ul_status & TC_SR_CPCS) == TC_SR_CPCS) {
#ifdef CONF_BOARD_UART0
		if (buart_chn_open[0]) {
			/* Flush PDC buffer. */
			ul_byte_total = UART_BUFFER_SIZE - pdc_read_rx_counter(g_p_uart_pdc0);
			if (ul_byte_total > 0) {
				if (ul_byte_total == num_bytes_rx_uart0) {
					/* Disable timer. */
					tc_stop(TC_UART, TC_UART_CHN);

					/* Log current size */
					gs_ul_size_uart_buf0 = ul_byte_total;

					/* Stop DMA UART_RX -> force Uart Handler*/
					g_st_uart_rx_packet0.ul_size = 0;
					pdc_rx_init(g_p_uart_pdc0, &g_st_uart_rx_packet0, NULL);
				} else {
					num_bytes_rx_uart0 = ul_byte_total;
				}
			} else {
				num_bytes_rx_uart0 = 0;
			}
		}
#endif
#ifdef CONF_BOARD_UART1
		if (buart_chn_open[1]) {
			/* Flush PDC buffer. */
			ul_byte_total = UART_BUFFER_SIZE - pdc_read_rx_counter(g_p_uart_pdc1);
			if (ul_byte_total > 0) {
				if (ul_byte_total == num_bytes_rx_uart1) {
					/* Disable timer. */
					tc_stop(TC_UART, TC_UART_CHN);

					/* Log current size */
					gs_ul_size_uart_buf1 = ul_byte_total;

					/* Stop DMA UART_RX -> force Uart Handler*/
					g_st_uart_rx_packet1.ul_size = 0;
					pdc_rx_init(g_p_uart_pdc1, &g_st_uart_rx_packet1, NULL);
				} else {
					num_bytes_rx_uart1 = ul_byte_total;
				}
			} else {
				num_bytes_rx_uart1 = 0;
			}
		}
#endif
	}
}

#ifdef CONF_BOARD_UART0

/** @brief	Interruption handler for UART0
 *
 */
void UART0_Handler(void)
{
	uint32_t ul_status;
	uint16_t us_wr_idx, us_data_count;
	uint16_t us_end_size, us_free_size, us_part_size;

	/* Read USART Status. */
	ul_status = uart_get_status(UART0);

	/* Receive buffer is full. */
	if (ul_status & US_CSR_ENDRX) {
		/* manage data */
		us_wr_idx = buart_comm_data_0.us_wq_idx;
		us_data_count = buart_comm_data_0.us_rq_count;
		us_free_size = RX_UART_BUF0_SIZE - us_data_count;
		if (gs_ul_size_uart_buf0 <= us_free_size) {
			/* there is enough space to write all data */
			us_end_size = RX_UART_BUF0_SIZE - us_wr_idx;
			/* there is no overflow of us_wq_idx */
			if (us_end_size >= gs_ul_size_uart_buf0) {
				memcpy(&buart_comm_data_0.puc_rq_buf[us_wr_idx],
						gs_puc_uart_buf0, gs_ul_size_uart_buf0);
				/* update counters */
				buart_comm_data_0.us_rq_count += gs_ul_size_uart_buf0;
				buart_comm_data_0.us_wq_idx += gs_ul_size_uart_buf0;
			} else { /* there is overflow of us_wq_idx -> write in 2
				  * steps	*/
				memcpy(&buart_comm_data_0.puc_rq_buf[us_wr_idx],
						gs_puc_uart_buf0, us_end_size);
				us_part_size = gs_ul_size_uart_buf0 - us_end_size;
				memcpy(&buart_comm_data_0.puc_rq_buf[0],
						&gs_puc_uart_buf0[us_end_size],	us_part_size);
				/* update counters */
				buart_comm_data_0.us_rq_count += gs_ul_size_uart_buf0;
				buart_comm_data_0.us_wq_idx = us_part_size;
			}
		} else { /* there is not enough space to write all data */
			tc_start(TC_UART, TC_UART_CHN);
		}

		/* change RX buffer */
		gs_ul_size_uart_buf0 = UART_BUFFER_SIZE;

		/* Restart read on buffer. */
		g_st_uart_rx_packet0.ul_addr = (uint32_t)gs_puc_uart_buf0;
		g_st_uart_rx_packet0.ul_size = UART_BUFFER_SIZE;
		pdc_rx_init(g_p_uart_pdc0, &g_st_uart_rx_packet0, NULL);

		/* Restart timer. */
		tc_start(TC_UART, TC_UART_CHN);
	}
}

#endif

#ifdef CONF_BOARD_UART1

/** @brief	Interruption handler for UART1
 *
 */
void UART1_Handler(void)
{
	uint32_t ul_status;
	uint16_t us_wr_idx, us_data_count;
	uint16_t us_end_size, us_free_size, us_part_size;

	/* Read USART Status. */
	ul_status = uart_get_status(UART1);

	/* Receive buffer is full. */
	if (ul_status & US_CSR_ENDRX) {
		/* manage data */
		us_wr_idx = buart_comm_data_1.us_wq_idx;
		us_data_count = buart_comm_data_1.us_rq_count;
		us_free_size = RX_UART_BUF1_SIZE - us_data_count;
		if (gs_ul_size_uart_buf1 <= us_free_size) {
			/* there is enough space to write all data */
			us_end_size = RX_UART_BUF1_SIZE - us_wr_idx;
			if (us_end_size >= gs_ul_size_uart_buf1) {
				/* there is no overflow of us_wq_idx */
				memcpy(&buart_comm_data_1.puc_rq_buf[us_wr_idx],
						gs_puc_uart_buf1, gs_ul_size_uart_buf1);
				/* update counters */
				buart_comm_data_1.us_rq_count += gs_ul_size_uart_buf1;
				buart_comm_data_1.us_wq_idx += gs_ul_size_uart_buf1;
			} else {
				/* there is overflow of us_wq_idx -> write in 2
				 * steps	*/
				memcpy(&buart_comm_data_1.puc_rq_buf[us_wr_idx],
						gs_puc_uart_buf1, us_end_size);
				us_part_size = gs_ul_size_uart_buf1 - us_end_size;
				memcpy(&buart_comm_data_1.puc_rq_buf[0],
						&gs_puc_uart_buf1[us_end_size], us_part_size);
				/* update counters */
				buart_comm_data_1.us_rq_count += gs_ul_size_uart_buf1;
				buart_comm_data_1.us_wq_idx = us_part_size;
			}
		} else { /* there is not enough space to write all data */
			tc_start(TC_UART, TC_UART_CHN);
		}

		/* change RX buffer */
		gs_ul_size_uart_buf1 = UART_BUFFER_SIZE;

		/* Restart read on buffer. */
		g_st_uart_rx_packet1.ul_addr = (uint32_t)gs_puc_uart_buf1;
		g_st_uart_rx_packet1.ul_size = UART_BUFFER_SIZE;
		pdc_rx_init(g_p_uart_pdc1, &g_st_uart_rx_packet1, NULL);

		/* Restart timer. */
		tc_start(TC_UART, TC_UART_CHN);
	}
}

 #endif
#endif  /* #if defined(CONF_BOARD_UART0) || defined(CONF_BOARD_UART1) */

/**
 * \brief This function opens an UART
 *
 * \note Opening of the specified UART implies initializing local variables and
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
int8_t buart_if_open(uint8_t chn, uint32_t bauds)
{
#if defined(CONF_BOARD_UART0) || defined(CONF_BOARD_UART1)
	sam_uart_opt_t uart_console_settings;

	/* MCK for UART */
	uart_console_settings.ul_mck = sysclk_get_cpu_hz();
	/* Expected baud rate. */
	uart_console_settings.ul_baudrate = bauds;
	/* Initialize value for UART mode register */
	uart_console_settings.ul_mode = UART_MR_PAR_NO;
#else
	UNUSED(bauds);
#endif

	/* check uart and it is close */
	if (chn >= 2) {
		return false;
	}

	if (buart_chn_open[chn]) {
		return false;
	}

	switch (chn) {
#ifdef CONF_BOARD_UART0
	case 0:
	{
		/* Configure PMC. */
		pmc_enable_periph_clk(ID_UART0);
		/* Configure UART. */
		uart_init(UART0, &uart_console_settings);

		/* Assign buffers to pointers */
		buart_comm_data_0.puc_tq_buf = ptr_tx_uart_buf0;
		buart_comm_data_0.puc_rq_buf = ptr_rx_uart_buf0;
		buart_comm_data_0.us_rq_count = 0;
		buart_comm_data_0.us_rq_idx = 0;
		buart_comm_data_0.us_wq_idx = 0;

		/* Get board UART0 PDC base address and enable receiver and
		 * transmitter. */
		g_p_uart_pdc0 = uart_get_pdc_base(UART0);
		pdc_enable_transfer(g_p_uart_pdc0,
				PERIPH_PTCR_RXTEN | PERIPH_PTCR_TXTEN);

		/* Start receiving data and start timer. */
		g_st_uart_rx_packet0.ul_addr = (uint32_t)gs_puc_uart_buf0;
		g_st_uart_rx_packet0.ul_size = UART_BUFFER_SIZE;
		pdc_rx_init(g_p_uart_pdc0, &g_st_uart_rx_packet0, NULL);

		/* Stop transmitting data */
		g_st_uart_tx_packet0.ul_addr = (uint32_t)buart_comm_data_0.puc_tq_buf;
		g_st_uart_tx_packet0.ul_size = 0;
		pdc_tx_init(g_p_uart_pdc0, &g_st_uart_tx_packet0, NULL);

		gs_ul_size_uart_buf0 = UART_BUFFER_SIZE;

		/* Transfer to PDC communication mode, disable RXRDY interrupt
		 * and enable RXBUFF interrupt. */
		uart_disable_interrupt(UART0, UART_IDR_RXRDY);
		uart_enable_interrupt(UART0, UART_IER_RXBUFF);

		/* Enable the receiver and transmitter. */
		uart_enable_tx(UART0);
		uart_enable_rx(UART0);

		/* Configure and enable interrupt of USART. */
		NVIC_SetPriority((IRQn_Type)UART0_IRQn, UART0_PRIO);
		NVIC_EnableIRQ(UART0_IRQn);

		buart_chn_open[chn] = true;
		num_bytes_rx_uart0 = 0;

		/* Configure TC uart */
		_configure_TC_uart();
		tc_start(TC_UART, TC_UART_CHN);
		return true;
	}
	break;
#endif

#ifdef CONF_BOARD_UART1
	case 1:
	{
		/* Configure PMC. */
		pmc_enable_periph_clk(ID_UART1);
		/* Configure UART. */
		uart_init(UART1, &uart_console_settings);

		/* Assign buffers to pointers */
		buart_comm_data_1.puc_tq_buf = ptr_tx_uart_buf1;
		buart_comm_data_1.puc_rq_buf = ptr_rx_uart_buf1;
		buart_comm_data_1.us_rq_count = 0;
		buart_comm_data_1.us_rq_idx = 0;
		buart_comm_data_1.us_wq_idx = 0;

		/* Get board UART1 PDC base address and enable receiver and
		 * transmitter. */
		g_p_uart_pdc1 = uart_get_pdc_base(UART1);
		pdc_enable_transfer(g_p_uart_pdc1,
				PERIPH_PTCR_RXTEN | PERIPH_PTCR_TXTEN);

		/* Start receiving data and start timer. */
		g_st_uart_rx_packet1.ul_addr = (uint32_t)gs_puc_uart_buf1;
		g_st_uart_rx_packet1.ul_size = UART_BUFFER_SIZE;
		pdc_rx_init(g_p_uart_pdc1, &g_st_uart_rx_packet1, NULL);

		/* Stop transmitting data */
		g_st_uart_tx_packet1.ul_addr = (uint32_t)buart_comm_data_1.puc_tq_buf;
		g_st_uart_tx_packet1.ul_size = 0;
		pdc_tx_init(g_p_uart_pdc1, &g_st_uart_tx_packet1, NULL);

		gs_ul_size_uart_buf1 = UART_BUFFER_SIZE;

		/* Transfer to PDC communication mode, disable RXRDY interrupt
		 * and enable RXBUFF interrupt. */
		uart_disable_interrupt(UART1, UART_IDR_RXRDY);
		uart_enable_interrupt(UART1, UART_IER_RXBUFF);

		/* Enable the receiver and transmitter. */
		uart_enable_tx(UART1);
		uart_enable_rx(UART1);

		/* Configure and enable interrupt of USART. */
		NVIC_SetPriority((IRQn_Type)UART1_IRQn, UART1_PRIO);
		NVIC_EnableIRQ(UART1_IRQn);

		buart_chn_open[chn] = true;
		num_bytes_rx_uart1 = 0;

		/* Configure TC uart */
		_configure_TC_uart();
		tc_start(TC_UART, TC_UART_CHN);
		return true;
	}
	break;
#endif
	default:
		return false;
	}
}

/**
 * \brief This function closes and disables communication in the specified UART.
 *
 * \param chn  Communication channel [0, 1]
 *
 * \retval true on success.
 * \retval false on failure.
 */
int8_t buart_if_close(uint8_t chn)
{
	if (!buart_chn_open[chn]) {
		return false;
	}

	switch (chn) {
#ifdef CONF_BOARD_UART0
	case 0:
	{
		uart_disable(UART0);
		uart_disable_interrupt(UART0, US_IDR_RXRDY);
		uart_disable_interrupt(UART0, US_IER_ENDRX);

		/* Stop TC */
		if (!buart_chn_open[1]) {
			tc_stop(TC_UART, TC_UART_CHN);
		}

		return true;
	}
	break;
#endif

#ifdef CONF_BOARD_UART1
	case 1:
	{
		uart_disable(UART1);
		uart_disable_interrupt(UART1, US_IDR_RXRDY);
		uart_disable_interrupt(UART1, US_IER_ENDRX);

		/* Stop TC */
		if (!buart_chn_open[0]) {
			tc_stop(TC_UART, TC_UART_CHN);
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
 * UART. If so configured, the function waits until all characters are received.
 * In this case, the watchdog timer must be reloaded to avoid a program reset.
 *
 * \param  chn     Communication channel [0, 1]
 * \param  buffer  Pointer to buffer for information
 * \param  len     Number of characters to receive
 *
 * \retval Number of received characters
 */
uint16_t buart_if_read(uint8_t chn, void *buffer, uint16_t len)
{
#if defined(CONF_BOARD_UART0) || defined(CONF_BOARD_UART1)
	uint16_t us_rd_idx = 0;
	uint16_t us_num_bytes_read, us_num_bytes_to_end, us_num_bytes_to_start;
	uint16_t us_total_pos;
	uint16_t us_buf_size;

	uint8_t *msg = (uint8_t *)buffer;
#else
	UNUSED(buffer);
	UNUSED(len);
#endif

	/* check uart is open */
	if (!buart_chn_open[chn]) {
		return 0;
	}

	switch (chn) {
#ifdef CONF_BOARD_UART0
	case 0:
		us_buf_size = RX_UART_BUF0_SIZE;
		/* check if there is any byte in rx queue */
		if (buart_comm_data_0.us_rq_count == 0) {
			return 0;
		}

		/* get counters */
		us_rd_idx = buart_comm_data_0.us_rq_idx;
		/* get number of bytes to read */
		if (buart_comm_data_0.us_rq_count >= len) {
			us_num_bytes_read = len;
		} else {
			us_num_bytes_read = buart_comm_data_0.us_rq_count;
		}

		/* check overflow us_rd_idx counter */
		us_total_pos = us_rd_idx + us_num_bytes_read;
		/* copy data to buffer */
		if (us_total_pos <= us_buf_size) {
			memcpy(msg, &buart_comm_data_0.puc_rq_buf[us_rd_idx],
					us_num_bytes_read);
			/* update counters */
			buart_comm_data_0.us_rq_count -= us_num_bytes_read;
			buart_comm_data_0.us_rq_idx += us_num_bytes_read;
		} else {
			/* copy data to buffer in fragments -> overflow
			 * us_rq_idx counter */
			us_num_bytes_to_start = us_total_pos - us_buf_size;
			us_num_bytes_to_end = us_num_bytes_read - us_num_bytes_to_start;
			memcpy(msg, &buart_comm_data_0.puc_rq_buf[us_rd_idx],
					us_num_bytes_to_end);
			msg += us_num_bytes_to_end;
			memcpy(msg, &buart_comm_data_0.puc_rq_buf[0],
					us_num_bytes_to_start);
			/* update counters */
			buart_comm_data_0.us_rq_count -= us_num_bytes_read;
			buart_comm_data_0.us_rq_idx = us_num_bytes_to_start;
		}

		return us_num_bytes_read;

		break;
#endif

#ifdef CONF_BOARD_UART1
	case 1:
		us_buf_size = RX_UART_BUF1_SIZE;
		/* check if there is any byte in rx queue */
		if (buart_comm_data_1.us_rq_count == 0) {
			return 0;
		}

		/* get counters */
		us_rd_idx = buart_comm_data_1.us_rq_idx;
		/* get number of bytes to read */
		if (buart_comm_data_1.us_rq_count >= len) {
			us_num_bytes_read = len;
		} else {
			us_num_bytes_read = buart_comm_data_1.us_rq_count;
		}

		/* check overflow us_rd_idx counter */
		us_total_pos = us_rd_idx + us_num_bytes_read;
		if (us_total_pos <= us_buf_size) {
			/* copy data to buffer */
			memcpy(msg, &buart_comm_data_1.puc_rq_buf[us_rd_idx],
					us_num_bytes_read);
			/* update counters */
			buart_comm_data_1.us_rq_count -= us_num_bytes_read;
			buart_comm_data_1.us_rq_idx += us_num_bytes_read;
		} else {
			/* copy data to buffer in fragments -> overflow
			 * us_rq_idx counter */
			us_num_bytes_to_start = us_total_pos - us_buf_size;
			us_num_bytes_to_end = us_num_bytes_read - us_num_bytes_to_start;
			memcpy(msg, &buart_comm_data_1.puc_rq_buf[us_rd_idx],
					us_num_bytes_to_end);
			msg += us_num_bytes_to_end;
			memcpy(msg, &buart_comm_data_1.puc_rq_buf[0],
					us_num_bytes_to_start);
			/* update counters */
			buart_comm_data_1.us_rq_count -= us_num_bytes_read;
			buart_comm_data_1.us_rq_idx = us_num_bytes_to_start;
		}

		return us_num_bytes_read;

		break;
#endif
	default:
		return 0;
	}
}

/**
 * \brief This function transmits a message.
 *
 * \note This function transmits characters via the specified UART.
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
uint16_t buart_if_write(uint8_t chn, const void *buffer, uint16_t len)
{
#if !defined(CONF_BOARD_UART0) || !defined(CONF_BOARD_UART1)
	UNUSED(buffer);
	UNUSED(len);
#endif

	/* check uart is open */
	if (!buart_chn_open[chn]) {
		return 0;
	}

	switch (chn) {
#ifdef CONF_BOARD_UART0
	case 0:
		if (len > TX_UART_BUF0_SIZE) {
			return 0;
		}

		while (pdc_read_tx_counter(g_p_uart_pdc0) > 0) {
		}
		memcpy(&buart_comm_data_0.puc_tq_buf[0], buffer, len);
		g_st_uart_tx_packet0.ul_addr = (uint32_t)&buart_comm_data_0.puc_tq_buf[0];
		g_st_uart_tx_packet0.ul_size = len;
		pdc_tx_init(g_p_uart_pdc0, &g_st_uart_tx_packet0, NULL);
		return len;
#endif

#ifdef CONF_BOARD_UART1
	case 1:
		if (len > TX_UART_BUF1_SIZE) {
			return 0;
		}

		while (pdc_read_tx_counter(g_p_uart_pdc1) > 0) {
		}
		memcpy(&buart_comm_data_1.puc_tq_buf[0], buffer, len);
		g_st_uart_tx_packet1.ul_addr = (uint32_t)&buart_comm_data_1.puc_tq_buf[0];
		g_st_uart_tx_packet1.ul_size = len;
		pdc_tx_init(g_p_uart_pdc1, &g_st_uart_tx_packet1, NULL);
		return len;
#endif

	default:
		return 0;
	}
}

/**
 * \brief Get byte from UART.
 *
 * \param  chn  Communication channel [0, 1]
 *
 * \retval Byte received
 * \retval -1 in case of no reception
 */
int buart_if_rx_char(uint8_t chn)
{
	uint8_t buf[4] = {0, 0, 0, 0};

	if (buart_if_read(chn, buf, 1) <= 0) {
		return (-1);
	}

	return buf[0];
}

/**
 * \brief Sent byte to UART.
 *
 * \param  chn   Communication channel [0, 1]
 * \param  data  Data to sent
 *
 * \retval Number of characters sent
 */
uint16_t buart_if_tx_char(uint8_t chn, char data)
{
	return (buart_if_write(chn, &data, 1));
}

/* @} */

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/* @endcond */
