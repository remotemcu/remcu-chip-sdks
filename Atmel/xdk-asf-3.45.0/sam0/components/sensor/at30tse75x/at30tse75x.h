/**
 * \file
 *
 * \brief AT30TSE75X driver
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

#ifndef AT30TSE75X_H_INCLUDED
#define AT30TSE75X_H_INCLUDED

#include <compiler.h>
#include <i2c_common.h>
#include <i2c_master.h>

/* Temperature sensor configuration file */
#include "conf_at30tse75x.h"

/**
 * \defgroup asfdoc_sam0_at30tse75x_group AT30TSE75X Temperature Sensor
 * This driver provides API for AT30TSE75X temperature sensor through
 * I2C interface.
 *
 * See \ref asfdoc_sam0_at30tse75x_qs.
 *
 *
 * \section asfdoc_sam0_at30tse75x_dependencies Dependencies
 * This driver depends on the following module:
 * - \ref asfdoc_sam0_i2c_group "SAM D20/D21 I2C master"
 *
 * \section asfdoc_sam0_at30tse75x_api_overview API Overview
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef AT30TSE_TEMPERATURE_TWI_ADDR
#define AT30TSE_TEMPERATURE_TWI_ADDR	0x4F //0b1001111
#endif
#define AT30TSE758_EEPROM_TWI_ADDR		0x54 //0b1010100
#define AT30TSE754_EEPROM_TWI_ADDR		0x56 //0b1010110
#define AT30TSE752_EEPROM_TWI_ADDR		0x57 //0b1010111

#define AT30TSE_TEMPERATURE_REG			0x00
#define AT30TSE_TEMPERATURE_REG_SIZE	2
#define AT30TSE_NON_VOLATILE_REG		0x00
#define AT30TSE_VOLATILE_REG			0x10

#define AT30TSE_CONFIG_REG				0x01
#define AT30TSE_CONFIG_REG_SIZE			2
#define AT30TSE_TLOW_REG				0x02
#define AT30TSE_TLOW_REG_SIZE			2
#define AT30TSE_THIGH_REG				0x03
#define AT30TSE_THIGH_REG_SIZE			2

#define AT30TSE_CONFIG_RES_Pos 			13
#define AT30TSE_CONFIG_RES_Msk 			(0x03 << AT30TSE_CONFIG_RES_Pos)
#define AT30TSE_CONFIG_RES(value) 		((AT30TSE_CONFIG_RES_Msk & ((value) << AT30TSE_CONFIG_RES_Pos)))

#define AT30TSE_CONFIG_RES_9_bit		0
#define AT30TSE_CONFIG_RES_10_bit		1
#define AT30TSE_CONFIG_RES_11_bit		2
#define AT30TSE_CONFIG_RES_12_bit		3

#define AT30TSE_CONFIG_FTQ_Pos 			13
#define AT30TSE_CONFIG_FTQ_Msk 			(0x03 << AT30TSE_CONFIG_FTQ_Pos)
#define AT30TSE_CONFIG_FTQ(value) 		((AT30TSE_CONFIG_FTQ_Msk & ((value) << AT30TSE_CONFIG_FTQ_Pos)))

#define AT30TSE_CONFIG_FTQ_1_fault		0
#define AT30TSE_CONFIG_RES_2_fault		1
#define AT30TSE_CONFIG_RES_4_fault		2
#define AT30TSE_CONFIG_RES_6_fault		3

// R/W bits
#define AT30TSE_CONFIG_OS				(1 << 15)
#define AT30TSE_CONFIG_R1				(1 << 14)
#define AT30TSE_CONFIG_R0				(1 << 13)
#define AT30TSE_CONFIG_FT1				(1 << 12)
#define AT30TSE_CONFIG_FT0				(1 << 11)
#define AT30TSE_CONFIG_POL				(1 << 10)
#define AT30TSE_CONFIG_CMP_INT			(1 << 9)
#define AT30TSE_CONFIG_SD				(1 << 8)

/* Read only bits */
#define AT30TSE_CONFIG_NVRBSY			(1 << 0)

void at30tse_init(void);
void at30tse_eeprom_write(uint8_t *data, uint8_t length, uint8_t word_addr, uint8_t page);
void at30tse_eeprom_read(uint8_t *data, uint8_t length, uint8_t word_addr, uint8_t page);
double at30tse_read_temperature(void);
void at30tse_write_config_register(uint16_t value);
uint16_t at30tse_read_register(uint8_t reg, uint8_t reg_type, uint8_t reg_size);
void at30tse_write_register(uint8_t reg, uint8_t reg_type, uint8_t reg_size, uint16_t reg_value);
void at30tse_set_register_pointer(uint8_t reg, uint8_t reg_type);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* AT30TSE75X_H_ */
