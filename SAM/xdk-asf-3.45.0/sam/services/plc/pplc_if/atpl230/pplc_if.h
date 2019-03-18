/**
 * \file
 *
 * \brief Proxy PLC Controller interface layer implementation.
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

#ifndef CHIP_PPLC_IF_H_INCLUDED
#define CHIP_PPLC_IF_H_INCLUDED

#include "compiler.h"

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/* @endcond */

/**
 * \ingroup plc_group
 * \defgroup pplc_plc_group Proxy PLC Controller
 *
 * This module provides configuration and utils to control the PLC interface
 * with the ATPL230 PHY layer.
 *
 * @{
 */

/* \name Proxy PLC Controller commands (PPLC_CMD) */
/* @{ */
#define PPLC_CMD_READ       0x63 /* < Read operation */
#define PPLC_CMD_WRITE      0x2a /* < Write operation */
#define PPLC_CMD_WRITE_REP  0x1e /* < Repetitive write operation */
#define PPLC_CMD_AND        0x4c /* < AND operation */
#define PPLC_CMD_OR         0x71 /* < OR operation */
#define PPLC_CMD_XOR        0x6d /* < XOR operation */
/* @} */

/* \name Programmable Clock Settings (Hz) */
/* @{ */
#define PPLC_CLOCK          9000000 /* < PPLC clock setting */
/* @} */

/* \name PPLC interruption priority */

/* \note In case of use of FreeRTOS, GROUP_PRIO is greater value than
 * configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY */
/* @{ */
#define PPLC_PRIO          11 /* < PPLC interruption group priority */
/* @} */

/* \name PPLC communication parameters */
/* @{ */
#define PPLC_DLYBS         10 /* < Delay before SPCK */
#define PPLC_DLYBCT        0  /* < Delay between consecutive transfers */
/* @} */

/* \name Proxy PLC Controller interface */
/* @{ */
void pplc_if_init(void);
uint8_t pplc_if_read8(uint16_t us_addr);
uint8_t pplc_if_write8(uint16_t us_addr, uint8_t uc_dat);
uint16_t pplc_if_read16(uint16_t us_addr);
uint8_t pplc_if_write16(uint16_t us_addr, uint16_t us_dat);
uint32_t pplc_if_read32(uint16_t us_addr);
uint8_t pplc_if_write32(uint16_t us_addr, uint32_t ul_dat);
uint8_t pplc_if_read_buf(uint16_t us_addr, uint8_t *buf, uint16_t us_len);
uint8_t pplc_if_write_buf(uint16_t us_addr, uint8_t *buf, uint16_t us_len);
uint8_t pplc_if_write_rep(uint16_t us_addr, uint8_t uc_bytes_rep,
		uint8_t *ptr_buf, uint16_t us_len);
void pplc_if_and8(uint16_t us_addr, uint8_t uc_mask);
void pplc_if_or8(uint16_t us_addr, uint8_t uc_mask);
void pplc_if_xor8(uint16_t us_addr, uint8_t uc_mask);
void pplc_set_handler(void (*p_handler)(void));

/* @} */
/* @} */

/* @cond 0 */
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/* @endcond */

#endif /* CHIP_PPLC_IF_H_INCLUDED */
