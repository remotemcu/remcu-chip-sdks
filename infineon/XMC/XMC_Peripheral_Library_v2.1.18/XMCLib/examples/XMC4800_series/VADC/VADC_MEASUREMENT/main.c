/*
 * Copyright (C) 2015 Infineon Technologies AG. All rights reserved.
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
 * @date 8 October, 2015
 * @version 1.0.0
 *
 * @brief XMC4800 Relax Kit board VADC measurement example
 *
 * This is an example depicting usage of the ADC driver.
 * The ADC driver is used to configure various functional blocks of the
 * peripheral, setting up of a single entry queue and converting the lone
 * entry by means of a software generated queue conversion request periodically
 * in the SysTick handler. The SysTick timer is configured to fire every 10ms.
 * The results are send via UART and can be visualize in a PC using a terminal program
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 *
 */

/*********************************************************************************************************************
 * HEADER FILES
 ********************************************************************************************************************/
#include <stdio.h>

#include <xmc_vadc.h>
#include <xmc_scu.h>
#include <xmc_gpio.h>
#include <xmc_uart.h>

/*********************************************************************************************************************
 * MACROS
 ********************************************************************************************************************/
/* Pin P14.1 is measured and converted */
#define CHANNEL_NUMBER    (7U)
#define VADC_GROUP_PTR    (VADC_G0)  

/* Register result */
#define RES_REG_NUMBER    (0)

/* UART pins */
#define UART_TX P1_5
#define UART_RX P1_4

/* ADC Conversion rate (ms) */
#define TICK_PERIOD (10U)

/*********************************************************************************************************************
 * GLOBAL DATA
 ********************************************************************************************************************/

/* Initialization data of VADC Global resources */
XMC_VADC_GLOBAL_CONFIG_t g_global_config =
{
  .clock_config = 
  {
    .analog_clock_divider  = 3,
    .msb_conversion_clock  = 0,
    .arbiter_clock_divider = 1
  },
};

/* Initialization data of a VADC group */
XMC_VADC_GROUP_CONFIG_t g_group_config =
{
  .class1 = 
  {
    .conversion_mode_standard 	 =  XMC_VADC_CONVMODE_12BIT,
    .sample_time_std_conv 	     = 3U,
  }
};

XMC_VADC_QUEUE_CONFIG_t g_queue_config;

/* Channel configuration data */
XMC_VADC_CHANNEL_CONFIG_t  g_channel_config =
{
  .input_class       = XMC_VADC_CHANNEL_CONV_GROUP_CLASS1,
  .result_reg_number = RES_REG_NUMBER,
  .alias_channel     = XMC_VADC_CHANNEL_ALIAS_DISABLED
};

/* Result configuration data */
XMC_VADC_RESULT_CONFIG_t g_result_config = 
{
  .wait_for_read_mode = true
};

/* Queue Entry */
XMC_VADC_QUEUE_ENTRY_t g_queue_entry = 
{
  .channel_num = CHANNEL_NUMBER,
  .refill_needed = true, /* Refill is needed */
  .generate_interrupt = true, /* Interrupt generation is needed */
  .external_trigger = true  /* External trigger is required */
};

XMC_UART_CH_CONFIG_t uart_config =
{
  .data_bits = 8U,
  .stop_bits = 1U,
  .baudrate = 115200U
};

/*********************************************************************************************************************
 * MAIN APPLICATION
 ********************************************************************************************************************/

/* Result handler */
void VADC0_G0_0_IRQHandler(void)
{
  XMC_VADC_RESULT_SIZE_t result;

  /* Read the result register */
  result = XMC_VADC_GROUP_GetResult(VADC_GROUP_PTR, RES_REG_NUMBER);

  /* Acknowledge the interrupt */
  XMC_VADC_GROUP_QueueClearReqSrcEvent(VADC_GROUP_PTR);
 
  printf("ADC: %d\r\n", result);
}

/* Trigger periodically a conversion request */
void SysTick_Handler(void)
{
  /* Trigger next conversion */
  XMC_VADC_GROUP_QueueTriggerConversion(VADC_GROUP_PTR);  
}

/* Application entry point */
int main(void)
{
  XMC_UART_CH_Init(XMC_UART0_CH0, &uart_config);
  XMC_UART_CH_SetInputSource(XMC_UART0_CH0, XMC_UART_CH_INPUT_RXD, USIC0_C0_DX0_P1_4);
  XMC_UART_CH_Start(XMC_UART0_CH0);

  XMC_GPIO_SetMode(UART_TX, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2);
  XMC_GPIO_SetMode(UART_RX, XMC_GPIO_MODE_INPUT_TRISTATE);
	
  /* Initialize the VADC global registers */
  XMC_VADC_GLOBAL_Init(VADC, &g_global_config);

  /* Configure a conversion kernel */
  XMC_VADC_GROUP_Init(VADC_GROUP_PTR, &g_group_config);

  XMC_VADC_GROUP_QueueInit(VADC_GROUP_PTR, &g_queue_config);
	
  /* Configure a channel belonging to the aforesaid conversion kernel */
  XMC_VADC_GROUP_ChannelInit(VADC_GROUP_PTR,CHANNEL_NUMBER, &g_channel_config);

  /* Configure a result resource belonging to the aforesaid conversion kernel */
  XMC_VADC_GROUP_ResultInit(VADC_GROUP_PTR, RES_REG_NUMBER, &g_result_config);

  /* Add the channel to the queue */
  XMC_VADC_GROUP_QueueInsertChannel(VADC_GROUP_PTR, g_queue_entry);

  /* Connect Request Source Event to the NVIC nodes */
  XMC_VADC_GROUP_QueueSetReqSrcEventInterruptNode(VADC_GROUP_PTR, XMC_VADC_SR_GROUP_SR0);

  /* Enable IRQ */
  NVIC_SetPriority(VADC0_G0_0_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 63, 0));
  NVIC_EnableIRQ(VADC0_G0_0_IRQn);

  /* Enable the analog converters */
  XMC_VADC_GROUP_SetPowerMode(VADC_GROUP_PTR, XMC_VADC_GROUP_POWERMODE_NORMAL);

  /* Perform calibration of the converter */
  XMC_VADC_GLOBAL_StartupCalibration(VADC);

  /* System timer configuration */
  SysTick_Config(SystemCoreClock / TICK_PERIOD);

  while(1);
}
