/**
  ******************************************************************************
  * @file    stm320518_eval_i2c_tsensor_cpal.h
  * @author  MCD Application Team
  * @version V1.1.1
  * @date    16-January-2014
  * @brief   This file contains all the functions prototypes for the 
  *          stm320518_eval_i2c_tsensor_cpal.c firmware driver.
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
#ifndef __STM320518_EVAL_I2C_TSENSOR_CPAL_H
#define __STM320518_EVAL_I2C_TSENSOR_CPAL_H

#ifdef __cplusplus
 extern "C" {
#endif
   
   
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_i2c_cpal.h"
   
/* Exported types ------------------------------------------------------------*/

/** 
  * @brief  TSENSOR Status  
  */ 
typedef enum
{
  LM75_OK = 0,
  LM75_FAIL
}LM75_Status_TypDef;

/* Exported constants --------------------------------------------------------*/
    
/*====================== CPAL Structure configuration ========================*/ 
/* Select I2C device (uncomment relative define) */

//#define LM75_DevStructure                I2C1_DevStructure   
#define LM75_DevStructure                I2C2_DevStructure  

   
/*============== TIMING Configuration ==========================*/
#define LM75_I2C_TIMING 0x1045061D


/*=================== Programming model Configuration ========================*/
/* Select interrupt programming model : By default DMA programming model is selected.
 To select interrupt programming model uncomment this define */
//#define LM75_IT


/* Maximum Timeout values for waiting until device is ready for communication.*/
   
#define LM75_TIMEOUT        ((uint32_t)0x3FFFF)

/**
  * @brief  Internal register Memory
  */
#define LM75_REG_TEMP       0x00  /* Temperature Register of LM75 */
#define LM75_REG_CONF       0x01  /* Configuration Register of LM75 */
#define LM75_REG_THYS       0x02  /* Temperature Register of LM75 */
#define LM75_REG_TOS        0x03  /* Over-temp Shutdown threshold Register of LM75 */
#define LM75_ADDR           0x90   /* LM75 address */
   

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 

void LM75_DeInit(void);
void LM75_Config(void);
ErrorStatus LM75_GetStatus(void);
uint16_t LM75_ReadTemp(void);
uint16_t LM75_ReadReg(uint8_t RegName);
uint8_t LM75_WriteReg(uint8_t RegName, uint16_t RegValue);
uint8_t LM75_ReadConfReg(void);
uint8_t LM75_WriteConfReg(uint8_t RegValue);
uint8_t LM75_ShutDown(FunctionalState NewState);


 
#ifdef __cplusplus
}
#endif

#endif /* __STM320518_EVAL_I2C_TSENSOR_CPAL_H */
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

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
