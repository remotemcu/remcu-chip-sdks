/**
 * \file
 *
 * \brief SAM Event System Driver Quick Start
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
#include "conf_qs_events.h"

//! [setup]

static void configure_event_channel(struct events_resource *resource)
{
//! [setup_1]
	struct events_config config;
//! [setup_1]

//! [setup_2]
	events_get_config_defaults(&config);
//! [setup_2]

//! [setup_3]
	config.generator      = CONF_EVENT_GENERATOR;
	config.edge_detect    = EVENTS_EDGE_DETECT_RISING;
	config.path           = EVENTS_PATH_SYNCHRONOUS;
	config.clock_source   = GCLK_GENERATOR_0;
//! [setup_3]

//! [setup_4]
	events_allocate(resource, &config);
//! [setup_4]
}

static void configure_event_user(struct events_resource *resource)
{
//! [setup_5]
	events_attach_user(resource, CONF_EVENT_USER);
//! [setup_5]
}

//! [setup]

int main(void)
{
//! [events_resource_struct]
	struct events_resource example_event;
//! [events_resource_struct]

	system_init();

//! [setup_init]
	configure_event_channel(&example_event);
	configure_event_user(&example_event);
//! [setup_init]

	//! [main]

	//! [main_1]
	while (events_is_busy(&example_event)) {
		/* Wait for channel */
	};
	//! [main_1]

	//! [main_2]
	events_trigger(&example_event);
	//! [main_2]

	while (true) {
		/* Nothing to do */
	}

	//! [main]
}
