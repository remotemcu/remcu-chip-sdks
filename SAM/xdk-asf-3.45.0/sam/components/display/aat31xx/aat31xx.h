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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef AAT31XX_H_INCLUDED
#define AAT31XX_H_INCLUDED

#include "compiler.h"
#include "conf_board.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/* The minimum, average and maximum brightness level values */
#ifdef CONF_BOARD_AAT3155
#define AAT31XX_MIN_BACKLIGHT_LEVEL           1
#define AAT31XX_AVG_BACKLIGHT_LEVEL           8
#define AAT31XX_MAX_BACKLIGHT_LEVEL           16
#endif
#ifdef CONF_BOARD_AAT3193
#define AAT31XX_MIN_BACKLIGHT_LEVEL           1
#define AAT31XX_AVG_BACKLIGHT_LEVEL           8
#define AAT31XX_MAX_BACKLIGHT_LEVEL           16
#endif
#ifdef CONF_BOARD_AAT3194
#define AAT31XX_MIN_BACKLIGHT_LEVEL           1
#define AAT31XX_AVG_BACKLIGHT_LEVEL           25
#define AAT31XX_MAX_BACKLIGHT_LEVEL           32
#endif

/* No component found */
#ifndef AAT31XX_MIN_BACKLIGHT_LEVEL
#warning Cannot configure AAT31XX. The component must be declared in conf_board.h first!
#define AAT31XX_MIN_BACKLIGHT_LEVEL           0
#define AAT31XX_AVG_BACKLIGHT_LEVEL           0
#define AAT31XX_MAX_BACKLIGHT_LEVEL           0
#endif

void aat31xx_set_backlight(uint32_t ul_level);
void aat31xx_disable_backlight(void);

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

#endif /* AAT31XX_H_INCLUDED */
