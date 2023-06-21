/**
 * \file
 *
 * \brief API driver for component aat31xx.
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

/**
 * \defgroup aat31xx_display_group Display - AAT31XX Controller
 *
 * Low-level driver for the AAT31XX LCD backlight controller. This driver provides access to the main
 * features of the AAT31XX controller.
 *
 * \{
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "board.h"
#include "ioport.h"
#include "aat31xx.h"
#include "conf_aat31xx.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

#define DELAY_PULSE      (0x18u)
#define DELAY_ENABLE     (0x20000u)
#define DELAY_DISABLE    (0x20000u)

/**
 * \brief Set the LCD backlight level.
 *
 * \param ul_level backlight level.
 *
 * \note pin BOARD_AAT31XX_SET_GPIO must be configured before calling aat31xx_set_backlight.
 */
void aat31xx_set_backlight(uint32_t ul_level)
{
	volatile uint32_t ul_delay;
	uint32_t i;

#ifdef CONF_BOARD_AAT3155
	ul_level = AAT31XX_MAX_BACKLIGHT_LEVEL - ul_level + 1;
#endif

#ifdef CONF_BOARD_AAT3193
	ul_level = AAT31XX_MAX_BACKLIGHT_LEVEL - ul_level + 1;
#endif

	/* Ensure valid level */
	ul_level = (ul_level > AAT31XX_MAX_BACKLIGHT_LEVEL) ? AAT31XX_MAX_BACKLIGHT_LEVEL : ul_level;
	ul_level = (ul_level < AAT31XX_MIN_BACKLIGHT_LEVEL) ? AAT31XX_MIN_BACKLIGHT_LEVEL : ul_level;

	/* Set new backlight level */
	for (i = 0; i < ul_level; i++) {
		ioport_set_pin_level(BOARD_AAT31XX_SET_GPIO, IOPORT_PIN_LEVEL_LOW);
		ul_delay = DELAY_PULSE;
		while (ul_delay--) {
		}

		ioport_set_pin_level(BOARD_AAT31XX_SET_GPIO, IOPORT_PIN_LEVEL_HIGH);

		ul_delay = DELAY_PULSE;
		while (ul_delay--) {
		}
	}

	ul_delay = DELAY_ENABLE;
	while (ul_delay--) {
	}
}

/**
 * \brief Switch off backlight.
 */
void aat31xx_disable_backlight(void)
{
	volatile uint32_t ul_delay;

	ioport_set_pin_level(BOARD_AAT31XX_SET_GPIO, IOPORT_PIN_LEVEL_LOW);

	ul_delay = DELAY_DISABLE;
	while (ul_delay--) {
	}
}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \}
 */
