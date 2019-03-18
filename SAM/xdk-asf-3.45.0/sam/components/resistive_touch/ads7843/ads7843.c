/**
 * \file
 *
 * \brief API driver for component ADS7843.
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

#include "ads7843.h"
#include "conf_ads7843.h"
#include "board.h"
#include "ioport.h"
#include "pio_handler.h"
#include "pio.h"
#include "spi_master.h"
#include "conf_spi_master.h"

/** PD0 */
#define ADS_CTRL_PD0              (1 << 0)
/** PD1 */
#define ADS_CTRL_PD1              (1 << 1)
/** SER/DFR */
#define ADS_CTRL_DFR              (1 << 2)
/** Mode */
#define ADS_CTRL_EIGHT_BITS_MOD   (1 << 3)
/** Start Bit */
#define ADS_CTRL_START            (1 << 7)
/** Address setting */
#define ADS_CTRL_SWITCH_SHIFT     4

/** Get X position command */
#define CMD_Y_POSITION ((1 << ADS_CTRL_SWITCH_SHIFT) | ADS_CTRL_START |\
		ADS_CTRL_PD0 | ADS_CTRL_PD1)

/** Get Y position command */
#define CMD_X_POSITION ((5 << ADS_CTRL_SWITCH_SHIFT) | ADS_CTRL_START |\
		ADS_CTRL_PD0 | ADS_CTRL_PD1)

/** Enable penIRQ */
#define CMD_ENABLE_PENIRQ  ((1 << ADS_CTRL_SWITCH_SHIFT) | ADS_CTRL_START)

#define ADS7843_TIMEOUT        5000000
#define ADS7843_BUFSIZE        3

/** Frequence rate for sending one bit */
#define ADS7843_SPI_BAUDRATE   1000000

/** 2us min (tCSS) <=> 200/100 000 000 = 2us */
#define DELAY_BEFORE_SPCK          200
/** 5us min (tCSH) <=> (32 * 15) / (100 000 000) = 5us */
#define DELAY_BETWEEN_CONS_COM     0xf

/** @cond 0*/
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/** @endcond*/

/**
 * \brief Send a command to the ADS7843 touch controller.
 *
 * \param uc_cmd command to send.
 *
 * \return Command result.
 */
static uint32_t ads7843_send_cmd(uint8_t uc_cmd)
{
	uint32_t uResult = 0;
	volatile uint32_t i;
	uint8_t data;
	uint32_t timeout = SPI_TIMEOUT;

	/** (volatile declaration needed for code optimisation by compiler) */
	volatile uint8_t bufferRX[ADS7843_BUFSIZE];
	volatile uint8_t bufferTX[ADS7843_BUFSIZE];

	bufferRX[0] = 0;
	bufferRX[1] = 0;
	bufferRX[2] = 0;

	bufferTX[0] = uc_cmd;
	bufferTX[1] = 0;
	bufferTX[2] = 0;

	for(i = 0; i < ADS7843_BUFSIZE; i++){
		timeout = SPI_TIMEOUT;
		while (!spi_is_tx_ready(BOARD_ADS7843_SPI_BASE)) {
			if (!timeout--) {
				return SPI_ERROR_TIMEOUT;
			}
		}
		spi_write_single(BOARD_ADS7843_SPI_BASE, bufferTX[i]);
	}
	for(i = 0; i < ADS7843_BUFSIZE; i++){
		timeout = SPI_TIMEOUT;
		while (!spi_is_rx_full(BOARD_ADS7843_SPI_BASE)) {
			if (!timeout--) {
				return SPI_ERROR_TIMEOUT;
			}
		}
		spi_read_single(BOARD_ADS7843_SPI_BASE, &data);
		bufferRX[i] = data;
	}

	uResult = (uint32_t)bufferRX[1] << 8;
	uResult |= (uint32_t)bufferRX[2];
	uResult = uResult >> 4;

	return uResult;
}

uint32_t ads7843_is_pressed(void)
{
	return (ioport_get_pin_level(BOARD_ADS7843_IRQ_GPIO) ==
			IOPORT_PIN_LEVEL_LOW);
}

void ads7843_set_handler(void (*p_handler) (uint32_t, uint32_t))
{
	/** Initialize interrupts */
	pio_handler_set_pin(BOARD_ADS7843_IRQ_GPIO,
			BOARD_ADS7843_IRQ_FLAGS,
			(void (*)(uint32_t, uint32_t)) p_handler
			);

	/** Enable the interrupt */
	pio_enable_pin_interrupt(BOARD_ADS7843_IRQ_GPIO);
}

void ads7843_enable_interrupt(void)
{
	/** Enable the interrupt */
	pio_enable_pin_interrupt(BOARD_ADS7843_IRQ_GPIO);
}

void ads7843_disable_interrupt(void)
{
	/** Disable the interrupt */
	pio_disable_pin_interrupt(BOARD_ADS7843_IRQ_GPIO);
}

void ads7843_get_raw_point(uint32_t *p_x, uint32_t *p_y)
{
	/** Disable interrupt to quickly evaluate the coordinates */
	pio_disable_pin_interrupt(BOARD_ADS7843_IRQ_GPIO);

	/** Get X position */
	*p_x = ads7843_send_cmd(CMD_X_POSITION);

	/** Get Y position */
	*p_y = ads7843_send_cmd(CMD_Y_POSITION);

	/** Switch to full power mode */
	ads7843_send_cmd(CMD_ENABLE_PENIRQ);

	/** Re-enable interrupt */
	pio_enable_pin_interrupt(BOARD_ADS7843_IRQ_GPIO);
}

uint32_t ads7843_init(void)
{
	volatile uint32_t uDummy;
	struct spi_device ADS7843_SPI_DEVICE_CFG = {
		/** Board specific chip select configuration*/
#ifdef BOARD_ADS7843_SPI_NPCS
		.id = BOARD_ADS7843_SPI_NPCS
#else
#warning The board TouchScreen chip select definition is missing. Default configuration is used.
		.id = 0
#endif
	};

	spi_master_init(BOARD_ADS7843_SPI_BASE);
	spi_master_setup_device(BOARD_ADS7843_SPI_BASE, &ADS7843_SPI_DEVICE_CFG,
			SPI_MODE_0, ADS7843_SPI_BAUDRATE, 0);
	spi_select_device(BOARD_ADS7843_SPI_BASE, &ADS7843_SPI_DEVICE_CFG);
	spi_enable(BOARD_ADS7843_SPI_BASE);

	for (uDummy = 0; uDummy < 100000; uDummy++) {
	}

	ads7843_send_cmd(CMD_ENABLE_PENIRQ);

	return 0;
}

/** @cond 0*/
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/** @endcond*/

/**
 * \}
 */
