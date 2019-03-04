/**
  ******************************************************************************
  * @file    stm8l15x_pwr.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    09/24/2010
  * @brief   This file provides all the PWR firmware functions.
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
#include "stm8l15x_pwr.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/**
  * @addtogroup PWR_Public_Functions
  * @{
  */

/**
  * @brief  Deinitializes the PWR peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void PWR_DeInit(void)
{
  PWR->CSR1 = PWR_CSR1_PVDIF;
  PWR->CSR2 = PWR_CSR2_RESET_VALUE;
}

/**
  * @brief  Enable or disable the PWR fast wake up function.
  * @param  NewState : Indicates the new state of the PWR fast wake up .
  * @retval None
  */
void PWR_FastWakeUpCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the PWR FWU */
    PWR->CSR2 |= PWR_CSR2_FWU;
  }
  else
  {
    /* Disable the PWR FWU */
    PWR->CSR2 &= (uint8_t)(~PWR_CSR2_FWU);
  }
}

/**
  * @brief  Enable or disable the PWR Ultra Low Power (ULP) function.
  * @param  NewState :  Indicates the new state of the PWR ULP.
  * @retval None
  */
void PWR_UltraLowPowerCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the PWR ULP */
    PWR->CSR2 |= PWR_CSR2_ULP;
  }
  else
  {
    /* Disable the PWR ULP */
    PWR->CSR2 &= (uint8_t)(~PWR_CSR2_ULP);
  }
}

/**
  * @brief  Enable or disable the PWR Programmable Voltage Detector (PVD) function.
  * @param  NewState : Indicates the new state of the PWR PVD.
  * @retval None
  */
void PWR_PVDCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the PWR PVD */
    PWR->CSR1 |= PWR_CSR1_PVDE;
  }
  else
  {
    /* Disable the PWR PVD */
    PWR->CSR1 &= (uint8_t)(~PWR_CSR1_PVDE);
  }
}

/**
  * @brief  Configures the Programmable Voltage Detector (PVD) Interrupt .
  * @param  NewState : Indicates the new state of the PVD interrupt.
  * @retval None
  */
void PWR_PVDITConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the PVD interrupt */
    PWR->CSR1 |= PWR_CSR1_PVDIEN;
  }
  else
  {
    /* Disable the PVD interrupt */
    PWR->CSR1 &= (uint8_t)(~PWR_CSR1_PVDIEN);
  }
}

/**
  * @brief  Configures the Programmable Voltage Detector (PVD)  levels .
  * @param  PWR_PVDLevel : Indicates the new level of the PWR PVD.
  *         This paramter can be value of @ref PWR_PVDLevel_TypeDef
  * @retval None
  */
void PWR_PVDLevelConfig(PWR_PVDLevel_TypeDef PWR_PVDLevel)
{
  /* Check the parameters */
  assert_param(IS_PWR_PVD_LEVEL(PWR_PVDLevel));

  /* Clear the PVD level */
  PWR->CSR1 &= (uint8_t)(~PWR_CSR1_PLS);

  /* Configure the PVD level */
  PWR->CSR1 |= PWR_PVDLevel;

}

/**
  * @brief  Checks whether the specified PWR flag is set or not.
  * @param  PWR_FLAG : Flag to check.
  *         This paramter can be value of @ref PWR_Flag_TypeDef
  * @retval FlagStatus: status of the checked flag
  */
FlagStatus PWR_GetFlagStatus(PWR_FLAG_TypeDef PWR_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_PWR_FLAG(PWR_FLAG));

  if ((PWR_FLAG & PWR_FLAG_VREFINTF) != 0)
  {
    if ((PWR->CSR2 & PWR_CR2_VREFINTF) != (uint8_t)RESET )
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }
  else
  {
    if ((PWR->CSR1 & PWR_FLAG) != (uint8_t)RESET )
    {
      bitstatus = SET;
    }
    else
    {
      bitstatus = RESET;
    }
  }

  /* Return the flag status */
  return((FlagStatus)bitstatus);
}
/**
  * @brief  Clears the PWR PVDIF Flag.
  * @param  None
  * @retval None
  */
void PWR_PVDClearFlag(void)
{
  /* Set the PVDIF to clear it */
  PWR->CSR1 |= PWR_CSR1_PVDIF;
}

/**
  * @brief  Checks whether the PVD interrupt has occurred or not.
  * @param  None
  * @retval ITStatus : The new state of the PVD Interrupt.
  */
ITStatus PWR_PVDGetITStatus(void)
{
  ITStatus bitstatus = RESET;

  uint8_t PVD_itStatus = 0x0, PVD_itEnable = 0x0;

  PVD_itStatus = (uint8_t)(PWR->CSR1 & (uint8_t)PWR_CSR1_PVDIF);
  PVD_itEnable = (uint8_t)(PWR->CSR1 & (uint8_t)PWR_CSR1_PVDIEN);

  if ((PVD_itStatus != (uint8_t)RESET ) && (PVD_itEnable != (uint8_t)RESET))
  {
    bitstatus = (ITStatus)SET;
  }
  else
  {
    bitstatus = (ITStatus)RESET;
  }
  return ((ITStatus)bitstatus);
}

/**
  * @brief  Clears the PWR interrupt pending bit.
  * @param  None
  * @retval None
  */
void PWR_PVDClearITPendingBit(void)
{
  /* Set the PVDIF to clear it */
  PWR->CSR1 |= PWR_CSR1_PVDIF;
}

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
