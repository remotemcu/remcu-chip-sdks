/**
 * \file
 *
 * \brief MCP980X driver
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

#include "mcp980x.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \defgroup common_component_sensors_mcp980x_group MCP980X Temperature Sensor
 *
 * See \ref common_component_sensors_mcp980x_quickstart.
 *
 * \par Purpose
 *
 * The module provides useful API of MCP980X temperature sensor through a TWI interface.
 *
 * \section dependencies Dependencies
 * This driver depends on the following module:
 * - \ref twi_group for common TWI service.
 *
 * @{
 */

#define MCP980X_TEMP_REG  (0x00) /* Temperature Register */
#define MCP980X_CONF_REG  (0x01) /* Configuration Register */
#define MCP980X_HYST_REG  (0x02) /* Temperature Hysteresis Register */
#define MCP980X_LIMT_REG  (0x03) /* Temperature Limit-set Register */

#define MCP980X_DEC_UNIT  (625)

#define TWI_SPEED         (400000ul) /* 400KHz TWI bus frequency */

/**
 * \brief Read the MCP980X register specified by ul_reg_index.
 *
 * \param ul_reg_index The index of MCP980X register.
 * \param p_reg_value Pointer to the value read from the specified MCP980X register.
 *
 * \return TWI bus operation result.
 */
static uint32_t mcp980x_read_register(uint32_t ul_reg_index,
		uint8_t *p_reg_value)
{
	twi_package_t rx = {
		.chip = BOARD_MCP980X_ADDR,
		.addr = {ul_reg_index},
		.addr_length = 1,
		.buffer = p_reg_value
	};

	if (ul_reg_index == MCP980X_CONF_REG) {
		rx.length = 1;
	} else {
		rx.length = 2;
	}

	return twi_master_read(BOARD_MCP980X_TWI_INSTANCE, &rx);
}

/**
 * \brief Write the MCP980X register specified by ul_reg_index.
 *
 * \param ul_reg_index The index of MCP980X register.
 * \param p_reg_value Pointer to the value to be written to the specified MCP980X register.
 *
 * \return TWI bus operation result.
 */
static uint32_t mcp980x_write_register(uint32_t ul_reg_index,
		uint8_t *p_reg_value)
{
	twi_package_t tx = {
		.chip = BOARD_MCP980X_ADDR,
		.addr = {ul_reg_index},
		.addr_length = 1,
		.buffer = p_reg_value
	};

	if (ul_reg_index == MCP980X_CONF_REG) {
		tx.length = 1;
	} else {
		tx.length = 2;
	}

	return twi_master_write(BOARD_MCP980X_TWI_INSTANCE, &tx);
}

/**
 * \brief Convert hexadecimal value to integer part of temperature.
 *
 * \param uc_hex The hexadecimal value.
 * \param p_integer Pointer to the integer part of temperature.
 */
static void mcp980x_hex_to_temperature_int(uint8_t uc_hex, int8_t *p_integer)
{
	*p_integer = (int8_t) uc_hex;
}

/**
 * \brief Convert hexadecimal value to decimal part of temperature.
 *
 * \param uc_hex The hexadecimal value.
 * \param p_decimal Pointer to the decimal part of temperature.
 */
static void mcp980x_hex_to_temperature_dec(uint8_t uc_hex, uint32_t *p_decimal)
{
	*p_decimal = ((uint32_t) uc_hex >> 4) * MCP980X_DEC_UNIT;
}

/**
 * \brief Convert integer part of temperature to hexadecimal value.
 *
 * \param c_integer The integer part of temperature.
 * \param p_hex Pointer to the hexadecimal value.
 */
static void mcp980x_temperature_to_hex_int(int8_t c_integer, uint8_t *p_hex)
{
	*p_hex = (uint8_t) c_integer;
}

/**
 * \brief Convert decimal part of temperature to hexadecimal value.
 *
 * \param ul_decimal The decimal part of temperature.
 * \param p_hex Pointer to the hexadecimal value.
 */
static void mcp980x_temperature_to_hex_dec(uint32_t ul_decimal, uint8_t *p_hex)
{
	*p_hex = (uint8_t) ((ul_decimal / MCP980X_DEC_UNIT) << 4);
}

/**
 * \brief Initialize the hardware interface to the controller
 *
 * This will initialize the module used for communication with the controller.
 * Currently supported interface by this driver is the TWI module in master mode.
 *
 * \return TWI bus operation result.
 */
static uint32_t mcp980x_interface_init(void)
{
	/* TWI master initialization options. */
	twi_master_options_t opt = {
		.speed = TWI_SPEED,
		.chip = BOARD_MCP980X_ADDR
	};

	/* Initialize the TWI master driver. */
	return twi_master_setup(BOARD_MCP980X_TWI_INSTANCE, &opt);
}

/**
 * \brief Get ambient temperature.
 *
 * \param p_integer Pointer to the integer part of ambient temperature in degree Celsius.
 * \param p_decimal Pointer to the decimal part of ambient temperature in 10 ^ -4 degree Celsius.
 *
 * \return TWI bus operation result.
 */
uint32_t mcp980x_get_temperature(int8_t *p_integer,
		uint32_t *p_decimal)
{
	uint8_t uc_ta[2] = { 0 };
	uint32_t ul_retval = mcp980x_read_register(MCP980X_TEMP_REG, uc_ta);

	if (ul_retval == TWI_SUCCESS) {
		mcp980x_hex_to_temperature_int(uc_ta[0], p_integer);
		mcp980x_hex_to_temperature_dec(uc_ta[1], p_decimal);
	}

	return ul_retval;
}

/**
 * \brief Set temperature limit.
 *
 * \param c_integer The integer part of temperature limit in degree Celsius.
 * \param ul_decimal The decimal part of temperature limit in 10 ^ -4 degree Celsius.
 *
 * \return TWI bus operation result.
 */
uint32_t mcp980x_set_temperature_limit(int8_t c_integer, uint32_t ul_decimal)
{
	uint8_t uc_tset[2] = { 0 };
	mcp980x_temperature_to_hex_int(c_integer, &uc_tset[0]);
	mcp980x_temperature_to_hex_dec(ul_decimal, &uc_tset[1]);

	return mcp980x_write_register(MCP980X_LIMT_REG, uc_tset);
}

/**
 * \brief Get temperature limit.
 *
 * \param p_integer Pointer to the integer part of temperature limit in degree Celsius.
 * \param p_decimal Pointer to the decimal part of temperature limit in 10 ^ -4 degree Celsius.
 *
 * \return TWI bus operation result.
 */
uint32_t mcp980x_get_temperature_limit(int8_t *p_integer, uint32_t *p_decimal)
{
	uint8_t uc_tset[2] = { 0 };
	uint32_t ul_retval = mcp980x_read_register(MCP980X_LIMT_REG, uc_tset);

	if (ul_retval == TWI_SUCCESS) {
		mcp980x_hex_to_temperature_int(uc_tset[0], p_integer);
		mcp980x_hex_to_temperature_dec(uc_tset[1], p_decimal);
	}

	return ul_retval;
}

/**
 * \brief Set temperature hysteresis.
 *
 * \param c_integer The integer part of temperature hysteresis in degree Celsius.
 * \param ul_decimal The decimal part of temperature hysteresis in 10 ^ -4 degree Celsius.
 *
 * \return TWI bus operation result.
 */
uint32_t mcp980x_set_temperature_hysteresis(int8_t c_integer,
		uint32_t ul_decimal)
{
	uint8_t uc_thyst[2] = { 0 };
	mcp980x_temperature_to_hex_int(c_integer, &uc_thyst[0]);
	mcp980x_temperature_to_hex_dec(ul_decimal, &uc_thyst[1]);

	return mcp980x_write_register(MCP980X_HYST_REG, uc_thyst);
}

/**
 * \brief Get temperature hysteresis.
 *
 * \param p_integer Pointer to the integer part of temperature hysteresis in degree Celsius.
 * \param p_decimal Pointer to the decimal part of temperature hysteresis in 10 ^ -4 degree Celsius.
 *
 * \return TWI bus operation result.
 */
uint32_t mcp980x_get_temperature_hysteresis(int8_t *p_integer,
		uint32_t *p_decimal)
{
	uint8_t uc_thyst[2] = { 0 };
	uint32_t ul_retval = mcp980x_read_register(MCP980X_HYST_REG, uc_thyst);

	if (ul_retval == TWI_SUCCESS) {
		mcp980x_hex_to_temperature_int(uc_thyst[0], p_integer);
		mcp980x_hex_to_temperature_dec(uc_thyst[1], p_decimal);
	}

	return ul_retval;
}

/**
 * \brief Set MCP980X configuration.
 *
 * \param uc_config The configuration of sensor.
 *
 * \return TWI bus operation result.
 */
uint32_t mcp980x_set_configuration(uint8_t uc_config)
{
	return mcp980x_write_register(MCP980X_CONF_REG, &uc_config);
}

/**
 * \brief Get MCP980X configuration.
 *
 * \param p_config Pointer to the configuration of sensor.
 *
 * \return TWI bus operation result.
 */
uint32_t mcp980x_get_configuration(uint8_t *p_config)
{
	return mcp980x_read_register(MCP980X_CONF_REG, p_config);
}

/**
 * \brief Init the sensor.
 *
 * \return TWI bus operation result.
 */
uint32_t mcp980x_init(void)
{
	return mcp980x_interface_init();
}

/**
 * \brief Enable the sensor.
 *
 * \return TWI bus operation result.
 */
uint32_t mcp980x_enable(void)
{
	uint8_t uc_config_reg = 0;
	uint32_t ul_retval = 0;

	ul_retval = mcp980x_read_register(MCP980X_CONF_REG, &uc_config_reg);
	if (ul_retval != TWI_SUCCESS) {
		return ul_retval;
	}

	uc_config_reg &= (uint8_t)(~MCP980X_CONFIG_SHUTDOWN_ENABLE);

	return mcp980x_write_register(MCP980X_CONF_REG, &uc_config_reg);
}

/**
 * \brief Disable the sensor.
 *
 * \return TWI bus operation result.
 */
uint32_t mcp980x_disable(void)
{
	uint8_t uc_config_reg = 0;
	uint32_t ul_retval = 0;

	ul_retval = mcp980x_read_register(MCP980X_CONF_REG, &uc_config_reg);
	if (ul_retval != TWI_SUCCESS) {
		return ul_retval;
	}

	uc_config_reg &= (uint8_t)(MCP980X_CONFIG_SHUTDOWN_ENABLE);

	return mcp980x_write_register(MCP980X_CONF_REG, &uc_config_reg);
}

/**
 * \brief Enable One-Shot mode and perform a single temperature measure.
 *
 * \return TWI bus operation result.
 */
uint32_t mcp980x_one_shot_mode(void)
{
	uint8_t uc_config_reg = 0;
	uint32_t ul_retval = mcp980x_get_configuration(&uc_config_reg);

	if (ul_retval != TWI_SUCCESS) {
		return ul_retval;
	}

	if (!(uc_config_reg & MCP980X_CONFIG_SHUTDOWN_ENABLE)) {
		/* MCP980X needs to initially be in Shutdown mode to access One-Shot mode. */
		ul_retval = mcp980x_disable();
		if (ul_retval != TWI_SUCCESS) {
			return ul_retval;
		}
		uc_config_reg &= (~MCP980X_CONFIG_SHUTDOWN_ENABLE);
	}

	/* Enable One-Shot mode to perform a single temperature measurement. */
	return mcp980x_set_configuration(MCP980X_CONFIG_ONE_SHOT_ENABLE | uc_config_reg);
}

//@}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
