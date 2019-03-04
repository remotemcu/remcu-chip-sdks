/**
  ******************************************************************************
  * @file    stm8l15x_comp.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    09/24/2010
  * @brief   This file provides all the COMP firmware functions.
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
#include "stm8l15x_comp.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @addtogroup COMP_Public_Functions
  * @{
  */

/**
  * @brief  Deinitializes the COMPx peripheral registers to their default reset values.
  * @param  None.
  * @retval None.
  */
void COMP_DeInit(void)
{
  /* Set COMP->CSR1 to reset value 0x00 */
  COMP->CSR1 = (uint8_t) COMP_CSR1_RESET_VALUE;

  /* Set COMP->CSR2 to reset value 0x00 */
  COMP->CSR2 = (uint8_t) COMP_CSR2_RESET_VALUE;

  /* Set COMP->CSR3 to reset value 0xC0 */
  COMP->CSR3 = (uint8_t) COMP_CSR3_RESET_VALUE;

  /* Set COMP->CSR4 to reset value 0x00 */
  COMP->CSR4 = (uint8_t) COMP_CSR4_RESET_VALUE;

  /* Set COMP->CSR5 to reset value 0x00 */
  COMP->CSR5 = (uint8_t) COMP_CSR5_RESET_VALUE;
}

/**
  * @brief  Initializes the comparator inverting input, output and speed.
  * @note   This function configures only COMP2.
  * @param  COMP_InvertingInput : selects the comparator inverting input and can
  *         be any of the @ref COMP_InvertingInput_Typedef enumeration.
  * @param  COMP_OutputSelect : selects the comparator output and can be any of
  *         the @ref COMP_OutputSelect_Typedef enumeation.
  * @param  COMP_Speed selects the comparator speed and can be any of the
  *         @ref COMP_Speed_TypeDef enumeration.
  * @retval None.
  */
void COMP_Init(COMP_InvertingInput_Typedef COMP_InvertingInput,
               COMP_OutputSelect_Typedef COMP_OutputSelect, COMP_Speed_TypeDef COMP_Speed)
{
  /* Check the parameters */
  assert_param(IS_COMP_INVERTING_INPUT(COMP_InvertingInput));
  assert_param(IS_COMP_OUTPUT(COMP_OutputSelect));
  assert_param(IS_COMP_SPEED(COMP_Speed));

  /* Reset the INSEL[2:0] bits in CSR3 register */
  COMP->CSR3 &= (uint8_t) (~COMP_CSR3_INSEL);
  /* Select the comparator inverting input */
  COMP->CSR3 |= (uint8_t) COMP_InvertingInput;

  /* Reset the OUTSEL[1:0] bits in CSR3 register */
  COMP->CSR3 &= (uint8_t) (~COMP_CSR3_OUTSEL);
  /* Redirect the comparator output */
  COMP->CSR3 |= (uint8_t) COMP_OutputSelect;

  /* Reset the comparator speed bit */
  COMP->CSR2 &= (uint8_t) (~COMP_CSR2_SPEED);
  /* Select the comparator speed */
  COMP->CSR2 |= (uint8_t) COMP_Speed;
}

/**
  * @brief  Enables or disables connection between VREFINT and COMP1 inverting input.
  * @param  NewState new state of the VREFINT connection to COMP1 inverting input.
  *         This parameter can be ENABLE or DISABLE.
  * @retval None
  */
void COMP_VrefintToCOMP1Connect(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the comparator */
    COMP->CSR3 |= COMP_CSR3_VREFEN;
  }
  else
  {
    /* Disable the comparator */
    COMP->CSR3 &= (uint8_t)(~COMP_CSR3_VREFEN);
  }
}

/**
  * @brief  Configures the COMP edge detection.
  * @param  COMP_Selection : selects the comparator and can be any of the
  *         @ref COMP_Selection_TypeDef enum.
  * @param  COMP_Edge : can be any of the @ref COMP_Edge_TypeDef enumeration
  * @retval None.
  */
void COMP_EdgeConfig(COMP_Selection_TypeDef COMP_Selection, COMP_Edge_TypeDef COMP_Edge)
{
  /* Check the parameters */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));
  assert_param(IS_COMP_EDGE(COMP_Edge));

  /* Check if comparator 1 is selected */
  if (COMP_Selection == COMP_Selection_COMP1)
  {
    /* Reset the comparator 1 edge control bits */
    COMP->CSR1 &= (uint8_t) (~COMP_CSR1_CMP1);

    /* Select the edge detection of comparator 1 output */
    COMP->CSR1 |= (uint8_t) COMP_Edge;
  }
  /* The comparator 2 is selected */
  else
  {
    /* Reset the comparator 2 edge control bits */
    COMP->CSR2 &= (uint8_t) (~COMP_CSR2_CMP2);

    /* Select the edge detection of comparator 2 output */
    COMP->CSR2 |= (uint8_t) COMP_Edge;
  }
}

/**
  * @brief  Returns the output level of the comparator.
  * @param  COMP_Selection : selects the comparator and can be any of the
  *         @ref COMP_Selection_TypeDef enum.
  * @retval Returns the comparator output level and can be any of the
  *         @ref COMP_OutputLevel_TypeDef enum.
  */
COMP_OutputLevel_TypeDef COMP_GetOutputLevel(COMP_Selection_TypeDef COMP_Selection)
{
  uint8_t compout;

  /* Check the parameters */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));

  /* Check if Comparator 1 is selected */
  if (COMP_Selection == COMP_Selection_COMP1)
  {
    /* Check if comparator 1 output level is high */
    if ((COMP->CSR1 & COMP_CSR1_CMP1OUT) != (uint8_t) RESET)
    {
      /* Get Comparator 1 output level */
      compout = (COMP_OutputLevel_TypeDef) COMP_OutputLevel_High;
    }
    /* comparator 1 output level is low */
    else
    {
      /* Get Comparator 1 output level */
      compout = (COMP_OutputLevel_TypeDef) COMP_OutputLevel_Low;
    }
  }
  /* Comparator 2 is selected */
  else
  {
    /* Check if comparator 2 output level is high */
    if ((COMP->CSR2 & COMP_CSR2_CMP2OUT) != (uint8_t) RESET)
    {
      /* Get Comparator output level */
      compout = (COMP_OutputLevel_TypeDef) COMP_OutputLevel_High;
    }
    /* comparator 2 output level is low */
    else
    {
      /* Get Comparator 2 output level */
      compout = (COMP_OutputLevel_TypeDef) COMP_OutputLevel_Low;
    }
  }

  /* Return the comparator output level */
  return (COMP_OutputLevel_TypeDef)(compout);
}

/**
  * @brief  Enables or disables the window mode.
  * @param  NewState new state of the window mode.
  *         This parameter can be ENABLE or DISABLE.
  * @retval None
  */
void COMP_WindowCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the window mode */
    COMP->CSR3 |= (uint8_t) COMP_CSR3_WNDWE;
  }
  else
  {
    /* Disable the window mode */
    COMP->CSR3 &= (uint8_t)(~COMP_CSR3_WNDWE);
  }
}

/**
  * @brief  Enables or disables the interrupt generation when an event is detected.
  * @param  COMP_Selection : selects the comparator and can be any of the
  *         @ref COMP_Selection_TypeDef enum.
  * @param  NewState : new state of the COMPx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void COMP_ITConfig(COMP_Selection_TypeDef COMP_Selection, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Check if Comparator 1 is selected */
  if (COMP_Selection == COMP_Selection_COMP1)
  {
    if (NewState != DISABLE)
    {
      /* Enable the COMP1 Interrupt source */
      COMP->CSR1 |= (uint8_t) COMP_CSR1_IE1;
    }
    else
    {
      /* Disable the COMP1 Interrupt source */
      COMP->CSR1 &= (uint8_t)(~COMP_CSR1_IE1);
    }
  }
  else /* Comparator 2 is selected */
  {
    if (NewState != DISABLE)
    {
      /* Enable the COMP2 Interrupt source */
      COMP->CSR2 |= (uint8_t) COMP_CSR2_IE2;
    }
    else
    {
      /* Disable the COMP2 Interrupt source */
      COMP->CSR2 &= (uint8_t)(~COMP_CSR2_IE2);
    }
  }
}

/**
  * @brief  Enables or disables trigger on the specified input/output group.
  * @param  COMP_TriggerGroup : specifies the input/output group
  *         This parameter can be a value @ref COMP_TriggerGroup_TypeDef
  * @param  COMP_TriggerPin : specifies the pin(s) within the input/output group
  *         This parameter can be a value @ref COMP_TriggerPin_TypeDef
  * @param  NewState : enable or disable the trigger on the selected pin(s)
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void COMP_TriggerConfig(COMP_TriggerGroup_TypeDef COMP_TriggerGroup,
                        COMP_TriggerPin_TypeDef COMP_TriggerPin,
                        FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_COMP_TRIGGERGROUP(COMP_TriggerGroup));
  assert_param(IS_COMP_TRIGGERPIN(COMP_TriggerPin));

  switch (COMP_TriggerGroup)
  {
    case COMP_TriggerGroup_InvertingInput:

      if (NewState != DISABLE)
      {
        COMP->CSR4 &= (uint8_t) ~COMP_TriggerPin;
      }
      else
      {
        COMP->CSR4 |= (uint8_t) COMP_TriggerPin;
      }
      break;

    case COMP_TriggerGroup_NonInvertingInput:
      if (NewState != DISABLE)
      {
        COMP->CSR4 &= (uint8_t) ~((uint8_t)(COMP_TriggerPin << 3));
      }
      else
      {
        COMP->CSR4 |= (uint8_t) (COMP_TriggerPin << 3);
      }
      break;

    case COMP_TriggerGroup_VREFINTOutput:
      if (NewState != DISABLE)
      {
        COMP->CSR5 &= (uint8_t) ~COMP_TriggerPin;
      }
      else
      {
        COMP->CSR5 |= (uint8_t) COMP_TriggerPin;
      }
      break;

    case COMP_TriggerGroup_DACOutput:
      if (NewState != DISABLE)
      {
        COMP->CSR5 &= (uint8_t) ~((uint8_t)(COMP_TriggerPin << 3));
      }
      else
      {
        COMP->CSR5 |= (uint8_t) (COMP_TriggerPin << 3);
      }
      break;

    default:
      break;
  }
}

/**
  * @brief  Enables or disables the output of the internal reference voltage.
  * @param  NewState : new state of the Vrefint output.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void COMP_VrefintOutputCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the output of internal reference voltage */
    COMP->CSR3 |= (uint8_t) COMP_CSR3_VREFOUTEN;
  }
  else
  {
    /* Disable the output of internal reference voltage */
    COMP->CSR3 &= (uint8_t) (~COMP_CSR3_VREFOUTEN);
  }
}

/**
  * @brief  Enables or disables the schmitt trigger.
  * @param  NewState : new state of the schmitt trigger.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void COMP_SchmittTriggerCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable Schmitt trigger on Input Output switches Channels */
    COMP->CSR1 |= (uint8_t) COMP_CSR1_STE;
  }
  else
  {
    /* Enable Schmitt trigger on Input Output switches Channels */
    COMP->CSR1 &= (uint8_t) (~COMP_CSR1_STE);
  }
}

/**
  * @brief  Checks whether the comparator flag is set or not.
  * @param  COMP_Selection : selects the comparator and can be any of the
  *         @ref COMP_Selection_TypeDef enum.
  * @retval The new state of COMPx event flag (SET or RESET).
  */
FlagStatus COMP_GetFlagStatus(COMP_Selection_TypeDef COMP_Selection)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));

  /* Check if COMP1 is selected */
  if (COMP_Selection == COMP_Selection_COMP1)
  {
    if ((COMP->CSR1 & COMP_CSR1_EF1) != (uint8_t) RESET)
    {
      /* The comparator 1 event flag is set */
      bitstatus = SET;
    }
    else
    {
      /* The comparator 1 event flag is reset */
      bitstatus = RESET;
    }
  }
  else   /* COMP2 is selected */
  {
    if ((COMP->CSR2 & COMP_CSR2_EF2) != (uint8_t) RESET)
    {
      /* The comparator 2 event flag is set */
      bitstatus = SET;
    }
    else
    {
      /* The comparator 2 event flag is reset */
      bitstatus = RESET;
    }
  }

  /* return the comparator event flag status */
  return (FlagStatus)(bitstatus);
}

/**
  * @brief  Clears the comparator’s pending flag.
  * @param  COMP_Selection : selects the comparator and can be any of the
  *         @ref COMP_Selection_TypeDef enum.
  * @retval None.
  */
void COMP_ClearFlag(COMP_Selection_TypeDef COMP_Selection)
{
  /* Check the parameters */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));

  if (COMP_Selection == COMP_Selection_COMP1)
  {
    /* Clear the flag EF1 (rc_w0) clear this bit by writing 0. */
    COMP->CSR1 &= (uint8_t) (~COMP_CSR1_EF1);
  }
  else
  {
    /* Clear the flag EF2 (rc_w0) clear this bit by writing 0. */
    COMP->CSR2 &= (uint8_t) (~COMP_CSR2_EF2);
  }
}

/**
  * @brief  Checks whether the comparator interrupt has occurred or not.
  * @param  COMP_Selection : selects the comparator and can be any of the
  *         @ref COMP_Selection_TypeDef enum.
  * @retval ITStatus : The state of the COMPx event flag (SET or RESET).
  */
ITStatus COMP_GetITStatus(COMP_Selection_TypeDef COMP_Selection)
{
  ITStatus bitstatus = RESET;
  uint8_t itstatus = 0x00, itenable = 0x00;

  /* Check the parameters */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));

  if (COMP_Selection == COMP_Selection_COMP1)
  {
    /* Get the EF1 comparator event falg status */
    itstatus = (uint8_t) (COMP->CSR1 & COMP_CSR1_EF1);

    /* Get the IE1 interrupt enable bit status */
    itenable = (uint8_t) (COMP->CSR1 & COMP_CSR1_IE1);

    if ((itstatus != (uint8_t) RESET) && (itenable != (uint8_t) RESET))
    {
      /* the EF1 and IE1 are set */
      bitstatus = SET;
    }
    else
    {
      /* the EF1 or IE1 is reset */
      bitstatus = RESET;
    }
  }
  else
  {
    /* Get the EF2 comparator event falg value */
    itstatus = (uint8_t) (COMP->CSR2 & COMP_CSR2_EF2);

    /* Get the IE2 interrupt enable bit value */
    itenable = (uint8_t) (COMP->CSR2 & COMP_CSR2_IE2);

    if ((itstatus != (uint8_t)RESET) && (itenable != (uint8_t)RESET))
    {
      /* The EF2 and IE2 are set */
      bitstatus = SET;
    }
    else
    {
      /* The EF2 or IE2 is reset */
      bitstatus = RESET;
    }
  }

  /* Return the COMP interrupt status */
  return (ITStatus) bitstatus;
}

/**
  * @brief  Clears the interrupt pending bits of the comparator.
  * @param  COMP_Selection : selects the comparator and can be any of the
  *         @ref COMP_Selection_TypeDef enum.
  * @retval None
  */
void COMP_ClearITPendingBit(COMP_Selection_TypeDef COMP_Selection)
{
  /* Check the parameters */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));

  if (COMP_Selection == COMP_Selection_COMP1)
  {
    /* Clear the flag EF1 (rc_w0) clear this bit by writing 0. */
    COMP->CSR1 &= (uint8_t) (~COMP_CSR1_EF1);
  }
  else
  {
    /* Clear the flag EF2 (rc_w0) clear this bit by writing 0. */
    COMP->CSR2 &= (uint8_t) (~COMP_CSR2_EF2);
  }
}

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
