/**
  ******************************************************************************
  * @file    stm32h7xx_ll_crs.h
  * @author  MCD Application Team
  * @brief   CRS LL module driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "remcu_exports_symbol_enter.h"
#include "stm32h7xx_ll_crs.h"
#include "remcu_exports_symbol_exit.h"

#include "remcu_exports_symbol_enter.h"
#include "stm32h7xx_ll_bus.h"
#include "remcu_exports_symbol_exit.h"


/** @addtogroup STM32H7xx_LL_Driver
  * @{
  */

#if defined(CRS)

/** @defgroup CRS_LL CRS
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup CRS_LL_Exported_Functions
  * @{
  */

/** @addtogroup CRS_LL_EF_Init
  * @{
  */

/**
  * @brief  De-Initializes CRS peripheral registers to their default reset values.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: CRS registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_CRS_DeInit(void)
{
  LL_APB1_GRP2_ForceReset(LL_APB1_GRP2_PERIPH_CRS);
  LL_APB1_GRP2_ReleaseReset(LL_APB1_GRP2_PERIPH_CRS);

  return  SUCCESS;
}



/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(CRS) */

/**
  * @}
  */
  
#endif /* USE_FULL_LL_DRIVER */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
