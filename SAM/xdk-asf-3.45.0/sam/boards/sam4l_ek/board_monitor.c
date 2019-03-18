/**
 * \file
 *
 * \brief SAM4L-EK Board Monitor Control.
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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

#include "board_monitor.h"
#include "delay.h"

/** Board Monitor Message Start pattern. */
#define BM_MSG_START_PATTERN                0x75
/** Board Monitor Message Stop pattern. */
#define BM_MSG_STOP_PATTERN                 0xa3
/** Board Monitor Message Number of bytes to transfer. */
#define BM_MSG_LENGTH_DEFAULT               9
/** Board Monitor Message Default ID Message. */
#define BM_MSG_ID_DEFAULT                   0
/** Enable/disable the board monitor mouse-like pointer. */
#define BM_POINTER_CTRL                     0x01
/** Send new mouse pointer position. */
#define BM_POINTER_MOVE                     0x02
/** Enable/disable the board monitor. */
#define BM_CTRL                             0x03
/** Turn-on a LED of the board monitor. */
#define BM_LED_SET                          0x04
/** Turn-off a LED of the board monitor. */
#define BM_LED_CLR                          0x05
/** Toggle a LED of the board monitor. */
#define BM_LED_TGL                          0x06
/** Send MCU power saving information to the board monitor. */
#define BM_MCU_STATUS                       0x07
/** Enable/disable the pull-up on TWI lines. */
#define BM_PULLUP_TWI                       0x08
/** Send PicoUart Frame. */
#define BM_PICOUART_SEND                    0x09
/** Send Current Consumption Measured Request. */
#define BM_MCU_GET_CURRENT                  0x0A
/** Force Toggle of Button Line. */
#define BM_TGL_BUTTON                       0x0B
/** Return Current Consumption Measured. */
#define BM_MCU_RET_CURRENT                  0x0C
/** Send free size (in byte) of the board monitor command fifo request. */
#define BM_MCU_GET_FIFO_FREE_SIZE           0x0D
/** Return the free size (in byte) of the board monitor command fifo. */
#define BM_MCU_RET_FIFO_FREE_SIZE           0x0E
/** Print Text On Board Monitor. */
#define BM_PRINT_TEXT                       0x0F
/** Clear Print Text Area On Board Monitor. */
#define BM_PRINT_CLEAR                      0x10
/** Send Firmware Version Request. */
#define BM_GET_FIRMWARE_VERSION             0x11
/** Return Firmware Version value . */
#define BM_RET_FIRMWARE_VERSION             0x12

/**
 *  \brief Configure the USART.
 */
void bm_init(void)
{
	static uint32_t ul_sysclk;
	const sam_usart_opt_t usart_console_settings = {
		115200,
		US_MR_CHRL_8_BIT,
		US_MR_PAR_NO,
		US_MR_NBSTOP_1_BIT,
		US_MR_CHMODE_NORMAL,
		/* This field is only used in IrDA mode. */
		0
	};

	/* Get system clock. */
	ul_sysclk = sysclk_get_peripheral_bus_hz(BM_USART_USART);

	/* Configure sysclk. */
	sysclk_enable_peripheral_clock(BM_USART_USART);

	/* Configure UART. */
	usart_init_rs232(BM_USART_USART, &usart_console_settings, ul_sysclk);
}

void bm_ctrl(bool state)
{
	usart_enable_tx(BM_USART_USART);
	usart_putchar(BM_USART_USART, BM_MSG_START_PATTERN);
	usart_putchar(BM_USART_USART, 4 /* length */);
	usart_putchar(BM_USART_USART, BM_CTRL);
	usart_putchar(BM_USART_USART, state);
	usart_putchar(BM_USART_USART, BM_MSG_STOP_PATTERN);
	while (!usart_is_tx_empty(BM_USART_USART));
	usart_disable_tx(BM_USART_USART);
}
void bm_mouse_pointer_ctrl(bool state)
{
	usart_enable_tx(BM_USART_USART);
	usart_putchar(BM_USART_USART, BM_MSG_START_PATTERN);
	usart_putchar(BM_USART_USART, 4 /* length */);
	usart_putchar(BM_USART_USART, BM_POINTER_CTRL);
	usart_putchar(BM_USART_USART, state);
	usart_putchar(BM_USART_USART, BM_MSG_STOP_PATTERN);
	while (!usart_is_tx_empty(BM_USART_USART));
	usart_disable_tx(BM_USART_USART);
}
void bm_mouse_pointer_move(uint32_t x, uint32_t y)
{
	usart_enable_tx(BM_USART_USART);
	usart_putchar(BM_USART_USART, BM_MSG_START_PATTERN);
	usart_putchar(BM_USART_USART, 5 /* length */);
	usart_putchar(BM_USART_USART, BM_POINTER_MOVE);
	usart_putchar(BM_USART_USART, x);
	usart_putchar(BM_USART_USART, y);
	usart_putchar(BM_USART_USART, BM_MSG_STOP_PATTERN);
	while (!usart_is_tx_empty(BM_USART_USART));
	usart_disable_tx(BM_USART_USART);
}
void bm_led_set(uint32_t led)
{
	usart_enable_tx(BM_USART_USART);
	usart_putchar(BM_USART_USART, BM_MSG_START_PATTERN);
	usart_putchar(BM_USART_USART, 4 /* length */);
	usart_putchar(BM_USART_USART, BM_LED_SET);
	usart_putchar(BM_USART_USART, led);
	usart_putchar(BM_USART_USART, BM_MSG_STOP_PATTERN);
	while (!usart_is_tx_empty(BM_USART_USART));
	usart_disable_tx(BM_USART_USART);
}
void bm_led_clr(uint32_t led)
{
	usart_enable_tx(BM_USART_USART);
	usart_putchar(BM_USART_USART, BM_MSG_START_PATTERN);
	usart_putchar(BM_USART_USART, 4 /* length */);
	usart_putchar(BM_USART_USART, BM_LED_CLR);
	usart_putchar(BM_USART_USART, led);
	usart_putchar(BM_USART_USART, BM_MSG_STOP_PATTERN);
	while (!usart_is_tx_empty(BM_USART_USART));
	usart_disable_tx(BM_USART_USART);
}
void bm_led_tgl(uint32_t led)
{
	usart_enable_tx(BM_USART_USART);
	usart_putchar(BM_USART_USART, BM_MSG_START_PATTERN);
	usart_putchar(BM_USART_USART, 4 /* length */);
	usart_putchar(BM_USART_USART, BM_LED_TGL);
	usart_putchar(BM_USART_USART, led);
	usart_putchar(BM_USART_USART, BM_MSG_STOP_PATTERN);
	while (!usart_is_tx_empty(BM_USART_USART));
	usart_disable_tx(BM_USART_USART);
}

void bm_send_mcu_status(uint32_t power_scaling, uint32_t sleep_mode,
		uint32_t cpu_freq, uint32_t cpu_src)
{
	usart_enable_tx(BM_USART_USART);
	usart_putchar(BM_USART_USART, BM_MSG_START_PATTERN);
	usart_putchar(BM_USART_USART, 10 /* length */);
	usart_putchar(BM_USART_USART, BM_MCU_STATUS);
	usart_putchar(BM_USART_USART, power_scaling);
	usart_putchar(BM_USART_USART, sleep_mode);
	usart_putchar(BM_USART_USART, cpu_freq >> 24);
	usart_putchar(BM_USART_USART, (cpu_freq >> 16) & 0xff);
	usart_putchar(BM_USART_USART, (cpu_freq >> 8 ) & 0xff);
	usart_putchar(BM_USART_USART, cpu_freq & 0xff);
	usart_putchar(BM_USART_USART, cpu_src);
	usart_putchar(BM_USART_USART, BM_MSG_STOP_PATTERN);
	while (!usart_is_tx_empty(BM_USART_USART));
	usart_disable_tx(BM_USART_USART);
}

bool bm_get_mcu_current(uint32_t* sleep_mode, float* current)
{
	uint32_t current_d;
        uint32_t c;
	usart_enable_tx(BM_USART_USART);
	usart_putchar(BM_USART_USART, BM_MSG_START_PATTERN);
	usart_putchar(BM_USART_USART, 4 /* length */);
	usart_putchar(BM_USART_USART, BM_MCU_GET_CURRENT);
	usart_putchar(BM_USART_USART, *sleep_mode);
	usart_putchar(BM_USART_USART, BM_MSG_STOP_PATTERN);
	while (!usart_is_tx_empty(BM_USART_USART));
	usart_disable_tx(BM_USART_USART);
	usart_enable_rx(BM_USART_USART);
	// Check first caracter is start pattern
	usart_getchar(BM_USART_USART, &c);
	if (c == BM_MSG_STOP_PATTERN) {
		usart_getchar(BM_USART_USART, &c);
	}
	if (c != BM_MSG_START_PATTERN) {
		return false;
	}
	// Check second caracter is length
	usart_getchar(BM_USART_USART, &c);
	if (c != 8) {
		return false;
	}
	// Check third caracter is Current Command
	usart_getchar(BM_USART_USART, &c);
	if (c != BM_MCU_RET_CURRENT) {
		return false;
	}
	// Check third caracter is sleepmode
	usart_getchar(BM_USART_USART, &c);
	*sleep_mode = c;
	// Then read current
	usart_getchar(BM_USART_USART, &c);
	current_d = c<<24;
	usart_getchar(BM_USART_USART, &c);
	current_d |= c<<16;
	usart_getchar(BM_USART_USART, &c);
	current_d |= c<<8;
	usart_getchar(BM_USART_USART, &c);
	current_d |= c;
	*current = *(float*)& current_d;
	// Check last caracter is stop pattern
	usart_getchar(BM_USART_USART, &c);
	if (c != BM_MSG_STOP_PATTERN) {
		return false;
	}
	usart_disable_rx(BM_USART_USART);
	return true;
}

bool bm_get_fifo_free_size(uint16_t* free_size)
{
        uint32_t start, length, stop, cmd_id, c;

	// Wait for some microseconds in order to avoid fifo overrun
	//
	delay_ms(20);

	usart_enable_tx(BM_USART_USART);
	usart_putchar(BM_USART_USART, BM_MSG_START_PATTERN);
	usart_putchar(BM_USART_USART, 3 /* length */);
	usart_putchar(BM_USART_USART, BM_MCU_GET_FIFO_FREE_SIZE);
	usart_putchar(BM_USART_USART, BM_MSG_STOP_PATTERN);

	while (!usart_is_tx_empty(BM_USART_USART));
	usart_disable_tx(BM_USART_USART);
	usart_enable_rx(BM_USART_USART);
	
	// Check first character is start pattern
	usart_getchar(BM_USART_USART, &start);
	if (start == BM_MSG_STOP_PATTERN) {
		usart_getchar(BM_USART_USART, &start);
	}
	if (start != BM_MSG_START_PATTERN) {
		return false;
	}
	// Check second character is length
	usart_getchar(BM_USART_USART, &length);
	if (length != 5) {
		return false;
	}
	// Check third character is Current Command
	usart_getchar(BM_USART_USART, &cmd_id);
	if (cmd_id != BM_MCU_RET_FIFO_FREE_SIZE) {
		return false;
	}

	// Get Fifo free size
	usart_getchar(BM_USART_USART, &c);
	*free_size = c << 8;
	usart_getchar(BM_USART_USART, &c);
	*free_size |= c;

	// Check last character is stop pattern
	usart_getchar(BM_USART_USART, &stop);
	if (stop != BM_MSG_STOP_PATTERN) {
		return false;
	}
	usart_disable_rx(BM_USART_USART);
	return true;
}

void bm_send_picouart_frame(uint8_t frame, uint32_t timeout_ms)
{
	usart_enable_tx(BM_USART_USART);
	usart_putchar(BM_USART_USART, BM_MSG_START_PATTERN);
	usart_putchar(BM_USART_USART, 8 /* length */);
	usart_putchar(BM_USART_USART, BM_PICOUART_SEND);
	usart_putchar(BM_USART_USART, frame);
	usart_putchar(BM_USART_USART, timeout_ms & 0xff);
	usart_putchar(BM_USART_USART, (timeout_ms >> 8 ) & 0xff);
	usart_putchar(BM_USART_USART, (timeout_ms >> 16) & 0xff);
	usart_putchar(BM_USART_USART, timeout_ms >> 24);
	usart_putchar(BM_USART_USART, BM_MSG_STOP_PATTERN);
	while (!usart_is_tx_empty(BM_USART_USART));
	usart_disable_tx(BM_USART_USART);
}

void bm_tgl_button(uint32_t timeout_ms)
{
	usart_enable_tx(BM_USART_USART);
	usart_putchar(BM_USART_USART, BM_MSG_START_PATTERN);
	usart_putchar(BM_USART_USART, 7 /* length */);
	usart_putchar(BM_USART_USART, BM_TGL_BUTTON);
	usart_putchar(BM_USART_USART, timeout_ms & 0xff);
	usart_putchar(BM_USART_USART, (timeout_ms >> 8 ) & 0xff);
	usart_putchar(BM_USART_USART, (timeout_ms >> 16) & 0xff);
	usart_putchar(BM_USART_USART, timeout_ms >> 24);
	usart_putchar(BM_USART_USART, BM_MSG_STOP_PATTERN);
	while (!usart_is_tx_empty(BM_USART_USART));
	usart_disable_tx(BM_USART_USART);
}

void bm_pullup_twi(bool state)
{
	usart_enable_tx(BM_USART_USART);
	usart_putchar(BM_USART_USART, BM_MSG_START_PATTERN);
	usart_putchar(BM_USART_USART, 4 /* length */);
	usart_putchar(BM_USART_USART, BM_PULLUP_TWI);
	usart_putchar(BM_USART_USART, state);
	usart_putchar(BM_USART_USART, BM_MSG_STOP_PATTERN);
	while (!usart_is_tx_empty(BM_USART_USART));
	usart_disable_tx(BM_USART_USART);
}

void bm_print_clear(void)
{
	usart_enable_tx(BM_USART_USART);
	usart_putchar(BM_USART_USART, BM_MSG_START_PATTERN);
	usart_putchar(BM_USART_USART, 3 /* length */);
	usart_putchar(BM_USART_USART, BM_PRINT_CLEAR);
	usart_putchar(BM_USART_USART, BM_MSG_STOP_PATTERN);
	while (!usart_is_tx_empty(BM_USART_USART));
	usart_disable_tx(BM_USART_USART);
}

void bm_print_txt(uint8_t* str, uint8_t str_length)
{
#define BM_PRINT_TEXT_SIZE                  21
#define BM_PRINT_TEXT_DEEP                  6
	usart_enable_tx(BM_USART_USART);
	usart_putchar(BM_USART_USART, BM_MSG_START_PATTERN);
	usart_putchar(BM_USART_USART, BM_PRINT_TEXT_SIZE + 3 /* length */);
	usart_putchar(BM_USART_USART, BM_PRINT_TEXT);
	if (str_length < BM_PRINT_TEXT_SIZE) {
		for (uint8_t i=0;i<str_length;i++){
			usart_putchar(BM_USART_USART, str[i]);
		}
		for (uint8_t i=0;i < BM_PRINT_TEXT_SIZE - str_length;i++){
			usart_putchar(BM_USART_USART, '\0');
		}
	} else {
		for (uint8_t i=0;i<BM_PRINT_TEXT_SIZE;i++){
			usart_putchar(BM_USART_USART, str[i]);
		}
	}
	usart_putchar(BM_USART_USART, BM_MSG_STOP_PATTERN);
	while (!usart_is_tx_empty(BM_USART_USART));
	usart_disable_tx(BM_USART_USART);
}

bool bm_get_firmware_version(uint8_t* fw_minor_version, uint8_t* fw_major_version)
{
        uint32_t start, length, stop, cmd_id, c;

	// Wait for some microseconds in order to avoid fifo overrun
	//
	delay_ms(20);

	usart_enable_tx(BM_USART_USART);
	usart_putchar(BM_USART_USART, BM_MSG_START_PATTERN);
	usart_putchar(BM_USART_USART, 3 /* length */);
	usart_putchar(BM_USART_USART, BM_GET_FIRMWARE_VERSION);
	usart_putchar(BM_USART_USART, BM_MSG_STOP_PATTERN);

	while (!usart_is_tx_empty(BM_USART_USART));
	usart_disable_tx(BM_USART_USART);
	usart_enable_rx(BM_USART_USART);
	
	// Check first character is start pattern
	usart_getchar(BM_USART_USART, &start);
	if (start == BM_MSG_STOP_PATTERN) {
		usart_getchar(BM_USART_USART, &start);
	}
	if (start != BM_MSG_START_PATTERN) {
		return false;
	}
	// Check second character is length
	usart_getchar(BM_USART_USART, &length);
	if (length != 5) {
		return false;
	}
	// Check third character is Current Command
	usart_getchar(BM_USART_USART, &cmd_id);
	if (cmd_id != BM_RET_FIRMWARE_VERSION) {
		return false;
	}

	// Get Fifo free size
	usart_getchar(BM_USART_USART, &c);
	*fw_major_version = c;
	usart_getchar(BM_USART_USART, &c);
	*fw_minor_version = c;

	// Check last character is stop pattern
	usart_getchar(BM_USART_USART, &stop);
	if (stop != BM_MSG_STOP_PATTERN) {
		return false;
	}
	usart_disable_rx(BM_USART_USART);
	return true;
}
