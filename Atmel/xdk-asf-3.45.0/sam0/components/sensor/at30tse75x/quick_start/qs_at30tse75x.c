/**
 * \file
 *
 * \brief AT30TSE75X Temperature Sensor Driver Quick Start
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

#include <asf.h>

//! [temp_res]
double temp_res;
//! [temp_res]

int main(void)
{
//! [init]
	/* Init system. */
//! [system_init]
	system_init();
//! [system_init]
	/* Configure device and enable. */
//! [temp_init]
	at30tse_init();
//! [temp_init]
//! [init]

//! [impl]
    /* Read thigh and tlow */
//! [read_thigh]
	volatile uint16_t thigh = 0;
	thigh = at30tse_read_register(AT30TSE_THIGH_REG,
			AT30TSE_NON_VOLATILE_REG, AT30TSE_THIGH_REG_SIZE);
//! [read_thigh]
//! [read_tlow]
	volatile uint16_t tlow = 0;
	tlow = at30tse_read_register(AT30TSE_TLOW_REG,
			AT30TSE_NON_VOLATILE_REG, AT30TSE_TLOW_REG_SIZE);
//! [read_tlow]

	/* Set 12-bit resolution mode. */
//! [write_conf]
	at30tse_write_config_register(
			AT30TSE_CONFIG_RES(AT30TSE_CONFIG_RES_12_bit));
//! [write_conf]

//! [read_temp]
	while (1) {
		temp_res = at30tse_read_temperature();
	}
//! [read_temp]
//! [impl]
	UNUSED(tlow);
	UNUSED(thigh);
}
//! [qs]
