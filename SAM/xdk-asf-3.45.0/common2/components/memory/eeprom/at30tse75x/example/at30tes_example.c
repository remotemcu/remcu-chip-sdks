/**
 * \file
 *
 * \brief AT30TS(E)75x EEPROM and Temperature Sensor Example.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

/**
 * \page asfdoc_samb_at30tse75x_qs AT30TS(E)75x EEPROM and Temperature Sensor Example
 *
 * \section Purpose
 *
 * The application demonstrates how to access AT30TS(E)75x temperature sensor.
 *
 * \section Requirements
 *
 * This package can be used with:
 * - SAMB11 Xplained Pro board.
 *
 * \section Description
 * There are 2 stages in the example.
 * - In 1st stage, some patterns are written to the specified memory address of
 * the EEPROM in AT30TSE75x. Then the memory is read and checked (note this
 * stage is only for the device which has EEPROM).
 * - In 2nd stage, the temperature sampled by AT30TS(E)75x is read every second.
 *
 * \section compinfo Compilation Info
 * This software was written for the GNU GCC and IAR EWARM.
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com/">Microchip</A>.\n
 * Support and FAQ: https://www.microchip.com/support/
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <string.h>
#include "at30tse75x.h"

#define NB_PAGE 16
#define NB_BYTE 16

static uint8_t rx_buffer[NB_BYTE], tx_buffer[NB_BYTE];

static void delay(uint32_t count)
{
	for (uint32_t i = 0; i < count; i++) {
		for (uint32_t j = 0; j < 1000; j++)
			asm volatile ("nop");
	}
}

int main(void)
{
	volatile double temper_value;
	volatile bool data_check_status1 = true,
	              data_check_status2 = true;
	uint32_t i;

	system_clock_config(CLOCK_RESOURCE_XO_26_MHZ, CLOCK_FREQ_26_MHZ);

	/* Initialize AT30TS(E)75x */
	at30tse_init();

	/* First round data check */
	for (i = 0; i < NB_BYTE; i++) {
		tx_buffer[i] = i;
	}

	/* Write pages in EEPROM */
	for (i = 0; i < NB_PAGE; i++) {
		at30tse_eeprom_write(tx_buffer, NB_BYTE, 0, i);
		delay(200);
	}
	
	/* Read each page in EEPROM and compare them */
	for (i = 0; i < NB_PAGE; i++) {
		memset(rx_buffer, 0, NB_BYTE);
		at30tse_eeprom_read(rx_buffer, NB_BYTE, 0, i);
		if (memcmp(tx_buffer, rx_buffer, NB_BYTE)) {
			data_check_status1 = false;
			break;
		}
	}

	/* Second round data check */
	for (i = 0; i < NB_BYTE; i++) {
		tx_buffer[i] = NB_BYTE - i;
	}

	/* Write pages in EEPROM */
	for (i = 0; i < NB_PAGE; i++) {
		at30tse_eeprom_write(tx_buffer, NB_BYTE, 0, i);
		delay(200);
	}
	
	/* Read each page in EEPROM and compare them */
	for (i = 0; i < NB_PAGE; i++) {
		memset(rx_buffer, 0, NB_BYTE);
		at30tse_eeprom_read(rx_buffer, NB_BYTE, 0, i);
		if (memcmp(tx_buffer, rx_buffer, NB_BYTE)) {
			data_check_status2 = false;
			break;
		}
	}

	/* Read thigh and tlow */
	volatile uint16_t thigh = 0;
	thigh = at30tse_read_register(AT30TSE_THIGH_REG,
			AT30TSE_NON_VOLATILE_REG, AT30TSE_THIGH_REG_SIZE);

	volatile uint16_t tlow = 0;
	tlow = at30tse_read_register(AT30TSE_TLOW_REG,
			AT30TSE_NON_VOLATILE_REG, AT30TSE_TLOW_REG_SIZE);
			
	/* Set 12-bit resolution mode. */
	at30tse_write_config_register(
			AT30TSE_CONFIG_RES(AT30TSE_CONFIG_RES_12_bit));

	while (1) {
		/* Read current temperature. */
		temper_value = at30tse_read_temperature();
	}

	UNUSED(data_check_status1);
	UNUSED(data_check_status2);
	UNUSED(temper_value);
	UNUSED(tlow);
	UNUSED(thigh);
}
