/**
 * \file
 *
 * \brief SECURITY_XPLAINED extension board adaptation.
 *
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


#include "security_xplained.h"
#include "sha204_physical.h"
#include "conf_atsha204.h"


//! TWI address used at SHA204 library startup
#define SHA204_I2C_DEFAULT_ADDRESS  (0xCA)


/** \brief This function initializes peripherals needed to communicate with
 *         the I2C security devices (ATSHA204 and ATAES132).
 */
void security_board_init(void)
{
	sha204p_init();
}


/** \brief This function returns the I2C address of a chosen SHA204 device.
 *  \param[in] index the selected device on the Security Xplained board
 *  \return I2C address of chosen device
 */
uint8_t sha204_i2c_address(uint8_t index)
{
	static uint8_t i2c_addresses[SHA204_DEVICE_COUNT] = {SHA204_I2C_DEFAULT_ADDRESS, 0xCC, 0xCE, 0xF8};
	return i2c_addresses[index % SHA204_DEVICE_COUNT];
}

