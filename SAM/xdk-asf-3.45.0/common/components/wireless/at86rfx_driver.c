/**
 * \file
 *
 * \brief AT86RFx driver.
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


#include "compiler.h"
#include "board.h"
#include "conf_at86rfx.h"
#include "spi_master.h"
#include "gpio.h"
#include "at86rfx_driver.h"
#include "conf_spi_master.h"

/*
 * Default value of current channel in TAL
 */
#if EXT_BOARD == RZ600_AT86RF212
#  define CURRENT_CHANNEL_DEFAULT         (1)
#else
#  define CURRENT_CHANNEL_DEFAULT         (20)
#endif


struct spi_device SPI_AT86RFX_DEVICE = {
	//! Board specific select id
	.id = AT86RFX_SPI_NPCS
};

/**
 * Static receive buffer that can be used to upload a frame from the trx.
 */
uint8_t at86rfx_rx_buffer[LARGE_BUFFER_SIZE];

/*
 * Flag indicating if an unprocessed frame has been received.
 */
bool at86rfx_frame_rx = false;


/**
 * \brief ISR for transceiver's main interrupt
 */
ISR(ext_int_isr, EXT_INT_ISR_GROUP, EXT_INT_ISR_PRIORITY)
{
	/*Clearing the AT86RFx interrupt */
	CLEAR_TRX_IRQ();
	/*Calling the interrupt routines */
	trx_irq_handler_cb();
}

uint8_t pal_trx_reg_read(uint8_t addr)
{
	uint8_t register_value = 0;

	/*Saving the current interrupt status & disabling the global interrupt */
	ENTER_CRITICAL_REGION();

	/* Prepare the command byte */
	addr |= READ_ACCESS_COMMAND;

	/* Start SPI transaction by pulling SEL low */
	spi_select_device(AT86RFX_SPI, &SPI_AT86RFX_DEVICE);

	/* Send the Read command byte */
	spi_write_packet(AT86RFX_SPI, &addr, 1);

	/* Do dummy read for initiating SPI read */
	spi_read_packet(AT86RFX_SPI, &register_value, 1);

	/* Stop the SPI transaction by setting SEL high */
	spi_deselect_device(AT86RFX_SPI, &SPI_AT86RFX_DEVICE);

	/*Restoring the interrupt status which was stored & enabling the global interrupt */
	LEAVE_CRITICAL_REGION();

	return register_value;
}

void pal_trx_reg_write(uint8_t addr, uint8_t data)
{
	/*Saving the current interrupt status & disabling the global interrupt */
	ENTER_CRITICAL_REGION();

	/* Prepare the command byte */
	addr |= WRITE_ACCESS_COMMAND;

	/* Start SPI transaction by pulling SEL low */
	spi_select_device(AT86RFX_SPI, &SPI_AT86RFX_DEVICE);

	/* Send the Read command byte */
	spi_write_packet(AT86RFX_SPI, &addr, 1);

	/* Write the byte in the transceiver data register */
	spi_write_packet(AT86RFX_SPI, &data, 1);

	/* Stop the SPI transaction by setting SEL high */
	spi_deselect_device(AT86RFX_SPI, &SPI_AT86RFX_DEVICE);

	/*Restoring the interrupt status which was stored & enabling the global interrupt */
	LEAVE_CRITICAL_REGION();
}

void pal_trx_frame_read(uint8_t * data, uint8_t length)
{
	uint8_t temp;
	/*Saving the current interrupt status & disabling the global interrupt */
	ENTER_CRITICAL_REGION();

	/* Start SPI transaction by pulling SEL low */
	spi_select_device(AT86RFX_SPI, &SPI_AT86RFX_DEVICE);

	temp = TRX_CMD_FR;

	/* Send the command byte */
	spi_write_packet(AT86RFX_SPI, &temp, 1);

	spi_read_packet(AT86RFX_SPI, data, length);

	/* Stop the SPI transaction by setting SEL high */
	spi_deselect_device(AT86RFX_SPI, &SPI_AT86RFX_DEVICE);

	/*Restoring the interrupt status which was stored & enabling the global interrupt */
	LEAVE_CRITICAL_REGION();
}

void pal_trx_frame_write(uint8_t * data, uint8_t length)
{
	uint8_t temp;
	/*Saving the current interrupt status & disabling the global interrupt */
	ENTER_CRITICAL_REGION();

	/* Start SPI transaction by pulling SEL low */
	spi_select_device(AT86RFX_SPI, &SPI_AT86RFX_DEVICE);

	temp = TRX_CMD_FW;

	/* Send the command byte */
	spi_write_packet(AT86RFX_SPI, &temp, 1);

	spi_write_packet(AT86RFX_SPI, data, length);

	/* Stop the SPI transaction by setting SEL high */
	spi_deselect_device(AT86RFX_SPI, &SPI_AT86RFX_DEVICE);

	/*Restoring the interrupt status which was stored & enabling the global interrupt */
	LEAVE_CRITICAL_REGION();
}

uint8_t pal_trx_bit_read(uint8_t addr, uint8_t mask, uint8_t pos)
{
	uint8_t ret;
	ret = pal_trx_reg_read(addr);
	ret &= mask;
	ret >>= pos;
	return ret;
}

void pal_trx_bit_write(uint8_t reg_addr, uint8_t mask, uint8_t pos,
		uint8_t new_value)
{
	uint8_t current_reg_value;
	current_reg_value = pal_trx_reg_read(reg_addr);
	current_reg_value &= ~mask;
	new_value <<= pos;
	new_value &= mask;
	new_value |= current_reg_value;
	pal_trx_reg_write(reg_addr, new_value);
}

void at86rfx_task(void)
{
	/*
	 * If the transceiver has received a frame and it has been placed
	 * into the rf buffer, frame needs to be processed further in application.
	 */
	if (at86rfx_frame_rx) {
		AT86RFX_RX_NOTIFY(at86rfx_rx_buffer);
		at86rfx_frame_rx = false;
	}

	handle_tal_state();
}

at86rfx_retval_t at86rfx_init(void)
{
	pal_trx_init();

	if (tal_init() != TRX_SUCCESS) {
		return AT86RFX_FAILURE;
	}

	pal_trx_bit_write(SR_CHANNEL, CURRENT_CHANNEL_DEFAULT);

	/* Enable transceiver interrupts. */
	ENABLE_TRX_IRQ();

	pal_trx_reg_write(RG_TRX_STATE, CMD_RX_ON);

	return AT86RFX_SUCCESS;
}

void pal_trx_init(void)
{
	/* Initialize SPI in master mode to access the transceiver */
	spi_master_init(AT86RFX_SPI);
	spi_master_setup_device(AT86RFX_SPI, &SPI_AT86RFX_DEVICE, SPI_MODE_0,
			AT86RFX_SPI_BAUDRATE, 0);
	spi_enable(AT86RFX_SPI);
	spi_deselect_device(AT86RFX_SPI, &SPI_AT86RFX_DEVICE);

	/* Initialize EXT_INT as interrupt for transceiver */
	gpio_enable_pin_interrupt(EXT_INT, GPIO_RISING_EDGE);
	gpio_clear_pin_interrupt_flag(EXT_INT);
	irq_register_handler(ext_int_isr, AVR32_GPIO_IRQ_2,
			EXT_INT_ISR_PRIORITY);

	/* Initialize TRX_RST and SLP_TR as GPIO. */
	gpio_configure_pin(TRX_RST, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH);
	gpio_configure_pin(SLP_TR, GPIO_DIR_OUTPUT | GPIO_INIT_HIGH);
}

void at86rfx_tx_frame(uint8_t * frame_tx)
{
	DISABLE_TRX_IRQ();

	tx_frame_config();

	/*
	 * Send the frame to the transceiver.
	 * Note: The PhyHeader is the first byte of the frame to
	 * be sent to the transceiver and this contains the frame
	 * length.
	 * The actual length of the frame to be downloaded
	 * (parameter two of pal_trx_frame_write)
	 * is
	 * 1 octet frame length octet
	 * + n octets frame (i.e. value of frame_tx[0])
	 * - 2 octets FCS. Shall be added automatically
	 */
	pal_trx_frame_write(frame_tx, frame_tx[0] - LENGTH_FIELD_LEN);

	ENABLE_TRX_IRQ();
}
