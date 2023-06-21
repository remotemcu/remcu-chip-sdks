/**
 * \file
 *
 * \brief GPIO Quick Start Guide with Callbacks for SAMB11
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

/**
 * \page asfdoc_samb_gpio_callback_use_case Quick Start Guide for GPIO - Callback
 *
 * In this use case, the GPIO module is configured for:
 *  \li One pin as an external interrupt with rising edge
 *  \li UART to print message on getting the interrupt
 *
 * The GPIO Controller also allows all GPIO pins (LP_GPIO_x, GPIO_MSy, AO_GPIO_z) to 
 * be configured as interrupt lines. Each interrupt line can be individually masked 
 * and can generate an interrupt to CPU on rising, falling, or on high or low levels. 
 *
 * \subsection asfdoc_samb_gpio_callback_use_case_setup_code Code
 * Copy-paste the following setup code to your user application:
 * \snippet qs_gpio_callback.c setup
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_gpio_callback.c setup_init
 *
 * \subsection asfdoc_samb_gpio_callback_use_case_setup_flow Workflow
 * -# Create a UART module configuration struct.
 *    \snippet qs_gpio_callback.c setup_uart_1
 * -# Initialize the config_uart configuration struct with the module's default values.
 *    \snippet qs_gpio_callback.c setup_uart_2 
 *    \note This should always be performed before using the configuration
 *          struct to ensure that all values are initialized to known default
 *          settings.
 *
 * -# Adjust the configuration struct to request setting.
 *    \snippet qs_gpio_callback.c setup_uart_3
 *
 * -# Configure UART with the initialized configuration struct, to enable
 *    the driver.
 *    \snippet qs_gpio_callback.c setup_uart_4
 *
 * -# Create a GPIO module pin configuration struct. Initialize the pin configuration
 *    struct with the module's default values.
 *    \snippet qs_gpio_callback.c setup_gpio_1
 *    \note This should always be performed before using the configuration
 *          struct to ensure that all values are initialized to known default
 *          settings.
 *
 * -# Adjust the configuration struct to request an input pin.
 *    \snippet qs_gpio_callback.c setup_gpio_2
 *
 * -# Configure GPIO pin with the initialized pin configuration struct.
 *    \snippet qs_gpio_callback.c setup_gpio_3
 *
 * -# Initialize callback function. This assigns the GPIO ISR handler address in
 *    interrupt vector table.
 *    \snippet qs_gpio_callback.c callback_init
 *
 * -# Register callback function.
 *    \snippet qs_gpio_callback.c callback_reg
 * -# Enable callback function. This enables the interrupt
 *    \snippet qs_gpio_callback.c callback_en 
 * 
 * \section asfdoc_samb_gpio_callback_use_case_use_main Use Case
 *
 * \subsection asfdoc_samb_gpio_callback_use_case_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_gpio_callback.c main
 *
 * \subsection asfdoc_samb_gpio_callback_use_case_flow Workflow
 * -# Infinite loop.
 *    \snippet qs_gpio_callback.c main
 */