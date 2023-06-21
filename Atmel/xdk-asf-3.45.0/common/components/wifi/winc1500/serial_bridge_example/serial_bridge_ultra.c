/**
 *
 * \file
 *
 * \brief Serial Bridge.
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

/** \mainpage
 * \section intro Introduction
 * This example demonstrates how to implement a EDBG UART to WINC1500 SPI
 * bridge.<br>
 * It uses the following hardware:
 * - the SAM Xplained Pro.
 * - the WINC1500 on EXT1.
 *
 * \section files Main Files
 * - serial_bridge_ultra.c : Initialize the WINC1500 perform bridge operation.
 *
 * \section compinfo Compilation Information
 * This software was written for the GNU GCC compiler using Atmel Studio 6.2
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com">Microchip</A>.\n
 */
 
#include <asf.h>
#include "common/include/nm_common.h"
#include "bsp/include/nm_bsp.h"
#include "bus_wrapper/include/nm_bus_wrapper.h"
#include "driver/source/nmbus.h"
#include "driver/include/m2m_wifi.h"
#include "stdio_serial.h"

/** UART commands. */
enum nm_usart_event_types {
	USART_PKT_RECEIVED = 0,
	USART_PKT_TRANSMITTED,
	USART_ERROR_ON_RECEPTION,
};

enum nm_usart_cmd_process_states {
	INIT = 0,
	WAIT_SYNC,
	WAITING,
	COLLECTING_HDR,
	COLLECTING_PAYLOAD,
	PROCESSING,
};

typedef struct uart_cmd_hdr_t {
	unsigned long cmd;
	unsigned long addr;
	unsigned long val;
} uart_cmd_hdr;

#define READ_REG                0
#define WRITE_REG               1
#define READ_BUFF               2
#define WRITE_BUFF              3
#define RESET                   4
#define RECONFIGURE_UART        5

#define CONF_STDIO_USART_MODULE  EDBG_CDC_MODULE
#define CONF_STDIO_MUX_SETTING   EDBG_CDC_SERCOM_MUX_SETTING
#define CONF_STDIO_PINMUX_PAD0   EDBG_CDC_SERCOM_PINMUX_PAD0
#define CONF_STDIO_PINMUX_PAD1   EDBG_CDC_SERCOM_PINMUX_PAD1
#define CONF_STDIO_PINMUX_PAD2   EDBG_CDC_SERCOM_PINMUX_PAD2
#define CONF_STDIO_PINMUX_PAD3   EDBG_CDC_SERCOM_PINMUX_PAD3
#define CONF_STDIO_BAUDRATE      115200

#define USART_CMD_HDR_LENGTH    sizeof(uart_cmd_hdr)
#define SPI_TRANSFER_SIZE       512

static struct usart_module cdc_uart_module;
static uint16_t usart_cmd_recv_buffer[8];
static uint16_t usart_payload_buffer[512];
static uint8_t usart_tx_buffer[16];
static uint8_t serial_command_pending = 0;
static uint8_t usart_pkt_received = 0;
static uint8_t usart_err_on_reception = 0;
static uint8 *uart_cmd_buf;
static uart_cmd_hdr uart_cmd;
static uint16_t schedule_rx_length = 0;
static uint8_t schedule_rx = 0;
static uint16_t *schedule_rx_buffer = NULL;
static uint8_t *usart_pkt = NULL;
static uint8_t usart_prot_handler_status = INIT;
static uint8_t new_state = INIT;
static uint8_t change_state = 0;
static uint8_t uart_reconfigure = 0;

static void usart_tx_complete_handler(struct usart_module *const module)
{
	if (schedule_rx) {
		if (schedule_rx_length == 1) {
			usart_read_job((struct usart_module *)module, schedule_rx_buffer);
		} else {
			usart_read_buffer_job((struct usart_module *)module, (uint8_t *)schedule_rx_buffer, schedule_rx_length);
		}

		schedule_rx = 0;
	}

	if (change_state) {
		usart_prot_handler_status = new_state;
		change_state = 0;
	}
}

static void usart_rx_complete_handler(struct usart_module *const module)
{
	usart_pkt_received = 1;
	usart_pkt = (uint8_t *)(module->rx_buffer_ptr - schedule_rx_length);
	if (change_state) {
		usart_prot_handler_status = new_state;
		change_state = 0;
	}
}

static void nm_usart_send_regval(struct usart_module *module, uint8_t *tx_data, uint16_t length)
{
	uint8_t temp, i, j;
	for (i = 0, j = (length - 1); i < j; i++, j--) {
		temp = tx_data[i];
		tx_data[i] = tx_data[j];
		tx_data[j] = temp;
	}
	usart_write_buffer_job(module, tx_data, length);
}

static void nm_usart_protocol_handler(struct usart_module *module, enum nm_usart_event_types event_name)
{
	static uint16_t payload_length = 0;
	uint8 checksum = 0;
	uint16_t uartdata;
	uint8 i;

	switch (usart_prot_handler_status) {
	case INIT:
		if ((event_name == USART_PKT_RECEIVED) && (schedule_rx_length == 1)) {
			if ((usart_pkt[0] == 0x12)) {
				usart_prot_handler_status = WAIT_SYNC;
				usart_cmd_recv_buffer[0] = 0xFF;
				schedule_rx_buffer = &usart_cmd_recv_buffer[0];
				schedule_rx_length = 1;
				schedule_rx = 1;
				uartdata = 0x5B;
				usart_write_job(module, &uartdata);
			} else {
				schedule_rx_buffer = &usart_cmd_recv_buffer[0];
				schedule_rx_length = 1;
				schedule_rx = 1;
				uartdata = usart_pkt[0];
				usart_write_job(module, &uartdata);
				/* usart_read_job(module,&usart_cmd_recv_buffer[0]); */
			}
		} else {
			usart_cmd_recv_buffer[0] = 0xFF;
			schedule_rx_buffer = &usart_cmd_recv_buffer[0];
			schedule_rx_length = 1;
			schedule_rx = 1;
			uartdata = 0xEA;
			usart_write_job(module, &uartdata);
		}

		break;

	case WAIT_SYNC:
		if (event_name == USART_PKT_RECEIVED) {
			if (usart_pkt[0] == 0xA5) {
				uint8 *usart_cmd_recv_buffer_u8 = (uint8 *)&usart_cmd_recv_buffer[0];
				usart_prot_handler_status = WAITING;
				usart_cmd_recv_buffer_u8[4] = 0xFF;
				schedule_rx_length = 1;
				usart_read_job(module, &usart_cmd_recv_buffer[2]);
			} else if (usart_pkt[0] == 0x12) {
				/* UART identification command. */
				uartdata = 0x5B;
				usart_cmd_recv_buffer[0] = 0xFF;
				schedule_rx_buffer = &usart_cmd_recv_buffer[0];
				schedule_rx_length = 1;
				schedule_rx = 1;
				usart_write_job(module, &uartdata);
			} else {
				if (!uart_reconfigure) {
					uartdata = 0x5A;
					usart_cmd_recv_buffer[0] = 0xFF;
					schedule_rx_buffer = &usart_cmd_recv_buffer[0];
					schedule_rx_length = 1;
					schedule_rx = 1;
					usart_write_job(module, &uartdata);
				} else {
					schedule_rx_length = 1;
					usart_read_job(module, &usart_cmd_recv_buffer[0]);
				}
			}
		}

		break;

	case WAITING:
		if (event_name == USART_PKT_RECEIVED) {
			usart_prot_handler_status = COLLECTING_HDR;
			uart_cmd_buf = usart_pkt;
			schedule_rx_length = (USART_CMD_HDR_LENGTH - 1);
			usart_read_buffer_job(module, (uint8_t *)module->rx_buffer_ptr, (USART_CMD_HDR_LENGTH - 1));
		} else {
			usart_prot_handler_status = WAIT_SYNC;
			schedule_rx_buffer = &usart_cmd_recv_buffer[0];
			schedule_rx = 1;
			schedule_rx_length = 1;
			uartdata = 0xEA;
			usart_write_job(module, &uartdata);
		}

		break;

	case COLLECTING_HDR:
		if (event_name == USART_PKT_RECEIVED) {
			/* Verify checksum. */
			for (i = 0; i < (USART_CMD_HDR_LENGTH); i++) {
				checksum ^= *(((uint8_t *)uart_cmd_buf) + i);
			}
			if (checksum != 0) {
				usart_prot_handler_status = WAIT_SYNC;
				usart_cmd_recv_buffer[0] = 0xFF;
				schedule_rx_buffer = &usart_cmd_recv_buffer[0];
				schedule_rx_length = 1;
				schedule_rx = 1;
				uartdata = 0x5A;
				usart_write_job(module, &uartdata);
			} else {
				memcpy(&uart_cmd, uart_cmd_buf, sizeof(uart_cmd_hdr));
				/* Process the Command. */
				if ((uart_cmd.cmd & 0xFF) == WRITE_BUFF) {
					usart_prot_handler_status = COLLECTING_PAYLOAD;
					payload_length = (uart_cmd.cmd >> 16) & 0xFFFF;
					schedule_rx = 1;
					schedule_rx_buffer = &usart_payload_buffer[0];
					schedule_rx_length = payload_length;
					uartdata = 0xAC;
					usart_write_job(module, &uartdata);
				} else if ((uart_cmd.cmd & 0xFF) == WRITE_REG) {
					serial_command_pending = 1;
					usart_prot_handler_status = PROCESSING;
				} else {
					serial_command_pending = 1;
					change_state = 1;
					new_state = PROCESSING;
					uartdata = 0xAC;
					usart_write_job(module, &uartdata);
				}
			}
		} else if (event_name == USART_ERROR_ON_RECEPTION) {
			usart_prot_handler_status = WAIT_SYNC;
			schedule_rx_buffer = &usart_cmd_recv_buffer[0];
			schedule_rx = 1;
			schedule_rx_length = 1;
			uartdata = 0xEA;
			usart_write_job(module, &uartdata);
		}

		break;

	case COLLECTING_PAYLOAD:
		if ((event_name == USART_PKT_RECEIVED) && (schedule_rx_length == payload_length)) {
			serial_command_pending = 1;
			usart_prot_handler_status = PROCESSING;
		} else if (event_name == USART_ERROR_ON_RECEPTION) {
			usart_prot_handler_status = WAIT_SYNC;
			uartdata = 0xEA;
			usart_cmd_recv_buffer[0] = 0xFF;
			schedule_rx_length = 1;
			schedule_rx_buffer = &usart_cmd_recv_buffer[0];
			schedule_rx = 1;
			usart_write_job(module, &uartdata);
		} else {
			usart_prot_handler_status = WAIT_SYNC;
			uartdata = 0x5A;
			usart_cmd_recv_buffer[0] = 0xFF;
			schedule_rx_length = 1;
			schedule_rx_buffer = &usart_cmd_recv_buffer[0];
			schedule_rx = 1;
			usart_write_job(module, &uartdata);
		}

		break;

	default:
		usart_prot_handler_status = WAIT_SYNC;
		break;
	}
}

/**
 * \brief Configure UART console.
 *
 * \param baud UART baudrate to use.
 */
static void configure_console(uint32_t baud)
{
	struct usart_config usart_conf;

	usart_get_config_defaults(&usart_conf);
	usart_conf.mux_setting = CONF_STDIO_MUX_SETTING;
	usart_conf.pinmux_pad0 = CONF_STDIO_PINMUX_PAD0;
	usart_conf.pinmux_pad1 = CONF_STDIO_PINMUX_PAD1;
	usart_conf.pinmux_pad2 = CONF_STDIO_PINMUX_PAD2;
	usart_conf.pinmux_pad3 = CONF_STDIO_PINMUX_PAD3;
	usart_conf.baudrate    = baud;
	stdio_serial_init(&cdc_uart_module, CONF_STDIO_USART_MODULE, &usart_conf);
	usart_register_callback(&cdc_uart_module, usart_rx_complete_handler, USART_CALLBACK_BUFFER_RECEIVED);
	usart_register_callback(&cdc_uart_module, usart_tx_complete_handler, USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_enable_callback(&cdc_uart_module, USART_CALLBACK_BUFFER_RECEIVED);
	usart_enable_callback(&cdc_uart_module, USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_enable(&cdc_uart_module);
	schedule_rx_length = 1;
	usart_read_job(&cdc_uart_module, &usart_cmd_recv_buffer[0]);
}

/**
 * \brief Process input UART command and forward to SPI.
 */
static sint8 enter_wifi_firmware_download(void)
{
	uint16_t uartdata;
	sint8 ret;

	ret = m2m_wifi_download_mode();
	if (ret != M2M_SUCCESS) {
		puts("Failed to put the WiFi Chip in download mode!\n");
		return M2M_ERR_INIT;
	}

	/* Process UART input command and forward to SPI. */
	while (1) {
		if (usart_pkt_received) {
			usart_pkt_received = 0;
			nm_usart_protocol_handler(&cdc_uart_module, USART_PKT_RECEIVED);
		}

		if (usart_err_on_reception) {
			usart_err_on_reception = 0;
			nm_usart_protocol_handler(&cdc_uart_module, USART_ERROR_ON_RECEPTION);
		}

		if (serial_command_pending && (usart_prot_handler_status == PROCESSING)) {
			uint32_t temp;
			switch ((uart_cmd.cmd) & 0xFF) {
			/* Forward it to SPI. */
			case READ_REG:
				/* Translate it to SPI Read register command. */
				temp = nm_read_reg(uart_cmd.addr);
				usart_tx_buffer[0] = (uint8)(temp >> 0);
				usart_tx_buffer[1] = (uint8)(temp >> 8);
				usart_tx_buffer[2] = (uint8)(temp >> 16);
				usart_tx_buffer[3] = (uint8)(temp >> 24);
				schedule_rx_buffer = &usart_cmd_recv_buffer[0];
				schedule_rx_length = 1;
				schedule_rx = 1;
				usart_prot_handler_status = WAIT_SYNC;
				nm_usart_send_regval(&cdc_uart_module, &usart_tx_buffer[0], sizeof(uint32_t));
				break;

			case WRITE_REG:
				/* Translate it to SPI Write register command. */
				nm_write_reg(uart_cmd.addr, uart_cmd.val);
				schedule_rx_buffer = &usart_cmd_recv_buffer[0];
				schedule_rx_length = 1;
				schedule_rx = 1;
				uartdata = 0xAC;
				usart_prot_handler_status = WAIT_SYNC;
				usart_write_job(&cdc_uart_module, &uartdata);
				break;

			case READ_BUFF:
				/* Translate it to SPI Read buffer command. */
				nm_read_block(uart_cmd.addr, (uint8 *)&usart_payload_buffer[0], ((uart_cmd.cmd >> 16) & 0xFFFF));
				schedule_rx_buffer = &usart_cmd_recv_buffer[0];
				schedule_rx_length = 1;
				schedule_rx = 1;
				usart_prot_handler_status = WAIT_SYNC;
				usart_write_buffer_job(&cdc_uart_module, (uint8 *)&usart_payload_buffer[0], ((uart_cmd.cmd >> 16) & 0xFFFF));
				break;

			case WRITE_BUFF:
				/* Translate it to SPI Write buffer command. */
				nm_write_block(uart_cmd.addr, (uint8 *)&usart_payload_buffer[0], ((uart_cmd.cmd >> 16) & 0xFFFF));
				schedule_rx_buffer = &usart_cmd_recv_buffer[0];
				schedule_rx_length = 1;
				schedule_rx = 1;
				uartdata = 0xAC;
				usart_prot_handler_status = WAIT_SYNC;
				usart_write_job(&cdc_uart_module, &uartdata);
				break;

			case RECONFIGURE_UART:
				/* Send ACK. */
				usart_prot_handler_status = WAIT_SYNC;
				uart_reconfigure = 1;
				usart_disable(&cdc_uart_module);
				configure_console(uart_cmd.val);
				break;

			default:
				break;
			}
			serial_command_pending = 0;
		}
	}
	return ret;
}

/**
 * \brief Main application function.
 *
 * Application entry point.
 *
 * \return program return value.
 */
int main(void)
{
	/* Initialize the system. */
	system_init();

	/* Initialize the UART console. */
	configure_console(CONF_STDIO_BAUDRATE);

	/* Initialize WINC IOs. */
	nm_bsp_init();

	/* Enter WiFi firmware download mode. */
	enter_wifi_firmware_download();

	return 0;
}
