/***************************************************************************//**
 * @file ccs811.h
 * @brief Driver for the Cambridge CMOS Sensors CCS811 gas and indoor air
 * quality sensor
 * @version 5.1.1
 *******************************************************************************
 * @section License
 * <b>Copyright 2016 Silicon Laboratories, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef __CCS811_H_
#define __CCS811_H_

#include <stdbool.h>

#include "ccs811_config.h"

 /**************************************************************************//**
 * @addtogroup CCS811
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @defgroup CCS811_Config_Settings CCS811 Configuration Settings
 * @{
 * @brief CCS811 configuration setting macro definitions
 ******************************************************************************/

#ifndef CCS811_CONFIG_FIRMWARE_UPDATE
  #define CCS811_CONFIG_FIRMWARE_UPDATE (0)        /**< Default value of firmware upgrade enable   */
#endif

#ifndef CCS811_CONFIG_I2C_BUS_TIMEOUT
  #define CCS811_CONFIG_I2C_BUS_TIMEOUT (1000)     /**< Default I2C bus timeout value              */
#endif

#ifndef CCS811_CONFIG_I2C_DEVICE
  #define CCS811_CONFIG_I2C_DEVICE (I2C0)          /**< Default I2C device to control the CCS811   */
#endif

#ifndef CCS811_CONFIG_I2C_BUS_ADDRESS
  #define CCS811_CONFIG_I2C_BUS_ADDRESS (0xB4)     /**< Default I2C bus address of the CCS811      */
#endif

#define CCS811_FIRMWARE_UPDATE        (CCS811_CONFIG_FIRMWARE_UPDATE)   /**< Enable or disable CCS811 firmware upgrade  */
#define CCS811_I2C_DEVICE             (CCS811_CONFIG_I2C_DEVICE)        /**< I2C device used to control the CCS811      */
#define CCS811_I2C_DEVICE_BUS_ADDRESS (CCS811_CONFIG_I2C_BUS_ADDRESS)   /**< I2C bus address of the CCS881              */
#define CCS811_I2C_DEVICE_BUS_TIMEOUT (CCS811_CONFIG_I2C_BUS_TIMEOUT)   /**< I2C bus timeout                            */
#define CCS811_HW_ID                   0x81                             /**< The hardware ID of the CCS881              */

/** @} { defgroup CCS811_Config_Settings }*/

/***************************************************************************//**
 * @defgroup CCS811_Error_Codes CCS811 Error Codes
 * @{
 * @brief CCS811 error code macro definitions
 ******************************************************************************/

#define CCS811_OK                            0x0000   /**< No errors                            */
#define CCS811_ERROR_APPLICATION_NOT_PRESENT 0x0001   /**< Application firmware is not present  */
#define CCS811_ERROR_NOT_IN_APPLICATION_MODE 0x0002   /**< The part is not in application mode  */
#define CCS811_ERROR_DRIVER_NOT_INITIALIZED  0x0003   /**< The driver is not initialized        */
#define CCS811_ERROR_I2C_TRANSACTION_FAILED  0x0004   /**< I2C transaction failed               */
#define CCS811_ERROR_INIT_FAILED             0x0005   /**< The initialization failed            */
#define CCS811_ERROR_FIRMWARE_UPDATE_FAILED  0x0006   /**< The firmware update was unsuccessful */

/** @} {end defgroup CCS811_Error_Codes} */

/***************************************************************************//**
 * @defgroup CCS811_I2C_Regs CCS811 I2C Registers
 * @{
 * @brief CCS811 I2C register macro definitions
 ******************************************************************************/

#define CCS811_ADDR_STATUS                   0x00 /**< Status register                                                                           */
#define CCS811_ADDR_MEASURE_MODE             0x01 /**< Measurement mode and conditions register                                                  */
#define CCS811_ADDR_ALG_RESULT_DATA          0x02 /**< Algorithm result                                                                          */
#define CCS811_ADDR_RAW_DATA                 0x03 /**< Raw ADC data values for resistance and current source used                                */
#define CCS811_ADDR_ENV_DATA                 0x05 /**< Temperature and Humidity data can be written to enable compensation                       */
#define CCS811_ADDR_NTC                      0x06 /**< Provides the voltage across the reference resistor and the voltage across the NTC resistor */
#define CCS811_ADDR_THRESHOLDS               0x10 /**< Thresholds for operation when interrupts are only generated when eCO2 ppm crosses a threshold */
#define CCS811_ADDR_HW_ID                    0x20 /**< Hardware ID                                                                               */
#define CCS811_ADDR_HW_VERSION               0x21 /**< Hardware Version                                                                          */
#define CCS811_ADDR_FW_BOOT_VERSION          0x23 /**< Firmware Boot Version                                                                     */
#define CCS811_ADDR_FW_APP_VERSION           0x24 /**< Firmware Application Version                                                              */
#define CCS811_ADDR_ERR_ID                   0xE0 /**< Error ID                                                                                  */
#define CCS811_ADDR_FW_ERASE                 0xF1 /**< Firmware erase                                                                            */
#define CCS811_ADDR_FW_PROGRAM               0xF2 /**< Firmware programming                                                                      */
#define CCS811_ADDR_FW_VERIFY                0xF3 /**< Firmware verification                                                                     */
#define CCS811_ADDR_APP_START                0xF4 /**< Application start                                                                         */
#define CCS811_ADDR_SW_RESET                 0xFF /**< Software reset                                                                            */

/** @} {end defgroup CCS811_I2C_Regs} */

/***************************************************************************//**
 * @defgroup CCS811_Meas_Mode_Reg CCS811 Measurement Mode Settings
 * @{
 * @brief CCS811 measurement mode setting macro definitions
 ******************************************************************************/

#define CCS811_MEASURE_MODE_DRIVE_MODE_SHIFT 4     /**< DRIVE_MODE field bit shift value                                                           */
#define CCS811_MEASURE_MODE_DRIVE_MODE_IDLE  0x00  /**< Idle mode, measurements are disabled                                                       */
#define CCS811_MEASURE_MODE_DRIVE_MODE_1SEC  0x10  /**< IAQ Mode 1, a measurement is performed every second                                        */
#define CCS811_MEASURE_MODE_DRIVE_MODE_10SEC 0x20  /**< IAQ Mode 2, a measurement is performed every 10 seconds                                    */
#define CCS811_MEASURE_MODE_DRIVE_MODE_60SEC 0x30  /**< IAQ Mode 3, a measurement is performed every 60 seconds                                    */
#define CCS811_MEASURE_MODE_DRIVE_MODE_RAW   0x40  /**< IAQ Mode 4, Raw Data Mode, a measurement is performed every 250ms for external algorithms  */
#define CCS811_MEASURE_MODE_INTERRUPT        0x08  /**< Interrupt generation enable                                                                */
#define CCS811_MEASURE_MODE_THRESH           0x04  /**< Enable interrupt when eCO2 level exceeds threshold                                         */

/** @} {end defgroup CCS811_Meas_Mode_Reg} */

/***************************************************************************//**
 * @defgroup CCS811_Functions CCS811 Functions
 * @{
 * @brief CCS811 driver and support functions
 ******************************************************************************/

uint32_t CCS811_init                 ( void );
uint32_t CCS811_deInit               ( void );
uint32_t CCS811_getHardwareID        ( uint8_t *hwID );
uint32_t CCS811_getStatus            ( uint8_t *status );
uint32_t CCS811_readMailbox          ( uint8_t id, uint8_t length, uint8_t *data );
uint32_t CCS811_startApplication     ( void );
uint32_t CCS811_softwareReset        ( void );
uint32_t CCS811_setMeasureMode       ( uint8_t measMode );
void     CCS811_dumpRegisters        ( void );

bool     CCS811_isDataAvailable      ( void );
uint32_t CCS811_getMeasurement       ( uint16_t *eco2, uint16_t *tvoc );
uint32_t CCS811_getRawData           ( uint16_t *current, uint16_t *rawData );
uint32_t CCS811_setEnvData           ( int32_t tempData, uint32_t rhData );

/** @} {end defgroup CCS811_Functions} */

/** @} {end addtogroup CCS811 */

#endif /* __CCS811_H_ */
