/*******************************************************************************
 Copyright (c) 2017, Infineon Technologies AG                                 **
 All rights reserved.                                                         **
                                                                              **
 Redistribution and use in source and binary forms, with or without           **
 modification,are permitted provided that the following conditions are met:   **
                                                                              **
 *Redistributions of source code must retain the above copyright notice,      **
 this list of conditions and the following disclaimer.                        **
 *Redistributions in binary form must reproduce the above copyright notice,   **
 this list of conditions and the following disclaimer in the documentation    **
 and/or other materials provided with the distribution.                       **
 *Neither the name of the copyright holders nor the names of its contributors **
 may be used to endorse or promote products derived from this software without**
 specific prior written permission.                                           **
                                                                              **
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  **
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE    **
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE   **
 ARE  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE   **
 LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         **
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF         **
 SUBSTITUTE GOODS OR  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    **
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN      **
 CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)       **
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE   **
 POSSIBILITY OF SUCH DAMAGE.                                                  **
                                                                              **
 To improve the quality of the software, users are encouraged to share        **
 modifications, enhancements or bug fixes with Infineon Technologies AG       **
 dave@infineon.com).                                                          **
                                                                              **
********************************************************************************/

/**
 * @file
 * @date 26 June, 2017
 * @version 1.0.0
 *
 * @brief The example shows how to route the state of the BUTTON2 using the ERU
 *
 * History
 * Version 1.0.0 Initial
 */

#include "xmc_scu.h"
#include "xmc_gpio.h"
#include "xmc_eru.h"

#define TICKS_PER_SECOND 1000
#define LED1 P4_0
#define LED2 P4_1
#define BUTTON1 P3_4

const XMC_ERU_ETL_CONFIG_t eru_etl_config =
{
  .input_a = ERU0_ETL1_INPUTA_SCU_HIB_SR0,
  .source = XMC_ERU_ETL_SOURCE_A,
  .status_flag_mode = XMC_ERU_ETL_STATUS_FLAG_MODE_HWCTRL,
  .edge_detection = XMC_ERU_ETL_EDGE_DETECTION_FALLING
};

volatile uint32_t msTicks;                      /* counts 1ms timeTicks       */
void SysTick_Handler(void) 
{
  msTicks++;
}

/*----------------------------------------------------------------------------
 * delays number of tick Systicks (happens every 1 ms)
 *----------------------------------------------------------------------------*/
static void delay(uint32_t dlyTicks) 
{
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks) 
  { 
    __NOP(); 
  }
}

static uint32_t Buttons_GetState(void) 
{
  uint32_t val = 0;

  val = ((uint32_t)~XMC_GPIO_GetInput(BUTTON1) & 0x1U);

  if (XMC_ERU_ETL_GetStatusFlag(XMC_ERU0, 1) != 0)
  {
    val |= 2;
  }
  
  return val;
}

static void led_init(void)
{
  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetMode(LED2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL); 
}

static void button_init(void)
{
  XMC_GPIO_SetMode(BUTTON1, XMC_GPIO_MODE_INPUT_TRISTATE);

  /* Route BUTTON2(HIB_IO_1) state though ERU */
  XMC_SCU_HIB_EnableHibernateDomain();
  
  XMC_SCU_HIB_SetPinMode(XMC_SCU_HIB_IO_1, XMC_SCU_HIB_PIN_MODE_INPUT_PULL_NONE);
  XMC_SCU_HIB_SetSR0Input(XMC_SCU_HIB_SR0_INPUT_HIB_IO_1);
  while (XMC_SCU_GetMirrorStatus() != 0)
  {
    /* Wait until update of registers in HIB is done */
  }

  XMC_ERU_ETL_Init(XMC_ERU0, 1, &eru_etl_config);
}

int main(void) 
{
  led_init();
  button_init();

  SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

  /* Loop forever */
  while (1) 
  {                    
    if ((Buttons_GetState() & 0x3) == 0)         /* If no button is pressed continue blinking */
    {
      XMC_GPIO_ToggleOutput(LED1);             /* Toggle LED  */
      delay(500);                              /* Delay 500ms  */
    }
  }

}

