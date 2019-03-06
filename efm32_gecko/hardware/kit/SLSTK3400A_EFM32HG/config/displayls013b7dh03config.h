/**************************************************************************//**
 * @file displayls013b7dh03config.h
 * @brief SLSTK3400A specific configuration for the display driver for
 *        the Sharp Memory LCD model LS013B7DH03.
 * @version 5.1.1
 ******************************************************************************
 * @section License
 * <b>Copyright 2015 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/


#ifndef __SILICON_LABS_DISPLAY_LS013B7DH03_CONFIG_H_
#define __SILICON_LABS_DISPLAY_LS013B7DH03_CONFIG_H_

#include "displayconfigapp.h"

/* Display device name. */
#define SHARP_MEMLCD_DEVICE_NAME   "Sharp LS013B7DH03 #1"


/* LCD and SPI GPIO pin connections on the STK. */
#define LCD_PORT_SCLK             (4)  /* = gpioPortE */
#define LCD_PIN_SCLK             (12)
#define LCD_PORT_SI               (4)  /* = gpioPortE */
#define LCD_PIN_SI               (10)
#define LCD_PORT_SCS              (0)  /* = gpioPortA */
#define LCD_PIN_SCS              (10)
#define LCD_PORT_EXTCOMIN         (5)  /* = gpioPortF */
#define LCD_PIN_EXTCOMIN          (3)
#define LCD_PORT_DISP_SEL         (0)  /* = gpioPortA */
#define LCD_PIN_DISP_SEL          (8)

/* PRS settings for polarity inversion extcomin auto toggle.  */
#define LCD_AUTO_TOGGLE_PRS_CH    (0)  /* PRS channel 0.      */
#define LCD_AUTO_TOGGLE_PRS_ROUTE_LOC   PRS_ROUTE_LOCATION_LOC1
#define LCD_AUTO_TOGGLE_PRS_ROUTE_PEN   PRS_ROUTE_CH0PEN

/*
 * Select how LCD polarity inversion should be handled:
 *
 * If POLARITY_INVERSION_EXTCOMIN is defined,
 * the polarity inversion is armed for every rising edge of the EXTCOMIN
 * pin. The actual polarity inversion is triggered at the next transision of
 * SCS. This mode is recommended because it causes less CPU and SPI load than
 * the alternative mode, see below.
 * If POLARITY_INVERSION_EXTCOMIN is undefined,
 * the polarity inversion is toggled by sending an SPI command. This mode
 * causes more CPU and SPI load than using the EXTCOMIN pin mode.
 */
#define POLARITY_INVERSION_EXTCOMIN

/* Define POLARITY_INVERSION_EXTCOMIN_PAL_AUTO_TOGGLE if you want the PAL
 * (Platform Abstraction Layer interface) to automatically toggle the EXTCOMIN
 *  pin.
 * If the PAL_TIMER_REPEAT function is defined the EXTCOMIN toggling is handled
 * by a timer repeat system, therefore we must undefine
 * POLARITY_INVERSION_EXTCOMIN_PAL_AUTO_TOGGLE;
 */
#ifndef PAL_TIMER_REPEAT_FUNCTION
  #define POLARITY_INVERSION_EXTCOMIN_PAL_AUTO_TOGGLE
#endif

/* Frequency of LCD polarity inversion. */
#define LS013B7DH03_POLARITY_INVERSION_FREQUENCY (64)

#endif /* __SILICON_LABS_DISPLAY_LS013B7DH03_CONFIG_H_ */
