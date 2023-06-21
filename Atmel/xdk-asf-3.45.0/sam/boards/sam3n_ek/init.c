/**
 * \file
 *
 * \brief SAM3N-EK board init.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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
#include "gpio.h"
#include "ioport.h"

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

	/* Configure LED pins */
	gpio_configure_pin(LED0_GPIO, LED0_FLAGS);
	gpio_configure_pin(LED1_GPIO, LED1_FLAGS);

	/* Configure Push Button pins */
	gpio_configure_pin(GPIO_PUSH_BUTTON_1, GPIO_PUSH_BUTTON_1_FLAGS);
	gpio_configure_pin(GPIO_PUSH_BUTTON_2, GPIO_PUSH_BUTTON_2_FLAGS);

#ifdef CONF_BOARD_UART_CONSOLE
	/* Configure UART pins */
	gpio_configure_group(PINS_UART0_PIO, PINS_UART0, PINS_UART0_FLAGS);
#endif

	/* Configure ADC example pins */
#ifdef CONF_BOARD_ADC
	/* TC TIOA configuration */
	gpio_configure_pin(PIN_TC0_TIOA0,PIN_TC0_TIOA0_FLAGS);

	/* ADC Trigger configuration */
	gpio_configure_pin(PINS_ADC_TRIG, PINS_ADC_TRIG_FLAG);
#endif

#ifdef CONF_BOARD_PWM_LED0
	/* Configure PWM LED0 pin */
	gpio_configure_pin(PIN_PWM_LED0_GPIO, PIN_PWM_LED0_FLAGS);
#endif

#ifdef CONF_BOARD_PWM_LED1
	/* Configure PWM LED1 pin */
	gpio_configure_pin(PIN_PWM_LED1_GPIO, PIN_PWM_LED1_FLAGS);
#endif

#ifdef CONF_BOARD_TWI0
		gpio_configure_pin(TWI0_DATA_GPIO, TWI0_DATA_FLAGS);
		gpio_configure_pin(TWI0_CLK_GPIO, TWI0_CLK_FLAGS);
#endif
	
#ifdef CONF_BOARD_TWI1
		gpio_configure_pin(TWI1_DATA_GPIO, TWI1_DATA_FLAGS);
		gpio_configure_pin(TWI1_CLK_GPIO, TWI1_CLK_FLAGS);
#endif

	/* Configure SPI pins */
#if (defined CONF_BOARD_SPI) || (defined CONF_BOARD_SD_MMC_SPI)
	gpio_configure_pin(SPI_MISO_GPIO, SPI_MISO_FLAGS);
	gpio_configure_pin(SPI_MOSI_GPIO, SPI_MOSI_FLAGS);
	gpio_configure_pin(SPI_SPCK_GPIO, SPI_SPCK_FLAGS);

	/**
	 * For NPCS 1, 2, and 3, different PINs can be used to access the same NPCS line.
	 * Depending on the application requirements, the default PIN may not be available.
	 * Hence a different PIN should be selected using the CONF_BOARD_SPI_NPCS_GPIO and
	 * CONF_BOARD_SPI_NPCS_FLAGS macros.
	 */

	#ifdef CONF_BOARD_SD_MMC_SPI
		gpio_configure_pin(SPI_NPCS0_GPIO, SPI_NPCS0_FLAGS);
		/* Configure SD/MMC card detect pin */
		gpio_configure_pin(SD_MMC_0_CD_GPIO, SD_MMC_0_CD_FLAGS);
	#endif

	#ifdef CONF_BOARD_SPI_NPCS1
		#if defined(CONF_BOARD_SPI_NPCS1_GPIO) && defined(CONF_BOARD_SPI_NPCS1_FLAGS)
			gpio_configure_pin(CONF_BOARD_SPI_NPCS1_GPIO, CONF_BOARD_SPI_NPCS1_FLAGS);
		#else
			gpio_configure_pin(SPI_NPCS1_PA31_GPIO, SPI_NPCS1_PA31_FLAGS);
		#endif
	#endif

	#ifdef CONF_BOARD_SPI_NPCS2
		#if defined(CONF_BOARD_SPI_NPCS2_GPIO) && defined(CONF_BOARD_SPI_NPCS2_FLAGS)
			gpio_configure_pin(CONF_BOARD_SPI_NPCS2_GPIO, CONF_BOARD_SPI_NPCS2_FLAGS);
		#else
			gpio_configure_pin(SPI_NPCS2_PA30_GPIO, SPI_NPCS2_PA30_FLAGS);
		#endif
	#endif

	#ifdef CONF_BOARD_SPI_NPCS3
		#if defined(CONF_BOARD_SPI_NPCS3_GPIO) && defined(CONF_BOARD_SPI_NPCS3_FLAGS)
			gpio_configure_pin(CONF_BOARD_SPI_NPCS3_GPIO, CONF_BOARD_SPI_NPCS3_FLAGS);
		#else
			gpio_configure_pin(SPI_NPCS3_PA22_GPIO, SPI_NPCS3_PA22_FLAGS);
		#endif
	#endif
#endif

#ifdef CONF_BOARD_USART_RXD
	/* Configure USART RXD pin */
	gpio_configure_pin(PIN_USART0_RXD_IDX, PIN_USART0_RXD_FLAGS);
#endif

#ifdef CONF_BOARD_USART_TXD
	/* Configure USART TXD pin */
	gpio_configure_pin(PIN_USART0_TXD_IDX, PIN_USART0_TXD_FLAGS);
#endif

#ifdef CONF_BOARD_USART_CTS
	/* Configure USART CTS pin */
	gpio_configure_pin(PIN_USART0_CTS_IDX, PIN_USART0_CTS_FLAGS);
#endif

#ifdef CONF_BOARD_USART_RTS
	/* Configure USART RTS pin */
	gpio_configure_pin(PIN_USART0_RTS_IDX, PIN_USART0_RTS_FLAGS);
#endif

#ifdef CONF_BOARD_USART_SCK
	/* Configure USART synchronous communication SCK pin */
	gpio_configure_pin(PIN_USART0_SCK_IDX, PIN_USART0_SCK_FLAGS);
#endif

#ifdef CONF_BOARD_TFDU4300_SD
	/* Configure IrDA transceiver shutdown pin */
	gpio_configure_pin(PIN_IRDA_SD_IDX, PIN_IRDA_SD_FLAGS);
	gpio_set_pin_low(PIN_IRDA_SD_IDX);
#endif

#ifdef CONF_BOARD_ADM3485_RE
	/* Configure RS485 transceiver RE pin */
	gpio_configure_pin(PIN_RE_IDX, PIN_RE_FLAGS);
	gpio_set_pin_low(PIN_RE_IDX);
#endif

#ifdef CONF_BOARD_ILI9225
	/* Configure SPI LCD control pin */
	gpio_configure_pin(SPI_MISO_GPIO, SPI_MISO_FLAGS);
	gpio_configure_pin(SPI_MOSI_GPIO, SPI_MOSI_FLAGS);
	gpio_configure_pin(SPI_SPCK_GPIO, SPI_SPCK_FLAGS);
	gpio_configure_pin(SPI_NPCS2_PA30_GPIO, SPI_NPCS2_PA30_FLAGS);
	gpio_configure_pin(BOARD_ILI9225_RS_GPIO, BOARD_ILI9225_RS_FLAGS);
	gpio_configure_pin(BOARD_ILI9225_RSTN_GPIO, BOARD_ILI9225_RSTN_FLAGS);
#endif

#ifdef CONF_BOARD_AAT3193
	/* Configure Backlight control pin */
	gpio_configure_pin(BOARD_AAT31XX_SET_GPIO, BOARD_AAT31XX_SET_FLAGS);
#endif

#ifdef CONF_BOARD_MMA7341L
	/* Configure MMA7341L mode set control pin */
	gpio_configure_pin(PIN_MMA7341L_MODE, PIN_MMA7341L_MODE_FLAG);
	/* Configure MMA7341L x,y,z axis output voltage pin */
	gpio_configure_pin(PIN_MMA7341L_X_AXIS, PIN_MMA7341L_X_AXIS_FLAG);
	gpio_configure_pin(PIN_MMA7341L_Y_AXIS, PIN_MMA7341L_Y_AXIS_FLAG);
	gpio_configure_pin(PIN_MMA7341L_Z_AXIS, PIN_MMA7341L_Z_AXIS_FLAG);
#endif

#ifdef CONF_BOARD_ISO7816_RST
	/* Configure ISO7816 card reset pin */
	gpio_configure_pin(PIN_ISO7816_RST_IDX, PIN_ISO7816_RST_FLAG);
#endif

#ifdef CONF_BOARD_ISO7816
	/* Configure ISO7816 interface TXD & SCK pin */
	gpio_configure_pin(PIN_USART0_TXD_IDX, PIN_USART0_TXD_FLAGS);
	gpio_configure_pin(PIN_USART0_SCK_IDX, PIN_USART0_SCK_FLAGS);
#endif
}
