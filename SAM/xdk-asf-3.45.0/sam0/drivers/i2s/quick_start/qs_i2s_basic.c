/**
 * \file
 *
 * \brief SAM Inter-IC Sound Controller Basic Quickstart
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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
#include <conf_i2s_quick_start.h>

static void _configure_i2s(void);

//! [module_inst]
struct i2s_module i2s_instance;
//! [module_inst]

//! [setup]
static void _configure_i2s(void)
{
	//! [setup_i2s_init]
	i2s_init(&i2s_instance, CONF_I2S_MODULE);
	//! [setup_i2s_init]

	//! [setup_clock_unit_config]
	struct i2s_clock_unit_config config_clock_unit;
	//! [setup_clock_unit_config]
	//! [setup_clock_unit_config_defaults]
	i2s_clock_unit_get_config_defaults(&config_clock_unit);
	//! [setup_clock_unit_config_defaults]

	//! [setup_clock_unit_change_config]
	config_clock_unit.clock.gclk_src = GCLK_GENERATOR_0;

	config_clock_unit.clock.mck_src = I2S_MASTER_CLOCK_SOURCE_GCLK;
	config_clock_unit.clock.mck_out_enable = true;
	config_clock_unit.clock.mck_out_div = 2;

	config_clock_unit.clock.sck_src = I2S_SERIAL_CLOCK_SOURCE_MCKDIV;
	config_clock_unit.clock.sck_div = 4;

	config_clock_unit.frame.number_slots = 2;
	config_clock_unit.frame.slot_size = I2S_SLOT_SIZE_32_BIT;
	config_clock_unit.frame.data_delay = I2S_DATA_DELAY_0;

	config_clock_unit.frame.frame_sync.source = I2S_FRAME_SYNC_SOURCE_SCKDIV;
	config_clock_unit.frame.frame_sync.width = I2S_FRAME_SYNC_WIDTH_HALF_FRAME;
	//! [setup_clock_unit_change_config]

	//! [setup_clock_unit_change_pins]
	config_clock_unit.mck_pin.enable = true;
	config_clock_unit.mck_pin.gpio = CONF_I2S_MCK_PIN;
	config_clock_unit.mck_pin.mux = CONF_I2S_MCK_MUX;

	config_clock_unit.sck_pin.enable = true;
	config_clock_unit.sck_pin.gpio = CONF_I2S_SCK_PIN;
	config_clock_unit.sck_pin.mux = CONF_I2S_SCK_MUX;

	config_clock_unit.fs_pin.enable = true;
	config_clock_unit.fs_pin.gpio = CONF_I2S_FS_PIN;
	config_clock_unit.fs_pin.mux = CONF_I2S_FS_MUX;
	//! [setup_clock_unit_change_pins]

	//! [setup_clock_unit_set_config]
	i2s_clock_unit_set_config(&i2s_instance, I2S_CLOCK_UNIT_0,
			&config_clock_unit);
	//! [setup_clock_unit_set_config]

	//! [setup_serializer_config]
	struct i2s_serializer_config config_serializer;
	//! [setup_serializer_config]
	//! [setup_serializer_config_defaults]
	i2s_serializer_get_config_defaults(&config_serializer);
	//! [setup_serializer_config_defaults]

	//! [setup_serializer_change_config_tx]
	config_serializer.clock_unit = I2S_CLOCK_UNIT_0;
	config_serializer.mode = I2S_SERIALIZER_TRANSMIT;
	config_serializer.data_size = I2S_DATA_SIZE_16BIT;
	//! [setup_serializer_change_config_tx]

	//! [setup_serializer_change_config_pin_tx]
	config_serializer.data_pin.enable = true;
	config_serializer.data_pin.gpio = CONF_I2S_SD_PIN;
	config_serializer.data_pin.mux = CONF_I2S_SD_MUX;
	//! [setup_serializer_change_config_pin_tx]

	//! [setup_serializer_set_config_tx]
	i2s_serializer_set_config(&i2s_instance, I2S_SERIALIZER_0,
			&config_serializer);
	//! [setup_serializer_set_config_tx]

	//! [setup_enable]
	i2s_enable(&i2s_instance);
	i2s_clock_unit_enable(&i2s_instance, I2S_CLOCK_UNIT_0);
	i2s_serializer_enable(&i2s_instance, I2S_SERIALIZER_0);
	//! [setup_enable]
}
//! [setup]

int main(void)
{
	system_init();

	//! [setup_init]
	_configure_i2s();
	//! [setup_init]

//! [main]
	//! [main_loop]
	while (true) {
		/* Infinite loop */
		i2s_serializer_write_wait(&i2s_instance, I2S_SERIALIZER_0, 0xF87F);
		i2s_serializer_write_wait(&i2s_instance, I2S_SERIALIZER_0, 0x901F);
		i2s_serializer_write_wait(&i2s_instance, I2S_SERIALIZER_0, 0);
		i2s_serializer_write_wait(&i2s_instance, I2S_SERIALIZER_0, 0);
	}
	//! [main_loop]
//! [main]
}
