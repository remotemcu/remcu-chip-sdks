#include "remcu_exports_symbol_enter.h"
#include "stm32h7xx_hal.h"

 /**
  ******************************************************************************
  * @file    stm32h7xx_hal_sai_ex.h
  * @author  MCD Application Team
  * @brief   Header file of SAI HAL extended module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7xx_HAL_SAI_EX_H
#define STM32H7xx_HAL_SAI_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal_def.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @addtogroup SAIEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup SAIEx_Exported_Types SAIEx Exported Types
  * @{
  */

/**
  * @brief  PDM microphone delay structure definition
  */
typedef struct
{
  uint32_t MicPair;     /*!< Specifies which pair of microphones is selected.
                             This parameter must be a number between Min_Data = 1 and Max_Data = 3. */

  uint32_t LeftDelay;   /*!< Specifies the delay in PDM clock unit to apply on left microphone.
                             This parameter must be a number between Min_Data = 0 and Max_Data = 7. */

  uint32_t RightDelay;  /*!< Specifies the delay in PDM clock unit to apply on right microphone.
                             This parameter must be a number between Min_Data = 0 and Max_Data = 7. */
} SAIEx_PdmMicDelayParamTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup SAIEx_Exported_Functions SAIEx Extended Exported Functions
  * @{
  */

/** @addtogroup SAIEx_Exported_Functions_Group1 Peripheral Control functions
  * @{
  */
HAL_StatusTypeDef HAL_SAIEx_ConfigPdmMicDelay(SAI_HandleTypeDef *hsai, SAIEx_PdmMicDelayParamTypeDef *pdmMicDelay);
/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup SAIEx_Private_Macros SAIEx Extended Private Macros
  * @{
  */
#define IS_SAI_PDM_MIC_DELAY(VALUE)   ((VALUE) <= 7U)
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7xx_HAL_SAI_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

#include "remcu_exports_symbol_exit.h"