/**
 * \file
 *
 * \brief SAM PWM Driver Quick Start for SAMB11
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

//! [setup]
static void configure_pwm(void)
{
//! [setup_1]
	struct pwm_config config_pwm;
//! [setup_1]

//! [setup_2]
	pwm_get_config_defaults(&config_pwm);
//! [setup_2]

//! [setup_3]
	config_pwm.duty_cycle = 50;
	config_pwm.pin_number_pad = CONF_PWM_OUT_PIN;
	config_pwm.pinmux_sel_pad = CONF_PWM_OUT_MUX;
//! [setup_3]

//! [setup_4]
	pwm_init(CONF_PWM, &config_pwm);
//! [setup_4]

//! [setup_5]
	pwm_enable(CONF_PWM);
//! [setup_5]
}
//! [setup]

int main(void)
{
	system_clock_config(CLOCK_RESOURCE_XO_26_MHZ, CLOCK_FREQ_26_MHZ);

	//! [setup_init]
	configure_pwm();
	//! [setup_init]

	//! [main]
	while (true) {
		/* Infinite loop */
	}
	//! [main]
}
