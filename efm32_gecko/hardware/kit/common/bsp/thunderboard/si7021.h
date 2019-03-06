/***************************************************************************//**
 * @file si7021.h
 * @brief Driver for the Si7021 I2C Humidity and Temperature Sensor
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

#ifndef __SI7021_H_
#define __SI7021_H_

#include <stdlib.h>
#include <stdint.h>
#include "si7021_config.h"

/***************************************************************************//**
 * @addtogroup Si7021
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @defgroup SI7021_Config_Settings Si7021 Configuration Settings
 * @{
 * @brief Si7021 configuration setting macro definitions
 ******************************************************************************/

#ifndef SI7021_CONFIG_I2C_DEVICE
#define SI7021_CONFIG_I2C_DEVICE       (I2C0)                           /**< Default I2C device                      */
#endif

#ifndef SI7021_CONFIG_I2C_BUS_ADDRESS
#define SI7021_CONFIG_I2C_BUS_ADDRESS  0x40                             /**< Default I2C bus address of the Si7021   */
#endif

#ifndef SI7021_CONFIG_DEVICE_ID
#define SI7021_CONFIG_DEVICE_ID        0x21                             /**< Default device ID of the Si7021         */
#endif

#define SI7021_I2C_DEVICE              SI7021_CONFIG_I2C_DEVICE         /**< I2C device used to control the Si7021   */
#define SI7021_I2C_BUS_ADDRESS         SI7021_CONFIG_I2C_BUS_ADDRESS    /**< I2C bus address                         */
#define SI7021_DEVICE_ID               SI7021_CONFIG_DEVICE_ID          /**< Si7021 device ID                        */

/** @} {end defgroup SI7021_Config_Settings} */

/***************************************************************************//**
 * @defgroup SI7021_Error_Messages Si7021 Error Messages
 * @{
 * @brief Si7021 error message macro definitions
 ******************************************************************************/

#define SI7021_OK                             0       /**< No errors                   */
#define SI7021_ERROR_I2C_TRANSFER_NACK        0x0001  /**< No acknowledgement received */
#define SI7021_ERROR_I2C_TRANSFER_FAILED      0x0002  /**< I2C transaction failed      */
#define SI7021_ERROR_INVALID_DEVICE_ID        0x0003  /**< The device ID is invalid    */
#define SI7021_ERROR_TIMEOUT                  0x0004  /**< Timeout occurred            */

/** @} {end defgroup SI7021_Error_Messages} */

/***************************************************************************//**
 * @defgroup SI7021_Commands Si7021 Commands
 * @{
 * @brief Si7021 command macro definitions
 ******************************************************************************/

#define SI7021_CMD_MEASURE_RH            0xE5            /**< Measure Relative Humidity, Hold Master Mode */
#define SI7021_CMD_MEASURE_RH_NO_HOLD    0xF5            /**< Measure Relative Humidity, No Hold Master Mode */
#define SI7021_CMD_MEASURE_TEMP          0xE3            /**< Measure Temperature, Hold Master Mode */
#define SI7021_CMD_MEASURE_TEMP_NO_HOLD  0xF3            /**< Measure Temperature, No Hold Master Mode */
#define SI7021_CMD_READ_TEMP             0xE0            /**< Read Temperature Value from Previous RH Measurement */
#define SI7021_CMD_RESET                 0xFE            /**< Reset */
#define SI7021_CMD_WRITE_USER_REG1       0xE6            /**< Write RH/T User Register 1 */
#define SI7021_CMD_READ_USER_REG1        0xE7            /**< Read RH/T User Register 1 */
#define SI7021_CMD_WRITE_HEATER_CTRL     0x51            /**< Write Heater Control Register */
#define SI7021_CMD_READ_HEATER_CTRL      0x11            /**< Read Heater Control Register */
#define SI7021_CMD_READ_ID_BYTE1         {0xFA, 0x0F}    /**< Read Electronic ID 1st Byte */
#define SI7021_CMD_READ_ID_BYTE2         {0xFC, 0xC9}    /**< Read Electronic ID 2nd Byte */
#define SI7021_CMD_READ_FW_REV           {0x84, 0xB8}    /**< Read Firmware Revision */

/** @} {end defgroup SI7021_Commands} */

/***************************************************************************//**
 * @defgroup Si7021_Functions Si7021 Functions
 * @{
 * @brief Si7021 driver and support functions
 ******************************************************************************/

uint32_t SI7021_init     ( void );
void     SI7021_deInit   ( void );
uint32_t SI7021_measure  ( uint32_t *rhData, int32_t *tData );
uint32_t SI7021_getFwRev ( uint8_t *fwRev );

uint32_t SI7021_cmdWrite ( uint8_t *cmd, size_t cmdLen, uint8_t *data,   size_t dataLen );
uint32_t SI7021_cmdRead  ( uint8_t *cmd, size_t cmdLen, uint8_t *result, size_t resultLen );

/** @} {end defgroup Si7021_Functions} */

/** @} {end addtogroup Si7021} */

#endif /* __SI7021_H_ */
