/***************************************************************************//**
 * @file bmp.h
 * @brief Driver for the Bosch Sensortec BMP280 pressure sensor
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

#ifndef __BMP_H_
#define __BMP_H_

/**************************************************************************//**
 * @addtogroup BMP
 * @{
 ******************************************************************************/

#include "bmp_config.h"
#include "thunderboard/bmp_regs.h"

/***************************************************************************//**
 * @defgroup BMP_Config_Settings BMP Configuration Settings
 * @{
 * @brief BMP configuration setting macro definitions
 ******************************************************************************/

#ifndef BMP_CONFIG_I2C_DEVICE
  #define BMP_CONFIG_I2C_DEVICE       (I2C0)                      /**< Default I2C device used to control the BMP280 */
#endif

#ifndef BMP_CONFIG_I2C_BUS_ADDRESS
  #define BMP_CONFIG_I2C_BUS_ADDRESS  (0xEE)                      /**< Default I2C bus address of the BMP280         */
#endif

#define BMP_I2C_DEVICE             (BMP_CONFIG_I2C_DEVICE)        /**< I2C device used to control the BMP280         */
#define BMP_I2C_BUS_ADDRESS        (BMP_CONFIG_I2C_BUS_ADDRESS)   /**< I2C bus address                               */

#define BMP_DEVICE_ID_BMP280           0x58                       /**< Device ID of the BMP280 chip                  */

/** @} {end defgroup BMP_Config_Settings} */

/***************************************************************************//**
 * @defgroup BMP_Error_Messages BMP Error Codes
 * @{
 * @brief BMP error message macro definitions
 ******************************************************************************/

#define BMP_OK                             0x0000  /**< No errors                                        */
#define BMP_ERROR_DRIVER_NOT_INITIALIZED   0x0001  /**< The driver is not initialized                    */
#define BMP_ERROR_I2C_TRANSACTION_FAILED   0x0002  /**< I2C transaction failed                           */
#define BMP_ERROR_DEVICE_ID_MISMATCH       0x0003  /**< The device ID does not match the expected value  */

/** @} {end defgroup BMP_Error_Messages} */

/***************************************************************************//**
 * @defgroup BMP_Typedefs BMP Type Definitions
 * @{
 * @brief BMP280 type definitions used by the driver
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *    Structure to configure the BMP280 device
 ******************************************************************************/
typedef struct __BMP_Config {

   uint8_t oversampling;      /**< Oversampling value                         */
   uint8_t powerMode;         /**< SLEEP, FORCED or NORMAL power mode setting */
   uint8_t standbyTime;       /**< Standby time setting                       */

} BMP_Config;

/** @} {end defgroup BMP_Typedefs BMP} */

/***************************************************************************//**
 * @addtogroup BMP_Functions
 * @{
 ******************************************************************************/

uint32_t BMP_init             ( uint8_t *deviceId );
void     BMP_deInit           ( void );
uint32_t BMP_config           ( BMP_Config *cfg );
uint32_t BMP_getTemperature   ( float *temperature );
uint32_t BMP_getPressure      ( float *pressure );

/** @} {end addtogroup BMP_Functions} */

/** @} {end addtogroup BMP} */

#endif /* __BMP_H_ */
