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
#include "bus_wrapper/include/nm_bus_wrapper.h"
#include "driver/source/nmbus.h"
#include "driver/include/m2m_wifi.h"
#include "usart_stream.h"
#include <string.h>

#ifndef MIN
#define MIN(x, y) (x > y) ? y : x
#endif

enum cmd_err_code {
	CMD_ERR_NO_ERROR = 0,
	CMD_ERR_INTERNAL_ERROR,
	CMD_ERR_INVALID_FRAME,
};

struct uart_cmd_hdr {
	uint32_t cmd;
	uint32_t addr;
	uint32_t val;
};

static void buffer_to_cmd_hdr(uint8_t *buffer, struct uart_cmd_hdr *cmd_hdr)
{
	union {
		uint32_t i;
		char c[4];
	}
	bint = {0x01020304};

	if (bint.c[0] == 1) {
		/* Big endian. */
		cmd_hdr->cmd = ((uint32)buffer[0] << 24) | ((uint32)buffer[1] << 16) | ((uint32)buffer[2] << 8) | ((uint32)buffer[3] << 0);
		cmd_hdr->addr = ((uint32)buffer[4] << 24) | ((uint32)buffer[5] << 16) | ((uint32)buffer[6] << 8) | ((uint32)buffer[7] << 0);
		cmd_hdr->val = ((uint32)buffer[8] << 24) | ((uint32)buffer[9] << 16) | ((uint32)buffer[10] << 8) | ((uint32)buffer[11] << 0);
	} else {
		/* Little endian. */
		memcpy(cmd_hdr, buffer, sizeof(struct uart_cmd_hdr));
	}
}

static uint8_t checksum_check(uint8_t *buffer, uint8_t size)
{
	uint8 checksum = 0;
	int i;

	for (i = 0; i < size; i++) {
		checksum ^= buffer[i];
	}

	return checksum;
}

static int usart_sync_cmd_handler(uint8_t *buffer, uint8_t size)
{
	usart_stream_move(1);
	usart_stream_write(0x5B);

	return CMD_ERR_NO_ERROR;
}

static int usart_read_reg_with_ret_handler(uint8_t *buffer, uint8_t size)
{
	struct uart_cmd_hdr cmd_hdr;
	uint32_t val;

	if (checksum_check(buffer + 1, sizeof(struct uart_cmd_hdr)) != 0) {
		usart_stream_move(sizeof(struct uart_cmd_hdr) + 1);
		usart_stream_write(0x5A);
		return CMD_ERR_INVALID_FRAME;
	}

	buffer_to_cmd_hdr(buffer + 1, &cmd_hdr);

	usart_stream_move(sizeof(struct uart_cmd_hdr) + 1);
	usart_stream_write(0xAC);

	/* Translate it to SPI Read register command. */
	val = nm_read_reg(cmd_hdr.addr);
	usart_stream_write((uint8_t)(val >> 24));
	usart_stream_write((uint8_t)(val >> 16));
	usart_stream_write((uint8_t)(val >> 8));
	usart_stream_write((uint8_t)(val >> 0));

	return CMD_ERR_NO_ERROR;
}

static int usart_write_reg_handler(uint8_t *buffer, uint8_t size)
{
	struct uart_cmd_hdr cmd_hdr;

	if (checksum_check(buffer + 1, sizeof(struct uart_cmd_hdr)) != 0) {
		usart_stream_move(sizeof(struct uart_cmd_hdr) + 1);
		usart_stream_write(0x5A);
		return CMD_ERR_INVALID_FRAME;
	}

	buffer_to_cmd_hdr(buffer + 1, &cmd_hdr);
	nm_write_reg(cmd_hdr.addr, cmd_hdr.val);

	usart_stream_move(sizeof(struct uart_cmd_hdr) + 1);
	usart_stream_write(0xAC);

	return CMD_ERR_NO_ERROR;
}

static int usart_read_block_handler(uint8_t *buffer, uint8_t size)
{
	struct uart_cmd_hdr cmd_hdr;
	uint8_t reg_buffer[USART_BUFFER_MAX];
	uint32_t payload_length;

	if (checksum_check(buffer + 1, sizeof(struct uart_cmd_hdr)) != 0) {
		usart_stream_move(sizeof(struct uart_cmd_hdr) + 1);
		usart_stream_write(0x5A);
		return CMD_ERR_INVALID_FRAME;
	}

	buffer_to_cmd_hdr(buffer + 1, &cmd_hdr);
	usart_stream_write(0xAC);

	payload_length = (cmd_hdr.cmd >> 16) & 0xFFFF;

	nm_read_block(cmd_hdr.addr, reg_buffer, payload_length);

	usart_stream_move(sizeof(struct uart_cmd_hdr) + 1);
	usart_stream_write_buffer(reg_buffer, payload_length);

	return CMD_ERR_NO_ERROR;
}

static int usart_write_block_handler(uint8_t *buffer, uint8_t size)
{
	struct uart_cmd_hdr cmd_hdr;
	uint16_t payload_length;
	uint32_t read_size;
	uint8 *read_buffer;

	if (checksum_check(buffer + 1, sizeof(struct uart_cmd_hdr)) != 0) {
		usart_stream_move(sizeof(struct uart_cmd_hdr) + 1);
		usart_stream_write(0x5A);
		return CMD_ERR_INVALID_FRAME;
	}

	buffer_to_cmd_hdr(buffer + 1, &cmd_hdr);
	payload_length = (cmd_hdr.cmd >> 16) & 0xFFFF;

	usart_stream_move(sizeof(struct uart_cmd_hdr) + 1);
	usart_stream_write(0xAC);

	while (1) {
		if (usart_stream_read(&read_buffer, &read_size)) {
			continue;
		}

		if (read_size < payload_length) {
			continue;
		}

		break;
	}

	nm_write_block(cmd_hdr.addr, read_buffer, payload_length);
	usart_stream_move(payload_length);
	usart_stream_write(0xAC);

	return CMD_ERR_NO_ERROR;
}

static int usart_reconfigure_handler(uint8_t *buffer, uint8_t size)
{
	struct uart_cmd_hdr cmd_hdr;

	if (checksum_check(buffer + 1, sizeof(struct uart_cmd_hdr)) != 0) {
		usart_stream_move(sizeof(struct uart_cmd_hdr) + 1);
		usart_stream_write(0x5A);
		return CMD_ERR_INVALID_FRAME;
	}

	buffer_to_cmd_hdr(buffer + 1, &cmd_hdr);
	usart_stream_move(sizeof(struct uart_cmd_hdr) + 1);
	usart_stream_write(0xAC);

	configure_usart(cmd_hdr.val);

	return CMD_ERR_NO_ERROR;
}

struct usart_frame {
	uint8_t header[4];
	uint32_t header_size;
	uint32_t min_size;
	int (*handler)(uint8_t *buffer, uint8_t size);
};

struct usart_frame usart_handler[] = {
	{{0x12, 0}, 1, 1, usart_sync_cmd_handler}, /* nm_uart_sync_cmd */
	{{0xa5, 0x00, 0}, 2, sizeof(struct uart_cmd_hdr) + 1, usart_read_reg_with_ret_handler}, /* nm_uart_read_reg_with_ret */
	{{0xa5, 0x01, 0}, 2, sizeof(struct uart_cmd_hdr) + 1, usart_write_reg_handler}, /* nm_uart_write_reg */
	{{0xa5, 0x02, 0}, 2, sizeof(struct uart_cmd_hdr) + 1, usart_read_block_handler}, /* nm_uart_read_block */
	{{0xa5, 0x03, 0}, 2, sizeof(struct uart_cmd_hdr) + 1, usart_write_block_handler}, /* nm_uart_write_block */
	{{0xa5, 0x04, 0}, 2, 2, NULL}, /* Reset */
	{{0xa5, 0x05, 0}, 2, sizeof(struct uart_cmd_hdr) + 1, usart_reconfigure_handler}, /* nm_uart_reconfigure */
	{{0xa5, 0x0A, 0}, 2, 2, NULL}, /* Read SPI read GPIO */
};

#define HANDLER_SIZE sizeof(usart_handler) / sizeof(struct usart_frame)

/**
 * \brief Parse incoming frame and find the handler to process the request.
 */
static void usart_frame_parse(uint8_t *buffer, uint8_t size)
{
	if (size == 0) {
		return;
	}

	for (uint32_t i = 0; i < HANDLER_SIZE; i++) {
		if (size >= usart_handler[i].min_size &&
				!memcmp(usart_handler[i].header, buffer, usart_handler[i].header_size)) {
			if (usart_handler[i].handler) {
				if ((usart_handler[i].handler(buffer, size)) == 0) {
					return;
				} else {
					break;
				}
			}
		}
	}

	if (buffer[0] == 0xFF) {
		usart_stream_reset();
	} else if (buffer[0] != 0x12 && buffer[0] != 0xA5) {
		/* Undefined message, send error. */
		usart_stream_write(0xEA);
		usart_stream_reset();
	}
}

/**
 * \brief Process input UART command and forward to SPI.
 */
static sint8 enter_wifi_firmware_download(void)
{
	sint8 ret;
	uint8_t *usart_data;
	uint32_t usart_size;

	ret = m2m_wifi_download_mode();
	if (ret != M2M_SUCCESS) {
		puts("Failed to put the WiFi Chip in download mode!\n");
		return M2M_ERR_INIT;
	}

	usart_stream_reset();

	/* Process UART input command and forward to SPI. */
	while (1) {
		if (usart_stream_read(&usart_data, &usart_size) != 0) {
			continue;
		}

		usart_frame_parse(usart_data, usart_size);
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
	sysclk_init();
	board_init();

	/* Initialize the UART console. */
	configure_usart(115200);

	/* Initialize WINC IOs. */
	nm_bsp_init();

	/* Enter WiFi firmware download mode. */
	enter_wifi_firmware_download();

	return 0;
}
