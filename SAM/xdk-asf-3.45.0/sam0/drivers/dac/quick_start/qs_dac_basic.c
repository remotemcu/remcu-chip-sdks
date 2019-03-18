/**
 * \file
 *
 * \brief SAM DAC Quick Start
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

void configure_dac(void);
void configure_dac_channel(void);

//! [module_inst]
struct dac_module dac_instance;
//! [module_inst]

//! [setup]
void configure_dac(void)
{
//! [setup_config]
	struct dac_config config_dac;
//! [setup_config]
//! [setup_config_defaults]
	dac_get_config_defaults(&config_dac);
//! [setup_config_defaults]

//! [setup_set_config]
	dac_init(&dac_instance, DAC, &config_dac);
//! [setup_set_config]
}

void configure_dac_channel(void)
{
//! [setup_ch_config]
	struct dac_chan_config config_dac_chan;
//! [setup_ch_config]
//! [setup_ch_config_defaults]
	dac_chan_get_config_defaults(&config_dac_chan);
//! [setup_ch_config_defaults]

//! [setup_ch_set_config]
	dac_chan_set_config(&dac_instance, DAC_CHANNEL_0, &config_dac_chan);
//! [setup_ch_set_config]

//! [setup_ch_enable]
	dac_chan_enable(&dac_instance, DAC_CHANNEL_0);
//! [setup_ch_enable]
}
//! [setup]

int main(void)
{
	system_init();

//! [setup_init]
	configure_dac();
	configure_dac_channel();
//! [setup_init]

//! [setup_enable]
	dac_enable(&dac_instance);
//! [setup_enable]

//! [main]
//! [main_output_var]
	uint16_t i = 0;
//! [main_output_var]

//! [main_loop]
	while (1) {
//! [main_loop]
//! [main_write]
		dac_chan_write(&dac_instance, DAC_CHANNEL_0, i);
//! [main_write]

//! [main_inc_val]
		if (++i == 0x3FF) {
			i = 0;
		}
//! [main_inc_val]
	}
//! [main]
}
