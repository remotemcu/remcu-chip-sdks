/**
 * \file
 *
 * \brief SAM Generic Clock Driver Quick Start
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

void configure_gclock_generator(void);
void configure_gclock_channel(void);

//! [setup]
void configure_gclock_generator(void)
{
//! [setup_1]
	struct system_gclk_gen_config gclock_gen_conf;
//! [setup_1]
//! [setup_2]
	system_gclk_gen_get_config_defaults(&gclock_gen_conf);
//! [setup_2]

#if (SAML21) || (SAML22) || (SAMR30)
//! [setup_3]
	gclock_gen_conf.source_clock    = SYSTEM_CLOCK_SOURCE_OSC16M;
	gclock_gen_conf.division_factor = 128;
//! [setup_3]
#elif (SAMC21)
//! [setup_3]
	gclock_gen_conf.source_clock    = SYSTEM_CLOCK_SOURCE_OSC48M;
	gclock_gen_conf.division_factor = 128;
//! [setup_3]
#else
//! [setup_3]
	gclock_gen_conf.source_clock    = SYSTEM_CLOCK_SOURCE_OSC8M;
	gclock_gen_conf.division_factor = 128;
//! [setup_3]
#endif

//! [setup_4]
	system_gclk_gen_set_config(GCLK_GENERATOR_1, &gclock_gen_conf);
//! [setup_4]

//! [setup_5]
	system_gclk_gen_enable(GCLK_GENERATOR_1);
//! [setup_5]
}

void configure_gclock_channel(void)
{
//! [setup_6]
	struct system_gclk_chan_config gclk_chan_conf;
//! [setup_6]
//! [setup_7]
	system_gclk_chan_get_config_defaults(&gclk_chan_conf);
//! [setup_7]

//! [setup_8]
	gclk_chan_conf.source_generator = GCLK_GENERATOR_1;
//! [setup_8]
#if (SAMD10) || (SAMD11) || SAMR30
//! [setup_9]
	system_gclk_chan_set_config(TC1_GCLK_ID, &gclk_chan_conf);
//! [setup_9]

//! [setup_10]
	system_gclk_chan_enable(TC1_GCLK_ID);
//! [setup_10]
#else
//! [setup_9]
	system_gclk_chan_set_config(TC3_GCLK_ID, &gclk_chan_conf);
//! [setup_9]

//! [setup_10]
	system_gclk_chan_enable(TC3_GCLK_ID);
//! [setup_10]
#endif
}
//! [setup]

int main(void)
{
	//! [setup_init]
	configure_gclock_generator();
	configure_gclock_channel();
	//! [setup_init]

	//! [main]
	while (true) {
		/* Nothing to do */
	}
	//! [main]
}
