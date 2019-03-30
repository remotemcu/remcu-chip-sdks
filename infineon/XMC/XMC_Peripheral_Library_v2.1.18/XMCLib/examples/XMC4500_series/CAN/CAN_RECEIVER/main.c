#include <stdio.h>

#include <xmc_gpio.h>
#include <xmc_can.h>

#define LED1 P3_9

// MCAN Node 2
#define CAN_TXD P1_9
#define CAN_RXD P1_8

#define CAN_FREQUENCY 120000000

/* CAN Bit time */
const XMC_CAN_NODE_NOMINAL_BIT_TIME_CONFIG_t baud = 
{
  .can_frequency = CAN_FREQUENCY,
  .baudrate = 500000,
  .sample_point = 8000,
  .sjw = 1,
};

/* CAN message */
XMC_CAN_MO_t CAN_message =
{
  .can_mo_ptr = CAN_MO0,
  .can_priority = XMC_CAN_ARBITRATION_MODE_IDE_DIR_BASED_PRIO_2,
  .can_identifier = 0xff,
  .can_id_mask = 0xff,
  .can_id_mode = XMC_CAN_FRAME_TYPE_STANDARD_11BITS,
  .can_ide_mask = 1,
  .can_data_length = 2,
  .can_mo_type = XMC_CAN_MO_TYPE_RECMSGOBJ
};

/*This function is the Interrupt Event Handler for the CAN Node*/
void CAN0_7_IRQHandler(void)
{
  /* Receive the mensagge in the CAN_message MO*/
  XMC_CAN_MO_Receive(&CAN_message);
	
  printf("ADC result: %d\n", CAN_message.can_data_word[0]);
	
  /* Switch on LED1  to indicate that the requested message is received*/
  XMC_GPIO_ToggleOutput(LED1);
}

#if defined(__GNUC__)
extern void initialise_monitor_handles(void);
#endif

int main(void)
{
#if defined(__GNUC__)
  initialise_monitor_handles();
#endif

  /*Configure CAN Module*/
  XMC_CAN_Init(CAN, CAN_FREQUENCY);

  /*Configure CAN Node baudrate*/
  XMC_CAN_NODE_NominalBitTimeConfigure(CAN_NODE2, &baud);
	
  XMC_CAN_NODE_EnableConfigurationChange(CAN_NODE2);
  XMC_CAN_NODE_SetInitBit(CAN_NODE2);

  /* Configure CAN NODE input pin */
  XMC_GPIO_SetMode(CAN_RXD, XMC_GPIO_MODE_INPUT_TRISTATE);
  XMC_CAN_NODE_SetReceiveInput(CAN_NODE2, XMC_CAN_NODE_RECEIVE_INPUT_RXDCA);

  /*Message Configuration*/
  XMC_CAN_MO_Config(&CAN_message);

  /*Allocate MO in Node List*/
  XMC_CAN_AllocateMOtoNodeList(CAN, 2, 0);
	
  /*Enable transmit interrupt */
  XMC_CAN_MO_EnableEvent(&CAN_message, XMC_CAN_MO_EVENT_RECEIVE);
	
  /*Set transmit interrupt*/
  XMC_CAN_MO_SetEventNodePointer(&CAN_message, XMC_CAN_MO_POINTER_EVENT_RECEIVE, 7);

  /*Enable nvic node*/
  NVIC_EnableIRQ(CAN0_7_IRQn);

  XMC_CAN_NODE_DisableConfigurationChange(CAN_NODE2);
  XMC_CAN_NODE_ResetInitBit(CAN_NODE2);
	
  /* Configure CAN NODE output pin */
  XMC_GPIO_SetMode(CAN_TXD, XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2);

  /* Configure LED pin */
  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);

  while(1);
}

