/***************************************************************************//**
 * @file bmp_regs.h
 * @brief Register definitions for the BMP280 pressure sensor
 * @version 5.1.1
 *******************************************************************************
 * @section License
 * <b>Copyright 2016 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef __BMP_REGS_H_
#define __BMP_REGS_H_

/***************************************************************************//**
 * @addtogroup BMP
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @defgroup BMP_I2C_Regs BMP Barometric Sensor I2C Registers
 * @{
 * @brief BMP Barometric Sensor I2C register macro definitions
 ******************************************************************************/

#define BMP_REG_ADDR_ID              0xD0   /**< Chip ID register                      */
#define BMP_REG_ADDR_SOFTRESET       0xE0   /**< Soft reset register                   */
#define BMP_REG_ADDR_CTRL_MEAS       0xF4   /**< Measurement control register          */

#define BMP_REG_ADDR_TEMP_XLSB       0xFC   /**< Temperature output register extra LSB */
#define BMP_REG_ADDR_TEMP_LSB        0xFB   /**< Temperature output register LSB       */
#define BMP_REG_ADDR_TEMP_MSB        0xFA   /**< Temperature output register MSB       */
#define BMP_REG_ADDR_PRESS_XLSB      0xF9   /**< Pressure output register extra LSB    */
#define BMP_REG_ADDR_PRESS_LSB       0xF8   /**< Pressure output register LSB          */
#define BMP_REG_ADDR_PRESS_MSB       0xF7   /**< Pressure output register MSB          */
#define BMP_REG_ADDR_CONFIG          0xF5   /**< Device configuration register         */
#define BMP_REG_ADDR_CTRL_MEAS       0xF4   /**< Measurement control register          */
#define BMP_REG_ADDR_STATUS          0xF3   /**< Device status register                */
#define BMP_REG_ADDR_SOFTRESET       0xE0   /**< Soft reset register                   */
#define BMP_REG_ADDR_ID              0xD0   /**< Chip ID register                      */

#define BMP_REG16_ADDR_RESV          0xA0   /**< Reserved                              */
#define BMP_REG16_ADDR_DIG_P9        0x9E   /**< Calibration coefficient P9            */
#define BMP_REG16_ADDR_DIG_P8        0x9C   /**< Calibration coefficient P8            */
#define BMP_REG16_ADDR_DIG_P7        0x9A   /**< Calibration coefficient P7            */
#define BMP_REG16_ADDR_DIG_P6        0x98   /**< Calibration coefficient P6            */
#define BMP_REG16_ADDR_DIG_P5        0x96   /**< Calibration coefficient P5            */
#define BMP_REG16_ADDR_DIG_P4        0x94   /**< Calibration coefficient P4            */
#define BMP_REG16_ADDR_DIG_P3        0x92   /**< Calibration coefficient P3            */
#define BMP_REG16_ADDR_DIG_P2        0x90   /**< Calibration coefficient P2            */
#define BMP_REG16_ADDR_DIG_P1        0x8E   /**< Calibration coefficient P1            */
#define BMP_REG16_ADDR_DIG_T3        0x8C   /**< Calibration coefficient T3            */
#define BMP_REG16_ADDR_DIG_T2        0x8A   /**< Calibration coefficient T2            */
#define BMP_REG16_ADDR_DIG_T1        0x88   /**< Calibration coefficient T1            */

/** @} {end defgroup BMP_I2C_Regs} */

/** @} {end addtogroup BMP} */

#endif /* __BMP_REGS_H_ */
