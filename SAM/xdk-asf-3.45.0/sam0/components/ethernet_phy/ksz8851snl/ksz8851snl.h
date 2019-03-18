/**
 * \file
 *
 * \brief KS8851SNL driver for SAM0.
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
#ifndef KSZ8851SNL_H_INCLUDED
#define KSZ8851SNL_H_INCLUDED

#include <compiler.h>
#include <port.h>
#include <spi.h>
#include <delay.h>

// KSZ8851SNL configuration file
#include "conf_eth.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup ksz8851snl_phy_controller_group KSZ8851SNL ethernet PHY driver
 *
 * This is a low level driver for the KSZ8851SNL ethernet PHY through 4-wire SPI.
 * It provides functions for configuring and communicating with the ethernet PHY.
 *
 * Before writing data to the ethernet PHY call \ref ksz8851snl_init() which will set up
 * the physical interface and the PHY. A file named \ref conf_eth.h is needed
 * to define which interface to use.
 * In addition one also need to define the pins
 * \ref KSZ8851SNL_RSTN_PIN, \ref KSZ8851SNL_CS_PIN and \ref KSZ8851SNL_INTN_EIC_PIN and
 * the PHY \ref KSZ8851SNL_CLOCK_SPEED.
 *
 * \warning This driver is not reentrant and can not be used in interrupt\
 * service routines without extra care.
 *
 *
 * An example \ref conf_eth.h file could look like
 * \code
 * // Interface configuration for SAM D20 Xplained Pro
 * #define KSZ8851SNL_SPI                                EXT1_SPI_MODULE
 * #define KSZ8851SNL_SPI_IRQn                           SERCOM0_IRQn
 *
 * // Pins configuration.
 * #define KSZ8851SNL_RSTN_PIN                           EXT1_PIN_6
 * #define KSZ8851SNL_CS_PIN                             EXT1_PIN_15
 * #define KSZ8851SNL_INTN_EIC_CHANNEL                   EXT1_IRQ_INPUT
 * #define KSZ8851SNL_INTN_EIC_PIN                       EXT1_IRQ_PIN
 * #define KSZ8851SNL_INTN_EIC_PIN_MUX                   EXT1_IRQ_PINMUX
 *
 * // SPI settings.
 * #define KSZ8851SNL_SPI_PINMUX_SETTING                 EXT1_SPI_SERCOM_MUX_SETTING
 * #define KSZ8851SNL_SPI_PINMUX_PAD0                    EXT1_SPI_SERCOM_PINMUX_PAD0
 * #define KSZ8851SNL_SPI_PINMUX_PAD1                    PINMUX_UNUSED
 * #define KSZ8851SNL_SPI_PINMUX_PAD2                    EXT1_SPI_SERCOM_PINMUX_PAD2
 * #define KSZ8851SNL_SPI_PINMUX_PAD3                    EXT1_SPI_SERCOM_PINMUX_PAD3
 * #define KSZ8851SNL_CLOCK_SPEED                        10000000UL
 * \endcode
 *
 * \section dependencies Dependencies
 * This driver depends on the following modules:
 * - \ref asfdoc_samd20_port_group for IO port control.
 * - \ref asfdoc_samd20_extint_group for IO port interrupt control.
 * - \ref asfdoc_samd20_system_group for getting system clock speeds for init functions.
 * - \ref asfdoc_samd20_sercom_spi_group for communication with the OLED controller
 * @{
 */

/** @{@} */

extern struct spi_module ksz8851snl_master;
extern struct spi_slave_inst ksz8851snl_slave;

//! \name PHY register read/write functions
//@{
uint16_t ksz8851_reg_read(uint16_t reg);
void ksz8851_reg_write(uint16_t reg, uint16_t wrdata);
void ksz8851_reg_setbits(uint16_t reg, uint16_t bits_to_set);
void ksz8851_reg_clrbits(uint16_t reg, uint16_t bits_to_clr);
//@}

//! \name PHY FIFO read/write functions
//@{
void ksz8851_fifo_read(uint8_t *buf, uint32_t len);
void ksz8851_fifo_write_begin(uint32_t tot_len);
void ksz8851_fifo_write(uint8_t *buf, uint32_t len);
void ksz8851_fifo_write_end(uint32_t pad);
//@}

//! \name Initialization and configuration
//@{
uint32_t ksz8851snl_init(void);
void configure_intn(void (*p_handler) (void));
//@}

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* KSZ8851SNL_H_INCLUDED */
