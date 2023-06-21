/**
 * \file
 *
 * \brief Management of C42364A LCD Glass component.
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef C42364A_H_INCLUDED
#define C42364A_H_INCLUDED

#include "compiler.h"
#include "status_codes.h"
#include "c42364a_segmap.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup c42364a_display_group Atmel YMCC42364AAANDCL LCD Glass component
 *
 * This is a driver for Atmel YMCC42364AAANDCL LCD component.
 * This component is the custom LCD used for SAM4C-EK and SAM4L-EK.
 * This driver provides functions for initialization and control of the
 * LCD segments.
 *
 * \section dependencies Dependencies
 * This driver depends on the following modules:
 * - \ref group_sam_drivers_lcdca for Liquid Crystal Display (LCD) module.
 * - \ref group_sam_drivers_slcdc for Liquid Crystal Display (LCD) module.
 * @{
 */

/**
 * \name Circular Animation Shift Direction
 * @{
 */
/** Right Direction. */
#define C42364A_CSR_RIGHT       1
/** Left Direction. */
#define C42364A_CSR_LEFT          0
/** @} */

/**
 * \name Value for battery Icon setting
 * @{
 */
enum c42364a_battery_value {
	C42364A_BATTERY_NONE = 0,
	C42364A_BATTERY_ONE,
	C42364A_BATTERY_TWO,
	C42364A_BATTERY_THREE,
};
/** @} */

/**
 * \name Function Prototypes
 * @{
 */

/**
 * \brief Initialize the C42364A LCD Glass component.
 *
 * This function initializes the LCD driver to control the LCD glass.
 * It perform LCD module intialization according to the C42364A characteristics.
 *
 */
status_code_t c42364a_init(void);

/**
 * \brief Write string to c42364a lcd glass alphanumeric field.
 *
 * This function will write the input string to the alphanumeric field of the
 * lcd glass.
 *
 * \param data Pointer to the input string(max length is 7)
 */
void c42364a_write_alphanum_packet(const uint8_t *data);

/**
 * \brief Write string to c42048a lcd glass numeric field.
 *
 * This function will write the input string to the numeric field of the
 * lcd glass.
 *
 * \param data Pointer to the input string(max length is 4)
 */
void c42364a_write_num_packet(const uint8_t *data);

/**
 * \brief Show text on C42364A LCD glass alphanumeric field.
 *
 * This function will show text on the alphanumeric field of the LCD glass.
 *
 * \param data Pointer to the input string(max length is 7)
 */
void c42364a_show_text(const uint8_t *data);

/**
 * \brief Clear C42364A LCD glass alphanumeric field.
 *
 * This function will clear the alphanumeric field of the LCD glass.
 */
void c42364a_clear_text(void);

/**
 * \brief Clear a specific icon on the LCD glass.
 *
 * This function will clear a specific icon.
 *
 * \param icon_com  Pixel coordinate - COMx - of the icon.
 * \param icon_seg  Pixel coordinate - SEGy - of the icon.
 *
 * \note Use the icon define in header file.
 */
void c42364a_clear_icon(uint8_t icon_com, uint8_t icon_seg);

/**
 * \brief Show a specific icon on the LCD glass.
 *
 * This function will show a specific icon.
 *
 * \param icon_com  Pixel coordinate - COMx - of the icon.
 * \param icon_seg  Pixel coordinate - SEGy - of the icon.
 *
 * \note Use the icon define in header file.
 */
void c42364a_show_icon(uint8_t icon_com, uint8_t icon_seg);

/**
 * \brief Blink a specific icon on the LCD glass.
 *
 * This function will blink a specific icon.
 *
 * \param icon_com  Pixel coordinate - COMx - of the icon.
 * \param icon_seg  Pixel coordinate - SEGy - of the icon.
 *
 * \note Use the icon define in header file(with selected segments
 * blinking feature).
 */
void c42364a_blink_icon_start(uint8_t icon_com, uint8_t icon_seg);

/**
 * \brief Stop blink a specific icon on the LCD glass.
 *
 * This function will stop blink a specific icon.
 *
 * \param icon_com  Pixel coordinate - COMx - of the icon.
 * \param icon_seg  Pixel coordinate - SEGy - of the icon.
 *
 * \note Use the icon define in header file(with selected segments
 * blinking feature).
 */
void c42364a_blink_icon_stop(uint8_t icon_com, uint8_t icon_seg);

/**
 * \brief Blink the current screen content.
 *
 * This function will make the current screen blink.
 *
 */
void c42364a_blink_screen(void);

/**
 * \brief Disable all Blink.
 *
 * This function will disable all Blink content.
 *
 */
void c42364a_blink_disable(void);

/**
 * \brief Set the C42364A LCD glass contrast.
 *
 *  This function allows to adjust the contrast of the C42364A LCD glass.
 *
 *  \param contrast  -32 <= signed contrast value <= 31(Using LCDCA)
 *                                0 <= contrast value <= 15(Using SLCDC).
 */
void c42364a_set_contrast(int8_t contrast);

/**
 * \brief Start circular animation.
 *
 * This function start the circular animation.
 *
 * \param csr_dir Direction.
 * \param size Defines the size of the circular animation icon.
 * \param data Circular Shift Register Value.
 */
void c42364a_circular_animation_start(uint8_t csr_dir,
		uint8_t size, uint8_t data);

/**
 * \brief Stop circular animation.
 *
 *  This function stop the circular animation.
 */
void c42364a_circular_animation_stop(void);

/**
 * \brief Scrolling start.
 *
 * This function start the text scrolling.
 *
 * \param data Data string buffer.
 * \param length Data string length.
 */
void c42364a_text_scrolling_start(const uint8_t *data, uint32_t length);

/**
 * \brief Scrolling stop.
 *
 * This function stop the text scrolling.
 */
void c42364a_text_scrolling_stop(void);

/**
 * \brief Show all content of the LCD glass.
 *
 * This function sets all pixels and areas of the LCD glass C42364A.
 *
 */
void c42364a_show_all(void);

/**
 * \brief Clear all content of the LCD glass.
 *
 * This function clears all pixels and areas of the LCD glass C42364A.
 *
 */
void c42364a_clear_all(void);

/**
 * \brief Show a decimal numeric value to LCD glass.
 *
 * This function displays an int32 value to the LCD numeric field of the glass.
 *
 * \param value The int32_t value to be displayed
 *
 * \note The value range is [-19999,19999].
 */
void c42364a_show_numeric_dec(int32_t value);

/**
 * \brief Clear C42364A LCD glass numeric field and the three
 * C42364A_ICON_MINUS*** icons.
 *
 * This function will clear the numeric field of the LCD glass.
 */
void c42364a_clear_numeric_dec(void);

/**
 * \brief Show battery condition by the battery icons on the LCD glass.
 *
 * This function allows to Show battery condition by the battery icons
 * on the LCD glass..
 *
 * \param val The 0 to 3 value which show the battery condition.
 */
void c42364a_show_battery(enum c42364a_battery_value val);

/** @} */


/** @} */

#ifdef __cplusplus
}
#endif

/**
 * \page sam_component_c42364a_quick_start Quick Start Guide for the C42364A
 * LCD Glass component.
 *
 * This is the quick start guide for the \ref c42364a_display_group, with
 * step-by-step instructions on how to configure and use the driver for
 * a specific use case.The code examples can be copied into e.g the main
 * application loop or any other function that will need to control the
 * C42364A LCD Glass component module.
 *
 * \section c42364a_qs_use_cases Use cases
 * - \ref c42364a_basic
 *
 * \section c42364a_basic C42364A LCD Glass basic usage
 *
 * This use case will demonstrate how to initialize the C42364A LCD Glass
 * module.
 *
 *
 * \section c42364a_basic_setup Setup steps
 *
 * \subsection c42364a_basic_prereq Prerequisites
 *
 * This module requires the following driver
 * - \ref group_sam_drivers_lcdca
 *
 * \subsection c42364a_basic_setup_code
 *
 * Add this to the main loop or a setup function:
 * \code
	c42364a_init();
\endcode
 *
 * \subsection c42364a_basic_setup_workflow
 *
 * -# Initialize the c42364a module
 *  - \code c42364a_init(); \endcode
 *
 * \section c42364a_basic_usage Usage steps
 *
 * \subsection c42364a_basic_usage_code
 *
 * We can set all the contents by
 * \code
	c42364a_set_all();;
\endcode
 * Or we can clear all the contents by
 * \code
	c42364a_clear_all();;
\endcode
 *
 * We can use the basic show feature by
 * \code
	int32_t value = -12345;
	c42364a_show_icon(C42364A_ICON_ARM);
	c42364a_show_numeric_dec(value);
	c42364a_show_text("Welcome");
	c42364a_show_battery(c42364a_battery_two);
\endcode
 *
 * We can use the blink feature by
 * \code
	c42364a_blink_icon_start(C42364A_ICON_COLON);;
\endcode
 *
 * We can start/stop the circular animation feature by
 * \code
	 c42364a_circular_animation_start(C42364A_CSR_RIGHT, 7, 0x03);

	 c42364a_circular_animation_stop();
\endcode
 *
 * We can start/stop the text scrolling feature by
 * \code
	 uint8_t const scrolling_str[] = "C42364A Example  ";

	 c42364a_text_scrolling_start(scrolling_str,
	         strlen((char const *)scrolling_str));

	 c42364a_text_scrolling_stop();
\endcode
 */

#endif  /* C42364A_H_INCLUDED */
