/***************************************************************************//**
 * @file mic.h
 * @brief Driver for the SPV1840LR5H-B MEMS Microphone
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

#ifndef __MIC_H_
#define __MIC_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "mic_config.h"

/***************************************************************************//**
 * @addtogroup Mic
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @defgroup Mic_Config_Settings MEMS Microphone Configuration Settings
 * @{
 * @brief MEMS microphone configuration setting macro definitions
 ******************************************************************************/

#define MIC_ADC_ACQ_TIME      MIC_CONFIG_ADC_ACQ_TIME    /**< ADC acquisition time  */
#define MIC_ADC_CLOCK_FREQ    MIC_CONFIG_ADC_CLOCK_FREQ  /**< ADC clock frequency   */

/** @} {end defgroup Mic_Config_Settings} */

/***************************************************************************//**
 * @defgroup Mic_Error_Messages MEMS Microphone Error Messages
 * @{
 * @brief MEMS microphone error message macro definitions
 ******************************************************************************/

#define MIC_OK                0                          /**< No errors */

/** @} {end defgroup Mic_Error_Messages} */

/***************************************************************************//**
 * @defgroup Mic_Functions MEMS Microphone Functions
 * @{
 * @brief MEMS microphone driver and support functions
 ******************************************************************************/

uint32_t  MIC_init           ( uint32_t fs, uint16_t *sampleBuffer, size_t len );
void      MIC_deInit         ( void );
void      MIC_start          ( uint32_t nsamples );
bool      MIC_isBusy         ( void );

float     MIC_getSoundLevel  ( float *var );
float     MIC_getMean        ( void );
uint16_t *MIC_getSampleBuffer( void );

/** @} {end defgroup Mic_Functions}*/

/** @} {end addtogroup Mic} */

#endif /* __MIC_H_ */
