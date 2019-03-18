/**
 * \file
 *
 * \brief SAM PAC Quick Start
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

void config_port_pins(void);

//! [pin_setup]
void config_port_pins(void)
{
	struct port_config pin_conf;

	port_get_config_defaults(&pin_conf);

	pin_conf.direction  = PORT_PIN_DIR_INPUT;
	pin_conf.input_pull = PORT_PIN_PULL_UP;
	port_pin_set_config(BUTTON_0_PIN, &pin_conf);

	pin_conf.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(LED_0_PIN, &pin_conf);
}
//! [pin_setup]

int main (void)
{
//! [main]
	system_init();

//! [init]
	config_port_pins();
//! [init]

//! [init_lock]
	system_peripheral_lock(SYSTEM_PERIPHERAL_ID(PORT),
			~SYSTEM_PERIPHERAL_ID(PORT));
//! [init_lock]

//! [enable_interrupts]
#if (SAML21) || (SAML22) || (SAMC21) || defined(__DOXYGEN__)
	system_pac_enable_interrupt();
#endif
	system_interrupt_enable_global();
//! [enable_interrupts]

//! [button_press]
	while (port_pin_get_input_level(BUTTON_0_PIN)) {
		/* Wait for button press */
	}
//! [button_press]

//! [disable_interrupts]
	system_interrupt_enter_critical_section();
//! [disable_interrupts]

//! [unlock_perph]
	system_peripheral_unlock(SYSTEM_PERIPHERAL_ID(PORT),
			~SYSTEM_PERIPHERAL_ID(PORT));
//! [unlock_perph]

//! [alter_config]
	port_pin_toggle_output_level(LED_0_PIN);
//! [alter_config]

//! [lock_perph]
	system_peripheral_lock(SYSTEM_PERIPHERAL_ID(PORT),
			~SYSTEM_PERIPHERAL_ID(PORT));
//! [lock_perph]

//! [enable_interrupts_2]
	system_interrupt_leave_critical_section();
//! [enable_interrupts_2]

//! [inf_loop]
	while (1) {
		/* Do nothing */
	}
//! [inf_loop]
//! [main]
}
