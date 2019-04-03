/**
  ******************************************************************************
  * @file    stm32072b_eval.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    16-January-2014
  * @brief   This file contains definitions for STM32072B_EVAL's Leds, push-buttons
  *          and COM ports hardware resources.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32072B_EVAL_H
#define __STM32072B_EVAL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include "stm32_eval_legacy.h"

/** @addtogroup Utilities
  * @{
  */

/** @addtogroup STM32_EVAL
  * @{
  */

/** @addtogroup STM32072B_EVAL
  * @{
  */
      
/** @addtogroup STM32072B_EVAL_LOW_LEVEL
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/
typedef enum 
{
  LED1 = 0,
  LED2 = 1,
  LED3 = 2,
  LED4 = 3
} Led_TypeDef;

typedef enum 
{
  BUTTON_TAMPER = 0,
  BUTTON_RIGHT = 1,
  BUTTON_LEFT = 2,
  BUTTON_UP = 3,
  BUTTON_DOWN = 4,
  BUTTON_SEL = 5
} Button_TypeDef;

typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;

typedef enum 
{ 
  JOY_NONE = 0,
  JOY_SEL = 1,
  JOY_DOWN = 2,
  JOY_LEFT = 3,
  JOY_RIGHT = 4,
  JOY_UP = 5
} JOYState_TypeDef
;

typedef enum 
{
  COM1 = 0,
  COM2 = 1
} COM_TypeDef;   

/* Exported constants --------------------------------------------------------*/
/** @defgroup STM32072B_EVAL_LOW_LEVEL_Exported_Constants
  * @{
  */ 

/** 
  * @brief  Define for STM32072B_EVAL board  
  */ 
#if !defined (USE_STM32072B_EVAL)
 #define USE_STM32072B_EVAL
#endif

/** @addtogroup STM32072B_EVAL_LOW_LEVEL_LED
  * @{
  */
#define LEDn                             4

#define LED1_PIN                         GPIO_Pin_8
#define LED1_GPIO_PORT                   GPIOD
#define LED1_GPIO_CLK                    RCC_AHBPeriph_GPIOD
  
#define LED2_PIN                         GPIO_Pin_9
#define LED2_GPIO_PORT                   GPIOD
#define LED2_GPIO_CLK                    RCC_AHBPeriph_GPIOD
  
#define LED3_PIN                         GPIO_Pin_10
#define LED3_GPIO_PORT                   GPIOD
#define LED3_GPIO_CLK                    RCC_AHBPeriph_GPIOD
  
#define LED4_PIN                         GPIO_Pin_11
#define LED4_GPIO_PORT                   GPIOD
#define LED4_GPIO_CLK                    RCC_AHBPeriph_GPIOD

/**
  * @}
  */ 

/** @addtogroup STM32072B_EVAL_LOW_LEVEL_BUTTON
  * @{
  */  
#define BUTTONn                          6

/**
 * @brief Tamper push-button
 */
#define TAMPER_BUTTON_PIN                GPIO_Pin_13
#define TAMPER_BUTTON_GPIO_PORT          GPIOC
#define TAMPER_BUTTON_GPIO_CLK           RCC_AHBPeriph_GPIOC
#define TAMPER_BUTTON_EXTI_LINE          EXTI_Line13
#define TAMPER_BUTTON_EXTI_PORT_SOURCE   EXTI_PortSourceGPIOC
#define TAMPER_BUTTON_EXTI_PIN_SOURCE    EXTI_PinSource13
#define TAMPER_BUTTON_EXTI_IRQn          EXTI4_15_IRQn 

/**
 * @brief Joystick Right push-button
 */
#define RIGHT_BUTTON_PIN                 GPIO_Pin_3
#define RIGHT_BUTTON_GPIO_PORT           GPIOE
#define RIGHT_BUTTON_GPIO_CLK            RCC_AHBPeriph_GPIOE
#define RIGHT_BUTTON_EXTI_LINE           EXTI_Line3
#define RIGHT_BUTTON_EXTI_PORT_SOURCE    EXTI_PortSourceGPIOE
#define RIGHT_BUTTON_EXTI_PIN_SOURCE     EXTI_PinSource3
#define RIGHT_BUTTON_EXTI_IRQn           EXTI2_3_IRQn

/**
 * @brief Joystick Left push-button
 */
#define LEFT_BUTTON_PIN                  GPIO_Pin_2
#define LEFT_BUTTON_GPIO_PORT            GPIOE
#define LEFT_BUTTON_GPIO_CLK             RCC_AHBPeriph_GPIOE
#define LEFT_BUTTON_EXTI_LINE            EXTI_Line2
#define LEFT_BUTTON_EXTI_PORT_SOURCE     EXTI_PortSourceGPIOE
#define LEFT_BUTTON_EXTI_PIN_SOURCE      EXTI_PinSource2
#define LEFT_BUTTON_EXTI_IRQn            EXTI2_3_IRQn  

/**
 * @brief Joystick Up push-button
 */
#define UP_BUTTON_PIN                    GPIO_Pin_9
#define UP_BUTTON_GPIO_PORT              GPIOF
#define UP_BUTTON_GPIO_CLK               RCC_AHBPeriph_GPIOF
#define UP_BUTTON_EXTI_LINE              EXTI_Line9
#define UP_BUTTON_EXTI_PORT_SOURCE       EXTI_PortSourceGPIOF
#define UP_BUTTON_EXTI_PIN_SOURCE        EXTI_PinSource9
#define UP_BUTTON_EXTI_IRQn              EXTI4_15_IRQn  

/**
 * @brief Joystick Down push-button
 */  
#define DOWN_BUTTON_PIN                  GPIO_Pin_10
#define DOWN_BUTTON_GPIO_PORT            GPIOF
#define DOWN_BUTTON_GPIO_CLK             RCC_AHBPeriph_GPIOF
#define DOWN_BUTTON_EXTI_LINE            EXTI_Line10
#define DOWN_BUTTON_EXTI_PORT_SOURCE     EXTI_PortSourceGPIOF
#define DOWN_BUTTON_EXTI_PIN_SOURCE      EXTI_PinSource10
#define DOWN_BUTTON_EXTI_IRQn            EXTI4_15_IRQn  

/**
 * @brief Joystick Sel push-button
 */
#define SEL_BUTTON_PIN                   GPIO_Pin_0
#define SEL_BUTTON_GPIO_PORT             GPIOA
#define SEL_BUTTON_GPIO_CLK              RCC_AHBPeriph_GPIOA
#define SEL_BUTTON_EXTI_LINE             EXTI_Line0
#define SEL_BUTTON_EXTI_PORT_SOURCE      EXTI_PortSourceGPIOA
#define SEL_BUTTON_EXTI_PIN_SOURCE       EXTI_PinSource0
#define SEL_BUTTON_EXTI_IRQn             EXTI0_1_IRQn 

/**
  * @}
  */ 


/** @addtogroup STM32072B_EVAL_LOW_LEVEL_COM
  * @{
  */
#define COMn                             1

/**
 * @brief Definition for COM port1, connected to USART2
 */ 
#define EVAL_COM1                        USART2
#define EVAL_COM1_CLK                    RCC_APB1Periph_USART2

#define EVAL_COM1_TX_PIN                 GPIO_Pin_5
#define EVAL_COM1_TX_GPIO_PORT           GPIOD
#define EVAL_COM1_TX_GPIO_CLK            RCC_AHBPeriph_GPIOD
#define EVAL_COM1_TX_SOURCE              GPIO_PinSource5
#define EVAL_COM1_TX_AF                  GPIO_AF_0

#define EVAL_COM1_RX_PIN                 GPIO_Pin_6
#define EVAL_COM1_RX_GPIO_PORT           GPIOD
#define EVAL_COM1_RX_GPIO_CLK            RCC_AHBPeriph_GPIOD
#define EVAL_COM1_RX_SOURCE              GPIO_PinSource6
#define EVAL_COM1_RX_AF                  GPIO_AF_0

#define EVAL_COM1_CTS_PIN                GPIO_Pin_3
#define EVAL_COM1_CTS_GPIO_PORT          GPIOD
#define EVAL_COM1_CTS_GPIO_CLK           RCC_AHBPeriph_GPIOD
#define EVAL_COM1_CTS_SOURCE             GPIO_PinSource3
#define EVAL_COM1_CTS_AF                 GPIO_AF_0

#define EVAL_COM1_RTS_PIN                GPIO_Pin_4
#define EVAL_COM1_RTS_GPIO_PORT          GPIOD
#define EVAL_COM1_RTS_GPIO_CLK           RCC_AHBPeriph_GPIOD
#define EVAL_COM1_RTS_SOURCE             GPIO_PinSource4
#define EVAL_COM1_RTS_AF                 GPIO_AF_0
   
#define EVAL_COM1_IRQn                   USART2_IRQn

/**
  * @}
  */

/** @addtogroup STM32072B_EVAL_LOW_LEVEL_SD_SPI
  * @{
  */
/**
  * @brief  SD SPI Interface pins
  */
#define SD_SPI                           SPI1
#define SD_SPI_CLK                       RCC_APB2Periph_SPI1

#define SD_SPI_SCK_PIN                   GPIO_Pin_3                  /* PB.03 */
#define SD_SPI_SCK_GPIO_PORT             GPIOB                       /* GPIOB */
#define SD_SPI_SCK_GPIO_CLK              RCC_AHBPeriph_GPIOB
#define SD_SPI_SCK_SOURCE                GPIO_PinSource3
#define SD_SPI_SCK_AF                    GPIO_AF_0

#define SD_SPI_MISO_PIN                 GPIO_Pin_14                  /* PE.14 */
#define SD_SPI_MISO_GPIO_PORT           GPIOE                       /* GPIOE */
#define SD_SPI_MISO_GPIO_CLK            RCC_AHBPeriph_GPIOE
#define SD_SPI_MISO_SOURCE              GPIO_PinSource14
#define SD_SPI_MISO_AF                  GPIO_AF_1

#define SD_SPI_MOSI_PIN                  GPIO_Pin_15                  /* PE.15 */
#define SD_SPI_MOSI_GPIO_PORT            GPIOE                       /* GPIOE */
#define SD_SPI_MOSI_GPIO_CLK             RCC_AHBPeriph_GPIOE
#define SD_SPI_MOSI_SOURCE               GPIO_PinSource15
#define SD_SPI_MOSI_AF                   GPIO_AF_1

#define SD_CS_PIN                        GPIO_Pin_2                  /* PF.02 */
#define SD_CS_GPIO_PORT                  GPIOF                       /* GPIOF */
#define SD_CS_GPIO_CLK                   RCC_AHBPeriph_GPIOF

#define SD_DETECT_PIN                    GPIO_Pin_15                 /* PB.15 */
#define SD_DETECT_EXTI_LINE              EXTI_Line15
#define SD_DETECT_EXTI_PIN_SOURCE        EXTI_PinSource15
#define SD_DETECT_GPIO_PORT              GPIOB                       /* GPIOB */
#define SD_DETECT_GPIO_CLK               RCC_AHBPeriph_GPIOB
#define SD_DETECT_EXTI_PORT_SOURCE       EXTI_PortSourceGPIOB
#define SD_DETECT_EXTI_IRQn              EXTI4_15_IRQn

/**
  * @}
  */
  
/** @addtogroup STM32072B_EVAL_LOW_LEVEL_LCD_SPI
  * @{
  */
/**
  * @brief  LCD SPI Interface pins
  */  

#define LCD_SPI                       SPI1
#define LCD_SPI_CLK                   RCC_APB2Periph_SPI1

#define LCD_SPI_SCK_PIN               GPIO_Pin_3                     /* PB.03 */
#define LCD_SPI_SCK_GPIO_PORT         GPIOB                          /* GPIOB */
#define LCD_SPI_SCK_GPIO_CLK          RCC_AHBPeriph_GPIOB  
#define LCD_SPI_SCK_SOURCE            GPIO_PinSource3
#define LCD_SPI_SCK_AF                GPIO_AF_0

#define LCD_SPI_MISO_PIN              GPIO_Pin_14                    /* PE.14 */
#define LCD_SPI_MISO_GPIO_PORT        GPIOE                          /* GPIOE */
#define LCD_SPI_MISO_GPIO_CLK         RCC_AHBPeriph_GPIOE
#define LCD_SPI_MISO_SOURCE           GPIO_PinSource14
#define LCD_SPI_MISO_AF               GPIO_AF_1

#define LCD_SPI_MOSI_PIN              GPIO_Pin_15                    /* PA.15 */
#define LCD_SPI_MOSI_GPIO_PORT        GPIOE                          /* GPIOE */
#define LCD_SPI_MOSI_GPIO_CLK         RCC_AHBPeriph_GPIOE  
#define LCD_SPI_MOSI_SOURCE           GPIO_PinSource15
#define LCD_SPI_MOSI_AF               GPIO_AF_1

/** 
  * @brief  LCD Control pins  
  */
  
#define LCD_NCS_PIN                   GPIO_Pin_6                     /* PE.06 */      
#define LCD_NCS_GPIO_PORT             GPIOE                          /* GPIOE */
#define LCD_NCS_GPIO_CLK              RCC_AHBPeriph_GPIOE 


#define LCD_SD_SPI                       SPI1
/**
  * @}
  */  
  
/** @addtogroup STM32072B_EVAL_LOW_LEVEL_TSENSOR_I2C
  * @{
  */
/**
  * @brief  LM75 Temperature Sensor I2C Interface pins
  */
#define LM75_I2C                         I2C1
#define LM75_I2C_CLK                     RCC_APB1Periph_I2C1

#define LM75_I2C_SCL_PIN                 GPIO_Pin_6                  /* PB.6 */
#define LM75_I2C_SCL_GPIO_PORT           GPIOB                       /* GPIOB */
#define LM75_I2C_SCL_GPIO_CLK            RCC_AHBPeriph_GPIOB
#define LM75_I2C_SCL_SOURCE              GPIO_PinSource6
#define LM75_I2C_SCL_AF                  GPIO_AF_1

#define LM75_I2C_SDA_PIN                 GPIO_Pin_7                  /* PB.7 */
#define LM75_I2C_SDA_GPIO_PORT           GPIOB                       /* GPIOB */
#define LM75_I2C_SDA_GPIO_CLK            RCC_AHBPeriph_GPIOB
#define LM75_I2C_SDA_SOURCE              GPIO_PinSource7
#define LM75_I2C_SDA_AF                  GPIO_AF_1

#define LM75_I2C_SMBUSALERT_PIN          GPIO_Pin_5                  /* PB.05 */
#define LM75_I2C_SMBUSALERT_GPIO_PORT    GPIOB                       /* GPIOB */
#define LM75_I2C_SMBUSALERT_GPIO_CLK     RCC_AHBPeriph_GPIOB
#define LM75_I2C_SMBUSALERT_SOURCE       GPIO_PinSource5
#define LM75_I2C_SMBUSALERT_AF           GPIO_AF_3

/**
  * @}
  */
   
/** @addtogroup STM32072B_EVAL_LOW_LEVEL_I2C_EE
  * @{
  */
/**
  * @brief  I2C EEPROM Interface pins
  */  
#define sEE_I2C                          I2C1
#define sEE_I2C_CLK                      RCC_APB1Periph_I2C1
   
#define sEE_I2C_SCL_PIN                  GPIO_Pin_6                  /* PB.06 */
#define sEE_I2C_SCL_GPIO_PORT            GPIOB                       /* GPIOB */
#define sEE_I2C_SCL_GPIO_CLK             RCC_AHBPeriph_GPIOB
#define sEE_I2C_SCL_SOURCE               GPIO_PinSource6
#define sEE_I2C_SCL_AF                   GPIO_AF_1

#define sEE_I2C_SDA_PIN                  GPIO_Pin_7                  /* PB.07 */
#define sEE_I2C_SDA_GPIO_PORT            GPIOB                       /* GPIOB */
#define sEE_I2C_SDA_GPIO_CLK             RCC_AHBPeriph_GPIOB
#define sEE_I2C_SDA_SOURCE               GPIO_PinSource7
#define sEE_I2C_SDA_AF                   GPIO_AF_1

/**
  * @}
  */

/** @addtogroup STM32072B_EVAL_LOW_LEVEL_CEC
  * @{
  */  
/**
  * @brief  HDMI CEC I2C Interface pins
  */
#define HDMI_CEC_I2C_SCL_PIN                                GPIO_Pin_6          /* PB.06 */
#define HDMI_CEC_I2C_SDA_PIN                                GPIO_Pin_7          /* PB.07 */
#define HDMI_CEC_I2C_SCL_PIN_SOURCE                         GPIO_PinSource6
#define HDMI_CEC_I2C_SDA_PIN_SOURCE                         GPIO_PinSource7
#define HDMI_CEC_I2C_GPIO_PORT                              GPIOB               
#define HDMI_CEC_I2C_GPIO_CLK                               RCC_AHBPeriph_GPIOB
#define HDMI_CEC_I2C                                        I2C1
#define HDMI_CEC_I2C_CLK                                    RCC_APB1Periph_I2C1

#define HDMI_CEC_SINK_I2C_SCL_PIN                           GPIO_Pin_13         /* PB.13 */
#define HDMI_CEC_SINK_I2C_SDA_PIN                           GPIO_Pin_14         /* PB.14 */
#define HDMI_CEC_SINK_I2C_SCL_PIN_SOURCE                    GPIO_PinSource13
#define HDMI_CEC_SINK_I2C_SDA_PIN_SOURCE                    GPIO_PinSource14
#define HDMI_CEC_SINK_I2C_GPIO_PORT                         GPIOB
#define HDMI_CEC_SINK_I2C_GPIO_CLK                          RCC_AHBPeriph_GPIOB
#define HDMI_CEC_SINK_I2C                                   I2C2
#define HDMI_CEC_SINK_I2C_CLK                               RCC_APB1Periph_I2C2

/**
  * @brief  HDMI CEC HPD (Hot Plug Detect) Interface pin
  */
#define HDMI_CEC_HPD_SINK_PIN                               GPIO_Pin_15         /* PD.15 */
#define HDMI_CEC_HPD_SINK_GPIO_PORT                         GPIOD
#define HDMI_CEC_HPD_SINK_GPIO_CLK                          RCC_AHBPeriph_GPIOD

/**
  * @brief  HDMI CEC HPD (Hot Plug Detect) Interface pin
  */
#define HDMI_CEC_HPD_SOURCE_PIN                             GPIO_Pin_0          /* PE.00 */
#define HDMI_CEC_HPD_SOURCE_GPIO_PORT                       GPIOE
#define HDMI_CEC_HPD_SOURCE_GPIO_CLK                        RCC_AHBPeriph_GPIOE

/**
  * @brief  HDMI CEC Interface pin
  */
#define HDMI_CEC_LINE_PIN                                   GPIO_Pin_8          /* PB.08 */
#define HDMI_CEC_LINE_GPIO_PORT                             GPIOB
#define HDMI_CEC_LINE_GPIO_CLK                              RCC_AHBPeriph_GPIOB

/**
  * @}
  */  

/** @defgroup STM32072B_EVAL_LOW_LEVEL_Exported_Functions
  * @{
  */
void STM_EVAL_LEDInit(Led_TypeDef Led);
void STM_EVAL_LEDOn(Led_TypeDef Led);
void STM_EVAL_LEDOff(Led_TypeDef Led);
void STM_EVAL_LEDToggle(Led_TypeDef Led);
void STM_EVAL_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode);
uint32_t STM_EVAL_PBGetState(Button_TypeDef Button);
void STM_EVAL_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct);
void SD_LowLevel_DeInit(void);
void SD_LowLevel_Init(void); 
uint8_t STM_SPI_WriteRead(uint8_t Data);
void sFLASH_LowLevel_DeInit(void);
void sFLASH_LowLevel_Init(void);
void LM75_LowLevel_DeInit(void);
void LM75_LowLevel_Init(void);
void sEE_LowLevel_DeInit(void);
void sEE_LowLevel_Init(void); 

/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif /* __STM32072B_EVAL_H */
/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */

/**
  * @}
  */  

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
