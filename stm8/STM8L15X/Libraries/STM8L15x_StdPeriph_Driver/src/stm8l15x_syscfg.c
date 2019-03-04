/**
  ******************************************************************************
  * @file    stm8l15x_syscfg.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    09/24/2010
  * @brief   This file provides all the SYSCFG firmware functions.
  ******************************************************************************
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  * @image html logo.bmp@ref
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x_syscfg.h"

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
  * @addtogroup SYSCFG_Public_Functions
  * @{
  */

/**
  * @brief  Deinitializes the RI registers to their default reset values.
  * @param  None
  * @retval None
  */
void SYSCFG_RIDeInit(void)
{
  RI->ICR1   = RI_ICR1_RESET_VALUE;     /*!< Set RI->ICR1 to reset value */
  RI->ICR2   = RI_ICR2_RESET_VALUE;     /*!< Set RI->ICR2 to reset value */
  RI->IOSR1  = RI_IOSR1_RESET_VALUE;    /*!< Set RI->IOSR1 to reset value */
  RI->IOSR2  = RI_IOSR2_RESET_VALUE;    /*!< Set RI->IOSR2 to reset value */
  RI->IOSR3  = RI_IOSR3_RESET_VALUE;    /*!< Set RI->IOSR3 to reset value */
  RI->ASCR1  = RI_ASCR1_RESET_VALUE;    /*!< Set RI->ASCR1 to reset value */
  RI->ASCR2  = RI_ASCR2_RESET_VALUE;    /*!< Set RI->ASCR2 to reset value */
  RI->RCR    = RI_RCR_RESET_VALUE;      /*!< Set RI->RCR to reset value */
}

/**
  * @brief  Configures the routing interface to select which Input Output pin
  *         to be routed to TIM1 Input Capture.
  * @param  RI_InputCapture: selects the TIM1 input capture2 RI_InputCapture_IC2
  *         or the TIM1 input capture3 RI_InputCapture_IC3
  * @param  RI_InputCaptureRouting : selects the value to set in TIM1 Input Capture
  *         routing register ICRx and can be from RI_InputCaptureRouting_0 to
  *         RI_InputCaptureRouting_22.
  * @retval None.
  */
void SYSCFG_RITIMInputCaptureConfig(RI_InputCapture_TypeDef RI_InputCapture,
                                    RI_InputCaptureRouting_TypeDef RI_InputCaptureRouting)
{
  /* Check the parameters */
  assert_param(IS_RI_INPUTCAPTURE(RI_InputCapture));
  assert_param(IS_RI_INPUTCAPTUREROUTING(RI_InputCaptureRouting));

  /* Check whether Input Capture 2 is selected */
  if (RI_InputCapture == RI_InputCapture_IC2)
  {
    /* Set the value in ICR1 register to route TIM input Capture 2 */
    RI->ICR1 = (uint8_t) RI_InputCaptureRouting;
  }

  else /* The Input Capture 3 is selected */
  {
    /* Set the value in ICR2 register to route TIM input capture 3 */
    RI->ICR2 = (uint8_t) RI_InputCaptureRouting;
  }
}

/**
  * @brief  Enables or disables the Routing Interface Analog switch.
  * @param  RI_AnalogSwitch : can be one of @ref RI_AnalogSwitch_TypeDef
  * @param  NewState : new state of the analog switch.
  *         This parameter can be ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG_RIAnalogSwitchConfig(RI_AnalogSwitch_TypeDef RI_AnalogSwitch,
                                 FunctionalState NewState)
{
  uint8_t AnalogSwitchRegister, AnalogSwitchIndex = 0;

  /* Check the parameters */
  assert_param(IS_RI_ANALOGSWITCH(RI_AnalogSwitch));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Get the analog switch register ASCR1 or ASCR2 */
  AnalogSwitchRegister = (uint8_t) (RI_AnalogSwitch & (uint8_t) 0xF0);

  /* Get the analog switch bit index in ASCRx register */
  AnalogSwitchIndex = (uint8_t) (RI_AnalogSwitch & (uint8_t) 0x0F);

  if (NewState != DISABLE)
  {
    if (AnalogSwitchRegister == (uint8_t) 0x10)
    {
      /* Enable the analog switch */
      RI->ASCR1 |= (uint8_t) ((uint8_t)1 << (uint8_t) AnalogSwitchIndex);
    }
    else
    {
      /* Enable the analog switch */
      RI->ASCR2 |= (uint8_t) ((uint8_t)1 << (uint8_t) AnalogSwitchIndex);
    }
  }
  else
  {
    if (AnalogSwitchRegister == (uint8_t) 0x10)
    {
      /* Disable the analog switch */
      RI->ASCR1 &= (uint8_t) (~(uint8_t)((uint8_t)1 <<  AnalogSwitchIndex));
    }
    else
    {
      /* Disable the analog switch */
      RI->ASCR2 &= (uint8_t) (~ (uint8_t)((uint8_t)1 << AnalogSwitchIndex));
    }
  }
}

/**
  * @brief  Closes or Opens the routing interface Input Output switchs.
  * @param  RI_IOSwitch : can be one of RI_IOSwitch_1..RI_IOSwitch_24
  * @param  NewState : new state of the Input Output Switch.
  *         This parameter can be ENABLE or DISABLE.
  * @retval None.
  */
void SYSCFG_RIIOSwitchConfig(RI_IOSwitch_TypeDef RI_IOSwitch,
                             FunctionalState NewState)
{
  uint8_t IOSwitchRegsiter, IOSwitchIndex = 0;

  /* Check the parameters */
  assert_param(IS_RI_IOSWITCH(RI_IOSwitch));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Get the Input Output switch bit index in IOSRx register */
  IOSwitchIndex = (uint8_t) (RI_IOSwitch & (uint8_t) 0x0F);

  /* Get the Input Output switch register IOSR1, IOSR2 or IOSR3 */
  IOSwitchRegsiter = (uint8_t) (RI_IOSwitch & (uint8_t) 0xF0);

  /* Check whether the Input Output switch control bit is in the IOSR1 register */
  if (IOSwitchRegsiter == (uint8_t) 0x10)
  {
    if (NewState != DISABLE)
    {
      /* Close the Input Output switch */
      RI->IOSR1 |= (uint8_t) ((uint8_t)1 << IOSwitchIndex);
    }
    else
    {
      /* Open the Input Output switch */
      RI->IOSR1 &= (uint8_t) (~ (uint8_t)((uint8_t)1 << IOSwitchIndex));
    }
  }

  /* Check whether the Input Output switch control bit is in the IOSR2 register */
  else if (IOSwitchRegsiter == (uint8_t) 0x20)
  {
    if (NewState != DISABLE)
    {
      /* Close the Input Output switch */
      RI->IOSR2 |= (uint8_t) ((uint8_t)1 << IOSwitchIndex);
    }
    else
    {
      /* Open the Input Output switch */
      RI->IOSR2 &= (uint8_t) (~(uint8_t)((uint8_t)1 <<  IOSwitchIndex));
    }
  }

  /* The Input Output switch control bit is in the IOSR3 register */
  else
  {
    if (NewState != DISABLE)
    {
      /* Close the Input Output switch */
      RI->IOSR3 |= (uint8_t) ((uint8_t)1 << IOSwitchIndex);
    }
    else
    {
      /* Open the Input Output switch */
      RI->IOSR3 &= (uint8_t) (~ (uint8_t) ((uint8_t) 1 << IOSwitchIndex));
    }
  }
}

/**
  * @brief  Configures the Pull-up and Pull-down Resistors
  * @param  RI_Resistor : selects the resistor to connect,
  *         This parameter can be a value of @ref RI_Resistor_TypeDef
  * @retval None
  */
void SYSCFG_RIResistorConfig(RI_Resistor_TypeDef RI_Resistor, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RI_RESISTOR(RI_Resistor));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the resistor */
    RI->RCR |= (uint8_t) RI_Resistor;
  }
  else
  {
    /* Disable the Resistor */
    RI->RCR &= (uint8_t) (~RI_Resistor);
  }
}

/**
  * @brief  Deinitializes the Remapping registers to their default reset values.
  * @param  None
  * @retval None
  */
void SYSCFG_REMAPDeInit(void)
{
  /*!< Set RMPCR1 to reset value */
  SYSCFG->RMPCR1 = SYSCFG_RMPCR1_RESET_VALUE;

  /*!< Set RMPCR2 to reset value */
  SYSCFG->RMPCR2 = SYSCFG_RMPCR2_RESET_VALUE;

  /*!< Set RMPCR3 to reset value */
  SYSCFG->RMPCR3 = SYSCFG_RMPCR3_RESET_VALUE;
}

/**
  * @brief  Changes the mapping of the specified pins.
  * @param  REMAP_Pin: selects the pin to remap.
  *         This parameter can be a value of @ref REMAP_Pin_TypeDef
  * @param  NewState: This parameter can be ENABLE or DISABLE.
  * @retval None
  */
void SYSCFG_REMAPPinConfig(REMAP_Pin_TypeDef REMAP_Pin, FunctionalState NewState)
{
  uint8_t regindex = 0;
  /* Check the parameters */
  assert_param(IS_REMAP_PIN(REMAP_Pin));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  /* Read register index */
  regindex = (uint8_t) ((uint16_t) REMAP_Pin >> 8);

  /* Check if REMAP_Pin is in RMPCR1 register */
  if (regindex == 0x01)
  {
    SYSCFG->RMPCR1 &= (uint8_t)((uint8_t)((uint8_t)REMAP_Pin << 4) | (uint8_t)0x0F);
    if (NewState != DISABLE)
    {
      SYSCFG->RMPCR1 |= (uint8_t)((uint16_t)REMAP_Pin & (uint16_t)0x00F0);
    }
  }
  /* Check if REMAP_Pin is in RMPCR2 register */
  else if (regindex == 0x02)
  {
    if (NewState != DISABLE)
    {
      SYSCFG->RMPCR2 |= (uint8_t) REMAP_Pin;
    }
    else
    {
      SYSCFG->RMPCR2 &= (uint8_t)((uint16_t)(~(uint16_t)REMAP_Pin));
    }
  }
  /* REMAP_Pin is in RMPCR3 register */
  else
  {
    if (NewState != DISABLE)
    {
      SYSCFG->RMPCR3 |= (uint8_t) REMAP_Pin;
    }
    else
    {
      SYSCFG->RMPCR3 &= (uint8_t)((uint16_t)(~(uint16_t)REMAP_Pin));
    }
  }
}

/**
  * @brief  Remaps the DMA Channel to the specific peripheral (ADC or TIM4)
  * @param  REMAP_DMAChannel: specifies the DMA Channel to remap.
  *         This parameter can be one of @ref REMAP_DMAChannel_TypeDef
  * @retval None
  */
void SYSCFG_REMAPDMAChannelConfig(REMAP_DMAChannel_TypeDef REMAP_DMAChannel)
{
  /* Check the parameters */
  assert_param(IS_REMAP_DMACHANNEL(REMAP_DMAChannel));

  /* Check if the TIM4 DMA channel is selected: bits 4 --> 7 are set */
  if ((REMAP_DMAChannel & 0xF0) != RESET)
  {
    /* Reset the TIM4 DMA channels */
    SYSCFG->RMPCR1 &= (uint8_t) (~SYSCFG_RMPCR1_TIM4DMA_REMAP);
  }
  /* ADC DMA channel is selected: bits 4 --> 7 are reset */
  else
  {
    /* Reset the ADC DMA channels */
    SYSCFG->RMPCR1 &= (uint8_t) (~SYSCFG_RMPCR1_ADC1DMA_REMAP);
  }
  /* Set the DMA Channels remapping */
  SYSCFG->RMPCR1 |= (uint8_t) ((uint8_t)0x0F & REMAP_DMAChannel);
}

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
