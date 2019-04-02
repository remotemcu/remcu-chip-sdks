/**
 * \file
 *
 * \brief SAM GPIO Port Driver
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
#include <port.h>

/**
 *  \brief Retrieves the state of a port pin that is configured as an input.
 *
 *  Reads the current logic level of a port pin and returns the current
 *  level as a Boolean value.
 *
 *  \param[in] gpio_pin  Index of the GPIO pin to read
 *
 *  \return Status of the port pin's input buffer.
 */
bool port_pin_get_input_level(
		const uint8_t gpio_pin)
{
	PortGroup *const port_base = port_get_group_from_gpio_pin(gpio_pin);
	uint32_t pin_mask  = (1UL << (gpio_pin % 32));

	return (port_base->IN.reg & pin_mask);
}
/**
 *  \brief Retrieves the state of a port pin that is configured as an output.
 *
 *  Reads the current logical output level of a port pin and returns the current
 *  level as a Boolean value.
 *
 *  \param[in] gpio_pin  Index of the GPIO pin to read
 *
 *  \return Status of the port pin's output buffer.
 */
bool port_pin_get_output_level(
		const uint8_t gpio_pin)
{
	PortGroup *const port_base = port_get_group_from_gpio_pin(gpio_pin);
	uint32_t pin_mask  = (1UL << (gpio_pin % 32));

	return (port_base->OUT.reg & pin_mask);
}

/**
 *  \brief Toggles the state of a port pin that is configured as an output.
 *
 *  Toggles the current output level of a port pin.
 *
 *  \param[in] gpio_pin  Index of the GPIO pin to toggle
 */
void port_pin_toggle_output_level(
		const uint8_t gpio_pin)
{
	PortGroup *const port_base = port_get_group_from_gpio_pin(gpio_pin);
	uint32_t pin_mask  = (1UL << (gpio_pin % 32));

	/* Toggle pin output level */
	port_base->OUTTGL.reg = pin_mask;
}

/**
 *  \brief Sets the state of a port pin that is configured as an output.
 *
 *  Sets the current output level of a port pin to a given logic level.
 *
 *  \param[in] gpio_pin  Index of the GPIO pin to write to
 *  \param[in] level     Logical level to set the given pin to
 */
void port_pin_set_output_level(
		const uint8_t gpio_pin,
		const bool level)
{
	PortGroup *const port_base = port_get_group_from_gpio_pin(gpio_pin);
	uint32_t pin_mask  = (1UL << (gpio_pin % 32));

	/* Set the pin to high or low atomically based on the requested level */
	if (level) {
		port_base->OUTSET.reg = pin_mask;
	} else {
		port_base->OUTCLR.reg = pin_mask;
	}
}

/**
 *  \brief Writes a Port pin configuration to the hardware module.
 *
 *  Writes out a given configuration of a Port pin configuration to the hardware
 *  module.
 *
 *  \note If the pin direction is set as an output, the pull-up/pull-down input
 *        configuration setting is ignored.
 *
 *  \param[in] gpio_pin  Index of the GPIO pin to configure
 *  \param[in] config    Configuration settings for the pin
 */
void port_pin_set_config(
		const uint8_t gpio_pin,
		const struct port_config *const config)
{
	/* Sanity check arguments */
	Assert(config);

	struct system_pinmux_config pinmux_config;
	system_pinmux_get_config_defaults(&pinmux_config);

	pinmux_config.mux_position = SYSTEM_PINMUX_GPIO;
	pinmux_config.direction    = (enum system_pinmux_pin_dir)config->direction;
	pinmux_config.input_pull   = (enum system_pinmux_pin_pull)config->input_pull;
	pinmux_config.powersave    = config->powersave;

	system_pinmux_pin_set_config(gpio_pin, &pinmux_config);
}

/**
 *  \brief Writes a Port group configuration group to the hardware module.
 *
 *  Writes out a given configuration of a Port group configuration to the
 *  hardware module.
 *
 *  \note If the pin direction is set as an output, the pull-up/pull-down input
 *        configuration setting is ignored.
 *
 *  \param[out] port    Base of the PORT module to write to
 *  \param[in]  mask    Mask of the port pin(s) to configure
 *  \param[in]  config  Configuration settings for the pin group
 */
void port_group_set_config(
		PortGroup *const port,
		const uint32_t mask,
		const struct port_config *const config)
{
	/* Sanity check arguments */
	Assert(port);
	Assert(config);

	struct system_pinmux_config pinmux_config;
	system_pinmux_get_config_defaults(&pinmux_config);

	pinmux_config.mux_position = SYSTEM_PINMUX_GPIO;
	pinmux_config.direction    = (enum system_pinmux_pin_dir)config->direction;
	pinmux_config.input_pull   = (enum system_pinmux_pin_pull)config->input_pull;
	pinmux_config.powersave    = config->powersave;

	system_pinmux_group_set_config(port, mask, &pinmux_config);
}

#ifdef REMCU_LIB
void port_get_config_defaults(
		struct port_config *const config)
{
	/* Sanity check arguments */
	Assert(config);

	/* Default configuration values */
	config->direction  = PORT_PIN_DIR_INPUT;
	config->input_pull = PORT_PIN_PULL_UP;
	config->powersave  = false;
}
#endif