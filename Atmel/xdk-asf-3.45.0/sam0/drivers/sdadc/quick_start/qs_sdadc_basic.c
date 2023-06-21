/**
 * \file
 *
 * \brief SAM SDADC Quick Start
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>

void configure_sdadc(void);

//! [module_inst]
struct sdadc_module sdadc_instance;
//! [module_inst]

//! [setup]
void configure_sdadc(void)
{
//! [setup_config]
	struct sdadc_config config_sdadc;
//! [setup_config]
//! [setup_config_defaults]
	sdadc_get_config_defaults(&config_sdadc);
//! [setup_config_defaults]

//! [setup_set_config]
	sdadc_init(&sdadc_instance, SDADC, &config_sdadc);
//! [setup_set_config]

//! [setup_enable]
	sdadc_enable(&sdadc_instance);
//! [setup_enable]
}
//! [setup]

int main(void)
{
	system_init();

//! [setup_init]
	configure_sdadc();
//! [setup_init]

//! [main]
//! [start_conv]
	sdadc_start_conversion(&sdadc_instance);
//! [start_conv]

//! [get_res]
	int32_t result;

	do {
		/* Wait for conversion to be done and read out result */
	} while (sdadc_read(&sdadc_instance, &result) == STATUS_BUSY);
//! [get_res]

//! [inf_loop]
	while (1) {
		/* Infinite loop */
	}
//! [inf_loop]
//! [main]
}
