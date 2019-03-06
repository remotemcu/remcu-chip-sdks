/**************************************************************************//**
 * @file displayls013b7dh03config.h
 * @brief BRD4101B specific configuration for the display driver for
 *        the Sharp Memory LCD model LS013B7DH03.
 * @version 5.1.1
 ******************************************************************************
 * @section License
 * <b>Copyright 2016 Silicon Laboratories, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/


#ifndef DISPLAY_LS013B7DH03_CONFIG_H
#define DISPLAY_LS013B7DH03_CONFIG_H

#include "displayconfigapp.h"

/* Display device name. */
#define SHARP_MEMLCD_DEVICE_NAME   "Sharp LS013B7DH03 #1"


/* LCD and SPI GPIO pin connections on the BRD4101B. */
#define LCD_PORT_SCLK             (gpioPortB)  /* EFM_DISP_SCLK on PB11 */
#define LCD_PIN_SCLK              (11)
#define LCD_PORT_SI               (gpioPortA)  /* EFM_DISP_MOSI on PA0 */
#define LCD_PIN_SI                (0)
#define LCD_PORT_SCS              (gpioPortC)  /* EFM_DISP_CS on PC6 */
#define LCD_PIN_SCS               (6)

/* The EFM8 I/O-expander will take care of display EXTCOMIN toggling. */
/* The following two defines will achieve this.                       */
#define POLARITY_INVERSION_EXTCOMIN_PAL_AUTO_TOGGLE
#define POLARITY_INVERSION_EXTCOMIN_MANUAL

#endif /* DISPLAY_LS013B7DH03_CONFIG_H */
