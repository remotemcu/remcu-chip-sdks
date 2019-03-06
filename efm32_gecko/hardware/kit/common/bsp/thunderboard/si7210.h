/***************************************************************************//**
 * @file si7210.h
 * @brief Driver for the Silicon Labs Si7210 Hall Effect Sensor
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

#ifndef __SI7210_H_
#define __SI7210_H_

#include <stdint.h>
#include <stdbool.h>

#include "si7210_config.h"
#include "thunderboard/si7210_regs.h"

/***************************************************************************//**
 * @cond DOXYGEN_INCLUDE_HALL_EFFECT_SENSOR
 * @addtogroup Si7210
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @cond DOXYGEN_INCLUDE_HALL_EFFECT_SENSOR
 * @defgroup Si7210_Config_Settings Si7210 Configuration Settings
 * @{
 * @brief Si7210 configuration setting macro definitions
 ******************************************************************************/

#ifndef SI7210_CONFIG_I2C_DEVICE
  #define SI7210_CONFIG_I2C_DEVICE (I2C0)             /**< Default I2C device to control the Si7210 */
#endif

#ifndef SI7210_CONFIG_I2C_BUS_ADDRESS
  #define SI7210_CONFIG_I2C_BUS_ADDRESS (0x30)        /**< Default I2C address of the Si7210 */
#endif

#ifndef SI7210_CONFIG_DEVICE_ID
  #define SI7210_CONFIG_DEVICE_ID        0x11         /**< Default Device ID of the Si7210 */
#endif

#ifndef SI7210_CONFIG_GPIO_PORT_OUT1
  #define SI7210_CONFIG_GPIO_PORT_OUT1   gpioPortB    /**< Default port where the ALERT pin connected */
#endif

#ifndef SI7210_CONFIG_GPIO_PIN_OUT1
  #define SI7210_CONFIG_GPIO_PIN_OUT1    11           /**< Default pin where the ALERT pin connected */
#endif


#define SI7210_I2C_DEVICE                    ( SI7210_CONFIG_I2C_DEVICE )        /**< I2C device used to control the Si7210   */
#define SI7210_I2C_DEVICE_BUS_ADDRESS        ( SI7210_CONFIG_I2C_BUS_ADDRESS )   /**< I2C bus address                         */
#define SI7210_I2C_DEVICE_BUS_TIMEOUT        ( SI7210_CONFIG_I2C_BUS_TIMEOUT )   /**< I2C bus timeout                         */
#define SI7210_GPIO_PORT_OUT1                ( SI7210_CONFIG_GPIO_PORT_OUT1 )    /**< GPIO port where the ALERT pin connected */
#define SI7210_GPIO_PIN_OUT1                 ( SI7210_CONFIG_GPIO_PIN_OUT1 )     /**< GPIO pin where the ALERT pin connected  */
#define SI7210_DEVICE_ID                     ( SI7210_CONFIG_DEVICE_ID )         /**< Si7210 device ID                        */

/** @} {end defgroup Si7210_Config_Settings} */
/** @endcond {DOXYGEN_INCLUDE_HALL_EFFECT_SENSOR} */

/***************************************************************************//**
 * @cond DOXYGEN_INCLUDE_HALL_EFFECT_SENSOR
 * @defgroup Si7210_Error_Messages Si7210 Error Messages
 * @{
 * @brief Si7210 error message macro definitions
 ******************************************************************************/

#define SI7210_OK                            0        /**< No errors                               */
#define SI7210_ERROR_I2C_TRANSFER_FAILED     0x0001   /**< I2C transaction failed                  */
#define SI7210_ERROR_INVALID_DEVICE_ID       0x0002   /**< The device ID is invalid                */
#define SI7210_ERROR_CONFIG_INVALID_MODE     0x0003   /**< The chosen configuration is invalid     */
#define SI7210_ERROR_OTP_BUSY                0x0004   /**< The OTP memory is busy                  */
#define SI7210_ERROR_READ_TIMEOUT            0x0005   /**< Timeout occurred during read operation  */

/** @} {end defgroup Si7210_Error_Messages} */
/** @endcond {DOXYGEN_INCLUDE_HALL_EFFECT_SENSOR} */

/***************************************************************************//**
 * @cond DOXYGEN_INCLUDE_HALL_EFFECT_SENSOR
 * @defgroup Si7210_Config_Defines Si7210 Configuration Definitions
 * @{
 * @brief Si7210 configuration macro definitions
 ******************************************************************************/

#define SI7210_CONFIG_MODE_THRESHOLD         0x01     /**< Configure the device in Threshold mode  */
#define SI7210_CONFIG_MODE_MEASURE           0x02     /**< Configure the device in Measure mode    */

#define SI7210_CONFIG_SCALE_20mT             0x00     /**< Set full scale to 20mT                  */
#define SI7210_CONFIG_SCALE_200mT            0x01     /**< Set full scale to 200mT                 */

#define SI7210_CONFIG_POLARITY_OMNI          0x00     /**< Omnipolar field polarity                */
#define SI7210_CONFIG_POLARITY_NEG           0x01     /**< Negative field polarity                 */
#define SI7210_CONFIG_POLARITY_POS           0x02     /**< Positive field polarity                 */

#define SI7210_CONFIG_THRESHOLD_MIN          0.08f    /**< Minimum threshold value                 */
#define SI7210_CONFIG_THRESHOLD_MAX          19.2f    /**< Maximum threshold value                 */

/** @} {end defgroup Si7210_Config_Defines} */
/** @endcond {DOXYGEN_INCLUDE_HALL_EFFECT_SENSOR} */

/***************************************************************************//**
 * @cond DOXYGEN_INCLUDE_HALL_EFFECT_SENSOR
 * @defgroup Si7210_Typedefs Si7210 Type Definitions
 * @{
 * @brief Si7210 type definitions used by the driver
 ******************************************************************************/

typedef void * SI7210_Config;                         /**<  Configuration structure placeholder */
typedef void (*SI7210_IntCallback)(uint8_t level);    /**<  Interrupt callback function         */

/***************************************************************************//**
 * @brief
 *    Structure to configure the Si7210 in Measure mode
 *
 ******************************************************************************/
typedef struct __SI7210_ConfigMeasure {

   uint8_t  mode;            /**<  "Threshold" or "Measure" mode                   */
   uint8_t  scale;           /**<  20 mT or 200 mT full scale                      */
   uint32_t samplePeriod;    /**<  usec between each sample (if not continous)     */

} SI7210_ConfigMeasure;

/***************************************************************************//**
 * @brief
 *    Structure to configure the Si7210 in Threshold mode
 *
 ******************************************************************************/
typedef struct __SI7210_ConfigThreshold {

   uint8_t            mode;           /**<  "Threshold" or "Measure" mode                   */
   SI7210_IntCallback callback;       /**<  Interrupt callback function                     */
   float              threshold;      /**<  Decision point in mT                            */
   float              hysteresis;     /**<  Hysterisis in mT                                */
   uint8_t            polarity;       /**<  Omnipolar, negative or positive field polarity  */
   bool               outputInvert;   /**<  Output signal should be high to conserve power  */

} SI7210_ConfigThreshold;

/** @} {end defgroup Si7210_Typedefs} */
/** @endcond {DOXYGEN_INCLUDE_HALL_EFFECT_SENSOR} */

/***************************************************************************//**
 * @cond DOXYGEN_INCLUDE_HALL_EFFECT_SENSOR
 * @defgroup Si7210_Functions Si7210 Functions
 * @{
 * @brief Si7210 driver and support functions
 ******************************************************************************/

uint32_t SI7210_init         ( void );
void     SI7210_deInit       ( void );
uint32_t SI7210_config       ( SI7210_Config config );
uint32_t SI7210_measure      ( float *result );
uint32_t SI7210_suspend      ( void );

uint32_t SI7210_regRead      ( uint8_t addr, uint8_t *data );
uint32_t SI7210_regWrite     ( uint8_t addr, uint8_t data );
uint32_t SI7210_regSetBits   ( uint8_t addr, uint8_t mask );
uint32_t SI7210_regClearBits ( uint8_t addr, uint8_t mask );
uint32_t SI7210_regReadOTP   ( uint8_t otpAddr, uint8_t *otpData );

/** @} end defgroup Si7210_Functions */
/** @endcond {DOXYGEN_INCLUDE_HALL_EFFECT_SENSOR} */

/** @} end addtogroup Si7210 */
/** @endcond {DOXYGEN_INCLUDE_HALL_EFFECT_SENSOR} */

#endif /* __SI7210_H_ */
