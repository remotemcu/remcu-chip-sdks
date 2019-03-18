/**
 * \file
 *
 * \brief Connection of the AT25DFx SerialFlash to SPI interface driver.
 *
 * This file manages the connection of the AT25DFx SerialFlash driver to an
 * SPI service (could be spi master service or usart in spi mode). The SPI
 * service selection depends on  AT25DFX_USES_SPI_MASTER_SERVICE or
 * AT25DFX_USES_USART_SPI_SERVICE in conf_at25dfx.h.
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

#ifndef AT25DFX_HAL_SPI_H_INCLUDED
#define AT25DFX_HAL_SPI_H_INCLUDED

#include "conf_at25dfx.h"
#include "status_codes.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(AT25DFX_SPI_MODULE)
#warning AT25DFX_SPI_MODULE not defined, set default to 0
#define AT25DFX_SPI_MODULE 0
#endif
#if !defined(AT25DFX_CS)
#warning AT25DFX_CS not defined, set default to 0
#define AT25DFX_CS 0
#endif

void at25dfx_spi_init(void);
void at25dfx_spi_select_device(uint8_t mem_id);
void at25dfx_spi_deselect_device(uint8_t mem_id);
status_code_t at25dfx_spi_write_byte(uint8_t data);
status_code_t at25dfx_spi_read_byte(uint8_t *data);
status_code_t at25dfx_spi_read_packet(void const *data, size_t len);
status_code_t at25dfx_spi_write_packet(void const *data, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* AT25DFX_HAL_SPI_H_INCLUDED */
