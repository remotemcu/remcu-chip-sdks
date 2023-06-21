/**
 * \file
 *
 * \brief SAM GPIO Driver for SAMB11
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
#include <gpio.h>

/**
 * \internal
 * Internal driver device instance struct.
 */
struct gpio_module _gpio_instances[3];
/**
 * \internal
 * Handling Wakeup/Sleep operation for AO_GPIO
 * 0x1bc51 is the function address in ROM firmware, as AON GPIO is special function
 * GPIO which controls ULP mode. ROM Firmware handles wakeup-sleep operations.
 * User should not change this value. When aon_wakeup is true to enable AO_GPIO as
 * wakeup source calling this function will trigger the wakeup of ARM.
 * Rising edge on AO_GPIO wakes-up the ARM and falling edge will trigger the
 * sleep. It is recommended to configure AO_GPIO as rising edge, on rising edge
 * interrupt this function, configures the AO_GPIO as falling edge. As long as it 
 * is held high; device will be awake and awaiting a falling edge on this pin.
 * Falling edge on the pin, triggers the interrupt and this function configures the pin
 * as rising edge and enable sleep. So, configuring rising edge using gpio_register_callback
 * for AO_GPIO with wakeup source will trigger to 2 interrupts, 1 on rising edge and
 * another on falling edge.
 */
static void (*aon_handle_ext_wakeup_isr)(void) = (void (*)(void))0x1bc51;

/**
 *  \brief Initializes a gpio pin/group configuration structure to defaults.
 *
 *  Initializes a given gpio pin/group configuration structure to a set of
 *  known default values. This function should be called on all new
 *  instances of these configuration structures before being modified by the
 *  user application.
 *
 *  The default configuration is as follows:
 *   \li Input mode with internal pullup enabled
 *
 *  \param[out] config  Configuration structure to initialize to default values.
 */
void gpio_get_config_defaults(struct gpio_config *const config)
{
	/* Default configuration values */
	config->direction  = GPIO_PIN_DIR_INPUT;
	config->input_pull = GPIO_PIN_PULL_UP;
	/* Applicable only for AO_GPIO */
	config->aon_wakeup = true;
}

/**
 *  \brief Writes a gpio pin configuration to the hardware module.
 *
 *  Writes out a given configuration of a gpio pin configuration to the hardware
 *  module. If the configuration is NULL then it releases the gpio pin.
 *
 *  \note Normally internal pull-up or pull-down is used for input. If the input pin 
 *  is not connected, then pin will be in Hi-z state. Enabling pull-up or down will lead to 
 *  defined state on input line. The Pull-up/down circuit is common for input as well as output. 
 *  Also certain gpio pin is used by FW and not available for user application. Please \ref gpio_pin
 *  for list of gpio_pin available.
 *
 *  \param[in] gpio_pin  Index of the GPIO pin to configure.
 *	gpio_pin index 0 to 15 is controlled by GPIO0 controller.
 *	gpio_pin index 16 to 31 is controlled by GPIO1 controller.
 *	gpio_pin index 32 to 47 is controlled by GPIO2 controller.
 *  \param[in] config    Configuration settings for the pin.
 *
 *  \return Status of initialization.
 *  \retval STATUS_OK                       gpio configured correctly
 *  \retval STATUS_ERR_INVALID_ARG          Invalid gpio number, Certain gpios
 *                                          are used by FW and not allowed to change.
 *
 */
enum status_code gpio_pin_set_config(const uint8_t gpio_pin,
		const struct gpio_config *config)
{
	enum status_code status = STATUS_OK;

	/* Following GPIO's should never be modified by user.
	* GPIO_0 & GPIO_1 are used for SWD.
	*/
	if ((gpio_pin == PIN_LP_GPIO_0) || \
		(gpio_pin == PIN_LP_GPIO_1))
	{
		status = STATUS_ERR_INVALID_ARG;
	}
	else
	{
		/* Enable Clock for GPIO controller if not done previously */
		if(!((LPMCU_MISC_REGS0->LPMCU_CLOCK_ENABLES_0.reg  & \
		LPMCU_MISC_REGS_LPMCU_CLOCK_ENABLES_0_GPIO_CLK_EN)  &&
		(LPMCU_MISC_REGS0->LPMCU_CLOCK_ENABLES_1.reg & \
		LPMCU_MISC_REGS_LPMCU_CLOCK_ENABLES_1_GPIO_GCLK_EN)))
		{
			system_clock_peripheral_enable(PERIPHERAL_GPIO_CLK);
			system_clock_peripheral_enable(PERIPHERAL_GPIO_GCLK);
		}

		/* Configure Pinmux = 0 for enabling general purpose gpio */
		gpio_pinmux_cofiguration(gpio_pin,GPIO_PINMUX_SEL_0);

		/* Direction Set */
		if(config->direction == GPIO_PIN_DIR_INPUT) {
			if(gpio_pin < 16) {
				GPIO0->OUTENCLR.reg = (1 << gpio_pin);
			}
			else if (gpio_pin < 32){
				GPIO1->OUTENCLR.reg = (1 << (gpio_pin % 16));
			}
			else {
				GPIO2->OUTENCLR.reg = (1 << (gpio_pin % 16));
			}
		} else if(config->direction == GPIO_PIN_DIR_OUTPUT) {
			if (gpio_pin < 16) {
				GPIO0->OUTENSET.reg = (1 << gpio_pin);
			} 
			else if (gpio_pin < 32) {
				GPIO1->OUTENSET.reg = (1 << (gpio_pin % 16));
			}
			else {
				GPIO2->OUTENSET.reg = (1 << (gpio_pin % 16));
			}
		}
	
		if ((gpio_pin == PIN_AO_GPIO_0) || (gpio_pin == PIN_AO_GPIO_1) ||
				(gpio_pin == PIN_AO_GPIO_2)) {
			/* Only Pull-Up option is supported */
			if(config->input_pull == GPIO_PIN_PULL_DOWN)
			{
				return STATUS_ERR_INVALID_ARG;
			}
			/* Only AO_GPIO_0, could enable this feature as per current ROM firmware code
				Please restrict to use only AO_GPIO_0 for waking up BLE and MCU */
			if(config->aon_wakeup == true && ((gpio_pin == PIN_AO_GPIO_1) || (gpio_pin == PIN_AO_GPIO_2)))
			{
				return STATUS_ERR_INVALID_ARG;
			}
			/* When using AO_GPIO as wakeup source, it should not be output */
			if(config->aon_wakeup == true && config->direction == GPIO_PIN_DIR_OUTPUT)
			{
				return STATUS_ERR_INVALID_ARG;
			}
			/* Active Low, Always On Pull Enable Control */
			if (config->input_pull == GPIO_PIN_PULL_UP) {
				AON_GP_REGS0->AON_PULL_ENABLE.reg &= ~(1 << (31 - gpio_pin));
			} else {
				AON_GP_REGS0->AON_PULL_ENABLE.reg |= 1 << (31 - gpio_pin);
			}

			if (config->aon_wakeup) {
				/* Enable AO_GPIO_z to be a wakeup MCU from sleep mode */
				AON_GP_REGS0->AON_PINMUX_SEL.reg |= 1 << (4 * (31 - gpio_pin));
				/* Enable AO_GPIO_z to wake up the BLE domain from sleep mode */
				AON_PWR_SEQ0->GPIO_WAKEUP_CTRL.bit.BLE_ENABLE = 1;
			} else {
				/* Disable AO_GPIO_z to wake up the BLE domain from sleep mode */
				AON_PWR_SEQ0->GPIO_WAKEUP_CTRL.bit.BLE_ENABLE = 0;
			}
		} else {
			/* pull_enable. */
			if (gpio_pin <= 23) {
				switch(config->input_pull) {
					case GPIO_PIN_PULL_NONE:
						LPMCU_MISC_REGS0->PULL_ENABLE.reg |= (1 << gpio_pin);
						break;
					case GPIO_PIN_PULL_UP:
						/* Set R-Type */
						LPMCU_MISC_REGS0->RTYPE_PAD_0.reg &= ~(1 << gpio_pin);
						/* Set REN */
						LPMCU_MISC_REGS0->PULL_ENABLE.reg &= ~(1 << gpio_pin);
						break;
					case GPIO_PIN_PULL_DOWN:
						/* Set R-Type */
						LPMCU_MISC_REGS0->RTYPE_PAD_0.reg |= (1 << gpio_pin);
						/* Set REN */
						LPMCU_MISC_REGS0->PULL_ENABLE.reg &= ~(1 << gpio_pin);
						break;
					default:
						status = STATUS_ERR_INVALID_ARG;
					break;
				}
			}
			if (gpio_pin >= 44 && gpio_pin < 48) {
				switch(config->input_pull) {
					case GPIO_PIN_PULL_NONE:
						LPMCU_MISC_REGS0->MS_GPIO.vec.PULL_ENABLE_ |= (1<<(gpio_pin - PIN_GPIO_MS4));
						break;
					case GPIO_PIN_PULL_UP:
						/* Set R-Type */
						LPMCU_MISC_REGS0->MS_GPIO.vec.PULL_TYPE_ &= ~(1<<(gpio_pin - PIN_GPIO_MS4));
						/* Set REN */
						LPMCU_MISC_REGS0->MS_GPIO.vec.PULL_ENABLE_ &= ~(1<<(gpio_pin - PIN_GPIO_MS4));
						break;
					case GPIO_PIN_PULL_DOWN:
						/* Set R-Type */
						LPMCU_MISC_REGS0->MS_GPIO.vec.PULL_TYPE_ |= (1<<(gpio_pin - PIN_GPIO_MS4));
						/* Set REN */
						LPMCU_MISC_REGS0->MS_GPIO.vec.PULL_ENABLE_ &= ~(1<<(gpio_pin - PIN_GPIO_MS4));
						break;
					default:
						status = STATUS_ERR_INVALID_ARG;
						break;
				}
			}
		}
	}
	return status;
}

/**
 *  \brief Retrieves the state of a gpio pin that is configured as an input.
 *
 *  Reads the current logic level of a gpio pin and returns the current
 *  level as a boolean value.
 *
 *  \param[in] gpio_pin  Index of the GPIO pin to read.
 *	gpio_pin index 0 to 15 is controlled by GPIO0 controller.
 *	gpio_pin index 16 to 31 is controlled by GPIO1 controller.
 *	gpio_pin index 32 to 47 is controlled by GPIO2 controller.
 *
 *  \return Status of the gpio pin's input buffer.
 */
bool gpio_pin_get_input_level(const uint8_t gpio_pin)
{
	uint32_t regval = 0;

	if (gpio_pin < 16) {
		regval = GPIO0->DATA.reg;
		regval &= (1 << gpio_pin);
	} else if (gpio_pin < 32) {
		regval = GPIO1->DATA.reg;
		regval &= (1 << (gpio_pin % 16));
	} else {
		regval = GPIO2->DATA.reg;
		regval &= (1 << (gpio_pin % 16));
	}

	return regval;
}

/**
 *  \brief Retrieves the state of a gpio pin that is configured as an output.
 *
 *  Reads the current logical output level of a gpio pin and returns the current
 *  level as a boolean value.
 *
 *  \param[in] gpio_pin  Index of the GPIO pin to read.
 *	gpio_pin index 0 to 15 is controlled by GPIO0 controller.
 *	gpio_pin index 16 to 31 is controlled by GPIO1 controller.
 *	gpio_pin index 32 to 47 is controlled by GPIO2 controller.
 *
 *  \return Status of the gpio pin's output buffer.
 */
bool gpio_pin_get_output_level(const uint8_t gpio_pin)
{
	uint32_t regval = 0;

	if (gpio_pin < 16) {
		regval = GPIO0->DATAOUT.reg;
		regval &= (1 << gpio_pin);
	} else if (gpio_pin < 32) {
		regval = GPIO1->DATAOUT.reg;
		regval &= (1 << (gpio_pin % 16));
	} else {
		regval = GPIO2->DATAOUT.reg;
		regval &= (1 << (gpio_pin % 16));
	}

	return regval;
}

/**
 *  \brief Sets the state of a gpio pin that is configured as an output.
 *
 *  Sets the current output level of a gpio pin to a given logic level.
 *
 *  \param[in] gpio_pin  Index of the GPIO pin to write to.
 *	gpio_pin index 0 to 15 is controlled by GPIO0 controller.
 *	gpio_pin index 16 to 31 is controlled by GPIO1 controller.
 *	gpio_pin index 32 to 47 is controlled by GPIO2 controller.
 *  \param[in] level     Logical level to set the given pin to.
 */
void gpio_pin_set_output_level(const uint8_t gpio_pin, const bool level)
{
	if (gpio_pin < 16) {
		if(level) {
			GPIO0->DATAOUT.reg |= (1 << gpio_pin);
		} else {
			GPIO0->DATAOUT.reg &= ~(1 << gpio_pin);
		}
	} else if (gpio_pin < 32) {
		if(level) {
			GPIO1->DATAOUT.reg |= (1 << (gpio_pin % 16));
		} else {
			GPIO1->DATAOUT.reg &= ~(1 << (gpio_pin % 16));
		}
	} else {
		if(level) {
			GPIO2->DATAOUT.reg |= (1 << (gpio_pin % 16));
		} else {
			GPIO2->DATAOUT.reg &= ~(1 << (gpio_pin % 16));
		}
	}
}

/**
 *  \brief Toggles the state of a gpio pin that is configured as an output.
 *
 *  Toggles the current output level of a gpio pin.
 *
 *  \param[in] gpio_pin  Index of the GPIO pin to toggle. 
 *	gpio_pin index 0 to 15 is controlled by GPIO0 controller.
 *	gpio_pin index 16 to 31 is controlled by GPIO1 controller.
 *	gpio_pin index 32 to 47 is controlled by GPIO2 controller.
 */
void gpio_pin_toggle_output_level(const uint8_t gpio_pin)
{
	if (gpio_pin < 16) {
		GPIO0->DATAOUT.reg ^= (1 << gpio_pin);
	} else if (gpio_pin < 32) {
		GPIO1->DATAOUT.reg ^= (1 << (gpio_pin % 16));
	} else {
		GPIO2->DATAOUT.reg ^= (1 << (gpio_pin % 16));
	}
}

/**
 *  \brief Inverts the logical output level set using DATAOUT register 
 *  This inversion applicable only for LP_GPIO_x
 *  \param[in] gpio_pin  Index of the GPIO pin to invert the output level.
 *  \param[in] invert    Invert the output level on GPIO pin.
 *  \return Status of initialization.
 *  \retval STATUS_OK                       gpio configured correctly
 *  \retval STATUS_ERR_INVALID_ARG          Feature not supported for this GPIO
 */
enum status_code gpio_pin_invert_output_level(const uint8_t gpio_pin, const bool invert)
{
	enum status_code status = STATUS_OK;
	if (gpio_pin <= 23) {
		if(invert)
			LPMCU_MISC_REGS0->INVERT_OUTPUT_CTRL.reg |= (1 << gpio_pin);
		else
			LPMCU_MISC_REGS0->INVERT_OUTPUT_CTRL.reg &= ~(1 << gpio_pin);
	} else
		status = STATUS_ERR_INVALID_ARG;

	return status;
}

/**
 *  \brief Writes a GPIO pin configuration to the hardware module.
 *
 *  Writes out a given configuration of a GPIO pin configuration to the hardware
 *  module.
 *
 *  \param[in] gpio_pin   Index of the GPIO pin to configure the pinmux.
 *  \param[in] pinmux_megamux_sel PINMUX selection.  MSB 8bits of pinmux_megamux_sel holds the MEGAMUX value
 *  LSB 8bits of pinmux_megamux_sel holds the PINMUX value
 *  Possible pinmux values: PINMUX = 0 to 3 is for AO_GPIO_z, PINMUX = 0 to 7 for LP_GPIO_x
 *  PINMUX = 0,1 for GPIO_MSy. Refer to I/O Port Function Multiplexing Table from SAMB11 datasheet for more details.
 *  MEGAMUX is applicable only for LP_GPIO_x. Possible MEGAMUX values: 0 to 0x3F. Refer to MEGAMUX Options table from
 *	SAMB11 datasheet.
 */
void gpio_pinmux_cofiguration(const uint8_t gpio_pin, uint16_t pinmux_megamux_sel)
{
	uint8_t megamux_sel = (pinmux_megamux_sel >> 8) & 0xFF;

	pinmux_megamux_sel &= 0xFF;

	if (gpio_pin <= 7) {
		LPMCU_MISC_REGS0->PINMUX_SEL_0.reg &= ~(7 << ((gpio_pin % 8) * 4));
		LPMCU_MISC_REGS0->PINMUX_SEL_0.reg |= (pinmux_megamux_sel << ((gpio_pin % 8)*4));
		if (pinmux_megamux_sel == 0x01) {
			if (gpio_pin <= 3) {
				LPMCU_MISC_REGS0->MEGA_MUX_IO_SEL_0.reg &= ~(0x3F << ((gpio_pin % 4) * 8));
				LPMCU_MISC_REGS0->MEGA_MUX_IO_SEL_0.reg |= (megamux_sel << ((gpio_pin % 4) * 8));
			} else if (gpio_pin <= 7) {
				LPMCU_MISC_REGS0->MEGA_MUX_IO_SEL_1.reg &= ~(0x3F << ((gpio_pin % 4) * 8));
				LPMCU_MISC_REGS0->MEGA_MUX_IO_SEL_1.reg |= (megamux_sel << ((gpio_pin % 4) * 8));
			}
		}
	} else if (gpio_pin <= 15) {
		LPMCU_MISC_REGS0->PINMUX_SEL_1.reg &= ~(7 << ((gpio_pin % 8) * 4));
		LPMCU_MISC_REGS0->PINMUX_SEL_1.reg |= (pinmux_megamux_sel << ((gpio_pin % 8)*4));
		if (pinmux_megamux_sel == 0x01) {
			if (gpio_pin <= 11) {
				LPMCU_MISC_REGS0->MEGA_MUX_IO_SEL_2.reg &= ~(0x3F << ((gpio_pin % 4) * 8));
				LPMCU_MISC_REGS0->MEGA_MUX_IO_SEL_2.reg |= (megamux_sel << ((gpio_pin % 4) * 8));
			} else if (gpio_pin <= 15) {
				LPMCU_MISC_REGS0->MEGA_MUX_IO_SEL_3.reg &= ~(0x3F << ((gpio_pin % 4) * 8));
				LPMCU_MISC_REGS0->MEGA_MUX_IO_SEL_3.reg |= (megamux_sel << ((gpio_pin % 4) * 8));
			}
		}
	} else if (gpio_pin <= 23) {
		LPMCU_MISC_REGS0->PINMUX_SEL_2.reg &= ~(7 << ((gpio_pin % 8) * 4));
		LPMCU_MISC_REGS0->PINMUX_SEL_2.reg |= (pinmux_megamux_sel << ((gpio_pin % 8)*4));
		if (pinmux_megamux_sel == 0x01) {
			if (gpio_pin <= 19) {
				LPMCU_MISC_REGS0->MEGA_MUX_IO_SEL_4.reg &= ~(0x3F << ((gpio_pin % 4) * 8));
				LPMCU_MISC_REGS0->MEGA_MUX_IO_SEL_4.reg |= (megamux_sel << ((gpio_pin % 4) * 8));
			} else if (gpio_pin <= 23) {
				LPMCU_MISC_REGS0->MEGA_MUX_IO_SEL_5.reg &= ~(0x3F << ((gpio_pin % 4) * 8));
				LPMCU_MISC_REGS0->MEGA_MUX_IO_SEL_5.reg |= (megamux_sel << ((gpio_pin % 4) * 8));
			}
		}
	}else if (29 <= gpio_pin  && gpio_pin < 32) {
		/* Enable AO_GPIO_z Pinmux. Megamux is not applicable for AO_GPIO_z*/
		AON_GP_REGS0->AON_PINMUX_SEL.reg &= ~(0x3 << (4 * (31 - gpio_pin)));
		AON_GP_REGS0->AON_PINMUX_SEL.reg |= (pinmux_megamux_sel << (4 * (31 - gpio_pin)));
	}else if (44 <= gpio_pin  && gpio_pin < 48) {
		/* Enable GPIO_MSy Pinmux. 0 means general purpose GPIO, 1 means analog input
		Megamux is not applicable for GPIO_MSy*/
		AON_GP_REGS0->MS_GPIO_MODE.vec.ANALOG_ENABLE_ &= ~(1 << (gpio_pin - PIN_GPIO_MS4));
		AON_GP_REGS0->MS_GPIO_MODE.vec.ANALOG_ENABLE_ |= (pinmux_megamux_sel << (gpio_pin - PIN_GPIO_MS4));
	}
}

/**
 * \brief Registers a callback
 *
 * Registers a callback function which is implemented by the user.
 *
 * \note The callback must be enabled by \ref gpio_enable_callback,
 *       in order for the interrupt handler to call it when the conditions for
 *       the callback type are met.
 *
 * \param[in]  gpio_pin       GPIO pin number
 *	gpio_pin index 0 to 15 is controlled by GPIO0 controller.
 *	gpio_pin index 16 to 31 is controlled by GPIO1 controller.
 *	gpio_pin index 32 to 47 is controlled by GPIO2 controller.
 * \param[in]  callback_func  Pointer to callback function
 * \param[in]  callback_type  Callback type given by an enum
 *
 */
void gpio_register_callback(uint8_t gpio_pin, gpio_callback_t callback_func,
				enum gpio_callback callback_type)
{
	/* Sanity check arguments */
	Assert(callback_func);
	Assert(gpio_pin < 48);

	uint8_t gpio_port = 0;

	if (gpio_pin < 16) {
		gpio_port = 0;
	} else if (gpio_pin < 32) {
		gpio_port = 1;
	} else {
		gpio_port = 2;
	}
	switch (callback_type) {
	case GPIO_CALLBACK_LOW:
		_gpio_instances[gpio_port].hw->INTTYPECLR.reg = 1 << (gpio_pin % 16);
		_gpio_instances[gpio_port].hw->INTPOLCLR.reg = 1 << (gpio_pin % 16);
		break;

	case GPIO_CALLBACK_HIGH:
		_gpio_instances[gpio_port].hw->INTTYPECLR.reg = 1 << (gpio_pin % 16);
		_gpio_instances[gpio_port].hw->INTPOLSET.reg = 1 << (gpio_pin % 16);
		break;

	case GPIO_CALLBACK_RISING:
		_gpio_instances[gpio_port].hw->INTTYPESET.reg = 1 << (gpio_pin % 16);
		_gpio_instances[gpio_port].hw->INTPOLSET.reg = 1 << (gpio_pin % 16);
		break;

	case GPIO_CALLBACK_FALLING:
		_gpio_instances[gpio_port].hw->INTTYPESET.reg = 1 << (gpio_pin % 16);
		_gpio_instances[gpio_port].hw->INTPOLCLR.reg = (1 << (gpio_pin % 16));
		break;

	case GPIO_CALLBACK_N:
		break;
	}
	/* Register callback function */
	_gpio_instances[gpio_port].callback[gpio_pin % 16] = callback_func;
	/* Set the bit corresponding to the gpio pin */
	_gpio_instances[gpio_port].callback_reg_mask |= (1 << (gpio_pin % 16));
}

/**
 * \brief Unregisters a callback
 *
 * Unregisters a callback function which is implemented by the user.
 *
 *
 * \param[in]  gpio_pin       GPIO pin number
 *	gpio_pin index 0 to 15 is controlled by GPIO0 controller.
 *	gpio_pin index 16 to 31 is controlled by GPIO1 controller.
 *	gpio_pin index 32 to 47 is controlled by GPIO2 controller.
 * \param[in]  callback_type  Callback type given by an enum
 *
 */
void gpio_unregister_callback(uint8_t gpio_pin,
				enum gpio_callback callback_type)
{
	/* Sanity check arguments */
	Assert(callback_func);
	Assert(gpio_pin < 48);

	uint8_t gpio_port = 0;

	if (gpio_pin < 16) {
		gpio_port = 0;
	} else if (gpio_pin < 32) {
		gpio_port = 1;
	} else {
		gpio_port = 2;
	}

	/* Unregister callback function */
	_gpio_instances[gpio_port].callback[gpio_pin % 16] = NULL;
	/* Set the bit corresponding to the gpio pin */
	_gpio_instances[gpio_port].callback_reg_mask &= ~(1 << (gpio_pin % 16));
}

/**
 * \brief Enables callback
 *
 * Enables the callback function registered by the \ref gpio_register_callback.
 * The callback function will be called from the interrupt handler when the
 * conditions for the callback type are met.
 *
 * \param[in]  gpio_pin   GPIO pin
 *	gpio_pin index 0 to 15 is controlled by GPIO0 controller.
 *	gpio_pin index 16 to 31 is controlled by GPIO1 controller.
 *	gpio_pin index 32 to 47 is controlled by GPIO2 controller. 
 */
void gpio_enable_callback(uint8_t gpio_pin)
{
	Assert(gpio_pin < 48);

	uint8_t gpio_port = 0;

	if (gpio_pin < 16) {
		gpio_port = 0;
		NVIC_EnableIRQ(GPIO0_IRQn);
	} else if (gpio_pin < 32) {
		gpio_port = 1;
		NVIC_EnableIRQ(GPIO1_IRQn);
	} else {
		gpio_port = 2;
		NVIC_EnableIRQ(GPIO2_IRQn);
	}

	/* Enable callback */
	_gpio_instances[gpio_port].callback_enable_mask |= (1 << (gpio_pin % 16));
	_gpio_instances[gpio_port].hw->INTENSET.reg = (1 << (gpio_pin % 16));
}

/**
 * \brief Disables callback
 *
 * Disables the callback function registered by the \ref usart_register_callback.
 * The callback function will not be called from the interrupt handler.
 *
 * \param[in]  gpio_pin   GPIO pin
 *	gpio_pin index 0 to 15 is controlled by GPIO0 controller.
 *	gpio_pin index 16 to 31 is controlled by GPIO1 controller.
 *	gpio_pin index 32 to 47 is controlled by GPIO2 controller. 
 */
void gpio_disable_callback(uint8_t gpio_pin)
{
	Assert(gpio_pin < 48);

	uint8_t gpio_port = 0;

	if (gpio_pin < 16) {
		gpio_port = 0;
	} else if (gpio_pin < 32) {
		gpio_port = 1;
	} else {
		gpio_port = 2;
	}

	/* Enable callback */
	_gpio_instances[gpio_port].callback_enable_mask &= ~(1 << (gpio_pin % 16));
	_gpio_instances[gpio_port].hw->INTENCLR.reg = (1 << (gpio_pin % 16));
}

/**
 * \internal GPIO port0 isr handler.
 *
 * This function will enter interrupt.
 *
 */
static void gpio_port0_isr_handler(void)
{
	uint32_t flag = _gpio_instances[0].hw->INTSTATUSCLEAR.reg;

	for (uint8_t i = 0; i < 16; i++){
		if (flag & (1 << i)) {
			/* Clear interrupt flag */
			_gpio_instances[0].hw->INTSTATUSCLEAR.reg = (1 << i);
			if ((_gpio_instances[0].callback_enable_mask & (1 << i)) && \
					(_gpio_instances[0].callback_reg_mask & (1 << i)))
				_gpio_instances[0].callback[i]();
			break;
		}
	}
	NVIC_ClearPendingIRQ(GPIO0_IRQn);
}

/**
 * \internal GPIO port1 isr handler.
 *
 * This function will enter interrupt.
 *
 */
static void gpio_port1_isr_handler(void)
{
	uint32_t flag = _gpio_instances[1].hw->INTSTATUSCLEAR.reg;

	for (uint8_t i = 0; i < 16; i++){
		/* For AON wakeup pin clear interrupt */
		if (flag & ((1<<15) | (1<<14) | (1<<13))) {
		/* This is the call to the function in ROM firmware code.*/
			aon_handle_ext_wakeup_isr();
		}

		if (flag & (1 << i)) {
			/* Clear interrupt flag */
			_gpio_instances[1].hw->INTSTATUSCLEAR.reg = (1 << i);
			if ((_gpio_instances[1].callback_enable_mask & (1 << i)) && \
			(_gpio_instances[1].callback_reg_mask & (1 << i))) {
				_gpio_instances[1].callback[i]();
				break;
			}
		}
	}
	NVIC_ClearPendingIRQ(GPIO1_IRQn);
}

/**
 * \internal GPIO port2 isr handler.
 *
 * This function will enter interrupt.
 *
 */
static void gpio_port2_isr_handler(void)
{
	uint32_t flag = _gpio_instances[2].hw->INTSTATUSCLEAR.reg;

	for (uint8_t i = 12; i < 16; i++){
		if (flag & (1 << i)) {
			/* Clear interrupt flag */
			_gpio_instances[2].hw->INTSTATUSCLEAR.reg = (1 << i);
			if ((_gpio_instances[2].callback_enable_mask & (1 << i)) && \
					(_gpio_instances[2].callback_reg_mask & (1 << i)))
				_gpio_instances[2].callback[i]();
			break;
		}
	}
	NVIC_ClearPendingIRQ(GPIO2_IRQn);
}

/**
 * \internal GPIO callback init.
 *
 * This function will init GPIO callback.
 * Register the ISR handler address in interrupt vector table
 */
void gpio_init(void)
{
	uint8_t i, j;

	for(i = 0; i < 3; i++) {
		for(j = 0; j < 16; j++) {
			_gpio_instances[i].callback[j] = NULL;
		}
		_gpio_instances[i].callback_enable_mask = 0;
		_gpio_instances[i].callback_reg_mask = 0;
	}
	_gpio_instances[0].hw = (void *)GPIO0;
	_gpio_instances[1].hw = (void *)GPIO1;
	_gpio_instances[2].hw = (void *)GPIO2;
	system_register_isr(RAM_ISR_TABLE_PORT0_COMB_INDEX, (uint32_t)gpio_port0_isr_handler);
	system_register_isr(RAM_ISR_TABLE_PORT1_COMB_INDEX, (uint32_t)gpio_port1_isr_handler);
	system_register_isr(RAM_ISR_TABLE_PORT2_COMB_INDEX, (uint32_t)gpio_port2_isr_handler);
}

