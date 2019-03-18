/**
 * \file
 *
 * \brief SAM System Clock Driver Quick Start
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
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>

void configure_osc32k(void);
void configure_extosc32k(void);
void configure_dfll_open_loop(void);

//! [setup]
//! [config_osc32k]
void configure_osc32k(void)
{
	//! [config_osc32k_config]
	struct system_clock_source_xosc_config config_osc32k;
	//! [config_osc32k_config]
	//! [config_osc32k_get_defaults]
	system_clock_source_xosc32k_get_config_defaults(&config_osc32k);
	//! [config_osc32k_get_defaults]

	//! [config_osc32k_change_defaults]
	config_osc32k.startup_time = SYSTEM_XOSC_STARTUP_4096;
	//! [config_osc32k_change_defaults]

	//! [config_osc32k_set_config]
	system_clock_source_xosc_set_config(&config_osc32k);
	//! [config_osc32k_set_config]
}
//! [config_osc32k]

//! [setup]
//! [config_extosc32k]
void configure_extosc32k(void)
{
//! [config_extosc32k_config]
	struct system_clock_source_xosc32k_config config_ext32k;
//! [config_extosc32k_config]
//! [config_extosc32k_get_defaults]
	system_clock_source_xosc32k_get_config_defaults(&config_ext32k);
//! [config_extosc32k_get_defaults]

//! [config_extosc32k_change_defaults]
	config_ext32k.startup_time = SYSTEM_XOSC32K_STARTUP_4096;
//! [config_extosc32k_change_defaults]

//! [config_extosc32k_set_config]
	system_clock_source_xosc32k_set_config(&config_ext32k);
//! [config_extosc32k_set_config]
}
//! [config_extosc32k]

#if (!SAMC21)
//! [config_dfll]
void configure_dfll_open_loop(void)
{
//! [config_dfll_config]
	struct system_clock_source_dfll_config config_dfll;
//! [config_dfll_config]
//! [config_dfll_get_defaults]
	system_clock_source_dfll_get_config_defaults(&config_dfll);
//! [config_dfll_get_defaults]

//! [config_dfll_set_config]
	system_clock_source_dfll_set_config(&config_dfll);
//! [config_dfll_set_config]
}
//! [config_dfll]
#endif
//! [setup]

int main(void)
{
//! [main]

#if(SAMR30E)
{
  /* Configure the internal 32KHz oscillator */
  //! [config_osc32k_main]
  configure_osc32k();
  //! [config_osc32k_main]
  /* Enable the internal 32KHz oscillator */
  //! [enable_osc32k_main]
  enum status_code osc32k_status =
  system_clock_source_enable(SYSTEM_CLOCK_SOURCE_XOSC);

  if (osc32k_status != STATUS_OK) {
	  /* Error enabling the clock source */
  }
  //! [enable_osc32k_main]
}
	
#else
{
	/* Configure the external 32KHz oscillator */
//! [config_extosc32k_main]
	configure_extosc32k();
//! [config_extosc32k_main]
	/* Enable the external 32KHz oscillator */
//! [enable_extosc32k_main]
	enum status_code osc32k_status =
			system_clock_source_enable(SYSTEM_CLOCK_SOURCE_XOSC32K);

	if (osc32k_status != STATUS_OK) {
		/* Error enabling the clock source */
	}
//! [enable_extosc32k_main]
}
#endif
#if (!SAMC21)
	/* Configure the DFLL in open loop mode using default values */
//! [config_dfll_main]
	configure_dfll_open_loop();
//! [config_dfll_main]

	/* Enable the DFLL oscillator */
//! [enable_dfll_main]
	enum status_code dfll_status =
			system_clock_source_enable(SYSTEM_CLOCK_SOURCE_DFLL);

	if (dfll_status != STATUS_OK) {
		/* Error enabling the clock source */
	}
//! [enable_dfll_main]

	/* Configure flash wait states before switching to high frequency clock */
//! [set_sys_wait_states]
	system_flash_set_waitstates(2);
//! [set_sys_wait_states]

	/* Change system clock to DFLL */
//! [set_sys_clk_src]
	struct system_gclk_gen_config config_gclock_gen;
	system_gclk_gen_get_config_defaults(&config_gclock_gen);
	config_gclock_gen.source_clock    = SYSTEM_CLOCK_SOURCE_DFLL;
	config_gclock_gen.division_factor = 1;
	system_gclk_gen_set_config(GCLK_GENERATOR_0, &config_gclock_gen);
//! [set_sys_clk_src]
#endif
//! [main]

	while (true) {

	}
}
