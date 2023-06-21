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

#ifndef _USART_SPI_H_
#define _USART_SPI_H_

#include "compiler.h"
#include "usart.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/*! \name USART in SPI mode Management Configuration.
 */
//! @{
#include "conf_usart_spi.h"

//! Default Configuration of SPI Master Dummy Field
#ifndef CONFIG_USART_SPI_DUMMY
	#define CONFIG_USART_SPI_DUMMY              0xFF
#endif
//! @}

/** Clock phase. */
#define SPI_CPHA	(1 << 0)

/** Clock polarity. */
#define SPI_CPOL	(1 << 1)

/** SPI mode definition. */
#define SPI_MODE_0	(SPI_CPHA)
#define SPI_MODE_1	0
#define SPI_MODE_2	(SPI_CPOL | SPI_CPHA)
#define SPI_MODE_3	(SPI_CPOL)

#ifndef SPI_TYPE_DEFS
#define SPI_TYPE_DEFS
//! SPI Flags Definition
typedef uint8_t spi_flags_t;

//! Board SPI Select Id Definition
typedef uint32_t board_spi_select_id_t;
#endif

typedef uint8_t port_pin_t; 

//! \brief Polled SPI device definition.
struct usart_spi_device {
	/* Board specific select id. */
	port_pin_t	id;
};

void usart_spi_init(volatile avr32_usart_t *p_usart);
void usart_spi_setup_device(volatile avr32_usart_t *p_usart, struct usart_spi_device *device,
     spi_flags_t flags, unsigned long baud_rate, board_spi_select_id_t sel_id);
void usart_spi_write_single(volatile avr32_usart_t *p_usart, uint8_t data);
uint32_t usart_spi_write_packet(volatile avr32_usart_t *p_usart, const uint8_t *data, size_t len);
void usart_spi_read_single(volatile avr32_usart_t *p_usart, uint8_t *data);
uint32_t usart_spi_read_packet(volatile avr32_usart_t *p_usart, uint8_t *data, size_t len);
void usart_spi_select_device(volatile avr32_usart_t *p_usart, struct usart_spi_device *device);
void usart_spi_deselect_device(volatile avr32_usart_t *p_usart, struct usart_spi_device *device);
uint32_t usart_spi_is_tx_empty(volatile avr32_usart_t *p_usart);
uint32_t usart_spi_is_rx_ready(volatile avr32_usart_t *p_usart);
uint32_t usart_spi_is_tx_ready(volatile avr32_usart_t *p_usart);
uint32_t usart_spi_is_rx_full(volatile avr32_usart_t *p_usart);

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

#endif  /* _USART_SPI_H_ */
