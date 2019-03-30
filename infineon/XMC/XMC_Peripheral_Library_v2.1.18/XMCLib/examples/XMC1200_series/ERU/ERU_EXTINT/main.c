/*
 * Copyright (C) 2014 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

/**
 * @file
 * @date 04 Dec, 2014
 * @version 1.0.0
 *
 * @brief External interrupt using ERU
 *
 * The user can switch on/off the LED connected to (P0.0) of bootkit board using the potentiometer.
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 *
 */


#include <xmc_gpio.h>
#include <xmc_eru.h>

#define LED P0_0
#define POT P2_5

XMC_ERU_ETL_CONFIG_t button_event_generator_config =
{
  .input = ERU0_ETL1_INPUTA_P2_5,
  .source = XMC_ERU_ETL_SOURCE_A,
  .edge_detection = XMC_ERU_ETL_EDGE_DETECTION_FALLING,
  .status_flag_mode = XMC_ERU_ETL_STATUS_FLAG_MODE_HWCTRL,
  .enable_output_trigger = true,
  .output_trigger_channel = XMC_ERU_ETL_OUTPUT_TRIGGER_CHANNEL0
};

XMC_ERU_OGU_CONFIG_t button_event_detection_config =
{
  .service_request = XMC_ERU_OGU_SERVICE_REQUEST_ON_TRIGGER
};

void ERU0_0_IRQHandler(void)
{
  XMC_GPIO_ToggleOutput(LED);
}

int main(void)
{

  XMC_ERU_ETL_Init(ERU0_ETL1, &button_event_generator_config);
  XMC_ERU_OGU_Init(ERU0_OGU0, &button_event_detection_config);

  XMC_GPIO_CONFIG_t config;

  config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
  config.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH;
  XMC_GPIO_Init(LED, &config);

  config.mode = XMC_GPIO_MODE_INPUT_TRISTATE;
  XMC_GPIO_Init(POT, &config);	

  NVIC_SetPriority(ERU0_0_IRQn, 3U);
  NVIC_EnableIRQ(ERU0_0_IRQn);

  while(1)
  {
	/* Infinite loop */
  }
}
