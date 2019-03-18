/**
 * \file
 *
 * \brief Configurations for the WILC3000 Serial Bridge Application
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
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
 * This example demonstrates the use of the WILC3000 with the SAM4S Xplained Pro
 * board to behave as a station.<br>
 * It uses the following hardware:
 * - the SAM4S Xplained Pro.
 * - the WILC3000 SD interface.
 *
 * \section files Main Files
 * - Serial Bridge.c : Initialize the WILC3000 and creates the serial bridge interface.
 * - between UART and SPI or SDIO interfaces for WiFi and UART interface BLE.
 * \section usage Usage
 * 
 * \endcode
 * -# Build the program and download it into the board.
 * -# On the computer, open and configure a terminal application as the follows.
 * \code
 *    Baud Rate : 115200
 *    Data : 8bit
 *    Parity bit : none
 *    Stop bit : 1bit
 *    Flow control : none
 * \endcode
 * -# Start the application.
 * -# Now serial bridge application is ready to communicate with WILC3000 module with PC GUI tool.
 *
 * \section compinfo Compilation Information
 * This software was written for the GNU GCC compiler using Atmel Studio 6.2
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.atmel.com">Atmel</A>.\n
 */

#include "asf.h"
#include "uart_stream.h"
#include "FreeRTOS.h"
#include "osprintf.h"
#include "os/include/net_init.h"
#include "os/include/m2m_wifi_ex.h"
#include "bsp/include/nm_bsp.h"
#include "driver/source/nmbus.h"
#include "lwip/def.h"
#include "conf_wilc.h"
#include "bt_uart.h"

#include <string.h>
#include <stdio.h>

#ifndef MIN
#define MIN(x, y) (x > y) ? y : x
#endif

#define MODE_STA_STACK_SIZE		(1024 / sizeof(portSTACK_TYPE))
#define MODE_STA_PRIORITY			(tskIDLE_PRIORITY + 1)
extern void bt_serial_bridge();
#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- WILC station mode example --"STRING_EOL \
"-- "BOARD_NAME " --"STRING_EOL	\
"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

/** SysTick counter to avoid busy wait delay. */
uint32_t ms_ticks = 0;

void fatal(int code, const char *msg);
void fatal(int code, const char *msg)
{
	for (;;) {
	}
}

#if configUSE_MALLOC_FAILED_HOOK
void vApplicationMallocFailedHook(void);
void vApplicationMallocFailedHook(void)
{
	for (;;) {
	}
}
#endif

#if configCHECK_FOR_STACK_OVERFLOW
void vApplicationStackOverflowHook(xTaskHandle pxTask, signed char *pcTaskName);
void vApplicationStackOverflowHook(xTaskHandle pxTask, signed char *pcTaskName)
{
	/*TRACE("ERROR: STACK OVERFLOW");
	TRACE(pcTaskName);*/
	M2M_ERR("ERROR: STACK OVERFLOW");
	M2M_ERR(pcTaskName);
	for (;;) {
	}
}
#endif

static uint32_t fault_addr;
void hard_fault(uint32_t *args, uint32_t lr);
void hard_fault(uint32_t *args, uint32_t lr)
{
	fault_addr = args[6];
#ifndef WILC_SERIAL_BRIDGE_INTERFACE
	osprintf("Hard fault at address 0x%X\r\n", fault_addr);
#endif
	for (;;) {
	}
}

void HardFault_Handler(void)
{
	__asm(
		"  mov r0, #4          \n"
		"  mov r1, lr          \n"
		"  tst r0, r1          \n"
		"  beq using_msp       \n"
		"  mrs r0, psp         \n"
		"  b call_c            \n"
		"using_msp:            \n"
		"  mrs r0, msp         \n"
		"call_c:               \n"
		"  ldr r2, =hard_fault \n"
		"  bx r2               \n"
	);
}

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
uint8_t hci_recv_buffer[13];

static int bt_hci_reset_handler(uint8_t *buffer, uint8_t size)
{
		bt_usart_receive(hci_recv_buffer,7);
	bt_usart_stream_write_buffer(buffer,size);
	usart_stream_reset();
	return CMD_ERR_NO_ERROR;
	}
static int bt_hci_start_tx_handler(uint8_t *buffer, uint8_t size)
	{
	bt_usart_receive(hci_recv_buffer,7);
	bt_usart_stream_write_buffer(buffer,size);
	usart_stream_reset();
	return CMD_ERR_NO_ERROR;
	}
static int bt_hci_start_rx_handler(uint8_t *buffer, uint8_t size)
	{		
		bt_usart_receive(hci_recv_buffer,7);
	bt_usart_stream_write_buffer(buffer,size);
	usart_stream_reset();
	return CMD_ERR_NO_ERROR;
	}
static int bt_hci_stop_txrx_handler(uint8_t *buffer, uint8_t size)
	{
	bt_usart_receive(hci_recv_buffer,9);
	bt_usart_stream_write_buffer(buffer,size);
	usart_stream_reset();
	return CMD_ERR_NO_ERROR;
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
	uint32_t val = 0;

	if (checksum_check(buffer + 1, sizeof(struct uart_cmd_hdr)) != 0) {
		usart_stream_move(sizeof(struct uart_cmd_hdr) + 1);
		usart_stream_write(0x5A);
		return CMD_ERR_INVALID_FRAME;
	}

	buffer_to_cmd_hdr(buffer + 1, &cmd_hdr);

	usart_stream_move(sizeof(struct uart_cmd_hdr) + 1);
	usart_stream_write(0xAC);
#ifdef WILC_WIFI
	/* Translate it to SPI Read register command. */
	val = nm_read_reg(cmd_hdr.addr);
#endif
#ifdef WILC_BLE
	bt_usart_receive(&val,4);
	usart_stream_write_buffer(&cmd_hdr.addr,4);	
#endif
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
	
#ifdef WILC_WIFI
	nm_write_reg(cmd_hdr.addr, cmd_hdr.val);
#endif
#ifdef WILC_BLE
	usart_stream_write_buffer(cmd_hdr.addr,4);
	usart_stream_write_buffer(cmd_hdr.val,4);
#endif
	usart_stream_move(sizeof(struct uart_cmd_hdr) + 1);
	usart_stream_write(0xAC);
	memset(buffer,0,size);
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

	
#ifdef WILC_WIFI
	nm_read_block(cmd_hdr.addr, reg_buffer, payload_length);
#endif
#ifdef WILC_BLE
	bt_usart_receive(&reg_buffer[0],payload_length);
	usart_stream_write_buffer(cmd_hdr.addr,4);
#endif
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
#ifdef WILC_WIFI
	nm_write_block(cmd_hdr.addr, read_buffer, payload_length);
#endif
#ifdef WILC_BLE
	usart_stream_write_buffer(cmd_hdr.addr,4);
	usart_stream_write_buffer(&read_buffer,payload_length);
#endif
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
	{{0x01, 0x03, 0}, 2, 4, bt_hci_reset_handler}, /* nm_uart_sync_cmd */
	{{0x01, 0x1E, 0}, 2, 7, bt_hci_start_tx_handler}, /* nm_uart_sync_cmd */
	{{0x01, 0x1D, 0}, 2, 5, bt_hci_start_rx_handler}, /* nm_uart_sync_cmd */
	{{0x01, 0x1F, 0}, 2, 4, bt_hci_stop_txrx_handler}, /* nm_uart_sync_cmd */
};

#define HANDLER_SIZE sizeof(usart_handler) / sizeof(struct usart_frame)

uint8_t reset_sdio_buffer[13] = {0xA5,0x01,0x10,0x00,0x00,0x00,0x14,0x00,0x00,0xFF,0xFB,0xFF,0xFF};
uint8_t reset_buffer[13] = {0xA5,0x01,0x10,0x00,0x00,0x00,0x14,0x00,0x00,005,0x00,0x00,0x00};


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
#ifdef CONF_WILC_USE_SDIO
				if(!(memcmp(reset_buffer, buffer, 13)))
				{
					memcpy(buffer,reset_sdio_buffer,13);
				}
#endif
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
		} else if (buffer[0] != 0x12 && buffer[0] != 0xA5 && buffer[0] != 0x01) {
		/* Undefined message, send error. */
		usart_stream_write(0xEA);
		usart_stream_reset();
	}

}

/**
 * \brief Process input UART command and forward to SPI.
 */
static sint8 serial_bridge(void)
{
	sint8 ret = 0;
	uint8_t *usart_data;
	uint32_t usart_size;
#ifdef WILC_WIFI
	/* Initialize the WILC driver. */
	tstrWifiInitParam param;

	memset(&param, 0, sizeof(param));
	param.pfAppWifiCb = NULL;
	ret = os_m2m_wifi_init(&param);
	if (ret != M2M_SUCCESS) {
		puts("Failed to put the Initialize the Chip!\n");
		return M2M_ERR_INIT;
	}
#endif
#ifdef WILC_BLE
	nm_bsp_init();
	bt_serial_bridge();
	bt_usart_receive(hci_recv_buffer,1);
#endif
	usart_stream_reset();

	/* Process UART input command and forward to SPI. */
	while (1) {
		if (usart_stream_read(&usart_data, &usart_size) != 0) {
			continue;
		}
		usart_frame_parse(usart_data, usart_size);
	}
	return 0;
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
	/* Initialize the board. */
	sysclk_init();
	board_init();

	/* Initialize the UART console. */
	configure_usart(115200);

#ifdef WILC_BLE
    bt_configure_usart(115200);
#endif

	/* Create main task. */
	xTaskCreate(serial_bridge, (signed char *)"Serial Bridge", MODE_STA_STACK_SIZE, 0, MODE_STA_PRIORITY, 0);
	vTaskStartScheduler();
	
	while (1) {
	}
	
	return 0;
}
