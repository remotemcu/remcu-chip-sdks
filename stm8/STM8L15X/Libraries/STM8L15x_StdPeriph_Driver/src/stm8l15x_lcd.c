/**
  ******************************************************************************
  * @file    stm8l15x_lcd.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    09/24/2010
  * @brief   This file provides all the LCD firmware functions.
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
#include "stm8l15x_lcd.h"

/** @addtogroup STM8L15x_StdPeriph_Driver
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/** @addtogroup LCD_Public_Functions
  * @{
  */

/**
  * @brief  Deinitializes the LCD Controller registers to their default reset values.
  * @param  None
  * @retval None
  */
void LCD_DeInit(void)
{
  uint8_t counter = 0;

  LCD->CR1 = LCD_CR1_RESET_VALUE;
  LCD->CR2 = LCD_CR2_RESET_VALUE;
  LCD->CR3 = LCD_CR3_RESET_VALUE;
  LCD->FRQ = LCD_FRQ_RESET_VALUE;

  for (counter = 0;counter < 0x05; counter++)
  {
    LCD->PM[counter] = LCD_PM_RESET_VALUE;
  }

  for (counter = 0;counter < 0x16; counter++)
  {
    LCD->RAM[counter] =  LCD_RAM_RESET_VALUE;
  }

  LCD->CR4 = LCD_CR4_RESET_VALUE;

}

/**
  * @brief  Initializes the LCD according to the specified parameters.
  * @param  LCD_CLKPrescalerDiv : This parameter can be any of the  @ref LCD_Divider_TypeDef enumeration.
  * @param  LCD_Divider : This parameter can be any of the @ref LCD_Divider_TypeDef enumeration.
  * @param  LCD_Duty : This parameter can be any of the @ref LCD_Duty_TypeDef enumeration.
  * @param  LCD_Bias : This parameter can be any of the @ref LCD_Bias_TypeDef enumeration.
  * @param  LCD_VoltageSource : This parameter can be any of the @ref LCD_VoltageSource_TypeDef enumeration.
  * @retval None
  */
void LCD_Init(LCD_Prescaler_TypeDef LCD_Prescaler, LCD_Divider_TypeDef LCD_Divider,
              LCD_Duty_TypeDef LCD_Duty, LCD_Bias_TypeDef LCD_Bias,
              LCD_VoltageSource_TypeDef LCD_VoltageSource)
{
  /* Check function parameters */
  assert_param(IS_LCD_CLOCK_PRESCALER(LCD_Prescaler));
  assert_param(IS_LCD_CLOCK_DIVIDER(LCD_Divider));
  assert_param(IS_LCD_DUTY(LCD_Duty));
  assert_param(IS_LCD_BIAS(LCD_Bias));
  assert_param(IS_LCD_VOLTAGE_SOURCE(LCD_VoltageSource));

  LCD->FRQ &= (uint8_t)(~LCD_FRQ_PS);     /* Clear the prescaler bits */
  LCD->FRQ |= LCD_Prescaler;

  LCD->FRQ &= (uint8_t)(~LCD_FRQ_DIV);     /* Clear the divider bits */
  LCD->FRQ |= LCD_Divider;

  /* Configure the Duty cycle */
  LCD->CR1 &= (uint8_t)(~LCD_CR1_DUTY);    /* Clear the duty bits */
  LCD->CR4 &= (uint8_t)(~LCD_CR4_DUTY8);   /* Clear the DUTY8 bit */

  if (LCD_Duty == LCD_Duty_1_8)
  {
    LCD->CR4 |= (uint8_t)((uint8_t)((uint8_t)LCD_Duty & (uint8_t)0xF0) >> 4);
  }
  else
  {
    LCD->CR1 |= (uint8_t)((uint8_t)LCD_Duty & (uint8_t)0x0F);
  }

  /* Configure the Bias */
  LCD->CR1 &= (uint8_t)(~LCD_CR1_B2);      /* Clear the B2 bit */
  LCD->CR4 &= (uint8_t)(~LCD_CR4_B4);      /* Clear the B4 bit */

  if (LCD_Bias == LCD_Bias_1_4)
  {
    LCD->CR1 |= (uint8_t)((uint8_t)LCD_Bias & (uint8_t)0x0F);
    LCD->CR4 |= (uint8_t)((uint8_t)((uint8_t)LCD_Bias & (uint8_t)0xF0) >> 4);
  }
  else
  {
    LCD->CR1 |= (uint8_t)((uint8_t)LCD_Bias & (uint8_t)0x0F);
  }

  LCD->CR2 &= (uint8_t)(~LCD_CR2_VSEL);    /* Clear the voltage source bit */
  LCD->CR2 |= LCD_VoltageSource;

}

/**
  * @brief  Enables or disables the LCD Controller.
  * @param  NewState: New state of the LCD peripheral.
  *         This parameter can be: ENABLE or DISABLE
  * @retval None
  */
void LCD_Cmd(FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    LCD->CR3 |= LCD_CR3_LCDEN; /* Enable the LCD peripheral*/
  }
  else
  {
    LCD->CR3 &= (uint8_t)(~LCD_CR3_LCDEN); /* Disable the LCD peripheral*/
  }

}

/**
  * @brief  Enables or disables the interrupt.
  * @param  NewState: The new state of the LCD interrupt.
  *         This parameter can be: ENABLE or DISABLE
  * @retval None
  */
void LCD_ITConfig(FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    LCD->CR3 |= LCD_CR3_SOFIE; /* Enable interrupt*/
  }
  else
  {
    LCD->CR3 &= (uint8_t)(~LCD_CR3_SOFIE); /* Disable interrupt*/
  }

}
/**
  * @brief  Enables or disables the low resistance divider.
  * @param  NewState: The state of the low resistance divider.
  *         This parameter can be: ENABLE or DISABLE
  * @retval None
  */
void LCD_HighDriveCmd(FunctionalState NewState)
{
  /* Check function parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    LCD->CR2 |= LCD_CR2_HD; /* Permanently enable low resistance divider */
  }
  else
  {
    LCD->CR2 &= (uint8_t)(~LCD_CR2_HD); /* Permanently disable low resistance divider */
  }

}
/**
  * @brief  Configures the pulses on duration.
  * @note   The pulses on duration have a sense only when enabling the High drive
  * @param  LCD_PulseOnDuration : This parameter can be any of the
  *         @ref LCD_PulseOnDuration_TypeDef enumeration.
  * @retval None
  */
void LCD_PulseOnDurationConfig(LCD_PulseOnDuration_TypeDef LCD_PulseOnDuration)
{
  /* Check function parameters */
  assert_param(IS_LCD_PULSE_DURATION(LCD_PulseOnDuration));

  LCD->CR2 &= (uint8_t)(~LCD_CR2_PON); /* Clear the pulses on duration bits */
  LCD->CR2 |= LCD_PulseOnDuration;

}
/**
  * @brief  Configures the LCD dead time.
  * @param  LCD_DeadTime : This parameter can be any of the
  *         @ref LCD_DeadTime_TypeDef enumeration.
  * @retval None
  */
void LCD_DeadTimeConfig(LCD_DeadTime_TypeDef LCD_DeadTime)
{
  /* Check function parameters */
  assert_param(IS_LCD_DEAD_TIME(LCD_DeadTime));

  LCD->CR3 &= (uint8_t)(~LCD_CR3_DEAD);  /* Clear the dead time bits  */

  LCD->CR3 |= LCD_DeadTime;

}

/**
  * @brief  Configures the LCD Blink mode.
  * @param  LCD_BlinkMode: Specifies the LCD blink mode.
  *         This parameter can be any of the @ref LCD_BlinkMode_TypeDef
  *         enumeration.
  * @param  LCD_BlinkFrequency: Specifies the LCD blink frequency.
  *         This parameter can be any of the @ref LCD_BlinkFrequency_TypeDef
  *         enumeration.
  * @retval None
  */
void LCD_BlinkConfig(LCD_BlinkMode_TypeDef LCD_BlinkMode,
                     LCD_BlinkFrequency_TypeDef LCD_BlinkFrequency)
{
  /* Check function parameters */
  assert_param(IS_LCD_BLINK_MODE(LCD_BlinkMode));
  assert_param(IS_LCD_BLINK_FREQUENCY(LCD_BlinkFrequency));

  LCD->CR1 &= (uint8_t)(~LCD_CR1_BLINK); /* Clear the blink mode bits */
  LCD->CR1 |= LCD_BlinkMode; /* Config the LCD Blink Mode */

  LCD->CR1 &= (uint8_t)(~LCD_CR1_BLINKF); /* Clear the blink frequency bits */
  LCD->CR1 |= LCD_BlinkFrequency; /* Config the LCD Blink Frequency */

}

/**
  * @brief  Configures the LCD Contrast.
  * @param  LCD_Contrast: Specifies the LCD contrast.
  *         This parameter can be any of the @ref LCD_Contrast_TypeDef enumeration.
  * @retval None
  */
void LCD_ContrastConfig(LCD_Contrast_TypeDef LCD_Contrast)
{
  /* Check function parameters */
  assert_param(IS_LCD_CONTRAST(LCD_Contrast));

  LCD->CR2 &= (uint8_t)(~LCD_CR2_CC); /* Clear the contrast bits  */
  LCD->CR2 |= LCD_Contrast; /* Select the maximum voltage value Vlcd */

}

/**
  * @brief  Configures the LCD Port Mask.
  * @param  LCD_PortMaskRegister: The LCD register index in the port mask matrix.
  *         This parameter can be any of the @ref LCD_PortMaskRegister_TypeDef
  *         enumeration.
  * @param  LCD_Mask : Value to be written
  * @retval None
  */
void LCD_PortMaskConfig(LCD_PortMaskRegister_TypeDef LCD_PortMaskRegister, uint8_t LCD_Mask)
{
  /* Check function parameters */
  assert_param(IS_LCD_PORT_MASK(LCD_PortMaskRegister));

  /* Copy data bytes to Port mask register */
  LCD->PM[LCD_PortMaskRegister] =  LCD_Mask;

}

/**
  * @brief  Writes a byte in the specific LCD RAM .
  * @param  LCD_RAMRegister: The LCD register index in the RAM matrix.
  *         This parameter can be any of the @ref LCD_RAMRegister_TypeDef
  *         enumeration.
  * @param  LCD_Data : Value to be written
  * @retval None
  */
void LCD_WriteRAM(LCD_RAMRegister_TypeDef LCD_RAMRegister, uint8_t LCD_Data)
{
  /* Check function parameters */
  assert_param(IS_LCD_RAM_REGISTER(LCD_RAMRegister));

  /* Copy data bytes to RAM register */
  LCD->RAM[LCD_RAMRegister] =  LCD_Data;

}

/**
  * @brief  Select the LCD page where the data will be writen.
  * @param  LCD_Page: The accessed LCD page.
  *         This parameter can be any of the @ref LCD_PageSelection_TypeDef
  *         enumeration.
  * @retval None
  */
void LCD_PageSelect(LCD_PageSelection_TypeDef LCD_PageSelection)
{
  /* Check function parameters */
  assert_param(IS_LCD_PAGE_SELECT(LCD_PageSelection));

  LCD->CR4 &= (uint8_t)(~LCD_CR4_PAGECOM); /* Clear the PAGE COM bit */
  LCD->CR4 |= LCD_PageSelection; /* Select the LCD page */

}

/**
  * @brief  Checks whether the LCD start of new frame flag is set or not.
  * @retval FlagStatus : Indicates the state of SPI_FLAG (SET or RESET).
  */
FlagStatus LCD_GetFlagStatus(void)
{
  FlagStatus status = RESET;

  /* Check the status of the start of new frame LCD flag */
  if ((LCD->CR3 & (uint8_t)LCD_CR3_SOF) != (uint8_t)RESET)
  {
    status = SET; /* Flag is set */
  }
  else
  {
    status = RESET; /* Flag is reset*/
  }
  /* Return the FLAG status */
  return status;

}

/**
  * @brief  Clears the start of frame LCD flag.
  * @param  None
  * @retval None
  */
void LCD_ClearFlag(void)
{
  /* Clear the flag bit */
  LCD->CR3 |= (uint8_t)(LCD_CR3_SOFC);

}

/**
  * @brief  Checks whether the start of frame interrupt has occurred or not.
  * @param  None
  * @retval ITStatus : Indicates the state of the start of frame interrupt (SET or RESET).
  */
ITStatus LCD_GetITStatus(void)
{
  ITStatus pendingbitstatus = RESET;
  uint8_t enablestatus = 0;

  enablestatus = (uint8_t)((uint8_t)LCD->CR3 & LCD_CR3_SOFIE);
  /* Check the status of the start of frame interrupt */
  if (((LCD->CR3 & LCD_CR3_SOF) != RESET) && enablestatus)
  {
    /* ITPENDINGBIT is set */
    pendingbitstatus = SET;
  }
  else
  {
    /* ITPENDINGBIT is reset */
    pendingbitstatus = RESET;
  }
  /* Return the ITPENDINGBIT status */
  return  pendingbitstatus;

}

/**
  * @brief  Clears the start of frame interrupt pending bits.
  * @param  None
  * @retval None
  */
void LCD_ClearITPendingBit(void)
{
  /* Clear the flag bit */
  LCD->CR3 |= (uint8_t)(LCD_CR3_SOFC);

}

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
