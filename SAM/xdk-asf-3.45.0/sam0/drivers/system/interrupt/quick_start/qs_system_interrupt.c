/**
 * \file
 *
 * \brief SAM System Interrupt Driver Quick Start
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

volatile bool is_ready;

int main(void)
{
	system_init();

//! [main_1]
//! [critical_section_start]
	system_interrupt_enter_critical_section();
//! [critical_section_start]

//! [do_critical_code]
	if (is_ready == true) {
		/* Do something in response to the global shared flag */
		is_ready = false;
	}
//! [do_critical_code]

//! [critical_section_end]
	system_interrupt_leave_critical_section();
//! [critical_section_end]
//! [main_1]

//! [main_2]
//! [module_int_enable]
	system_interrupt_enable(SYSTEM_INTERRUPT_MODULE_RTC);
//! [module_int_enable]

//! [global_int_enable]
	system_interrupt_enable_global();
//! [global_int_enable]
//! [main_2]

	while (true) {
		/* Infinite loop */
	}
}
