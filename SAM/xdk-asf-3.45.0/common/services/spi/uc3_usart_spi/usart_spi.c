/**
 * \file
 *
 * \brief UC3 USART in SPI mode driver functions.
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

#include "usart_spi.h"
#include "sysclk.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/*! \brief Enable the USART system clock in SPI master mode.
 *
 * \param p_usart Pointer to Base address of the USART instance.
 *
 */
void usart_spi_init(volatile avr32_usart_t *p_usart)
{
#if (defined(AVR32_USART0_ADDRESS))
	if ((uint32_t)p_usart == AVR32_USART0_ADDRESS)
	{
		sysclk_enable_pba_module(SYSCLK_USART0);
	}
#endif
#if (defined(AVR32_USART1_ADDRESS))
	if ((uint32_t)p_usart == AVR32_USART1_ADDRESS)
	{
#if UC3C
		sysclk_enable_pbc_module(SYSCLK_USART1);
#else
		sysclk_enable_pba_module(SYSCLK_USART1);
#endif
	}
#endif
#if (defined(AVR32_USART2_ADDRESS))
	if ((uint32_t)p_usart == AVR32_USART2_ADDRESS)
	{
		sysclk_enable_pba_module(SYSCLK_USART2);
	}
#endif
#if (defined(AVR32_USART3_ADDRESS))
	if ((uint32_t)p_usart == AVR32_USART3_ADDRESS)
	{
		sysclk_enable_pba_module(SYSCLK_USART3);
	}
#endif
}

/**
 * \brief Set up a USART in SPI master mode device.
 *
 * The returned device descriptor structure must be passed to the driver
 * whenever that device should be used as current slave device.
 *
 * \param p_usart   Base address of the USART instance.
 * \param device    Pointer to usart device struct that should be initialized.
 * \param flags     USART configuration flags. Common flags for all
 *                  implementations are the usart modes, which should be SPI_MODE_0,
 *                  SPI_MODE_1, SPI_MODE_2, SPI_MODE_3.
 * \param baud_rate Baud rate for communication with slave device in Hz.
 * \param sel_id    Board specific select id.
 */
void usart_spi_setup_device(volatile avr32_usart_t *p_usart, 
	struct usart_spi_device *device, spi_flags_t flags, 
	unsigned long baud_rate, board_spi_select_id_t sel_id)
{
	usart_spi_options_t opt;

	/* avoid Cppcheck Warning */
	UNUSED(device);
	UNUSED(sel_id);
	
	/* Basic usart SPI configuration. */
	opt.baudrate = baud_rate;
	opt.charlength = 8;
	opt.spimode = flags;
	opt.channelmode = USART_NORMAL_CHMODE;
	
	/* Initialize the USART module as SPI master. */
	usart_init_spi_master(p_usart, &opt, sysclk_get_cpu_hz());

}

/*! \brief Write one byte to an SPI device using USART in SPI mode.
 *
 * \param p_usart Base address of the USART instance.
 * \param data    The data to be sent out. 
 *
 */
void usart_spi_write_single(volatile avr32_usart_t *p_usart, uint8_t data)
{
	usart_putchar(p_usart, data);
}

/**
 * \brief Send a sequence of bytes to an SPI device using USART in SPI mode.
 *
 * Received bytes on the USART in SPI mode are discarded.
 *
 * \param p_usart Base address of the USART instance.
 * \param data    Data buffer to write.
 * \param len     Length of data.
 *
 * \return 0 if the USART in SPI master mode sends packet successfully.
 *
 * \pre USART device must be selected with usart_spi_select_device() first.
 */
uint32_t usart_spi_write_packet(volatile avr32_usart_t *p_usart, 
	const uint8_t *data, size_t len)
{
	uint32_t dummy_data;
	size_t i=0;
	while(len) {
		usart_putchar(p_usart, *(data+i));
		dummy_data = usart_getchar(p_usart);
		len--;
		i++;
	}
	return 0;
}

/*! \brief Receive one byte from an SPI device using USART in SPI mode.
 *
 * \param p_usart Base address of the USART instance.
 * \param data    Pointer to the data byte where to store the received data.
 *
 * \pre USART device must be selected with usart_spi_select_device() first.
 */
void usart_spi_read_single(volatile avr32_usart_t *p_usart, uint8_t *data)
{
	/* Dummy write one data to slave in order to read data. */
	usart_putchar(p_usart, CONFIG_USART_SPI_DUMMY);
	*data = usart_getchar(p_usart);
}

/**
 * \brief Receive a sequence of bytes from a USART in SPI mode device.
 *
 * All bytes sent out on usart bus are sent as value 0.
 *
 * \param p_usart Base address of the usart instance.
 * \param data    Data buffer to put read data.
 * \param len     Length of data.
 *
 * \return 0 if the USART in SPI master mode reads packet successfully.
 *
 * \pre USART device must be selected with usart_spi_select_device() first.
 */
uint32_t usart_spi_read_packet(volatile avr32_usart_t *p_usart, uint8_t *data, 
	size_t len)
{
	uint32_t val;
	uint32_t i = 0;

	while(len) {
		/* Dummy write one data to slave in order to read data. */
		usart_putchar(p_usart, CONFIG_USART_SPI_DUMMY);
		val = usart_getchar(p_usart);

		data[i] = (uint8_t)(val & 0xFF);
		i++;
		len--;
	}

	return 0;
}

/**
 * \brief Select the given device on the SPI bus.
 *
 * \param p_usart  Base address of the USART instance.
 * \param device   SPI device.
 *
 */
void usart_spi_select_device(volatile avr32_usart_t *p_usart, 
	struct usart_spi_device *device)
{
	/* avoid Cppcheck Warning */
	UNUSED(device);

	usart_spi_selectChip(p_usart);
}

/**
 * \brief De-select the given device on the SPI bus.
 *
 * \param p_usart Base address of the USART instance.
 * \param device  SPI device.
 */
void usart_spi_deselect_device(volatile avr32_usart_t *p_usart, 
	struct usart_spi_device *device)
{
	/* avoid Cppcheck Warning */
	UNUSED(device);

	usart_spi_unselectChip(p_usart);
}

/*! \brief Check whether there are data in Transmit Holding Register or
 *         Transmit Shift Register in SPI master mode.
 *
 * \param p_usart Base address of the USART instance.
 *
 * \retval 1      The two registers are empty.
 * \retval 0      One of the two registers contains data.
 */
uint32_t usart_spi_is_tx_empty(volatile avr32_usart_t *p_usart)
{
	return usart_tx_empty(p_usart);
}

/*! \brief Check whether the USART in SPI master mode contains a received character.
 *
 * \param p_usart Base address of the USART instance.
 *
 * \retval 1      Some data have been received.
 * \retval 0      No data has been received.
 */
uint32_t usart_spi_is_rx_ready(volatile avr32_usart_t *p_usart)
{
	return (p_usart->csr & AVR32_USART_CSR_RXRDY_MASK) != 0;
}

/*! \brief Check if the USART Transmit Holding Register is empty or not in SPI mode.
 *
 * \param p_usart Base address of the USART instance.
 *
 * \retval 1      There is no data in the Transmit Holding Register.
 * \retval 0      There are data in the Transmit Holding Register.
 */
uint32_t usart_spi_is_tx_ready(volatile avr32_usart_t *p_usart)
{
	return usart_tx_ready(p_usart);
}

/*! \brief Check if both receive buffers are full.
 *
 * \param p_usart Base address of the USART instance.
 *
 * \retval 1      Receive buffers are full.
 * \retval 0      Receive buffers are not full.
 */
uint32_t usart_spi_is_rx_full(volatile avr32_usart_t *p_usart)
{
	return (p_usart->csr & AVR32_USART_CSR_RXBUFF_MASK) > 0;
}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
