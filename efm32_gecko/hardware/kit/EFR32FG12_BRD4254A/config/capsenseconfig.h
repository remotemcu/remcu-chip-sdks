/***************************************************************************//**
 * @file
 * @brief capsense configuration parameters.
 * @version 5.0.0
 *******************************************************************************
 * @section License
 * <b>Copyright 2017 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef CAPSENSCONFIG_H
#define CAPSENSCONFIG_H
#ifdef __cplusplus
extern "C" {
#endif

/* Use ACMP0 module for capsense */
#define ACMP_CAPSENSE                           ACMP0
#define ACMP_CAPSENSE_CMUCLOCK                  cmuClock_ACMP0
#define PRS_CH_CTRL_SOURCESEL_ACMP_CAPSENSE     PRS_CH_CTRL_SOURCESEL_ACMP0
#define PRS_CH_CTRL_SIGSEL_ACMPOUT_CAPSENSE     PRS_CH_CTRL_SIGSEL_ACMP0OUT

/* Touch buttons are connected to PC0, PC1, PC2 and PC3.
 *
 * Pin  | APORT Channel (for ACMP0)
 * -------------------------
 * PC0  | APORT1XCH0 or APORT2YCH0
 * PC1  | APORT1YCH1 or APORT2XCH1
 * PC2  | APORT1XCH2 or APORT2YCH2
 * PC3  | APORT1YCH3 or APORT2XCH3
 *
 */
#define CAPSENSE_CHANNELS       { acmpInputAPORT1XCH0, acmpInputAPORT2XCH1, acmpInputAPORT1XCH2, acmpInputAPORT2XCH3 }
#define BUTTON0_CHANNEL         0             /**< Button 0 channel */
#define BUTTON1_CHANNEL         3             /**< Button 1 channel */
#define ACMP_CHANNELS           4             /**< Number of channels in use for capsense */
#define NUM_SLIDER_CHANNELS     4             /**< The kit has a slider with 4 pads */

#ifdef __cplusplus
}
#endif
#endif /* CAPSENSCONFIG_H */
