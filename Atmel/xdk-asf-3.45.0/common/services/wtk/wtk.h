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
#ifndef WTK_H
#define WTK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <win.h>
#include <sysfont.h>
#include <wtk_basic_frame.h>
#include <wtk_frame.h>
#include <wtk_button.h>
#include <wtk_check_box.h>
#include <wtk_radio_button.h>
#include <wtk_slider.h>
#include <wtk_label.h>
#include <wtk_progress_bar.h>
#include <wtk_icon.h>
#include <wtk_plot.h>
#include "conf_wtk.h"

/**
 * \ingroup gfx_group
 * \defgroup wtk_group Widget toolkit
 *
 * The Widget toolkit implements many common widgets for use on a graphical
 * display using the functionality of \ref win_group "Window system"
 * and \ref gfx_group "Graphics library".
 *
 * \image html WTK.jpg
 *
 * The following widgets are implemented:
 * - \ref wtk_basic_frame_group
 * - \ref wtk_button_group
 * - \ref wtk_check_box_group
 * - \ref wtk_frame_group
 * - \ref wtk_icon_group
 * - \ref wtk_plot_group
 * - \ref wtk_progress_bar_group
 * - \ref wtk_radio_button_group
 * - \ref wtk_slider_group
 * - \ref wtk_label_group
 *
 * \section wtk_dependencies_sec Dependencies
 * This component driver depends on the following modules:
 * - \ref win_group "Window system"
 * - \ref gfx_group "Graphics library"
 *
 * @{
 */

uint8_t wtk_rescale_value(uint8_t value, uint8_t from_scale, uint8_t to_scale);
void wtk_copy_string(char *dest, char const *source);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* WTK_H */
