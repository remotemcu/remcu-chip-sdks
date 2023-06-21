/**
 * \file
 *
 * \brief Graphical Widget toolkit
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
#ifndef WTK_SLIDER_H
#define WTK_SLIDER_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup wtk_group
 *
 * \defgroup wtk_slider_group Slider widget
 * @{
 */

/**
 * \defgroup wtk_slider_options_group Slider widget options
 * These options can be ORed together to specify the behaviour of a
 * slider widget when creating it with \ref wtk_slider_create
 * @{
 */

/**
 * \name Slider widget command event configuration options.
 * For use with the option parameter of \ref wtk_slider_create
 * @{
 */

/** Never issue command events. (Default option) */
#define WTK_SLIDER_CMD_NONE             (0 << 0)
/** Issue command event whenever slider value is updated. */
#define WTK_SLIDER_CMD_MOVE             (1 << 0)
/** Issue command event whenever slider is released. */
#define WTK_SLIDER_CMD_RELEASE          (1 << 1)

/** @} */

/**
 * \name Slider widget orientation configuration options.
 * For use with the option parameter of \ref wtk_slider_create
 * @{
 */

/** Slider is horizontally oriented. (Default option) */
#define WTK_SLIDER_HORIZONTAL           (0 << 0)
/** Slider is vertically oriented. */
#define WTK_SLIDER_VERTICAL             (1 << 2)

/** @} */

/**
 * \name Slider widget invert configuration options.
 * For use with the option parameter of \ref wtk_slider_create
 * @{
 */
 
/** Slider value is inverted. */
#define WTK_SLIDER_INVERT               (1 << 3)

/** @} */

/** @} */

struct wtk_slider;

struct wtk_slider *wtk_slider_create(struct win_window *parent,
		struct win_area const *area, uint8_t maximum, uint8_t value,
		uint8_t option, win_command_t command_data);
struct win_window *wtk_slider_as_child(struct wtk_slider *slider);
win_command_t wtk_slider_get_command(struct wtk_slider *slider);
bool wtk_slider_is_moving(struct wtk_slider const *slider);
uint8_t wtk_slider_get_value(struct wtk_slider const *slider);
bool wtk_slider_set_value(struct wtk_slider *slider, uint8_t value);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
