/***************************************************************************//**
 * @file imu.h
 * @brief Inertial Measurement Unit DCM matrix related routines
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

#ifndef __IMU_H_
#define __IMU_H_

#include <stdint.h>

#include "em_gpio.h"

#include "i2cspm.h"

#include "thunderboard/board_pic_regs.h"
#include "thunderboard/board_rgbled_profiles.h"

/***************************************************************************//**
 * @addtogroup IMU
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @defgroup IMU_Error_Messages IMU Error Messages
 * @{
 * @brief Inertial Measurement Unit error message macro definitions
 ******************************************************************************/

#define IMU_OK                         0  /**< No errors */

/** @} {end defgroup IMU_Error_Messages} */

/***************************************************************************//**
 * @defgroup IMU_Defs IMU Macro Definitions
 * @{
 * @brief Macro definitions used by the IMU driver
 ******************************************************************************/

#define IMU_PI                     3.14159265358979323            /**< The value of the Pi                  */
#define IMU_DEG_TO_RAD_FACTOR      ( (2.0*IMU_PI) / 360.0 )       /**< Degrees to radians conversion factor */
#define IMU_RAD_TO_DEG_FACTOR      ( 360.0 / (2.0*IMU_PI) )       /**< Radians to degrees conversion factor */
#define IMU_DEG_TO_RAD(ang)        (ang * IMU_DEG_TO_RAD_FACTOR)  /**< Degrees to radians converter macro   */
#define IMU_RAD_TO_DEG(ang)        (ang * IMU_RAD_TO_DEG_FACTOR)  /**< Radians to degrees converter macro   */

#define IMU_MAX_ACCEL_FOR_ANGLE    0.9848  /**< Maximum acceleration value for a given angle                */

#define IMU_STATE_DISABLED         0x00    /**< The IMU is disabled                                         */
#define IMU_STATE_READY            0x01    /**< The IMU is fully configured and ready to take measurements  */
#define IMU_STATE_INITIALIZING     0x02    /**< The IMU is being initialized                                */
#define IMU_STATE_CALIBRATING      0x03    /**< The IMU is being calibrated                                 */

/** @} {end defgroup IMU_Defs} */

/***************************************************************************//**
 * @defgroup IMU_Typedefs IMU Type Definitions
 * @{
 * @brief IMU type definitions used by the driver
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *    Structure to store the sensor fusion data
 ******************************************************************************/
typedef struct _IMU_SensorFusion
{

   /* Direction Cosine Matrix */
   float     dcm[3][3];          /**< Direction Cosine Matrix                       */

   /* Accelerometer filtering */
   float     aVector[3];         /**< Acceleration vector                           */
   float     aAccumulator[3];    /**< Accumulator for acceleration vector           */
   uint32_t  aAccumulatorCount;  /**< Number of vectors stored in the accumulator   */
   float     aSampleRate;        /**< Acceleration measurement sample rate          */

   /* Gyro */
   float     gVector[3];         /**< Gyro vector                                   */
   float     gSampleRate;        /**< Gyroscope measurement sample rate             */
   float     gDeltaTime;         /**< Time between gyro samples                     */
   float     gDeltaTimeScale;    /**< Rotation between gyro samples                 */

   /* Orientation */
   float     angleCorrection[3]; /**< Angle correction vector                       */
   float     orientation[3];     /**< Orientation vector                            */

} IMU_SensorFusion;

/** @} {end defgroup IMU_Typedefs} */

/***************************************************************************//**
 * @addtogroup IMU_Functions
 * @{
 ******************************************************************************/

/******************************************************************************/
/** Module functions                                                         **/
/******************************************************************************/
uint32_t IMU_init                       ( void );
uint32_t IMU_deInit                     ( void );
uint8_t  IMU_getState                   ( void );
void     IMU_update                     ( void );
void     IMU_reset                      ( void );

void     IMU_accelerationGet            ( int16_t avec[3] );
void     IMU_orientationGet             ( int16_t ovec[3] );
void     IMU_gyroGet                    ( int16_t gvec[3] );
uint32_t IMU_gyroCalibrate              ( void );
void     IMU_getGyroCorrectionAngles    ( float acorr[3] );

/*****************************************************************************/
/** Vector and Matrix math                                                  **/
/*****************************************************************************/
void     IMU_normalizeAngle             ( float *a );
void     IMU_matrixMultiply             ( float c[3][3], float a[3][3], float b[3][3] );
void     IMU_vectorNormalizeAngle       ( float v[3] );
void     IMU_vectorZero                 ( float v[3] );
void     IMU_vectorScale                ( float v[3], float scale );
void     IMU_vectorScalarMultiplication ( float r[3], float v[3], float scale );
void     IMU_vectorAdd                  ( float r[3], float a[3], float b[3] );
void     IMU_vectorSubtract             ( float r[3], float a[3], float b[3] );
float    IMU_vectorDotProduct           ( float a[3], float b[3] );
void     IMU_vectorCrossProduct         ( float r[3], float a[3], float b[3] );

/*****************************************************************************/
/** Direction Cosine Matrix functions                                       **/
/*****************************************************************************/
void     IMU_dcmReset                   ( float dcm[3][3] );
void     IMU_dcmResetZ                  ( float dcm[3][3] );
void     IMU_dcmNormalize               ( float dcm[3][3] );
void     IMU_dcmRotate                  ( float dcm[3][3], float ang[3] );
void     IMU_dcmGetAngles               ( float dcm[3][3], float ang[3] );

/*****************************************************************************/
/** IMU general use                                                         **/
/*****************************************************************************/
void     IMU_config                     ( float sampleRate );
bool     IMU_isDataReady                ( void );
bool     IMU_isDataReadyFlag            ( void );
void     IMU_clearDataReadyFlag         ( void );

void     IMU_getAccelerometerData       ( float avec[3] );
void     IMU_getGyroData                ( float gvec[3] );

/*****************************************************************************/
/** Sensor Fusion functions                                                 **/
/*****************************************************************************/
void     IMU_fuseAccelerometerSetSampleRate ( IMU_SensorFusion *f, float rate );
void     IMU_fuseAccelerometerUpdateFilter  ( IMU_SensorFusion *f, float avec[3] );

void     IMU_fuseGyroSetSampleRate          ( IMU_SensorFusion *f, float rate );
void     IMU_fuseGyroUpdate                 ( IMU_SensorFusion *f, float gvec[3] );
void     IMU_fuseGyroCorrectionClear        ( IMU_SensorFusion *f );
void     IMU_fuseGyroCorrection             ( IMU_SensorFusion *f,
                                              bool accValid, bool dirValid,
                                              float dirZ );

void     IMU_fuseNew                        ( IMU_SensorFusion *f );
void     IMU_fuseReset                      ( IMU_SensorFusion *f );
void     IMU_fuseUpdate                     ( IMU_SensorFusion *f );

/** @} {end addtogroup IMU_Functions} */

/** @} {end addtogroup IMU} */

#endif /* __IMU_H_ */
