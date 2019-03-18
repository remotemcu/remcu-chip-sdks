/**
 * \file
 *
 * \brief SAM4C-EK board init.
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

#include "compiler.h"
#include "board.h"
#include "conf_board.h"
#include "conf_clock.h"
#include "ioport.h"

/**
 * \addtogroup sam4c_ek_group
 * @{
 */

/**
 * \brief Set peripheral mode for IOPORT pins.
 * It will configure port mode and disable pin mode (but enable peripheral).
 * \param port IOPORT port to configure
 * \param masks IOPORT pin masks to configure
 * \param mode Mode masks to configure for the specified pin (\ref ioport_modes)
 */
#define ioport_set_port_peripheral_mode(port, masks, mode) \
	do {\
		ioport_set_port_mode(port, masks, mode);\
		ioport_disable_port(port, masks);\
	} while (0)

/**
 * \brief Set peripheral mode for one single IOPORT pin.
 * It will configure port mode and disable pin mode (but enable peripheral).
 * \param pin IOPORT pin to configure
 * \param mode Mode masks to configure for the specified pin (\ref ioport_modes)
 */
#define ioport_set_pin_peripheral_mode(pin, mode) \
	do {\
		ioport_set_pin_mode(pin, mode);\
		ioport_disable_pin(pin);\
	} while (0)

/**
 * \brief Set input mode for one single IOPORT pin.
 * It will configure port mode and disable pin mode (but enable peripheral).
 * \param pin IOPORT pin to configure
 * \param mode Mode masks to configure for the specified pin (\ref ioport_modes)
 * \param sense Sense for interrupt detection (\ref ioport_sense)
 */
#define ioport_set_pin_input_mode(pin, mode, sense) \
	do {\
		ioport_set_pin_dir(pin, IOPORT_DIR_INPUT);\
		ioport_set_pin_mode(pin, mode);\
		ioport_set_pin_sense_mode(pin, sense);\
	} while (0)

void board_init(void)
{
#ifndef CONF_BOARD_KEEP_WATCHDOG_AT_INIT
	/* Disable the watchdog */
	WDT->WDT_MR = WDT_MR_WDDIS;
#endif

	/* GPIO has been deprecated, the old code just keeps it for compatibility.
	 * In new designs IOPORT is used instead.
	 * Here IOPORT must be initialized for others to use before setting up IO.
	 */
	ioport_init();

#ifdef CONFIG_CPCLK_ENABLE
	/* Configure the pins connected to LEDs as output and set their
	 * default initial state to high (LEDs off).
	 */
	ioport_set_pin_dir(LED0_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED0_GPIO, LED0_INACTIVE_LEVEL);
	ioport_set_pin_dir(LED1_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED1_GPIO, LED0_INACTIVE_LEVEL);
	ioport_set_pin_dir(LED2_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED2_GPIO, LED0_INACTIVE_LEVEL);
#else
#warning Please enable CONFIG_CPCLK_ENABLE in conf_clock.h to use LEDs (PIOC).
#endif

	/* Configure Push Button pins */
	ioport_set_pin_input_mode(GPIO_PUSH_BUTTON_1, GPIO_PUSH_BUTTON_1_FLAGS,
			GPIO_PUSH_BUTTON_1_SENSE);
	ioport_set_pin_input_mode(GPIO_PUSH_BUTTON_2, GPIO_PUSH_BUTTON_2_FLAGS,
			GPIO_PUSH_BUTTON_2_SENSE);

	/* Configure UART0 pins */
#ifdef CONF_BOARD_UART_CONSOLE
	ioport_set_pin_peripheral_mode(PIO_PB4_IDX, IOPORT_MODE_MUX_A);
	ioport_set_pin_peripheral_mode(PIO_PB5_IDX, IOPORT_MODE_MUX_A);
#endif

	/* Configure LCD backlight */
#ifdef CONF_BOARD_BL
	ioport_set_pin_dir(LCD_BL_GPIO, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LCD_BL_GPIO, LCD_BL_INACTIVE_LEVEL);
#endif

	/* Configure PWM LED pins */
#ifdef CONF_BOARD_PWM_LED0
	/* Configure PWM LED0 pin */
	ioport_set_pin_peripheral_mode(PIN_PWM_LED0_GPIO, PIN_PWM_LED0_FLAGS);
#endif

#ifdef CONF_BOARD_PWM_LED1
	/* Configure PWM LED1 pin */
	ioport_set_pin_peripheral_mode(PIN_PWM_LED1_GPIO, PIN_PWM_LED1_FLAGS);
#endif

#ifdef CONF_BOARD_PWM_LED2
	/* Configure PWM LED2 pin */
	ioport_set_pin_peripheral_mode(PIN_PWM_LED2_GPIO, PIN_PWM_LED2_FLAGS);
#endif

	/* Configure SPI pins */
#ifdef CONF_BOARD_SPI0
	ioport_set_pin_peripheral_mode(SPI0_MISO_GPIO, SPI0_MISO_FLAGS);
	ioport_set_pin_peripheral_mode(SPI0_MOSI_GPIO, SPI0_MOSI_FLAGS);
	ioport_set_pin_peripheral_mode(SPI0_SPCK_GPIO, SPI0_SPCK_FLAGS);

#ifdef CONF_BOARD_SPI0_NPCS0
	ioport_set_pin_peripheral_mode(SPI0_NPCS0_GPIO, SPI0_NPCS0_FLAGS);
#endif
#endif

#ifdef CONF_BOARD_SPI1
	ioport_set_pin_peripheral_mode(SPI1_MISO_GPIO, SPI1_MISO_FLAGS);
	ioport_set_pin_peripheral_mode(SPI1_MOSI_GPIO, SPI1_MOSI_FLAGS);
	ioport_set_pin_peripheral_mode(SPI1_SPCK_GPIO, SPI1_SPCK_FLAGS);

#ifdef CONF_BOARD_SPI1_NPCS0
	ioport_set_pin_peripheral_mode(SPI1_NPCS0_GPIO, SPI1_NPCS0_FLAGS);
#endif
#endif
	/* Configure TWI pins */
#if defined(CONF_BOARD_TWI0) || defined(CONF_BOARD_AT30TSE)
	ioport_set_pin_peripheral_mode(TWIO_DATA_GPIO, TWIO_DATA_FLAG);
	ioport_set_pin_peripheral_mode(TWIO_CLK_GPIO, TWIO_CLK_FLAG);
#endif

#ifdef CONF_BOARD_TWI1
	ioport_set_pin_peripheral_mode(TWI1_DATA_GPIO, TWI1_DATA_FLAG);
	ioport_set_pin_peripheral_mode(TWI1_CLK_GPIO, TWI1_CLK_FLAG);
#endif
	/* Configure USART pins */
#ifdef CONF_BOARD_USART_RXD
	/* Configure USART RXD pin */
	ioport_set_pin_peripheral_mode(PIN_USART2_RXD_IDX,
			PIN_USART2_RXD_FLAGS);
#endif

#ifdef CONF_BOARD_USART_TXD
	/* Configure USART TXD pin */
	ioport_set_pin_peripheral_mode(PIN_USART2_TXD_IDX,
			PIN_USART2_TXD_FLAGS);
#endif

#ifdef CONF_BOARD_USART_CTS
	/* Configure USART CTS pin */
	ioport_set_pin_peripheral_mode(PIN_USART2_CTS_IDX,
			PIN_USART2_CTS_FLAGS);
#endif

#ifdef CONF_BOARD_USART_RTS
	/* Configure USART RTS pin */
	ioport_set_pin_peripheral_mode(PIN_USART2_RTS_IDX,
			PIN_USART2_RTS_FLAGS);
#endif

#ifdef CONF_BOARD_USART_SCK
	/* Configure USART synchronous communication SCK pin */
	ioport_set_pin_peripheral_mode(PIN_USART2_SCK_IDX,
			PIN_USART2_SCK_FLAGS);
#endif

#ifdef CONF_BOARD_TFDU4300_SD
	/* Configure IrDA transceiver shutdown pin */
	ioport_set_pin_dir(PIN_IRDA_SD_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIN_IRDA_SD_IDX, IOPORT_PIN_LEVEL_HIGH);
#endif

#ifdef CONF_BOARD_ADM3485_RE
	/* Configure RS485 transceiver RE pin */
	ioport_set_pin_dir(PIN_RE_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIN_RE_IDX, IOPORT_PIN_LEVEL_LOW);
#endif

#ifdef CONF_BOARD_ISO7816_RST
	/* Configure ISO7816 card reset pin */
	ioport_set_pin_dir(PIN_ISO7816_RST_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIN_ISO7816_RST_IDX, IOPORT_PIN_LEVEL_LOW);
#endif

#ifdef CONF_BOARD_ISO7816
	/* Configure ISO7816 interface TXD & SCK pin */
	ioport_set_pin_peripheral_mode(PIN_USART2_TXD_IDX, PIN_USART2_TXD_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_USART2_SCK_IDX, PIN_USART2_SCK_FLAGS);
#endif
	/* Configure ADC pins */
#ifdef CONF_BOARD_ADC
	/* TC TIOA configuration */
	ioport_set_pin_peripheral_mode(PIN_TC0_TIOA0,PIN_TC0_TIOA0_FLAGS);

	/* ADC Trigger configuration */
	ioport_set_pin_peripheral_mode(PINS_ADC_TRIG, PINS_ADC_TRIG_FLAG);
#endif
	/* Configure EBI pins */
}

/* @} */
