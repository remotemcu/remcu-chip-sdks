/**
  ******************************************************************************
  * @file    stm8l15x_rst.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    09/24/2010
  * @brief   This file provides all the RST firmware functions.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/

#include "stm8l15x_rst.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/**
  * @addtogroup RST_Private_Define
  * @{
  */
#define RST_CR_MASK  0xD0 /*!< Enable the GPIO */

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private Constants ---------------------------------------------------------*/

/**
  * @addtogroup RST_Public_Functions
  * @{
  */


/**
  * @brief   Checks whether the specified RST flag is set or not.
  * @param   RST_Flag : specify the reset flag to check.
  *          This parameter can be a value of @ref RST_FLAG_TypeDef.
  * @retval  FlagStatus: status of the given RST flag.
  */
FlagStatus RST_GetFlagStatus(RST_FLAG_TypeDef RST_Flag)
{
  /* Check the parameters */
  assert_param(IS_RST_FLAG(RST_Flag));

  /* Get flag status */

  return ((FlagStatus)((uint8_t)RST->SR & (uint8_t)RST_Flag));
}

/**
  * @brief  Clears the specified RST flag.
  * @param  RST_Flag : specify the reset flag to clear.
  *         This parameter can be a value of @ref RST_FLAG_TypeDef.
  * @retval None
  */
void RST_ClearFlag(RST_FLAG_TypeDef RST_Flag)
{
  /* Check the parameters */
  assert_param(IS_RST_FLAG(RST_Flag));

  RST->SR = (uint8_t)RST_Flag;
}

/**
  * @brief  Configures the reset pad as GP output.
  * @param  None
  * @retval None
  */
void RST_GPOutputEnable(void)
{

  RST->CR = RST_CR_MASK;
}

/**
  * @}
  */


/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
