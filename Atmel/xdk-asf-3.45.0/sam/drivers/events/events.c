/**
 * \file
 *
 * \brief SAM4L Peripheral Event Controller (PEVC) Driver.
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

#include <events.h>
#include <sysclk.h>
#include <sleepmgr.h>

/**
 * \brief Initialize an events configuration structure to defaults.
 *
 *  The default configuration is as follows:
 *  - Input Glitch Filter Divider is set to \ref EVENT_IGF_DIVIDER_1024
 *
 *  \param[out] config    Configuration structure to initialize to default values
 */
void events_get_config_defaults(
		struct events_conf *const config)
{
	/* Validate parameters. */
	Assert(config);
	
	config->igf_divider = EVENT_IGF_DIVIDER_1024;
}

/**
 * \brief Initialize the events module.
 *
 *  \param[in] config    Configuration structure to initialize to default values
 */
void events_init(
		struct events_conf *const config)
{
	/* Validate parameters. */
	Assert(config);
	
	/* Enable clock for PEVC module */
	sysclk_enable_peripheral_clock(PEVC);

	/* Set configuration */
	events_set_igf_divider(config->igf_divider);
}

/**
 * \brief Enable the events module.
 */
void events_enable(void)
{
	sysclk_enable_peripheral_clock(PEVC);
	sleepmgr_lock_mode(SLEEPMGR_BACKUP);
}

/**
 * \brief Disable the events module.
 */
void events_disable(void)
{
	sysclk_disable_peripheral_clock(PEVC);
	sleepmgr_unlock_mode(SLEEPMGR_BACKUP);
}

/**
 * \brief Initialize an Event Channel configuration structure to defaults.
 *
 *  The default configuration is as follows:
 *  - Channel ID is initialized to invalid number
 *  - Generator ID is initialized to invalid number
 *  - Event shaper is disabled
 *  - Event Input Glitch Filter is disabled
 *
 *  \param[out] config    Configuration structure to initialize to default values
 */
void events_ch_get_config_defaults(
		struct events_ch_conf *const config)
{
	/* Sanity check arguments */
	Assert(config);

	/* Default configuration values */
	config->channel_id = EVENT_CHANNEL_N;
	config->generator_id = EVENT_GENERATOR_N;
	config->shaper_enable = false;
	config->igf_edge = EVENT_IGF_EDGE_NONE;
}

/**
 * \brief Configure an Event Channel.
 *
 * \param[in,out] config      Configuration settings for the Event Channel
 */
void events_ch_configure(
		struct events_ch_conf *const config)
{
	uint32_t evs_val = 0;

	/* Sanity check arguments */
	Assert(config);
	Assert(config->channel_id < EVENT_CHANNEL_N);
	Assert(config->generator_id < EVENT_GENERATOR_N);

	/* Disable the channel first */
	events_ch_disable(config->channel_id);

	/* Configure the event channel */
	PEVC->PEVC_CHMX[config->channel_id].PEVC_CHMX =
		PEVC_CHMX_EVMX(config->generator_id);
	if (config->shaper_enable) {
		evs_val |= PEVC_EVS_EN;
	} else {
		evs_val &= (~PEVC_EVS_EN);
	}
	switch (config->igf_edge) {
	case EVENT_IGF_EDGE_RISING:
		evs_val |= PEVC_EVS_IGFR_1;
		break;
	case EVENT_IGF_EDGE_FALLING:
		evs_val |= PEVC_EVS_IGFF_1;
		break;
	case EVENT_IGF_EDGE_BOTH:
		evs_val |= (PEVC_EVS_IGFR_1 | PEVC_EVS_IGFF_1);
		break;
	case EVENT_IGF_EDGE_NONE:
	default:
		break;
	}
	PEVC->PEVC_EVS[config->generator_id].PEVC_EVS = evs_val;
}
