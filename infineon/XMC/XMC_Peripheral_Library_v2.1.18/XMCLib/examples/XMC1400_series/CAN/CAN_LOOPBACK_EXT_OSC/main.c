/* =========================================================================== *
 * Copyright (c) 2015, Infineon Technologies AG                                *
 * All rights reserved.                                                        *
 *                                                                             *
 * Redistribution and use in source and binary forms, with or without          *
 * modification, are permitted provided that the following conditions are met: *
 * Redistributions of source code must retain the above copyright notice, this *
 * list of conditions and the following disclaimer. Redistributions in binary  *
 * form must reproduce the above copyright notice, this list of conditions and *
 * the following disclaimer in the documentation and/or other materials        *
 * provided with the distribution. Neither the name of the copyright holders   *
 * nor the names of its contributors may be used to endorse or promote         *
 * products derived from this software without specific prior written          *
 * permission.                                                                 *
 *                                                                                                                                                                                                                                                                                                                   *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" *
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,       *
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR      *
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR           *
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,       *
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,         *
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; *
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,    *
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR     *
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF      *
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                                  *
 * To improve the quality of the software, users are encouraged to share       *
 * modifications, enhancements or bug fixes with                               *
 * Infineon Technologies AG (dave@infineon.com).                               *
 *                                                                             *
 * ========================================================================== */

/**
 * @file
 * @date 8 October,2015
 * @version 1.0.0
 *
 * @brief CAN demo example
 *
 * Send a message via CAN using Loopback Mode
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 *
 */
#include <xmc1400.h>
#include <xmc_can.h>
#include <xmc_can_map.h>
#include <xmc_gpio.h>
#include <xmc_scu.h>

#define LED1 P4_0
#define CAN_FREQUENCY 10000000

/*CAN Bit time*/
XMC_CAN_NODE_NOMINAL_BIT_TIME_CONFIG_t baud = 
{
  .can_frequency = CAN_FREQUENCY,
  .baudrate = 1000000,
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

/* LOCAL DATA STRUCTURES */
const XMC_SCU_CLOCK_CONFIG_t clock_config =
{
  .pclk_src = XMC_SCU_CLOCK_PCLKSRC_DOUBLE_MCLK,
  .rtc_src = XMC_SCU_CLOCK_RTCCLKSRC_DCO2,
  .fdiv = 0U,  /**< 8/10 Bit Fractional divider */
  .idiv = 1U,  /**< 8 Bit integer divider */

  .dclk_src = XMC_SCU_CLOCK_DCLKSRC_DCO1,
  .oschp_mode = XMC_SCU_CLOCK_OSCHP_MODE_OSC,
  .osclp_mode = XMC_SCU_CLOCK_OSCLP_MODE_DISABLED

};

/*This function is the Interrupt Event Handler for the CAN Node*/
void IRQ3_Handler(void)
{
	/* Receive the mensagge in the CAN_message_2 MO*/
  XMC_CAN_MO_Receive(&CAN_message_2);
	/* Switch on LED1  to indicate that the requested message is received*/
  XMC_GPIO_ToggleOutput(LED1);
}



int main(void)
{
  /*Led on Board Initialization*/
  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetOutputHigh(LED1);

  /* Configure FDIV, IDIV, PCLKSEL dividers*/
  XMC_SCU_CLOCK_Init(&clock_config);

  /*Configure CAN Module*/
  XMC_CAN_Init(CAN,XMC_CAN_CANCLKSRC_FOHP,CAN_FREQUENCY);

  /*Configure CAN Node baudrate*/
  XMC_CAN_NODE_NominalBitTimeConfigure(CAN_NODE1,&baud);
  XMC_CAN_NODE_NominalBitTimeConfigure(CAN_NODE0,&baud);
	
  /*NODE 2 initialization*/
  XMC_CAN_NODE_EnableConfigurationChange(CAN_NODE1);
  XMC_CAN_NODE_EnableLoopBack(CAN_NODE1);
  XMC_CAN_NODE_DisableConfigurationChange(CAN_NODE1);
  XMC_CAN_NODE_ResetInitBit(CAN_NODE1);

   /*NODE 1 initialization*/
  XMC_CAN_NODE_EnableConfigurationChange(CAN_NODE0);
  XMC_CAN_NODE_EnableLoopBack(CAN_NODE0);
  XMC_CAN_NODE_DisableConfigurationChange(CAN_NODE0);
  XMC_CAN_NODE_ResetInitBit(CAN_NODE0);

  /*Message 4 Configuration*/
  XMC_CAN_MO_Config(&CAN_message_4);

  /*Message 2 Configuration*/
  XMC_CAN_MO_Config(&CAN_message_2);

  /*Enable transmit interrupt */
  XMC_CAN_MO_EnableEvent(&CAN_message_2, XMC_CAN_MO_EVENT_RECEIVE);

  /*Set transmit interrupt*/
  XMC_CAN_MO_SetEventNodePointer(&CAN_message_2, XMC_CAN_MO_POINTER_EVENT_RECEIVE, 0);

  /*Allocate MO in Node List*/
  XMC_CAN_AllocateMOtoNodeList(CAN, 0, 2);

  /*Allocate MO in Node List*/
  XMC_CAN_AllocateMOtoNodeList(CAN, 1, 4);

  /* Interrupt Multiplexer configuration */
  XMC_SCU_SetInterruptControl(3, XMC_SCU_IRQCTRL_CAN0_SR0_IRQ3);

  /*Enable nvic node*/
  NVIC_EnableIRQ(IRQ3_IRQn);

  /*Send data in CAN_message_4*/
  XMC_CAN_MO_Transmit(&CAN_message_4);

  while(1);
}

