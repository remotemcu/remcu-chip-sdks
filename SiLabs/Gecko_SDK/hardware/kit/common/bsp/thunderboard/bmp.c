/***************************************************************************//**
 * @file bmp.c
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

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "thunderboard/bmp.h"
#include "thunderboard/board.h"
#include "thunderboard/util.h"
#include "i2cspm.h"

#include "thunderboard/bosch/BMP280_Driver/bmp280.h"

/***************************************************************************//**
 * @defgroup BMP BMP - Barometric Pressure Sensor
 * @{
 * @brief Driver for the Bosch Sensortec BMP280 pressure sensor
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/****************************************************************************/
/* Local Function Prototypes                                                */
/****************************************************************************/
static int8_t  i2cBusRead   ( uint8_t devAddr, uint8_t regAddr, uint8_t *regData, uint8_t count );
static int8_t  i2cBusWrite  ( uint8_t devAddr, uint8_t regAddr, uint8_t *regData, uint8_t count );
static uint8_t readRegister ( uint8_t addr );


/***************************************************************************//**
 * Local Variables
 ******************************************************************************/
static uint8_t bmpDeviceId;       /* The device ID of the connected chip  */
static uint8_t bmp280PowerMode;   /* The actual power mode of the BMP280  */
static struct  bmp280_t bmp280;   /* Structure to hold BMP280 driver data */

/** @endcond DO_NOT_INCLUDE_WITH_DOXYGEN */

/***************************************************************************//**
 * @defgroup BMP_Functions BMP Functions
 * @{
 * @brief BMP driver and support functions
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *    Initializes the barometric pressure sensor chip
 *
 * @param[out] deviceId
 *    The device ID of the connected chip
 *
 * @return
 *    Returns zero on OK, non-zero otherwise
 ******************************************************************************/
uint32_t BMP_init( uint8_t *deviceId )
{

   int result;

   /* Enable power to the enviromental sensor group */
   BOARD_envSensEnable( true );

   /* The device needs 2 ms startup time */
   UTIL_delay( 2 );

   /* Read device ID to determine if we have a BMP280 connected */
   bmpDeviceId = readRegister( BMP_REG_ADDR_ID );

   if( bmpDeviceId != BMP_DEVICE_ID_BMP280 ) {
      return BMP_ERROR_DEVICE_ID_MISMATCH;
   }

   bmp280.bus_write  = i2cBusWrite;
   bmp280.bus_read   = i2cBusRead;
   bmp280.dev_addr   = BMP_I2C_BUS_ADDRESS;
   bmp280.delay_msec = UTIL_delay;

   result = bmp280_init( &bmp280 );

   if( result != BMP_OK ) {
      return result;
   }

   result = bmp280_set_power_mode( BMP280_FORCED_MODE );

   if( result != BMP_OK ) {
      return result;
   }

   result = bmp280_set_work_mode( BMP280_ULTRA_HIGH_RESOLUTION_MODE );

   if( result != BMP_OK ) {
      return result;
   }

   bmp280PowerMode = BMP280_FORCED_MODE;

   *deviceId = bmpDeviceId;

   return BMP_OK;

}

/***************************************************************************//**
 * @brief
 *    De-initializes the barometric pressure module
 *
 * @return
 *    None
 ******************************************************************************/
void BMP_deInit( void )
{
   bmp280_set_power_mode( BMP280_SLEEP_MODE );
   return;
}

/***************************************************************************//**
 * @brief
 *    Configure the barometric pressure sensor
 *
 * @param[in] cfg
 *    Structure, which holds the configuration parameters
 *
 * @return
 *    Returns zero on OK, non-zero otherwise
 ******************************************************************************/
uint32_t BMP_config( BMP_Config *cfg )
{

   uint32_t result;

   result = 0;

   result += bmp280_set_work_mode( cfg->oversampling );
   result += bmp280_set_power_mode( cfg->powerMode );
   bmp280PowerMode = cfg->powerMode;
   result += bmp280_set_standby_durn( cfg->standbyTime );

   return result;

}

/***************************************************************************//**
 * @brief
 *    Initiates temperature measurement on the barometric pressure sensor and reads
 *    pressure from it.
 *
 * @param[out] temperature
 *    The measured temperature in degrees Celsius
 *
 * @return
 *    Returns zero on OK, non-zero otherwise
 ******************************************************************************/
uint32_t BMP_getTemperature( float *temperature )
{

   int8_t result;
   int32_t uncompTemp;
   int32_t uncompPressure;
   int32_t compTemp;

   if( bmp280PowerMode == BMP280_NORMAL_MODE ) {
      result = bmp280_read_uncomp_temperature( &uncompTemp );
   }
   else {
      result = bmp280_get_forced_uncomp_pressure_temperature( &uncompPressure, &uncompTemp );
   }

   if( result != SUCCESS ) {
      return (uint32_t) result;
   }

   compTemp = bmp280_compensate_temperature_int32( uncompTemp );
   *temperature = (float) compTemp;
   *temperature /= 100.0f;

   return BMP_OK;

}

/***************************************************************************//**
 * @brief
 *    Initiates pressure measurement on the barometric pressure sensor and reads
 *    pressure from it.
 *
 * @param[out] pressure
 *    The measured pressure in millibars
 *
 * @return
 *    Returns zero on OK, non-zero otherwise
 ******************************************************************************/
uint32_t BMP_getPressure( float *pressure )
{

   int8_t result;
   int32_t uncompTemp;
   int32_t uncompPressure;
   uint32_t compPressure;

   if( bmp280PowerMode == BMP280_NORMAL_MODE ) {
      result = bmp280_read_uncomp_pressure( &uncompPressure );
      if( result == SUCCESS ){
         result = bmp280_read_uncomp_temperature( &uncompTemp );
      }
   }
   else {
      result = bmp280_get_forced_uncomp_pressure_temperature( &uncompPressure, &uncompTemp );
   }

   if( result != SUCCESS ) {
      return (uint32_t) result;
   }
  
   bmp280_compensate_temperature_int32( uncompTemp );
   compPressure = bmp280_compensate_pressure_int64( uncompPressure );
   
   *pressure = (float) compPressure;
   *pressure /= 256.0f;
   *pressure /= 100.0f;
   
   return BMP_OK;

}

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/***************************************************************************//**
 * @brief
 *    Reads register from the barometric pressure sensor
 *
 * @param[in] addr
 *    The register address to read from in the sensor
 *
 * @return
 *    The value stored in the register in uint8_t format if there were no
 *    errors, 0 otherwise
 ******************************************************************************/
static uint8_t readRegister( uint8_t addr )
{

   I2C_TransferSeq_TypeDef seq;
   I2C_TransferReturn_TypeDef ret;
   uint8_t reg;

   seq.addr = BMP_I2C_BUS_ADDRESS << 1;
   seq.flags = I2C_FLAG_WRITE_READ;

   seq.buf[0].len  = 1;
   seq.buf[0].data = &addr;
   seq.buf[1].len  = 1;
   seq.buf[1].data = &reg;

   ret = I2CSPM_Transfer( BMP_I2C_DEVICE, &seq );

   if( ret != i2cTransferDone ) {
      return 0;
   }

   return reg;

}

/***************************************************************************//**
 * @brief
 *    Writes data to a device via the I2C bus
 *
 * @param[in] devAddr
 *    The I2C address of the device
 *
 * @param[in] regAddr
 *    The address of the register to write to
 *
 * @param[in] regData
 *    The data to write
 *
 * @param[in] count
 *    The number of data bytes to write
 *
 * @return
 *    Returns zero on OK, non-zero otherwise
 ******************************************************************************/
static int8_t i2cBusWrite( uint8_t devAddr, uint8_t regAddr, uint8_t *regData, uint8_t count )
{

   I2C_TransferSeq_TypeDef seq;
   I2C_TransferReturn_TypeDef ret;

   seq.addr = devAddr << 1;
   seq.flags = I2C_FLAG_WRITE_WRITE;

   seq.buf[0].len  = 1;
   seq.buf[0].data = &regAddr;
   seq.buf[1].len  = count;
   seq.buf[1].data = regData;

   ret = I2CSPM_Transfer( BMP_I2C_DEVICE, &seq );

   if( ret != i2cTransferDone ) {
      return BMP_ERROR_I2C_TRANSACTION_FAILED;
   }

   return BMP_OK;

}

/***************************************************************************//**
 * @brief
 *    Reads data from a device via the I2C bus
 *
 * @param[in] devAddr
 *    The I2C address of the device
 *
 * @param[in] regAddr
 *    The address of the register to read from
 *
 * @param[out] regData
 *    The data read from the device
 *
 * @param[in] count
 *    The number of data bytes to read
 *
 * @return
 *    Returns zero on OK, non-zero otherwise
 ******************************************************************************/
static int8_t i2cBusRead( uint8_t devAddr, uint8_t regAddr, uint8_t *regData, uint8_t count )
{

   I2C_TransferSeq_TypeDef seq;
   I2C_TransferReturn_TypeDef ret;

   seq.addr = devAddr << 1;
   seq.flags = I2C_FLAG_WRITE_READ;

   seq.buf[0].len  = 1;
   seq.buf[0].data = &regAddr;
   seq.buf[1].len  = count;
   seq.buf[1].data = regData;

   ret = I2CSPM_Transfer( BMP_I2C_DEVICE, &seq );

   if( ret != i2cTransferDone ) {
      return BMP_ERROR_I2C_TRANSACTION_FAILED;
   }

   return BMP_OK;

}

/** @endcond DO_NOT_INCLUDE_WITH_DOXYGEN */

/** @} (end defgroup BMP_Functions) */

/** @} (end defgroup BMP) */
