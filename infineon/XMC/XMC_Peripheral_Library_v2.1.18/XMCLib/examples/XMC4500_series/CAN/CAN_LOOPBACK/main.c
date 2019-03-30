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
 * @date 17 July,2015
 * @version 1.1.0
 *
 * @brief CAN demo example
 *
 * Send a message via CAN using Loopback Mode
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 * Version 1.1.0 Modified API to be compatible with XMCLib 2.0.0  <br>
 *
 */
#include <xmc_can.h>
#include <xmc_gpio.h>

#define LED1 P1_1
#define CAN_FREQUENCY 120000000

/*CAN Bit time*/
XMC_CAN_NODE_NOMINAL_BIT_TIME_CONFIG_t baud = 
{
  .can_frequency = CAN_FREQUENCY,
  .baudrate = 500000,
  .sample_point = 8000,
  .sjw = 1,
};

/*CAN message= CAN_MO4 */
XMC_CAN_MO_t CAN_message_4 = 
{
  .can_mo_ptr = CAN_MO4,
  .can_priority = XMC_CAN_ARBITRATION_MODE_IDE_DIR_BASED_PRIO_2,
  .can_identifier = 0xff,
  .can_id_mask= 0xff,
  .can_id_mode = XMC_CAN_FRAME_TYPE_STANDARD_11BITS,
  .can_ide_mask = 1,
  .can_data_length = 8,
  .can_data = {0x12345555, 0x12345556},
  .can_mo_type = XMC_CAN_MO_TYPE_TRANSMSGOBJ
};

/*CAN message= CAN_MO2 */
XMC_CAN_MO_t CAN_message_2 =
{
  .can_mo_ptr = CAN_MO2,
  .can_priority = XMC_CAN_ARBITRATION_MODE_IDE_DIR_BASED_PRIO_2,
  .can_identifier = 0xff,
  .can_id_mask = 0xff,
  .can_id_mode = XMC_CAN_FRAME_TYPE_STANDARD_11BITS,
  .can_ide_mask = 1,
  .can_data_length = 8,
  .can_mo_type = XMC_CAN_MO_TYPE_RECMSGOBJ
};


int main(void)
{
  /*Led on Board Initialization*/
  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

  /*Configure CAN Module*/
  XMC_CAN_Init(CAN,CAN_FREQUENCY);

  /*Configure CAN Node baudrate*/
  XMC_CAN_NODE_NominalBitTimeConfigure(CAN_NODE2,&baud);
  XMC_CAN_NODE_NominalBitTimeConfigure(CAN_NODE1,&baud);
	
  /*NODE 2 initialization*/
  XMC_CAN_NODE_EnableConfigurationChange(CAN_NODE2);
  XMC_CAN_NODE_EnableLoopBack(CAN_NODE2);
  XMC_CAN_NODE_DisableConfigurationChange(CAN_NODE2);
  XMC_CAN_NODE_ResetInitBit(CAN_NODE2);

   /*NODE 1 initialization*/
  XMC_CAN_NODE_EnableConfigurationChange(CAN_NODE1);
  XMC_CAN_NODE_EnableLoopBack(CAN_NODE1);
  XMC_CAN_NODE_DisableConfigurationChange(CAN_NODE1);
  XMC_CAN_NODE_ResetInitBit(CAN_NODE1);

  /*Message 4 Configuration*/
  XMC_CAN_MO_Config(&CAN_message_4);

  /*Message 2 Configuration*/
  XMC_CAN_MO_Config(&CAN_message_2);

  /*Enable transmit interrupt */
  XMC_CAN_MO_EnableEvent(&CAN_message_2, XMC_CAN_MO_EVENT_RECEIVE);

  /*Set transmit interrupt*/
  XMC_CAN_MO_SetEventNodePointer(&CAN_message_2, XMC_CAN_MO_POINTER_EVENT_RECEIVE, 7);

  /*Allocate MO in Node List*/
  XMC_CAN_AllocateMOtoNodeList(CAN, 1, 2);

  /*Allocate MO in Node List*/
  XMC_CAN_AllocateMOtoNodeList(CAN, 2, 4);

  /*Enable nvic node*/
  NVIC_EnableIRQ(CAN0_7_IRQn);

  /*Send data in CAN_message_4*/
  XMC_CAN_MO_Transmit(&CAN_message_4);

  while(1);
}

/*This function is the Interrupt Event Handler for the CAN Node*/
void CAN0_7_IRQHandler(void)
{
	/* Receive the mensagge in the CAN_message_2 MO*/
  XMC_CAN_MO_Receive(&CAN_message_2);
	/* Switch on LED1  to indicate that the requested message is received*/
  XMC_GPIO_ToggleOutput(LED1);
}
